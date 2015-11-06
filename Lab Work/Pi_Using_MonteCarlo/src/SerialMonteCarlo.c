#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

int main(int argc, char **argv){
	double x, y, dist;
	long long  n, i, fav;
	fav=0;
	n=atof(argv[1]);
	double start = omp_get_wtime();
	srand((unsigned) time(NULL));
	for(i=0.0; i<n; i++){
		x = (double)rand() / (double)RAND_MAX - 0.5;
		y = (double)rand() / (double)RAND_MAX - 0.5;

		dist = (x*x + y*y);
		if(dist < 0.25)	//if distance is less than 0.5 units (no sqrt)
			fav++;
	}
	// printf("Approx. Val. of PI is: %f\n", 4*((double)fav/(double)n));
	// printf("Total Time taken: %f\n", omp_get_wtime()-start);
	printf("%lld %f\n", n, omp_get_wtime()-start);
	return 0;
}
