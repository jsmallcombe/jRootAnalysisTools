{ 
//    j_gating_select_frame_tester* bob=new j_gating_select_frame_tester(sili);
    
    
    
    TGMainFrame *bob=new TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame);
    TH1* h=(TH1*)sili;
    j_gating_result_frame *ResFrame =new j_gating_result_frame(bob,&h,&h,&h,false);
    bob->AddFrame(ResFrame,new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0));
    bob->MapSubwindows();
    bob->Resize(bob->GetDefaultSize());
    bob->MapWindow();
    
    
    
    bob->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");

}
