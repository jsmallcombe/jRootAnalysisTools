#include "james_env.h"


		
///////////////////////////////////////////////////////////////////////////////////////////////////////


jEnv::jEnv() : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame),
    fFitPanel(0),fSpecTool(0),addsub(0),DirList(0),SameSave(0),gDrawSame(false),fTab(0),
    fPixOffX(1),fPixOffY(33),
    fDefaultDirWidth(180),fDefaultDirHeight(400),
    fDefaultTabsWidth(800),fDefaultTabsHeight(600),
    fDefaultGrabSize(140)
{
    
    
TVirtualPad* hold=gPad;
	SetWindowName("jEnv");
    
	SetCleanup(kDeepCleanup);

	TGLayoutHints* ExpandX= new TGLayoutHints(kLHintsExpandX,5,5,3,2);

    DirList=new jDirList(this);
    this->AddFrame(DirList,new TGLayoutHints(kLHintsExpandY,4,4,4,4));
    
	TGVerticalFrame* controlframe1 = new TGVerticalFrame(this);
		fCanvas1 = new CCframe("Embedded1", controlframe1, fDefaultGrabSize, fDefaultGrabSize);
		
		controlframe1->AddFrame(fCanvas1);
        
// 		DirList->Connect("NewObject(TObject*)","CCframe",fCanvas1,"NonGuiNew(TObject*)");
		DirList->Connect("NewObject(TKey*)","CCframe",fCanvas1,"NonGuiNew(TKey*)");
		DirList->Connect("NewObject(TObject*)","jEnv",this,"NewDirObject(TObject*)");
		
		TGTextButton* fitter = new TGTextButton(controlframe1,"Fit Panel");
		fitter->Connect("Clicked()","jEnv",this,"FitPanel()");	
		controlframe1->AddFrame(fitter,ExpandX);
		TGTextButton* Spect = new TGTextButton(controlframe1,"SpecTool");
		Spect->Connect("Clicked()","jEnv",this,"Spectrum()");
		controlframe1->AddFrame(Spect,ExpandX);
		TGTextButton* gatter = new TGTextButton(controlframe1,"Gate");
		gatter->Connect("Clicked()","jEnv",this,"Gatter()");	
		controlframe1->AddFrame(gatter,ExpandX);
		TGTextButton* jbrowser = new TGTextButton(controlframe1,"< jBrowser");
		jbrowser->Connect("Clicked()","jEnv",this,"ShowHideDir()");
		controlframe1->AddFrame(jbrowser,ExpandX);
		TGTextButton* tbrowser = new TGTextButton(controlframe1,"TBrowser");
		tbrowser->Connect("Clicked()","jEnv",this,"Browser()");
		controlframe1->AddFrame(tbrowser,ExpandX);
		TGTextButton* Drawer = new TGTextButton(controlframe1,"DrawCopy");
		Drawer->Connect("Clicked()","jEnv",this,"DrawCpy()");
		controlframe1->AddFrame(Drawer,ExpandX);
		TGTextButton* Drawsm = new TGTextButton(controlframe1,"DrawSame");
		Drawsm->Connect("Clicked()","jEnv",this,"DrawSm()");
		controlframe1->AddFrame(Drawsm,ExpandX);
		TGTextButton* Saver = new TGTextButton(controlframe1,"SaveAs");
		Saver->Connect("Clicked()","jEnv",this,"jSaveAs()");
		controlframe1->AddFrame(Saver,ExpandX);
		TGTextButton* close = new TGTextButton(controlframe1,"Close");
		close->Connect("Clicked()","jEnv",this,"DeleteWindow()");
		controlframe1->AddFrame(close,ExpandX);
		TGTextButton* exit = new TGTextButton(controlframe1,"Exit","gApplication->Terminate(0)");
		controlframe1->AddFrame(exit,ExpandX);
    this->AddFrame(controlframe1);
	
    
	TGTextButton* expandB = new TGTextButton(this,">");
        expandB->Connect("Clicked()","jEnv",this,"ShowHideTabs()");	
	this->AddFrame(expandB,new TGLayoutHints(kLHintsExpandY, 1, 1, 1, 1));

    fTab = new TGTab(this, fDefaultTabsWidth, fDefaultTabsHeight);  
    fTab->Connect("CloseTab(Int_t)", "jEnv", this, "CloseTab(Int_t)");
	this->AddFrame(fTab, new TGLayoutHints(kLHintsExpandY|kLHintsExpandX, 1, 1, 1, 1));
    
    TGCompositeFrame *TabOne= fTab->AddTab("Add/Sub");
    fTabs.push_back(TabOne);
    addsub = new jAddSubTool(fCanvas1,TabOne);
    TabOne->AddFrame(addsub,new TGLayoutHints(kLHintsExpandY|kLHintsExpandX, 1, 1, 1, 1));
    
    AddTab();
    AddTab();
    AddTab();
    AddTab();
    AddTab();
    AddTab();
    AddTab();
    
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();

	HideTabs();
	HideDir();
    
    Move(70+fDefaultDirWidth,70);
    SetWMPosition(70+fDefaultDirWidth, 70);	
    
#if __linux__
    // An extra small offset due to window bar
    // There is probably a more sophisticated way of dealing with this 
    Window_t wdummy;
    gVirtualX->TranslateCoordinates(GetId(),GetParent()->GetId(),0,0,fPixOffX,fPixOffY,wdummy);
    if(!fPixOffY)fPixOffY=33;
#endif

    
// 	Connect("CloseWindow()","jEnv",this,"~jEnv()");
	Connect("CloseWindow()","jEnv",this,"DontCallClose()");

gPad=hold;
}

void jEnv::ClearFreeObjects(){
    TObject *obj;
    TIter next(&FreeObjects);
    vector<TFile*> files;
    vector<jgating_tool*> gates;
    vector<TFileJointCustody*> custodians;
    
    while((obj= next())){
        if(obj->InheritsFrom(jgating_tool::Class())){
            jgating_tool* gate=(jgating_tool*)obj;
            gate->Disconnect(0,this,0);
            TFile *file=gate->GetOriginFile();
            if(file){
                file->SetBit(kCanDelete,kFALSE);//Now DirList wont/cant delete/close
                files.push_back(file);
                gates.push_back(gate);
                custodians.push_back(0);
            }
        }
    }
    
    
    for(unsigned int i=0;i<files.size();i++){
        bool SoleOwner=true;
        for(unsigned int j=0;j<files.size();j++){
            if(i==j)continue;
            if(files[i]==files[j]){
                SoleOwner=false;
                if(i<j){
                    cout<<endl<<"TFile "<<files[i]->GetName()<<" is being shared and will be left open."<<endl;
                    custodians[i]=new TFileJointCustody(files[i]);
                    custodians[i]->AddObject(gates[i]);
                    gates[i]->Connect("Closed(TObject*)", "TFileJointCustody", custodians[i],"RemoveObject(TObject*)");
                }else{
                    custodians[j]->AddObject(gates[i]);
                    gates[i]->Connect("Closed(TObject*)", "TFileJointCustody", custodians[j],"RemoveObject(TObject*)");
                }
                
                break;
            }
        }
        
        if(SoleOwner){
            gates[i]->SetFileOwner();
        }
    }
}

void jEnv::Browser(){
	new TBrowser;
	if(fCanvas1->Type()>0&&fCanvas1->Type()<3)fCanvas1->Hist()->DrawCopy("colz");
}
void jEnv::FitPanel(){
	if(fFitPanel){
		if(fCanvas1->Type()==1)fFitPanel->PassNewHist(fCanvas1->Hist());
	}else {
		if(fCanvas1->Type()==1)fFitPanel=new UltraFitEnv(fCanvas1->Hist());
		else fFitPanel=new UltraFitEnv();  
		fFitPanel->Connect("Destroyed()", "jEnv", this,"FitPanelClose()");
	}
};
void jEnv::Spectrum(){
	if(fCanvas1->Type()==1){
		if(fSpecTool){
			if(fCanvas1->Type()==1)fSpecTool->NewInput(fCanvas1->Hist());
		}else {
			fSpecTool=new jSpecTool(fCanvas1->Hist());
			fSpecTool->Connect("Destroyed()", "jEnv", this,"SpecToolClose()");
		}
	}
};


void jEnv::Gatter(){
	if(fCanvas1->Type()>1){
        jgating_tool* gate=new jgating_tool(fCanvas1->Hist());
		gate->Connect("Closed(TObject*)", "jEnv", this,"ClosedObject(TObject*)");

        //Sets if a it is allowed to be deleted by lists it is added to
        gate->SetBit(kCanDelete,kFALSE);
        FreeObjects.Add(gate);
    }
};


void jEnv::DrawCpy(){
	HistDrawCopyPeaker(fCanvas1->Hist());
};

void jEnv::DrawSm(){
	gDrawSame=false;
	if(SameSave){delete SameSave;SameSave=0;}
	TH1* h=fCanvas1->Hist();
	if(fCanvas1->Type()==1&&h){
		SameSave=(TH1*)h->Clone();
		gDrawSame=true;
		TQObject::Connect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", "jEnv", this,"DrawSmHere(TPad*,TObject*,Int_t)");
	}
};

void jEnv::DrawSmHere(TPad* pad,TObject* obj,Int_t event){
	
	if(SameSave&&gDrawSame){
		TCanvas* sender=(TCanvas*)gTQSender;
		TVirtualPad* hold=gPad;
		pad->cd();
		hformat(SameSave,0);
        SameSave->SetLineColor(2);
		DrawHistOpt(SameSave,true,true);
		sender->Modified();
		sender->Update();
		gPad=hold;
	}

	gDrawSame=false;
	TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "DrawSmHere(TPad*,TObject*,Int_t)");
	if(SameSave){delete SameSave;SameSave=0;}
}


void jEnv::jSaveAs(){
	if(fCanvas1->Type())HistSaveAs(fCanvas1->Hist(),this);
};


void jEnv::ShowHideTabs(){if(!fTab)return;
	if(IsVisible(fTab)){
		HideTabs();
	}else{
		ShowTabs();
	}
}

void jEnv::ShowTabs(){
	ShowFrame(fTab);
	fTab->Resize(fDefaultTabsWidth, fDefaultTabsHeight);
	Resize(this->GetDefaultSize());
	gClient->NeedRedraw(this);
}

void jEnv::HideTabs(){
	HideFrame(fTab);
	DirList->Resize(fDefaultDirWidth,fDefaultDirHeight);
	Resize(this->GetDefaultSize());
	gClient->NeedRedraw(this);
}

void jEnv::AddTab(){
    TGCompositeFrame *NewTab= fTab->AddTab(" ");
    fTabs.push_back(NewTab);
    fTab->GetTabTab(fTabs.size()-1)->ShowClose();
}

void jEnv::CloseTab(Int_t ID){
//     cout<<endl<<ID<<endl;
    fTab->RemoveTab(ID);
    if(ID<(signed)fTabs.size()){
        fTabs.erase(fTabs.begin()+ID);
    }
}


void jEnv::ShowHideDir(){if(!DirList)return;
	if(IsVisible(DirList)){
		HideDir();
	}else{
		ShowDir();
	}
}

void jEnv::ShowDir(){
    int tW=fTab->GetWidth(),tH=fTab->GetHeight();
	DirList->Resize(fDefaultDirWidth,fDefaultDirHeight);
	ShowFrame(DirList);
	fTab->Resize(tW, tH);
	Resize(this->GetDefaultSize());
	gClient->NeedRedraw(this);

#if __linux__
    int x,y;
    Window_t wdummy;
    gVirtualX->TranslateCoordinates(GetId(),GetParent()->GetId(),0,0,x,y,wdummy);
    Move(x-fDefaultDirWidth-8-fPixOffX,y-fPixOffY);
    SetWMPosition(x-fDefaultDirWidth-8-fPixOffX,y-fPixOffY);
#endif
}

void jEnv::HideDir(){
    int tW=fTab->GetWidth(),tH=fTab->GetHeight();
	HideFrame(DirList);
	fTab->Resize(tW, tH);
	Resize(this->GetDefaultSize());
	gClient->NeedRedraw(this);
    
#if __linux__
    int x,y;
    Window_t wdummy;
    gVirtualX->TranslateCoordinates(GetId(),GetParent()->GetId(),0,0,x,y,wdummy);
    Move(x+fDefaultDirWidth+8-fPixOffX,y-fPixOffY);
    SetWMPosition(x+fDefaultDirWidth+8-fPixOffX,y-fPixOffY);
#endif
}

void jEnv::NewDirObject(TObject* obj){
	if(obj->InheritsFrom(TGraph::Class())){
		new TCanvas();
		gPad->Update();
		((TGraph*)obj)->DrawClone("al");
	}	
}

void jEnv::ClosedObject(TObject* obj){
//     cout<<endl<<"A free object has closed. Here is a pointer to where it HAD been located in memory "<<obj<<endl;    
    FreeObjects.Remove(obj);
}

////////////////////////////////////////////////////////////////

jScale::jScale() : TGMainFrame(gClient->GetRoot(), 100, 100,kVerticalFrame),gg(0){
TVirtualPad* hold=gPad;
	SetWindowName("jScale");
	SetCleanup(kDeepCleanup);
	

	TGLayoutHints* ExpandX= new TGLayoutHints(kLHintsExpandX,5,5,3,2);
	
	TGHorizontalFrame* inputframe = new TGHorizontalFrame(this);
		fCanvas1 = new CCframe("Embedded1", inputframe, 100, 100);
        fCanvas1->Connect("NewObject()","jScale",this,"NewInput()");
		inputframe->AddFrame(fCanvas1);
		fCanvas2 = new CCframe("Embedded2", inputframe, 100, 100);
        fCanvas2->SetClass(TGraph::Class());
        fCanvas2->Connect("NewObject()","jScale",this,"NewInput()");
		inputframe->AddFrame(fCanvas2);
	this->AddFrame(inputframe,ExpandX);
	
    
    result= new TRootEmbeddedCanvas("scaledhistcan",this,600,400);
		result->GetCanvas()->SetMargin(0.12,0.04,0.12,0.05);
// 		result->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0,0,"ClickPeakDrawConnect(Int_t,Int_t,Int_t,TObject*)");
// 		result->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0,0,"ToolTipHide()");//added because this embedded canvas put tooltip at wrong coordinates on screen

	this->AddFrame(result,ExpandX);
    
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
    
    
	fCanvas1->CFriends.push_back(fCanvas2->GetCanvas());
	fCanvas1->CFriends.push_back(result->GetCanvas());
	fCanvas2->CFriends.push_back(fCanvas1->GetCanvas());
	fCanvas2->CFriends.push_back(result->GetCanvas());
	
gPad=hold;
}


void jScale::NewInput(){
    TH1* H=fCanvas1->Hist();
    TGraph* G=(TGraph*)fCanvas2->Object();
    
    if(G){
        if(gg)delete gg;
        gg=(TGraph*)G->Clone();
    }
    
//     cout<<endl<<H<<endl<<gg<<endl;
    if(HType(H)&&gg&&HType(H)<3){
        TH1* scaled=(TH1*)H->Clone();
        scaled->Reset();
        bool Y=(HType(H)==2);
        int NX=H->GetNbinsX();
        int ny=0;
        int NY=0;
        if(Y){
            ny=1;
            NY=H->GetNbinsY();
        }
        
        for(int x=1;x<=NX;x++){
            double efX=gg->Eval(H->GetXaxis()->GetBinCenter(x));
            
            for(int y=ny;y<=NY;y++){
                int bin=H->GetBin(x,y);
                double n=H->GetBinContent(bin);
                double e=H->GetBinError(bin);
                double efY=1;
                if(Y){
                    efY=gg->Eval(H->GetYaxis()->GetBinCenter(y));
                }
                double scale=1/(efY*efX);
                scaled->SetBinContent(bin,n*scale);
                scaled->SetBinError(bin,e*scale);
            }
        }
        
//         Draw new results with and adjust axis
        TVirtualPad* hold=gPad;
        result->GetCanvas()->cd();
            hformat(scaled,0);
            scaled->DrawCopy("hiscol");
            delete scaled;
//             gPad->Update();
//             G->DrawClone("al");
        result->GetCanvas()->Modified();
        result->GetCanvas()->Update();
        gPad=hold;
    }
}



