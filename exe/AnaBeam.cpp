#include "EUAnaBeta.h"
#include "EUDataBeam.h"

#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Please type 'AnaBeam #run'." << endl;
		return 0;
	}

	int run_num = atoi(argv[1]);

	EUDataBeam* beam;

	TFile* out = new TFile(Form("../results/AnaBeam/AnaBeam%04d.root", run_num), "RECREATE");
	TTree* tree = new TTree("tree", "tree");
	EUAnaBeta* beta = new EUAnaBeta(tree);

	TString beamfile = Form("../data/bigrips_run%04d.root", run_num);
	beam = new EUDataBeam(beamfile.Data());

	Int_t nBytes;
	Long64_t nEnt = beam->fData->GetEntries();

	for (Long64_t ient = 0; ient < nEnt; ient++)
	{
		if (ient%1000 == 0)
		{
			tree->AutoSave("FlushBaskets");
			nBytes=tree->FlushBaskets();
			tree->DropBuffers(nBytes);
			tree->DropBaskets();
			printf("%lld entry done.", ient);
			fflush(stdout);
			printf("\r");
		}
		beam->GetEntry(ient);
		beta->CopyTS(beam);
		beta->ResetPID();
		beta->CopyBigRIPS(beam);

		tree->Fill();

	}

	out -> cd();
	tree -> Write();
	cout << "Tree has been saved." << endl;
	out -> Close();
	cout << "All work has been finished." << endl;
	return 0;
}

