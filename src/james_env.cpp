#include "james_env.h"

CCframe::CCframe(const char * name,const TGWindow* p,UInt_t w,UInt_t h,UInt_t options,Pixel_t back):TRootEmbeddedCanvas(name,p,w,h,options,back),current(0),currentpad(0),currentcan(0){TVirtualPad* hold=gPad;
	this->GetCanvas()->SetMargin(0,0,0,0);
	TQObject::Connect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", "CCframe", this,"TrackCaptureHistogram(TPad*,TObject*,Int_t)");
	gPad=hold;
    fClass=TH1::Class();
    fNamed=TH1::Class()->InheritsFrom("TNamed");
}

CCframe::~CCframe(){
	TQObject::Disconnect(this);
	TQObject::Disconnect("TCanvas", 0, this);
// 	TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "CaptureCanvas(TPad*,TObject*,Int_t)");
// 	Disconnect(0,this,0);
// 	TQObject::Disconnect((TCanvas*)this);
}


void CCframe::SetClass(TClass* iClass){
    fClass=iClass;
    fNamed=iClass->InheritsFrom("TNamed");
    this->GetCanvas()->Clear();
    current=0;
    currentpad=0;
    currentcan=0;
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
			TObject* fH=0;
			if(obj->InheritsFrom(fClass))fH=obj;//If click was exactly on a histogram?
			else fH=obj_capture(fClass,pad);//Else find first object this pad has
// 			else fH=hist_capture(pad);//Else find first histogram this pad has
			
			if(fH)SetNewObject(fH,pad,sender);
			return;
		}
	}
}

void CCframe::SetNewObject(TObject* fH,TPad* Pad,TCanvas* Can){
	if(fH!=current){
		current=fH;
		currentpad=Pad;
		currentcan=Can;
        if(fNamed)fName=current->GetName();
		TVirtualPad* hold=gPad;
		this->GetCanvas()->cd();
        
        //Drawing Options
		if(HType(fH)){
            if(HType(fH)==3){
                this->GetCanvas()->Clear();
                TText t;
                t.SetTextAlign(22);
                t.SetTextSize(.6);
                t.DrawTextNDC(.5,.5,"TH3");
            }else{
                TH1* H=((TH1*)fH)->DrawCopy("COL");
                H->GetXaxis()->SetLabelSize(0);
                H->GetYaxis()->SetLabelSize(0);
                H->SetStats(kFALSE);
            }
		}else if(fH->InheritsFrom("TGraph")){
            gPad->Update();
            ((TGraph*)fH)->DrawClone("al");
        }
		this->GetCanvas()->Modified();
		this->GetCanvas()->Update();
		gPad=hold;
        NewObject();
	}
}

TH1* CCframe::Hist(){
        if(fClass->InheritsFrom("TH1")){
            return (TH1*)Object();
        }
        return 0;
}
    
    
TObject* CCframe::Object(){
	if(current){
        TObject* Ob;
        if(fNamed&&fName.size()){
            Ob = gROOT->FindObject(fName.c_str());
    // 		cout<<endl<<"Checking if histogram pointer "<<current<<" is valid: "<<Ob<<endl;
            if(Ob)if(Ob->InheritsFrom(fClass))return Ob;
            //Often fails because FindObject has limitations in terms of directories and drawn histograms we might have grabbed.
            //If the canvas is still drawn we might still be able to grab the histogram
        }
		
		TPad* Pad=(TPad*)gROOT->GetListOfCanvases()->FindObject(currentpad);
// 		cout<<endl<<"Checking if pad pointer "<<currentpad<<" is in gROOT->GetListOfCanvases() :"<<Pad<<endl;
		if(Pad){
			Ob=Pad->GetListOfPrimitives()->FindObject(current);
			if(Ob)if(Ob->InheritsFrom(fClass))return Ob;
		}
		
		TCanvas* Can=(TCanvas*)gROOT->GetListOfCanvases()->FindObject(currentcan);
// 		cout<<endl<<"Checking if canvas pointer "<<currentcan<<" is in gROOT->GetListOfCanvases() :"<<Can<<endl;
		if(Can){
			Ob=Can->GetListOfPrimitives()->FindObject(current);
			if(Ob)if(Ob->InheritsFrom(fClass))return Ob;
			
			Pad=(TPad*)Can->GetListOfPrimitives()->FindObject(currentpad);
			if(Pad){
				Ob=Pad->GetListOfPrimitives()->FindObject(current);
				if(Ob)if(Ob->InheritsFrom(fClass))return (TH1*)Ob;
			}
		}
	}
	return 0;
}

int CCframe::Type(){
	return HType(Hist());
}
		
		
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

int jEnv::SumNameItt = 0;

jEnv::jEnv() : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame),fFitPanel(0),fSpecTool(0),addsub(0),A(0),B(0),result(0),AHist(0),BHist(0),SumHist(0),SameSave(0),gDrawSame(false){
TVirtualPad* hold=gPad;
	SetWindowName("jEnv");
	char buf[32];	//A buffer for processing text through to text boxes
	SetCleanup(kDeepCleanup);
	gSubtract=0;
	
	Stop.Start();

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
		
			fTeh1 = new TGTextEntry(FracControl, fTbh1 = new TGTextBuffer(5));//Create some text entry boxes 
			fTeh1->SetToolTipText("Subtraction/Addition Fraction");
			fTeh1->SetDefaultSize(50,25);
			fTeh1->SetAlignment (kTextRight);
			fTeh1->Connect("ReturnPressed()", "jEnv", this,"DoText()");//So it doesnt continually do things while typing is occurrings
			fTeh1->Connect("TabPressed()", "jEnv", this,"DoText()");
			sprintf(buf, "%.1f", 0.0);fTbh1->AddText(0, buf);
			FracControl->AddFrame(fTeh1);
			
			addsubclick = new TGTextButton(FracControl,"     Add/Sub     ");
			addsubclick->Connect("Clicked()","jEnv",this,"AddSubButton()");
			FracControl->AddFrame(addsubclick);
			
			fCheck1 = new TGCheckButton(FracControl,"Hide Ers");
			fCheck1->SetState(kButtonDown);
			fCheck1->Connect(" Clicked()", "jEnv", this,"DoSlider()");
			fCheck1->SetToolTipText("Hide Bin Errors on drawn histograms");
			FracControl->AddFrame(fCheck1);
		
		addsub->AddFrame(FracControl,new TGLayoutHints(kLHintsCenterX, 2, 2, 2, 2));
        
		TGHorizontalFrame* FracSlider= new TGHorizontalFrame(addsub);
			fHslider1 = new TGHSlider(FracSlider,1000, kSlider2);
			fHslider1->Connect("PositionChanged(Int_t)", "jEnv", this, "DoSlider()");
			fHslider1->SetRange(-500,500);
			fHslider1->SetPosition(0);
			FracSlider->AddFrame(fHslider1,new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 1));
		addsub->AddFrame(FracSlider,new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 1));
		
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
	if(fCanvas1->Type()<3){
		if(*H)delete *H;
		*H=(TH1*)fCanvas1->Hist()->Clone(S.c_str());
		DrawAB(i);
		if(SumHist){delete SumHist;SumHist=0;SumNameItt++;}
		DoSlider();
	}
}

void jEnv::DrawAB(int i){
	TVirtualPad* hold=gPad;
	TH1* H=AHist;TCanvas* Can=A->GetCanvas();
	if(i){
        H=BHist;Can=B->GetCanvas();
    }else{
        Abinwidth=H->GetXaxis()->GetBinWidth(1);
    }
	if(H){
		Can->cd();
		H->GetXaxis()->SetLabelSize(0);
		H->GetYaxis()->SetLabelSize(0);
		H->SetStats(kFALSE);
		H->DrawCopy("histcol");
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
	if(SumHist){delete SumHist;SumHist=0;SumNameItt++;}
	DoSlider();
}


void jEnv::DoSlider(){
    int slidepos=fHslider1->GetPosition();
	double frac=slidepos/500.0;
	double fracfrac=0.03;//Arbitrary summing fraction error 
	
	UpdateText();
	
	if(AHist&&BHist){
		int Type=HType(AHist);
		if(Type==HType(BHist)){
            
			if(Type==2){
                if(gSubtract>1){
                    gSubtract=-1;
                    AddSubButton();
                    return;
                }
                
				if(Stop.RealTime()<4){
// 					cout<<endl<<"NO TIME "<<Stop.CpuTime()<<endl;
					Stop.Start(kFALSE);	
					return;
				}
// 				cout<<endl<<"GOOD TIME"<<endl;
				Stop.Start();
			}
			
			int rmin=1;
			int rmax=-1;
			
			//Check the 2 ranges
			double AXt=AHist->GetXaxis()->GetXmax();
			double AXb=AHist->GetXaxis()->GetXmin();
			double BXt=BHist->GetXaxis()->GetXmax();
			double BXb=BHist->GetXaxis()->GetXmin();
			double ranges=(AXt-AXb)/(BXt-BXb);
			if(AXt<BXb||BXt<AXb)return;
				
			TH1* back=BHist;
			bool backtmp=false;
			
			//Get the B hist in the right form
			if((AHist->GetNbinsX()!=BHist->GetNbinsX())||
			(ranges<0.999)||(ranges>1.001)){
				if(Type==2)return;
				back=(TH1*)AHist->Clone();
				back->Reset();
				ExtreemRebin(back,BHist);
				backtmp=true;
			}
			
			if(Type==2){
				AXt=AHist->GetYaxis()->GetXmax();
				AXb=AHist->GetYaxis()->GetXmin();
				BXt=BHist->GetYaxis()->GetXmax();
				BXb=BHist->GetYaxis()->GetXmin();
				ranges=(AXt-AXb)/(BXt-BXb);
				if((AXt<BXb||BXt<AXb)||(AHist->GetNbinsY()!=BHist->GetNbinsY())||
				(ranges<0.999)||(ranges>1.001)){
					return;
				}
			}
			
			
			//Delete the previous result and get axis info
			if(SumHist){
				rmin=SumHist->GetXaxis()->GetFirst();
				rmax=SumHist->GetXaxis()->GetLast();
				delete SumHist;SumHist=0;
			}
			
			//Do add/subtraction
			
            switch(gSubtract) {
                case 1 :    SumHist=scaled_addition(AHist,back,frac,fracfrac);
                            //SumHist=scaled_back_subtract(AHist,back,frac,-fracfrac);
                            break;
                case 2 :    SumHist=(TH1*)back->Clone();
                            SumHist->Scale((frac+1)*AHist->Integral()/back->Integral());
                            break;
                case 3 :    SumHist=(TH1*)back->Clone();
                            transpose_bins(SumHist,slidepos);
                            break;
                default :   SumHist=(TH1*)AHist->Clone();
                            SumHist->Add(back,frac);   
                            break;
            }
			stringstream ss;ss<<"AddSubResultHist"<<SumNameItt;
			SumHist->SetName(ss.str().c_str());

			if(backtmp)delete back;
			
			//Draw new results with and adjust axis
			TVirtualPad* hold=gPad;
			result->GetCanvas()->cd();
                
                if(gSubtract>1){
                    TH1* H;
                    if(fCheck1->GetState())H=AHist->DrawCopy("hist");else   H=AHist->DrawCopy(""); 
                    hformat(H,0); 
                    if(rmax>rmin)H->GetXaxis()->SetRange(rmin,rmax);
                    if(rmax>rmin)SumHist->GetXaxis()->SetRange(rmin,rmax);
                    
                    SumHist->SetLineColor(2);
                    if(fCheck1->GetState())SumHist->Draw("histsame");else SumHist->Draw("same");
                }else{
                    hformat(SumHist,0);
                    if(rmax>rmin)SumHist->GetXaxis()->SetRange(rmin,rmax);
                    if(fCheck1->GetState())SumHist->Draw("hiscol");else SumHist->Draw("col"); 
                }
                
                
// 			if(rmax>rmin)SumHist->GetXaxis()->SetRange(rmin,rmax);
//             hformat(SumHist,0);
//             if(fCheck1->GetState())SumHist->Draw("hiscol");else SumHist->Draw("col");
//             if(gSubtract>1){
//                 if(fCheck1->GetState())AHist->Draw("histsame");else AHist->Draw("same");  
//                 SumHist->SetLineColor(2);
//             }
            
			result->GetCanvas()->Modified();
			result->GetCanvas()->Update();
			gPad=hold;
		}else{
			result->GetCanvas()->Clear();
		}
	}else{
		result->GetCanvas()->Clear();
	}
}

void jEnv::DoText(){
	double backfrack=atof(fTbh1->GetString());
    
    if(gSubtract==3){
        backfrack/=Abinwidth;
    }else{
        backfrack*=500;
    }
    
	fHslider1->SetPosition(backfrack);
	DoSlider();
}
	
void jEnv::UpdateText(){
	char buf[32];
	//update the text now the sliders have moved
    
    
    if(gSubtract==3){
        int s=floor(log10(Abinwidth)); if(s>0)s=0;
        stringstream format;
        format<<"%."<<abs(s)<<"f";
        sprintf(buf, format.str().c_str(), fHslider1->GetPosition()*Abinwidth);
    }else{
        sprintf(buf, "%.3f", fHslider1->GetPosition()/500.0);
    }  
    
	fTbh1->Clear();	fTbh1->AddText(0, buf);
	fTeh1->SetCursorPosition(fTeh1->GetCursorPosition());fTeh1->Deselect();
	gClient->NeedRedraw(fTeh1);

}

void jEnv::AddSubButton(){
	gSubtract++;
    
	if(gSubtract>3)gSubtract=0;
    
    switch(gSubtract) {
    case 0 : addsubclick->SetText("   Add/Sub   ");
             break;       
    case 1 : addsubclick->SetText("Scale Add/Sub");
             break;
    case 2 : addsubclick->SetText("Scale Compare");
             break;
    case 3 : addsubclick->SetText("Shift Compare");
             break;
    }

	fHslider1->SetPosition(0);
	gClient->NeedRedraw(addsubclick);
	DoSlider();
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
                double efY=1;
                if(Y){
                    efY=gg->Eval(H->GetYaxis()->GetBinCenter(y));
                }
                scaled->SetBinContent(bin,n/(efY*efX));
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



