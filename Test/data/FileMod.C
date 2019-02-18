{ 
	TH1* ret;
	TFile* MyFile= new TFile("FileStructure.root","UPDATE");
	gROOT->cd();

    
    TFile* Three= new TFile("3Ddata.root","READ");
	gROOT->cd();
	C=(TH1*)Three->Get("Mult_alphaprotons_gamma")->Clone();
    
    MyFile->cd("ADirectory");
    C->Write("YYY",TH1::kOverwrite);
    MyFile->Write();
	gROOT->cd();
    
    Three->Close();
    MyFile->Close();
}
