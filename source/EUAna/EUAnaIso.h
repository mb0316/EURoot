#ifndef EUANAISO_H
#define EUANAISO_H

#include <TROOT.h>
#include <TChain.h>
#include "EUAna.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "EUTreeIso.h"
#include "EUTreeBeta.h"
#include "TH1D.h"
#include "TH2D.h"

class EUAnaIso : public EUAna, public EUTreeIso
{
	public :
		EUAnaIso(TTree* tree);
		~EUAnaIso();

		void GetCalib();
		void CopyDSSD(EUTreeBeta *beta);
		void CopyEURICA(EUTreeBeta *beta);
		void ResetEURICA();
		void PIDFitting(TH1D* hist, Double_t &mean, Double_t &sig);
		void TWCor();
		void CopyData(EUTreeIso* iso);
};
#endif
