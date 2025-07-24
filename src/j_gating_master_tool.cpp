// //
// //
// //	James gating GUI tool 1.2
// // 	27/10/16		16/10/2015
// //	james.smallcombe@outlook.com
// //
// //
// 

#include "j_gating_master_tool.h"
#include "j_gpad_tools.h"  // For gGlobalAskWindowName 

ClassImp(jGatingToolTHnMany);


jGatingToolTHnMany::jGatingToolTHnMany(THnBase* input,TString OverrideName) : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame),
    fInputStore(nullptr), fBack(nullptr), fResult(nullptr), fResFullProj(nullptr),fBackFrac(0.0),   
    fGateFrame(nullptr), fResFrameTHn(nullptr), fResFrameTH3(nullptr), child(nullptr)
{    
TVirtualPad* hold=gPad;
if(!input)return;

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

    
//         child->MapSubwindows();
//         child->Resize();
//         child->MapWindow();
    
	UpdateInput(input,OverrideName);
    DoHistogram();//Calling manually for special case of initlisations
    
    if(fResult){

        if(Ndim>4){
//new THnI("Dummy","Dummy",N-1,DummyBins,DummyLow,DummyHigh)
            fResFrameTHn=new jGatingToolTHnMany(fResult,ChildName);
            child=(TGMainFrame*)fResFrameTHn;
        }else{
            fResFrameTH3=new jGatingToolTH3(fResult,false,ChildName);
            child=(TGMainFrame*)fResFrameTH3;
        }
        
        child->DontCallClose();  // disables the default WM close handler
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


//______________________________________________________________________________


void jGatingToolTHnMany::UpdateInput(THnBase* input, TString OverrideName){
    if(input==nullptr)return;
    
    if(input->IsA()->InheritsFrom("THnBase")){
        fInputStore=input; //Dont clone for a THn type
    }
    
    if(fInputStore){
     
        ///// Handle window naming /////
        TString FrameName=fInputStore->GetName();
        FrameName=FrameName+"_"+Ndim;

        if(OverrideName.Length()){
            FrameName=OverrideName;
        }else if(gGlobalAskWindowName){
            char* FrameReNamChar=new char[128];
            new TGInputDialog(gClient->GetRoot(),gClient->GetRoot(),"Rename Gate Tool Window",FrameName,FrameReNamChar);
            FrameName=FrameReNamChar;
        }
        
        if(FrameName.Length()){
            SetWindowName(FrameName);
        }
        
        int ChildN=Ndim-1;
        ChildName=FrameName+"_"+ChildN;
        
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
TGTransientFrame* PopUp=MakeTH3Popup(this);

    CleanResHist();
	if(fResFullProj)delete fResFullProj;
    fResFullProj=nullptr;
       
    fGateFrame->UpdateInput(fInputStore, fResFullProj);
    
if(PopUp){PopUp->CloseWindow();}
gPad=hold;
}

// The main gating function, which is called when child select_frame says so
void jGatingToolTHnMany::DoHistogram(){
if(fInputStore==nullptr)return;
    
    CleanResHist();
    fBackFrac=fGateFrame->DoGateSubtract(fInputStore, fResult, fBack, fResFullProj);
    
//  When called during the constuctor, child is not yet set so this is skipped 
    if(child){
        cout<<endl<<"ChildName "<<ChildName;;
        if(fResFrameTHn==child)fResFrameTHn->UpdateInput(fResult,ChildName);
        else if(fResFrameTH3==child) fResFrameTH3->UpdateInput(fResult,ChildName);
        child->RaiseWindow();
    }
        
}

