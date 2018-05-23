void WASABI_4()
{
	TFile* file = new TFile("WASABI_T_hist_1.root", "read");
	TH1D* hist_X[5][60];
	TH1D* hist_Y[5][40];

	TCanvas* cvs = new TCanvas("cvs", "", 700, 400);

	TF1* ftn = new TF1("ftn", "gaus(0)", -5000, 5000);

	Int_t max;
	Double_t mean;

	Int_t temp_dssd, temp_ch;
	Double_t temp_mean;

	ifstream inputfile;
	inputfile.open ("temp_tzero.dat");

	ofstream datafile;
	datafile.open ("tzero.dat");

	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t ix = 0; ix < 60; ix++)
		{
			hist_X[idssd][ix] = (TH1D*) file->Get(Form("hist_X_%d_%d", idssd, ix));
			hist_X[idssd][ix]->GetXaxis()->SetRangeUser(-500, 500);
			cvs->cd();
			hist_X[idssd][ix] ->Draw();
			max = hist_X[idssd][ix]->GetMaximum();
			mean = 0;
			ftn->SetParameter(0, max);
			ftn->SetParameter(1, mean);
/*
			if (idssd == 0 && idssd == 1)   hist_X[idssd][ix]->Fit(ftn, "MQ", "", mean-80, mean+80);
			else if (idssd == 4)	hist_X[idssd][ix]->Fit(ftn, "MQ", "", mean-30, mean+20);
			else    hist_X[idssd][ix]->Fit(ftn, "MQ", "", mean-100, mean+30);
*/
			hist_X[idssd][ix]->Fit(ftn, "MQ", "", mean-100, mean+50);

			gSystem->ProcessEvents();
			cvs->Update();
			cvs->Modified();

			mean = ftn->GetParameter(1);

			inputfile >> temp_dssd >> temp_ch >> temp_mean;
			mean = mean+temp_mean;

			datafile << idssd << "	" << ix << "	" << mean << endl;	
		}
		for (Int_t iy = 0; iy < 40; iy++)
		{
			hist_Y[idssd][iy] = (TH1D*) file->Get(Form("hist_Y_%d_%d", idssd, iy));
			hist_Y[idssd][iy]->GetXaxis()->SetRangeUser(-500,500);
			cvs->cd();
			hist_Y[idssd][iy] ->Draw();
			max = hist_Y[idssd][iy]->GetMaximum();
			mean = 0;
			ftn->SetParameter(0, max);
			ftn->SetParameter(1, mean);
/*
			if (idssd == 0 && idssd == 1)   hist_Y[idssd][iy]->Fit(ftn, "MQ", "", mean-80, mean+80);
			else if (idssd == 4)   hist_Y[idssd][iy]->Fit(ftn, "MQ", "", mean-30, mean+20);
			else    hist_Y[idssd][iy]->Fit(ftn, "MQ", "", mean-100, mean+30);
*/
			if (idssd == 4) hist_Y[idssd][iy]->Fit(ftn, "MQ", "", -50, 10);
			else hist_Y[idssd][iy]->Fit(ftn, "MQ", "", mean-100, mean+50);

			gSystem->ProcessEvents();
			cvs->Update();
			cvs->Modified();
	
			mean = ftn->GetParameter(1);

			inputfile >> temp_dssd >> temp_ch >> temp_mean;
			mean = mean+temp_mean;

			datafile << idssd << "	" << iy+60 << "	" << mean << endl;	
		}


	}
}
