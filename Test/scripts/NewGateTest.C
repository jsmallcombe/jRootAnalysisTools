{

	int a=3;

	
	TH1 *reta,*retb;
	if(a==2){
		TFile* MyFile= new TFile("Test/data/2Ddata.root","READ");
		gROOT->cd();
		reta=(TH2F*)MyFile->Get("yy")->Clone();
		retb=(TH2F*)MyFile->Get("ey")->Clone();
		MyFile->Close();
			
		new jGateToolTwoDee(retb);
// 		new jgating_tool(retb);
		
// 		new jGateToolTwoDee("");
// 		jGateToolTwoDee *bob=new jGateToolTwoDee("");
// 		bob->UpdateInput(reta);
		
	}else{

		TFile* MyFile= new TFile("Test/data/3Ddata.root","READ");
		gROOT->cd();
		retb=(TH3F*)MyFile->Get("Mult_alphaprotons_gamma");
		
		TH3I* three=new TH3I("three","three",20,0,20,20,0,20,20,0,20);
		TRandom r;
		TF1 bob("bob","1+sin(x*3.14159/10.)",0,20);
		for(int i=0;i<20000;i++){
			three->Fill(r.Gaus(10,3),bob.GetRandom(),r.Uniform()*20);
		}
		reta=three;
		
// 		b = new jgating_tool(reta);
		
		
// 		new jGateToolThreeDee(retb);
// 		new jgating_tool(retb);
		
// 		new jGateToolThreeDee("");
		
		jGateToolThreeDee *bill=new jGateToolThreeDee("");
		bill->UpdateInput(reta);
		
		
	}
	
	
	
	
// 		new jEnv;
// 		new TBrowser;
}
