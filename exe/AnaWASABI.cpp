#include "EUAnaBeta.h"
#include "EUDataSi.h"

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
		cout << "Please type 'AnaWASABI #run'." << endl;
		return 0;
	}

	int run_num = atoi(argv[1]);

	EUDataSi* dssd;

	TFile* out = new TFile(Form("../results/AnaWASABI/AnaWASABI%04d.root", run_num), "RECREATE");
	TTree* tree = new TTree("tree", "tree");
	EUAnaBeta* beta = new EUAnaBeta(tree);

	TString dssdfile = Form("../data/WASABI%04d.root", run_num);
	dssd = new EUDataSi(dssdfile.Data());
	Int_t nBytes;
	Long64_t nEnt = dssd->fData->GetEntries();

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
		dssd->GetEntry(ient);
		beta->CopyTS(dssd);
		beta->ResetPL();
		beta->CopyPL(dssd);
		if ((beta->F11_TDC_L > -2200 && beta->F11_TDC_L < -1800 && beta->F11_TDC_R > -2200 && beta->F11_TDC_R < -1800) && (beta->vetoPL1 < -100E3 && beta->vetoPL2 < -100E3))
		{
			beta->ResetDSSD();
			beta->eventid = 0;
			beta->GetIonPos(dssd);
			tree->Fill();
		}

		else if (beta->vetoPL1 < -100E3 && beta->vetoPL2 < -100E3)
		{
			beta->eventid = 1;
			beta->ResetDSSD();

			for (Int_t ihit = 0; ihit < 5; ihit++)
			{
				beta->GetBetaPos(dssd, ihit, tree);
//				if (beta->fire == 0)	tree->Fill();
			}

		}

	}

	out -> cd();
	tree -> Write();
	cout << "Tree has been saved." << endl;
	out -> Close();
	cout << "All work has been finished." << endl;

}

