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

	if (argc < 6 || argc > 7)
	{
		cout << "Please type 'MakeMAT #Z #Mass #statistics #tstart #tend'." << endl;
		return 0;
	}

	Int_t zpro = atoi(argv[1]);
	Int_t mass = atoi(argv[2]);
	Int_t stat = atoi(argv[3]);
	Int_t tstart = atoi(argv[4]);
	Int_t tend = atoi(argv[5]);

	EUAnaMat* mat = new EUAnaMat(Form("../results/PID/Betadecay_%d_%d.root", zpro, mass));
	mat->MakeBGG(stat, tstart, tend);
	mat->MakeBTG(stat);

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

	cvs->SaveAs(Form("../results/MAT/Beta%d_%d.pdf", zpro, mass));

	FILE* out_gga;
	FILE* out_ggg;
	FILE* out_tga;
	FILE* out_tgg;
	out_gga = fopen(Form("../results/MAT/%d_%d_add_gg.mat",  zpro, mass), "wb");
	out_ggg = fopen(Form("../results/MAT/%d_%d_gc_gg.mat",  zpro, mass), "wb");
	out_tga = fopen(Form("../results/MAT/%d_%d_add_tg.mat",  zpro, mass), "wb");
	out_tgg = fopen(Form("../results/MAT/%d_%d_gc_tg.mat",  zpro, mass), "wb");
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

	TFile* out1 = new TFile(Form("../results/MAT/%d_%d_add_gg.root", zpro, mass), "RECREATE");
	TFile* out2 = new TFile(Form("../results/MAT/%d_%d_gc_gg.root", zpro, mass), "RECREATE");
	TFile* out3 = new TFile(Form("../results/MAT/%d_%d_add_tg.root", zpro, mass), "RECREATE");
	TFile* out4 = new TFile(Form("../results/MAT/%d_%d_gc_tg.root", zpro, mass), "RECREATE");

	out1->cd();
	mat->gg_a -> Write();
	out1->Close();

	out2->cd();
	mat->gg_g -> Write();
	out2->Close();

	out3->cd();
	mat->tg_a -> Write();
	out3->Close();

	out4->cd();
	mat->tg_g -> Write();
	out4->Close();

	return 0;
//	theApp.Run();
}
