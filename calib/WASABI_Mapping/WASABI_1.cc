void WASABI_1()
{
	TFile* file = new TFile("WASABI_map.root", "READ");
	TH1D* hist_E_X[5][60];
	TH1D* hist_T_X[5][60];
	TH1D* hist_E_Y[5][40];
	TH1D* hist_T_Y[5][40];

	TH1D* hist_ADC_X[5][60];
	TH1D* hist_TDC_X[5][60];
	TH1D* hist_ADC_Y[5][40];
	TH1D* hist_TDC_Y[5][40];


	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t ix = 0; ix < 60; ix++)
		{
			hist_E_X[i][ix] = (TH1D*) file->Get(Form("hist_E_X_%d_%d", i, ix));
			hist_T_X[i][ix] = (TH1D*) file->Get(Form("hist_T_X_%d_%d", i, ix));
			hist_ADC_X[i][ix] = (TH1D*) file->Get(Form("hist_ADC_X_%d_%d", i, ix));
			hist_TDC_X[i][ix] = (TH1D*) file->Get(Form("hist_TDC_X_%d_%d", i, ix));
		}

		for (Int_t iy = 0; iy < 40; iy++)
		{
			hist_E_Y[i][iy] = (TH1D*) file->Get(Form("hist_E_Y_%d_%d", i, iy));
			hist_T_Y[i][iy] = (TH1D*) file->Get(Form("hist_T_Y_%d_%d", i, iy));
			hist_ADC_Y[i][iy] = (TH1D*) file->Get(Form("hist_ADC_Y_%d_%d", i, iy));
			hist_TDC_Y[i][iy] = (TH1D*) file->Get(Form("hist_TDC_Y_%d_%d", i, iy));
		}
	}


	TCanvas* cvs = new TCanvas("cvs", "", 1200, 400);
	cvs->Divide(2,1);

	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t ix = 0; ix < 60; ix++)
		{
			cvs->cd(1);
			hist_E_X[idssd][ix] -> Draw();
			hist_E_X[idssd][ix] -> SetLineColor(2);
			hist_ADC_X[idssd][ix] -> Draw("same");
			hist_ADC_X[idssd][ix] ->SetLineColor(4);
			cvs->Update();
			cvs->Modified();

			cvs->cd(2);
			hist_T_X[idssd][ix] -> Draw();
			hist_T_X[idssd][ix] -> SetLineColor(2);
			hist_TDC_X[idssd][ix] -> Draw("same");
			hist_TDC_X[idssd][ix] ->SetLineColor(4);
			hist_T_X[idssd][ix]->GetXaxis()->SetRangeUser(1000, 100000);
			cvs->Update();
			cvs->Modified();
		}
		for (Int_t iy = 0; iy < 40; iy++)
		{
			cvs->cd(1);
			hist_E_Y[idssd][iy] -> Draw();
			hist_E_Y[idssd][iy] -> SetLineColor(2);
			hist_ADC_Y[idssd][iy] -> Draw("same");
			hist_ADC_Y[idssd][iy] ->SetLineColor(4);
			cvs->Update();
			cvs->Modified();

			cvs->cd(2);
			hist_T_Y[idssd][iy] -> Draw();
			hist_T_Y[idssd][iy] -> SetLineColor(2);
			hist_TDC_Y[idssd][iy] -> Draw("same");
			hist_TDC_Y[idssd][iy] ->SetLineColor(4);
			hist_T_Y[idssd][iy]->GetXaxis()->SetRangeUser(1000, 100000);
			cvs->Update();
			cvs->Modified();
		}

	}
}

