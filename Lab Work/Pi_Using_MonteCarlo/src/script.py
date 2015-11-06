import os

#Removing Old files
os.system("rm nvst_serial nvst_omp_4 nvst_omp_8 nvst_omp_16 nvst_mpi_4cores nvst_mpi_8cores nvst_mpi_16cores")
os.system("rm speedup_omp_4 speedup_omp_8 speedup_omp_16 speedup_mpi_4cores speedup_mpi_8cores speedup_mpi_16cores")

#Compiling everything
print "Compiling SerialMonteCarlo..."
os.system("gcc -o SerialMonteCarlo SerialMonteCarlo.c -fopenmp")
print "Compiling OMPMonteCarlo..."
os.system("gcc -o OMPMonteCarlo OMPMonteCarlo.c -fopenmp")
print "Compiling MPIMonteCarlo (MPI)..."
os.system("mpicc -o MPIMonteCarlo MPIMonteCarlo.c")

#Executing the Serial Code
print "Executing the Serial Code..."
i=10000;
while i<=1000000000:
	os.system("./SerialMonteCarlo " + str(i) + " >> nvst_serial");
	i = i*5;
os.system("./SerialMonteCarlo 2000000000 >> nvst_serial");
print "Serial Code Execution Over"

#Executing the OMP code for 4 threads
print "Executing the OMP code for 4 threads..."
i=10000
while i<=1000000000:
	os.system("./OMPMonteCarlo " + str(i) + " 4 >> nvst_omp_4");
	i = i*5;
os.system("./OMPMonteCarlo 2000000000 4 >> nvst_omp_4");
print "OMP Code Excution Over for 4 threads"


#Executing the OMP code for 8 threads
print "Executing the OMP code for 8 threads..."
i=10000
while i<=1000000000:
	os.system("./OMPMonteCarlo " + str(i) + " 8 >> nvst_omp_8");
	i = i*5;
os.system("./OMPMonteCarlo 2000000000 8 >> nvst_omp_8");
print "OMP Code Excution Over for 8 threads"


#Executing the OMP code for 16 threads
print "Executing the OMP code for 16 threads..."
i=10000
while i<=1000000000:
	os.system("./OMPMonteCarlo " + str(i) + " 16 >> nvst_omp_16");
	i = i*5;
os.system("./OMPMonteCarlo 2000000000 16 >> nvst_omp_16");
print "OMP Code Excution Over for 16 threads"

#Executing the MPI Code with 4 cores
print "Executing the MPI Code with 4 cores..."
i=10000
while i<=1000000000:
	os.system("mpirun -np 4 ./MPIMonteCarlo " + str(i) + " >> nvst_mpi_4cores");
	i = i*5;
os.system("mpirun -np 4 ./MPIMonteCarlo 2000000000 >> nvst_mpi_4cores");
print "MPI Code Execution Over on 4 cores"

#Executing the MPI Code with 8 cores
print "Executing the MPI Code with 8 cores..."
i=10000
while i<=1000000000:
	os.system("mpirun -np 8 ./MPIMonteCarlo " + str(i) + " >> nvst_mpi_8cores");
	i = i*5;
os.system("mpirun -np 8 ./MPIMonteCarlo 2000000000 >> nvst_mpi_8cores");
print "MPI Code Execution Over on 8 cores"

#Executing the MPI Code with 16 cores
print "Executing the MPI Code with 16 cores..."
i=10000
while i<=1000000000:
	os.system("mpirun -np 16 ./MPIMonteCarlo " + str(i) + " >> nvst_mpi_16cores");
	i = i*5;
os.system("mpirun -np 16 ./MPIMonteCarlo 2000000000 >> nvst_mpi_16cores");
print "MPI Code Execution Over on 16 cores"

#Calculating Speedup for OMP for 4 threads
print "Calculating Speedup for OMP for 4 threads"
f1 = open("nvst_omp_4", "r")
f2 = open("nvst_serial", "r")
f3 = open("speedup_omp_4", "w")
for line in f1.readlines():
	line1 = line.split()
	line2 = f2.readline().split()
	f3.write(str(line1[0]) + " " + str(float(line2[1])/float(line1[1])) + "\n")
f1.close()
f2.close()
f3.close()

#Calculating Speedup for OMP for 9 threds
print "Calculating Speedup for OMP for 8 threads"
f1 = open("nvst_omp_8", "r")
f2 = open("nvst_serial", "r")
f3 = open("speedup_omp_8", "w")
for line in f1.readlines():
	line1 = line.split()
	line2 = f2.readline().split()
	f3.write(str(line1[0]) + " " + str(float(line2[1])/float(line1[1])) + "\n")
f1.close()
f2.close()
f3.close()

#Calculating Speedup for OMP for 16 threads
print "Calculating Speedup for OMP for 16 threads"
f1 = open("nvst_omp_16", "r")
f2 = open("nvst_serial", "r")
f3 = open("speedup_omp_16", "w")
for line in f1.readlines():
	line1 = line.split()
	line2 = f2.readline().split()
	f3.write(str(line1[0]) + " " + str(float(line2[1])/float(line1[1])) + "\n")
f1.close()
f2.close()
f3.close()


#Calculating Speedup for MPI on 4 cores
print "Calculating Speedup for MPI on 4 cores"
f1 = open("nvst_mpi_4cores", "r")
f2 = open("nvst_serial", "r")
f3 = open("speedup_mpi_4cores", "w")
for line in f1.readlines():
	line1 = line.split()
	line2 = f2.readline().split()
	f3.write(str(line1[0]) + " " + str(float(line2[1])/float(line1[1])) + "\n")
f1.close()
f2.close()
f3.close()


#Calculating Speedup for MPI on 8 cores
print "Calculating Speedup for MPI on 8 cores"
f1 = open("nvst_mpi_8cores", "r")
f2 = open("nvst_serial", "r")
f3 = open("speedup_mpi_8cores", "w")
for line in f1.readlines():
	line1 = line.split()
	line2 = f2.readline().split()
	f3.write(str(line1[0]) + " " + str(float(line2[1])/float(line1[1])) + "\n")
f1.close()
f2.close()
f3.close()


#Calculating Speedup for MPI on 16 cores
print "Calculating Speedup for MPI on 16 cores"
f1 = open("nvst_mpi_16cores", "r")
f2 = open("nvst_serial", "r")
f3 = open("speedup_mpi_16cores", "w")
for line in f1.readlines():
	line1 = line.split()
	line2 = f2.readline().split()
	f3.write(str(line1[0]) + " " + str(float(line2[1])/float(line1[1])) + "\n")
f1.close()
f2.close()
f3.close()