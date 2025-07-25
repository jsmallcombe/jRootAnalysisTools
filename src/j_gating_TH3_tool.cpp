#include "j_gating_master.h"

ClassImp(jGatingToolTH3);


jGatingToolTH3::jGatingToolTH3(const char * input,int detach) : jGatingToolTH3(gROOT->FindObject(input),detach){}

jGatingToolTH3::jGatingToolTH3(TObject* input,int detach) : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame),
    fInputStore(nullptr), fBack(nullptr), fResult(nullptr), fResFullProj(nullptr),fBackFrac(0.0),
    fGateFrame(new jGateSubtractionFrame(this,3)),
    UpdateLock(false),THnBaseType(false),
    DetachedHead(gGlobalTH3UseHead),child(nullptr),
    UpdateLockSetting(true)
{    
TVirtualPad* hold=gPad;

    TGLayoutHints* ffExpandYLeft = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kLHintsLeft, 0, 0, 0, 0);
    TGLayoutHints* ffExpandRight = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kLHintsRight, 0, 0, 0, 0);
    AddFrame(fGateFrame,ffExpandYLeft);
    
    // default -1 uses gGlobalTH3UseHead setting
    if(detach==0)DetachedHead=false;
    if(detach==1)DetachedHead=true;
    if(DetachedHead){
//         child = new TGMainFrame(gClient->GetRoot(), 200, 200);
        child = new TGTransientFrame(gClient->GetRoot(),this,  200, 200);
        child->DontCallClose();  // disables the default WM close handler
        
        fResFrame=new jGatingFrameTH2(child, fResult, true);
        child->AddFrame(fResFrame,ffExpandRight);

        child->MapSubwindows();
        child->Resize();
        child->MapWindow();
        
    }else{
        fResFrame=new jGatingFrameTH2(this, fResult, true);
        AddFrame(fResFrame,ffExpandRight);
    }

    fGateFrame->Connect("OutputReady()","jGatingToolTH3",this,"DoHistogram()");
    fGateFrame->Connect("RequestProjection(Int_t)","jGatingToolTH3",this,"ChangeProjection(Int_t)");
    fGateFrame->Connect("BackModeChange()","jGatingToolTH3",this,"CallDoHistogram()");
    fGateFrame->Connect("UpdateClicked()","jGatingToolTH3",this,"CallDoHistogram()");
    
    
//     fResFrame->Connect("RequestTwoDee(Bool_t)","jGatingToolTH3",this,"RequestTwoDee(Bool_t)");
    fResFrame->SetTwoDeePass(&fResult, &fBack, &fResFullProj, &fBackFrac);
    
    MapSubwindows();
    Resize(GetDefaultSize());
    MapWindow();
    Init();
    
    // Moved the  histogram input out from the Constructor so Maping is done before the popup call etc. Maybe?
	UpdateInput(input);
    
    // Set (both) window name(s)
    if(fInputStore){
        SetWindowName(fInputStore->GetName());
    }
    
    RaiseWindow();
gPad=hold;
}
    
jGatingToolTH3::~jGatingToolTH3(){
// 	Closed(this);
    
    CleanResHist();
	if(fResFullProj)delete fResFullProj;
    
    if(DetachedHead)if(child)delete child;
    
	Cleanup(); 
}

void jGatingToolTH3::SetWindowName(const char * input) {
    TString FrameName=input;
    
    if(DetachedHead){
        child->SetWindowName(FrameName+"_SecondAxis");
        FrameName=FrameName+"_FirstAxis";
    }
    
    TGMainFrame::SetWindowName(FrameName);
}

//______________________________________________________________________________


void jGatingToolTH3::UpdateInput(const char * input){
    UpdateInput(gROOT->FindObject(input));
}

void jGatingToolTH3::UpdateInput(TObject* input){
    if(input==nullptr)return;
    
    if(input->IsA()->InheritsFrom("THnBase")){
        fInputStore=input; //Dont clone for a THn type
        THnBaseType=true;
    }
    if(input->IsA()->InheritsFrom("TH3")){
        fInputStore=input; //Dont clone for a TH3 type
        THnBaseType=false;
    }
    if(fInputStore){

        UpdateInput(); //Actually Process the input
    }
}


void jGatingToolTH3::ChangeProjection(const Int_t id)
{  
// 	xyz=id;
	UpdateInput();
}


//______________________________________________________________________________

void jGatingToolTH3::CleanResHist(){
    if(fBack)if(fBack!=fResult&&fBack!=fResFullProj) delete fBack;
    fBack=nullptr;  
  	if(fResult)delete fResult;
    fResult=nullptr;
}

// Replace histograms and pass new projection to gatingframe
// Subsequently gatingframe will "emit" and this frame will do the gate
// Called for new input histogram or change axis
void jGatingToolTH3::UpdateInput(){       
if(fInputStore==nullptr)return;
TVirtualPad* hold=gPad;

    CleanResHist();
	if(fResFullProj)delete fResFullProj;
    fResFullProj=nullptr;
    
    UpdateLock=false;
    
    if(THnBaseType)fGateFrame->UpdateInput((THnBase*)fInputStore, fResFullProj);
    else           fGateFrame->UpdateInput((TH1*)fInputStore, fResFullProj);
    
gPad=hold;
}

// The main gating function, which is called when child select_frame says so
void jGatingToolTH3::DoHistogram(){
if(fInputStore==nullptr)return;
if(UpdateLock) return;

    if(THnBaseType){
        // THn::Projection doesnt support the histogram-in-memory reuse of TH2/3
        CleanResHist();
        fBackFrac=fGateFrame->DoGateSubtract((THnBase*)fInputStore, fResult, fBack, fResFullProj);
    }else{
        fBackFrac=fGateFrame->DoGateSubtract((TH1*)fInputStore, fResult, fBack, fResFullProj);
    }
    
    fResult->SetLineColor(1);
    fResult->GetXaxis()->SetTitleOffset(1.0);//Fixed a problem from other lib with Yaxis title
    fResFrame->UpdateInput(fResult);

    if(DetachedHead){
        child->RaiseWindow();
//         child->SetFocus();
    }
        
    if(UpdateLockSetting)UpdateLock=true;
}

void jGatingToolTH3::CallDoHistogram(){
if(fInputStore==nullptr)return;
    UpdateLock=false;
	DoHistogram();
}

void jGatingToolTH3::Layout(){
    
    int W = GetWidth();
    int H = GetHeight();
    int W1 = W / 3.;
    if(fResFrame->TestThreeDee())W1 = W / 2;
    int W2 = W - W1;
    
    if(DetachedHead)W1=W;
    fGateFrame->MoveResize(0, 0, W1, H);
    if(!DetachedHead)fResFrame->MoveResize(W1, 0, W2, H);
}   

