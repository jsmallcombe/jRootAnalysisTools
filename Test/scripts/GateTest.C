{

	int a=2;

	
	TH1* ret;
	if(a==2){
		TFile* MyFile= new TFile("Test/data/2Ddata.root","READ");
		gROOT->cd();
// 		ret=(TH2F*)MyFile->Get("yy")->Clone();
		ret=(TH2F*)MyFile->Get("ey")->Clone();
		MyFile->Close();
	}else{

		TFile* MyFile= new TFile("Test/data/3Ddata.root","READ");
		gROOT->cd();
		ret=(TH3F*)MyFile->Get("Gamma_Gamma_Gamma")->Clone();
		MyFile->Close();	
	}
	b = new jgating_tool(ret);
	
// 		new jEnv;
// 		new TBrowser;
}
