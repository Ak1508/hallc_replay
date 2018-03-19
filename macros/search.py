import re

with open("REPORT_OUTPUT/SHMS/PRODUCTION/replay_shms_production_1680_100000.report", 'r') as in_file:

 for line in in_file:
  if "BCM1 Current" in line:
  # if "Charge" in line:  
    if "Bean" in line:
 
     print line,

 # for line1 in in_file:
  #  if "SHMS Computer Dead Time" in line1:
   #   print line1,
  
 
 
