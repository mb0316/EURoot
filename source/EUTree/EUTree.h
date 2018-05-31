#ifndef EUTREE_H
#define EUTREE_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TObject.h>
#include <TNamed.h>
#include <TTree.h>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

class EUTree : public TObject
{
	public :
		TFile	*f;
		TTree	*fData;
		Int_t	fCurrent;

		Long64_t ts; //timestamp
		Int_t eventid; //0 : ion, 1 : beta

		//Decay Info.
		Double_t t; //decay time, only for Decay data
		Int_t z; //implanted depth, only for Decay data
		Int_t x; //implanted pixel, only for Decay data
		Int_t y; //implanted pixel, only for Decay data
		Int_t beta_E; //final beta energy, only for Decay data
		Double_t deltaxy; //distance between an ion and an emitted beta, only for Decay data
		Int_t beta_flag; //0 : no dleta E cut, 1: delta E cut

		//Beam Info.
		Double_t AoQ;
		Double_t Zpro;

		//WASABI Info.
		Int_t ion_z; //implanted depth for an ion, only for BetaMerge data
		Int_t ion_x; //implanted pixel for an ion, only for BetaMerge data
		Int_t ion_y; //implanted pixel for an ion, only for BetaMerge data
		Int_t dssdhit;
		Int_t beta_z[100]; //hit position for betas, only for BetaMerge data
		Int_t beta_x[100]; //hit position for betas, only for BetaMerge data
		Int_t beta_y[100]; //hit position for betas, only for BetaMerge data
		Double_t ion_E_X; //ion energy in x strip, only for BetaMerge data
		Double_t ion_E_Y; //ion energy in y strip, only for BetaMerge data
		Double_t ion_T_X; //time for an ion in x strip, only for BetaMerge data
		Double_t ion_T_Y; //time for an ion in y strip, only for BetaMerge data
		Double_t beta_E_X[100]; //beta energy in x strip, only for BetaMerge data
		Double_t beta_E_Y[100]; //beta energy in y strip, only for BetaMerge data
		Double_t beta_E_delta[100]; //difference between Ex and Ey
		Double_t beta_T_X[100]; //time for betas in x strip, only for BetaMerge data
		Double_t beta_T_Y[100]; //time for betas in y strip, only for BetaMerge data
		Int_t beta_good[100]; //0 : no dleta E cut, 1: delta E cut

		//EURICA Info.
		Int_t gchit; //number of hit in EURICA
		Int_t gc_ch[84]; //hit channel
		Int_t gc_ang[84]; //azimuthal angle
		Int_t gc_cl[84]; //hit cluster
		Double_t gc_E[84]; //gamma energy for each channel
		Double_t gc_T[84]; //time for each channel, DGFt
		Double_t gc_Ts[84]; //short range TDC for each chnnel
		Double_t gc_Tl[84]; //long range TDC for each channel
		Int_t addhit; //number of hit for addback
		Int_t add_ch[84]; //hit channel for addback
		Int_t add_ang[84]; //azimuthal angle
		Int_t add_cl[84]; //hit cluster
		Double_t add_E[84]; //gamma energy after addback
		Double_t add_T[84]; //time after addback

		//LaBr Info.
		Int_t lbhit; //numebr of hit in LaBr
		Int_t lb_ch[18]; //hit channel
		Double_t lb_E[18]; //gamma energy for each LaBr
		Double_t lb_Ts[18]; //short range TDC for each LaBr
		Double_t lb_Tl[18]; //long range TDC for each LaBr

		//betaPL Info.
		Int_t betaPL1_Beam_ADCL;
		Int_t betaPL1_Beta_ADCL;
		Int_t betaPL1_Beam_ADCR;
		Int_t betaPL1_Beta_ADCR;
		Double_t betaPL1_TLs;
		Double_t betaPL1_TRs;
		Double_t betaPL1_TLl;
		Double_t betaPL1_TRl;
		Int_t betaPL2_Beam_ADCL;
		Int_t betaPL2_Beta_ADCL;
		Int_t betaPL2_Beam_ADCR;
		Int_t betaPL2_Beta_ADCR;
		Double_t betaPL2_TLs;
		Double_t betaPL2_TRs;
		Double_t betaPL2_TLl;
		Double_t betaPL2_TRl;

		//F11 PL Info.
		Int_t F11_ADC_L;
		Int_t F11_ADC_R;
		Int_t F11_TDC_L;
		Int_t F11_TDC_R;

		// List of branches
		TBranch       	*b_ts;   //!
		TBranch        	*b_eventid;   //!
		TBranch		*b_t;
		TBranch 	*b_z;
		TBranch 	*b_x;
		TBranch		*b_y;
		TBranch		*b_beta_E;
		TBranch		*b_beta_flag;
		TBranch		*b_deltaxy;
		TBranch        *b_AoQ;   //!
		TBranch        *b_Zpro;   //!
		TBranch        *b_ion_z;   //!
		TBranch        *b_ion_x;   //!
		TBranch        *b_ion_y;   //!
		TBranch        *b_ion_E_X;   //!
		TBranch        *b_ion_E_Y;   //!
		TBranch        *b_ion_T_X;   //!
		TBranch        *b_ion_T_Y;   //!
		TBranch		*b_dssdhit;
		TBranch        *b_beta_z;   //!
		TBranch        *b_beta_x;   //!
		TBranch        *b_beta_y;   //!
		TBranch        *b_beta_E_X;   //!
		TBranch        *b_beta_E_Y;   //!
		TBranch		*b_beta_E_delta;
		TBranch        *b_beta_T_X;   //!
		TBranch        *b_beta_T_Y;   //!
		TBranch        *b_beta_good;   //!
		TBranch        *b_gchit;   //!
		TBranch        *b_gc_ch;   //!
		TBranch        *b_gc_ang;   //!
		TBranch        *b_gc_cl;   //!
		TBranch        *b_gc_E;   //!
		TBranch        *b_gc_T;   //!
		TBranch        *b_gc_Ts;   //!
		TBranch        *b_gc_Tl;   //!
		TBranch        *b_addhit;   //!
		TBranch        *b_add_ch;   //!
		TBranch        *b_add_ang;   //!
		TBranch        *b_add_cl;   //!
		TBranch        *b_add_E;   //!
		TBranch        *b_add_T;   //!
		TBranch        *b_lbhit;   //!
		TBranch        *b_lb_ch;   //!
		TBranch        *b_lb_E;   //!
		TBranch        *b_lb_Ts;   //!
		TBranch        *b_lb_Tl;   //!
		TBranch        *b_betaPL1_Beam_ADCL;   //!
		TBranch        *b_betaPL1_Beta_ADCL;   //!
		TBranch        *b_betaPL1_Beam_ADCR;   //!
		TBranch        *b_betaPL1_Beta_ADCR;   //!
		TBranch        *b_betaPL1_TLs;   //!
		TBranch        *b_betaPL1_TRs;   //!
		TBranch        *b_betaPL1_TLl;   //!
		TBranch        *b_betaPL1_TRl;   //!
		TBranch        *b_betaPL2_Beam_ADCL;   //!
		TBranch        *b_betaPL2_Beta_ADCL;   //!
		TBranch        *b_betaPL2_Beam_ADCR;   //!
		TBranch        *b_betaPL2_Beta_ADCR;   //!
		TBranch        *b_betaPL2_TLs;   //!
		TBranch        *b_betaPL2_TRs;   //!
		TBranch        *b_betaPL2_TLl;   //!
		TBranch        *b_betaPL2_TRl;   //!
		TBranch        *b_F11_ADC_L;   //!
		TBranch        *b_F11_ADC_R;   //!
		TBranch        *b_F11_TDC_L;   //!
		TBranch        *b_F11_TDC_R;   //!

		EUTree();
		~EUTree();
		virtual Int_t	GetEntry(Long64_t entry) = 0;
		virtual void	Init(TTree *tree) = 0;
		virtual void	GetTsEntry(std::map<Long64_t, Long64_t> &mts) = 0;
};
#endif

