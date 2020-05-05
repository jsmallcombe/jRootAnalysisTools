{ 
// 	TGMainFrame *bob=new TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame);
// 	j_gating_select_frame *SelFrame =new j_gating_select_frame(bob,C);
// 	bob->AddFrame(SelFrame);
// 
// 	
// 	bob->MapSubwindows();
//     bob->Resize(bob->GetDefaultSize());
//     bob->MapWindow();
	
	TGMainFrame *bob=new jRootTreeCube("AlphaTuple.root");

	
    bob->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
}
