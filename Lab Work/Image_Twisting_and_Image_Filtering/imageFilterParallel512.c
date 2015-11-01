#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

char sort(char* temp){
	int j,k, min;
	for(j=0;j<49;++j)
	{
		min=temp[j];
		for(k=j;k<49;++k)
		{
			if(temp[k]<min)
			{
				min=temp[k];
			}
		}
		temp[j]=min;	
	}
	return temp[24];
}

int main(int argc, char** argv){

	FILE *fp= fopen("lena512.bmp", "rb");
	FILE *f = fopen("ShaleenlenaFilterParallel.bmp", "wb");

	if (fp == NULL){
		printf("Error while opening file");
		exit(0);
	}

	if (f == NULL){
		printf("Error while creating new file to write into\n");
		exit(0);
	}

	int temp=0;

	fseek(fp, 18,SEEK_SET);
	fread(&temp, sizeof(int), 1, fp);
	int width = temp;

	fseek(fp, 22,SEEK_SET);
	fread(&temp, sizeof(int), 1, fp);
	int height = temp;
	
	fseek(fp, 34,SEEK_SET);
	fread(&temp, sizeof(int), 1, fp);
	
	fseek(fp, 0,SEEK_SET);

	int i, j, var;
	int re;
	int pixInit[temp];
	int pixFinal[temp];

	j=0;
//	printf("Size: %d",temp);	

	int t = atoi(argv[1]);
	#pragma omp parallel for shared(i) num_threads(t)
	for(i=1;i<(54+temp);++i){

		fread(&re, sizeof(char), 1, fp);		
		if(i>=54)		
		{
			var=(int)re;
			//var=var/2;
			re=(char)var;
			pixInit[j++]=re;
			fwrite(&re, 1, sizeof(char), f);
		}		
		else
			fwrite(&re, 1, sizeof(char), f);

	}

	double timeInit=omp_get_wtime();	
	i=0;
	j=0;
	var=0;
	char arr[512][512];

	#pragma omp parallel for shared(i, j) num_threads(t)
	for(i=0;i<512;++i)
		for(j=0;j<512;++j)
			arr[i][j]=pixInit[var++];

	char temp1[49];				
	int m,n,o,p;
	int IS=0;
	int w,z;

	#pragma omp parallel for shared(m, n, temp1) num_threads(t)
	for(m=0;m<512;++m)
	{
		for(n=0;n<512;++n)
		{
			if(m>=3 && n>=3 && m<=508 && n<=508)
			{
				IS=0;
				for(w=m-3;w<=(m+3);++w)
					for(z=n-3;z<=(n+3);++z)
					{	//printf("In %d %d\n",w, z);	
						temp1[IS++]=arr[w][z];	
}
				arr[m][n]=sort(temp1);

			}
		}				
	}

	i=0;
	fseek(f, 54, SEEK_SET);

	#pragma omp parallel for shared(m, n, re) num_threads(t)
	for(m=0;m<512;++m)
	{
		for(n=0;n<512;++n)
		{
			re=arr[m][n];
			fwrite(&re, 1, sizeof(char), f);
		}
	}
	
	double timeFinal=omp_get_wtime();
	printf("%lf\n",(timeFinal-timeInit));
}
