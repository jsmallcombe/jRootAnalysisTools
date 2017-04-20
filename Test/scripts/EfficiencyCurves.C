{
Double_t _fx1001[21] = {
   188.618,
   192.098,
   268.659,
   393.94,
   491.381,
   592.302,
   714.103,
   926.385,
   1016.87,
   1110.83,
   1232.63,
   1260.47,
   1361.39,
   1448.39,
   1556.27,
   219.938,
   233.858,
   717.583,
   1211.75,
   1591.07,
   1918.19};
   Double_t _fy1001[21] = {
   0.00202931,
   0.00303882,
   0.137305,
   0.109038,
   0.098943,
   0.0898574,
   0.084305,
   0.0732003,
   0.0711813,
   0.0681527,
   0.0656289,
   0.0631051,
   0.0605813,
   0.0595718,
   0.0575528,
   0.0414005,
   0.0484671,
   0.0792574,
   0.0636099,
   0.055029,
   0.0504862};
   Double_t _fex1001[21] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t _fey1001[21] = {
   0.01,
   0.01,
   0.0142531,
   0.00345075,
   0.00317103,
   0.002925,
   0.00337979,
   0.00231395,
   0.00225204,
   0.00215603,
   0.00205628,
   0.00198648,
   0.00190641,
   0.00187686,
   0.00179339,
   0.01,
   0.01,
   0.00268264,
   0.00215128,
   0.0020166,
   0.00170236};
   TGraphErrors *gre = new TGraphErrors(21,_fx1001,_fy1001,_fex1001,_fey1001);
	
   gre->Draw("AP");

   
//    	TF1 high("high",radeff,300,2000,6);
// 	high.FixParameter(0,0);
// 	high.FixParameter(1,0);
// 	high.FixParameter(5,20);
// 	
// 	gre->Fit(&high,"+r");
// 	
//     	TF1 low("low",radeff,0,300,6);
// 	low.FixParameter(2,0);
// 	low.FixParameter(3,0);
// 	low.FixParameter(4,0);
// 	low.FixParameter(5,20); 
// 	gre->Fit(&low,"+r"); 
//    
// 	
//     	TF1 all("all",radeff,0,2000,6);
// 	all.FixParameter(0,low.GetParameter(1));
// 	all.SetParameter(1,low.GetParameter(0));
// 	all.FixParameter(2,high.GetParameter(2));
// 	all.FixParameter(3,high.GetParameter(3));
// 	all.FixParameter(4,high.GetParameter(4));
// 	all.SetParameter(5,20); 
// 	gre->Fit(&all,"+"); 
// 	
// 	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(10000);
//     	TF1 allB("allB",radeff,0,2000,6);
// 	allB.SetParameters(all.GetParameters());
// 	allB.FixParameter(5,all.GetParameter(5)); 
// 	gre->Fit(&allB,"+"); 
	
   TF1* A;
	A=rad_eff_scaled(gre);
	A->SetLineColor(1);
	A->Draw("same");
	A=auto_radeff_scaled(gre);
	A->SetLineColor(2);
	A->Draw("same");
	(gre)->Draw("same");
	A=radeff_by_parts(gre,true);
	A->SetLineColor(3);
	A->Draw("same");
	A=radeff_by_parts(gre,false);
	A->SetLineColor(4);
	A->Draw("same");
	A=prepare_stefeff(gre);
	A->SetLineColor(5);
	A->Draw("same");

}