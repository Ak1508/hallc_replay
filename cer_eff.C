void cer_eff()
{
  TFile *myFile = new TFile("ROOTfiles/shms_replay_production_all_1665_-1.root");

   TTreeReader myReader("T", myFile);


   TH1F *deltaHist = new TH1F("h1", "delta", 60, -10, 20);
   TH1F *calHist = new TH1F("h2", "cal", 100, 0.0, 2.0);
   TH1F *W2Hist = new TH1F("h3", "W2", 100, 0.001, 5.0);
   TH1F *npeHist = new TH1F("h4", "npeSum", 100, 0, 10);
   TH1F *h1 = new TH1F("hist1", "", 100, 0, 5);
   TH1F *h2 = new TH1F("hist2", "", 100, 0, 5);


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
	    
	    if (*delta>-10.0 && *delta <20.0)
	      {
		h1->Fill(*cal);
		
		if (*cal>0.8 && *npe>3 && *W2>0.8 && *W2< 1.5)
		  {
		    h2->Fill(*cal);
		  }
	      }//end of delta

	  	
      }//end of while
    
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

    double deno_elec = h1->GetEntries();
    double num_elec = h2->GetEntries();
 
    cout <<"eff :"<< num_elec/deno_elec <<endl;
    
    
}//end of void
