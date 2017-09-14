#ifndef EUANABETA_H
#define EUANABETA_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EUAna.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "EUTree.h"
#include "EUDataSi.h"
#include "EUDataGe.h"
#include "EUDataBeam.h"
#include "EUTreeBeta.h"

class EUAnaBeta : public EUAna, public EUTreeBeta
{
	private	:
		Int_t	temp_z;
		Int_t	temp_x;
		Int_t	temp_y;
		Int_t	max_tempT;
		Int_t	fire_x;
		Int_t	fire_y;
	
		Int_t	ix;
		Int_t	iy;
		Int_t	idssd;

	public :
		Int_t	fire;

		EUAnaBeta(TTree* tree);
		~EUAnaBeta();
		void	GetBetaTDCoffset();
		void	GetIonPos(EUDataSi *dssd);
		void	GetBetaPos(EUDataSi *dssd, Int_t &ndssd);

		void	MapCorrel(std::map<Long64_t, Long64_t> &master_mts, std::map<Long64_t, Long64_t>::iterator &imaster_mts, std::map<Long64_t, Long64_t> &slave_mts, std::map<Long64_t, Long64_t>::iterator &islave_mts, std::map<Long64_t, Long64_t> &target_mts, Int_t lower_limit, Int_t upper_limit);
        void	CopyTS(EUDataSi *dssd); //copy the timestamp from WASABI data
        void	CopyTS(EUTreeBeta *beta); //copy the timestamp from EUTreeBeta data
        void	CopyBigRIPS(EUDataBeam *beam); //copy AoQ and Z data from bigrips data
        void	CopyPL(EUDataSi *dssd); //copy F11 PL and veto PL data from WASABI data
        void	CopyEURICA(EUDataGe *hpge); //copy EURICA, LaBr, beta PL data from eurica data
        void	CopyEURICA(EUTreeBeta *beta); //copy EURICA, LaBr, beta PL data from EUTreeBeta data
		void	CopyDSSD(EUTreeBeta *beta);	//copy DSSD data from EUTreeBeta data
        void	ResetEURICA(); //reset or set 0 for hit information of eurica
        void	ResetPID(); //reset or set 0 for PID
        void	ResetDSSD(); //reset or set 0 for hit information of wasabi
        void	Addback(); //addback algorithm
		void	AngleEURICA();
};
#endif
