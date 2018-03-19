#! /bin/bash

SPEC=SHMS
# Which spectrometer are we analyzing.
#spec=${0##*_}
#spec=${spec%%.sh}
#SPEC=$(echo "$spec" | tr '[:lower:]' '[:upper:]')

# What is the last run number for the spectrometer.
# The pre-fix zero must be stripped because ROOT is ... well ROOT
# 


# Which run to analyze.
runNum=$1
if [ -z "$runNum" ]; then
  runNum=2248
fi

# How many events to analyze.
numEvents=$2

# Which scripts to run.
#script="SCRIPTS/${SPEC}/PRODUCTION/readout.py"
script="/net/cdaqfs/home/cdaq/abishek/hallc_replay/readout.py"

# Which commands to run.
runpy="$script $runNum $numEvents"


# Name of the replay ROOT file
# Where to put log.
#summaryFile="REPORT_OUTPUT/${SPEC}/PRODUCTION/run_summary_${runNum}.txt"
summaryFile="run_summary_${runNum}.txt"
outfile="output.txt"


# Start analysis and monitoring plots.
{
  echo ""
  echo ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:="
  echo ""  
  date
  echo ""
  echo "Running ${SPEC} analysis on the run ${runNum}:"
  echo " -> SCRIPT:  ${script}"
  echo " -> RUN:     ${runNum}"
  echo " -> NEVENTS: ${numEvents}"
  echo " -> COMMAND: ${runpy}"
  echo ""
  echo ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:="

  sleep 2
  eval ${runpy}
  mv $outfile $summaryFile
} 

