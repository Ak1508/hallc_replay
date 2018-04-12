void cer_eff()
{
  TFile *myFile = new TFile("ROOTfiles/shms_replay_production_all_2485_-1.root");

   TTreeReader myReader("T", myFile);


   TH1F *deltaHist = new TH1F("h1", "delta", 60, -10, 20);
   TH1F *calHist = new TH1F("h2", "cal", 100, 0.0, 1.4);
   TH1F *W2Hist = new TH1F("h3", "W2", 100, -10.0, 20.0);
   TH1F *npeHist = new TH1F("h4", "npeSum", 100, 0.0, 50.0);
   TH1F *h2 = new TH1F("h2_hist", "num", 100, 0.0, 2.0);
   TH1D *h1[7];
   for (int k =0; k<7; k++)
    {
      h1[k] = new TH1D(Form("h%d_hist",k), " ", 100, 0.0, 1.5);
    }
   
   Double_t npe_cut[7]={1, 1.5, 2, 4, 6, 8, 10};
   Double_t eff[7];

   TTreeReaderValue<Double_t> delta(myReader, "P.gtr.dp");

   TTreeReaderValue<Double_t> cal(myReader, "P.cal.etracknorm");

   TTreeReaderValue<Double_t> W2(myReader, "P.kin.W2");

   TTreeReaderValue<Double_t> npe(myReader, "P.ngcer.npeSum");

   while (myReader.Next()) 
      {
	
	if (*cal>0.001)
	      {
		calHist->Fill(*cal);
	      }
	    
	    deltaHist->Fill(*delta);
	    
	    //	x_jHist->Fill(*x_j);
	    if(*npe>0)
	      {
		npeHist->Fill(*npe);
	      }
	    W2Hist->Fill(*W2);
	    
	    if (*delta >-10.0 && *delta <20.0)
	      {
		if (*cal>0.8)
		  {
		    h2->Fill(*cal);
		  }
		for (int j = 0; j < 7 ; j++)// looping over the no of photoelectrons	  
		  {
		    
		    if(*cal>0.8 && *npe>npe_cut[j])
		      
		      {
			
			h1[j]->Fill(*cal);
		      }
		  }//end of for loop
	      }//end of delta    
      }//end of while

   Double_t num;
   Double_t deno = h2->GetEntries();
   for (int j = 0; j<7 ; j++)
     { 
       num = h1[j]->GetEntries();
       eff[j]= num/deno;
       cout << "efficiency :"<< eff[j]<<endl;
     }
   TGraph *gr1 = new TGraph(7, npe_cut, eff);
   TCanvas *c1 = new TCanvas ("c1","  ", 400, 400);
   c1->Divide(3,2);
   
   c1->cd(1);
   calHist->Draw();
   
   c1->cd(2);
   deltaHist->Draw();
   
   c1->cd(3);
   W2Hist->Draw();
   
   c1->cd(4);
   npeHist->Draw();
   
   c1->cd(5);
   gr1->Draw("AP*");
   gr1->SetTitle("Effciency");
   gr1->GetXaxis()->SetTitle("NPE cut");
   gr1->GetYaxis()->SetTitle("Elec Efficiency");
   
}//end of void
