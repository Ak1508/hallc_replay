{
  TFile * f = new TFile ("ROOTfiles/shms_replay_production_1678_100000.root");
  TH2F *h2 = (TH2F*)f.Get("phodo_1x_pped_vs_pmt_pos");
  TH1D *h1 = h2->ProjectionY();
  h1->Draw();
    }
