#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EUDataSi.h"
#include <TClonesArray.h>
#include <TObject.h>
#include <TNamed.h>

#include <stdio.h>
#include <stdlib.h>
#include <map>

EUDataSi::EUDataSi(const char* filename, TTree *tree)
{
	if (tree == 0) {
		f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
		if (!f || !f->IsOpen()) {
			f = new TFile(filename);
		}
		f->GetObject("WASABI",tree);

	}
	Init(tree);
}

EUDataSi::~EUDataSi()
{
	fData->Delete();
	delete f;
}

Int_t EUDataSi::GetEntry(Long64_t entry)
{
	// Read contents of entry.
	if (!fData) return 0;
	return fData->GetEntry(entry);
}

void EUDataSi::Init(TTree *tree)
{
	if (!tree) return;
	fData = tree;
	fCurrent = -1;
	fData->SetMakeClass(1);

	fData->SetBranchAddress("EventInfo", &EventInfo_, &b_EventInfo_);
	fData->SetBranchAddress("EventInfo.fUniqueID", EventInfo_fUniqueID, &b_EventInfo_fUniqueID);
	fData->SetBranchAddress("EventInfo.fBits", EventInfo_fBits, &b_EventInfo_fBits);
	fData->SetBranchAddress("EventInfo.fName", EventInfo_fName, &b_EventInfo_fName);
	fData->SetBranchAddress("EventInfo.fTitle", EventInfo_fTitle, &b_EventInfo_fTitle);
	fData->SetBranchAddress("EventInfo.runnumber", EventInfo_runnumber, &b_EventInfo_runnumber);
	fData->SetBranchAddress("EventInfo.eventnumber", EventInfo_eventnumber, &b_EventInfo_eventnumber);
	fData->SetBranchAddress("EventInfo.subsysname", EventInfo_subsysname, &b_EventInfo_subsysname);
	fData->SetBranchAddress("EventInfo.timestamp", EventInfo_timestamp, &b_EventInfo_timestamp);
	fData->SetBranchAddress("EventInfo.comp_val", EventInfo_comp_val, &b_EventInfo_comp_val);
	fData->SetBranchAddress("EventInfo.fBit", EventInfo_fBit, &b_EventInfo_fBit);
	fData->SetBranchAddress("IF_BETA", &IF_BETA, &b_IF_BETA);
	fData->SetBranchAddress("IF_ION", &IF_ION, &b_IF_ION);
	fData->SetBranchAddress("numdssd", &numdssd, &b_numdssd);
	fData->SetBranchAddress("numadc", &numadc, &b_numadc);
	fData->SetBranchAddress("numtdc", &numtdc, &b_numtdc);
	fData->SetBranchAddress("dstrx", &dstrx, &b_dstrx);
	fData->SetBranchAddress("dstry", &dstry, &b_dstry);
	fData->SetBranchAddress("scal", scal, &b_scal);
	fData->SetBranchAddress("dssd_E_X", dssd_E_X, &b_dssd_E_X);
	fData->SetBranchAddress("dssd_ch_X", dssd_ch_X, &b_dssd_ch_X);
	fData->SetBranchAddress("dssd_id_X", dssd_id_X, &b_dssd_id_X);
	fData->SetBranchAddress("dssd_E_Y", dssd_E_Y, &b_dssd_E_Y);
	fData->SetBranchAddress("dssd_ch_Y", dssd_ch_Y, &b_dssd_ch_Y);
	fData->SetBranchAddress("dssd_id_Y", dssd_id_Y, &b_dssd_id_Y);
	fData->SetBranchAddress("dssd_T_X", dssd_T_X, &b_dssd_T_X);
	fData->SetBranchAddress("dssd_T_Y", dssd_T_Y, &b_dssd_T_Y);
	fData->SetBranchAddress("dssd_X", dssd_X, &b_dssd_X);
	fData->SetBranchAddress("dssd_Y", dssd_Y, &b_dssd_Y);
	fData->SetBranchAddress("dssd_Z", &dssd_Z, &b_dssd_Z);
	fData->SetBranchAddress("ADC", ADC, &b_ADC);
	fData->SetBranchAddress("TDC", TDC, &b_TDC);
	fData->SetBranchAddress("DSSD_E", DSSD_E, &b_DSSD_E);
	fData->SetBranchAddress("DSSD_T", DSSD_T, &b_DSSD_T);
	fData->SetBranchAddress("bigrips_F7PPAC1X1", &bigrips_F7PPAC1X1, &b_bigrips_F7PPAC1X1);
	fData->SetBranchAddress("bigrips_F7PPAC1X2", &bigrips_F7PPAC1X2, &b_bigrips_F7PPAC1X2);
	fData->SetBranchAddress("bigrips_F7PPAC2X1", &bigrips_F7PPAC2X1, &b_bigrips_F7PPAC2X1);
	fData->SetBranchAddress("bigrips_F7PPAC2X2", &bigrips_F7PPAC2X2, &b_bigrips_F7PPAC2X2);
	fData->SetBranchAddress("bigrips_F5PPAC1X1", &bigrips_F5PPAC1X1, &b_bigrips_F5PPAC1X1);
	fData->SetBranchAddress("bigrips_F5PPAC1X2", &bigrips_F5PPAC1X2, &b_bigrips_F5PPAC1X2);
	fData->SetBranchAddress("bigrips_F5PPAC2X1", &bigrips_F5PPAC2X1, &b_bigrips_F5PPAC2X1);
	fData->SetBranchAddress("bigrips_F5PPAC2X2", &bigrips_F5PPAC2X2, &b_bigrips_F5PPAC2X2);
	fData->SetBranchAddress("bigrips_F3L", &bigrips_F3L, &b_bigrips_F3L);
	fData->SetBranchAddress("bigrips_F3R", &bigrips_F3R, &b_bigrips_F3R);
	fData->SetBranchAddress("bigrips_F7L", &bigrips_F7L, &b_bigrips_F7L);
	fData->SetBranchAddress("bigrips_F7R", &bigrips_F7R, &b_bigrips_F7R);
	fData->SetBranchAddress("bigrips_F11L", &bigrips_F11L, &b_bigrips_F11L);
	fData->SetBranchAddress("bigrips_F11R", &bigrips_F11R, &b_bigrips_F11R);
	fData->SetBranchAddress("bigrips_IC1e", &bigrips_IC1e, &b_bigrips_IC1e);
	fData->SetBranchAddress("bigrips_IC2e", &bigrips_IC2e, &b_bigrips_IC2e);
	fData->SetBranchAddress("bigrips_IC3e", &bigrips_IC3e, &b_bigrips_IC3e);
	fData->SetBranchAddress("bigrips_IC4e", &bigrips_IC4e, &b_bigrips_IC4e);
	fData->SetBranchAddress("bigrips_IC5e", &bigrips_IC5e, &b_bigrips_IC5e);
	fData->SetBranchAddress("bigrips_IC6e", &bigrips_IC6e, &b_bigrips_IC6e);
	fData->SetBranchAddress("vetoPL_front", &vetoPL_front, &b_vetoPL_front);
	fData->SetBranchAddress("vetoPL_back", &vetoPL_back, &b_vetoPL_back);
	fData->SetBranchAddress("betaPL1L", &betaPL1L, &b_betaPL1L);
	fData->SetBranchAddress("betaPL1R", &betaPL1R, &b_betaPL1R);
	fData->SetBranchAddress("betaPL2L", &betaPL2L, &b_betaPL2L);
	fData->SetBranchAddress("betaPL2R", &betaPL2R, &b_betaPL2R);
	fData->SetBranchAddress("LaBr_TDCl", LaBr_TDCl, &b_LaBr_TDCl);
	fData->SetBranchAddress("bigrips_F7PPAC1_TDiffX", &bigrips_F7PPAC1_TDiffX, &b_bigrips_F7PPAC1_TDiffX);
	fData->SetBranchAddress("bigrips_F7PPAC2_TDiffX", &bigrips_F7PPAC2_TDiffX, &b_bigrips_F7PPAC2_TDiffX);
	fData->SetBranchAddress("bigrips_F5PPAC1_TDiffX", &bigrips_F5PPAC1_TDiffX, &b_bigrips_F5PPAC1_TDiffX);
	fData->SetBranchAddress("bigrips_F5PPAC2_TDiffX", &bigrips_F5PPAC2_TDiffX, &b_bigrips_F5PPAC2_TDiffX);
	fData->SetBranchAddress("bigrips_F7PPAC1_X", &bigrips_F7PPAC1_X, &b_bigrips_F7PPAC1_X);
	fData->SetBranchAddress("bigrips_F7PPAC2_X", &bigrips_F7PPAC2_X, &b_bigrips_F7PPAC2_X);
	fData->SetBranchAddress("bigrips_F5PPAC1_X", &bigrips_F5PPAC1_X, &b_bigrips_F5PPAC1_X);
	fData->SetBranchAddress("bigrips_F5PPAC2_X", &bigrips_F5PPAC2_X, &b_bigrips_F5PPAC2_X);
	fData->SetBranchAddress("bigrips_F7_X", &bigrips_F7_X, &b_bigrips_F7_X);
	fData->SetBranchAddress("bigrips_F7_A", &bigrips_F7_A, &b_bigrips_F7_A);
	fData->SetBranchAddress("bigrips_F5_X", &bigrips_F5_X, &b_bigrips_F5_X);
	fData->SetBranchAddress("bigrips_F5_A", &bigrips_F5_A, &b_bigrips_F5_A);
	fData->SetBranchAddress("bigrips_dERaw", &bigrips_dERaw, &b_bigrips_dERaw);
	fData->SetBranchAddress("bigrips_dE", &bigrips_dE, &b_bigrips_dE);
	fData->SetBranchAddress("pid_Delta_F5F7", &pid_Delta_F5F7, &b_pid_Delta_F5F7);
	fData->SetBranchAddress("pid_TOF_F3F7", &pid_TOF_F3F7, &b_pid_TOF_F3F7);
	fData->SetBranchAddress("pid_Beta_F3F5", &pid_Beta_F3F5, &b_pid_Beta_F3F5);
	fData->SetBranchAddress("pid_Beta_F5F7", &pid_Beta_F5F7, &b_pid_Beta_F5F7);
	fData->SetBranchAddress("pid_AoQ_F5F7", &pid_AoQ_F5F7, &b_pid_AoQ_F5F7);
	fData->SetBranchAddress("pid_Zet_F11", &pid_Zet_F11, &b_pid_Zet_F11);
}

void EUDataSi::GetTsEntry(std::map<Long64_t, Long64_t> &mts)
{
	Long64_t nentries = fData->GetEntriesFast();
	for (Long64_t jentry=0; jentry<nentries;jentry++)
	{
		fData->GetEntry(jentry); 
		mts.insert(std::pair<Long64_t, Long64_t> (EventInfo_timestamp[0], jentry));
	}
}
