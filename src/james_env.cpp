#include "james_env.h"

CCframe::CCframe(const char * name,const TGWindow* p,UInt_t w,UInt_t h,UInt_t options,Pixel_t back):TRootEmbeddedCanvas(name,p,w,h,options,back),current(0),currentpad(0),currentcan(0){TVirtualPad* hold=gPad;
	this->GetCanvas()->SetMargin(0,0,0,0);
	TQObject::Connect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", "CCframe", this,"TrackCaptureHistogram(TPad*,TObject*,Int_t)");
	gPad=hold;
}

CCframe::~CCframe(){
	TQObject::Disconnect(this);
/*	
	Disconnect(0,this,0);
	TQObject::Disconnect((TCanvas*)cCan);
	TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "CaptureCanvas(TPad*,TObject*,Int_t)");*/
}


void CCframe::TrackCaptureHistogram(TPad* pad,TObject* obj,Int_t event){
	//Called by ALL TCanvas
	TCanvas* sender=(TCanvas*)gTQSender;
	
	//To make this ignore certain pads
	for(unsigned int i=0;i<CFriends.size();i++){if(pad==CFriends[i])return;}
	
	
	if(1 == event){//Left Click
		if(this->GetCanvas()==pad){
			//cout<<endl<<"self click"<<endl;
			return;
		}

		if(obj){
			TH1* fH=0;
			if(obj->InheritsFrom("TH1"))fH=(TH1*)obj;//If click was exactly on a histogram?
			else fH=hist_capture(pad);//Else find first histogram this pad has
			
			if(fH)SetNewHist(fH,pad,sender);
			return;
		}
	}
}

void CCframe::SetNewHist(TH1* fH,TPad* Pad,TCanvas* Can){
	if(fH!=current){
		current=fH;
		currentpad=Pad;
		currentcan=Can;
		histname=current->GetName();
		TVirtualPad* hold=gPad;
		this->GetCanvas()->cd();
		if(fH->InheritsFrom("TH3")){
			this->GetCanvas()->Clear();
			TText t;
			t.SetTextAlign(22);
			t.SetTextSize(.6);
			t.DrawTextNDC(.5,.5,"TH3");
		}else{
			double xt=fH->GetXaxis()->GetLabelSize();
			double yt=fH->GetYaxis()->GetLabelSize();
			fH->GetXaxis()->SetLabelSize(0);
			fH->GetYaxis()->SetLabelSize(0);
			fH->SetStats(kFALSE);
			fH->DrawCopy("COLZ");
			fH->GetXaxis()->SetLabelSize(xt);
			fH->GetYaxis()->SetLabelSize(yt);
		}
		this->GetCanvas()->Modified();
		this->GetCanvas()->Update();
		gPad=hold;
	}
}

TH1* CCframe::Hist(){

	if(current){
		TObject* Ob = gROOT->FindObject(histname.c_str());
// 		cout<<endl<<"Checking if histogram pointer "<<current<<" is valid: "<<Ob<<endl;
		if(Ob)if(Ob->InheritsFrom("TH1"))return (TH1*)Ob;
		//Often fails because FindObject has limitations in terms of directories and drawn histograms we might have grabbed.
		//If the canvas is still drawn we might still be able to grab the histogram
		
		TPad* Pad=(TPad*)gROOT->GetListOfCanvases()->FindObject(currentpad);
// 		cout<<endl<<"Checking if pad pointer "<<currentpad<<" is in gROOT->GetListOfCanvases() :"<<Pad<<endl;
		if(Pad){
			Ob=Pad->GetListOfPrimitives()->FindObject(current);
			if(Ob)if(Ob->InheritsFrom("TH1"))return (TH1*)Ob;
		}
		
		TCanvas* Can=(TCanvas*)gROOT->GetListOfCanvases()->FindObject(currentcan);
// 		cout<<endl<<"Checking if canvas pointer "<<currentcan<<" is in gROOT->GetListOfCanvases() :"<<Can<<endl;
		if(Can){
			Ob=Can->GetListOfPrimitives()->FindObject(current);
			if(Ob)if(Ob->InheritsFrom("TH1"))return (TH1*)Ob;
			
			Pad=(TPad*)Can->GetListOfPrimitives()->FindObject(currentpad);
			if(Pad){
				Ob=Pad->GetListOfPrimitives()->FindObject(current);
				if(Ob)if(Ob->InheritsFrom("TH1"))return (TH1*)Ob;
			}
		}
	}
	return 0;
}

int CCframe::Type(){
	TH1* H=Hist();
	if(H){
		if(H->InheritsFrom("TH3"))return 3;
		if(H->InheritsFrom("TH2"))return 2;
		if(H->InheritsFrom("TH1"))return 1;
	}
	return 0;
}
		
		
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////


jEnv::jEnv() : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame),fFitPanel(0),addsub(0),A(0),B(0),result(0),AHist(0),BHist(0),SumHist(0){
TVirtualPad* hold=gPad;
	SetWindowName("jEnv");
	char buf[32];	//A buffer for processing text through to text boxes
	SetCleanup(kDeepCleanup);
	gSubtract=true;

	TGLayoutHints* ExpandX= new TGLayoutHints(kLHintsExpandX,5,5,3,2);
	
	TGVerticalFrame* controlframe1 = new TGVerticalFrame(this);
		fCanvas1 = new CCframe("Embedded1", controlframe1, 100, 100);
		controlframe1->AddFrame(fCanvas1);
		TGTextButton* fitter = new TGTextButton(controlframe1,"Fit Panel");
		fitter->Connect("Clicked()","jEnv",this,"FitPanel()");	
		controlframe1->AddFrame(fitter,ExpandX);
		TGTextButton* gatter = new TGTextButton(controlframe1,"Gate");
		gatter->Connect("Clicked()","jEnv",this,"Gatter()");	
		controlframe1->AddFrame(gatter,ExpandX);
		TGTextButton* browser = new TGTextButton(controlframe1,"Browser");
		browser->Connect("Clicked()","jEnv",this,"Browser()");
		controlframe1->AddFrame(browser,ExpandX);
		TGTextButton* Drawer = new TGTextButton(controlframe1,"DrawCopy");
		Drawer->Connect("Clicked()","jEnv",this,"DrawCpy()");
		controlframe1->AddFrame(Drawer,ExpandX);
		TGTextButton* Saver = new TGTextButton(controlframe1,"SaveAs");
		Saver->Connect("Clicked()","jEnv",this,"SaveAs()");
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
	
	addsub = new TGVerticalFrame(this);
		TGHorizontalFrame* ABswap= new TGHorizontalFrame(addsub);
			A= new TRootEmbeddedCanvas("histholdA",ABswap,100,100);
			A->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "jEnv", this,"GrabA(Int_t,Int_t,Int_t,TObject*)");
			TGTextButton* swapB = new TGTextButton(ABswap,"<->");
			swapB->Connect("Clicked()","jEnv",this,"Swap()");	
			B= new TRootEmbeddedCanvas("histholdB",ABswap,100,100);
			B->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "jEnv", this,"GrabB(Int_t,Int_t,Int_t,TObject*)");
			ABswap->AddFrame(A);
			ABswap->AddFrame(swapB,new TGLayoutHints(kLHintsCenterY, 1, 1, 1, 1));
			ABswap->AddFrame(B);
		addsub->AddFrame(ABswap,new TGLayoutHints(kLHintsCenterX, 1, 1, 1, 1));
		
		TGHorizontalFrame* FracControl= new TGHorizontalFrame(addsub);
			fHslider1 = new TGHSlider(FracControl,500, kSlider2);
			fHslider1->Connect("PositionChanged(Int_t)", "jEnv", this, "DoSlider()");
			fHslider1->SetRange(0,500);
			fHslider1->SetPosition(0);
			FracControl->AddFrame(fHslider1,new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 1));
		
			fTeh1 = new TGTextEntry(FracControl, fTbh1 = new TGTextBuffer(5));//Create some text entry boxes 
			fTeh1->SetToolTipText("Subtraction/Addition Fraction");
			fTeh1->SetDefaultSize(50,25);
			fTeh1->SetAlignment (kTextRight);
			fTeh1->Connect("ReturnPressed()", "jEnv", this,"DoText()");//So it doesnt continually do things while typing is occurrings
			fTeh1->Connect("TabPressed()", "jEnv", this,"DoText()");
			sprintf(buf, "%.1f", 0.0);fTbh1->AddText(0, buf);
			FracControl->AddFrame(fTeh1);
			
			addsubclick = new TGTextButton(FracControl," Sub ");
			addsubclick->Connect("Clicked()","jEnv",this,"AddSubButton()");
			FracControl->AddFrame(addsubclick);
			
			fCheck1 = new TGCheckButton(FracControl,"Hide Ers");
			fCheck1->SetState(kButtonDown);
			fCheck1->Connect(" Clicked()", "jEnv", this,"DoSlider()");
			fCheck1->SetToolTipText("Hide Bin Errors on drawn histograms");
			FracControl->AddFrame(fCheck1);
		
			
		addsub->AddFrame(FracControl,new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 1));
		
		result= new TRootEmbeddedCanvas("histaddres",addsub,600,400);
		result->GetCanvas()->SetMargin(0.12,0.04,0.12,0.05);
		
		result->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0,0,"ClickPeakDrawConnect(Int_t,Int_t,Int_t,TObject*)");
		result->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0,0,"ToolTipHide()");//added because this embedded canvas put tooltip at wrong coordinates on screen
		
		addsub->AddFrame(result,new TGLayoutHints(kLHintsExpandY|kLHintsExpandX, 1, 1, 1, 1));
	this->AddFrame(addsub,new TGLayoutHints(kLHintsExpandY|kLHintsExpandX, 1, 1, 1, 1));
	
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
	
	Hide();
	
	fCanvas1->CFriends.push_back(A->GetCanvas());
	fCanvas1->CFriends.push_back(B->GetCanvas());
	A->GetCanvas()->SetMargin(0,0,0,0);
	B->GetCanvas()->SetMargin(0,0,0,0);
	
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
void jEnv::Gatter(){
	if(fCanvas1->Type()>1)new jgating_tool(fCanvas1->Hist());
};


void jEnv::DrawCpy(){
	HistDrawCopyPeaker(fCanvas1->Hist());
};

void jEnv::SaveAs(){
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
	result->Resize(600,400);
	Resize(this->GetDefaultSize());
	gClient->NeedRedraw(this);
}

void jEnv::Hide(){
	HideFrame(addsub);
	Resize(this->GetDefaultSize());
	gClient->NeedRedraw(this);
}

void jEnv::GrabA(Int_t c,Int_t a,Int_t b,TObject* d){if(c==1)Grab(0);}
void jEnv::GrabB(Int_t c,Int_t a,Int_t b,TObject* d){if(c==1)Grab(1);}
void jEnv::Grab(int i){
	TH1** H=&AHist;string S="AddSubHoldHistA";
	if(i){H=&BHist;S="AddSubHoldHistB";}
	if(fCanvas1->Type()==1){
		if(*H)delete *H;
		*H=(TH1*)fCanvas1->Hist()->Clone(S.c_str());
		DrawAB(i);
		if(SumHist){delete SumHist;SumHist=0;}
		DoSlider();
	}
}

void jEnv::DrawAB(int i){
	TVirtualPad* hold=gPad;
	TH1* H=AHist;TCanvas* Can=A->GetCanvas();
	if(i){H=BHist;Can=B->GetCanvas();}
	if(H){
		Can->cd();
		H->GetXaxis()->SetLabelSize(0);
		H->GetYaxis()->SetLabelSize(0);
		H->SetStats(kFALSE);
		H->DrawCopy();
	}else{
		Can->Clear();
	}
	Can->Modified();
	Can->Update();
	gPad=hold;
}

void jEnv::Swap(){
	TH1* H=AHist;
	AHist=BHist;
	BHist=H;
	DrawAB(0);
	DrawAB(1);
	if(SumHist){delete SumHist;SumHist=0;}
	DoSlider();
}


void jEnv::DoSlider(){TVirtualPad* hold=gPad;
	
	double frac=fHslider1->GetPosition()/500.0;
	double fracfrac=0.03;
	
	if(AHist&&BHist){
		int rmin=1;
		int rmax=-1;
		
		//Check the 2 ranges
		double AXt=AHist->GetXaxis()->GetXmax();
		double AXb=AHist->GetXaxis()->GetXmin();
		double BXt=BHist->GetXaxis()->GetXmax();
		double BXb=BHist->GetXaxis()->GetXmin();
		double ranges=(AXt-AXb)/(BXt-BXb);
		if(AXt<BXb||BXt<AXb)return;
			
		TH1* back;
		bool backtmp=false;
		
		//Get the B hist in the right form
		if((AHist->GetNbinsX()!=BHist->GetNbinsX())||
		   (ranges<0.999)||(ranges>1.001)){
			back=(TH1*)AHist->Clone();
			back->Reset();
			ExtreemRebin(back,BHist);
			backtmp=true;
		}else{
			back=BHist;
		}
		
		//Delete the previous result and get axis info
		if(SumHist){
			rmin=SumHist->GetXaxis()->GetFirst();
			rmax=SumHist->GetXaxis()->GetLast();
			delete SumHist;SumHist=0;
		}
		
		//Do add/subtraction
		if(gSubtract){
			SumHist=scaled_back_subtract(AHist,back,frac,fracfrac);
		}else{
// 			SumHist=scaled_addition(AHist,back,frac,fracfrac);//Decided no scaling for addition
			SumHist=(TH1*)AHist->Clone();
			SumHist->Add(back,frac);
		}
		
		if(backtmp)delete back;
		
		//Draw new results with and adjust axis
		result->GetCanvas()->cd();
			// SumHist->GetXaxis()->SetLabelSize();
			// SumHist->GetYaxis()->SetLabelSize();
			if(rmax>rmin)SumHist->GetXaxis()->SetRange(rmin,rmax);
			SumHist->SetName("AddSubResultHist");
			hformat(SumHist,0);
			// SumHist->SetMinimum(SumHist->GetBinContent(SumHist->GetMinimumBin()));
			if(fCheck1->GetState())SumHist->Draw("hist");else SumHist->Draw();
		result->GetCanvas()->Modified();
		result->GetCanvas()->Update();
	}else{
		result->GetCanvas()->Clear();
	}
	
	UpdateText();
	
gPad=hold;}

void jEnv::DoText(){
	double backfrack=atof(fTbh1->GetString());
	backfrack*=500;
	fHslider1->SetPosition(backfrack);
	DoSlider();
}
	
void jEnv::UpdateText(){
	char buf[32];
	//update the text now the sliders have moved
	sprintf(buf, "%.3f", fHslider1->GetPosition()/500.0);
	fTbh1->Clear();	fTbh1->AddText(0, buf);
	fTeh1->SetCursorPosition(fTeh1->GetCursorPosition());fTeh1->Deselect();
	gClient->NeedRedraw(fTeh1);

}

void jEnv::AddSubButton(){
	gSubtract=!gSubtract;
	if(gSubtract)
		addsubclick->SetText(" Sub ");
	else
		addsubclick->SetText(" Add ");
	gClient->NeedRedraw(addsubclick);
	DoSlider();
}
