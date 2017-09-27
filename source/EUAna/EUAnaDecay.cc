#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EUAna.h"
#include "EUAnaDecay.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "EUAnaBeta.h"
#include "EUAnaIso.h"

using namespace std;

EUAnaDecay::EUAnaDecay(TTree* tree):EUTreeDecay(tree)
{}

EUAnaDecay::~EUAnaDecay()
{}

void EUAnaDecay::GetCalib()
{
	ifstream gcT_beta_twfile("../calib/betaT_TW.dat");

	for (Int_t i = 0; i < 84; i++)	gcT_beta_twfile >> gcT_beta_twc[i][0] >> gcT_beta_twc[i][1] >> gcT_beta_twc[i][2] >> gcT_beta_twc[i][3];

	gcT_beta_twfile.close();
}

void EUAnaDecay::CopyDSSD(EUTreeBeta *beta)
{
    z = beta->ion_z;
    x = beta->ion_x;
    y = beta->ion_y;
    AoQ = beta->AoQ;
    Zpro = beta->Zpro;
}

void EUAnaDecay::TWCor()
{
	for (Int_t ihit = 0; ihit < gchit; ihit++)
	{
		if (gc_T[ihit] > -500E3 && gc_T[ihit] < 500E3)    gc_T[ihit] = -(gc_T[ihit] - gcT_beta_twc[gc_ch[ihit]][1]*(TMath::Power(gc_E[ihit]-gcT_beta_twc[gc_ch[ihit]][2], -gcT_beta_twc[gc_ch[ihit]][3])) - gcT_beta_twc[gc_ch[ihit]][0]);
		else continue;
	}
	for (Int_t ihit = 0; ihit < addhit; ihit++)
	{
		if (add_T[ihit] > -500E3 && add_T[ihit] < 500E3)    add_T[ihit] = -(add_T[ihit] - gcT_beta_twc[add_ch[ihit]][1]*(TMath::Power(add_E[ihit]-gcT_beta_twc[add_ch[ihit]][2], -gcT_beta_twc[add_ch[ihit]][3])) - gcT_beta_twc[add_ch[ihit]][0]);
		else continue;
	}

}

void EUAnaDecay::CopyEURICA(EUTreeBeta *beta)
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

void EUAnaDecay::GetBetaEnergy(EUTreeBeta *beta)
{
/*
    Int_t tempE  = 0;
    Int_t beta_E = 0;
    for (Int_t i = 0; i < beta.dssdhit; i++)
    {
        tempE = beta.beta_E_X[i] + beta.beta_E_Y[i];
        beta_E = beta_E + tempE;
    }
*/
    beta_E = beta->beta_E_X + beta->beta_E_Y;
}

void EUAnaDecay::GetBetaTDCoffset()
{
    for (Int_t ihit = 0; ihit < gchit; ihit++)
    {
        gc_Ts[ihit] = gc_Ts[ihit] - art_beta_tdcs_offset[gc_ch[ihit]];
        gc_Tl[ihit] = -(gc_Tl[ihit] - art_beta_tdcl_offset[gc_ch[ihit]]);
    }
}

double EUAnaDecay::GetXYDistance(int beta_x, int beta_y)
{
	deltaxy = sqrt((x - beta_x)*(x - beta_x) + (y - beta_y)*(y - beta_y));
	return deltaxy;
}

void EUAnaDecay::ResetEURICA()
{
    gchit = 0;
    addhit = 0;
    lbhit = 0;
}
