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
    fInputStore(nullptr), fBack(nullptr), fResult(nullptr), fResFullProj(nullptr),
    fBackFrac(0.0),
    ThreeDee(0), 
    fBackTwo(nullptr), fResultTwo(nullptr), fResFullProjTwo(nullptr),
    fGateFrame(new jGateSubtractionFrame(this, 2)),
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
    
	if(fBack)if(fBack!=fResult&&fBack!=fResFullProj) delete fBack;
	if(fResFullProj)delete fResFullProj;
	if(fResult)delete fResult;
    
	Cleanup(); 
}

void jGatingFrameTH2::ChangeProjection(const Int_t id)
{  
// 	xyz=id;
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

    // Reset the range of the result frame which otherwise keeps the axis zoom the same when gates are changed
	fResFrame->ResetRange();
        
    // Decided to keep ownership and deletion of gated histograms in this class 
    // and to pass to the jGateSubtractionFrame functions by reference each time
    // rather than setting TH1** at fGateFrame initilisation time
    // this *should* make it easy to template functions for different matrix types ...
	if(fBack)if(fBack!=fResult&&fBack!=fResFullProj) delete fBack;
    fBack=nullptr;  
  	if(fResult)delete fResult;
    fResult=nullptr;
	if(fResFullProj)delete fResFullProj;
    fResFullProj=nullptr;
    
    fGateFrame->UpdateInput(fInputStore, fResFullProj);
//     jGateSubtractionFrame::UpdateInput() sets projection histogram and calls parent
//     jGateSelectFrame::UpdateInput() which in turn calls jGateSelectFrame::DoHistogram()
//     at the end of that function the signal Emit("OutputReady()"); is called
//     through signal slot mechanism, that calls this jGatingFrameTH2::DoHistogram()
    
//     Creating fResFullProj at this point is unnecessary/complex for 1D projections
//     but it is efficient at higher dim, and we are trying to keep the code the same
    
gPad=hold;
}

// The main gating function, which is called when daugter select_frame says so
void jGatingFrameTH2::DoHistogram(){
if(fInputStore==nullptr)return;
	
    fBackFrac=fGateFrame->DoGateSubtract(fInputStore, fResult, fBack, fResFullProj);
    
    fResult->SetLineColor(1);
    fResult->GetXaxis()->SetTitleOffset(1.0);//Fixed a problem from other lib with Yaxis title
    fResFrame->DrawHist();
    
}

