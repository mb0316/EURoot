#ifndef EUDATAGE_H
#define EUDATAGE_H

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

const Int_t kMaxUnpackEvent = 1;
const Int_t kMaxGeCluster = 84;
const Int_t kMaxGeAddback = 84;
const Int_t kMaxLaBr = 18;
const Int_t kMaxBetaPlasticUp = 1;
const Int_t kMaxBetaPlasticDown = 1;
const Int_t kMaxEventInfo = 1;
const Int_t kMaxBigRIPSRaw = 10;

class EUDataGe : public EUData
{

	public :
		// Declaration of leaf types
		Int_t           UnpackEvent_;
		UInt_t          UnpackEvent_fUniqueID[kMaxUnpackEvent];   //[UnpackEvent_]
		UInt_t          UnpackEvent_fBits[kMaxUnpackEvent];   //[UnpackEvent_]
		TString         UnpackEvent_fName[kMaxUnpackEvent];
		TString         UnpackEvent_fTitle[kMaxUnpackEvent];
		Bool_t          UnpackEvent_fbIsValid[kMaxUnpackEvent];   //[UnpackEvent_]
		Short_t         UnpackEvent_fIdentifier[kMaxUnpackEvent];   //[UnpackEvent_]
		Int_t           UnpackEvent_detBP[kMaxUnpackEvent][16];   //[UnpackEvent_]
		Int_t           UnpackEvent_detHP[kMaxUnpackEvent];   //[UnpackEvent_]
		Int_t           UnpackEvent_vme1_1[kMaxUnpackEvent][32];   //[UnpackEvent_]
		Int_t           UnpackEvent_vme1_2[kMaxUnpackEvent][32];   //[UnpackEvent_]
		Int_t           UnpackEvent_nhit1[kMaxUnpackEvent][128];   //[UnpackEvent_]
		Int_t           UnpackEvent_vme1s[kMaxUnpackEvent][128][10];   //[UnpackEvent_]
		Int_t           UnpackEvent_vme4_5[kMaxUnpackEvent][30][4][2];   //[UnpackEvent_]
		Int_t           UnpackEvent_vme6[kMaxUnpackEvent][4][32];   //[UnpackEvent_]
		Int_t           UnpackEvent_vmel[kMaxUnpackEvent][128][3];   //[UnpackEvent_]
		Int_t           UnpackEvent_nhitl[kMaxUnpackEvent][128];   //[UnpackEvent_]
		Int_t           UnpackEvent_hp[kMaxUnpackEvent][4];   //[UnpackEvent_]
		Int_t           UnpackEvent_vme20[kMaxUnpackEvent][21][64];   //[UnpackEvent_]
		Int_t           UnpackEvent_vmehit[kMaxUnpackEvent][21][64][10];   //[UnpackEvent_]
		Int_t           UnpackEvent_nhit[kMaxUnpackEvent][21][64];   //[UnpackEvent_]
		Int_t           UnpackEvent_lenUSR[kMaxUnpackEvent];   //[UnpackEvent_]
		Int_t           UnpackEvent_lenDGF[kMaxUnpackEvent];   //[UnpackEvent_]
		Int_t           UnpackEvent_lenGeTDC[kMaxUnpackEvent];   //[UnpackEvent_]
		UInt_t          UnpackEvent_lupotslo[kMaxUnpackEvent];   //[UnpackEvent_]
		UInt_t          UnpackEvent_lupotshi[kMaxUnpackEvent];   //[UnpackEvent_]
		Int_t           UnpackEvent_qlength[kMaxUnpackEvent];   //[UnpackEvent_]
		Int_t           UnpackEvent_qtype[kMaxUnpackEvent];   //[UnpackEvent_]
		Int_t           UnpackEvent_qsubtype[kMaxUnpackEvent];   //[UnpackEvent_]
		Int_t           UnpackEvent_qdummy[kMaxUnpackEvent];   //[UnpackEvent_]
		Int_t           UnpackEvent_qtrigger[kMaxUnpackEvent];   //[UnpackEvent_]
		Int_t           UnpackEvent_qevent_nr[kMaxUnpackEvent];   //[UnpackEvent_]
		Int_t           UnpackEvent_Time_sec[kMaxUnpackEvent];   //[UnpackEvent_]
		Int_t           UnpackEvent_Time_msec[kMaxUnpackEvent];   //[UnpackEvent_]
		Float_t         UnpackEvent_rTime[kMaxUnpackEvent];   //[UnpackEvent_]
		Int_t           GeCluster_;
		UInt_t          GeCluster_fUniqueID[kMaxGeCluster];   //[GeCluster_]
		UInt_t          GeCluster_fBits[kMaxGeCluster];   //[GeCluster_]
		Int_t           GeCluster_id[kMaxGeCluster];   //[GeCluster_]
		Int_t           GeCluster_fpl[kMaxGeCluster];   //[GeCluster_]
		TString         GeCluster_name[kMaxGeCluster];
		Int_t           GeCluster_fDataState[kMaxGeCluster];   //[GeCluster_]
		Int_t           GeCluster_channel[kMaxGeCluster];   //[GeCluster_]
		Int_t           GeCluster_fADCe[kMaxGeCluster];   //[GeCluster_]
		Int_t           GeCluster_fADCt[kMaxGeCluster];   //[GeCluster_]
		Int_t           GeCluster_fTDCs[kMaxGeCluster];   //[GeCluster_]
		Int_t           GeCluster_fTDCl[kMaxGeCluster];   //[GeCluster_]
		Double_t        GeCluster_fEnergy[kMaxGeCluster];   //[GeCluster_]
		Double_t        GeCluster_fTime[kMaxGeCluster];   //[GeCluster_]
		Int_t           GeAddback_;
		UInt_t          GeAddback_fUniqueID[kMaxGeAddback];   //[GeAddback_]
		UInt_t          GeAddback_fBits[kMaxGeAddback];   //[GeAddback_]
		Int_t           GeAddback_id[kMaxGeAddback];   //[GeAddback_]
		Int_t           GeAddback_fpl[kMaxGeAddback];   //[GeAddback_]
		TString         GeAddback_name[kMaxGeAddback];
		Int_t           GeAddback_fDataState[kMaxGeAddback];   //[GeAddback_]
		Int_t           GeAddback_channel[kMaxGeAddback];   //[GeAddback_]
		Int_t           GeAddback_fADCe[kMaxGeAddback];   //[GeAddback_]
		Int_t           GeAddback_fADCt[kMaxGeAddback];   //[GeAddback_]
		Int_t           GeAddback_fTDCs[kMaxGeAddback];   //[GeAddback_]
		Int_t           GeAddback_fTDCl[kMaxGeAddback];   //[GeAddback_]
		Double_t        GeAddback_fEnergy[kMaxGeAddback];   //[GeAddback_]
		Double_t        GeAddback_fTime[kMaxGeAddback];   //[GeAddback_]
		Int_t           LaBr_;
		UInt_t          LaBr_fUniqueID[kMaxLaBr];   //[LaBr_]
		UInt_t          LaBr_fBits[kMaxLaBr];   //[LaBr_]
		Int_t           LaBr_id[kMaxLaBr];   //[LaBr_]
		Int_t           LaBr_fpl[kMaxLaBr];   //[LaBr_]
		TString         LaBr_name[kMaxLaBr];
		Int_t           LaBr_fDataState[kMaxLaBr];   //[LaBr_]
		Int_t           LaBr_channel[kMaxLaBr];   //[LaBr_]
		Int_t           LaBr_fADC[kMaxLaBr];   //[LaBr_]
		Int_t           LaBr_fTDC_srt[kMaxLaBr];   //[LaBr_]
		Int_t           LaBr_fTDC_lrt[kMaxLaBr];   //[LaBr_]
		Double_t        LaBr_fEnergy[kMaxLaBr];   //[LaBr_]
		Double_t        LaBr_fTime_srt[kMaxLaBr];   //[LaBr_]
		Double_t        LaBr_fTime_lrt[kMaxLaBr];   //[LaBr_]
		Int_t           BetaPlasticUp_;
		UInt_t          BetaPlasticUp_fUniqueID[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		UInt_t          BetaPlasticUp_fBits[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		Int_t           BetaPlasticUp_id[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		Int_t           BetaPlasticUp_fpl[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		TString         BetaPlasticUp_name[kMaxBetaPlasticUp];
		Int_t           BetaPlasticUp_fDataState[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		Int_t           BetaPlasticUp_ADC_L_Beta[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		Int_t           BetaPlasticUp_ADC_R_Beta[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		Int_t           BetaPlasticUp_ADC_L_Beam[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		Int_t           BetaPlasticUp_ADC_R_Beam[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		Int_t           BetaPlasticUp_TDC_L_lrt[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		Int_t           BetaPlasticUp_TDC_R_lrt[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		Int_t           BetaPlasticUp_TDC_L_srt[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		Int_t           BetaPlasticUp_TDC_R_srt[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		Double_t        BetaPlasticUp_Time_L_srt[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		Double_t        BetaPlasticUp_Time_R_srt[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		Double_t        BetaPlasticUp_Time_L_lrt[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		Double_t        BetaPlasticUp_Time_R_lrt[kMaxBetaPlasticUp];   //[BetaPlasticUp_]
		Int_t           BetaPlasticDown_;
		UInt_t          BetaPlasticDown_fUniqueID[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		UInt_t          BetaPlasticDown_fBits[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		Int_t           BetaPlasticDown_id[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		Int_t           BetaPlasticDown_fpl[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		TString         BetaPlasticDown_name[kMaxBetaPlasticDown];
		Int_t           BetaPlasticDown_fDataState[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		Int_t           BetaPlasticDown_ADC_L_Beta[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		Int_t           BetaPlasticDown_ADC_R_Beta[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		Int_t           BetaPlasticDown_ADC_L_Beam[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		Int_t           BetaPlasticDown_ADC_R_Beam[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		Int_t           BetaPlasticDown_TDC_L_lrt[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		Int_t           BetaPlasticDown_TDC_R_lrt[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		Int_t           BetaPlasticDown_TDC_L_srt[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		Int_t           BetaPlasticDown_TDC_R_srt[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		Double_t        BetaPlasticDown_Time_L_srt[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		Double_t        BetaPlasticDown_Time_R_srt[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		Double_t        BetaPlasticDown_Time_L_lrt[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
		Double_t        BetaPlasticDown_Time_R_lrt[kMaxBetaPlasticDown];   //[BetaPlasticDown_]
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
		Int_t           BigRIPSRaw_;
		UInt_t          BigRIPSRaw_fUniqueID[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_fBits[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		TString         BigRIPSRaw_fName[kMaxBigRIPSRaw];
		TString         BigRIPSRaw_fTitle[kMaxBigRIPSRaw];
		UInt_t          BigRIPSRaw_F3PPAC1_X1[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F3PPAC1_X2[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F3PPAC2_X1[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F3PPAC2_X2[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F5PPAC1_X1[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F5PPAC1_X2[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F5PPAC2_X1[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F5PPAC2_X2[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F3SCI_L[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F3SCI_R[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F7SCI_L[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F7SCI_R[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F11PPAC1_X1[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F11PPAC1_Y1[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F11PPAC1_X2[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F11PPAC1_Y2[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F11PPAC2_X1[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F11PPAC2_Y1[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F11PPAC2_X2[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F11PPAC2_Y2[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F11SCI_L[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		UInt_t          BigRIPSRaw_F11SCI_R[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_DE[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_F3PPAC1_TDiffX[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_F3PPAC2_TDiffX[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_F5PPAC1_TDiffX[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_F5PPAC2_TDiffX[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_F3PPAC1_X[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_F3PPAC2_X[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_F5PPAC1_X[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_F5PPAC2_X[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_F3_X[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_F3_A[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_F5_X[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_F5_A[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_TF3SCI_L[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_TF3SCI_R[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_TF7SCI_L[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_TF7SCI_R[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_Delta_F3F5[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_TOF_F3F7[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_dT_F3L[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_dT_F3R[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_dT_F7L[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_dT_F7R[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_dT_F3F11L[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_dT_F3F11R[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_ToF_F7[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_ToF_F11[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_Beta_F3F5[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_Beta_F5F7[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_AoQ_F3F5[kMaxBigRIPSRaw];   //[BigRIPSRaw_]
		Float_t         BigRIPSRaw_Zed_F11[kMaxBigRIPSRaw];   //[BigRIPSRaw_]

		// List of branches
		TBranch        *b_UnpackEvent_;   //!
		TBranch        *b_UnpackEvent_fUniqueID;   //!
		TBranch        *b_UnpackEvent_fBits;   //!
		TBranch        *b_UnpackEvent_fName;   //!
		TBranch        *b_UnpackEvent_fTitle;   //!
		TBranch        *b_UnpackEvent_fbIsValid;   //!
		TBranch        *b_UnpackEvent_fIdentifier;   //!
		TBranch        *b_UnpackEvent_detBP;   //!
		TBranch        *b_UnpackEvent_detHP;   //!
		TBranch        *b_UnpackEvent_vme1_1;   //!
		TBranch        *b_UnpackEvent_vme1_2;   //!
		TBranch        *b_UnpackEvent_nhit1;   //!
		TBranch        *b_UnpackEvent_vme1s;   //!
		TBranch        *b_UnpackEvent_vme4_5;   //!
		TBranch        *b_UnpackEvent_vme6;   //!
		TBranch        *b_UnpackEvent_vmel;   //!
		TBranch        *b_UnpackEvent_nhitl;   //!
		TBranch        *b_UnpackEvent_hp;   //!
		TBranch        *b_UnpackEvent_vme20;   //!
		TBranch        *b_UnpackEvent_vmehit;   //!
		TBranch        *b_UnpackEvent_nhit;   //!
		TBranch        *b_UnpackEvent_lenUSR;   //!
		TBranch        *b_UnpackEvent_lenDGF;   //!
		TBranch        *b_UnpackEvent_lenGeTDC;   //!
		TBranch        *b_UnpackEvent_lupotslo;   //!
		TBranch        *b_UnpackEvent_lupotshi;   //!
		TBranch        *b_UnpackEvent_qlength;   //!
		TBranch        *b_UnpackEvent_qtype;   //!
		TBranch        *b_UnpackEvent_qsubtype;   //!
		TBranch        *b_UnpackEvent_qdummy;   //!
		TBranch        *b_UnpackEvent_qtrigger;   //!
		TBranch        *b_UnpackEvent_qevent_nr;   //!
		TBranch        *b_UnpackEvent_Time_sec;   //!
		TBranch        *b_UnpackEvent_Time_msec;   //!
		TBranch        *b_UnpackEvent_rTime;   //!
		TBranch        *b_GeCluster_;   //!
		TBranch        *b_GeCluster_fUniqueID;   //!
		TBranch        *b_GeCluster_fBits;   //!
		TBranch        *b_GeCluster_id;   //!
		TBranch        *b_GeCluster_fpl;   //!
		TBranch        *b_GeCluster_name;   //!
		TBranch        *b_GeCluster_fDataState;   //!
		TBranch        *b_GeCluster_channel;   //!
		TBranch        *b_GeCluster_fADCe;   //!
		TBranch        *b_GeCluster_fADCt;   //!
		TBranch        *b_GeCluster_fTDCs;   //!
		TBranch        *b_GeCluster_fTDCl;   //!
		TBranch        *b_GeCluster_fEnergy;   //!
		TBranch        *b_GeCluster_fTime;   //!
		TBranch        *b_GeAddback_;   //!
		TBranch        *b_GeAddback_fUniqueID;   //!
		TBranch        *b_GeAddback_fBits;   //!
		TBranch        *b_GeAddback_id;   //!
		TBranch        *b_GeAddback_fpl;   //!
		TBranch        *b_GeAddback_name;   //!
		TBranch        *b_GeAddback_fDataState;   //!
		TBranch        *b_GeAddback_channel;   //!
		TBranch        *b_GeAddback_fADCe;   //!
		TBranch        *b_GeAddback_fADCt;   //!
		TBranch        *b_GeAddback_fTDCs;   //!
		TBranch        *b_GeAddback_fTDCl;   //!
		TBranch        *b_GeAddback_fEnergy;   //!
		TBranch        *b_GeAddback_fTime;   //!
		TBranch        *b_LaBr_;   //!
		TBranch        *b_LaBr_fUniqueID;   //!
		TBranch        *b_LaBr_fBits;   //!
		TBranch        *b_LaBr_id;   //!
		TBranch        *b_LaBr_fpl;   //!
		TBranch        *b_LaBr_name;   //!
		TBranch        *b_LaBr_fDataState;   //!
		TBranch        *b_LaBr_channel;   //!
		TBranch        *b_LaBr_fADC;   //!
		TBranch        *b_LaBr_fTDC_srt;   //!
		TBranch        *b_LaBr_fTDC_lrt;   //!
		TBranch        *b_LaBr_fEnergy;   //!
		TBranch        *b_LaBr_fTime_srt;   //!
		TBranch        *b_LaBr_fTime_lrt;   //!
		TBranch        *b_BetaPlasticUp_;   //!
		TBranch        *b_BetaPlasticUp_fUniqueID;   //!
		TBranch        *b_BetaPlasticUp_fBits;   //!
		TBranch        *b_BetaPlasticUp_id;   //!
		TBranch        *b_BetaPlasticUp_fpl;   //!
		TBranch        *b_BetaPlasticUp_name;   //!
		TBranch        *b_BetaPlasticUp_fDataState;   //!
		TBranch        *b_BetaPlasticUp_ADC_L_Beta;   //!
		TBranch        *b_BetaPlasticUp_ADC_R_Beta;   //!
		TBranch        *b_BetaPlasticUp_ADC_L_Beam;   //!
		TBranch        *b_BetaPlasticUp_ADC_R_Beam;   //!
		TBranch        *b_BetaPlasticUp_TDC_L_lrt;   //!
		TBranch        *b_BetaPlasticUp_TDC_R_lrt;   //!
		TBranch        *b_BetaPlasticUp_TDC_L_srt;   //!
		TBranch        *b_BetaPlasticUp_TDC_R_srt;   //!
		TBranch        *b_BetaPlasticUp_Time_L_srt;   //!
		TBranch        *b_BetaPlasticUp_Time_R_srt;   //!
		TBranch        *b_BetaPlasticUp_Time_L_lrt;   //!
		TBranch        *b_BetaPlasticUp_Time_R_lrt;   //!
		TBranch        *b_BetaPlasticDown_;   //!
		TBranch        *b_BetaPlasticDown_fUniqueID;   //!
		TBranch        *b_BetaPlasticDown_fBits;   //!
		TBranch        *b_BetaPlasticDown_id;   //!
		TBranch        *b_BetaPlasticDown_fpl;   //!
		TBranch        *b_BetaPlasticDown_name;   //!
		TBranch        *b_BetaPlasticDown_fDataState;   //!
		TBranch        *b_BetaPlasticDown_ADC_L_Beta;   //!
		TBranch        *b_BetaPlasticDown_ADC_R_Beta;   //!
		TBranch        *b_BetaPlasticDown_ADC_L_Beam;   //!
		TBranch        *b_BetaPlasticDown_ADC_R_Beam;   //!
		TBranch        *b_BetaPlasticDown_TDC_L_lrt;   //!
		TBranch        *b_BetaPlasticDown_TDC_R_lrt;   //!
		TBranch        *b_BetaPlasticDown_TDC_L_srt;   //!
		TBranch        *b_BetaPlasticDown_TDC_R_srt;   //!
		TBranch        *b_BetaPlasticDown_Time_L_srt;   //!
		TBranch        *b_BetaPlasticDown_Time_R_srt;   //!
		TBranch        *b_BetaPlasticDown_Time_L_lrt;   //!
		TBranch        *b_BetaPlasticDown_Time_R_lrt;   //!
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
		TBranch        *b_BigRIPSRaw_;   //!
		TBranch        *b_BigRIPSRaw_fUniqueID;   //!
		TBranch        *b_BigRIPSRaw_fBits;   //!
		TBranch        *b_BigRIPSRaw_fName;   //!
		TBranch        *b_BigRIPSRaw_fTitle;   //!
		TBranch        *b_BigRIPSRaw_F3PPAC1_X1;   //!
		TBranch        *b_BigRIPSRaw_F3PPAC1_X2;   //!
		TBranch        *b_BigRIPSRaw_F3PPAC2_X1;   //!
		TBranch        *b_BigRIPSRaw_F3PPAC2_X2;   //!
		TBranch        *b_BigRIPSRaw_F5PPAC1_X1;   //!
		TBranch        *b_BigRIPSRaw_F5PPAC1_X2;   //!
		TBranch        *b_BigRIPSRaw_F5PPAC2_X1;   //!
		TBranch        *b_BigRIPSRaw_F5PPAC2_X2;   //!
		TBranch        *b_BigRIPSRaw_F3SCI_L;   //!
		TBranch        *b_BigRIPSRaw_F3SCI_R;   //!
		TBranch        *b_BigRIPSRaw_F7SCI_L;   //!
		TBranch        *b_BigRIPSRaw_F7SCI_R;   //!
		TBranch        *b_BigRIPSRaw_F11PPAC1_X1;   //!
		TBranch        *b_BigRIPSRaw_F11PPAC1_Y1;   //!
		TBranch        *b_BigRIPSRaw_F11PPAC1_X2;   //!
		TBranch        *b_BigRIPSRaw_F11PPAC1_Y2;   //!
		TBranch        *b_BigRIPSRaw_F11PPAC2_X1;   //!
		TBranch        *b_BigRIPSRaw_F11PPAC2_Y1;   //!
		TBranch        *b_BigRIPSRaw_F11PPAC2_X2;   //!
		TBranch        *b_BigRIPSRaw_F11PPAC2_Y2;   //!
		TBranch        *b_BigRIPSRaw_F11SCI_L;   //!
		TBranch        *b_BigRIPSRaw_F11SCI_R;   //!
		TBranch        *b_BigRIPSRaw_DE;   //!
		TBranch        *b_BigRIPSRaw_F3PPAC1_TDiffX;   //!
		TBranch        *b_BigRIPSRaw_F3PPAC2_TDiffX;   //!
		TBranch        *b_BigRIPSRaw_F5PPAC1_TDiffX;   //!
		TBranch        *b_BigRIPSRaw_F5PPAC2_TDiffX;   //!
		TBranch        *b_BigRIPSRaw_F3PPAC1_X;   //!
		TBranch        *b_BigRIPSRaw_F3PPAC2_X;   //!
		TBranch        *b_BigRIPSRaw_F5PPAC1_X;   //!
		TBranch        *b_BigRIPSRaw_F5PPAC2_X;   //!
		TBranch        *b_BigRIPSRaw_F3_X;   //!
		TBranch        *b_BigRIPSRaw_F3_A;   //!
		TBranch        *b_BigRIPSRaw_F5_X;   //!
		TBranch        *b_BigRIPSRaw_F5_A;   //!
		TBranch        *b_BigRIPSRaw_TF3SCI_L;   //!
		TBranch        *b_BigRIPSRaw_TF3SCI_R;   //!
		TBranch        *b_BigRIPSRaw_TF7SCI_L;   //!
		TBranch        *b_BigRIPSRaw_TF7SCI_R;   //!
		TBranch        *b_BigRIPSRaw_Delta_F3F5;   //!
		TBranch        *b_BigRIPSRaw_TOF_F3F7;   //!
		TBranch        *b_BigRIPSRaw_dT_F3L;   //!
		TBranch        *b_BigRIPSRaw_dT_F3R;   //!
		TBranch        *b_BigRIPSRaw_dT_F7L;   //!
		TBranch        *b_BigRIPSRaw_dT_F7R;   //!
		TBranch        *b_BigRIPSRaw_dT_F3F11L;   //!
		TBranch        *b_BigRIPSRaw_dT_F3F11R;   //!
		TBranch        *b_BigRIPSRaw_ToF_F7;   //!
		TBranch        *b_BigRIPSRaw_ToF_F11;   //!
		TBranch        *b_BigRIPSRaw_Beta_F3F5;   //!
		TBranch        *b_BigRIPSRaw_Beta_F5F7;   //!
		TBranch        *b_BigRIPSRaw_AoQ_F3F5;   //!
		TBranch        *b_BigRIPSRaw_Zed_F11;   //!

		EUDataGe(const char* filename, TTree* tree=0);
		~EUDataGe();
		Int_t	GetEntry(Long64_t entry);
		void	Init(TTree *tree);
		void    GetTsEntry(std::map<Long64_t, Long64_t> &mts);
};
#endif
