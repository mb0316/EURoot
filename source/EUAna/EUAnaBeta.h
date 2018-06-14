#ifndef EUANABETA_H
#define EUANABETA_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EUAna.h"
#include <map>
#include <vector>
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
		Int_t	temp_x[5];
		Int_t	temp_y[5];
		Int_t	max_tempTX_1[5] = {1500, 1000, 150, 1000, 1000};
		//Int_t	max_tempTX_2[5] = {80, 100, 800, 100, 100};
		Int_t	max_tempTX_2[5] = {500, 1000, 2500, 1000, 1000};
		Int_t	max_tempTY_1[5] = {1500, 1500, 100, 500, 1000};
		//Int_t	max_tempTY_2[5] = {80, 100, 400, 160, 15};
		Int_t	max_tempTY_2[5] = {700, 1000, 1200, 500, 1000};
		Int_t	max_tempT;
		Int_t	fire_z[6];
		Int_t	fire_x[6];
//		Int_t	fire_x;
		Int_t	fire_y[6];
//		Int_t	fire_y;

		Int_t	ix;
		Int_t	iy;
		Int_t	idssd;

		Bool_t	good_xy;
		Double_t deltaE_cut_L[5] = {-44.55, -113.92, -50.6, -41.33, -59.84};
		Double_t deltaE_cut_U[5] = {55.37, 92.92, 60.04, 53.91, 68.6};
		Int_t beta_T_X_cut_L[5] = {-300, -300, -300, -300, -300};
		Int_t beta_T_Y_cut_L[5] = {-400, -500, -400, -400, -300};
		Int_t beta_T_X_cut_H[5] = {500, 600, 500, 500, 500};
		Int_t beta_T_Y_cut_H[5] = {500, 800, 500, 500, 200};
		Int_t tem_dssdhit;
		Int_t tem_beta_z[100];
		Int_t tem_beta_x[100];
		Int_t tem_beta_y[100];
		Double_t tem_beta_E_X[100];
		Double_t tem_beta_E_Y[100];
		Double_t tem_beta_E_delta[100];
		Double_t tem_beta_T_X[100];
		Double_t tem_beta_T_Y[100];

		vector<pair<int, int>> temp_beta_pos;
		vector<int> temp_beta_z;

	public :
		Int_t	fire;
		Double_t nw3tx[5][60];
		Double_t nw3ty[5][40];

		EUAnaBeta(TTree* tree);
		~EUAnaBeta();
		void	GetCalib();
		void	CalibBeam(Int_t &runnum);
		void	GetBetaTDCoffset();
		void	CalibTzero(EUDataSi *dssd);
		void	CalibTzeroBeta(EUDataSi *dssd);
		void	GetIonPos(EUDataSi *dssd, Int_t &run_num);
		//int	GetXY(Int_t temp_z, EUDataSi *dssd);
		void	GetBetaPos(EUDataSi *dssd, TTree* tree);
//		void	GetBetaPos(EUDataSi *dssd, Int_t &ndssd, TTree* tree);

		void	MapCorrel(std::map<Long64_t, Long64_t> &master_mts, std::map<Long64_t, Long64_t>::iterator &imaster_mts, std::map<Long64_t, Long64_t> &slave_mts, std::map<Long64_t, Long64_t>::iterator &islave_mts, std::map<Long64_t, Long64_t> &target_mts, Int_t lower_limit, Int_t upper_limit);
		void	CopyTS(EUDataSi *dssd); //copy the timestamp from WASABI data
		void	CopyTS(EUDataGe *hpge); //copy the timestamp from WASABI data
		void	CopyTS(EUDataBeam *beam); //copy the timestamp from WASABI data
		void	CopyTS(EUTreeBeta *beta); //copy the timestamp from EUTreeBeta data
		void	CopyBigRIPS(EUDataBeam *beam); //copy AoQ and Z data from bigrips data
		void	CopyBigRIPS(EUTreeBeta *beta); //copy AoQ and Z data from bigrips data
		void	CopyPL(EUDataSi *dssd); //copy F11 PL and veto PL TDC data from WASABI data
		void	CopyPL(EUDataGe *hpge); //copy F11 PL ADC data from eurica data
		void	CopyPL(EUTreeBeta *dssd, EUTreeBeta *hpge); //copy F11 PL ADC data from EUTreeBeta data
		void	CopyPL(EUTreeBeta *beta); //copy F11 PL ADC data from EUTreeBeta data
		void	CopyEURICA(EUDataGe *hpge); //copy EURICA, LaBr, beta PL data from eurica data
		void	CopyEURICA(EUTreeBeta *beta, Int_t opt); //copy EURICA, LaBr, beta PL data from EUTreeBeta data
		void	CopyDSSD(EUTreeBeta *beta, Int_t opt);	//copy DSSD data from EUTreeBeta data
		void	ResetPL();
		void	ResetEURICA(); //reset or set 0 for hit information of eurica
		void	ResetPID(); //reset or set 0 for PID
		void	ResetDSSD(); //reset or set 0 for hit information of wasabi
		void	Addback(); //addback algorithm
		void	AngleEURICA();
};
#endif
