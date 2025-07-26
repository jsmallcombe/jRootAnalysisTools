#include "j_ultrapeak_env.h"

bool gGlobalForceMinuitOldMinimiser=false;

///////////////////////////////////////
// Initialiser functions  //
///////////////////////////////////////

int UltraFitEnv::UltraFitEnv_iterator = 0;
    
UltraFitEnv::UltraFitEnv(TH1* fHist,TCanvas* fCan):UltraFitEnv(new TGMainFrame(gClient->GetRoot(), 100, 100,kVerticalFrame),fHist,fCan,0){
    const TGWindow *P=GetParent();
    MainFrame = (TGMainFrame*)P;
    
    // To avoid double deletion when deleting from UltraFitEnv
    MainFrame->SetCleanup(kNoCleanup);
    SetCleanup(kDeepCleanup);
    MainFrame->Connect("CloseWindow()","TGMainFrame",MainFrame,"DontCallClose()");
    MainFrame->Connect("CloseWindow()","UltraFitEnv",this,"~UltraFitEnv()");
    
    MainFrame->AddFrame(this, new TGLayoutHints(kLHintsExpandX|kLHintsExpandY, 1, 1, 1, 1));
	MainFrame->Resize(MainFrame->GetDefaultSize());
	MainFrame->MapWindow();
	MainFrame->SetWindowName("UltraFitControls");
}

UltraFitEnv::UltraFitEnv(const TGWindow * p,TH1* fHist,TCanvas* fCan,int opt): TGCompositeFrame(p,100,100,kVerticalFrame),MainFrame(0),cFrame(0),cPan(0),cCan(0),gHist(0),gHistDrawn(0),gHistDrawnName(""),cShift(0),cCtrl(0),cAlt(0),cGoodFit(0),cSaveConf(0),cClearConf(0),cTrueCent(0),cNfit(1),cNfree(1)
{TVirtualPad* hold=gPad;
    if(opt==1){
        fCan=0;
        //opt1 no link canvas option
    }
    Stop.Start();
	BuildDialogBox(opt);
	ConnectNewCanvas(fCan);//does nothing if fCan=0
	SetNewHist(fHist);//does nothing if fHist=0
gPad=hold;};

UltraFitEnv::~UltraFitEnv(){
    Cleanup();
    Closed(this);
    TQObject::Disconnect(this);
    if(MainFrame){
        delete MainFrame;
    }
    
    cout<<"UltraFitEnv DELETED"<<endl;
   
	KillCan();
// 	if(gHist){delete gHist;gHist=0;} // No idea, old segfault
	gHist=0;
	ClearFits();
};

void UltraFitEnv::BuildDialogBox(int opt){
	//cout<<endl<<"ERROR IN FN C"<<flush;
    
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
    TGTextButton *button;
    TGLayoutHints* buffright= new TGLayoutHints(kLHintsRight,5,5,3,2);
    TGLayoutHints* buffleft= new TGLayoutHints(kLHintsLeft,5,5,3,2);
    TGLayoutHints* buff= new TGLayoutHints(kLHintsLeft,5,5,3,2);
    TGLayoutHints* ExpandX= new TGLayoutHints(kLHintsExpandX,5,5,3,2);
    TGLayoutHints* ExpandXz= new TGLayoutHints(kLHintsExpandX,0,0,0,0);
    TGLayoutHints* YY= new TGLayoutHints(kLHintsCenterY,8,8,3,3);
    TGLayoutHints* XX= new TGLayoutHints(kLHintsCenterX,3,3,3,1);
    TGLayoutHints* XB= new TGLayoutHints(kLHintsExpandX|kLHintsBottom,2,2,2,2);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

    TGHorizontalFrame* menuB = new TGHorizontalFrame(this, 0, 0, 0);
        button = new TGTextButton(menuB," Help ");
        button->Connect("Clicked()","UltraFitEnv",this,"Help()");
        menuB->AddFrame(button,new TGLayoutHints(kLHintsRight,0,0,0,0));
        button = new TGTextButton(menuB," SaveAs ");
        button->Connect("Clicked()","UltraFitEnv",this,"jSaveAs()");
        menuB->AddFrame(button,new TGLayoutHints(kLHintsLeft,0,0,0,0));
   AddFrame(menuB,ExpandXz);
    
    mainhold = new TGHorizontalFrame(this, 0, 0, 0); 
    cFrame = new TGVerticalFrame(mainhold);

    if(opt!=2){
        TGHorizontalFrame* capt = new TGHorizontalFrame(cFrame, 0, 0, 0);
            button = new TGTextButton(capt," Capture Hist ");
            button->Connect("Clicked()","UltraFitEnv",this,"SetCapture(int=1)");
            button->SetToolTipText("Copy histogram from another frame\n(subsequent click).");
            capt->AddFrame(button,ExpandXz);	
        
            if(opt!=1){
                button = new TGTextButton(capt," Link Canvas ");
                button->Connect("Clicked()","UltraFitEnv",this,"SetCapture(int=0)");
                button->Resize(150);
                button->SetToolTipText("Begin fitting in another canvas\n(subsequent click).");
                capt->AddFrame(button,ExpandXz);
            }
        cFrame->AddFrame(capt,ExpandX);
    }
    
    fCheckLabels = new TGCheckButton(cFrame,"Peak Labels ");
    fCheckLabels->SetState(kButtonDown);
    fCheckLabels->Connect("Clicked()","UltraFitEnv",this,"DrawSaveLabels()");
    fCheckLabels->SetToolTipText("Show peak labels on histogram.");
    cFrame->AddFrame(fCheckLabels,XX);
    
    button = new TGTextButton(cFrame,"Re-Draw Hist");
    button->Connect("Clicked()","UltraFitEnv",this,"ReDrawgHist()");
    button->SetToolTipText("Re-draw the currently selected histogram\nand any saved fits.");
    cFrame->AddFrame(button,ExpandX);
    
    button = new TGTextButton(cFrame,"Clear Exclusion");
    button->Connect("Clicked()","UltraFitEnv",this,"ClearExclusion()");
    button->SetToolTipText("Clear any user specified\n fit exclusion region.");
    cFrame->AddFrame(button,ExpandX);
    
    
    if(opt!=1){
        button = new TGTextButton(cFrame,"");
        button->Connect("Clicked()","UltraFitEnv",this,"PointMe()");
        cFrame->AddFrame(button,ExpandX);
    }
    
    button = new TGTextButton(cFrame,"Save Peak Info");
    button->Connect("Clicked()","UltraFitEnv",this,"SaveFit()");
    button->SetToolTipText("Save the most recently completed fit\nto the local list of fits\nand to the histogram.");
    cFrame->AddFrame(button,ExpandX);
        
    button = new TGTextButton(cFrame,"Clear Saved Peaks");
    button->Connect("Clicked()","UltraFitEnv",this,"ClearFitsD()");
    button->SetToolTipText("Delete all fits saved\nto the local list of fits\nand to the histogram.");
    cFrame->AddFrame(button,ExpandX);
    
    button = new TGTextButton(cFrame,"Print Peak Info");
    button->Connect("Clicked()","UltraFitEnv",this,"PrintFits()");
    button->SetToolTipText("Print the peak data for the\n list of saved fits\nto the terminal.");
    cFrame->AddFrame(button,ExpandX);
    
    button = new TGTextButton(cFrame,"Export Peak Info");
    button->Connect("Clicked()","UltraFitEnv",this,"ExportFits()");
    button->SetToolTipText("Save the peak data for the list of\n saved fits in plain text to the file\n peakinfo.dat (overwrites)");
    cFrame->AddFrame(button,ExpandX);
    
    if(opt!=2){
        button = new TGTextButton(cFrame,"Load Session");
        button->Connect("Clicked()","UltraFitEnv",this,"LoadSession()");
        button->SetToolTipText("Load a session saved with Export Peak Info");
        cFrame->AddFrame(button,ExpandX);
    }
    
    button = new TGTextButton(cFrame,"");//Just filler
    cFrame->AddFrame(button,ExpandX);	
    
    button = new TGTextButton(cFrame,"Fit Peaks");
    button->Connect("Clicked()","UltraFitEnv",this,"FitGUIPeak()");
    button->SetToolTipText("Fit the selected histogram using\nthe current inputs.");
    cFrame->AddFrame(button,ExpandX);
    
    TGHorizontalFrame* fHframe0 = new TGHorizontalFrame(cFrame, 0, 0, 0);
    
        TGVerticalFrame* ticks = new TGVerticalFrame(fHframe0, 0, 0, 0);
        
            TGLabel *label = new TGLabel(ticks, "Background Mode");
            ticks->AddFrame(label,XX);
            
            fCombo = new TGComboBox(ticks,100);
            fCombo->AddEntry("null",Ultrapeak::cBackTypeN);
            fCombo->AddEntry("pol0",Ultrapeak::cBackType0);
            fCombo->AddEntry("pol0+step",Ultrapeak::cBackType0s);
            fCombo->AddEntry("pol1 fixed",Ultrapeak::cBackType1f);
            fCombo->AddEntry("pol1",Ultrapeak::cBackType1);
            fCombo->AddEntry("pol1+step",Ultrapeak::cBackType1s);
            fCombo->AddEntry("pol2",Ultrapeak::cBackType2);
            fCombo->AddEntry("pol2+step",Ultrapeak::cBackType2s);
            fCombo->Resize(110, 20);
            fCombo->Select(Ultrapeak::cBackType1s);
            ticks->AddFrame(fCombo,XX);	

            
            fCheckLimit = new TGCheckButton(ticks,"Limit Tail  ");// A tick box with hover text belonging to a parent frame
            fCheckLimit->SetState(kButtonUp);
            fCheckLimit->SetToolTipText("Force strict maximum values on the\nexponential tail parameters.\n Recommended for fitting gamma rays.");
            fCheckLimit->Connect("Clicked()","UltraFitEnv",this,"HideSubShapes()");
            
            fCheckNoTail = new TGCheckButton(ticks,"No Tail    ");// A tick box with hover text belonging to a parent frame
            fCheckNoTail->SetState(kButtonUp);
            fCheckNoTail->SetToolTipText("Turn off decay tail complelty");
            fCheckNoTail->Connect("Clicked()","UltraFitEnv",this,"HideSubShapes()");
            
            fCheckTwin = new TGCheckButton(ticks,"Twin Gaus");// A tick box with hover text belonging to a parent frame
            fCheckTwin->SetState(kButtonUp);
            fCheckTwin->SetToolTipText("Use the peak fit mode which adds a\n second Gaussians compontent with \n larger sigma.");
            fCheckTwin->Connect("Clicked()","UltraFitEnv",this,"HideSubShapes()");

        ticks->AddFrame(fCheckLimit,XX);
        ticks->AddFrame(fCheckNoTail,XX);
        ticks->AddFrame(fCheckTwin,XX);
    fHframe0->AddFrame(ticks,ExpandXz);
        
        TGVerticalFrame* fHframepm = new TGVerticalFrame(fHframe0, 0, 0, 0);
        
            button = new TGTextButton(fHframepm," + ");
            button->Connect("Clicked()","UltraFitEnv",this,"AddTextBox()");
            button->SetToolTipText("Increase the number of peaks to fit.");
            fHframepm->AddFrame(button,ExpandXz);
            button = new TGTextButton(fHframepm," - ");
            button->SetToolTipText("Decrease the number of peaks to fit.");
            button->Connect("Clicked()","UltraFitEnv",this,"RemoveTextBox()");
            fHframepm->AddFrame(button,ExpandXz);
        
        fHframe0->AddFrame(fHframepm,YY);
        
    cFrame->AddFrame(fHframe0,ExpandXz);		
// 		
    TGHorizontalFrame* fHframeN = new TGHorizontalFrame(cFrame, 0, 0, 0);

    
        fZERO = new TGTextEntry(fHframeN,new TGTextBuffer(5));
            fZERO->Connect("TextChanged(char*)", "UltraFitEnv", this,"TextToSep()");//Continually does things while typing is occurring, so only link to simple fn
            fZERO->SetDefaultSize(60,25);
            fZERO->SetToolTipText("Peak Zero\n Centroid x.size())");
        fHframeN->AddFrame(fZERO,buffleft);
    // 				
        cZc = new TGTextEntry(fHframeN,new TGTextBuffer(5));
            cZc->SetDefaultSize(50,25);
            cZc->SetEnabled(0);
            cPTbox.push_back(cZc);			
            cZc->SetToolTipText("Centroid\n Peak 0 absolute centroid\n Selected/Result.");
        fHframeN->AddFrame(cZc,buffright);
        
        cNpd=new TGTextEntry(fHframeN,new TGTextBuffer(5));
            cNpd->SetText("1");
            cNpd->SetDefaultSize(25,25);
            cNpd->Connect("TextChanged(char*)","UltraFitEnv",this,"SetN()");
            cNpd->SetEnabled(0);
            cNpd->SetToolTipText("Current number of peaks to fit.");
        fHframeN->AddFrame(cNpd,buffright);

// 		
    cFrame->AddFrame(fHframeN,new TGLayoutHints(kLHintsExpandX));
    
    cShapePane= new TGVerticalFrame(cFrame);
        TGHorizontalFrame* shapeelement = new TGHorizontalFrame(cShapePane, 0, 0, 0);
            cShapeTsig = new TGTextEntry(shapeelement,new TGTextBuffer(5));
            cShapeTsig->SetDefaultSize(60,25);	
            cShapeTsig->SetToolTipText("Sigma\n Fix or constrain peak sigma.");
            shapeelement->AddFrame(cShapeTsig,buff);
            label = new TGLabel(shapeelement, "Sigma");
            shapeelement->AddFrame(label,buff);
        cShapePane->AddFrame(shapeelement,ExpandXz);
        
        cTailParPane= new TGVerticalFrame(cShapePane);
            shapeelement = new TGHorizontalFrame(cTailParPane, 0, 0, 0);
                cShapeTdecay = new TGTextEntry(shapeelement,new TGTextBuffer(5));
                cShapeTdecay->SetDefaultSize(60,25);	
                cShapeTdecay->SetToolTipText("Decay Tail\n Fix or constrain peak decay tail.");
                shapeelement->AddFrame(cShapeTdecay,buff);
                label = new TGLabel(shapeelement, "Decay  ");
                decaysigmablabel=label;
                shapeelement->AddFrame(label,buff);
            cTailParPane->AddFrame(shapeelement,ExpandXz);
            
            shapeelement = new TGHorizontalFrame(cTailParPane, 0, 0, 0);
                cShapeTshare = new TGTextEntry(shapeelement,new TGTextBuffer(5));
                cShapeTshare->SetDefaultSize(60,25);	
                cShapeTshare->SetToolTipText("Sharing Parameter\n Fix or constrain peak sharing parameter.");
                shapeelement->AddFrame(cShapeTshare,buff);
                label = new TGLabel(shapeelement, "Sharing");
                shapeelement->AddFrame(label,buff);
            cTailParPane->AddFrame(shapeelement,ExpandXz);
        cShapePane->AddFrame(cTailParPane,ExpandXz);
        
        cTwinParPane= new TGVerticalFrame(cShapePane);
            shapeelement = new TGHorizontalFrame(cTwinParPane, 0, 0, 0);
                cShapeTtwinwidth = new TGTextEntry(shapeelement,new TGTextBuffer(5));
                cShapeTtwinwidth->SetDefaultSize(60,25);	
                cShapeTtwinwidth->SetToolTipText("Twin Gaussian Width Parameter\n Fix or constrain twin peak ratio.");
                shapeelement->AddFrame(cShapeTtwinwidth,buff);
                label = new TGLabel(shapeelement, "Twin Sigma");
                shapeelement->AddFrame(label,buff);
            cTwinParPane->AddFrame(shapeelement,ExpandXz);
        
            shapeelement = new TGHorizontalFrame(cTwinParPane, 0, 0, 0);
                cShapeTtwinshare = new TGTextEntry(shapeelement,new TGTextBuffer(5));
                cShapeTtwinshare->SetDefaultSize(60,25);	
                cShapeTtwinshare->SetToolTipText("Twin Gaussian Height Parameter\n Fix or constrain twin peak ratio.");
                shapeelement->AddFrame(cShapeTtwinshare,buff);
                label = new TGLabel(shapeelement, "Twin Height");
                shapeelement->AddFrame(label,buff);
            cTwinParPane->AddFrame(shapeelement,ExpandXz);
        cShapePane->AddFrame(cTwinParPane,ExpandXz);
        
         shapeelement = new TGHorizontalFrame(cShapePane, 0, 0, 0);
            cTrueCentButton = new TGTextButton(shapeelement," YMax ");
            cTrueCentButton->Connect("Clicked()","UltraFitEnv",this,"ChangeCentMode()");
            cTrueCentButton->SetToolTipText("Centroid parameter input control.");
            shapeelement->AddFrame(cTrueCentButton,buff);
            label = new TGLabel(shapeelement, "Centroid");
            shapeelement->AddFrame(label,buff);
        cShapePane->AddFrame(shapeelement,ExpandXz);       
        
    
    cFrame->AddFrame(cShapePane,XB);
    
    button = new TGTextButton(cFrame,"^");
    button->Connect("Clicked()","UltraFitEnv",this,"HideShape()");
    button->SetToolTipText("Show Peak Shape Controls.");
    cFrame->AddFrame(button,XB);
    
    
    mainhold->AddFrame(cFrame,new TGLayoutHints(kLHintsExpandY,0,0,0,0));
    
    stringstream ss;
    ss <<"UltraFitCanvas"<<UltraFitEnv_iterator;
    UltraFitEnv_iterator++;
    can_name=ss.str();
    cPan = new TRootEmbeddedCanvas(can_name.c_str(), mainhold, 800,600);
    mainhold->AddFrame(cPan,new TGLayoutHints(kLHintsExpandY|kLHintsExpandX,3,3,3,3));

   AddFrame(mainhold,new TGLayoutHints(kLHintsExpandY|kLHintsExpandX,0,0,0,0));
    
   SetWindowName("UltraFitControls");
    
    MapSubwindows();
    MapWindow();
    
    HideCanvas();
    HideShape();
    cPan->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "UltraFitEnv", this,"ClickedCanvas(Int_t,Int_t,Int_t,TObject*)");
    ReMargin(cPan->GetCanvas());
}


void UltraFitEnv::ClearFits(){
	//cout<<endl<<"ERROR IN FN A"<<flush;
	for(int i=0;(unsigned)i<cFitList.size();i++)delete cFitList[i];
	cFitList.clear();
	cSaveLabels.clear();
	if(gHist){
		gHist->GetListOfFunctions()->Clear();
	}
};

void UltraFitEnv::ClearFitsD(){
	//cout<<endl<<"ERROR IN FN B"<<flush;
	if(!cClearConf&&cFitList.size()>0){
		cout<<endl<<"Are you sure you want to clear all saved fits?";
		cout<<endl<<"Click again to confirm."<<endl;
		cClearConf=true;
		return;
	}
	cout<<endl<<"Fit data for "<<cFitList.size()<<" fits cleared."<<endl;
	ClearFits();
	DrawgHist();
	cSaveConf=false;
};


void UltraFitEnv::HideSubShapes(){
    
    if(!fCheckTwin->GetState()){
        cShapeTtwinwidth->SetText("");
        cShapeTtwinshare->SetText("");
        cShapePane->HideFrame(cTwinParPane);
    }else{
        cShapePane->ShowFrame(cTwinParPane);
    }
    
    if(fCheckLimit->GetState()||fCheckNoTail->GetState()){
        cShapeTdecay->SetText("");
        cShapeTshare->SetText("");
        cShapePane->HideFrame(cTailParPane);
    }else{
        cShapePane->ShowFrame(cTailParPane);
    }
    
	ReDrawFrames();
}

void UltraFitEnv::HideShape(){
	cShapeTsig->SetText("");
	cShapeTdecay->SetText("");
	cShapeTshare->SetText("");
	cShapeTtwinwidth->SetText("");
	cShapeTtwinshare->SetText("");
	if(cFrame->IsVisible(cShapePane)){
        cFrame->HideFrame(cShapePane);
        ReDrawFrames();
    }else{
        cFrame->ShowFrame(cShapePane);
        HideSubShapes(); //This Fn Calls ReDrawFrames()
    }
}

///////////////////////////////////////
/// Canvas and histogram management  //
///////////////////////////////////////

// Checks if the Canvas we were using still exists
TObject* UltraFitEnv::FindCan(){
	//cout<<endl<<"ERROR IN FN D"<<flush;

	return gROOT->GetListOfCanvases()->FindObject(cCan);
}

// Check if we are still using an existing canvas
// Else make a new one
TCanvas* UltraFitEnv::GetCan(){
	//cout<<endl<<"ERROR IN FN E"<<flush;
	cCan=(TCanvas*)FindCan();//
	
	if(!cCan){
		// Switch back to class owned if it exists
		
		ShowCanvas();
		if(cPan)cCan=cPan->GetCanvas();//This should always be true in new version
// 		cCan=(TCanvas*)gROOT->GetListOfCanvases()->FindObject(can_name.c_str());
		if(cCan)return cCan;
		
		
		// Create it if it doesnt exist // This shouldnt be reached in current version
		cCan=new TCanvas(can_name.c_str(),can_name.c_str(),800,600);
		cCan->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "UltraFitEnv", this,"ClickedCanvas(Int_t,Int_t,Int_t,TObject*)");
		//Make it invincible, for reasons
// 		TRootCanvas* c=(TRootCanvas*)cCan->GetCanvasImp();
// 		c->Connect("CloseWindow()","TRootCanvas",c,"DontCallClose()");
	}
	return cCan;
}

void UltraFitEnv::KillCan(){
	if(FindCan()){
		cCan->Disconnect(0,this,0);
// 		if(!(strcmp(cCan->GetName(),can_name.c_str()))){			
// 			TQObject::Disconnect((TCanvas*)cCan);
// 			gROOT->GetListOfCanvases()->Remove(cCan);
// 			delete cCan;
// 		}
	}
	cCan=0;
}

// Setting to an external canvas not controlled by UltraFitEnv
void UltraFitEnv::ConnectNewCanvas(TVirtualPad* fPad){if(!fPad)return;
	//cout<<endl<<"ERROR IN FN F"<<flush;
	if(!gROOT->GetListOfCanvases()->FindObject(fPad))return;
	if(!(strcmp(fPad->GetName(),can_name.c_str())))return;
	//Its got to exist and be unrelated

	HideCanvas();
	KillCan();

// 	//Connect the new pad and grab the histogram if it has one
	cCan=fPad->GetCanvas();
	SetNewHist(hist_capture(fPad),false);
	cCan->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "UltraFitEnv", this,"ClickedCanvas(Int_t,Int_t,Int_t,TObject*)");
};

void UltraFitEnv::ExternalHistUpdateCheck(){
	//cout<<endl<<"ERROR IN FN G"<<flush;
	if(GetCan()!=cPan->GetCanvas()){//if using external canvas
		TH1* fHist=hist_capture(GetCan());
		if(fHist){//if it has a histogram
			if(gHist&&gHistDrawn){//If there is a current histogram
				if(!(strcmp(fHist->GetName(),gHistDrawnName.c_str()))){//Is it just a the one we drew
					//used to compare pointer not name, but then DrawCopy was using the same memory so pointer didnt change!
					return;
				}
			}
			SetNewHist(fHist,false);
		}
	}
}

void UltraFitEnv::SetNewHist(TH1* fHist,bool format){if(!fHist)return;
	//cout<<endl<<"ERROR IN FN H"<<flush;
    ClearFits();
	stringstream ss;
	ss <<"gHist"<<UltraFitEnv_iterator;
	UltraFitEnv_iterator++;
	if(gHist!=0)delete gHist;
	gHist=(TH1*)fHist->Clone(ss.str().c_str());
	if(format)hformat(gHist,0);
	gHist->GetXaxis()->SetRange(1,-1);
	DrawgHist();
	cRClicker.clear();
	cClicker.clear();
	cExClicker.clear();
	cSaveLabels.clear();
	fFitFinished=false;
}

void UltraFitEnv::ReDrawgHist(){
	cRClicker.clear();
	cClicker.clear();
	cExClicker.clear();
	DrawgHist();
}

void UltraFitEnv::DrawgHist(){
	TVirtualPad* hold=gPad;
	
	//cout<<endl<<"ERROR IN FN I"<<flush;
	if(!gHist)return;
	TCanvas* fCan=GetCan();
	if(fCan){
		fCan->cd();
		
		//This is another protection of gHist
		gHistDrawn=DrawHistOpt(gHist,true,true);
		gHistDrawnName=gHistDrawn->GetName();
		
		//Add the labels on the top
		DrawSaveLabels();

		if(!fCan->GetShowEventStatus())fCan->ToggleEventStatus();//info at the bottom
		gPad->Update();	
	}
	
	gPad=hold;
}

void UltraFitEnv::DrawSaveLabels(){
	TVirtualPad* hold=gPad;
	
	TCanvas* fCan=GetCan();
	if(fCan){
		fCan->cd();
		
		obj_removeall(TText::Class(),GetCan());
		if(fCheckLabels->GetState()){
			for(unsigned int i=0;i<cSaveLabels.size();i++){
				cSaveLabels[i].Draw();
			}
		}
		gPad->Modified();
		gPad->Update();
	
	}
	gPad=hold;
}

void UltraFitEnv::SetCapture(int mode){
	//cout<<endl<<"ERROR IN FN J"<<flush;
	TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "CaptureHistogram(TPad*,TObject*,Int_t)");
	TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "CaptureCanvas(TPad*,TObject*,Int_t)");
	if(mode)TQObject::Connect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", "UltraFitEnv", this, "CaptureHistogram(TPad*,TObject*,Int_t)");
	else TQObject::Connect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", "UltraFitEnv", this, "CaptureCanvas(TPad*,TObject*,Int_t)");
};

void UltraFitEnv::CaptureHistogram(TPad* pad,TObject* obj,Int_t event){
	//cout<<endl<<"ERROR IN FN K"<<flush;
	if(1 == event){
		
		TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "CaptureHistogram(TPad*,TObject*,Int_t)");
		
		if(obj){
			TH1* fH=0;
			if(obj->InheritsFrom("TH1"))fH=(TH1*)obj;
			else fH=hist_capture(pad);
			
			if(fH){
				// If we're using an external canvas, stop doing that
// 				if(strcmp(GetCan()->GetName(),can_name.c_str())){
				if(GetCan()!=cPan->GetCanvas()){
					cCan->Disconnect(0,this,0);
					cCan=0;
				}
				
				ShowCanvas();
				cPan->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "UltraFitEnv", this,"ClickedCanvas(Int_t,Int_t,Int_t,TObject*)");
				SetNewHist(fH);return;
			}
		}
		HideCanvas();
		cout<<endl<<endl<<"Capture Failed"<<endl;
	}
}

//For external setting of a new hist rather than GUI
void UltraFitEnv::PassNewHist(TH1* fH){if(!(cPan&&fH))return;
	// If we're using an external canvas, stop doing that
	if(GetCan()!=cPan->GetCanvas()){
		cCan->Disconnect(0,this,0);
		cCan=0;
	}
	
	ShowCanvas();
	cPan->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "UltraFitEnv", this,"ClickedCanvas(Int_t,Int_t,Int_t,TObject*)");
	SetNewHist(fH);
}


void UltraFitEnv::CaptureCanvas(TPad* pad,TObject* obj,Int_t event){
	//cout<<endl<<"ERROR IN FN L"<<flush;
	if(1 == event && pad){
		TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "CaptureCanvas(TPad*,TObject*,Int_t)");
		ConnectNewCanvas(pad);
	}

}

void UltraFitEnv::HideCanvas(){
	mainhold->HideFrame(cPan);
	ReDrawFrames();
}
void UltraFitEnv::ShowCanvas(){
    if(!mainhold->IsVisible(cPan)){
        mainhold->ShowFrame(cPan);
        cPan->Resize(1000,700);
        ReDrawFrames();
    }
}
void UltraFitEnv::ReDrawFrames(){
	cFrame->Resize(cFrame->GetDefaultSize());
	Resize(GetDefaultSize());
// 	gClient->NeedRedraw(this);
    
    //TGFrame *P=(TGFrame *)GetParent();//Dodgy 
    TGFrame *P=(TGFrame *)GetMainFrame();//Double dodgy 
    P->Resize(P->GetDefaultSize());
	gClient->NeedRedraw(P);
}


///////////////////////////////////////
/// Text Box Management  //
///////////////////////////////////////
	
void  UltraFitEnv::TextToSep(){
	//cout<<endl<<"ERROR IN FN N"<<flush;
	this->SetN();
	UpdateLines();
}
	
void  UltraFitEnv::SetN(){
	//cout<<endl<<"ERROR IN FN P"<<flush;
	stringstream ss;
	ss<<cNfit;
	cNpd->SetText(ss.str().c_str());
	gClient->NeedRedraw(cNpd);
	
	if(cNfit>6)cout<<endl<<endl<<"BAD IDEA"<<endl<<endl;
	
	cNfree=cNfit;
	for(int i=0;(unsigned)i<cNfit-1;i++)if(string(cTbox[i]->GetBuffer()->GetString()).size()>0)cNfree--;
}

void  UltraFitEnv::SetSep(unsigned int fN,double fS,double fSe){
	//cout<<endl<<"ERROR IN FN Q"<<flush;
	while(cNfit<fN)this->AddTextBox();
	if(fN<2)return;
	stringstream ss;
	ss<<fS;
	if(fSe>0)ss<<"+"<<fSe;
	cTbox[fN-2]->SetText(ss.str().c_str());
}
	
void  UltraFitEnv::AddTextBox(){
	//cout<<endl<<"ERROR IN FN R"<<flush;
	
	TGHorizontalFrame* fHframe0;
	
	if(cTframe.size()<cNfit){
		fHframe0  = new TGHorizontalFrame(cFrame, 0, 0, 0);   //create a frame, filled with objects horizontally

			TGTextEntry* fTeh1 = new TGTextEntry(fHframe0,new TGTextBuffer(5));
			fTeh1->Connect("TextChanged(char*)", "UltraFitEnv", this,"TextToSep()");//Continually does things while typing is occurring, so only link to simple fn
			fTeh1->SetDefaultSize(60,25);
			fTeh1->SetToolTipText(("Separation\n Peak "+std::to_string(cPTbox.size()-1)+"<->"+std::to_string(cPTbox.size())+" fixed separation.\n blank = unconstrained").c_str());
			cTbox.push_back(fTeh1);
			
		fHframe0->AddFrame(fTeh1);
		
			TGTextEntry* fTeh2 = new TGTextEntry(fHframe0,new TGTextBuffer(5));
			fTeh2->SetDefaultSize(60,25);
			fTeh2->SetToolTipText(("Ratio\n Peak "+std::to_string(cPTbox.size()-1)+"<->"+std::to_string(cPTbox.size())+" fixed area ratio.\n blank = no relation").c_str());
			cRTbox.push_back(fTeh2);		
		fHframe0->AddFrame(fTeh2);		

			TGTextEntry* fTeh3 = new TGTextEntry(fHframe0,new TGTextBuffer(5));
			fTeh3->SetDefaultSize(45,25);
			fTeh3->SetEnabled(0);
			fTeh3->SetToolTipText(("Centroid\n Peak "+std::to_string(cPTbox.size())+" absolute centroid\n Selected/Result.").c_str());
			cPTbox.push_back(fTeh3);
			
		fHframe0->AddFrame(fTeh3,new TGLayoutHints(kLHintsExpandX));
		
		cTframe.push_back(fHframe0);
		cFrame->AddFrame(fHframe0,new TGLayoutHints(kLHintsExpandX,5,5,3,2));
		if(!cFrame->IsVisible(cShapePane)){cFrame->MapSubwindows();HideShape();}
		else{cFrame->MapSubwindows(); HideSubShapes();}
		// MapSubwindows required when adding new frames for first time but causes all hidden frames to become visible
	}else{
		fHframe0=cTframe[cNfit-1];
		cFrame->ShowFrame(fHframe0);
	}

	ReDrawFrames();
	
	cNfit++;
	this->SetN();
}
	
void  UltraFitEnv::RemoveTextBox(){
	//cout<<endl<<"ERROR IN FN S"<<flush;
	if(cNfit>1){
		cFrame->HideFrame(cTframe[cNfit-2]);
		cFrame->Resize();
		
		ReDrawFrames();

		cNfit--;
		this->SetN();
	}
	
}

///////////////////////////////////////
/// Canvas clicking handling  //
///////////////////////////////////////


vector< double > UltraFitEnv::GetClicks(int fN){
	//cout<<endl<<"ERROR IN FN T"<<flush;
	if(cClicker.size()==0)cClicker.push_back(0.0);
	while(cClicker.size()<(unsigned)fN)cClicker.push_back(cClicker[cClicker.size()-1]);
	
	vector< double > fReturn;
	for(int i=1;i<=fN;i++)fReturn.push_back(cClicker[cClicker.size()-i]);
	std::sort (fReturn.begin(), fReturn.end());
	return fReturn;
}

void UltraFitEnv::ClickedCanvas(Int_t event, Int_t px, Int_t py, TObject *selected_ob){// cout<<event<<endl;
	//cout<<endl<<"ERROR IN FN U"<<flush;
	
	cSaveConf=0;
	cClearConf=0;
	
	TCanvas* fCan=GetCan();
	if(!fCan)return;
	
	double Y=fCan->AbsPixeltoY(py);
	double X=fCan->AbsPixeltoX(px);	
	double y1=fCan->GetUymin(),y2=fCan->GetUymax();
	double x1=fCan->GetUxmin(),x2=fCan->GetUxmax();

	//To find the number binding of key presses
// 	if(kKeyPress == event)cout<<endl<<px<<" "<<py<<endl;
	
	//Number keys set the number of peaks
	unsigned int N=py-kKey_0;
	if(kKeyPress == event && N>0 &&  N<10){
		while(cNfit<N)AddTextBox();
		while(cNfit>N)RemoveTextBox();
		return;
	}

// #ifdef __linux__
#ifdef __APPLE__

	//pressing shift turns on background specification
	if(kKeyPress == event && (py==kKey_f||py==kKey_F) ){cShift=!cShift;return;}
	
	//pressing ctrl turns on off maxima peak specification
	if(kKeyPress == event && (py==kKey_p||py==kKey_P) ){cCtrl=!cCtrl;return;}
	
	//pressing alt turns on off exclusion range specification
	if(kKeyPress == event && (py==kKey_e||py==kKey_E) ){cAlt=!cAlt;return;}

#endif
// #else
	
	//  . s S Del
	if(kKeyPress == event && (py==kKey_Period||py==kKey_s||py==kKey_S||py==kKey_Delete) ){SaveFit();return;}

	//Enter key to fit
	if(kKeyPress == event && (py==4100 ||  py==kKey_Enter)){
		FitGUIPeak();
		return;
	}

	//pressing shift turns on background specification
	if(kKeyPress == event &&py==kKey_Shift ){cShift=!cShift;return;}
	
	//pressing ctrl turns on off maxima peak specification
	if(kKeyPress == event &&py==kKey_Control ){cCtrl=!cCtrl;return;}
	
	//pressing alt turns on off exclusion range specification
	if(kKeyPress == event &&py==kKey_Alt ){cAlt=!cAlt;return;}

	
	//+- key adds remove a peak
	if(kKeyPress == event &&py==kKey_Plus ){AddTextBox();return;}
	if(kKeyPress == event &&py==kKey_Minus ){RemoveTextBox();return;}
	
	//  C c  key clears exclusion regions
	if(kKeyPress == event && (py==kKey_c||py==kKey_C) ){ClearExclusion();return;}
	
	if(Y>y2||Y<y1||X<x1||X>x2){
		fCan->SetCrosshair(0);
	}else{
		if (event==kMouseEnter){
            
            // Convoluted solution to crosshairs in saved images
            if(Stop.RealTime()>1){
					fCan->SetCrosshair(1);
            }else{
					Stop.Start(kFALSE);	
            }
			
			return;
		}
		
		if ( (event == kButton1Up && cShift) || event == kButton2Up ) {
			cRClicker.push_back(X);
			this->UpdateLines();
			cShift=0;
		}else if(event == kButton1Up && cAlt){
			if(cExClicker.size()%2)cAlt=0;
			cExClicker.push_back(X);
			this->UpdateLines();
		}else if(event == kButton1Up && cCtrl){
			if(fFitFinished){fFitFinished=false;cRClicker.clear();}
			cClicker.push_back(X);
			this->UpdateLines();
		}else if(event == kButton1Up){if(gHist){
			if(fFitFinished){fFitFinished=false;cRClicker.clear();}
			ExternalHistUpdateCheck();
			FindLocalMax(gHist,X);
			cClicker.push_back(X);
			this->UpdateLines();		
		}}
	}
	return;
}

void UltraFitEnv::RemoveLines(){
	//cout<<endl<<"ERROR IN FN V"<<flush;
	if(!fCheckLabels->GetState())obj_removeall(TText::Class(),GetCan());
	obj_removeall(TLine::Class(),GetCan());
	obj_removeall(TBox::Class(),GetCan());
	
// 	TCanvas* fCan=GetCan();		
// 	if(fCan){
// 		//remove old lines
// 		TObject *obj;TIter next(fCan->GetListOfPrimitives());
// 		while ((obj = next())){
// 		if(obj->InheritsFrom("TText")||obj->InheritsFrom("TLine")||obj->InheritsFrom("TBox"))
// 			fCan->GetListOfPrimitives()->Remove(obj);
// 		}
// 	}
}

void UltraFitEnv::UpdateLines(){
	TVirtualPad* hold=gPad;
	//cout<<endl<<"ERROR IN FN W"<<flush;
	TCanvas* fCan=GetCan();	
	if(!fCan)return;
	
	fCan->cd();
	
	RemoveLines();

	double y1=fCan->GetUymin(),y2=fCan->GetUymax();
	double x1=fCan->GetUxmin(),x2=fCan->GetUxmax();	
	if(fCan->GetLogy()){y1=pow(10,y1);y2=pow(10,y2);}
	
	vector< double >fPass=MakeBoundryPeakListAbs();
	
	TLine fLine;
	for(unsigned int i=0;i<fPass.size();i++){
		if(i==0||i==fPass.size()-1)fLine.SetLineColor(3);
		else fLine.SetLineColor(2);
		double X=fPass[i];
		if(X<x2&&X>x1)
		fLine.DrawLine(X,y1,X,y2);
	}
	
	TBox fBox;
	fBox.SetLineColor(7);
	fBox.SetFillColor(7);
	fBox.SetFillStyle(3005);
	TBox fBoxL;
	fBoxL.SetFillStyle(0);
	fBoxL.SetLineColor(7);
	fLine.SetLineColor(7);
	
	for(unsigned int i=0;(i*2)+1<cExClicker.size();i++){
		double X1=cExClicker[i*2];
		double X2=cExClicker[i*2+1];
		if((X2>x2&&X1>x2)||(X2<x1&&X1<x1))continue;
		if(X2>x2)X2=x2;
		if(X1>x2)X1=x2;
		if(X2<x1)X2=x1;
		if(X1<x1)X1=x1;
		fBox.DrawBox(X1,y1,X2,y2);
		fBoxL.DrawBox(X1,y1,X2,y2);
	}
	
	if(cExClicker.size()%2){
		double X=cExClicker[cExClicker.size()-1];
		if(X<x2&&X>x1)
		fLine.DrawLine(X,y1,X,y2);
	}
	
	fCan->Modified();
	fCan->Update();
	gPad->Update();
	gPad=hold;
}

///////////////////////////////////////
/// Fitting Functions  //
///////////////////////////////////////

vector< jPeakDat > UltraFitEnv::MakePeakList(){
	//cout<<endl<<"ERROR IN FN X"<<flush;
	
	vector< jPeakDat > fPass;	
	vector< double > fC;
	int sClick=1;
     
    //Check if zero is manually set
	string Zstr=fZERO->GetBuffer()->GetString();
	if(Zstr.size()>0){
        double Zval,Zerr=-1;
		ExtractError(Zstr,Zval,Zerr);
        fPass.push_back(jPeakDat(Zval,1,Zerr,-1,-1));// first peak
        
        fC= GetClicks(cNfree-1);//Get the absolute peak positions of any NOT fixed peaks
        sClick=0;
        
	}else{
        fC= GetClicks(cNfree);//Get the absolute peak positions of any NOT fixed peaks
        fPass.push_back(jPeakDat(fC[0],0,-1,-1,-1));// first peak
    }
       

    double prevpos=fPass[0].Centroid;
	cZc->SetText(TString::Format("%.1f",prevpos));
	gClient->NeedRedraw(cZc);	

	for(unsigned int i=0;i<cNfit-1;i++){
		
		double Pval,Perr=-1,Rval=-1,Rerr=-1;
		bool Pconstr=false;
		
		string str=cTbox[i]->GetBuffer()->GetString();
		if(str.size()>0){
			Pconstr=true;
			ExtractError(str,Pval,Perr);	
		}
		
		str=cRTbox[i]->GetBuffer()->GetString();
		if(str.size()>0){
			ExtractError(str,Rval,Rerr);	
		}
		
		if(!Pconstr){
			Pval=fC[sClick]-prevpos;
			sClick++;
		}
		
		fPass.push_back(jPeakDat(Pval,Pconstr,Perr,Rval,Rerr));
		prevpos+=Pval;
		
		//update the text on the Control Bar
		cPTbox[i+1]->SetText(TString::Format("%.1f",prevpos));
		gClient->NeedRedraw(cPTbox[i+1]);		
	}
	
	return fPass;
}

vector< double > UltraFitEnv::MakeBoundryPeakListAbs(){
	
	double bound_l,bound_u;
	vector< jPeakDat >fPass=MakeBoundryPeakList(bound_l,bound_u);
	vector< double > ret;
	double prevpos=0;

	ret.push_back(bound_l);
	for(unsigned int i=0;i<fPass.size();i++){
		prevpos+=fPass[i].Centroid;
		ret.push_back(prevpos);
	}
	ret.push_back(bound_u);
	
	return ret;		
}

vector< jPeakDat > UltraFitEnv::MakeBoundryPeakList(double& bound_l,double& bound_u){
	//cout<<endl<<"ERROR IN FN Y"<<flush;
	vector< jPeakDat > fPeaks=MakePeakList();

	double prevpos=fPeaks[0].Centroid;
	double peaklow=prevpos,peakhigh=prevpos;
	
	for(unsigned int i=1;i<fPeaks.size();i++){
		prevpos+=fPeaks[i].Centroid;
		if(prevpos<peaklow)peaklow=prevpos;
		if(prevpos>peakhigh)peakhigh=prevpos;
	}
	
	bound_l=peaklow-20;
	bound_u=peakhigh+20;

	if(cRClicker.size()>1){
		bound_l=cRClicker[cRClicker.size()-1];bound_u=cRClicker[cRClicker.size()-2];
		if(bound_l>bound_u){double t=bound_l;bound_l=bound_u;bound_u=t;}
	}else{
		if(gHist){
			int a=gHist->GetXaxis()->FindBin(peaklow);
			int b=gHist->GetXaxis()->FindBin(peakhigh);
			int L=a-20,U=a+20;
			int l=b-20,u=b+20;
			
			TH1* lHist=SmoothOffBack(gHist);
			FitPositionOptimisation(lHist,a,L,U);
			FitPositionOptimisation(lHist,b,l,u);
			delete lHist;
			
			bound_l=gHist->GetXaxis()->GetBinCenter(L);
			bound_u=gHist->GetXaxis()->GetBinCenter(u);
		}
		
		if(cRClicker.size()==1){
			if(cRClicker[0]<peaklow)bound_l=cRClicker[0];
			else bound_u=cRClicker[0];
		}
	}

	return fPeaks;
}

void  UltraFitEnv::FitGUIPeak(){
	//cout<<endl<<"ERROR IN FN Z"<<flush;
	ExternalHistUpdateCheck();
			
	cGoodFit=false;
	cPeakLabels.clear();
	cSaveConf=0;
	cClearConf=0;
	
	if(!gHist)return;
	double bound_l,bound_u;
	vector< jPeakDat >fPass=MakeBoundryPeakList(bound_l,bound_u);
	
	TH1* fExclusionHist=0;
	if(cExClicker.size()>1){
		fExclusionHist=(TH1*)gHist->Clone("ExclusionHist");
		for(unsigned int i=0;(i*2)+1<cExClicker.size();i++){
			int X1=gHist->GetXaxis()->FindBin(cExClicker[i*2]);
			int X2=gHist->GetXaxis()->FindBin(cExClicker[i*2+1]);
			if(X1>X2){int X=X1;X1=X2;X2=X;}
			
			for(int j=X1;j<=X2;j++){
				fExclusionHist->SetBinContent(j,0);
				fExclusionHist->SetBinError(j,0);
			}
		}
	}
	
	string fixsig=cShapeTsig->GetBuffer()->GetString();
	string fixdec=cShapeTdecay->GetBuffer()->GetString();
	string fixsha=cShapeTshare->GetBuffer()->GetString();
	string fixtwiw=cShapeTtwinwidth->GetBuffer()->GetString();
	string fixtwih=cShapeTtwinshare->GetBuffer()->GetString();
    
    // Text input overides check boxes // Should be mutually exclusive in GUI, but just in case
    if(fixdec.size()+fixsha.size()){ // Shouldnt be possible 
        fCheckLimit->SetState(kButtonUp);
        fCheckNoTail->SetState(kButtonUp);
    }
    
	int fittype=1;
    if(fCheckNoTail->GetState()){
        fittype=0;
        fCheckLimit->SetState(kButtonUp); // fCheckNoTail overides fCheckLimit
    } 
    
	if(fCheckTwin->GetState()){
        fittype+=10;
    }
	
    if(fCheckLimit->GetState()){ // Will have been set false if fixsha or fixdec already given
        fixsha="0.965+-0.035";  // 0.93 - 1.
        double Sig,Err;
        ExtractError(fixsig,Sig,Err);
        if(Sig<=0){Sig=2;} // Sig=0 if fixsig empty
        stringstream decss;
        decss<<Sig*1.75<<"+"<<Sig*1.25; // 0.5 - 3 * sigma
        fixdec=decss.str();
    }
    
    string OptString=fixsig+'/'+fixdec+'/'+fixsha+'/'+fixtwiw+'/'+fixtwih;
    
	FullFitHolder* fHold=Ultrapeak::PeakFit(gHist,fExclusionHist,bound_l,bound_u,fPass,fCombo->GetSelected(),fittype,cTrueCent,OptString);
// 	if(fExclusionHist)delete fExclusionHist;
	
	fFitFinished=true;
	this->UltraFitAfter(fHold);
}

void UltraFitEnv::UltraFitAfter(FullFitHolder* fHold){
	TVirtualPad* hold=gPad;
	//cout<<endl<<"ERROR IN FN AAA"<<flush;
	if(fHold&&gHist){
		
// 		cRClicker.clear();
// 		cClicker.clear();
// 		cExClicker.clear();
				
		//update the text on the cBar
		cPeakLabels.clear();
		for(unsigned int i=0;i<cNfit;i++){
			double cc=fHold->CVal(Ultrapeak::VPC(i));
// 			double oo=fHold->CVal(Ultrapeak::VOff);
			
			cPTbox[i]->SetText(TString::Format("%.1f",cc));
			gClient->NeedRedraw(cPTbox[i]);
			
			double hh = gHist->GetBinContent(gHist->GetXaxis()->FindBin(cc));
			cPeakLabels.push_back(TText(cc,hh*1.05,TString::Format("%.1f",cc)));
		}
		
		// Actually update what is drawn
		TCanvas* fCan=GetCan();
		if(fCan){
			fCan->cd();
			double x1=fCan->GetUxmin(),x2=fCan->GetUxmax();
			DrawgHist();
			if(gHistDrawn){
				if(fCheckLabels->GetState())for(unsigned int i=0;i<cNfit;i++){
					cPeakLabels[i].SetTextAlign(21);
					cPeakLabels[i].SetTextFont(82);
					cPeakLabels[i].SetTextSize(0.025);
					cPeakLabels[i].Draw();
				}
				
				gHistDrawn->GetXaxis()->SetRangeUser(x1,x2);
				Ultrapeak::DrawPeak(fHold,GetCan()); // Want this to be the last thing drawn
			}
		}
		
		
		cLastFit=*fHold;
		delete fHold;
		cGoodFit=true;
	}
	gPad=hold;
}


///////////////////////////////////////
/// Saving  //
///////////////////////////////////////

void UltraFitEnv::SaveFit(){
	//cout<<endl<<"ERROR IN FN BBB"<<flush;
	if(cGoodFit){
		cFitList.push_back(new FullFitHolder(cLastFit));
		cout<<endl<<"Fit data saved."<<endl;
		cGoodFit=false;
		
		TObject* last = GetCan()->GetListOfPrimitives()->Last();
		if(last)if(last->InheritsFrom("TF1"))((TF1*)last)->SetLineColor(4);
		
		for(unsigned int i=0;i<cPeakLabels.size();i++)cSaveLabels.push_back(cPeakLabels[i]);
		cPeakLabels.clear();
		DrawSaveLabels();
		
		gPad->Modified();
		gPad->Update();
		
		if(gHist)Ultrapeak::DrawPeak(&cLastFit,0,gHist);//giving histogram says add and 0 for pad skips the draw
	}
}

void UltraFitEnv::ExportFits(){
	//cout<<endl<<"ERROR IN FN CCC"<<flush;
	if(cFitList.size()==0){
		cout << "No Peaks to export" << endl;
		return;
	}
	
	if(!cSaveConf){
		ifstream check("peakinfo.dat");
		if(check.is_open()){
			check.close();
			cout<<endl<<"File peakinfo.dat exists in the current directory.";
			cout<<endl<<"Click again to overwrite."<<endl;
			cSaveConf=true;
			return;
		}
	}

	ofstream outFile("peakinfo.dat");

	if(gHist)Ultrapeak::PrintData(cFitList,gHist,outFile);//Extra inputs shouldn't be needed as cVal already calculated
	else Ultrapeak::PrintData(cFitList,1,outFile);
	
	outFile.close();
	
	ExportSession();
	
	cout<< "Peak info for "<<cFitList.size()<<" fits exported!" << endl;
	cSaveConf=false;
	
}

void UltraFitEnv::ExportFitsMan(string name){
	if(cFitList.size()>0){
        if(name.find(".")<name.size()){
            name=name.substr(0,name.find("."));
        }
        name+=".dat";
        ofstream outFile(name);
        if(gHist)Ultrapeak::PrintData(cFitList,gHist,outFile);// Extra inputs shouldn't be needed as cVal already calculated
        else Ultrapeak::PrintData(cFitList,1,outFile);
        outFile.close();
    }
}


void UltraFitEnv::ExportSession(TString FileName){
    
// 	if(cFitList.size()==0)return;
	
	// Collect Parameters
	
	vector<string> ParamSave(11,"");
	for(int i=0;i<fCombo->GetSelected();i++)ParamSave[0]+="b";
	
	if(fCheckLimit->GetState())ParamSave[1]="t";
	if(fCheckNoTail->GetState())ParamSave[2]="t";
	if(fCheckTwin->GetState())ParamSave[3]="t";
	
	ParamSave[4]=cShapeTsig->GetBuffer()->GetString();
	ParamSave[5]=cShapeTdecay->GetBuffer()->GetString();
	ParamSave[6]=cShapeTshare->GetBuffer()->GetString();
	ParamSave[7]=cShapeTtwinwidth->GetBuffer()->GetString();
	ParamSave[8]=cShapeTtwinshare->GetBuffer()->GetString();
	if(cTrueCent)ParamSave[9]="t";
	ParamSave[10]=fZERO->GetBuffer()->GetString();

	for(unsigned int i=0;i<cNfit-1;i++){
		ParamSave.push_back(cTbox[i]->GetBuffer()->GetString());
		ParamSave.push_back(cRTbox[i]->GetBuffer()->GetString());
	}
	
	// Save Data

    TFile outFileR(FileName,"RECREATE");
	outFileR.cd();
	if(gHist)gHist->Write();
	for(unsigned int i=0;i<cFitList.size();i++){
		stringstream ss;
		ss<<"FIT_"<<i;
		cFitList[i]->Write(ss.str().c_str());
	}
	outFileR.WriteObject(&ParamSave, "ParamSave");
	outFileR.Close();

}

void UltraFitEnv::LoadSession(){
//     const TGWindow *P=GetParent();
	TFile* file =RootFileLoad(this);
	if(file){
		LoadSession(file);
		file->Close();
	}
	
}

void UltraFitEnv::LoadSession(string file){
	
	gROOT->cd();
	TFile* infile=new TFile(file.c_str(),"READ");
	gROOT->cd();
	if(infile->IsOpen()){
		LoadSession(infile);
		infile->Close();
	}else{
		cout<<file<<" not opened."<<endl;
	}
}

void UltraFitEnv::LoadSession(TFile* file){
    gROOT->cd();

	TIter next(file->GetListOfKeys());
	TKey *key;
	TH1* hist=0;
	while ((key = (TKey*)next())) {
		TClass *cl = gROOT->GetClass(key->GetClassName());
		if (cl->InheritsFrom("TH1")){
			hist=(TH1*)key->ReadObj();
			break;
		}
	}
	
	ImportParam(file);
	
	if(hist){
        CaptureHistogram(0,hist,1);//This takes care of disconnecting any canvas 
// 		SetNewHist(hist);
		ImportPeaks(file);
	}

}
	
void UltraFitEnv::ImportPeaks(string file){
	
	TFile* infile=new TFile(file.c_str(),"READ");
	if(infile->IsOpen()){
		ImportPeaks(infile);
		infile->Close();
	}else{
		cout<<file<<" not opened."<<endl;
	}
}

void UltraFitEnv::ImportPeaks(TFile* file){
	gROOT->cd();
	ClearFits();
	TIter next(file->GetListOfKeys());
	TKey *key;
	while ((key = (TKey*)next())) {
		string n=key->GetClassName();
		if(n=="FullFitHolder"){
			FullFitHolder* fit=(FullFitHolder*)key->ReadObj()->Clone();
			fit->Refresh(Ultrapeak(Ultrapeak::NfromTF1(fit),fit->cBits));
			cFitList.push_back(fit);
			if(gHist)Ultrapeak::DrawPeak(fit,0,gHist); // Passing histogram says to addtolist. 0 for pad skips actual drawing
		}
	}
	cGoodFit=false;
	DrawgHist();
}


void UltraFitEnv::ImportParam(TFile* file){
	
	vector<string> *ParamSave=0;
	file->GetObject("ParamSave", ParamSave);
	if(ParamSave){
		vector<string> ParamLoad= *ParamSave;
		
// 		for(auto s:ParamLoad) {
// 			cout << s << '\n';
// 		};

		fCombo->Select(ParamLoad[0].size());
		
		fCheckLimit->SetState(kButtonUp);
		fCheckNoTail->SetState(kButtonUp);
		fCheckTwin->SetState(kButtonUp);
		if(ParamLoad[1].size())fCheckLimit->SetState(kButtonDown);
		if(ParamLoad[2].size())fCheckNoTail->SetState(kButtonDown);
		if(ParamLoad[3].size())fCheckTwin->SetState(kButtonDown);

		string ap=ParamLoad[4]+ParamLoad[5]+ParamLoad[6]+ParamLoad[7]+ParamLoad[8];

		if(cFrame->IsVisible(cShapePane)!=((bool)ap.size())){
			HideShape();// Flips visible state and calls HideSubShapes() when showing;
		}else{
			HideSubShapes();
		}
		
		cShapeTsig->SetText(ParamLoad[4].c_str());
		cShapeTdecay->SetText(ParamLoad[5].c_str());
		cShapeTshare->SetText(ParamLoad[6].c_str());
		cShapeTtwinwidth->SetText(ParamLoad[7].c_str());
		cShapeTtwinshare->SetText(ParamLoad[8].c_str());
		
		if(cTrueCent!=((bool)ParamLoad[9].size()))ChangeCentMode();

		fZERO->SetText(ParamLoad[10].c_str());
			
		for(unsigned int i=11;(i+1)<ParamLoad.size();i+=2){
			unsigned int np=(i-7)/2;
			if(ParamLoad[i].size()||ParamLoad[i+1].size()){
				while(cNfit<np)this->AddTextBox();
				
				cTbox[np-2]->SetText(ParamLoad[i].c_str());
				cRTbox[np-2]->SetText(ParamLoad[i+1].c_str());
			}
		}
   }
}

void UltraFitEnv::PrintFits(){
	if(gHist)Ultrapeak::PrintData(cFitList,gHist);//Extra inputs shouldn't be needed as cVal already calculated
	else Ultrapeak::PrintData(cFitList,1);
}

void UltraFitEnv::ChangeCentMode(){
    cTrueCent=!cTrueCent;
    if(cTrueCent){
        cTrueCentButton->SetText(" True  ");
    }else{
        cTrueCentButton->SetText(" YMax ");
    }
}

const char gHelpCanvas[] = "\n\
  This fitting environment is designed for the automatic fitting of Gaussian \n\
  peaks convolved with exponential tails.\n\
\n\
  To begin fitting click either [Capture Hist] or [Link Canvas] and\n\
  then immediately click on the Canvas/Histogram you want to fit.\n\
\n\
  While the mouse pointer is over the fit histogram,\n\
  the following controls and short-cuts may be used:\n\
		    <[Left Click]>	Select peak.\n\
			  <[Ctrl]>	Set manual bin select (default auto)\n\
			 <[Enter]>	Fit.\n\
		  <[Middle Click]>	Select fit-range.\n\
	<[Shft] THEN [Left Click]>	Select fit-range.\n\
	 <[Alt] THEN [Left Click]>	Select exclusion region.\n\
			     <[+]>	Increase the number of peaks.\n\
			     <[-]>	Decrease the number of peaks.\n\
		    <[0]-[9] keys>	Set the number of peaks.\n\
		   <[.]/[s]/[Del]>	Save latest fit to list & histogram.\n\
			     <[c]>	Clear the selected exclusion region.\n\
\n\
  If the controls do not seem to be working, click on an empty part of the \n\
  environment to de-select any text-input boxes.\n\
\n\
  The tool is designed for fits over small energy regions, as such, all shape \n\
  parameters of degenerate peaks are shared.\n\
\n\
  For multi-peak fits, peak separation are set rather than absolute centroids.\n\
  The area ratio between peaks may also be set if it is in known.\n\
\n\
  Separation and ratio text inputs provide fit constraints, the box should be \n\
  blank to free the fit. Input without errors fill fix the parameter.\n\
  Example inputs : \"25.0\" \"0.051(2)\" \"-16.0 5\" \"6+-5\" \"3E-5+3e-6\"  \n\
  Only symmetric error inputs are presently implemented.\n\
  \n\
  For very small numbers of counts the fit mode will automatically switch to\n\
  Poisson Likelihood fitting rather than Pearson Chi Squared minimisation,\n\
  unless error bars have been manually set.\n\
  Exclusion regions will not function for Likelihood fitting.\n\
  \n\
  Shape parameters (Sigma, Decay and Sharing) may be constrained.\n\
  The bottom most button on the panel [^] will expose these options.\n\
\n\
  Please read the full pdf manual for more details.\n\
\n\
  On Mac, use [F] to set fit region, \n\
			[P] for manual peak-bin selection \n\
			[E] to set exclusion region \n\
\n\n\n\
";


	
	
	
void UltraFitEnv::Help(){
	TRootHelpDialog *hd;
	hd = new TRootHelpDialog(0, "Fitting tool help", 600, 400);
	hd->SetText(gHelpCanvas);
	hd->Popup();
}

void UltraFitEnv::jSaveAs(){
    GetCan()->SetCrosshair(0);
    Stop.Stop();
    Stop.Reset();
	if(gHist){
        TString fileN=HistSaveAs(gHist,this,GetCan());
		if(fileN.EndsWith(".root")){
            ExportSession(fileN);//Overwrite it with session file
            ExportFitsMan((string)fileN);
        }
    }
    Stop.Start();
}

void UltraFitEnv::ClearExclusion(){
	cExClicker.clear();
	this->UpdateLines();
}


double UltraFitEnv::GetFitVal(unsigned int f,unsigned int v){
    if(f<cFitList.size()){
        return cFitList[f]->CVal(v);
    }
    return 0;
}


double UltraFitEnv::GetPeakVal(unsigned int p,unsigned int v){
    int tp=p;
    
    for(unsigned int f=0;f<cFitList.size();f++){
        int Nf=Ultrapeak::NfromTF1(cFitList[f]);
        if(tp<Nf){
            switch (v) {
                case 1: return cFitList[f]->CVal(Ultrapeak::VPC(tp)); break;
                case 2: return cFitList[f]->CVal(Ultrapeak::VPCe(tp)); break; 
                case 3: return cFitList[f]->CVal(Ultrapeak::VPA(tp)); break; 
                case 4: return cFitList[f]->CVal(Ultrapeak::VPAe(tp)); break;
                case 5: return cFitList[f]->CVal(Ultrapeak::VPI(tp)); break; 
                case 6: return cFitList[f]->CVal(Ultrapeak::VPIe(tp)); break; 
                default: return 0;
            }
        }
        tp-=Nf;
    }
    return 0;
}
