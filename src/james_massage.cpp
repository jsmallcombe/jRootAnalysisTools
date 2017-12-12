//
//
//	James data tweaking GUI tool 1.0
// 	27/10/16		16/10/2015
//	james.smallcombe@outlook.com
//
//

#include "james_massage.h"
#include "james_hist_formatting.h"

ClassImp(jmassage);

int jmassage::jmassage_iterator = 0;

vector<string> jmassage::BackOpt={"BackOrder2","BackOrder4","BackOrder6","BackOrder8","BackSmoothing3","BackSmoothing5","BackSmoothing7","BackSmoothing9","BackSmoothing11","BackSmoothing13","BackIncreasingWindow","Compton"};

jmassage::jmassage(TObject* input) : TGMainFrame(gClient->GetRoot(), 100, 100,kVerticalFrame),histin(0),histsub(0),specback(0){
TVirtualPad* hold=gPad;

	if(!input)return;
	if(!input->IsA()->InheritsFrom("TH1"))return;

	histin=(TH1*)input->Clone(("massahist"+make_iterator()).c_str());
	histsub=(TH1*)input->Clone(("massasubhist"+make_iterator()).c_str());
	
	TGLayoutHints* ffExpandXpad = new TGLayoutHints(kLHintsExpandX, 1, 1, 1, 1);
		
	SetCleanup(kDeepCleanup);
	SetWindowName(input->GetName());
	
	TGHorizontalFrame* fHframe0 = new TGHorizontalFrame(this, 0, 0, 0);  //create a frame, filled with objects horizontally

	fCheck0 = new TGCheckButton(fHframe0,"Remove Oversub   ");// A tick box with hover text belonging to a parent frame
	fCheck0->SetState(kButtonUp);
	fCheck0->Connect(" Clicked()", "jmassage", this,"DoUpdate()");
	fCheck0->SetToolTipText("Remove over subtraction with the current background");
	
	fCheck1 = new TGCheckButton(fHframe0,"Hide Bin Errors   ");
	fCheck1->SetState(kButtonDown);
	fCheck1->Connect(" Clicked()", "jmassage", this,"DoUpdate()");
	fCheck1->SetToolTipText("Hide Bin Errors on drawn histograms");
	
	fCheck2 = new TGCheckButton(fHframe0,"Remove Background   ");// A tick box with hover text belonging to a parent frame
	fCheck2->SetState(kButtonUp);
	fCheck2->Connect(" Clicked()", "jmassage", this,"DoUpdate()");
	fCheck2->SetToolTipText("Subtract the background");	

	fHframe0->AddFrame(fCheck0);
	fHframe0->AddFrame(fCheck1);
	fHframe0->AddFrame(fCheck2);

	fCanvas1 = new TRootEmbeddedCanvas(("Embedded"+make_iterator()).c_str(), this, 800, 600);
	fCanvas1->GetCanvas()->SetName(("ResultCan"+make_iterator()).c_str());
		//Results panel

// 	fCanvas1->GetCanvas()->SetFillColor(33);
// 	fCanvas1->GetCanvas()->SetBorderMode(0);
// 	fCanvas1->GetCanvas()->SetFrameFillColor(10);
// 	fCanvas1->GetCanvas()->SetMargin(0.1,0.01,0.05,0.01);	

	TQObject::Connect(fCanvas1->GetCanvas(), "ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0,0,"ClickPeakDrawConnect(Int_t,Int_t,Int_t,TObject*)");
		// rebin bar
	TGHorizontalFrame* rebinframe = new TGHorizontalFrame(this, 0, 0, 0);
	TGLabel *label = new TGLabel(rebinframe, "  Rebin Histogram   ");
	rebinframe->AddFrame(label);	
	fHslider1 = new TGHSlider(rebinframe, 9, kSlider2);
	fHslider1->SetPosition(0);
	fHslider1->Connect("PositionChanged(Int_t)", "jmassage", this, "DoUpdate()");
	rebinframe->AddFrame(fHslider1, ffExpandXpad);
	
	TGHorizontalFrame* orderframe = new TGHorizontalFrame(this, 0, 0, 0);
	label = new TGLabel(orderframe, "  Background Opt   ");
	orderframe->AddFrame(label);
	fHslider2 = new TGHSlider(orderframe, abs(BackOpt.size()-1), kSlider2);
	fHslider2->SetPosition(0);
	fHslider2->Connect("PositionChanged(Int_t)", "jmassage", this, "UpdateSpecBack()");
	orderframe->AddFrame(fHslider2, ffExpandXpad);
	
	fTeh1 = new TGTextEntry(orderframe);
	fTeh1->SetDefaultSize(200,25);
	fTeh1->SetAlignment (kTextLeft);
	fTeh1->SetEnabled(kFALSE);
	orderframe->AddFrame(fTeh1);
	
	
	TGHorizontalFrame* smoothframe = new TGHorizontalFrame(this, 0, 0, 0);
	label = new TGLabel(smoothframe, "  Smoothing N       ");
	smoothframe->AddFrame(label);
	fHslider3 = new TGHSlider(smoothframe, 50, kSlider2);
	fHslider3->SetPosition(15);
	fHslider3->Connect("PositionChanged(Int_t)", "jmassage", this, "UpdateSpecBack()");
	smoothframe->AddFrame(fHslider3, ffExpandXpad);
	
	fTeh2 = new TGTextEntry(smoothframe);
	fTeh2 ->SetDefaultSize(50,25);
	fTeh2 ->SetAlignment (kTextLeft);
	fTeh2 ->SetEnabled(kFALSE);
	smoothframe->AddFrame(fTeh2);
	
	fCheck3 = new TGCheckButton(smoothframe," OverSubMode ");
	fCheck3->SetState(kButtonDown);
	fCheck3->Connect(" Clicked()", "jmassage", this,"UpdateSpecBack()");
	fCheck3->SetToolTipText("Background will do anti-oversubtraction iterations background");	
	smoothframe->AddFrame(fCheck3);
	
	AddFrame(fHframe0, new TGLayoutHints(kLHintsCenterX, 3, 3, 3, 3));
	AddFrame(fCanvas1,new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 3, 3, 3, 3));
	AddFrame(rebinframe,ffExpandXpad);
	AddFrame(orderframe,ffExpandXpad);
	AddFrame(smoothframe,ffExpandXpad);

	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();

	UpdateSpecBack();
	
gPad=hold;
}


//______________________________________________________________________________
jmassage::~jmassage()
{
   if(histin){delete histin;}
   if(specback){delete specback;}
   if(histsub){delete histsub;}

   // Clean up
   Cleanup();
}

//______________________________________________________________________________
// void jmassage::DoClose()
// {
//    // Called when window is closed via the window manager
//    
//    cout<<endl<<"DOO0000000OM"<<endl;
//    delete this;
// }


void jmassage::UpdateSpecBack(){  
	unsigned int opt=fHslider2->GetPosition();
	N=fHslider3->GetPosition()+10;
	StrOpt="";
	if(opt<BackOpt.size())StrOpt=BackOpt[opt];
	fTeh1->SetText(StrOpt.c_str());
	fTeh2->SetText(std::to_string(N).c_str());


	if(fCheck3->GetState()){
		if(histsub){delete histsub;}
		histsub=(TH1*)histin->Clone(("massasubhist"+make_iterator()).c_str());
		RemovalProcess(histsub);
	}else{
		ReMakeSpecBack(histin);
	}

	DoUpdate();
}


string jmassage::make_iterator(){
	stringstream ss;
	ss << jmassage_iterator;
	jmassage_iterator++;
	return ss.str();
}

void jmassage::ReMakeSpecBack(TH1* hist){
	if(hist){
		if(specback){delete specback;}
		specback= TSpectrum::StaticBackground(hist,N,StrOpt.c_str());
		specback->SetLineColor(6);
	}
}



void jmassage::DoUpdate(){TVirtualPad* hold=gPad;
	if(!histin)return;
	
	
	fCanvas1->GetCanvas()->cd();
	
	unsigned short rebin=fHslider1->GetPosition()+1;
	
	TH1 *H,*S=0;

	if(fCheck0->GetState())H=histsub;
	else H=histin;

	if(fCheck1->GetState())H=DrawCopyHistOpt(H);//Needed if any functions have been drawn
	else H=H->DrawCopy();
	
	if(specback){
		if(fCheck2->GetState()){
			if(!H->GetSumw2N())H->Sumw2();
			H->Add(specback,-1.);
		}else{
			S=specback->DrawCopy("same");
		}
	}

	if(rebin>1){
		H->Rebin(rebin);
		if(S)S->Rebin(rebin);
	}

	fCanvas1->GetCanvas()->Modified();
	fCanvas1->GetCanvas()->Update();
gPad=hold;
}

void jmassage::RemovalProcess(TH1* hist){
	if(!hist->GetSumw2N())hist->Sumw2();
	bool Itter=true;
	double max=hist->GetBinContent(hist->GetMaximumBin());
	int start=0;//because often zeros at the start make trouble
	
	for(int i=1;i<=hist->GetNbinsX();i++){
		double Y=hist->GetBinContent(i);
		if(!start&&Y>max*0.05)start=i;
		if(Y<0){
			hist->SetBinContent(i,0);
		}
	}
	
	while(Itter){
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
					if(j>=start&&j<bad.size())bad[j]=true;
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
	}
}