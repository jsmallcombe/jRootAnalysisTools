// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME bindIDictOutput
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "include/j_clipboard_parse.h"
#include "include/j_effpeaks.h"
#include "include/j_elements.h"
#include "include/j_env.h"
#include "include/j_extra_guitools.h"
#include "include/j_fitholder.h"
#include "include/j_fitting.h"
#include "include/j_gate_subtract.h"
#include "include/j_gating_frame.h"
#include "include/j_gating_result_frame.h"
#include "include/j_gating_select_frame.h"
#include "include/j_gating_tool.h"
#include "include/j_gpad_tools.h"
#include "include/j_hist_formatting.h"
#include "include/j_new_gating_tool.h"
#include "include/j_spectool.h"
#include "include/j_treetup_tool.h"
#include "include/j_ultrafit_env.h"
#include "include/j_ultrapeakfit.h"
#include "include/j_ultrapeak.h"
#include "include/j_utility.h"
#include "include/j_X11paste.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static TClass *TransientBitsClasslElonggR_Dictionary();
   static void TransientBitsClasslElonggR_TClassManip(TClass*);
   static void *new_TransientBitsClasslElonggR(void *p = nullptr);
   static void *newArray_TransientBitsClasslElonggR(Long_t size, void *p);
   static void delete_TransientBitsClasslElonggR(void *p);
   static void deleteArray_TransientBitsClasslElonggR(void *p);
   static void destruct_TransientBitsClasslElonggR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TransientBitsClass<long>*)
   {
      ::TransientBitsClass<long> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TransientBitsClass<long>));
      static ::ROOT::TGenericClassInfo 
         instance("TransientBitsClass<long>", "j_utility.h", 124,
                  typeid(::TransientBitsClass<long>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TransientBitsClasslElonggR_Dictionary, isa_proxy, 4,
                  sizeof(::TransientBitsClass<long>) );
      instance.SetNew(&new_TransientBitsClasslElonggR);
      instance.SetNewArray(&newArray_TransientBitsClasslElonggR);
      instance.SetDelete(&delete_TransientBitsClasslElonggR);
      instance.SetDeleteArray(&deleteArray_TransientBitsClasslElonggR);
      instance.SetDestructor(&destruct_TransientBitsClasslElonggR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TransientBitsClass<long>*)
   {
      return GenerateInitInstanceLocal(static_cast<::TransientBitsClass<long>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TransientBitsClass<long>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TransientBitsClasslElonggR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::TransientBitsClass<long>*>(nullptr))->GetClass();
      TransientBitsClasslElonggR_TClassManip(theClass);
   return theClass;
   }

   static void TransientBitsClasslElonggR_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/j_utility.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_TH1Efficiency(void *p = nullptr);
   static void *newArray_TH1Efficiency(Long_t size, void *p);
   static void delete_TH1Efficiency(void *p);
   static void deleteArray_TH1Efficiency(void *p);
   static void destruct_TH1Efficiency(void *p);
   static void directoryAutoAdd_TH1Efficiency(void *obj, TDirectory *dir);
   static Long64_t merge_TH1Efficiency(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TH1Efficiency*)
   {
      ::TH1Efficiency *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TH1Efficiency >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TH1Efficiency", ::TH1Efficiency::Class_Version(), "j_utility.h", 199,
                  typeid(::TH1Efficiency), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TH1Efficiency::Dictionary, isa_proxy, 4,
                  sizeof(::TH1Efficiency) );
      instance.SetNew(&new_TH1Efficiency);
      instance.SetNewArray(&newArray_TH1Efficiency);
      instance.SetDelete(&delete_TH1Efficiency);
      instance.SetDeleteArray(&deleteArray_TH1Efficiency);
      instance.SetDestructor(&destruct_TH1Efficiency);
      instance.SetDirectoryAutoAdd(&directoryAutoAdd_TH1Efficiency);
      instance.SetMerge(&merge_TH1Efficiency);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TH1Efficiency*)
   {
      return GenerateInitInstanceLocal(static_cast<::TH1Efficiency*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TH1Efficiency*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TH2Efficiency(void *p = nullptr);
   static void *newArray_TH2Efficiency(Long_t size, void *p);
   static void delete_TH2Efficiency(void *p);
   static void deleteArray_TH2Efficiency(void *p);
   static void destruct_TH2Efficiency(void *p);
   static void directoryAutoAdd_TH2Efficiency(void *obj, TDirectory *dir);
   static Long64_t merge_TH2Efficiency(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TH2Efficiency*)
   {
      ::TH2Efficiency *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TH2Efficiency >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TH2Efficiency", ::TH2Efficiency::Class_Version(), "j_utility.h", 282,
                  typeid(::TH2Efficiency), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TH2Efficiency::Dictionary, isa_proxy, 4,
                  sizeof(::TH2Efficiency) );
      instance.SetNew(&new_TH2Efficiency);
      instance.SetNewArray(&newArray_TH2Efficiency);
      instance.SetDelete(&delete_TH2Efficiency);
      instance.SetDeleteArray(&deleteArray_TH2Efficiency);
      instance.SetDestructor(&destruct_TH2Efficiency);
      instance.SetDirectoryAutoAdd(&directoryAutoAdd_TH2Efficiency);
      instance.SetMerge(&merge_TH2Efficiency);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TH2Efficiency*)
   {
      return GenerateInitInstanceLocal(static_cast<::TH2Efficiency*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TH2Efficiency*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_jRootMultiPurposePopup(void *p = nullptr);
   static void *newArray_jRootMultiPurposePopup(Long_t size, void *p);
   static void delete_jRootMultiPurposePopup(void *p);
   static void deleteArray_jRootMultiPurposePopup(void *p);
   static void destruct_jRootMultiPurposePopup(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jRootMultiPurposePopup*)
   {
      ::jRootMultiPurposePopup *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jRootMultiPurposePopup >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("jRootMultiPurposePopup", ::jRootMultiPurposePopup::Class_Version(), "j_utility.h", 400,
                  typeid(::jRootMultiPurposePopup), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jRootMultiPurposePopup::Dictionary, isa_proxy, 4,
                  sizeof(::jRootMultiPurposePopup) );
      instance.SetNew(&new_jRootMultiPurposePopup);
      instance.SetNewArray(&newArray_jRootMultiPurposePopup);
      instance.SetDelete(&delete_jRootMultiPurposePopup);
      instance.SetDeleteArray(&deleteArray_jRootMultiPurposePopup);
      instance.SetDestructor(&destruct_jRootMultiPurposePopup);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jRootMultiPurposePopup*)
   {
      return GenerateInitInstanceLocal(static_cast<::jRootMultiPurposePopup*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::jRootMultiPurposePopup*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FullFitHolder(void *p = nullptr);
   static void *newArray_FullFitHolder(Long_t size, void *p);
   static void delete_FullFitHolder(void *p);
   static void deleteArray_FullFitHolder(void *p);
   static void destruct_FullFitHolder(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FullFitHolder*)
   {
      ::FullFitHolder *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FullFitHolder >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("FullFitHolder", ::FullFitHolder::Class_Version(), "j_fitholder.h", 42,
                  typeid(::FullFitHolder), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FullFitHolder::Dictionary, isa_proxy, 4,
                  sizeof(::FullFitHolder) );
      instance.SetNew(&new_FullFitHolder);
      instance.SetNewArray(&newArray_FullFitHolder);
      instance.SetDelete(&delete_FullFitHolder);
      instance.SetDeleteArray(&deleteArray_FullFitHolder);
      instance.SetDestructor(&destruct_FullFitHolder);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FullFitHolder*)
   {
      return GenerateInitInstanceLocal(static_cast<::FullFitHolder*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::FullFitHolder*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *jPeakDat_Dictionary();
   static void jPeakDat_TClassManip(TClass*);
   static void delete_jPeakDat(void *p);
   static void deleteArray_jPeakDat(void *p);
   static void destruct_jPeakDat(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jPeakDat*)
   {
      ::jPeakDat *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::jPeakDat));
      static ::ROOT::TGenericClassInfo 
         instance("jPeakDat", "j_fitting.h", 76,
                  typeid(::jPeakDat), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &jPeakDat_Dictionary, isa_proxy, 4,
                  sizeof(::jPeakDat) );
      instance.SetDelete(&delete_jPeakDat);
      instance.SetDeleteArray(&deleteArray_jPeakDat);
      instance.SetDestructor(&destruct_jPeakDat);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jPeakDat*)
   {
      return GenerateInitInstanceLocal(static_cast<::jPeakDat*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::jPeakDat*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *jPeakDat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::jPeakDat*>(nullptr))->GetClass();
      jPeakDat_TClassManip(theClass);
   return theClass;
   }

   static void jPeakDat_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/j_fitting.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *HistClickStop_Dictionary();
   static void HistClickStop_TClassManip(TClass*);
   static void *new_HistClickStop(void *p = nullptr);
   static void *newArray_HistClickStop(Long_t size, void *p);
   static void delete_HistClickStop(void *p);
   static void deleteArray_HistClickStop(void *p);
   static void destruct_HistClickStop(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HistClickStop*)
   {
      ::HistClickStop *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::HistClickStop));
      static ::ROOT::TGenericClassInfo 
         instance("HistClickStop", "j_gpad_tools.h", 77,
                  typeid(::HistClickStop), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &HistClickStop_Dictionary, isa_proxy, 4,
                  sizeof(::HistClickStop) );
      instance.SetNew(&new_HistClickStop);
      instance.SetNewArray(&newArray_HistClickStop);
      instance.SetDelete(&delete_HistClickStop);
      instance.SetDeleteArray(&deleteArray_HistClickStop);
      instance.SetDestructor(&destruct_HistClickStop);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HistClickStop*)
   {
      return GenerateInitInstanceLocal(static_cast<::HistClickStop*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::HistClickStop*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *HistClickStop_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::HistClickStop*>(nullptr))->GetClass();
      HistClickStop_TClassManip(theClass);
   return theClass;
   }

   static void HistClickStop_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/j_gpad_tools.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_jhistquestion(void *p = nullptr);
   static void *newArray_jhistquestion(Long_t size, void *p);
   static void delete_jhistquestion(void *p);
   static void deleteArray_jhistquestion(void *p);
   static void destruct_jhistquestion(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jhistquestion*)
   {
      ::jhistquestion *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jhistquestion >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("jhistquestion", ::jhistquestion::Class_Version(), "j_gpad_tools.h", 126,
                  typeid(::jhistquestion), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jhistquestion::Dictionary, isa_proxy, 4,
                  sizeof(::jhistquestion) );
      instance.SetNew(&new_jhistquestion);
      instance.SetNewArray(&newArray_jhistquestion);
      instance.SetDelete(&delete_jhistquestion);
      instance.SetDeleteArray(&deleteArray_jhistquestion);
      instance.SetDestructor(&destruct_jhistquestion);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jhistquestion*)
   {
      return GenerateInitInstanceLocal(static_cast<::jhistquestion*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::jhistquestion*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TH1ErrorAdj(void *p = nullptr);
   static void *newArray_TH1ErrorAdj(Long_t size, void *p);
   static void delete_TH1ErrorAdj(void *p);
   static void deleteArray_TH1ErrorAdj(void *p);
   static void destruct_TH1ErrorAdj(void *p);
   static void directoryAutoAdd_TH1ErrorAdj(void *obj, TDirectory *dir);
   static Long64_t merge_TH1ErrorAdj(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TH1ErrorAdj*)
   {
      ::TH1ErrorAdj *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TH1ErrorAdj >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TH1ErrorAdj", ::TH1ErrorAdj::Class_Version(), "j_gate_subtract.h", 78,
                  typeid(::TH1ErrorAdj), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TH1ErrorAdj::Dictionary, isa_proxy, 4,
                  sizeof(::TH1ErrorAdj) );
      instance.SetNew(&new_TH1ErrorAdj);
      instance.SetNewArray(&newArray_TH1ErrorAdj);
      instance.SetDelete(&delete_TH1ErrorAdj);
      instance.SetDeleteArray(&deleteArray_TH1ErrorAdj);
      instance.SetDestructor(&destruct_TH1ErrorAdj);
      instance.SetDirectoryAutoAdd(&directoryAutoAdd_TH1ErrorAdj);
      instance.SetMerge(&merge_TH1ErrorAdj);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TH1ErrorAdj*)
   {
      return GenerateInitInstanceLocal(static_cast<::TH1ErrorAdj*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TH1ErrorAdj*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CCframe(void *p = nullptr);
   static void *newArray_CCframe(Long_t size, void *p);
   static void delete_CCframe(void *p);
   static void deleteArray_CCframe(void *p);
   static void destruct_CCframe(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CCframe*)
   {
      ::CCframe *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CCframe >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("CCframe", ::CCframe::Class_Version(), "j_elements.h", 46,
                  typeid(::CCframe), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::CCframe::Dictionary, isa_proxy, 4,
                  sizeof(::CCframe) );
      instance.SetNew(&new_CCframe);
      instance.SetNewArray(&newArray_CCframe);
      instance.SetDelete(&delete_CCframe);
      instance.SetDeleteArray(&deleteArray_CCframe);
      instance.SetDestructor(&destruct_CCframe);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CCframe*)
   {
      return GenerateInitInstanceLocal(static_cast<::CCframe*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::CCframe*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_jHistCapButton(void *p = nullptr);
   static void *newArray_jHistCapButton(Long_t size, void *p);
   static void delete_jHistCapButton(void *p);
   static void deleteArray_jHistCapButton(void *p);
   static void destruct_jHistCapButton(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jHistCapButton*)
   {
      ::jHistCapButton *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jHistCapButton >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("jHistCapButton", ::jHistCapButton::Class_Version(), "j_elements.h", 87,
                  typeid(::jHistCapButton), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jHistCapButton::Dictionary, isa_proxy, 4,
                  sizeof(::jHistCapButton) );
      instance.SetNew(&new_jHistCapButton);
      instance.SetNewArray(&newArray_jHistCapButton);
      instance.SetDelete(&delete_jHistCapButton);
      instance.SetDeleteArray(&deleteArray_jHistCapButton);
      instance.SetDestructor(&destruct_jHistCapButton);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jHistCapButton*)
   {
      return GenerateInitInstanceLocal(static_cast<::jHistCapButton*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::jHistCapButton*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_jAddSubTool(void *p);
   static void deleteArray_jAddSubTool(void *p);
   static void destruct_jAddSubTool(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jAddSubTool*)
   {
      ::jAddSubTool *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jAddSubTool >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("jAddSubTool", ::jAddSubTool::Class_Version(), "j_elements.h", 116,
                  typeid(::jAddSubTool), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jAddSubTool::Dictionary, isa_proxy, 4,
                  sizeof(::jAddSubTool) );
      instance.SetDelete(&delete_jAddSubTool);
      instance.SetDeleteArray(&deleteArray_jAddSubTool);
      instance.SetDestructor(&destruct_jAddSubTool);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jAddSubTool*)
   {
      return GenerateInitInstanceLocal(static_cast<::jAddSubTool*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::jAddSubTool*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_jDirList(void *p);
   static void deleteArray_jDirList(void *p);
   static void destruct_jDirList(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jDirList*)
   {
      ::jDirList *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jDirList >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("jDirList", ::jDirList::Class_Version(), "j_elements.h", 160,
                  typeid(::jDirList), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jDirList::Dictionary, isa_proxy, 4,
                  sizeof(::jDirList) );
      instance.SetDelete(&delete_jDirList);
      instance.SetDeleteArray(&deleteArray_jDirList);
      instance.SetDestructor(&destruct_jDirList);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jDirList*)
   {
      return GenerateInitInstanceLocal(static_cast<::jDirList*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::jDirList*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Ultrapeak(void *p = nullptr);
   static void *newArray_Ultrapeak(Long_t size, void *p);
   static void delete_Ultrapeak(void *p);
   static void deleteArray_Ultrapeak(void *p);
   static void destruct_Ultrapeak(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Ultrapeak*)
   {
      ::Ultrapeak *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Ultrapeak >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("Ultrapeak", ::Ultrapeak::Class_Version(), "j_ultrapeak.h", 107,
                  typeid(::Ultrapeak), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Ultrapeak::Dictionary, isa_proxy, 4,
                  sizeof(::Ultrapeak) );
      instance.SetNew(&new_Ultrapeak);
      instance.SetNewArray(&newArray_Ultrapeak);
      instance.SetDelete(&delete_Ultrapeak);
      instance.SetDeleteArray(&deleteArray_Ultrapeak);
      instance.SetDestructor(&destruct_Ultrapeak);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Ultrapeak*)
   {
      return GenerateInitInstanceLocal(static_cast<::Ultrapeak*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::Ultrapeak*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *UltrapeakArea_Dictionary();
   static void UltrapeakArea_TClassManip(TClass*);
   static void *new_UltrapeakArea(void *p = nullptr);
   static void *newArray_UltrapeakArea(Long_t size, void *p);
   static void delete_UltrapeakArea(void *p);
   static void deleteArray_UltrapeakArea(void *p);
   static void destruct_UltrapeakArea(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::UltrapeakArea*)
   {
      ::UltrapeakArea *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::UltrapeakArea));
      static ::ROOT::TGenericClassInfo 
         instance("UltrapeakArea", "j_ultrapeak.h", 456,
                  typeid(::UltrapeakArea), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &UltrapeakArea_Dictionary, isa_proxy, 4,
                  sizeof(::UltrapeakArea) );
      instance.SetNew(&new_UltrapeakArea);
      instance.SetNewArray(&newArray_UltrapeakArea);
      instance.SetDelete(&delete_UltrapeakArea);
      instance.SetDeleteArray(&deleteArray_UltrapeakArea);
      instance.SetDestructor(&destruct_UltrapeakArea);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::UltrapeakArea*)
   {
      return GenerateInitInstanceLocal(static_cast<::UltrapeakArea*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::UltrapeakArea*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *UltrapeakArea_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::UltrapeakArea*>(nullptr))->GetClass();
      UltrapeakArea_TClassManip(theClass);
   return theClass;
   }

   static void UltrapeakArea_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/j_ultrapeak.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *UltrapeakFrac_Dictionary();
   static void UltrapeakFrac_TClassManip(TClass*);
   static void *new_UltrapeakFrac(void *p = nullptr);
   static void *newArray_UltrapeakFrac(Long_t size, void *p);
   static void delete_UltrapeakFrac(void *p);
   static void deleteArray_UltrapeakFrac(void *p);
   static void destruct_UltrapeakFrac(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::UltrapeakFrac*)
   {
      ::UltrapeakFrac *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::UltrapeakFrac));
      static ::ROOT::TGenericClassInfo 
         instance("UltrapeakFrac", "j_ultrapeak.h", 502,
                  typeid(::UltrapeakFrac), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &UltrapeakFrac_Dictionary, isa_proxy, 4,
                  sizeof(::UltrapeakFrac) );
      instance.SetNew(&new_UltrapeakFrac);
      instance.SetNewArray(&newArray_UltrapeakFrac);
      instance.SetDelete(&delete_UltrapeakFrac);
      instance.SetDeleteArray(&deleteArray_UltrapeakFrac);
      instance.SetDestructor(&destruct_UltrapeakFrac);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::UltrapeakFrac*)
   {
      return GenerateInitInstanceLocal(static_cast<::UltrapeakFrac*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::UltrapeakFrac*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *UltrapeakFrac_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::UltrapeakFrac*>(nullptr))->GetClass();
      UltrapeakFrac_TClassManip(theClass);
   return theClass;
   }

   static void UltrapeakFrac_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/j_ultrapeak.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *UltrapeakCentroid_Dictionary();
   static void UltrapeakCentroid_TClassManip(TClass*);
   static void *new_UltrapeakCentroid(void *p = nullptr);
   static void *newArray_UltrapeakCentroid(Long_t size, void *p);
   static void delete_UltrapeakCentroid(void *p);
   static void deleteArray_UltrapeakCentroid(void *p);
   static void destruct_UltrapeakCentroid(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::UltrapeakCentroid*)
   {
      ::UltrapeakCentroid *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::UltrapeakCentroid));
      static ::ROOT::TGenericClassInfo 
         instance("UltrapeakCentroid", "j_ultrapeak.h", 533,
                  typeid(::UltrapeakCentroid), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &UltrapeakCentroid_Dictionary, isa_proxy, 4,
                  sizeof(::UltrapeakCentroid) );
      instance.SetNew(&new_UltrapeakCentroid);
      instance.SetNewArray(&newArray_UltrapeakCentroid);
      instance.SetDelete(&delete_UltrapeakCentroid);
      instance.SetDeleteArray(&deleteArray_UltrapeakCentroid);
      instance.SetDestructor(&destruct_UltrapeakCentroid);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::UltrapeakCentroid*)
   {
      return GenerateInitInstanceLocal(static_cast<::UltrapeakCentroid*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::UltrapeakCentroid*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *UltrapeakCentroid_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::UltrapeakCentroid*>(nullptr))->GetClass();
      UltrapeakCentroid_TClassManip(theClass);
   return theClass;
   }

   static void UltrapeakCentroid_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/j_ultrapeak.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_UltraFitEnv(void *p = nullptr);
   static void *newArray_UltraFitEnv(Long_t size, void *p);
   static void delete_UltraFitEnv(void *p);
   static void deleteArray_UltraFitEnv(void *p);
   static void destruct_UltraFitEnv(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::UltraFitEnv*)
   {
      ::UltraFitEnv *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::UltraFitEnv >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("UltraFitEnv", ::UltraFitEnv::Class_Version(), "j_ultrafit_env.h", 75,
                  typeid(::UltraFitEnv), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::UltraFitEnv::Dictionary, isa_proxy, 4,
                  sizeof(::UltraFitEnv) );
      instance.SetNew(&new_UltraFitEnv);
      instance.SetNewArray(&newArray_UltraFitEnv);
      instance.SetDelete(&delete_UltraFitEnv);
      instance.SetDeleteArray(&deleteArray_UltraFitEnv);
      instance.SetDestructor(&destruct_UltraFitEnv);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::UltraFitEnv*)
   {
      return GenerateInitInstanceLocal(static_cast<::UltraFitEnv*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::UltraFitEnv*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_j_gating_frame(void *p = nullptr);
   static void *newArray_j_gating_frame(Long_t size, void *p);
   static void delete_j_gating_frame(void *p);
   static void deleteArray_j_gating_frame(void *p);
   static void destruct_j_gating_frame(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::j_gating_frame*)
   {
      ::j_gating_frame *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::j_gating_frame >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("j_gating_frame", ::j_gating_frame::Class_Version(), "j_gating_frame.h", 62,
                  typeid(::j_gating_frame), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::j_gating_frame::Dictionary, isa_proxy, 4,
                  sizeof(::j_gating_frame) );
      instance.SetNew(&new_j_gating_frame);
      instance.SetNewArray(&newArray_j_gating_frame);
      instance.SetDelete(&delete_j_gating_frame);
      instance.SetDeleteArray(&deleteArray_j_gating_frame);
      instance.SetDestructor(&destruct_j_gating_frame);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::j_gating_frame*)
   {
      return GenerateInitInstanceLocal(static_cast<::j_gating_frame*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::j_gating_frame*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_jgating_tool(void *p = nullptr);
   static void *newArray_jgating_tool(Long_t size, void *p);
   static void delete_jgating_tool(void *p);
   static void deleteArray_jgating_tool(void *p);
   static void destruct_jgating_tool(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jgating_tool*)
   {
      ::jgating_tool *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jgating_tool >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("jgating_tool", ::jgating_tool::Class_Version(), "j_gating_tool.h", 50,
                  typeid(::jgating_tool), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jgating_tool::Dictionary, isa_proxy, 4,
                  sizeof(::jgating_tool) );
      instance.SetNew(&new_jgating_tool);
      instance.SetNewArray(&newArray_jgating_tool);
      instance.SetDelete(&delete_jgating_tool);
      instance.SetDeleteArray(&deleteArray_jgating_tool);
      instance.SetDestructor(&destruct_jgating_tool);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jgating_tool*)
   {
      return GenerateInitInstanceLocal(static_cast<::jgating_tool*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::jgating_tool*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_minimalist_th3slice(void *p = nullptr);
   static void *newArray_minimalist_th3slice(Long_t size, void *p);
   static void delete_minimalist_th3slice(void *p);
   static void deleteArray_minimalist_th3slice(void *p);
   static void destruct_minimalist_th3slice(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::minimalist_th3slice*)
   {
      ::minimalist_th3slice *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::minimalist_th3slice >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("minimalist_th3slice", ::minimalist_th3slice::Class_Version(), "j_gating_tool.h", 137,
                  typeid(::minimalist_th3slice), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::minimalist_th3slice::Dictionary, isa_proxy, 4,
                  sizeof(::minimalist_th3slice) );
      instance.SetNew(&new_minimalist_th3slice);
      instance.SetNewArray(&newArray_minimalist_th3slice);
      instance.SetDelete(&delete_minimalist_th3slice);
      instance.SetDeleteArray(&deleteArray_minimalist_th3slice);
      instance.SetDestructor(&destruct_minimalist_th3slice);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::minimalist_th3slice*)
   {
      return GenerateInitInstanceLocal(static_cast<::minimalist_th3slice*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::minimalist_th3slice*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_jSpecTool(void *p = nullptr);
   static void *newArray_jSpecTool(Long_t size, void *p);
   static void delete_jSpecTool(void *p);
   static void deleteArray_jSpecTool(void *p);
   static void destruct_jSpecTool(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jSpecTool*)
   {
      ::jSpecTool *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jSpecTool >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("jSpecTool", ::jSpecTool::Class_Version(), "j_spectool.h", 42,
                  typeid(::jSpecTool), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jSpecTool::Dictionary, isa_proxy, 4,
                  sizeof(::jSpecTool) );
      instance.SetNew(&new_jSpecTool);
      instance.SetNewArray(&newArray_jSpecTool);
      instance.SetDelete(&delete_jSpecTool);
      instance.SetDeleteArray(&deleteArray_jSpecTool);
      instance.SetDestructor(&destruct_jSpecTool);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jSpecTool*)
   {
      return GenerateInitInstanceLocal(static_cast<::jSpecTool*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::jSpecTool*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_jEnv(void *p = nullptr);
   static void *newArray_jEnv(Long_t size, void *p);
   static void delete_jEnv(void *p);
   static void deleteArray_jEnv(void *p);
   static void destruct_jEnv(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jEnv*)
   {
      ::jEnv *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jEnv >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("jEnv", ::jEnv::Class_Version(), "j_env.h", 51,
                  typeid(::jEnv), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jEnv::Dictionary, isa_proxy, 4,
                  sizeof(::jEnv) );
      instance.SetNew(&new_jEnv);
      instance.SetNewArray(&newArray_jEnv);
      instance.SetDelete(&delete_jEnv);
      instance.SetDeleteArray(&deleteArray_jEnv);
      instance.SetDestructor(&destruct_jEnv);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jEnv*)
   {
      return GenerateInitInstanceLocal(static_cast<::jEnv*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::jEnv*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_jScale(void *p = nullptr);
   static void *newArray_jScale(Long_t size, void *p);
   static void delete_jScale(void *p);
   static void deleteArray_jScale(void *p);
   static void destruct_jScale(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jScale*)
   {
      ::jScale *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jScale >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("jScale", ::jScale::Class_Version(), "j_extra_guitools.h", 52,
                  typeid(::jScale), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jScale::Dictionary, isa_proxy, 4,
                  sizeof(::jScale) );
      instance.SetNew(&new_jScale);
      instance.SetNewArray(&newArray_jScale);
      instance.SetDelete(&delete_jScale);
      instance.SetDeleteArray(&deleteArray_jScale);
      instance.SetDestructor(&destruct_jScale);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jScale*)
   {
      return GenerateInitInstanceLocal(static_cast<::jScale*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::jScale*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_jEval(void *p = nullptr);
   static void *newArray_jEval(Long_t size, void *p);
   static void delete_jEval(void *p);
   static void deleteArray_jEval(void *p);
   static void destruct_jEval(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jEval*)
   {
      ::jEval *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jEval >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("jEval", ::jEval::Class_Version(), "j_extra_guitools.h", 74,
                  typeid(::jEval), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jEval::Dictionary, isa_proxy, 4,
                  sizeof(::jEval) );
      instance.SetNew(&new_jEval);
      instance.SetNewArray(&newArray_jEval);
      instance.SetDelete(&delete_jEval);
      instance.SetDeleteArray(&deleteArray_jEval);
      instance.SetDestructor(&destruct_jEval);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jEval*)
   {
      return GenerateInitInstanceLocal(static_cast<::jEval*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::jEval*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_jAngleAngel(void *p = nullptr);
   static void *newArray_jAngleAngel(Long_t size, void *p);
   static void delete_jAngleAngel(void *p);
   static void deleteArray_jAngleAngel(void *p);
   static void destruct_jAngleAngel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jAngleAngel*)
   {
      ::jAngleAngel *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jAngleAngel >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("jAngleAngel", ::jAngleAngel::Class_Version(), "j_extra_guitools.h", 98,
                  typeid(::jAngleAngel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jAngleAngel::Dictionary, isa_proxy, 4,
                  sizeof(::jAngleAngel) );
      instance.SetNew(&new_jAngleAngel);
      instance.SetNewArray(&newArray_jAngleAngel);
      instance.SetDelete(&delete_jAngleAngel);
      instance.SetDeleteArray(&deleteArray_jAngleAngel);
      instance.SetDestructor(&destruct_jAngleAngel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jAngleAngel*)
   {
      return GenerateInitInstanceLocal(static_cast<::jAngleAngel*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::jAngleAngel*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_j2DPeakFit(void *p = nullptr);
   static void *newArray_j2DPeakFit(Long_t size, void *p);
   static void delete_j2DPeakFit(void *p);
   static void deleteArray_j2DPeakFit(void *p);
   static void destruct_j2DPeakFit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::j2DPeakFit*)
   {
      ::j2DPeakFit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::j2DPeakFit >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("j2DPeakFit", ::j2DPeakFit::Class_Version(), "j_extra_guitools.h", 151,
                  typeid(::j2DPeakFit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::j2DPeakFit::Dictionary, isa_proxy, 4,
                  sizeof(::j2DPeakFit) );
      instance.SetNew(&new_j2DPeakFit);
      instance.SetNewArray(&newArray_j2DPeakFit);
      instance.SetDelete(&delete_j2DPeakFit);
      instance.SetDeleteArray(&deleteArray_j2DPeakFit);
      instance.SetDestructor(&destruct_j2DPeakFit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::j2DPeakFit*)
   {
      return GenerateInitInstanceLocal(static_cast<::j2DPeakFit*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::j2DPeakFit*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_jIntegrator(void *p = nullptr);
   static void *newArray_jIntegrator(Long_t size, void *p);
   static void delete_jIntegrator(void *p);
   static void deleteArray_jIntegrator(void *p);
   static void destruct_jIntegrator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jIntegrator*)
   {
      ::jIntegrator *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jIntegrator >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("jIntegrator", ::jIntegrator::Class_Version(), "j_extra_guitools.h", 181,
                  typeid(::jIntegrator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jIntegrator::Dictionary, isa_proxy, 4,
                  sizeof(::jIntegrator) );
      instance.SetNew(&new_jIntegrator);
      instance.SetNewArray(&newArray_jIntegrator);
      instance.SetDelete(&delete_jIntegrator);
      instance.SetDeleteArray(&deleteArray_jIntegrator);
      instance.SetDestructor(&destruct_jIntegrator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jIntegrator*)
   {
      return GenerateInitInstanceLocal(static_cast<::jIntegrator*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::jIntegrator*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_jCompCanvas(void *p = nullptr);
   static void *newArray_jCompCanvas(Long_t size, void *p);
   static void delete_jCompCanvas(void *p);
   static void deleteArray_jCompCanvas(void *p);
   static void destruct_jCompCanvas(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jCompCanvas*)
   {
      ::jCompCanvas *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jCompCanvas >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("jCompCanvas", ::jCompCanvas::Class_Version(), "j_extra_guitools.h", 200,
                  typeid(::jCompCanvas), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jCompCanvas::Dictionary, isa_proxy, 4,
                  sizeof(::jCompCanvas) );
      instance.SetNew(&new_jCompCanvas);
      instance.SetNewArray(&newArray_jCompCanvas);
      instance.SetDelete(&delete_jCompCanvas);
      instance.SetDeleteArray(&deleteArray_jCompCanvas);
      instance.SetDestructor(&destruct_jCompCanvas);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jCompCanvas*)
   {
      return GenerateInitInstanceLocal(static_cast<::jCompCanvas*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::jCompCanvas*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_j_gating_result_frame(void *p = nullptr);
   static void *newArray_j_gating_result_frame(Long_t size, void *p);
   static void delete_j_gating_result_frame(void *p);
   static void deleteArray_j_gating_result_frame(void *p);
   static void destruct_j_gating_result_frame(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::j_gating_result_frame*)
   {
      ::j_gating_result_frame *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::j_gating_result_frame >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("j_gating_result_frame", ::j_gating_result_frame::Class_Version(), "j_gating_result_frame.h", 48,
                  typeid(::j_gating_result_frame), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::j_gating_result_frame::Dictionary, isa_proxy, 4,
                  sizeof(::j_gating_result_frame) );
      instance.SetNew(&new_j_gating_result_frame);
      instance.SetNewArray(&newArray_j_gating_result_frame);
      instance.SetDelete(&delete_j_gating_result_frame);
      instance.SetDeleteArray(&deleteArray_j_gating_result_frame);
      instance.SetDestructor(&destruct_j_gating_result_frame);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::j_gating_result_frame*)
   {
      return GenerateInitInstanceLocal(static_cast<::j_gating_result_frame*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::j_gating_result_frame*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_j_gating_select_frame(void *p = nullptr);
   static void *newArray_j_gating_select_frame(Long_t size, void *p);
   static void delete_j_gating_select_frame(void *p);
   static void deleteArray_j_gating_select_frame(void *p);
   static void destruct_j_gating_select_frame(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::j_gating_select_frame*)
   {
      ::j_gating_select_frame *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::j_gating_select_frame >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("j_gating_select_frame", ::j_gating_select_frame::Class_Version(), "j_gating_select_frame.h", 46,
                  typeid(::j_gating_select_frame), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::j_gating_select_frame::Dictionary, isa_proxy, 4,
                  sizeof(::j_gating_select_frame) );
      instance.SetNew(&new_j_gating_select_frame);
      instance.SetNewArray(&newArray_j_gating_select_frame);
      instance.SetDelete(&delete_j_gating_select_frame);
      instance.SetDeleteArray(&deleteArray_j_gating_select_frame);
      instance.SetDestructor(&destruct_j_gating_select_frame);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::j_gating_select_frame*)
   {
      return GenerateInitInstanceLocal(static_cast<::j_gating_select_frame*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::j_gating_select_frame*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_j_gating_select_frame_tester(void *p);
   static void deleteArray_j_gating_select_frame_tester(void *p);
   static void destruct_j_gating_select_frame_tester(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::j_gating_select_frame_tester*)
   {
      ::j_gating_select_frame_tester *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::j_gating_select_frame_tester >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("j_gating_select_frame_tester", ::j_gating_select_frame_tester::Class_Version(), "j_gating_select_frame.h", 167,
                  typeid(::j_gating_select_frame_tester), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::j_gating_select_frame_tester::Dictionary, isa_proxy, 4,
                  sizeof(::j_gating_select_frame_tester) );
      instance.SetDelete(&delete_j_gating_select_frame_tester);
      instance.SetDeleteArray(&deleteArray_j_gating_select_frame_tester);
      instance.SetDestructor(&destruct_j_gating_select_frame_tester);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::j_gating_select_frame_tester*)
   {
      return GenerateInitInstanceLocal(static_cast<::j_gating_select_frame_tester*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::j_gating_select_frame_tester*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_jRootTreeCube(void *p = nullptr);
   static void *newArray_jRootTreeCube(Long_t size, void *p);
   static void delete_jRootTreeCube(void *p);
   static void deleteArray_jRootTreeCube(void *p);
   static void destruct_jRootTreeCube(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jRootTreeCube*)
   {
      ::jRootTreeCube *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jRootTreeCube >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("jRootTreeCube", ::jRootTreeCube::Class_Version(), "j_treetup_tool.h", 32,
                  typeid(::jRootTreeCube), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::jRootTreeCube::Dictionary, isa_proxy, 4,
                  sizeof(::jRootTreeCube) );
      instance.SetNew(&new_jRootTreeCube);
      instance.SetNewArray(&newArray_jRootTreeCube);
      instance.SetDelete(&delete_jRootTreeCube);
      instance.SetDeleteArray(&deleteArray_jRootTreeCube);
      instance.SetDestructor(&destruct_jRootTreeCube);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::jRootTreeCube*)
   {
      return GenerateInitInstanceLocal(static_cast<::jRootTreeCube*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::jRootTreeCube*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TH1Efficiency::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TH1Efficiency::Class_Name()
{
   return "TH1Efficiency";
}

//______________________________________________________________________________
const char *TH1Efficiency::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH1Efficiency*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TH1Efficiency::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH1Efficiency*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TH1Efficiency::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH1Efficiency*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TH1Efficiency::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH1Efficiency*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TH2Efficiency::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TH2Efficiency::Class_Name()
{
   return "TH2Efficiency";
}

//______________________________________________________________________________
const char *TH2Efficiency::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH2Efficiency*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TH2Efficiency::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH2Efficiency*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TH2Efficiency::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH2Efficiency*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TH2Efficiency::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH2Efficiency*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jRootMultiPurposePopup::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *jRootMultiPurposePopup::Class_Name()
{
   return "jRootMultiPurposePopup";
}

//______________________________________________________________________________
const char *jRootMultiPurposePopup::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jRootMultiPurposePopup*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int jRootMultiPurposePopup::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jRootMultiPurposePopup*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jRootMultiPurposePopup::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jRootMultiPurposePopup*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jRootMultiPurposePopup::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jRootMultiPurposePopup*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FullFitHolder::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *FullFitHolder::Class_Name()
{
   return "FullFitHolder";
}

//______________________________________________________________________________
const char *FullFitHolder::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FullFitHolder*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int FullFitHolder::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FullFitHolder*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FullFitHolder::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FullFitHolder*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FullFitHolder::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FullFitHolder*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jhistquestion::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *jhistquestion::Class_Name()
{
   return "jhistquestion";
}

//______________________________________________________________________________
const char *jhistquestion::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jhistquestion*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int jhistquestion::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jhistquestion*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jhistquestion::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jhistquestion*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jhistquestion::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jhistquestion*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TH1ErrorAdj::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TH1ErrorAdj::Class_Name()
{
   return "TH1ErrorAdj";
}

//______________________________________________________________________________
const char *TH1ErrorAdj::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH1ErrorAdj*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TH1ErrorAdj::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH1ErrorAdj*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TH1ErrorAdj::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH1ErrorAdj*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TH1ErrorAdj::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH1ErrorAdj*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr CCframe::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *CCframe::Class_Name()
{
   return "CCframe";
}

//______________________________________________________________________________
const char *CCframe::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CCframe*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int CCframe::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CCframe*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *CCframe::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CCframe*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CCframe::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CCframe*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jHistCapButton::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *jHistCapButton::Class_Name()
{
   return "jHistCapButton";
}

//______________________________________________________________________________
const char *jHistCapButton::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jHistCapButton*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int jHistCapButton::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jHistCapButton*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jHistCapButton::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jHistCapButton*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jHistCapButton::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jHistCapButton*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jAddSubTool::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *jAddSubTool::Class_Name()
{
   return "jAddSubTool";
}

//______________________________________________________________________________
const char *jAddSubTool::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jAddSubTool*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int jAddSubTool::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jAddSubTool*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jAddSubTool::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jAddSubTool*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jAddSubTool::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jAddSubTool*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jDirList::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *jDirList::Class_Name()
{
   return "jDirList";
}

//______________________________________________________________________________
const char *jDirList::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jDirList*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int jDirList::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jDirList*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jDirList::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jDirList*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jDirList::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jDirList*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Ultrapeak::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Ultrapeak::Class_Name()
{
   return "Ultrapeak";
}

//______________________________________________________________________________
const char *Ultrapeak::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Ultrapeak*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Ultrapeak::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Ultrapeak*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Ultrapeak::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Ultrapeak*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Ultrapeak::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Ultrapeak*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr UltraFitEnv::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *UltraFitEnv::Class_Name()
{
   return "UltraFitEnv";
}

//______________________________________________________________________________
const char *UltraFitEnv::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::UltraFitEnv*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int UltraFitEnv::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::UltraFitEnv*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *UltraFitEnv::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::UltraFitEnv*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *UltraFitEnv::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::UltraFitEnv*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr j_gating_frame::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *j_gating_frame::Class_Name()
{
   return "j_gating_frame";
}

//______________________________________________________________________________
const char *j_gating_frame::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::j_gating_frame*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int j_gating_frame::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::j_gating_frame*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *j_gating_frame::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::j_gating_frame*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *j_gating_frame::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::j_gating_frame*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jgating_tool::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *jgating_tool::Class_Name()
{
   return "jgating_tool";
}

//______________________________________________________________________________
const char *jgating_tool::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jgating_tool*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int jgating_tool::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jgating_tool*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jgating_tool::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jgating_tool*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jgating_tool::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jgating_tool*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr minimalist_th3slice::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *minimalist_th3slice::Class_Name()
{
   return "minimalist_th3slice";
}

//______________________________________________________________________________
const char *minimalist_th3slice::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::minimalist_th3slice*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int minimalist_th3slice::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::minimalist_th3slice*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *minimalist_th3slice::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::minimalist_th3slice*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *minimalist_th3slice::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::minimalist_th3slice*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jSpecTool::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *jSpecTool::Class_Name()
{
   return "jSpecTool";
}

//______________________________________________________________________________
const char *jSpecTool::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jSpecTool*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int jSpecTool::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jSpecTool*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jSpecTool::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jSpecTool*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jSpecTool::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jSpecTool*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jEnv::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *jEnv::Class_Name()
{
   return "jEnv";
}

//______________________________________________________________________________
const char *jEnv::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jEnv*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int jEnv::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jEnv*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jEnv::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jEnv*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jEnv::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jEnv*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jScale::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *jScale::Class_Name()
{
   return "jScale";
}

//______________________________________________________________________________
const char *jScale::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jScale*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int jScale::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jScale*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jScale::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jScale*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jScale::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jScale*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jEval::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *jEval::Class_Name()
{
   return "jEval";
}

//______________________________________________________________________________
const char *jEval::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jEval*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int jEval::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jEval*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jEval::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jEval*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jEval::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jEval*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jAngleAngel::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *jAngleAngel::Class_Name()
{
   return "jAngleAngel";
}

//______________________________________________________________________________
const char *jAngleAngel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jAngleAngel*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int jAngleAngel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jAngleAngel*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jAngleAngel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jAngleAngel*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jAngleAngel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jAngleAngel*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr j2DPeakFit::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *j2DPeakFit::Class_Name()
{
   return "j2DPeakFit";
}

//______________________________________________________________________________
const char *j2DPeakFit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::j2DPeakFit*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int j2DPeakFit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::j2DPeakFit*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *j2DPeakFit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::j2DPeakFit*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *j2DPeakFit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::j2DPeakFit*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jIntegrator::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *jIntegrator::Class_Name()
{
   return "jIntegrator";
}

//______________________________________________________________________________
const char *jIntegrator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jIntegrator*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int jIntegrator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jIntegrator*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jIntegrator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jIntegrator*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jIntegrator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jIntegrator*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jCompCanvas::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *jCompCanvas::Class_Name()
{
   return "jCompCanvas";
}

//______________________________________________________________________________
const char *jCompCanvas::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jCompCanvas*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int jCompCanvas::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jCompCanvas*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jCompCanvas::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jCompCanvas*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jCompCanvas::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jCompCanvas*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr j_gating_result_frame::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *j_gating_result_frame::Class_Name()
{
   return "j_gating_result_frame";
}

//______________________________________________________________________________
const char *j_gating_result_frame::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::j_gating_result_frame*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int j_gating_result_frame::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::j_gating_result_frame*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *j_gating_result_frame::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::j_gating_result_frame*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *j_gating_result_frame::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::j_gating_result_frame*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr j_gating_select_frame::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *j_gating_select_frame::Class_Name()
{
   return "j_gating_select_frame";
}

//______________________________________________________________________________
const char *j_gating_select_frame::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::j_gating_select_frame*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int j_gating_select_frame::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::j_gating_select_frame*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *j_gating_select_frame::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::j_gating_select_frame*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *j_gating_select_frame::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::j_gating_select_frame*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr j_gating_select_frame_tester::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *j_gating_select_frame_tester::Class_Name()
{
   return "j_gating_select_frame_tester";
}

//______________________________________________________________________________
const char *j_gating_select_frame_tester::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::j_gating_select_frame_tester*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int j_gating_select_frame_tester::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::j_gating_select_frame_tester*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *j_gating_select_frame_tester::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::j_gating_select_frame_tester*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *j_gating_select_frame_tester::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::j_gating_select_frame_tester*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jRootTreeCube::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *jRootTreeCube::Class_Name()
{
   return "jRootTreeCube";
}

//______________________________________________________________________________
const char *jRootTreeCube::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jRootTreeCube*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int jRootTreeCube::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jRootTreeCube*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jRootTreeCube::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jRootTreeCube*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jRootTreeCube::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jRootTreeCube*)nullptr)->GetClass(); }
   return fgIsA;
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TransientBitsClasslElonggR(void *p) {
      return  p ? new(p) ::TransientBitsClass<long> : new ::TransientBitsClass<long>;
   }
   static void *newArray_TransientBitsClasslElonggR(Long_t nElements, void *p) {
      return p ? new(p) ::TransientBitsClass<long>[nElements] : new ::TransientBitsClass<long>[nElements];
   }
   // Wrapper around operator delete
   static void delete_TransientBitsClasslElonggR(void *p) {
      delete (static_cast<::TransientBitsClass<long>*>(p));
   }
   static void deleteArray_TransientBitsClasslElonggR(void *p) {
      delete [] (static_cast<::TransientBitsClass<long>*>(p));
   }
   static void destruct_TransientBitsClasslElonggR(void *p) {
      typedef ::TransientBitsClass<long> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TransientBitsClass<long>

//______________________________________________________________________________
void TH1Efficiency::Streamer(TBuffer &R__b)
{
   // Stream an object of class TH1Efficiency.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TH1Efficiency::Class(),this);
   } else {
      R__b.WriteClassBuffer(TH1Efficiency::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TH1Efficiency(void *p) {
      return  p ? new(p) ::TH1Efficiency : new ::TH1Efficiency;
   }
   static void *newArray_TH1Efficiency(Long_t nElements, void *p) {
      return p ? new(p) ::TH1Efficiency[nElements] : new ::TH1Efficiency[nElements];
   }
   // Wrapper around operator delete
   static void delete_TH1Efficiency(void *p) {
      delete (static_cast<::TH1Efficiency*>(p));
   }
   static void deleteArray_TH1Efficiency(void *p) {
      delete [] (static_cast<::TH1Efficiency*>(p));
   }
   static void destruct_TH1Efficiency(void *p) {
      typedef ::TH1Efficiency current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around the directory auto add.
   static void directoryAutoAdd_TH1Efficiency(void *p, TDirectory *dir) {
      ((::TH1Efficiency*)p)->DirectoryAutoAdd(dir);
   }
   // Wrapper around the merge function.
   static Long64_t  merge_TH1Efficiency(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::TH1Efficiency*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::TH1Efficiency

//______________________________________________________________________________
void TH2Efficiency::Streamer(TBuffer &R__b)
{
   // Stream an object of class TH2Efficiency.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TH2Efficiency::Class(),this);
   } else {
      R__b.WriteClassBuffer(TH2Efficiency::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TH2Efficiency(void *p) {
      return  p ? new(p) ::TH2Efficiency : new ::TH2Efficiency;
   }
   static void *newArray_TH2Efficiency(Long_t nElements, void *p) {
      return p ? new(p) ::TH2Efficiency[nElements] : new ::TH2Efficiency[nElements];
   }
   // Wrapper around operator delete
   static void delete_TH2Efficiency(void *p) {
      delete (static_cast<::TH2Efficiency*>(p));
   }
   static void deleteArray_TH2Efficiency(void *p) {
      delete [] (static_cast<::TH2Efficiency*>(p));
   }
   static void destruct_TH2Efficiency(void *p) {
      typedef ::TH2Efficiency current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around the directory auto add.
   static void directoryAutoAdd_TH2Efficiency(void *p, TDirectory *dir) {
      ((::TH2Efficiency*)p)->DirectoryAutoAdd(dir);
   }
   // Wrapper around the merge function.
   static Long64_t  merge_TH2Efficiency(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::TH2Efficiency*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::TH2Efficiency

//______________________________________________________________________________
void jRootMultiPurposePopup::Streamer(TBuffer &R__b)
{
   // Stream an object of class jRootMultiPurposePopup.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(jRootMultiPurposePopup::Class(),this);
   } else {
      R__b.WriteClassBuffer(jRootMultiPurposePopup::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_jRootMultiPurposePopup(void *p) {
      return  p ? new(p) ::jRootMultiPurposePopup : new ::jRootMultiPurposePopup;
   }
   static void *newArray_jRootMultiPurposePopup(Long_t nElements, void *p) {
      return p ? new(p) ::jRootMultiPurposePopup[nElements] : new ::jRootMultiPurposePopup[nElements];
   }
   // Wrapper around operator delete
   static void delete_jRootMultiPurposePopup(void *p) {
      delete (static_cast<::jRootMultiPurposePopup*>(p));
   }
   static void deleteArray_jRootMultiPurposePopup(void *p) {
      delete [] (static_cast<::jRootMultiPurposePopup*>(p));
   }
   static void destruct_jRootMultiPurposePopup(void *p) {
      typedef ::jRootMultiPurposePopup current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::jRootMultiPurposePopup

//______________________________________________________________________________
void FullFitHolder::Streamer(TBuffer &R__b)
{
   // Stream an object of class FullFitHolder.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FullFitHolder::Class(),this);
   } else {
      R__b.WriteClassBuffer(FullFitHolder::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FullFitHolder(void *p) {
      return  p ? new(p) ::FullFitHolder : new ::FullFitHolder;
   }
   static void *newArray_FullFitHolder(Long_t nElements, void *p) {
      return p ? new(p) ::FullFitHolder[nElements] : new ::FullFitHolder[nElements];
   }
   // Wrapper around operator delete
   static void delete_FullFitHolder(void *p) {
      delete (static_cast<::FullFitHolder*>(p));
   }
   static void deleteArray_FullFitHolder(void *p) {
      delete [] (static_cast<::FullFitHolder*>(p));
   }
   static void destruct_FullFitHolder(void *p) {
      typedef ::FullFitHolder current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::FullFitHolder

namespace ROOT {
   // Wrapper around operator delete
   static void delete_jPeakDat(void *p) {
      delete (static_cast<::jPeakDat*>(p));
   }
   static void deleteArray_jPeakDat(void *p) {
      delete [] (static_cast<::jPeakDat*>(p));
   }
   static void destruct_jPeakDat(void *p) {
      typedef ::jPeakDat current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::jPeakDat

namespace ROOT {
   // Wrappers around operator new
   static void *new_HistClickStop(void *p) {
      return  p ? new(p) ::HistClickStop : new ::HistClickStop;
   }
   static void *newArray_HistClickStop(Long_t nElements, void *p) {
      return p ? new(p) ::HistClickStop[nElements] : new ::HistClickStop[nElements];
   }
   // Wrapper around operator delete
   static void delete_HistClickStop(void *p) {
      delete (static_cast<::HistClickStop*>(p));
   }
   static void deleteArray_HistClickStop(void *p) {
      delete [] (static_cast<::HistClickStop*>(p));
   }
   static void destruct_HistClickStop(void *p) {
      typedef ::HistClickStop current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::HistClickStop

//______________________________________________________________________________
void jhistquestion::Streamer(TBuffer &R__b)
{
   // Stream an object of class jhistquestion.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(jhistquestion::Class(),this);
   } else {
      R__b.WriteClassBuffer(jhistquestion::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_jhistquestion(void *p) {
      return  p ? new(p) ::jhistquestion : new ::jhistquestion;
   }
   static void *newArray_jhistquestion(Long_t nElements, void *p) {
      return p ? new(p) ::jhistquestion[nElements] : new ::jhistquestion[nElements];
   }
   // Wrapper around operator delete
   static void delete_jhistquestion(void *p) {
      delete (static_cast<::jhistquestion*>(p));
   }
   static void deleteArray_jhistquestion(void *p) {
      delete [] (static_cast<::jhistquestion*>(p));
   }
   static void destruct_jhistquestion(void *p) {
      typedef ::jhistquestion current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::jhistquestion

//______________________________________________________________________________
void TH1ErrorAdj::Streamer(TBuffer &R__b)
{
   // Stream an object of class TH1ErrorAdj.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TH1ErrorAdj::Class(),this);
   } else {
      R__b.WriteClassBuffer(TH1ErrorAdj::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TH1ErrorAdj(void *p) {
      return  p ? new(p) ::TH1ErrorAdj : new ::TH1ErrorAdj;
   }
   static void *newArray_TH1ErrorAdj(Long_t nElements, void *p) {
      return p ? new(p) ::TH1ErrorAdj[nElements] : new ::TH1ErrorAdj[nElements];
   }
   // Wrapper around operator delete
   static void delete_TH1ErrorAdj(void *p) {
      delete (static_cast<::TH1ErrorAdj*>(p));
   }
   static void deleteArray_TH1ErrorAdj(void *p) {
      delete [] (static_cast<::TH1ErrorAdj*>(p));
   }
   static void destruct_TH1ErrorAdj(void *p) {
      typedef ::TH1ErrorAdj current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around the directory auto add.
   static void directoryAutoAdd_TH1ErrorAdj(void *p, TDirectory *dir) {
      ((::TH1ErrorAdj*)p)->DirectoryAutoAdd(dir);
   }
   // Wrapper around the merge function.
   static Long64_t  merge_TH1ErrorAdj(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::TH1ErrorAdj*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::TH1ErrorAdj

//______________________________________________________________________________
void CCframe::Streamer(TBuffer &R__b)
{
   // Stream an object of class CCframe.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(CCframe::Class(),this);
   } else {
      R__b.WriteClassBuffer(CCframe::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CCframe(void *p) {
      return  p ? new(p) ::CCframe : new ::CCframe;
   }
   static void *newArray_CCframe(Long_t nElements, void *p) {
      return p ? new(p) ::CCframe[nElements] : new ::CCframe[nElements];
   }
   // Wrapper around operator delete
   static void delete_CCframe(void *p) {
      delete (static_cast<::CCframe*>(p));
   }
   static void deleteArray_CCframe(void *p) {
      delete [] (static_cast<::CCframe*>(p));
   }
   static void destruct_CCframe(void *p) {
      typedef ::CCframe current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::CCframe

//______________________________________________________________________________
void jHistCapButton::Streamer(TBuffer &R__b)
{
   // Stream an object of class jHistCapButton.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(jHistCapButton::Class(),this);
   } else {
      R__b.WriteClassBuffer(jHistCapButton::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_jHistCapButton(void *p) {
      return  p ? new(p) ::jHistCapButton : new ::jHistCapButton;
   }
   static void *newArray_jHistCapButton(Long_t nElements, void *p) {
      return p ? new(p) ::jHistCapButton[nElements] : new ::jHistCapButton[nElements];
   }
   // Wrapper around operator delete
   static void delete_jHistCapButton(void *p) {
      delete (static_cast<::jHistCapButton*>(p));
   }
   static void deleteArray_jHistCapButton(void *p) {
      delete [] (static_cast<::jHistCapButton*>(p));
   }
   static void destruct_jHistCapButton(void *p) {
      typedef ::jHistCapButton current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::jHistCapButton

//______________________________________________________________________________
void jAddSubTool::Streamer(TBuffer &R__b)
{
   // Stream an object of class jAddSubTool.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(jAddSubTool::Class(),this);
   } else {
      R__b.WriteClassBuffer(jAddSubTool::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_jAddSubTool(void *p) {
      delete (static_cast<::jAddSubTool*>(p));
   }
   static void deleteArray_jAddSubTool(void *p) {
      delete [] (static_cast<::jAddSubTool*>(p));
   }
   static void destruct_jAddSubTool(void *p) {
      typedef ::jAddSubTool current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::jAddSubTool

//______________________________________________________________________________
void jDirList::Streamer(TBuffer &R__b)
{
   // Stream an object of class jDirList.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(jDirList::Class(),this);
   } else {
      R__b.WriteClassBuffer(jDirList::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_jDirList(void *p) {
      delete (static_cast<::jDirList*>(p));
   }
   static void deleteArray_jDirList(void *p) {
      delete [] (static_cast<::jDirList*>(p));
   }
   static void destruct_jDirList(void *p) {
      typedef ::jDirList current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::jDirList

//______________________________________________________________________________
void Ultrapeak::Streamer(TBuffer &R__b)
{
   // Stream an object of class Ultrapeak.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Ultrapeak::Class(),this);
   } else {
      R__b.WriteClassBuffer(Ultrapeak::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Ultrapeak(void *p) {
      return  p ? new(p) ::Ultrapeak : new ::Ultrapeak;
   }
   static void *newArray_Ultrapeak(Long_t nElements, void *p) {
      return p ? new(p) ::Ultrapeak[nElements] : new ::Ultrapeak[nElements];
   }
   // Wrapper around operator delete
   static void delete_Ultrapeak(void *p) {
      delete (static_cast<::Ultrapeak*>(p));
   }
   static void deleteArray_Ultrapeak(void *p) {
      delete [] (static_cast<::Ultrapeak*>(p));
   }
   static void destruct_Ultrapeak(void *p) {
      typedef ::Ultrapeak current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::Ultrapeak

namespace ROOT {
   // Wrappers around operator new
   static void *new_UltrapeakArea(void *p) {
      return  p ? new(p) ::UltrapeakArea : new ::UltrapeakArea;
   }
   static void *newArray_UltrapeakArea(Long_t nElements, void *p) {
      return p ? new(p) ::UltrapeakArea[nElements] : new ::UltrapeakArea[nElements];
   }
   // Wrapper around operator delete
   static void delete_UltrapeakArea(void *p) {
      delete (static_cast<::UltrapeakArea*>(p));
   }
   static void deleteArray_UltrapeakArea(void *p) {
      delete [] (static_cast<::UltrapeakArea*>(p));
   }
   static void destruct_UltrapeakArea(void *p) {
      typedef ::UltrapeakArea current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::UltrapeakArea

namespace ROOT {
   // Wrappers around operator new
   static void *new_UltrapeakFrac(void *p) {
      return  p ? new(p) ::UltrapeakFrac : new ::UltrapeakFrac;
   }
   static void *newArray_UltrapeakFrac(Long_t nElements, void *p) {
      return p ? new(p) ::UltrapeakFrac[nElements] : new ::UltrapeakFrac[nElements];
   }
   // Wrapper around operator delete
   static void delete_UltrapeakFrac(void *p) {
      delete (static_cast<::UltrapeakFrac*>(p));
   }
   static void deleteArray_UltrapeakFrac(void *p) {
      delete [] (static_cast<::UltrapeakFrac*>(p));
   }
   static void destruct_UltrapeakFrac(void *p) {
      typedef ::UltrapeakFrac current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::UltrapeakFrac

namespace ROOT {
   // Wrappers around operator new
   static void *new_UltrapeakCentroid(void *p) {
      return  p ? new(p) ::UltrapeakCentroid : new ::UltrapeakCentroid;
   }
   static void *newArray_UltrapeakCentroid(Long_t nElements, void *p) {
      return p ? new(p) ::UltrapeakCentroid[nElements] : new ::UltrapeakCentroid[nElements];
   }
   // Wrapper around operator delete
   static void delete_UltrapeakCentroid(void *p) {
      delete (static_cast<::UltrapeakCentroid*>(p));
   }
   static void deleteArray_UltrapeakCentroid(void *p) {
      delete [] (static_cast<::UltrapeakCentroid*>(p));
   }
   static void destruct_UltrapeakCentroid(void *p) {
      typedef ::UltrapeakCentroid current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::UltrapeakCentroid

//______________________________________________________________________________
void UltraFitEnv::Streamer(TBuffer &R__b)
{
   // Stream an object of class UltraFitEnv.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(UltraFitEnv::Class(),this);
   } else {
      R__b.WriteClassBuffer(UltraFitEnv::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_UltraFitEnv(void *p) {
      return  p ? new(p) ::UltraFitEnv : new ::UltraFitEnv;
   }
   static void *newArray_UltraFitEnv(Long_t nElements, void *p) {
      return p ? new(p) ::UltraFitEnv[nElements] : new ::UltraFitEnv[nElements];
   }
   // Wrapper around operator delete
   static void delete_UltraFitEnv(void *p) {
      delete (static_cast<::UltraFitEnv*>(p));
   }
   static void deleteArray_UltraFitEnv(void *p) {
      delete [] (static_cast<::UltraFitEnv*>(p));
   }
   static void destruct_UltraFitEnv(void *p) {
      typedef ::UltraFitEnv current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::UltraFitEnv

//______________________________________________________________________________
void j_gating_frame::Streamer(TBuffer &R__b)
{
   // Stream an object of class j_gating_frame.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(j_gating_frame::Class(),this);
   } else {
      R__b.WriteClassBuffer(j_gating_frame::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_j_gating_frame(void *p) {
      return  p ? new(p) ::j_gating_frame : new ::j_gating_frame;
   }
   static void *newArray_j_gating_frame(Long_t nElements, void *p) {
      return p ? new(p) ::j_gating_frame[nElements] : new ::j_gating_frame[nElements];
   }
   // Wrapper around operator delete
   static void delete_j_gating_frame(void *p) {
      delete (static_cast<::j_gating_frame*>(p));
   }
   static void deleteArray_j_gating_frame(void *p) {
      delete [] (static_cast<::j_gating_frame*>(p));
   }
   static void destruct_j_gating_frame(void *p) {
      typedef ::j_gating_frame current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::j_gating_frame

//______________________________________________________________________________
void jgating_tool::Streamer(TBuffer &R__b)
{
   // Stream an object of class jgating_tool.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(jgating_tool::Class(),this);
   } else {
      R__b.WriteClassBuffer(jgating_tool::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_jgating_tool(void *p) {
      return  p ? new(p) ::jgating_tool : new ::jgating_tool;
   }
   static void *newArray_jgating_tool(Long_t nElements, void *p) {
      return p ? new(p) ::jgating_tool[nElements] : new ::jgating_tool[nElements];
   }
   // Wrapper around operator delete
   static void delete_jgating_tool(void *p) {
      delete (static_cast<::jgating_tool*>(p));
   }
   static void deleteArray_jgating_tool(void *p) {
      delete [] (static_cast<::jgating_tool*>(p));
   }
   static void destruct_jgating_tool(void *p) {
      typedef ::jgating_tool current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::jgating_tool

//______________________________________________________________________________
void minimalist_th3slice::Streamer(TBuffer &R__b)
{
   // Stream an object of class minimalist_th3slice.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(minimalist_th3slice::Class(),this);
   } else {
      R__b.WriteClassBuffer(minimalist_th3slice::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_minimalist_th3slice(void *p) {
      return  p ? new(p) ::minimalist_th3slice : new ::minimalist_th3slice;
   }
   static void *newArray_minimalist_th3slice(Long_t nElements, void *p) {
      return p ? new(p) ::minimalist_th3slice[nElements] : new ::minimalist_th3slice[nElements];
   }
   // Wrapper around operator delete
   static void delete_minimalist_th3slice(void *p) {
      delete (static_cast<::minimalist_th3slice*>(p));
   }
   static void deleteArray_minimalist_th3slice(void *p) {
      delete [] (static_cast<::minimalist_th3slice*>(p));
   }
   static void destruct_minimalist_th3slice(void *p) {
      typedef ::minimalist_th3slice current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::minimalist_th3slice

//______________________________________________________________________________
void jSpecTool::Streamer(TBuffer &R__b)
{
   // Stream an object of class jSpecTool.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(jSpecTool::Class(),this);
   } else {
      R__b.WriteClassBuffer(jSpecTool::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_jSpecTool(void *p) {
      return  p ? new(p) ::jSpecTool : new ::jSpecTool;
   }
   static void *newArray_jSpecTool(Long_t nElements, void *p) {
      return p ? new(p) ::jSpecTool[nElements] : new ::jSpecTool[nElements];
   }
   // Wrapper around operator delete
   static void delete_jSpecTool(void *p) {
      delete (static_cast<::jSpecTool*>(p));
   }
   static void deleteArray_jSpecTool(void *p) {
      delete [] (static_cast<::jSpecTool*>(p));
   }
   static void destruct_jSpecTool(void *p) {
      typedef ::jSpecTool current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::jSpecTool

//______________________________________________________________________________
void jEnv::Streamer(TBuffer &R__b)
{
   // Stream an object of class jEnv.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(jEnv::Class(),this);
   } else {
      R__b.WriteClassBuffer(jEnv::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_jEnv(void *p) {
      return  p ? new(p) ::jEnv : new ::jEnv;
   }
   static void *newArray_jEnv(Long_t nElements, void *p) {
      return p ? new(p) ::jEnv[nElements] : new ::jEnv[nElements];
   }
   // Wrapper around operator delete
   static void delete_jEnv(void *p) {
      delete (static_cast<::jEnv*>(p));
   }
   static void deleteArray_jEnv(void *p) {
      delete [] (static_cast<::jEnv*>(p));
   }
   static void destruct_jEnv(void *p) {
      typedef ::jEnv current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::jEnv

//______________________________________________________________________________
void jScale::Streamer(TBuffer &R__b)
{
   // Stream an object of class jScale.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(jScale::Class(),this);
   } else {
      R__b.WriteClassBuffer(jScale::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_jScale(void *p) {
      return  p ? new(p) ::jScale : new ::jScale;
   }
   static void *newArray_jScale(Long_t nElements, void *p) {
      return p ? new(p) ::jScale[nElements] : new ::jScale[nElements];
   }
   // Wrapper around operator delete
   static void delete_jScale(void *p) {
      delete (static_cast<::jScale*>(p));
   }
   static void deleteArray_jScale(void *p) {
      delete [] (static_cast<::jScale*>(p));
   }
   static void destruct_jScale(void *p) {
      typedef ::jScale current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::jScale

//______________________________________________________________________________
void jEval::Streamer(TBuffer &R__b)
{
   // Stream an object of class jEval.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(jEval::Class(),this);
   } else {
      R__b.WriteClassBuffer(jEval::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_jEval(void *p) {
      return  p ? new(p) ::jEval : new ::jEval;
   }
   static void *newArray_jEval(Long_t nElements, void *p) {
      return p ? new(p) ::jEval[nElements] : new ::jEval[nElements];
   }
   // Wrapper around operator delete
   static void delete_jEval(void *p) {
      delete (static_cast<::jEval*>(p));
   }
   static void deleteArray_jEval(void *p) {
      delete [] (static_cast<::jEval*>(p));
   }
   static void destruct_jEval(void *p) {
      typedef ::jEval current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::jEval

//______________________________________________________________________________
void jAngleAngel::Streamer(TBuffer &R__b)
{
   // Stream an object of class jAngleAngel.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(jAngleAngel::Class(),this);
   } else {
      R__b.WriteClassBuffer(jAngleAngel::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_jAngleAngel(void *p) {
      return  p ? new(p) ::jAngleAngel : new ::jAngleAngel;
   }
   static void *newArray_jAngleAngel(Long_t nElements, void *p) {
      return p ? new(p) ::jAngleAngel[nElements] : new ::jAngleAngel[nElements];
   }
   // Wrapper around operator delete
   static void delete_jAngleAngel(void *p) {
      delete (static_cast<::jAngleAngel*>(p));
   }
   static void deleteArray_jAngleAngel(void *p) {
      delete [] (static_cast<::jAngleAngel*>(p));
   }
   static void destruct_jAngleAngel(void *p) {
      typedef ::jAngleAngel current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::jAngleAngel

//______________________________________________________________________________
void j2DPeakFit::Streamer(TBuffer &R__b)
{
   // Stream an object of class j2DPeakFit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(j2DPeakFit::Class(),this);
   } else {
      R__b.WriteClassBuffer(j2DPeakFit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_j2DPeakFit(void *p) {
      return  p ? new(p) ::j2DPeakFit : new ::j2DPeakFit;
   }
   static void *newArray_j2DPeakFit(Long_t nElements, void *p) {
      return p ? new(p) ::j2DPeakFit[nElements] : new ::j2DPeakFit[nElements];
   }
   // Wrapper around operator delete
   static void delete_j2DPeakFit(void *p) {
      delete (static_cast<::j2DPeakFit*>(p));
   }
   static void deleteArray_j2DPeakFit(void *p) {
      delete [] (static_cast<::j2DPeakFit*>(p));
   }
   static void destruct_j2DPeakFit(void *p) {
      typedef ::j2DPeakFit current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::j2DPeakFit

//______________________________________________________________________________
void jIntegrator::Streamer(TBuffer &R__b)
{
   // Stream an object of class jIntegrator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(jIntegrator::Class(),this);
   } else {
      R__b.WriteClassBuffer(jIntegrator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_jIntegrator(void *p) {
      return  p ? new(p) ::jIntegrator : new ::jIntegrator;
   }
   static void *newArray_jIntegrator(Long_t nElements, void *p) {
      return p ? new(p) ::jIntegrator[nElements] : new ::jIntegrator[nElements];
   }
   // Wrapper around operator delete
   static void delete_jIntegrator(void *p) {
      delete (static_cast<::jIntegrator*>(p));
   }
   static void deleteArray_jIntegrator(void *p) {
      delete [] (static_cast<::jIntegrator*>(p));
   }
   static void destruct_jIntegrator(void *p) {
      typedef ::jIntegrator current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::jIntegrator

//______________________________________________________________________________
void jCompCanvas::Streamer(TBuffer &R__b)
{
   // Stream an object of class jCompCanvas.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(jCompCanvas::Class(),this);
   } else {
      R__b.WriteClassBuffer(jCompCanvas::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_jCompCanvas(void *p) {
      return  p ? new(p) ::jCompCanvas : new ::jCompCanvas;
   }
   static void *newArray_jCompCanvas(Long_t nElements, void *p) {
      return p ? new(p) ::jCompCanvas[nElements] : new ::jCompCanvas[nElements];
   }
   // Wrapper around operator delete
   static void delete_jCompCanvas(void *p) {
      delete (static_cast<::jCompCanvas*>(p));
   }
   static void deleteArray_jCompCanvas(void *p) {
      delete [] (static_cast<::jCompCanvas*>(p));
   }
   static void destruct_jCompCanvas(void *p) {
      typedef ::jCompCanvas current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::jCompCanvas

//______________________________________________________________________________
void j_gating_result_frame::Streamer(TBuffer &R__b)
{
   // Stream an object of class j_gating_result_frame.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(j_gating_result_frame::Class(),this);
   } else {
      R__b.WriteClassBuffer(j_gating_result_frame::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_j_gating_result_frame(void *p) {
      return  p ? new(p) ::j_gating_result_frame : new ::j_gating_result_frame;
   }
   static void *newArray_j_gating_result_frame(Long_t nElements, void *p) {
      return p ? new(p) ::j_gating_result_frame[nElements] : new ::j_gating_result_frame[nElements];
   }
   // Wrapper around operator delete
   static void delete_j_gating_result_frame(void *p) {
      delete (static_cast<::j_gating_result_frame*>(p));
   }
   static void deleteArray_j_gating_result_frame(void *p) {
      delete [] (static_cast<::j_gating_result_frame*>(p));
   }
   static void destruct_j_gating_result_frame(void *p) {
      typedef ::j_gating_result_frame current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::j_gating_result_frame

//______________________________________________________________________________
void j_gating_select_frame::Streamer(TBuffer &R__b)
{
   // Stream an object of class j_gating_select_frame.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(j_gating_select_frame::Class(),this);
   } else {
      R__b.WriteClassBuffer(j_gating_select_frame::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_j_gating_select_frame(void *p) {
      return  p ? new(p) ::j_gating_select_frame : new ::j_gating_select_frame;
   }
   static void *newArray_j_gating_select_frame(Long_t nElements, void *p) {
      return p ? new(p) ::j_gating_select_frame[nElements] : new ::j_gating_select_frame[nElements];
   }
   // Wrapper around operator delete
   static void delete_j_gating_select_frame(void *p) {
      delete (static_cast<::j_gating_select_frame*>(p));
   }
   static void deleteArray_j_gating_select_frame(void *p) {
      delete [] (static_cast<::j_gating_select_frame*>(p));
   }
   static void destruct_j_gating_select_frame(void *p) {
      typedef ::j_gating_select_frame current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::j_gating_select_frame

//______________________________________________________________________________
void j_gating_select_frame_tester::Streamer(TBuffer &R__b)
{
   // Stream an object of class j_gating_select_frame_tester.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(j_gating_select_frame_tester::Class(),this);
   } else {
      R__b.WriteClassBuffer(j_gating_select_frame_tester::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_j_gating_select_frame_tester(void *p) {
      delete (static_cast<::j_gating_select_frame_tester*>(p));
   }
   static void deleteArray_j_gating_select_frame_tester(void *p) {
      delete [] (static_cast<::j_gating_select_frame_tester*>(p));
   }
   static void destruct_j_gating_select_frame_tester(void *p) {
      typedef ::j_gating_select_frame_tester current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::j_gating_select_frame_tester

//______________________________________________________________________________
void jRootTreeCube::Streamer(TBuffer &R__b)
{
   // Stream an object of class jRootTreeCube.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(jRootTreeCube::Class(),this);
   } else {
      R__b.WriteClassBuffer(jRootTreeCube::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_jRootTreeCube(void *p) {
      return  p ? new(p) ::jRootTreeCube : new ::jRootTreeCube;
   }
   static void *newArray_jRootTreeCube(Long_t nElements, void *p) {
      return p ? new(p) ::jRootTreeCube[nElements] : new ::jRootTreeCube[nElements];
   }
   // Wrapper around operator delete
   static void delete_jRootTreeCube(void *p) {
      delete (static_cast<::jRootTreeCube*>(p));
   }
   static void deleteArray_jRootTreeCube(void *p) {
      delete [] (static_cast<::jRootTreeCube*>(p));
   }
   static void destruct_jRootTreeCube(void *p) {
      typedef ::jRootTreeCube current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::jRootTreeCube

namespace ROOT {
   static TClass *vectorlEstringgR_Dictionary();
   static void vectorlEstringgR_TClassManip(TClass*);
   static void *new_vectorlEstringgR(void *p = nullptr);
   static void *newArray_vectorlEstringgR(Long_t size, void *p);
   static void delete_vectorlEstringgR(void *p);
   static void deleteArray_vectorlEstringgR(void *p);
   static void destruct_vectorlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<string>*)
   {
      vector<string> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<string>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<string>", -2, "vector", 389,
                  typeid(vector<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<string>) );
      instance.SetNew(&new_vectorlEstringgR);
      instance.SetNewArray(&newArray_vectorlEstringgR);
      instance.SetDelete(&delete_vectorlEstringgR);
      instance.SetDeleteArray(&deleteArray_vectorlEstringgR);
      instance.SetDestructor(&destruct_vectorlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<string> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<string>","std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<string>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<string>*>(nullptr))->GetClass();
      vectorlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string> : new vector<string>;
   }
   static void *newArray_vectorlEstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string>[nElements] : new vector<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEstringgR(void *p) {
      delete (static_cast<vector<string>*>(p));
   }
   static void deleteArray_vectorlEstringgR(void *p) {
      delete [] (static_cast<vector<string>*>(p));
   }
   static void destruct_vectorlEstringgR(void *p) {
      typedef vector<string> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<string>

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = nullptr);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 389,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<int>","std::vector<int, std::allocator<int> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<int>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<int>*>(nullptr))->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete (static_cast<vector<int>*>(p));
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] (static_cast<vector<int>*>(p));
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = nullptr);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 389,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<double>","std::vector<double, std::allocator<double> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<double>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<double>*>(nullptr))->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete (static_cast<vector<double>*>(p));
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] (static_cast<vector<double>*>(p));
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlETTextgR_Dictionary();
   static void vectorlETTextgR_TClassManip(TClass*);
   static void *new_vectorlETTextgR(void *p = nullptr);
   static void *newArray_vectorlETTextgR(Long_t size, void *p);
   static void delete_vectorlETTextgR(void *p);
   static void deleteArray_vectorlETTextgR(void *p);
   static void destruct_vectorlETTextgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TText>*)
   {
      vector<TText> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TText>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TText>", -2, "vector", 389,
                  typeid(vector<TText>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETTextgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TText>) );
      instance.SetNew(&new_vectorlETTextgR);
      instance.SetNewArray(&newArray_vectorlETTextgR);
      instance.SetDelete(&delete_vectorlETTextgR);
      instance.SetDeleteArray(&deleteArray_vectorlETTextgR);
      instance.SetDestructor(&destruct_vectorlETTextgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TText> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<TText>","std::vector<TText, std::allocator<TText> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<TText>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETTextgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<TText>*>(nullptr))->GetClass();
      vectorlETTextgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETTextgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETTextgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TText> : new vector<TText>;
   }
   static void *newArray_vectorlETTextgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TText>[nElements] : new vector<TText>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETTextgR(void *p) {
      delete (static_cast<vector<TText>*>(p));
   }
   static void deleteArray_vectorlETTextgR(void *p) {
      delete [] (static_cast<vector<TText>*>(p));
   }
   static void destruct_vectorlETTextgR(void *p) {
      typedef vector<TText> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<TText>

namespace ROOT {
   static TClass *vectorlETH1mUgR_Dictionary();
   static void vectorlETH1mUgR_TClassManip(TClass*);
   static void *new_vectorlETH1mUgR(void *p = nullptr);
   static void *newArray_vectorlETH1mUgR(Long_t size, void *p);
   static void delete_vectorlETH1mUgR(void *p);
   static void deleteArray_vectorlETH1mUgR(void *p);
   static void destruct_vectorlETH1mUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TH1*>*)
   {
      vector<TH1*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TH1*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TH1*>", -2, "vector", 389,
                  typeid(vector<TH1*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETH1mUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TH1*>) );
      instance.SetNew(&new_vectorlETH1mUgR);
      instance.SetNewArray(&newArray_vectorlETH1mUgR);
      instance.SetDelete(&delete_vectorlETH1mUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETH1mUgR);
      instance.SetDestructor(&destruct_vectorlETH1mUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TH1*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<TH1*>","std::vector<TH1*, std::allocator<TH1*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<TH1*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETH1mUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<TH1*>*>(nullptr))->GetClass();
      vectorlETH1mUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETH1mUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETH1mUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TH1*> : new vector<TH1*>;
   }
   static void *newArray_vectorlETH1mUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TH1*>[nElements] : new vector<TH1*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETH1mUgR(void *p) {
      delete (static_cast<vector<TH1*>*>(p));
   }
   static void deleteArray_vectorlETH1mUgR(void *p) {
      delete [] (static_cast<vector<TH1*>*>(p));
   }
   static void destruct_vectorlETH1mUgR(void *p) {
      typedef vector<TH1*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<TH1*>

namespace ROOT {
   static TClass *vectorlETGTextEntrymUgR_Dictionary();
   static void vectorlETGTextEntrymUgR_TClassManip(TClass*);
   static void *new_vectorlETGTextEntrymUgR(void *p = nullptr);
   static void *newArray_vectorlETGTextEntrymUgR(Long_t size, void *p);
   static void delete_vectorlETGTextEntrymUgR(void *p);
   static void deleteArray_vectorlETGTextEntrymUgR(void *p);
   static void destruct_vectorlETGTextEntrymUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TGTextEntry*>*)
   {
      vector<TGTextEntry*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TGTextEntry*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TGTextEntry*>", -2, "vector", 389,
                  typeid(vector<TGTextEntry*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETGTextEntrymUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TGTextEntry*>) );
      instance.SetNew(&new_vectorlETGTextEntrymUgR);
      instance.SetNewArray(&newArray_vectorlETGTextEntrymUgR);
      instance.SetDelete(&delete_vectorlETGTextEntrymUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETGTextEntrymUgR);
      instance.SetDestructor(&destruct_vectorlETGTextEntrymUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TGTextEntry*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<TGTextEntry*>","std::vector<TGTextEntry*, std::allocator<TGTextEntry*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<TGTextEntry*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETGTextEntrymUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<TGTextEntry*>*>(nullptr))->GetClass();
      vectorlETGTextEntrymUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETGTextEntrymUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETGTextEntrymUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGTextEntry*> : new vector<TGTextEntry*>;
   }
   static void *newArray_vectorlETGTextEntrymUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGTextEntry*>[nElements] : new vector<TGTextEntry*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETGTextEntrymUgR(void *p) {
      delete (static_cast<vector<TGTextEntry*>*>(p));
   }
   static void deleteArray_vectorlETGTextEntrymUgR(void *p) {
      delete [] (static_cast<vector<TGTextEntry*>*>(p));
   }
   static void destruct_vectorlETGTextEntrymUgR(void *p) {
      typedef vector<TGTextEntry*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<TGTextEntry*>

namespace ROOT {
   static TClass *vectorlETGTextButtonmUgR_Dictionary();
   static void vectorlETGTextButtonmUgR_TClassManip(TClass*);
   static void *new_vectorlETGTextButtonmUgR(void *p = nullptr);
   static void *newArray_vectorlETGTextButtonmUgR(Long_t size, void *p);
   static void delete_vectorlETGTextButtonmUgR(void *p);
   static void deleteArray_vectorlETGTextButtonmUgR(void *p);
   static void destruct_vectorlETGTextButtonmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TGTextButton*>*)
   {
      vector<TGTextButton*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TGTextButton*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TGTextButton*>", -2, "vector", 389,
                  typeid(vector<TGTextButton*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETGTextButtonmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TGTextButton*>) );
      instance.SetNew(&new_vectorlETGTextButtonmUgR);
      instance.SetNewArray(&newArray_vectorlETGTextButtonmUgR);
      instance.SetDelete(&delete_vectorlETGTextButtonmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETGTextButtonmUgR);
      instance.SetDestructor(&destruct_vectorlETGTextButtonmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TGTextButton*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<TGTextButton*>","std::vector<TGTextButton*, std::allocator<TGTextButton*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<TGTextButton*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETGTextButtonmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<TGTextButton*>*>(nullptr))->GetClass();
      vectorlETGTextButtonmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETGTextButtonmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETGTextButtonmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGTextButton*> : new vector<TGTextButton*>;
   }
   static void *newArray_vectorlETGTextButtonmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGTextButton*>[nElements] : new vector<TGTextButton*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETGTextButtonmUgR(void *p) {
      delete (static_cast<vector<TGTextButton*>*>(p));
   }
   static void deleteArray_vectorlETGTextButtonmUgR(void *p) {
      delete [] (static_cast<vector<TGTextButton*>*>(p));
   }
   static void destruct_vectorlETGTextButtonmUgR(void *p) {
      typedef vector<TGTextButton*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<TGTextButton*>

namespace ROOT {
   static TClass *vectorlETGLabelmUgR_Dictionary();
   static void vectorlETGLabelmUgR_TClassManip(TClass*);
   static void *new_vectorlETGLabelmUgR(void *p = nullptr);
   static void *newArray_vectorlETGLabelmUgR(Long_t size, void *p);
   static void delete_vectorlETGLabelmUgR(void *p);
   static void deleteArray_vectorlETGLabelmUgR(void *p);
   static void destruct_vectorlETGLabelmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TGLabel*>*)
   {
      vector<TGLabel*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TGLabel*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TGLabel*>", -2, "vector", 389,
                  typeid(vector<TGLabel*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETGLabelmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TGLabel*>) );
      instance.SetNew(&new_vectorlETGLabelmUgR);
      instance.SetNewArray(&newArray_vectorlETGLabelmUgR);
      instance.SetDelete(&delete_vectorlETGLabelmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETGLabelmUgR);
      instance.SetDestructor(&destruct_vectorlETGLabelmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TGLabel*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<TGLabel*>","std::vector<TGLabel*, std::allocator<TGLabel*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<TGLabel*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETGLabelmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<TGLabel*>*>(nullptr))->GetClass();
      vectorlETGLabelmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETGLabelmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETGLabelmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGLabel*> : new vector<TGLabel*>;
   }
   static void *newArray_vectorlETGLabelmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGLabel*>[nElements] : new vector<TGLabel*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETGLabelmUgR(void *p) {
      delete (static_cast<vector<TGLabel*>*>(p));
   }
   static void deleteArray_vectorlETGLabelmUgR(void *p) {
      delete [] (static_cast<vector<TGLabel*>*>(p));
   }
   static void destruct_vectorlETGLabelmUgR(void *p) {
      typedef vector<TGLabel*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<TGLabel*>

namespace ROOT {
   static TClass *vectorlETGHorizontalFramemUgR_Dictionary();
   static void vectorlETGHorizontalFramemUgR_TClassManip(TClass*);
   static void *new_vectorlETGHorizontalFramemUgR(void *p = nullptr);
   static void *newArray_vectorlETGHorizontalFramemUgR(Long_t size, void *p);
   static void delete_vectorlETGHorizontalFramemUgR(void *p);
   static void deleteArray_vectorlETGHorizontalFramemUgR(void *p);
   static void destruct_vectorlETGHorizontalFramemUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TGHorizontalFrame*>*)
   {
      vector<TGHorizontalFrame*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TGHorizontalFrame*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TGHorizontalFrame*>", -2, "vector", 389,
                  typeid(vector<TGHorizontalFrame*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETGHorizontalFramemUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TGHorizontalFrame*>) );
      instance.SetNew(&new_vectorlETGHorizontalFramemUgR);
      instance.SetNewArray(&newArray_vectorlETGHorizontalFramemUgR);
      instance.SetDelete(&delete_vectorlETGHorizontalFramemUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETGHorizontalFramemUgR);
      instance.SetDestructor(&destruct_vectorlETGHorizontalFramemUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TGHorizontalFrame*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<TGHorizontalFrame*>","std::vector<TGHorizontalFrame*, std::allocator<TGHorizontalFrame*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<TGHorizontalFrame*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETGHorizontalFramemUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<TGHorizontalFrame*>*>(nullptr))->GetClass();
      vectorlETGHorizontalFramemUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETGHorizontalFramemUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETGHorizontalFramemUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGHorizontalFrame*> : new vector<TGHorizontalFrame*>;
   }
   static void *newArray_vectorlETGHorizontalFramemUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGHorizontalFrame*>[nElements] : new vector<TGHorizontalFrame*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETGHorizontalFramemUgR(void *p) {
      delete (static_cast<vector<TGHorizontalFrame*>*>(p));
   }
   static void deleteArray_vectorlETGHorizontalFramemUgR(void *p) {
      delete [] (static_cast<vector<TGHorizontalFrame*>*>(p));
   }
   static void destruct_vectorlETGHorizontalFramemUgR(void *p) {
      typedef vector<TGHorizontalFrame*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<TGHorizontalFrame*>

namespace ROOT {
   static TClass *vectorlETGCheckButtonmUgR_Dictionary();
   static void vectorlETGCheckButtonmUgR_TClassManip(TClass*);
   static void *new_vectorlETGCheckButtonmUgR(void *p = nullptr);
   static void *newArray_vectorlETGCheckButtonmUgR(Long_t size, void *p);
   static void delete_vectorlETGCheckButtonmUgR(void *p);
   static void deleteArray_vectorlETGCheckButtonmUgR(void *p);
   static void destruct_vectorlETGCheckButtonmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TGCheckButton*>*)
   {
      vector<TGCheckButton*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TGCheckButton*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TGCheckButton*>", -2, "vector", 389,
                  typeid(vector<TGCheckButton*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETGCheckButtonmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TGCheckButton*>) );
      instance.SetNew(&new_vectorlETGCheckButtonmUgR);
      instance.SetNewArray(&newArray_vectorlETGCheckButtonmUgR);
      instance.SetDelete(&delete_vectorlETGCheckButtonmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETGCheckButtonmUgR);
      instance.SetDestructor(&destruct_vectorlETGCheckButtonmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TGCheckButton*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<TGCheckButton*>","std::vector<TGCheckButton*, std::allocator<TGCheckButton*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<TGCheckButton*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETGCheckButtonmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<TGCheckButton*>*>(nullptr))->GetClass();
      vectorlETGCheckButtonmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETGCheckButtonmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETGCheckButtonmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGCheckButton*> : new vector<TGCheckButton*>;
   }
   static void *newArray_vectorlETGCheckButtonmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGCheckButton*>[nElements] : new vector<TGCheckButton*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETGCheckButtonmUgR(void *p) {
      delete (static_cast<vector<TGCheckButton*>*>(p));
   }
   static void deleteArray_vectorlETGCheckButtonmUgR(void *p) {
      delete [] (static_cast<vector<TGCheckButton*>*>(p));
   }
   static void destruct_vectorlETGCheckButtonmUgR(void *p) {
      typedef vector<TGCheckButton*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<TGCheckButton*>

namespace ROOT {
   static TClass *vectorlETGButtonmUgR_Dictionary();
   static void vectorlETGButtonmUgR_TClassManip(TClass*);
   static void *new_vectorlETGButtonmUgR(void *p = nullptr);
   static void *newArray_vectorlETGButtonmUgR(Long_t size, void *p);
   static void delete_vectorlETGButtonmUgR(void *p);
   static void deleteArray_vectorlETGButtonmUgR(void *p);
   static void destruct_vectorlETGButtonmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TGButton*>*)
   {
      vector<TGButton*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TGButton*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TGButton*>", -2, "vector", 389,
                  typeid(vector<TGButton*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETGButtonmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TGButton*>) );
      instance.SetNew(&new_vectorlETGButtonmUgR);
      instance.SetNewArray(&newArray_vectorlETGButtonmUgR);
      instance.SetDelete(&delete_vectorlETGButtonmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETGButtonmUgR);
      instance.SetDestructor(&destruct_vectorlETGButtonmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TGButton*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<TGButton*>","std::vector<TGButton*, std::allocator<TGButton*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<TGButton*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETGButtonmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<TGButton*>*>(nullptr))->GetClass();
      vectorlETGButtonmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETGButtonmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETGButtonmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGButton*> : new vector<TGButton*>;
   }
   static void *newArray_vectorlETGButtonmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TGButton*>[nElements] : new vector<TGButton*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETGButtonmUgR(void *p) {
      delete (static_cast<vector<TGButton*>*>(p));
   }
   static void deleteArray_vectorlETGButtonmUgR(void *p) {
      delete [] (static_cast<vector<TGButton*>*>(p));
   }
   static void destruct_vectorlETGButtonmUgR(void *p) {
      typedef vector<TGButton*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<TGButton*>

namespace ROOT {
   static TClass *vectorlETCanvasmUgR_Dictionary();
   static void vectorlETCanvasmUgR_TClassManip(TClass*);
   static void *new_vectorlETCanvasmUgR(void *p = nullptr);
   static void *newArray_vectorlETCanvasmUgR(Long_t size, void *p);
   static void delete_vectorlETCanvasmUgR(void *p);
   static void deleteArray_vectorlETCanvasmUgR(void *p);
   static void destruct_vectorlETCanvasmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TCanvas*>*)
   {
      vector<TCanvas*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TCanvas*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TCanvas*>", -2, "vector", 389,
                  typeid(vector<TCanvas*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETCanvasmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TCanvas*>) );
      instance.SetNew(&new_vectorlETCanvasmUgR);
      instance.SetNewArray(&newArray_vectorlETCanvasmUgR);
      instance.SetDelete(&delete_vectorlETCanvasmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETCanvasmUgR);
      instance.SetDestructor(&destruct_vectorlETCanvasmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TCanvas*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<TCanvas*>","std::vector<TCanvas*, std::allocator<TCanvas*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<TCanvas*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETCanvasmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<TCanvas*>*>(nullptr))->GetClass();
      vectorlETCanvasmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETCanvasmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETCanvasmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TCanvas*> : new vector<TCanvas*>;
   }
   static void *newArray_vectorlETCanvasmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TCanvas*>[nElements] : new vector<TCanvas*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETCanvasmUgR(void *p) {
      delete (static_cast<vector<TCanvas*>*>(p));
   }
   static void deleteArray_vectorlETCanvasmUgR(void *p) {
      delete [] (static_cast<vector<TCanvas*>*>(p));
   }
   static void destruct_vectorlETCanvasmUgR(void *p) {
      typedef vector<TCanvas*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<TCanvas*>

namespace ROOT {
   static TClass *vectorlEFullFitHoldermUgR_Dictionary();
   static void vectorlEFullFitHoldermUgR_TClassManip(TClass*);
   static void *new_vectorlEFullFitHoldermUgR(void *p = nullptr);
   static void *newArray_vectorlEFullFitHoldermUgR(Long_t size, void *p);
   static void delete_vectorlEFullFitHoldermUgR(void *p);
   static void deleteArray_vectorlEFullFitHoldermUgR(void *p);
   static void destruct_vectorlEFullFitHoldermUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<FullFitHolder*>*)
   {
      vector<FullFitHolder*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<FullFitHolder*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<FullFitHolder*>", -2, "vector", 389,
                  typeid(vector<FullFitHolder*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEFullFitHoldermUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<FullFitHolder*>) );
      instance.SetNew(&new_vectorlEFullFitHoldermUgR);
      instance.SetNewArray(&newArray_vectorlEFullFitHoldermUgR);
      instance.SetDelete(&delete_vectorlEFullFitHoldermUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEFullFitHoldermUgR);
      instance.SetDestructor(&destruct_vectorlEFullFitHoldermUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<FullFitHolder*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<FullFitHolder*>","std::vector<FullFitHolder*, std::allocator<FullFitHolder*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<FullFitHolder*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEFullFitHoldermUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<FullFitHolder*>*>(nullptr))->GetClass();
      vectorlEFullFitHoldermUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEFullFitHoldermUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEFullFitHoldermUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<FullFitHolder*> : new vector<FullFitHolder*>;
   }
   static void *newArray_vectorlEFullFitHoldermUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<FullFitHolder*>[nElements] : new vector<FullFitHolder*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEFullFitHoldermUgR(void *p) {
      delete (static_cast<vector<FullFitHolder*>*>(p));
   }
   static void deleteArray_vectorlEFullFitHoldermUgR(void *p) {
      delete [] (static_cast<vector<FullFitHolder*>*>(p));
   }
   static void destruct_vectorlEFullFitHoldermUgR(void *p) {
      typedef vector<FullFitHolder*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<FullFitHolder*>

namespace {
  void TriggerDictionaryInitialization_DictOutput_Impl() {
    static const char* headers[] = {
"include/j_clipboard_parse.h",
"include/j_effpeaks.h",
"include/j_elements.h",
"include/j_env.h",
"include/j_extra_guitools.h",
"include/j_fitholder.h",
"include/j_fitting.h",
"include/j_gate_subtract.h",
"include/j_gating_frame.h",
"include/j_gating_result_frame.h",
"include/j_gating_select_frame.h",
"include/j_gating_tool.h",
"include/j_gpad_tools.h",
"include/j_hist_formatting.h",
"include/j_new_gating_tool.h",
"include/j_spectool.h",
"include/j_treetup_tool.h",
"include/j_ultrafit_env.h",
"include/j_ultrapeakfit.h",
"include/j_ultrapeak.h",
"include/j_utility.h",
"include/j_X11paste.h",
nullptr
    };
    static const char* includePaths[] = {
"/home/js/jRootAnalysisTools/include",
"/opt/root_v6.28.06.Linux-ubuntu22-x86_64-gcc11.4/include/",
"/home/js/jRootAnalysisTools/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "DictOutput dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
template <typename T> class __attribute__((annotate("$clingAutoload$j_utility.h")))  __attribute__((annotate("$clingAutoload$include/j_effpeaks.h")))  TransientBitsClass;

class __attribute__((annotate("$clingAutoload$j_utility.h")))  __attribute__((annotate("$clingAutoload$include/j_effpeaks.h")))  TH1Efficiency;
class __attribute__((annotate("$clingAutoload$j_utility.h")))  __attribute__((annotate("$clingAutoload$include/j_effpeaks.h")))  TH2Efficiency;
class __attribute__((annotate("$clingAutoload$j_utility.h")))  __attribute__((annotate("$clingAutoload$include/j_effpeaks.h")))  jRootMultiPurposePopup;
class __attribute__((annotate("$clingAutoload$j_fitholder.h")))  __attribute__((annotate("$clingAutoload$include/j_effpeaks.h")))  FullFitHolder;
struct __attribute__((annotate("$clingAutoload$j_fitting.h")))  __attribute__((annotate("$clingAutoload$include/j_elements.h")))  jPeakDat;
class __attribute__((annotate("$clingAutoload$j_gpad_tools.h")))  __attribute__((annotate("$clingAutoload$include/j_elements.h")))  HistClickStop;
class __attribute__((annotate("$clingAutoload$j_gpad_tools.h")))  __attribute__((annotate("$clingAutoload$include/j_elements.h")))  jhistquestion;
class __attribute__((annotate("$clingAutoload$j_gate_subtract.h")))  __attribute__((annotate("$clingAutoload$include/j_elements.h")))  TH1ErrorAdj;
class __attribute__((annotate("$clingAutoload$include/j_elements.h")))  CCframe;
class __attribute__((annotate("$clingAutoload$include/j_elements.h")))  jHistCapButton;
class __attribute__((annotate("$clingAutoload$include/j_elements.h")))  jAddSubTool;
class __attribute__((annotate("$clingAutoload$include/j_elements.h")))  jDirList;
class __attribute__((annotate("$clingAutoload$j_ultrapeak.h")))  __attribute__((annotate("$clingAutoload$include/j_env.h")))  Ultrapeak;
class __attribute__((annotate("$clingAutoload$j_ultrapeak.h")))  __attribute__((annotate("$clingAutoload$include/j_env.h")))  UltrapeakArea;
class __attribute__((annotate("$clingAutoload$j_ultrapeak.h")))  __attribute__((annotate("$clingAutoload$include/j_env.h")))  UltrapeakFrac;
class __attribute__((annotate("$clingAutoload$j_ultrapeak.h")))  __attribute__((annotate("$clingAutoload$include/j_env.h")))  UltrapeakCentroid;
class __attribute__((annotate("$clingAutoload$j_ultrafit_env.h")))  __attribute__((annotate("$clingAutoload$include/j_env.h")))  UltraFitEnv;
class __attribute__((annotate("$clingAutoload$j_gating_frame.h")))  __attribute__((annotate("$clingAutoload$include/j_env.h")))  j_gating_frame;
class __attribute__((annotate("$clingAutoload$j_gating_tool.h")))  __attribute__((annotate("$clingAutoload$include/j_env.h")))  jgating_tool;
class __attribute__((annotate("$clingAutoload$j_gating_tool.h")))  __attribute__((annotate("$clingAutoload$include/j_env.h")))  minimalist_th3slice;
class __attribute__((annotate("$clingAutoload$j_spectool.h")))  __attribute__((annotate("$clingAutoload$include/j_env.h")))  jSpecTool;
class __attribute__((annotate("$clingAutoload$include/j_env.h")))  jEnv;
class __attribute__((annotate("$clingAutoload$include/j_extra_guitools.h")))  jScale;
class __attribute__((annotate("$clingAutoload$include/j_extra_guitools.h")))  jEval;
class __attribute__((annotate("$clingAutoload$include/j_extra_guitools.h")))  jAngleAngel;
class __attribute__((annotate("$clingAutoload$include/j_extra_guitools.h")))  j2DPeakFit;
class __attribute__((annotate("$clingAutoload$include/j_extra_guitools.h")))  jIntegrator;
class __attribute__((annotate("$clingAutoload$include/j_extra_guitools.h")))  jCompCanvas;
class __attribute__((annotate("$clingAutoload$include/j_gating_result_frame.h")))  j_gating_result_frame;
class __attribute__((annotate("$clingAutoload$include/j_gating_select_frame.h")))  j_gating_select_frame;
class __attribute__((annotate("$clingAutoload$include/j_gating_select_frame.h")))  j_gating_select_frame_tester;
class __attribute__((annotate("$clingAutoload$include/j_treetup_tool.h")))  jRootTreeCube;
typedef struct jPeakDat jPeakDat __attribute__((annotate("$clingAutoload$j_fitting.h")))  __attribute__((annotate("$clingAutoload$include/j_elements.h"))) ;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "DictOutput dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "include/j_clipboard_parse.h"
#include "include/j_effpeaks.h"
#include "include/j_elements.h"
#include "include/j_env.h"
#include "include/j_extra_guitools.h"
#include "include/j_fitholder.h"
#include "include/j_fitting.h"
#include "include/j_gate_subtract.h"
#include "include/j_gating_frame.h"
#include "include/j_gating_result_frame.h"
#include "include/j_gating_select_frame.h"
#include "include/j_gating_tool.h"
#include "include/j_gpad_tools.h"
#include "include/j_hist_formatting.h"
#include "include/j_new_gating_tool.h"
#include "include/j_spectool.h"
#include "include/j_treetup_tool.h"
#include "include/j_ultrafit_env.h"
#include "include/j_ultrapeakfit.h"
#include "include/j_ultrapeak.h"
#include "include/j_utility.h"
#include "include/j_X11paste.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"", payloadCode, "@",
"AddPeakLabel", payloadCode, "@",
"AnalyticalFullCovError", payloadCode, "@",
"AnyParAtLimit", payloadCode, "@",
"AxisYWhiteBox", payloadCode, "@",
"CCframe", payloadCode, "@",
"CCframe::fgIsA", payloadCode, "@",
"CanvasNegative", payloadCode, "@",
"CanvasNegativeFull", payloadCode, "@",
"ClickPeakDrawConnect", payloadCode, "@",
"ConnectPeakClickerCanvas", payloadCode, "@",
"CopyBufferHistOrGraph", payloadCode, "@",
"CovDiag", payloadCode, "@",
"DecGaus", payloadCode, "@",
"DecGausArea", payloadCode, "@",
"DecGausCFD", payloadCode, "@",
"DecGausMaxX", payloadCode, "@",
"DecGausStep", payloadCode, "@",
"DecMaxCorrPow", payloadCode, "@",
"DrawCanvas", payloadCode, "@",
"DrawCopyCanvas", payloadCode, "@",
"DrawCopyGraphOpt", payloadCode, "@",
"DrawCopyHistOpt", payloadCode, "@",
"DrawCopyPeakClickerCanvas", payloadCode, "@",
"DrawFromClipboard", payloadCode, "@",
"DrawGraphOpt", payloadCode, "@",
"DrawHformat", payloadCode, "@",
"DrawHistOpt", payloadCode, "@",
"DrawPeakClickerCanvas", payloadCode, "@",
"DrawSharedTitle", payloadCode, "@",
"ExtractAsymError", payloadCode, "@",
"ExtractAsymErrorTest", payloadCode, "@",
"ExtractError", payloadCode, "@",
"ExtractErrorTest", payloadCode, "@",
"ExtreemRebin", payloadCode, "@",
"FindBinRangeMax", payloadCode, "@",
"FindBinRangeMaxD", payloadCode, "@",
"FindLocalMax", payloadCode, "@",
"FitPositionOptimisation", payloadCode, "@",
"FitUltra", payloadCode, "@",
"FixLimitPushers", payloadCode, "@",
"FullFitHolder", payloadCode, "@",
"FullFitHolder::fgIsA", payloadCode, "@",
"GetHistClickVal", payloadCode, "@",
"GosiaAdhoc", payloadCode, "@",
"GosiaHigh", payloadCode, "@",
"GosiaWoodsac", payloadCode, "@",
"GraphNegative", payloadCode, "@",
"HType", payloadCode, "@",
"HistClickStop", payloadCode, "@",
"HistDrawnXRange", payloadCode, "@",
"HistSaveAs", payloadCode, "@",
"HistoClassDetect", payloadCode, "@",
"HistogramNegative", payloadCode, "@",
"IsParFixed", payloadCode, "@",
"MegaEffAuto", payloadCode, "@",
"MegaEffAutoFH", payloadCode, "@",
"PadNDCtoUser", payloadCode, "@",
"ParAtLimit", payloadCode, "@",
"PostUpdateCanvasUpdateCall", payloadCode, "@",
"QuickReTexAxis", payloadCode, "@",
"QuickSingleGausAutoFit", payloadCode, "@",
"QuickSingleGausAutoFitE", payloadCode, "@",
"QuickSingleGausAutoFitEE", payloadCode, "@",
"RangeChangeBisectCanvasBoth", payloadCode, "@",
"ReMargin", payloadCode, "@",
"ReTexAxisLab", payloadCode, "@",
"ReTexAxisTitle", payloadCode, "@",
"ReadFirstHist", payloadCode, "@",
"ReadFirstObject", payloadCode, "@",
"ReadX11CopyBufferAsText", payloadCode, "@",
"RootFileLoad", payloadCode, "@",
"ScientificErrorPrint", payloadCode, "@",
"SetGlobalAskWindowName", payloadCode, "@",
"SetGlobalNegative", payloadCode, "@",
"SmoothOffBack", payloadCode, "@",
"SortFullFitByRedChi", payloadCode, "@",
"SortFullFitByVal", payloadCode, "@",
"Sqrt2Pi", payloadCode, "@",
"TH1Efficiency", payloadCode, "@",
"TH1Efficiency::fgIsA", payloadCode, "@",
"TH1ErrorAdj", payloadCode, "@",
"TH1ErrorAdj::fgIsA", payloadCode, "@",
"TH2Efficiency", payloadCode, "@",
"TH2Efficiency::fgIsA", payloadCode, "@",
"TH3axisreseter", payloadCode, "@",
"ToolTipHide", payloadCode, "@",
"TransientBitsClass<long>", payloadCode, "@",
"TrueCentroid", payloadCode, "@",
"UltraFitEnv", payloadCode, "@",
"UltraFitEnv::UltraFitEnv_iterator", payloadCode, "@",
"UltraFitEnv::fgIsA", payloadCode, "@",
"Ultrapeak", payloadCode, "@",
"Ultrapeak::DecayCorrPow", payloadCode, "@",
"Ultrapeak::DecayXR10", payloadCode, "@",
"Ultrapeak::UBits", payloadCode, "@",
"Ultrapeak::Ultra_iterator", payloadCode, "@",
"Ultrapeak::VBI", payloadCode, "@",
"Ultrapeak::VChi", payloadCode, "@",
"Ultrapeak::VN", payloadCode, "@",
"Ultrapeak::VOff", payloadCode, "@",
"Ultrapeak::cBackType0", payloadCode, "@",
"Ultrapeak::cBackType0s", payloadCode, "@",
"Ultrapeak::cBackType1", payloadCode, "@",
"Ultrapeak::cBackType1f", payloadCode, "@",
"Ultrapeak::cBackType1s", payloadCode, "@",
"Ultrapeak::cBackType2", payloadCode, "@",
"Ultrapeak::cBackType2s", payloadCode, "@",
"Ultrapeak::cBackTypeN", payloadCode, "@",
"Ultrapeak::fgIsA", payloadCode, "@",
"Ultrapeak::gMaxPeaks", payloadCode, "@",
"Ultrapeak::gUltraOffsetOrPol2", payloadCode, "@",
"Ultrapeak::gUltraPol0", payloadCode, "@",
"Ultrapeak::gUltraPol1", payloadCode, "@",
"Ultrapeak::gUltraStep", payloadCode, "@",
"Ultrapeak::gUltraTGHR", payloadCode, "@",
"Ultrapeak::gUltraTGWR", payloadCode, "@",
"UltrapeakArea", payloadCode, "@",
"UltrapeakCentroid", payloadCode, "@",
"UltrapeakFrac", payloadCode, "@",
"UniGaus", payloadCode, "@",
"UniGausArea", payloadCode, "@",
"UniGausCFD", payloadCode, "@",
"UniGausStep", payloadCode, "@",
"UserQuickSingleGausAutoFit", payloadCode, "@",
"UserQuickSingleGausAutoFitE", payloadCode, "@",
"UserQuickSingleGausAutoFitEE", payloadCode, "@",
"ZeroBinsFitFix", payloadCode, "@",
"auto_radeff_scaled", payloadCode, "@",
"axislab", payloadCode, "@",
"axislabelkev", payloadCode, "@",
"bins_smooth", payloadCode, "@",
"bins_var", payloadCode, "@",
"draw_corrected_titles", payloadCode, "@",
"draw_electron_gamma", payloadCode, "@",
"draw_hist_bisect", payloadCode, "@",
"draw_hist_inset", payloadCode, "@",
"gGlobalAskWindowName", payloadCode, "@",
"gGlobalBackColor", payloadCode, "@",
"gGlobalDrawMenuBars", payloadCode, "@",
"gGlobalForceMinuitOldMinimiser", payloadCode, "@",
"gGlobalForeColor", payloadCode, "@",
"gGlobalMainFont", payloadCode, "@",
"gGlobalNegativeDraw", payloadCode, "@",
"gPeakBackA", payloadCode, "@",
"gPeakBackB", payloadCode, "@",
"gPeakBackC", payloadCode, "@",
"gPeakBackD", payloadCode, "@",
"gPeakDecay", payloadCode, "@",
"gPeakNC", payloadCode, "@",
"gPeakNH", payloadCode, "@",
"gPeakSharing", payloadCode, "@",
"gPeakSigma", payloadCode, "@",
"gPeakSigmaB", payloadCode, "@",
"gPeakSigmaC", payloadCode, "@",
"hformat", payloadCode, "@",
"higher_jd", payloadCode, "@",
"hist_capture", payloadCode, "@",
"hist_gater", payloadCode, "@",
"hist_gater_bin", payloadCode, "@",
"hist_proj", payloadCode, "@",
"invert", payloadCode, "@",
"j2DPeakFit", payloadCode, "@",
"j2DPeakFit::fgIsA", payloadCode, "@",
"jAddSubTool", payloadCode, "@",
"jAddSubTool::SumNameItt", payloadCode, "@",
"jAddSubTool::fgIsA", payloadCode, "@",
"jAngleAngel", payloadCode, "@",
"jAngleAngel::fgIsA", payloadCode, "@",
"jCompCanvas", payloadCode, "@",
"jCompCanvas::ColBase", payloadCode, "@",
"jCompCanvas::fgIsA", payloadCode, "@",
"jDirList", payloadCode, "@",
"jDirList::fgIsA", payloadCode, "@",
"jEnv", payloadCode, "@",
"jEnv::fgIsA", payloadCode, "@",
"jEval", payloadCode, "@",
"jEval::fgIsA", payloadCode, "@",
"jHistCapButton", payloadCode, "@",
"jHistCapButton::fgIsA", payloadCode, "@",
"jIntegrator", payloadCode, "@",
"jIntegrator::fgIsA", payloadCode, "@",
"jPeakDat", payloadCode, "@",
"jRootMultiPurposePopup", payloadCode, "@",
"jRootMultiPurposePopup::fgIsA", payloadCode, "@",
"jRootTreeCube", payloadCode, "@",
"jRootTreeCube::fgIsA", payloadCode, "@",
"jRootTreeCube::jRootTreeCube_iterator", payloadCode, "@",
"jScale", payloadCode, "@",
"jScale::fgIsA", payloadCode, "@",
"jSpecTool", payloadCode, "@",
"jSpecTool::BackOpt", payloadCode, "@",
"jSpecTool::fgIsA", payloadCode, "@",
"jSpecTool::spectool_iterator", payloadCode, "@",
"j_gating_frame", payloadCode, "@",
"j_gating_frame::fgIsA", payloadCode, "@",
"j_gating_result_frame", payloadCode, "@",
"j_gating_result_frame::fgIsA", payloadCode, "@",
"j_gating_select_frame", payloadCode, "@",
"j_gating_select_frame::fgIsA", payloadCode, "@",
"j_gating_select_frame_tester", payloadCode, "@",
"j_gating_select_frame_tester::fgIsA", payloadCode, "@",
"jgating_tool", payloadCode, "@",
"jgating_tool::fgIsA", payloadCode, "@",
"jgating_tool::jgating_tool_iterator", payloadCode, "@",
"jhistquestion", payloadCode, "@",
"jhistquestion::fgIsA", payloadCode, "@",
"jsigfig", payloadCode, "@",
"minimalist_th3slice", payloadCode, "@",
"minimalist_th3slice::fgIsA", payloadCode, "@",
"minimalist_th3slice::minimalist_th3slice_iterator", payloadCode, "@",
"obj_capture", payloadCode, "@",
"obj_remove", payloadCode, "@",
"obj_removeall", payloadCode, "@",
"preapre_canvas", payloadCode, "@",
"preapre_canvas_bisect", payloadCode, "@",
"preapre_canvas_inset", payloadCode, "@",
"prepare_gosiaA", payloadCode, "@",
"prepare_gosiaB", payloadCode, "@",
"prepare_stefeff", payloadCode, "@",
"rad_eff", payloadCode, "@",
"rad_eff_scaled", payloadCode, "@",
"radeff", payloadCode, "@",
"radeff_by_parts", payloadCode, "@",
"radeffscadef", payloadCode, "@",
"scaled_addition", payloadCode, "@",
"scaled_back_subtract", payloadCode, "@",
"scaleradeff", payloadCode, "@",
"stefeff", payloadCode, "@",
"stefeffwonky", payloadCode, "@",
"swap_jd", payloadCode, "@",
"transpose_axis", payloadCode, "@",
"transpose_bins", payloadCode, "@",
"vector_d_sort", payloadCode, "@",
"vector_order_gen", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("DictOutput",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_DictOutput_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_DictOutput_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_DictOutput() {
  TriggerDictionaryInitialization_DictOutput_Impl();
}
