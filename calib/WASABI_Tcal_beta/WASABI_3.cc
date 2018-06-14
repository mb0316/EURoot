void WASABI_3()
{
	TFile* file = new TFile("WASABI_T_beta_hist.root", "read");
	TH2D* hist;
	TH1D* pro;
	TGraphErrors* graph = new TGraphErrors();
	TF1* gaus = new TF1("gaus", "gaus(0)", -3000,0);
	TF1* ftn = new TF1("twcorr", "[0]+[1]*TMath::Power(x, -[2])", 100, 2000);
	TCanvas* cvs1 = new TCanvas("cvs1", "", 800,400);
	TCanvas* cvs2 = new TCanvas("cvs2", "", 800,400);

	Double_t mean, max, start, end;

	ofstream calib;
	calib.open("tzero_beta_y.dat");

	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t iy = 0; iy < 40; iy++)
		{
			hist = (TH2D*) file->Get(Form("hist_Y_2d_%d_%d",idssd,iy));
			for (Int_t i = 9; i < 55; i++)
			{
				start = i*6;
				end = 6 + 6*i;
				pro = hist->ProjectionY("pro", start, end, "");
				max = pro->GetMaximum();
				mean = pro->GetBinCenter(pro->GetMaximumBin());
				gaus->SetParameter(0, max);
				gaus->SetParameter(1, mean);
				gaus->SetParameter(2, 100);

				pro->Fit(gaus, "MQ", "", mean - 1000, mean + 1000);
				mean = gaus->GetParameter(1);
				graph->SetPoint(i-9, (start+end)*2, mean);
				graph->SetPointError(i-9, 5, gaus->GetParameter(2));
			}

			ftn->SetParameter(0, -1500);
			ftn->SetParameter(1, 10000);
			ftn->SetParameter(2, 1.5);
			if (idssd == 1)	ftn->SetParLimits(0, -3000, -1200);
			else if (idssd == 4)	ftn->SetParLimits(0, -2000, -500);
			else	ftn->SetParLimits(0, -2500, -1200);
			if (idssd == 1)	ftn->SetParLimits(2, 0.7, 2.0);
			else if (idssd == 4)	ftn->SetParLimits(2, 0.1, 2.0);
			else	ftn->SetParLimits(2, 1.1, 1.7);

			if (idssd == 2)	graph->Fit(ftn, "M0", "", 250, 1200);
			else if (idssd == 1)	graph->Fit(ftn, "M0", "", 250, 1100);
			else if (idssd == 4)	graph->Fit(ftn, "M0", "", 420, 1200);
			else	graph->Fit(ftn, "M0", "", 220, 1200);
/*
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
*/
			calib << idssd << "	" << iy << "	" << ftn->GetParameter(0) << "	" << ftn->GetParameter(1) << "	" << ftn->GetParameter(2) << endl;
			cout << idssd << " " << iy << " " << ftn->GetParameter(0) << " " << ftn->GetParameter(1) << " " << ftn->GetParameter(2) << endl;
		}
	}


}
