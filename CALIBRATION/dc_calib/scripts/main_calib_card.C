//Main Calibration Code
#include "DC_calib_card.h"
#include "DC_calib_card.C"
#include <iostream>
#include <ctime>
using namespace std;

int main_calib_card()
{

  //prevent root from displaying graphs while executing
  gROOT->SetBatch(1);


  //measure execution time
  clock_t cl;
  cl = clock();


  DC_calib obj("HMS", "../../../ROOTfiles/hms_replay_production_all_1616_old.root", 1616,200000);
  // DC_calib obj("HMS", "../../ROOTfiles/hms_coin_replay_production_166_1000000.root", 1616, 1000000);

 
  //  obj.printInitVar();
  obj.SetPlaneNames();
  obj.GetDCLeafs();
  obj.AllocateDynamicArrays();
  obj.CreateHistoNames();
  obj.GetCard();
  obj.EventLoopCard();
  obj.Calculate_tZero();
  obj.WriteTZeroParam();
  obj.ApplyTZeroCorrectionPerCard();
  obj.WriteLookUpTable();
  obj.WriteToFile(1);  //set argument to (1) for debugging

  
 

  //stop clock
  cl = clock() - cl;
 cout << "execution time: " << cl/(double)CLOCKS_PER_SEC << " sec" << endl;

  return 0;
}
