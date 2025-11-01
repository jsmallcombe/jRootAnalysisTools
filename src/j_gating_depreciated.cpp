#include "j_gating_depreciated.h"

TAxis* hist_gater(TH3* in,string& pro,int xyz){
	switch (xyz) { 
		case 0: pro="yz"; return in->GetXaxis();  break;
		case 1: pro="xz"; return in->GetYaxis();  break;
		default: pro="xy"; return in->GetZaxis();  break;
	}
}

TAxis* hist_proj(TH3* in,string& pro,int xyz){
	switch (xyz) { 
		case 0: pro="x"; return in->GetXaxis();  break;
		case 1: pro="y"; return in->GetYaxis();  break;
		default: pro="z"; return in->GetZaxis();  break;
	}
}

	//	
	// 3D gating functions
	//

TH2* hist_gater(double lower,double upper,TH3* in,int xyz,string name){
	string is;TAxis *ax=hist_gater(in,is,xyz); TH3axisreseter(in);
	ax->SetRangeUser(lower,upper);
	TH2* ret=(TH2*)in->Project3D(is.c_str());
	if(name!="")ret->SetName(name.c_str());
	return ret;
}

TH2* hist_gater_bin(int lower,int upper,TH3* in,int xyz,string name){
	string is;TAxis *ax=hist_gater(in,is,xyz); TH3axisreseter(in);
	ax->SetRange(lower,upper);
	TH2* ret=(TH2*)in->Project3D(is.c_str());
	if(name!="")ret->SetName(name.c_str());
	return ret;
}

TH2* hist_gater(double lower,TH3* in,int xyz,string name){
	string is;TAxis *ax=hist_gater(in,is,xyz); TH3axisreseter(in);
	ax->SetRange(ax->FindFixBin(lower),ax->GetNbins()+1);
	TH2* ret=(TH2*)in->Project3D(is.c_str());
	if(name!="")ret->SetName(name.c_str());
	return ret;
}

TH2* hist_gater_bin(int lower,TH3* in,int xyz,string name){
	string is;TAxis *ax=hist_gater(in,is,xyz); TH3axisreseter(in);
	ax->SetRange(lower,ax->GetNbins()+1);
	TH2* ret=(TH2*)in->Project3D(is.c_str());
	if(name!="")ret->SetName(name.c_str());
	return ret;
}


 //NOTE 1: The generated histogram is named th3name + option


	//
	//2D gating functions
	//
	
TH1* hist_gater(double lower,double upper,TH2* in,int xyz,string name){
	if(xyz==1) return (TH1*)in->ProjectionX(name.c_str(),in->GetYaxis()->FindFixBin(lower),in->GetYaxis()->FindFixBin(upper));
	else  return (TH1*)in->ProjectionY(name.c_str(),in->GetXaxis()->FindFixBin(lower),in->GetXaxis()->FindFixBin(upper));
}
TH1* hist_gater_bin(int lower,int upper,TH2* in,int xyz,string name){
	if(xyz==1) return (TH1*)in->ProjectionX(name.c_str(),lower,upper);
	else  return (TH1*)in->ProjectionY(name.c_str(),lower,upper);
}
TH1* hist_gater(double lower,TH2* in,int xyz,string name){
	if(xyz==1) return (TH1*)in->ProjectionX(name.c_str(),in->GetYaxis()->FindFixBin(lower),in->GetYaxis()->GetNbins()+1);
	else  return (TH1*)in->ProjectionY(name.c_str(),in->GetXaxis()->FindFixBin(lower),in->GetXaxis()->GetNbins()+1);
}
TH1* hist_gater_bin(int lower,TH2* in,int xyz,string name){
	if(xyz==1) return (TH1*)in->ProjectionX(name.c_str(),lower,in->GetYaxis()->GetNbins()+1);
	else  return (TH1*)in->ProjectionY(name.c_str(),lower,in->GetXaxis()->GetNbins()+1);
}


///////

TH1* hist_gater(double a,double b,TH1* c,int d,string e){
	if(c->IsA()->InheritsFrom(TH3::Class()))return hist_gater(a,b,(TH3*)c,d,e);
	if(c->IsA()->InheritsFrom(TH2::Class()))return hist_gater(a,b,(TH2*)c,d,e);
	return 0;
}
TH1* hist_gater_bin(int a,int b,TH1* c,int d,string e){
	if(c->IsA()->InheritsFrom(TH3::Class()))return hist_gater_bin(a,b,(TH3*)c,d,e);
	if(c->IsA()->InheritsFrom(TH2::Class()))return hist_gater_bin(a,b,(TH2*)c,d,e);
	return 0;
}
TH1* hist_gater(double a,TH1* c,int d,string e){
	if(c->IsA()->InheritsFrom(TH3::Class()))return hist_gater(a,(TH3*)c,d,e);
	if(c->IsA()->InheritsFrom(TH2::Class()))return hist_gater(a,(TH2*)c,d,e);
	return 0;
}
TH1* hist_gater_bin(int a,TH1* c,int d,string e){
	if(c->IsA()->InheritsFrom(TH3::Class()))return hist_gater_bin(a,(TH3*)c,d,e);
	if(c->IsA()->InheritsFrom(TH2::Class()))return hist_gater_bin(a,(TH2*)c,d,e);
	return 0;
}

	//
	// Projection functions
	//

TH1* hist_proj(TH1* input,int xyz,string name,bool flowless){
	if(input->IsA()->InheritsFrom(TH3::Class())){
		TH3* in=(TH3*)input;
		if(flowless){
			switch (xyz) { 
				case 0: return (TH1*)in->ProjectionX(name.c_str(),1,in->GetYaxis()->GetNbins(),1,in->GetZaxis()->GetNbins());  break;
				case 1: return (TH1*)in->ProjectionY(name.c_str(),1,in->GetXaxis()->GetNbins(),1,in->GetZaxis()->GetNbins());  break;
				default: return (TH1*)in->ProjectionZ(name.c_str(),1,in->GetXaxis()->GetNbins(),1,in->GetYaxis()->GetNbins());  break;
			}			
		}else{
			switch (xyz) { 
				case 0: return (TH1*)in->ProjectionX(name.c_str());  break;
				case 1: return (TH1*)in->ProjectionY(name.c_str());  break;
				default: return (TH1*)in->ProjectionZ(name.c_str());  break;
			}			
		}
	}
	if(input->IsA()->InheritsFrom(TH2::Class())){
		TH2* in=(TH2*)input;
		if(flowless){
			if(xyz==0)return (TH1*)in->ProjectionX(name.c_str(),1,in->GetYaxis()->GetNbins());
			else return (TH1*)in->ProjectionY(name.c_str(),1,in->GetXaxis()->GetNbins());			
		}else{
			if(xyz==0)return (TH1*)in->ProjectionX(name.c_str());
			else return (TH1*)in->ProjectionY(name.c_str());			
		}
	}	
	return 0;	
}


	//
	//subtraction functions
	//
TH1* scaled_back_subtract(TH1* gate,TH1* back ,double backfrack,double uncertainfrac,bool scale){
	TH1* pass=(TH1*)gate->Clone();
	return scaled_back_subtract(gate,back ,backfrack,pass,uncertainfrac,scale);
}

TH1* scaled_back_subtract(TH1* gate,TH1* back ,double backfrack,TH1* pass,double uncertainfrac,bool scale){
    
    if(scale){
        double backcount=back->Integral();
        double forecount=gate->Integral();
        backfrack*=forecount/backcount;
    }
	
	if(!back->GetSumw2N())back->Sumw2();
	if(!gate->GetSumw2N())gate->Sumw2();
	
	pass->Add(gate,back,1.0,-backfrack);
	
	if(uncertainfrac){static_cast< TH1ErrorAdj* > (pass)->AdjustError(back,backfrack*uncertainfrac);}
	return pass;
}

//Doing it this way allows direct access to BinErrorSq so saves on wasteful squaring and rooting
void TH1ErrorAdj::AdjustError(const TH1* back,double frac){
	if(!fSumw2.fN)Sumw2();
	double v;
	for (Int_t bin = 0; bin < fNcells; ++bin) {
		v=back->GetBinContent(bin);
		fSumw2.fArray[bin] += v*v*frac*frac;
	}
}


void TH3axisreseter(TH3* hist){
	hist->GetXaxis()->SetRange();
	hist->GetYaxis()->SetRange();
	hist->GetZaxis()->SetRange();
}




//______________________________________________________________________________
j_gating_frame::j_gating_frame() : TGVerticalFrame(gClient->GetRoot(), 100, 100){}

j_gating_frame::j_gating_frame(TGWindow * parent, TH1* input,string suffin) : TGVerticalFrame(parent, 100, 100),peaknumremove(0)
{
TVirtualPad* hold=gPad;
	char buf[32];	//A buffer for processing text through to text boxes
	SetCleanup(kDeepCleanup);//Sets this MainFrame to clean all subframes
	
	set_for_3D=input->IsA()->InheritsFrom(TH3::Class());
	
	suffix=suffin;

	//
	//	CONTROL VALUES
	//
	
	
	hidebinerrors=false;
	background_mode=2;
	backfit_mode=2;
	xyz=0;
	target_bin=20;
	gate_down=19;gate_up=21;
	gate_range=3;
	fit_down=1;fit_up=39;
	backfrack=0.1;
	backfrackfrac=0.05;
	storef1=1;storef2=1;
	axis_down=0;axis_up=-1;
	m_back_down=1;m_back_up=20;
    RebinFactor=1;
	
	action_hold=false;
	
	//
	//	HISTOGRAMS AND TF1
	//

	fFitFcn = new TF1(("quickgausmain"+suffix).c_str(),"gaus(0)+pol2(3)",0,0);
    fFitFcn->SetLineColor(1);
    if(gGlobalNegativeDraw)fFitFcn->SetLineColor(3);
 
	projraw=new TH1F();
	proj_flowraw=new TH1F();
	proj=new TH1F();
	proj_flow=new TH1F();
	selected=new TH1F();
	specback=new TH1F();
	full=new TH1F();
	b_man=new TH1F();
	output_hist_point=new TH1F();
	gate_hist=new TH1F();
	free_hist=new TH1F();
		
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
		fRButtonz = new TGRadioButton(fHframe0);//create buttons belonging to the group		
		fRButtonz->Connect(" Pressed()", "j_gating_frame", this,"ShowFullProj()");
		fRButtonz->Connect(" Released()", "j_gating_frame", this,"HideFullProj()");
		fRButtonz->SetToolTipText("Show Full Projection\n Hold this button down to temporarily\n view the full projection of the matrix\n INCLUDING over/underflow of other axis.");
		fHframe0->AddFrame(fRButtonz, fBfly2);
	
		fCheck2 = new TGCheckButton(fHframe0);// A tick box with hover text belonging to a parent frame
		fCheck2->SetState(kButtonDown);
		fCheck2->Connect("Clicked()","j_gating_frame",this,"TickClick()");//Link it signal to its slot
		fCheck2->SetToolTipText("Show Fit Centroid\n Reset X-Zoom and Hide/Show centroid of fit used to calculate background.");
		fHframe0->AddFrame(fCheck2, fBfly2);

		fBgroup1 = new TGButtonGroup(fHframe0,"Projection",kChildFrame);//create a group of buttons belonging (point) to the parent frame
			fRButton1 = new TGRadioButton(fBgroup1,"X ");//create buttons belonging to the group
			fRButton2 = new TGRadioButton(fBgroup1,"Y ");
			fRButton1->SetToolTipText("Change Gating Projection\n Switch which side of the matrix\n is used for gating. Also useful\n to reset when glitch occurs.");
			fRButton2->SetToolTipText("Change Gating Projection\n Switch which side of the matrix\n is used for gating. Also useful\n to reset when glitch occurs.");
			if(set_for_3D)fRButton3 = new TGRadioButton(fBgroup1,"Z");
		fRButton1->SetState(kButtonDown);//Set which is pressed
		fBgroup1->Show();//Display/Add all the buttons
		fBgroup1->Connect(" Clicked(Int_t)", "j_gating_frame", this,"ChangeProjection(Int_t)");//Link test signal to its    int gate_down,gate_up; (method fn) 
		fHframe0->AddFrame(fBgroup1, fBfly1);

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
		fBgroup2->Connect(" Clicked(Int_t)", "j_gating_frame", this,"ChangeBackMode(Int_t)");
		fHframe0->AddFrame(fBgroup2, fBfly1);
		
		fBgroup3 = new TGButtonGroup(fHframe0,"Rebin",kChildFrame);// Another button group
            TGTextButton *RebinPlusButton=new TGTextButton(fBgroup3,"+");
            RebinPlusButton->Connect("Clicked()","j_gating_frame",this,"RebinPlus()");
            TGTextButton *RebinMinusButton=new TGTextButton(fBgroup3,"-");
            RebinMinusButton->Connect("Clicked()","j_gating_frame",this,"RebinMinus()");
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
			fCanvas1->GetCanvas()->Connect("RangeChanged()", "j_gating_frame", this, "ReDrawOne()");
			fCanvas1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "j_gating_frame", this,"ClickedCanvasOne(Int_t,Int_t,Int_t,TObject*)");
	this->AddFrame(fCanvas1, fLcan);
	
	TGLabel *sliderlabel = new TGLabel(this, "Gate Position and Fit Range");
	this->AddFrame(sliderlabel, fBfly5);	
	
	fHframe1 = new TGHorizontalFrame(this, 0, 0, 0);// Create a new horizontally alighed frame for some control widgets
		if(set_for_3D){
			fTButton1 = new TGTextButton(fHframe1,"&Update",HCId2);
			fTButton1->Connect("Clicked()","j_gating_frame",this,"DoHistogram()");
			fTButton1->SetToolTipText("Update Gate Result\n For TH3s the first gate is only applied\n when this button is clicked or when\n the suppression scheme is changed");
			fHframe1->AddFrame(fTButton1, fBfly2);
		}
		
		fTeh1 = new TGTextEntry(fHframe1, fTbh1 = new TGTextBuffer(4), HId1);//Create some text entry boxes 
		fTeh1->SetToolTipText("Gate Position");
		fTeh1->SetDefaultSize(50,25);
		fTeh1->SetAlignment (kTextRight);
		fTeh1->Connect("ReturnPressed()", "j_gating_frame", this,"DoText()");//So it doesnt continually do things while typing is occuring
		fTeh1->Connect("TabPressed()", "j_gating_frame", this,"DoText()");
		fHframe1->AddFrame(fTeh1, fBfly1);

		fHslider1 = new TGTripleHSlider(fHframe1, 190, kSlider1, HSId1);//Create a control slider
			fHslider1->Connect("PointerPositionChanged()", "j_gating_frame", this, "DoSlidePoint()");//Link it signal to its slot (method fn) 
			fHslider1->Connect("PositionChanged()", "j_gating_frame", this, "DoSlider()");//Link it signal to its slot (method fn) 	
			fHslider1->Connect("Released()", "j_gating_frame", this, "SliderRelease()");
// 			fHslider1->SetRange(1,raw_2d->GetNbinsX()); //Assiagn default range
// 			fHslider1->SetPointerPosition(1); //set inital value
			fHslider1->SetConstrained(kFALSE);//The pointer can traverse the full range, not just the sub slider
			fHslider1->SetRelative(kFALSE);
			fHframe1->AddFrame(fHslider1, fBly);
	this->AddFrame(fHframe1, fBly);		
	
	fHframe2 = new TGHorizontalFrame(this);
		
		fTeh2 = new TGTextEntry(fHframe2, fTbh2 = new TGTextBuffer(5), HId2);
			fTeh2->SetToolTipText("Gate Width");
			fTeh2->SetDefaultSize(50,25);
			fTeh2->SetAlignment(kTextRight);
			// Set the data in the text buffer the text entry boxes are using
			snprintf(buf, sizeof(buf),"%.1f", proj->GetBinCenter(1));	fTbh1->AddText(0, buf);
			snprintf(buf, sizeof(buf),"%.1f", 5*(double)proj->GetBinWidth(1));	fTbh2->AddText(0, buf);
			
		fTeh2->Connect("ReturnPressed()", "j_gating_frame", this,"DoText()");
		fTeh2->Connect("TabPressed()", "j_gating_frame", this,"DoText()");
		
		fHframe2->AddFrame(fTeh2, fBfly1);

		TGVerticalFrame* minifvertrame = new TGVerticalFrame(fHframe2);
			sliderlabel = new TGLabel(minifvertrame, "Gate Width");
			minifvertrame->AddFrame(sliderlabel, fBfly5);
			
			fHslider2 = new TGHSlider(minifvertrame, 200, kSlider2, HSId2);
			fHslider2->Connect("PositionChanged(Int_t)", "j_gating_frame", this, "DoSlider()");
			fHslider2->Connect("Released()", "j_gating_frame", this, "SliderRelease()");
			minifvertrame->AddFrame(fHslider2, fBly);
		fHframe2->AddFrame(minifvertrame, fBly);
		

	this->AddFrame(fHframe2, fBly);
	
	//Create some text entry boxes 
	fHframe3 = new TGHorizontalFrame(this, 0, 0, 0);

		fTeh3 = new TGTextEntry(fHframe3, fTbh3 = new TGTextBuffer(5), HId3);
			fTeh3->SetDefaultSize(50,25);
			fTeh3->SetAlignment (kTextRight);
			fTeh3->SetToolTipText("Background Fraction");
			snprintf(buf, sizeof(buf),"%.4f", backfrack);fTbh3->AddText(0, buf);
			fTeh3->Connect("ReturnPressed()", "j_gating_frame", this,"DoText()");
			fTeh3->Connect("TabPressed()", "j_gating_frame", this,"DoText()");
			fTeh3->SetEnabled(kFALSE); //The default is disabled
		fHframe3->AddFrame(fTeh3, fBfly1);

		
		minifvertrame = new TGVerticalFrame(fHframe3);
			sliderlabel = new TGLabel(minifvertrame, "Background Subtraction Fraction");
			fHslider3 = new TGHSlider(minifvertrame, 300, kSlider2, HSId3);
				fHslider3->Connect("PositionChanged(Int_t)", "j_gating_frame", this, "DoSlider()");
				fHslider3->Connect("Released()", "j_gating_frame", this, "SliderRelease()");
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
			BackModeDrop->Connect(" Selected(Int_t)", "j_gating_frame", this,"ChangeBackFit(Int_t)");
		fHframe3->AddFrame(BackModeDrop, fBfly3);
		
	this->AddFrame(fHframe3, fBly);


	fHframe4 = new TGVerticalFrame(this, 0, 0, 0);// Create a new horizontally alighed frame for some control widgets
		sliderlabel = new TGLabel(fHframe4, "Manual Background Gate Position");
		fHslider4 = new TGDoubleHSlider(fHframe4, 190, kSlider1, HSId4);//Create a control slider
			fHslider4->Connect("PositionChanged()", "j_gating_frame", this, "DoSlider()");
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
	//SetWindowName("j_gating_frame");
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
	
gPad=hold;
}

//______________________________________________________________________________

j_gating_frame::~j_gating_frame()
{
	fTip->Hide();
	delete fTip;
	
	delete proj;
	delete proj_flow;
	delete projraw;
	delete proj_flowraw;
	delete selected;
	delete specback;
	delete fFitFcn;
	delete full;
	delete b_man;
	delete output_hist_point;
	delete gate_hist;
	delete free_hist;

	//Clean up	
	Cleanup(); 
}

//______________________________________________________________________________
// void j_gating_frame::CloseWindow()
// {
//    // Called when window is closed via the window manager.
// 
//    cout<<endl<<"MOOOOO"<<endl;
// 	delete this;
// }


void j_gating_frame::TickClick(){
	proj->GetXaxis()->SetRange(1,-1);
	UpdateCanvas();
}

//______________________________________________________________________________

void j_gating_frame::NewAxisDrawn() //adjust sliders and control values for new axis
{//cout<<"NewAxisDrawn "<<flush;
	axis_down=proj->GetXaxis()->GetFirst();
	axis_up=proj->GetXaxis()->GetLast();
	
	fHslider1->SetRange(axis_down,axis_up);	
	fHslider2->SetRange(1,(axis_up-axis_down));
// 	fHslider2->SetRange(1,(axis_up-axis_down)*0.3);
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

void j_gating_frame::ValidateValues() //checks stored control parameters are valid
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

void j_gating_frame::FetchSliderValues() //copy slider values to control parameters
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

void j_gating_frame::ValuesToSliders() //copy control parameters to sliders
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

void j_gating_frame::FetchTextValues() //copy text values to control parameters
{//cout<<"FetchTextValues "<<flush;	
	target_bin=proj->GetXaxis()->FindFixBin(atof(fTbh1->GetString()));
	gate_range=atof(fTbh2->GetString())/proj->GetBinWidth(1);
	backfrack=atof(fTbh3->GetString());
}

//______________________________________________________________________________

void j_gating_frame::ValuesToText() //copy control parameters to text
{	char buf[32];
//cout<<"ValuesToText "<<flush;
	//update the text now the sliders have moved
	snprintf(buf, sizeof(buf),"%.1f", proj->GetBinCenter(target_bin));
	fTbh1->Clear();	fTbh1->AddText(0, buf);
	fTeh1->SetCursorPosition(fTeh1->GetCursorPosition());fTeh1->Deselect();
	gClient->NeedRedraw(fTeh1);
	
	snprintf(buf, sizeof(buf),"%.1f", (double)gate_range*(double)proj->GetBinWidth(1));
	fTbh2->Clear();	fTbh2->AddText(0, buf);
	fTeh2->SetCursorPosition(fTeh2->GetCursorPosition());	fTeh2->Deselect();
	gClient->NeedRedraw(fTeh2);

	snprintf(buf, sizeof(buf),"%.4f", backfrack);
	fTbh3->Clear();	fTbh3->AddText(0, buf);
	fTeh3->SetCursorPosition(fTeh3->GetCursorPosition());	fTeh3->Deselect();
	gClient->NeedRedraw(fTeh3);
		
}

//______________________________________________________________________________

void j_gating_frame::DoText() // Updates sliders to match text THEN calls DO HISTOGRAMS (which does everything else)
{//cout<<"DoText "<<flush;
	// Handle text entry widgets.
	//double tvalue;

	//Ask which id called this (should be one of the text boxes)
// 	TGTextEntry *te = (TGTextEntry *) gTQSender;
// 	Int_t id = te->WidgetId();
// 
// 	switch (id) {
// 		case HId1:	
// 			break;
// 		case HId2:		
// 			break;
// 		case HId3:
// 			break;
// 		default:
// 			break;
// 	}

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

void j_gating_frame::DoSlidePoint() // Updates text to match sliders THEN calls DO HISTOGRAMS (which does everything else)
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
void j_gating_frame::DoSlider()
{	
	if(!action_hold){//cout<<"DoSlider "<<flush;
		FetchSliderValues();
		ValidateValues();
		ValuesToSliders();
		ValuesToText();
		DoAutoFit();
		UpdateCanvas();
		if(!set_for_3D) DoHistogram();//in the 3D version we dont update for slider slide
	}
}


void j_gating_frame::SliderRelease(){
// 	if(set_for_3D) DoHistogram(); //only on release
}


//______________________________________________________________________________
// void j_gating_frame::HandleButtons()// Various depending on button
// {      
//    // Handle different buttons.
// //cout<<"HandleButtons "<<flush;
//    TGButton *btn = (TGButton *) gTQSender;
//    Int_t id = btn->WidgetId();
//    switch (id) {
//       case HCId2://manual update for 3D gating that is slow
// 		DoHistogram();
//          break;
//       default:
//          break;
//    }
// }
//______________________________________________________________________________
void j_gating_frame::ChangeProjection(const Int_t id)
{  
//cout<<"ChangeProjection "<<flush;
	xyz=id-1;
	//cout<<endl<<xyz<<endl;
	UpdateInput();
}

//______________________________________________________________________________
void j_gating_frame::UpdateInput(TH1* input){ 
//cout<<"boooom "<<flush;
	raw_input=input;
	UpdateInput();
}

//______________________________________________________________________________

// Basically redo everything.
// All histograms, drawing etc
// Calles for new input histogram or change axis
void j_gating_frame::UpdateInput()
{       
    Emit("InputChange()");
    
TVirtualPad* hold=gPad;

//cout<<"UpdateInput "<<flush;
    RebinFactor=1;

	delete projraw;
	delete proj_flowraw;

	projraw=hist_proj(raw_input,xyz,"projraw"+suffix,true);
	proj_flowraw=hist_proj(raw_input,xyz,"proj_flowraw"+suffix);
    
	projraw->SetStats(0);
	projraw->SetTitle("");
	projraw->SetLineColor(1);
	proj_flowraw->SetStats(0);
	proj_flowraw->SetTitle("");

	delete full;
	full=hist_gater_bin(1,raw_input,xyz,"full"+suffix);
	full->SetStats(0);	
	full->SetTitle("");
	delete output_hist_point;
	output_hist_point=(TH1*)full->Clone(("outputhist"+suffix).c_str());
	output_hist_point->SetLineColor(1);
	output_hist_point->GetXaxis()->SetTitleOffset(1.0);//Fixed a problem from other lib with Yaxis title
	
	delete gate_hist;
	gate_hist=(TH1*)full->Clone(("gate_hist"+suffix).c_str());
	delete free_hist;
	free_hist=(TH1*)full->Clone(("free_hist"+suffix).c_str());
	free_hist->SetLineColor(kRed+1);
	
    UpdateProj();
	
// 	fCanvas1->GetCanvas()->cd();
// 	if(hidebinerrors)proj->Draw("hist");else proj->Draw("");
// 	NewAxisDrawn();//sets sliders ranges and selected to match new axis
// 	if(background_mode==5)b_man->Draw("samehist");
// 	selected->Draw("samehist");
// 	fFitFcn->Draw("same");
// 	DoAutoFit();
// 	UpdateCanvas();
// 	DoHistogram();

	
gPad=hold;
}

void j_gating_frame::UpdateProj(bool DoHist){
TVirtualPad* hold=gPad;

	axis_down=0;axis_up=-1;

	delete proj;
	delete proj_flow;

    proj=(TH1*)projraw->Clone(("proj"+suffix).c_str());
    proj_flow=(TH1*)proj_flowraw->Clone(("proj_flow"+suffix).c_str());
    
    if(RebinFactor>1){
        proj->Rebin(RebinFactor);
        proj_flow->Rebin(RebinFactor);
    }
    
    axis_down=1;
	axis_up=proj->GetNbinsX();

	delete selected;
	selected=(TH1*)proj->Clone(("selected"+suffix).c_str());
	selected->SetLineWidth(3);
	selected->SetLineColor(2);

	delete b_man;
	b_man=(TH1*)proj->Clone(("b_man"+suffix).c_str());
	b_man->SetLineWidth(3);
	b_man->SetLineColor(1);
    
	UpdateSpecBack();
	DoAutoFit();
	UpdateDraw();
	if(DoHist)DoHistogram();
    
gPad=hold;
}

//______________________________________________________________________________

//Make the 2 TSpectrum background histogram
void j_gating_frame::UpdateSpecBack(){
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
void j_gating_frame::ChangeBackMode(const Int_t id)
{       
//cout<<"ChangeBackMode "<<flush;
	background_mode=id;
	
	if(background_mode>4)ShowFrame(fHframe4);else HideFrame(fHframe4); 
	UpdateDraw();
	
	if(background_mode==4){
		gate_hist->Sumw2(kFALSE);
	}
	
	DoHistogram();
}

//______________________________________________________________________________

// Change the mode of background fraction calculation
// Then update the histograms etc
void j_gating_frame::ChangeBackFit(const Int_t id)
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
	
	if(!set_for_3D)DoHistogram();
}


//______________________________________________________________________________

// Calculated the background fraction
// Either by fitting or TSpectrum intergral
// Does nothing when on manual mode
void j_gating_frame::DoAutoFit()
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
void j_gating_frame::UpdateCanvas()
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
void j_gating_frame::ReDrawOne(){
	
	
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
void j_gating_frame::ClickedCanvasOne(Int_t event, Int_t px, Int_t py, TObject *selected_ob)
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
			if(!set_for_3D)DoHistogram();
// 		}
	}
}

//______________________________________________________________________________

// Do the gating on the matrix and produce the output histogram
void j_gating_frame::DoHistogram(){
	
	//Rough error on background fraction
	if(backfit_mode==3)//If its manual increase it
		backfrackfrac=0.08;
	else
		backfrackfrac=0.04;
	

	if(set_for_3D){
		//this is needed because the 3D->2D projection method doesnt nicely fill the named histogram, instead creating a new one, where as the 2D->1D one does
		delete gate_hist; 
	}
// 	gate_hist=hist_gater_bin(gate_down,gate_up,raw_input,xyz,"gate_hist"+suffix);
	gate_hist=hist_gater_bin((gate_down-1)*RebinFactor+1,gate_up*RebinFactor,raw_input,xyz,"gate_hist"+suffix);
	gate_hist->SetLineColor(1);
	gate_hist->GetXaxis()->SetTitleOffset(1.0);//Fixed a problem from other lib with Yaxis title
	
    // Note thw "Full" projection used to make full and anti includes the overflow but excludes the underflow bin
    // This is an intentional choice as often intentionally zeroed data may be sorted into the underflow bin
    // The underflow bin can be selected with manual sliders
	switch (background_mode) {
		case 1://full
			scaled_back_subtract(gate_hist,full,backfrack,output_hist_point,backfrackfrac);
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
				
                compton_offset=(compton_offset-1)*RebinFactor+1;
                
				TH1* compton_hist=hist_gater_bin(compton_offset,raw_input,xyz,"c_gate");
				scaled_back_subtract(gate_hist,compton_hist,backfrack,output_hist_point,backfrackfrac);
				delete compton_hist;
			}
			break;
		case 3://anti gate
			{
// 				if(set_for_3D){ fullcount=full_2d->Integral();gatecount=gate_hist_2d->Integral();}
// 				else{ fullcount=full->Integral();gatecount=gate_hist->Integral();}
				TH1* anti_hist=(TH1*)full->Clone("antiback");
				anti_hist->Add(gate_hist,-1);
				anti_hist->Sumw2(kFALSE);
				scaled_back_subtract(gate_hist,anti_hist,backfrack,output_hist_point,backfrackfrac);
				delete anti_hist;
			}
			break;
		case 4://none
			{
				string hpt=output_hist_point->GetName();
				gate_hist->Copy(*output_hist_point);
				output_hist_point->SetName(hpt.c_str());
			}
			break;
		default://manual
			{				
				
// 				TH1* manb_hist=hist_gater_bin(m_back_down,m_back_up,raw_input,xyz,"m_gate_2d");
				TH1* manb_hist=hist_gater_bin((m_back_down-1)*RebinFactor+1,m_back_up*RebinFactor,raw_input,xyz,"m_gate_2d");
				if(gate_down>m_back_down&&gate_up<m_back_up)manb_hist->Add(gate_hist,-1);//In special case remove the gated part
				manb_hist->Sumw2(kFALSE);
				scaled_back_subtract(gate_hist,manb_hist,backfrack,output_hist_point,backfrackfrac);
				delete manb_hist;				
			}
			break;				
	}
	
	output_hist_point->SetTitle("");

	Emit("OutputReady()");
}

//______________________________________________________________________________
	
//Draw histograms to canvas but with an additional
//matrix full projection shown.
void j_gating_frame::ShowFullProj(){
	action_hold=true;
		TVirtualPad* hold=gPad;
		fCanvas1->GetCanvas()->cd();
		proj_flow->GetXaxis()->SetRange(axis_down,axis_up);
		DrawHistOpt(proj_flow,true);
        
        UpdateDraw(true);
        
        gPad=hold;
	action_hold=false;
}

//______________________________________________________________________________

// Redraw histograms to canvas without the full projection
void j_gating_frame::HideFullProj(){
	action_hold=true;
		UpdateDraw();
		fRButtonz->SetState(kButtonUp);
	action_hold=false;
}

//______________________________________________________________________________

// Draw histograms & canvas to the pad
// these may be updated without redraw
void j_gating_frame::UpdateDraw(bool overlay){
	TVirtualPad* hold=gPad;
	fCanvas1->GetCanvas()->cd();
    
    DrawHistOpt(proj,hidebinerrors,false,overlay);
    if(backfit_mode>3)DrawHistOpt(specback,true,false,true);
    if(background_mode>4)DrawHistOpt(b_man,true,false,true);
    DrawHistOpt(selected,true,false,true);
	fFitFcn->Draw("same");
	UpdateCanvas();
	gPad=hold;
}


void j_gating_frame::RebinPlus(){
    RebinFactor++;
    UpdateProj(!set_for_3D);
}

void j_gating_frame::RebinMinus(){
    if(RebinFactor>1){
        RebinFactor--;
        UpdateProj(!set_for_3D);
    }
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
		
// 	char* FrameReNamChar=new char[128];
//     string FrameReNamStr;
// 	if(gGlobalAskWindowName){
//         new TGInputDialog(gClient->GetRoot(),gClient->GetRoot(),"Rename Gate Tool Window",input->GetName(),FrameReNamChar);
//         FrameReNamStr=FrameReNamChar;
//     }
//     
// 	if(FrameReNamStr.size()){
// 		SetWindowName(FrameReNamStr.c_str());	
// 	}else{
		SetWindowName(input->GetName());	
// 	}
	
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
    
    //I cant remember/determine who/when calls/connects this. But it seems to do with adjustable frame partition
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
    snprintf(buf, sizeof(buf),"%.1f", H->GetXaxis()->GetBinWidth(1));
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




ClassImp(jRootTreeCube);

int jRootTreeCube::jRootTreeCube_iterator = 0;


jRootTreeCube::jRootTreeCube():
	TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame),
	Popup(0),DataChain(0),Symmetrisation(0),Hist{0,0,0},XYZ(0),
	Gate(0),Back(0),gd(-1),gu(-1),bd(-1),bu(-1){
    
    SetCleanup(kDeepCleanup);	
    
    
    TGLayoutHints* ffExpandY = new TGLayoutHints(kLHintsExpandY | kLHintsCenterY, 0, 0, 0, 0);
    TGLayoutHints* ffExpand = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0);

	TGVerticalFrame *ControlFrame = new TGVerticalFrame(this, 0, 0, 0); 

		fBgroup1 = new TGButtonGroup(ControlFrame,"Projection",kChildFrame);
		TGRadioButton *fRButton = new TGRadioButton(fBgroup1,"X ");
		fRButton->SetState(kButtonDown);
		fRButton = new TGRadioButton(fBgroup1,"Y ");
		fRButton = new TGRadioButton(fBgroup1,"Z");
		fBgroup1->Show();
		fBgroup1->Connect(" Clicked(Int_t)", "jRootTreeCube", this,"ChangeProjection(Int_t)");//Link test signal to its    int gate_down,gate_up;
	ControlFrame->AddFrame(fBgroup1);
	
		TGTextButton *fTButton1 = new TGTextButton(ControlFrame,"DoGates");
		fTButton1->Connect("Clicked()","jRootTreeCube",this,"DoGatesDraw()");
	ControlFrame->AddFrame(fTButton1);
		TGTextButton *fTButton2 = new TGTextButton(ControlFrame,"GateGates");
		fTButton2->Connect("Clicked()","jRootTreeCube",this,"DoGatesGate()");
	ControlFrame->AddFrame(fTButton2);
	
	
    AddFrame(ControlFrame,ffExpandY);

	SelectFrame = new jGateSelectFrame(this);
    AddFrame(SelectFrame,ffExpand);

    MapSubwindows();
    Resize(GetDefaultSize());
    MapWindow();
}

void jRootTreeCube::ChangeProjection(Int_t xyz){
	fBgroup1->SetButton(xyz);
	XYZ=xyz-1;
	SelectFrame->UpdateInput(Hist[XYZ]);
}


// If using the quick AddBinContent it doesnt incriment fEntries properly, which can cause issues down the line
void jRootTreeCube::ResetTH1fEntries(TH1* hist){
	double fEntriesCount=0;
	int N=hist->GetNcells();
	for(int b=0;b<N;b++){
		fEntriesCount+=hist->GetBinContent(b);
	}
	hist->SetEntries(fEntriesCount);
}

// If using the quick AddBinContent it doesnt incriment fEntries properly, which can cause issues down the line
void jRootTreeCube::SymmetriseTH2(TH2* hist){
	double fEntriesCount=0;
	for (int x=0;x<=hist->GetNbinsX()+1;x++){
		for (int y=0;y<=x;y++){
			double D=hist->GetBinContent(x,y)+hist->GetBinContent(y,x);
			hist->SetBinContent(x,y,D);
			hist->SetBinContent(y,x,D);
			fEntriesCount+=2*D;
		}
	}
	hist->SetEntries(fEntriesCount);
}


bool jRootTreeCube::TestFileExists(string InputFile){
	TFile InFile(InputFile.c_str(),"READ");
	gROOT->cd();	
	if(!InFile.IsOpen()){
		cout<<endl<<"No File Named "<<InputFile<<endl;
		return false;
	}
	InFile.Close();
	return true;
}

void jRootTreeCube::ClearHistList(){
	for(auto h:HistList)delete h;
	HistList.clear();
}

void jRootTreeCube::SetNewInput(string InputFile){
	
	if(!TestFileExists(InputFile))return;
	TFile InFile(InputFile.c_str(),"READ");
	gROOT->cd();	
	
	string TTreeName="";
	ClearHistList();
	
	TKey *key;
	TIter next(InFile.GetListOfKeys());
	while ((key = (TKey*)next())){
		TClass *cl = gROOT->GetClass(key->GetClassName());
		if(cl->InheritsFrom(TTree::Class())&&!TTreeName.size()){
            TTreeName=key->GetName();
		}
		if(cl->InheritsFrom(TH1::Class())
		&& !cl->InheritsFrom(TH2::Class())
		&& !cl->InheritsFrom(TH3::Class())){
			// Only find and clone 1D
            HistList.push_back((TH1*)key->ReadObj()->Clone());
			HistList[HistList.size()-1]->Reset(); // Empty them because we will sum the first file
		}
	}
	InFile.Close();
	
	if(!HistList.size()){
		cout<<endl<<"No Projections Histograms Located in file "<<InputFile<<endl;
	}
	
	ArrangeInputHistograms();
	
	if(!TTreeName.size()){
		cout<<endl<<"No TTree Located in file "<<InputFile<<endl;
		return;
	}
	
	if(DataChain)delete DataChain;
	DataChain=new TChain(TTreeName.c_str());
	
	AddFile(InputFile);
	
	SetBranches();

	return;
}

void jRootTreeCube::AddFile(string InputFile){
	
	if(!DataChain){
		SetNewInput(InputFile);
		return;
	}
		
	if(!TestFileExists(InputFile))return;

	TFile InFile(InputFile.c_str(),"READ");
	gROOT->cd();
	for(auto h:HistList){
		TH1* H=(TH1*) InFile.Get(h->GetName());
		if(H)h->Add(H);
	}	
	InFile.Close();
	
	DataChain->Add(InputFile.c_str());
	
	ChangeProjection(1);
	
	cout<<"Added File : "<<InputFile<<endl;
}


void jRootTreeCube::SetBranches(){
	if(!DataChain)return;
	
	SelectedLeafType= nullptr;
	BranchAddresses.clear();
	LeafAddresses.clear();

	auto obarray=DataChain->GetListOfBranches();
	
	for(int b=0;b<DataChain->GetNbranches();b++){
		if(obarray->At(b)->IsA()->InheritsFrom("TBranch")){
			TBranch* branch=(TBranch*)obarray->At(b);
			TClass *expectedClass=0;
			EDataType expectedType;
			if(!branch->GetExpectedType(expectedClass,expectedType)){ //returns 0 when no error
				if(!expectedClass){ // Not a TClass
					TDataType* LeafType=TDataType::GetDataType(expectedType);
// 					cout<<"  Type "<<TDataType::GetTypeName(expectedType);
					if(SelectedLeafType==nullptr)SelectedLeafType=LeafType;
					if(LeafType==SelectedLeafType)BranchAddresses.push_back((string)branch->GetName());	
				}
			}
			
			auto leafarray=branch->GetListOfLeaves();
			for(int l=0;l<branch->GetNleaves();l++){
				if(leafarray->At(l)->IsA()->InheritsFrom("TLeaf")){
					TLeaf* leaf=(TLeaf*)leafarray->At(l);
					TDataType* LeafType=TDataType::GetDataType(GetEDataType(leaf->GetTypeName()));
			
					if(SelectedLeafType==nullptr)SelectedLeafType=LeafType;
					
					if(LeafType==SelectedLeafType){
						string BrNm=branch->GetName();
						BrNm+="."+(string)leaf->GetName();
						LeafAddresses.push_back(BrNm);
					}
				}
			}
		}
	}
	/// If using the TTreeReader method, even when a branch is a basic data type
	/// If it was "created using a leaf list" it will have a leaf that must be addressed directly

	if(SelectedLeafType==nullptr){
		cout<<endl<<"No Valid Leaf Types Found"<<endl;
		return;
	}
}


void jRootTreeCube::ArrangeInputHistograms(){
	
	if(!HistList.size()){
		return;
	}
	
	Hist[0]=HistList[0];
	Hist[1]=HistList[0];
	Hist[2]=HistList[0];
	if(HistList.size()>1){
		Hist[1]=HistList[1];
		Hist[2]=HistList[1];
	}
	if(HistList.size()>2){
		Hist[2]=HistList[2];
	}
	for(auto h:HistList){
		string name=h->GetName();
		if(name.find("X")<name.size())Hist[0]=h;
		if(name.find("Y")<name.size())Hist[1]=h;
		if(name.find("Z")<name.size())Hist[2]=h;
	}
	
	
	bool x=(Hist[0]==Hist[1])||(Hist[0]==Hist[2]);
	bool y=(Hist[1]==Hist[0])||(Hist[1]==Hist[2]);
	bool z=(Hist[2]==Hist[0])||(Hist[1]==Hist[2]);
	SetSymmetry(x,y,z);
	
}

TH2* jRootTreeCube::PerformGate(unsigned short GateAxis,int GateDown,int GateUp){

	if(!DataChain){
		return 0;
	}
		
	bool BrcN=(BranchAddresses.size()>2);
	bool LfN=(BranchAddresses.size()>2);
	if(!(BrcN||LfN)){
		return 0;
	}
	
	///////////////////////////////////////////
	// Preapre the TH2 Histogram For Filling //
	///////////////////////////////////////////

	int Ny=Hist[(GateAxis+1)%3]->GetNbinsX();
	double Zeroy=Hist[(GateAxis+1)%3]->GetBinLowEdge(1);
	double Widthy=Hist[(GateAxis+1)%3]->GetBinWidth(1);
	int Nz=Hist[(GateAxis+2)%3]->GetNbinsX();
	double Zeroz=Hist[(GateAxis+2)%3]->GetBinLowEdge(1);
	double Widthz=Hist[(GateAxis+2)%3]->GetBinWidth(1);

	TH2F* FillHist=new TH2F(FillHistNum().c_str(),"FillHist",Ny,Zeroy,Zeroy+Ny*Widthy,Nz,Zeroz,Zeroz+Nz*Widthz);
/*	
	unsigned int GBd=Hist[GateAxis%3]->GetXaxis()->FindBin(GateDown);
	unsigned int GBu=Hist[GateAxis%3]->GetXaxis()->FindBin(GateUp);*/
	unsigned int GBd=GateDown;
	unsigned int GBu=GateUp;	
	
	
	// A popup message window, as this can be a very slow process
	if(!Popup)Popup=new jRootMultiPurposePopup();
	string title="Running TChain sort for class : "+(string)SelectedLeafType->GetFullTypeName();
// 	string title="Running TChain sort for class : "+(string)typeid(T).name();
	Popup->UpdateLine(title,1);
	Popup->UpdateLine("Starting",2);

	
	TStopwatch stopw;
	stopw.Start();//Defauly behaviour clears
	
	switch (SelectedLeafType->GetType()) {
		case  EDataType::kUShort_t:
			if(BrcN)UnsignedTypedTTreeSortBranchLoop<UShort_t>(FillHist,GateAxis,GBd,GBu); // This is the case that we expect
			else TypedTTreeSortTTreeReader<UShort_t>(FillHist,GateAxis,GateDown,GateUp);
			break;
		case  EDataType::kUInt_t:
			if(BrcN)UnsignedTypedTTreeSortBranchLoop<UInt_t>(FillHist,GateAxis,GBd,GBu);
			else TypedTTreeSortTTreeReader<UInt_t>(FillHist,GateAxis,GateDown,GateUp);
			break;
		case  EDataType::kULong64_t:
			if(BrcN)UnsignedTypedTTreeSortBranchLoop<ULong64_t>(FillHist,GateAxis,GBd,GBu);
			else TypedTTreeSortTTreeReader<ULong64_t>(FillHist,GateAxis,GateDown,GateUp);
			break;
		case  EDataType::kULong_t:
			if(BrcN)UnsignedTypedTTreeSortBranchLoop<ULong_t>(FillHist,GateAxis,GBd,GBu);
			else TypedTTreeSortTTreeReader<ULong_t>(FillHist,GateAxis,GateDown,GateUp);
			break;
// 		case  EDataType::kShort_t: if(LfN)TypedTTreeSortTTreeReader<Short_t>(FillHist,GateAxis,GateDown,GateUp); break;
// 		case  EDataType::kInt_t: if(LfN)TypedTTreeSortTTreeReader<Int_t>(FillHist,GateAxis,GateDown,GateUp); break;
// 		case  EDataType::kLong_t: if(LfN)TypedTTreeSortTTreeReader<Long_t>(FillHist,GateAxis,GateDown,GateUp); break;
// 		case  EDataType::kLong64_t: if(LfN)TypedTTreeSortTTreeReader<Long64_t>(FillHist,GateAxis,GateDown,GateUp); break;
// 		case  EDataType::kFloat_t: if(LfN)TypedTTreeSortTTreeReader<Float_t>(FillHist,GateAxis,GateDown,GateUp); break;
// 		case  EDataType::kFloat16_t: if(LfN)TypedTTreeSortTTreeReader<Float16_t>(FillHist,GateAxis,GateDown,GateUp); break;
// 		case  EDataType::kDouble_t: if(LfN)TypedTTreeSortTTreeReader<Double_t>(FillHist,GateAxis,GateDown,GateUp); break;
// 		case  EDataType::kDouble32_t: if(LfN)TypedTTreeSortTTreeReader<Double32_t>(FillHist,GateAxis,GateDown,GateUp); break;
		default: break;
	}
	
	double CpuTime=stopw.CpuTime(); // and stops
	cout<<endl<<CpuTime<<" s"<<endl;

	return FillHist;
}
	
	
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
int jRootTreeCube::TypedTTreeSortTTreeReader(TH2* FillHist,
											 unsigned short GateAxis,
											 double GateDown,
											 double GateUp){	
	// Inputs are in tree's leaf order. Rearrange cyclically setting gate to 0.
	string LeafAddress[3]={LeafAddresses[GateAxis%3],LeafAddresses[(GateAxis+1)%3],LeafAddresses[(GateAxis+2)%3]};
	bool SymBools[3]={(bool)(Symmetrisation&(1<<(GateAxis%3))),(bool)(Symmetrisation&(1<<((GateAxis+1)%3))),(bool)(Symmetrisation&(1<<((GateAxis+2)%3)))};
	
	unsigned long nevent = DataChain->GetEntries();
	unsigned long e = 0;
	
	DataChain->ResetBranchAddresses();
	TTreeReader myReader(DataChain);
	myReader.Restart();
	
	TTreeReaderValue<T> ReadVal1(myReader,LeafAddress[0].c_str());
	TTreeReaderValue<T> ReadVal2(myReader,LeafAddress[1].c_str());
	TTreeReaderValue<T> ReadVal3(myReader,LeafAddress[2].c_str());
	double val[3];
	
	while(myReader.Next()){
		val[0]=*ReadVal1;
		val[1]=*ReadVal2;
		val[2]=*ReadVal3;	
		
		if(val[0]>=GateDown && val[0]<GateUp)FillHist->Fill(val[1],val[2]);
		
		if(SymBools[0]&&SymBools[1]){
			if(val[1]>=GateDown && val[1]<GateUp)FillHist->Fill(val[0],val[2]);
		}
		
		if(SymBools[0]&&SymBools[2]){
			if(val[2]>=GateDown && val[2]<GateUp)FillHist->Fill(val[1],val[0]);
		}
		
		if(!(e&0x3FFFFF)){ // Update the popup about every 4 million events.
			Popup->UpdatePercentage(100.0*e/nevent,2);
		}
		e++;
	}
	
	if(SymBools[1]&&SymBools[2]){
		Popup->UpdateLine("Finisihed sort, symmetrisating histogram.",2);
		SymmetriseTH2(FillHist);
	}
	
	return 0;
}

template <class T>
int jRootTreeCube::UnsignedTypedTTreeSortBranchLoop(TH2* FillHist,
										unsigned short GateAxis,
										unsigned int GateDown,
										unsigned int GateUp){
	
	// Inputs are in tree's leaf order. Rearrange cyclically setting gate to 0.
	string BranchAddress[3]={BranchAddresses[GateAxis%3],BranchAddresses[(GateAxis+1)%3],BranchAddresses[(GateAxis+2)%3]};
	bool SymBools[3]={(bool)(Symmetrisation&(1<<(GateAxis%3))),(bool)(Symmetrisation&(1<<((GateAxis+1)%3))),(bool)(Symmetrisation&(1<<((GateAxis+2)%3)))};
// 	bool SymBools[3];
	
	bool AllAxisSym=SymBools[0]&&SymBools[1]&&SymBools[2];
	bool GateAxisSym=SymBools[0];
	bool HistSym=SymBools[1]&&SymBools[2];

	unsigned int OvX=FillHist->GetNbinsX()+1;
	unsigned int OvY=FillHist->GetNbinsY()+1;
	unsigned int NBX=OvX+1;
	
	if(HistSym&&(OvX!=OvY)){
		cout<<endl<<"Error : Asymmetric histogram provided when requesting symmetric fill."<<endl;
		return -1;
	}
	
	unsigned long nevent = DataChain->GetEntries();
	T val[3]; // Holder array for branch values
	DataChain->ResetBranchAddresses();
	DataChain->SetBranchAddress(BranchAddress[0].c_str(),&val[0]);
	DataChain->SetBranchAddress(BranchAddress[1].c_str(),&val[1]);
	DataChain->SetBranchAddress(BranchAddress[2].c_str(),&val[2]);
	
	if(AllAxisSym){
		for (unsigned long e=0;e<nevent;e++) {
			DataChain->GetEvent(e);
			
			//// This fuction is for unsigned, so only have to check if bin number is past the overflow
			if(val[0]>OvX)val[0]=OvX;
			if(val[1]>OvX)val[1]=OvX;
			if(val[2]>OvX)val[2]=OvX;
			
////////  Fractionally faster to not have to do [(i+2)%3] address lookup for every event //////
////////  So write out the 3 cases explicity rather than the nice neat loop below        //////
			if(val[0]>=GateDown && val[0]<=GateUp)FillHist->AddBinContent(val[1]+NBX*val[2]);
			if(val[1]>=GateDown && val[1]<=GateUp)FillHist->AddBinContent(val[2]+NBX*val[0]);
			if(val[2]>=GateDown && val[2]<=GateUp)FillHist->AddBinContent(val[0]+NBX*val[1]);
			
// // 				for(int i=0;i<3;i++){
// // 					if(val[i]>=GateDown && val[i]<=GateUp) {
// // 						FillHist->AddBinContent(val[(i+1)%3]+NBX*val[(i+2)%3]);
// // 					}
// // 				}
			
			if(!(e&0x3FFFFF)){ // Update the popup about every 4 million events.
				Popup->UpdatePercentage(100.0*e/nevent,2);
			}
		}
	}else if(GateAxisSym){
		// In this case 2 of the three axis are the gating axis
		for (unsigned long e=0;e<nevent;e++) {
			DataChain->GetEvent(e);
			if(val[1]>OvX)val[1]=OvX;
			if(val[2]>OvY)val[2]=OvY;

			// Histogram are defined X-axis == (GateAxis+1)%3, Y-axis == (GateAxis+2)%3
			// Filling here they are NOT symetric
			if(val[0]>=GateDown && val[0]<=GateUp){
// 				cout<<","<<flush;
				FillHist->AddBinContent(val[1]+NBX*val[2]);
			}
			if(SymBools[1])if(val[1]>=GateDown && val[1]<=GateUp){
// 				cout<<"."<<flush;
				if(val[0]>OvX)val[0]=OvX;
				FillHist->AddBinContent(val[0]+NBX*val[2]);
			}
			if(SymBools[2])if(val[2]>=GateDown && val[2]<=GateUp){
				cout<<"'"<<flush;
				if(val[0]>OvY)val[0]=OvY;
				FillHist->AddBinContent(val[1]+NBX*val[0]);
			}
			
			if(!(e&0x3FFFFF)){ // Update the popup about every 4 million events.
				Popup->UpdatePercentage(100.0*e/nevent,2);
			}
		}	
	}else{
		// When only gating on one branch then it is much faster to initially load only that branch.
		auto br=DataChain->GetBranch(BranchAddress[0].c_str()); 
		for (unsigned long e=0;e<nevent;e++) {
			br->GetEvent(e);
			if(val[0]>=GateDown && val[0]<=GateUp) {
				DataChain->GetEvent(e);
				if(val[1]>OvX)val[1]=OvX;
				if(val[2]>OvX)val[2]=OvX;
				FillHist->AddBinContent(val[1]+NBX*val[2]);
			}
			
			if(!(e&0x3FFFFF)){ // Update the popup about every 4 million events.
				Popup->UpdatePercentage(100.0*e/nevent,2);
			}
		}
		
		// Alteratively one may use the TTree draw command. This is slower than a basic loop.
// // 			string DrawCmd=BranchAddress[2]+":"+BranchAddress[1]+">>+"+FillHist->GetName(); // Note X/Y in TTree::Draw command flipped
// // 			stringstream ss; ss<<BranchAddress[0]<<">="<<GateDown<<"&&"<<BranchAddress[0]<<"<"<<GateUp;
// // 			DataChain->Draw(DrawCmd.c_str(),ss.str().c_str(),"goff");
		
	}

	
	///// Make the output histogram symetric if it should be
	///// The treatmet of diagonal being double filled is correct.
	if(HistSym){
		Popup->UpdateLine("Finisihed sort, symmetrisating histogram.",2);
		SymmetriseTH2(FillHist);
	}else{
		ResetTH1fEntries(FillHist);// Result of using AddBinContent
	}
	
	return 0;
}


// For some reason I can only find getting leaf type names by hardcoded output in 
// inherited classes TLeafD, TLeafS etc, and in these they use the "UShort_t" typename 
// TDataType will return these names, but I can find no function to TAKE these names
EDataType jRootTreeCube::GetEDataType(string typestring){
	if (!typestring.compare("Char_t"))return EDataType::kChar_t;
	if (!typestring.compare("Short_t"))return EDataType::kShort_t;
	if (!typestring.compare("Int_t"))return EDataType::kInt_t;
	if (!typestring.compare("Long_t"))return EDataType::kLong_t;
	if (!typestring.compare("Float_t"))return EDataType::kFloat_t;
	if (!typestring.compare("char*"))return EDataType::kCharStar;
	if (!typestring.compare("Double_t"))return EDataType::kDouble_t;
	if (!typestring.compare("Double32_t"))return EDataType::kDouble32_t;
	if (!typestring.compare("UChar_t"))return EDataType::kUChar_t;
	if (!typestring.compare("UShort_t"))return EDataType::kUShort_t;
	if (!typestring.compare("UInt_t"))return EDataType::kUInt_t;
	if (!typestring.compare("ULong_t"))return EDataType::kULong_t;
	if (!typestring.compare("Long64_t"))return EDataType::kLong64_t;
	if (!typestring.compare("ULong64_t"))return EDataType::kULong64_t;
	if (!typestring.compare("Bool_t"))return EDataType::kBool_t;
	if (!typestring.compare("Float16_t"))return EDataType::kFloat16_t;
	return EDataType::kVoid_t;
}



TH1* jRootTreeCube::DoGates(){
	
	if(!Popup)Popup=new jRootMultiPurposePopup();
	
	if(SelectFrame->GetGateBinDown()!=gd||SelectFrame->GetGateBinUp()!=gu){
		Popup->UpdateLine("Performing New Gate",0);
		gd=SelectFrame->GetGateBinDown();
		gu=SelectFrame->GetGateBinUp();
		if(Gate)delete Gate;
		
		Gate=PerformGate(XYZ,gd,gu);
		/// DO THE GATE
	}
	
	if(!Gate)return 0;
	
	if(SelectFrame->GetBackBinDown()!=bd||SelectFrame->GetBackBinUp()!=bu){
		Popup->UpdateLine("Performing New Background Gate",0);
		bd=SelectFrame->GetBackBinDown();
		bu=SelectFrame->GetBackBinUp();
		if(Back)delete Back;
		Back=0;
		
		if(bu>bd){
		/// DO THE GATE
			Back=PerformGate(XYZ,bd,bu);
		}
	}	
	double Frac=SelectFrame->GetBackFrac();
	
	TH1* RetHist;
	
	if(Frac>0 && Back){// If do background subtraction
		Popup->UpdateLine("Performing Background Subtraction",0);
		
		if(SelectFrame->SubtractGate()){// If special case gate overlaps
			Back->Add(Gate,-1);
		}
		
		RetHist=scaled_back_subtract(Gate,Back,Frac,0.04,true);
	}else{
		RetHist=(TH1*)Gate->Clone();
	}
	
	if(Popup){
		delete Popup;
		Popup=0;
	}

	return RetHist;
}

void jRootTreeCube::DoGatesDraw(){
	TH1* HistRet=DoGates();
	if(HistRet){
		TCanvas *C1=new TCanvas();
		C1->cd();
		gPad->Update();
		HistRet->SetDirectory(0);
		HistRet->AppendPad("col");
	}
	
}

void jRootTreeCube::DoGatesGate(){
	TH1* HistRet=DoGates();
	if(HistRet){
		new jgating_tool(HistRet,true);
	}
}

