#include <stdio.h>
#include <math.h>
#include "omp.h"
#include <time.h>

double calcPiParallel(int num_steps)
{
	int no_of_threads=omp_get_max_threads();
	unsigned int k;
	int rank;
	short int factor=1;
	double sum=0.0;
	double start = omp_get_wtime();
	#pragma omp parallel private(k,rank,factor) reduction(+:sum)
	{
		rank=omp_get_thread_num();
		for(k=rank;k<=num_steps;k+=4){
			factor = (rank%2==0)?1:-1;
			sum+=factor/(2.0*k + 1);
		}
	}
	double stop = omp_get_wtime();
	printf("Time taken by parallel function is: %lf\n", (stop-start));
	return 4.0*sum;
}

double calcPiSerial(int num_steps){
	unsigned int k;
	double factor = 1.0;
	double sum = 0.0;
	double start = omp_get_wtime();
	for(k=0; k<=num_steps; ++k){
		sum+=factor/(2*k+1);
		factor*=-1;
	}
	double stop = omp_get_wtime();
	printf("Time taken by serial function is: %lf\n", (stop-start));
	return 4.0*sum;
}

int main(int argc, char **argv){

	int n=atoi(argv[1]);
	double pi = calcPiSerial(n);
	printf("Serial Pi is: %lf\n", pi);
	pi = calcPiParallel(n);
	printf("Prallel Pi is: %lf\n", pi);
	return 0;
}


