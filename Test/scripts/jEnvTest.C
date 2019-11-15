{ 
//     SetGlobalNegative();
    
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
    
    TCanvas* C1=new TCanvas();
    C1->Divide(2,3);
    C1->cd(1);
    A->Draw("col");
    C1->cd(2);
    B->Draw("col");
    CanvasNegative(C1->cd(2));
    C1->cd(3);
    C->Draw("col");
    C1->cd(4);
    D->Draw("col");
    CanvasNegative(C1->cd(4));
    C1->cd(5);
    gPad->Update();
    G1->DrawClone("al");
    C1->cd(6);
    gPad->Update();
    G2->DrawClone("al");
    CanvasNegative(C1->cd(6));
    
    
    gPad->Update();
    
    gROOT->cd();
    gSystem->cd("./Test/data/");
    
    new jEnv();
//    new jScale();
//    new jEval();

}
