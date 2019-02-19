//
//
//	James Root Library
//	An object for using the QT functionality to manage TFiles
//	16 Feb 2019
//	james.smallcombe@outlook.com
//
//

#ifndef jamesfile_custodian
#define jamesfile_custodian

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <TObject.h>
#include <TQObject.h>
#include <TROOT.h>
#include <TFile.h>
#include <RQ_OBJECT.h>

using namespace std;


class jTFileCustodian : public TObject {
    // Should always be created on heap and left to self delete
    
   RQ_OBJECT("jTFileCustodian")
   // not inherited from TQObject, allows class to use signal/slot communication
   // Could also just add TQObject to public inheritance ...
    
private:
    TList Custodians;
    TFile* File;
    bool SelfOwned;

    void CloseFile();
    
public:
	jTFileCustodian(TFile* f=0,bool b=0):TObject(),File(f),SelfOwned(b){}
	virtual ~jTFileCustodian(){
        Custodians.Clear("nodelete");
        CloseFile();
    }
    
    void AddObject(TObject* obj);
    bool RemoveObject(TObject* obj);
    bool CompareFile(TFile* f);
    
    void DisconnectSignals(void*);
    
	ClassDef(jTFileCustodian, 2)
};



class jChiefCustodian : public TObject, public TQObject  {

private:
    TList Custodians;
    void DisconnectSignals();
    
public:
    jChiefCustodian():TObject(),TQObject(){
        Custodians.IsOwner();
    }
	virtual ~jChiefCustodian(){
        if(Custodians.First()){
            cout<<endl<<"ERROR ChiefCustodian Closed while files in use"<<endl;
        }
        DisconnectSignals();
    }
    
    void Add(TObject* obj,TFile* file);
    void ObjectDestroyed();
    void ObjectDestroyed(TObject*);

	ClassDef(jChiefCustodian, 1)
};

extern jChiefCustodian* gChiefCustodian;


#endif
