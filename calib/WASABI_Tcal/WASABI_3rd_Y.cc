#include "wasabi.h"

using namespace std;

void WASABI_3rd_Y()
{
	TFile* file = new TFile("../../data/WASABI_Calib/w3.root", "read");
	TTree* tree;
	tree = (TTree*) file->Get("w3");

	Int_t w3tx[5][60], w3ty[5][40];
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

	TH2D* hist_Y[40];

	for (Int_t iy = 0; iy < 40; iy++)	hist_Y[iy] = new TH2D(Form("hist_Y%d",iy), "", 1000,-1000,5000,1000, -3000, 5000);


	ifstream datafile;
	datafile.open ("../tzero.dat");

	Double_t tz_x[5][60], tz_y[5][40];

	Int_t temp_dssd, temp_ch;

	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t ix = 0; ix < 60; ix++)
		{
			datafile >> temp_dssd >> temp_ch >> tz_x[idssd][ix];
//			cout << idssd << " " << temp_dssd << " " << ix << " " << temp_ch << " " << tz_x[idssd][ix] << endl;
		}
		for (Int_t iy = 0; iy < 40; iy++)
		{
			datafile >> temp_dssd >> temp_ch >> tz_y[idssd][iy];
//			cout << idssd << " " << temp_dssd << " " << iy << " " << temp_ch << " " << tz_y[idssd][iy] << endl;
		}
	}
	

	for (Long64_t ient = 0; ient < nEnt; ient++)
	{
		tree->GetEntry(ient);
                if (ient%1000 == 0)
                {
                        printf("%lld entry done.", ient);
                        fflush(stdout);
                        printf("\r");
                }

		if (f11L < 50000)
		{
			for (Int_t i = 0; i < 40; i++)
			{
				w3ty[1][i] = w3ty[1][i] - tz_y[1][i];
				hist_Y[i] -> Fill(w3ty[1][i],w3ty[2][i]);
			}
		}
	}

	TFile* out = new TFile("WASABI_T_hist_3rd_Y.root", "recreate");
	for (Int_t iy = 0; iy < 40; iy++)	hist_Y[iy]->Write();
	out->Close();

}
