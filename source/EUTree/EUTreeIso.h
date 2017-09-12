#ifndef EUTREEISO_H
#define EUTREEISO_H

#include <TROOT.h>
#include <TChain.h>
#include "EUTree.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>

class EUTreeIso : public EUTree
{
	public :

		EUTreeIso(const char* filename, TTree* tree=0);
		EUTreeIso(TTree* tree);
		~EUTreeIso();
		Int_t		GetEntry(Long64_t entry);
		void		Init(TTree *tree);
		void		GetTsEntry(std::map<Long64_t, Long64_t> &mts);
};
#endif
