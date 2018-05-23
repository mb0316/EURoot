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

void WASABI_7()
{
	TFile* file = new TFile("GeSiCorr.root", "read");
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

	Int_t iden, numdssd, ich;
	Double_t sig;
	Double_t temp_gain0[5][100], temp_gain1[5][2], temp_offset0[5][100], temp_offset1[5][2];
	Double_t gain_X[5][60];
	Double_t gain_Y[5][40];
	Double_t offset_X[5][60];
	Double_t offset_Y[5][40];

	ifstream cal0;
	cal0.open ("WASABI_gain_final.dat");
	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t ich = 0; ich < 100; ich++)
		{
			cal0 >> numdssd >> ich >> temp_gain0[idssd][ich] >> temp_offset0[idssd][ich];
			cout << idssd << " " << ich << " " << temp_gain0[idssd][ich] << " " << temp_offset0[idssd][ich] << endl;
		}
	}
	cal0.close();


	ifstream cal1;
	cal1.open ("WASABI_gain_modi.dat");
	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t ich = 0; ich < 2; ich++)
		{
			cal1 >> numdssd >> ich >> temp_offset1[idssd][ich];
			cout << temp_offset1[idssd][ich] << endl;
		}
	}
	cal1.close();

	ofstream calout;
	calout.open ("../WASABI_gain.dat");

	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t ich = 0; ich < 100; ich++)
		{

			if (ich < 60)
			{
				gain_X[idssd][ich] = temp_gain0[idssd][ich];
				offset_X[idssd][ich] = temp_offset0[idssd][ich] + temp_offset1[idssd][0];
				calout << idssd << "	" << ich << "	" << gain_X[idssd][ich] << "	" << offset_X[idssd][ich] << endl;
				cout << "X" << " " << idssd << " " << ich << " " << gain_X[idssd][ich] << " " << offset_X[idssd][ich] << endl;
			}
			else
			{
				gain_Y[idssd][ich-60] = temp_gain0[idssd][ich];
				offset_Y[idssd][ich-60] = temp_offset0[idssd][ich] + temp_offset1[idssd][1];
				calout << idssd << "	" << ich << "	" << gain_Y[idssd][ich-60] << "	" << offset_Y[idssd][ich-60] << endl;
				cout << "Y" << " " << idssd << " " << ich << " " << gain_Y[idssd][ich-60] << " " << offset_Y[idssd][ich-60] << endl;
			}
		}
	}

	for (Int_t ich = 0; ich < 40; ich++)
	{
		gain_Y[4][ich] = 1;
		offset_Y[4][ich] = 0;
	}

	TH1D* histX[5];
	TH1D* histY[5];
	for (Int_t i = 0; i < 5; i++)
	{
		histX[i] = new TH1D(Form("dssd_x%d", i+1), "", 1000, 0,2000);
		histY[i] = new TH1D(Form("dssd_y%d", i+1), "", 1000, 0,2000);
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
							sienergy = beta_E_X[isi][ich]*gain_X[isi][ich] + offset_X[isi][ich];
							histX[isi] -> Fill(sienergy+ge_E[i]);
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
							sienergy = beta_E_Y[isi][ich]*gain_Y[isi][ich] + offset_Y[isi][ich];
							histY[isi] -> Fill(sienergy+ge_E[i]);
						}
						else continue;
					}
				}

			}
		}
	}

	TFile* out = new TFile("SiEcal_calib_hist_final_2.root", "recreate");
	out -> cd();
	for (Int_t i = 0; i < 5; i++)
	{
		histX[i] -> Write();
		histY[i] -> Write();
	}

	cout << "corrhist has been saved." << endl;
	out -> Close();
	cout << "All work has been finished." << endl;
}
