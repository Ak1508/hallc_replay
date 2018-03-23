//slope for hms 
void slope_hms(string spectro, string spec, Int_t runNo)
{

  gROOT->SetBatch(1);
  
  string filename = Form("ROOTfiles/%s_replay_production_all_%d_-1.root", spec.c_str(), runNo);
 
  
  TFile *f =  new TFile(filename.c_str());
  
  TTree *t = (TTree*)f->Get("T");
  
  TFile *output = new TFile(Form("output_%d_Slope.root",runNo), "RECREATE");
  
  TH1F * drift_dist[12];
  

  double slope [12];
  double slopeErr [12];
  double planes [12];

  // TCut cut = "H.cer.npeSum>1.0";
  TCut nhit;
  TCut time;

  // string *plane[12];
  

      
  // if (spec=="hms")
  // {
  //  cout << "Doing HMS . . . " << endl;
      //HMS
  string plane[12] = {"1u1", "1u2", "1x1", "1x2", "1v2", "1v1", "2v1", "2v2", "2x2", "2x1", "2u2", "2u1"};
      // }
      // if (spec=="shms")
      //  {
      //cout << "Doing HMS . . . " << endl;
      //HMS
  //  string plane[12] = {"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2v2", "2v1", "2x2", "2x1", "2u2", "2u1"};
  //  }
  

  for (int ip = 0; ip<12; ip++)
    {
      nhit = Form("%s.dc.%s.nhit==1", spectro.c_str(), plane[ip].c_str());
      time =  Form("H.dc.%s.time<190.0&&H.dc.%s.time>0.0",plane[ip].c_str(), plane[ip].c_str());
      drift_dist[ip] = new TH1F(Form("drift_dist_%s", plane[ip].c_str()),  "", 100, -0.01, 0.6 );
      t->Draw(Form("H.dc.%s.dist>>drift_dist_%s", plane[ip].c_str(), plane[ip].c_str()), time&&nhit);
      // mean[ip] = res[ip]->GetMean();
      // sigma[ip] = res[ip]->GetStdDev();

      // TF1 * myfun = new TF1("myfun","gaus",mean[ip]-sigma[ip],mean[ip]+sigma[ip]); 
      TF1 *myfunc = new TF1 ("myfunc", "[0]+x*[1]", 0.01, 0.49);

      drift_dist[ip]->Fit("myfunc","R");
      slope[ip] = myfunc->GetParameter(1);
      slopeErr[ip]= myfunc->GetParError(1);
      // h[j]->Draw();
      planes [ip] = ip+1;
      
      



      // res[ip]->Fit("myfun","R");
      // fitSigma[ip] = myfun->GetParameter(2);
      // fitErrSigma[ip]= myfun->GetParError(2);
      // planes[ip]=ip+1;
      // cout << "Mean of plane " << plane[ip] << " = " << mean[ip] << endl;
      // cout <<"std of plane :" << plane[ip] << " = " << sigma[ip]<<endl;
      // cout << "sigma :" <<   fitSigma[ip]<<endl;  
      
      //output->Close();
      // cout <<  fitErrSigma[ip]<<endl;
	      
    }
    


TCanvas *c1 = new TCanvas("c1", "", 2000, 500);

  TGraphErrors * graph = new TGraphErrors(12, planes, slope, 0, slopeErr);
  graph->SetMarkerStyle(24);
  graph->SetMarkerColor(2);
  graph->GetXaxis()->SetTitle("Plane");
  graph->GetYaxis()->SetTitle("Slope");
  
  // graph->GetXaxis()->SetRangeUser(0,13);
  graph->Draw("AP");

  TLine *tl = new TLine(0,0,graph->GetXaxis()->GetXmax(),0); 
  tl->Draw();
  tl->SetLineColor(4);
  c1->Update();
  
  output->Write();
  c1->Write("slopeVsplane");
  // c1->SaveAs("1268_residuals.pdf");
}
