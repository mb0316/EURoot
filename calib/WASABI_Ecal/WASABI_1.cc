#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "eurica.h"
#include "wasabi.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"

using namespace std;

void WASABI_1()
{
	TFile* file = new TFile("../../data/WASABI_Cal/GeSiCorr.root", "read");
	TTree* tree;
	tree = (TTree*) file->Get("data");

	Int_t gehit, ge_ch[84], addhit, add_ch[84], beta_E_X[5][60], beta_T_X[5][60][3], beta_T_Y[5][40][3], beta_E_Y[5][40];
	Double_t ge_E[84], ge_T[84], add_E[84], add_T[84];
	tree->SetBranchAddress("gehit", &gehit);
	tree->SetBranchAddress("ge_ch", ge_ch);
	tree->SetBranchAddress("ge_E", ge_E);
	tree->SetBranchAddress("ge_T", ge_T);
	tree->SetBranchAddress("addhit", &addhit);
	tree->SetBranchAddress("add_ch", add_ch);
	tree->SetBranchAddress("add_E", add_E);
	tree->SetBranchAddress("add_T", add_T);
	tree->SetBranchAddress("beta_E_X", beta_E_X);
	tree->SetBranchAddress("beta_T_X", beta_T_X);
	tree->SetBranchAddress("beta_E_Y", beta_E_Y);
	tree->SetBranchAddress("beta_T_Y", beta_T_Y);

	TH2D* hist_X[5];
	TH2D* hist_chX[5][60];
	TH2D* hist_Y[5];
	TH2D* hist_chY[5][40];
	TH2D* hist_Y3[2];
	TH2D* hist_Y4[2];
	for (Int_t i = 0; i < 5; i++)
	{
		hist_X[i] = new TH2D(Form("dssd_x%d",i+1), "", 350, 0, 1400, 700, 0, 1400);
		hist_Y[i] = new TH2D(Form("dssd_y%d",i+1), "", 350, 0, 1400, 700, 0, 1400);
		for (Int_t j = 0; j < 60; j++)	hist_chX[i][j] = new TH2D(Form("dssd_x%d_ch%d",i+1,j+1), "", 1400, 0, 1400, 1400, 0, 1400);
		for (Int_t j = 0; j < 40; j++)	hist_chY[i][j] = new TH2D(Form("dssd_y%d_ch%d",i+1,j+1), "", 1400, 0, 1400, 1400, 0, 1400);
	}

	Int_t sitime;
	Double_t getime;

	Int_t nEnt = tree->GetEntries();
	cout << nEnt << "entries" << endl;
	for (Int_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		tree->GetEntry(iEnt);
		for (Int_t i = 0; i < addhit; i++)
		{
			getime = add_T[i];
			for (Int_t isi = 0; isi < 5; isi++)
			{
				for (Int_t ich = 0; ich < 60; ich++)
				{
					sitime = beta_T_X[isi][ich][0];
					//if (getime > 21000 && getime < 22500 && sitime > -50000 && beta_E_X[isi][ich] >= 200 && add_E[i] >= 400 && add_E[i] <= 1000)
					if (getime > 21000 && getime < 22500 && sitime > -50000)
					{
						hist_X[isi] -> Fill(beta_E_X[isi][ich], add_E[i]);
						hist_chX[isi][ich] -> Fill(beta_E_X[isi][ich], add_E[i]);
					}
					else continue;
				}
				for (Int_t ich = 0; ich < 40; ich++)
				{
					sitime = beta_T_Y[isi][ich][0];
					//if (getime > 21000 && getime < 22500 && sitime > -50000 && beta_E_Y[isi][ich] >= 200 && add_E[i] >= 400 && add_E[i] <= 1000)
					if (getime > 21000 && getime < 22500 && sitime > -50000)
					{
						hist_Y[isi] -> Fill(beta_E_Y[isi][ich], add_E[i]);
						hist_chY[isi][ich] -> Fill(beta_E_Y[isi][ich], add_E[i]);
					}
					else continue;
				}


			}
		}
	}	

	TFile* out = new TFile("SiEcal_hist.root", "recreate");
	out -> cd();
	for (Int_t i = 0; i < 5; i++)
	{
		hist_X[i] -> Write();
		hist_Y[i] -> Write();
		for (Int_t j = 0; j < 60; j++) hist_chX[i][j] ->Write();
		for (Int_t j = 0; j < 40; j++) hist_chY[i][j] ->Write();
	}

	cout << "corrhist has been saved." << endl;
	out -> Close();
	cout << "All work has been finished." << endl;
}
