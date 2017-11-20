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

	if (argc < 7 || argc > 8)
	{
		cout << "Please type 'MakeMAT #Z #Mass #statistics # mode #tstart #tend'." << endl;
		cout << "Z : Proton number" << endl;
		cout << "Mass : Mass number" << endl;
		cout << "statistics : 0 for good statistics, 1 for bad statistics" << endl;
		cout << "mode : 0 for 1 MeV, 1 for 2 MeV, 2 for 4 MeV, 3 for 8 MeV" << endl;
		cout << "tstart : set first time cut for g-g matrix" << endl;
		cout << "tend : set end time cut for g-g matrix" << endl;
		return 0;
	}

	Int_t zpro = atoi(argv[1]);
	Int_t mass = atoi(argv[2]);
	Int_t stat = atoi(argv[3]);
	Int_t mode = atoi(argv[4]);
	Int_t tstart = atoi(argv[5]);
	Int_t tend = atoi(argv[6]);

	EUAnaMat* mat = new EUAnaMat(Form("../results/PID/Betadecay_%d_%d.root", zpro, mass), 0);
	mat->MakeBGG(stat, mode, tstart, tend);
	mat->MakeBTG(stat, mode);

	TCanvas* cvs = new TCanvas("cvs", "", 1500, 1000);
	cvs->Divide(2,2);
	cvs->cd(1);
	mat->gg_a->Draw("colz");
	cvs->cd(2);
	mat->gg_g->Draw("colz");
	cvs->cd(3);
	mat->tg_a->Draw("colz");
	cvs->cd(4);
	mat->tg_g->Draw("colz");

	Int_t ch;
	if (mode == 0)	ch = 1;
	if (mode == 1)	ch = 2;
	if (mode == 2)	ch = 4;
	if (mode == 3)	ch = 8;


	cvs->SaveAs(Form("../results/MAT/Beta%d_%d_%dk.pdf", zpro, mass, ch));

	FILE* out_gga;
	FILE* out_ggg;
	FILE* out_tga;
	FILE* out_tgg;
	out_gga = fopen(Form("../results/MAT/Beta%d_%d_%dk_add_gg.mat",  zpro, mass, ch), "wb");
	out_ggg = fopen(Form("../results/MAT/Beta%d_%d_%dk_gc_gg.mat",  zpro, mass, ch), "wb");
	out_tga = fopen(Form("../results/MAT/Beta%d_%d_%dk_add_tg.mat",  zpro, mass, ch), "wb");
	out_tgg = fopen(Form("../results/MAT/Beta%d_%d_%dk_gc_tg.mat",  zpro, mass, ch), "wb");
	Short_t temp1[4096]={0};
	Short_t temp2[4096]={0};
	Short_t temp3[4096]={0};
	Short_t temp4[4096]={0};
	for (Int_t i = 0; i < 4096; i++)
	{
		for (Int_t j = 0; j < 4096; j++)
		{
			temp1[j] = mat->gg_a -> GetBinContent(i+1, j+1);
			temp2[j] = mat->gg_g -> GetBinContent(i+1, j+1);
			temp3[j] = mat->tg_a -> GetBinContent(i+1, j+1);
			temp4[j] = mat->tg_g -> GetBinContent(i+1, j+1);
		}
		fwrite(temp1, sizeof(short), 4096, out_gga);
		fwrite(temp2, sizeof(short), 4096, out_ggg);
		fwrite(temp3, sizeof(short), 4096, out_tga);
		fwrite(temp4, sizeof(short), 4096, out_tgg);
	}
//	theApp.Run();
}
