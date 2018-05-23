void WASABI_6()
{
	TFile* file = new TFile("SiEcal_calib_hist_final.root", "READ");
	TH1D* hist;

	TF1* ftn1 = new TF1("ftn1", "gaus(0)", 0, 1500);
	
	TCanvas* cvs = new TCanvas("cvs", "", 800, 500);

	Double_t max, mean;

	ofstream ncalib;
	ncalib.open ("WASABI_gain_modi.dat");

	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t i = 0; i < 2; i++)
		{
			if (i == 0)	hist = (TH1D*) file->Get(Form("dssd_x%d", idssd+1));
			else	hist = (TH1D*) file->Get(Form("dssd_y%d", idssd+1));

			hist->GetXaxis()->SetRangeUser(1050, 1250);
			max = hist->GetMaximum();
			mean = hist->GetBinCenter(hist->GetMaximumBin());
			if (i == 0 || (idssd == 0 && i == 1))	hist->Fit(ftn1, "MQ", "", mean-10, mean+15);
			else if (idssd == 1 && i == 1)	hist->Fit(ftn1, "MQ", "", mean-20, mean+40);
			else	hist->Fit(ftn1, "MQ", "", mean-25, mean+30);

			mean = ftn1->GetParameter(1);

			cvs->cd();
			hist->Draw();
			cvs->Update();
			cvs->Modified();
			sleep(1);

			cout << idssd << " " << i << " " << mean << " " << 1173.2-mean << " " << ftn1->GetParameter(2) << endl;
			ncalib << idssd << "	" << i << "	" << 1173.2-mean << endl;
		}
	}
}
