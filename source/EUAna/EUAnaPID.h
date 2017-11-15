#ifndef EUANAPID_H
#define EUANAPID_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include "EUAna.h"
#include <stdio.h>
#include <stdlib.h>
#include "EUTreeBeta.h"
#include "EUTreeIso.h"
#include "EUTreeDecay.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"

class EUAnaPID : public EUAna//, public EUTreeDecay, public EUTreeIso
{
	private :
		Double_t ampl;
		Double_t dev;
		Double_t mean;
		Double_t bin;

	public :
		TTree* ftree;
		Double_t t;
		Double_t deltaxy;
		Double_t Zpro;
		Double_t AoQ;
		Int_t gchit;
		Double_t gc_E[84];
		Double_t gc_T[84];


		Double_t timecut[50] = {0};

		EUAnaPID(const char* filename);
		~EUAnaPID();
		void	PIDFitting(TH1D* hist, Double_t &mean, Double_t &sig);
		void	MakeOutFile(const char* filename, Int_t &z, Int_t &mass, Double_t &zpro, Double_t &zpro_cut, Double_t &aoq, Double_t &aoq_cut);
		void	GammaTimeCut(TH2D* hist);
};
#endif
