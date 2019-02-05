{ 
    TH1 *A,*B,*C,*D;
    
	TH1* ret;
	TFile* MyFile= new TFile("Test/data/2Ddata.root","READ");
	gROOT->cd();
	A=(TH2F*)MyFile->Get("yy")->Clone();
	B=(TH2F*)MyFile->Get("ey")->Clone();
	MyFile->Close();
    
    MyFile= new TFile("Test/data/1Dgammas.root","READ");
	gROOT->cd();
	C=(TH2F*)MyFile->Get("gHist2")->Clone();
	MyFile->Close();
    
    MyFile= new TFile("Test/data/1Dice.root","READ");
	gROOT->cd();
	D=(TH2F*)MyFile->Get("gHist1")->Clone();
	MyFile->Close();

    MyFile= new TFile("Test/data/RelGammaEfficiency.root","READ");
	gROOT->cd();
	G1=(TH2F*)MyFile->Get("RelGammaEff")->Clone();
	MyFile->Close();  
    
    
    MyFile= new TFile("Test/data/RelGammaEfficiencyError.root","READ");
	gROOT->cd();
	G2=(TH2F*)MyFile->Get("RelGammaError")->Clone();
	MyFile->Close();  
    
    TCanvas* C1=new TCanvas();
    C1->Divide(2,3);
    C1->cd(1);
    A->Draw("col");
    C1->cd(2);
    B->Draw("col");
    C1->cd(3);
    C->Draw("col");
    C1->cd(4);
    D->Draw("col");
    C1->cd(5);
    G1->DrawClone("al");
    C1->cd(6);
    G2->DrawClone("al");
    
    gPad->Update();
    
    gROOT->cd();
    
    new jEnv();
    new jScale();

}