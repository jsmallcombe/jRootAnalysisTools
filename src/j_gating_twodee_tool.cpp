// //
// //
// //	James gating GUI tool 1.2
// // 	27/10/16		16/10/2015
// //	james.smallcombe@outlook.com
// //
// //
// 

#include "j_gating_twodee_tool.h"
#include "j_gpad_tools.h"  // For gGlobalAskWindowName 


ClassImp(jGateToolTwoDee);


jGateToolTwoDee::jGateToolTwoDee(const char * input) : jGateToolTwoDee(gROOT->FindObject(input)){}

jGateToolTwoDee::jGateToolTwoDee(TObject* input) : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame)
{
TVirtualPad* hold=gPad;

    TH1* pass=nullptr;
    TString FrameName="";
    
    if(input!=nullptr){
        if(input->IsA()->InheritsFrom("TH2")){
            pass=(TH1*)input;
            FrameName=pass->GetName();
        }
    }
    
///// Handle window naming /////
        if(gGlobalAskWindowName){
            char* FrameReNamChar=new char[128];
            new TGInputDialog(gClient->GetRoot(),gClient->GetRoot(),"Rename Gate Tool Window",FrameName,FrameReNamChar);
            FrameName=FrameReNamChar;
        }
        
        if(FrameName.Length()){
            SetWindowName(FrameName);	
        }
/////    

    gJframe1=new jGateFrameTwoDee(this,pass,false);

    TGLayoutHints* ffExpand = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0);
    
    AddFrame(gJframe1, ffExpand);

    MapSubwindows();
    Resize(GetDefaultSize());
    MapWindow();

    gJframe1->Init();

gPad=hold;
}


void jGateToolTwoDee::UpdateInput(const char * input){
    UpdateInput(gROOT->FindObject(input));
}

void jGateToolTwoDee::UpdateInput(TObject* input){
    if(input!=nullptr){
        if(input->IsA()->InheritsFrom("TH2")){
            gJframe1->UpdateInput((TH1*)input);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ClassImp(jGateFrameTwoDee);


jGateFrameTwoDee::jGateFrameTwoDee(TGWindow *parent,TH1* input,bool ThreeDee) : TGHorizontalFrame(parent, 100, 100),
    fInputStore(nullptr),fProj(nullptr), fGate(nullptr), fResult(nullptr), fResFullProj(nullptr),
    xy(0), suffix(jGateSelectFrame::Iterator("")),
    fGateFrame(new jGateSelectFrame(this, fProj,(((int)ThreeDee)+1)*2)),
    fResFrame(new jGateResultFrame(this, &fResult, &fGate, &fResFullProj, fGateFrame->PointGateCentre(), ThreeDee)){
        // It may be better to initilise the frames after processing input histograms
        // so that they dont try to do their first draw with empty histograms
   
    TGLayoutHints* ffExpandYLeft = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kLHintsLeft, 0, 0, 0, 0);
    TGLayoutHints* ffExpandRight = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kLHintsRight, 0, 0, 0, 0);
        
    AddFrame(fGateFrame,ffExpandYLeft);
    AddFrame(fResFrame,ffExpandRight);

    fGateFrame->Connect("OutputReady()","jGateFrameTwoDee",this,"DoHistogram()");
    fGateFrame->Connect("RequestProjection(Int_t)","jGateFrameTwoDee",this,"ChangeProjection(Int_t)");
    
    fResFrame->Connect("RequestTwoDee(Bool_t)","jGateFrameTwoDee",this,"RequestTwoDee(Bool_t)");
        
	UpdateInput(input);
}
    
jGateFrameTwoDee::~jGateFrameTwoDee(){
	Cleanup(); 
}

void jGateFrameTwoDee::ChangeProjection(const Int_t id)
{  
	xy=id;
	UpdateInput();
}

//______________________________________________________________________________
void jGateFrameTwoDee::UpdateInput(TH1* input){ 
    if(input==nullptr)return;
	fInputStore=(TH1*)input->Clone(jGateSelectFrame::Iterator("GateStoreCopy"));
	UpdateInput();
}

//______________________________________________________________________________

// Replace histograms and pass new projection to gatingframe
// Subsequently gatingframe will "emit" and this frame will do the gate
// Called for new input histogram or change axis
void jGateFrameTwoDee::UpdateInput(){       
if(fInputStore==nullptr)return;
TVirtualPad* hold=gPad;

	if(fProj)delete fProj;

	fProj=hist_proj(fInputStore,xy,"proj"+suffix,true);
    // We decided to get rid of the overflow histgram view proj_flow from old class
    
    // May not be needed
	fProj->SetStats(0);
	fProj->SetTitle("");
	fProj->SetLineColor(1);

	if(fResFullProj)delete fResFullProj;
	fResFullProj=hist_gater_bin(1,fInputStore,xy,"fResFullProj"+suffix);
	fResFullProj->SetStats(0);	
	fResFullProj->SetTitle("");
	
	if(fResult)delete fResult;
	fResult=(TH1*)fResFullProj->Clone(("outputhist"+suffix).c_str());
	fResult->SetLineColor(1);
	fResult->GetXaxis()->SetTitleOffset(1.0);//Fixed a problem from other lib with Yaxis title

	fResFrame->ResetRange();
    fGateFrame->UpdateInput(fProj);
    
gPad=hold;
}

// The main gating function, which is called when daugter select_frame says so
void jGateFrameTwoDee::DoHistogram(){
if(fInputStore==nullptr)return;
	
    // Some of these could have been set by jGateSelectFrame emits
    // Or by having DoHistogram takes these as inputs and connecting though the signals
    double backfrack=fGateFrame->GetBackFrac();
    double backfrackfrac=fGateFrame->GetBackFracFrac();
    int gate_down=fGateFrame->GetGateBinDown(), gate_up=fGateFrame->GetGateBinUp();
    int background_mode=fGateFrame->GetBackMode();
    int back_down=fGateFrame->GetBackBinDown(), back_up=fGateFrame->GetBackBinUp();
    
	// hist_gater_bin *should* nicely fill the histogram matching the name if the TH1 exists
	// so we dont need to delete pointer fGate
	fGate=hist_gater_bin(gate_down,gate_up,fInputStore,xy,"fGate"+suffix);
    fGate->SetLineColor(1);
	fGate->GetXaxis()->SetTitleOffset(1.0);//Fixed a problem from other lib with Yaxis title
	
    // Note the "fResFullProj" projection used to make full and anti includes the overflow, but excludes the underflow bin
    // This is an intentional choice as often intentionally zeroed data may be sorted into the underflow bin
    // The underflow bin can be selected with manual sliders
    
	switch (background_mode) {
		case 1://full
            scaled_back_subtract(fGate,fResFullProj,backfrack,fResult,backfrackfrac);
			break;
		case 2://compton
            {
                TH1* compton_hist=hist_gater_bin(back_down,fInputStore,xy,"c_gate");
                scaled_back_subtract(fGate,compton_hist,backfrack,fResult,backfrackfrac);
                delete compton_hist;
            }
			break;
		case 3://anti gate
			{
				TH1* anti_hist=(TH1*)fResFullProj->Clone("antiback");
				anti_hist->Add(fGate,-1);
				anti_hist->Sumw2(kFALSE);
				scaled_back_subtract(fGate,anti_hist,backfrack,fResult,backfrackfrac);
				delete anti_hist;
			}
			break;
		case 4://none
			{
				TString hpt=fResult->GetName();
				fGate->Copy(*fResult);
				fResult->SetName(hpt);
			}
			break;
		default://manual // Compton // Antiate
			{
				TH1* manb_hist=hist_gater_bin(back_down,back_up,fInputStore,xy,"m_gate_2d");
                if(gate_down>back_down&&gate_up<back_up)manb_hist->Add(fGate,-1);//In special case remove the gated part
				manb_hist->Sumw2(kFALSE);
				scaled_back_subtract(fGate,manb_hist,backfrack,fResult,backfrackfrac);
				delete manb_hist;				
			}
			break;
	}
	
	fResult->SetTitle("");

    fResFrame->DrawHist();
}

