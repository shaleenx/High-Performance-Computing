# Define required macros here
SHELL = /bin/sh

CFLAG = -Wall -g 
CC = gcc
MPI = mpicc
INCLUDE = -fopenmp
LIBS = -lm

all: Vertigo_phase2.c
	${CC} ${INCLUDE} Vertigo_phase2.c ${LIBS}	

clean:
	rm mp mpi ser

