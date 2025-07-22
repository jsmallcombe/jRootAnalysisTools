// //
// //
// //	James gating GUI tool 1.2
// // 	27/10/16		16/10/2015
// //	james.smallcombe@outlook.com
// //
// //
// 

#include "j_gating_TH2_tool.h"
#include "j_gpad_tools.h"  // For gGlobalAskWindowName 


ClassImp(jGatingToolTH2);


jGatingToolTH2::jGatingToolTH2(const char * input) : jGatingToolTH2(gROOT->FindObject(input)){}

jGatingToolTH2::jGatingToolTH2(TObject* input) : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame)
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

    gJframe1=new jGatingFrameTH2(this,pass,false);

    TGLayoutHints* ffExpand = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0);
    
    AddFrame(gJframe1, ffExpand);

    MapSubwindows();
    Resize(GetDefaultSize());
    MapWindow();

    gJframe1->Init();

gPad=hold;
}


void jGatingToolTH2::UpdateInput(const char * input){
    UpdateInput(gROOT->FindObject(input));
}

void jGatingToolTH2::UpdateInput(TObject* input){
    if(input!=nullptr){
        if(input->IsA()->InheritsFrom("TH2")){
            gJframe1->UpdateInput((TH1*)input);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ClassImp(jGatingFrameTH2);

jGatingFrameTH2::jGatingFrameTH2(TGWindow *parent,TH1* input,bool DeeThree) : TGHorizontalFrame(parent, 100, 100),
    fInputStore(nullptr),fProj(nullptr), fBack(nullptr), fResult(nullptr), fResFullProj(nullptr),
    fBackFrac(0.0),
    ThreeDee(0), xy(0), suffix(jGateSelectFrame::Iterator("")),
    fBackTwo(nullptr), fResultTwo(nullptr), fResFullProjTwo(nullptr),
    fGateFrame(new jGateSubtractionFrame(this, fProj,2)),
    fResFrame(new jGateResultFrame(this, &fResult, &fBack, &fResFullProj, &fBackFrac, fGateFrame->PointGateCentre(), DeeThree)){
        // It may be better to initilise the frames after processing input histograms
        // so that they dont try to do their first draw with empty histograms
   
    TGLayoutHints* ffExpandYLeft = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kLHintsLeft, 0, 0, 0, 0);
    TGLayoutHints* ffExpandRight = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kLHintsRight, 0, 0, 0, 0);
        
    AddFrame(fGateFrame,ffExpandYLeft);
    AddFrame(fResFrame,ffExpandRight);

    fGateFrame->Connect("OutputReady()","jGatingFrameTH2",this,"DoHistogram()");
    fGateFrame->Connect("RequestProjection(Int_t)","jGatingFrameTH2",this,"ChangeProjection(Int_t)");
    
    fResFrame->Connect("RequestTwoDee(Bool_t)","jGatingFrameTH2",this,"RequestTwoDee(Bool_t)");
        
	UpdateInput(input);
}
    
jGatingFrameTH2::~jGatingFrameTH2(){
    if(fInputStore){delete fInputStore;}
	Cleanup(); 
}

void jGatingFrameTH2::ChangeProjection(const Int_t id)
{  
	xy=id;
	UpdateInput();
}

//______________________________________________________________________________
void jGatingFrameTH2::UpdateInput(TH1* input){ 
    if(input==nullptr)return;
	fInputStore=(TH1*)input->Clone(jGateSelectFrame::Iterator("GateStoreCopy"));
	UpdateTypeSwitch();
}

//______________________________________________________________________________

// Toggle the current 2D vs 1D opperation
void jGatingFrameTH2::RequestTwoDee(const bool DoThreeDee){
    if(DoThreeDee==ThreeDee){
        cout<<endl<<"jGatingFrameTH2::RequestTwoDee(const bool) CALL ERROR"<<endl;
    }
    
    if(!ThreeDee&&DoThreeDee){
        if(fBack)delete fBack;
        if(fResult)delete fResult;
        if(fResFullProj)delete fResFullProj;
    }
    
    ThreeDee=DoThreeDee;
    fBack=nullptr;
    fResult=nullptr;
    fResFullProj=nullptr;
    
    if(ThreeDee){
        HideFrame(fGateFrame); 
    }else{
        ShowFrame(fGateFrame);
    }
    
    UpdateTypeSwitch();
    
    TGFrame *parent = (TGFrame *)this->GetParent();
    parent->Layout();
}
    
//______________________________________________________________________________

// In "2D mode" we simply pass new histograms to resultframes
void jGatingFrameTH2::UpdateTypeSwitch(){     
    if(ThreeDee){
        
        // We are trusting the 3D level frame to have called jGatingFrameTH2::SetTwoDeePass()
        fBack=*fBackTwo;
        fResult=*fResultTwo;
        fResFullProj=*fResFullProjTwo;
        fBackFrac=*fBackFracTwo;
        
        fResFrame->DrawHist();
    }else{
        UpdateInput();
    }
}

//______________________________________________________________________________

// Replace histograms and pass new projection to gatingframe
// Subsequently gatingframe will "emit" and this frame will do the gate
// Called for new input histogram OR change axis
void jGatingFrameTH2::UpdateInput(){       
if(fInputStore==nullptr)return;
TVirtualPad* hold=gPad;

	if(fProj)delete fProj;

	fProj=fGateFrame->ProjectAxisByBin(fInputStore,xy,"proj"+suffix);
    // We decided to get rid of the overflow histgram view proj_flow from old class
    
    // May not be needed
	fProj->SetStats(0);
	fProj->SetTitle("");
	fProj->SetLineColor(1);

	if(fResFullProj)delete fResFullProj;
	fResFullProj=fGateFrame->GateAxisByBin(fInputStore,xy,1,-1,"ResFullProj"+suffix);
	fResFullProj->SetStats(0);	
	fResFullProj->SetTitle("");
	
	if(fResult)delete fResult;
	if(fBack)if(fBack!=fResult&&fBack!=fResFullProj) delete fBack;
    
	fResFrame->ResetRange();
    fGateFrame->UpdateInput(fProj);
    
gPad=hold;
}

// The main gating function, which is called when daugter select_frame says so
void jGatingFrameTH2::DoHistogram(){
if(fInputStore==nullptr)return;
	
    // Some of these could have been set by jGateSelectFrame emits
    // Or by having DoHistogram takes these as inputs and connecting though the signals
    double backfrack=fGateFrame->GetBackFrac();
    double backfrackfrac=fGateFrame->GetBackFracFrac();
    int gate_down=fGateFrame->GetGateBinDown(), gate_up=fGateFrame->GetGateBinUp();
    int background_mode=fGateFrame->GetBackMode();
    int back_down=fGateFrame->GetBackBinDown(), back_up=fGateFrame->GetBackBinUp();
    
	// fGateFrame->GateAxisByBin *should* nicely fill the histogram matching the name if the TH1 exists
	// so we dont need to delete pointers except for when changing axis, handled by UpdateInput
	fResult=fGateFrame->GateAxisByBin(fInputStore,xy,gate_down,gate_up,"Gated"+suffix);
    fResult->SetLineColor(1);
    fResult->GetXaxis()->SetTitleOffset(1.0);//Fixed a problem from other lib with Yaxis title
	fResult->SetTitle("");

    // Note the projection "fResFullProj" used to make "full" and "anti" background options
    // include the overflow bins, but excludes the underflow bin.
    // This is an intentional choice, as often intentionally zeroed data may be sorted into the underflow bin
    // The underflow bin can be selected with manual sliders

	switch (background_mode) {
		case 1://full
                fBack=fResFullProj;
			break;
		case 2://compton
                fBack=fGateFrame->GateAxisByBin(fInputStore,xy,back_down,-1,"Back");
			break;
		case 3://anti gate
			{
				fBack=(TH1*)fResFullProj->Clone(TString(fResFullProj->GetName()).ReplaceAll("ResFullProj", "Back"));
				fBack->Add(fResult,-1);
				fBack->Sumw2(kFALSE);//Important as the Add is not an arithmetic subtraction, but an exact data removal
			}
			break;
		case 4://none
			{
                fBack=fResult;
			}
			break;
		default:  //manual 
			{
				fBack=fGateFrame->GateAxisByBin(fInputStore,xy,back_down,back_up,"Back");
                if(gate_down>back_down&&gate_up<back_up){
                    fBack->Add(fResult,-1);//In special case remove the gated part
                    fBack->Sumw2(kFALSE);
                }				
			}
			break;
	}
	
	if(fResult!=fBack)fBackFrac=fGateFrame->ScaledBackgroundSubtract(fResult,fBack,backfrack,backfrackfrac);
    else fBackFrac=1;

    fResFrame->DrawHist();
}

