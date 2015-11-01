#include <stdio.h>
#include "omp.h"

#define f(x) (4.0/(1.0 + x*x))

int main(int argc, char* argv[])
{
	int a,b;
	long long int n;
	a=0;
	b=1;
	n=atoi(argv[1]);//10000000;
	double length_of_interval=(double)(b-a)/n;
	//double x = 0.0;
	double approx=(f(b)-f(a))/2.0;
	double local_approx[4];
	double start = omp_get_wtime();
	#pragma omp parallel num_threads(4)
	{
		int i;
		double x=0.0;
		int rank=omp_get_thread_num();
		local_approx[rank]=approx;
		for(i=rank;i<n;i+=4)
		{
			x= a + i*length_of_interval;
			local_approx[rank]+=f(x);
		}
//		local_approx*=length_of_interval;
//		approx+=local_approx;
	}
	approx=local_approx[0]+local_approx[1]+local_approx[2]+local_approx[3];
	approx*=length_of_interval;
	double stop = omp_get_wtime();
	printf("%lf\n",(stop-start));
//	printf("Value of pi in parallel code is: %f\n",approx);
//	printf("Time taken: %lf milliseconds\n", (stop-start));
	return 0;
}
