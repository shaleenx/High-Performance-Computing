#include <stdio.h>
#include <math.h>
#include "omp.h"

int main(argc,argv)
int argc;
char *argv[];
{
    int done = 0, myid, numprocs;
    unsigned long long i, n;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x, start;

	n=atoll(argv[1]);
	start = omp_get_wtime();
//	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	//if (n == 0) break;
  
	h   = 1.0 / (double) n;
	sum = 0.0;
	//for (i = myid + 1; i <= n; i += numprocs) {
	for(i=1; i<=n; i++){
	    x = h * ((double)i - 0.5);
	    sum += 4.0 / (1.0 + x*x);
	}
	pi = h * sum;
    
	/*MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0,
		   MPI_COMM_WORLD);*/
    
	//if (myid == 0)
	    /*printf("pi is approximately %.16f, Error is %.16f\n",
		   pi, fabs(pi - PI25DT));*/
		printf("%llu %.16f\n", n, omp_get_wtime()-start);
		//printf("%d %.16f\n",n, fabs(pi - PI25DT));
    
//    MPI_Finalize();
    return 0;
}

