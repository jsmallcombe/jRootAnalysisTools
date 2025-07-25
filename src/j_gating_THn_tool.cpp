#include "j_gating_master.h"

ClassImp(jGatingToolTHnMany);


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


jGatingToolTHnMany::jGatingToolTHnMany(THnBase* input) : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame),
    fInputStore(nullptr), fBack(nullptr), fResult(nullptr), fResFullProj(nullptr),fBackFrac(0.0),   
    fGateFrame(nullptr), fResFrameTHn(nullptr), fResFrameTH3(nullptr), child(nullptr)
{    
TVirtualPad* hold=gPad;
if(!input)return; //Unlike the lower Ndim classes, this must be initilised with input


	Ndim=input->GetNdimensions();
    if(Ndim<4)return;
    
    fGateFrame=new jGateSubtractionFrame(this,Ndim);

    AddFrame(fGateFrame,new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0));

    fGateFrame->Connect("BackModeChange()","jGatingToolTHnMany",this,"DoHistogram()");
    fGateFrame->Connect("UpdateClicked()","jGatingToolTHnMany",this,"DoHistogram()");
    fGateFrame->Connect("RequestProjection(Int_t)","jGatingToolTHnMany",this,"UpdateInput()");
    // In this version UpdateInput will NOT call result frame Update, that only comes from DoHistogram
    // which is NOT called automatically except at initilisation

    MapSubwindows();
    Resize(GetDefaultSize());
    MapWindow();
    Init();
    
	UpdateInput(input);
    
    DoHistogram();// Calling manually for special case of initlisations
    // Need resultant THn/TH1 fResult to initilise child frames to correct dimensionality 
    
    if(fResult){
        if(Ndim>4){
//new THnI("Dummy","Dummy",N-1,DummyBins,DummyLow,DummyHigh)
            fResFrameTHn=new jGatingToolTHnMany(fResult);
            child=(TGMainFrame*)fResFrameTHn;
        }else{
            fResFrameTH3=new jGatingToolTH3(fResult,false);
            child=(TGMainFrame*)fResFrameTH3;
        }
//  child->MapSubwindows();child->Resize();child->MapWindow();
        
        child->DontCallClose();  // disables the default WM close handler
    }
    
    // Set (both) window name(s)
    if(fInputStore){
        SetWindowName(fInputStore->GetName());
    }
    
    RaiseWindow();
gPad=hold;
}
    
jGatingToolTHnMany::~jGatingToolTHnMany(){
// 	Closed(this);
    
    CleanResHist();
	if(fResFullProj)delete fResFullProj;
    if(child)delete child;
    
	Cleanup(); 
}


void jGatingToolTHnMany::SetWindowName(const char * input) {
    TString FrameName=input;
    FrameName=FrameName+"_"+Ndim;
    
    int ChildN=Ndim-1;
    TString ChildName=FrameName;
    
    if(child==fResFrameTH3)ChildName=ChildName+"_"+ChildN;
    
    TGMainFrame::SetWindowName(FrameName);
    if(child)child->SetWindowName(ChildName);
}

//______________________________________________________________________________


void jGatingToolTHnMany::UpdateInput(THnBase* input){
    if(input==nullptr)return;
    
    // On the rare occasion of giving an updated input after initilisation Ndim must be the same as initilsation
    if(Ndim==input->GetNdimensions()){
        fInputStore=input; //Dont clone for a THn type
    }
    
    if(fInputStore){        
        UpdateInput(); //Actually Process the input
    }
}


//______________________________________________________________________________

void jGatingToolTHnMany::CleanResHist(){
    if(fBack)if(fBack!=fResult&&fBack!=fResFullProj) delete fBack;
    fBack=nullptr;  
  	if(fResult)delete fResult;
    fResult=nullptr;
}

// Replace histograms and pass new projection to gatingframe
// The emit from fGateFrame->UpdateInput is not a signal accepted by jGatingToolTHnMany
// So processing will stop at the end of this function
// Called for new input histogram or change axis
void jGatingToolTHnMany::UpdateInput(){       
if(fInputStore==nullptr)return;
TVirtualPad* hold=gPad;

    CleanResHist();
	if(fResFullProj)delete fResFullProj;
    fResFullProj=nullptr;
       
    fGateFrame->UpdateInput(fInputStore, fResFullProj);
    
gPad=hold;
}

// The main gating function, which is called when child select_frame says so
void jGatingToolTHnMany::DoHistogram(){
if(fInputStore==nullptr)return;
    
    CleanResHist();
    fBackFrac=fGateFrame->DoGateSubtract(fInputStore, fResult, fBack, fResFullProj);
    
//  When called during the constuctor, child is not yet set so this is skipped 
    if(child){
        if(fResFrameTHn==child)fResFrameTHn->UpdateInput(fResult);
        else if(fResFrameTH3==child) fResFrameTH3->UpdateInput(fResult);
        child->RaiseWindow();
    }
        
}


