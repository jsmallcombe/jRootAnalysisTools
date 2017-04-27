{

	int a=3;

	
	TH1* ret;
	if(a==2){
		TFile* MyFile= new TFile("Test/data/2Ddata.root","READ");
		gROOT->cd();
// 		ret=(TH2F*)MyFile->Get("yy")->Clone();
		ret=(TH2F*)MyFile->Get("ey")->Clone();
		MyFile->Close();
	}else{

// 		TFile* MyFile= new TFile("Test/data/3Ddata.root","READ");
// 		gROOT->cd();
// 		ret=(TH3F*)MyFile->Get("Gamma_Gamma_Gamma")->Clone();
// 		MyFile->Close();	
		
		TH3I* three=new TH3I("three","three",20,0,20,20,0,20,20,0,20);
		TRandom r;
		TF1 bob("bob","1+sin(x*3.14159/10.)",0,20);
		for(int i=0;i<20000;i++){
			three->Fill(r.Gaus(10,3),bob.GetRandom(),r.Uniform()*20);
		}
		ret=three;
	}
	b = new jgating_tool(ret);
	
// 		new jEnv;
// 		new TBrowser;
}
