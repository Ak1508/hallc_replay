void residual()
{

  gROOT->SetBatch(1);
  
  
  TFile *f =  new TFile("ROOTfiles/hms_replay_production_all_1268_1000000.root");
  TTree *t = (TTree*)f->Get("T");
  
  TFile *output = new TFile("output.root", "RECREATE");
  /*
  TH1F *res_1u1 = new TH1F("res_1u1", "1U1 Plane Residuals", 100, -0.1, 0.1);
  TH1F *res_1u2 = new TH1F("res_1u2", "1U2 Plane Residuals", 100, -0.1, 0.1);
  TH1F *res_1x1 = new TH1F("res_1x1", "1X1 Plane Residuals", 100, -0.1, 0.1);
  TH1F *res_1x2 = new TH1F("res_1x2", "1X2 Plane Residuals", 100, -0.1, 0.1);
  TH1F *res_1v1 = new TH1F("res_1v1", "1V1 Plane Residuals", 100, -0.1, 0.1);
  TH1F *res_1v2 = new TH1F("res_1v2", "1V2 Plane Residuals", 100, -0.1, 0.1);
  
  TH1F *res_2u1 = new TH1F("res_2u1", "2U1 Plane Residuals", 100, -0.1, 0.1);
  TH1F *res_2u2 = new TH1F("res_2u2", "2U2 Plane Residuals", 100, -0.1, 0.1);
  TH1F *res_2x1 = new TH1F("res_2x1", "2X1 Plane Residuals", 100, -0.1, 0.1);
  TH1F *res_2x2 = new TH1F("res_2x2", "2X2 Plane Residuals", 100, -0.1, 0.1);
  TH1F *res_2v1 = new TH1F("res_2v1", "2V1 Plane Residuals", 100, -0.1, 0.1);
  TH1F *res_2v2 = new TH1F("res_2v2", "2V2 Plane Residuals", 100, -0.1, 0.1);
  */
  TH1F * res[12];
  
  

  string plane[12] = {"1u1", "1u2", "1x1", "1x2", "1v2", "1v1", "2v1", "2v2", "2x2", "2x1", "2u2", "2u1"};
  // TCanvas * c[12];
 
  double mean[12];
  double sigma[12];
  double fitSigma[12];
  double fitErrSigma[12];
  double planes[12];
  for (int ip = 0; ip<12; ip++)
    {
      
      res[ip] = new TH1F(Form("res_%s", plane[ip].c_str()),  "", 100, -0.1, 0.1 );
      t->Draw(Form("H.dc.residual[%d]>>res_%s", ip, plane[ip].c_str()));
      
      mean[ip] = res[ip]->GetMean();
      sigma[ip] = res[ip]->GetStdDev();
      TF1 * myfun = new TF1("myfun","gaus",mean[ip]-sigma[ip],mean[ip]+sigma[ip]);
      res[ip]->Fit("myfun","R");
      fitSigma[ip] = myfun->GetParameter(2);
      fitErrSigma[ip]= myfun->GetParError(2);
      planes[ip]=ip+1;
      // cout << "Mean of plane " << plane[ip] << " = " << mean[ip] << endl;
      // cout <<"std of plane :" << plane[ip] << " = " << sigma[ip]<<endl;
      // cout << "sigma :" <<   fitSigma[ip]<<endl;  
      
	      //output->Close();
      // cout <<  fitErrSigma[ip]<<endl;
	      
    }

  TCanvas *c1 = new TCanvas("c1", "", 2000, 500);
  TGraphErrors * graph = new TGraphErrors(12, planes, fitSigma, 0, fitErrSigma);
  graph->SetMarkerStyle(24);
  graph->SetMarkerColor(2);
  graph->GetXaxis()->SetTitle("Plane");
  graph->GetYaxis()->SetTitle("Sigma");
  
  // graph->GetXaxis()->SetRangeUser(0,13);
  graph->Draw("AP");

  TLine *tl = new TLine(0,0.025,graph->GetXaxis()->GetXmax(),0.025); 
  tl->Draw();
  tl->SetLineColor(4);
  c1->Update();
  
  output->Write();
  c1->Write("sigmaVsplane");
  c1->SaveAs("1268_residuals.pdf");
}
