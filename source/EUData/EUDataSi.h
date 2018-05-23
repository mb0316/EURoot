#ifndef EUDATASI_H
#define EUDATASI_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TObject.h>
#include <TNamed.h>
#include "EUData.h"

#include <stdio.h>
#include <stdlib.h>
#include <map>

const Int_t MaxEventInfo = 1;

class EUDataSi : public EUData
{
	public :
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
		Int_t           scal[32];
		Int_t           ADC[18][32];   //[numadc]
		Int_t           TDC[5][128][3];   //[numtdc]
		Int_t			TDCref[5][128][3];
		Int_t			w3_ex[5][60];
		Int_t			w3_ey[5][40];
		Int_t			w3_tx[5][60][3];
		Int_t			w3_ty[5][40][3];
		Int_t			f11L;
		Int_t			f11R;
		Int_t			t_ref[5];
		Int_t			w3tx[5][60][3];
		Int_t			w3ty[5][40][3];
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
		TBranch			*b_TDCref;
		TBranch			*b_w3_ex;
		TBranch			*b_w3_ey;
		TBranch			*b_w3_tx;
		TBranch			*b_w3_ty;
		TBranch			*b_f11L;
		TBranch			*b_f11R;
		TBranch			*b_t_ref;
		TBranch			*b_w3tx;
		TBranch			*b_w3ty;
		TBranch        *b_vetoPL_front;   //!
		TBranch        *b_vetoPL_back;   //!
		TBranch        *b_betaPL1L;   //!
		TBranch        *b_betaPL1R;   //!
		TBranch        *b_betaPL2L;   //!
		TBranch        *b_betaPL2R;   //!


		EUDataSi(const char* filename, TTree *tree=0);
		~EUDataSi();
		Int_t	GetEntry(Long64_t entry);
		void	Init(TTree *tree);
		void	GetTsEntry(std::map<Long64_t, Long64_t> &mts);
};
#endif
