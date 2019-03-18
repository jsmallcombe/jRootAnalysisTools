#include "james_env.h"
#include "james_filecustodian.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////

FontStruct_t jEnv::GetFont(){
    TGFontPool *pool = gClient->GetFontPool();
    // family , size (minus value - in pixels, positive value - in points), weight, slant
    //  kFontWeightNormal,  kFontSlantRoman are defined in TGFont.h
    TGFont *font = pool->GetFont("helvetica", 12,  kFontWeightBold,  kFontSlantRoman);
    FontStruct_t ft = TGTextButton::GetDefaultFontStruct();
//     GContext_t gc=TGButton::GetDefaultGC()();
    if(font){
        ft = font->GetFontStruct();
    }
    return ft;
}


jEnv::jEnv() : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame),
    fFitPanel(0),fSpecTool(0),addsub(0),DirList(0),SameSave(0),gDrawSame(false),fTabs(0),
    fPixOffX(1),fPixOffY(33),
    fDefaultDirWidth(200),fDefaultDirHeight(400),
    fDefaultTabsWidth(1000),fDefaultTabsHeight(650),
    fDefaultGrabSize(140)
{

    FontStruct_t ft =GetFont();
    
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
		DirList->Connect("NewObject(TObject*)","CCframe",fCanvas1,"NonGuiNew(TObject*)");
		DirList->Connect("NewObject(TObject*)","jEnv",this,"NewDirObject(TObject*)");
		
        TGHorizontalFrame* drawduelbuttons = new TGHorizontalFrame(controlframe1);            
            TGTextButton* fitter = new TGTextButton(drawduelbuttons,"Fit Panel");
            fitter->SetFont(ft);
            fitter->Connect("Clicked()","jEnv",this,"FitPanel()");	
            drawduelbuttons->AddFrame(fitter,ExpandX);
			TGPictureButton *fPictureBut = new TGPictureButton(drawduelbuttons,gClient->GetPicture("newcanvas.xpm"));
            fPictureBut->SetMinWidth(30);
            fPictureBut->SetWidth(35);
			fPictureBut->Connect("Clicked()","jEnv",this,"FreeFitPanel()");
			drawduelbuttons->AddFrame(fPictureBut,new TGLayoutHints(kLHintsExpandY,0,5,3,2));
		controlframe1->AddFrame(drawduelbuttons,new TGLayoutHints(kLHintsExpandX,0,0,0,0));

		TGTextButton* Spect = new TGTextButton(controlframe1,"SpecTool");
        Spect->SetFont(ft);
		Spect->Connect("Clicked()","jEnv",this,"Spectrum()");
		controlframe1->AddFrame(Spect,ExpandX);
		TGTextButton* gatter = new TGTextButton(controlframe1,"Gate");
        gatter->SetFont(ft);
		gatter->Connect("Clicked()","jEnv",this,"Gatter()");	
		controlframe1->AddFrame(gatter,ExpandX);
		TGTextButton* jbrowser = new TGTextButton(controlframe1,"< jBrowser");
        jbrowser->SetFont(ft);
		jbrowser->Connect("Clicked()","jEnv",this,"ShowHideDir()");
		controlframe1->AddFrame(jbrowser,ExpandX);
		TGTextButton* tbrowser = new TGTextButton(controlframe1,"TBrowser");
        tbrowser->SetFont(ft);
		tbrowser->Connect("Clicked()","jEnv",this,"Browser()");
		controlframe1->AddFrame(tbrowser,ExpandX);
		
		drawduelbuttons = new TGHorizontalFrame(controlframe1);
			TGTextButton* Drawer = new TGTextButton(drawduelbuttons," Draw ");
            Drawer->SetFont(ft);
			Drawer->Connect("Clicked()","jEnv",this,"DrawCpyTab()");
			drawduelbuttons->AddFrame(Drawer,ExpandX);
			fPictureBut = new TGPictureButton(drawduelbuttons,gClient->GetPicture("newcanvas.xpm"));
            fPictureBut->SetMinWidth(30);
            fPictureBut->SetWidth(35);
             
			fPictureBut->Connect("Clicked()","jEnv",this,"DrawCpy()");
			drawduelbuttons->AddFrame(fPictureBut,new TGLayoutHints(kLHintsExpandY,0,5,3,2));
		controlframe1->AddFrame(drawduelbuttons,new TGLayoutHints(kLHintsExpandX,0,0,0,0));
		
		TGTextButton* Drawsm = new TGTextButton(controlframe1,"DrawSame");
        Drawsm->SetFont(ft);
		Drawsm->Connect("Clicked()","jEnv",this,"DrawSm()");
		controlframe1->AddFrame(Drawsm,ExpandX);
		TGTextButton* Saver = new TGTextButton(controlframe1,"SaveAs");
        Saver->SetFont(ft);
		Saver->Connect("Clicked()","jEnv",this,"jSaveAs()");
		controlframe1->AddFrame(Saver,ExpandX);
		TGTextButton* close = new TGTextButton(controlframe1,"Close");
        close->SetFont(ft);
		close->Connect("Clicked()","jEnv",this,"DeleteWindow()");
		controlframe1->AddFrame(close,ExpandX);
// 		TGTextButton* exit = new TGTextButton(controlframe1,"Exit","gApplication->Terminate(0)");
		TGTextButton* exit = new TGTextButton(controlframe1,"Exit");
		exit->Connect("Clicked()","jEnv",this,"Terminate()");
        exit->SetFont(ft);
        controlframe1->AddFrame(exit,ExpandX);
    this->AddFrame(controlframe1);
	
    
	TGTextButton* expandB = new TGTextButton(this,">");
        expandB->Connect("Clicked()","jEnv",this,"ShowHideTabs()");	
	this->AddFrame(expandB,new TGLayoutHints(kLHintsExpandY, 1, 1, 1, 1));

    fTabs = new TGTab(this, fDefaultTabsWidth, fDefaultTabsHeight);  
    fTabs->Connect("CloseTab(Int_t)", "jEnv", this, "CloseTab(Int_t)");
	this->AddFrame(fTabs, new TGLayoutHints(kLHintsExpandY|kLHintsExpandX, 1, 1, 1, 1));
    
    addsub = new jAddSubTool(fCanvas1,fTabs);
    fTabs->AddTab("Add/Sub",addsub);

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


void jEnv::Terminate(){
    FreeObjects.SetOwner();//Will delete list objects irrespective of kCanDelete
    delete this;
    delete gChiefCustodian;//Closes any open files
    gApplication->Terminate(0);
}


void jEnv::ClearFreeObjects(){
    // Disconnected signals from FreeObjects, objects in list will be deleted along with jEnv depenendent on individual kCanDelete values
    
    TObject *obj;
    TIter next(&FreeObjects);
    while((obj= next())){
        if(obj->InheritsFrom("TQObject")){
            dynamic_cast<TQObject*>(obj)->Disconnect(0,this,0);
        }
    }
    
//     FreeObjects.Clear("nodelete");
}

void jEnv::AddFreeObject(TObject* obj,bool CanDelete){
    
    // See james_filecustodian.cpp for more details of cast options
    dynamic_cast<TQObject*>(obj)->Connect("Closed(TObject*)","jEnv", this,"ClosedObject(TObject*)");
   
    // Sets if it is allowed to be deleted by TLists it is added to
    if(CanDelete)obj->SetBit(kCanDelete,kTRUE);
    else obj->SetBit(kCanDelete,kFALSE);
    
    FreeObjects.Add(obj);
}

void jEnv::Browser(){
	new TBrowser;
	if(fCanvas1->Type()>0&&fCanvas1->Type()<3)fCanvas1->Hist()->DrawCopy("colz");
}

void jEnv::FitPanel(){
    if(fCanvas1->Type()==1){
        if(fFitPanel){
            fFitPanel->PassNewHist(fCanvas1->Hist());
            for(int i=0;i<fTabs->GetNumberOfTabs();i++)if(fFitPanel==fTabs->GetTabContainer(i)){fTabs->SetTab(i,kFALSE);break;}
            if(!IsVisible(fTabs))ShowTabs();
		}else {
            fFitPanel=new UltraFitEnv(fTabs,fCanvas1->Hist(),0,1);
            fTabs->AddTab("FitPanel",fFitPanel);
            fTabs->SetTab(fTabs->GetNumberOfTabs()-1,kFALSE);
            ShowTabs();
		}
	}
};

void jEnv::FreeFitPanel(){
        if(fCanvas1->Type()==1)AddFreeObject(new UltraFitEnv(fCanvas1->Hist()),true);
		else AddFreeObject(new UltraFitEnv(),true);
}

void jEnv::Spectrum(){
	if(fCanvas1->Type()==1){
		if(fSpecTool){
			fSpecTool->NewInput(fCanvas1->Hist());
//          fSpecTool->RaiseWindow();
            
            for(int i=0;i<fTabs->GetNumberOfTabs();i++)if(fSpecTool==fTabs->GetTabContainer(i)){fTabs->SetTab(i,kFALSE);break;}
            if(!IsVisible(fTabs))ShowTabs();
		}else {
            ////// Old free jSpecTool
//          fSpecTool=new jSpecTool(fCanvas1->Hist());
// 			fSpecTool->Connect("Destroyed()", "jEnv", this,"SpecToolClose()");
            
            fSpecTool=new jSpecTool(fTabs,fCanvas1->Hist());
            fTabs->AddTab("SpecTool",fSpecTool);
            fTabs->SetTab(fTabs->GetNumberOfTabs()-1,kFALSE);
            ShowTabs();
		}
	}
};


void jEnv::Gatter(){
	if(fCanvas1->Type()>1){
        jgating_tool* gate=new jgating_tool(fCanvas1->Hist(),1);
        AddFreeObject(gate,false);
    }
};


void jEnv::DrawCpy(){
	DrawCopyCanvas(fCanvas1->Hist());
};

void jEnv::DrawCpyTab(){
	TH1* H=fCanvas1->Hist();
	if(!H)return;
	TCanvas* Can= AddCanvasTab(H->GetName());
	Can->cd();
	DrawCopyHistOpt(H);
	ConnectPeakClickerCanvas(Can);
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
		TH1* H=DrawHistOpt(SameSave,true,true,true);
        H->SetLineColor(2);
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


void jEnv::ShowHideTabs(){if(!fTabs)return;
	if(IsVisible(fTabs)){
		HideTabs();
	}else{
		ShowTabs();
	}
}

void jEnv::ShowTabs(){
	ShowFrame(fTabs);
	fTabs->Resize(fDefaultTabsWidth, fDefaultTabsHeight);
	Resize(this->GetDefaultSize());
	gClient->NeedRedraw(this);
}

void jEnv::HideTabs(){
	HideFrame(fTabs);
	DirList->Resize(fDefaultDirWidth,fDefaultDirHeight);
	Resize(this->GetDefaultSize());
	gClient->NeedRedraw(this);
}


TGCompositeFrame* jEnv::AddTab(string TabName,bool ShowClose){
    if(TabName.size()<1){
        stringstream ss;
        ss<<"Tab "<<fTabs->GetNumberOfTabs()+1;
        TabName=ss.str();
    }
    TGCompositeFrame *NewTab= fTabs->AddTab(TabName.c_str());
    Int_t ID=fTabs->GetNumberOfTabs()-1;
    if(ShowClose){
        fTabs->GetTabTab(ID)->ShowClose();
    }
    fTabs->SetTab(ID,kFALSE);
	if(!IsVisible(fTabs))ShowTabs();
    return NewTab;
}

TCanvas* jEnv::AddCanvasTab(string TabName){
    TGCompositeFrame *NewTab= AddTab(TabName.c_str(),true);
    TabName+="EmbededCanvas";
	TRootEmbeddedCanvas* Embeded= new TRootEmbeddedCanvas(TabName.c_str(),NewTab,600,400);
	NewTab->AddFrame(Embeded, new TGLayoutHints(kLHintsExpandY|kLHintsExpandX, 1, 1, 1, 1));
    fTabs->MapSubwindows();
    ShowFrame(fTabs);
    
	TCanvas* Can= Embeded->GetCanvas();
	ReMargin(Can);
    return Can;
}

void jEnv::CloseTab(Int_t ID){
//     cout<<endl<<ID<<endl;
    fTabs->RemoveTab(ID);
    if(ID>=fTabs->GetNumberOfTabs())ID--;
    fTabs->SetTab(ID,kFALSE);
}


void jEnv::ShowHideDir(){if(!DirList)return;
	if(IsVisible(DirList)){
		HideDir();
	}else{
		ShowDir();
	}
}

void jEnv::ShowDir(){
    int tW=fTabs->GetWidth(),tH=fTabs->GetHeight();
	DirList->Resize(fDefaultDirWidth,fDefaultDirHeight);
	ShowFrame(DirList);
	fTabs->Resize(tW, tH);
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
    int tW=fTabs->GetWidth(),tH=fTabs->GetHeight();
	HideFrame(DirList);
	fTabs->Resize(tW, tH);
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
        TCanvas* Can=AddCanvasTab(obj->GetName());
        Can->cd();
		gPad->Update();
		TObject* graph=((TGraph*)obj)->DrawClone("al");
        hformat(((TGraph*)graph)->GetHistogram());
	}	
}

void jEnv::ClosedObject(TObject* obj){
//     cout<<endl<<"A free object has closed. Here is a pointer to where it HAD been located in memory "<<obj<<endl;    
    FreeObjects.Remove(obj);
}

////////////////////////////////////////////////////////////////

jScale::jScale() : TGMainFrame(gClient->GetRoot(), 100, 100,kVerticalFrame),gg(0),IsLocked(0){
TVirtualPad* hold=gPad;
	SetWindowName("jScale");
	SetCleanup(kDeepCleanup);
	
    FontStruct_t ft =jEnv::GetFont();

	TGLayoutHints* ExpandX= new TGLayoutHints(kLHintsExpandX,5,5,3,2);
	
	TGHorizontalFrame* inputframe = new TGHorizontalFrame(this);
		fCanvas1 = new CCframe("Embedded1", inputframe, 100, 100);
        fCanvas1->Connect("NewObject()","jScale",this,"NewInput()");
		inputframe->AddFrame(fCanvas1);
		fCanvas2 = new CCframe("Embedded2", inputframe, 100, 100);
        fCanvas2->SetClass(TGraph::Class());
        fCanvas2->Connect("NewObject()","jScale",this,"NewInput()");
		inputframe->AddFrame(fCanvas2);
            
        lockbutton = new TGTextButton(inputframe,"  Lock  ");
        lockbutton->SetFont(ft);
        lockbutton->Connect("Clicked()","jScale",this,"Lock()");	
		inputframe->AddFrame(lockbutton,new TGLayoutHints(kLHintsCenterY, 1, 1, 1, 1));
        
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
    
    if(IsLocked) return;
    
//     cout<<endl<<H<<endl<<gg<<endl;
    if(HType(H)&&gg&&HType(H)<3){
        stringstream nn;
        nn<<H->GetName()<<"x"<<gg->GetName();
        TH1* scaled=(TH1*)H->Clone(nn.str().c_str());
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
        stringstream ss;
        ss<<"jScale : "<<H->GetName()<<" x "<<gg->GetName();
        SetWindowName(ss.str().c_str());
    }
}


void jScale::Lock(){
    IsLocked=!IsLocked;
    if(IsLocked){
        lockbutton->SetText("Unlock");
        lockbutton->SetTextColor(2);
        lockbutton->SetState(kButtonDown);
    }else{
        lockbutton->SetText("  Lock  ");
        lockbutton->SetTextColor(1);
        lockbutton->SetState(kButtonUp);
        NewInput();
    }
}


////////////////////////////////////////////////////////////////

jEval::jEval() : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame),gg(0),GG(0),IsLocked(0){
TVirtualPad* hold=gPad;
    SetWindowName("jEval");
    SetCleanup(kDeepCleanup);

    FontStruct_t ft =jEnv::GetFont();


    fCanvas1 = new CCframe("Embedded1", this, 100, 100);
    fCanvas1->SetClass(TGraph::Class());
    fCanvas1->Connect("NewObject()","jEval",this,"NewInput()");
    this->AddFrame(fCanvas1);
        
    lockbutton = new TGTextButton(this,"  Lock  ");
    lockbutton->SetFont(ft);
    lockbutton->Connect("Clicked()","jEval",this,"Lock()");	
    this->AddFrame(lockbutton,new TGLayoutHints(kLHintsCenterY, 1, 1, 1, 1));

    fTeh1 = new TGTextEntry(this, new TGTextBuffer(4));
    fTeh1->SetDefaultSize(50,25);
    fTeh1->SetAlignment (kTextRight);
//     fTeh1->Connect("ReturnPressed()", "jEval", this,"Eval()");
//     fTeh1->Connect("TabPressed()", "jEval", this,"Eval()");
    fTeh1->Connect("TextChanged(char*)", "jEval", this,"Eval(char*)");
    this->AddFrame(fTeh1,new TGLayoutHints(kLHintsCenterY, 1, 1, 1, 1));
    
    fTeh2 = new TGTextEntry(this,new TGTextBuffer(6));
    fTeh2->SetDefaultSize(100,25);
    fTeh2->SetAlignment (kTextRight);
    this->AddFrame(fTeh2,new TGLayoutHints(kLHintsCenterY, 1, 1, 1, 1));
    
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
    
gPad=hold;
}


void jEval::NewInput(){
    TGraph* G=(TGraph*)fCanvas1->Object();
    
    if(G){
        if(gg)delete gg;
        gg=(TGraph*)G->Clone();
    }
    
    if(IsLocked) return;
    
    if(gg){
        if(GG)delete GG;
        GG=(TGraph*)gg->Clone();
        stringstream ss;
        ss<<"jEval : "<<gg->GetName();
        SetWindowName(ss.str().c_str());
    }
}


void jEval::Lock(){
    IsLocked=!IsLocked;
    if(IsLocked){
        lockbutton->SetText("Unlock");
        lockbutton->SetTextColor(2);
        lockbutton->SetState(kButtonDown);
    }else{
        lockbutton->SetText("  Lock  ");
        lockbutton->SetTextColor(1);
        lockbutton->SetState(kButtonUp);
        NewInput();
    }
}

void jEval:: Eval(char* cha){
    stringstream in;
    in<<cha;
    double input;
    in>>input;
    if(GG){
        double Y=GG->Eval(input);
        char buf[32];
        sprintf(buf, "%.5f", Y);
        TGTextBuffer* fTbh2=fTeh2->GetBuffer();
        fTbh2->Clear();	fTbh2->AddText(0, buf);
        fTeh2->SetCursorPosition(fTeh2->GetCursorPosition());
        fTeh2->Deselect();
        gClient->NeedRedraw(fTeh2);
        cout<<endl<<GG->GetName()<<" Eval at "<<input<<" = "<<Y<<flush;
    }
}
