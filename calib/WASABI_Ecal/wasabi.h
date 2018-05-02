//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Sep 28 12:44:24 2016 by ROOT version 5.34/21
// from TTree WASABI/data
// found on file: WASABI_SiCalib0012.root
//////////////////////////////////////////////////////////

//#ifndef wasabi_h
//#define wasabi_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TClonesArray.h>
#include <TObject.h>
#include <TNamed.h>

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>


// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t MaxEventInfo = 1;

class wasabi {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           EventInfo_;
   UInt_t          EventInfo_fUniqueID[MaxEventInfo];   //[EventInfo_]
   UInt_t          EventInfo_fBits[MaxEventInfo];   //[EventInfo_]
   TString         EventInfo_fName[MaxEventInfo];
   TString         EventInfo_fTitle[MaxEventInfo];
   Int_t           EventInfo_runnumber[MaxEventInfo];   //[EventInfo_]
   Int_t           EventInfo_eventnumber[MaxEventInfo];   //[EventInfo_]
   TString         EventInfo_subsysname[MaxEventInfo];
   ULong64_t       EventInfo_timestamp[MaxEventInfo];   //[EventInfo_]
   Int_t           EventInfo_comp_val[MaxEventInfo];   //[EventInfo_]
   UInt_t          EventInfo_fBit[MaxEventInfo];   //[EventInfo_]
   Int_t           IF_BETA;
   Int_t           IF_ION;
   Int_t           numdssd;
   Int_t           numadc;
   Int_t           numtdc;
   Int_t           dstrx;
   Int_t           dstry;
   Int_t           scal[32];
   Int_t           dssd_E_X[5][60];   //[numdssd]
   Int_t           dssd_ch_X[5][60];   //[numdssd]
   Int_t           dssd_id_X[5][60];   //[numdssd]
   Int_t           dssd_E_Y[5][40];   //[numdssd]
   Int_t           dssd_ch_Y[5][40];   //[numdssd]
   Int_t           dssd_id_Y[5][40];   //[numdssd]
   Int_t           dssd_T_X[5][60][3];   //[numdssd]
   Int_t           dssd_T_Y[5][40][3];   //[numdssd]
   Int_t           dssd_X[5];   //[numdssd]
   Int_t           dssd_Y[5];   //[numdssd]
   Int_t           dssd_Z;
   Int_t           ADC[18][32];   //[numadc]
   Int_t           TDC[5][128][3];   //[numtdc]
   Int_t           DSSD_E[5][100];   //[numdssd]
   Int_t           DSSD_T[5][100][3];   //[numdssd]
   Int_t           bigrips_F7PPAC1X1;
   Int_t           bigrips_F7PPAC1X2;
   Int_t           bigrips_F7PPAC2X1;
   Int_t           bigrips_F7PPAC2X2;
   Int_t           bigrips_F5PPAC1X1;
   Int_t           bigrips_F5PPAC1X2;
   Int_t           bigrips_F5PPAC2X1;
   Int_t           bigrips_F5PPAC2X2;
   Int_t           bigrips_F3L;
   Int_t           bigrips_F3R;
   Int_t           bigrips_F7L;
   Int_t           bigrips_F7R;
   Int_t           bigrips_F11L;
   Int_t           bigrips_F11R;
   Int_t           bigrips_IC1e;
   Int_t           bigrips_IC2e;
   Int_t           bigrips_IC3e;
   Int_t           bigrips_IC4e;
   Int_t           bigrips_IC5e;
   Int_t           bigrips_IC6e;
   Int_t           vetoPL_front;
   Int_t           vetoPL_back;
   Int_t           betaPL1L;
   Int_t           betaPL1R;
   Int_t           betaPL2L;
   Int_t           betaPL2R;
   Int_t           LaBr_TDCl[18];
   Double_t        bigrips_F7PPAC1_TDiffX;
   Double_t        bigrips_F7PPAC2_TDiffX;
   Double_t        bigrips_F5PPAC1_TDiffX;
   Double_t        bigrips_F5PPAC2_TDiffX;
   Double_t        bigrips_F7PPAC1_X;
   Double_t        bigrips_F7PPAC2_X;
   Double_t        bigrips_F5PPAC1_X;
   Double_t        bigrips_F5PPAC2_X;
   Double_t        bigrips_F7_X;
   Double_t        bigrips_F7_A;
   Double_t        bigrips_F5_X;
   Double_t        bigrips_F5_A;
   Double_t        bigrips_dERaw;
   Double_t        bigrips_dE;
   Double_t        pid_Delta_F5F7;
   Double_t        pid_TOF_F3F7;
   Double_t        pid_Beta_F3F5;
   Double_t        pid_Beta_F5F7;
   Double_t        pid_AoQ_F5F7;
   Double_t        pid_Zet_F11;

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
   TBranch        *b_IF_BETA;   //!
   TBranch        *b_IF_ION;   //!
   TBranch        *b_numdssd;   //!
   TBranch        *b_numadc;   //!
   TBranch        *b_numtdc;   //!
   TBranch        *b_dstrx;   //!
   TBranch        *b_dstry;   //!
   TBranch        *b_scal;   //!
   TBranch        *b_dssd_E_X;   //!
   TBranch        *b_dssd_ch_X;   //!
   TBranch        *b_dssd_id_X;   //!
   TBranch        *b_dssd_E_Y;   //!
   TBranch        *b_dssd_ch_Y;   //!
   TBranch        *b_dssd_id_Y;   //!
   TBranch        *b_dssd_T_X;   //!
   TBranch        *b_dssd_T_Y;   //!
   TBranch        *b_dssd_X;   //!
   TBranch        *b_dssd_Y;   //!
   TBranch        *b_dssd_Z;   //!
   TBranch        *b_ADC;   //!
   TBranch        *b_TDC;   //!
   TBranch        *b_DSSD_E;   //!
   TBranch        *b_DSSD_T;   //!
   TBranch        *b_bigrips_F7PPAC1X1;   //!
   TBranch        *b_bigrips_F7PPAC1X2;   //!
   TBranch        *b_bigrips_F7PPAC2X1;   //!
   TBranch        *b_bigrips_F7PPAC2X2;   //!
   TBranch        *b_bigrips_F5PPAC1X1;   //!
   TBranch        *b_bigrips_F5PPAC1X2;   //!
   TBranch        *b_bigrips_F5PPAC2X1;   //!
   TBranch        *b_bigrips_F5PPAC2X2;   //!
   TBranch        *b_bigrips_F3L;   //!
   TBranch        *b_bigrips_F3R;   //!
   TBranch        *b_bigrips_F7L;   //!
   TBranch        *b_bigrips_F7R;   //!
   TBranch        *b_bigrips_F11L;   //!
   TBranch        *b_bigrips_F11R;   //!
   TBranch        *b_bigrips_IC1e;   //!
   TBranch        *b_bigrips_IC2e;   //!
   TBranch        *b_bigrips_IC3e;   //!
   TBranch        *b_bigrips_IC4e;   //!
   TBranch        *b_bigrips_IC5e;   //!
   TBranch        *b_bigrips_IC6e;   //!
   TBranch        *b_vetoPL_front;   //!
   TBranch        *b_vetoPL_back;   //!
   TBranch        *b_betaPL1L;   //!
   TBranch        *b_betaPL1R;   //!
   TBranch        *b_betaPL2L;   //!
   TBranch        *b_betaPL2R;   //!
   TBranch        *b_LaBr_TDCl;   //!
   TBranch        *b_bigrips_F7PPAC1_TDiffX;   //!
   TBranch        *b_bigrips_F7PPAC2_TDiffX;   //!
   TBranch        *b_bigrips_F5PPAC1_TDiffX;   //!
   TBranch        *b_bigrips_F5PPAC2_TDiffX;   //!
   TBranch        *b_bigrips_F7PPAC1_X;   //!
   TBranch        *b_bigrips_F7PPAC2_X;   //!
   TBranch        *b_bigrips_F5PPAC1_X;   //!
   TBranch        *b_bigrips_F5PPAC2_X;   //!
   TBranch        *b_bigrips_F7_X;   //!
   TBranch        *b_bigrips_F7_A;   //!
   TBranch        *b_bigrips_F5_X;   //!
   TBranch        *b_bigrips_F5_A;   //!
   TBranch        *b_bigrips_dERaw;   //!
   TBranch        *b_bigrips_dE;   //!
   TBranch        *b_pid_Delta_F5F7;   //!
   TBranch        *b_pid_TOF_F3F7;   //!
   TBranch        *b_pid_Beta_F3F5;   //!
   TBranch        *b_pid_Beta_F5F7;   //!
   TBranch        *b_pid_AoQ_F5F7;   //!
   TBranch        *b_pid_Zet_F11;   //!

//   wasabi(TTree *tree=0);
//   virtual ~wasabi();
   virtual void     GetTree(char* filename, TTree *tree=0);
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
//   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void	GetTsEntry(std::map<Long64_t, Long64_t> &mts);
};

//#endif

//#ifdef wasabi_cxx
void wasabi::GetTree(char* filename, TTree *tree)
{
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
      if (!f || !f->IsOpen()) {
         f = new TFile(filename);
      }
      f->GetObject("WASABI",tree);

   }
   Init(tree);
}
/*
wasabi::~wasabi()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}
*/
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
   fChain->SetBranchAddress("IF_BETA", &IF_BETA, &b_IF_BETA);
   fChain->SetBranchAddress("IF_ION", &IF_ION, &b_IF_ION);
   fChain->SetBranchAddress("numdssd", &numdssd, &b_numdssd);
   fChain->SetBranchAddress("numadc", &numadc, &b_numadc);
   fChain->SetBranchAddress("numtdc", &numtdc, &b_numtdc);
   fChain->SetBranchAddress("dstrx", &dstrx, &b_dstrx);
   fChain->SetBranchAddress("dstry", &dstry, &b_dstry);
   fChain->SetBranchAddress("scal", scal, &b_scal);
   fChain->SetBranchAddress("dssd_E_X", dssd_E_X, &b_dssd_E_X);
   fChain->SetBranchAddress("dssd_ch_X", dssd_ch_X, &b_dssd_ch_X);
   fChain->SetBranchAddress("dssd_id_X", dssd_id_X, &b_dssd_id_X);
   fChain->SetBranchAddress("dssd_E_Y", dssd_E_Y, &b_dssd_E_Y);
   fChain->SetBranchAddress("dssd_ch_Y", dssd_ch_Y, &b_dssd_ch_Y);
   fChain->SetBranchAddress("dssd_id_Y", dssd_id_Y, &b_dssd_id_Y);
   fChain->SetBranchAddress("dssd_T_X", dssd_T_X, &b_dssd_T_X);
   fChain->SetBranchAddress("dssd_T_Y", dssd_T_Y, &b_dssd_T_Y);
   fChain->SetBranchAddress("dssd_X", dssd_X, &b_dssd_X);
   fChain->SetBranchAddress("dssd_Y", dssd_Y, &b_dssd_Y);
   fChain->SetBranchAddress("dssd_Z", &dssd_Z, &b_dssd_Z);
   fChain->SetBranchAddress("ADC", ADC, &b_ADC);
   fChain->SetBranchAddress("TDC", TDC, &b_TDC);
   fChain->SetBranchAddress("DSSD_E", DSSD_E, &b_DSSD_E);
   fChain->SetBranchAddress("DSSD_T", DSSD_T, &b_DSSD_T);
   fChain->SetBranchAddress("bigrips_F7PPAC1X1", &bigrips_F7PPAC1X1, &b_bigrips_F7PPAC1X1);
   fChain->SetBranchAddress("bigrips_F7PPAC1X2", &bigrips_F7PPAC1X2, &b_bigrips_F7PPAC1X2);
   fChain->SetBranchAddress("bigrips_F7PPAC2X1", &bigrips_F7PPAC2X1, &b_bigrips_F7PPAC2X1);
   fChain->SetBranchAddress("bigrips_F7PPAC2X2", &bigrips_F7PPAC2X2, &b_bigrips_F7PPAC2X2);
   fChain->SetBranchAddress("bigrips_F5PPAC1X1", &bigrips_F5PPAC1X1, &b_bigrips_F5PPAC1X1);
   fChain->SetBranchAddress("bigrips_F5PPAC1X2", &bigrips_F5PPAC1X2, &b_bigrips_F5PPAC1X2);
   fChain->SetBranchAddress("bigrips_F5PPAC2X1", &bigrips_F5PPAC2X1, &b_bigrips_F5PPAC2X1);
   fChain->SetBranchAddress("bigrips_F5PPAC2X2", &bigrips_F5PPAC2X2, &b_bigrips_F5PPAC2X2);
   fChain->SetBranchAddress("bigrips_F3L", &bigrips_F3L, &b_bigrips_F3L);
   fChain->SetBranchAddress("bigrips_F3R", &bigrips_F3R, &b_bigrips_F3R);
   fChain->SetBranchAddress("bigrips_F7L", &bigrips_F7L, &b_bigrips_F7L);
   fChain->SetBranchAddress("bigrips_F7R", &bigrips_F7R, &b_bigrips_F7R);
   fChain->SetBranchAddress("bigrips_F11L", &bigrips_F11L, &b_bigrips_F11L);
   fChain->SetBranchAddress("bigrips_F11R", &bigrips_F11R, &b_bigrips_F11R);
   fChain->SetBranchAddress("bigrips_IC1e", &bigrips_IC1e, &b_bigrips_IC1e);
   fChain->SetBranchAddress("bigrips_IC2e", &bigrips_IC2e, &b_bigrips_IC2e);
   fChain->SetBranchAddress("bigrips_IC3e", &bigrips_IC3e, &b_bigrips_IC3e);
   fChain->SetBranchAddress("bigrips_IC4e", &bigrips_IC4e, &b_bigrips_IC4e);
   fChain->SetBranchAddress("bigrips_IC5e", &bigrips_IC5e, &b_bigrips_IC5e);
   fChain->SetBranchAddress("bigrips_IC6e", &bigrips_IC6e, &b_bigrips_IC6e);
   fChain->SetBranchAddress("vetoPL_front", &vetoPL_front, &b_vetoPL_front);
   fChain->SetBranchAddress("vetoPL_back", &vetoPL_back, &b_vetoPL_back);
   fChain->SetBranchAddress("betaPL1L", &betaPL1L, &b_betaPL1L);
   fChain->SetBranchAddress("betaPL1R", &betaPL1R, &b_betaPL1R);
   fChain->SetBranchAddress("betaPL2L", &betaPL2L, &b_betaPL2L);
   fChain->SetBranchAddress("betaPL2R", &betaPL2R, &b_betaPL2R);
   fChain->SetBranchAddress("LaBr_TDCl", LaBr_TDCl, &b_LaBr_TDCl);
   fChain->SetBranchAddress("bigrips_F7PPAC1_TDiffX", &bigrips_F7PPAC1_TDiffX, &b_bigrips_F7PPAC1_TDiffX);
   fChain->SetBranchAddress("bigrips_F7PPAC2_TDiffX", &bigrips_F7PPAC2_TDiffX, &b_bigrips_F7PPAC2_TDiffX);
   fChain->SetBranchAddress("bigrips_F5PPAC1_TDiffX", &bigrips_F5PPAC1_TDiffX, &b_bigrips_F5PPAC1_TDiffX);
   fChain->SetBranchAddress("bigrips_F5PPAC2_TDiffX", &bigrips_F5PPAC2_TDiffX, &b_bigrips_F5PPAC2_TDiffX);
   fChain->SetBranchAddress("bigrips_F7PPAC1_X", &bigrips_F7PPAC1_X, &b_bigrips_F7PPAC1_X);
   fChain->SetBranchAddress("bigrips_F7PPAC2_X", &bigrips_F7PPAC2_X, &b_bigrips_F7PPAC2_X);
   fChain->SetBranchAddress("bigrips_F5PPAC1_X", &bigrips_F5PPAC1_X, &b_bigrips_F5PPAC1_X);
   fChain->SetBranchAddress("bigrips_F5PPAC2_X", &bigrips_F5PPAC2_X, &b_bigrips_F5PPAC2_X);
   fChain->SetBranchAddress("bigrips_F7_X", &bigrips_F7_X, &b_bigrips_F7_X);
   fChain->SetBranchAddress("bigrips_F7_A", &bigrips_F7_A, &b_bigrips_F7_A);
   fChain->SetBranchAddress("bigrips_F5_X", &bigrips_F5_X, &b_bigrips_F5_X);
   fChain->SetBranchAddress("bigrips_F5_A", &bigrips_F5_A, &b_bigrips_F5_A);
   fChain->SetBranchAddress("bigrips_dERaw", &bigrips_dERaw, &b_bigrips_dERaw);
   fChain->SetBranchAddress("bigrips_dE", &bigrips_dE, &b_bigrips_dE);
   fChain->SetBranchAddress("pid_Delta_F5F7", &pid_Delta_F5F7, &b_pid_Delta_F5F7);
   fChain->SetBranchAddress("pid_TOF_F3F7", &pid_TOF_F3F7, &b_pid_TOF_F3F7);
   fChain->SetBranchAddress("pid_Beta_F3F5", &pid_Beta_F3F5, &b_pid_Beta_F3F5);
   fChain->SetBranchAddress("pid_Beta_F5F7", &pid_Beta_F5F7, &b_pid_Beta_F5F7);
   fChain->SetBranchAddress("pid_AoQ_F5F7", &pid_AoQ_F5F7, &b_pid_AoQ_F5F7);
   fChain->SetBranchAddress("pid_Zet_F11", &pid_Zet_F11, &b_pid_Zet_F11);
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
//		mts[ts] = jentry;
		if (jentry%100000 == 0)
		{
			std::cout << jentry << " done." << std::endl;
			std::cout << ts << " " << jentry << std::endl;
			std::cout << "size of map : " << mts.size() << std::endl;
		}
	}
	cout << "Finding Ts of WASABI has been finished." << endl;
}
      // if (Cut(ientry) < 0) continue;
      //    }
//#endif // #ifdef wasabi_cxx
