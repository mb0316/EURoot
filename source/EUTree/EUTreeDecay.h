#ifndef EUTREEDECAY_H
#define EUTREEDECAY_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EUTree.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>

class EUTreeDecay : public EUTree
{
	public :
		
		EUTreeDecay(const char* filename, TTree* tree=0);
		EUTreeDecay(TTree* tree);
		~EUTreeDecay();
        Int_t       GetEntry(Long64_t entry);
        void        Init(TTree *tree);
		void		GetTsEntry(std::map<Long64_t, Long64_t> &mts);
};
#endif
