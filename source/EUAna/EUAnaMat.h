#ifndef EUANAMAT_H
#define EUANAMAT_H

#include "EUAna.h"
#include "EUTreeDecay.h"
#include "EUTreeIso.h"
#include <stdio.h>
#include <stdlib.h>
#include "TH2D.h"
#include "TTree.h"

class EUAnaMat : public EUAna
{
	public :
		TH2D* gg_a;
		TH2D* gg_g;
		TH2D* tg_a;
		TH2D* tg_g;
		TH2D* gcT_E;
		TH2D* addT_E;
		TTree* ftree;
		Double_t t;
		Double_t deltaxy;
		Int_t gchit;
		Double_t gc_E[84];
		Double_t gc_T[84];
		Int_t addhit;
		Double_t add_E[84];
		Double_t add_T[84];

		Double_t beta_time_cut[50] = {0};
		Double_t iso_time_cut[50] = {0};

		EUAnaMat(const char* filename, int mode);
		~EUAnaMat();
 		//mass : mass number, name : name of nuclide, type : 0 : addback / 1 : Ge, stat : statistics(0 : good, 1 : bad), format : 0 : 32MB, 1 : 64MB
		void MakeBGG(Int_t &stat, Int_t &mode, Int_t &tstart, Int_t &tend);
		void MakeIGG(Int_t &mode, Int_t &tend);
		void MakeBTG(Int_t &stat, Int_t &mode);
		void MakeITG(Int_t &mode1, Int_t &mode2);
};

#endif
