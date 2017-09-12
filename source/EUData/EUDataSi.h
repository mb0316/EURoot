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

		EUDataSi(const char* filename, TTree *tree=0);
		~EUDataSi();
		Int_t	GetEntry(Long64_t entry);
		void	Init(TTree *tree);
		void	GetTsEntry(std::map<Long64_t, Long64_t> &mts);
};
#endif
