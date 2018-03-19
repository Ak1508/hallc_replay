void hist_test()
{

  Double_t getmax;
  Double_t getmaxbin;
  Double_t getbinwithcontent;
  Int_t bin_x = 0;
  Int_t x;

  TH1F *h1 = new TH1F("h1", "", 100, -5, 5);

  h1->FillRandom("gaus");
  h1->Draw();

  
  getmax = h1->GetMaximum(); //returns maximum histo bin content
  getmaxbin = h1->GetMaximumBin(); //returns bin value of maxim bin content
  getbinwithcontent = h1->GetBinWithContent(bin_x, x, 0,getmax, 1);
  cout << "getmax: " << getmax << endl;
  cout << "getmaxbin :"<<getmaxbin<<endl;
  cout <<"getbinwithcontent :" <<getbinwithcontent<<endl;
}
