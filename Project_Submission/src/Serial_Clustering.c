#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*  * An n*k array: data[n][k], with n data points and each data point having k dimensions
    * Each data point is recognized by its row index: 0 to n-1

    * Variable no_of_clusters gives the number of clusters
    * An array called center_array[no_of_clusters][k] which stores the center points

    * Essentially, the indices of center_array are the indices of the clusters
    * Output array: output[n] for each data point, tells you to which cluster it belongs (0 to no_of_clusters-1)
*/

int n;
int k;
int no_of_clusters;
double **data;
double **center_array;
int *output;



void takeDataInput()
{
	FILE* f=fopen("input.csv","r");
	
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

	f=fopen("input.csv","r");	
	data=malloc(sizeof(double *)*n);
	for(i=0;i<n;i++)
		data[i]=malloc(sizeof(double *)*k);

	center_array=malloc(sizeof(double *)*no_of_clusters);
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
	//printf("Col: %d Row: %d\n",k,n);
	fclose(f);
	

}



void chooseCenterPointsRandom()	
{
	int i=0;
	int j;
	int center_num;
	bool temp[n];
	for(i=0;i<n;i++) temp[i]=false;
	i=0;
	double seed=1444247712.0;//time(NULL);
	srand((unsigned)seed);
	//printf("%lf\n",seed);
	while(i != no_of_clusters)
	{
		center_num=rand()%n;	// Generate random numbers from 0 to n-1
		if(temp[center_num] == false)
		{
			temp[center_num]=true;
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
	int j;			/* Going through each dimension */
	double distance=0.0;

	for(j=0;j<k;j++)
	{
		distance+=((x[j]-y[j])*(x[j]-y[j]));	
	}
	return sqrt(distance);
}

void update_center(int x,int i)
{
	int j;
	for(j=0;j<k;j++)
	{
		center_array[x][j]=(center_array[x][j]+data[i][j])/2.0;
	}	
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

	/**********************NUMERATOR: NEED TO CALCULATE MINIMUM DISTANCE BETWEEN TWO CLUSTERS***********************************/
	for(x=0;x<no_of_clusters;x++)
		for(y=x+1;y<no_of_clusters;y++)
		{
			inter_cluster_distance= Euclidian_metric(center_array[x],center_array[y]);	
			//printf("Distance between cluster %d and cluster %d is %f\n",x,y,inter_cluster_distance);
			if(inter_cluster_distance < min_inter_cluster_distance)
				min_inter_cluster_distance=inter_cluster_distance;		
		}
	/***********************CALCULATING THE DENOMINATOR********************************/
	for(x=0;x<no_of_clusters;x++)
	{
		size_of_cluster= avg_size_of_cluster(x);
		
		if(size_of_cluster > max_size_of_a_cluster)
			max_size_of_a_cluster=size_of_cluster;
	}
	return (min_inter_cluster_distance/max_size_of_a_cluster);
}

void cluster()
{
	int x;				/* Goes through all the center points */
	int i;				/* Goes through all data points */
	double distance;		/* Gives the distance between the data points based on the metric */
	double min_distance=INT_MAX;	/* This will tell us which cluster to add it to */
	for(i=0;i<n;i++)	
	{
		min_distance=INT_MAX;
		for(x=0;x<no_of_clusters;x++)
		{
			distance=Euclidian_metric(center_array[x],data[i]);
			
			if(distance < min_distance)
			{
				min_distance=distance;
				output[i]=x;			/* Updates the cluster data point i belongs to  */
			}		
		}
		update_center(output[i],i);
	}
}

void start_clustering()
{
	int iterations=10; 
	int i;
	double dunn=0.0;		  
	chooseCenterPointsRandom();
	
	do
	{
		cluster();
		dunn=Dunn_index();
		iterations--;
			
	
	}while(iterations>0);

	for(i=0;i<n;i++) output[i]++;	// to make it a 1 based index
	
}

void main(int argc,char **argv)
{
	no_of_clusters=22;

	takeDataInput();
	start_clustering();

	int i;
	for(i=0;i<n;i++) 
	{
		if(i != n-1)
		printf("%d, ",output[i]);
		else
		printf("%d",output[i]);
	}
}	
