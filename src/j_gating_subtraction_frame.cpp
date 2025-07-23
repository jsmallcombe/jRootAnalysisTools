#include "j_gating_subtraction_frame.h"

ClassImp(jGateSubtractionFrame);

//______________________________________________________________________________

jGateSubtractionFrame::jGateSubtractionFrame() : jGateSelectFrame(){}

jGateSubtractionFrame::jGateSubtractionFrame(TGWindow * parent,int ThreeDee) : 
		jGateSelectFrame(parent, nullptr,ThreeDee),IterSuffix(Iterator(""))
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
	TString is[6]={"yz","zx","xy","x","y","z"};
	//Note "xz" not "zx" was used previously, so there will be some orientation differences

	switch (xyz%3) { 
		case 0: SetRangeAxis(in->GetXaxis(),lower,upper);  break;
		case 1: SetRangeAxis(in->GetYaxis(),lower,upper);  break;
		default: SetRangeAxis(in->GetZaxis(),lower,upper);  break;
	}
	
	TString Opt=is[xyz%6];
// 	if(name.Length())Opt=name+"_"+Opt;
// // Officially Project3D supports adding extra name portion
// // Had problems combining this with filling-existing-histograms-by-name functionality
// // Ended up with some overwrites that should have been possible resulting in deletions and segfaults
// // This work around works	
	TString Holdname=in->GetName();
	in->SetName(name);
	TH1* ret=in->Project3D(Opt);
	in->SetName(Holdname);
	
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
	if(in->IsA()->InheritsFrom(TH3::Class()))return GateByBin((TH3*)in,xyz,lower,upper,name);
	if(in->IsA()->InheritsFrom(TH2::Class()))return GateByBin((TH2*)in,xyz,lower,upper,name);
	return 0;
}

//
// Projection functions
//

TH1* jGateSubtractionFrame::ProjectAxisByBin(TH1* input,int xyz,TString name){
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


double jGateSubtractionFrame::ScaledBackgroundSubtract(TH1* gate,TH1* back ,double backfrack,double uncertainfrac){
	 
	double backcount=back->Integral();
	double forecount=gate->Integral();
	backfrack*=forecount/backcount;
	
	if(!back->GetSumw2N())back->Sumw2();
	if(!gate->GetSumw2N())gate->Sumw2();
	
	gate->Add(back,-backfrack);
	
	if(uncertainfrac>0){static_cast< TH1ErrorErrorAdj* > (gate)->AdjustError(back,backfrack*uncertainfrac);}
	
	return backfrack;
}

///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

void jGateSubtractionFrame::UpdateInput(TH1*&fInput, TH1*&fResFullProj){
    
	fResFullProj=GateAxisByBin(fInput,xyz,1,-1,"ResFullProj"+IterSuffix);
	fResFullProj->SetStats(0);	
	fResFullProj->SetTitle("");
	
	TH1* proj=ProjectAxisByBin(fInput,xyz,"proj"+IterSuffix);
    jGateSelectFrame::UpdateInput(proj);// call base class version
	delete proj; //Cloned inside jGateSelectFrame::UpdateInput()
}
    

 
double jGateSubtractionFrame::DoGateSubtract(TH1*&fInput, TH1*&fResult, TH1*&fBack, TH1*&fResFullProj){
        
//     // Testing the name-based histogram recycling functions as intended
// 	cout<<endl;
//     if(fResFullProj)cout<<" "<<fResFullProj->GetName()<<" ";
// 	if(fBack)cout<<fBack->GetName()<<" ";
// 	if(fResult)cout<<fResult->GetName()<<" ";
//     cout<<endl<<" "<<fResFullProj<<" "<<fBack<<" "<<fResult<<" ";
    
	// GateAxisByBin *should* nicely fill the histogram matching the name if the TH1 exists
	// so we dont need to delete pointers except for when changing axis, handled by UpdateInput
	fResult=GateAxisByBin(fInput,xyz,GetGateBinDown(),GetGateBinUp(),"Gated"+IterSuffix);
    fResult->SetLineColor(1);
    fResult->GetXaxis()->SetTitleOffset(1.0);//Fixed a problem from other lib with Yaxis title
	fResult->SetTitle("");

    // Note the projection "fResFullProj" used to make "full" and "anti" background options
    // include the overflow bins, but excludes the underflow bin.
    // This is an intentional choice, as often intentionally zeroed data may be sorted into the underflow bin
    // The underflow bin can be selected with manual sliders

    TH1* fBackTidy=fBack;
	switch (GetBackMode()) {
		case 1://full
                fBack=fResFullProj;
			break;
		case 2://compton
                fBack=GateAxisByBin(fInput,xyz,GetBackBinDown(),-1,"Back"+IterSuffix);
			break;
		case 3://anti gate
			{
				fBack=(TH1*)fResFullProj->Clone(TString(fResFullProj->GetName()).ReplaceAll("ResFullProj", "Back"));
				fBack->Add(fResult,-1);
				fBack->Sumw2(kFALSE);//Important as the Add is *not* an arithmetic subtraction, but an exact data removal
			}
			break;
		case 4://none
			{
                fBack=fResult;
			}
			break;
		default:  //manual 
			{
				fBack=GateAxisByBin(fInput,xyz,GetBackBinDown(),GetBackBinUp(),"Back"+IterSuffix);
                if(GetGateBinDown()>GetBackBinDown()&&GetGateBinUp()<GetBackBinUp()){
                    fBack->Add(fResult,-1);//In special case remove the gated part
                    fBack->Sumw2(kFALSE);
                }				
			}
			break;
	}
	
	double fBackFrac=1;
	if(fResult!=fBack)fBackFrac=ScaledBackgroundSubtract(fResult,fBack,GetBackFrac(),GetBackFracFrac());
    
    
//    The method GateAxisByBin, used for fResult, and for the backgrounds Compton & manual
//    will reuse the exiting histogram in memory, the other options do not.
//    So we catch those and delete the abandoned fBack histgram
    if(fBackTidy&&fBack!=fBackTidy){
        if(fBackTidy!=fResult&&fBackTidy!=fResFullProj) delete fBackTidy;
    }
    
    // Testing the name-based histogram recycling functions as intended
//     cout<<endl<<" "<<fResFullProj<<" "<<fBack<<" "<<fResult<<" ";
//     cout<<endl<<" "<<fResFullProj->GetName()<<" "<<fBack->GetName()<<" "<<fResult->GetName()<<endl;

    return fBackFrac;
}


///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////



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


