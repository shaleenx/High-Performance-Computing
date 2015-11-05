#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "omp.h"


/*  * An n*k array: data[n][k], with n data points and each data point having k dimensions
    * Each data point is recognized by its row index: 0 to n-1

    * Variable no_of_clusters gives the number of clusters
    * An array called center_array[no_of_clusters][k] which stores the center points

    * Essentially, the indices of center_array are the indices of the clusters
    * Output array: output[n] for each data point, tells you to which cluster it belongs (1 to no_of_clusters)
*/

int n;
int k;
double dunn=0.0;		  
int no_of_clusters;
double **data;
double **center_array;
int *output;



void takeDataInput()
{
	FILE* f=fopen("HiPC2015_IntelData_40k.csv","r");
	
	if(f==NULL){
		printf("ERROR OPENING FILE\n");
		exit(1);
	}

	//Find the number of rows and columns in the .csv file
	int i,j;
	char temp[1],tempRead[1];
	while(1){
		fscanf(f,"%c",temp);
		if(*temp=='\n'){
			n++;
			break;
		}
		else if(*temp==',')
			k++;		// counting the number of commas: no. of columns = no. of commas+1
	}
	k++;

	while(1){
		if(fscanf(f,"%c",temp)==EOF)
			break;
		else if(*temp=='\n'){
			n++;
		}
	}
	
	fclose(f);

	f=fopen("HiPC2015_IntelData_40k.csv","r");	
	data=malloc(sizeof(double *)*n);
	#pragma omp for
	for(i=0;i<n;i++)
		data[i]=malloc(sizeof(double *)*k);

	center_array=malloc(sizeof(double *)*no_of_clusters);
	#pragma omp for
	for(i=0;i<no_of_clusters;i++)
		center_array[i]=malloc(sizeof(double *)*k);

	output=malloc(sizeof(double *)*n);	

	double val;
	for(i=0;i<n;i++){
		for(j=0;j<k;j++){
			fscanf(f,"%lf",&val);
			fscanf(f,"%c",tempRead);
			data[i][j]=val;
			
		}
	}
	fclose(f);
	

}



void chooseCenterPointsRandom()	
{
	int i=0;
	int j;
	int center_num;
	bool temp[n];
	#pragma omp for
	for(i=0;i<n;i++) 
		temp[i]=false;
	i=0;
	double seed=1444247712.0;
	srand((unsigned)seed);
	while(i != no_of_clusters)
	{
		center_num=rand()%n;	// Generate random numbers from 0 to n-1
		if(temp[center_num] == false)
		{
			temp[center_num]=true;
			#pragma omp for
			for(j=0;j<k;j++)
			{
				center_array[i][j]=data[center_num][j];			
			}
			i++;
		} 	 			
	}
}

double Euclidian_metric(double x[],double y[])
{
	int j;			
	double distance=0.0;

	//#pragma omp for
	for(j=0;j<k;j++)
	{
		distance+=((x[j]-y[j])*(x[j]-y[j]));	
	}
	return sqrt(distance);
}

double avg_size_of_cluster(int x)
{
	int i;	
	double sum=0.0;
	int count=0;	
	for(i=0;i<no_of_clusters;i++)
	{
		if(output[i]==x)		/* If the data point i belongs to cluster x   */
		{
			count++;
			sum+=(Euclidian_metric(center_array[x],data[i]));		
		}
	}
	return (sum/count);	
		
}

double Dunn_index()
{
	double inter_cluster_distance=0.0;		/* FOR NUMERATOR */
	double min_inter_cluster_distance=INT_MAX;

	double max_size_of_a_cluster=INT_MIN;		/* FOR DENOMINATOR */
	double size_of_cluster=0.0;
	
	int x,y;

	for(x=0;x<no_of_clusters;x++)
		for(y=x+1;y<no_of_clusters;y++)
		{
			inter_cluster_distance= Euclidian_metric(center_array[x],center_array[y]);	
			if(inter_cluster_distance < min_inter_cluster_distance)
				min_inter_cluster_distance=inter_cluster_distance;		
		}
	for(x=0;x<no_of_clusters;x++)
	{
		size_of_cluster= avg_size_of_cluster(x);
		
		if(size_of_cluster > max_size_of_a_cluster)
			max_size_of_a_cluster=size_of_cluster;
	}
	return (min_inter_cluster_distance/max_size_of_a_cluster);
}


void main(int argc,char **argv)
{
	no_of_clusters=22;
	int iterations=10; 
	int i,j,x;
	
	double input_start=omp_get_wtime();
	takeDataInput();
	double input_stop=omp_get_wtime();
	//printf("Time taken by data input is: %f\n",(input_stop-input_start));

	double center_start=omp_get_wtime();
	chooseCenterPointsRandom();
	double center_stop=omp_get_wtime();
	//printf("Time taken for center array allocation is: %f\n",(center_stop-center_start));
		
	double distance;		/* Gives the distance between the data points based on the metric */
	double min_distance;	/* This will tell us which cluster to add it to */
	int rank;
	int max_threads;
	
	double cluster_start=omp_get_wtime();
	do
	{
		#pragma omp parallel shared(output,no_of_clusters,center_array,max_threads,data,k,n) private(i,j,x,rank,distance,min_distance) default(none)
		{
			rank=omp_get_thread_num();
			max_threads=omp_get_num_threads();
			for(i=rank;i<n;i+=max_threads)	
			{
				min_distance=INT_MAX;
				for(x=0;x<no_of_clusters;x++)
				{
					distance=0.0;

					for(j=0;j<k;j++)
					{
						distance+=((center_array[x][j]-data[i][j])*(center_array[x][j]-data[i][j]));	
					}
					distance= sqrt(distance);



					if(distance < min_distance)
					{
						min_distance=distance;
						output[i]=x;			
					}
					
				}
				
				#pragma omp critical
				for(j=0;j<k;j++)
				{
					center_array[output[i]][j]=(center_array[output[i]][j]+data[i][j])/2.0;
				}
			}
		}
		iterations--;
	}while(iterations>0);

	#pragma omp for		
	for(i=0;i<n;i++) output[i]++;	// to make it a 1 based index
	
	
	double cluster_stop=omp_get_wtime();
	
	dunn=Dunn_index();
	//	printf("Time taken in clustering is: %f\n",(cluster_stop-cluster_start));
	//	printf("Dunn Index is: %f\n",dunn);

	for(i=0;i<n;i++) 
	{
		if(i != n-1)
		printf("%d, ",output[i]);
		else
		printf("%d\n",output[i]);
	}
}