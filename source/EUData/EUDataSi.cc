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
		f->GetObject("w3",tree);

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
	fData->SetBranchAddress("scal", scal, &b_scal);
	fData->SetBranchAddress("ADC", ADC, &b_ADC);
	fData->SetBranchAddress("TDC", TDC, &b_TDC);
	fData->SetBranchAddress("TDCref", TDCref, &b_TDCref);
	fData->SetBranchAddress("w3_ex", w3_ex, &b_w3_ex);
	fData->SetBranchAddress("w3_ey", w3_ey, &b_w3_ey);
	fData->SetBranchAddress("w3_tx", w3_tx, &b_w3_tx);
	fData->SetBranchAddress("w3_ty", w3_ty, &b_w3_ty);
	fData->SetBranchAddress("f11L", &f11L, &b_f11L);
	fData->SetBranchAddress("f11R", &f11R, &b_f11R);
	fData->SetBranchAddress("t_ref", t_ref, &b_t_ref);
	fData->SetBranchAddress("w3tx", w3tx, &b_w3tx);
	fData->SetBranchAddress("w3ty", w3ty, &b_w3ty);
	fData->SetBranchAddress("vetoPL_back", &vetoPL_back, &b_vetoPL_back);
	fData->SetBranchAddress("betaPL1L", &betaPL1L, &b_betaPL1L);
	fData->SetBranchAddress("betaPL1R", &betaPL1R, &b_betaPL1R);
	fData->SetBranchAddress("betaPL2L", &betaPL2L, &b_betaPL2L);
	fData->SetBranchAddress("betaPL2R", &betaPL2R, &b_betaPL2R);
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
