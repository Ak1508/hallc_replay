// Filename: Distributions.cc
// Description: Look at some distributions by looping over each event. The main purpose is to show how to loop over events.
// Author: Latif Kabir < latif@jlab.org >
// Created: Thu Jan  4 17:03:26 2018 (-0500)
// URL: jlab.org/~latif

void Distributions()
{
    TString fileName;
    // fileName += "coin_replay_production_1487_10000.root";
    fileName += "ROOTfiles/shms_replay_production_1966_100000.root";
    TFile *file = new TFile(fileName);
    TTree *tree = (TTree*)file->Get("T");    
    //    tree->Print();

    TH1D *hist = new TH1D("hist", "hist", 100, 0, 5);
    TH1D *hist1 = new TH1D("hist2", "hist1", 100, 0, 5);
    
    Double_t pcal,pcalNgcer;

    //tree->SetBranchAddress("P.kin.primary.W", &W);

    for (Int_t event = 0; event < tree->GetEntries(); ++ event)
    {
	tree->GetEntry(event);

	pcal = tree->GetLeaf("P.hgcer.npeSum")->GetValue();
	pcalNgcer = tree->GetLeaf("P.cal.etottracknorm")->GetValue();
	hist->Fill(pcal);
	hist1->Fill(pcalNgcer);
    }
    hist->Draw(); 
    hist->Draw();

    }
