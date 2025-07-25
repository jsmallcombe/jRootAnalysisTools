#include "j_gating_master.h"


TGMainFrame* jGatingToolSelector(const char * input){
    return jGatingToolSelector(gROOT->FindObject(input));
}

TGMainFrame* jGatingToolSelector(TObject* input){
    if(input==nullptr)return nullptr;
    
    TGTransientFrame* PopUp=nullptr;
    
    /// Handle window naming /////
    TString FrameName;
    if(input->IsA()->InheritsFrom("TNamed"))FrameName=((TNamed*)input)->GetName();
    
    if(gGlobalAskGateWindowName){
        char* FrameReNamChar=new char[128];
        new TGInputDialog(gClient->GetRoot(),gClient->GetRoot(),"Rename Gate Tool Window",FrameName,FrameReNamChar);
        FrameName=FrameReNamChar;
    }
    
    TGMainFrame* ret=nullptr;
    if(input->IsA()->InheritsFrom("TH3")){
        PopUp=MakeTH3Popup();
        ret= new jGatingToolTH3((TH1*)input);
    }else if(input->IsA()->InheritsFrom("TH2")){
        ret= new jGatingToolTH2((TH1*)input);
    }else if(input->IsA()->InheritsFrom("THnBase")){
        PopUp=MakeTH3Popup();
        if(dynamic_cast<THnBase*>(input)->GetNdimensions()>3){
            ret= new jGatingToolTHnMany((THnBase*)input);
        }else{
            ret= new jGatingToolTH3((THnBase*)input);
        }
    }
    
/// Handle window naming /////
    if(ret){
        if(FrameName.Length()){
            ret->SetWindowName(FrameName);
        }
    }
    
    if(PopUp){PopUp->CloseWindow();}
    
    return ret;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
	
#include <TGIcon.h>

TGTransientFrame* MakeTH3Popup(){
	
// 	return nullptr;
    TGTransientFrame* popup=new TGTransientFrame(gClient->GetRoot(), gClient->GetRoot(), 400, 200, kHorizontalFrame);

    TGLayoutHints *fL1 = new TGLayoutHints(kLHintsCenterY | kLHintsExpandX, 5, 20, 0, 0);

    TGIcon *fIcon = new TGIcon(popup, popup->GetClient()->GetPicture("mb_stop_s.xpm"),100, 100);
    popup->AddFrame(fIcon,new TGLayoutHints(kLHintsCenterY, 20, 15, 20, 20));

    TGVerticalFrame* fLabelFrame = new TGVerticalFrame(popup, 60, 20);
    popup->AddFrame(fLabelFrame,fL1);
   
    TGLabel *label1 = new TGLabel(fLabelFrame,"====================================================");
    TGLabel *label2 = new TGLabel(fLabelFrame,"========= Beginning Processing of Histogram ========");
    TGLabel *label3 = new TGLabel(fLabelFrame,"================ Please Be Patient =================");
    TGLabel *label4 = new TGLabel(fLabelFrame,"====================================================");
//        label->SetTextJustify(text_align);
    fLabelFrame->AddFrame(label1, fL1);    
    fLabelFrame->AddFrame(label2, fL1);    
    fLabelFrame->AddFrame(label3, fL1);    
    fLabelFrame->AddFrame(label4, fL1);    
        
    cout<<endl<<endl<<" ============== Beginning Processing of Histogram ============ "<<endl<<" ====== Please be patient until window appears ====== "<<endl<<endl;
    
    popup->SetWindowName("LOADING");

    popup->CenterOnParent();// position relative to the parent's window
    popup->DontCallClose();
	
    popup->MapSubwindows();
    popup->Resize(popup->GetDefaultSize());
    popup->MapWindow();
	
//     gClient->NeedRedraw(popup,kTRUE);
//     gClient->WaitFor(popup);

    int waitc=0;
    while(waitc++<20){
        gSystem->ProcessEvents();//gSystem->InnerLoop();
        gSystem->Sleep(5);
    // Little loop to buy Xsystem time to draw the box before code moves on
    }
    
    return popup;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


