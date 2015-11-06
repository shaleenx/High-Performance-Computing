#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char **argv){
	double x, y, dist;
	long long n, i, fav;
	unsigned long myfav = 0;
	fav=0;
	n=atof(argv[1]);
	srand((unsigned) time(NULL));

	int numprocs, myid;
	
	MPI_Init(&argc, &argv);
	double start = MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
	for(i=myid; i<n; i+=numprocs){
		x = (double)rand() / (double)RAND_MAX - 0.5;
		y = (double)rand() / (double)RAND_MAX - 0.5;

		dist = (x*x + y*y);
		if(dist < 0.25)
			myfav++;
	}
	MPI_Reduce(&myfav, &fav, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if (myid == 0){
		// printf("pi is approximately %f\n", 4*((double)fav/(double)n));
		// printf("Time taken is: %f\n", MPI_Wtime()-start);
		printf("%lld %f", n, MPI_Wtime()-start);
		// printf("Time taken is: %f\n", MPI_Wtime()-start);
	}
	MPI_Finalize();
	return 0;
}
