//SHMS DC Calibration Class
#ifndef DC_CALIB_H
#define DC_CALIB_H

#define NPLANES 12
#define NBINS 400
#define MINBIN -50.0
#define MAXBIN 350.0
#define TOTAL_BINS 274  
class DC_calib
{
 public:
  
  //consructor and destructor
  DC_calib(TString a, TString b, const Int_t c, Long64_t d);
  ~DC_calib();


  //Define Functions
  void printInitVar();
  void SetPlaneNames();
  void GetDCLeafs();
  void AllocateDynamicArrays();
  void CreateHistoNames();
  void EventLoop();
  void WriteToFile(Int_t debug);
  void CalcT0Historical();
  void Calculate_tZero();
  void GetTwentyPercent_Peak();
  void FitWireDriftTime();
  void WriteTZeroParam();
  void ApplyTZeroCorrection();
  void WriteLookUpTable();
  void GetCard();       //Abishek's method
  void EventLoopCard(); //Abishek
  void GetTwentyPercent_Card();  //Abishek Method
  void FitCardDriftTime();   //Abishek Method

  void ApplyTZeroCorrectionPerCard(); //Abishek Method

  // TString *GetPlaneNames();

 private:
 
  Int_t run_NUM;
  Long64_t num_evts;
 

  TTree *tree;
  Long64_t nentries;
  
  TString SPECTROMETER;
  TString spectre;
  TString spec;
  TString DETECTOR;
  TString plane_names[NPLANES];

  TString base_name;
  TString ndatatime;
  TString ndatawirenum;
  
  TString drifttime;
  TString wirenum;

  TString ntrack;
  TString etracknorm; 
  TString cernpe;
  TString pELCLEAN;

  Double_t dc_ntrack;
  Double_t psh_etracknorm;
  Double_t cer_npe;
  Double_t pEL_CLEAN;

  Int_t wire;
  Int_t card;

  Int_t ndata_time[NPLANES];
  Double_t drift_time[NPLANES][1000];

  Int_t ndata_wirenum[NPLANES];
  Double_t wire_num[NPLANES][1000];

  Int_t nwires[NPLANES];


  //Declare variables to plot and save histo (dt = drift time)
  TString plane_dt_name;
  TString plane_dt_title;

  TString plane_dt_name_corr;
  TString plane_dt_title_corr;


  TString cell_dt_name;
  TString cell_dt_title;

  TString card_hist_name;
  TString card_hist_title;

  TString fitted_card_hist_name;
  TString fitted_card_hist_title;
  
  TString corr_card_hist_name;
  TString corr_card_hist_title;

  TString fitted_cell_dt_name;
  TString fitted_cell_dt_title;  
  
  TString dt_vs_wire_name;
  TString dt_vs_wire_title;

  TString ifile_name;
  TString ofile_name;
  
  TString itxtfile_name;
  TString otxtfile_name;  

  //Declare variables to store histograms
  TH1F *plane_dt;
  TH1F *plane_dt_corr;
  TH1F **cell_dt;
  TH1F **cell_dt_corr;
  TH1F **fitted_cell_dt;
  TH2F *dt_vs_wire;
  TH2F *dt_vs_wire_corr;
  TH1F **card_hist; 
  TH1F **corr_card_hist;

  TH1F **fitted_card_hist;

  

  //Read/Write ROOT files
  TFile *in_file;
  TFile *out_file;
  
  //Read/Write txt files
  ifstream in_txtFILE;
  ofstream out_txtFILE;

  TDirectory *main_dir;


  //Declare 2d dynamic arrays to get histogram bin properties
  
  Int_t **bin_max;
  Int_t **bin_maxContent;
  Double_t **time_max;
  Double_t **twenty_perc_maxContent;
  Double_t **ref_time;

  //variables to be used in loop over bins for wire drift time
  Int_t content_bin;      //stores content for each bin
  Int_t counts;           //a counter used to count the number of bins that have >20% max bin content for a plane 

  vector<Int_t>  content;               //stores bin content
  vector <Int_t> bin_num;               //stores bin number
   

  //Declare 'FIT' related variables
  Int_t **entries;               //wire drift time histo entries
  Int_t **entries_card;
  Int_t binx;
  Double_t time_init;           //start fit value 
  Double_t time_final;          //end fit value
  TF1 *tZero_fit;               //linear fit function

 
  Double_t m;                //slope
  Double_t y_int;            //y-intercept
  Double_t m_err;
  Double_t y_int_err;
  Double_t std_dev;
  Double_t **t_zero;         
  Double_t **t_zero_err;
  Double_t **t_zero_card;         
  Double_t **t_zero_card_err;
  

  //declare variables to make plot of tzero v. wire number
  
  Double_t weighted_avg[NPLANES];
  TGraphErrors *graph;
  TString graph_title;
  TCanvas *gr1_canv;

  //Declare varibales to write LoookUp Table
  Int_t bin_count;
  Int_t bin_t0[NPLANES];
  Int_t bin_final[NPLANES];
  Int_t bin_Content[NPLANES];
  Double_t binContent_TOTAL[NPLANES];
  Double_t binSUM[NPLANES];
  Double_t lookup_value[NPLANES];
  TString lookup_table;
  TString headers;

  //Declare variables to apply constant offset in time
  Double_t offset;
  Double_t max_wire_entry;

  //Abishek's Varibales for Abishek's Class
  Int_t **wire_min;
  Int_t **wire_max;
  Double_t **wireBinContentMax;
  Double_t **wireBinContentLow;
  Double_t **wireBinContentHigh;
  Double_t **wireBinHigh;
  Double_t **wireBinLow;
  Double_t **wireFitRangeLow;
  Double_t **wireFitRangeHigh;
  Int_t plane_cards[NPLANES];
  //Variable to store values for 80 to 20 percernt fit
  Int_t binContentMax, binContentLow, binContentHigh, binValLow, binValHigh, binSearchLow, binSearchHigh;

  Double_t binDiffThresh;
  

};


#endif  //DC_CALIBRATION_H
