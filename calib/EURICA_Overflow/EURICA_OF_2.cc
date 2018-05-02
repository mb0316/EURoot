void EURICA_OF_2()
{
	TFile* file = new TFile("EURICA_E.root", "read");
	TH2D* hist_2 = (TH2D*) file->Get("Energy_ch");

	TH1D* hist[84];
	for (Int_t i = 0; i < 84; i++)
	{
		hist[i] = hist_2->ProjectionY(Form("hist%d", i), i+1, i+1);
	}

	TCanvas* cvs = new TCanvas("cvs", "", 800,400);
	cvs->SetLogy();

	Int_t maxbin, cutbin;
	ofstream outfile("../eurica_overflow.dat");

	for (Int_t i = 0; i < 84; i++)
	{
		cvs->cd();
		hist[i] -> Draw();
		if (i == 13) hist[i] -> GetXaxis() -> SetRangeUser(4500, 5500);
		else if (i == 54) hist[i] -> GetXaxis() -> SetRangeUser(3500, 4500);
		else if (i == 65) hist[i] -> GetXaxis() -> SetRangeUser(4000, 5000);
		else hist[i] -> GetXaxis() -> SetRangeUser(5500, 8000);
		maxbin = hist[i] -> GetMaximumBin();
		cout << i+1 << " channel overflow : " << maxbin << endl;
		cutbin = maxbin - 500;
		outfile << i << "	" << cutbin << endl;
		cvs->Update();
		cvs->Modified();
//		usleep(5E5);
	}
/*
	TCanvas* cvs2 = new TCanvas("cvs2", "", 800, 400);
	TCanvas* cvs3 = new TCanvas("cvs3", "", 800, 400);
	cvs2->SetLogy();
	cvs3->SetLogy();

	cvs->cd();
	hist[54] -> Draw();
	cvs2->cd();
	hist[65] -> Draw();
	cvs3->cd();
	hist[13] -> Draw();
*/
}
