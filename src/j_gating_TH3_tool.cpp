// //
// //
// //	James gating GUI tool 1.2
// // 	27/10/16		16/10/2015
// //	james.smallcombe@outlook.com
// //
// //
// 

#include "j_gating_TH3_tool.h"
#include "j_gpad_tools.h"  // For gGlobalAskWindowName 


ClassImp(jGatingToolTH3);


jGatingToolTH3::jGatingToolTH3(const char * input) : jGatingToolTH3(gROOT->FindObject(input)){}

jGatingToolTH3::jGatingToolTH3(TObject* input) : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame)
{
TVirtualPad* hold=gPad;

    TH1* pass=nullptr;
    TString FrameName="";
    
    if(input!=nullptr){
        if(input->IsA()->InheritsFrom("TH3")){
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

//     gJframe1=new jGatingFrameTH3(this,pass);
    gJframe1=new jGatingFrameTH3(this,nullptr);

    TGLayoutHints* ffExpand = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0);
    
    AddFrame(gJframe1, ffExpand);

    MapSubwindows();
    Resize(GetDefaultSize());
    MapWindow();
    gJframe1->Init();
    
    // Moved the  histogram input out from the Constructor so Maping is done before the popup call etc. Maybe?
    gJframe1->UpdateInput(pass);

gPad=hold;
}


void jGatingToolTH3::UpdateInput(const char * input){
    UpdateInput(gROOT->FindObject(input));
}

void jGatingToolTH3::UpdateInput(TObject* input){
    if(input!=nullptr){
        if(input->IsA()->InheritsFrom("TH3")){
            gJframe1->UpdateInput((TH1*)input);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


jGatingFrameTH3::jGatingFrameTH3(TGWindow *parent,TH1* input) : TGHorizontalFrame(parent, 100, 100),
    fInputStore(nullptr),fProj(nullptr), fBack(nullptr), fResult(nullptr), fResFullProj(nullptr),fBackFrac(0.0),
    fGateFrame(new jGateSubtractionFrame(this,3)),
    fResFrame(new jGatingFrameTH2(this, fResult, true)),
    UpdateLock(false),UpdateLockSetting(true)
{
        // It may be better to initilise the frames after processing input histograms
        // so that they dont try to do their first draw with empty histograms
           
    TGLayoutHints* ffExpandYLeft = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kLHintsLeft, 0, 0, 0, 0);
    TGLayoutHints* ffExpandRight = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY | kLHintsRight, 0, 0, 0, 0);
        
    AddFrame(fGateFrame,ffExpandYLeft);
    AddFrame(fResFrame,ffExpandRight);

    fGateFrame->Connect("OutputReady()","jGatingFrameTH3",this,"DoHistogram()");
    fGateFrame->Connect("RequestProjection(Int_t)","jGatingFrameTH3",this,"ChangeProjection(Int_t)");
    fGateFrame->Connect("BackModeChange()","jGatingFrameTH3",this,"CallDoHistogram()");
    fGateFrame->Connect("UpdateClicked()","jGatingFrameTH3",this,"CallDoHistogram()");
    
//     fResFrame->Connect("RequestTwoDee(Bool_t)","jGatingFrameTH3",this,"RequestTwoDee(Bool_t)");
    fResFrame->SetTwoDeePass(&fResult, &fBack, &fResFullProj, &fBackFrac);
    
	UpdateInput(input);
}
    
jGatingFrameTH3::~jGatingFrameTH3(){
// 	Closed(this);
	Cleanup(); 
}

void jGatingFrameTH3::ChangeProjection(const Int_t id)
{  
// 	xyz=id;
	UpdateInput();
}

//______________________________________________________________________________
void jGatingFrameTH3::UpdateInput(TH1* input){ 
    if(input==nullptr)return;
	fInputStore=input; //Dont clone for a TH3 type
	UpdateInput();
}

//______________________________________________________________________________

// Replace histograms and pass new projection to gatingframe
// Subsequently gatingframe will "emit" and this frame will do the gate
// Called for new input histogram or change axis
void jGatingFrameTH3::UpdateInput(){       
if(fInputStore==nullptr)return;
TVirtualPad* hold=gPad;
TGTransientFrame* PopUp=MakeTH3Popup(this);

	if(fBack)if(fBack!=fResult&&fBack!=fResFullProj) delete fBack;
    fBack=nullptr;  
  	if(fResult)delete fResult;
    fResult=nullptr;
	if(fResFullProj)delete fResFullProj;
    fResFullProj=nullptr;
    
    UpdateLock=false;
    
    fGateFrame->UpdateInput(fInputStore, fResFullProj);
    
if(PopUp){PopUp->CloseWindow();}
gPad=hold;
}

// The main gating function, which is called when daugter select_frame says so
void jGatingFrameTH3::DoHistogram(){
if(fInputStore==nullptr)return;
if(UpdateLock) return;
	
    fBackFrac=fGateFrame->DoGateSubtract(fInputStore, fResult, fBack, fResFullProj);
    
    fResFrame->UpdateInput(fResult);
    
    if(UpdateLockSetting)UpdateLock=true;
}

void jGatingFrameTH3::CallDoHistogram(){
if(fInputStore==nullptr)return;
    UpdateLock=false;
	DoHistogram();
}

void jGatingFrameTH3::Layout(){
    int W = GetWidth();
    int H = GetHeight();
    int W1 = W / 3.;
    if(fResFrame->TestThreeDee())W1 = W / 2;
    int W2 = W - W1;

    fGateFrame->MoveResize(0, 0, W1, H);
    fResFrame->MoveResize(W1, 0, W2, H);
}   

ClassImp(jGatingFrameTH3);
