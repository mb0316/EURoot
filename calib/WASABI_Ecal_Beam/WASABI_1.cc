void WASABI_1()
{
	TChain* tree = new TChain("tree");
	for (Int_t i = 1016; i < 1130; i++)
	{
		if (i == 1024 || i == 1027 || (i >= 1041 && i <= 1044) || i == 1049 || i == 1110 || i == 1113) continue;
		else
		{
			tree -> Add(Form("../../results/AnaWASABI/AnaWASABI%d.root",i));
			cout << i << " done." << endl;
		}
	}
	Int_t dssdhit, beta_z[100], beta_x[100], beta_y[100];
	Double_t beta_E_X[100], beta_E_Y[100], beta_T_X[100], beta_T_Y[100];

	tree->SetBranchAddress("dssdhit", &dssdhit);
	tree->SetBranchAddress("beta_z", beta_z);
	tree->SetBranchAddress("beta_x", beta_x);
	tree->SetBranchAddress("beta_y", beta_y);
	tree->SetBranchAddress("beta_E_X", beta_E_X);
	tree->SetBranchAddress("beta_E_Y", beta_E_Y);
	tree->SetBranchAddress("beta_T_X", beta_T_X);
	tree->SetBranchAddress("beta_T_Y", beta_T_Y);
	
	TH2D* histX[60];
	TH2D* histY[5][40];

	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t j = 0; j < 40; j++)	histY[i][j] = new TH2D(Form("hist_y%d_ch%d",i,j), "", 200,0,2000,200,0,2000);
		if (i == 1)
		{
			for (Int_t j = 0; j < 60; j++)
				histX[j] = new TH2D(Form("hist_x%d_ch%d", i, j), "", 200,0,2000,200,0,2000);
		}
	}


	Long64_t nEnt = tree->GetEntries();
	cout << nEnt << " entries." << endl;

	Double_t dssd_X_Tcut_L[5] = {-2950, -2960, -3000, -2950, -3050};
	Double_t dssd_X_Tcut_H[5] = {-2910, -2914, -2910, -2914, -2920};
	Double_t dssd_Y_Tcut_L[5] = {-3845.3, -3833.9, -3403.2, -3643.4, -2550.6};
	Double_t dssd_Y_Tcut_H[5] = {-1691.8, -1113.1, -1861.2, -1343, -964.6};

	for (Long64_t ient = 0; ient < nEnt; ient++)
	{
		tree->GetEntry(ient);
		if (ient%1000 == 0)
		{
			printf("%lld entry done.", ient);
			fflush(stdout);
			printf("\r");
		}
		for (Int_t ihit = 0; ihit < dssdhit; ihit++)
		{
			if (beta_x[ihit] > -1 && beta_x[ihit] < 60 && beta_y[ihit] > -1 && beta_y[ihit] < 40)
			{
				if (beta_z[ihit] == 1)
				{
 					if (beta_x[ihit] == 22 || beta_x[ihit] == 27 || beta_x[ihit] == 28)
					{
						if (beta_E_X[ihit] > 750) histX[beta_x[ihit]] -> Fill(beta_E_X[ihit], beta_E_Y[ihit]);
					}
					else
					{
						if (beta_E_X[ihit] > 120)	histX[beta_x[ihit]] -> Fill(beta_E_X[ihit], beta_E_Y[ihit]);
					}
				}
				else	histY[beta_z[ihit]][beta_y[ihit]] -> Fill(beta_E_Y[ihit], beta_E_X[ihit]);
			}
		}
	}

	TFile* out = new TFile("SiEcal_beam.root", "recreate");
	out->cd();
	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t j = 0; j < 40; j++)	histY[i][j]->Write();
	}
	for (Int_t i = 0; i < 60; i++)	histX[i]->Write();
	out->Close();
}
