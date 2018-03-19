#! /bin/bash

# Which spectrometer are we analyzing.
spec=${0##*_}
spec=${spec%%.sh}
SPEC=$(echo "$spec" | tr '[:lower:]' '[:upper:]')

# What is the last run number for the spectrometer.
# The pre-fix zero must be stripped because ROOT is ... well ROOT
lastRun=$( \
    ls raw/"${spec}"_all_*.dat raw/../raw.copiedtotape/"${spec}"_all_*.dat -R 2>/dev/null | perl -ne 'if(/0*(\d+)/) {print "$1\n"}' | sort -n | tail -1 \
)

# Which run to analyze.
runNum=$1
if [ -z "$runNum" ]; then
  runNum=$lastRun
fi

# How many events to analyze.
numEvents=50000

# Which scripts to run.
script="SCRIPTS/${SPEC}/PRODUCTION/replay_production_${spec}.C"
config="CONFIG/${SPEC}/PRODUCTION/${spec}_production.cfg"

# Which commands to run.
runHcana="./hcana -q \"${script}(${runNum}, ${numEvents})\""
runOnlineGUI="./online -f ${config} -r ${runNum}"
#saveOnlineGUI="./online -f ${config} -r ${runNum} -P"
runReportMon="./readout_hms.py ${runNum} ${numEvents}"

# DEfine report monitoring directory
reportMonDir="UTIL/REPORT_MON/${SPEC}/"

#Define where to put the REPORT_MON
ReportMon="emacs ../../../REPORT_MONITOR/reportMonitor_${spec}_production_${runNum}_${numEvents}.txt"

pathReportMon="../../../REPORT_MONITOR/reportMonitor_${spec}_production_${runNum}_${numEvents}.txt"

# Name of the replay ROOT file
rootFileDir="./ROOTfiles"
replayFile="${spec}_replay_production_${runNum}"
rootFile="${replayFile}_${numEvents}.root"
latestRootFile="${rootFileDir}/${replayFile}_latest.root"

# Where to put log.
reportFile="REPORT_OUTPUT/${SPEC}/PRODUCTION/replay_${spec}_production_${runNum}_${numEvents}.txt"
summaryFile="REPORT_OUTPUT/${SPEC}/PRODUCTION/summary_production_${runNum}_${numEvents}.txt"

# Names of the monitoring file
monRootDir="./HISTOGRAMS/${SPEC}/ROOT"
monPdfDir="./HISTOGRAMS/${SPEC}/PDF"
monRootFile="${spec}_production_${runNum}.root"
monPdfFile="${spec}_production_${runNum}.pdf"
latestMonRootFile="${monRootDir}/${spec}_production_latest.root"
latestMonPdfFile="${monPdfDir}/${spec}_production_latest.pdf"

# What is base name of onlineGUI output.
outFile="${spec}_production_${runNum}"
outFileMonitor="output"
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
  echo " -> COMMAND: ${runHcana}"
  echo ""
  echo ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:="

  sleep 2
  eval ${runHcana}

  # Link the ROOT file to latest for online monitoring
  ln -fs ${rootFile} ${latestRootFile}

  echo ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:="
  echo ""
  echo "Running onlineGUI for analyzed ${SPEC} run ${runNum}:"
  echo " -> CONFIG:  ${config}"
  echo " -> RUN:     ${runNum}"
  echo " -> COMMAND: ${runOnlineGUI}"
  echo ""
  echo ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:="

  sleep 2
  cd onlineGUI
  eval ${runOnlineGUI}
  mv "${outFile}.pdf" "../HISTOGRAMS/${SPEC}/PDF/${outFile}.pdf"
  mv "${outFile}.root" "../HISTOGRAMS/${SPEC}/ROOT/${outFile}.root"
  cd ..
  ln -fs ${monRootFile} ${latestMonRootFile}
  ln -fs ${monPdfFile} ${latestMonPdfFile}

  echo ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:="
  echo ""
  echo "Done analyzing ${SPEC} run ${runNum}."
  echo ""
  echo ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:="
sleep 2

  echo ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:="
  echo ""
  echo "Generating report file monitoring data file ${SPEC} run ${runNum}."
  echo ""
  echo ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:="
  cd ${reportMonDir}
  eval ${runReportMon}
  mv "${outFileMonitor}.txt" ${pathReportMon}
  eval ${ReportMon}

sleep 2

  echo ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:="
  echo ""
  echo "Done producing report file monitoring data file ${SPEC} run ${runNum}."
  echo ""
  echo ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:="

  echo ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:="
  echo ""
  echo "So long and thanks for all the fish!"
  echo ""
  echo ":=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:="

} 2>&1 | tee "${reportFile}"
2>&1 | tee "${summaryFile}"
