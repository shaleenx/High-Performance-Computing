# Define required macros here
SHELL = /bin/sh

CFLAG = -Wall -g 
CC = gcc
MPI = mpicc
INCLUDE = -fopenmp
LIBS = -lm

all: Parallel_Clustering.c
	${CC} ${INCLUDE} Parallel_Clustering.c ${LIBS}	

clean:
	rm mp mpi ser

