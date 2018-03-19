{

  TFile *f =  new TFile("ROOTfiles/shms_replay_production_2248_100000.root");
  TTree *T = (TTree*)f->Get("T");

  TH1D *h1 = new TH1D("h1","  ",100, 0, 1.5);

  Double_t cal;
  
  T->SetBranchAddress("P.cal.etottracknorm", &cal);

  Int_t nentries = T->GetEntries();

  for(int i = 0; i < nentries; i++)
    {
      T->GetEntry(i);
      if (cal>0)
      h1->Fill(cal);

      

    }

  h1->Draw();

}
