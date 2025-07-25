#include "j_gating_master.h"

ClassImp(jGateResultFrame);

//______________________________________________________________________________
jGateResultFrame::jGateResultFrame() : TGHorizontalFrame(gClient->GetRoot(), 100, 100){}

jGateResultFrame::jGateResultFrame(TGWindow * parent,  TH1** res, TH1** back, TH1** proj, double* frac, double* cent,  bool threedee) : TGHorizontalFrame(parent, 100, 100), ThreeDee(threedee), RangeUpdateHold(true),  fCheck0(0), fCheck1(0), fFitFcn(0),fPeakNumText(0),fTip(0),fFitPanel(0),
fResult(res), fBack(back), fProj(proj), fBackFrac(frac), fCentroid(cent),
x1(1),x2(-1),y1(1),y2(-1)
{
	if(fResult==nullptr)return;
	if(fBack==nullptr)return;
	if(fProj==nullptr)return;
	if(fBackFrac==nullptr)return;
	if(fCentroid==nullptr)return;
    
	
TVirtualPad* hold=gPad;
// 	char buf[32];	//A buffer for processing text through to text boxes
	SetCleanup(kDeepCleanup);//Sets this Frame to clean all subframes
	
    TGLayoutHints* ffExpand = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0);
    TGLayoutHints* ffExpandY = new TGLayoutHints(kLHintsExpandY, 0, 0, 0, 0);
    TGLayoutHints* ffExpandXpad = new TGLayoutHints(kLHintsExpandX, 3, 3, 3, 3);
    TGLayoutHints* ffCenX = new TGLayoutHints(kLHintsCenterX, 3, 3, 3, 3);
    TGLayoutHints* ffCenY = new TGLayoutHints(kLHintsCenterY, 3, 3, 3, 3);
    TGLayoutHints* ffCenTop = new TGLayoutHints(kLHintsTop | kLHintsCenterX, 3, 3, 3, 3);
    TGLayoutHints* ffSpeBuf = new TGLayoutHints(kLHintsTop | kLHintsCenterX, 0, 0,10,10);
    
    //
    //   BUILD HISTOGRAM SAVING FRAME
    //
    
    savehists.clear();
    savechecks.clear();
    savebutton.clear();
    
    TGTextButton* spbutton = new TGTextButton(this,">");
    spbutton->Connect("Clicked()","jGateResultFrame",this,"SavePanel()");
    spbutton->SetToolTipText("Show Save Panel\n Open side-panel for holding gating results\n  in memory to enable on-the-fly summing.");
    
    saveframe= new TGVerticalFrame(this, 0, 0, 0); 
    TGTextButton* plushist = new TGTextButton(saveframe,"DrawSum");
    plushist->Connect("Clicked()","jGateResultFrame",this,"DrawSaved()");
    plushist->SetToolTipText("Draw a sum of currently\n selected saved Histograms.");
    saveframe->AddFrame(plushist,ffSpeBuf);//
    
    plushist = new TGTextButton(saveframe,"DeleteAll");
    plushist->Connect("Clicked()","jGateResultFrame",this,"CSaveButton()");
    plushist->SetToolTipText("Clear all locally saved\n gated histograms.");
    saveframe->AddFrame(plushist,ffSpeBuf);//
    
    TGLabel *label = new TGLabel(saveframe, "Saved Gated\n Histograms.\n Check box\n   to sum.");
    savebuttons = new TGButtonGroup(saveframe,15,2);
    savebuttons->Connect(" Clicked(Int_t)", "jGateResultFrame", this,"StoreHistograms(Int_t)");//Link test signal to its	
	AddStoreHistogram();
    
    saveframe->AddFrame(label,ffSpeBuf);//
    saveframe->AddFrame(savebuttons,ffCenTop);//
	
	//
    //   BUILD RESULT FRAME
    //
    
    resultframe = new TGVerticalFrame(this, 0, 0, 0);
    TGHorizontalFrame* buttonframe = new TGHorizontalFrame(resultframe, 0, 0, 0); 
    fBgroup1 = new TGButtonGroup(buttonframe,"Show Extra",kChildFrame);// Another button group
        fRButton1 = new TGRadioButton(fBgroup1,"    ");
        fRButton1->SetToolTipText("Normal View Mode");
        fRButton2 = new TGRadioButton(fBgroup1,"Projection ");
        fRButton2->SetToolTipText("Show Projection\n Show a scaled version of the full\n un-gated projection for this axis.");
        fRButton3 = new TGRadioButton(fBgroup1,"Background ");
        fRButton3->SetToolTipText("Show Background\n Show the background spectrum currently\n being subtracted (actual size).");
    fRButton1->SetState(kButtonDown);
    fBgroup1->Show();
    fBgroup1->Connect(" Clicked(Int_t)", "jGateResultFrame", this,"ButtonGroupDoUpdate(Int_t)");
    
    if(ThreeDee){
        fCheck0 = new TGCheckButton(buttonframe,"2D ");
        fCheck0->SetState(kButtonUp);
        fCheck0->Connect(" Clicked()", "jGateResultFrame", this,"DoCheckbox2D()");
        fCheck0->SetToolTipText("2D Only\n Do not perform the second axis subtraction.\n Instead view TH2 matrix results from the first.");
    }
	
	fCanvas1 = new TRootEmbeddedCanvas(jGateSelectFrame::Iterator("Embedded"), resultframe, 600, 400);
    fCanvas1->GetCanvas()->SetName(jGateSelectFrame::Iterator("ResultCan"));
    
    fCanvas1->GetCanvas()->SetFillColor(33);
    fCanvas1->GetCanvas()->SetBorderMode(0);
    fCanvas1->GetCanvas()->SetFrameFillColor(10);

    fCanvas1->GetCanvas()->SetMargin(0.01,0.005,0.08,0.005);	
    fCanvas1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "jGateResultFrame", this,"ClickedFinalCanvas(Int_t,Int_t,Int_t,TObject*)");
    fCanvas1->GetCanvas()->Connect("RangeChanged()", "jGateResultFrame", this, "NewAxisDrawn()");
	
	// rebin bar
    TGHorizontalFrame* rebinframe = new TGHorizontalFrame(resultframe, 0, 0, 0);
        TGLabel *reblabel = new TGLabel(rebinframe, "Binning ");
        rebinframe->AddFrame(reblabel,ffCenY);
        
        fHslider1 = new TGHSlider(rebinframe, 9, kSlider2);
        fHslider1->SetPosition(0);
        fHslider1->Connect("PositionChanged(Int_t)", "jGateResultFrame", this, "DrawHist()");
        rebinframe->AddFrame(fHslider1, ffExpandXpad);
        
        RebinText = new TGTextEntry(rebinframe, new TGTextBuffer(4));
        RebinText->SetDefaultSize(40,25);
        RebinText->SetAlignment(kTextCenterX);
        RebinText->SetEnabled(kFALSE);
        rebinframe->AddFrame(RebinText,ffCenY);
    
    ftbutton = new TGTextButton(buttonframe,"Fit Panel");
    ftbutton->Connect("Clicked()","jGateResultFrame",this,"FitPanel()");
    ftbutton->SetToolTipText("Open Fit Tool\n Open an instance of J-fit panel,\n initially connected to result canvas.");

    TGTextButton* SAbutton = new TGTextButton(buttonframe,"SaveAs");
    SAbutton->Connect("Clicked()","jGateResultFrame",this,"jSaveAs()");
    SAbutton->SetToolTipText("Save the currently drawn histogram.");
    
    fCheck1 = new TGCheckButton(buttonframe,"Hide Ers");
    fCheck1->SetState(kButtonDown);
    fCheck1->Connect(" Clicked()", "jGateResultFrame", this,"DrawHist()");
    fCheck1->SetToolTipText("Hide Bin Errors on drawn histograms");

    buttonframe->AddFrame(fBgroup1, ffCenX);
    if(ThreeDee)buttonframe->AddFrame(fCheck0, ffCenY);
    buttonframe->AddFrame(ftbutton, ffCenY);
    buttonframe->AddFrame(SAbutton, ffCenY);
    buttonframe->AddFrame(fCheck1, ffCenY);
    resultframe->AddFrame(buttonframe, ffCenX);
    resultframe->AddFrame(fCanvas1, ffExpand);
    resultframe->AddFrame(rebinframe, ffExpandXpad);  
	
    //
    //   Add Frames to the main layout
    //
    
    AddFrame(resultframe,ffExpand);
    AddFrame(spbutton,ffExpandY);
    AddFrame(saveframe,ffExpandY);

	InputUpdated();
    
    // create the tooltip with a timeout of 250 ms
    fTip = new TGToolTip(gClient->GetRoot(), fCanvas1, "", 250);

gPad=hold;
}

jGateResultFrame::~jGateResultFrame()
{
    // if(fTip){fTip->Hide();delete fTip;} // Inclusion caused crashes, but ommiting leaves an orphaned tooltip
    ClearSaved();//delete any saved result histograms
	Cleanup(); 
}

void jGateResultFrame::DrawHist(){
    TVirtualPad* hold=gPad;
    RangeUpdateHold=true;
	fCanvas1->GetCanvas()->cd();
    
    TH1* H=nullptr;
    TH1* HIn=*fResult;
    TH1* HBack=*fBack;
    TH1* HProj=*fProj;
    double Frac=*fBackFrac;
    
    if(HIn==nullptr||HBack==nullptr||HProj==nullptr)return;
    
    bool TwoDee=false;
    if(ThreeDee)TwoDee=fCheck0->GetState(); //If draw 2D

    if(TwoDee){//Slight changed for 2D vs 1D drawing
            
        if(fRButton2->GetState()){//If Full Projection Drawing Requested
            H=DrawHistOpt(HProj); //Drawing a using jRoot library default options
		}else if(fRButton3->GetState()){//If Drawing of Background Requested
            H=DrawCopyHistOpt(HBack); //Use copy as we want to modify
            H->Scale(Frac);
            // The correctly *scaled* background hist never actually exists
            // The scaling is done in within the internal subtraction routine
            // The errors will not be scaled as they are in the subtraction
        }else{//Default 
            H=DrawHistOpt(HIn);//Draw directly the result (for 2D we avoid Copy for speed)
        }
    }else{// 1D
        H=DrawCopyHistOpt(HIn,fCheck1->GetState());//fCheck1 option for draw bin errors or not
        
        // Rebining is only used for 1D hists
        unsigned short rebin=fHslider1->GetPosition()+1;
        
        if(rebin>1)H->Rebin(rebin);
        
        // Update the rebin slider text
            char buf[32];
            sprintf(buf, "%.1f", H->GetXaxis()->GetBinWidth(1));
            TGTextBuffer* fTbh2=RebinText->GetBuffer();
            fTbh2->Clear();	fTbh2->AddText(0, buf);
            RebinText->SetCursorPosition(RebinText->GetCursorPosition());
            RebinText->Deselect();
            gClient->NeedRedraw(RebinText);
        // Exists in this function as adjusting the slider just calls this function
        
        TH1* h=nullptr;
        
        if(fRButton2->GetState()){//If Full Projection 
            h=HProj->DrawCopy("same");
            h->Scale(HIn->Integral()/HProj->Integral());//Scale to make visible
            h->SetLineColor(kGreen+1);
        }
        if(fRButton3->GetState()){//If Background
            h=HBack->DrawCopy("same");
            h->Scale(Frac);
            h->SetLineColor(kRed+1);
        }
        if(h){
            h->Sumw2(kFALSE);
            if(rebin>1)h->Rebin(rebin);
        }  
    }//1D/2D
    
    
    //Set the range to what they were before the draw update
    H->GetXaxis()->SetRangeUser(x1,x2);
    if(TwoDee){
        H->GetYaxis()->SetRangeUser(y1,y2);
    }
    
	fCanvas1->GetCanvas()->Modified();
	fCanvas1->GetCanvas()->Update();
    
    RangeUpdateHold=false; 
    gPad=hold;
}

//Just reset the viewing range of thefinal canvas
void jGateResultFrame::ResetRange(){
    x1=0;
    x2=0;
    y1=0;
    y2=0;
//Previously +-1E20 was used, but that was because RangeUser, not bins, were being used
}


void jGateResultFrame::NewAxisDrawn() // Save the draw range, so that when gating conditions change we view the same area
{
	if(!RangeUpdateHold){ // Set true by DrawHist(), so only do this on axis zooming, NOT on new draw
		TH1* h=hist_capture(fCanvas1->GetCanvas());
        if(h){
            TAxis* x=h->GetXaxis();
            x1=x->GetBinLowEdge(x->GetFirst());
            x2=x->GetBinUpEdge(x->GetLast());
            
            if(ThreeDee){if(fCheck0->GetState()){
                TAxis* y=h->GetXaxis();
                y1=y->GetBinLowEdge(y->GetFirst());
                y2=y->GetBinUpEdge(y->GetLast());
            }}
            
            if(fFitFcn&&fCanvas1->GetCanvas()->GetListOfPrimitives()->FindObject(fPeakNumText)){
                double cent=fFitFcn->GetParameter(1);
                fPeakNumText->SetX(cent+(x2-x1)*0.05);
                fCanvas1->GetCanvas()->Modified();
                fCanvas1->GetCanvas()->Update();
            }
        }
    }
	
}

void jGateResultFrame::DoCheckbox2D(){
    
    //If the 2D checkbox exist, i.e. ThreeDee was set
    if(ThreeDee){
        if(fCheck0->GetState()&&fFitPanel){//If 2D drawing is being requested, and a fit panne exists
            ftbutton->SetState(kButtonUp);//Pop out the fit pannel button which is kept depressed
            HideFrame(fFitPanel);//Hide the fitpanel as it is not in use from now
        }
    }
    
    ResetRange(); //Reset any saved histogram range
	ClearSavedButtons();ClearSaved(); //Clear the saved histograms so 2D and 1D arent mixed
    
    Bool_t emitbool=fCheck0->GetState(); 
    Emit("RequestTwoDee(Bool_t)", emitbool); //Pass the request to change up to the parent
}


void jGateResultFrame::ButtonGroupDoUpdate(Int_t i){ //When the projection buttons clicked
    if(i==1){
        ResetRange(); // Reset range
    }
    DrawHist(); //Draw the histogram panel
}


// Just a basic little no frills, minimal input peak fitter for standard size y/e peaks
// Added it in to help with quick peak identification
void jGateResultFrame::ClickedFinalCanvas(Int_t event, Int_t px, Int_t py, TObject *selected_ob)
{TVirtualPad* hold=gPad;
	if (event == kMouseLeave){fTip->Hide(); return;}
	
    if(ThreeDee){
        if(fCheck0->GetState()) return;
        //Dont try to fit in 2D mode
    }
	
	if(event == kMouseMotion||event == kButton1Double){
        //Click is given in pixel coordinates
        double x =fCanvas1->GetCanvas()->PixeltoX(px);
        
        //Update the tooltip
        fTip->Hide();
        fTip->SetText(TString::Format("%.1f",x));
        fTip->SetPosition(px+15, py-15);
        fTip->Reset();
        
        if ( event == kButton1Double) {
            
            fCanvas1->GetCanvas()->cd();
        
            TH1* h=hist_capture(fCanvas1->GetCanvas());
            if(!h)return;
            
            TF1* Quick=UserQuickSingleGausAutoFitE(h,x,x-20,x+20,1);//Free & linear back

            if(fFitFcn)fCanvas1->GetCanvas()->GetListOfPrimitives()->Remove(fFitFcn);
            fFitFcn=Quick->DrawCopy("same");

            // Print the text on the canvas
            double cent=Quick->GetParameter(1);
            stringstream ss;
            ss<<round(cent*10)/10;
            
            delete Quick;
            
            TText peaknum;
            peaknum.SetTextAlign(22);
            peaknum.SetTextSize(0.035);
            
            double shif=(h->GetXaxis()->GetBinCenter(h->GetXaxis()->GetLast())-h->GetXaxis()->GetBinCenter(h->GetXaxis()->GetFirst()))*0.05;
            //GetXmin() doesnt account for zooming
            
            if(fPeakNumText)fCanvas1->GetCanvas()->GetListOfPrimitives()->Remove(fPeakNumText);//Remove if its there else ignored
            fPeakNumText=peaknum.DrawText(cent+shif,h->GetBinContent(h->FindBin(cent))*0.95,ss.str().c_str());

            fCanvas1->GetCanvas()->Modified();
            fCanvas1->GetCanvas()->Update();
        }
    }
gPad=hold;
}

void jGateResultFrame::HideSave(){
    HideFrame(saveframe);
}


// Toggle Save-Panel Visibility 
void jGateResultFrame::SavePanel(){
	if(IsVisible(saveframe)){
		HideSave();
	}else{
		ShowFrame(saveframe);
	}
}

void jGateResultFrame::AddStoreHistogram(){
	if(savehists.size()<15){
		savebutton.push_back(new TGTextButton(savebuttons,"  [save]  "));
		
		savebutton[savebutton.size()-1]->SetToolTipText("Save current gating\n result histogram.");
		savechecks.push_back(new TGCheckButton(savebuttons,""));
		savechecks[savechecks.size()-1]->SetEnabled(false);
		savechecks[savechecks.size()-1]->SetToolTipText("Include this saved histogram\n when drawing sum.");
		savehists.push_back(0);
		savebuttons->Show();
		saveframe->MapSubwindows();saveframe->Resize(saveframe->GetDefaultSize());saveframe->MapWindow();
	}
}

void jGateResultFrame::StoreHistograms(Int_t i){
	if(i%2){
		uint select=i/2;
        
		if(select<savehists.size()){
			if(savehists[select]){delete savehists[select];}savehists[select]=0;
			
			TH1* targ=*fResult;
            if(!targ)return;
			
			savehists[select]=(TH1*)targ->Clone(jGateSelectFrame::Iterator("SavedHist"));
			savehists[select]->GetListOfFunctions()->Clear();
			
			if(!savechecks[select]->IsEnabled())savechecks[select]->SetEnabled();
			
			stringstream ss;ss<<" "<<*fCentroid<<" ";
		
			savebutton[select]->SetText(ss.str().c_str());
            
            if(select==savebutton.size()-1)AddStoreHistogram();
		}
	}
}

void jGateResultFrame::DrawSaved(){
	TH1* saveadd=0;
	for(uint i=0;i<savehists.size();i++){
		if(savehists[i])if(savechecks[i]->GetState()==EButtonState::kButtonDown){
			if(saveadd){
				if(saveadd->GetNbinsX()==savehists[i]->GetNbinsX())
					saveadd->Add(savehists[i]);
			}else{
				saveadd=(TH1*)savehists[i]->Clone(jGateSelectFrame::Iterator("SavedHist"));
			}
		}
	}
	if(saveadd){
		unsigned short rebin=fHslider1->GetPosition()+1;
		if(rebin>1)saveadd->Rebin(rebin);
        DrawPeakClickerCanvas(saveadd);
        saveadd->SetDirectory(0);
        saveadd->SetBit(kCanDelete);
        //Could have done drawcopy but this saves one copy if a big TH2
	}
}

void jGateResultFrame::ClearSavedButtons(){
    for(uint i=0;i<savehists.size();i++){
        savechecks[i]->SetState(kButtonUp);
        savechecks[i]->SetState(kButtonDisabled);
        savebutton[i]->SetText("[Empty]");
    }
}

void jGateResultFrame::ClearSaved(){
	for(uint i=0;i<savehists.size();i++){
        if(savehists[i]){
            delete savehists[i];
            savehists[i]=0;
        }
    }
}


void jGateResultFrame::CSaveButton(){
    
    std::chrono::duration<double> diff= std::chrono::system_clock::now()-clicktime;
    if(abs(diff.count())<2){
        ClearSavedButtons();
        ClearSaved();
    }else{
        cout<<"Click twice to clear."<<endl;
    }
    
    clicktime=std::chrono::system_clock::now();
}


void jGateResultFrame::jSaveAs(){
	TH1* h=hist_capture(fCanvas1->GetCanvas());
    if(!h)return;
	HistSaveAs(h,this,fCanvas1->GetCanvas());
}

// Create an instance of the hitpanel panel and connect it the output canvas to catch new draws
// Or hide disconnect it and hide it if it is currently acrive
void jGateResultFrame::FitPanel(){
    
	if(ThreeDee)if(fCheck0->GetState())return;//Do nothing in 2D mode
    
    if(!fFitPanel){
		fFitPanel=new UltraFitEnv(this,0,fCanvas1->GetCanvas(),2);
        AddFrame(fFitPanel,new TGLayoutHints(kLHintsExpandY, 1, 1, 1, 1));
        Resize(GetDefaultSize());
        HideFrame(fFitPanel);//Hiding panel just for next i
    }
    
	if(IsVisible(fFitPanel)){
        ftbutton->SetState(kButtonUp);
        HideFrame(fFitPanel);
        fFitPanel->KillCan();
        DrawHist();
    }else{
        ftbutton->SetState(kButtonDown);
        ShowFrame(fFitPanel);
        fFitPanel->ConnectNewCanvas(fCanvas1->GetCanvas());
	}
	
}
