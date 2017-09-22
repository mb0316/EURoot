#ifndef EUDATA_H
#define EUDATA_H

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TObject.h>
#include <TNamed.h>
#include <TTree.h>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

class EUData : public TObject
{
	public :
		TFile	*f;
		TTree	*fData;
		Int_t	fCurrent;

		EUData();
		~EUData();
		virtual Int_t	GetEntry(Long64_t entry) = 0;
		virtual void	Init(TTree *tree) = 0;
		virtual void	GetTsEntry(std::map<Long64_t, Long64_t> &mts) = 0;
};
#endif

