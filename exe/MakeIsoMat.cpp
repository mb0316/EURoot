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

	if (argc < 5 || argc > 7)
	{
		cout << "Please type 'MakeMAT #Z #Mass #mode1 # mode2 #tend'." << endl;
		cout << "Z : Proton number" << endl;
		cout << "Mass : Mass number" << endl;
		cout << "mode1 : 0 for 1 MeV, 1 for 2 MeV, 2 for 4 MeV, 3 for 8 MeV" << endl;
		cout << "mode2 : 0 for 1ns/ch, 1 for 2ns/ch, 2 for 5ns/ch, 3 for 10ns/ch" << endl;
		cout << "tend : set end time cut for g-g matrix" << endl;
		return 0;
	}

	Int_t zpro = atoi(argv[1]);
	Int_t mass = atoi(argv[2]);
	Int_t mode1 = atoi(argv[3]);
	Int_t mode2 = atoi(argv[4]);
	Int_t tend = atoi(argv[5]);

	EUAnaMat* mat = new EUAnaMat(Form("../results/PID/Isomerdecay_%d_%d.root", zpro, mass), 1);
	mat->MakeIGG(mode1, tend);
	mat->MakeITG(mode1, mode2);

	TCanvas* cvs = new TCanvas("cvs", "", 500, 1000);
	cvs->Divide(1,2);
	cvs->cd(1);
	mat->gg_g->Draw("colz");
	cvs->cd(2);
	mat->tg_g->Draw("colz");

	Int_t ch, bin;
	if (mode1 == 0)	ch = 1;
	if (mode1 == 1)	ch = 2;
	if (mode1 == 2)	ch = 4;
	if (mode1 == 3)	ch = 8;

	if (mode2 == 0)	bin = 1;
	if (mode2 == 1)	bin = 2;
	if (mode2 == 2) bin = 5;
	if (mode2 == 3)	bin = 10;

	cvs->SaveAs(Form("../results/MAT/Iso%d_%d_%dk_%dns.pdf", zpro, mass, ch, tend));

	FILE* out_ggg;
	FILE* out_tgg;
	out_ggg = fopen(Form("../results/MAT/Iso%d_%d_%dk_%dns_gg.mat",  zpro, mass, ch, tend), "wb");
	out_tgg = fopen(Form("../results/MAT/Iso%d_%d_%dk_%dns_tg.mat",  zpro, mass, ch, bin), "wb");
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

//	theApp.Run();
}
