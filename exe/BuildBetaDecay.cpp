#include "TTree.h"
#include "EUTreeBeta.h"
#include "EUTreeDecay.h"
#include "EUAnaBeta.h"
#include "EUAnaDecay.h"
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
		cout << "Please type 'BuildBetaDecay #run'." << endl;
		return 0;
	}

	int run_num = atoi(argv[1]);

	TString betafile = Form("../results/MergeBeam/MergeBeam%04d.root", run_num);
	TFile* out = new TFile(Form("../results/BuildBetaDecay/BuildBetaDecay%04d.root", run_num), "RECREATE");
	TTree* tree = new TTree("tree", "tree");

	EUTreeBeta* beta = new EUTreeBeta(betafile.Data());
	EUAnaDecay* decay = new EUAnaDecay(tree);

	map<Long64_t, Long64_t> mts_master, mts_slave;
	map<Long64_t, Long64_t>::iterator imts_master, imts_slave;

	cout << "Start checking timestamp for ions and betas." << endl;
	beta->GetTsEntry(mts_master, mts_slave);

	cout << mts_master.size() << " events for ions." << endl;
	cout << mts_slave.size() << " eventsf for betas." << endl;

	Long64_t twL = -1e8;
	Long64_t twH = 6e8;
	Long64_t tsL = 0;
	Long64_t tsH = 0;
	Long64_t tsIon = 0;
	Long64_t tsBeta = 0;

	cout << "Start analyzing and build beta decay data." << endl;
	Long64_t ent = 0;
	decay->GetCalib();
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
		tsIon = imts_master->first;
		tsL = tsIon + twL;
		tsH = tsL + twH;
		beta->GetEntry(imts_master->second);
		decay->CopyDSSD(beta);
		imts_slave = mts_slave.begin();

		while (imts_slave != mts_slave.end() && imts_slave->first < tsH)
		{
			if (imts_slave->first > tsL)
			{
				beta->GetEntry(imts_slave->second);

				decay->BetaTrack(beta);
				if (decay->good_beta == 1)
				{
					tsBeta = imts_slave->first;
					decay->t = (tsBeta - tsIon)/(1e5);
					decay->ResetEURICA();
					decay->CopyEURICA(beta);
					decay->TWCor();
					tree->Fill();
				}

			}
			imts_slave++;
		}
		tsIon = 0;
		tsBeta = 0;
	}

	out->cd();
	tree->Write();
	cout << "Tree has been saved." << endl;
	out->Close();
	cout << "All work has been finished." << endl;
}
