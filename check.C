//reading the leaf from root file  like P.dc.1u1.dist

#define NPLANES 12
#define NBINS 100
#define bin_min -0.1
#define bin_max 0.6


void check()
  
{
  gROOT->SetBatch(1);
  // Long64_t num_evts;       
  
  TString file_name = "ROOTfiles/shms_replay_production_all_1791_1000000.root";
  
  //open file
  TFile *f = new TFile(file_name, "READ");
  
  TFile * output =  new TFile ("output_1791_driftdist_slope.root","RECREATE");
  
  f->cd();

  //Get the tree
  TTree *tree = (TTree*)f->Get("T");
  TString SPECTROMETER="P";
  TString DETECTOR="dc";
  TString plane_names[NPLANES]={"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2v2", "2v1", "2x2", "2x1", "2u2", "2u1"};
  
  //Declare Variables to Loop Over
  Int_t Ndata[NPLANES];
  Double_t pdc_time[NPLANES][1000];
  Double_t pdc_dist[NPLANES][1000];
  Double_t cer_npeSum, cal;
  Double_t Ndata_hit[NPLANES];
  //Declare Histogram array to store AVG drift times per plane
  TH1F* h[NPLANES];
  TCanvas *c[NPLANES];
  
  //Loop over each plane
  for(Int_t ip=0; ip<NPLANES; ip++)
    {
      TString base_name = SPECTROMETER+"."+DETECTOR+"."+plane_names[ip];
      TString ndata_name = "Ndata."+base_name+".time";
      TString drift_time = base_name+".time";
      TString drift_dist = base_name+".dist";
      TString ndata_hit = base_name + ".nhit";
      // cout << drift_dist<<endl;
      // Int_t           Ndata_H_dc_1x1_dist;
      // Double_t        H_dc_1x1_dist[65];
      
      TString drift_time_histo = "pdc"+plane_names[ip]+"_time"; 
      TString title = "P_"+plane_names[ip]+"_driftdist";
      TString distplane = drift_dist;
     
      //  cout <<" distplane :"<<distplane<< endl;
      
      
      //Set Branch Address
      tree->SetBranchAddress(drift_time, pdc_time[ip]);
      tree->SetBranchAddress(drift_dist, pdc_dist[ip]); 
      tree->SetBranchAddress(ndata_name, &Ndata[ip]);
      tree->SetBranchAddress(ndata_hit, &Ndata_hit[ip]);
      
      
      //Create Histograms
      h[ip] = new TH1F(distplane, title, NBINS, bin_min, bin_max);              
      h[ip]->GetXaxis()->SetTitle("Drift Dist (cm)");
      h[ip]->GetYaxis()->SetTitle("Number of Entries");
      
      // h[ip]->Draw();
      
      
    }  
  
  tree->SetBranchAddress("P.ngcer.npeSum",&cer_npeSum);
  tree->SetBranchAddress("P.cal.etot", &cal);
  
  Long64_t nentries = tree->GetEntries();
 
  for(Long64_t i=0; i<nentries; i++)
    {
      tree->GetEntry(i);
      
      for(Int_t ip=0; ip<NPLANES; ip++)
	{
	   
	  
	  for(Int_t j=0; j<Ndata[ip]; j++)
	    {
	      if (cer_npeSum>1.0 && pdc_time[ip][j]<190.0 && Ndata_hit[ip] ==1.0 && cal>0.1)
		{
		  h[ip]->Fill(pdc_dist[ip][j]);
		}
	    }//end loop over hits
	  
	}//end loop over planes
      
      
    }//end loop over entries
  
  TF1 *myfunc = new TF1 ("myfunc", "[0]+x*[1]", 0.01, 0.49);
  double slope [NPLANES];
  double slopeErr [NPLANES];
  double plane [NPLANES];
  for (int j = 0; j<NPLANES; j++)
    {
      c[j]= new TCanvas(Form("name%d",j), " ", 400, 400);
      h[j]->Fit("myfunc","R");
      slope[j] = myfunc->GetParameter(1);
      slopeErr[j]= myfunc->GetParError(1);
      h[j]->Draw();
      plane [j] = j+1;
      cout<<"SLope: "<<slope[j]<<endl;
    }

  TCanvas *c1 = new TCanvas("c1","", 400, 400);
  
  TGraphErrors *gr = new TGraphErrors(NPLANES, plane, slope, 0 , slopeErr);
  c1->cd();
  gr->Draw("AP");
  gr->SetMarkerStyle(20);
  gr->SetMarkerColor(2);
  gr->GetXaxis()->SetTitle("Planes");
  gr->GetYaxis()->SetTitle("slope");
  // TLine *tl = new TLine(0,0,12,0);
  TLine *tl = new TLine(0,0,gr->GetXaxis()->GetXmax(),0); 
  tl->Draw();
  tl->SetLineColor(2);
  // c1->SaveAs("1791_slope.pdf");
  c1->Update();

  output->Write();
  c1->Write("Drift_dis_planeVsSlope");
}//end of void 

