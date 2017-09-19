#include "EUAnaBeta.h"
#include "EUDataGe.h"

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
        cout << "Please type 'AnaEURICA #run'." << endl;
        return 0;
    }

    int run_num = atoi(argv[1]);

	EUDataGe* hpge;

    TFile* out = new TFile(Form("../results/AnaEURICA/AnaEURICA%04d.root", run_num), "RECREATE");
    TTree* tree = new TTree("tree", "tree");
	EUAnaBeta* beta = new EUAnaBeta(tree);

	TString hpgefile = Form("../data/go4_%04d.root", run_num);
	hpge = new EUDataGe(hpgefile.Data());

    beta->GetCalib();
	Int_t nBytes;
	Long64_t nEnt = hpge->fData->GetEntries();

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
        hpge->GetEntry(ient);
        beta->CopyTS(hpge);
		beta->ResetPL();
		beta->ResetEURICA();
        beta->CopyPL(hpge);
		beta->CopyEURICA(hpge);
		beta->AngleEURICA();

		tree->Fill();

    }

    out -> cd();
    tree -> Write();
    cout << "Tree has been saved." << endl;
    out -> Close();
    cout << "All work has been finished." << endl;

}

