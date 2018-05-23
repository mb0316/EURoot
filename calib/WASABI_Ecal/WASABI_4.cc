void WASABI_4()
{
	TFile* file = new TFile("SiEcal_calib_hist.root", "READ");
	TH1D* hist;

	TF1* ftn1 = new TF1("ftn1", "gaus(0)", 0, 1500);
	TF1* ftn2 = new TF1("ftn2", "gaus(0)", 0, 1500);
	
	TCanvas* cvs = new TCanvas("cvs", "", 800, 500);

	Double_t max, mean;

	TGraph* graph = new TGraph();
	TF1* ftn3 = new TF1("ftn3", "[0]*x+[1]", 1000, 1500);
	Double_t ngain[5][100];
	Double_t noffset[5][100];

	ofstream ncalib;
	ncalib.open ("WASABI_gain_recal.dat");

	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t ich = 0; ich < 100; ich++)
		{
			if (ich < 60)	hist = (TH1D*) file->Get(Form("dssd_x%d_ch%d", idssd+1, ich+1));
			else	hist = (TH1D*) file->Get(Form("dssd_y%d_ch%d", idssd+1, ich-60+1));

			hist->GetXaxis()->SetRangeUser(1050, 1250);
			max = hist->GetMaximum();
			mean = hist->GetBinCenter(hist->GetMaximumBin());
			if (idssd == 0)
			{	
				if (ich < 60)	hist->Fit(ftn1, "MQ", "", mean-15, mean+20);
				if (ich >= 60)	hist->Fit(ftn1, "MQ", "", mean-15, mean+25);
			}
			else
			{	
				if (ich < 60)	hist->Fit(ftn1, "MQ", "", mean-15, mean+25);
				if (ich >= 60)	hist->Fit(ftn1, "MQ", "", mean-30, mean+40);
			}

			mean = ftn1->GetParameter(1);

			cvs->cd();
			hist->Draw();
			cvs->Update();
			cvs->Modified();

			hist->GetXaxis()->SetRangeUser(1250, 1450);
			max = hist->GetMaximum();
			mean = hist->GetBinCenter(hist->GetMaximumBin());
			if (idssd == 0)
			{	
				if (ich < 60)	hist->Fit(ftn2, "MQ", "", mean-15, mean+20);
				if (ich >= 60)	hist->Fit(ftn2, "MQ", "", mean-15, mean+25);
			}
			else
			{	
				if (ich < 60)	hist->Fit(ftn2, "MQ", "", mean-15, mean+25);
				if (ich >= 60)	hist->Fit(ftn2, "MQ", "", mean-30, mean+40);
			}

			mean = ftn2->GetParameter(1);

			cvs->cd();
			hist->Draw();
			cvs->Update();
			cvs->Modified();

			graph->SetPoint(0, ftn1->GetParameter(1), 1173);
			graph->SetPoint(1, ftn2->GetParameter(1), 1332);
		
			ftn3->SetParameters(1.0, 1173-ftn1->GetParameter(1));
			graph->Fit(ftn3, "MQ");
			cout << idssd << " " << ich << " " << ftn3->GetParameter(0) << " " << ftn3->GetParameter(1) << endl;
			ngain[idssd][ich] = ftn3->GetParameter(0);
			noffset[idssd][ich] = ftn3->GetParameter(1);
			ncalib << idssd << "	" << ich << "	" << ngain[idssd][ich] << "	" << noffset[idssd][ich] << endl;;
		}
	}
}
