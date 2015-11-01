import os

#Removing Old files
os.system("rm nvst_serial nvst_omp nvst_4cores nvst_8cores nvst_16cores")

#Compiling everything
print "Compiling fpi_serial..."
os.system("gcc -o fpi_serial fpi_serial.c -fopenmp")
print "Compiling fpi_omp..."
os.system("gcc -o fpi_omp fpi_omp.c -fopenmp")
print "Compiling fpi (MPI)..."
os.system("mpicc -o fpi fpi.c")

#Executing the Serial Code
print "Executing the Serial Code..."
i=10000
while i<=1000000000:
	os.system("./fpi_serial " + str(i) + " >> nvst_serial");
	i = i*5;
os.system("./fpi_serial 2000000000 >> nvst_serial");
print "Serial Code Execution Over"

#Executing the OMP code
print "Executing the OMP code..."
i=10000
while i<=1000000000:
	os.system("./fpi_omp " + str(i) + " >> nvst_omp");
	i = i*5;
os.system("./fpi_omp 2000000000 >> nvst_omp");
print "OMP Code Excution Over"

#Executing the MPI Code with 4 cores
print "Executing the MPI Code with 4 cores..."
i=10000
while i<=1000000000:
	os.system("mpirun -np 4 ./fpi " + str(i) + " >> nvst_4cores");
	i = i*5;
os.system("mpirun -np 4 ./fpi 2000000000 >> nvst_4cores");
print "MPI Code Execution Over on 4 cores"

#Executing the MPI Code with 8 cores
print "Executing the MPI Code with 8 cores..."
i=10000
while i<=1000000000:
	os.system("mpirun -np 8 ./fpi " + str(i) + " >> nvst_8cores");
	i = i*5;
os.system("mpirun -np 8 ./fpi 2000000000 >> nvst_8cores");
print "MPI Code Execution Over on 8 cores"

#Executing the MPI Code with 16 cores
print "Executing the MPI Code with 16 cores..."
i=10000
while i<=1000000000:
	os.system("mpirun -np 16 ./fpi " + str(i) + " >> nvst_16cores");
	i = i*5;
os.system("mpirun -np 16 ./fpi 2000000000 >> nvst_16cores");
print "MPI Code Execution Over on 16 cores"

#Calculating Speedup for OMP
print "Calculating Speedup for OMP"
f1 = open("nvst_omp", "r")
f2 = open("nvst_serial", "r")
f3 = open("speedup_omp", "w")
for line in f1.readlines():
	line1 = line.split()
	line2 = f2.readline().split()
	f3.write(str(line1[0]) + " " + str(float(line2[1])/float(line1[1])) + "\n")
f1.close()
f2.close()
f3.close()


#Calculating Speedup for MPI on 4 cores
print "Calculating Speedup for MPI on 4 cores"
f1 = open("nvst_4cores", "r")
f2 = open("nvst_serial", "r")
f3 = open("speedup_4cores", "w")
for line in f1.readlines():
	line1 = line.split()
	line2 = f2.readline().split()
	f3.write(str(line1[0]) + " " + str(float(line2[1])/float(line1[1])) + "\n")
f1.close()
f2.close()
f3.close()


#Calculating Speedup for MPI on 8 cores
print "Calculating Speedup for MPI on 8 cores"
f1 = open("nvst_8cores", "r")
f2 = open("nvst_serial", "r")
f3 = open("speedup_8cores", "w")
for line in f1.readlines():
	line1 = line.split()
	line2 = f2.readline().split()
	f3.write(str(line1[0]) + " " + str(float(line2[1])/float(line1[1])) + "\n")
f1.close()
f2.close()
f3.close()


#Calculating Speedup for MPI on 16 cores
print "Calculating Speedup for MPI on 16 cores"
f1 = open("nvst_16cores", "r")
f2 = open("nvst_serial", "r")
f3 = open("speedup_16cores", "w")
for line in f1.readlines():
	line1 = line.split()
	line2 = f2.readline().split()
	f3.write(str(line1[0]) + " " + str(float(line2[1])/float(line1[1])) + "\n")
f1.close()
f2.close()
f3.close()