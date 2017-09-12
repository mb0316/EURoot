#include "EUTreeBeta.h"
#include "EUAnaDecay.h"
#include "EUTreeDecay.h"

#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Please type 'betadecay #run'." << endl;
		return 0;
	}

	int run_num = atoi(argv[1]);

	TFile* out = new TFile(Form("../results/BetaDecayData/betadecay%04d.root", run_num), "RECREATE");
	TTree* tree = new TTree("tree", "tree");

	EUAnaDecay* decay = new EUAnaDecay(tree);

	TString betafile = Form("../results/BetaMergeData/beta_beam%04d.root", run_num);

	EUTreeBeta* beta = new EUTreeBeta(betafile.Data());

	map<Long64_t, Long64_t> mtsion, mtsbeta;
	map<Long64_t, Long64_t>::iterator imtsion, imtsbeta;

	beta->GetTsEntry(mtsion, mtsbeta);
	cout << mtsion.size() << " events for ions." << endl;
	cout << mtsbeta.size() << " events for betas." << endl;

	Long64_t timewindowL = -1e8;
	Long64_t timewindowU = 5e8;
	Long64_t tsL = 0;
	Long64_t tsU = 0;

	cout << "Start analyzing and build beta-decay data." << endl;
	Long64_t tsIon, tsBeta;
	decay->GetCalib();

	Long64_t ent = 0;
	Int_t nBytes;

	for (imtsion = mtsion.begin(); imtsion != mtsion.end(); imtsion++)
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

		tsIon = imtsion -> first;
		tsL = tsIon + timewindowL;
		tsU = tsIon + timewindowU;

		beta->GetEntry(imtsion->second);
		decay->CopyDSSD(beta);
		imtsbeta = mtsbeta.begin();

		while (imtsbeta != mtsbeta.end() && imtsbeta->first < tsU)
		{
			if (imtsbeta->first > tsL)
			{
				beta->GetEntry(imtsbeta->second);
				decay->GetXYDistance(beta->beta_x, beta->beta_y);

				if (beta->beta_z == decay->z && decay->deltaxy < 3)
				{
					tsBeta = imtsbeta->first;
					decay->t = (tsBeta - tsIon)/(1e5);
					decay->GetBetaEnergy(beta);
					decay->ResetEURICA();
					decay->CopyEURICA(beta);
					decay->GetBetaTDCoffset();

					tree->Fill();
				}
			}
			imtsbeta++;
		}
		tsIon = 0;
		tsBeta = 0;
	}

	out->cd();
	tree->Write();
	cout << "Tree has been saved." << endl;
	out -> Close();
	cout << "All work has been finished." << endl;
}
