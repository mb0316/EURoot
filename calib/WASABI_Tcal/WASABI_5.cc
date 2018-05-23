#include "wasabi.h"

using namespace std;

void WASABI_5()
{
	TFile* file = new TFile("../../data/WASABI_Calib/w3.root", "read");
	TTree* tree;
	tree = (TTree*) file->Get("w3");

	Int_t w3tx[5][60][3], w3ty[5][40][3];
	Int_t w3_ex[5][60], w3_ey[5][40];
	Int_t f11L, betaPL2L, betaPL2R;

	tree->SetBranchAddress("w3tx", w3tx);
	tree->SetBranchAddress("w3ty", w3ty);
	tree->SetBranchAddress("w3_ex", w3_ex);
	tree->SetBranchAddress("w3_ey", w3_ey);
	tree->SetBranchAddress("f11L", &f11L);
	tree->SetBranchAddress("betaPL2L", &betaPL2L);
	tree->SetBranchAddress("betaPL2R", &betaPL2R);

	Long64_t nEnt = tree->GetEntries();
	cout << nEnt << " entries." << endl;

	TH1D* hist_X[5][60];
	TH1D* hist_Y[5][40];

	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t ix = 0; ix < 60; ix++)	hist_X[i][ix] = new TH1D(Form("hist_X_%d_%d",i,ix), "", 1000, -5000, 5000);
		for (Int_t iy = 0; iy < 40; iy++)	hist_Y[i][iy] = new TH1D(Form("hist_Y_%d_%d",i,iy), "", 1000, -5000, 5000);
	}

	Int_t max_tempT; 
	Int_t temp_x, temp_y;
	Int_t fire_x[5] = {-1};
	Int_t fire_y[5] = {-1};

	ifstream datafile1;
	datafile1.open ("tzero.dat");
	Double_t tz_x[5][60], tz_y[5][40];

	Int_t temp_dssd, temp_ch;

	for (Int_t idssd = 0; idssd < 4; idssd++)
	{
		for (Int_t ix = 0; ix < 60; ix++)
		{
			datafile1 >> temp_dssd >> temp_ch >> tz_x[idssd][ix];
			cout << idssd << " " << temp_dssd << " " << ix << " " << temp_ch << " " << tz_x[idssd][ix] << endl;
		}
		for (Int_t iy = 0; iy < 40; iy++)
		{
			datafile1 >> temp_dssd >> temp_ch >> tz_y[idssd][iy];
			cout << idssd << " " << temp_dssd << " " << iy << " " << temp_ch << " " << tz_y[idssd][iy] << endl;
		}
	}
	

	for (Long64_t ient = 0; ient < nEnt; ient++)
	{
		tree->GetEntry(ient);
		if (f11L < 50000)
		{
			for (Int_t idssd = 0; idssd < 5; idssd++)
			{
				fire_x[idssd] = -1;
				fire_y[idssd] = -1;

				max_tempT = 150;
				for (Int_t ix = 0; ix < 60; ix++)
				{
					if (idssd < 5) w3tx[idssd][ix][0] = w3tx[idssd][ix][0] - tz_x[idssd][ix];
					if (w3_ex[idssd][ix] > 4000 && w3tx[idssd][ix][0] > -5000 && w3tx[idssd][ix][0] < max_tempT)
					{
						fire_x[idssd] = ix;
						max_tempT = w3tx[idssd][ix][0];
					}
					else continue;

				}

				max_tempT = 150;
				for (Int_t iy = 0; iy < 40; iy++)
				{
					if (idssd < 5) w3ty[idssd][iy][0] = w3ty[idssd][iy][0] - tz_y[idssd][iy];

					if (w3_ey[idssd][iy] > 4000 && w3ty[idssd][iy][0] > -5000 && w3ty[idssd][iy][0] < max_tempT)
					{
						fire_y[idssd] = iy;
						max_tempT = w3ty[idssd][iy][0];
					}
					else continue;

				}

				if (fire_x[idssd] > -1 && fire_y[idssd] > -1)
				{
					if (idssd > -1 && idssd < 2)
					{
						hist_X[idssd][fire_x[idssd]] -> Fill(w3tx[idssd][fire_x[idssd]][0]);
						hist_Y[idssd][fire_y[idssd]] -> Fill(w3ty[idssd][fire_y[idssd]][0]);
					}
					if (idssd == 2)
					{
//						if (fire_x[0] > -1 && fire_x[1] > -1 && fire_x[0] == fire_x[2] && abs(w3tx[0][fire_x[0]][0] - w3tx[2][fire_x[2]][0]) < 100) hist_X[idssd][fire_x[idssd]] -> Fill(w3tx[idssd][fire_x[idssd]][0]);
						if (fire_x[0] > -1 && fire_x[1] > -1 && fire_x[0] == fire_x[2]) hist_X[idssd][fire_x[idssd]] -> Fill(w3tx[idssd][fire_x[idssd]][0]);
//						if (fire_y[0] > -1 && fire_y[1] > -1 && fire_y[0] == fire_y[2] && abs(w3ty[0][fire_y[0]][0] - w3ty[2][fire_y[2]][0]) < 100) hist_Y[idssd][fire_y[idssd]] -> Fill(w3ty[idssd][fire_y[idssd]][0]);
						if (fire_y[0] > -1 && fire_y[1] > -1 && fire_y[0] == fire_y[2]) hist_Y[idssd][fire_y[idssd]] -> Fill(w3ty[idssd][fire_y[idssd]][0]);
					}
					if (idssd == 3)
					{
//						if (fire_x[0] > -1 && fire_x[1] > -1 && fire_x[2] > -1 && fire_x[0] == fire_x[3] && abs(w3tx[0][fire_x[0]][0] - w3tx[3][fire_x[3]][0]) < 150)   hist_X[idssd][fire_x[idssd]] -> Fill(w3tx[idssd][fire_x[idssd]][0]);
						if (fire_x[0] > -1 && fire_x[1] > -1 && fire_x[2] > -1 && fire_x[0] == fire_x[3])   hist_X[idssd][fire_x[idssd]] -> Fill(w3tx[idssd][fire_x[idssd]][0]);
//						if (fire_y[0] > -1 && fire_y[1] > -1 && fire_y[2] > -1 && fire_y[0] == fire_y[3] && abs(w3ty[0][fire_y[0]][0] - w3ty[3][fire_y[3]][0]) < 150)   hist_Y[idssd][fire_y[idssd]] -> Fill(w3ty[idssd][fire_y[idssd]][0]);
						if (fire_y[0] > -1 && fire_y[1] > -1 && fire_y[2] > -1 && fire_y[0] == fire_y[3])   hist_Y[idssd][fire_y[idssd]] -> Fill(w3ty[idssd][fire_y[idssd]][0]);
					}
					if (idssd == 4)
					{
						if (fire_x[0] > -1 && fire_x[3] > -1 && fire_x[0] == fire_x[3] && abs(w3tx[0][fire_x[0]][0] - w3tx[4][fire_x[4]][0]) < 150) hist_X[idssd][fire_x[idssd]] -> Fill(w3tx[idssd][fire_x[idssd]][0]);
						if (fire_y[0] > -1 && fire_y[3] > -1 && fire_y[0] == fire_y[3] && abs(w3ty[0][fire_y[0]][0] - w3ty[4][fire_y[4]][0]) < 150) hist_Y[idssd][fire_y[idssd]] -> Fill(w3ty[idssd][fire_y[idssd]][0]);
					}
				}
			}
		}
	}

	TFile* out = new TFile("WASABI_T_hist_2.root", "recreate");
	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t ix = 0; ix < 60; ix++)	hist_X[i][ix]->Write();
		for (Int_t iy = 0; iy < 40; iy++)	hist_Y[i][iy]->Write();
	}
	out->Close();

}
