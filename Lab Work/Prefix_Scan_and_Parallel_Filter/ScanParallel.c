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
}

// int* prefixSumSerialImproved(int* arr, long long int size){
// 	// printf("prefixSumSerialImproved\n");
// 	if(size<1){
// 		printf("Error: Array Size less than 1\n");
// 		return NULL;
// 	}
// 	long long int j;
// 	for(j=1; j<size; ++j){
// 		arr[j] = arr[j] + arr[j-1];
// 	}
// 	return arr;
// }

// int* prefixSumSerial(int* arr, long long int size){
// 	int* ps = (int *) malloc(size*sizeof(int));
// 	if(size<1){
// 		printf("Error: Array Size less than 1\n");
// 		return NULL;
// 	}
// 	long long int i;
// 	ps[0] = arr[0];
// 	for(i=1; i<size; ++i){
// 		ps[i] = ps[i-1] + arr[i];
// 	}
// 	return ps;
// }

int main(int argc, char** argv)
{
  int *t, toread;
	long long int n, i, j, size;

	n=atof(argv[1]);
	int ar[2][n];
int a[n];
	randomArray(a,n);

	// double serialStart = omp_get_wtime();
	// int* aserial = prefixSumSerial(a, n);
	// double serialStop = omp_get_wtime();
	//Serial
	// printf("%lf\n", (serialStop-serialStart));

//  printf("Enter length:");
//  scanf("%d", &n);
//  printf("Enter numbers:\n", n);
  for(i = 0; i < n; i++)
	ar[0][i] = a[i];
//    scanf("%d", &ar[0][i]);
  toread = 1;
  ar[1][0] = ar[0][0];
  size = 0;
  while(i) {
    size++;
    i >>= 1;
  }
	double start = omp_get_wtime();
  for(j = 0; j < size; j++) {
    toread = !toread;
    if(toread) t = ar[0];
    else t = ar[1];
	#pragma omp parallel for default(none) private(i) shared(n, j, t, ar, toread)
	    for(i = 1; i < n; i++) {
	      if(i - (1 << j) >= 0)
		t[i] = ar[toread][i] + ar[toread][i - (1 << j)];
	      else t[i] = ar[toread][i];
	    }
   }
	double stop = omp_get_wtime();
	//Parallel
	printf("%lf\n", (stop-start));

  toread = !toread;
 // for(i = 0; i < n; i++)
//    printf("%d ", *(*(ar + toread) + i));
//	printf("\n");
  return 0;
}
