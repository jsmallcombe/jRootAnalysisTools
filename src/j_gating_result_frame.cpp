#include "j_gating_result_frame.h"
#include "j_gating_tool.h"

ClassImp(j_gating_result_frame);

//______________________________________________________________________________
j_gating_result_frame::j_gating_result_frame() : TGHorizontalFrame(gClient->GetRoot(), 100, 100){}

j_gating_result_frame::j_gating_result_frame(TGWindow * parent,  TH1** input, TH1** back, TH1** proj, bool threedee) : TGHorizontalFrame(parent, 100, 100),ThreeDee(threedee),fCheck0(0),fCheck1(0),fFitFcn(0),peaknumremove(0),fTip(0),fFitPanel(0)
{
	if(input==nullptr)return;
	if(back==nullptr)return;
	if(proj==nullptr)return;
	
	fInput=input;
	fBack=back;
	fProj=proj;
	
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
    spbutton->Connect("Clicked()","j_gating_result_frame",this,"SavePanel()");
    spbutton->SetToolTipText("Show Save Panel\n Open side-panel for holding gating results\n  in memory to enable on-the-fly summing.");
    
    saveframe= new TGVerticalFrame(this, 0, 0, 0); 
    TGTextButton* plushist = new TGTextButton(saveframe,"DrawSum");
    plushist->Connect("Clicked()","j_gating_result_frame",this,"DrawSaved()");
    plushist->SetToolTipText("Draw a sum of currently\n selected saved Histograms.");
    saveframe->AddFrame(plushist,ffSpeBuf);//
    
    plushist = new TGTextButton(saveframe,"DeleteAll");
    plushist->Connect("Clicked()","j_gating_result_frame",this,"CSaveButton()");
    plushist->SetToolTipText("Clear all locally saved\n gated histograms.");
    saveframe->AddFrame(plushist,ffSpeBuf);//
    
    TGLabel *label = new TGLabel(saveframe, "Saved Gated\n Histograms.\n Check box\n   to sum.");
    savebuttons = new TGButtonGroup(saveframe,15,2);
    savebuttons->Connect(" Clicked(Int_t)", "j_gating_result_frame", this,"StoreHistograms(Int_t)");//Link test signal to its	
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
    fBgroup1->Connect(" Clicked(Int_t)", "j_gating_result_frame", this,"ButtonGroupDoUpdate(Int_t)");
    
    if(ThreeDee){
        fCheck0 = new TGCheckButton(buttonframe,"2D ");
        fCheck0->SetState(kButtonUp);
        fCheck0->Connect(" Clicked()", "j_gating_result_frame", this,"DoCheckbox2D()");
        fCheck0->SetToolTipText("2D Only\n Do not perform the second axis subtraction.\n Instead view TH2 matrix results from the first.");
    }
	
	
	fCanvas1 = new TRootEmbeddedCanvas(jgating_tool::Iterator("Embedded"), resultframe, 600, 400);
    fCanvas1->GetCanvas()->SetName(jgating_tool::Iterator("ResultCan"));
    
    fCanvas1->GetCanvas()->SetFillColor(33);
    fCanvas1->GetCanvas()->SetBorderMode(0);
    fCanvas1->GetCanvas()->SetFrameFillColor(10);

    fCanvas1->GetCanvas()->SetMargin(0.01,0.005,0.08,0.005);	
    fCanvas1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "j_gating_result_frame", this,"ClickedFinalCanvas(Int_t,Int_t,Int_t,TObject*)");
    fCanvas1->GetCanvas()->Connect("RangeChanged()", "j_gating_result_frame", this, "NewAxisDrawn()");
	
	// rebin bar
    
    TGHorizontalFrame* rebinframe = new TGHorizontalFrame(resultframe, 0, 0, 0);
        TGLabel *reblabel = new TGLabel(rebinframe, "Binning ");
        rebinframe->AddFrame(reblabel,ffCenY);
        
        fHslider1 = new TGHSlider(rebinframe, 9, kSlider2);
        fHslider1->SetPosition(0);
        fHslider1->Connect("PositionChanged(Int_t)", "j_gating_result_frame", this, "DoUpdate()");
        rebinframe->AddFrame(fHslider1, ffExpandXpad);
        
        RebinText = new TGTextEntry(rebinframe, new TGTextBuffer(4));
        RebinText->SetDefaultSize(40,25);
        RebinText->SetAlignment(kTextCenterX);
        RebinText->SetEnabled(kFALSE);
        rebinframe->AddFrame(RebinText,ffCenY);
    
    ftbutton = new TGTextButton(buttonframe,"Fit Panel");
    ftbutton->Connect("Clicked()","j_gating_result_frame",this,"FitPanel()");
    ftbutton->SetToolTipText("Open Fit Tool\n Open an instance of J-fit panel,\n initially connected to result canvas.");

    TGTextButton* SAbutton = new TGTextButton(buttonframe,"SaveAs");
    SAbutton->Connect("Clicked()","j_gating_result_frame",this,"jSaveAs()");
    SAbutton->SetToolTipText("Save the currently drawn histogram.");
    
    fCheck1 = new TGCheckButton(buttonframe,"Hide Ers");
    fCheck1->SetState(kButtonDown);
    fCheck1->Connect(" Clicked()", "j_gating_result_frame", this,"DoUpdate()");
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

	//    // Set main frame name, map sub windows (buttons), initialize layout
	//    // algorithm via Resize() and map main frame
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
	
    HideFrame(saveframe);//Will be undone my parent frame, need to add a functional call to set it
    
gPad=hold;
}

j_gating_result_frame::~j_gating_result_frame()
{
	Cleanup(); 
}

void j_gating_result_frame::InputUpdated(){
	
}	

void j_gating_result_frame::AddStoreHistogram(){
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

