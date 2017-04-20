{

	int a=3;

	
	jgating_tool* b;
	if(a=='2'){
		
		TFile* MyFile= new TFile("Test/data/2Ddata.root","READ");
		gROOT->cd();
	// 	TH2F *ret=(TH2F*)MyFile->Get("yy")->Clone();
		TH2F *ret=(TH2F*)MyFile->Get("ey")->Clone();
		MyFile->Close();
		b = new jgating_tool(ret);
	}else{

		TFile* MyFile= new TFile("Test/data/3Ddata.root","READ");
		gROOT->cd();
		TH3F *ret=(TH3F*)MyFile->Get("hh")->Clone();
		MyFile->Close();
		b = new jgating_tool(ret);
	}
	
// 		new jEnv;
// 		new TBrowser;
}
