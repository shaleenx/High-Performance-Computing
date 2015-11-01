#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

long long a[2][2];
long long b[2][2];
long long FibNumber(long long n)
{
	int i, j, k;
	int p;
	long long c[2][2];
	double start=omp_get_wtime();
	#pragma omp for private(p,c)
	for(p=3;p<=n;p++)
	{ 
		#pragma omp parallel shared(a,b,c) private(i,j,k)
			{
  				#pragma omp for
  				for (i=0; i<2; i++)    
   	 			{
    					for(j=0; j<2; j++)
					{ 
						c[i][j]=0;      
      						for (k=0; k<2; k++)
        						c[i][j] += a[i][k] * b[k][j];
					}
    				}
  			}
	
		for(i=0;i<2;i++)
			for(j=0;j<2;j++)
				b[i][j]=c[i][j];
	}
	double stop=omp_get_wtime();
	printf("%f\n",(stop-start));
	return b[0][0];   
}

int main (int argc, char *argv[]) 
{
	int n=atoi(argv[1]);
	a[0][0]=a[0][1]=a[1][0]=1;
	a[1][1]=0;
	b[0][0]=b[0][1]=b[1][0]=1;
	b[1][1]=0;
	FibNumber(n);
	//printf("%dth fibonacci number is %d\n",n,FibNumber(n));
}

