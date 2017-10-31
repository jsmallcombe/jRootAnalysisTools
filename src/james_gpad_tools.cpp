#include "james_gpad_tools.h"
#include "james_fitting.h"



///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

TObject* obj_capture(TClass* tclass,TVirtualPad* fPad){
	if(fPad){
		TObjLink *lnk = fPad->GetListOfPrimitives()->FirstLink();
		while (lnk) {
			if(lnk->GetObject()->InheritsFrom(tclass))return lnk->GetObject();
			lnk = lnk->Next();
		}
	}
	return 0;
}

void obj_removeall(TClass* tclass,TVirtualPad* fPad){
	obj_remove(tclass,fPad,true);
}


void obj_remove(TClass* tclass,TVirtualPad* fPad,bool all){
	if(fPad){
		TObjLink *lnk = fPad->GetListOfPrimitives()->FirstLink();
		while (lnk) {
			if(lnk->GetObject()->InheritsFrom(tclass)){
				fPad->GetListOfPrimitives()->Remove(lnk->GetObject());
				lnk = fPad->GetListOfPrimitives()->FirstLink();//shouldnt cause infinite loop
				if(!all)return;
			}else{
				lnk = lnk->Next();
			}
		}
	}
	return;
}

TH1* hist_capture(TVirtualPad* fPad){
	return (TH1*)obj_capture(TH1::Class(),fPad);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////


// Just a basic little no frills, minimal input peak fitter for standard size y/e peaks
// Added it in to help with quick peak identification
void ClickPeakDrawConnect(Int_t event, Int_t px, Int_t py, TObject *selected_ob)
{TVirtualPad* hold=gPad;
	
	if(!gTQSender)return;
	if(((TObject*)gTQSender)->IsA() != TCanvas::Class())return;
	TCanvas* Can=((TCanvas*)gTQSender);
	
	TGToolTip *fTip=(TGToolTip*)obj_capture(TGToolTip::Class(),Can);
	if(!fTip){
		fTip = new TGToolTip(100, 100,"", 200);	// create the tooltip with a timeout of 200 ms
			fTip->Hide();
			Can->GetListOfPrimitives()->Add(fTip);
	}
	if(event == kMouseLeave){fTip->Hide(); return;}
	
	//Click is given in pixel coordinates
	double x =Can->PixeltoX(px);
	
	fTip->Hide();
	fTip->SetText(TString::Format("%.1f",x));
	fTip->SetPosition(Can->GetWindowTopX()+px+15,Can->GetWindowTopY()+py-15);
	fTip->Reset();

	if (event == kButton1Double){

		TH1* h=hist_capture(Can);
		if(!h) return;
		
		obj_removeall(TF1::Class(),Can);
		obj_removeall(TText::Class(),Can);
		
		TF1* Quick=UserQuickSingleGausAutoFitE(h,x,x-20,x+20,1);//Free & linear back
		Can->cd();
		Quick->DrawCopy("same");
		// Print the text on the canvas
		double cent=Quick->GetParameter(1);
		stringstream ss;
		ss<<round(cent*10)/10;
		delete Quick;
		TText peaknum;
		peaknum.SetTextAlign(22);
		peaknum.SetTextSize(0.035);	
		
		double shif=(h->GetXaxis()->GetBinCenter(h->GetXaxis()->GetLast())-h->GetXaxis()->GetBinCenter(h->GetXaxis()->GetFirst()))*0.05;
		//GetXmin() doesnt account for zooming		
		
		peaknum.DrawText(cent+shif,h->GetBinContent(h->FindBin(cent))*0.95,ss.str().c_str());
		
		Can->GetCanvas()->Modified();
		Can->GetCanvas()->Update();
	}
	
gPad=hold;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

HistClickStop::HistClickStop(TH1* hist,string title,bool yaxis):selected(0),pickedx(0),pickedy(0),cCan(0),xy(yaxis){
	if(!hist){pickedx=1;pickedy=1;selected=true;return;}
	
	cCan=new TCanvas("NAMETEST");
	cCan->SetTitle(title.c_str());
	//Make it invincible, for reasons
	TRootCanvas* c=(TRootCanvas*)cCan->GetCanvasImp();
	c->Connect("CloseWindow()","TRootCanvas",c,"DontCallClose()");
	c->ShowMenuBar(kFALSE);	
	
	TVirtualPad* pad=gPad;
	cCan->cd();
	TH1* h=hist->DrawCopy("colzhist");
	h->SetStats(kFALSE);
	h->SetTitle(title.c_str());
	cCan->Update();
	pad->cd();
	
	cCan->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "HistClickStop", this,"ClickedCanvas(Int_t,Int_t,Int_t,TObject*)");
};
	
void HistClickStop::ClickedCanvas(Int_t event, Int_t px, Int_t py, TObject *selected_ob){
		if(!cCan)return;
		
		double Y=cCan->AbsPixeltoY(py);
		double X=cCan->AbsPixeltoX(px);	
		double y1=cCan->GetUymin(),y2=cCan->GetUymax();
		double x1=cCan->GetUxmin(),x2=cCan->GetUxmax();
		
		bool incan=(Y<y2&&Y>y1&&X>x1&&X<x2);
		
		if (event==kMouseEnter){
			if(incan)
			cCan->SetCrosshair(1);
			else
			cCan->SetCrosshair(0);
		}
		
		if(event==kButton1Up)if(incan){
// 			cout<<endl<<Y<<" "<<X<<endl;
			pickedx=X;
			pickedy=Y;
			selected=true;
			DeleteCan();
		}
}

double GetHistClickVal(TH1* hist,string title,bool y){
	HistClickStop Click(hist,title,y);
	while(Click){
		gSystem->ProcessEvents();
	}
	return Click;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

ClassImp(jhistquestion);

jhistquestion::jhistquestion(vector<string> butnam,TH1* hist) : TGMainFrame(gClient->GetRoot(), 100, 100,kVerticalFrame),fCanvas1(0){

	if(butnam.size()<1)return;
	if(butnam[0].size()<1)return;
	
	fCanvas1 = new TRootEmbeddedCanvas("", this, 800, 600);
	fCanvas1->GetCanvas()->SetBorderMode(0);
// 	fCanvas1->GetCanvas()->SetMargin(0.1,0.01,0.05,0.01);	
	AddFrame(fCanvas1, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0));	
	
	fBgroup1 = new TGButtonGroup(this,"",kChildFrame);// Another button group
		
		for(unsigned int i=0;i<butnam.size();i++){
			if(butnam[i].size()){
				TGTextButton* ftbutton = new TGTextButton(fBgroup1,butnam[i].c_str(),i+1);	
				ftbutton->SetToolTipText(butnam[i].c_str());
			}
		}	
		fBgroup1->SetLayoutHints(new TGLayoutHints(0,10, 10, 0, 0));
		fBgroup1->Show();
	AddFrame(fBgroup1,new TGLayoutHints(kLHintsCenterX, 0,0, 0, 0));
	
	if(hist){
		fCanvas1->GetCanvas()->cd();
		hist->DrawCopy("histcolz");
	}
	
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
}

TH1*  jhistquestion::DrawCopySame(TH1* h){
	if(h&&fCanvas1){
		fCanvas1->GetCanvas()->cd();
		return h->DrawCopy("histcolzsame");
	}
	return 0;
}

int jhistquestion::WaitAnswer(){
	answer=-1;
	if(fBgroup1){
		fBgroup1->Connect(" Clicked(Int_t)", "jhistquestion", this,"SetAnswer(Int_t)");
		this->Connect("CloseWindow()","TGMainFrame",this,"DontCallClose()");
		while(answer<0){
			gSystem->ProcessEvents();
		}
		this->CloseWindow();
	// 	this->Disconnect("CloseWindow()","TGMainFrame",this,"DontCallClose()");
	// 	this->SendCloseMessage();
	}
	return answer;
}
void jhistquestion::SetAnswer(Int_t in){
// 	TGButton *btn = (TGButton *) gTQSender;
// 	Int_t id = btn->WidgetId();
	answer=in;	
}
