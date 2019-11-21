//
//
//	James data tweaking GUI tool 1.0
// 	27/10/16		16/10/2015
//	james.smallcombe@outlook.com
//
//

#include "j_spectool.h"
#include "j_hist_formatting.h"

ClassImp(jSpecTool);

int jSpecTool::spectool_iterator = 0;

vector<string> jSpecTool::BackOpt={"BackOrder2","BackOrder4","BackOrder6","BackOrder8","BackSmoothing3","BackSmoothing5","BackSmoothing7","BackSmoothing9","BackSmoothing11","BackSmoothing13","BackIncreasingWindow","Compton"};


    
jSpecTool::jSpecTool(TH1* input):jSpecTool(new TGMainFrame(gClient->GetRoot(), 100, 100,kVerticalFrame),input){
    const TGWindow *P=GetParent();
    ParentWindow=(TGMainFrame*)P;

    // To avoid double deletion when deleting from jSpecTool
    ParentWindow->SetCleanup(kNoCleanup);
    SetCleanup(kDeepCleanup);
    ParentWindow->Connect("CloseWindow()","TGMainFrame",ParentWindow,"DontCallClose()");
    ParentWindow->Connect("CloseWindow()","jSpecTool",this,"~jSpecTool()");
    
    ParentWindow->AddFrame(this, new TGLayoutHints(kLHintsExpandX|kLHintsExpandY, 1, 1, 1, 1));
	ParentWindow->Resize(ParentWindow->GetDefaultSize());
	ParentWindow->MapWindow();
	ParentWindow->SetWindowName("SpectrumTool");
}

jSpecTool::jSpecTool(const TGWindow * p,TH1* input) : TGCompositeFrame(p,100,100,kVerticalFrame),ParentWindow(0),histin(0),histsub(0),histzero(0),specback(0){
TVirtualPad* hold=gPad;

    if(input)input->GetXaxis()->SetRange(1,-1);

	TGLayoutHints* ffExpandXpad = new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 1);

	
	TGHorizontalFrame* fHframe0 = new TGHorizontalFrame(this, 0, 0, 0);  //create a frame, filled with objects horizontally

	fCheck0 = new TGCheckButton(fHframe0,"Remove Oversub   ");// A tick box with hover text belonging to a parent frame
	fCheck0->SetState(kButtonUp);
	fCheck0->Connect(" Clicked()", "jSpecTool", this,"DoUpdate()");
	fCheck0->SetToolTipText("Remove over subtraction with the current background");
	
	fCheck1 = new TGCheckButton(fHframe0,"Hide Bin Errors   ");
	fCheck1->SetState(kButtonDown);
	fCheck1->Connect(" Clicked()", "jSpecTool", this,"DoUpdate()");
	fCheck1->SetToolTipText("Hide Bin Errors on drawn histograms");
	
	fCheck2 = new TGCheckButton(fHframe0,"Remove Background   ");// A tick box with hover text belonging to a parent frame
	fCheck2->SetState(kButtonUp);
	fCheck2->Connect(" Clicked()", "jSpecTool", this,"DoUpdate()");
	fCheck2->SetToolTipText("Subtract the background");	
    
    TGTextButton *InvertButton = new TGTextButton(fHframe0,"  Invert  ");
    InvertButton->Connect("Clicked()","jSpecTool",this,"Invert()");

	fHframe0->AddFrame(fCheck0);
	fHframe0->AddFrame(fCheck1);
	fHframe0->AddFrame(fCheck2);
	fHframe0->AddFrame(InvertButton);

	fCanvas1 = new TRootEmbeddedCanvas(("Embedded"+make_iterator()).c_str(), this, 800, 500);
	fCanvas1->GetCanvas()->SetName(("ResultCan"+make_iterator()).c_str());
		//Results panel
// 	ReMargin(fCanvas1->GetCanvas());
// 	fCanvas1->GetCanvas()->SetFillColor(33);
// 	fCanvas1->GetCanvas()->SetBorderMode(0);
// 	fCanvas1->GetCanvas()->SetFrameFillColor(10);
	fCanvas1->GetCanvas()->SetMargin(0.1,0.01,0.05,0.01);	

	TQObject::Connect(fCanvas1->GetCanvas(), "ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0,0,"ClickPeakDrawConnect(Int_t,Int_t,Int_t,TObject*)");
		// rebin bar
	TGHorizontalFrame* rebinframe = new TGHorizontalFrame(this, 0, 0, 0);
	TGLabel *label = new TGLabel(rebinframe, "   Rebin Histogram  ");
	rebinframe->AddFrame(label);	
	fHslider1 = new TGHSlider(rebinframe, 9, kSlider2);
	fHslider1->SetPosition(0);
	fHslider1->Connect("PositionChanged(Int_t)", "jSpecTool", this, "DoUpdateF()");
	rebinframe->AddFrame(fHslider1, ffExpandXpad);
	
	TGHorizontalFrame* orderframe = new TGHorizontalFrame(this, 0, 0, 0);
	label = new TGLabel(orderframe, "   Background Opt  ");
	orderframe->AddFrame(label);
	fHslider2 = new TGHSlider(orderframe, (unsigned int)BackOpt.size() - 1, kSlider2);
	fHslider2->SetPosition(0);
	fHslider2->Connect("PositionChanged(Int_t)", "jSpecTool", this, "UpdateSpecBack()");
	orderframe->AddFrame(fHslider2, ffExpandXpad);
	
	fTeh1 = new TGTextEntry(orderframe);
	fTeh1->SetDefaultSize(200,25);
	fTeh1->SetAlignment (kTextLeft);
	fTeh1->SetEnabled(kFALSE);
	orderframe->AddFrame(fTeh1);
	
	TGHorizontalFrame* smoothframe = new TGHorizontalFrame(this, 0, 0, 0);
	label = new TGLabel(smoothframe, "   Smoothing N       ");
	smoothframe->AddFrame(label);
	fHslider3 = new TGHSlider(smoothframe, 140, kSlider2);
	fHslider3->SetPosition(15);
	fHslider3->Connect("PositionChanged(Int_t)", "jSpecTool", this, "UpdateSpecBack()");
	smoothframe->AddFrame(fHslider3, ffExpandXpad);
	
	fTeh2 = new TGTextEntry(smoothframe);
	fTeh2 ->SetDefaultSize(30,25);
	fTeh2 ->SetAlignment (kTextLeft);
	fTeh2 ->SetEnabled(kFALSE);
	smoothframe->AddFrame(fTeh2);
	
	fCheck3 = new TGCheckButton(smoothframe," OverSubMode ");
	fCheck3->SetState(kButtonUp);
	fCheck3->Connect(" Clicked()", "jSpecTool", this,"UpdateSpecBack()");
	fCheck3->SetToolTipText("Background will do anti-oversubtraction iterations background");	
	smoothframe->AddFrame(fCheck3);
	
	fCheck4 = new TGCheckButton(smoothframe," ZeroMin ");
	fCheck4->SetState(kButtonDown);
	fCheck4->Connect(" Clicked()", "jSpecTool", this,"UpdateSpecBack()");
	fCheck4->SetToolTipText("Set Zero as the minimum when calculating oversubtraction");	
	smoothframe->AddFrame(fCheck4);
	
	AddFrame(fHframe0, new TGLayoutHints(kLHintsCenterX, 3, 3, 3, 3));
	AddFrame(fCanvas1,new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 3, 3, 3, 3));
	AddFrame(rebinframe,ffExpandXpad);
	AddFrame(orderframe,ffExpandXpad);
	AddFrame(smoothframe,ffExpandXpad);

	NewInput(input);
    
    MapSubwindows();
	MapWindow();
	
gPad=hold;
}

void jSpecTool::NewInput(TH1* input){
	if(!input)return;
	
	if(input->IsA()->InheritsFrom("TH2"))return;

	if(histin){delete histin;}
	if(specback){delete specback;specback=0;}
	if(histsub){delete histsub;}
	if(histzero){delete histzero;}

	histin=(TH1*)input->Clone(("massahist"+make_iterator()).c_str());
    histin->GetListOfFunctions()->Clear();
	histsub=(TH1*)histin->Clone(("massasubhist"+make_iterator()).c_str());
	histzero=(TH1*)histin->Clone(("massasubzero"+make_iterator()).c_str());
	RemovalPrep(histzero);
	gStart=RemovalStart(histin);
	
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();

	UpdateSpecBack();	
    DoUpdateF();
}
	

//______________________________________________________________________________
jSpecTool::~jSpecTool()
{
   if(histin){delete histin;}
   if(specback){delete specback;}
   if(histsub){delete histsub;}
   if(histzero){delete histzero;}
   if(ParentWindow){delete ParentWindow;}

   Closed(this);
   TQObject::Disconnect(this);
    
   cout<<"SPECTOOL DELETED"<<endl;
   
   // Clean up
   Cleanup();
}

//______________________________________________________________________________
// void jSpecTool::DoClose()
// {
//    // Called when window is closed via the window manager
//    
//    cout<<endl<<"DOO0000000OM"<<endl;
//    delete this;
// }


void jSpecTool::UpdateSpecBack(){  
	unsigned int opt=fHslider2->GetPosition();
	N=fHslider3->GetPosition()+10;
	StrOpt="";
	if(opt<BackOpt.size())StrOpt=BackOpt[opt];
	fTeh1->SetText(StrOpt.c_str());
	fTeh2->SetText(std::to_string(N).c_str());


	if(fCheck3->GetState()){
		if(histsub){delete histsub;}
		if(fCheck4->GetState())histsub=(TH1*)histzero->Clone(("massasubhist"+make_iterator()).c_str());
		else histsub=(TH1*)histin->Clone(("massasubhist"+make_iterator()).c_str());
		RemovalPrivate(histsub);
	}else{
		ReMakeSpecBack(histin);
	}

	DoUpdate();
}

string jSpecTool::make_iterator(){
	stringstream ss;
	ss << spectool_iterator;
	spectool_iterator++;
	return ss.str();
}

void jSpecTool::ReMakeSpecBack(TH1* hist){
	if(hist){
		if(specback){delete specback;}
		specback= TSpectrum::StaticBackground(hist,N,StrOpt.c_str());
		specback->SetLineColor(6);
	}
}

//Subtract/Rebin/Draw, following background calculations
void jSpecTool::DoUpdate(bool saveaxis){TVirtualPad* hold=gPad;
	if(!histin)return;

	//Get the currently drawn axis
	int axis_down=1,axis_up=-1;
	TH1* hp=hist_capture(fCanvas1->GetCanvas());
	if(hp&&saveaxis){
		axis_down=hp->GetXaxis()->GetFirst();
		axis_up=hp->GetXaxis()->GetLast();
	}
	
	fCanvas1->GetCanvas()->cd();
	
	unsigned short rebin=fHslider1->GetPosition()+1;
	
	TH1 *H,*S=0;

	//If remove oversubtraction
	if(fCheck0->GetState()){
		//OverSubMode
		if(fCheck3->GetState())H=histsub;
		else H=histzero;
	}else{H=histin;}

	
	//If Hide Bin Errors
	H=DrawCopyHistOpt(H,fCheck1->GetState());//Needed if any functions have been drawn

	
	//H is now the draw copy, not modifying original
	
	if(specback){
		// if Remove Background
		if(fCheck2->GetState()){
			if(!H->GetSumw2N())H->Sumw2();
			H->Add(specback,-1.);
		}else{
			S=specback->DrawCopy("same");
		}
	}

	if(rebin>1){
// 		cout<<endl<<H;
		H->Rebin(rebin);
		if(S)S->Rebin(rebin);
	}
	
	hformat(H,false);
	
	H->GetXaxis()->SetRange(axis_down,axis_up);

	fCanvas1->GetCanvas()->Modified();
	fCanvas1->GetCanvas()->Update();
gPad=hold;
}

void jSpecTool::RemovalPrep(TH1* hist){
	if(!hist->GetSumw2N())hist->Sumw2();
	for(int i=1;i<=hist->GetNbinsX();i++){
		if(hist->GetBinContent(i)<0){
			hist->SetBinContent(i,0);
		}
	}
}

int jSpecTool::RemovalStart(TH1* hist){
	//because often zeros at the start make trouble
	double max=hist->GetBinContent(hist->GetMaximumBin());
	double min=hist->GetBinContent(hist->GetMinimumBin());
	for(int i=1;i<=hist->GetNbinsX();i++){
		if(hist->GetBinContent(i)>min+((max-min)*0.05)){
			return i;
		}
	}
	return 1;
}
	
void jSpecTool::RemovalPrivate(TH1* hist){
	RemovalProcess(hist,gStart);
}

void jSpecTool::RemovalPublic(TH1* hist,bool zero){
	if(zero)RemovalPrep(hist);
	RemovalProcess(hist,RemovalStart(hist));
}
	
void jSpecTool::RemovalProcess(TH1* hist,int start){
	if(!hist->GetSumw2N())hist->Sumw2();

	bool Itter=true;
	short n=0;
	while(Itter){
		n++;
		Itter=false;
		ReMakeSpecBack(hist);
		vector<bool> bad(hist->GetNbinsX(),false);
		for(int i=start;i<=hist->GetNbinsX();i++){
			double Y=hist->GetBinContent(i);
			double E=hist->GetBinError(i);
			double B=specback->GetBinContent(i);
			if((Y+E)<B){
				Itter=true;
				for(int j=i-4;j<i+3;j++){
					if(j>=start&&(unsigned)j<bad.size())bad[j]=true;
				}
			}
		}
		for(int i=1;i<=hist->GetNbinsX();i++){
			if(bad[i-1]){
				double Y=hist->GetBinContent(i);
// 				double E=hist->GetBinError(i);
				double B=specback->GetBinContent(i);
				if(Y<B){
					hist->SetBinContent(i,B);
					//Add extra errors
				}
			}
		}
		if(n>50)Itter=false;
	}
}


void jSpecTool::Invert(){
    TH1* H=histin;
    if(H){
        histin=0;
        invert(H);
        NewInput(H);
        delete H;
    }
}
