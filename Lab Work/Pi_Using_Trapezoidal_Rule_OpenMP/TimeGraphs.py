import os, time
f1 = open("GraphValsSerial.txt", "w")
f2 = open("GraphValsParallel.txt", "w")
f3 = open("GraphValsSpeedUp.txt", "w")
x=10000;
while x<=10000000:
#for x in range(1000,10000000,100):
#	print x
#	print "./serialTrapezoid " + str(x) + " > NvsTime_Serial.txt"
	os.system("./serialTrapezoid " + str(x) + " > NvsTime_Serial.txt");
	os.system("./parallelTrapezoid " + str(x) + " > NvsTime_Parallel.txt");
	s=open("NvsTime_Serial.txt","r")
	p=open("NvsTime_Parallel.txt","r")
#	time.sleep(2)
	y=float(s.readline());	#serial
	z=float(p.readline()); #parallel
	v=y/z;
	#print y
	f1.write(str(x)+ " " + str(y)+ "\n")
	f2.write(str(x)+ " " + str(z)+ "\n")
	f3.write(str(x)+ " " + str(v)+ "\n")
	s.close()
	p.close()
	x = x*2;
