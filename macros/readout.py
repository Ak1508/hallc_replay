#!/usr/bin/env python
import sys
runNo = sys.argv[1]
#raw_input("Enter the run number: ")
#eveNo = $2
#raw_input("Enter the event number: ")
filename = 'REPORT_OUTPUT/SHMS/PRODUCTION/replay_shms_production_%s_50000.report'% (runNo)

f = open(filename)
fout = open('output.txt','w')

for line in f:
    data = line.split(':')
    if('3_of_4 EFF' in data[0]) or ('4_of_4 EFF' in data[0])  or ('BCM1 Current'in data[0]) or ('BCM2 Current'in data[0]) or('BCM4a Current' in data[0]) or ('BCM1  Charge' in data[0]) or ('BCM2  Charge' in data[0])or ('BCM4a Charge' in data[0]) or ('SING FID TRACK EFFIC ' in data[0]):
        
      

         print (data[0]+ ': '+ data[1])
      
         fout.write(data[0]+ ': '+ data[1])

    
   
  	
	

    data2 = line.split('=')
    if 'Ps' in data2[0] and 'factor' in data2[0]:
        
      

         print (data2[0]+ '= '+ data2[1])
      
         fout.write(data2[0]+ '= '+ data2[1])
    
fout.close()
f.close()
