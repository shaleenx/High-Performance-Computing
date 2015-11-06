#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

int main(int argc, char **argv){
	double x, y, dist;
	struct drand48_data drand_buf;
	long long n, i, fav;
	int threads = atoi(argv[2]);
	fav=0;
	n=atof(argv[1]);
	double start = omp_get_wtime();
	#pragma omp parallel num_threads(threads) private(x, y, dist, drand_buf)
	{
		srand48_r ((unsigned) time(NULL), &drand_buf);
		#pragma omp for reduction(+: fav) 
		for(i=0.0; i<n; i++){
			drand48_r(&drand_buf, &x);//(double)rand() / (double)RAND_MAX - 0.5;
			drand48_r(&drand_buf, &y);//y = (double)rand() / (double)RAND_MAX - 0.5;
			x -= 0.5;
			y -= 0.5;

			dist = (x*x + y*y);
			if(dist < 0.25)
				fav++;
		}
	}
	//printf("Approx. Val. of PI is: %f\n", 4*((double)fav/(double)n));
	//printf("Total Time taken: %f\n", omp_get_wtime()-start);
	printf("%lld %f\n", n, omp_get_wtime()-start);
	return 0;
}
