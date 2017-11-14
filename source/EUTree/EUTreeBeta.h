#ifndef EUTREEBETA_H
#define EUTREEBETA_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EUTree.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>

class EUTreeBeta : public EUTree
{
	public :

		EUTreeBeta(const char* filename, TTree* tree=0);
		EUTreeBeta(TTree* tree);
		~EUTreeBeta();
		Int_t		GetEntry(Long64_t entry);
		void		Init(TTree *tree);
		void		GetTsEntry(std::multimap<Long64_t, Long64_t> &mts);
		void		GetTsEntry(std::multimap<Long64_t, Long64_t> &mts1, std::multimap<Long64_t, Long64_t> &mts2);
};
#endif
