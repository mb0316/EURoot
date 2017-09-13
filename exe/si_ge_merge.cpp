#include "EUAnaBeta.h"
#include "EUDataSi.h"
#include "EUDataGe.h"

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
        cout << "Please type 'si_ge_merge #run'." << endl;
        return 0;
    }


    int run_num = atoi(argv[1]);

	EUDataSi* dssd;
	EUDataGe* hpge;

    TFile* out = new TFile(Form("../results/BetaMergeData/si_ge%04d.root", run_num), "RECREATE");
    TTree* tree = new TTree("tree", "tree");
	EUAnaBeta* beta = new EUAnaBeta(tree);

	TString dssdfile = Form("../data/WASABI%04d.root", run_num);
	TString hpgefile = Form("../data/go4_%04d.root", run_num);
	dssd = new EUDataSi(dssdfile.Data());
	hpge = new EUDataGe(hpgefile.Data());

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

//    beta->MakeBetaTree(tree);
//	EUTreeBeta* btree = new EUTreeBeta(tree);
    beta->GetCalib();
    Long64_t ent = 0;
    Int_t ihit;
    UInt_t  jhit;
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
        beta->CopyPL(dssd);
        hpge->GetEntry(imvdg->second);
        if (((beta->F11_PLl > -50000 && beta->F11_PLr > -50000) || (beta->F7_PLl > -50000 && beta->F7_PLr > -50000)) && (beta->vetoPL1 < -10000 || beta->vetoPL2 < -10000))
        {
			beta->ResetDSSD();
            beta->ResetEURICA();
            beta->CopyEURICA(hpge);
            beta->eventid = 0;
            beta->GetIonPos(dssd);
			tree->Fill();
        }

        else if (beta->vetoPL1 < -10000 || beta->vetoPL2 < -10000)
        {
            beta->eventid = 1;
            beta->ResetDSSD();

            for (Int_t ihit = 0; ihit < 5; ihit++)
            {
                beta->GetBetaPos(dssd, ihit);
                beta->ResetEURICA();
                if (beta->fire == 0)
                {
                    beta->CopyEURICA(hpge);
					tree->Fill();
                }
            }

        }

    }

    out -> cd();
    tree -> Write();
    cout << "Tree has been saved." << endl;
    out -> Close();
    cout << "All work has been finished." << endl;

}

