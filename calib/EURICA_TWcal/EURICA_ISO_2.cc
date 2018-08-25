void EURICA_ISO_2()
{
	TFile* file = new TFile("TWhist_ISO.root", "read");
	TH2D* hist;
	TH1D* pro;

	TGraphErrors* graph = new TGraphErrors();

	TF1* gaus = new TF1("gaus", "gaus(0)", -3000,0);
	TF1* ftn = new TF1("twcorr", "[0]+[1]*TMath::Power(x, -[2])", 20, 2000);
	TCanvas* cvs1 = new TCanvas("cvs1", "", 800,400);
	TCanvas* cvs2 = new TCanvas("cvs2", "", 800,400);

	Double_t mean, max, start, end;

	ofstream calib;
	calib.open("gcT_iso_TW.dat");

	for (Int_t ich = 0; ich < 84; ich++)
	{
		hist = (TH2D*) file->Get(Form("hist%d", ich));
		for (Int_t i = 0; i < 50; i++)
		{
			start = i*20;
			end = 20+i*20;
			pro = hist->ProjectionY("pro", start, end, "");
			max = pro->GetMaximum();
			mean = pro->GetBinCenter(pro->GetMaximumBin());
			gaus->SetParameter(0, max);
			gaus->SetParameter(1, mean);
			gaus->SetParameter(2, 100);

			pro->Fit(gaus, "MQ", "", mean - 500, mean + 500);
			mean = gaus->GetParameter(1);
			graph->SetPoint(i, (start+end), mean);
			graph->SetPointError(i, 20, gaus->GetParameter(2));
		}

		ftn->SetParameter(0, 23000);
		ftn->SetParameter(1, -10000);
		ftn->SetParameter(2, 1.0);
		ftn->SetParLimits(0, 21500, 25000);
		ftn->SetParLimits(2, 0.2, 1.5);
		graph->Fit(ftn, "MQ0", "", 50, 2000);
		cvs1->cd();
		hist->Draw("colz");
		ftn->Draw("same");
		cvs1->Update();
		cvs1->Modified();

		cvs2->cd();
		graph->Draw();
		ftn->Draw("same");
		cvs2->Update();
		cvs2->Modified();
		calib << ich << "    " << ftn->GetParameter(0) << "  " << ftn->GetParameter(1) << "  " << ftn->GetParameter(2) << endl;
		cout << ich << " " << ftn->GetParameter(0) << " " << ftn->GetParameter(1) << " " << ftn->GetParameter(2) << endl;
	}
}
