{TObject* O;

///// TH2
// 	new jEnv;
// 	O=A;//yy // TH2
// 	O=B;//ey // TH2
	
SetGlobalTH3UpdateLock(false);
	O=A3;//ymm // TH3
// 	O=B3;//rrr // TH3
// 	O=S3;//rrr // THnSparse

//// Change overflow underflow settings
	SetGlobalOverflowInclude(true);
	SetGlobalUnderflowInclude(false);
////////////////////
	
	TGMainFrame* tool=nullptr;
	if(O==A||O==B){
		TH1* H=(TH1*)O;
		
		//// Removing overflow underflow for comparison with old methods
		int X=H->GetNbinsX();
		int Y=H->GetNbinsY();
		for(int y=0;y<Y+1;y++){
			H->SetBinContent(0,y,0.0);
			H->SetBinContent(X+1,y,0.0);
		}
		for(int y=0;y<X+1;y++){
			H->SetBinContent(y,0,0.0);
			H->SetBinContent(y,Y+1,0.0);
		}
	}
	
	new jgating_tool(O);//Old Tool
	jGatingToolSelector(O)->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
	
}
