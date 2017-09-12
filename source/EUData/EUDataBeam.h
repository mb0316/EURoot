#ifndef EUDATABEAM_H
#define EUDATABEAM_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TObject.h>
#include <TNamed.h>
#include <TVectorT.h>
#include <TMatrixT.h>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "EUData.h"

const Int_t kMaxBigRIPSPPAC = 34;
const Int_t kMaxBigRIPSPlastic = 8;
const Int_t kMaxBigRIPSIC = 2;
const Int_t kMaxBigRIPSFocalPlane = 11;
const Int_t kMaxBigRIPSTOF = 1;
const Int_t kMaxBigRIPSRIPS = 2;
const Int_t kMaxBigRIPSBeam = 1;
const Int_t kMaxRIBeam = 1;
const Int_t kMaxRIBeamOthers = 1;
const Int_t kkMaxEventInfo = 1;

class EUDataBeam : public EUData
{

	public :
		// Declaration of leaf types
		Int_t           EventInfo_;
		UInt_t          EventInfo_fUniqueID[kkMaxEventInfo];   //[EventInfo_]
		UInt_t          EventInfo_fBits[kkMaxEventInfo];   //[EventInfo_]
		TString         EventInfo_fName[kkMaxEventInfo];
		TString         EventInfo_fTitle[kkMaxEventInfo];
		Int_t           EventInfo_runnumber[kkMaxEventInfo];   //[EventInfo_]
		Int_t           EventInfo_eventnumber[kkMaxEventInfo];   //[EventInfo_]
		TString         EventInfo_subsysname[kkMaxEventInfo];
		ULong64_t       EventInfo_timestamp[kkMaxEventInfo];   //[EventInfo_]
		Int_t           EventInfo_comp_val[kkMaxEventInfo];   //[EventInfo_]
		UInt_t          EventInfo_fBit[kkMaxEventInfo];   //[EventInfo_]
		Int_t           BigRIPSPPAC_;
		UInt_t          BigRIPSPPAC_fUniqueID[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		UInt_t          BigRIPSPPAC_fBits[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Int_t           BigRIPSPPAC_id[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Int_t           BigRIPSPPAC_fpl[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		TString         BigRIPSPPAC_name[kMaxBigRIPSPPAC];
		Int_t           BigRIPSPPAC_fDataState[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Double_t        BigRIPSPPAC_xzpos[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Double_t        BigRIPSPPAC_yzpos[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Int_t           BigRIPSPPAC_fTX1Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Int_t           BigRIPSPPAC_fTX2Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Int_t           BigRIPSPPAC_fTY1Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Int_t           BigRIPSPPAC_fTY2Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Int_t           BigRIPSPPAC_fTARaw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Int_t           BigRIPSPPAC_fQX1Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Int_t           BigRIPSPPAC_fQX2Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Int_t           BigRIPSPPAC_fQY1Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Int_t           BigRIPSPPAC_fQY2Raw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Int_t           BigRIPSPPAC_fQARaw[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Double_t        BigRIPSPPAC_fTSumX[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Double_t        BigRIPSPPAC_fTSumY[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Double_t        BigRIPSPPAC_fTDiffX[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Double_t        BigRIPSPPAC_fTDiffY[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Double_t        BigRIPSPPAC_fX[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Double_t        BigRIPSPPAC_fY[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Bool_t          BigRIPSPPAC_fFiredX[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Bool_t          BigRIPSPPAC_fFiredY[kMaxBigRIPSPPAC];   //[BigRIPSPPAC_]
		Int_t           BigRIPSPlastic_;
		UInt_t          BigRIPSPlastic_fUniqueID[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		UInt_t          BigRIPSPlastic_fBits[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		Int_t           BigRIPSPlastic_id[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		Int_t           BigRIPSPlastic_fpl[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		TString         BigRIPSPlastic_name[kMaxBigRIPSPlastic];
		Int_t           BigRIPSPlastic_fDataState[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		Double_t        BigRIPSPlastic_zposition[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		Double_t        BigRIPSPlastic_zoffset[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		Int_t           BigRIPSPlastic_fTLRaw[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		Int_t           BigRIPSPlastic_fTRRaw[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		Int_t           BigRIPSPlastic_fQLRaw[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		Int_t           BigRIPSPlastic_fQRRaw[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		Double_t        BigRIPSPlastic_fTime[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		Double_t        BigRIPSPlastic_fTimeL[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		Double_t        BigRIPSPlastic_fTimeR[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		Double_t        BigRIPSPlastic_fTimeLSlew[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		Double_t        BigRIPSPlastic_fTimeRSlew[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		Double_t        BigRIPSPlastic_fTimeSlew[kMaxBigRIPSPlastic];   //[BigRIPSPlastic_]
		Int_t           BigRIPSIC_;
		UInt_t          BigRIPSIC_fUniqueID[kMaxBigRIPSIC];   //[BigRIPSIC_]
		UInt_t          BigRIPSIC_fBits[kMaxBigRIPSIC];   //[BigRIPSIC_]
		Int_t           BigRIPSIC_id[kMaxBigRIPSIC];   //[BigRIPSIC_]
		Int_t           BigRIPSIC_fpl[kMaxBigRIPSIC];   //[BigRIPSIC_]
		TString         BigRIPSIC_name[kMaxBigRIPSIC];
		Int_t           BigRIPSIC_fDataState[kMaxBigRIPSIC];   //[BigRIPSIC_]
		Double_t        BigRIPSIC_zcoef[kMaxBigRIPSIC][2];   //[BigRIPSIC_]
		Double_t        BigRIPSIC_ionpair[kMaxBigRIPSIC];   //[BigRIPSIC_]
		Int_t           BigRIPSIC_nhitchannel[kMaxBigRIPSIC];   //[BigRIPSIC_]
		Int_t           BigRIPSIC_fADC[kMaxBigRIPSIC][10];   //[BigRIPSIC_]
		Double_t        BigRIPSIC_fEnergy[kMaxBigRIPSIC][10];   //[BigRIPSIC_]
		Double_t        BigRIPSIC_fRawADCSqSum[kMaxBigRIPSIC];   //[BigRIPSIC_]
		Double_t        BigRIPSIC_fRawADCAvSum[kMaxBigRIPSIC];   //[BigRIPSIC_]
		Double_t        BigRIPSIC_fCalMeVSqSum[kMaxBigRIPSIC];   //[BigRIPSIC_]
		Double_t        BigRIPSIC_fCalMeVAvSum[kMaxBigRIPSIC];   //[BigRIPSIC_]
		Int_t           BigRIPSFocalPlane_;
		UInt_t          BigRIPSFocalPlane_fUniqueID[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
		UInt_t          BigRIPSFocalPlane_fBits[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
		Int_t           BigRIPSFocalPlane_id[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
		Int_t           BigRIPSFocalPlane_fpl[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
		TString         BigRIPSFocalPlane_name[kMaxBigRIPSFocalPlane];
		Int_t           BigRIPSFocalPlane_fDataState[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
		TVectorT<double> BigRIPSFocalPlane_opt_vector[kMaxBigRIPSFocalPlane];
		Double_t        BigRIPSFocalPlane_X[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
		Double_t        BigRIPSFocalPlane_A[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
		Double_t        BigRIPSFocalPlane_Y[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
		Double_t        BigRIPSFocalPlane_B[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
		Int_t           BigRIPSFocalPlane_nfired_ppacx[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
		Int_t           BigRIPSFocalPlane_nfired_ppacy[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
		Double_t        BigRIPSFocalPlane_zpos[kMaxBigRIPSFocalPlane];   //[BigRIPSFocalPlane_]
		Int_t           BigRIPSTOF_;
		UInt_t          BigRIPSTOF_fUniqueID[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
		UInt_t          BigRIPSTOF_fBits[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
		Int_t           BigRIPSTOF_id[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
		Int_t           BigRIPSTOF_fpl[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
		TString         BigRIPSTOF_name[kMaxBigRIPSTOF];
		Int_t           BigRIPSTOF_fDataState[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
		Double_t        BigRIPSTOF_tof[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
		Double_t        BigRIPSTOF_clight[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
		Double_t        BigRIPSTOF_length[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
		Double_t        BigRIPSTOF_ulength[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
		Double_t        BigRIPSTOF_dlength[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
		TString         BigRIPSTOF_upstream_plname[kMaxBigRIPSTOF];
		TString         BigRIPSTOF_downstream_plname[kMaxBigRIPSTOF];
		Int_t           BigRIPSTOF_upstream_plfpl[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
		Int_t           BigRIPSTOF_downstream_plfpl[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
		Double_t        BigRIPSTOF_time_offset[kMaxBigRIPSTOF];   //[BigRIPSTOF_]
		Int_t           BigRIPSRIPS_;
		UInt_t          BigRIPSRIPS_fUniqueID[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
		UInt_t          BigRIPSRIPS_fBits[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
		Int_t           BigRIPSRIPS_id[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
		Int_t           BigRIPSRIPS_fpl[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
		TString         BigRIPSRIPS_name[kMaxBigRIPSRIPS];
		Int_t           BigRIPSRIPS_fDataState[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
		Int_t           BigRIPSRIPS_upstream_fpl[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
		Int_t           BigRIPSRIPS_downstream_fpl[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
		Double_t        BigRIPSRIPS_center_brho[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
		Double_t        BigRIPSRIPS_brho[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
		Double_t        BigRIPSRIPS_length[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
		TMatrixT<double> BigRIPSRIPS_matrix[kMaxBigRIPSRIPS];
		Double_t        BigRIPSRIPS_delta[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
		Double_t        BigRIPSRIPS_angle[kMaxBigRIPSRIPS];   //[BigRIPSRIPS_]
		Int_t           BigRIPSBeam_;
		UInt_t          BigRIPSBeam_fUniqueID[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
		UInt_t          BigRIPSBeam_fBits[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
		Int_t           BigRIPSBeam_id[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
		Int_t           BigRIPSBeam_fpl[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
		TString         BigRIPSBeam_name[kMaxBigRIPSBeam];
		Int_t           BigRIPSBeam_fDataState[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
		Double_t        BigRIPSBeam_brho[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
		Double_t        BigRIPSBeam_aoq[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
		Double_t        BigRIPSBeam_zet[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
		Double_t        BigRIPSBeam_beta[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
		Double_t        BigRIPSBeam_clight[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
		Double_t        BigRIPSBeam_mnucleon[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
		Int_t           BigRIPSBeam_nrips[kMaxBigRIPSBeam];   //[BigRIPSBeam_]
		TString         BigRIPSBeam_ripsname[2][kMaxBigRIPSBeam];
		TString         BigRIPSBeam_tofname[kMaxBigRIPSBeam];
		TString         BigRIPSBeam_icname[kMaxBigRIPSBeam];
		Int_t           RIBeam_;
		UInt_t          RIBeam_fUniqueID[kMaxRIBeam];   //[RIBeam_]
		UInt_t          RIBeam_fBits[kMaxRIBeam];   //[RIBeam_]
		Double_t        RIBeam_beta35[kMaxRIBeam];   //[RIBeam_]
		Double_t        RIBeam_beta57[kMaxRIBeam];   //[RIBeam_]
		Double_t        RIBeam_beta711[kMaxRIBeam];   //[RIBeam_]
		Double_t        RIBeam_aoq37[kMaxRIBeam];   //[RIBeam_]
		Double_t        RIBeam_zed[kMaxRIBeam];   //[RIBeam_]
		Int_t           RIBeam_Zed[kMaxRIBeam];   //[RIBeam_]
		Int_t           RIBeam_Mass[kMaxRIBeam];   //[RIBeam_]
		Int_t           RIBeam_flagall[kMaxRIBeam];   //[RIBeam_]
		Int_t           RIBeam_flagTSumX[kMaxRIBeam];   //[RIBeam_]
		Int_t           RIBeam_flagTOFt[kMaxRIBeam];   //[RIBeam_]
		Int_t           RIBeam_flagTOFq[kMaxRIBeam];   //[RIBeam_]
		Int_t           RIBeam_flagReaction[kMaxRIBeam];   //[RIBeam_]
		Int_t           RIBeam_flagdERelation[kMaxRIBeam];   //[RIBeam_]
		Int_t           RIBeam_flagAngle[kMaxRIBeam];   //[RIBeam_]
		Int_t           RIBeamOthers_;
		UInt_t          RIBeamOthers_fUniqueID[kMaxRIBeamOthers];   //[RIBeamOthers_]
		UInt_t          RIBeamOthers_fBits[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_tof37[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_tof711[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_F3X[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_F3A[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_F3Y[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_F3B[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_F5X[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_F5A[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_F5Y[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_F5B[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_F7X[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_F7A[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_F7Y[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_F7B[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_delta35[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_delta57[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_brho35[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_brho57[kMaxRIBeamOthers];   //[RIBeamOthers_]
		Double_t        RIBeamOthers_deltaE[kMaxRIBeamOthers];   //[RIBeamOthers_]

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
		TBranch        *b_BigRIPSPPAC_;   //!
		TBranch        *b_BigRIPSPPAC_fUniqueID;   //!
		TBranch        *b_BigRIPSPPAC_fBits;   //!
		TBranch        *b_BigRIPSPPAC_id;   //!
		TBranch        *b_BigRIPSPPAC_fpl;   //!
		TBranch        *b_BigRIPSPPAC_name;   //!
		TBranch        *b_BigRIPSPPAC_fDataState;   //!
		TBranch        *b_BigRIPSPPAC_xzpos;   //!
		TBranch        *b_BigRIPSPPAC_yzpos;   //!
		TBranch        *b_BigRIPSPPAC_fTX1Raw;   //!
		TBranch        *b_BigRIPSPPAC_fTX2Raw;   //!
		TBranch        *b_BigRIPSPPAC_fTY1Raw;   //!
		TBranch        *b_BigRIPSPPAC_fTY2Raw;   //!
		TBranch        *b_BigRIPSPPAC_fTARaw;   //!
		TBranch        *b_BigRIPSPPAC_fQX1Raw;   //!
		TBranch        *b_BigRIPSPPAC_fQX2Raw;   //!
		TBranch        *b_BigRIPSPPAC_fQY1Raw;   //!
		TBranch        *b_BigRIPSPPAC_fQY2Raw;   //!
		TBranch        *b_BigRIPSPPAC_fQARaw;   //!
		TBranch        *b_BigRIPSPPAC_fTSumX;   //!
		TBranch        *b_BigRIPSPPAC_fTSumY;   //!
		TBranch        *b_BigRIPSPPAC_fTDiffX;   //!
		TBranch        *b_BigRIPSPPAC_fTDiffY;   //!
		TBranch        *b_BigRIPSPPAC_fX;   //!
		TBranch        *b_BigRIPSPPAC_fY;   //!
		TBranch        *b_BigRIPSPPAC_fFiredX;   //!
		TBranch        *b_BigRIPSPPAC_fFiredY;   //!
		TBranch        *b_BigRIPSPlastic_;   //!
		TBranch        *b_BigRIPSPlastic_fUniqueID;   //!
		TBranch        *b_BigRIPSPlastic_fBits;   //!
		TBranch        *b_BigRIPSPlastic_id;   //!
		TBranch        *b_BigRIPSPlastic_fpl;   //!
		TBranch        *b_BigRIPSPlastic_name;   //!
		TBranch        *b_BigRIPSPlastic_fDataState;   //!
		TBranch        *b_BigRIPSPlastic_zposition;   //!
		TBranch        *b_BigRIPSPlastic_zoffset;   //!
		TBranch        *b_BigRIPSPlastic_fTLRaw;   //!
		TBranch        *b_BigRIPSPlastic_fTRRaw;   //!
		TBranch        *b_BigRIPSPlastic_fQLRaw;   //!
		TBranch        *b_BigRIPSPlastic_fQRRaw;   //!
		TBranch        *b_BigRIPSPlastic_fTime;   //!
		TBranch        *b_BigRIPSPlastic_fTimeL;   //!
		TBranch        *b_BigRIPSPlastic_fTimeR;   //!
		TBranch        *b_BigRIPSPlastic_fTimeLSlew;   //!
		TBranch        *b_BigRIPSPlastic_fTimeRSlew;   //!
		TBranch        *b_BigRIPSPlastic_fTimeSlew;   //!
		TBranch        *b_BigRIPSIC_;   //!
		TBranch        *b_BigRIPSIC_fUniqueID;   //!
		TBranch        *b_BigRIPSIC_fBits;   //!
		TBranch        *b_BigRIPSIC_id;   //!
		TBranch        *b_BigRIPSIC_fpl;   //!
		TBranch        *b_BigRIPSIC_name;   //!
		TBranch        *b_BigRIPSIC_fDataState;   //!
		TBranch        *b_BigRIPSIC_zcoef;   //!
		TBranch        *b_BigRIPSIC_ionpair;   //!
		TBranch        *b_BigRIPSIC_nhitchannel;   //!
		TBranch        *b_BigRIPSIC_fADC;   //!
		TBranch        *b_BigRIPSIC_fEnergy;   //!
		TBranch        *b_BigRIPSIC_fRawADCSqSum;   //!
		TBranch        *b_BigRIPSIC_fRawADCAvSum;   //!
		TBranch        *b_BigRIPSIC_fCalMeVSqSum;   //!
		TBranch        *b_BigRIPSIC_fCalMeVAvSum;   //!
		TBranch        *b_BigRIPSFocalPlane_;   //!
		TBranch        *b_BigRIPSFocalPlane_fUniqueID;   //!
		TBranch        *b_BigRIPSFocalPlane_fBits;   //!
		TBranch        *b_BigRIPSFocalPlane_id;   //!
		TBranch        *b_BigRIPSFocalPlane_fpl;   //!
		TBranch        *b_BigRIPSFocalPlane_name;   //!
		TBranch        *b_BigRIPSFocalPlane_fDataState;   //!
		TBranch        *b_BigRIPSFocalPlane_opt_vector;   //!
		TBranch        *b_BigRIPSFocalPlane_X;   //!
		TBranch        *b_BigRIPSFocalPlane_A;   //!
		TBranch        *b_BigRIPSFocalPlane_Y;   //!
		TBranch        *b_BigRIPSFocalPlane_B;   //!
		TBranch        *b_BigRIPSFocalPlane_nfired_ppacx;   //!
		TBranch        *b_BigRIPSFocalPlane_nfired_ppacy;   //!
		TBranch        *b_BigRIPSFocalPlane_zpos;   //!
		TBranch        *b_BigRIPSTOF_;   //!
		TBranch        *b_BigRIPSTOF_fUniqueID;   //!
		TBranch        *b_BigRIPSTOF_fBits;   //!
		TBranch        *b_BigRIPSTOF_id;   //!
		TBranch        *b_BigRIPSTOF_fpl;   //!
		TBranch        *b_BigRIPSTOF_name;   //!
		TBranch        *b_BigRIPSTOF_fDataState;   //!
		TBranch        *b_BigRIPSTOF_tof;   //!
		TBranch        *b_BigRIPSTOF_clight;   //!
		TBranch        *b_BigRIPSTOF_length;   //!
		TBranch        *b_BigRIPSTOF_ulength;   //!
		TBranch        *b_BigRIPSTOF_dlength;   //!
		TBranch        *b_BigRIPSTOF_upstream_plname;   //!
		TBranch        *b_BigRIPSTOF_downstream_plname;   //!
		TBranch        *b_BigRIPSTOF_upstream_plfpl;   //!
		TBranch        *b_BigRIPSTOF_downstream_plfpl;   //!
		TBranch        *b_BigRIPSTOF_time_offset;   //!
		TBranch        *b_BigRIPSRIPS_;   //!
		TBranch        *b_BigRIPSRIPS_fUniqueID;   //!
		TBranch        *b_BigRIPSRIPS_fBits;   //!
		TBranch        *b_BigRIPSRIPS_id;   //!
		TBranch        *b_BigRIPSRIPS_fpl;   //!
		TBranch        *b_BigRIPSRIPS_name;   //!
		TBranch        *b_BigRIPSRIPS_fDataState;   //!
		TBranch        *b_BigRIPSRIPS_upstream_fpl;   //!
		TBranch        *b_BigRIPSRIPS_downstream_fpl;   //!
		TBranch        *b_BigRIPSRIPS_center_brho;   //!
		TBranch        *b_BigRIPSRIPS_brho;   //!
		TBranch        *b_BigRIPSRIPS_length;   //!
		TBranch        *b_BigRIPSRIPS_matrix;   //!
		TBranch        *b_BigRIPSRIPS_delta;   //!
		TBranch        *b_BigRIPSRIPS_angle;   //!
		TBranch        *b_BigRIPSBeam_;   //!
		TBranch        *b_BigRIPSBeam_fUniqueID;   //!
		TBranch        *b_BigRIPSBeam_fBits;   //!
		TBranch        *b_BigRIPSBeam_id;   //!
		TBranch        *b_BigRIPSBeam_fpl;   //!
		TBranch        *b_BigRIPSBeam_name;   //!
		TBranch        *b_BigRIPSBeam_fDataState;   //!
		TBranch        *b_BigRIPSBeam_brho;   //!
		TBranch        *b_BigRIPSBeam_aoq;   //!
		TBranch        *b_BigRIPSBeam_zet;   //!
		TBranch        *b_BigRIPSBeam_beta;   //!
		TBranch        *b_BigRIPSBeam_clight;   //!
		TBranch        *b_BigRIPSBeam_mnucleon;   //!
		TBranch        *b_BigRIPSBeam_nrips;   //!
		TBranch        *b_BigRIPSBeam_ripsname;   //!
		TBranch        *b_BigRIPSBeam_tofname;   //!
		TBranch        *b_BigRIPSBeam_icname;   //!
		TBranch        *b_RIBeam_;   //!
		TBranch        *b_RIBeam_fUniqueID;   //!
		TBranch        *b_RIBeam_fBits;   //!
		TBranch        *b_RIBeam_beta35;   //!
		TBranch        *b_RIBeam_beta57;   //!
		TBranch        *b_RIBeam_beta711;   //!
		TBranch        *b_RIBeam_aoq37;   //!
		TBranch        *b_RIBeam_zed;   //!
		TBranch        *b_RIBeam_Zed;   //!
		TBranch        *b_RIBeam_Mass;   //!
		TBranch        *b_RIBeam_flagall;   //!
		TBranch        *b_RIBeam_flagTSumX;   //!
		TBranch        *b_RIBeam_flagTOFt;   //!
		TBranch        *b_RIBeam_flagTOFq;   //!
		TBranch        *b_RIBeam_flagReaction;   //!
		TBranch        *b_RIBeam_flagdERelation;   //!
		TBranch        *b_RIBeam_flagAngle;   //!
		TBranch        *b_RIBeamOthers_;   //!
		TBranch        *b_RIBeamOthers_fUniqueID;   //!
		TBranch        *b_RIBeamOthers_fBits;   //!
		TBranch        *b_RIBeamOthers_tof37;   //!
		TBranch        *b_RIBeamOthers_tof711;   //!
		TBranch        *b_RIBeamOthers_F3X;   //!
		TBranch        *b_RIBeamOthers_F3A;   //!
		TBranch        *b_RIBeamOthers_F3Y;   //!
		TBranch        *b_RIBeamOthers_F3B;   //!
		TBranch        *b_RIBeamOthers_F5X;   //!
		TBranch        *b_RIBeamOthers_F5A;   //!
		TBranch        *b_RIBeamOthers_F5Y;   //!
		TBranch        *b_RIBeamOthers_F5B;   //!
		TBranch        *b_RIBeamOthers_F7X;   //!
		TBranch        *b_RIBeamOthers_F7A;   //!
		TBranch        *b_RIBeamOthers_F7Y;   //!
		TBranch        *b_RIBeamOthers_F7B;   //!
		TBranch        *b_RIBeamOthers_delta35;   //!
		TBranch        *b_RIBeamOthers_delta57;   //!
		TBranch        *b_RIBeamOthers_brho35;   //!
		TBranch        *b_RIBeamOthers_brho57;   //!
		TBranch        *b_RIBeamOthers_deltaE;   //!

		EUDataBeam(const char* filename, TTree *tree=0);
		~EUDataBeam();
		Int_t		GetEntry(Long64_t entry);
		void		Init(TTree *tree);
		void		GetTsEntry(std::map<Long64_t, Long64_t> &mts);
};
#endif
