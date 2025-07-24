{ 
	TGMainFrame *bob=new TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame);
	jGateSelectFrame *SelFrame =new jGateSelectFrame(bob,C,5);
	bob->AddFrame(SelFrame);
// 
// 	
	bob->MapSubwindows();
    bob->Resize(bob->GetDefaultSize());
    bob->MapWindow();
	
// 	TGMainFrame *bob=new jRootTreeCube("AlphaTuple.root");

	
    bob->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
}
