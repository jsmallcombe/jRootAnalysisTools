//
//
//	James gating GUI tool 1.2
// 	27/10/16		16/10/2015
//	james.smallcombe@outlook.com
//
//

#include "j_gating_tool.h"
#include "j_gpad_tools.h"

bool gGlobalAskWindowName=false;
void SetGlobalAskWindowName(bool set){
	gGlobalAskWindowName=set;
}

ClassImp(jgating_tool);

int jgating_tool::jgating_tool_iterator = 0;


jgating_tool::jgating_tool(const char * input) : jgating_tool(gROOT->FindObject(input)){}

jgating_tool::jgating_tool(TObject* input,bool Owner) : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame) ,gJframe1(0),fCheck0(0),fCheck1(0),fFitFcn(0),peaknumremove(0),fTip(0),fFitPanel(0),fInputStore(0),x1(1),x2(-1),y1(1),y2(-1),RangeUpdateHold(1){
TVirtualPad* hold=gPad;
    ResetRange();

	if(!input){
//      delete this;
        return;
    }
    
	bool Bthree=input->IsA()->InheritsFrom("TH3");
    
    if(!(Bthree||input->IsA()->InheritsFrom("TH2"))){
        return;
    }
    
	TGTransientFrame* PopUp=0;
	if(Bthree){
        PopUp=MakeTH3Popup();
		cout<<endl<<endl<<" ============== Beginning Loading of TH3 ============ "<<endl<<" ====== Please be patient until window appears ====== "<<endl<<endl;
	}
		
	char* FrameReNamChar=new char[128];
    string FrameReNamStr;
	if(gGlobalAskWindowName){
        new TGInputDialog(gClient->GetRoot(),gClient->GetRoot(),"Rename Gate Tool Window",input->GetName(),FrameReNamChar);
        FrameReNamStr=FrameReNamChar;
    }
    
	if(FrameReNamStr.size()){
		SetWindowName(FrameReNamStr.c_str());	
	}else{
		SetWindowName(input->GetName());	
	}
	
    TH1* pass=(TH1*)input;

    if(!Bthree){
        // Make a local copy of TH2
        // Still too intensive to do it for TH3 though.
        stringstream ss;
        ss<<"GateStoreCopy"<<make_iterator();
        fInputStore=(TH1*)pass->Clone(ss.str().c_str());
        pass=fInputStore;
    }


    //
    //   FINISHED INPUT START BUILDING THE FRAMES
    //
    
    SetCleanup(kDeepCleanup);	
    
    //    //--- layout for the frame:
    TGLayoutHints* ffExpandLeft = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0);
    TGLayoutHints* ffExpand = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0);
    TGLayoutHints* ffExpandRight = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kLHintsRight, 0, 0, 0, 0);
//     TGLayoutHints* ffExpandY = new TGLayoutHints(kLHintsExpandY, 0, 0, 0, 0);
    TGLayoutHints* ffExpandYRight = new TGLayoutHints(kLHintsExpandY | kLHintsRight, 0, 0, 0, 0);
    TGLayoutHints* ffExpandYLeft = new TGLayoutHints(kLHintsExpandY | kLHintsLeft, 0, 0, 0, 0);
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
    spbutton->Connect("Clicked()","jgating_tool",this,"SavePanel()");
    spbutton->SetToolTipText("Show Save Panel\n Open side-panel for holding gating results\n  in memory to enable on-the-fly summing.");
    
    saveframe= new TGVerticalFrame(this, 0, 0, 0); 
// 		TGButtonGroup* savecontrolbut = new TGButtonGroup(saveframe,1,2);
    TGTextButton* plushist = new TGTextButton(saveframe,"DrawSum");
    plushist->Connect("Clicked()","jgating_tool",this,"DrawSaved()");
    plushist->SetToolTipText("Draw a sum of currently\n selected saved Histograms.");
    saveframe->AddFrame(plushist,ffSpeBuf);//
    
    plushist = new TGTextButton(saveframe,"DeleteAll");
    plushist->Connect("Clicked()","jgating_tool",this,"CSaveButton()");
    plushist->SetToolTipText("Clear all locally saved\n gated histograms.");
    saveframe->AddFrame(plushist,ffSpeBuf);//
    
    TGLabel *label = new TGLabel(saveframe, "Saved Gated\n Histograms.\n Check box\n   to sum.");
// 		TGHorizontalFrame* inbetw= new TGHorizontalFrame(saveframe, 0, 0, 0);
// 		savebuttons = new TGButtonGroup(inbetw,"",kVerticalFrame);
    savebuttons = new TGButtonGroup(saveframe,15,2);
    savebuttons->Connect(" Clicked(Int_t)", "jgating_tool", this,"StoreHistograms(Int_t)");//Link test signal to its	
    AddStoreHistogram();
    
    saveframe->AddFrame(label,ffSpeBuf);//
    saveframe->AddFrame(savebuttons,ffCenTop);//
    
    //
    //   BUILD RESULT FRAME
    //
    
    MainPanels = new TGHorizontalFrame(this, 0, 0, 0); 

    resultframe = new TGVerticalFrame(MainPanels, 0, 0, 0);
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
    fBgroup1->Connect(" Clicked(Int_t)", "jgating_tool", this,"ButtonGroupDoUpdate(Int_t)");
    
    if(Bthree){
        fCheck0 = new TGCheckButton(buttonframe,"2D ");
        fCheck0->SetState(kButtonUp);
        fCheck0->Connect(" Clicked()", "jgating_tool", this,"DoCheckbox2D()");
        fCheck0->SetToolTipText("2D Only\n Do not perform the second axis subtraction.\n Instead view TH2 matrix results from the first.");
    }
    
    fCanvas1 = new TRootEmbeddedCanvas(("Embedded"+make_iterator()).c_str(), resultframe, 600, 400);
    fCanvas1->GetCanvas()->SetName(("ResultCan"+make_iterator()).c_str());
    
    fCanvas1->GetCanvas()->SetFillColor(33);
    fCanvas1->GetCanvas()->SetBorderMode(0);
    fCanvas1->GetCanvas()->SetFrameFillColor(10);

    fCanvas1->GetCanvas()->SetMargin(0.01,0.005,0.08,0.005);	
    fCanvas1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "jgating_tool", this,"ClickedFinalCanvas(Int_t,Int_t,Int_t,TObject*)");
    fCanvas1->GetCanvas()->Connect("RangeChanged()", "jgating_tool", this, "NewAxisDrawn()");
    
    // rebin bar
    
    TGHorizontalFrame* rebinframe = new TGHorizontalFrame(resultframe, 0, 0, 0);
        TGLabel *reblabel = new TGLabel(rebinframe, "Binning ");
        rebinframe->AddFrame(reblabel,ffCenY);
        
        fHslider1 = new TGHSlider(rebinframe, 9, kSlider2);
        fHslider1->SetPosition(0);
        fHslider1->Connect("PositionChanged(Int_t)", "jgating_tool", this, "DoUpdate()");
        rebinframe->AddFrame(fHslider1, ffExpandXpad);
        
        RebinText = new TGTextEntry(rebinframe, new TGTextBuffer(4));
        RebinText->SetDefaultSize(40,25);
        RebinText->SetAlignment(kTextCenterX);
        RebinText->SetEnabled(kFALSE);
        rebinframe->AddFrame(RebinText,ffCenY);
    
    ftbutton = new TGTextButton(buttonframe,"Fit Panel");
    ftbutton->Connect("Clicked()","jgating_tool",this,"FitPanel()");
    ftbutton->SetToolTipText("Open Fit Tool\n Open an instance of J-fit panel,\n initially connected to result canvas.");

    TGTextButton* SAbutton = new TGTextButton(buttonframe,"SaveAs");
    SAbutton->Connect("Clicked()","jgating_tool",this,"jSaveAs()");
    SAbutton->SetToolTipText("Save the currently drawn histogram.");
    
    fCheck1 = new TGCheckButton(buttonframe,"Hide Ers");
    fCheck1->SetState(kButtonDown);
    fCheck1->Connect(" Clicked()", "jgating_tool", this,"DoUpdate()");
    fCheck1->SetToolTipText("Hide Bin Errors on drawn histograms");

    buttonframe->AddFrame(fBgroup1, ffCenX);
    if(Bthree)buttonframe->AddFrame(fCheck0, ffCenY);
    buttonframe->AddFrame(ftbutton, ffCenY);
    buttonframe->AddFrame(SAbutton, ffCenY);
    buttonframe->AddFrame(fCheck1, ffCenY);
    resultframe->AddFrame(buttonframe, ffCenX);
    resultframe->AddFrame(fCanvas1, ffExpand);
    resultframe->AddFrame(rebinframe, ffExpandXpad);  
    
    //
    //   BUILD j_gating_frame FRAMES
    //
    
    //If TH3 extra gate panel
    if(Bthree){
        gJframe1 = new j_gating_frame(MainPanels,pass,make_iterator());
        gJframe1->Connect("InputChange()", "jgating_tool", this,"ResetRange()");
        gJframe1->Connect("OutputReady()", "jgating_tool", this,"DoUpdate2D()");
        pass=(TH1*)gJframe1->output_hist_point;
    }
    
    //TH2 gate panel
    gJframe2 = new j_gating_frame(MainPanels,pass,make_iterator());
    gJframe2->Connect("InputChange()", "jgating_tool", this,"ResetRange()");
    gJframe2->Connect("OutputReady()", "jgating_tool", this,"DoUpdate()");
    
    
    //
    //   Add Frames to the main layout
    //
    
    AddFrame(MainPanels, ffExpandLeft);
    AddFrame(saveframe,ffExpandYRight);
    AddFrame(spbutton,ffExpandYRight);
    
    
    if(Bthree){
        gJframe1->ChangeOptions(kFixedWidth);
        MainPanels->AddFrame(gJframe1,ffExpandYLeft);
        TGVSplitter* splitter = new TGVSplitter(MainPanels);
        splitter->SetFrame(gJframe1, kTRUE);
        MainPanels->AddFrame(splitter,ffExpandYLeft);
    }
    
    gJframe2->ChangeOptions(kFixedWidth);
    MainPanels->AddFrame(gJframe2,ffExpandYLeft);
    splitterB = new TGVSplitter(MainPanels);   
    splitterB->SetFrame(gJframe2, kTRUE);
    MainPanels->AddFrame(splitterB,ffExpandYLeft);
    MainPanels->AddFrame(resultframe,ffExpandRight);
    
    Connect("ProcessedConfigure(Event_t*)","jgating_tool", this,"ProcessedConfigure(Event_t*)");
    
    // create the tooltip with a timeout of 250 ms
    fTip = new TGToolTip(gClient->GetRoot(), fCanvas1, "", 250);

    MapSubwindows();
    Resize(GetDefaultSize());
    MapWindow();

    HideFrame(saveframe);
    gJframe2->HideFrame(gJframe2->fHframe4);
    if(Bthree)gJframe1->HideFrame(gJframe1->fHframe4);
    
    ShareMainPanels();
    
    DoUpdate();
    if(PopUp){PopUp->CloseWindow();}
	
gPad=hold;
}

//______________________________________________________________________________
jgating_tool::~jgating_tool()
{
    ClearSaved();//delete any saved result histograms
    
// 	if(fTip){fTip->Hide();delete fTip;} // Seems have created many crashes recently 
	if(fInputStore){delete fInputStore;}
	
	Closed(this);
    
   // Clean up
    Cleanup();
}

//______________________________________________________________________________
// void jgating_tool::DoClose()
// {
//    // Called when window is closed via the window manager
//    
//    cout<<endl<<"DOO0000000OM"<<endl;
//    delete this;
// }


void jgating_tool::ProcessedConfigure(Event_t*){
//     cout<<endl<<"Processed "<<in<<flush;
    ShareMainPanels();
}


void jgating_tool::ShareMainPanels(){
    double width = MainPanels->GetWidth();
    if(gJframe1){
        if(MainPanels->IsVisible(gJframe2)){
            gJframe1->SetWidth(width*0.333);
            gJframe2->SetWidth(width*0.333);
        }else{
            gJframe1->SetWidth(width*0.5);
        }
    }else{
        gJframe2->SetWidth(width*0.5);
    }
    MainPanels->Layout();//This was the only way I could get for the above SetWidth to happen NOW
}

//Just reset the viewing range of thefinal canvas
void jgating_tool::ResetRange(){
//     cout<<endl<<"RESETTING RANGE"<<endl;
    // usual -1 +1 actually doesnt work if they are in the same bin
    x1=1E20;
    x2=-1E20;
    y1=1E20;
    y2=-1E20;
}


void jgating_tool::DoCheckbox2D(){
    if(fCheck0)if(fCheck0->GetState()&&fFitPanel){
        ftbutton->SetState(kButtonUp);
        HideFrame(fFitPanel);
    }
    
    ResetRange();
	CSaveButton();
	DoUpdate2D();
}


void jgating_tool::ButtonGroupDoUpdate(Int_t i){
    if(i==1){
        ResetRange();
    }
    DoUpdate();
}



void jgating_tool::DoUpdate2D(){TVirtualPad* hold=gPad;
    RangeUpdateHold=true;
	if(!gJframe1)return;
	gJframe1->hidebinerrors=fCheck1->GetState();
	if(fCheck0->GetState()){
		MainPanels->HideFrame(gJframe2);
		MainPanels->HideFrame(splitterB);
		fCanvas1->GetCanvas()->cd();
		if(fRButton2->GetState()){
            
			TH1* H=DrawCopyHistOpt(gJframe1->full);
            H->GetXaxis()->SetRangeUser(x1,x2);
            H->GetYaxis()->SetRangeUser(y1,y2);
		}else if(fRButton3->GetState()){
			gJframe1->free_hist->Add(gJframe1->gate_hist,gJframe1->output_hist_point,1,-1);
			TH1* H=DrawCopyHistOpt(gJframe1->free_hist);
            H->GetXaxis()->SetRangeUser(x1,x2);
            H->GetYaxis()->SetRangeUser(y1,y2);
		}else{
			TH1* H=gJframe1->output_hist_point;
            DrawHistOpt(H);
            H->GetXaxis()->SetRangeUser(x1,x2);
            H->GetYaxis()->SetRangeUser(y1,y2);
		}

		fCanvas1->GetCanvas()->Modified();
		fCanvas1->GetCanvas()->Update();
	}else{
		gJframe2->hidebinerrors=fCheck1->GetState();
		MainPanels->ShowFrame(gJframe2);
		MainPanels->ShowFrame(splitterB);
		gJframe2->UpdateInput(gJframe1->output_hist_point);
	}
	ShareMainPanels();
RangeUpdateHold=false;
gPad=hold;
}


void jgating_tool::DoUpdate(){
    TVirtualPad* hold=gPad;
    RangeUpdateHold=true;
    
	gJframe2->hidebinerrors=fCheck1->GetState();

	if(fCheck0){
		if(fCheck0->GetState()){//Dangerously close to awful loop behaviour
			DoUpdate2D();
			return;
		}
	}

	ShowFrame(gJframe2);
	
	unsigned short rebin=fHslider1->GetPosition()+1;
	
	TH1* H;
	fCanvas1->GetCanvas()->cd();
    
	H=DrawCopyHistOpt(gJframe2->output_hist_point,fCheck1->GetState());
	if(rebin>1)H->Rebin(rebin);		
    H->GetXaxis()->SetRangeUser(x1,x2);
    
    char buf[32];
    sprintf(buf, "%.1f", H->GetXaxis()->GetBinWidth(1));
    TGTextBuffer* fTbh2=RebinText->GetBuffer();
    fTbh2->Clear();	fTbh2->AddText(0, buf);
    RebinText->SetCursorPosition(RebinText->GetCursorPosition());
    RebinText->Deselect();
    gClient->NeedRedraw(RebinText);
    
//     H->GetXaxis()->SetLabelSize(0.03);
//     H->GetXaxis()->SetTicks("+");
//     H->GetXaxis()->SetLabelFont(42);
    H->GetYaxis()->SetNdivisions(8);
    H->GetYaxis()->SetTickLength(0.03);
    
	if(fRButton2->GetState()){
		gJframe2->free_hist->Reset();
		gJframe2->free_hist->Add(gJframe2->full,gJframe2->output_hist_point->Integral()/gJframe2->full->Integral());
	}
	if(fRButton3->GetState()){
		gJframe2->free_hist->Add(gJframe2->gate_hist,gJframe2->output_hist_point,1,-1);
	}
	if(!fRButton1->GetState()){
		gJframe2->free_hist->Sumw2(kFALSE);
		TH1* h=gJframe2->free_hist->DrawCopy("same");
		if(rebin>1)h->Rebin(rebin);		
	}
	
	fCanvas1->GetCanvas()->Modified();
	fCanvas1->GetCanvas()->Update();
	
RangeUpdateHold=false;
gPad=hold;
}


string jgating_tool::make_iterator(){
	stringstream ss;
	ss << jgating_tool_iterator;
	jgating_tool_iterator++;
	return ss.str();
}


// Just a basic little no frills, minimal input peak fitter for standard size y/e peaks
// Added it in to help with quick peak identification
void jgating_tool::ClickedFinalCanvas(Int_t event, Int_t px, Int_t py, TObject *selected_ob)
{TVirtualPad* hold=gPad;
	if (event == kMouseLeave){fTip->Hide(); return;}
	
	//Click is given in pixel coordinates
	double x =fCanvas1->GetCanvas()->PixeltoX(px);
	
	//Update the tooltip
	fTip->Hide();
	fTip->SetText(TString::Format("%.1f",x));
	fTip->SetPosition(px+15, py-15);
	fTip->Reset();
	
	if ( event == kButton1Double) {
        if(gJframe1){
            if(fCheck0->GetState())return;
            //Dont try to fit in 2D mode
        }
        
		fCanvas1->GetCanvas()->cd();
	
		TH1* h=hist_capture(fCanvas1->GetCanvas());
		if(!h)h=gJframe2->output_hist_point;
		
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
		
		if(peaknumremove)fCanvas1->GetCanvas()->GetListOfPrimitives()->Remove(peaknumremove);//Remove if its there else ignored
		peaknumremove=peaknum.DrawText(cent+shif,h->GetBinContent(h->FindBin(cent))*0.95,ss.str().c_str());

		fCanvas1->GetCanvas()->Modified();
		fCanvas1->GetCanvas()->Update();
	}
	
gPad=hold;
}

void jgating_tool::SavePanel(){
	if(IsVisible(saveframe)){
		HideFrame(saveframe);
	}else{
		ShowFrame(saveframe);
	}
	ShareMainPanels();
}

void jgating_tool::FitPanel(){
	if(fCheck0)if(fCheck0->GetState())return;
    
    if(!fFitPanel){
		fFitPanel=new UltraFitEnv(this,0,fCanvas1->GetCanvas(),2);
        AddFrame(fFitPanel,new TGLayoutHints(kLHintsExpandY, 1, 1, 1, 1));
        Resize(GetDefaultSize());
        HideFrame(fFitPanel);
    }
    
	if(IsVisible(fFitPanel)){
        ftbutton->SetState(kButtonUp);
        HideFrame(fFitPanel);
        fFitPanel->KillCan();
        DoUpdate();
    }else{
        ftbutton->SetState(kButtonDown);
        ShowFrame(fFitPanel);
        fFitPanel->ConnectNewCanvas(fCanvas1->GetCanvas());
	}
	ShareMainPanels();
}

void jgating_tool::jSaveAs(){
	TH1* h=hist_capture(fCanvas1->GetCanvas());
	if(!h)h=gJframe2->output_hist_point;
	HistSaveAs(h,this,fCanvas1->GetCanvas());
}

void jgating_tool::AddStoreHistogram(){
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


void jgating_tool::StoreHistograms(Int_t i){
	if(i%2){
		uint select=i/2;
	// 	cout<<endl<<endl<<i<<endl<<endl;
		if(select<savehists.size()){
			if(savehists[select]){delete savehists[select];}savehists[select]=0;

// 			savehists[select]=new TH1F();
// 			gJframe2->output_hist_point->Copy(*savehists[select]);
// 			savehists[select]->SetName(("savedhist"+make_iterator()).c_str());
			
			TH1* targ=gJframe2->output_hist_point;;
			if(fCheck0)if(fCheck0->GetState()) targ=gJframe1->output_hist_point;
			
			savehists[select]=(TH1*)targ->Clone(("savedhist"+make_iterator()).c_str());
			savehists[select]->GetListOfFunctions()->Clear();
			
			if(!savechecks[select]->IsEnabled())savechecks[select]->SetEnabled();
			
			stringstream ss;ss<<" "<<gJframe2->GateCentre<<" ";
			if(fCheck0)if(fCheck0->GetState()){ss.clear(); ss.str("");ss<<" "<<gJframe1->GateCentre<<" ";}
			
			savebutton[select]->SetText(ss.str().c_str());
            
            if(select==savebutton.size()-1)AddStoreHistogram();
		}
	}
}

void jgating_tool::DrawSaved(){
	TH1* saveadd=0;
	for(uint i=0;i<savehists.size();i++){
		if(savehists[i]&&savechecks[i]->GetState()==EButtonState::kButtonDown){
			if(saveadd){
				if(saveadd->GetNbinsX()==savehists[i]->GetNbinsX())
					saveadd->Add(savehists[i]);
			}else{
				saveadd=(TH1*)savehists[i]->Clone(("savedhist"+make_iterator()).c_str());
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

void jgating_tool::ClearSaved(){
	for(uint i=0;i<savehists.size();i++){
        if(savehists[i]){
            delete savehists[i];
            savehists[i]=0;
        }
    }
}


//Doesnt actually clear anything, you just cant select them
void jgating_tool::CSaveButton(){
    
    std::chrono::duration<double> diff= std::chrono::system_clock::now()-clicktime;
    if(abs(diff.count())<2){
        for(uint i=0;i<savehists.size();i++){
            savechecks[i]->SetState(kButtonUp);
            savechecks[i]->SetState(kButtonDisabled);
            savebutton[i]->SetText("[Empty]");
        }
        ClearSaved();
        
//         cout<<endl<<"Saved results cleared."<<endl;
    }else{
        cout<<"Click twice to clear."<<endl;
    }
    
    clicktime=std::chrono::system_clock::now();
}

void jgating_tool::NewAxisDrawn() //adjust sliders and control values for new axis
{
	if(fFitFcn&&fCanvas1->GetCanvas()->GetListOfPrimitives()->FindObject(peaknumremove)){
		
		TH1* h=hist_capture(fCanvas1->GetCanvas());
		if(!h)h=gJframe2->output_hist_point;
		double cent=fFitFcn->GetParameter(1);
		double shif=(h->GetXaxis()->GetBinCenter(h->GetXaxis()->GetLast())-h->GetXaxis()->GetBinCenter(h->GetXaxis()->GetFirst()))*0.05;
		peaknumremove->SetX(cent+shif);
		fCanvas1->GetCanvas()->Modified();
		fCanvas1->GetCanvas()->Update();
	}
	
	if(!RangeUpdateHold){
		TH1* h=hist_capture(fCanvas1->GetCanvas());
        if(h){
//             cout<<endl<<"GRABBING NEW RANGE"<<endl;
            TAxis* x=h->GetXaxis();
            x1=x->GetBinLowEdge(x->GetFirst());
            x2=x->GetBinUpEdge(x->GetLast());
            
            if(fCheck0){if(fCheck0->GetState()){
                TAxis* y=h->GetXaxis();
                y1=y->GetBinLowEdge(y->GetFirst());
                y2=y->GetBinUpEdge(y->GetLast());
            }}
        }
    }
	
}

#include <TGIcon.h>
TGTransientFrame* jgating_tool::MakeTH3Popup(){
    TGTransientFrame* popup=new TGTransientFrame(gClient->GetRoot(), gClient->GetRoot(), 400, 200, kHorizontalFrame);

//    fClient->GetPicture("mb_exclamation_s.xpm");
//    fClient->GetPicture("mb_asterisk_s.xpm");
    TGLayoutHints *fL1 = new TGLayoutHints(kLHintsCenterY | kLHintsExpandX, 5, 20, 0, 0);

    TGIcon *fIcon = new TGIcon(popup, fClient->GetPicture("mb_stop_s.xpm"),100, 100);
    popup->AddFrame(fIcon,new TGLayoutHints(kLHintsCenterY, 20, 15, 20, 20));

    TGVerticalFrame* fLabelFrame = new TGVerticalFrame(popup, 60, 20);
    popup->AddFrame(fLabelFrame,fL1);
   
    TGLabel *label1 = new TGLabel(fLabelFrame,"====================================================");
    TGLabel *label2 = new TGLabel(fLabelFrame,"============= Beginning Loading of TH3 =============");
    TGLabel *label3 = new TGLabel(fLabelFrame,"====== Please be patient until window appears ======");
    TGLabel *label4 = new TGLabel(fLabelFrame,"====================================================");
//        label->SetTextJustify(text_align);
    fLabelFrame->AddFrame(label1, fL1);    
    fLabelFrame->AddFrame(label2, fL1);    
    fLabelFrame->AddFrame(label3, fL1);    
    fLabelFrame->AddFrame(label4, fL1);    
        
    popup->SetWindowName("LOADING");

    popup->MapSubwindows();
    popup->Resize(popup->GetDefaultSize());
    popup->MapWindow();
    gClient->NeedRedraw(popup,kTRUE);

    int waitc=0;
    while(waitc<20){
        gSystem->ProcessEvents();//gSystem->InnerLoop();
        gSystem->Sleep(5);
        waitc++;
    // Little loop to buy Xsystem time to draw the box before code moves on
    }
//     gClient->WaitFor(popup);
        
// 	popup->Connect("CloseWindow()","TGTransientFrame",popup,"DontCallClose()");
    popup->DontCallClose();
    
//     CenterOnParent();// position relative to the parent's window
    
    return popup;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////  MINIMALIST TH3 SLICER  /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////



int minimalist_th3slice::minimalist_th3slice_iterator = 0;

//______________________________________________________________________________
minimalist_th3slice::minimalist_th3slice() : TGMainFrame(gClient->GetRoot(), 100, 100),slice(0),proj(0){this->initialise();}

minimalist_th3slice::minimalist_th3slice(TH3* input) : TGMainFrame(gClient->GetRoot(), 100, 100),slice(0),proj(0)
{
	this->initialise();
	*this=input;	
}

void minimalist_th3slice::initialise(){
	SetCleanup(kDeepCleanup);//Sets this MainFrame to clean all subframes
	
	iterator=make_iterator();
	
	xyz=3;
	bin=0;
		
	fHframe0 = new TGHorizontalFrame(this, 0, 0, 0);// Create a new horizontally alighed frame for some control widgets
		miniframe = new TGVerticalFrame(fHframe0, 0, 0, 0);

			fCanvas1 = new TRootEmbeddedCanvas(("Embedded"+make_iterator()).c_str(), miniframe, 600, 400);
			fCanvas1->GetCanvas()->SetName(("ResultCan"+make_iterator()).c_str());
			fCanvas1->GetCanvas()->SetBorderMode(0);
			fCanvas1->GetCanvas()->SetMargin(0.1,0.02,0.05,0.02);	
			fCanvas1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "minimalist_th3slice", this,"DoUpdate(Int_t,Int_t,Int_t,TObject*)");	

			fBgroup1 = new TGButtonGroup(miniframe,"Projection",kChildFrame);//create a group of buttons belonging (point) to the parent frame
			fRButton1 = new TGRadioButton(fBgroup1,new TGHotString("&X "));//create buttons belonging to the group
			fRButton2 = new TGRadioButton(fBgroup1,new TGHotString("&Y "));
			fRButton3 = new TGRadioButton(fBgroup1,new TGHotString("&Z"));
			fBgroup1->SetButton(xyz);//Set which is pressed
			fBgroup1->Show();//Display/Add all the buttons
			fBgroup1->Connect(" Clicked(Int_t)", "minimalist_th3slice", this,"ChangeProjection(Int_t)");//Link test signal to its    int gate_down,gate_up; (method fn) 
			
		miniframe1 = new TGVerticalFrame(fHframe0, 0, 0, 0);
			fCanvas2 = new TRootEmbeddedCanvas("Canvas2", miniframe1, 600, 400);
			fCanvas2->GetCanvas()->SetBorderMode(0);
			fCanvas2->GetCanvas()->SetMargin(0.1,0.1,0.05,0.02);	
			
			fCheck0 = new TGCheckButton(miniframe1,"Titles and Stats");
			fCheck0->SetState(kButtonUp);
			fCheck0->SetToolTipText("Titles and Stats");	
	
	//
	//	ADD ALL THE GUI COMPONETS TOGETHER
	//		
	
	//    //--- layout for the frame:
	TGLayoutHints* fLcan = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5, 5, 0, 0);
	TGLayoutHints* fBfly4 = new TGLayoutHints(kLHintsTop | kLHintsCenterX, 5, 5, 3, 3);
	// 

	// Add control widgets to their parent frames lists
			miniframe->AddFrame(fCanvas1, fLcan);
			miniframe->AddFrame(fBgroup1, fBfly4);
		fHframe0->AddFrame(miniframe, fLcan);
			miniframe1->AddFrame(fCanvas2, fLcan);
			miniframe1->AddFrame(fCheck0, fBfly4);
		fHframe0->AddFrame(miniframe1, fLcan);
	this->AddFrame(fHframe0, fLcan);
	// Add the control widget frames to the mainframe

	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();	
}

minimalist_th3slice& minimalist_th3slice::operator= (TH3* input){   
	
	raw_3d=input;
	while(raw_3d->GetXaxis()->GetNbins()>1000)raw_3d->RebinX();
	while(raw_3d->GetYaxis()->GetNbins()>1000)raw_3d->RebinY();
	while(raw_3d->GetZaxis()->GetNbins()>1000)raw_3d->RebinZ();

	bin=0;
	
	if(proj!=0)delete proj;
	if(slice!=0)delete slice;
	proj=0;
	slice=0;
		xyz=3;
		fBgroup1->SetButton(xyz);//Set which is pressed
		gClient->NeedRedraw(fBgroup1);
	ChangeProjection(xyz);
	
	return *this;
}
   
minimalist_th3slice& minimalist_th3slice::operator() (TH3* input){return *this=input;}

//______________________________________________________________________________
minimalist_th3slice::~minimalist_th3slice()
{
   raw_3d=0;
   if(proj!=0)delete proj;
   if(slice!=0)delete slice;
   Cleanup();
}

//______________________________________________________________________________

void minimalist_th3slice::ChangeProjection(Int_t in)
{TVirtualPad* hold=gPad;
	xyz=in;
	if(proj!=0){delete proj;proj=0;}
	if(slice!=0){delete slice;slice=0;}

	switch (xyz) { 
		case 1: proj=raw_3d->ProjectionX(("proj"+iterator).c_str(),1,raw_3d->GetYaxis()->GetNbins(),1,raw_3d->GetZaxis()->GetNbins());  break;
		case 2: proj=raw_3d->ProjectionY(("proj"+iterator).c_str(),1,raw_3d->GetXaxis()->GetNbins(),1,raw_3d->GetZaxis()->GetNbins());  break;
		default: proj=raw_3d->ProjectionZ(("proj"+iterator).c_str(),1,raw_3d->GetXaxis()->GetNbins(),1,raw_3d->GetYaxis()->GetNbins());  break;
	}	
			
	fCanvas1->GetCanvas()->cd();
	if(fCheck0->GetState())proj->SetTitle("");
	proj->Draw();
	fCanvas1->GetCanvas()->Modified();
	fCanvas1->GetCanvas()->Update();
	DoUpdate(0,0,0,fCanvas1->GetCanvas());
	
gPad=hold;
}


void minimalist_th3slice::DoUpdate(Int_t event, Int_t px, Int_t py, TObject *selected_ob)
{if(!proj)return;
TVirtualPad* hold=gPad;

	double x =fCanvas1->GetCanvas()->PixeltoX(px);
	int xtemp=proj->GetXaxis()->FindFixBin(x);
	if(xtemp!=bin && xtemp>0 && xtemp<proj->GetXaxis()->GetNbins()){
		bin=xtemp;
				
		switch (xyz) { 	
			case 1: raw_3d->GetXaxis()->SetRange(bin,bin);
				slice=(TH2*)raw_3d->Project3D("yz"); break;
			case 2: raw_3d->GetYaxis()->SetRange(bin,bin);
				slice=(TH2*)raw_3d->Project3D("xz"); break;
			default: raw_3d->GetZaxis()->SetRange(bin,bin);
				slice=(TH2*)raw_3d->Project3D("xy"); break;
		}

		raw_3d->GetXaxis()->SetRange();
		raw_3d->GetYaxis()->SetRange();
		raw_3d->GetZaxis()->SetRange();
		

		fCanvas2->GetCanvas()->cd();
		if(slice!=0){
			if(fCheck0->GetState()){					
				gStyle->SetOptStat(0);
				slice->SetTitle("");
			}else{			
				stringstream convert; 
				convert <<"Bin "<<bin<<" ("<<x<<")" ;
				gStyle->SetOptStat(1);
				slice->SetTitle(convert.str().c_str());
			}
			slice->Draw("colz");
		}
		fCanvas2->GetCanvas()->Modified();
		fCanvas2->GetCanvas()->Update();	
	}
	
gPad=hold;
}



string minimalist_th3slice::make_iterator(){
	stringstream ss;
	ss << minimalist_th3slice_iterator;
	minimalist_th3slice_iterator++;
	return ss.str();
}
