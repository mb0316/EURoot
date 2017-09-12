#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "wasabi.h"
#include "bigrips.h"
#include "eurica.h"
#include "betamerge.h"
#include "isomerge.h"
#include "BMana.h"

using namespace std;

int main(int argc, char* argv[])
{
/*
        if (argc < 2)
        {
                cout << "Please type 'Isoana #Merge'." << endl;
                return 0;
        }
*/
//	int runN = atoi(argv[1]);
	char inputfile[100];

	sprintf(inputfile, "./IsoMergeData/IsoMerge_tot.root");

	BMana ana;
	isomerge iso;
	iso.GetTree(inputfile);
	ana.GetCalib();
	TFile* out = new TFile("./IsoMergeData/IsoAna_tot.root", "RECREATE");
	TTree* tree = new TTree("tree", "tree");

	cout << "Start analyzing and build isomer decay." << endl;
	ana.MakeIsomerTree(tree);
	Long64_t nEnt = iso.fChain -> GetEntries();

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		iso.GetEntry(iEnt);
		ana.CopyIsoData(iso);
		ana.Slewcor();
		ana.GeIsoTDCoffset();
		tree -> Fill();
	}
	out -> cd();
	tree -> Write();
	cout << "Tree has been saved." << endl;
	out -> Close();
	cout << "All work has been finished." << endl;


}	
