#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void randomArray(int a[],long long int n)
{
	long int i;
	for(i=0;i<n;i++)
	{
		a[i]=rand()%100;
	}
//	for(i=0;i<n;i++)
//		printf("%d ",a[i]);
//	printf("\n");
}

int* prefixSumSerialImproved(int* arr, long long int size){
	// printf("prefixSumSerialImproved\n");
	if(size<1){
		printf("Error: Array Size less than 1\n");
		return NULL;
	}
	long long int j;
	for(j=1; j<size; ++j){
		arr[j] = arr[j] + arr[j-1];
	}
	return arr;
}

int* prefixSumSerial(int* arr, long long int size){
	int* ps = (int *) malloc(size*sizeof(int));
	if(size<1){
		printf("Error: Array Size less than 1\n");
		return NULL;
	}
	long long int i;
	ps[0] = arr[0];
	for(i=1; i<size; ++i){
		ps[i] = ps[i-1] + arr[i];
	}
	return ps;
}

int main(int argc, char** argv)
{
  int *t, toread;
	long long int n, i, j, size;

	n=atof(argv[1]);
	int ar[2][n];
int a[n];
	randomArray(a,n);

	double serialStart = omp_get_wtime();
	int* aserial = prefixSumSerial(a, n);
	double serialStop = omp_get_wtime();
	//Serial
	printf("%lf\n", (serialStop-serialStart));
  return 0;
}
