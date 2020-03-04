{    
    TH1 *A,*B,*C,*D;
    
	TH1* ret;
	TFile* MyFile= new TFile("Test/data/2Ddata.root","READ");
	gROOT->cd();
	A=(TH2F*)MyFile->Get("yy")->Clone("yyClone");
	B=(TH2F*)MyFile->Get("ey")->Clone("eyClone");
	MyFile->Close();
    
    MyFile= new TFile("Test/data/1Dgammas.root","READ");
	gROOT->cd();
	C=(TH1*)MyFile->Get("gHist2")->Clone("gHist2Clone");
	MyFile->Close();
    
    MyFile= new TFile("Test/data/1Dice.root","READ");
	gROOT->cd();
	D=(TH1*)MyFile->Get("gHist1")->Clone("gHist1Clone");
	MyFile->Close();
    
    TGraph *G1, *G2;
    
    MyFile= new TFile("Test/data/RelGammaEfficiency.root","READ");
	gROOT->cd();
	G1=(TGraph*)MyFile->Get("RelGammaEff")->Clone("RelGammaEffClone");
	MyFile->Close();  
    
    
    MyFile= new TFile("Test/data/RelGammaEfficiencyError.root","READ");
	gROOT->cd();
	G2=(TGraph*)MyFile->Get("RelGammaError")->Clone("RelGammaErrorClone");
	MyFile->Close();  
    
}
