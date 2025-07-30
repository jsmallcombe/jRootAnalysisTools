{	
	TGMainFrame *toolbox= new TGMainFrame();
	TGTextButton *Button;
	Button = new TGTextButton(toolbox,"Arb. Angle Projection Tool");
	Button->Connect("Clicked()","jAngleAngel",0,"GlobalNewAngleAngel()");
	toolbox->AddFrame(Button);
	Button = new TGTextButton(toolbox,"Graphical Integrator");
	Button->Connect("Clicked()","jIntegrator",0,"GlobalNewIntegrator()");
	toolbox->AddFrame(Button);
	Button = new TGTextButton(toolbox,"Function Evaluator");
	Button->Connect("Clicked()","jEval",0,"GlobalNewEval()");	
	toolbox->AddFrame(Button);
	Button = new TGTextButton(toolbox,"Function Based Scaler");
	Button->Connect("Clicked()","jScale",0,"GlobalNewScale()");	
	toolbox->AddFrame(Button);
	Button = new TGTextButton(toolbox,"2D Gaussian Peak Fitter");
	Button->Connect("Clicked()","jFittingTool2D",0,"GlobalNew2DFittingTool()");	
	toolbox->AddFrame(Button);
	
	toolbox->MapSubwindows();
	toolbox->Resize(toolbox->GetDefaultSize());
	toolbox->MapWindow();
}


	

	
