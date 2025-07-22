#include "j_gating_subtraction_frame.h"

ClassImp(jGateSubtractionFrame);

//______________________________________________________________________________

jGateSubtractionFrame::jGateSubtractionFrame() : jGateSelectFrame(){}

jGateSubtractionFrame::jGateSubtractionFrame(TGWindow * parent, TH1* input,int ThreeDee) : 
		jGateSelectFrame(parent, input,ThreeDee)
		{}
		
void jGateSubtractionFrame::SetRangeAxis(TAxis* ax,int lower,int upper){
	if(ax){//Check for nullptr, such as if GetZaxis() called on TH2
		if(lower>upper){
			if(upper==0) upper=ax->GetNbins();  	 // We pass upper=0 for "end of range"
			else 		 upper=ax->GetNbins()+1;    //  and any other value "include overflow" e.g. -1
		} 
		ax->SetRange(lower,upper);
	}
}
// 	TAxis::SetRange(), defaults to 0,0 which sents excluding OverUnderFlow, but ONLY if BOTH are zero

void jGateSubtractionFrame::ResetRanges(TH1* hist,bool OverUnderFlow) {
	SetRangeAxis(hist->GetXaxis(),!OverUnderFlow,-1*OverUnderFlow);
	SetRangeAxis(hist->GetYaxis(),!OverUnderFlow,-1*OverUnderFlow);
	SetRangeAxis(hist->GetZaxis(),!OverUnderFlow,-1*OverUnderFlow);
}

// All ranges are reset by the master GateAxisByBin, so only gating range needs setting 
TH1* jGateSubtractionFrame::GateByBin(TH3* in,int xyz,int lower,int upper,TString name){
	TString is[6]={"x","y","z","yz","zx","xy"};
	//Note "xz" not "zx" was used previously, so there will be some orientation differences

	switch (xyz%3) { 
		case 0: SetRangeAxis(in->GetXaxis(),lower,upper);  break;
		case 1: SetRangeAxis(in->GetYaxis(),lower,upper);  break;
		default: SetRangeAxis(in->GetZaxis(),lower,upper);  break;
	}
	TH1* ret=in->Project3D(is[xyz%6]);
	if(name!="")ret->SetName(name);
	return ret;
}
 //NOTE 1: The generated histogram is named th3name + option

// // ProjectionX/Y/Z are not in TH1 only TH2/TH3
// // Project3D is only in TH3, but can also function as ProjectionX/Y/Z
	
TH1* jGateSubtractionFrame::GateByBin(TH2* in,int xyz,int lower,int upper,TString name){
	if(xyz%2==1){
		SetRangeAxis(in->GetYaxis(),lower,upper);
		return (TH1*)in->ProjectionX(name);
	}
	
	SetRangeAxis(in->GetXaxis(),lower,upper);
	return (TH1*)in->ProjectionY(name,lower,upper);
}

///////
TH1* jGateSubtractionFrame::GateAxisByBin(TH1* in,int xyz,int lower,int upper,TString name){
	ResetRanges(in,false); //Change to "true" for ranges to include under/overflows
	if(in->IsA()->InheritsFrom(TH3::Class()))return GateAxisByBin((TH3*)in,xyz,lower,upper,name);
	if(in->IsA()->InheritsFrom(TH2::Class()))return GateAxisByBin((TH2*)in,xyz,lower,upper,name);
	return 0;
}

//
// Projection functions
//

TH1* jGateSubtractionFrame::ProjectAxisByBin(TH1* input,int xyz,string name){
	return GateAxisByBin(input,xyz+3,1,0,name); //exclude underoverflow
// 	return GateAxisByBin(input,xyz+3,0,-1,name);  //include underoverflow
}



//
//subtraction functions
//

TH1* jGateSubtractionFrame::scaled_back_subtract(TH1* gate,TH1* back ,double backfrack,double uncertainfrac,bool scale){
	TH1* pass=(TH1*)gate->Clone();
	return scaled_back_subtract(gate,back ,backfrack,pass,uncertainfrac,scale);
}

TH1* jGateSubtractionFrame::scaled_back_subtract(TH1* gate,TH1* back ,double backfrack,TH1* pass,double uncertainfrac,bool scale){
    
    if(scale){
        double backcount=back->Integral();
        double forecount=gate->Integral();
        backfrack*=forecount/backcount;
    }
	
	if(!back->GetSumw2N())back->Sumw2();
	if(!gate->GetSumw2N())gate->Sumw2();
	
	pass->Add(gate,back,1.0,-backfrack);
	
	if(uncertainfrac){static_cast< TH1ErrorErrorAdj* > (pass)->AdjustError(back,backfrack*uncertainfrac);}
	return pass;
}



//Doing it this way allows direct access to BinErrorSq so saves on wasteful squaring and rooting
void TH1ErrorErrorAdj::AdjustError(const TH1* back,double frac){
    if (!back || back->GetNcells() != fNcells) {
        Error("AdjustError", "Incompatible histogram bin structure");
        return;
    }
	
	if(!fSumw2.fN)Sumw2();
	double v;
	for (Int_t bin = 0; bin < fNcells; ++bin) {
		v=back->GetBinContent(bin);
		fSumw2.fArray[bin] += v*v*frac*frac;
	}
}
// NOTE: This relies on fSumw2 being protected in TH1 (ROOT). If ROOT changes this to private, this will break.


