#include "james_gpad_tools.h"



///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

TH1* hist_capture(TVirtualPad* fPad){
	if(fPad){
		TObjLink *lnk = fPad->GetListOfPrimitives()->FirstLink();
		while (lnk) {
			if(lnk->GetObject()->InheritsFrom("TH1"))return (TH1*)lnk->GetObject();
			lnk = lnk->Next();
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////


HistClickStop::HistClickStop(TH1* hist,string title,bool yaxis):selected(0),pickedx(0),pickedy(0),cCan(0),xy(yaxis){
	if(!hist){pickedx=1;pickedy=1;selected=true;return;}
	
	cCan=new TCanvas();
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

