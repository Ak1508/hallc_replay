#include <iostream>
#include <fstream>
#include <string>
#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TMatrixD.h>
#include <TROOT.h>
#include <TMatrixDBase.h>
#include <TMath.h>
#include <TChain.h>
#include <TH1F.h>
#include <TF1.h>
#include <cstdlib>
#include "TColor.h"

using namespace std;

static const double degtorad = 3.141592653589793/180.;

void formatit(TH1F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.03);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);
  //  gPad->SetLiny(1);
  if (flag == 1){
    gPad->SetLogy(1);

  }

  histo->SetLabelSize(0.045, "x");
  histo->SetLabelSize(0.045, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->SetLineColor(kAzure-2);
  histo->SetLineWidth(3);
  histo->SetLineStyle(1);
  histo->Draw("");  

  leg = new TLegend(0.1,0.85,0.35,0.95);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.055);
  leg->SetTextColor(kAzure-2);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same"); 

}

void formatit_diff(TH1F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.03);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);
  //  gPad->SetLiny(1);
  if (flag == 1){
    gPad->SetLogy(1);

  }

  histo->SetLabelSize(0.045, "x");
  histo->SetLabelSize(0.045, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->SetLineColor(kPink-2);
  histo->SetLineWidth(3);
  histo->SetLineStyle(2);
  histo->Draw("same");  

  leg = new TLegend(0.1,0.7,0.35,0.85);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.055);
  leg->SetTextColor(kPink-2);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same"); 

}

void formatit_2d(TH2F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.21);
  gPad->SetRightMargin(0.11);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);
  

  histo->SetLabelSize(0.045, "x");
  histo->SetLabelSize(0.045, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->Draw("colz");  

  leg = new TLegend(0.1,0.85,0.35,0.95);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.055);
  leg->SetTextColor(kRed-4);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same"); 

  if (flag == 0){

    TLine *linex = new TLine(30.,0.,30.,600.);
    TLine *liney = new TLine(0.,30.,600.,30.);
    linex->SetLineColor(kOrange+7);
    liney->SetLineColor(kOrange+7);
    linex->Draw("same");
    liney->Draw("same");

  }

}



int main(){

TFile *myfile;


  TChain chain("T");


  // H2 42.96 0.7
  chain.Add("ROOTfiles/shms_replay_production_1680_100000.root");

  //  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/hms_replay_production_1255_50000.root");

  //  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/hms_replay_production_1218_-1.root");

  //  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/hms_replay_production_303_300007.root");


  Int_t nTracksx;
  Int_t nTracksy;
  Double_t track_nr;
  Double_t ng_npe;
  Double_t shtrk;
  Double_t prshtrk, nprshtrk;
  Double_t totshtrk;

  Double_t track_x[1000];
  Double_t track_y[1000];
  Double_t track_xp[1000];
  Double_t track_yp[1000];
  Double_t nhits_2x;
  Double_t goodtdchits_2x;
  Double_t goodpostdchits_2x;
  Double_t goodnegtdchits_2x;
  Double_t goodpostdchits_1x;
  Double_t goodnegtdchits_1x;
  Double_t goodpostdchits_1y;
  Double_t goodnegtdchits_1y;
  Double_t goodpostdchits_2y;
  Double_t goodnegtdchits_2y;
  Double_t track_beta, notrack_beta, justw,pist, delta;
  Double_t h1x_fptime, h2x_fptime, h1y_fptime, h2y_fptime;
  Double_t prlo, prhi, shlo, ceramp;


  //  Float_t 1x_fptime, 2x_fptime, 1y_fptime, 2y_fptime;

  chain.SetBranchAddress("T.hms.hPRLO_tdcTimeRaw", &prlo); 
  chain.SetBranchAddress("T.hms.hPRHI_tdcTimeRaw", &prhi); 
  chain.SetBranchAddress("H.cer.goodAdcPulseAmp", &ceramp); 

  chain.SetBranchAddress("Ndata.H.dc.x", &nTracksx);
  chain.SetBranchAddress("Ndata.H.dc.y", &nTracksy);
  chain.SetBranchAddress("H.dc.ntrack", &track_nr);        
  chain.SetBranchAddress("H.cer.npeSum", &ng_npe);        
  chain.SetBranchAddress("H.hod.2x.nhits", &nhits_2x);        

  chain.SetBranchAddress("H.hod.2x.totNumGoodTdcHits", &goodtdchits_2x);        
  chain.SetBranchAddress("H.hod.2x.totNumGoodNegTdcHits", &goodnegtdchits_2x);        
  chain.SetBranchAddress("H.hod.2x.totNumGoodPosTdcHits", &goodpostdchits_2x);        
  chain.SetBranchAddress("H.hod.1x.totNumGoodNegTdcHits", &goodnegtdchits_1x);        
  chain.SetBranchAddress("H.hod.1x.totNumGoodPosTdcHits", &goodpostdchits_1x);        
  chain.SetBranchAddress("H.hod.1y.totNumGoodNegTdcHits", &goodnegtdchits_1y);        
  chain.SetBranchAddress("H.hod.1y.totNumGoodPosTdcHits", &goodpostdchits_1y);        
  chain.SetBranchAddress("H.hod.1y.totNumGoodNegTdcHits", &goodnegtdchits_2y);        
  chain.SetBranchAddress("H.hod.1y.totNumGoodPosTdcHits", &goodpostdchits_2y);        

  chain.SetBranchAddress("H.dc.x", track_x);        
  chain.SetBranchAddress("H.dc.y", track_y);        
  chain.SetBranchAddress("H.dc.xp", track_xp);      
  chain.SetBranchAddress("H.dc.yp", track_yp);    
  chain.SetBranchAddress("H.cal.etracknorm", &shtrk); 
  chain.SetBranchAddress("H.cal.eprtracknorm", &prshtrk); 
  chain.SetBranchAddress("H.cal.eprtrack", &nprshtrk); 
  chain.SetBranchAddress("H.cal.etottracknorm", &totshtrk); 
  chain.SetBranchAddress("H.hod.beta", &track_beta);  
  chain.SetBranchAddress("H.hod.betanotrack", &notrack_beta);  
  chain.SetBranchAddress("H.hod.1x.fptime", &h1x_fptime);  
  chain.SetBranchAddress("H.hod.2x.fptime", &h2x_fptime);  
  chain.SetBranchAddress("H.hod.1y.fptime", &h1y_fptime);  
  chain.SetBranchAddress("H.hod.2y.fptime", &h2y_fptime);  
  chain.SetBranchAddress("H.kin.W", &justw);  
  chain.SetBranchAddress("H.gtr.p", &pist); 

  chain.SetBranchAddress("H.gtr.dp", &delta);

  //  Int_t nentries = (Int_t)this_tree->GetEntries();
  Int_t nentries = chain.GetEntries();
  
  
  TH1F *calo_etracknorm = new TH1F("", "", 100, 0.01, 1.5);  
  TH1F* ngpeh = new TH1F("", "", 100, 0., 30.);  
  TH1F *elec_calo = new TH1F("", "", 100, 0.01, 1.5);  
  TH1F *pion_calo = new TH1F("", "", 100, 0.01, 1.);  
  TH1F *elec_prcalo = new TH1F("", "", 100, 0.01, 1.5);  
  TH1F *pion_prcalo = new TH1F("", "", 100, 0.01, 1.);  
  TH1F *prlo_pion_calo = new TH1F("", "", 100, 0.01, 1.);  
  TH1F *prlo_elec_calo = new TH1F("", "", 100, 0.01, 1.5);  
  TH1F *prhi_pion_calo = new TH1F("", "", 100, 0.01, 1.);  
  TH1F *prhi_elec_calo = new TH1F("", "", 100, 0.01, 1.5);  
  TH1F *prlo_pion_prcalo = new TH1F("", "", 100, 0.01, 1.);  
  TH1F *prlo_elec_prcalo = new TH1F("", "", 100, 0.01, 1.5);  
  TH1F *prhi_pion_prcalo = new TH1F("", "", 100, 0.01, 1.);  
  TH1F *prhi_elec_prcalo = new TH1F("", "", 100, 0.01, 1.5);  


  TH1F *elec_npe = new TH1F("", "", 100, 0., 30.); 

  //  for(Int_t i=0; i < nentries; i++){
  for(Int_t i=0; i < 20000; i++){
    
    chain.GetEntry(i);
    
    //    cout << " " << shtrk << endl;

    if(delta > -8. && delta < 8.){

    calo_etracknorm->Fill(shtrk);
    //    calo_etottracknorm->Fill(totshtrk);
    ngpeh->Fill(ng_npe);
    
    if (ng_npe > 5.){    
      elec_calo->Fill(shtrk);
      elec_prcalo->Fill(nprshtrk);



      if(prlo > 0.){
	prlo_elec_calo->Fill(shtrk);
	prlo_elec_prcalo->Fill(nprshtrk);
	
      }

      if(prhi > 0.){
	prhi_elec_calo->Fill(shtrk);
      prhi_elec_prcalo->Fill(nprshtrk);

      }

    } 
    
    if(ng_npe == 0.){
    //    if(ceramp == 0){
      
      pion_calo->Fill(shtrk);
      pion_prcalo->Fill(nprshtrk);

      if(prlo > 0.){
	prlo_pion_calo->Fill(shtrk);
	prlo_pion_prcalo->Fill(nprshtrk);
      }

      if(prhi > 0.){
	prhi_pion_calo->Fill(shtrk);
	prhi_pion_prcalo->Fill(nprshtrk);
      }

    }

    if (shtrk > 1.){
      
      elec_npe->Fill(ng_npe);
      
    }
    
    }

  }

    Long64_t deno = elec_calo->GetEntries();
    Long64_t prlonumer = prlo_elec_calo->GetEntries();
    Long64_t prhinumer = prhi_elec_calo->GetEntries();

    Long64_t denop = pion_calo->GetEntries();
    Long64_t prlonumerp = prlo_pion_calo->GetEntries();
    Long64_t prhinumerp = prhi_pion_calo->GetEntries();


    cout << "prlo is: " << " " << prlonumer << " " << deno << endl;  
    cout << "prhi is: " << " " << prhinumer << " " << deno << endl;  
    cout << "prlo pion is: " << " " << prlonumerp << " " << denop << endl;  
    cout << "prhi pion is: " << " " << prhinumerp << " " << denop << endl;  

  gStyle->SetCanvasColor(10);
  gStyle->SetFrameFillColor(10);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPalette(1,0);

  
  TCanvas *c3 = new TCanvas("c3","",900,900);
  
  c3->Divide(2,2);

  c3->cd(1);
  formatit(calo_etracknorm, "1 GeV/c , th = 14 deg, ALL", "HMS Shower_Track","Events",0);

  c3->cd(2);
  formatit(ngpeh, "1 GeV/c , th = 14 deg, ALL", "Cherenkov Npe","Events",1);

  c3->cd(3);
  formatit(calo_etracknorm, "1 GeV/c , th = 14 deg, ALL", "HMS Shower_Track","Events",0);
  formatit_diff(elec_calo, "Electrons only", "HMS Shower_Track","Events",0);

  c3->cd(4);
  formatit(calo_etracknorm, "1 GeV/c , th = 14 deg, ALL", "HMS Shower_Track","Events",0);
  formatit_diff(pion_calo, "Pions only", "HMS Shower_Track","Events",0);

  c3->Print("calo_npe_1255.png"); 

  TCanvas *c4 = new TCanvas("c4","",900,900);
  
  c4->Divide(2,2);
  c4->cd(1);
  formatit(elec_calo, "Electrons only", "HMS Shower_Track","Events",0);
  formatit_diff(prlo_elec_calo, "Electrons only + prlo", "HMS Shower_Track","Events",0);

  c4->cd(2);
  formatit(pion_calo, "Pions only", "HMS Shower_Track","Events",0);
  formatit_diff(prlo_pion_calo, "Pions only + prlo", "HMS Shower_Track","Events",0);

  c4->cd(3);
  formatit(elec_calo, "Electrons only", "HMS Shower_Track","Events",0);
  formatit_diff(prhi_elec_calo, "Electrons only + prhi", "HMS Shower_Track","Events",0);

  c4->cd(4);
  formatit(pion_calo, "Pions only", "HMS Shower_Track","Events",0);
  formatit_diff(prhi_pion_calo, "Pions only + prhi", "HMS Shower_Track","Events",0);

  c4->Print("calo_npe_prlo_1255.png"); 

  TCanvas *c5 = new TCanvas("c5","",900,900);
  
  c5->Divide(2,2);
  c5->cd(1);
  formatit(elec_prcalo, "Electrons only", "HMS PrShower_Track","Events",0);
  formatit_diff(prlo_elec_prcalo, "Electrons only + prlo", "PrHMS Shower_Track","Events",0);

  c5->cd(2);
  formatit(pion_prcalo, "Pions only", "HMS PrShower_Track","Events",0);
  formatit_diff(prlo_pion_prcalo, "Pions only + prlo", "PrHMS Shower_Track","Events",0);

  c5->cd(3);
  formatit(elec_prcalo, "Electrons only", "HMS PrShower_Track","Events",0);
  formatit_diff(prhi_elec_prcalo, "Electrons only + prhi", "PrHMS Shower_Track","Events",0);

  c5->cd(4);
  formatit(pion_prcalo, "Pions only", "HMS PrShower_Track","Events",0);
  formatit_diff(prhi_pion_prcalo, "Pions only + prhi", "HMS PrShower_Track","Events",0);

  c5->Print("prcalo_npe_prlo_1255.png"); 

   return 0;
   
}
