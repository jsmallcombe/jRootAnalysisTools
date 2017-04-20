#include "james_gate_subtract.h"

TAxis* hist_gater(TH3F* in,string& pro,int xyz){
	switch (xyz) { 
		case 0: pro="yz"; return in->GetXaxis();  break;
		case 1: pro="xz"; return in->GetYaxis();  break;
		default: pro="xy"; return in->GetZaxis();  break;
	}
}

TAxis* hist_proj(TH3F* in,string& pro,int xyz){
	switch (xyz) { 
		case 0: pro="x"; return in->GetXaxis();  break;
		case 1: pro="y"; return in->GetYaxis();  break;
		default: pro="z"; return in->GetZaxis();  break;
	}
}

	//	
	// 3D gating functions
	//

TH2F* hist_gater(double lower,double upper,TH3F* in,int xyz,string name){
	string is;TAxis *ax=hist_gater(in,is,xyz); TH3axisreseter(in);
	ax->SetRangeUser(lower,upper);
	TH2F* ret=(TH2F*)in->Project3D(is.c_str());
	if(name!="")ret->SetName(name.c_str());
	return ret;
}

TH2F* hist_gater_bin(int lower,int upper,TH3F* in,int xyz,string name){
	string is;TAxis *ax=hist_gater(in,is,xyz); TH3axisreseter(in);
	ax->SetRange(lower,upper);
	TH2F* ret=(TH2F*)in->Project3D(is.c_str());
	if(name!="")ret->SetName(name.c_str());
	return ret;
}

TH2F* hist_gater(double lower,TH3F* in,int xyz,string name){
	string is;TAxis *ax=hist_gater(in,is,xyz); TH3axisreseter(in);
	ax->SetRange(ax->FindFixBin(lower),ax->GetNbins()+1);
	TH2F* ret=(TH2F*)in->Project3D(is.c_str());
	if(name!="")ret->SetName(name.c_str());
	return ret;
}

TH2F* hist_gater_bin(int lower,TH3F* in,int xyz,string name){
	string is;TAxis *ax=hist_gater(in,is,xyz); TH3axisreseter(in);
	ax->SetRange(lower,ax->GetNbins()+1);
	TH2F* ret=(TH2F*)in->Project3D(is.c_str());
	if(name!="")ret->SetName(name.c_str());
	return ret;
}


TH2F* hist_gater_anti(double lower,double upper,TH3F* in,int xyz,string name){
	string is;TAxis *ax=hist_gater(in,is,xyz); TH3axisreseter(in);

	ax->SetRange(ax->FindFixBin(upper)+1,ax->GetNbins()+1);
	TH2F* temp=(TH2F*)in->Project3D(is.c_str());
	temp->SetName("thistemphist");
	ax->SetRange(1,ax->FindFixBin(lower)+1);
	TH2F* ret=(TH2F*)in->Project3D(is.c_str());
	if(name!="")ret->SetName(name.c_str());
	ret->Add(temp);delete temp;return ret;
}

TH2F* hist_gater_anti_bin(int lower,int upper,TH3F* in,int xyz,string name){
	string is;TAxis *ax=hist_gater(in,is,xyz); TH3axisreseter(in);
	
	ax->SetRange(upper+1,ax->GetNbins()+1);
	TH2F* temp=(TH2F*)in->Project3D(is.c_str());
	temp->SetName("thistemphist");
	ax->SetRange(1,lower-1);
	TH2F* ret=(TH2F*)in->Project3D(is.c_str());
	if(name!="")ret->SetName(name.c_str());
	ret->Add(temp);delete temp;return ret;
}
 //NOTE 1: The generated histogram is named th3name + option


	//
	//2D gating functions
	//
	
TH1F* hist_gater(double lower,double upper,TH2F* in,int xyz,string name){
	if(xyz==1) return (TH1F*)in->ProjectionX(name.c_str(),in->GetYaxis()->FindFixBin(lower),in->GetYaxis()->FindFixBin(upper));
	else  return (TH1F*)in->ProjectionY(name.c_str(),in->GetXaxis()->FindFixBin(lower),in->GetXaxis()->FindFixBin(upper));
}
TH1F* hist_gater_bin(int lower,int upper,TH2F* in,int xyz,string name){
	if(xyz==1) return (TH1F*)in->ProjectionX(name.c_str(),lower,upper);
	else  return (TH1F*)in->ProjectionY(name.c_str(),lower,upper);
}
TH1F* hist_gater(double lower,TH2F* in,int xyz,string name){
	if(xyz==1) return (TH1F*)in->ProjectionX(name.c_str(),in->GetYaxis()->FindFixBin(lower),in->GetYaxis()->GetNbins()+1);
	else  return (TH1F*)in->ProjectionY(name.c_str(),in->GetXaxis()->FindFixBin(lower),in->GetXaxis()->GetNbins()+1);
}
TH1F* hist_gater_bin(int lower,TH2F* in,int xyz,string name){
	if(xyz==1) return (TH1F*)in->ProjectionX(name.c_str(),lower,in->GetYaxis()->GetNbins()+1);
	else  return (TH1F*)in->ProjectionY(name.c_str(),lower,in->GetXaxis()->GetNbins()+1);
}
TH1F* hist_gater_anti(double lower,double upper,TH2F* in,int xyz,string name){
	if(xyz==1){
		TH1F* temp=(TH1F*)in->ProjectionX("temporaryadditionhistogram",in->GetYaxis()->FindFixBin(upper)+1,in->GetYaxis()->GetNbins()+1);		
		TH1F* ret=(TH1F*)in->ProjectionX(name.c_str(),1,in->GetYaxis()->FindFixBin(lower)-1);
		ret->Add(temp);delete temp;return ret;		
	} else {
		TH1F* temp=(TH1F*)in->ProjectionY("temporaryadditionhistogram",in->GetXaxis()->FindFixBin(upper)+1,in->GetXaxis()->GetNbins()+1);		
		TH1F* ret=(TH1F*)in->ProjectionY(name.c_str(),1,in->GetXaxis()->FindFixBin(lower)-1);
		ret->Add(temp);delete temp;return ret;		
	}
}

TH1F* hist_gater_anti_bin(int lower,int upper,TH2F* in,int xyz,string name){
	if(xyz==1){
		TH1F* temp=(TH1F*)in->ProjectionX("temporaryadditionhistogram",upper+1,in->GetYaxis()->GetNbins()+1);		
		TH1F* ret=(TH1F*)in->ProjectionX(name.c_str(),1,lower-1);
		ret->Add(temp);delete temp;return ret;		
	} else {
		TH1F* temp=(TH1F*)in->ProjectionY("temporaryadditionhistogram",upper+1,in->GetXaxis()->GetNbins()+1);		
		TH1F* ret=(TH1F*)in->ProjectionY(name.c_str(),1,lower-1);
		ret->Add(temp);delete temp;return ret;		
	}
}


	//
	// Projection functions
	//

TH1F* hist_proj(TH3F* in,int xyz,string name){
	switch (xyz) { 
		case 0: return (TH1F*)in->ProjectionX(name.c_str());  break;
		case 1: return (TH1F*)in->ProjectionY(name.c_str());  break;
		default: return (TH1F*)in->ProjectionZ(name.c_str());  break;
	}
}

TH1F* hist_proj(TH2F* in,int xyz,string name){
	if(xyz==0)return (TH1F*)in->ProjectionX(name.c_str());
	else return (TH1F*)in->ProjectionY(name.c_str());
}

TH1F* hist_proj_flowless(TH3F* in,int xyz,string name){
	switch (xyz) { 
		case 0: return (TH1F*)in->ProjectionX(name.c_str(),1,in->GetYaxis()->GetNbins(),1,in->GetZaxis()->GetNbins());  break;
		case 1: return (TH1F*)in->ProjectionY(name.c_str(),1,in->GetXaxis()->GetNbins(),1,in->GetZaxis()->GetNbins());  break;
		default: return (TH1F*)in->ProjectionZ(name.c_str(),1,in->GetXaxis()->GetNbins(),1,in->GetYaxis()->GetNbins());  break;
	}
}

TH1F* hist_proj_flowless(TH2F* in,int xyz,string name){
	if(xyz==0)return (TH1F*)in->ProjectionX(name.c_str(),1,in->GetYaxis()->GetNbins());
	else return (TH1F*)in->ProjectionY(name.c_str(),1,in->GetXaxis()->GetNbins());
}

	//
	//subtraction functions
	//
TH1* scaled_back_subtract(TH1* gate,TH1* back ,double backfrack,double uncertainfrac){
	TH1* pass=(TH1*)gate->Clone();
	return scaled_back_subtract(gate,back ,backfrack,pass,uncertainfrac);
}

TH1* scaled_back_subtract(TH1* gate,TH1* back ,double backfrack,TH1* pass,double uncertainfrac){
	double backcount=back->Integral();
	double forecount=gate->Integral();
	
	if(!back->GetSumw2N())back->Sumw2();
	if(!gate->GetSumw2N())gate->Sumw2();
	
	double subtraction=-(backfrack*forecount)/backcount;
	pass->Add(gate,back,1.0,subtraction);
	
	if(uncertainfrac>0){static_cast< TH1ErrorAdj* > (pass)->AdjustError(back,subtraction*uncertainfrac);}
	return pass;
}

//Doing it this way allows direct access to BinErrorSq so saves on wasteful squaring and rooting
void TH1ErrorAdj::AdjustError(const TH1* back,double frac){
	if(!fSumw2.fN)Sumw2();
	double v;
	for (Int_t bin = 0; bin < fNcells; ++bin) {
		v=back->GetBinContent(bin);
		fSumw2.fArray[bin] += v*v*frac*frac;
	}
}


void TH3axisreseter(TH3* hist){
	hist->GetXaxis()->SetRange();
	hist->GetYaxis()->SetRange();
	hist->GetZaxis()->SetRange();
}


