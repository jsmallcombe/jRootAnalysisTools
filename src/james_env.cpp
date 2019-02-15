#include "james_env.h"


		
///////////////////////////////////////////////////////////////////////////////////////////////////////


jEnv::jEnv() : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame),fFitPanel(0),fSpecTool(0),addsub(0),SameSave(0),gDrawSame(false){
TVirtualPad* hold=gPad;
	SetWindowName("jEnv");
    
	SetCleanup(kDeepCleanup);

	TGLayoutHints* ExpandX= new TGLayoutHints(kLHintsExpandX,5,5,3,2);
	
	TGVerticalFrame* controlframe1 = new TGVerticalFrame(this);
		fCanvas1 = new CCframe("Embedded1", controlframe1, 100, 100);
		controlframe1->AddFrame(fCanvas1);
		TGTextButton* fitter = new TGTextButton(controlframe1,"Fit Panel");
		fitter->Connect("Clicked()","jEnv",this,"FitPanel()");	
		controlframe1->AddFrame(fitter,ExpandX);
		TGTextButton* Spect = new TGTextButton(controlframe1,"SpecTool");
		Spect->Connect("Clicked()","jEnv",this,"Spectrum()");
		controlframe1->AddFrame(Spect,ExpandX);
		TGTextButton* gatter = new TGTextButton(controlframe1,"Gate");
		gatter->Connect("Clicked()","jEnv",this,"Gatter()");	
		controlframe1->AddFrame(gatter,ExpandX);
		TGTextButton* browser = new TGTextButton(controlframe1,"Browser");
		browser->Connect("Clicked()","jEnv",this,"Browser()");
		controlframe1->AddFrame(browser,ExpandX);
		TGTextButton* Drawer = new TGTextButton(controlframe1,"DrawCopy");
		Drawer->Connect("Clicked()","jEnv",this,"DrawCpy()");
		controlframe1->AddFrame(Drawer,ExpandX);
		TGTextButton* Drawsm = new TGTextButton(controlframe1,"DrawSame");
		Drawsm->Connect("Clicked()","jEnv",this,"DrawSm()");
		controlframe1->AddFrame(Drawsm,ExpandX);
		TGTextButton* Saver = new TGTextButton(controlframe1,"SaveAs");
		Saver->Connect("Clicked()","jEnv",this,"jSaveAs()");
		controlframe1->AddFrame(Saver,ExpandX);
		TGTextButton* close = new TGTextButton(controlframe1,"Close");
		close->Connect("Clicked()","jEnv",this,"DeleteWindow()");
		controlframe1->AddFrame(close,ExpandX);
		TGTextButton* exit = new TGTextButton(controlframe1,"Exit","gApplication->Terminate(0)");
		controlframe1->AddFrame(exit,ExpandX);
		

	this->AddFrame(controlframe1);
	
	TGTextButton* expandB = new TGTextButton(this,">");
	expandB->Connect("Clicked()","jEnv",this,"ShowHide()");	
	this->AddFrame(expandB,new TGLayoutHints(kLHintsExpandY, 1, 1, 1, 1));
	
	addsub = new jAddSubTool(fCanvas1,this);
	this->AddFrame(addsub,new TGLayoutHints(kLHintsExpandY|kLHintsExpandX, 1, 1, 1, 1));
	
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
	
	Hide();
	
// 	Connect("CloseWindow()","jEnv",this,"~jEnv()");
	Connect("CloseWindow()","jEnv",this,"DontCallClose()");

gPad=hold;
}

void jEnv::Browser(){
	new TBrowser;
	if(fCanvas1->Type()>0&&fCanvas1->Type()<3)fCanvas1->Hist()->DrawCopy("colz");
}
void jEnv::FitPanel(){
	if(fFitPanel){
		if(fCanvas1->Type()==1)fFitPanel->PassNewHist(fCanvas1->Hist());
	}else {
		if(fCanvas1->Type()==1)fFitPanel=new UltraFitEnv(fCanvas1->Hist());
		else fFitPanel=new UltraFitEnv();  
		fFitPanel->Connect("Destroyed()", "jEnv", this,"FitPanelClose()");
	}
};
void jEnv::Spectrum(){
	if(fCanvas1->Type()==1){
		if(fSpecTool){
			if(fCanvas1->Type()==1)fSpecTool->NewInput(fCanvas1->Hist());
		}else {
			fSpecTool=new jSpecTool(fCanvas1->Hist());
			fSpecTool->Connect("Destroyed()", "jEnv", this,"SpecToolClose()");
		}
	}
};


void jEnv::Gatter(){
	if(fCanvas1->Type()>1)new jgating_tool(fCanvas1->Hist());
};


void jEnv::DrawCpy(){
	HistDrawCopyPeaker(fCanvas1->Hist());
};

void jEnv::DrawSm(){
	gDrawSame=false;
	if(SameSave){delete SameSave;SameSave=0;}
	TH1* h=fCanvas1->Hist();
	if(fCanvas1->Type()==1&&h){
		SameSave=(TH1*)h->Clone();
		gDrawSame=true;
		TQObject::Connect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", "jEnv", this,"DrawSmHere(TPad*,TObject*,Int_t)");
	}
};

void jEnv::DrawSmHere(TPad* pad,TObject* obj,Int_t event){
	
	if(SameSave&&gDrawSame){
		TCanvas* sender=(TCanvas*)gTQSender;
		TVirtualPad* hold=gPad;
		pad->cd();
		hformat(SameSave,0);
        SameSave->SetLineColor(2);
		DrawHistOpt(SameSave,true,true);
		sender->Modified();
		sender->Update();
		gPad=hold;
	}

	gDrawSame=false;
	TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "DrawSmHere(TPad*,TObject*,Int_t)");
	if(SameSave){delete SameSave;SameSave=0;}
}


void jEnv::jSaveAs(){
	if(fCanvas1->Type())HistSaveAs(fCanvas1->Hist(),this);
};


void jEnv::ShowHide(){if(!addsub)return;
	if(IsVisible(addsub)){
		Hide();
	}else{
		Show();
	}
}

void jEnv::Show(){
	ShowFrame(addsub);
	Resize(this->GetDefaultSize());
	gClient->NeedRedraw(this);
}

void jEnv::Hide(){
	HideFrame(addsub);
	Resize(this->GetDefaultSize());
	gClient->NeedRedraw(this);
}


////////////////////////////////////////////////////////////////

jScale::jScale() : TGMainFrame(gClient->GetRoot(), 100, 100,kVerticalFrame),gg(0){
TVirtualPad* hold=gPad;
	SetWindowName("jScale");
	SetCleanup(kDeepCleanup);
	

	TGLayoutHints* ExpandX= new TGLayoutHints(kLHintsExpandX,5,5,3,2);
	
	TGHorizontalFrame* inputframe = new TGHorizontalFrame(this);
		fCanvas1 = new CCframe("Embedded1", inputframe, 100, 100);
        fCanvas1->Connect("NewObject()","jScale",this,"NewInput()");
		inputframe->AddFrame(fCanvas1);
		fCanvas2 = new CCframe("Embedded2", inputframe, 100, 100);
        fCanvas2->SetClass(TGraph::Class());
        fCanvas2->Connect("NewObject()","jScale",this,"NewInput()");
		inputframe->AddFrame(fCanvas2);
	this->AddFrame(inputframe,ExpandX);
	
    
    result= new TRootEmbeddedCanvas("scaledhistcan",this,600,400);
		result->GetCanvas()->SetMargin(0.12,0.04,0.12,0.05);
// 		result->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0,0,"ClickPeakDrawConnect(Int_t,Int_t,Int_t,TObject*)");
// 		result->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0,0,"ToolTipHide()");//added because this embedded canvas put tooltip at wrong coordinates on screen

	this->AddFrame(result,ExpandX);
    
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
    
    
	fCanvas1->CFriends.push_back(fCanvas2->GetCanvas());
	fCanvas1->CFriends.push_back(result->GetCanvas());
	fCanvas2->CFriends.push_back(fCanvas1->GetCanvas());
	fCanvas2->CFriends.push_back(result->GetCanvas());
	
gPad=hold;
}


void jScale::NewInput(){
    TH1* H=fCanvas1->Hist();
    TGraph* G=(TGraph*)fCanvas2->Object();
    
    if(G){
        if(gg)delete gg;
        gg=(TGraph*)G->Clone();
    }
    
//     cout<<endl<<H<<endl<<gg<<endl;
    if(HType(H)&&gg&&HType(H)<3){
        TH1* scaled=(TH1*)H->Clone();
        scaled->Reset();
        bool Y=(HType(H)==2);
        int NX=H->GetNbinsX();
        int ny=0;
        int NY=0;
        if(Y){
            ny=1;
            NY=H->GetNbinsY();
        }
        
        for(int x=1;x<=NX;x++){
            double efX=gg->Eval(H->GetXaxis()->GetBinCenter(x));
            
            for(int y=ny;y<=NY;y++){
                int bin=H->GetBin(x,y);
                double n=H->GetBinContent(bin);
                double e=H->GetBinError(bin);
                double efY=1;
                if(Y){
                    efY=gg->Eval(H->GetYaxis()->GetBinCenter(y));
                }
                double scale=1/(efY*efX);
                scaled->SetBinContent(bin,n*scale);
                scaled->SetBinError(bin,e*scale);
            }
        }
        
//         Draw new results with and adjust axis
        TVirtualPad* hold=gPad;
        result->GetCanvas()->cd();
            hformat(scaled,0);
            scaled->DrawCopy("hiscol");
            delete scaled;
//             gPad->Update();
//             G->DrawClone("al");
        result->GetCanvas()->Modified();
        result->GetCanvas()->Update();
        gPad=hold;
    }
}



