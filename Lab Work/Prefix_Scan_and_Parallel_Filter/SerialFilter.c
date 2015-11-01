#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

void randomArray(int a[],int n)
{
	int i;
	for(i=0;i<n;i++)
		a[i]=rand()%100;
}

double serialFilter(int a[],int n,int filter)
{
	int i,j=0;
	int b[n];
	double start= omp_get_wtime();
	for(i=0;i<n;i++)
		if(a[i]>=filter)
			b[j++]=a[i];
	double stop= omp_get_wtime();	

	//for(i=0;i<j;i++)
	//	printf("%d ",b[i]);
	//printf("\n");
	return (stop-start);
}

void main(int argc,char **argv)
{
	int n=atoi(argv[1]);
	int filter=20;
	int a[n];
	randomArray(a,n);
	double serial_time=serialFilter(a,n,filter);
	printf("%f\n",serial_time);
}

