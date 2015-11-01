#include <stdio.h>
#include "omp.h"
#include <time.h>
#include <math.h>

/****************************************************************
The main problem here, actually, is the amount of work being done by each task.  In this case, when computing the fibonacci sequence, each "task" is performing almost no work - it's basically just returning a value, or starting a new task.

 

When you parallelize this, the overhead of constructing and launching new tasks is huge compared to the amount of work.  This tends to cause the parallel algorithm to run more slowly, because it has to setup extra work each recursive step.

Overhead: The master creates a new thread, work has to be divided and threads must syncronize at the end.

And a limit to the size: It did not go over 46th fibonacci number = 1836311903

P.S: It is bad load balancing- f[n-1] and f[n-2] almost double the cost 
****************************************************************/




unsigned long long serial(unsigned long long n)
{
	unsigned long long fib[1000];
	fib[0]=1;
	fib[1]=1;
	int i;
	for(i=2;i<n;i++)
	{
		fib[i]=fib[i-1]+fib[i-2];
	}
	//for(i=0;i<=100;i++) printf("%d. %d\n",i,fib[i]);
	return fib[n-1];
}

unsigned long long f[1000];
unsigned long long comp_fib_numbers_rec_serial(unsigned long long n)
{
	unsigned long long fnm1,fnm2;
	if(n==0 || n==1)
 	{
		 f[n]=n;
		 return f[n];
	}

	if(f[n]==0)
	{
		fnm1=comp_fib_numbers_rec_serial(n-1);
		fnm2=comp_fib_numbers_rec_serial(n-2);
		f[n]=fnm1+fnm2;
	}
	return f[n];
}

unsigned long long fp[1000];
unsigned long long comp_fib_numbers_rec_parallel(unsigned long long n)
{
  	if ( n == 0 || n == 1 )
	{
		 fp[n]=n;
		 return fp[n];
	}
  	
	if(fp[n]==0)
	{
		
     		#pragma omp task if(n<20) shared(fp)
      			fp[n-1] = comp_fib_numbers_rec_parallel(n-1);
     		#pragma omp task if(n<20) shared(fp)
       			fp[n-2] = comp_fib_numbers_rec_parallel(n-2);
     		#pragma omp taskwait
       			fp[n]= fp[n-1] + fp[n-2];
		
   	}
	
	return fp[n];
}

int main(int argc, char **argv)
{
	unsigned long long n;
	n=atoi(argv[1]);

	double start_time=omp_get_wtime();
	printf("The %dth fibonacci number is %d\n",n,serial(n));
	double stop_time=omp_get_wtime();
	printf("Time taken by serial code is %f\n",(stop_time-start_time));

	long long f[100];
	double start_time_rec_serial=omp_get_wtime();
	printf("The %dth fibonacci number(recursive serial) is %d\n",n,comp_fib_numbers_rec_serial(n));
	double stop_time_rec_serial=omp_get_wtime();
	printf("Time taken by recursive serial code is: %f\n",(stop_time_rec_serial-start_time_rec_serial));

	double start_time_rec_parallel=omp_get_wtime();
	printf("The %dth fibonacci number(recursive parallel) is %d\n",n,comp_fib_numbers_rec_parallel(n));
	double stop_time_rec_parallel=omp_get_wtime();
	printf("Time taken by recursive parallel code is %f\n",(stop_time_rec_parallel-start_time_rec_parallel));	

	return 0;
}
