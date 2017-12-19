#include "james_ultrafit_env.h"


///////////////////////////////////////
// Initialiser functions  //
///////////////////////////////////////

int UltraFitEnv::UltraFitEnv_iterator = 0;

UltraFitEnv::UltraFitEnv(TH1* fHist,TCanvas* fCan, double iSepA,double iSepB,double iSepC):TQObject(),
cBar(0),cFrame(0),cPan(0),cCan(0),gHist(0),gHistDrawn(0),cShift(0),cCtrl(0),cAlt(0),cGoodFit(0),cSaveConf(0),cClearConf(0),cNfit(1),cNfree(1)
{TVirtualPad* hold=gPad;
	if(iSepA!=0)SetSep(2,iSepA);
	if(iSepB!=0)SetSep(3,iSepB);
	if(iSepC!=0)SetSep(4,iSepC);
	DialogBox();
	ConnectNewCanvas(fCan);//does nothing if fCan=0
	SetNewHist(fHist);//does nothing if fHist=0
gPad=hold;};

UltraFitEnv::~UltraFitEnv(){
	if(cBar!=0){TQObject::Disconnect(cBar);cBar->Cleanup();delete cBar;}
	KillCan();
	if(gHist){delete gHist;gHist=0;} // No idea, old segfault
	ClearFits();
};

void UltraFitEnv::ClearFits(){
	//cout<<endl<<"ERROR IN FN A"<<flush;
	for(int i=0;(unsigned)i<cFitList.size();i++)delete cFitList[i];
	cFitList.clear();
	cSaveLabels.clear();
	if(gHist){
		gHist->GetListOfFunctions()->Clear();
	}
};

void UltraFitEnv::ClearFitsD(){
	//cout<<endl<<"ERROR IN FN B"<<flush;
	if(!cClearConf&&cFitList.size()>0){
		cout<<endl<<"Are you sure you want to clear all saved fits?";
		cout<<endl<<"Click again to confirm."<<endl;
		cClearConf=true;
		return;
	}
	cout<<endl<<"Fit data for "<<cFitList.size()<<" fits cleared."<<endl;
	ClearFits();
	DrawgHist();
	cSaveConf=false;
};

void UltraFitEnv::DialogBox() {
	//cout<<endl<<"ERROR IN FN C"<<flush;
	if(cBar==0){
		cBar=new TGMainFrame(gClient->GetRoot(), 100, 100);
		cBar->SetCleanup(kDeepCleanup);
		
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
		TGTextButton *button;
		TGLayoutHints* buff= new TGLayoutHints(0,5,5,3,2);
		TGLayoutHints* ExpandX= new TGLayoutHints(kLHintsExpandX,5,5,3,2);
		TGLayoutHints* ExpandXz= new TGLayoutHints(kLHintsExpandX,0,0,0,0);
		TGLayoutHints* YY= new TGLayoutHints(kLHintsCenterY,8,8,3,3);
		TGLayoutHints* XX= new TGLayoutHints(kLHintsCenterX,3,3,3,1);
		TGLayoutHints* XB= new TGLayoutHints(kLHintsExpandX|kLHintsBottom,2,2,2,2);
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

		TGHorizontalFrame* menuB = new TGHorizontalFrame(cBar, 0, 0, 0);
			button = new TGTextButton(menuB," Help ");
			button->Connect("Clicked()","UltraFitEnv",this,"Help()");
			menuB->AddFrame(button,new TGLayoutHints(kLHintsRight,0,0,0,0));
			button = new TGTextButton(menuB," SaveAs ");
			button->Connect("Clicked()","UltraFitEnv",this,"jSaveAs()");
			menuB->AddFrame(button,new TGLayoutHints(kLHintsLeft,0,0,0,0));
		cBar->AddFrame(menuB,ExpandXz);
		
		mainhold = new TGHorizontalFrame(cBar, 0, 0, 0); 
		cFrame = new TGVerticalFrame(mainhold);

		TGHorizontalFrame* capt = new TGHorizontalFrame(cFrame, 0, 0, 0);
			button = new TGTextButton(capt," Capture Hist ");
			button->Connect("Clicked()","UltraFitEnv",this,"SetCapture(int=1)");
			button->SetToolTipText("Copy histogram from another frame\n(subsequent click).");
			capt->AddFrame(button,ExpandXz);	
		
			button = new TGTextButton(capt," Link Canvas ");
			button->Connect("Clicked()","UltraFitEnv",this,"SetCapture(int=0)");
			button->Resize(150);
			button->SetToolTipText("Begin fitting in another canvas\n(subsequent click).");
			capt->AddFrame(button,ExpandXz);	
		cFrame->AddFrame(capt,ExpandX);
		
		fCheck0 = new TGCheckButton(cFrame,"Peak Labels ");
		fCheck0->SetState(kButtonDown);
		fCheck0->Connect("Clicked()","UltraFitEnv",this,"DrawSaveLabels()");
 		fCheck0->SetToolTipText("Show peak labels on histogram.");
		cFrame->AddFrame(fCheck0,XX);
		
		button = new TGTextButton(cFrame,"Re-Draw Hist");
		button->Connect("Clicked()","UltraFitEnv",this,"ReDrawgHist()");
		button->SetToolTipText("Re-draw the currently selected histogram\nand any saved fits.");
		cFrame->AddFrame(button,ExpandX);
		
		button = new TGTextButton(cFrame,"Clear Exclusion");
		button->Connect("Clicked()","UltraFitEnv",this,"ClearExclusion()");
		button->SetToolTipText("Clear any user specified\n fit exclusion region.");
		cFrame->AddFrame(button,ExpandX);
		
		button = new TGTextButton(cFrame,"");
		button->Connect("Clicked()","UltraFitEnv",this,"PointMe()");
		cFrame->AddFrame(button,ExpandX);	
		
		button = new TGTextButton(cFrame,"Save Peak Info");
		button->Connect("Clicked()","UltraFitEnv",this,"SaveFit()");
		button->SetToolTipText("Save the most recently completed fit\nto the local list of fits\nand to the histogram.");
		cFrame->AddFrame(button,ExpandX);
			
		button = new TGTextButton(cFrame,"Clear Saved Peaks");
		button->Connect("Clicked()","UltraFitEnv",this,"ClearFitsD()");
		button->SetToolTipText("Delete all fits saved\nto the local list of fits\nand to the histogram.");
		cFrame->AddFrame(button,ExpandX);
		
		button = new TGTextButton(cFrame,"Print Peak Info");
		button->Connect("Clicked()","UltraFitEnv",this,"PrintFits()");
		button->SetToolTipText("Print the peak data for the\n list of saved fits\nto the terminal.");
		cFrame->AddFrame(button,ExpandX);
		
		button = new TGTextButton(cFrame,"Export Peak Info");
		button->Connect("Clicked()","UltraFitEnv",this,"ExportFits()");
		button->SetToolTipText("Save the peak data for the list of\n saved fits in plain text to the file\n peakinfo.dat (overwrites)");
		cFrame->AddFrame(button,ExpandX);
		
		button = new TGTextButton(cFrame,"");//Just filler
		cFrame->AddFrame(button,ExpandX);	
		
		button = new TGTextButton(cFrame,"Fit Peaks");
		button->Connect("Clicked()","UltraFitEnv",this,"FitGUIPeak()");
		button->SetToolTipText("Fit the selected histogram using\nthe current inputs.");
		cFrame->AddFrame(button,ExpandX);
		
		TGHorizontalFrame* fHframe0 = new TGHorizontalFrame(cFrame, 0, 0, 0);
		
			TGVerticalFrame* ticks = new TGVerticalFrame(fHframe0, 0, 0, 0);
			
				TGLabel *label = new TGLabel(ticks, "Background Mode");
				ticks->AddFrame(label,XX);
				
				fCombo = new TGComboBox(ticks,100);
				fCombo->AddEntry("pol0+step",0);
				fCombo->AddEntry("pol1 fixed",1);
				fCombo->AddEntry("pol1",2);
				fCombo->AddEntry("pol1+step",3);
				fCombo->AddEntry("pol2",4);
				fCombo->AddEntry("pol2+step",5);
				fCombo->Resize(110, 20);
				fCombo->Select(0);
				ticks->AddFrame(fCombo,XX);	
				
				fCheck1 = new TGCheckButton(ticks,"Limit Tail  ");// A tick box with hover text belonging to a parent frame
				fCheck1->SetState(kButtonUp);
				fCheck1->SetToolTipText("Force strict maximum values on the\nexponential tail parameters.\n Recommended for fitting gamma rays.");
				
				fCheck2 = new TGCheckButton(ticks,"Two Gaus");// A tick box with hover text belonging to a parent frame
				fCheck2->SetState(kButtonUp);
				fCheck2->SetToolTipText("Use the peak fit mode which has no tail\n but instead two Gaussians\n of different sigma.");
				fCheck2->Connect("Clicked()","UltraFitEnv",this,"SwitchDecayLabel()");
				

			ticks->AddFrame(fCheck1,XX);
			ticks->AddFrame(fCheck2,XX);
		fHframe0->AddFrame(ticks,ExpandXz);
			
			TGVerticalFrame* fHframepm = new TGVerticalFrame(fHframe0, 0, 0, 0);
			
				button = new TGTextButton(fHframepm," + ");
				button->Connect("Clicked()","UltraFitEnv",this,"AddTextBox()");
				button->SetToolTipText("Increase the number of peaks to fit.");
				fHframepm->AddFrame(button,ExpandXz);
				button = new TGTextButton(fHframepm," - ");
				button->SetToolTipText("Decrease the number of peaks to fit.");
				button->Connect("Clicked()","UltraFitEnv",this,"RemoveTextBox()");
				fHframepm->AddFrame(button,ExpandXz);
			
			fHframe0->AddFrame(fHframepm,YY);
			
		cFrame->AddFrame(fHframe0,ExpandXz);		
// 		
		TGHorizontalFrame* fHframeN = new TGHorizontalFrame(cFrame, 0, 0, 0);

			cNpd=new TGTextEntry(fHframeN,new TGTextBuffer(5));
				cNpd->SetText("1");
				cNpd->SetDefaultSize(25,25);
				cNpd->Connect("TextChanged(char*)","UltraFitEnv",this,"SetN()");
				cNpd->SetEnabled(0);
				cNpd->SetToolTipText("Current number of peaks to fit.");
			fHframeN->AddFrame(cNpd,buff);
// 				
			cZc = new TGTextEntry(fHframeN,new TGTextBuffer(5));
				cZc->SetDefaultSize(50,25);
				cZc->SetEnabled(0);
				cPTbox.push_back(cZc);			
				cZc->SetToolTipText("Centroid\n Peak 0 absolute centroid\n Selected/Result.");
			fHframeN->AddFrame(cZc,buff);
// 		
		cFrame->AddFrame(fHframeN,new TGLayoutHints(kLHintsRight));
		
		cShapePane= new TGVerticalFrame(cFrame);
			TGHorizontalFrame* shapeelement = new TGHorizontalFrame(cShapePane, 0, 0, 0);
				cShapeTsig = new TGTextEntry(shapeelement,new TGTextBuffer(5));
				cShapeTsig->SetDefaultSize(50,25);	
				cShapeTsig->SetToolTipText("Sigma\n Fix or constrain peak sigma.");
				shapeelement->AddFrame(cShapeTsig,buff);
				label = new TGLabel(shapeelement, "Sigma");
				shapeelement->AddFrame(label,buff);
			cShapePane->AddFrame(shapeelement,ExpandXz);
		
			shapeelement = new TGHorizontalFrame(cShapePane, 0, 0, 0);
				cShapeTdecay = new TGTextEntry(shapeelement,new TGTextBuffer(5));
				cShapeTdecay->SetDefaultSize(50,25);	
				cShapeTdecay->SetToolTipText("Decay Tail\n Fix or constrain peak decay tail.");
				shapeelement->AddFrame(cShapeTdecay,buff);
				label = new TGLabel(shapeelement, "Decay  ");
				decaysigmablabel=label;
				shapeelement->AddFrame(label,buff);
			cShapePane->AddFrame(shapeelement,ExpandXz);
			
			shapeelement = new TGHorizontalFrame(cShapePane, 0, 0, 0);
				cShapeTshare = new TGTextEntry(shapeelement,new TGTextBuffer(5));
				cShapeTshare->SetDefaultSize(50,25);	
				cShapeTshare->SetToolTipText("Sharing Parameter\n Fix or constrain peak sharing parameter.");
				shapeelement->AddFrame(cShapeTshare,buff);
				label = new TGLabel(shapeelement, "Sharing");
				shapeelement->AddFrame(label,buff);
			cShapePane->AddFrame(shapeelement,ExpandXz);
		cFrame->AddFrame(cShapePane,XB);
		
		button = new TGTextButton(cFrame,"^");
		button->Connect("Clicked()","UltraFitEnv",this,"HideShape()");
		button->SetToolTipText("Show Peak Shape Controls.");
		cFrame->AddFrame(button,XB);
		
		
		mainhold->AddFrame(cFrame,new TGLayoutHints(kLHintsExpandY,0,0,0,0));
		
		stringstream ss;
		ss <<"UltraFitCanvas"<<UltraFitEnv_iterator;
		UltraFitEnv_iterator++;
		can_name=ss.str();
		cPan = new TRootEmbeddedCanvas(can_name.c_str(), mainhold, 800,600);
		mainhold->AddFrame(cPan,new TGLayoutHints(kLHintsExpandY|kLHintsExpandX,3,3,3,3));

		cBar->AddFrame(mainhold,new TGLayoutHints(kLHintsExpandY|kLHintsExpandX,0,0,0,0));
		
		cBar->SetWindowName("UltraFitControls");
		
		cBar->MapSubwindows();
		cBar->Resize(cBar->GetDefaultSize());
		cBar->MapWindow();
		
		HideCanvas();
		HideShape();
		cPan->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "UltraFitEnv", this,"ClickedCanvas(Int_t,Int_t,Int_t,TObject*)");
		
		cBar->Connect("CloseWindow()","UltraFitEnv",this,"DialogClose()");
	}
}

void UltraFitEnv::HideShape(){
	cShapeTsig->SetText("");
	cShapeTdecay->SetText("");
	cShapeTshare->SetText("");
	if(cFrame->IsVisible(cShapePane))cFrame->HideFrame(cShapePane);
	else cFrame->ShowFrame(cShapePane);
	
	ReDrawFrames();
}

///////////////////////////////////////
/// Canvas and histogram management  //
///////////////////////////////////////

// Checks if the Canvas we were using still exists
TObject* UltraFitEnv::FindCan(){
	//cout<<endl<<"ERROR IN FN D"<<flush;

	return gROOT->GetListOfCanvases()->FindObject(cCan);
}

// Check if we are still using an existing canvas
// Else make a new one
TCanvas* UltraFitEnv::GetCan(){
	//cout<<endl<<"ERROR IN FN E"<<flush;
	cCan=(TCanvas*)FindCan();//
	
	if(!cCan){
		// Switch back to class owned if it exists
		
		ShowCanvas();
		if(cPan)cCan=cPan->GetCanvas();//This should always be true in new version
// 		cCan=(TCanvas*)gROOT->GetListOfCanvases()->FindObject("UltraFitCanvas");
		if(cCan)return cCan;
		
		
		// Create it if it doesnt exist
		cCan=new TCanvas("UltraFitCanvas","UltraFitCanvas",800,600);
		cCan->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "UltraFitEnv", this,"ClickedCanvas(Int_t,Int_t,Int_t,TObject*)");
		//Make it invincible, for reasons
// 		TRootCanvas* c=(TRootCanvas*)cCan->GetCanvasImp();
// 		c->Connect("CloseWindow()","TRootCanvas",c,"DontCallClose()");
	}
	return cCan;
}

void UltraFitEnv::KillCan(){
	if(FindCan()){
		cCan->Disconnect(0,this,0);
// 		if(!(strcmp(cCan->GetName(),"UltraFitCanvas"))){			
// 			TQObject::Disconnect((TCanvas*)cCan);
// 			gROOT->GetListOfCanvases()->Remove(cCan);
// 			delete cCan;
// 		}
	}
	cCan=0;
}

// Setting to an external canvas no controlled by UltraFitEnv
void UltraFitEnv::ConnectNewCanvas(TVirtualPad* fPad){if(!fPad)return;
	//cout<<endl<<"ERROR IN FN F"<<flush;
	if(!gROOT->GetListOfCanvases()->FindObject(fPad))return;
	if(!(strcmp(fPad->GetName(),"UltraFitCanvas")))return;
	//Its got to exist and be unrelated

	HideCanvas();
	KillCan();

// 	//Connect the new pad and grab the histogram if it has one
	cCan=fPad->GetCanvas();
	SetNewHist(hist_capture(fPad));
	cCan->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "UltraFitEnv", this,"ClickedCanvas(Int_t,Int_t,Int_t,TObject*)");
};

void UltraFitEnv::ExternalHistUpdateCheck(){
	//cout<<endl<<"ERROR IN FN G"<<flush;
	if((strcmp(GetCan()->GetName(),"UltraFitCanvas"))){//if using external canvas
		TH1* fHist=hist_capture(GetCan());
		if(fHist){//if it has a histogram
			if(gHist&&gHistDrawn){//If there is a current histogram
					
				if(gHistDrawn==fHist){//Is it just a the one we drew
					return;
				}
			}
			SetNewHist(fHist);
		}
	}
}

void UltraFitEnv::SetNewHist(TH1* fHist){if(!fHist)return;
	//cout<<endl<<"ERROR IN FN H"<<flush;
	stringstream ss;
	ss <<"gHist"<<UltraFitEnv_iterator;
	UltraFitEnv_iterator++;
	if(gHist!=0)delete gHist;
	gHist=(TH1*)fHist->Clone(ss.str().c_str());
	gHist->SetStats(0);
	gHist->GetXaxis()->SetRange(1,-1);
	DrawgHist();
	cRClicker.clear();
	cClicker.clear();
	cExClicker.clear();
	cSaveLabels.clear();
	fFitFinished=false;
}

void UltraFitEnv::ReDrawgHist(){
	cRClicker.clear();
	cClicker.clear();
	cExClicker.clear();
	DrawgHist();
}

void UltraFitEnv::DrawgHist(){
	TVirtualPad* hold=gPad;
	
	//cout<<endl<<"ERROR IN FN I"<<flush;
	if(!gHist)return;
	TCanvas* fCan=GetCan();
	if(fCan){
		fCan->cd();
		
		//This is another protection of gHist
		gHistDrawn=DrawCopyHistOpt(gHist);
		
		//Add the labels on the top
		DrawSaveLabels();

		if(!fCan->GetShowEventStatus())fCan->ToggleEventStatus();//info at the bottom
		gPad->Update();	
	}
	
	gPad=hold;
}

void UltraFitEnv::DrawSaveLabels(){
	TVirtualPad* hold=gPad;
	
	TCanvas* fCan=GetCan();
	if(fCan){
		fCan->cd();
		
		obj_removeall(TText::Class(),GetCan());
		if(fCheck0->GetState()){
			for(unsigned int i=0;i<cSaveLabels.size();i++){
				cSaveLabels[i].Draw();
			}
		}
		gPad->Modified();
		gPad->Update();
	
	}
	gPad=hold;
}

void UltraFitEnv::SetCapture(int mode){
	//cout<<endl<<"ERROR IN FN J"<<flush;
	TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "CaptureHistogram(TPad*,TObject*,Int_t)");
	TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "CaptureCanvas(TPad*,TObject*,Int_t)");
	if(mode)TQObject::Connect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", "UltraFitEnv", this, "CaptureHistogram(TPad*,TObject*,Int_t)");
	else TQObject::Connect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", "UltraFitEnv", this, "CaptureCanvas(TPad*,TObject*,Int_t)");
};

void UltraFitEnv::CaptureHistogram(TPad* pad,TObject* obj,Int_t event){
	//cout<<endl<<"ERROR IN FN K"<<flush;
	if(1 == event){
		
		TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "CaptureHistogram(TPad*,TObject*,Int_t)");
		
		if(obj){
			TH1* fH=0;
			if(obj->InheritsFrom("TH1"))fH=(TH1*)obj;
			else fH=hist_capture(pad);
			
			if(fH){
				// If we're using an external canvas, stop doing that
// 				if(strcmp(GetCan()->GetName(),"UltraFitCanvas")){
				if(GetCan()!=cPan->GetCanvas()){
					cCan->Disconnect(0,this,0);
					cCan=0;
				}
				
				ShowCanvas();
				cPan->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "UltraFitEnv", this,"ClickedCanvas(Int_t,Int_t,Int_t,TObject*)");
				SetNewHist(fH);return;
			}
		}
		HideCanvas();
		cout<<endl<<endl<<"Capture Failed"<<endl;
	}
}

//For external setting of a new hist rather than GUI
void UltraFitEnv::PassNewHist(TH1* fH){if(!(cPan&&fH))return;
	// If we're using an external canvas, stop doing that
	if(GetCan()!=cPan->GetCanvas()){
		cCan->Disconnect(0,this,0);
		cCan=0;
	}
	
	ShowCanvas();
	cPan->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "UltraFitEnv", this,"ClickedCanvas(Int_t,Int_t,Int_t,TObject*)");
	SetNewHist(fH);
}


void UltraFitEnv::CaptureCanvas(TPad* pad,TObject* obj,Int_t event){
	//cout<<endl<<"ERROR IN FN L"<<flush;
	if(1 == event && pad){
		TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "CaptureCanvas(TPad*,TObject*,Int_t)");
		ConnectNewCanvas(pad);
	}

}

void UltraFitEnv::HideCanvas(){
	mainhold->HideFrame(cPan);
	ReDrawFrames();
}
void UltraFitEnv::ShowCanvas(){
	mainhold->ShowFrame(cPan);
	cPan->Resize(800,600);
	ReDrawFrames();
}
void UltraFitEnv::ReDrawFrames(){
// 	cFrame->MapSubwindows();
	cFrame->Resize(cFrame->GetDefaultSize());
	cBar->Resize(cBar->GetDefaultSize());
	gClient->NeedRedraw(cBar);
}


///////////////////////////////////////
/// Text Box Management  //
///////////////////////////////////////
	
void  UltraFitEnv::TextToSep(){
	//cout<<endl<<"ERROR IN FN N"<<flush;
	this->SetN();
	UpdateLines();
}
	
void  UltraFitEnv::SetN(){
	//cout<<endl<<"ERROR IN FN P"<<flush;
	stringstream ss;
	ss<<cNfit;
	cNpd->SetText(ss.str().c_str());
	gClient->NeedRedraw(cNpd);
	
	if(cNfit>6)cout<<endl<<endl<<"BAD IDEA"<<endl<<endl;
	
	cNfree=cNfit;
	for(int i=0;(unsigned)i<cNfit-1;i++)if(string(cTbox[i]->GetBuffer()->GetString()).size()>0)cNfree--;
}

void  UltraFitEnv::SetSep(unsigned int fN,double fS,double fSe){
	//cout<<endl<<"ERROR IN FN Q"<<flush;
	while(cNfit<fN)this->AddTextBox();
	if(fN<2)return;
	stringstream ss;
	ss<<fS;
	if(fSe>0)ss<<"+"<<fSe;
	cTbox[fN-2]->SetText(ss.str().c_str());
}
	
void  UltraFitEnv::AddTextBox(){if(!cBar)return;
	//cout<<endl<<"ERROR IN FN R"<<flush;
	
	TGHorizontalFrame* fHframe0;
	
	if(cTframe.size()<cNfit){
		fHframe0  = new TGHorizontalFrame(cFrame, 0, 0, 0);   //create a frame, filled with objects horizontally

			TGTextEntry* fTeh1 = new TGTextEntry(fHframe0,new TGTextBuffer(5));
			fTeh1->Connect("TextChanged(char*)", "UltraFitEnv", this,"TextToSep()");//Continually does things while typing is occurring, so only link to simple fn
			fTeh1->SetDefaultSize(60,25);
			fTeh1->SetToolTipText(("Separation\n Peak "+std::to_string(cPTbox.size()-1)+"<->"+std::to_string(cPTbox.size())+" fixed separation.\n blank = unconstrained").c_str());
			cTbox.push_back(fTeh1);
			
		fHframe0->AddFrame(fTeh1);
		
			TGTextEntry* fTeh2 = new TGTextEntry(fHframe0,new TGTextBuffer(5));
			fTeh2->SetDefaultSize(60,25);
			fTeh2->SetToolTipText(("Ratio\n Peak "+std::to_string(cPTbox.size()-1)+"<->"+std::to_string(cPTbox.size())+" fixed area ratio.\n blank = no relation").c_str());
			cRTbox.push_back(fTeh2);		
		fHframe0->AddFrame(fTeh2);		

			TGTextEntry* fTeh3 = new TGTextEntry(fHframe0,new TGTextBuffer(5));
			fTeh3->SetDefaultSize(45,25);
			fTeh3->SetEnabled(0);
			fTeh3->SetToolTipText(("Centroid\n Peak "+std::to_string(cPTbox.size())+" absolute centroid\n Selected/Result.").c_str());
			cPTbox.push_back(fTeh3);
			
		fHframe0->AddFrame(fTeh3,new TGLayoutHints(kLHintsExpandX));
		
		cTframe.push_back(fHframe0);
		cFrame->AddFrame(fHframe0,new TGLayoutHints(kLHintsExpandX,5,5,3,2));
		if(!cFrame->IsVisible(cShapePane)){cFrame->MapSubwindows();HideShape();}
		else cFrame->MapSubwindows();
	}else{
		fHframe0=cTframe[cNfit-1];
		cFrame->ShowFrame(fHframe0);
	}

	ReDrawFrames();
	
	cNfit++;
	this->SetN();
}
	
void  UltraFitEnv::RemoveTextBox(){if(!cBar)return;
	//cout<<endl<<"ERROR IN FN S"<<flush;
	if(cNfit>1){
		cFrame->HideFrame(cTframe[cNfit-2]);
		cFrame->Resize();
		
		ReDrawFrames();

		cNfit--;
		this->SetN();
	}
	
}

///////////////////////////////////////
/// Canvas clicking handling  //
///////////////////////////////////////


vector< double > UltraFitEnv::GetClicks(int fN){
	//cout<<endl<<"ERROR IN FN T"<<flush;
	if(cClicker.size()==0)cClicker.push_back(0.0);
	while(cClicker.size()<(unsigned)fN)cClicker.push_back(cClicker[cClicker.size()-1]);
	
	vector< double > fReturn;
	for(int i=1;i<=fN;i++)fReturn.push_back(cClicker[cClicker.size()-i]);
	std::sort (fReturn.begin(), fReturn.end());
	return fReturn;
}

void UltraFitEnv::ClickedCanvas(Int_t event, Int_t px, Int_t py, TObject *selected_ob){// cout<<event<<endl;
	//cout<<endl<<"ERROR IN FN U"<<flush;
	
	cSaveConf=0;
	cClearConf=0;
	
	TCanvas* fCan=GetCan();
	if(!fCan)return;
	
	double Y=fCan->AbsPixeltoY(py);
	double X=fCan->AbsPixeltoX(px);	
	double y1=fCan->GetUymin(),y2=fCan->GetUymax();
	double x1=fCan->GetUxmin(),x2=fCan->GetUxmax();

	//To find the number binding of key presses
// 	if(kKeyPress == event)cout<<endl<<px<<" "<<py<<endl;
	
	//+- key adds remove a peak
	if(kKeyPress == event &&py==43 ){AddTextBox();return;}
	if(kKeyPress == event &&py==45 ){RemoveTextBox();return;}
	
	//  . s S Del
	if(kKeyPress == event && (py==46||py==83||py==115||py==4103) ){SaveFit();return;}
	
	//Number keys set the number of peaks
	if(kKeyPress == event && py-48>0 &&  py-48<10){
		unsigned int N=py-48;
		while(cNfit<N)AddTextBox();
		while(cNfit>N)RemoveTextBox();
		return;
	}
	
	//Enter key to fit
	if(kKeyPress == event && (py==4100 ||  py==4101)){
		FitGUIPeak();
		return;
	}

	//pressing shift turns on background specification
	if(kKeyPress == event &&py==4128 ){cShift=!cShift;return;}
	
	//pressing ctrl turns on off maxima peak specification
	if(kKeyPress == event &&py==4129 ){cCtrl=!cCtrl;return;}
	
	//pressing alt turns on off exclusion range specification
	if(kKeyPress == event &&py==4131 ){cAlt=!cAlt;return;}
	
	//  C c  key clears exclusion regions
	if(kKeyPress == event && (py==99||py==67) ){ClearExclusion();return;}
	
	if(Y>y2||Y<y1||X<x1||X>x2){
		fCan->SetCrosshair(0);
	}else{
		if (event==kMouseEnter){
			fCan->SetCrosshair(1);
			return;
		}
		
		if ( (event == kButton1Up && cShift) || event == kButton2Up ) {
			cRClicker.push_back(X);
			this->UpdateLines();
			cShift=0;
		}else if(event == kButton1Up && cAlt){
			if(cExClicker.size()%2)cAlt=0;
			cExClicker.push_back(X);
			this->UpdateLines();
		}else if(event == kButton1Up && cCtrl){
			if(fFitFinished){fFitFinished=false;cRClicker.clear();}
			cClicker.push_back(X);
			this->UpdateLines();
		}else if(event == kButton1Up){if(gHist){
			if(fFitFinished){fFitFinished=false;cRClicker.clear();}
			ExternalHistUpdateCheck();
			FindLocalMax(gHist,X);
			cClicker.push_back(X);
			this->UpdateLines();		
		}}
	}
	return;
}

void UltraFitEnv::RemoveLines(){
	//cout<<endl<<"ERROR IN FN V"<<flush;
	if(!fCheck0->GetState())obj_removeall(TText::Class(),GetCan());
	obj_removeall(TLine::Class(),GetCan());
	obj_removeall(TBox::Class(),GetCan());
	
// 	TCanvas* fCan=GetCan();		
// 	if(fCan){
// 		//remove old lines
// 		TObject *obj;TIter next(fCan->GetListOfPrimitives());
// 		while ((obj = next())){
// 		if(obj->InheritsFrom("TText")||obj->InheritsFrom("TLine")||obj->InheritsFrom("TBox"))
// 			fCan->GetListOfPrimitives()->Remove(obj);
// 		}
// 	}
}

void UltraFitEnv::UpdateLines(){
	TVirtualPad* hold=gPad;
	//cout<<endl<<"ERROR IN FN W"<<flush;
	TCanvas* fCan=GetCan();	
	if(!fCan)return;
	
	fCan->cd();
	
	RemoveLines();

	double y1=fCan->GetUymin(),y2=fCan->GetUymax();
	double x1=fCan->GetUxmin(),x2=fCan->GetUxmax();	
	if(fCan->GetLogy()){y1=pow(10,y1);y2=pow(10,y2);}
	
	vector< double >fPass=MakeBoundryPeakListAbs();
	
	TLine fLine;
	for(unsigned int i=0;i<fPass.size();i++){
		if(i==0||i==fPass.size()-1)fLine.SetLineColor(3);
		else fLine.SetLineColor(2);
		double X=fPass[i];
		if(X<x2&&X>x1)
		fLine.DrawLine(X,y1,X,y2);
	}
	
	TBox fBox;
	fBox.SetLineColor(7);
	fBox.SetFillColor(7);
	fBox.SetFillStyle(3005);
	TBox fBoxL;
	fBoxL.SetFillStyle(0);
	fBoxL.SetLineColor(7);
	fLine.SetLineColor(7);
	
	for(unsigned int i=0;(i*2)+1<cExClicker.size();i++){
		double X1=cExClicker[i*2];
		double X2=cExClicker[i*2+1];
		if((X2>x2&&X1>x2)||(X2<x1&&X1<x1))continue;
		if(X2>x2)X2=x2;
		if(X1>x2)X1=x2;
		if(X2<x1)X2=x1;
		if(X1<x1)X1=x1;
		fBox.DrawBox(X1,y1,X2,y2);
		fBoxL.DrawBox(X1,y1,X2,y2);
	}
	
	if(cExClicker.size()%2){
		double X=cExClicker[cExClicker.size()-1];
		if(X<x2&&X>x1)
		fLine.DrawLine(X,y1,X,y2);
	}
	
	fCan->Modified();
	fCan->Update();
	gPad->Update();
	gPad=hold;
}

///////////////////////////////////////
/// Fitting Functions  //
///////////////////////////////////////

vector< jPeakDat > UltraFitEnv::MakePeakList(){
	//cout<<endl<<"ERROR IN FN X"<<flush;
	
	vector< double > fC= GetClicks(cNfree);//Get the absolute peak positions of any NOT fixed peaks
	vector< jPeakDat > fPass;	
	
	fPass.push_back(jPeakDat(fC[0],0,-1,-1,-1));// first peak
	double prevpos=fC[0];
	cZc->SetText(TString::Format("%.1f",prevpos));
	gClient->NeedRedraw(cZc);	

	int sClick=1;
	for(unsigned int i=0;i<cNfit-1;i++){
		
		double Pval,Perr=-1,Rval=-1,Rerr=-1;
		bool Pconstr=false;
		
		string str=cTbox[i]->GetBuffer()->GetString();
		if(str.size()>0){
			Pconstr=true;
			ExtractError(str,Pval,Perr);	
		}
		
		str=cRTbox[i]->GetBuffer()->GetString();
		if(str.size()>0){
			ExtractError(str,Rval,Rerr);	
		}
		
		if(!Pconstr){
			Pval=fC[sClick]-prevpos;
			sClick++;
		}
		
		fPass.push_back(jPeakDat(Pval,Pconstr,Perr,Rval,Rerr));
		prevpos+=Pval;
		
		//update the text on the cBar
		cPTbox[i+1]->SetText(TString::Format("%.1f",prevpos));
		gClient->NeedRedraw(cPTbox[i+1]);		
	}
	
	return fPass;
}

vector< double > UltraFitEnv::MakeBoundryPeakListAbs(){
	
	double bound_l,bound_u;
	vector< jPeakDat >fPass=MakeBoundryPeakList(bound_l,bound_u);
	vector< double > ret;
	double prevpos=0;

	ret.push_back(bound_l);
	for(unsigned int i=0;i<fPass.size();i++){
		prevpos+=fPass[i].Centroid;
		ret.push_back(prevpos);
	}
	ret.push_back(bound_u);
	
	return ret;		
}

vector< jPeakDat > UltraFitEnv::MakeBoundryPeakList(double& bound_l,double& bound_u){
	//cout<<endl<<"ERROR IN FN Y"<<flush;
	vector< jPeakDat > fPeaks=MakePeakList();

	double prevpos=fPeaks[0].Centroid;
	double peaklow=prevpos,peakhigh=prevpos;
	
	for(unsigned int i=1;i<fPeaks.size();i++){
		prevpos+=fPeaks[i].Centroid;
		if(prevpos<peaklow)peaklow=prevpos;
		if(prevpos>peakhigh)peakhigh=prevpos;
	}
	
	bound_l=peaklow-20;
	bound_u=peakhigh+20;

	if(cRClicker.size()>1){
		bound_l=cRClicker[cRClicker.size()-1];bound_u=cRClicker[cRClicker.size()-2];
		if(bound_l>bound_u){double t=bound_l;bound_l=bound_u;bound_u=t;}
	}else{
		if(gHist){
			int a=gHist->GetXaxis()->FindBin(peaklow);
			int b=gHist->GetXaxis()->FindBin(peakhigh);
			int L=a-20,U=a+20;
			int l=b-20,u=b+20;
			
			TH1* lHist=SmoothOffBack(gHist);
			FitPositionOptimisation(lHist,a,L,U);
			FitPositionOptimisation(lHist,b,l,u);
			delete lHist;
			
			bound_l=gHist->GetXaxis()->GetBinCenter(L);
			bound_u=gHist->GetXaxis()->GetBinCenter(u);
		}
		
		if(cRClicker.size()==1){
			if(cRClicker[0]<peaklow)bound_l=cRClicker[0];
			else bound_u=cRClicker[0];
		}
	}

	return fPeaks;
}

void  UltraFitEnv::FitGUIPeak(){
	//cout<<endl<<"ERROR IN FN Z"<<flush;
	ExternalHistUpdateCheck();
			
	cGoodFit=false;
	cPeakLabels.clear();
	cSaveConf=0;
	cClearConf=0;
	
	if(!gHist)return;
	double bound_l,bound_u;
	vector< jPeakDat >fPass=MakeBoundryPeakList(bound_l,bound_u);
	
	TH1* fExclusionHist=0;
	if(cExClicker.size()>1){
		fExclusionHist=(TH1*)gHist->Clone("ExclusionHist");
		for(unsigned int i=0;(i*2)+1<cExClicker.size();i++){
			int X1=gHist->GetXaxis()->FindBin(cExClicker[i*2]);
			int X2=gHist->GetXaxis()->FindBin(cExClicker[i*2+1]);
			if(X1>X2){int X=X1;X1=X2;X2=X;}
			
			for(int j=X1;j<=X2;j++){
				fExclusionHist->SetBinContent(j,0);
				fExclusionHist->SetBinError(j,0);
			}
		}
	}
	
	string fixsig=cShapeTsig->GetBuffer()->GetString();
	string fixdec=cShapeTdecay->GetBuffer()->GetString();
	string fixsha=cShapeTshare->GetBuffer()->GetString();
	
	int fittype=fCheck1->GetState();
	if(fCheck2->GetState())fittype=2;//trumps fCheck1
	
	FullFitHolder* fHold=Ultrapeak::PeakFit(gHist,bound_l,bound_u,fPass,fCombo->GetSelected(),fittype,fixsig,fixdec,fixsha,fExclusionHist);
	if(fExclusionHist)delete fExclusionHist;
	
	fFitFinished=true;
	this->UltraFitAfter(fHold);
}

void UltraFitEnv::UltraFitAfter(FullFitHolder* fHold){
	TVirtualPad* hold=gPad;
	//cout<<endl<<"ERROR IN FN AAA"<<flush;
	if(fHold&&gHist){
		
// 		cRClicker.clear();
// 		cClicker.clear();
// 		cExClicker.clear();
		
		//This calculates all the data (area etc) internally using MakeUltraData(fHold) and stores in fHold's vector
		Ultrapeak::PrintData(fHold,1,gHist);
				
		//update the text on the cBar
		cPeakLabels.clear();
		for(unsigned int i=0;i<cNfit;i++){
			double cc=fHold->CVal(Ultrapeak::VPC(i));
			double oo=fHold->CVal(Ultrapeak::VOff);
			
			cPTbox[i]->SetText(TString::Format("%.1f",cc+oo));
			gClient->NeedRedraw(cPTbox[i]);
			
			double hh = gHist->GetBinContent(gHist->GetXaxis()->FindBin(cc));
			cPeakLabels.push_back(TText(cc,hh*1.05,TString::Format("%.1f",cc+oo)));
		}
		
		// Actually update what is drawn
		TCanvas* fCan=GetCan();
		if(fCan){
			fCan->cd();
			double x1=fCan->GetUxmin(),x2=fCan->GetUxmax();
			DrawgHist();
			if(gHistDrawn){
				if(fCheck0->GetState())for(unsigned int i=0;i<cNfit;i++){
					cPeakLabels[i].SetTextAlign(21);
					cPeakLabels[i].SetTextFont(82);
					cPeakLabels[i].SetTextSize(0.025);
					cPeakLabels[i].Draw();
				}
				
				gHistDrawn->GetXaxis()->SetRangeUser(x1,x2);
				Ultrapeak::DrawPeak(fHold,GetCan()); // Want this to be the last thing drawn
			}
		}
		
		
		cLastFit=*fHold;
		delete fHold;
		cGoodFit=true;
	}
	gPad=hold;
}


///////////////////////////////////////
/// Saving  //
///////////////////////////////////////

void UltraFitEnv::SaveFit(){
	//cout<<endl<<"ERROR IN FN BBB"<<flush;
	if(cGoodFit){
		cFitList.push_back(new FullFitHolder(cLastFit));
		cout<<endl<<"Fit data saved."<<endl;
		cGoodFit=false;
		
		TObject* last = GetCan()->GetListOfPrimitives()->Last();
		if(last)if(last->InheritsFrom("TF1"))((TF1*)last)->SetLineColor(4);
		
		for(unsigned int i=0;i<cPeakLabels.size();i++)cSaveLabels.push_back(cPeakLabels[i]);
		cPeakLabels.clear();
		DrawSaveLabels();
		
		gPad->Modified();
		gPad->Update();
		
		if(gHist)Ultrapeak::DrawPeak(&cLastFit,0,gHist);//giving histogram says add and 0 for pad skips the draw
	}
}

void UltraFitEnv::ExportFits(){
	//cout<<endl<<"ERROR IN FN CCC"<<flush;
	if(cFitList.size()==0){
		cout << "No Peaks to export" << endl;
		return;
	}
	
	if(!cSaveConf){
		ifstream check("peakinfo.dat");
		if(check.is_open()){
			check.close();
			cout<<endl<<"File peakinfo.dat exists in the current directory.";
			cout<<endl<<"Click again to overwrite."<<endl;
			cSaveConf=true;
			return;
		}
	}

	ofstream outFile("peakinfo.dat");

	if(gHist)Ultrapeak::PrintData(cFitList,gHist,outFile);//Extra inputs shouldn't be needed as cVal already calculated
	else Ultrapeak::PrintData(cFitList,1,outFile);
	
	outFile.close();
	cout << "Peak info for "<<cFitList.size()<<" fits exported!" << endl;
	cSaveConf=false;
}

void UltraFitEnv::PrintFits(){
	if(gHist)Ultrapeak::PrintData(cFitList,gHist);//Extra inputs shouldn't be needed as cVal already calculated
	else Ultrapeak::PrintData(cFitList,1);
}

const char gHelpCanvas[] = "\n\
  This fitting environment is designed for the automatic fitting of Gaussian \n\
  peaks convolved with exponential tails.\n\
\n\
  The tool operates in two primary modes:\n\
	-A histogram may be captured and stored by the tool.\n\
	-A canvas can be linked to the tool, any new histogram drawn in that \n\
	 canvas will become the fitting target.\n\
\n\
  In order to begin fitting click either [Capture Hist] or [Link Canvas] and\n\
  then immediately click on the Canvas/Histogram you want to fit.\n\
\n\
  While the mouse pointer is over the fit histogram,\n\
  the following controls and short-cuts may be used:\n\
		    <[Left Click]>	Select peak.\n\
			  <[Ctrl]>	Set manual bin select (default auto)\n\
			 <[Enter]>	Fit.\n\
		  <[Middle Click]>	Select fit-range.\n\
	<[Shft] THEN [Left Click]>	Select fit-range.\n\
	 <[Alt] THEN [Left Click]>	Select exclusion region.\n\
			     <[+]>	Increase the number of peaks.\n\
			     <[-]>	Decrease the number of peaks.\n\
		    <[0]-[9] keys>	Set the number of peaks.\n\
		   <[.]/[s]/[Del]>	Save latest fit to list & histogram.\n\
			     <[c]>	Clear the selected exclusion region.\n\
\n\n\
  The tool is designed for fits over small energy regions, as such, all shape \n\
  parameters of degenerate peaks are shared, as these parameters are dominated\n\
  by energy dependant physical effects which do not change rapidly.\n\
  Background across the fit region is approximated by a polynomial + an \n\
  optional step function constrained by the peak parameters. The step should be\n\
  used when beak sizes are large compared to background.\n\
  Pol0, pol1 and pol2 backgrounds may be selected (pol2 are poorly constrained).\n\
  Watch your fit's Reduced ChiSquards\n\
\n\
  For multi-peak/degenerate fits peak separation are set rather than absolute\n\
  centroids. This provides more accurate fitting overall as it is less sensitive\n\
  to small deviations in the absolute scale i.e. poor calibration.\n\
  The area ratio between peaks may also be set if it is in known.\n\
\n\
  When inputting multiple peaks to a fit, any constrained peaks should\n\
  immediately follow the peak to which they are fixed. Un-constrained peaks\n\
  should be in ascending order.\n\
    e.g. We have 3 peaks:\n\
           An unknown ~130 keV, a known 125 keV and a known 145 keV.\n\
           Inputs : A = 125\n\
                    B = A + 20\n\
		    C = 130\n\
          -We set the tool for 3 peaks\n\
          -Enter [20] in to the peak 0-1 \"separation\" input box.\n\
          -Click on each peak A and C in the histogram window.\n\
          -Click [Fit Peaks].\n\
  \n\
  For both separation and area ratio between peaks, the box should be left\n\
  blank to free the fit. Uncertainties on both constraint parameters may also\n\
  be added in the input box. If no error is given the parameter will be fixed.\n\
  Plain text input is fairly robust and accepts ENSDF format errors.\n\
  Example inputs : \"25.0\" \"0.051(2)\" \"-16.0 5\" \"6+-5\" \"3E-5+3e-6\"  \n\
  \n\
  For very small numbers of counts the fit mode will automatically switch to\n\
  Poisson Likelihood fitting rather than Pearson Chi Squared minimisation.\n\
  Exclusion regions will not function for Likelihood fitting.\n\
  \n\
  For problematic fits the shape parameters (Sigma, Decay and Sharing)\n\
  may be constrained. The bottom most button on the panel [^] will expose\n\
  these options. As with centroid & ratio these parameters may be fixed\n\
  or given with uncertainties and should be left blank when not constrained.\n\
\n\n\n\
";

void UltraFitEnv::Help(){
	TRootHelpDialog *hd;
	hd = new TRootHelpDialog(0, "Fitting tool help", 600, 400);
	hd->SetText(gHelpCanvas);
	hd->Popup();
}

void UltraFitEnv::jSaveAs(){
	if(gHist)HistSaveAs(gHist,cBar,GetCan());
}

void UltraFitEnv::SwitchDecayLabel(){
	if(fCheck2->GetState()){
		decaysigmablabel->SetText("SigmaB");
		fCheck1->SetState(kButtonUp);
	}
	else decaysigmablabel->SetText("Decay  ");
}


void UltraFitEnv::ClearExclusion(){
	cExClicker.clear();
	this->UpdateLines();
}
