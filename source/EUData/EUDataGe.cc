#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EUDataGe.h"
#include <TClonesArray.h>
#include <TObject.h>
#include <TNamed.h>

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <iostream>

EUDataGe::EUDataGe(const char* filename, TTree* tree)
{
	if (tree == 0) {
		f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
		if (!f || !f->IsOpen()) {
			f = new TFile(filename);
		}
		f->GetObject("tree",tree);

	}
	Init(tree);
}

EUDataGe::~EUDataGe()
{
	fData->Delete();
	delete f;
}

Int_t EUDataGe::GetEntry(Long64_t entry)
{
	// Read contents of entry.
	if (!fData) return 0;
	return fData->GetEntry(entry);
}

void EUDataGe::Init(TTree *tree)
{
	// Set branch addresses and branch pointers
	if (!tree) return;
	fData = tree;
	fCurrent = -1;
	fData->SetMakeClass(1);
	fData->SetBranchAddress("UnpackEvent", &UnpackEvent_, &b_UnpackEvent_);
	fData->SetBranchAddress("UnpackEvent.fUniqueID", UnpackEvent_fUniqueID, &b_UnpackEvent_fUniqueID);
	fData->SetBranchAddress("UnpackEvent.fBits", UnpackEvent_fBits, &b_UnpackEvent_fBits);
	fData->SetBranchAddress("UnpackEvent.fName", UnpackEvent_fName, &b_UnpackEvent_fName);
	fData->SetBranchAddress("UnpackEvent.fTitle", UnpackEvent_fTitle, &b_UnpackEvent_fTitle);
	fData->SetBranchAddress("UnpackEvent.fbIsValid", UnpackEvent_fbIsValid, &b_UnpackEvent_fbIsValid);
	fData->SetBranchAddress("UnpackEvent.fIdentifier", UnpackEvent_fIdentifier, &b_UnpackEvent_fIdentifier);
	fData->SetBranchAddress("UnpackEvent.detBP[16]", UnpackEvent_detBP, &b_UnpackEvent_detBP);
	fData->SetBranchAddress("UnpackEvent.detHP", UnpackEvent_detHP, &b_UnpackEvent_detHP);
	fData->SetBranchAddress("UnpackEvent.vme1_1[32]", UnpackEvent_vme1_1, &b_UnpackEvent_vme1_1);
	fData->SetBranchAddress("UnpackEvent.vme1_2[32]", UnpackEvent_vme1_2, &b_UnpackEvent_vme1_2);
	fData->SetBranchAddress("UnpackEvent.nhit1[128]", UnpackEvent_nhit1, &b_UnpackEvent_nhit1);
	fData->SetBranchAddress("UnpackEvent.vme1s[128][10]", UnpackEvent_vme1s, &b_UnpackEvent_vme1s);
	fData->SetBranchAddress("UnpackEvent.vme4_5[30][4][2]", UnpackEvent_vme4_5, &b_UnpackEvent_vme4_5);
	fData->SetBranchAddress("UnpackEvent.vme6[4][32]", UnpackEvent_vme6, &b_UnpackEvent_vme6);
	fData->SetBranchAddress("UnpackEvent.vmel[128][3]", UnpackEvent_vmel, &b_UnpackEvent_vmel);
	fData->SetBranchAddress("UnpackEvent.nhitl[128]", UnpackEvent_nhitl, &b_UnpackEvent_nhitl);
	fData->SetBranchAddress("UnpackEvent.hp[4]", UnpackEvent_hp, &b_UnpackEvent_hp);
	fData->SetBranchAddress("UnpackEvent.vme20[21][64]", UnpackEvent_vme20, &b_UnpackEvent_vme20);
	fData->SetBranchAddress("UnpackEvent.vmehit[21][64][10]", UnpackEvent_vmehit, &b_UnpackEvent_vmehit);
	fData->SetBranchAddress("UnpackEvent.nhit[21][64]", UnpackEvent_nhit, &b_UnpackEvent_nhit);
	fData->SetBranchAddress("UnpackEvent.lenUSR", UnpackEvent_lenUSR, &b_UnpackEvent_lenUSR);
	fData->SetBranchAddress("UnpackEvent.lenDGF", UnpackEvent_lenDGF, &b_UnpackEvent_lenDGF);
	fData->SetBranchAddress("UnpackEvent.lenGeTDC", UnpackEvent_lenGeTDC, &b_UnpackEvent_lenGeTDC);
	fData->SetBranchAddress("UnpackEvent.lupotslo", UnpackEvent_lupotslo, &b_UnpackEvent_lupotslo);
	fData->SetBranchAddress("UnpackEvent.lupotshi", UnpackEvent_lupotshi, &b_UnpackEvent_lupotshi);
	fData->SetBranchAddress("UnpackEvent.qlength", UnpackEvent_qlength, &b_UnpackEvent_qlength);
	fData->SetBranchAddress("UnpackEvent.qtype", UnpackEvent_qtype, &b_UnpackEvent_qtype);
	fData->SetBranchAddress("UnpackEvent.qsubtype", UnpackEvent_qsubtype, &b_UnpackEvent_qsubtype);
	fData->SetBranchAddress("UnpackEvent.qdummy", UnpackEvent_qdummy, &b_UnpackEvent_qdummy);
	fData->SetBranchAddress("UnpackEvent.qtrigger", UnpackEvent_qtrigger, &b_UnpackEvent_qtrigger);
	fData->SetBranchAddress("UnpackEvent.qevent_nr", UnpackEvent_qevent_nr, &b_UnpackEvent_qevent_nr);
	fData->SetBranchAddress("UnpackEvent.Time_sec", UnpackEvent_Time_sec, &b_UnpackEvent_Time_sec);
	fData->SetBranchAddress("UnpackEvent.Time_msec", UnpackEvent_Time_msec, &b_UnpackEvent_Time_msec);
	fData->SetBranchAddress("UnpackEvent.rTime", UnpackEvent_rTime, &b_UnpackEvent_rTime);
	fData->SetBranchAddress("GeCluster", &GeCluster_, &b_GeCluster_);
	fData->SetBranchAddress("GeCluster.fUniqueID", GeCluster_fUniqueID, &b_GeCluster_fUniqueID);
	fData->SetBranchAddress("GeCluster.fBits", GeCluster_fBits, &b_GeCluster_fBits);
	fData->SetBranchAddress("GeCluster.id", GeCluster_id, &b_GeCluster_id);
	fData->SetBranchAddress("GeCluster.fpl", GeCluster_fpl, &b_GeCluster_fpl);
	fData->SetBranchAddress("GeCluster.name", GeCluster_name, &b_GeCluster_name);
	fData->SetBranchAddress("GeCluster.fDataState", GeCluster_fDataState, &b_GeCluster_fDataState);
	fData->SetBranchAddress("GeCluster.channel", GeCluster_channel, &b_GeCluster_channel);
	fData->SetBranchAddress("GeCluster.fADCe", GeCluster_fADCe, &b_GeCluster_fADCe);
	fData->SetBranchAddress("GeCluster.fADCt", GeCluster_fADCt, &b_GeCluster_fADCt);
	fData->SetBranchAddress("GeCluster.fTDCs", GeCluster_fTDCs, &b_GeCluster_fTDCs);
	fData->SetBranchAddress("GeCluster.fTDCl", GeCluster_fTDCl, &b_GeCluster_fTDCl);
	fData->SetBranchAddress("GeCluster.fEnergy", GeCluster_fEnergy, &b_GeCluster_fEnergy);
	fData->SetBranchAddress("GeCluster.fTime", GeCluster_fTime, &b_GeCluster_fTime);
	fData->SetBranchAddress("GeAddback", &GeAddback_, &b_GeAddback_);
	fData->SetBranchAddress("GeAddback.fUniqueID", GeAddback_fUniqueID, &b_GeAddback_fUniqueID);
	fData->SetBranchAddress("GeAddback.fBits", GeAddback_fBits, &b_GeAddback_fBits);
	fData->SetBranchAddress("GeAddback.id", GeAddback_id, &b_GeAddback_id);
	fData->SetBranchAddress("GeAddback.fpl", GeAddback_fpl, &b_GeAddback_fpl);
	fData->SetBranchAddress("GeAddback.name", GeAddback_name, &b_GeAddback_name);
	fData->SetBranchAddress("GeAddback.fDataState", GeAddback_fDataState, &b_GeAddback_fDataState);
	fData->SetBranchAddress("GeAddback.channel", GeAddback_channel, &b_GeAddback_channel);
	fData->SetBranchAddress("GeAddback.fADCe", GeAddback_fADCe, &b_GeAddback_fADCe);
	fData->SetBranchAddress("GeAddback.fADCt", GeAddback_fADCt, &b_GeAddback_fADCt);
	fData->SetBranchAddress("GeAddback.fTDCs", GeAddback_fTDCs, &b_GeAddback_fTDCs);
	fData->SetBranchAddress("GeAddback.fTDCl", GeAddback_fTDCl, &b_GeAddback_fTDCl);
	fData->SetBranchAddress("GeAddback.fEnergy", GeAddback_fEnergy, &b_GeAddback_fEnergy);
	fData->SetBranchAddress("GeAddback.fTime", GeAddback_fTime, &b_GeAddback_fTime);
	fData->SetBranchAddress("LaBr", &LaBr_, &b_LaBr_);
	fData->SetBranchAddress("LaBr.fUniqueID", LaBr_fUniqueID, &b_LaBr_fUniqueID);
	fData->SetBranchAddress("LaBr.fBits", LaBr_fBits, &b_LaBr_fBits);
	fData->SetBranchAddress("LaBr.id", LaBr_id, &b_LaBr_id);
	fData->SetBranchAddress("LaBr.fpl", LaBr_fpl, &b_LaBr_fpl);
	fData->SetBranchAddress("LaBr.name", LaBr_name, &b_LaBr_name);
	fData->SetBranchAddress("LaBr.fDataState", LaBr_fDataState, &b_LaBr_fDataState);
	fData->SetBranchAddress("LaBr.channel", LaBr_channel, &b_LaBr_channel);
	fData->SetBranchAddress("LaBr.fADC", LaBr_fADC, &b_LaBr_fADC);
	fData->SetBranchAddress("LaBr.fTDC_srt", LaBr_fTDC_srt, &b_LaBr_fTDC_srt);
	fData->SetBranchAddress("LaBr.fTDC_lrt", LaBr_fTDC_lrt, &b_LaBr_fTDC_lrt);
	fData->SetBranchAddress("LaBr.fEnergy", LaBr_fEnergy, &b_LaBr_fEnergy);
	fData->SetBranchAddress("LaBr.fTime_srt", LaBr_fTime_srt, &b_LaBr_fTime_srt);
	fData->SetBranchAddress("LaBr.fTime_lrt", LaBr_fTime_lrt, &b_LaBr_fTime_lrt);
	fData->SetBranchAddress("BetaPlasticUp", &BetaPlasticUp_, &b_BetaPlasticUp_);
	fData->SetBranchAddress("BetaPlasticUp.fUniqueID", BetaPlasticUp_fUniqueID, &b_BetaPlasticUp_fUniqueID);
	fData->SetBranchAddress("BetaPlasticUp.fBits", BetaPlasticUp_fBits, &b_BetaPlasticUp_fBits);
	fData->SetBranchAddress("BetaPlasticUp.id", BetaPlasticUp_id, &b_BetaPlasticUp_id);
	fData->SetBranchAddress("BetaPlasticUp.fpl", BetaPlasticUp_fpl, &b_BetaPlasticUp_fpl);
	fData->SetBranchAddress("BetaPlasticUp.name", BetaPlasticUp_name, &b_BetaPlasticUp_name);
	fData->SetBranchAddress("BetaPlasticUp.fDataState", BetaPlasticUp_fDataState, &b_BetaPlasticUp_fDataState);
	fData->SetBranchAddress("BetaPlasticUp.ADC_L_Beta", BetaPlasticUp_ADC_L_Beta, &b_BetaPlasticUp_ADC_L_Beta);
	fData->SetBranchAddress("BetaPlasticUp.ADC_R_Beta", BetaPlasticUp_ADC_R_Beta, &b_BetaPlasticUp_ADC_R_Beta);
	fData->SetBranchAddress("BetaPlasticUp.ADC_L_Beam", BetaPlasticUp_ADC_L_Beam, &b_BetaPlasticUp_ADC_L_Beam);
	fData->SetBranchAddress("BetaPlasticUp.ADC_R_Beam", BetaPlasticUp_ADC_R_Beam, &b_BetaPlasticUp_ADC_R_Beam);
	fData->SetBranchAddress("BetaPlasticUp.TDC_L_lrt", BetaPlasticUp_TDC_L_lrt, &b_BetaPlasticUp_TDC_L_lrt);
	fData->SetBranchAddress("BetaPlasticUp.TDC_R_lrt", BetaPlasticUp_TDC_R_lrt, &b_BetaPlasticUp_TDC_R_lrt);
	fData->SetBranchAddress("BetaPlasticUp.TDC_L_srt", BetaPlasticUp_TDC_L_srt, &b_BetaPlasticUp_TDC_L_srt);
	fData->SetBranchAddress("BetaPlasticUp.TDC_R_srt", BetaPlasticUp_TDC_R_srt, &b_BetaPlasticUp_TDC_R_srt);
	fData->SetBranchAddress("BetaPlasticUp.Time_L_srt", BetaPlasticUp_Time_L_srt, &b_BetaPlasticUp_Time_L_srt);
	fData->SetBranchAddress("BetaPlasticUp.Time_R_srt", BetaPlasticUp_Time_R_srt, &b_BetaPlasticUp_Time_R_srt);
	fData->SetBranchAddress("BetaPlasticUp.Time_L_lrt", BetaPlasticUp_Time_L_lrt, &b_BetaPlasticUp_Time_L_lrt);
	fData->SetBranchAddress("BetaPlasticUp.Time_R_lrt", BetaPlasticUp_Time_R_lrt, &b_BetaPlasticUp_Time_R_lrt);
	fData->SetBranchAddress("BetaPlasticDown", &BetaPlasticDown_, &b_BetaPlasticDown_);
	fData->SetBranchAddress("BetaPlasticDown.fUniqueID", BetaPlasticDown_fUniqueID, &b_BetaPlasticDown_fUniqueID);
	fData->SetBranchAddress("BetaPlasticDown.fBits", BetaPlasticDown_fBits, &b_BetaPlasticDown_fBits);
	fData->SetBranchAddress("BetaPlasticDown.id", BetaPlasticDown_id, &b_BetaPlasticDown_id);
	fData->SetBranchAddress("BetaPlasticDown.fpl", BetaPlasticDown_fpl, &b_BetaPlasticDown_fpl);
	fData->SetBranchAddress("BetaPlasticDown.name", BetaPlasticDown_name, &b_BetaPlasticDown_name);
	fData->SetBranchAddress("BetaPlasticDown.fDataState", BetaPlasticDown_fDataState, &b_BetaPlasticDown_fDataState);
	fData->SetBranchAddress("BetaPlasticDown.ADC_L_Beta", BetaPlasticDown_ADC_L_Beta, &b_BetaPlasticDown_ADC_L_Beta);
	fData->SetBranchAddress("BetaPlasticDown.ADC_R_Beta", BetaPlasticDown_ADC_R_Beta, &b_BetaPlasticDown_ADC_R_Beta);
	fData->SetBranchAddress("BetaPlasticDown.ADC_L_Beam", BetaPlasticDown_ADC_L_Beam, &b_BetaPlasticDown_ADC_L_Beam);
	fData->SetBranchAddress("BetaPlasticDown.ADC_R_Beam", BetaPlasticDown_ADC_R_Beam, &b_BetaPlasticDown_ADC_R_Beam);
	fData->SetBranchAddress("BetaPlasticDown.TDC_L_lrt", BetaPlasticDown_TDC_L_lrt, &b_BetaPlasticDown_TDC_L_lrt);
	fData->SetBranchAddress("BetaPlasticDown.TDC_R_lrt", BetaPlasticDown_TDC_R_lrt, &b_BetaPlasticDown_TDC_R_lrt);
	fData->SetBranchAddress("BetaPlasticDown.TDC_L_srt", BetaPlasticDown_TDC_L_srt, &b_BetaPlasticDown_TDC_L_srt);
	fData->SetBranchAddress("BetaPlasticDown.TDC_R_srt", BetaPlasticDown_TDC_R_srt, &b_BetaPlasticDown_TDC_R_srt);
	fData->SetBranchAddress("BetaPlasticDown.Time_L_srt", BetaPlasticDown_Time_L_srt, &b_BetaPlasticDown_Time_L_srt);
	fData->SetBranchAddress("BetaPlasticDown.Time_R_srt", BetaPlasticDown_Time_R_srt, &b_BetaPlasticDown_Time_R_srt);
	fData->SetBranchAddress("BetaPlasticDown.Time_L_lrt", BetaPlasticDown_Time_L_lrt, &b_BetaPlasticDown_Time_L_lrt);
	fData->SetBranchAddress("BetaPlasticDown.Time_R_lrt", BetaPlasticDown_Time_R_lrt, &b_BetaPlasticDown_Time_R_lrt);
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
	fData->SetBranchAddress("BigRIPSRaw", &BigRIPSRaw_, &b_BigRIPSRaw_);
	fData->SetBranchAddress("BigRIPSRaw.fUniqueID", BigRIPSRaw_fUniqueID, &b_BigRIPSRaw_fUniqueID);
	fData->SetBranchAddress("BigRIPSRaw.fBits", BigRIPSRaw_fBits, &b_BigRIPSRaw_fBits);
	fData->SetBranchAddress("BigRIPSRaw.fName", BigRIPSRaw_fName, &b_BigRIPSRaw_fName);
	fData->SetBranchAddress("BigRIPSRaw.fTitle", BigRIPSRaw_fTitle, &b_BigRIPSRaw_fTitle);
	fData->SetBranchAddress("BigRIPSRaw.F3PPAC1_X1", BigRIPSRaw_F3PPAC1_X1, &b_BigRIPSRaw_F3PPAC1_X1);
	fData->SetBranchAddress("BigRIPSRaw.F3PPAC1_X2", BigRIPSRaw_F3PPAC1_X2, &b_BigRIPSRaw_F3PPAC1_X2);
	fData->SetBranchAddress("BigRIPSRaw.F3PPAC2_X1", BigRIPSRaw_F3PPAC2_X1, &b_BigRIPSRaw_F3PPAC2_X1);
	fData->SetBranchAddress("BigRIPSRaw.F3PPAC2_X2", BigRIPSRaw_F3PPAC2_X2, &b_BigRIPSRaw_F3PPAC2_X2);
	fData->SetBranchAddress("BigRIPSRaw.F5PPAC1_X1", BigRIPSRaw_F5PPAC1_X1, &b_BigRIPSRaw_F5PPAC1_X1);
	fData->SetBranchAddress("BigRIPSRaw.F5PPAC1_X2", BigRIPSRaw_F5PPAC1_X2, &b_BigRIPSRaw_F5PPAC1_X2);
	fData->SetBranchAddress("BigRIPSRaw.F5PPAC2_X1", BigRIPSRaw_F5PPAC2_X1, &b_BigRIPSRaw_F5PPAC2_X1);
	fData->SetBranchAddress("BigRIPSRaw.F5PPAC2_X2", BigRIPSRaw_F5PPAC2_X2, &b_BigRIPSRaw_F5PPAC2_X2);
	fData->SetBranchAddress("BigRIPSRaw.F3SCI_L", BigRIPSRaw_F3SCI_L, &b_BigRIPSRaw_F3SCI_L);
	fData->SetBranchAddress("BigRIPSRaw.F3SCI_R", BigRIPSRaw_F3SCI_R, &b_BigRIPSRaw_F3SCI_R);
	fData->SetBranchAddress("BigRIPSRaw.F7SCI_L", BigRIPSRaw_F7SCI_L, &b_BigRIPSRaw_F7SCI_L);
	fData->SetBranchAddress("BigRIPSRaw.F7SCI_R", BigRIPSRaw_F7SCI_R, &b_BigRIPSRaw_F7SCI_R);
	fData->SetBranchAddress("BigRIPSRaw.F11PPAC1_X1", BigRIPSRaw_F11PPAC1_X1, &b_BigRIPSRaw_F11PPAC1_X1);
	fData->SetBranchAddress("BigRIPSRaw.F11PPAC1_Y1", BigRIPSRaw_F11PPAC1_Y1, &b_BigRIPSRaw_F11PPAC1_Y1);
	fData->SetBranchAddress("BigRIPSRaw.F11PPAC1_X2", BigRIPSRaw_F11PPAC1_X2, &b_BigRIPSRaw_F11PPAC1_X2);
	fData->SetBranchAddress("BigRIPSRaw.F11PPAC1_Y2", BigRIPSRaw_F11PPAC1_Y2, &b_BigRIPSRaw_F11PPAC1_Y2);
	fData->SetBranchAddress("BigRIPSRaw.F11PPAC2_X1", BigRIPSRaw_F11PPAC2_X1, &b_BigRIPSRaw_F11PPAC2_X1);
	fData->SetBranchAddress("BigRIPSRaw.F11PPAC2_Y1", BigRIPSRaw_F11PPAC2_Y1, &b_BigRIPSRaw_F11PPAC2_Y1);
	fData->SetBranchAddress("BigRIPSRaw.F11PPAC2_X2", BigRIPSRaw_F11PPAC2_X2, &b_BigRIPSRaw_F11PPAC2_X2);
	fData->SetBranchAddress("BigRIPSRaw.F11PPAC2_Y2", BigRIPSRaw_F11PPAC2_Y2, &b_BigRIPSRaw_F11PPAC2_Y2);
	fData->SetBranchAddress("BigRIPSRaw.F11SCI_L", BigRIPSRaw_F11SCI_L, &b_BigRIPSRaw_F11SCI_L);
	fData->SetBranchAddress("BigRIPSRaw.F11SCI_R", BigRIPSRaw_F11SCI_R, &b_BigRIPSRaw_F11SCI_R);
	fData->SetBranchAddress("BigRIPSRaw.DE", BigRIPSRaw_DE, &b_BigRIPSRaw_DE);
	fData->SetBranchAddress("BigRIPSRaw.F3PPAC1_TDiffX", BigRIPSRaw_F3PPAC1_TDiffX, &b_BigRIPSRaw_F3PPAC1_TDiffX);
	fData->SetBranchAddress("BigRIPSRaw.F3PPAC2_TDiffX", BigRIPSRaw_F3PPAC2_TDiffX, &b_BigRIPSRaw_F3PPAC2_TDiffX);
	fData->SetBranchAddress("BigRIPSRaw.F5PPAC1_TDiffX", BigRIPSRaw_F5PPAC1_TDiffX, &b_BigRIPSRaw_F5PPAC1_TDiffX);
	fData->SetBranchAddress("BigRIPSRaw.F5PPAC2_TDiffX", BigRIPSRaw_F5PPAC2_TDiffX, &b_BigRIPSRaw_F5PPAC2_TDiffX);
	fData->SetBranchAddress("BigRIPSRaw.F3PPAC1_X", BigRIPSRaw_F3PPAC1_X, &b_BigRIPSRaw_F3PPAC1_X);
	fData->SetBranchAddress("BigRIPSRaw.F3PPAC2_X", BigRIPSRaw_F3PPAC2_X, &b_BigRIPSRaw_F3PPAC2_X);
	fData->SetBranchAddress("BigRIPSRaw.F5PPAC1_X", BigRIPSRaw_F5PPAC1_X, &b_BigRIPSRaw_F5PPAC1_X);
	fData->SetBranchAddress("BigRIPSRaw.F5PPAC2_X", BigRIPSRaw_F5PPAC2_X, &b_BigRIPSRaw_F5PPAC2_X);
	fData->SetBranchAddress("BigRIPSRaw.F3_X", BigRIPSRaw_F3_X, &b_BigRIPSRaw_F3_X);
	fData->SetBranchAddress("BigRIPSRaw.F3_A", BigRIPSRaw_F3_A, &b_BigRIPSRaw_F3_A);
	fData->SetBranchAddress("BigRIPSRaw.F5_X", BigRIPSRaw_F5_X, &b_BigRIPSRaw_F5_X);
	fData->SetBranchAddress("BigRIPSRaw.F5_A", BigRIPSRaw_F5_A, &b_BigRIPSRaw_F5_A);
	fData->SetBranchAddress("BigRIPSRaw.TF3SCI_L", BigRIPSRaw_TF3SCI_L, &b_BigRIPSRaw_TF3SCI_L);
	fData->SetBranchAddress("BigRIPSRaw.TF3SCI_R", BigRIPSRaw_TF3SCI_R, &b_BigRIPSRaw_TF3SCI_R);
	fData->SetBranchAddress("BigRIPSRaw.TF7SCI_L", BigRIPSRaw_TF7SCI_L, &b_BigRIPSRaw_TF7SCI_L);
	fData->SetBranchAddress("BigRIPSRaw.TF7SCI_R", BigRIPSRaw_TF7SCI_R, &b_BigRIPSRaw_TF7SCI_R);
	fData->SetBranchAddress("BigRIPSRaw.Delta_F3F5", BigRIPSRaw_Delta_F3F5, &b_BigRIPSRaw_Delta_F3F5);
	fData->SetBranchAddress("BigRIPSRaw.TOF_F3F7", BigRIPSRaw_TOF_F3F7, &b_BigRIPSRaw_TOF_F3F7);
	fData->SetBranchAddress("BigRIPSRaw.dT_F3L", BigRIPSRaw_dT_F3L, &b_BigRIPSRaw_dT_F3L);
	fData->SetBranchAddress("BigRIPSRaw.dT_F3R", BigRIPSRaw_dT_F3R, &b_BigRIPSRaw_dT_F3R);
	fData->SetBranchAddress("BigRIPSRaw.dT_F7L", BigRIPSRaw_dT_F7L, &b_BigRIPSRaw_dT_F7L);
	fData->SetBranchAddress("BigRIPSRaw.dT_F7R", BigRIPSRaw_dT_F7R, &b_BigRIPSRaw_dT_F7R);
	fData->SetBranchAddress("BigRIPSRaw.dT_F3F11L", BigRIPSRaw_dT_F3F11L, &b_BigRIPSRaw_dT_F3F11L);
	fData->SetBranchAddress("BigRIPSRaw.dT_F3F11R", BigRIPSRaw_dT_F3F11R, &b_BigRIPSRaw_dT_F3F11R);
	fData->SetBranchAddress("BigRIPSRaw.ToF_F7", BigRIPSRaw_ToF_F7, &b_BigRIPSRaw_ToF_F7);
	fData->SetBranchAddress("BigRIPSRaw.ToF_F11", BigRIPSRaw_ToF_F11, &b_BigRIPSRaw_ToF_F11);
	fData->SetBranchAddress("BigRIPSRaw.Beta_F3F5", BigRIPSRaw_Beta_F3F5, &b_BigRIPSRaw_Beta_F3F5);
	fData->SetBranchAddress("BigRIPSRaw.Beta_F5F7", BigRIPSRaw_Beta_F5F7, &b_BigRIPSRaw_Beta_F5F7);
	fData->SetBranchAddress("BigRIPSRaw.AoQ_F3F5", BigRIPSRaw_AoQ_F3F5, &b_BigRIPSRaw_AoQ_F3F5);
	fData->SetBranchAddress("BigRIPSRaw.Zed_F11", BigRIPSRaw_Zed_F11, &b_BigRIPSRaw_Zed_F11);
}

void EUDataGe::GetTsEntry(std::map<Long64_t, Long64_t> &mts)
{
	Long64_t nentries = fData->GetEntriesFast();
	for (Long64_t jentry=0; jentry<nentries;jentry++)
	{
		fData->GetEntry(jentry);
		mts.insert(std::pair<Long64_t, Long64_t> (EventInfo_timestamp[0], jentry));
	}
}
