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

void WASABI_3()
{
	TFile* file = new TFile("GeSiCorr.root", "read");
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

	Int_t iden, numdssd, ich;
	Double_t temp_gain, temp_offset;
	Double_t gain_X[5][60];
	Double_t gain_Y[5][40];
	Double_t offset_X[5][60];
	Double_t offset_Y[5][40];

	ifstream cal;
	cal.open("../WASABI_gain.dat");
	for (Int_t i = 0; i < 500; i++)
	{
		cal >> iden >> numdssd >> ich >> temp_gain >> temp_offset;
		if (iden == 0)
		{
			gain_X[numdssd][ich] = abs(temp_gain);
			offset_X[numdssd][ich] = abs(temp_offset);
		}
		if (iden == 1)
		{
			gain_Y[numdssd][ich] = abs(temp_gain);
			offset_Y[numdssd][ich] = abs(temp_offset);
		}
		cout << iden << " " << numdssd << " " << ich << " " << temp_gain << " " << temp_offset << endl;
	}

	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t j = 0; j < 60; j++)
		{
			cout << "WASABI #"<< i+1 << ", X strip #"<< j+1 << " : " << gain_X[i][j] << " " << offset_X[i][j] << endl;
		}
		for (Int_t j = 0; j < 40; j++)
		{
			cout << "WASABI #"<< i+1 << ", Y strip #"<< j+1 << " : " << gain_Y[i][j] << " " << offset_Y[i][j] << endl;
		}
	}

	TH2D* hist_X[5];
	TH2D* hist_Y[5];
	for (Int_t i = 0; i < 5; i++)
	{
		hist_X[i] = new TH2D(Form("dssd_x%d",i+1), "", 350, 0, 1400, 700, 0, 1400);
		hist_Y[i] = new TH2D(Form("dssd_y%d",i+1), "", 350, 0, 1400, 700, 0, 1400);
	}

	Int_t sitime;
	Double_t getime;
	Double_t sienergy;

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
					if (getime > 21500 && getime < 22000 && sitime > -50000)
					{
						sienergy = double(double(beta_E_X[isi][ich])*gain_X[isi][ich]) + offset_X[isi][ich];
						hist_X[isi] -> Fill(sienergy, add_E[i]);
					}
					else continue;
				}
				for (Int_t ich = 0; ich < 40; ich++)
				{
					sitime = beta_T_Y[isi][ich][0];
					if (getime > 21500 && getime < 22000 && sitime > -50000)
					{
						sienergy = double(double(beta_E_Y[isi][ich])*gain_Y[isi][ich]) + offset_Y[isi][ich];
						hist_Y[isi] -> Fill(sienergy, add_E[i]);
					}
					else continue;
				}


			}
		}
	}	

	TFile* out = new TFile("SiEcal_calibrated_hist.root", "recreate");
	out -> cd();
	for (Int_t i = 0; i < 5; i++)
	{
		hist_X[i] -> Write();
		hist_Y[i] -> Write();
	}

	cout << "corrhist has been saved." << endl;
	out -> Close();
	cout << "All work has been finished." << endl;
}
