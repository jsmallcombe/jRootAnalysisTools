#include "james_filecustodian.h"
#include "james_elements.h"


jChiefCustodian* gChiefCustodian=new jChiefCustodian();

void jTFileCustodian::CloseFile(){
    if(File){
        cout<<"Last Custodian Deleted. Closing File "<<File->GetName()<<endl;
        delete File;
        File=0;
    }
}

void jTFileCustodian::AddObject(TObject* obj){
    Custodians.Add(obj);
}

bool jTFileCustodian::RemoveObject(TObject* obj){
    Custodians.Remove(obj);
    
    if(!Custodians.First()){
        CloseFile();
        if(IsOnHeap()&&SelfOwned){
            cout<<"jTFileCustodian deleting self "<<endl;
            delete this;
        }
        return true;
    }
    return false;
}

bool jTFileCustodian::CompareFile(TFile* f){
    return (f==File);
}

void jTFileCustodian::DisconnectSignals(void *obj){
    
    TObjLink *lnk = Custodians.FirstLink();
    while (lnk) {
        
        cout<<" disconnecting object "<<lnk->GetObject()<<endl;
         
        dynamic_cast<TQObject*>(lnk->GetObject())->Disconnect(0,obj,0);
        lnk = lnk->Next();
    }
}
    

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void jChiefCustodian::Add(TObject* obj,TFile* file){    
        TObject *listobj;
        jTFileCustodian* found=0;
        TIter next(&Custodians);
        
        while((listobj= next())){
            jTFileCustodian* cust=(jTFileCustodian*)listobj;
            if(cust->CompareFile(file)){
                found=cust;
                break;
            }
        }
        
        if(!found){
            found=new jTFileCustodian(file,0);
            Custodians.Add(found);
        }
        
        found->AddObject(obj);

        if(obj->InheritsFrom("TQObject")){
            //The dynamic cast is crucial here apparently 
            dynamic_cast<TQObject*>(obj)->Connect("Closed(TObject*)","jChiefCustodian", this,"ObjectDestroyed(TObject*)");
            //TQObject::Connect(dynamic_cast<TQObject*>(obj),"Closed(TObject*)","jChiefCustodian", this,"ObjectDestroyed(TObject*)");
            
            // This would link all of the class, which would work without error.
            // I could actually make the class link for all allowed classes at initilisation
            // But I would rather keep this class general
            // TQObject::Connect(obj->ClassName(),"Closed(TObject*)","jChiefCustodian", this,"ObjectDestroyed(TObject*)");
        }
}
    
void jChiefCustodian::ObjectDestroyed(){
            cout<<"gTQSender "<<gTQSender<<endl;
}
    
void jChiefCustodian::ObjectDestroyed(TObject* destobj){   
    TObjLink *lnk = Custodians.FirstLink();
    while (lnk) {
        jTFileCustodian* cust=(jTFileCustodian*)lnk->GetObject();
        bool FileClosed = cust->RemoveObject(destobj);
        lnk = lnk->Next();
        if(FileClosed){
            Custodians.Remove(cust);
            delete cust; //not needed as set to self delete;
        }
    }
    
}

void jChiefCustodian::DisconnectSignals(){  
    
    TObjLink *lnk = Custodians.FirstLink();
    while (lnk) {
        jTFileCustodian* cust=(jTFileCustodian*)lnk->GetObject();
        cout<<" disconnecting jChiefCustodian "<<this<<" From jTFileCustodian "<<cust<<" objects"<<endl;
        cust->DisconnectSignals(this);
        lnk = lnk->Next();
    }
}     
        
        
        
        
