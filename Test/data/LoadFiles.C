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
	
	TH1* dedx;
	MyFile= new TFile("Test/data/dedx.root","READ");
	gROOT->cd();
	dedx=(TH1*)MyFile->Get("red0Z_copy")->Clone("dedx");
	MyFile->Close();  
    
	TH1* ydots;
	MyFile= new TFile("Test/data/ydots.root","READ");
	gROOT->cd();
	ydots=(TH1*)MyFile->Get("YpairVs0_copy")->Clone("ydots");
	MyFile->Close();  
	
	TH3* A3;
	MyFile= new TFile("Test/data/3Ddata.root","READ");
	gROOT->cd();
	A3=(TH3*)MyFile->Get("Mult_alphaprotons_gamma")->Clone("MAlphaMProtonGamma");
	MyFile->Close();  
	
	TH3* B3=new TH3I("ThreeRand","ThreeRand",20,0,20,20,0,20,20,0,20);
	TRandom r;
	TF1 fn("RandFun","1+sin(x*3.14159/10.)",0,20);
	const Int_t nbins[3] = {20, 20, 20};
	const Double_t xmin[3] = {0, 0, 0};
	const Double_t xmax[3] = {20, 20, 20};
	Double_t coords[3];
	THnSparseI* S3 = new THnSparseI("sparse", "sparse", 3, nbins, xmin, xmax);
	for(int i=0;i<20000;i++){
		int a=r.Gaus(10,3);
		int b=fn.GetRandom();
		int c=r.Uniform()*20;
		if(b==12)continue; // Put some gaps in the data 
		if(c==7)continue; // Put some gaps in the data 
		B3->Fill(a,b,c);
		coords[0] = a;
		coords[1] = b;
		coords[2] = c;
		S3->Fill(coords);
	}
	
}
