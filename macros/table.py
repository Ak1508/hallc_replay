#!/usr/bin/env python
import sys
import csv
import os

#runNo = sys.argv[1] #for giving the run no argument
outputfile="table_shms.txt"
inputfile = "output_shms.txt" #%(runNo)

fd = open(inputfile,'r')
columns=[]
rows=[]

for line in fd:
	#print(line)
	line= line.strip()
	'''if  line=='':
		continue'''
	splits=line.split(":")
	columns.append(splits[0].strip())
	
#if you need values only for the plotting

	x = splits[1].strip()
	y = x.split(' ')
	value = y[0]
	print y,value
	rows.append(value)

	#rows.append(splits[1].strip())

	

#print columns
#print row
fd.close()

if os.access(outputfile,os.F_OK):

	#print outputfile
	ftest = open(outputfile)
	ltest = ftest.readlines()[1:]
	ltest = [x.split('\t')[0] for x in ltest]
	#print ltest
	if rows[0] in ltest:
		print 'run', rows[0], 'is already in database'
		sys.exit(0)
#write columns head
if not os.access(outputfile,os.F_OK):
	with open(outputfile,'w') as fd:
		for i in range(len(columns)):
			fd.write(columns[i])
			fd.write("\t")

		fd.write("\n")
		

#write rows
with open(outputfile,"a") as fd:
	#writer=csv.writer(fd,lineterminator='\n')
	for i in range(0, len(rows)):
                	fd.write(rows[i])
			fd.write("\t")
	fd.write("\n")
		
