// slope for SHMS
void hms_drift_dist(Int_t runNo)
{

  gROOT->SetBatch(1);
 
  
  TFile *f =  new TFile(Form("ROOTfiles/hms_replay_production_all_%d_-1.root", runNo));
  TTree *t = (TTree*)f->Get("T");
  
  TFile *output = new TFile(Form("hms_drift_dist_%d.root", runNo), "RECREATE");

  TH1F * drift_dist[12];

  string plane[12] = {"1u1", "1u2", "1x1", "1x2", "1v2", "1v1", "2v1", "2v2", "2x2", "2x1", "2u2", "2u1"};
 
  // double mean[12];
  // double sigma[12];
  // double fitSigma[12];
  // double fitErrSigma[12];
  // double planes[12];


  double slope [12];
  double slopeErr [12];
  double planes [12];

  TCut time_nhit;
  TCut nhit;

  // TCut cer = "P.ngcer.npeSum>1.0";
  // TCut cal = "P.cal.etot>0.1";
  //TCut pid = cal && cer ;

  //double norm = 0;

  for (int ip = 0; ip<12; ip++)
    {
      time_nhit =  Form("H.dc.%s.time>0.0&&H.dc.%s.time<190.0&&H.dc.%s.nhit==1", plane[ip].c_str(),plane[ip].c_str(),plane[ip].c_str());
 
      drift_dist[ip] = new TH1F(Form("drift_dist_%s", plane[ip].c_str()),  "", 100, -0.01, 0.6 );

      t->Draw(Form("H.dc.%s.dist>>drift_dist_%s", plane[ip].c_str(), plane[ip].c_str()), time_nhit);

      
      // mean[ip] = res[ip]->GetMean();
      // sigma[ip] = res[ip]->GetStdDev();
      //  norm = 1/drift_dist[ip]->GetEntries()
      //	cout << "norm :" << norm <<endl;
      
      // TF1 * myfun = new TF1("myfun","gaus",mean[ip]-sigma[ip],mean[ip]+sigma[ip]); 
      // TF1 *myfunc = new TF1 ("myfunc", "[0]+x*[1]", 0.01, 0.49);
      
      // drift_dist[ip]->Fit("myfunc","R");
      // slope[ip] = myfunc->GetParameter(1);
      // slopeErr[ip]= myfunc->GetParError(1);
      // // h[j]->Draw();
      // planes [ip] = ip+1;
      
      



           
    }

  // TCanvas *c1 = new TCanvas("c1", "", 2000, 500);

  // TGraphErrors * graph = new TGraphErrors(12, planes, slope, 0, slopeErr);
  // graph->SetMarkerStyle(24);
  // graph->SetMarkerColor(2);
  // graph->GetXaxis()->SetTitle("Plane");
  // graph->GetYaxis()->SetTitle("Slope");
  
  // // graph->GetXaxis()->SetRangeUser(0,13);
  // graph->Draw("AP");

  // TLine *tl = new TLine(0,0,graph->GetXaxis()->GetXmax(),0); 
  // tl->Draw();
  // tl->SetLineColor(4);
  // c1->Update();
  
  // output->Write();
  // c1->Write("slopeVsplane");
  // c1->SaveAs("1268_residuals.pdf");
}
