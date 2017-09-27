#ifndef EUANA_H
#define EUANA_H

#include "TROOT.h"
#include "TObject.h"
#include "TClonesArray.h"
#include "TChain.h"
#include "TFile.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <map>
#include "TMath.h"
#include "EUTree.h"
#include "EUTreeBeta.h"
#include "EUDataSi.h"
#include "EUDataGe.h"
#include "EUDataBeam.h"

using namespace std;

class EUAna : public TObject
{
	protected :
		//Calib info.
		Int_t adc_ch[84]; //for energy calibration of EURICA for each channel
		Double_t adc_gain[84]; //for energy calibration of EURICA for each channel
		Double_t adc_offset[84]; //for energy calibration of EURICA for each channel
		Int_t tdcs_ch[84]; //for short range tdc to time calibration of EURICA for each channel
		Double_t tdcs_gain[84]; //for short range tdc to time calibration of EURICA for each channel
		Double_t tdcs_offset[84];//for short range tdc to time calibration of EURICA for each channel
		Double_t tdcl_gain; //for long range tdc to time calibration of EURICA for each channel
		Double_t tdcl_offset; //for long range tdc to time calibration of EURICA for each channel
		Double_t gcT_iso_twc[84][4]; //for slew correction of gcT of EURICA, for isomeric decay
		Double_t tdcs_iso_twc[84][4]; //for slew correction of short range TDC of EURICA, for isomeric decay
		Double_t tdcl_iso_twc[84][4]; //for slew correction of long range TDC of EURICA, for isomeric decay
		Double_t gcT_beta_twc[84][4]; //for slew correction of gcT of EURICA, for beta decay
		Double_t art_iso_tdcs_offset[84]; //for artificial TDC offset correction
		Double_t art_iso_tdcl_offset[84]; //for artificial TDC offset correction
		Double_t art_beta_tdcs_offset[84]; //for artificial TDC offset correction
		Double_t art_beta_tdcl_offset[84]; //for artificial TDC offset correction

		//Addback Algo. Info.
		static const Int_t Addback_hitpattern[7][7]; //Addback hit pattern for each crystal
		Int_t tempgchit[12]; //temporary gchit data for the analysis
		Int_t tempaddhit[12]; //temporary addhit data for the analysis
		Int_t tempCry[12][7]; //temporary crystal id data for the analysis
		Double_t tempE[12][7]; //temporary energy data for the analysis
		Double_t tempT[12][7]; //temporary time data for the analysis
	public :

		//veto Info.
		Int_t vetoPL1;
		Int_t vetoPL2;
		Int_t F7_PLl;
		Int_t F7_PLr;


		//functions
		EUAna();
		~EUAna();
		virtual void	GetCalib(); //bring all external calibration data
		int		Addback2hitCheck(int iclust, int icryst1, int icryst2); //check the event whether it is for 2 hit addback or not
		int		Addback3hitCheck(int iclust, int icryst1, int icryst2, int icryst3); //check the event whether it is for 3 hit addback or not
//		virtual void    MapCorrel(std::map<Long64_t, Long64_t> &master_mts, std::map<Long64_t, Long64_t>::iterator &imaster_mts, std::map<Long64_t, Long64_t> &slave_mts, std::map<Long64_t, Long64_t>::iterator &islave_mts, std::map<Long64_t, Long64_t> &target_mts, Int_t lower_limit, Int_t upper_limit) = 0;
//		virtual void    CopyTS(EUDataSi *dssd) = 0; //copy the timestamp from WASABI data
//		virtual void    CopyBigRIPS(EUDataBeam *beam) = 0; //copy AoQ and Z data from bigrips data
//		virtual void    CopyPL(EUDataSi *dssd) = 0; //copy F11 PL and veto PL data from WASABI data
//		virtual void    CopyEURICA(EUDataGe *hpge) = 0; //copy EURICA, LaBr, beta PL data from eurica data
//		virtual void    CopyEURICA(EUTreeBeta *beta) = 0; //copy EURICA, LaBr, beta PL data from BetaMerge data
//		virtual void    CopyDSSD(EUTreeBeta *beta) = 0; //copy WASABI ion, beta data from BetaMerge data
//		virtual void    ResetEURICA() = 0; //reset or set 0 for hit information of eurica
//		virtual void    ResetPID() = 0; //reset or set 0 for PID
//		virtual void    ResetDSSD() = 0; //reset or set 0 for hit information of wasabi
//		virtual void    Addback() = 0; //addback algorithm
};
#endif
