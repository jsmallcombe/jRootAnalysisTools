#include "james_effpeaks.h"

double radeffscadef[7]={7.01,0.1465,6.98145,-0.0424513,0.0151779,3.25807,1};

TF1* rad_eff_scaled(TGraphErrors * graph){
	radeffscadef[6]=TMath::MaxElement(graph->GetN(),graph->GetY())/0.140001;	
	TF1* first=new TF1("rad_eff",scaleradeff,1,3000,7);
	first->SetParameters(radeffscadef);
	first->FixParameter(5,radeffscadef[5]);
	first->FixParameter(6,radeffscadef[6]);
	return first;
}

TF1* rad_eff(){
	TF1* first=new TF1("rad_eff",radeff,1,3000,6);
	first->SetParameters(radeffscadef);
	return first;
}

TF1* auto_radeff_scaled(TGraphErrors * graph,bool byparts){
	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(50000);
	TF1* first;
	if(byparts) first=radeff_by_parts(graph,true);
	else first=rad_eff_scaled(graph);
		
	graph->Fit(first,"QN");

	TF1* second=new TF1("rad_eff",scaleradeff,1,3000,7);
	second->SetParameters(first->GetParameters());
	second->SetParLimits(5,-1,100);
	second->FixParameter(6,first->GetParameter(6));
	
	graph->Fit(second,"NQ");
	graph->Fit(second,"NMQ");
	for(int i=0;i<5;i++){
		double p=second->GetParameter(i);
		double dp=abs(p)*0.001;
		second->SetParLimits(i,p-dp,p+dp);
	}
	// Extra finesse here because the minimum and phase space if so complex/fragile
	// Even computer rounding errors from different scaling seem to by unstable
	// This current configuration seems to lead to stable results
	// Successful fits for "E" option, with pos-def error matrix 
	
/////////second->FixParameter(5,second->GetParameter(5));
	//Fixes most problems but ruins gives untrue certainty in error bands
	
	delete first;
	return second;
}	

TF1* radeff_by_parts(TGraphErrors * graph,bool scale){
	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(10000);
	
	double lowR=0,maxY=TMath::MaxElement(graph->GetN(),graph->GetY());
	bool fix_par1=true;
	for(int i=0;i<graph->GetN();i++){
		double x,y;
		graph->GetPoint(i,x,y);
		if(y>maxY*0.9){
			lowR=x;
			if(i>3)fix_par1=false;
		}
	}
	
	TF1* high;
	if(scale)high=rad_eff_scaled(graph);
	else high=rad_eff();
	high->SetRange(lowR,3000);
	high->FixParameter(0,0);
	high->FixParameter(1,0);
	high->FixParameter(5,radeffscadef[5]);	
	graph->Fit(high,"QRN");	
	
	TF1* low;
	if(scale)low=rad_eff_scaled(graph);
	else low=rad_eff();
	low->SetRange(1,lowR);
	low->FixParameter(2,0);
	low->FixParameter(3,0);	
	low->FixParameter(4,0);	
	low->FixParameter(5,radeffscadef[5]);	
	graph->Fit(low,"QRN");
	
	low->FixParameter(2,high->GetParameter(2));
	low->FixParameter(3,high->GetParameter(3));
	low->FixParameter(4,high->GetParameter(4));
	low->FixParameter(1,low->GetParameter(1));
	low->FixParameter(0,low->GetParameter(0));
	low->ReleaseParameter(5);
	low->SetParLimits(5,-1,100);
	low->SetRange(1,lowR*2);
	graph->Fit(low,"QN");
	
	TF1* scaled;
	if(scale)scaled=rad_eff_scaled(graph);
	else scaled=rad_eff();	
	scaled->SetParameters(low->GetParameters());
	scaled->FixParameter(5,low->GetParameter(5));
	graph->Fit(scaled,"QN");
	
	scaled->ReleaseParameter(5);
	scaled->SetParLimits(5,-1,100);
	if(fix_par1)scaled->FixParameter(1,scaled->GetParameter(1));
	graph->Fit(scaled,"QN");
	
	delete low;
	delete high;
	return scaled;
}

TF1* prepare_stefeff(TGraphErrors * graph){
	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(10000);

	TF1 *newer=new TF1("stefeff",stefeff,10,3000,4);
	newer->SetParameters(-0.14,0.052,-2308,0.1);
	graph->Fit(newer,"QNR");
	return newer;
}
