#include "j_env_elements.h"

CCframe::CCframe(const char * name,const TGWindow* p,UInt_t w,UInt_t h,UInt_t options,Pixel_t back):TRootEmbeddedCanvas(name,p,w,h,options,back),current(0),currentpad(0),currentcan(0),currenttrust(0){TVirtualPad* hold=gPad;
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
    currenttrust=0;
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
			if(obj->InheritsFrom(fClass))fH=obj;// If click was exactly on a "histogram"?
			else fH=obj_capture(fClass,pad);// Else find first object this pad has
// 			else fH=hist_capture(pad);// Else find first histogram this pad has
			
			if(fH)SetNewObject(fH,pad,sender);
			return;
		}
	}
}

void CCframe::SetNewObject(TObject* fH,TPad* Pad,TCanvas* Can,bool Trust){
	if(fH!=current){
		current=fH;
		currentpad=Pad;
		currentcan=Can;
		currenttrust=Trust;
        
		if(fNamed)fName=current->GetName();
			TVirtualPad* hold=gPad;
			this->GetCanvas()->cd();
		
		// Drawing Options for all possible CCframe instances, so not only for current fClass setting
			if(HType(fH)){
                if(HType(fH)==3 || (HType(fH)==2&&(((TH1*)fH)->GetNbinsX()*((TH1*)fH)->GetNbinsY()>1000000))){
                    PrintMessageInternal(fH->ClassName(),fH->GetName());
                }else{
                    TH1* H=DrawCopyHistOpt((TH1*)fH);
                    H->GetXaxis()->SetLabelSize(0);
                    H->GetYaxis()->SetLabelSize(0);
                    H->SetStats(kFALSE);
                }
			}else if(fH->IsA()->InheritsFrom(TGraph::Class())){
                DrawCopyGraphOpt((TGraph*)fH);
            }
			this->GetCanvas()->Modified();
			this->GetCanvas()->Update();
			gPad=hold;
		NewObject();
		NewObject(fH);
	}
}


void CCframe::PrintMessage(TString main,TString sub){
	TVirtualPad* hold=gPad;
	this->GetCanvas()->cd();
	
	PrintMessageInternal(main,sub);
	
	this->GetCanvas()->Modified();
	this->GetCanvas()->Update();
	gPad=hold;
}

void CCframe::PrintMessageInternal(TString main,TString sub){
	this->GetCanvas()->Clear();
	TText t;
	t.SetTextAlign(22);
	t.SetTextSize(.45);
	t.DrawTextNDC(.5,.5,main);
	
	t.SetTextSize(1.5/(sub.Length()+1));
	t.DrawTextNDC(.5,0.12,sub);
}

void CCframe::NonGuiNew(TObject* obj){
	if(obj->InheritsFrom(fClass)){
		SetNewObject(obj,0,0,1);
	}
	return;
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
				if(Ob)if(Ob->InheritsFrom(fClass))return Ob;
			}
		}
		
		if(currenttrust){
            return current;
			// We trust the memory management system that 
			// although we haven't located current, it's pointer is still valid
		}
		
		if(fNamed&&fName.size()){
            // Re-arranged to put this last as it is susceptible to duplicate name errors
			Ob = gROOT->FindObject(fName.c_str());
	// 		cout<<endl<<"Checking if histogram pointer "<<current<<" is valid: "<<Ob<<endl;
			if(Ob)if(Ob->InheritsFrom(fClass))return Ob;
			//Often fails because FindObject has limitations in terms of directories and drawn histograms we might have grabbed.
		}
	}
	
// 	cout<<endl<<"CHECKING gObjectTable "<<gObjectTable->PtrIsValid(current)<<endl;
	
	return 0;
}

int CCframe::Type(){
	return HType(Hist());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

ClassImp(jHistCapButton);

void jHistCapButton::Clicked(){//SetCapture()
	TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "CaptureHistogram(TPad*,TObject*,Int_t)");
	TQObject::Connect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", "jHistCapButton", this, "CaptureHistogram(TPad*,TObject*,Int_t)");
};
void jHistCapButton::CaptureHistogram(TPad* pad,TObject* obj,Int_t event){
	if(1 == event){
		
		TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "CaptureHistogram(TPad*,TObject*,Int_t)");
		
		if(obj){
			TH1* fH=0;
			if(obj->InheritsFrom("TH1"))fH=(TH1*)obj;
			else fH=hist_capture(pad);
			
			if(fH){
				NewHist(fH);
                return;
			}
		}
		cout<<endl<<endl<<"Capture Failed"<<endl;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

int jAddSubTool::SumNameItt = 0;

jAddSubTool::jAddSubTool(CCframe* Frame,const TGWindow * p, UInt_t w, UInt_t h, UInt_t options):TGCompositeFrame(p,w,h,options),A(0),B(0),result(0),AHist(0),BHist(0),BSet(0),SumHist(0),DrawHist(0),TempB(0),fGrabFrame(Frame){
	char buf[32];	//A buffer for processing text through to text boxes
	SetCleanup(kDeepCleanup);
	gSubtract=0;
	
	Stop.Start();
    
		TGHorizontalFrame* ABswap= new TGHorizontalFrame(this);
			A= new TRootEmbeddedCanvas("histholdA",ABswap,100,100);
			A->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "jAddSubTool", this,"GrabA(Int_t,Int_t,Int_t,TObject*)");
			TGTextButton* swapB = new TGTextButton(ABswap,"<->");
			swapB->Connect("Clicked()","jAddSubTool",this,"Swap()");	
			B= new TRootEmbeddedCanvas("histholdB",ABswap,100,100);
			B->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "jAddSubTool", this,"GrabB(Int_t,Int_t,Int_t,TObject*)");
			ABswap->AddFrame(A);
			ABswap->AddFrame(swapB,new TGLayoutHints(kLHintsCenterY, 1, 1, 1, 1));
			ABswap->AddFrame(B);
		this->AddFrame(ABswap,new TGLayoutHints(kLHintsCenterX, 1, 1, 1, 1));
		
		TGHorizontalFrame* FracControl= new TGHorizontalFrame(this);
		
			fTeh1 = new TGTextEntry(FracControl, fTbh1 = new TGTextBuffer(5));//Create some text entry boxes 
			fTeh1->SetToolTipText("Subtraction/Addition Fraction");
			fTeh1->SetDefaultSize(50,25);
			fTeh1->SetAlignment (kTextRight);
			fTeh1->Connect("ReturnPressed()", "jAddSubTool", this,"DoText()");//So it doesnt continually do things while typing is occurrings
			fTeh1->Connect("TabPressed()", "jAddSubTool", this,"DoText()");
			sprintf(buf, "%.1f", 0.0);fTbh1->AddText(0, buf);
			FracControl->AddFrame(fTeh1);
			
			addsubclick = new TGTextButton(FracControl,"     Add/Sub     ");
			addsubclick->Connect("Clicked()","jAddSubTool",this,"AddSubButton()");
			FracControl->AddFrame(addsubclick);
			
			fCheck1 = new TGCheckButton(FracControl,"Hide Ers");
			fCheck1->SetState(kButtonDown);
			fCheck1->Connect(" Clicked()", "jAddSubTool", this,"DoSlider()");
			fCheck1->SetToolTipText("Hide Bin Errors on drawn histograms");
			FracControl->AddFrame(fCheck1);
		
		this->AddFrame(FracControl,new TGLayoutHints(kLHintsCenterX, 2, 2, 2, 2));
        
		TGHorizontalFrame* FracSlider= new TGHorizontalFrame(this);
			fHslider1 = new TGHSlider(FracSlider,1000, kSlider2);
			fHslider1->Connect("PositionChanged(Int_t)", "jAddSubTool", this, "DoSlider()");
			fHslider1->SetRange(-500,500);
			fHslider1->SetPosition(0);
			FracSlider->AddFrame(fHslider1,new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 1));
		this->AddFrame(FracSlider,new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 1));
		
		result= new TRootEmbeddedCanvas("histaddres",this,600,400);
		result->GetCanvas()->SetMargin(0.12,0.04,0.12,0.05);
		
		result->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0,0,"ClickPeakDrawConnect(Int_t,Int_t,Int_t,TObject*)");
		result->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0,0,"ToolTipHide()");//added because this embedded canvas put tooltip at wrong coordinates on screen
		
		this->AddFrame(result,new TGLayoutHints(kLHintsExpandY|kLHintsExpandX, 1, 1, 1, 1));
	
        
        
// 	result->Resize(600,400);
// 	MapSubwindows();
// 	Resize(GetDefaultSize());
// 	MapWindow();

	fGrabFrame->CFriends.push_back(A->GetCanvas());
	fGrabFrame->CFriends.push_back(B->GetCanvas());
    
	A->GetCanvas()->SetMargin(0,0,0,0);
	B->GetCanvas()->SetMargin(0,0,0,0);
}


void jAddSubTool::GrabA(Int_t c,Int_t a,Int_t b,TObject* d){if(c==1)Grab(0);}
void jAddSubTool::GrabB(Int_t c,Int_t a,Int_t b,TObject* d){if(c==1)Grab(1);}
void jAddSubTool::Grab(int i){
    // Make a copy of the globally selected histogram into the class 
    
	TH1** H=&AHist;string S="AddSubHoldHistA";
	if(i){H=&BHist;S="AddSubHoldHistB";}
	int type=fGrabFrame->Type();
	if(type && type<3){
		if(*H)delete *H;
		*H=(TH1*)fGrabFrame->Hist()->Clone(S.c_str());
        if(type==1){
            (*H)->SetBinContent((*H)->GetNbinsX(),0);//Empty TH1 over/overflows
            (*H)->SetBinContent(0,0);
        }
		DrawAB(i);
		if(SumHist){delete SumHist;SumHist=0;SumNameItt++;}
		PrepareB();
		DoSlider();
	}
}


void jAddSubTool::DrawAB(int i){
    // Draw the small selected histograms icons. Called for new or for swap AB.
    
	TVirtualPad* hold=gPad;
	TH1* H=AHist;TCanvas* Can=A->GetCanvas();
	if(i){
        H=BHist;Can=B->GetCanvas();
    }else{
        Abinwidth=1;
    }
    
	if(H){
		Can->cd();
        H->GetXaxis()->SetLabelSize(0);
		H->GetYaxis()->SetLabelSize(0);
		H->SetStats(kFALSE);
		DrawCopyHistOpt(H);
        
        // Set class-scope variable that holds the width of A (primary) histogram bins.
        // This is here rather than at input, because DrawAB is called for both a new histogram AND for switching AB
        if(!i)Abinwidth=H->GetXaxis()->GetBinWidth(1); 
	}else{
		Can->Clear();
	}
	Can->Modified();
	Can->Update();
	gPad=hold;
}

void jAddSubTool::Swap(){
	TH1* H=AHist;
	AHist=BHist;
	BHist=H;
	DrawAB(0);
	DrawAB(1);
	if(SumHist){delete SumHist;SumHist=0;SumNameItt++;DrawHist=0;} // Delete in advance so it isnt used by DoSlider() for range;
	PrepareB();
	DoSlider();
}

void jAddSubTool::PrepareB(){
    if(BSet&&TempB){delete BSet;} //If TempB=true then BSet is NOT sharing BHist
    BSet=0;
    TempB=false;
    
	if(!(AHist&&BHist))return;
    int Type=HType(AHist);
    if(Type!=HType(BHist))return;
			
    //Check the 2 ranges
    double AXt=AHist->GetXaxis()->GetXmax();
    double AXb=AHist->GetXaxis()->GetXmin();
    double BXt=BHist->GetXaxis()->GetXmax();
    double BXb=BHist->GetXaxis()->GetXmin();
    double ranges=(AXt-AXb)/(BXt-BXb);
    
    if(AXt<BXb||BXt<AXb)return; // No X overlap
        
    bool xrange=((ranges<0.9990)||(ranges>1.0001));  // True if range differ
    bool xbins=(AHist->GetNbinsX()!=BHist->GetNbinsX()); // True if Nbins differ

    if(Type==2){
        // For TH2s only exact matches, otherwise return with BSet=0;
        if(xbins||xrange)return;
        
        AXt=AHist->GetYaxis()->GetXmax();
        AXb=AHist->GetYaxis()->GetXmin();
        BXt=BHist->GetYaxis()->GetXmax();
        BXb=BHist->GetYaxis()->GetXmin();
        ranges=(AXt-AXb)/(BXt-BXb);
        if((AXt<BXb||BXt<AXb)||(AHist->GetNbinsY()!=BHist->GetNbinsY())||
        (ranges<0.9999)||(ranges>1.0001)){
            return;
        }
                
        BSet=BHist; // Perfect (enough) match
        return;
    }
    
    // Histogram types match sufficiently that BSet will be set
    BSet=BHist; // Initially just a pointer to the main BHist
    if(!xbins&&!xrange)return;
    
    // Now get B hist in the right form

    if(xbins&&!xrange){ // As the range is same, but bins differ, try integer rebinning.
        
        if(AHist->GetNbinsX()<BHist->GetNbinsX()){
            if(!(BHist->GetNbinsX()%AHist->GetNbinsX())){ // No remainder A_bins<B
                BSet=(TH1*)BHist->Clone();
                BSet->Rebin(BHist->GetNbinsX()/AHist->GetNbinsX()); // Just rebin B down
                TempB=true;
                return;
            }
        }else{
            if(!(AHist->GetNbinsX()%BHist->GetNbinsX())){ // No remainder A_bins>B
                BSet=(TH1*)AHist->Clone();
                double frac=AHist->GetNbinsX()/BHist->GetNbinsX();
                for(int b=1;b<=AHist->GetNbinsX();b++){  // Divide the content of bin into new narrow bins
                    double x=BSet->GetXaxis()->GetBinCenter(b);
                    double B=BHist->GetXaxis()->FindBin(x);
                    BSet->SetBinContent(b,BHist->GetBinContent(B)*frac);
                }
                TempB=true;
                return;
            }
            
        }
    }
        
    // If not a match or an easy rebin, do silly rebin    
    if(xbins||xrange){
        BSet=(TH1*)AHist->Clone();
        ExtreemRebin(BSet,BHist);
        TempB=true;
    }
}


void jAddSubTool::DoSlider(){
    // Take the value from the slider, do the histogram combining operations and then draw the result.
    
    int slidepos=fHslider1->GetPosition();
	double frac=slidepos/500.0;
	double fracfrac=gGlobalSubtractionFractionError;//Arbitrary summing fraction error. Default = 0.04
	
	UpdateText();
	
    // If we dont have 2 histogram pointers
	if(!(AHist&&BSet)){  
        result->GetCanvas()->Clear();
        result->GetCanvas()->Modified();
        result->GetCanvas()->Update();
        return;
    }
        
    // If TH2 
    if(HType(AHist)==2){
        
        // Only option <2 allowed for 2D 
        if(gSubtract>1){ 
            gSubtract=-1;
            AddSubButton();
            return;
        }
        
        // Limit update speed for TH2 to save the CPU
        if(Stop.RealTime()<4){
// 				cout<<endl<<"NO TIME "<<Stop.CpuTime()<<endl;
            Stop.Start(kFALSE);	
            return;
        }
        Stop.Start();
    }
    
    int rmin=1;
    int rmax=-1;

    //Delete the previous result and get axis info
    if(DrawHist){
        //Draw hist could be SumHist or a DrawCopy of A so DONT delete though DrawHist
        rmin=DrawHist->GetXaxis()->GetFirst();
        rmax=DrawHist->GetXaxis()->GetLast();
    }
    if(SumHist){
        delete SumHist;SumHist=0;
    }
        
    //Do add/subtraction/other prepartion of result histogram
    
    
// For addition, the rebinned "BSet" should be used, but for comparison the orginal BHist should be used,
// with aproiate scaling as needed to account for integral:Y_height ratio i.e. bin width

    switch(gSubtract) {
		
        case 1 :    SumHist=(TH1*)AHist->Clone();
					jGateSubtractionFrame::ScaledBackgroundSubtract(SumHist,BSet,-frac,fracfrac);  // Normalised Scaled Addition
                    break;
        case 2 :    SumHist=(TH1*)BHist->Clone();   //Scaled Comparison
                    SumHist->Scale(frac+1);
                    break;
        case 3 :    SumHist=(TH1*)BHist->Clone();
                    transpose_bins(SumHist,slidepos);
                    break;
        case 4 :    SumHist=(TH1*)BHist->Clone();
                    SumHist->GetXaxis()->SetLimits(BHist->GetXaxis()->GetXmin(),(frac+1)*BHist->GetXaxis()->GetXmax()); 
                    break; 
        default :   SumHist=(TH1*)AHist->Clone();
					jGateSubtractionFrame::ScaledBackgroundSubtract(SumHist,BSet,-frac,fracfrac,false);  // Simple Addition
                    break;
    }
    
    stringstream ss;ss<<"AddSubResultHist"<<SumNameItt;
    SumHist->SetName(ss.str().c_str());

    // Draw new results with and adjust axis
    TVirtualPad* hold=gPad;
    result->GetCanvas()->cd();
    
    if(gSubtract>1){   // Draw the comparison options
        
        DrawHist=DrawCopyHistOpt(AHist,fCheck1->GetState());
        
        SumHist->SetLineColor(2);
        DrawHistOpt(SumHist,fCheck1->GetState(),false,true); //Draw same
        
        TAxis* TA=DrawHist->GetXaxis();
        if(rmax>rmin){
            TA->SetRange(rmin,rmax);
        }
        
        if(gSubtract>2){ // Slide and stretch compare
//             double NA=DrawHist->Integral()*DrawHist->GetBinWidth(1);
            double NA=DrawHist->Integral(TA->GetFirst(),TA->GetLast())*DrawHist->GetBinWidth(1);

            TAxis* TB=SumHist->GetXaxis();
            double NB=SumHist->Integral(TB->FindBin(TA->GetBinLowEdge(TA->GetFirst())),TB->FindBin(TA->GetBinUpEdge(TA->GetLast())))*SumHist->GetBinWidth(1);

            if(NA>0&&NB>0){SumHist->Scale(NA/NB);}
        }
        
    }else{  // Draw the summed histogram options
        
        hformat(SumHist,0);
        DrawHist=SumHist;
        
        DrawHistOpt(SumHist,fCheck1->GetState(),false,false); //Draw
        
        if(rmax>rmin){
            DrawHist->GetXaxis()->SetRange(rmin,rmax);
        }
            
    }

    result->GetCanvas()->Modified();
    result->GetCanvas()->Update();
    gPad=hold;
}

void jAddSubTool::DoText(){
	double backfrack=atof(fTbh1->GetString());
    
    if(gSubtract==3){
        backfrack/=Abinwidth;
    }else{
        backfrack*=500;
    }
    
	fHslider1->SetPosition(backfrack);
	DoSlider();
}
	
void jAddSubTool::UpdateText(){
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

void jAddSubTool::AddSubButton(){
	gSubtract++;
    
	if(gSubtract>4)gSubtract=0;
    
    switch(gSubtract) {
    case 0 : addsubclick->SetText("   Add/Sub   ");
             break;       
    case 1 : addsubclick->SetText("Scale Add/Sub");
             break;
    case 2 : addsubclick->SetText("Scale Compare");
             break;
    case 3 : addsubclick->SetText("Shift Compare");
             break;
    case 4 : addsubclick->SetText("Stretch Comp.");
             break;
    }

	fHslider1->SetPosition(0);
	gClient->NeedRedraw(addsubclick);
	DoSlider();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
 
jDirList::jDirList(const TGWindow* p, UInt_t w, UInt_t h, UInt_t options):TGCompositeFrame(p,w,h,options)
{

//    p->Connect("CloseWindow()", "jDirList", this, "CloseWindow()");
//    p->DontCallClose(); // to avoid double deletions.

   fIcon = gClient->GetPicture("rootdb_t.xpm");
   fIconH1 = gClient->GetPicture("h1_t.xpm");
   fIconH2 = gClient->GetPicture("h2_t.xpm");
   fIconH3 = gClient->GetPicture("h3_t.xpm");
   fIconTHn = gClient->GetPicture("geohype_t.xpm");
   fIconGr = gClient->GetPicture("bld_embedcanvas.xpm");
// fIconGr = gClient->GetPicture("profile_t.xpm");
   fIconMGr = gClient->GetPicture("selection_t.xpm");
   fIconTF = gClient->GetPicture("f1_t.xpm");
   fIconCan = gClient->GetPicture("newcanvas.xpm");
   fIconTree = gClient->GetPicture("tree_t.xpm");


   // use hierarchical cleaning
   SetCleanup(kDeepCleanup);
   
   TGCanvas* canvas = new TGCanvas(this, w, h);
   fContents = new TGListTree(canvas, kHorizontalFrame);

//    fContents = new TGListTree(this, kHorizontalFrame);
   fContents->Connect("DoubleClicked(TGListTreeItem*,Int_t)","jDirList",this,
                      "OnDoubleClick(TGListTreeItem*,Int_t)");
   fContents->Connect("Clicked(TGListTreeItem*,Int_t)","jDirList",this,
                      "OnDoubleClick(TGListTreeItem*,Int_t)");
   AddFrame(canvas,new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kLHintsBottom));
   
#ifdef G__WIN32
   fContents->AddItem(0,"c:\\");  // browse the upper directory
#else
   fContents->AddItem(0,"/");  // browse the upper directory
   TGListTreeItem* CurDir=fContents->AddItem(0,gSystem->pwd());  // Add the current directory
   UseItem(CurDir);//Load the current directory
   fContents->OpenItem(CurDir);//Open the current directory
#endif
   
   
   // If this is set RootFileList will delete all files no matter what individual kCanDelete is set to
// 	RootFileList.SetOwner();

    MapSubwindows();
    Resize();
    MapWindow();
}

jDirList::~jDirList()
{
   // Cleanup.
//RootFileList.IsOwner()<<endl; 
// 	RootFileList.SetOwner(kFALSE);
// RootFileList.RemoveLast();
   gClient->FreePicture(fIcon);
   gClient->FreePicture(fIconH1);
   gClient->FreePicture(fIconH2);
   gClient->FreePicture(fIconH3);
   gClient->FreePicture(fIconTHn);
   gClient->FreePicture(fIconGr);
   gClient->FreePicture(fIconMGr);
   gClient->FreePicture(fIconTF);
   gClient->FreePicture(fIconCan);
   gClient->FreePicture(fIconTree);
   
    RootFileList.Clear("nodelete");
    // Leave the files in memory in case they are being used by other objects.
    // Got rid of complex "File custodians", TFiles can just be left open till end of runtime
    
    Closed(this);
 
   delete fContents;
}


void jDirList::CloseWindow()
{
   delete this;
}

TString jDirList::DirName(TGListTreeItem* item)
{
   // Returns an absolute system path up to and including *item*

   TGListTreeItem* parent;
   TString dirname = item->GetText();

   while ((parent=item->GetParent())) {
      dirname = gSystem->ConcatFileName(parent->GetText(),dirname);
      item = parent;
   }

   return dirname;
}

void jDirList::OnDoubleClick(TGListTreeItem* item, Int_t btn){
    
    if ((btn!=kButton1) || !item) return;
              
    UseItem(item);
}

void jDirList::OpenClose(TGListTreeItem* item){
        //So if it a directory and has already been loaded, clicking just toggles it open
        if(item->IsOpen())fContents->CloseItem(item);
        else fContents->OpenItem(item);
}



void jDirList::UseItem(TGListTreeItem* item){
    
    TSystemDirectory dir(item->GetText(),DirName(item));
    TList *files = dir.GetListOfFiles();

    // If *item* is a system directory files will be non 0
    if (files) {
        //It is a system directory
        if((Bool_t)item->GetUserData()){
            //*GetUserData* is set if *item* has already been processed i.e. opened and had its contents added to *fContents* list
            OpenClose(item);
            return;
        }else{
            files->Sort();
            ProcessSystemDir(files,item);
            return;
        }
        return;
    }

   // Should have dealt with any real system directory above
   // So anything beyond here should be TDirectory structure
    ProcessRootFileObject(item);
}

void jDirList::ProcessSystemDir(TList *files,TGListTreeItem* item){
    // Show Directory Contents
    if (files) {
      TIter next(files);
      TSystemFile *file;
      TString fname;

      while ((file=(TSystemFile*)next())) {
         fname = file->GetName();
         if (file->IsDirectory()) {
            if ((fname!="..") && (fname!=".") && (fname[0]!='.')) { // skip it
               fContents->AddItem(item,fname);
            }
         } else if (fname.EndsWith(".root")) {   // add root files
            fContents->AddItem(item,fname,fIcon,fIcon);
         }
      }
      delete files;

        // Use *UserData* to indicate that item was already browsed
        fContents->OpenItem(item);
        item->SetUserData((void*)1);
   }
   return;
}
   
void jDirList::ProcessRootFileObject(TGListTreeItem* item){
    // Either TFile, TDirectory or TObject
   
    TString TSitem(item->GetText());

    // If its a root file 
    if(TSitem.EndsWith(".root")){
        if((Bool_t)item->GetUserData()){
            OpenClose(item);
            return;
        }
                
        ////Only reached here if unopend TFile
        gROOT->cd();
        TFile* Rfile=new TFile(DirName(item),"READ");
        gROOT->cd();
        if(!Rfile->IsOpen())return;
        
        Rfile->SetBit(kCanDelete,kFALSE);
        
        RootFileList.Add(Rfile);
        AddTDir(item,Rfile);
        
        return;
    }
    
//  cout<<endl<<"Object "<<GetObject(item);
    TKey *key=GetKey(item);
    
    if(key){
        
        bool IsSkipFolder=false;
		TClass* tCl=gROOT->GetClass(key->GetClassName());
        if(tCl!=nullptr){
            if(tCl->InheritsFrom(TTree::Class())){IsSkipFolder=true;}
            if(tCl->InheritsFrom(THnBase::Class())){IsSkipFolder=true;}
        }
        
		if(key->IsFolder()&&!IsSkipFolder) { // !IsSkipFolder is because TTrees and THn present as folders, but we dont want to interact with that way
            if((Bool_t)item->GetUserData()){
                OpenClose(item);
                return;
            }
            
            AddTDir(item,(TDirectory*)key->ReadObj());
            return;
        }else{
            
            if(!((Bool_t)item->GetUserData())){
                //If item has never been used, its never been read from disk, so do that
                item->SetUserData((void*)key->ReadObj());
            }
            //GetRootFile(item)->ls();
            //GetRootFile(item)->ls("-m");
            //gROOT->ls("-m");
            //GetRootFile(item)->ls("-d");
            NewObject((TObject*)item->GetUserData()); // Method for broadcasting an "item" has been selected
        }
    }   
}
    
void jDirList::AddTDir(TGListTreeItem* item, TDirectory* dir){
//  Add all the content of a rootfile TDirectory to the *fContents* list as *items*
//     TDirectory *dirsav = gDirectory;
    TIter next(dir->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next())) {
        
        bool IsSkipFolder=false;
		TClass* tCl=gROOT->GetClass(key->GetClassName());
        if(tCl!=nullptr){
            if(tCl->InheritsFrom(TTree::Class())){IsSkipFolder=true;}
            if(tCl->InheritsFrom(THnBase::Class())){IsSkipFolder=true;}
        }
        
		if (key->IsFolder()&&!IsSkipFolder) { // !IsSkipFolder is because TTrees and THn present as folders, but we dont want to interact with that way
            fContents->AddItem(item,key->GetName());
			continue;
		}
		
		////////////////////////////////////////////////////////////////////////////////////////////
		// This section determines which TObjects will be allowed to be viewed and hence accessed //
		////////////////////////////////////////////////////////////////////////////////////////////
        
        if(tCl!=nullptr){//Added to handle root files containing root-inhereted objects from other libraries not presentntly loaded 
            
//             cout<<endl<<"NAME IS "<<key->GetClassName()<<endl;
//             cout<<"NAME IS "<<tCl->Class_Name()<<endl;
            
            switch(HistoClassDetect(tCl)) {
                case 1 : 
                    fContents->AddItem(item,key->GetName(),fIconH1,fIconH1); // TH1
                    continue;
                case 2 : // TH2
                    fContents->AddItem(item,key->GetName(),fIconH2,fIconH2); // TH2
                    continue;
                case 3 : // TH3
                    fContents->AddItem(item,key->GetName(),fIconH3,fIconH3); // TH3
                    continue;
                default :
                    break;
            }
            
            if(tCl->InheritsFrom(TTree::Class())){
                fContents->AddItem(item,key->GetName(),fIconTree,fIconTree); // TTree
            }else if(tCl->InheritsFrom(TCanvas::Class())){
                fContents->AddItem(item,key->GetName(),fIconCan,fIconCan);// TCanvas
            }else if(tCl->InheritsFrom(TGraph::Class())){
                fContents->AddItem(item,key->GetName(),fIconGr,fIconGr); // TGraph
            }else if(tCl==TMultiGraph::Class()){
                fContents->AddItem(item,key->GetName(),fIconMGr,fIconMGr); // TMultiGraph, does NOT Inherit from TGraph
            }else if(tCl->InheritsFrom(TF1::Class())){
                fContents->AddItem(item,key->GetName(),fIconTF,fIconTF); // TF1
            }else if(tCl->InheritsFrom(THnBase::Class())){
                fContents->AddItem(item,key->GetName(),fIconTHn,fIconTHn); // THnBase / THnSparse etc
            }
        }
    }
        
    // Use *UserData* to indicate that item was already browsed
    fContents->OpenItem(item);
    item->SetUserData((void*)1);
    return;
}
 

TFile* jDirList::GetRootFile(TGListTreeItem* item){
    TGListTreeItem* searchitem=item;
    while(searchitem->GetParent()){
        searchitem=searchitem->GetParent();
         TString TSitem(searchitem->GetText());
         if(TSitem.EndsWith(".root")){
             return (TFile*)RootFileList.FindObject(DirName(searchitem));
        }
    }
    return 0;
}


TKey* jDirList::GetKey(TGListTreeItem* item){
    TDirectory* Dir=GetDirectory(item);
    if(Dir){
        return Dir->GetKey(item->GetText());
    }
    
    return 0;
}


TDirectory* jDirList::GetDirectory(TGListTreeItem* item){
    TFile *Rfile=GetRootFile(item);
    if(Rfile){
        vector<TString> folderpath;

        TGListTreeItem* searchitem=item;
        while(searchitem->GetParent()){
            searchitem=searchitem->GetParent();
            TString TSitem(searchitem->GetText());
            if(TSitem.EndsWith(".root")){
                break;
            }
            folderpath.push_back(TSitem);
        }
        
        TDirectory* CurrentDir=(TDirectory*)Rfile;
        
        for(int i=folderpath.size()-1;i>=0;i--){
            TDirectory* next = (TDirectory*)CurrentDir->Get(folderpath[i]);
            if(next){
                CurrentDir=next;
            }else{
                return 0;
            }
        }
        
         // CurrentDir should now be item's parent
         return CurrentDir;
    }
    return 0;
}

TString jDirList::GetInternal(TGListTreeItem* item){
    TFile *Rfile=GetRootFile(item);
    if(Rfile){
            TString filepath=Rfile->GetName();
            TString itemname=DirName(item);
            TString insidepath( itemname(filepath.Length()+1,itemname.Length()) );
            return insidepath;
    }
    return TString();
}

TObject* jDirList::GetObject(TGListTreeItem* item){
    TFile *Rfile=GetRootFile(item);
    if(Rfile){
        return Rfile->Get(GetInternal(item));
    }
    return 0;
}

void jDirList::NewObject(TObject *obj)
 {
    Emit("NewObject(TObject*)", (Long_t)obj);
 }

 
 
bool jDirList::FindAndOpen(TString fname){
    // Lots of manual parsing based on linux, not made windows compatible :(
    
        if(fname.BeginsWith(".."))return false; //Our directories dont support upward refence.
        
        TGListTreeItem* TopItem=fContents->GetFirstItem(); // This is always system directory, as set in jDirList::jDirList()
        if(!fname.BeginsWith("/")){TopItem=TopItem->GetNextSibling();} // Always current directory
        else{
            UseItem(TopItem);//Load the system home directory, as it is not loaded by default
            fname=fname(1,fname.Length());
        }
        
        
    
        TString searchname;
        if(fname.First('/')>0){ //Need to go down a level 
            searchname=fname(0,fname.First('/'));
            fname=fname(fname.First('/')+1,fname.Length());
        }else{
            searchname=fname;fname="";
        }
        
        TGListTreeItem* item=TopItem->GetFirstChild();
        while(item){
            TString TSitem(item->GetText());
            if(TSitem==searchname){//Correct item name
                UseItem(item);//Load if not loaded
                if(fname.Length()<1){ //At final piece, success! 
                    return true;
                }else{ // Go down one more level
                    item=item->GetFirstChild();
                    
                    if(fname.First('/')>0){ //Need to go down a level 
                        searchname=fname(0,fname.First('/'));
                        fname=fname(fname.First('/')+1,fname.Length());
                    }else{
                        searchname=fname;fname="";
                    }
                }
            }else{
                item=item->GetNextSibling();
            }
        }
            
    fContents->CloseItem(fContents->GetFirstItem());//If we opend the top dir, but failed, close the top dir
    return false;  
}

