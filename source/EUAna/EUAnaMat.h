#ifndef EUANAMAT_H
#define EUANAMAT_H

#include "EUAna.h"
#include "EUTreeDecay.h"
#include "EUTreeIso.h"
#include <stdio.h>
#include <stdlib.h>


class EUAnaMat : public EUAna
{
	public :
		EUAnaMat(TTree *tree);
		~EUAnaMat();
 		//mass : mass number, name : name of nuclide, type : 0 : addback / 1 : Ge, stat : statistics(0 : good, 1 : bad), format : 0 : 32MB, 1 : 64MB
		void MakeGG(Int_t &mass, char* name, Int_t &type, Int_t &stat, Int_t &format, Int_t &tstart, Int_t &tend);
		void MakeTG(Int_t &mass, char* name, Int_t &type, Int_t &stat, Int_t &format);
		void MakeDCO(Int_t &mass, char* name, Int_t &type, Int_t &stat, Int_t &format);

}

#endif
