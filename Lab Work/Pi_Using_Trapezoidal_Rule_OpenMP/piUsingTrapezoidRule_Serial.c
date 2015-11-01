#include <stdio.h>
#include "omp.h"

#define f(x) (4.0/(1.0 + x*x))

int main(int argc, char* argv[])
{
	int a,b;
	long long int n;
	a=0;
	b=1;
	n=atoi(argv[1]);
	double length_of_interval=(double)(b-a)/n;
	double x = 0.0;
	double approx=(f(b)-f(a))/2.0;
	int i;
	double start = omp_get_wtime();
	for(i=1;i<n;i++)
	{
		x= a + i*length_of_interval;
		approx+=f(x);
	}
	approx*=length_of_interval;
	double stop = omp_get_wtime();
	printf("%lf\n", (stop-start));
//	printf("Value of pi in serial code is: %f\n",approx);
//	printf("Time taken: %lf milliseconds\n", (stop-start));
	return 0;
}
