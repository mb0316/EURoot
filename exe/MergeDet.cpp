#include "EUAnaBeta.h"

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
		cout << "Please type 'MergeDet #run'." << endl;
		return 0;
	}


	int run_num = atoi(argv[1]);

	EUTreeBeta* dssd;
	EUTreeBeta* hpge;

	TFile* out = new TFile(Form("../results/MergeDet/MergeDet%04d.root", run_num), "RECREATE");
	TTree* tree = new TTree("tree", "tree");
	EUAnaBeta* beta = new EUAnaBeta(tree);

	TString dssdfile = Form("../results/AnaWASABI/AnaWASABI%04d.root", run_num);
	TString hpgefile = Form("../results/AnaEURICA/AnaEURICA%04d.root", run_num);
	dssd = new EUTreeBeta(dssdfile.Data());
	hpge = new EUTreeBeta(hpgefile.Data());

	map<Long64_t, Long64_t> mtsd, mtsg, mvdg;
	map<Long64_t, Long64_t>::iterator imtsd, imtsg, imvdg;

	cout << "Start checking timestamp correlation between WASABI and EURICA" << endl;

	cout << "WASABI" << endl;
	dssd->GetTsEntry(mtsd);

	cout << "EURICA" << endl;
	hpge->GetTsEntry(mtsg);

	cout << mtsd.size() << " events for WASABI" << endl;
	cout << mtsg.size() << " events for EURICA" << endl;

	cout << "Start matching TS." << endl;

	beta->MapCorrel(mtsd, imtsd, mtsg, imtsg, mvdg, 10, 10);

	mtsg.erase(imtsg, mtsg.end());
	mtsg.clear();
	mtsd.erase(imtsd, mtsd.end());
	mtsd.clear();

	cout << "The size of matching TS between WASABI & EURICA : " << mvdg.size() << endl;


	cout << "Start analyzing and copying data." << endl;

	Long64_t ent = 0;
	Int_t nBytes;

	for (imvdg = mvdg.begin(); imvdg != mvdg.end(); imvdg++)
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
		dssd->GetEntry(imvdg->first);
		beta->CopyTS(dssd);
		beta->ResetPL();
		hpge->GetEntry(imvdg->second);
		beta->CopyPL(dssd, hpge);

		beta->ResetDSSD();
		beta->CopyDSSD(dssd);
		beta->ResetEURICA();
		beta->CopyEURICA(hpge);

		tree->Fill();

	}

	out -> cd();
	tree -> Write();
	cout << "Tree has been saved." << endl;
	out -> Close();
	cout << "All work has been finished." << endl;

}

