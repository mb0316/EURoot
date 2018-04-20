#ifndef EUANADECAY_H
#define EUANADECAY_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EUAna.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "EUTreeBeta.h"
#include "EUTreeIso.h"
#include "EUTreeDecay.h"

class EUAnaDecay : public EUAna, public EUTreeDecay
{
	private :
		Double_t temp_deltaxy;
	public :
		Bool_t good_beta;

		EUAnaDecay(TTree* tree);
		~EUAnaDecay();
		void	GetCalib();
		void	CopyDSSD(EUTreeBeta *beta); //copy all ion(beam) data from BetaMerge to build Decay data
		void	CopyEURICA(EUTreeBeta *beta); //copy all beta data from BetaMerge to build Decay data
		void	TWCor(); //Timewalk correction for EURICA
		void    GetBetaTDCoffset();
		int	BetaTrack(EUTreeBeta *beta);
		double	GetXYDistance(int beta_x, int beta_y);
		void	ResetEURICA();
};
#endif
