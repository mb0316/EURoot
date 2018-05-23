void WASABI_2()
{
	TFile* file = new TFile("WASABI_T_hist.root", "read");
	TH1D* hist_X[5][60];
	TH1D* hist_Y[5][40];

	TCanvas* cvs = new TCanvas("cvs", "", 700, 400);

	TF1* ftn = new TF1("ftn", "gaus(0)", -5000, 5000);

	Int_t max;
	Double_t mean;

	ofstream datafile;
	datafile.open ("temp_tzero.dat");

	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t ix = 0; ix < 60; ix++)
		{
			hist_X[idssd][ix] = (TH1D*) file->Get(Form("hist_X_%d_%d", idssd, ix));
			cvs->cd();
			hist_X[idssd][ix] ->Draw();
			max = hist_X[idssd][ix]->GetMaximum();
			mean = hist_X[idssd][ix]->GetBinCenter(hist_X[idssd][ix]->GetMaximumBin());
			ftn->SetParameter(0, max);
			ftn->SetParameter(1, mean);

			if (idssd == 0 && idssd == 1)	hist_X[idssd][ix]->Fit(ftn, "M", "", mean-100, mean+40);
//			else if (idssd == 2)	hist_X[idssd][ix]->Fit(ftn, "M", "", mean-150, mean+100);
			else	hist_X[idssd][ix]->Fit(ftn, "M", "", mean-100, mean+50);

			hist_X[idssd][ix]->GetXaxis()->SetRangeUser(mean-500, mean+500);

			gSystem->ProcessEvents();
			cvs->Update();
			cvs->Modified();
			usleep(500E3);
			mean = ftn->GetParameter(1);
			datafile << idssd << "	" << ix << "	" << mean << endl;	
		}
		for (Int_t iy = 0; iy < 40; iy++)
		{
			hist_Y[idssd][iy] = (TH1D*) file->Get(Form("hist_Y_%d_%d", idssd, iy));
			cvs->cd();
			hist_Y[idssd][iy] ->Draw();
			max = hist_Y[idssd][iy]->GetMaximum();
			mean = hist_Y[idssd][iy]->GetBinCenter(hist_Y[idssd][iy]->GetMaximumBin());
			ftn->SetParameter(0, max);
			ftn->SetParameter(1, mean);

			if (idssd == 0 && idssd == 1)	hist_Y[idssd][iy]->Fit(ftn, "M", "", mean-80, mean+40);
			else if (idssd == 2)	hist_Y[idssd][iy]->Fit(ftn, "M", "", mean-150, mean+100);
			else if (idssd == 4)	hist_Y[idssd][iy]->Fit(ftn, "M", "", mean-20, mean+20);
			else	hist_Y[idssd][iy]->Fit(ftn, "M", "", mean-100, mean+50);

			hist_Y[idssd][iy]->GetXaxis()->SetRangeUser(mean-500,mean+500);

			gSystem->ProcessEvents();
			cvs->Update();
			cvs->Modified();
			usleep(500E3);
			mean = ftn->GetParameter(1);
			if (idssd == 2) mean = mean - 200;
			datafile << idssd << "	" << iy+60 << "	" << mean << endl;	
		}
	}
}
