#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TChain.h"



void WASABI_0()
{

	TChain* chain = new TChain("data");
	TString filename;

	for (Int_t ifile = 37; ifile < 74; ifile++)
	{
		if (ifile == 65) continue;
		else
		{
			filename = Form("../../data/WASABI_Calib/GeSiCorr_%04d.root", ifile);
			chain -> Add(filename);
			cout << filename << endl;
		}
	}

	TFile* out = new TFile("../../data/WASABI_Calib/GeSiCorr.root", "RECREATE");
	out -> cd();
	chain -> CopyTree("") -> Write();
	out -> Close();
}
