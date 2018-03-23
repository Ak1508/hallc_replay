// looking at the residuals for the HMS 
#define NPLANES 12
Double_t residual_hms(Int_t Num)

{
  //Int_t Num = runNo;  
  gROOT->SetBatch(1);
  // cout << runNo<<endl;
  
  TFile *f =  new TFile(Form("ROOTfiles/hms_replay_production_all_%d_-1.root", Num));
  TTree *t = (TTree*)f->Get("T");
  
  TFile *output = new TFile(Form("output_%d_residual.root",Num), "RECREATE");

  TH1F * res[NPLANES];

  string plane[NPLANES] = {"1u1", "1u2", "1x1", "1x2", "1v2", "1v1", "2v1", "2v2", "2x2", "2x1", "2u2", "2u1"};
 
  double mean[NPLANES];
  double sigma[NPLANES];
  double fitSigma[NPLANES];
  double fitErrSigma[NPLANES];
  double planes[NPLANES];

  // TCut cer = "H.cer.npeSum>1.0";
  TCut time;
  TCut nhit; 

  for (int ip = 0; ip<NPLANES; ip++)
    {
      nhit = Form("H.dc.%s.nhit == 1", plane[ip].c_str());
      time = Form("H.dc.%s.time>0.0 && H.dc.%s.time<190.0", plane[ip].c_str(), plane[ip].c_str());
      res[ip] = new TH1F(Form("res_%s", plane[ip].c_str()),  "", 100, -0.2, 0.2 );
      t->Draw(Form("H.dc.residual[%d]>>res_%s", ip, plane[ip].c_str()),time && nhit);
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
  TGraphErrors * graph = new TGraphErrors(NPLANES, planes, fitSigma, 0, fitErrSigma);
  graph->SetMarkerStyle(24);
  graph->SetMarkerColor(2);
  graph->GetXaxis()->SetTitle("Plane");
  graph->GetYaxis()->SetTitle("Residal [cm]");
  
  // graph->GetXaxis()->SetRangeUser(0,13);
  graph->Draw("AP");

  TLine *tl = new TLine(0,0.025,graph->GetXaxis()->GetXmax(),0.025); 
  tl->Draw();
  tl->SetLineColor(4);
  c1->Update();
  
  output->Write();
  c1->Write("graph");
  // c1->SaveAs("1268_residuals.pdf");
  return 0;
}
