#include "j_extra_guitools.h"

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



////////////////////////////////////////////////////////////////

jAngleAngel::jAngleAngel(TH1* fH) : TGMainFrame(gClient->GetRoot(), 100, 100,kVerticalFrame),fHistHigh(0),fHistLow(0),fHist(0){
TVirtualPad* hold=gPad;
    SetWindowName("jAngleAngel");
    SetCleanup(kDeepCleanup);
	Stop.Start();

	TGTextButton *CaptureButton = new TGTextButton(this," Capture Hist ");
	CaptureButton->Connect("Clicked()","jAngleAngel",this,"SetCapture()");	
	AddFrame(CaptureButton,new TGLayoutHints(kLHintsCenterX, 1, 1, 1, 1));

	fCanvas1 = new TRootEmbeddedCanvas("anglecan1",this,600,400);
    AddFrame(fCanvas1,new TGLayoutHints(kLHintsExpandX|kLHintsExpandY, 1, 1, 1, 1));
	
	fHslider = new TGHSlider(this, 360, kSlider2);
	fHslider->Connect("PositionChanged(Int_t)", "jAngleAngel", this, "SliderChange()");
	fHslider->Connect("Released()", "jAngleAngel", this, "SliderRelease()");
    AddFrame(fHslider,new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));

	TGHorizontalFrame* buttons = new TGHorizontalFrame(this);            

		TGTextButton *MakeButton = new TGTextButton(buttons," Make Hist ");
		MakeButton->Connect("Clicked()","jAngleAngel",this,"MakeHist()");	
		buttons->AddFrame(MakeButton);
		
		MakeButton = new TGTextButton(buttons," Make Hist90 ");
		MakeButton->Connect("Clicked()","jAngleAngel",this,"MakeHist90()");	
		buttons->AddFrame(MakeButton);
	AddFrame(buttons,new TGLayoutHints(kLHintsCenterX, 1, 1, 1, 1));
	
	fLine.SetLineColor(2);
	Nl=20;
    
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
	
	SetNewHist(fH);
	DoLines();
	
	lock=false;
	sliderpos=-1;
    
gPad=hold;
}

jAngleAngel::~jAngleAngel(){
    TQObject::Disconnect(this);
}
void jAngleAngel::SetNewHist(TH1 *fH){
	if(!fH)return;
	if(!fH->InheritsFrom("TH2"))return;
	
	fHistHigh=(TH2*)fH->Clone("fHistHigh");
	fHistLow=fHistHigh->Rebin2D(floor(fHistHigh->GetNbinsX()/50.),floor(fHistHigh->GetNbinsY()/50.),"fHistLow");
	fHist=fHistHigh;
	
	fCanvas1->GetCanvas()->cd();
	fHist->DrawCopy("col");
	hformat(fHist);
	gPad->Update();	
}

void jAngleAngel::SetCapture(){
	TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "CaptureHistogram(TPad*,TObject*,Int_t)");
	TQObject::Connect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", "jAngleAngel", this, "CaptureHistogram(TPad*,TObject*,Int_t)");
};

void jAngleAngel::CaptureHistogram(TPad* pad,TObject* obj,Int_t event){
	if(1 == event){
		
		TQObject::Disconnect("TCanvas", "Selected(TVirtualPad*,TObject*,Int_t)", 0, "CaptureHistogram(TPad*,TObject*,Int_t)");
		
		if(obj){
			TH1* fH=0;
			if(obj->InheritsFrom("TH1"))fH=(TH1*)obj;
			else fH=hist_capture(pad);
			
			if(fH){
				SetNewHist(fH);return;
			}
		}
		cout<<endl<<endl<<"Capture Failed"<<endl;
	}
}



// Lots of checks to try and slow the thing down
void jAngleAngel::SliderChange(){
	if(!fHist||sliderpos==fHslider->GetPosition()||lock)return;
	if(Stop.RealTime()<0.2){
		Stop.Start(kFALSE);	
		return;
	}
	Stop.Start();
	lock=true;
	
	if(fHist==fHistHigh){
		fHist=fHistLow;
		fCanvas1->GetCanvas()->cd();
		fHist->DrawCopy("col");
	}
	DoLines();

	lock=false;
};

void jAngleAngel::SliderRelease(){
	if(fHist==fHistLow){
		fHist=fHistHigh;
		fCanvas1->GetCanvas()->cd();
		fHist->DrawCopy("col");
	}
	DoLines();
};

// No checks just do
void jAngleAngel::DoLines(){

	sliderpos=fHslider->GetPosition();

	TCanvas *can=fCanvas1->GetCanvas();
	can->cd();
	obj_removeall(TLine::Class(),can);
// 	obj_removeall(TMarker::Class(),can);
	
	double Angle=TMath::Pi()*fHslider->GetPosition()/360.0;
	
	TAxis *X=fHist->GetXaxis();
	TAxis *Y=fHist->GetYaxis();
	
	// The currently drawn limits 
	double y0=Y->GetBinLowEdge(Y->GetFirst());
	double y1=Y->GetBinLowEdge(Y->GetLast()+1);
	double x0=X->GetBinLowEdge(X->GetFirst());
	double x1=X->GetBinLowEdge(X->GetLast()+1);
	double xr=(x1-x0);
// 	double yr=(y1-y0);
	
	// The midpoint
	double yn=(y0+y1)*0.5;
	double xn=(x0+x1)*0.5;
	
	// Gradient y/x;
// 	double g=yr/xr;
	double g=Y->GetBinWidth(1)/X->GetBinWidth(1);
	
	double wg=(double)fCanvas1->GetWidth()/fCanvas1->GetHeight();
	// The extra wg factor is for nice spacing when drawing, but not actually used in the angle ratio
	
	// Division for line spacing in x
	double dx=xr/Nl;
	double nl=0.5;

	double sn=sin(Angle);
	double cs=cos(Angle);
	double tn=tan(Angle);
	
// 	TMarker mark;
// 	mark.SetMarkerStyle(20);
	
// 	cout<<"."<<flush;
	while(nl<Nl){
		double YY=nl*dx*cs*g*wg;
		double XX=nl*dx*sn;
		YY+=yn;
		XX+=xn;
// 		mark.DrawMarker(XX,YY);
		
		double xb=x1;
		double yb=YY-(xb-XX)*g*tn;
		if(tn>0&&yb<y0){
			yb=y0;
			xb=XX-(yb-YY)/(g*tn);
		}else if(tn<0&&yb>y1){
			yb=y1;
			xb=XX-(yb-YY)/(g*tn);
		}
		if(yb>y1||yb<y0){
			break;
		}
// 		mark.DrawMarker(xb,yb);
		
		double xt=x0;
		double yt=YY-(xt-XX)*g*tn;	
		if(tn>0&&yt>y1){
			yt=y1;
			xt=XX-(yt-YY)/(g*tn);
		}else if(tn<0&&yt<y0){
			yt=y0;
			xt=XX-(yt-YY)/(g*tn);
		}
// 		mark.DrawMarker(xt,yt);
		
		fLine.DrawLine(xb,yb,xt,yt);
		if(nl<0){
			nl--;
		}
		nl=-nl;
	}
	can->Update();
};


// No checks just do
void jAngleAngel::MakeHist(double offset){
	double Angle=TMath::Pi()*fHslider->GetPosition()/360.0;
	Angle+=offset;
	
	TAxis *X=fHist->GetXaxis();
	TAxis *Y=fHist->GetYaxis();
	
	// The currently drawn limits 
	double y0=Y->GetBinLowEdge(Y->GetFirst());
	double y1=Y->GetBinLowEdge(Y->GetLast()+1);
	double x0=X->GetBinLowEdge(X->GetFirst());
	double x1=X->GetBinLowEdge(X->GetLast()+1);
	double yr=(y1-y0);

	
	// Gradient y/x;
// 	double g=yr/xr;
	double g=Y->GetBinWidth(1)/X->GetBinWidth(1);
	
	
	double tn=tan(Angle);	

	double xlow=x0+yr/(tn*g);
	double xhigh=x1;
	if(tn>0){
		xlow=x0;
		xhigh=x1+yr/(tn*g);
	}

	// A whole lot of guff to calculate speading the counts over bins
	double w=X->GetBinWidth(1);
	double range=1;
	TGraph grh;
	double t=1/abs(tn);
	if(t>1){t=1/t;
		double dx=(1-t)/t;
		range=w*(0.5*dx+1);
		grh.SetPoint(1,-range,0);
		grh.SetPoint(2,w*(-0.5*dx),(1-t)/(dx*w));
		grh.SetPoint(3,w*(0.5*dx),(1-t)/(dx*w));
		grh.SetPoint(4,range,0);
	}else{
		range=w*(0.5*(1-t)+t);
		grh.SetPoint(1,-range,0);
		grh.SetPoint(2,w*(-0.5*(1-t)),1/w);
		grh.SetPoint(3,w*(0.5*(1-t)),1/w);
		grh.SetPoint(4,range,0);
	}
	grh.SetPoint(0,-range*10,0);
	grh.SetPoint(5,range*10,0);
	
	TH1D smth("smth","smth",100,-range,range);
	for(int b=1;b<=smth.GetNbinsX();b++){
		smth.SetBinContent(b,grh.Eval(smth.GetBinCenter(b)));
	}
	smth.Scale(1.0/smth.Integral());
	TAxis *sax=smth.GetXaxis();
	double smwdth=sax->GetBinWidth(1);
	
	
	TH1D ret("jAngleAngelRet","jAngleAngelRet",fHist->GetNbinsX()*2,xlow,xhigh);
	TAxis *ax=ret.GetXaxis();
	
	int brange=ceil(range/ret.GetBinWidth(1));

	for(int x=1;x<=fHist->GetNbinsX();x++){
		for(int y=1;y<=fHist->GetNbinsY();y++){
			
			double XX=X->GetBinCenter(x);
			double YY=Y->GetBinCenter(y);
			double A=XX+(YY-y0)/(g*tn);
// 			ret.Fill(A,fHist->GetBinContent(x,y));	
			
			double C=fHist->GetBinContent(x,y);
			int B=ax->FindBin(A);
			for(int b=B-brange;b<=B+brange;b++){
				double smin=ax->GetBinLowEdge(b)-A;				
				double smax=ax->GetBinLowEdge(b+1)-A;	
				int bmin = sax->FindBin(smin);		
				int bmax = sax->FindBin(smax);		
				double frc = smth.Integral(bmin,bmax);
				//// These corrections dont actuall make the individual frc values more accurate
				//// They just stop the sum being greater than 1
				frc -= smth.GetBinContent(bmin)*(smin-sax->GetBinLowEdge(bmin))/smwdth;
				frc -= smth.GetBinContent(bmax)*(sax->GetBinUpEdge(bmax)-smax)/smwdth;

				ret.Fill(ax->GetBinCenter(b),C*frc);
			}
		}
	}
	
	new TCanvas();
	gPad->Update();
	ret.DrawCopy("hist");
}
