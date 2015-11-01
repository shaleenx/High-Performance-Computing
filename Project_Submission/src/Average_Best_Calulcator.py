import os

min_clus=10;
min_elas=10;
avg_clus=0;
avg_elas=0;
os.system("gcc -o ./temp Parallel_Clustering.c -lm -fopenmp")
for i in range(0,100):
	os.system("perl hires_time.pl ./temp > temp.txt");
	f=open("temp.txt","r");
	cluster_time=float(f.readline().strip());
	elapsed_time=float(f.readline().strip());
	if cluster_time<min_clus:
		min_clus=cluster_time;
	if elapsed_time<min_elas:
		min_elas=elapsed_time;
	avg_clus+=cluster_time;
	avg_elas+=elapsed_time;
	#print avg_clus, avg_elas;
	f.close()
print "Minimum cluster time: "+str(min_clus)
print "Minimum elapsed time: "+str(min_elas)
print "Average cluster time: "+str(float(avg_clus/100.0))
print "Average elapsed time: "+str(float(avg_elas/100.0))
