// looking at the residuals for the HMS 
#define NPLANES 12
void residual_shms_compare()

{

  gROOT->SetBatch(1);

  TString fileArr [2];
  fileArr[0] = "ROOTfiles/shms_replay_production_all_1791_1000000.root";
  fileArr[1] = "~/cyero/hallc_replay/ROOTfiles/shms_replay_production_all_1791_dccalib_ndata1cut.root";
  //TTree *t = (TTree*)f->Get("T");
  
  // TFile *file =  new TFile("~/cyero/hallc_replay/ROOTfiles/shms_replay_production_all_1791_dccalib_ndata1cut.root");
  //TTree *tree = (TTree*)file->Get("T");

  TFile *data_file[2];
  
  TFile *output = new TFile("output_1791_residual_compare.root", "RECREATE");

  TH1F * res[NPLANES];

  // TH1F * res_nhit[NPLANES];

  string plane[NPLANES] = {"1u1", "1u2", "1x1", "1x2", "1v2", "1v1", "2v1", "2v2", "2x2", "2x1", "2u2", "2u1"};
 
  double mean[NPLANES];
  double sigma[NPLANES];
  double fitSigma[NPLANES];
  double fitErrSigma[NPLANES];
  double planes[NPLANES];

  TCut cer = "P.ngcer.npeSum>1.0";
  TCut cal = "P.cal.etot>0.1";
  TCut time;
  TCut nhit;

  cout << "OK HERE !!! " << endl;
  
  for (int ifile = 0; ifile <2; ifile++)
    {

      cout << "Inside File Loop " << endl;

      data_file[ifile] = new TFile(fileArr[ifile], "READ"); 
      TTree *t = (TTree*)data_file[ifile]->Get("T");
      
      cout << "read data file " << fileArr[ifile] << endl;
      
      for (int ip = 0; ip<NPLANES; ip++)
	{
	  time = Form("P.dc.%s.time>0.0 && P.dc.%s.time<190.0", plane[ip].c_str(), plane[ip].c_str());
	  nhit = Form("P.dc.%s.nhit == 1", plane[ip].c_str());
	  
	  res[ip] = new TH1F(Form("File_%d_res_%s", ifile, plane[ip].c_str())," ", 100, -0.2, 0.2 );
	}
    }
	  /*
	  if (ifile ==0)
	    {
	      t->Draw(Form("P.dc.residual[%d]>>res_%s", ip, plane[ip].c_str()),time && cer && nhit && cal);
	  //   }
	  // else if (ifile ==1)
	  //   {
	      //t->Draw(Form("P.dc.residual[%d]>>res_%s", ip, plane[ip].c_str()),time && nhit );

	    }

	  mean[ip] = res[ip]->GetMean();
	  sigma[ip] = res[ip]->GetStdDev();
	  cout <<" mean :"<<mean <<endl;
	  
	  
	  TF1 * myfun = new TF1("myfun","gaus",mean[ip]-sigma[ip],mean[ip]+sigma[ip]);
	  res[ip]->Fit("myfun","R");
	  fitSigma[ip] = myfun->GetParameter(2);
	  fitErrSigma[ip]= myfun->GetParError(2);
	  planes[ip]=ip+1;
	 
	  cout << "*********"<<planes[ip]<<endl;
	}// plane loop ends

 
      TCanvas *c1 = new TCanvas(Form("c%d",ifile), "", 2000, 500);
      TGraphErrors * graph = new TGraphErrors(NPLANES, planes, fitSigma, 0, fitErrSigma);
      graph->SetMarkerStyle(24);
      graph->SetMarkerColor(2);
      graph->GetXaxis()->SetTitle("Plane");
      graph->GetYaxis()->SetTitle("Sigma");
      
      // graph->GetXaxis()->SetRangeUser(0,13);
      graph->Draw("AP");
      
      TLine *tl = new TLine(0,0.0395,graph->GetXaxis()->GetXmax(),0.0395); 
      tl->Draw();
      tl->SetLineColor(4);
      c1->Update();
      
      output->Write();
      c1->Write("graph");
      // c1->SaveAs("1268_residuals.pdf");
      
    }// loop over file

  */
}

