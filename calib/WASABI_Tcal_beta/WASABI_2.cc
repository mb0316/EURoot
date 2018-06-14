void WASABI_2()
{
	TFile* file = new TFile("WASABI_T_beta_hist.root","read");
	TH1D* hist;
	TF1* ftn = new TF1("ftn","gaus(0)", -5000,5000);

	Double_t max, mean;

	ofstream calib;
	calib.open("tzero_beta.dat");

	TCanvas* cvs = new TCanvas("cvs", "", 800, 400);

	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t ix = 0; ix < 60; ix++)
		{
			hist = (TH1D*) file->Get(Form("hist_X_%d_%d",idssd,ix));
			mean = hist->GetBinCenter(hist->GetMaximumBin());
/*
			cvs->cd();
			hist->Draw();
			cvs->Update();
			cvs->Modified();
*/
			cout << idssd << " " << ix << " " << mean << endl;
			calib << idssd << "	" << ix << "	" << mean << endl;
		}

		for (Int_t iy = 0; iy < 40; iy++)
		{
			hist = (TH1D*) file->Get(Form("hist_Y_%d_%d",idssd,iy));
			hist->GetXaxis()->SetRangeUser(-3000,-500);
			mean = hist->GetBinCenter(hist->GetMaximumBin());
			max = hist->GetMaximum();

			ftn->SetParameters(max, mean, 100);

			if (idssd == 0)	hist->Fit(ftn,"MQ","",mean-500,mean+200);
			else	hist->Fit(ftn,"MQ","",mean-350,mean+350);

			cvs->cd();
			hist->Draw();
			cvs->Update();
			cvs->Modified();

			mean = ftn->GetParameter(1);

			cout << idssd << " " << iy+60 << " " << mean << endl;
			calib << idssd << "	" << iy+60 << "	" << mean << endl;
		}

	}
	calib.close();

}
			
