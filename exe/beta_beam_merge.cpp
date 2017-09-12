#include "EUAnaBeta.h"
#include "EUTreeBeta.h"
#include "EUDataBeam.h"

#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <map>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Please type 'beta_beam_merge #run'." << endl;
        return 0;
    }

    int run_num = atoi(argv[1]);

    TFile* out = new TFile(Form("../results/BetaMergeData/beta_beam%04d.root", run_num), "RECREATE");
    TTree* tree = new TTree("tree", "tree");
	EUAnaBeta* beta = new EUAnaBeta(tree);

	TString beamfile = Form("../data/bigrips_run%04d.root", run_num);
	TString betafile = Form("../results/BetaMergeData/si_ge%04d.root", run_num);

	EUDataBeam *beam = new EUDataBeam(beamfile.Data());
	EUTreeBeta *merge = new EUTreeBeta(betafile.Data());

	map<Long64_t, Long64_t> mts_master, mts_slave, mts_tot;
	map<Long64_t, Long64_t>::iterator imts_master, imts_slave, imts_tot;

    cout << "Start checking timestamp correlation between BetaMerge and Beam" << endl;

    cout << "BetaMerge" << endl;
    merge->GetTsEntry(mts_master);

    cout << "Beam" << endl;
    beam->GetTsEntry(mts_slave);

    cout << mts_master.size() << " events for BetaMerge" << endl;
    cout << mts_slave.size() << " events for Beam" << endl;

    cout << "Start matching TS." << endl;

	beta->MapCorrel(mts_master, imts_master, mts_slave, imts_slave, mts_tot, 100, 100);

    mts_slave.erase(imts_slave, mts_slave.end());
    mts_slave.clear();

    cout << "The size of matching TS between BetaMerge & Beam : " << mts_tot.size() << endl;


    cout << "Start analyzing and copying data." << endl;

    Long64_t ent = 0;
    Int_t ihit;
    UInt_t  jhit;
	Int_t nBytes;

    for (imts_master = mts_master.begin(); imts_master != mts_master.end(); imts_master++)
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
		beta->ResetPID();
		beta->ResetEURICA();
		beta->ResetDSSD();
        merge->GetEntry(imts_master->second);
        beta->CopyTS(merge);
		beta->CopyEURICA(merge);
		beta->CopyDSSD(merge);

		imts_tot = mts_tot.find(imts_master->second);
		if (imts_tot != mts_tot.end())
		{
			beam->GetEntry(imts_tot->second);
			beta->CopyBigRIPS(beam);
		}

		tree->Fill();
	}
    out -> cd();
    tree -> Write();
    cout << "Tree has been saved." << endl;
    out -> Close();
    cout << "All work has been finished." << endl;
}

