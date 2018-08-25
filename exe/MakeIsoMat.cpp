#include "TTree.h"
#include "EUTreeDecay.h"
#include "EUAnaMat.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include <fstream>
#include "TApplication.h"
#include "TROOT.h"
#include "TCanvas.h"

using namespace std;

int main (int argc, char* argv[])
{
	//	TApplication theApp("test",0,0);

	if (argc < 4 || argc > 5)
	{
		cout << "Please type 'MakeMAT #Z #Mass #statistics # mode #tstart #tend'." << endl;
		cout << "Z : Proton number" << endl;
		cout << "Mass : Mass number" << endl;
		cout << "mode : 0 for 1 MeV, 1 for 2 MeV, 2 for 4 MeV, 3 for 8 MeV" << endl;
		return 0;
	}

	Int_t zpro = atoi(argv[1]);
	Int_t mass = atoi(argv[2]);
	Int_t mode = atoi(argv[3]);
	Int_t tend = 100000;

	cout << "Proton number : " << zpro << endl;
	cout << "Mass number : " << mass << endl;

	EUAnaMat* mat = new EUAnaMat(Form("../results/PID/Isodecay_%d_%d.root", zpro, mass), 1);
	mat->MakeIGG(mode, tend);
	mat->MakeITG(mode);

	TCanvas* cvs = new TCanvas("cvs", "", 1500, 1000);
	cvs->Divide(1,2);
	cvs->cd(1);
	mat->gg_g->Draw("colz");
	cvs->cd(2);
	mat->tg_g->Draw("colz");

	Int_t ch;
	if (mode == 0)	ch = 1;
	if (mode == 1)	ch = 2;
	if (mode == 2)	ch = 4;
	if (mode == 3)	ch = 8;

	FILE* out_gga;
	FILE* out_ggg;
	FILE* out_tga;
	FILE* out_tgg;
	out_ggg = fopen(Form("../results/MAT/Iso%d_%d_%dk_gc_gg.mat",  zpro, mass, ch), "wb");
	out_tgg = fopen(Form("../results/MAT/Iso%d_%d_%dk_gc_tg.mat",  zpro, mass, ch), "wb");
	Short_t temp1[4096]={0};
	Short_t temp2[4096]={0};
	for (Int_t i = 0; i < 4096; i++)
	{
		for (Int_t j = 0; j < 4096; j++)
		{
			temp1[j] = mat->gg_g -> GetBinContent(i+1, j+1);
			temp2[j] = mat->tg_g -> GetBinContent(i+1, j+1);
		}
		fwrite(temp1, sizeof(short), 4096, out_ggg);
		fwrite(temp2, sizeof(short), 4096, out_tgg);
	}

	TFile* out1 = new TFile(Form("../results/MAT/%d_%d_gc_gg.root", zpro, mass), "RECREATE");
	TFile* out2 = new TFile(Form("../results/MAT/%d_%d_gc_tg.root", zpro, mass), "RECREATE");

	out1->cd();
	mat->gg_g -> Write();
	out1->Close();

	out2->cd();
	mat->tg_g -> Write();
	out2->Close();

	//	theApp.Run();
	return 0;
}
