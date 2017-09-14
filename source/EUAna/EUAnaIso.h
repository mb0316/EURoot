#ifndef EUANAISO_H
#define EUANAISO_H

#include <TROOT.h>
#include <TChain.h>
#include "EUAna.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "EUDataBeam.h"
#include "EUDataSi.h"
#include "EUDataGe.h"
#include "EUTreeIso.h"

class EUAnaIso : public EUAna, public EUTreeIso
{
	public :
		EUAnaIso(TTree* tree);
		~EUAnaIso();
		void	GeIsoTDCoffset(); //analysis for artificial correction of the TDCs, TDCl offset

        void    CopyTS(EUDataSi *dssd); //copy the timestamp from WASABI data
        void    CopyBigRIPS(EUDataBeam *beam); //copy AoQ and Z data from bigrips data
        void    CopyPL(EUDataSi *dssd); //copy F11 PL and veto PL data from WASABI data
        void    CopyEURICA(EUDataGe *hpge); //copy EURICA, LaBr, beta PL data from eurica data
        void    ResetEURICA(); //reset or set 0 for hit information of eurica
        void    ResetPID(); //reset or set 0 for PID
        void    Addback(); //addback algorithm
		void	AngleEURICA();
};
#endif
