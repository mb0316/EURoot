//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu May  3 13:06:10 2018 by ROOT version 6.10/08
// from TTree w3/tree
// found on file: WASABI1060.root
//////////////////////////////////////////////////////////


#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TClonesArray.h"
#include "TObject.h"
#include "TNamed.h"

class wasabi {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxEventInfo = 1;

   // Declaration of leaf types
   Int_t           EventInfo_;
   UInt_t          EventInfo_fUniqueID[kMaxEventInfo];   //[EventInfo_]
   UInt_t          EventInfo_fBits[kMaxEventInfo];   //[EventInfo_]
   TString         EventInfo_fName[kMaxEventInfo];
   TString         EventInfo_fTitle[kMaxEventInfo];
   Int_t           EventInfo_runnumber[kMaxEventInfo];   //[EventInfo_]
   Int_t           EventInfo_eventnumber[kMaxEventInfo];   //[EventInfo_]
   TString         EventInfo_subsysname[kMaxEventInfo];
   ULong64_t       EventInfo_timestamp[kMaxEventInfo];   //[EventInfo_]
   Int_t           EventInfo_comp_val[kMaxEventInfo];   //[EventInfo_]
   UInt_t          EventInfo_fBit[kMaxEventInfo];   //[EventInfo_]
   Int_t           scal[32];
   Int_t           ADC[18][32];
   Int_t           TDC[5][128][3];
   Int_t           TDCref[5][128][3];
   Int_t           w3_ex[5][60];
   Int_t           w3_ey[5][40];
   Int_t           w3_tx[5][60][3];
   Int_t           w3_ty[5][40][3];
   Int_t           f11L;
   Int_t           f11R;
   Int_t           t_ref[5];
   Int_t           w3tx[5][60][3];
   Int_t           w3ty[5][40][3];
   Double_t        zet;
   Double_t        aoq;
   Int_t           vetoPL_front;
   Int_t           vetoPL_back;
   Int_t           betaPL1L;
   Int_t           betaPL1R;
   Int_t           betaPL2L;
   Int_t           betaPL2R;

   // List of branches
   TBranch        *b_EventInfo_;   //!
   TBranch        *b_EventInfo_fUniqueID;   //!
   TBranch        *b_EventInfo_fBits;   //!
   TBranch        *b_EventInfo_fName;   //!
   TBranch        *b_EventInfo_fTitle;   //!
   TBranch        *b_EventInfo_runnumber;   //!
   TBranch        *b_EventInfo_eventnumber;   //!
   TBranch        *b_EventInfo_subsysname;   //!
   TBranch        *b_EventInfo_timestamp;   //!
   TBranch        *b_EventInfo_comp_val;   //!
   TBranch        *b_EventInfo_fBit;   //!
   TBranch        *b_scal;   //!
   TBranch        *b_ADC;   //!
   TBranch        *b_TDC;   //!
   TBranch        *b_TDCref;   //!
   TBranch        *b_w3_ex;   //!
   TBranch        *b_w3_ey;   //!
   TBranch        *b_w3_tx;   //!
   TBranch        *b_w3_ty;   //!
   TBranch        *b_f11L;   //!
   TBranch        *b_f11R;   //!
   TBranch        *b_t_ref;   //!
   TBranch        *b_w3tx;   //!
   TBranch        *b_w3ty;   //!
   TBranch        *b_zet;   //!
   TBranch        *b_aoq;   //!
   TBranch        *b_vetoPL_front;   //!
   TBranch        *b_vetoPL_back;   //!
   TBranch        *b_betaPL1L;   //!
   TBranch        *b_betaPL1R;   //!
   TBranch        *b_betaPL2L;   //!
   TBranch        *b_betaPL2R;   //!

//   wasabi(TTree *tree=0);
//   virtual ~wasabi();
   void 			GetTree(char* filename, TTree *tree=0);
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void GetTsEntry(std::map<Long64_t, Long64_t> &mts);
};

void wasabi::GetTree(char* filename, TTree *tree)
{
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
      if (!f || !f->IsOpen()) {
         f = new TFile(filename);
      }
      f->GetObject("w3",tree);

   }
   Init(tree);
}

Int_t wasabi::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t wasabi::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void wasabi::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventInfo", &EventInfo_, &b_EventInfo_);
   fChain->SetBranchAddress("EventInfo.fUniqueID", EventInfo_fUniqueID, &b_EventInfo_fUniqueID);
   fChain->SetBranchAddress("EventInfo.fBits", EventInfo_fBits, &b_EventInfo_fBits);
   fChain->SetBranchAddress("EventInfo.fName", EventInfo_fName, &b_EventInfo_fName);
   fChain->SetBranchAddress("EventInfo.fTitle", EventInfo_fTitle, &b_EventInfo_fTitle);
   fChain->SetBranchAddress("EventInfo.runnumber", EventInfo_runnumber, &b_EventInfo_runnumber);
   fChain->SetBranchAddress("EventInfo.eventnumber", EventInfo_eventnumber, &b_EventInfo_eventnumber);
   fChain->SetBranchAddress("EventInfo.subsysname", EventInfo_subsysname, &b_EventInfo_subsysname);
   fChain->SetBranchAddress("EventInfo.timestamp", EventInfo_timestamp, &b_EventInfo_timestamp);
   fChain->SetBranchAddress("EventInfo.comp_val", EventInfo_comp_val, &b_EventInfo_comp_val);
   fChain->SetBranchAddress("EventInfo.fBit", EventInfo_fBit, &b_EventInfo_fBit);
   fChain->SetBranchAddress("scal", scal, &b_scal);
   fChain->SetBranchAddress("ADC", ADC, &b_ADC);
   fChain->SetBranchAddress("TDC", TDC, &b_TDC);
   fChain->SetBranchAddress("TDCref", TDCref, &b_TDCref);
   fChain->SetBranchAddress("w3_ex", w3_ex, &b_w3_ex);
   fChain->SetBranchAddress("w3_ey", w3_ey, &b_w3_ey);
   fChain->SetBranchAddress("w3_tx", w3_tx, &b_w3_tx);
   fChain->SetBranchAddress("w3_ty", w3_ty, &b_w3_ty);
   fChain->SetBranchAddress("f11L", &f11L, &b_f11L);
   fChain->SetBranchAddress("f11R", &f11R, &b_f11R);
   fChain->SetBranchAddress("t_ref", t_ref, &b_t_ref);
   fChain->SetBranchAddress("w3tx", w3tx, &b_w3tx);
   fChain->SetBranchAddress("w3ty", w3ty, &b_w3ty);
   fChain->SetBranchAddress("zet", &zet, &b_zet);
   fChain->SetBranchAddress("aoq", &aoq, &b_aoq);
   fChain->SetBranchAddress("vetoPL_front", &vetoPL_front, &b_vetoPL_front);
   fChain->SetBranchAddress("vetoPL_back", &vetoPL_back, &b_vetoPL_back);
   fChain->SetBranchAddress("betaPL1L", &betaPL1L, &b_betaPL1L);
   fChain->SetBranchAddress("betaPL1R", &betaPL1R, &b_betaPL1R);
   fChain->SetBranchAddress("betaPL2L", &betaPL2L, &b_betaPL2L);
   fChain->SetBranchAddress("betaPL2R", &betaPL2R, &b_betaPL2R);
   Notify();
}

Bool_t wasabi::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void wasabi::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t wasabi::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
void wasabi::GetTsEntry(map<Long64_t, Long64_t> &mts)
{
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t ts;
    Long64_t nbytes = 0, nb = 0;
    std::cout << "start finding WASABI Ts." << std::endl;
    std::cout << nentries << " entries." << std::endl;

    for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);
        nbytes += nb;
        ts = EventInfo_timestamp[0];
        mts.insert(pair<Long64_t, Long64_t> (ts, jentry));
        if (jentry%100000 == 0)
        {
            std::cout << jentry << " done." << std::endl;
            std::cout << ts << " " << jentry << std::endl;
            std::cout << "size of map : " << mts.size() << std::endl;
        }
    }
    cout << "Finding Ts of WASABI has been finished." << endl;
}
  
