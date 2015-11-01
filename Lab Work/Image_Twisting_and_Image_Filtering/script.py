import os
import sys

os.system("gcc imageWarpSerial.c -o WarpSerial -lm -fopenmp")
os.system("gcc imageWarpParallel.c -o WarpParallel -lm -fopenmp")
os.system("gcc imageFilterSerial256.c -o FilterSerial256 -lm -fopenmp")
os.system("gcc imageFilterParallel256.c -o FilterParallel256 -lm -fopenmp")
os.system("gcc imageFilterSerial512.c -o FilterSerial512 -lm -fopenmp")
os.system("gcc imageFilterParallel512.c -o FilterParallel512 -lm -fopenmp")
# os.system("gcc -o parallel parallel.c -fopenmp")
# os.system("gcc -o spmdparallel spmdparallel.c -fopenmp")
# os.system("gcc -o spmdparallelpad spmdparallelpad.c -fopenmp")

# i=1
# while i<16:
f1 = open("Warp", "w")
f2 = open("Filter512", "w")
f3 = open("Filter256", "w")
# f4 = open("Parallel" + str(i), "w")
# f5 = open("Speedup" + str(i), "w")

i=1
while i<17:
	print "i=", i
	# print "i is", i
	os.system("./WarpParallel "+str(i)+" > temp")
	r = open("temp","r")
	a = r.readline()
	f1.write(str(i) + "\t" + a + "\n")
	r.close()
	# print "warp done"
	os.system("./FilterParallel256 "+str(i)+" > temp")
	r = open("temp","r")
	a = r.readline()
	f2.write(str(i) + "\t" + a + "\n")
	r.close()
	
	# print "256 done"
	os.system("./FilterParallel512 "+str(i)+" > temp")
	r = open("temp","r")
	a = r.readline()
	f3.write(str(i) + "\t" + a + "\n")
	r.close()
	i=i+1
	# print "512 done"



# N = 1000

# while(N<100000001):
# 	os.system("./serial " + str(N) + " > temp")
# 	r = open("temp","r")
# 	a = r.readline()
# 	f1.write(str(N) + "\t" + a + "\n")
# 	r.close()
# 	os.system("./spmdparallel " + str(N) + " " + str(i) + " > temp")
# 	r = open("temp","r")
# 	b = r.readline()
# 	f2.write(str(N) + "\t" + b + "\n")
# 	r.close()
# 	os.system("./spmdparallelpad " + str(N) + " " + str(i) + " > temp")
# 	r = open("temp","r")
# 	c = r.readline()
# 	f3.write(str(N) + "\t" + c + "\n")
# 	r.close()
# 	os.system("./parallel " + str(N) + " " + str(i) + " > temp")
# 	r = open("temp","r")
# 	d = r.readline()
# 	f4.write(str(N) + "\t" + d + "\n")
# 	r.close()
# 	os.system("rm temp")
# 	f5.write(str(N) + "\t" + str(float(a)/float(b)) + "\t" + str(float(a)/float(c)) + "\t" + str(float(a)/float(d)) + "\t" +"\n")
# 	N *= 10

f1.close()
f2.close()
f3.close()
# f4.close()
# f5.close()
# i+=1
