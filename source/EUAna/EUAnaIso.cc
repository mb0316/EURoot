#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EUAna.h"
#include "EUAnaIso.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "EUDataSi.h"
#include "EUDataGe.h"
#include "EUDataBeam.h"
#include "EUTreeIso.h"

EUAnaIso::EUAnaIso(TTree* tree):EUTreeIso(tree)
{
}

EUAnaIso::~EUAnaIso()
{}

void EUAnaIso::GetCalib()
{
	ifstream gcT_iso_twfile("../calib/isoT_TW.dat");
	Int_t temp_ch;
	Double_t temp_1, temp_2, temp_3;
	for (Int_t i = 0; i < 84; i++)
	{
		gcT_iso_twfile >> temp_ch >> temp_1 >> temp_2 >> temp_3;
		gcT_iso_twc[temp_ch][0] = temp_1;
		gcT_iso_twc[temp_ch][1] = temp_2;
		gcT_iso_twc[temp_ch][2] = temp_3;
		cout << i << " " << temp_ch << " " << gcT_iso_twc[temp_ch][0] << " " << gcT_iso_twc[temp_ch][1] << " " <<  gcT_iso_twc[temp_ch][2] << endl;
	}

	gcT_iso_twfile.close();
}

void EUAnaIso::CopyDSSD(EUTreeBeta *beta)
{
	z = beta->ion_z;
	x = beta->ion_x;
	y = beta->ion_y;
	AoQ = beta->AoQ;
	Zpro = beta->Zpro;
}

void EUAnaIso::TWCor()
{
	for (Int_t ihit = 0; ihit < gchit; ihit++)
	{
		if (gc_T[ihit] > -500E3 && gc_T[ihit] < 500E3)    gc_T[ihit] = -(gc_T[ihit] - gcT_iso_twc[gc_ch[ihit]][0] - gcT_iso_twc[gc_ch[ihit]][1]*TMath::Power(gc_E[ihit], -gcT_iso_twc[gc_ch[ihit]][2]));
		else continue;
	}
	for (Int_t ihit = 0; ihit < addhit; ihit++)
	{
		if (add_T[ihit] > -500E3 && add_T[ihit] < 500E3)    add_T[ihit] = -(add_T[ihit] - gcT_iso_twc[add_ch[ihit]][0] - gcT_iso_twc[add_ch[ihit]][1]*TMath::Power(add_E[ihit], -gcT_iso_twc[add_ch[ihit]][2]));
		else continue;
	}

}

void EUAnaIso::CopyEURICA(EUTreeBeta *beta)
{
	gchit = beta->gchit;
	memcpy(gc_ch, beta->gc_ch, gchit*sizeof(int));
	memcpy(gc_E, beta->gc_E, gchit*sizeof(double));
	memcpy(gc_T, beta->gc_T, gchit*sizeof(double));
	memcpy(gc_Ts, beta->gc_Ts, gchit*sizeof(double));
	memcpy(gc_Tl, beta->gc_Tl, gchit*sizeof(double));

	addhit = beta->addhit;
	memcpy(add_ch, beta->add_ch, addhit*sizeof(int));
	memcpy(add_E, beta->add_E, addhit*sizeof(double));
	memcpy(add_T, beta->add_T, addhit*sizeof(double));

	lbhit = beta->lbhit;
	memcpy(lb_ch, beta->lb_ch, lbhit*sizeof(int));
	memcpy(lb_E, beta->lb_E, lbhit*sizeof(double));
	memcpy(lb_Ts, beta->lb_Ts, lbhit*sizeof(double));
	memcpy(lb_Tl, beta->lb_Tl, lbhit*sizeof(double));

	betaPL1_Beam_ADCL = beta->betaPL1_Beam_ADCL;
	betaPL1_Beta_ADCL = beta->betaPL1_Beta_ADCL;
	betaPL1_Beam_ADCR = beta->betaPL1_Beam_ADCR;
	betaPL1_Beta_ADCR = beta->betaPL1_Beta_ADCR;
	betaPL2_Beam_ADCL = beta->betaPL2_Beam_ADCL;
	betaPL2_Beta_ADCL = beta->betaPL2_Beta_ADCL;
	betaPL2_Beam_ADCR = beta->betaPL2_Beam_ADCR;
	betaPL2_Beta_ADCR = beta->betaPL2_Beta_ADCR;
	betaPL1_TLs = beta->betaPL1_TLs;
	betaPL1_TRs = beta->betaPL1_TRs;
	betaPL2_TLs = beta->betaPL2_TLs;
	betaPL2_TRs = beta->betaPL2_TRs;
	betaPL1_TLl = beta->betaPL1_TLl;
	betaPL1_TRl = beta->betaPL1_TRl;
	betaPL2_TLl = beta->betaPL2_TLl;
	betaPL2_TRl = beta->betaPL2_TRl;
}

void EUAnaIso::ResetEURICA()
{
	gchit = 0;
	addhit = 0;
	lbhit = 0;
}
