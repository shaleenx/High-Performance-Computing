#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

void randomArray(int a[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		a[i]=rand()%100;
	}
}


double parallelFilter(int a[],int n,int filter)
{
	int bv[2][n];
	int i=n;

	int *t, toread, size, j;
	
	toread = 1;
	bv[1][0] = bv[0][0];
	size = 0;
	while(i) 
	{
		size++;
    		i >>= 1;
  	}
	int b[n];

	double start= omp_get_wtime();

	#pragma omp schdule(dynamic,1) for 
		for(i=0;i<n;i++)
			if(a[i]>=filter)
				bv[0][i]=1;
			else
				bv[0][i]=0;
	
	

	for(j = 0; j < size; j++) 
	{
    		toread = !toread;

    		if(toread) 
			t = bv[0];
    		else 
			t = bv[1];

		#pragma omp parallel for default(none) private(i) shared(n, j, t, bv, toread)
    		for(i = 1; i < n; i++) 
		{
      			if(i - (1 << j) >= 0)
				t[i] = bv[toread][i] + bv[toread][i - (1 << j)];
      			else 
				t[i] = bv[toread][i];
    		}
  	}
	toread = !toread;


	
	bv[toread][n]=-1;
	if(bv[toread][0]==1)
		b[0] = a[0];
	
	#pragma omp schdule(static) for
	for(i=1;i<n;i++)
	{
		if(bv[toread][i] > bv[toread][i-1])
			b[bv[toread][i]-1] = a[i];
//		if(bv[toread][i] != 0 && bv[toread][i+1]>bv[toread][i])
//		b[bv[toread][i]-1]=a[i];		
	}
	double stop= omp_get_wtime();	
	//for(i=0;i<n;i++)
	//	printf("%d ",b[i]);
	//printf("\n");
	return (stop-start);
}

void main(int argc,char **argv)
{
	int n=atoi(argv[1]);
	int filter=50;
	int a[n];
	randomArray(a,n);
	double parallel_time=parallelFilter(a,n,filter);
	printf("%f\n",parallel_time);
}
