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

class EUAnaIso : public EUAna, public EUTreeIso
{
	public :
		EUAnaIso(TTree* tree);
		~EUAnaIso();

		void GetCalib();
		void CopyDSSD(EUTreeBeta *beta);
		void TWCor();
		void CopyEURICA(EUTreeBeta *beta);
		void ResetEURICA();
		
};
#endif
