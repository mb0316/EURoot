#include "TTree.h"
#include "EUTreeBeta.h"
#include "EUTreeIso.h"
#include "EUAnaBeta.h"
#include "EUAnaIso.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "TFile.h"
#include <fstream>
#include <map>

using namespace std;

int main (int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Please type 'BuildIsoDecay #run'." << endl;
		return 0;
	}

	int run_num = atoi(argv[1]);

	TString betafile = Form("../results/MergeBeam/MergeBeam%04d.root", run_num);
	TFile* out = new TFile(Form("../results/BuildIsoDecay/BuildIsoDecay%04d.root", run_num), "RECREATE");
	TTree* tree = new TTree("tree", "tree");

	EUTreeBeta* beta = new EUTreeBeta(betafile.Data());
	EUAnaIso* decay = new EUAnaIso(tree);

	multimap<Long64_t, Long64_t> mts;
	multimap<Long64_t, Long64_t>::iterator imts;

	cout << "Start checking timestamp for ions." << endl;
	beta->GetTsEntry(mts);

	cout << mts.size() << " events for ions." << endl;

	cout << "Start analyzing and build isomer decay data." << endl;
	Long64_t ent = 0;
	decay->GetCalib();
	Int_t nBytes;

	for (imts = mts.begin(); imts != mts.end(); imts++)
	{
		ent++;
		if (ent%1000 == 0)
		{
			tree->AutoSave("FlushBaskets");
			nBytes=tree->FlushBaskets();
			tree->DropBuffers(nBytes);
			tree->DropBaskets();
			printf("%lld entry done.", ent);
			fflush(stdout);
			printf("\r");
		}
		beta->GetEntry(imts->second);
		if (beta->eventid == 0)
		{			
			decay->CopyDSSD(beta);
			if (decay->z >= 0 && decay->z <=4)
			{
				decay->ResetEURICA();
				decay->CopyEURICA(beta);
				decay->TWCor();
				tree->Fill();
			}
		}
	}

	out->cd();
	tree->Write();
	cout << "Tree has been saved." << endl;
	out->Close();
	cout << "All work has been finished." << endl;
}
