#include "j_gating_select_frame.h"
#include "j_gating_tool.h"

ClassImp(j_gating_select_frame);

//______________________________________________________________________________
j_gating_select_frame::j_gating_select_frame() : TGVerticalFrame(gClient->GetRoot(), 100, 100){}

j_gating_select_frame::j_gating_select_frame(TGWindow * parent, TH1* input,int ThreeDee) : TGVerticalFrame(parent, 100, 100),peaknumremove(0),set_for_3D(ThreeDee),RebinFactor(1),xyz(0)
{
TVirtualPad* hold=gPad;
	char buf[32];	//A buffer for processing text through to text boxes
	SetCleanup(kDeepCleanup);//Sets this MainFrame to clean all subframes
	
	
	//
	//	CONTROL VALUES
	//
	
	maxbin=1;
	background_mode=2;
	backfit_mode=2;
	target_bin=20;
	gate_down=19;gate_up=21;
	gate_range=3;
	fit_down=1;fit_up=39;
	backfrack=0.1;
	backfrackfrac=0.05;
	storef1=1;storef2=1;
	axis_down=0;axis_up=-1;
	m_back_down=1;m_back_up=20;
	back_down=1;back_up=-1;
	
	action_hold=false;
	
	//
	//	HISTOGRAMS AND TF1
	//

	fFitFcn = new TF1(jgating_tool::Iterator("quickgausmain"),"gaus(0)+pol2(3)",0,0);
    fFitFcn->SetLineColor(1);
    if(gGlobalNegativeDraw)fFitFcn->SetLineColor(3);
 
	raw_input=new TH1F();
	proj=new TH1F();
	selected=new TH1F();
	specback=new TH1F();
	b_man=new TH1F();
		
	//
	//	layout for the frame
	//
	
	
	//--- layout for the frame:
	TGLayoutHints* fLcan = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5, 5, 0, 0);
	fBly = new TGLayoutHints(kLHintsTop | kLHintsExpandX, 5, 3, 0, 0);
	TGLayoutHints* fBfly1 = new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 3, 3);
	TGLayoutHints* fBfly2 = new TGLayoutHints(kLHintsLeft | kLHintsCenterY,    0, 0, 0, 0);
	TGLayoutHints* fBfly3 = new TGLayoutHints(kLHintsBottom,    4,4, 4,4);
	TGLayoutHints* fBfly4 = new TGLayoutHints(kLHintsTop | kLHintsCenterX, 5, 5, 3, 3);
	TGLayoutHints* fBfly5 = new TGLayoutHints(kLHintsCenterX,    0, 0, 0, 0);

	

	fHframe0 = new TGHorizontalFrame(this, 0, 0, 0);  //create a frame, filled with objects horizontally

		fCheck2 = new TGCheckButton(fHframe0);// A tick box with hover text belonging to a parent frame
		fCheck2->SetState(kButtonDown);
		fCheck2->Connect("Clicked()","j_gating_select_frame",this,"TickClick()");//Link it signal to its slot
		fCheck2->SetToolTipText("Show Fit Centroid\n Hide/Show the centroid of the Gaussian\n fit used to calculate background fraction.");
		fHframe0->AddFrame(fCheck2, fBfly2);

		if(ThreeDee>1){
			TGButtonGroup* fBgroup1 = new TGButtonGroup(fHframe0,"Projection",kChildFrame);//create a group of buttons belonging (point) to the parent frame
			TGRadioButton* fRButton1 = new TGRadioButton(fBgroup1,"X ");//create buttons belonging to the group
			TGRadioButton* fRButton2 = new TGRadioButton(fBgroup1,"Y ");
			fRButton1->SetToolTipText("Change Gating Projection\n Switch which side of the matrix\n is used for gating. Also useful\n to reset when glitch occurs.");
			fRButton2->SetToolTipText("Change Gating Projection\n Switch which side of the matrix\n is used for gating. Also useful\n to reset when glitch occurs.");
			TGRadioButton* fRButton3;
			if(ThreeDee>2) fRButton3 = new TGRadioButton(fBgroup1,"Z");
			fRButton3->SetToolTipText("Change Gating Projection\n Switch which side of the matrix\n is used for gating. Also useful\n to reset when glitch occurs.");
			fRButton1->SetState(kButtonDown);//Set which is pressed
			fBgroup1->Show();//Display/Add all the buttons
			fBgroup1->Connect(" Clicked(Int_t)", "j_gating_select_frame", this,"ChangeProjection(Int_t)");
			fHframe0->AddFrame(fBgroup1, fBfly1);
		}
		
		
		fBgroup2 = new TGButtonGroup(fHframe0,"Subtraction Scheme",kChildFrame);// Another button group
			fRButton4 = new TGRadioButton(fBgroup2,"Full ");
			fRButton4->SetToolTipText("Full Projection\n Take the full projection of the matrix\n as the background spectrum.");
			fRButton5 = new TGRadioButton(fBgroup2,"Compton ");
			fRButton5->SetToolTipText("Compton Background\n Gate on entire spectrum (including overflow)\n above the gate to form a background spectrum.\n In manual mode a gap of 2 bins above the gate\n is left. In fit mode it begins at +2 sigma.");
			fRButton6 = new TGRadioButton(fBgroup2,"Anti ");
			fRButton6->SetToolTipText("Anti-gated Background\n The background spectrum is the full\n projection minus the gated spectrum.");
			fRButton9 = new TGRadioButton(fBgroup2,"None ");
			fRButton7 = new TGRadioButton(fBgroup2,"Man ");
			fRButton7->SetToolTipText("Manual Background\n Manually select a second gate to produce a background spectrum.\n An additional slider will be displayed.");
			fRButton8 = new TGRadioButton(fBgroup2,"ManRel");
			fRButton8->SetToolTipText("Relative Position Manual Background\n Manually select a second gate to produce a background spectrum.\n An additional slider will be displayed.\n This gate will move with the primary gate. Useful for scanning.");
		fRButton5->SetState(kButtonDown);
		background_mode=2;
		fBgroup2->Show();
		fBgroup2->Connect(" Clicked(Int_t)", "j_gating_select_frame", this,"ChangeBackMode(Int_t)");
		fHframe0->AddFrame(fBgroup2, fBfly1);
		
		TGButtonGroup* fBgroup3 = new TGButtonGroup(fHframe0,"Rebin",kChildFrame);// Another button group
            TGTextButton *RebinPlusButton=new TGTextButton(fBgroup3,"+");
            RebinPlusButton->Connect("Clicked()","j_gating_select_frame",this,"RebinPlus()");
            TGTextButton *RebinMinusButton=new TGTextButton(fBgroup3,"-");
            RebinMinusButton->Connect("Clicked()","j_gating_select_frame",this,"RebinMinus()");
		fBgroup3->Show();
		fHframe0->AddFrame(fBgroup3, fBfly1); 
		
		
	this->AddFrame(fHframe0, fBfly4);	
	
	// Create an embedded canvas and add to the main frame, centered in x and y
	// and with 30 pixel margins all around
	fCanvas1 = new TRootEmbeddedCanvas("Canvas1", this, 600, 500);
		fCanvas1->GetCanvas()->SetFillColor(33);
		fCanvas1->GetCanvas()->SetFrameFillColor(10);
		fCanvas1->GetCanvas()->SetMargin(0.01,0.005,0.08,0.005);
		//    fCanvas1->GetCanvas()->SetGrid();
			fCanvas1->GetCanvas()->Connect("RangeChanged()", "j_gating_select_frame", this, "ReDrawOne()");
			fCanvas1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "j_gating_select_frame", this,"ClickedCanvasOne(Int_t,Int_t,Int_t,TObject*)");
	this->AddFrame(fCanvas1, fLcan);
	
	TGLabel *sliderlabel = new TGLabel(this, "Gate Position and Fit Range");
	this->AddFrame(sliderlabel, fBfly5);	
	
	fHframe1 = new TGHorizontalFrame(this, 0, 0, 0);// Create a new horizontally alighed frame for some control widgets
	
		fTeh1 = new TGTextEntry(fHframe1, fTbh1 = new TGTextBuffer(4));//Create some text entry boxes 
		fTeh1->SetToolTipText("Gate Position");
		fTeh1->SetDefaultSize(50,25);
		fTeh1->SetAlignment (kTextRight);
		fTeh1->Connect("ReturnPressed()", "j_gating_select_frame", this,"DoText()");//So it doesnt continually do things while typing is occuring
		fTeh1->Connect("TabPressed()", "j_gating_select_frame", this,"DoText()");
		fHframe1->AddFrame(fTeh1, fBfly1);

		fHslider1 = new TGTripleHSlider(fHframe1, 190, kSlider1);//Create a control slider
			fHslider1->Connect("PointerPositionChanged()", "j_gating_select_frame", this, "DoSlidePoint()");//Link it signal to its slot (method fn) 
			fHslider1->Connect("PositionChanged()", "j_gating_select_frame", this, "DoSlider()");//Link it signal to its slot (method fn) 	
// 			fHslider1->SetRange(1,raw_2d->GetNbinsX()); //Assiagn default range
// 			fHslider1->SetPointerPosition(1); //set inital value
			fHslider1->SetConstrained(kFALSE);//The pointer can traverse the full range, not just the sub slider
			fHslider1->SetRelative(kFALSE);
			fHframe1->AddFrame(fHslider1, fBly);
	this->AddFrame(fHframe1, fBly);		
	
	fHframe2 = new TGHorizontalFrame(this);
		
		fTeh2 = new TGTextEntry(fHframe2, fTbh2 = new TGTextBuffer(5));
			fTeh2->SetToolTipText("Gate Width");
			fTeh2->SetDefaultSize(50,25);
			fTeh2->SetAlignment(kTextRight);
			// Set the data in the text buffer the text entry boxes are using
			sprintf(buf, "%.1f", proj->GetBinCenter(1));	fTbh1->AddText(0, buf);
			sprintf(buf, "%.1f", 5*(double)proj->GetBinWidth(1));	fTbh2->AddText(0, buf);
			
		fTeh2->Connect("ReturnPressed()", "j_gating_select_frame", this,"DoText()");
		fTeh2->Connect("TabPressed()", "j_gating_select_frame", this,"DoText()");
		
		fHframe2->AddFrame(fTeh2, fBfly1);

		TGVerticalFrame* minifvertrame = new TGVerticalFrame(fHframe2);
			sliderlabel = new TGLabel(minifvertrame, "Gate Width");
			minifvertrame->AddFrame(sliderlabel, fBfly5);
			
			fHslider2 = new TGHSlider(minifvertrame, 200, kSlider2);
			fHslider2->Connect("PositionChanged(Int_t)", "j_gating_select_frame", this, "DoSlider()");
			minifvertrame->AddFrame(fHslider2, fBly);
		fHframe2->AddFrame(minifvertrame, fBly);
		

	this->AddFrame(fHframe2, fBly);
	
	//Create some text entry boxes 
	fHframe3 = new TGHorizontalFrame(this, 0, 0, 0);

		fTeh3 = new TGTextEntry(fHframe3, fTbh3 = new TGTextBuffer(5));
			fTeh3->SetDefaultSize(50,25);
			fTeh3->SetAlignment (kTextRight);
			fTeh3->SetToolTipText("Background Fraction");
			sprintf(buf, "%.4f", backfrack);fTbh3->AddText(0, buf);
			fTeh3->Connect("ReturnPressed()", "j_gating_select_frame", this,"DoText()");
			fTeh3->Connect("TabPressed()", "j_gating_select_frame", this,"DoText()");
			fTeh3->SetEnabled(kFALSE); //The default is disabled
		fHframe3->AddFrame(fTeh3, fBfly1);

		
		minifvertrame = new TGVerticalFrame(fHframe3);
			sliderlabel = new TGLabel(minifvertrame, "Background Subtraction Fraction");
			fHslider3 = new TGHSlider(minifvertrame, 300, kSlider2);
				fHslider3->Connect("PositionChanged(Int_t)", "j_gating_select_frame", this, "DoSlider()");
				fHslider3->SetRange(0,10000);
				fHslider3->SetEnabled(kFALSE); //The default is disabled
			minifvertrame->AddFrame(sliderlabel, fBfly5);
			minifvertrame->AddFrame(fHslider3, fBly);
		fHframe3->AddFrame(minifvertrame, fBly);
		
		BackModeDrop=new TGComboBox(fHframe3);			
			BackModeDrop->AddEntry("Linear Fixed",1);
			BackModeDrop->AddEntry("Polynomial Flex",2);
			BackModeDrop->AddEntry("Manual",3);
			BackModeDrop->AddEntry("TSpectrum High",4);
			BackModeDrop->AddEntry("TSpectrum Medium",5);
			BackModeDrop->AddEntry("TSpectrum Low",6);
			BackModeDrop->Resize(150,20);
			BackModeDrop->Select(2);
			BackModeDrop->Connect(" Selected(Int_t)", "j_gating_select_frame", this,"ChangeBackFit(Int_t)");
		fHframe3->AddFrame(BackModeDrop, fBfly3);
		
	this->AddFrame(fHframe3, fBly);


	fHframe4 = new TGVerticalFrame(this, 0, 0, 0);// Create a new horizontally alighed frame for some control widgets
		sliderlabel = new TGLabel(fHframe4, "Manual Background Gate Position");
		fHslider4 = new TGDoubleHSlider(fHframe4, 190, kSlider1);//Create a control slider
			fHslider4->Connect("PositionChanged()", "j_gating_select_frame", this, "DoSlider()");
		fHframe4->AddFrame(sliderlabel, fBfly5);
		fHframe4->AddFrame(fHslider4, fBly);	
	this->AddFrame(fHframe4, fBly);	
		

	// create the tooltip with a timeout of 250 ms
	fTip = new TGToolTip(gClient->GetRoot(), fCanvas1, "", 250);

	//
	//	SEND INITIAL VALUES TO GUI
	//
	
	UpdateInput(input);

	//    // Set main frame name, map sub windows (buttons), initialize layout
	//    // algorithm via Resize() and map main frame
	//SetWindowName("j_gating_select_frame");
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
	
gPad=hold;
}

//______________________________________________________________________________

j_gating_select_frame::~j_gating_select_frame()
{
	fTip->Hide();
	delete fTip;
	
	delete raw_input;
	delete proj;
	delete selected;
	delete specback;
	delete fFitFcn;
	delete b_man;


	//Clean up	
	Cleanup(); 
}

//______________________________________________________________________________
// void j_gating_select_frame::CloseWindow()
// {
//    // Called when window is closed via the window manager.
// 
//    cout<<endl<<"MOOOOO"<<endl;
// 	delete this;
// }

void j_gating_select_frame::TickClick(){
	proj->GetXaxis()->SetRange(1,-1);
	UpdateCanvas();
}

//______________________________________________________________________________

void j_gating_select_frame::NewAxisDrawn() //adjust sliders and control values for new axis
{//cout<<"NewAxisDrawn "<<flush;
	axis_down=proj->GetXaxis()->GetFirst();
	axis_up=proj->GetXaxis()->GetLast();
	
	fHslider1->SetRange(axis_down,axis_up);	
	fHslider2->SetRange(1,(axis_up-axis_down));
	fHslider4->SetRange(axis_down-1,axis_up+1);	
    // Changed to allow selection of under/overflow
	
	ValidateValues();
	ValuesToSliders();
	ValuesToText();
		
	if(fFitFcn&&fCanvas1->GetCanvas()->GetListOfPrimitives()->FindObject(peaknumremove)){
		TH1* h=proj;
		double cent=fFitFcn->GetParameter(1);
		double shif=(h->GetXaxis()->GetBinCenter(h->GetXaxis()->GetLast())-h->GetXaxis()->GetBinCenter(h->GetXaxis()->GetFirst()))*0.05;
		peaknumremove->SetX(cent+shif);
		fCanvas1->GetCanvas()->Modified();
		fCanvas1->GetCanvas()->Update();
	}
}

//______________________________________________________________________________

void j_gating_select_frame::ValidateValues() //checks stored control parameters are valid
{//cout<<"ValidateValues "<<flush;
	if(target_bin<axis_down)target_bin=axis_down;
	if(target_bin>axis_up)target_bin=axis_up;
	
	//Find new gate values
	if(gate_range>(axis_up-axis_down)*2)gate_range=(axis_up-axis_down)*2;
	if(gate_range<1)gate_range=1;
		
	gate_down=target_bin-gate_range/2;
	gate_up=target_bin+gate_range/2;
	if(!(gate_range%2))gate_down++;
	
	if(gate_down>gate_up)gate_up=gate_down;
	if(gate_down<axis_down)gate_down=axis_down-1;
	if(gate_up>axis_up)gate_up=axis_up+1;
    // Changed to allow selection of under/overflow
	 	
	if(fit_down<axis_down)fit_down=axis_down;
	if(fit_down>gate_down)fit_down=gate_down;
	if(fit_up>axis_up)fit_up=axis_up;
	if(fit_up<gate_up)fit_up=gate_up;
	
	if(m_back_down<axis_down||m_back_down>axis_up)m_back_down=axis_down-1;
	if(m_back_up<axis_down||m_back_up>axis_up)m_back_up=axis_up+1;	
    // Changed to allow selection of under/overflow
	
	if(backfit_mode>2){//Not a peak fit
		fit_down=target_bin;
		fit_up=target_bin;
	}
		
	if(backfrack<0)backfrack=0.0;
	if(backfrack>1)backfrack=1.0;
}	 

//______________________________________________________________________________

void j_gating_select_frame::FetchSliderValues() //copy slider values to control parameters
{//cout<<"FetchSliderValues "<<flush;	
	target_bin=fHslider1->GetPointerPosition();
	gate_range=fHslider2->GetPosition();
	
// 	double over_speed=(double)gate_range/(double)(axis_up-axis_down);
// 	if(over_speed>0.25){
// 		gate_range=((over_speed-0.25)*35.0+0.25)*(axis_up-axis_down)+0.5;
// 	}

	if(backfit_mode==3){//manual background fraction mode
		backfrack=(double)fHslider3->GetPosition()/10000.0;
	}
	
	if(backfit_mode<3){//peal fitting mode
		fit_down=fHslider1->GetMinPosition();
		fit_up=fHslider1->GetMaxPosition();	
	}
	
	m_back_down=fHslider4->GetMinPosition();
	m_back_up=fHslider4->GetMaxPosition();	
	
}

//______________________________________________________________________________

void j_gating_select_frame::ValuesToSliders() //copy control parameters to sliders
{//cout<<"ValuesToSliders "<<flush;
	action_hold=true;
		fHslider1->SetPosition(fit_down,fit_up);
		fHslider1->SetPointerPosition((Double_t)target_bin);
		fHslider2->SetPosition(gate_range);		
// 			double over_speed=(double)gate_range/(double)(axis_up-axis_down);
// 			if(over_speed>0.25){
// 				fHslider2->SetPosition(((over_speed-0.25)*(1.0/35.0)+0.25)*(axis_up-axis_down)+0.5);
// 			}else{
// 				fHslider2->SetPosition(gate_range);
// 			}
		fHslider3->SetPosition(backfrack*10000);
		fHslider4->SetPosition(m_back_down,m_back_up);
	action_hold=false;
}

//______________________________________________________________________________

void j_gating_select_frame::FetchTextValues() //copy text values to control parameters
{//cout<<"FetchTextValues "<<flush;	
	target_bin=proj->GetXaxis()->FindFixBin(atof(fTbh1->GetString()));
	gate_range=atof(fTbh2->GetString())/proj->GetBinWidth(1);
	backfrack=atof(fTbh3->GetString());
}

//______________________________________________________________________________

void j_gating_select_frame::ValuesToText() //copy control parameters to text
{	char buf[32];
//cout<<"ValuesToText "<<flush;
	//update the text now the sliders have moved
	sprintf(buf, "%.1f", proj->GetBinCenter(target_bin));
	fTbh1->Clear();	fTbh1->AddText(0, buf);
	fTeh1->SetCursorPosition(fTeh1->GetCursorPosition());fTeh1->Deselect();
	gClient->NeedRedraw(fTeh1);
	
	sprintf(buf, "%.1f", (double)gate_range*(double)proj->GetBinWidth(1));
	fTbh2->Clear();	fTbh2->AddText(0, buf);
	fTeh2->SetCursorPosition(fTeh2->GetCursorPosition());	fTeh2->Deselect();
	gClient->NeedRedraw(fTeh2);

	sprintf(buf, "%.4f", backfrack);
	fTbh3->Clear();	fTbh3->AddText(0, buf);
	fTeh3->SetCursorPosition(fTeh3->GetCursorPosition());	fTeh3->Deselect();
	gClient->NeedRedraw(fTeh3);
		
}

//______________________________________________________________________________

void j_gating_select_frame::DoText() // Updates sliders to match text THEN calls DO HISTOGRAMS (which does everything else)
{//cout<<"DoText "<<flush;
	// Handle text entry widgets.

	int xtemp=fHslider1->GetPointerPosition();
	FetchTextValues();
	//stupid triple slider
	fit_down=target_bin+(fit_down-xtemp);
	fit_up=target_bin+(fit_up-xtemp);
	ValidateValues();
	ValuesToSliders();
	ValuesToText();
	DoAutoFit();
	UpdateCanvas();
	DoHistogram();
}

//______________________________________________________________________________

void j_gating_select_frame::DoSlidePoint() // Updates text to match sliders THEN calls DO HISTOGRAMS (which does everything else)
{
	if(!action_hold){//cout<<"DoSlidePoint "<<flush;
		action_hold=true;
		int xtemp=fHslider1->GetPointerPosition();
			fHslider1->SetPosition(xtemp+(fit_down-target_bin),xtemp+(fit_up-target_bin));
			
			if(background_mode==6){
				m_back_down+=xtemp-target_bin;
				m_back_up+=xtemp-target_bin;
				fHslider4->SetPosition(m_back_down,m_back_up);
			}
			
		action_hold=false;
		DoSlider();
	}
}

//______________________________________________________________________________
// Updates text to match sliders THEN calls DO HISTOGRAMS
// (which does everything else)
void j_gating_select_frame::DoSlider()
{	
	if(!action_hold){//cout<<"DoSlider "<<flush;
		FetchSliderValues();
		ValidateValues();
		ValuesToSliders();
		ValuesToText();
		DoAutoFit();
		UpdateCanvas();
		DoHistogram();//in the 3D version we dont update for slider slide
	}
}


//______________________________________________________________________________
void j_gating_select_frame::UpdateInput(TH1* input){
	if(!input)return;
//cout<<"boooom "<<flush;
	delete raw_input;
	raw_input=(TH1*)input->Clone(jgating_tool::Iterator("projraw"));
	maxbin=raw_input->GetNbinsX();
	UpdateInput();
}

//______________________________________________________________________________

// Basically redo everything.
// All histograms, drawing etc
// Calles for new input histogram or change axis
void j_gating_select_frame::UpdateInput()
{       
//     Emit("InputChange()"); // Not sure why this was at the start of Update function in original class, could cause issue
    
TVirtualPad* hold=gPad;

//cout<<"UpdateInput "<<flush;

	axis_down=0;axis_up=-1;
	
	delete proj;

	proj=(TH1*)raw_input->Clone(jgating_tool::Iterator("proje"));
	
	if(RebinFactor>1){
        proj->Rebin(RebinFactor);
    }
    
    axis_down=1;
	axis_up=proj->GetNbinsX();
	
	proj->SetStats(0);
	proj->SetTitle("");
	proj->SetLineColor(1);

	delete selected;
	selected=(TH1*)proj->Clone(jgating_tool::Iterator("selected"));
	selected->SetLineWidth(3);
	selected->SetLineColor(2);
	
	delete b_man;
	b_man=(TH1*)proj->Clone(jgating_tool::Iterator("b_man"));
	b_man->SetLineWidth(3);
	b_man->SetLineColor(1);
	
	UpdateSpecBack();
	DoAutoFit();
	UpdateDraw();
	DoHistogram();
gPad=hold;
    Emit("InputChange()");
}

//______________________________________________________________________________

//Make the 2 TSpectrum background histogram
void j_gating_select_frame::UpdateSpecBack(){
	delete specback;

	proj->GetXaxis()->SetRange(1,-1);//Doesnt seem to have any issues with NewAxisDrawn()
	if(backfit_mode==4)specback= TSpectrum::StaticBackground(proj,25);
	else if(backfit_mode==5)specback= TSpectrum::StaticBackground(proj,10);
	else specback=TSpectrum::StaticBackground(proj,30,"kBackOrder4");
	specback->SetLineColor(6);
	proj->GetXaxis()->SetRange(axis_down,axis_up);
}

//______________________________________________________________________________

// Change the way in which background historam is calcuated
// And recalculate
void j_gating_select_frame::ChangeBackMode(const Int_t id)
{       
//cout<<"ChangeBackMode "<<flush;
	background_mode=id;
	
	if(background_mode>4)ShowFrame(fHframe4);else HideFrame(fHframe4); 
	UpdateDraw();
	
	DoHistogram();
}

//______________________________________________________________________________

// Change the mode of background fraction calculation
// Then update the histograms etc
void j_gating_select_frame::ChangeBackFit(const Int_t id)
{
	if(backfit_mode<3&&id>2){//Switching away from a fitting mode
		storef1=fit_down-target_bin;storef2=fit_up-target_bin;
	}
	if(backfit_mode>2&&id<3){
		fit_down=storef1+target_bin;fit_up=storef2+target_bin;
	}
	
	bool doupdraw=(backfit_mode>3||id>3);//TSpectrum
	
	backfit_mode=id;
	
	if(backfit_mode==3){//manual mode
			fHslider3->SetEnabled(kTRUE);
			fTeh3->SetEnabled(kTRUE);
	}else{
			fHslider3->SetEnabled(kFALSE);
			fTeh3->SetEnabled(kFALSE);
	}
	
	if(backfit_mode>2){//manual or TSpectrum mode
		fFitFcn->SetParameters(0,0,0,0,0,0);
		fFitFcn->SetRange(0,0);
	}
	
	if(backfit_mode>3){//TSpectrum
		UpdateSpecBack();
	}
	
	DoAutoFit();
	
	if(doupdraw){//TSpectrum
		UpdateDraw();
	}else{   
		UpdateCanvas();
	}
	
	DoHistogram();
}


//______________________________________________________________________________

// Calculated the background fraction
// Either by fitting or TSpectrum intergral
// Does nothing when on manual mode
void j_gating_select_frame::DoAutoFit()
{  
	 if(backfit_mode==3)return;//manual mode
	 
	 double ingatecount=proj->Integral(gate_down,gate_up,"width");
	 double background=ingatecount;
	 
	 if(ingatecount<=0){//avoid empty fits
		backfrack=0;
		return;
	 }

	if(backfit_mode<3){//cout<<"DoAutoFit "<<flush;
				
// 			//Fit a gaus+pol1 where pol1 is constrained OR 	gaus+pol2	
			TF1* tempfn;
			if(backfit_mode==2)tempfn=QuickSingleGausAutoFitEE(proj,target_bin,fit_down,fit_up,1);
			else tempfn=QuickSingleGausAutoFit(proj,target_bin,fit_down,fit_up);			
			
			fFitFcn->SetParameters(tempfn->GetParameters());
			fFitFcn->SetRange(tempfn->GetXmin(),tempfn->GetXmax());
			delete  tempfn;
			//Fit is redundant, backfraction is from manually constrained linear background
			//Not really from fit at all
			
			//calc background frac from pol1
			double x0=proj->GetBinLowEdge(gate_down),x1=proj->GetBinLowEdge(gate_up+1);
			double m=fFitFcn->GetParameter(4),c=fFitFcn->GetParameter(3),d=fFitFcn->GetParameter(5);
			background=0.3333*d*x1*x1*x1+0.5*m*x1*x1+c*x1-0.3333*d*x0*x0*x0-0.5*m*x0*x0-c*x0;	
	}
	
	if(backfit_mode>3){
		background=specback->Integral(gate_down,gate_up,"width");
	}
	
	backfrack= background/ingatecount;	
	if(backfrack>1)backfrack=1;
	if(!(backfrack<=1&&backfrack>=0))backfrack=0;//guards against INF
	
	//Called to set calculated backfrack to gui
	ValuesToSliders();
	ValuesToText();
}
	

//______________________________________________________________________________

// Update all the currently drawn elements
// Histograms & peak text
// The call canvas update
// TF1 parameters should have already been set
void j_gating_select_frame::UpdateCanvas()
{       
//cout<<"UpdateCanvas "<<flush;

	b_man->GetXaxis()->SetRange(m_back_down,m_back_up);

	selected->GetXaxis()->SetRange(gate_down,gate_up);

	//New optional fit centroid text
	if(peaknumremove){fCanvas1->GetCanvas()->GetListOfPrimitives()->Remove(peaknumremove);}peaknumremove=0;
	if(fCheck2->GetState()&&backfit_mode<3){
		TVirtualPad* hold=gPad;
		fCanvas1->GetCanvas()->cd();
		
		TH1* h=proj;

		// Print the text on the canvas
		double cent=fFitFcn->GetParameter(1);
		stringstream ss;
		ss<<round(cent*10)/10;	
		
		TText peaknum;
		peaknum.SetTextAlign(22);
		peaknum.SetTextSize(0.04);
		
		double shif=(h->GetXaxis()->GetBinCenter(h->GetXaxis()->GetLast())-h->GetXaxis()->GetBinCenter(h->GetXaxis()->GetFirst()))*0.05;
		//GetXmin() doesnt account for zooming
		
		if(peaknumremove)fCanvas1->GetCanvas()->GetListOfPrimitives()->Remove(peaknumremove);//Removes if its there else ignored
		peaknumremove=peaknum.DrawText(cent+shif,h->GetBinContent(h->FindBin(cent))*0.95,ss.str().c_str());
		gPad=hold;
	}

	//update the already drawn histograms
	fCanvas1->GetCanvas()->Modified();
	fCanvas1->GetCanvas()->Update();
	
	//Update public number saying where gate is
	if(backfit_mode<3)GateCentre=round(fFitFcn->GetParameter(1)*10)/10.;	
	else if(proj)GateCentre=proj->GetBinCenter(target_bin);
}


//______________________________________________________________________________

// Called by canvas range change
// Either because drawing a new histogram or selecting axis
void j_gating_select_frame::ReDrawOne(){
	
	if(!action_hold){
	
		//cout<<"ReDrawOne "<<flush;
		// This function is called at the instant Canvas redraw is called
		// Canvas update will continue to run at the end of this function
		// Calling update from a subfunction causes nasty result so avoid it
		
		NewAxisDrawn();
		DoAutoFit();
		// When the axis was rescaled the draw range was reset
		b_man->GetXaxis()->SetRange(m_back_down,m_back_up);
		selected->GetXaxis()->SetRange(gate_down,gate_up);
	}
	
	//Cant call DoHistogram because it does an emit which transfers us to another draw canvas mid draw
	//DoHistogram();
}

//______________________________________________________________________________

// Function called by canvas interaction
// Mostly for moving the gate to double click position
void j_gating_select_frame::ClickedCanvasOne(Int_t event, Int_t px, Int_t py, TObject *selected_ob)
{   
	if (event == kMouseLeave){fTip->Hide(); return;}

	double x =fCanvas1->GetCanvas()->PixeltoX(px);
	
	//Update the tooltip
	fTip->Hide();
	fTip->SetText(TString::Format("%.1f",x));
	fTip->SetPosition(px+15, py-15);
	fTip->Reset();
	
//cout<<event<<endl;
	if ( event == kButton1Double) {//cout<<"ClickedCanvasOne "<<flush;
	//current is given in pixel coordinates
// 		//make sure we arent clicking in the borders
// 		if(x>proj->GetXaxis()->GetXmin()&&x<proj->GetXaxis()->GetXmax()){

			int xtemp=target_bin;
			//data are in bin number not real coordinates
			target_bin=proj->GetXaxis()->FindFixBin(x);

			fit_down=target_bin+(fit_down-xtemp);
			fit_up=target_bin+(fit_up-xtemp);
			
			ValidateValues();//this appears twice to calc new gate value			
			int g=m_back_up-m_back_down;
			m_back_down=gate_up+1;
			m_back_up=m_back_down+g;
	
			ValidateValues();			
			ValuesToSliders();
			ValuesToText();
			DoAutoFit();
			UpdateCanvas();
			DoHistogram();
// 		}
	}
}

//______________________________________________________________________________

// Do the gating on the matrix and produce the output channel information
void j_gating_select_frame::DoHistogram(){
	
	//Rough error on background fraction
	if(backfit_mode==3)//If its manual increase it
		backfrackfrac=0.08;
	else
		backfrackfrac=0.04;
	
	SubtractGateFromBack=false;

    // Note the "Full" projection used to make full and anti includes the overflow but excludes the underflow bin
    // This is an intentional choice as often intentionally zeroed data may be sorted into the underflow bin
    // The underflow bin can be selected with manual sliders
	switch (background_mode) {
		case 1://full
			back_down=1;
			back_up=proj->GetNbinsX()+1; //include overflow
			break;
		case 2://compton
			//set the compton background cut to 3sigma above centroid
			{
				int compton_offset=gate_up+2;
				if(backfit_mode<3){
					compton_offset=proj->GetXaxis()->FindFixBin(fFitFcn->GetParameter(1)+3*fFitFcn->GetParameter(2));
					if(compton_offset<gate_up)compton_offset=gate_up+2;
				}
				if(compton_offset>proj->GetNbinsX())compton_offset=proj->GetNbinsX();
					
				back_down=compton_offset;
				back_up=proj->GetNbinsX()+1; //include overflow
			}
			break;
		case 3://anti gate
			back_down=1;
			back_up=proj->GetNbinsX()+1; //include overflow
			SubtractGateFromBack=true;
			break;
		case 4://none
			back_down=0;
			back_up=-1;
			break;
		default://manual
			back_down=m_back_down;
			back_up=m_back_up;
			if(gate_down>m_back_down&&gate_up<m_back_up){
				SubtractGateFromBack=true;
			}
			break;				
	}

	Emit("OutputReady()");
}

//______________________________________________________________________________

// Draw histograms & canvas to the pad
// these may be updated without redraw
void j_gating_select_frame::UpdateDraw(bool overlay){
	TVirtualPad* hold=gPad;
	fCanvas1->GetCanvas()->cd();
    
    DrawHistOpt(proj,true,false,overlay);
    if(backfit_mode>3)DrawHistOpt(specback,true,false,true);
    if(background_mode>4)DrawHistOpt(b_man,true,false,true);
    DrawHistOpt(selected,true,false,true);
	fFitFcn->Draw("same");
	UpdateCanvas();
	gPad=hold;
}


void j_gating_select_frame::RebinPlus(){
    RebinFactor++;
	UpdateInput();	
}

void j_gating_select_frame::RebinMinus(){
    if(RebinFactor>1){
        RebinFactor--;
        UpdateInput();
    }
}

void j_gating_select_frame::ChangeProjection(const Int_t id)
{  
	xyz=id-1;
    Emit("RequestProjection(Int_t)",&xyz);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

ClassImp(j_gating_select_frame_tester);

// // // class j_gating_select_frame_tester : public TGMainFrame {
// // // 	
// // // 	private:
// // // 		TH1* testhist;
// // // 		j_gating_select_frame frame;
// // // 	public:
// // // 	j_gating_select_frame_tester();
// // // 	j_gating_select_frame_tester(TH1* input=nullptr, bool ThreeDee=false);
// // // 	
// // // 	
// // //    void OutputTest();
// // // 	
// // // 	ClassDef(j_gating_select_frame_tester, 1)
// // // }


j_gating_select_frame_tester::j_gating_select_frame_tester(TH1* input,int ThreeDee) : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame){
TVirtualPad* hold=gPad;

	if(!input){
        return;
    }
    testhist=input;
    
    SetCleanup(kDeepCleanup);	
    
	jgsframe = new  j_gating_select_frame(this, testhist,ThreeDee);

    TGLayoutHints* ffExpand = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0);
    AddFrame(jgsframe, ffExpand);
	
	jgsframe->Connect("RequestProjection(Int_t)","j_gating_select_frame_tester",this,"OutputTest()");
	jgsframe->Connect("OutputReady()","j_gating_select_frame_tester",this,"OutputTest()");
	
    MapSubwindows();
    Resize(GetDefaultSize());
    MapWindow();
	
gPad=hold;
}
void j_gating_select_frame_tester::OutputTest(){
	cout<<endl;
	cout<<endl<<jgsframe->GetGateBinDown();
	cout<<endl<<jgsframe->GetGateBinUp();
	cout<<endl<<jgsframe->GetBackBinDown();
	cout<<endl<<jgsframe->GetBackBinUp();
	cout<<endl<<jgsframe->GetBackFrac();
	cout<<endl<<jgsframe->SubtractGate();
	cout<<endl;
}
