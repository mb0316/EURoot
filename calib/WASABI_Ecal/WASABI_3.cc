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
	TFile* file = new TFile("../../data/WASABI_Calib/GeSiCorr.root", "read");
	TTree* tree;
	tree = (TTree*) file->Get("data");

	Int_t gehit, ge_ch[84], beta_E_X[5][60], beta_T_X[5][60], beta_T_Y[5][40], beta_E_Y[5][40];
	Double_t ge_E[84], ge_T[84];
	tree->SetBranchAddress("gehit", &gehit);
	tree->SetBranchAddress("ge_ch", ge_ch);
	tree->SetBranchAddress("ge_E", ge_E);
	tree->SetBranchAddress("ge_T", ge_T);
	tree->SetBranchAddress("beta_E_X", beta_E_X);
	tree->SetBranchAddress("beta_T_X", beta_T_X);
	tree->SetBranchAddress("beta_E_Y", beta_E_Y);
	tree->SetBranchAddress("beta_T_Y", beta_T_Y);

	Int_t iden, numdssd, nch;
	Double_t temp_gain, temp_offset;
	Double_t gain_X[5][60];
	Double_t gain_Y[5][40];
	Double_t offset_X[5][60];
	Double_t offset_Y[5][40];

	ifstream cal;

	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t ich = 0; ich < 100; ich++)
		{
			cal.open (Form("WASABI_gain/WASABI_gain_%d_%d.dat", idssd, ich));
			if (ich < 60)
			{
				cal >> temp_gain >> temp_offset;
				gain_X[idssd][ich] = -temp_gain;
				offset_X[idssd][ich] = -temp_gain*temp_offset;
			}
			else
			{
				cal >> temp_gain >> temp_offset;
				gain_Y[idssd][ich-60] = -temp_gain;
				offset_Y[idssd][ich-60] = -temp_gain*temp_offset;
			}
			cal.close();
		}
	}

	ofstream calout;
	calout.open ("WASABI_gain.dat");

	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t ich = 0; ich < 100; ich++)
		{
			if (ich < 60)
			{
				calout << idssd << "	" << ich << "	" << gain_X[idssd][ich] << "	" << offset_X[idssd][ich] << endl;
				cout << "X" << " " << idssd << " " << ich << " " << gain_X[idssd][ich] << " " << offset_X[idssd][ich] << endl;
			}
			else
			{
				calout << idssd << "	" << ich << "	"<< gain_Y[idssd][ich-60] << "	" << offset_Y[idssd][ich-60]  << endl;
				cout << "Y" << " " << idssd << " " << ich << " " << gain_Y[idssd][ich-60] << " " << offset_Y[idssd][ich-60] << endl;
			}
		}
	}



	TH1D* hist_X[5][60];
	TH1D* hist_Y[5][40];
	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t j = 0; j < 60; j++)	hist_X[i][j] = new TH1D(Form("dssd_x%d_ch%d",i+1,j+1), "", 500, 0, 2000);
		for (Int_t j = 0; j < 40; j++)	hist_Y[i][j] = new TH1D(Form("dssd_y%d_ch%d",i+1,j+1), "", 400, 0, 2000);
	}

	Int_t sitime;
	Double_t getime;
	Double_t sienergy;

	Int_t dssdhitX = 0;
	Int_t dssdhitY = 0;

	Double_t dssd_X_Tcut_L[5] = {-2950, -2960, -3000, -2950, -3050};
	Double_t dssd_X_Tcut_H[5] = {-2910, -2914, -2910, -2914, -2920};
	Double_t dssd_Y_Tcut_L[5] = {-3845.3, -3833.9, -3403.2, -3643.4, -2550.6};
	Double_t dssd_Y_Tcut_H[5] = {-1691.8, -1113.1, -1861.2, -1343, -964.6};

	Int_t nEnt = tree->GetEntries();
	cout << nEnt << "entries" << endl;

	for (Int_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		tree->GetEntry(iEnt);
		dssdhitX = 0;
		dssdhitY = 0;

		for (Int_t i = 0; i < gehit; i++)
		{
			getime = ge_T[i];
			for (Int_t isi = 0; isi < 5; isi++)
			{
				for (Int_t ich = 0; ich < 60; ich++)
				{
					sitime = beta_T_X[isi][ich];
					if (getime > 21558.5 && getime < 21796.1 && sitime < dssd_X_Tcut_H[isi] && sitime > dssd_X_Tcut_L[isi] && beta_E_X[isi][ich] >= 100 && ge_E[i] > 300 && ge_E[i] < 1100) dssdhitX++;
					else continue;
				}
				for (Int_t ich = 0; ich < 40; ich++)
				{
					sitime = beta_T_Y[isi][ich];
					if (getime > 21558.5 && getime < 21796.1 && sitime < dssd_Y_Tcut_H[isi] && sitime > dssd_Y_Tcut_L[isi] && beta_E_Y[isi][ich] >= 100 && ge_E[i] > 300 && ge_E[i] < 1100) dssdhitY++;
					else continue;
				}
			}
		}

		for (Int_t i = 0; i < gehit; i++)
		{
			getime = ge_T[i];
			for (Int_t isi = 0; isi < 5; isi++)
			{
				if (dssdhitX == 1)
				{
					for (Int_t ich = 0; ich < 60; ich++)
					{
						sitime = beta_T_X[isi][ich];
						if (getime > 21558.5 && getime < 21796.1 && sitime < dssd_X_Tcut_H[isi] && sitime > dssd_X_Tcut_L[isi] && beta_E_X[isi][ich] >= 100 && ge_E[i] > 300 && ge_E[i] < 1100)
						{
							sienergy = gain_X[isi][ich]*beta_E_X[isi][ich] + offset_X[isi][ich];
							hist_X[isi][ich] -> Fill(sienergy+ge_E[i]);
						}
						else continue;
					}
				}
				if (dssdhitY == 1)
				{
					for (Int_t ich = 0; ich < 40; ich++)
					{
						sitime = beta_T_Y[isi][ich];
						if (getime > 21558.5 && getime < 21796.1 && sitime < dssd_Y_Tcut_H[isi] && sitime > dssd_Y_Tcut_L[isi] && beta_E_Y[isi][ich] >= 100 && ge_E[i] > 300 && ge_E[i] < 1100)
						{
							sienergy = gain_Y[isi][ich]*beta_E_Y[isi][ich] + offset_Y[isi][ich];
							hist_Y[isi][ich] -> Fill(sienergy+ge_E[i]);
						}
						else continue;
					}
				}

			}
		}
	}

	TFile* out = new TFile("SiEcal_calib_hist.root", "recreate");
	out -> cd();
	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t j = 0; j < 60; j++) hist_X[i][j] ->Write();
		for (Int_t j = 0; j < 40; j++) hist_Y[i][j] ->Write();
	}

	cout << "corrhist has been saved." << endl;
	out -> Close();
	cout << "All work has been finished." << endl;
}
