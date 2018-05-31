#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EUAna.h"
#include "EUAnaDecay.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "EUAnaPID.h"
#include "EUTreeDecay.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TTree.h"
#include "TString.h"
#include "TObjArray.h"
#include "TObjString.h"

using namespace std;

EUAnaPID::EUAnaPID(TTree* tree):EUTreeDecay(tree)
{}

EUAnaPID::~EUAnaPID()
{}

void EUAnaPID::PIDFitting(TH1D* hist, Double_t &mean, Double_t &sig)
{
	Double_t ampl = hist->GetMaximum();
	TF1* gaus = new TF1("gaussian", "gaus(0)", mean - mean/5, mean + mean/5);
	gaus -> SetParameters(ampl, mean, sig);
	hist->Fit(gaus, "MQ", "", mean-sig, mean+sig);
	mean = gaus -> GetParameter(1);
	sig = gaus -> GetParameter(2);
}

void EUAnaPID::GammaTimeCut(TH2D* hist)
{
	TH1D* pro;
	TF1* gaus = new TF1("gaussian", "gaus(0)", -500, 500);
	
	for (Int_t i = 0; i < 50; i++)
	{
		pro = hist->ProjectionY("pro", 40*i, 40*i+40);
		gaus->SetParameters(pro->GetMaximum(), 0, 10.0);
		pro->Fit(gaus, "MQ", "", -250, 250);
		timecut[i] = 2*(gaus->GetParameter(2));
		pro->Clear();
		cout << 40*i << " keV time cut condition : " << timecut[i] << endl;
	}
}

void EUAnaPID::CopyData(EUTreeDecay* decay)
{

	AoQ = decay->AoQ;
	Zpro = decay->Zpro;
	t = decay->t;
	z = decay->z;
	x = decay->x;
	y = decay->y;
	beta_flag = decay->beta_flag;
	deltaxy = decay->deltaxy;

	gchit = decay->gchit;
	memcpy(gc_ch, decay->gc_ch, gchit*sizeof(int));
	memcpy(gc_E, decay->gc_E, gchit*sizeof(double));
	memcpy(gc_T, decay->gc_T, gchit*sizeof(double));
	memcpy(gc_Ts, decay->gc_Ts, gchit*sizeof(double));
	memcpy(gc_Tl, decay->gc_Tl, gchit*sizeof(double));

	addhit = decay->addhit;
	memcpy(add_ch, decay->add_ch, addhit*sizeof(int));
	memcpy(add_E, decay->add_E, addhit*sizeof(double));
	memcpy(add_T, decay->add_T, addhit*sizeof(double));

	lbhit = decay->lbhit;
	memcpy(lb_ch, decay->lb_ch, lbhit*sizeof(int));
	memcpy(lb_E, decay->lb_E, lbhit*sizeof(double));
	memcpy(lb_Ts, decay->lb_Ts, lbhit*sizeof(double));
	memcpy(lb_Tl, decay->lb_Tl, lbhit*sizeof(double));

	betaPL1_Beam_ADCL = decay->betaPL1_Beam_ADCL;
	betaPL1_Beta_ADCL = decay->betaPL1_Beta_ADCL;
	betaPL1_Beam_ADCR = decay->betaPL1_Beam_ADCR;
	betaPL1_Beta_ADCR = decay->betaPL1_Beta_ADCR;
	betaPL2_Beam_ADCL = decay->betaPL2_Beam_ADCL;
	betaPL2_Beta_ADCL = decay->betaPL2_Beta_ADCL;
	betaPL2_Beam_ADCR = decay->betaPL2_Beam_ADCR;
	betaPL2_Beta_ADCR = decay->betaPL2_Beta_ADCR;
	betaPL1_TLs = decay->betaPL1_TLs;
	betaPL1_TRs = decay->betaPL1_TRs;
	betaPL2_TLs = decay->betaPL2_TLs;
	betaPL2_TRs = decay->betaPL2_TRs;
	betaPL1_TLl = decay->betaPL1_TLl;
	betaPL1_TRl = decay->betaPL1_TRl;
	betaPL2_TLl = decay->betaPL2_TLl;
	betaPL2_TRl = decay->betaPL2_TRl;

}
