void WASABI_2()
{
	TFile* file = new TFile("SiEcal_beam.root", "read");

	TF1* ftn = new TF1("ftn", "[0]*x+[1]", 0, 2000);
	TF1* ftn_gaus = new TF1("gaus", "gaus(0)", 0, 2000);
	TH2D* hist;
	TH1D* pro;
	TGraph* graph;
	TCanvas* cvs = new TCanvas("cvs", "", 800, 400);
	cvs->SetLogz();
	TCanvas* cvs2 = new TCanvas("cvs2", "", 800, 400);
	Double_t max, mean, stdv, start, end;

	ofstream calib2;
	calib2.open ("WASABI_gain_beam.dat");

	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		if (idssd == 1)	continue;
		else if (idssd == 4)
		{
			for (Int_t ich = 0; ich < 40; ich++)
			{
				hist = (TH2D*) file->Get(Form("hist_y%d_ch%d", idssd, ich));
				graph = new TGraph();
				for (Int_t i = 70; i < 140; i++)
				{
					start = i*10;
					end = i*10+10;
					pro = hist->ProjectionY("proX", i, i+1, "");
					max = pro->GetMaximum();
					mean = pro->GetBinCenter(pro->GetMaximumBin());
					stdv = pro->GetStdDev();
					ftn_gaus->SetParameters(max, mean, stdv);
					pro->Fit(ftn_gaus, "MQ", "", mean - 30, mean + 30);
					graph->SetPoint(i-20, (start+end)/2, ftn_gaus->GetParameter(1));
				}
				ftn->SetParameter(0, 1.0);
				ftn->SetParameter(1, 0);
				cvs2->cd();
				graph->Draw();
				graph->Fit(ftn, "M0", "", 800, 1100);
				ftn->Draw("same");
				cvs2->Update();
				cvs2->Modified();

				cvs->cd();
				hist->Draw("colz");
				ftn->Draw("same");
				ftn->SetLineStyle(2);
				cout << idssd << " " << ich << " " << ftn->GetParameter(0) << " " << ftn->GetParameter(1) << endl;
				calib2 << idssd << "	" << ich << "	" << ftn->GetParameter(0) << "	" << ftn->GetParameter(1) << endl;

				cvs->Update();
				cvs->Modified();
				delete graph;
			}
		}

		else
		{
			for (Int_t ich = 0; ich < 40; ich++)
			{
				hist = (TH2D*) file->Get(Form("hist_y%d_ch%d", idssd, ich));
				graph = new TGraph();
				for (Int_t i = 20; i < 60; i++)
				{
					start = i*10;
					end = i*10+10;
					pro = hist->ProjectionY("proX", i, i+1, "");
					max = pro->GetMaximum();
					mean = pro->GetBinCenter(pro->GetMaximumBin());
					stdv = pro->GetStdDev();
					ftn_gaus->SetParameters(max, mean, stdv);
					pro->Fit(ftn_gaus, "MQ", "", mean - 30, mean + 30);
					graph->SetPoint(i-20, (start+end)/2, ftn_gaus->GetParameter(1));
				}
				ftn->SetParameter(0, 1.0);
				ftn->SetParameter(1, 0);
				cvs2->cd();
				graph->Draw();
				if (idssd == 3)	graph->Fit(ftn, "M0", "", 300, 600);
				else if (idssd == 2 && ich == 39)	graph->Fit(ftn, "M0", "", 300, 500);
				else	graph->Fit(ftn, "M0", "", 200, 600);
				ftn->Draw("same");
				cvs2->Update();
				cvs2->Modified();


				cvs->cd();
				hist->Draw("colz");
				ftn->Draw("same");
				ftn->SetLineStyle(2);
				cout << idssd << " " << ich << " " << ftn->GetParameter(0) << " " << ftn->GetParameter(1) << endl;
				calib2 << idssd << "	" << ich << "	" << ftn->GetParameter(0) << "	" << ftn->GetParameter(1) << endl;

				cvs->Update();
				cvs->Modified();
				delete graph;
//				sleep(1);
			}
		}

	}
	calib2.close();

	ofstream calib1;
	calib1.open ("WASABI_gain_beam_dssd1.dat");

	for (Int_t ich = 0; ich < 60; ich++)
	{
		hist = (TH2D*) file->Get(Form("hist_x1_ch%d", ich));
		graph = new TGraph();
		if (ich == 22 || ich == 27 || ich == 28)
		{
			for (Int_t i = 76; i < 120; i++)
			{
				start = i*10;
				end = i*10+10;
				pro = hist->ProjectionY("proX", i, i+1, "");
				max = pro->GetMaximum();
				mean = pro->GetBinCenter(pro->GetMaximumBin());
				stdv = pro->GetStdDev();
				ftn_gaus->SetParameters(max, mean, stdv);
				pro->Fit(ftn_gaus, "MQ", "", mean - 50, mean + 50);
				graph->SetPoint(i-76, (start+end)/2, ftn_gaus->GetParameter(1));
			}
			ftn->SetParameter(0, 1.0);
			ftn->SetParameter(1, 0);
			cvs2->cd();
			graph->Draw();
			graph->Fit(ftn, "M0", "", 750, 1200);
			cvs2->Modified();
		}
		else
		{
			for (Int_t i = 20; i < 50; i++)
			{
				start = i*10;
				end = i*10+10;
				pro = hist->ProjectionY("proX", i, i+1, "");
				max = pro->GetMaximum();
				mean = pro->GetBinCenter(pro->GetMaximumBin());
				stdv = pro->GetStdDev();
				ftn_gaus->SetParameters(max, mean, stdv);
				pro->Fit(ftn_gaus, "MQ", "", mean - 40, mean + 50);
				graph->SetPoint(i-20, (start+end)/2, ftn_gaus->GetParameter(1));
			}
			ftn->SetParameter(0, 1.0);
			ftn->SetParameter(1, 0);
			cvs2->cd();
			graph->Draw();
			if (ich == 30)	graph->Fit(ftn, "M0", "", 300, 500);
			else	graph->Fit(ftn, "M0", "", 200, 500);
			ftn->Draw("same");
			cvs2->Update();
			cvs2->Modified();
		}
		cvs->cd();
		hist->Draw("colz");
		ftn->Draw("same");
		ftn->SetLineStyle(2);
		cout << ich << " " << ftn->GetParameter(0) << " " << ftn->GetParameter(1) << endl;
		calib1 << ich << "	" << ftn->GetParameter(0) << "	" << ftn->GetParameter(1) << endl;

		cvs->Update();
		cvs->Modified();
		delete graph;
	}
	calib1.close();

}
