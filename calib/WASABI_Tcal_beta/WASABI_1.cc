using namespace std;

void WASABI_1()
{
	TFile* file = new TFile("../../data/WASABI_Calib/w3.root", "read");
//	TFile* file = new TFile("../../data/w3_data_1060.root", "read");
	TTree* tree;
	tree = (TTree*) file->Get("w3");

	Int_t w3tx[5][60], w3ty[5][40];
//	Int_t w3tx[5][60][3], w3ty[5][40][3];
	Int_t w3_ex[5][60], w3_ey[5][40];
	Int_t f11L, betaPL2L, betaPL2R;

	tree->SetBranchAddress("w3tx", w3tx);
	tree->SetBranchAddress("w3ty", w3ty);
	tree->SetBranchAddress("w3_ex", w3_ex);
	tree->SetBranchAddress("w3_ey", w3_ey);
	tree->SetBranchAddress("f11L", &f11L);

	Long64_t nEnt = tree->GetEntries();
	cout << nEnt << " entries." << endl;

	TH1D* hist_X[5][60];
	TH1D* hist_Y[5][40];
	TH2D* hist_Y2[5][40];
	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t ix = 0; ix < 60; ix++)	hist_X[i][ix] = new TH1D(Form("hist_X_%d_%d",i,ix), "", 10000, -5000, 5000);
		for (Int_t iy = 0; iy < 40; iy++)
		{
			hist_Y[i][iy] = new TH1D(Form("hist_Y_%d_%d",i,iy), "", 500, -5000, 5000);
			hist_Y2[i][iy] = new TH2D(Form("hist_Y_2d_%d_%d",i,iy), "", 500,0,2000,500, -5000, 5000);
		}
	}

	for (Long64_t ient = 0; ient < nEnt; ient++)
	{
		if (ient%1000 == 0)
		{
			printf("%lld entry done.", ient);
			fflush(stdout);
			printf("\r");
		}
		tree->GetEntry(ient);
		if (f11L > 50000)
		{
			for (Int_t idssd = 0; idssd < 5; idssd++)
			{
				for (Int_t ix = 0; ix < 60; ix++)	hist_X[idssd][ix]->Fill(w3tx[idssd][ix]);
				for (Int_t iy = 0; iy < 40; iy++)
				{
					hist_Y[idssd][iy]->Fill(w3ty[idssd][iy]);
					hist_Y2[idssd][iy]->Fill(w3_ey[idssd][iy], w3ty[idssd][iy]);
				}
			}
		}
	}

	TFile* out = new TFile("WASABI_T_beta_hist.root", "recreate");
	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t ix = 0; ix < 60; ix++)	hist_X[i][ix]->Write();
		for (Int_t iy = 0; iy < 40; iy++)
		{
			hist_Y[i][iy]->Write();
			hist_Y2[i][iy]->Write();
		}
	}
	out->Close();
}
