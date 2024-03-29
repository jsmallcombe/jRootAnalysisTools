#include "j_hist_formatting.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool gGlobalNegativeDraw=false;
Color_t gGlobalBackColor=kWhite;
Color_t gGlobalForeColor=kBlack;
bool gGlobalDrawMenuBars=true;




// Font_t gGlobalMainFont=42; //Text font code = 10*fontnumber + precision   4 = Helvetica 
// Font_t gGlobalMainFont=22; //Text font code = 10*fontnumber + precision   2 = Times-Bold 
///// bold-type carries over to pdf_latex
Font_t gGlobalMainFont=132; //Text font code = 10*fontnumber + precision   2 = Times


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Prepare Canvases for export as svg and subsequent conversion to pdf_latex
// The axis labes/titles alignments tend to be off if left to TAxis

void QuickReTexAxis(TH1* h,double x ,double y){
	ReTexAxisLab(h,x);
	ReTexAxisLab(h,y,true);
	ReTexAxisTitle(h);
	ReTexAxisTitle(h,"",true);
}


void ReTexAxisLab(TH1* h,double step,bool y,bool flipY,bool noExpt){
	
	gPad->Update();
	
	bool lx=gPad->GetLogx();
	bool ly=gPad->GetLogy();
	bool IsLog=((lx&&!y)||(ly&&y));
	if(IsLog){step=1;}
	
	double xrange=abs(gPad->GetX2()-gPad->GetX1()); //Canvas/window NOT AXIS
	double yrange=abs(gPad->GetY2()-gPad->GetY1());
    double Ymin=gPad->GetFrame()->GetY1();
	double Ymax=gPad->GetFrame()->GetY2();
    double Xmin=gPad->GetFrame()->GetX1();
	double Xmax=gPad->GetFrame()->GetX2();
	
	// If no step input (and not log) default to 5 ish divisions rounded to nearest 10
	if(step<=0){
		double range=(Xmax-Xmin)*0.4;
		if(y)range=(Ymax-Ymin)*0.4;
		double mag=pow(10,floor(log10(range)));
		step=floor(range/mag)*mag*0.5;
	}
	
	// Determine if an exponanty should be used
	bool Expt=(step>=5000)&&!noExpt&&!IsLog;
	int Expt10 =floor(log10(step)/3)*3;
	int Div=1;
	if(Expt){
		Div =pow(10,Expt10);
	}

	// Note:: Using GetY1 etc on Frame OR on gPad-directly, give range in user coords of axis-area OR entire-canvas respectively.
	// Note:: Also, GetFrame()->GetY2() == GetUymax()

	double xx=ceil(Xmin/step)*step;
	if(y)xx=ceil(Ymin/step)*step;

	if(y)h->GetYaxis()->SetLabelSize(0);
	else h->GetXaxis()->SetLabelSize(0);
	
	TText *text= new TText();
	text->SetTextFont(gGlobalMainFont);
	text->SetTextAlign(23);
	if(y){
		text->SetTextAlign(32);
		if(flipY)text->SetTextAlign(12);
	}

	double last=Xmax;
	if(y)last=Ymax;
	
	while(xx<=last){
        if(xx==0)xx=0;//Looks dumb but had issues with "-0"
		stringstream ss;
		if(IsLog){
			ss<<"10$^{"<<xx<<"}$";
		}else{
			ss<<xx/Div;
		}
		
		double px=xx;
		double py=Ymin-yrange*0.02;
		
		if(y){
			py=xx;
			px=Xmin-xrange*0.015;
			if(flipY){
				px=Xmax+xrange*0.015;
			}
		}
		
		// While the GetY1 etc return "value is in decades" the Draw command requires absolute value
		if(lx)px=pow(10,px);
		if(ly)py=pow(10,py);
		
		text->DrawText(px,py,ss.str().c_str());

		xx+=step;
	}
	
	if(Expt){
		stringstream ss;
		ss<<"$\\times$10$^{"<<Expt10<<"}$";
		
		text->SetTextAlign(11);
		double px=Xmax+xrange*0.01;
		double py=Ymin;
		if(y){
			px=Xmin;
			py=Ymax+yrange*0.01;
			if(flipY){
				text->SetTextAlign(31);
				px=Xmax;
			}
		}
		
		if(lx)px=pow(10,px);
		if(ly)py=pow(10,py);
		
		text->DrawText(Xmin,Ymax+yrange*0.01,ss.str().c_str());
	}
}

void ReTexAxisTitle(TH1* h,string title,bool y,double offset){

	double	a=gPad->GetLeftMargin();
	double	b=gPad->GetRightMargin();
	if(y){
		a=gPad->GetBottomMargin();
		b=gPad->GetTopMargin();
	}

	TAxis* X=h->GetXaxis();
	if(y)h->GetYaxis()->SetTitleSize(0);
	else X->SetTitleSize(0);
	

	TText *text= new TText();
	text->SetTextFont(gGlobalMainFont);
	
	text->SetTextAlign(21);
	if(y){text->SetTextAngle(90);text->SetTextAlign(23);}

	if(title.size()<1){
		title=X->GetTitle();
		if(y) title=h->GetYaxis()->GetTitle();
	}
	
	if(y) text->DrawTextNDC(offset,a+(1-b-a)*0.5,title.c_str());
	else text->DrawTextNDC(a+(1-b-a)*0.5,offset,title.c_str());

}

void DrawSharedTitle(string title,bool y,double offset){
	
	TCanvas* canvas = dynamic_cast<TCanvas*>(gPad->GetCanvas());

    if (!canvas) {
        std::cerr << "No TCanvas found." << std::endl;
        return;
    }
	
	double	a=1;
	double	b=1;
	if(y){
		a=gPad->GetBottomMargin();
		b=gPad->GetTopMargin();
	}

	
	// Iterate through all the pads of the canvas
    TList* pads = canvas->GetListOfPrimitives();
    TIter next(pads);
    TObject* obj;
	
	while ((obj = next())) {
        if (obj->InheritsFrom("TPad")) {
            TPad* pad = dynamic_cast<TPad*>(obj);

			if(y){
				Float_t bottomMargin = pad->GetBottomMargin();
				Float_t topMargin = pad->GetTopMargin();
				if(a>bottomMargin){a=bottomMargin;}
				if(b>topMargin){b=topMargin;}
			}else{
				Float_t leftMargin = pad->GetLeftMargin();
				Float_t rightMargin = pad->GetRightMargin();
				if(a>leftMargin){a=leftMargin;}
				if(b>rightMargin){b=rightMargin;}
				
			}
        }
    }
	
	TText *text= new TText();
	text->SetTextFont(gGlobalMainFont);
	
	if(y){
		text->SetTextAngle(90);
		text->SetTextAlign(23);
		text->DrawTextNDC(offset,a+(1-b-a)*0.5,title.c_str());
		
	}else{
		text->SetTextAlign(21);
		text->DrawTextNDC(a+(1-b-a)*0.5,offset,title.c_str());
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void invert(TH1* h){
   TH1* tmpclone=(TH1*)h->Clone("tmpclone");
   h->Reset();
   int N=h->GetNbinsX();
   for(int i=1;i<=N;i++){
        h->SetBinContent(i,tmpclone->GetBinContent(N-i+1));
        h->SetBinError(i,tmpclone->GetBinError(N-i+1));
   }
   delete tmpclone;
}

void transpose_bins(TH1* h, int binshift){
   int N=h->GetNbinsX();
   if(abs(binshift)>=N)return;
    
   TH1* tmpclone=(TH1*)h->Clone("tmpclone");
   h->Reset();
   for(int i=1;i<=N;i++){
        int b=i-binshift;
        if(b>0&&b<N){
            h->SetBinContent(i,tmpclone->GetBinContent(b));
            h->SetBinError(i,tmpclone->GetBinError(b));
        }
   }
   delete tmpclone;
}


void transpose_axis(TH1* h, double minX){
    TAxis* x=h->GetXaxis();
    double min=x->GetXmin();
    double max=x->GetXmax();
    x->SetLimits(minX,minX+max-min);
}

void axislab(TH1* HH,string x,string y,string z){
	HH->GetXaxis()->SetTitle(x.c_str());
	bool kev=(x.find("keV")<x.size());
	bool mev=(x.find("MeV")<x.size());
	
	
	if(y==""||y.find("ounts")<y.size()){
		double w=HH->GetXaxis()->GetBinWidth(1);
		stringstream ss;
		ss<<"Counts";
		bool N=true;
		
		if(w>1.0001||w<0.999){
			N=false;
			ss<<"/"<<w;
		}
		
		if(kev){
			if(N)ss<<"/";
			ss<<" keV";
		}
		
		if(mev){
			if(N)ss<<"/";
			ss<<" MeV";
		}
			
		HH->GetYaxis()->SetTitle(ss.str().c_str());
	}else{
		HH->GetYaxis()->SetTitle(y.c_str());	
	}
	if(z!=""){
		HH->GetZaxis()->SetTitle(z.c_str());	
	}	
}

//Add most common axis label so automated
void axislabelkev(TH1* HH){
	axislab(HH,"Energy (KeV)");
}

void hformat(TH1* HH,bool setminzero){if(!HH)return;
	TAxis* ax[3]={HH->GetXaxis(),HH->GetYaxis(),HH->GetZaxis()};
	axislab(HH,ax[0]->GetTitle(),ax[1]->GetTitle(),ax[2]->GetTitle());//slightly redundant
	for(int i=0;i<3;i++){
		ax[i]->SetTicks("+-");
		ax[i]->SetLabelFont(gGlobalMainFont);
		ax[i]->SetLabelSize(0.045);
		ax[i]->SetTitleFont(gGlobalMainFont);
		ax[i]->SetTitleSize(0.06);
		ax[i]->SetTitleOffset(1.1);
		ax[i]->SetTickLength(0.015);
		ax[i]->CenterTitle(true);
	}
	ax[1]->SetTitleOffset(-1.1);
	
    HistogramNegative(HH);
	
//  int DefaultCol=gStyle->GetHistLineColor();
    int colL=HH->GetLineColor();
// 	int colM=HH->GetMarkerColor();
    if(colL==602){
        HH->SetLineColor(gGlobalForeColor);
    }
    
	HH->SetStats(false);
	HH->SetTitle("");
	if(!(HH->InheritsFrom(TH2::Class()))){
		if(setminzero)HH->SetMinimum(0);
	}
}


TCanvas* DrawHformat(TH1* HH,bool setminzero){
	TCanvas* canv=preapre_canvas();
	canv->SetTitle(HH->GetTitle());
	hformat(HH,setminzero);
	draw_corrected_titles(HH);
	return canv;
}



TH1* ExtreemRebin(TH1* target,TH1* data){
    target->Reset();
	TAxis* tAx=target->GetXaxis();
	TAxis* dAx=data->GetXaxis();

	int j=1;
	for(int i=1;i<=data->GetNbinsX();++i){
		double dBinLower=dAx->GetBinLowEdge(i);
		double dBinUpper=dAx->GetBinUpEdge(i);
		
		double content=data->GetBinContent(i);
		vector<int> overlapedbins;
		
		while(tAx->GetBinLowEdge(j)<=dBinUpper){
			if(j>target->GetNbinsX())break;
			if(tAx->GetBinUpEdge(j)>=dBinLower)overlapedbins.push_back(j);
			if(tAx->GetBinUpEdge(j)<dBinUpper)j++;else break;
		}
		if(overlapedbins.size()==0)continue;
		
		vector<double> overlaparea;
		double overlapareatotal=0;
		
		for(unsigned int k=0;k<overlapedbins.size();++k){
			int bin=overlapedbins[k];
			double tBinLower=tAx->GetBinLowEdge(bin);
			double tBinUpper=tAx->GetBinUpEdge(bin);
			
			if(tBinLower<dBinLower)tBinLower=dBinLower;
			if(tBinUpper>dBinUpper)tBinUpper=dBinUpper;

			double binarea=tBinUpper-tBinLower;
			overlaparea.push_back(binarea);
			overlapareatotal+=binarea;
		}
		
		if(!(overlapareatotal>0))continue;
		
		for(unsigned int k=0;k<overlapedbins.size();++k){
			int bin=overlapedbins[k];
			double binC=content*overlaparea[k]/overlapareatotal;
			binC+=target->GetBinContent(bin);
			target->SetBinContent(bin,binC);
		}
	}
	
	// Fix the stats going to zero but lose any non-standard errors stored in original
	target->ResetStats();
    if(target->GetSumw2N())target->Sumw2(kFALSE);
    
	return target;
}


void ReMargin(TVirtualPad* pad){
	pad->SetMargin(0.15,0.04,0.15,0.04);
}

static unsigned int global_canvas_iterator=0;
TCanvas* preapre_canvas(unsigned int n,bool heightset,bool nobar){
	int dx=100;
	if(nobar)dx=-100;
	TCanvas *canv = new TCanvas(("AutoCan"+to_string(global_canvas_iterator)).c_str(), "AutoCan",dx,100,900,600);
	global_canvas_iterator++;
	canv->Divide(n);
	double tp=0.04/n;
	double bm=0.15/(n-1);
	
	double height=(1-tp-bm)/n;
	for(unsigned int i=0;i<n;i++){
		TVirtualPad* p=canv->cd(i+1);
		p->SetPad(0,0,1,1);
		p->SetFrameBorderMode(0);
		p->SetFillStyle(4000);
		p->SetFrameLineWidth(1);
		ReMargin(p);
		if(heightset){
			p->SetBottomMargin(bm+i*height);
			p->SetTopMargin(tp+(n-i-1)*height);
		}
	}
	return canv;
}

void draw_corrected_titles(TH1* hist){
	hist->GetXaxis()->SetTitleSize(0);
	hist->GetYaxis()->SetTitleSize(0);	
	
	DrawSharedTitle(hist->GetXaxis()->GetTitle());
	DrawSharedTitle(hist->GetYaxis()->GetTitle(),true);
}

TCanvas* preapre_canvas_bisect(){
	TCanvas *canv = preapre_canvas(2,true);
	canv->SetTitle("BisectCanvas");
// 	TVirtualPad* p=canv->cd(1);
// 	p->SetTopMargin(0.45);
// 	p=canv->cd(2);
// 	p->SetBottomMargin(0.55);
	return canv;
}

TCanvas* preapre_canvas_inset(){
	TCanvas *canv = preapre_canvas(2);
	canv->SetTitle("InsetCanvas");
	TVirtualPad* p=canv->cd(2);
	p->SetBottomMargin(0.55);
	p->SetTopMargin(0.07);
	p->SetRightMargin(0.07);
	p->SetLeftMargin(0.55);
	return canv;
}


TCanvas* draw_hist_inset(TH1* main,TH1* inset,int pixX,int pixY){
	main->SetMaximum(-1111);//Important if rebinned earlier. If setting manual, do after
	inset->SetMaximum(-1111);
	
	TCanvas *canv = preapre_canvas_inset();
	canv->SetTitle(main->GetTitle());
	hformat(main);hformat(inset);
	
	if(pixX>0&&pixY>0){
		canv->SetWindowSize(pixX,pixY);
	}
	
	TAxis* ax[2]={inset->GetXaxis(),inset->GetYaxis()};
	for(int i=0;i<2;i++){
		ax[i]->SetNdivisions(4,5,0);
		ax[i]->SetLabelSize(0.03);
		ax[i]->SetTitleSize(0.04);
		ax[i]->SetTitleOffset(0.5);
		ax[i]->SetTickLength(0.02);
	}
	
	canv->cd(1);main->Draw("hist");
	draw_corrected_titles(main);

	canv->cd(2);inset->Draw("hist");
	
	return canv;
}

TCanvas* draw_hist_bisect(TH1* bottom,TH1* top,int pixX,int pixY){
	bottom->SetMaximum(-1111);//Important if rebinned earlier. If setting manual, do after
	top->SetMaximum(-1111);
	
	TCanvas *canv = preapre_canvas_bisect();
	
	if(pixX>0&&pixY>0){
		canv->SetWindowSize(pixX,pixY);
	}
	
	canv->SetTitle(bottom->GetTitle());
	hformat(bottom);hformat(top);
	
	top->GetXaxis()->SetLabelSize(0);
	
	top->GetXaxis()->SetTitleSize(0);
	top->GetYaxis()->SetTitleSize(0);
	bottom->GetXaxis()->SetTitleSize(0);
	bottom->GetYaxis()->SetTitleSize(0);
	
	top->GetYaxis()->SetNdivisions(5,5,0);
	bottom->GetYaxis()->SetNdivisions(5,5,0);
	
	TPad* p=(TPad*)canv->cd(1);bottom->Draw("hist");
	
	//Whitebox covering top number
	AxisYWhiteBox();

	p=(TPad*)canv->cd(2);
	top->Draw("hist");
	draw_corrected_titles(top);
	TQObject::Connect(p, "RangeChanged()", 0, 0,"RangeChangeBisectCanvasBoth()");
	TQObject::Connect(canv, "ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", 0, 0,"PostUpdateCanvasUpdateCall(Int_t,Int_t,Int_t,TObject*)");
	
	return canv;	
}

void AxisYWhiteBox(TVirtualPad* p,double NDCY,double NDCX){
	TBox *box = new TBox();
	box->SetFillColor(0);
	p->cd();
	p->Update();//To load in the new coords properly
	box->DrawBox(p->PixeltoX(p->UtoPixel(0)),
	p->AbsPixeltoY(abs(p->VtoPixel(NDCY))),
	p->PixeltoX(p->UtoPixel(NDCX)),
	p->AbsPixeltoY(abs(p->VtoPixel(1))));
	delete box;
}

TCanvas* draw_electron_gamma(TH1* electron,TH1* gamma){
	axislabelkev(gamma);
	axislabelkev(electron);
	TCanvas *canv = draw_hist_bisect(electron,gamma);
	electron->SetMinimum((int)-1111);//undo the zero minimum set
	
	canv->cd(2);
	
	TLatex *latex= new TLatex();
	latex->SetTextSize(0.05);
	latex->SetTextFont(gGlobalMainFont);
	latex->SetTextAngle(0);
	latex->SetTextAlign(32);
	latex->DrawLatexNDC(0.93,0.9,"#gamma rays");
	latex->DrawLatexNDC(0.93,0.5,"Electrons");

	return canv;
	
	
}

//This function is added to sidestep interrupting update events
static bool PostUpdateCanvasUpdateCallbool=false;
void PostUpdateCanvasUpdateCall(Int_t event, Int_t x, Int_t y, TObject *selected){
	if(!gTQSender)return;
	if(PostUpdateCanvasUpdateCallbool&&((TObject*)gTQSender)->IsA() == TCanvas::Class()){
		PostUpdateCanvasUpdateCallbool=false;
		((TCanvas*)gTQSender)->Update();
	}
}


void RangeChangeBisectCanvasBoth(){
	cout<<endl<<"Pad 2->1 Range Change Start. "<<flush;

	//If gTQSender isnt a TObject pointer, this will crash
	if(!gTQSender)return;
	if (!(((TObject*)gTQSender)->IsA() == TPad::Class()))return;
	TPad* s=(TPad*)gTQSender;
	if(!(s->GetMother()->IsA() == TCanvas::Class()))return;
	TPad* p=(TPad*)s->GetMother()->cd(1);
	if(p==s)return;
	
	double l=1,u=-1;
	
	TH1* h=hist_capture(s);
	if(!h)return;
	HistDrawnXRange(h,l,u);//Use this rather than canvas GetRangeAxis/GetUxmin/GetUxmax because this fn is called mid-update and those dont work right
	
	cout<<l<<" "<<u;
	if(u<l)return;
	
	h=hist_capture(p);
	if(!h)return;
	h->GetXaxis()->SetRangeUser(l,u);
	
	double min=h->GetMaximum();
	double max=0;
	for(int i=h->GetXaxis()->GetFirst();i<=h->GetXaxis()->GetLast();i++){
		double y=h->GetBinContent(i);
		if(y<min)min=y;
		if(y>max)max=y;
	}
	h->SetMinimum(min);
	h->SetMaximum(min+(max-min)*1.2);

	cout<<" Range Change Finished."<<endl;
	
	//Because this function is called part way though a canvas update we cant force update of other canvas here
	p->Modified();
	PostUpdateCanvasUpdateCallbool=true;

	//We must change back to this canvas to allow the canvas update this function was called during to complete correctly
	s->cd();
}

void HistDrawnXRange(TH1* h,double &l,double &u){
	TAxis* a=h->GetXaxis();
	l=a->GetBinLowEdge(a->GetFirst());
	u=a->GetBinUpEdge(a->GetLast());
}


void AddPeakLabel(double E,bool exact,string text,TVirtualPad* pad,TH1* hist,TVirtualPad* pairpad){
	pad->cd();
	gPad->Update();//These lines seem to be quite important for range functions to work properly
	
	stringstream label;
	label<<" "<<E<<" "<<text;
	
	if(!hist)hist=hist_capture(pad);
	if(!hist)return;
	
	//Find y
	double y;
	if(exact)y=hist->GetBinContent(hist->GetXaxis()->FindBin(E));
	else y=FindLocalMax(hist,E);
	
	double yb=pad->GetUymin();
	double yt=pad->GetUymax();
	
	//Slight y offset
	double y5=0.05*(yt-yb);
	y+=y5;
	if(y>yt-y5)y=yt-y5;
	double yL=y+y5;
	double EL=E;
	
	//range of the drawn x-axis
	double xb=pad->GetUxmin();
	double xt=pad->GetUxmax();

// 	cout<<endl<<xb<<" "<<yb<<" "<<xt<<" "<<yt<<endl<<E<<" "<<y;	
	
	if(!(E>xb&&E<xt))return;
	
	if(pairpad){
		//convert to NDC and back
		PadNDCtoUser(E,y,pad,true);
		PadNDCtoUser(EL,yL,pad,true);
		PadNDCtoUser(E,y,pairpad);
		PadNDCtoUser(EL,yL,pairpad);
	}
	
	//By drawing in pad rather than NDC markers mover when x-axis changed
	//Also had all kinds of trouble with marker draw NDC
	
	TLatex* latex=new TLatex();
	latex->SetTextSize(0.045);
	latex->SetTextFont(gGlobalMainFont);
	latex->SetTextAlign(12);

	TMarker mark;
	mark.SetMarkerStyle(23);
	mark.DrawMarker(E,y);
	latex->DrawLatex(E,yL,label.str().c_str());
//TH1* backless SmoothOffBack(TH1*);	
}

void PadNDCtoUser(vector<double>& x,vector<double>& y,TVirtualPad* pad,bool reverse){
	double xy[4];
	pad->cd();gPad->Update();
	pad->GetRange(xy[0],xy[1],xy[2],xy[3]);

	for(unsigned int i=0;i<x.size()&&i<y.size();i++){
		PadNDCtoUser(x[i],y[i],xy,reverse);
	}
}

void PadNDCtoUser(double& x,double& y,TVirtualPad* pad,bool reverse){
	double xy[4];
	pad->cd();gPad->Update();
	pad->GetRange(xy[0],xy[1],xy[2],xy[3]);
	PadNDCtoUser(x,y,xy,reverse);
}

void PadNDCtoUser(double& x,double& y,double* xy,bool reverse){
	if(reverse){
			x=((x-xy[0])/(xy[2]-xy[0]));
			y=((y-xy[1])/(xy[3]-xy[1]));
	}else{
		x=(x*(xy[2]-xy[0]))+xy[0];
		y=(y*(xy[3]-xy[1]))+xy[1];
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TCanvas* DrawCopyCanvas(TH1* hist,bool HideErrors){
    return DrawCanvas(hist,HideErrors,true);
}

TCanvas* DrawCanvas(TH1* hist,bool HideErrors,bool copy){
	if(hist){
		TVirtualPad* hold=gPad;
		string name=hist->GetName();
		name+="DrawCan";
        if(copy){name+="Copy";}
		TCanvas* Can=new TCanvas(name.c_str());
		ReMargin(Can);
		Can->cd();
		DrawHistOpt(hist,HideErrors,copy);
		Can->Modified();
		Can->Update();
		gPad=hold;
		return Can;
	}
	return 0;
}

TCanvas* DrawCopyPeakClickerCanvas(TH1* hist,bool HideErrors){
	return DrawPeakClickerCanvas(hist,HideErrors,true);
}

TCanvas* DrawPeakClickerCanvas(TH1* hist,bool HideErrors,bool copy){
	TCanvas* Can=DrawCanvas(hist,HideErrors,copy);
    ConnectPeakClickerCanvas(Can);
	return Can;
}


TH1* DrawHistOpt(TH1* hist,bool HideErrors,bool Copy,bool Same){
	if(!hist)return 0;
    string opt="his";
    if(HideErrors)opt+="t";
    opt+="colz";
    if(Same)opt+="same";
    
    if(gGlobalNegativeDraw&&!Same)CanvasNegative();
    
    TH1* h=hist;
    if(Copy){//h->Draw("SAMEFUNC");
        h=hist->DrawCopy(opt.c_str());
        TObject *obj;TIter next(h->GetListOfFunctions());
        while ((obj = next()))((TF1*)obj)->DrawCopy("same");//Needed because of "Hist option turns off the functions"
    }else{
        hist->Draw(opt.c_str());
    }
    hformat(h,0);
    
	return h;	
}
	
TH1* DrawCopyHistOpt(TH1* hist,bool HideErrors){
	return DrawHistOpt(hist,HideErrors,true);
}

///////

TGraph* DrawGraphOpt(TGraph* graph,bool Copy,bool Same,bool Point){
	if(!graph)return 0;
    
    string opt="l";
    if(Point||graph->IsA()->InheritsFrom(TGraphErrors::Class())){
        opt="p";
    }else{
        graph->Sort();
    }
    if(Same)opt=opt+"same";
    else opt="a"+opt;
    
    if(gGlobalNegativeDraw){
        if(!Same)CanvasNegative();
    }
    if(graph->GetLineColor()==gGlobalBackColor)graph->SetLineColor(gGlobalForeColor);
    if(graph->GetMarkerColor()==gGlobalBackColor)graph->SetMarkerColor(gGlobalForeColor);
    
    gPad->Update();
    TGraph* g=graph;
    if(Copy){
        graph->Draw(opt.c_str());
    }else{
        g=(TGraph*)graph->DrawClone(opt.c_str());
    }
    
    if(!Same)hformat(g->GetHistogram(),false);
        
    return g;
}

TGraph* DrawCopyGraphOpt(TGraph* graph,bool point){
    return DrawGraphOpt(graph,true,false,point);
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Mostly stolen from TRootCanvas.cxx
static const char *HistSaveAsTypes[] = { "PDF",   "*.pdf",
					"ROOT files",   "*.root",
                                      "PNG",          "*.png",
                                      "ROOT macros",  "*.C",
                                      "All files",    "*",
                                      0,              0 };
TString HistSaveAs(TH1* hist, TGWindow *window,TPad* pad){
if(hist){
		//Save the stuff for the next loop;
		static TString dir(".");
		static Int_t typeidx = 2;
		static Bool_t overwr = kFALSE;
		
		TGFileInfo fi;//Root class for containing save/open file info
		
		//initialise fi			
		TString workdir = gSystem->WorkingDirectory();
		fi.fFileTypes   = HistSaveAsTypes;
		fi.fIniDir      = StrDup(dir);
		fi.fFileTypeIdx = typeidx;
		fi.fOverwrite = overwr;
		
		//This appears to halt the process until close
		new TGFileDialog(gClient->GetRoot(), window, kFDSave, &fi);
// 		new TGFileDialog(fClient->GetDefaultRoot(), this, kFDSave, &fi);

		gSystem->ChangeDirectory(workdir.Data());
		
		if (!fi.fFilename) return TString();
		
		TString fn = fi.fFilename;
		TString ft = fi.fFileTypes[fi.fFileTypeIdx+1];
		
		dir     = fi.fIniDir;
		typeidx = fi.fFileTypeIdx;
		overwr  = fi.fOverwrite;
		
		Bool_t  appendedType = kFALSE;
again:
		if (fn.EndsWith(".root") ||
			fn.EndsWith(".C") ){
			hist->SaveAs(fn);
		}else if(fn.EndsWith(".pdf") ||
			fn.EndsWith(".png") ){
            bool NegHold=gGlobalNegativeDraw;
            SetGlobalNegative(false);
			if(pad){
                CanvasNegativeFull(pad);
                pad->Update();
				pad->SaveAs(fn);
                SetGlobalNegative(NegHold);
                CanvasNegativeFull(pad);
			}else{
				TCanvas* fCan=DrawCopyCanvas(hist);
				fCan->Update();
				fCan->SaveAs(fn);
                SetGlobalNegative(NegHold);
                delete fCan;
			}
		}else {//check if the type has been added to string or nor
			if (!appendedType) {
			if (ft.Index(".") != kNPOS) {
				fn += ft(ft.Index("."), ft.Length());
				appendedType = kTRUE;
				goto again;//I didnt write this
			}
			}
			Warning("ProcessMessage", "file %s cannot be saved with this extension", fi.fFilename);
		}
		
		//Save the file type for the next loop;
		for (int i=1;HistSaveAsTypes[i];i+=2) {
			TString ftype = HistSaveAsTypes[i];
			ftype.ReplaceAll("*.", ".");
			if (fn.EndsWith(ftype.Data())) {
			typeidx = i-1;
			break;
			}
		}
		
		return fn;
	}
    return TString();
}

static const char *FileLoadTypes[] = {"ROOT files",   "*.root",
					"ROOT files",   "*.root",
                                      0,              0 };
				      
TFile* RootFileLoad(TGWindow *window){
		//Save the stuff for the next loop;
		static TString dir(".");
		static Int_t typeidx = 2;
		static Bool_t overwr = kFALSE;
		
		TGFileInfo fi;//Root class for containing save/open file info
		
		//initialise fi			
		TString workdir = gSystem->WorkingDirectory();
		fi.fFileTypes   = FileLoadTypes;
		fi.fIniDir      = StrDup(dir);
		fi.fFileTypeIdx = typeidx;
		fi.fOverwrite = overwr;
		
		//This appears to halt the process until close
		new TGFileDialog(gClient->GetRoot(), window, kFDOpen, &fi);
// 		new TGFileDialog(fClient->GetDefaultRoot(), this, kFDSave, &fi);

		gSystem->ChangeDirectory(workdir.Data());
		
		if(!fi.fFilename) return 0;
		
		TString fn = fi.fFilename;
		TString ft = fi.fFileTypes[fi.fFileTypeIdx+1];
		
		dir     = fi.fIniDir;
		typeidx = fi.fFileTypeIdx;
		overwr  = fi.fOverwrite;
		
		if(fn.EndsWith(".root")){
			gROOT->cd();
			TFile* infile=new TFile(fn,"READ");
			gROOT->cd();
			if(infile->IsOpen()){
				return infile;
			}
		}
		
		return 0;

}

//
// 
//


void CanvasNegativeFull(TVirtualPad* fPad){
    fPad->Modified();
    fPad->Update();
    
    TObjLink *lnk = fPad->GetListOfPrimitives()->FirstLink();
    while (lnk) {
        TObject *Ob=lnk->GetObject();
        if(Ob->InheritsFrom(TH1::Class())){
            HistogramNegative((TH1*)Ob);
        }
        if(Ob->InheritsFrom(TGraph::Class())){
            GraphNegative((TGraph*)Ob);
        }
        lnk = lnk->Next();
    }
    
    CanvasNegative(fPad);
    fPad->Modified();
    fPad->Update();
}

void CanvasNegative(TVirtualPad* fPad){
    
    fPad->SetFillColor(gGlobalBackColor);
    fPad->SetFrameLineColor(gGlobalForeColor);
    fPad->SetFrameFillColor(gGlobalBackColor);
    
    TObjLink *lnk = fPad->GetListOfPrimitives()->FirstLink();
    while (lnk) {
        TObject *Ob=lnk->GetObject();
        if(Ob->InheritsFrom(TFrame::Class())){
            ((TFrame*)Ob)->SetFillColor(gGlobalBackColor);
            ((TFrame*)Ob)->SetLineColor(gGlobalForeColor);
        }          
        lnk = lnk->Next();
    }
}
    
    
    
void HistogramNegative(TH1* Hist){
    TAxis* ax[3]={Hist->GetXaxis(),Hist->GetYaxis(),Hist->GetZaxis()};
	for(int i=0;i<3;i++){
		ax[i]->SetTitleColor(gGlobalForeColor);
		ax[i]->SetLabelColor(gGlobalForeColor);
		ax[i]->SetAxisColor(gGlobalForeColor);
	}

    if(Hist->GetLineColor()==gGlobalBackColor)Hist->SetLineColor(gGlobalForeColor);
    if(Hist->GetMarkerColor()==gGlobalBackColor)Hist->SetMarkerColor(gGlobalForeColor);
    
// 	Hist->SetFillColor(1);
}
    
    
void GraphNegative(TGraph* Graph){
    HistogramNegative(Graph->GetHistogram());
    
    if(Graph->GetLineColor()==gGlobalBackColor)Graph->SetLineColor(gGlobalForeColor);
    if(Graph->GetMarkerColor()==gGlobalBackColor)Graph->SetMarkerColor(gGlobalForeColor);
}


void SetGlobalNegative(bool negative){
    gGlobalNegativeDraw=negative;
    if(negative){
        gGlobalBackColor=kBlack;
        gGlobalForeColor=kWhite;
    }else{
        gGlobalBackColor=kWhite;
        gGlobalForeColor=kBlack;
    }
    
    
    gStyle->SetCanvasColor(gGlobalBackColor);
    gStyle->SetFrameFillColor(gGlobalBackColor);
    gStyle->SetTextColor(gGlobalForeColor);
    gStyle->SetMarkerColor(gGlobalForeColor);
    gStyle->SetLineColor(gGlobalForeColor);
    gStyle->SetFrameLineColor(gGlobalForeColor);
    gStyle->SetTitleTextColor(gGlobalForeColor);
    gStyle->SetHistLineColor(gGlobalForeColor);
    
    gStyle->SetFuncColor(2);
    
	Option_t*  ax[3]={"x","y","z"};
    for(int i=0;i<3;i++){
        gStyle->SetLabelColor(gGlobalForeColor,ax[i]);
        gStyle->SetTitleColor(gGlobalForeColor,ax[i]);
        gStyle->SetAxisColor(gGlobalForeColor,ax[i]);
    }

    //Changing gStyle alone is insufficient for histograms as any saved to disk aleardy have values set and will not take the defaults
}
