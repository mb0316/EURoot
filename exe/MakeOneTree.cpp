#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include <stdio.h>
#include <stdlib.h>
#include "TROOT.h"
#include <iostream>

using namespace std;

int main (int argc, char* argv[])
{
	int mode = atoi(argv[1]);

	if (argc < 2 || (mode < 0 && mode > 1))
	{
		cout << "Please type MakeOneTree #mode; mode == 0 : Beta-decay, mode == 1 : Isomeric decay" << endl;
		return 0;
	}

	TChain* chain = new TChain("tree");
	TString filename;

	for (Int_t ifile = 1016; ifile < 1130; ifile++)
	{
		if (ifile == 1012|| ifile == 1049 || ifile == 1051 || ifile == 1063 || ifile == 1067 || ifile == 1095 || ifile == 1110 || ifile == 1112 || ifile == 1113 || ifile == 1123)       continue;
		else if (ifile > 1023 && ifile < 1028)  continue;
		else if (ifile > 1040 && ifile < 1045)  continue;
		else if (mode == 0)
		{
			filename = Form("../results/BuildBetaDecay/BuildBetaDecay%04d.root", ifile);
			chain -> Add(filename);
			std::cout << filename << " done." << std::endl;
		}
		else if (mode == 1)
		{
			filename = Form("../results/BuildIsoDecay/BuildIsoDecay%04d.root", ifile);
			chain -> Add(filename);
			std::cout << filename << " done." << std::endl;
		}
	}

	if (mode == 0)
	{
		TFile* out = new TFile("../results/BuildBetaDecay/BuildBetaDecay.root", "RECREATE");
		out -> cd();
		chain -> CopyTree("") -> Write();
		out -> Close();
		std::cout << "All work has been done." << std::endl;
	}

	if (mode == 1)
	{
		TFile* out = new TFile("../results/BuildIsoDecay/BuildIsoDecay.root", "RECREATE");
		out -> cd();
		chain -> CopyTree("") -> Write();
		out -> Close();
		std::cout << "All work has been done." << std::endl;
	}
}
