#ifndef EUANAPID_H
#define EUANAPID_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EUAna.h"
#include <stdio.h>
#include <stdlib.h>
#include "EUTreeBeta.h"
#include "EUTreeIso.h"
#include "EUTreeDecay.h"
#include "TH1D.h"
#include "TH2D.h"

class EUAnaPID : public EUAna, public EUTreeDecay
{
	private :
		Double_t ampl;
		Double_t dev;
		Double_t mean;
		Double_t bin;

	public :
		Double_t timecut[50] = {0};

		EUAnaPID(const char* filename, TTree* tree=0);
		~EUAnaPID();
		void	PIDFitting(TH1D* hist, Double_t &mean, Double_t &sig);
		void	MakeOutFile(Int_t &z, Int_t &mass, Double_t &zpro, Double_t &zpro_cut, Double_t &aoq, Double_t &aoq_cut);
		void	GammaTimeCut(TH2D* hist);
};
#endif
