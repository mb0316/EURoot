#include "EUAnaBeta.h"
#include "EUDataSi.h"

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
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
	TString dssdfile = Form("../data/w3_data_%04d.root", run_num);
	dssd = new EUDataSi(dssdfile.Data());
	Int_t nBytes;
	Long64_t nEnt = dssd->fData->GetEntries();
	beta->GetCalib();

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
		if (beta->F11_TDC_L < 60000)
		{
			beta->ResetDSSD();
			beta->eventid = 0;
			beta->CalibTzero(dssd);
			beta->GetIonPos(dssd,run_num);
			tree->Fill();
		}

		if (beta->F11_TDC_L > 60000)
		{
			beta->eventid = 1;
			beta->ResetDSSD();
			beta->CalibTzeroBeta(dssd);
			beta->GetBetaPos(dssd, tree);
			if (beta->dssdhit < 100)	tree->Fill();
		}

	}

	out -> cd();
	tree -> Write();
	cout << "Tree has been saved." << endl;
	out -> Close();
	cout << "All work has been finished." << endl;
	return 0;
}

