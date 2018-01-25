// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME bindIDictOutput

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
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

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "include/james_env.h"
#include "include/james_gating_tool.h"
#include "include/james_spectool.h"
#include "include/james_utility.h"
#include "include/james_gating_frame.h"
#include "include/james_effpeaks.h"
#include "include/james_gpad_tools.h"
#include "include/james_fitholder.h"
#include "include/james_hist_formatting.h"
#include "include/james_gate_subtract.h"
#include "include/james_fitting.h"
#include "include/james_ultrafit_env.h"
#include "include/james_ultrapeak.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *TransientBitsClasslElonggR_Dictionary();
   static void TransientBitsClasslElonggR_TClassManip(TClass*);
   static void *new_TransientBitsClasslElonggR(void *p = 0);
   static void *newArray_TransientBitsClasslElonggR(Long_t size, void *p);
   static void delete_TransientBitsClasslElonggR(void *p);
   static void deleteArray_TransientBitsClasslElonggR(void *p);
   static void destruct_TransientBitsClasslElonggR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TransientBitsClass<long>*)
   {
      ::TransientBitsClass<long> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TransientBitsClass<long>));
      static ::ROOT::TGenericClassInfo 
         instance("TransientBitsClass<long>", "james_utility.h", 93,
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
      return GenerateInitInstanceLocal((::TransientBitsClass<long>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TransientBitsClass<long>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TransientBitsClasslElonggR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TransientBitsClass<long>*)0x0)->GetClass();
      TransientBitsClasslElonggR_TClassManip(theClass);
   return theClass;
   }

   static void TransientBitsClasslElonggR_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/james_utility.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *HistClickStop_Dictionary();
   static void HistClickStop_TClassManip(TClass*);
   static void *new_HistClickStop(void *p = 0);
   static void *newArray_HistClickStop(Long_t size, void *p);
   static void delete_HistClickStop(void *p);
   static void deleteArray_HistClickStop(void *p);
   static void destruct_HistClickStop(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HistClickStop*)
   {
      ::HistClickStop *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::HistClickStop));
      static ::ROOT::TGenericClassInfo 
         instance("HistClickStop", "james_gpad_tools.h", 61,
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
      return GenerateInitInstanceLocal((::HistClickStop*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::HistClickStop*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *HistClickStop_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::HistClickStop*)0x0)->GetClass();
      HistClickStop_TClassManip(theClass);
   return theClass;
   }

   static void HistClickStop_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/james_gpad_tools.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_jhistquestion(void *p = 0);
   static void *newArray_jhistquestion(Long_t size, void *p);
   static void delete_jhistquestion(void *p);
   static void deleteArray_jhistquestion(void *p);
   static void destruct_jhistquestion(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jhistquestion*)
   {
      ::jhistquestion *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jhistquestion >(0);
      static ::ROOT::TGenericClassInfo 
         instance("jhistquestion", ::jhistquestion::Class_Version(), "james_gpad_tools.h", 108,
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
      return GenerateInitInstanceLocal((::jhistquestion*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::jhistquestion*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FullFitHolder(void *p = 0);
   static void *newArray_FullFitHolder(Long_t size, void *p);
   static void delete_FullFitHolder(void *p);
   static void deleteArray_FullFitHolder(void *p);
   static void destruct_FullFitHolder(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FullFitHolder*)
   {
      ::FullFitHolder *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FullFitHolder >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FullFitHolder", ::FullFitHolder::Class_Version(), "james_fitholder.h", 40,
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
      return GenerateInitInstanceLocal((::FullFitHolder*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::FullFitHolder*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
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
      ::jPeakDat *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::jPeakDat));
      static ::ROOT::TGenericClassInfo 
         instance("jPeakDat", "james_fitting.h", 58,
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
      return GenerateInitInstanceLocal((::jPeakDat*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::jPeakDat*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *jPeakDat_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::jPeakDat*)0x0)->GetClass();
      jPeakDat_TClassManip(theClass);
   return theClass;
   }

   static void jPeakDat_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/james_fitting.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Ultrapeak_Dictionary();
   static void Ultrapeak_TClassManip(TClass*);
   static void *new_Ultrapeak(void *p = 0);
   static void *newArray_Ultrapeak(Long_t size, void *p);
   static void delete_Ultrapeak(void *p);
   static void deleteArray_Ultrapeak(void *p);
   static void destruct_Ultrapeak(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Ultrapeak*)
   {
      ::Ultrapeak *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Ultrapeak));
      static ::ROOT::TGenericClassInfo 
         instance("Ultrapeak", "james_ultrapeak.h", 193,
                  typeid(::Ultrapeak), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &Ultrapeak_Dictionary, isa_proxy, 4,
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
      return GenerateInitInstanceLocal((::Ultrapeak*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Ultrapeak*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Ultrapeak_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Ultrapeak*)0x0)->GetClass();
      Ultrapeak_TClassManip(theClass);
   return theClass;
   }

   static void Ultrapeak_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/james_ultrapeak.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *UltrapeakArea_Dictionary();
   static void UltrapeakArea_TClassManip(TClass*);
   static void *new_UltrapeakArea(void *p = 0);
   static void *newArray_UltrapeakArea(Long_t size, void *p);
   static void delete_UltrapeakArea(void *p);
   static void deleteArray_UltrapeakArea(void *p);
   static void destruct_UltrapeakArea(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::UltrapeakArea*)
   {
      ::UltrapeakArea *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::UltrapeakArea));
      static ::ROOT::TGenericClassInfo 
         instance("UltrapeakArea", "james_ultrapeak.h", 360,
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
      return GenerateInitInstanceLocal((::UltrapeakArea*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::UltrapeakArea*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *UltrapeakArea_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::UltrapeakArea*)0x0)->GetClass();
      UltrapeakArea_TClassManip(theClass);
   return theClass;
   }

   static void UltrapeakArea_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/james_ultrapeak.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *UltrapeakFrac_Dictionary();
   static void UltrapeakFrac_TClassManip(TClass*);
   static void *new_UltrapeakFrac(void *p = 0);
   static void *newArray_UltrapeakFrac(Long_t size, void *p);
   static void delete_UltrapeakFrac(void *p);
   static void deleteArray_UltrapeakFrac(void *p);
   static void destruct_UltrapeakFrac(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::UltrapeakFrac*)
   {
      ::UltrapeakFrac *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::UltrapeakFrac));
      static ::ROOT::TGenericClassInfo 
         instance("UltrapeakFrac", "james_ultrapeak.h", 387,
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
      return GenerateInitInstanceLocal((::UltrapeakFrac*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::UltrapeakFrac*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *UltrapeakFrac_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::UltrapeakFrac*)0x0)->GetClass();
      UltrapeakFrac_TClassManip(theClass);
   return theClass;
   }

   static void UltrapeakFrac_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("file_name","include/james_ultrapeak.h");
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_UltraFitEnv(void *p = 0);
   static void *newArray_UltraFitEnv(Long_t size, void *p);
   static void delete_UltraFitEnv(void *p);
   static void deleteArray_UltraFitEnv(void *p);
   static void destruct_UltraFitEnv(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::UltraFitEnv*)
   {
      ::UltraFitEnv *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::UltraFitEnv >(0);
      static ::ROOT::TGenericClassInfo 
         instance("UltraFitEnv", ::UltraFitEnv::Class_Version(), "james_ultrafit_env.h", 72,
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
      return GenerateInitInstanceLocal((::UltraFitEnv*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::UltraFitEnv*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TH1ErrorAdj(void *p = 0);
   static void *newArray_TH1ErrorAdj(Long_t size, void *p);
   static void delete_TH1ErrorAdj(void *p);
   static void deleteArray_TH1ErrorAdj(void *p);
   static void destruct_TH1ErrorAdj(void *p);
   static void directoryAutoAdd_TH1ErrorAdj(void *obj, TDirectory *dir);
   static Long64_t merge_TH1ErrorAdj(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TH1ErrorAdj*)
   {
      ::TH1ErrorAdj *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TH1ErrorAdj >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TH1ErrorAdj", ::TH1ErrorAdj::Class_Version(), "james_gate_subtract.h", 84,
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
      return GenerateInitInstanceLocal((::TH1ErrorAdj*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TH1ErrorAdj*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_j_gating_frame(void *p = 0);
   static void *newArray_j_gating_frame(Long_t size, void *p);
   static void delete_j_gating_frame(void *p);
   static void deleteArray_j_gating_frame(void *p);
   static void destruct_j_gating_frame(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::j_gating_frame*)
   {
      ::j_gating_frame *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::j_gating_frame >(0);
      static ::ROOT::TGenericClassInfo 
         instance("j_gating_frame", ::j_gating_frame::Class_Version(), "james_gating_frame.h", 60,
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
      return GenerateInitInstanceLocal((::j_gating_frame*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::j_gating_frame*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_jgating_tool(void *p = 0);
   static void *newArray_jgating_tool(Long_t size, void *p);
   static void delete_jgating_tool(void *p);
   static void deleteArray_jgating_tool(void *p);
   static void destruct_jgating_tool(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jgating_tool*)
   {
      ::jgating_tool *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jgating_tool >(0);
      static ::ROOT::TGenericClassInfo 
         instance("jgating_tool", ::jgating_tool::Class_Version(), "james_gating_tool.h", 42,
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
      return GenerateInitInstanceLocal((::jgating_tool*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::jgating_tool*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_minimalist_th3slice(void *p = 0);
   static void *newArray_minimalist_th3slice(Long_t size, void *p);
   static void delete_minimalist_th3slice(void *p);
   static void deleteArray_minimalist_th3slice(void *p);
   static void destruct_minimalist_th3slice(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::minimalist_th3slice*)
   {
      ::minimalist_th3slice *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::minimalist_th3slice >(0);
      static ::ROOT::TGenericClassInfo 
         instance("minimalist_th3slice", ::minimalist_th3slice::Class_Version(), "james_gating_tool.h", 103,
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
      return GenerateInitInstanceLocal((::minimalist_th3slice*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::minimalist_th3slice*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_jSpecTool(void *p = 0);
   static void *newArray_jSpecTool(Long_t size, void *p);
   static void delete_jSpecTool(void *p);
   static void deleteArray_jSpecTool(void *p);
   static void destruct_jSpecTool(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jSpecTool*)
   {
      ::jSpecTool *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jSpecTool >(0);
      static ::ROOT::TGenericClassInfo 
         instance("jSpecTool", ::jSpecTool::Class_Version(), "james_spectool.h", 42,
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
      return GenerateInitInstanceLocal((::jSpecTool*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::jSpecTool*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CCframe(void *p = 0);
   static void *newArray_CCframe(Long_t size, void *p);
   static void delete_CCframe(void *p);
   static void deleteArray_CCframe(void *p);
   static void destruct_CCframe(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CCframe*)
   {
      ::CCframe *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CCframe >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CCframe", ::CCframe::Class_Version(), "james_env.h", 42,
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
      return GenerateInitInstanceLocal((::CCframe*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::CCframe*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_jEnv(void *p = 0);
   static void *newArray_jEnv(Long_t size, void *p);
   static void delete_jEnv(void *p);
   static void deleteArray_jEnv(void *p);
   static void destruct_jEnv(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::jEnv*)
   {
      ::jEnv *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::jEnv >(0);
      static ::ROOT::TGenericClassInfo 
         instance("jEnv", ::jEnv::Class_Version(), "james_env.h", 66,
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
      return GenerateInitInstanceLocal((::jEnv*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::jEnv*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr jhistquestion::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *jhistquestion::Class_Name()
{
   return "jhistquestion";
}

//______________________________________________________________________________
const char *jhistquestion::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jhistquestion*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int jhistquestion::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jhistquestion*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jhistquestion::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jhistquestion*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jhistquestion::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jhistquestion*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FullFitHolder::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FullFitHolder::Class_Name()
{
   return "FullFitHolder";
}

//______________________________________________________________________________
const char *FullFitHolder::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FullFitHolder*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FullFitHolder::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FullFitHolder*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FullFitHolder::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FullFitHolder*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FullFitHolder::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FullFitHolder*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr UltraFitEnv::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *UltraFitEnv::Class_Name()
{
   return "UltraFitEnv";
}

//______________________________________________________________________________
const char *UltraFitEnv::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::UltraFitEnv*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int UltraFitEnv::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::UltraFitEnv*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *UltraFitEnv::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::UltraFitEnv*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *UltraFitEnv::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::UltraFitEnv*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TH1ErrorAdj::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TH1ErrorAdj::Class_Name()
{
   return "TH1ErrorAdj";
}

//______________________________________________________________________________
const char *TH1ErrorAdj::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH1ErrorAdj*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TH1ErrorAdj::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TH1ErrorAdj*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TH1ErrorAdj::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH1ErrorAdj*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TH1ErrorAdj::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TH1ErrorAdj*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr j_gating_frame::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *j_gating_frame::Class_Name()
{
   return "j_gating_frame";
}

//______________________________________________________________________________
const char *j_gating_frame::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::j_gating_frame*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int j_gating_frame::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::j_gating_frame*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *j_gating_frame::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::j_gating_frame*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *j_gating_frame::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::j_gating_frame*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jgating_tool::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *jgating_tool::Class_Name()
{
   return "jgating_tool";
}

//______________________________________________________________________________
const char *jgating_tool::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jgating_tool*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int jgating_tool::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jgating_tool*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jgating_tool::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jgating_tool*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jgating_tool::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jgating_tool*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr minimalist_th3slice::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *minimalist_th3slice::Class_Name()
{
   return "minimalist_th3slice";
}

//______________________________________________________________________________
const char *minimalist_th3slice::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::minimalist_th3slice*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int minimalist_th3slice::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::minimalist_th3slice*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *minimalist_th3slice::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::minimalist_th3slice*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *minimalist_th3slice::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::minimalist_th3slice*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jSpecTool::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *jSpecTool::Class_Name()
{
   return "jSpecTool";
}

//______________________________________________________________________________
const char *jSpecTool::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jSpecTool*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int jSpecTool::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jSpecTool*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jSpecTool::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jSpecTool*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jSpecTool::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jSpecTool*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr CCframe::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *CCframe::Class_Name()
{
   return "CCframe";
}

//______________________________________________________________________________
const char *CCframe::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CCframe*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CCframe::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CCframe*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *CCframe::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CCframe*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CCframe::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CCframe*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr jEnv::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *jEnv::Class_Name()
{
   return "jEnv";
}

//______________________________________________________________________________
const char *jEnv::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jEnv*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int jEnv::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::jEnv*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *jEnv::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jEnv*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *jEnv::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::jEnv*)0x0)->GetClass(); }
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
      delete ((::TransientBitsClass<long>*)p);
   }
   static void deleteArray_TransientBitsClasslElonggR(void *p) {
      delete [] ((::TransientBitsClass<long>*)p);
   }
   static void destruct_TransientBitsClasslElonggR(void *p) {
      typedef ::TransientBitsClass<long> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TransientBitsClass<long>

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
      delete ((::HistClickStop*)p);
   }
   static void deleteArray_HistClickStop(void *p) {
      delete [] ((::HistClickStop*)p);
   }
   static void destruct_HistClickStop(void *p) {
      typedef ::HistClickStop current_t;
      ((current_t*)p)->~current_t();
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
      delete ((::jhistquestion*)p);
   }
   static void deleteArray_jhistquestion(void *p) {
      delete [] ((::jhistquestion*)p);
   }
   static void destruct_jhistquestion(void *p) {
      typedef ::jhistquestion current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::jhistquestion

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
      delete ((::FullFitHolder*)p);
   }
   static void deleteArray_FullFitHolder(void *p) {
      delete [] ((::FullFitHolder*)p);
   }
   static void destruct_FullFitHolder(void *p) {
      typedef ::FullFitHolder current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FullFitHolder

namespace ROOT {
   // Wrapper around operator delete
   static void delete_jPeakDat(void *p) {
      delete ((::jPeakDat*)p);
   }
   static void deleteArray_jPeakDat(void *p) {
      delete [] ((::jPeakDat*)p);
   }
   static void destruct_jPeakDat(void *p) {
      typedef ::jPeakDat current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::jPeakDat

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
      delete ((::Ultrapeak*)p);
   }
   static void deleteArray_Ultrapeak(void *p) {
      delete [] ((::Ultrapeak*)p);
   }
   static void destruct_Ultrapeak(void *p) {
      typedef ::Ultrapeak current_t;
      ((current_t*)p)->~current_t();
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
      delete ((::UltrapeakArea*)p);
   }
   static void deleteArray_UltrapeakArea(void *p) {
      delete [] ((::UltrapeakArea*)p);
   }
   static void destruct_UltrapeakArea(void *p) {
      typedef ::UltrapeakArea current_t;
      ((current_t*)p)->~current_t();
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
      delete ((::UltrapeakFrac*)p);
   }
   static void deleteArray_UltrapeakFrac(void *p) {
      delete [] ((::UltrapeakFrac*)p);
   }
   static void destruct_UltrapeakFrac(void *p) {
      typedef ::UltrapeakFrac current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::UltrapeakFrac

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
      delete ((::UltraFitEnv*)p);
   }
   static void deleteArray_UltraFitEnv(void *p) {
      delete [] ((::UltraFitEnv*)p);
   }
   static void destruct_UltraFitEnv(void *p) {
      typedef ::UltraFitEnv current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::UltraFitEnv

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
      delete ((::TH1ErrorAdj*)p);
   }
   static void deleteArray_TH1ErrorAdj(void *p) {
      delete [] ((::TH1ErrorAdj*)p);
   }
   static void destruct_TH1ErrorAdj(void *p) {
      typedef ::TH1ErrorAdj current_t;
      ((current_t*)p)->~current_t();
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
      delete ((::j_gating_frame*)p);
   }
   static void deleteArray_j_gating_frame(void *p) {
      delete [] ((::j_gating_frame*)p);
   }
   static void destruct_j_gating_frame(void *p) {
      typedef ::j_gating_frame current_t;
      ((current_t*)p)->~current_t();
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
      delete ((::jgating_tool*)p);
   }
   static void deleteArray_jgating_tool(void *p) {
      delete [] ((::jgating_tool*)p);
   }
   static void destruct_jgating_tool(void *p) {
      typedef ::jgating_tool current_t;
      ((current_t*)p)->~current_t();
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
      delete ((::minimalist_th3slice*)p);
   }
   static void deleteArray_minimalist_th3slice(void *p) {
      delete [] ((::minimalist_th3slice*)p);
   }
   static void destruct_minimalist_th3slice(void *p) {
      typedef ::minimalist_th3slice current_t;
      ((current_t*)p)->~current_t();
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
      delete ((::jSpecTool*)p);
   }
   static void deleteArray_jSpecTool(void *p) {
      delete [] ((::jSpecTool*)p);
   }
   static void destruct_jSpecTool(void *p) {
      typedef ::jSpecTool current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::jSpecTool

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
      delete ((::CCframe*)p);
   }
   static void deleteArray_CCframe(void *p) {
      delete [] ((::CCframe*)p);
   }
   static void destruct_CCframe(void *p) {
      typedef ::CCframe current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CCframe

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
      delete ((::jEnv*)p);
   }
   static void deleteArray_jEnv(void *p) {
      delete [] ((::jEnv*)p);
   }
   static void destruct_jEnv(void *p) {
      typedef ::jEnv current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::jEnv

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 210,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
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
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlETTextgR_Dictionary();
   static void vectorlETTextgR_TClassManip(TClass*);
   static void *new_vectorlETTextgR(void *p = 0);
   static void *newArray_vectorlETTextgR(Long_t size, void *p);
   static void delete_vectorlETTextgR(void *p);
   static void deleteArray_vectorlETTextgR(void *p);
   static void destruct_vectorlETTextgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TText>*)
   {
      vector<TText> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TText>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TText>", -2, "vector", 210,
                  typeid(vector<TText>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETTextgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TText>) );
      instance.SetNew(&new_vectorlETTextgR);
      instance.SetNewArray(&newArray_vectorlETTextgR);
      instance.SetDelete(&delete_vectorlETTextgR);
      instance.SetDeleteArray(&deleteArray_vectorlETTextgR);
      instance.SetDestructor(&destruct_vectorlETTextgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TText> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TText>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETTextgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TText>*)0x0)->GetClass();
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
      delete ((vector<TText>*)p);
   }
   static void deleteArray_vectorlETTextgR(void *p) {
      delete [] ((vector<TText>*)p);
   }
   static void destruct_vectorlETTextgR(void *p) {
      typedef vector<TText> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TText>

namespace ROOT {
   static TClass *vectorlETH1mUgR_Dictionary();
   static void vectorlETH1mUgR_TClassManip(TClass*);
   static void *new_vectorlETH1mUgR(void *p = 0);
   static void *newArray_vectorlETH1mUgR(Long_t size, void *p);
   static void delete_vectorlETH1mUgR(void *p);
   static void deleteArray_vectorlETH1mUgR(void *p);
   static void destruct_vectorlETH1mUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TH1*>*)
   {
      vector<TH1*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TH1*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TH1*>", -2, "vector", 210,
                  typeid(vector<TH1*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETH1mUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TH1*>) );
      instance.SetNew(&new_vectorlETH1mUgR);
      instance.SetNewArray(&newArray_vectorlETH1mUgR);
      instance.SetDelete(&delete_vectorlETH1mUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETH1mUgR);
      instance.SetDestructor(&destruct_vectorlETH1mUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TH1*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TH1*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETH1mUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TH1*>*)0x0)->GetClass();
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
      delete ((vector<TH1*>*)p);
   }
   static void deleteArray_vectorlETH1mUgR(void *p) {
      delete [] ((vector<TH1*>*)p);
   }
   static void destruct_vectorlETH1mUgR(void *p) {
      typedef vector<TH1*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TH1*>

namespace ROOT {
   static TClass *vectorlETGTextEntrymUgR_Dictionary();
   static void vectorlETGTextEntrymUgR_TClassManip(TClass*);
   static void *new_vectorlETGTextEntrymUgR(void *p = 0);
   static void *newArray_vectorlETGTextEntrymUgR(Long_t size, void *p);
   static void delete_vectorlETGTextEntrymUgR(void *p);
   static void deleteArray_vectorlETGTextEntrymUgR(void *p);
   static void destruct_vectorlETGTextEntrymUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TGTextEntry*>*)
   {
      vector<TGTextEntry*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TGTextEntry*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TGTextEntry*>", -2, "vector", 210,
                  typeid(vector<TGTextEntry*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETGTextEntrymUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TGTextEntry*>) );
      instance.SetNew(&new_vectorlETGTextEntrymUgR);
      instance.SetNewArray(&newArray_vectorlETGTextEntrymUgR);
      instance.SetDelete(&delete_vectorlETGTextEntrymUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETGTextEntrymUgR);
      instance.SetDestructor(&destruct_vectorlETGTextEntrymUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TGTextEntry*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TGTextEntry*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETGTextEntrymUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TGTextEntry*>*)0x0)->GetClass();
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
      delete ((vector<TGTextEntry*>*)p);
   }
   static void deleteArray_vectorlETGTextEntrymUgR(void *p) {
      delete [] ((vector<TGTextEntry*>*)p);
   }
   static void destruct_vectorlETGTextEntrymUgR(void *p) {
      typedef vector<TGTextEntry*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TGTextEntry*>

namespace ROOT {
   static TClass *vectorlETGTextButtonmUgR_Dictionary();
   static void vectorlETGTextButtonmUgR_TClassManip(TClass*);
   static void *new_vectorlETGTextButtonmUgR(void *p = 0);
   static void *newArray_vectorlETGTextButtonmUgR(Long_t size, void *p);
   static void delete_vectorlETGTextButtonmUgR(void *p);
   static void deleteArray_vectorlETGTextButtonmUgR(void *p);
   static void destruct_vectorlETGTextButtonmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TGTextButton*>*)
   {
      vector<TGTextButton*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TGTextButton*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TGTextButton*>", -2, "vector", 210,
                  typeid(vector<TGTextButton*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETGTextButtonmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TGTextButton*>) );
      instance.SetNew(&new_vectorlETGTextButtonmUgR);
      instance.SetNewArray(&newArray_vectorlETGTextButtonmUgR);
      instance.SetDelete(&delete_vectorlETGTextButtonmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETGTextButtonmUgR);
      instance.SetDestructor(&destruct_vectorlETGTextButtonmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TGTextButton*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TGTextButton*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETGTextButtonmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TGTextButton*>*)0x0)->GetClass();
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
      delete ((vector<TGTextButton*>*)p);
   }
   static void deleteArray_vectorlETGTextButtonmUgR(void *p) {
      delete [] ((vector<TGTextButton*>*)p);
   }
   static void destruct_vectorlETGTextButtonmUgR(void *p) {
      typedef vector<TGTextButton*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TGTextButton*>

namespace ROOT {
   static TClass *vectorlETGHorizontalFramemUgR_Dictionary();
   static void vectorlETGHorizontalFramemUgR_TClassManip(TClass*);
   static void *new_vectorlETGHorizontalFramemUgR(void *p = 0);
   static void *newArray_vectorlETGHorizontalFramemUgR(Long_t size, void *p);
   static void delete_vectorlETGHorizontalFramemUgR(void *p);
   static void deleteArray_vectorlETGHorizontalFramemUgR(void *p);
   static void destruct_vectorlETGHorizontalFramemUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TGHorizontalFrame*>*)
   {
      vector<TGHorizontalFrame*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TGHorizontalFrame*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TGHorizontalFrame*>", -2, "vector", 210,
                  typeid(vector<TGHorizontalFrame*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETGHorizontalFramemUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TGHorizontalFrame*>) );
      instance.SetNew(&new_vectorlETGHorizontalFramemUgR);
      instance.SetNewArray(&newArray_vectorlETGHorizontalFramemUgR);
      instance.SetDelete(&delete_vectorlETGHorizontalFramemUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETGHorizontalFramemUgR);
      instance.SetDestructor(&destruct_vectorlETGHorizontalFramemUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TGHorizontalFrame*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TGHorizontalFrame*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETGHorizontalFramemUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TGHorizontalFrame*>*)0x0)->GetClass();
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
      delete ((vector<TGHorizontalFrame*>*)p);
   }
   static void deleteArray_vectorlETGHorizontalFramemUgR(void *p) {
      delete [] ((vector<TGHorizontalFrame*>*)p);
   }
   static void destruct_vectorlETGHorizontalFramemUgR(void *p) {
      typedef vector<TGHorizontalFrame*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TGHorizontalFrame*>

namespace ROOT {
   static TClass *vectorlETGCheckButtonmUgR_Dictionary();
   static void vectorlETGCheckButtonmUgR_TClassManip(TClass*);
   static void *new_vectorlETGCheckButtonmUgR(void *p = 0);
   static void *newArray_vectorlETGCheckButtonmUgR(Long_t size, void *p);
   static void delete_vectorlETGCheckButtonmUgR(void *p);
   static void deleteArray_vectorlETGCheckButtonmUgR(void *p);
   static void destruct_vectorlETGCheckButtonmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TGCheckButton*>*)
   {
      vector<TGCheckButton*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TGCheckButton*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TGCheckButton*>", -2, "vector", 210,
                  typeid(vector<TGCheckButton*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETGCheckButtonmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TGCheckButton*>) );
      instance.SetNew(&new_vectorlETGCheckButtonmUgR);
      instance.SetNewArray(&newArray_vectorlETGCheckButtonmUgR);
      instance.SetDelete(&delete_vectorlETGCheckButtonmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETGCheckButtonmUgR);
      instance.SetDestructor(&destruct_vectorlETGCheckButtonmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TGCheckButton*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TGCheckButton*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETGCheckButtonmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TGCheckButton*>*)0x0)->GetClass();
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
      delete ((vector<TGCheckButton*>*)p);
   }
   static void deleteArray_vectorlETGCheckButtonmUgR(void *p) {
      delete [] ((vector<TGCheckButton*>*)p);
   }
   static void destruct_vectorlETGCheckButtonmUgR(void *p) {
      typedef vector<TGCheckButton*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TGCheckButton*>

namespace ROOT {
   static TClass *vectorlETCanvasmUgR_Dictionary();
   static void vectorlETCanvasmUgR_TClassManip(TClass*);
   static void *new_vectorlETCanvasmUgR(void *p = 0);
   static void *newArray_vectorlETCanvasmUgR(Long_t size, void *p);
   static void delete_vectorlETCanvasmUgR(void *p);
   static void deleteArray_vectorlETCanvasmUgR(void *p);
   static void destruct_vectorlETCanvasmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TCanvas*>*)
   {
      vector<TCanvas*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TCanvas*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TCanvas*>", -2, "vector", 210,
                  typeid(vector<TCanvas*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETCanvasmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TCanvas*>) );
      instance.SetNew(&new_vectorlETCanvasmUgR);
      instance.SetNewArray(&newArray_vectorlETCanvasmUgR);
      instance.SetDelete(&delete_vectorlETCanvasmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlETCanvasmUgR);
      instance.SetDestructor(&destruct_vectorlETCanvasmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TCanvas*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TCanvas*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETCanvasmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TCanvas*>*)0x0)->GetClass();
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
      delete ((vector<TCanvas*>*)p);
   }
   static void deleteArray_vectorlETCanvasmUgR(void *p) {
      delete [] ((vector<TCanvas*>*)p);
   }
   static void destruct_vectorlETCanvasmUgR(void *p) {
      typedef vector<TCanvas*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TCanvas*>

namespace ROOT {
   static TClass *vectorlEFullFitHoldermUgR_Dictionary();
   static void vectorlEFullFitHoldermUgR_TClassManip(TClass*);
   static void *new_vectorlEFullFitHoldermUgR(void *p = 0);
   static void *newArray_vectorlEFullFitHoldermUgR(Long_t size, void *p);
   static void delete_vectorlEFullFitHoldermUgR(void *p);
   static void deleteArray_vectorlEFullFitHoldermUgR(void *p);
   static void destruct_vectorlEFullFitHoldermUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<FullFitHolder*>*)
   {
      vector<FullFitHolder*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<FullFitHolder*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<FullFitHolder*>", -2, "vector", 210,
                  typeid(vector<FullFitHolder*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEFullFitHoldermUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<FullFitHolder*>) );
      instance.SetNew(&new_vectorlEFullFitHoldermUgR);
      instance.SetNewArray(&newArray_vectorlEFullFitHoldermUgR);
      instance.SetDelete(&delete_vectorlEFullFitHoldermUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEFullFitHoldermUgR);
      instance.SetDestructor(&destruct_vectorlEFullFitHoldermUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<FullFitHolder*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<FullFitHolder*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEFullFitHoldermUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<FullFitHolder*>*)0x0)->GetClass();
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
      delete ((vector<FullFitHolder*>*)p);
   }
   static void deleteArray_vectorlEFullFitHoldermUgR(void *p) {
      delete [] ((vector<FullFitHolder*>*)p);
   }
   static void destruct_vectorlEFullFitHoldermUgR(void *p) {
      typedef vector<FullFitHolder*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<FullFitHolder*>

namespace {
  void TriggerDictionaryInitialization_DictOutput_Impl() {
    static const char* headers[] = {
"include/james_env.h",
"include/james_gating_tool.h",
"include/james_spectool.h",
"include/james_utility.h",
"include/james_gating_frame.h",
"include/james_effpeaks.h",
"include/james_gpad_tools.h",
"include/james_fitholder.h",
"include/james_hist_formatting.h",
"include/james_gate_subtract.h",
"include/james_fitting.h",
"include/james_ultrafit_env.h",
"include/james_ultrapeak.h",
0
    };
    static const char* includePaths[] = {
"/home/jsmallcombe/Dropbox/codes/JAnalysisTools/include",
"/opt/root_v6.10.04/include",
"/home/jsmallcombe/Dropbox/codes/JAnalysisTools/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "DictOutput dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
template <typename T> class __attribute__((annotate("$clingAutoload$james_utility.h")))  __attribute__((annotate("$clingAutoload$include/james_env.h")))  TransientBitsClass;

class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_gpad_tools.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$james_gpad_tools.h")))  __attribute__((annotate("$clingAutoload$include/james_env.h")))  HistClickStop;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_gpad_tools.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$james_gpad_tools.h")))  __attribute__((annotate("$clingAutoload$include/james_env.h")))  jhistquestion;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_fitholder.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$james_fitholder.h")))  __attribute__((annotate("$clingAutoload$include/james_env.h")))  FullFitHolder;
struct __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_fitting.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$james_fitting.h")))  __attribute__((annotate("$clingAutoload$include/james_env.h")))  jPeakDat;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_ultrapeak.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$james_ultrapeak.h")))  __attribute__((annotate("$clingAutoload$include/james_env.h")))  Ultrapeak;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_ultrapeak.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$james_ultrapeak.h")))  __attribute__((annotate("$clingAutoload$include/james_env.h")))  UltrapeakArea;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_ultrapeak.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$james_ultrapeak.h")))  __attribute__((annotate("$clingAutoload$include/james_env.h")))  UltrapeakFrac;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_ultrafit_env.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$james_ultrafit_env.h")))  __attribute__((annotate("$clingAutoload$include/james_env.h")))  UltraFitEnv;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_gate_subtract.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$james_gate_subtract.h")))  __attribute__((annotate("$clingAutoload$include/james_env.h")))  TH1ErrorAdj;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_gating_frame.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$james_gating_frame.h")))  __attribute__((annotate("$clingAutoload$include/james_env.h")))  j_gating_frame;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_gating_tool.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$james_gating_tool.h")))  __attribute__((annotate("$clingAutoload$include/james_env.h")))  jgating_tool;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_gating_tool.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$james_gating_tool.h")))  __attribute__((annotate("$clingAutoload$include/james_env.h")))  minimalist_th3slice;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_spectool.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$james_spectool.h")))  __attribute__((annotate("$clingAutoload$include/james_env.h")))  jSpecTool;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_env.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_env.h")))  CCframe;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@include/james_env.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$include/james_env.h")))  jEnv;
typedef struct jPeakDat jPeakDat __attribute__((annotate("$clingAutoload$james_fitting.h")))  __attribute__((annotate("$clingAutoload$include/james_env.h"))) ;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "DictOutput dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "include/james_env.h"
#include "include/james_gating_tool.h"
#include "include/james_spectool.h"
#include "include/james_utility.h"
#include "include/james_gating_frame.h"
#include "include/james_effpeaks.h"
#include "include/james_gpad_tools.h"
#include "include/james_fitholder.h"
#include "include/james_hist_formatting.h"
#include "include/james_gate_subtract.h"
#include "include/james_fitting.h"
#include "include/james_ultrafit_env.h"
#include "include/james_ultrapeak.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"", payloadCode, "@",
"AddPeakLabel", payloadCode, "@",
"AnalyticalFullCovError", payloadCode, "@",
"CCframe", payloadCode, "@",
"CCframe::fgIsA", payloadCode, "@",
"ClickPeakDrawConnect", payloadCode, "@",
"CombArea", payloadCode, "@",
"CombArea2Gaus", payloadCode, "@",
"CombRDpeak", payloadCode, "@",
"CombRDstep", payloadCode, "@",
"DecGaus", payloadCode, "@",
"DecGausArea", payloadCode, "@",
"DecGausCFD", payloadCode, "@",
"DecGausMaxX", payloadCode, "@",
"DecGausStep", payloadCode, "@",
"DrawCopyHistOpt", payloadCode, "@",
"DrawHformat", payloadCode, "@",
"DrawHistOpt", payloadCode, "@",
"ExtractError", payloadCode, "@",
"ExtractErrorTest", payloadCode, "@",
"ExtreemRebin", payloadCode, "@",
"FindBinRangeMax", payloadCode, "@",
"FindBinRangeMaxD", payloadCode, "@",
"FindLocalMax", payloadCode, "@",
"FitPositionOptimisation", payloadCode, "@",
"FitUltra", payloadCode, "@",
"FullFitHolder", payloadCode, "@",
"FullFitHolder::fgIsA", payloadCode, "@",
"GetHistClickVal", payloadCode, "@",
"HistClickStop", payloadCode, "@",
"HistDrawCopy", payloadCode, "@",
"HistDrawCopyPeaker", payloadCode, "@",
"HistDrawnXRange", payloadCode, "@",
"HistSaveAs", payloadCode, "@",
"LinearMulitPeak", payloadCode, "@",
"MulitPeak", payloadCode, "@",
"MulitPeak2Gaus", payloadCode, "@",
"MulitPeakBack", payloadCode, "@",
"MulitPeakBackUni", payloadCode, "@",
"MulitPeakBackUni2Gaus", payloadCode, "@",
"OldCombArea", payloadCode, "@",
"PadNDCtoUser", payloadCode, "@",
"PostUpdateCanvasUpdateCall", payloadCode, "@",
"QuickSingleGausAutoFit", payloadCode, "@",
"QuickSingleGausAutoFitE", payloadCode, "@",
"QuickSingleGausAutoFitEE", payloadCode, "@",
"RangeChangeBisectCanvasBoth", payloadCode, "@",
"ReMargin", payloadCode, "@",
"SmoothOffBack", payloadCode, "@",
"SortFullFitByRedChi", payloadCode, "@",
"SortFullFitByVal", payloadCode, "@",
"StepMulitPeak", payloadCode, "@",
"TH1ErrorAdj", payloadCode, "@",
"TH1ErrorAdj::fgIsA", payloadCode, "@",
"TH3axisreseter", payloadCode, "@",
"ToolTipHide", payloadCode, "@",
"TransientBitsClass<long>", payloadCode, "@",
"TrueCentroid", payloadCode, "@",
"UltraFitEnv", payloadCode, "@",
"UltraFitEnv::UltraFitEnv_iterator", payloadCode, "@",
"UltraFitEnv::fgIsA", payloadCode, "@",
"Ultrapeak", payloadCode, "@",
"Ultrapeak::UBits", payloadCode, "@",
"Ultrapeak::VBI", payloadCode, "@",
"Ultrapeak::VChi", payloadCode, "@",
"Ultrapeak::VN", payloadCode, "@",
"Ultrapeak::VOff", payloadCode, "@",
"Ultrapeak::gUltraOffsetOrPol2", payloadCode, "@",
"Ultrapeak::gUltraPol0", payloadCode, "@",
"Ultrapeak::gUltraPol1", payloadCode, "@",
"Ultrapeak::gUltraStep", payloadCode, "@",
"UltrapeakArea", payloadCode, "@",
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
"hformat", payloadCode, "@",
"higher_jd", payloadCode, "@",
"hist_capture", payloadCode, "@",
"hist_gater", payloadCode, "@",
"hist_gater_anti", payloadCode, "@",
"hist_gater_anti_bin", payloadCode, "@",
"hist_gater_bin", payloadCode, "@",
"hist_proj", payloadCode, "@",
"jEnv", payloadCode, "@",
"jEnv::SumNameItt", payloadCode, "@",
"jEnv::fgIsA", payloadCode, "@",
"jPeakDat", payloadCode, "@",
"jSpecTool", payloadCode, "@",
"jSpecTool::BackOpt", payloadCode, "@",
"jSpecTool::fgIsA", payloadCode, "@",
"jSpecTool::spectool_iterator", payloadCode, "@",
"j_gating_frame", payloadCode, "@",
"j_gating_frame::fgIsA", payloadCode, "@",
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
"vector_d_sort", payloadCode, "@",
"vector_order_gen", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("DictOutput",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_DictOutput_Impl, {}, classesHeaders);
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
