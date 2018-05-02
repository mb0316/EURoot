void WASABI_2()
{
	TFile* file = new TFile("SiEcal_hist.root", "read");
	TH2D* hist;

	TCanvas* cvs = new TCanvas("c1", "", 800, 400);

	TF1* ftn1 = new TF1("ftn1", "[0]*x + 1173", 0, 1400);
	TF1* ftn2 = new TF1("ftn2", "[0]*x + 1332", 0, 1400);

	Double_t gain_X[5][60];
	Double_t gain_Y[5][60];

	Double_t offset_X[5][60];
	Double_t offset_Y[5][40];
	
	Double_t data_X[5][60][2];
	Double_t data_Y[5][40][2];

	TGraph* graph = new TGraph();
	TF1* ftn3 = new TF1("ftn3", "[0]*x + [1]", 0, 1400);

	ofstream wasabi_gain;
	wasabi_gain.open ("../WASABI_gain.dat");

	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t j = 0; j < 60; j++)
		{
			hist = (TH2D*) file->Get(Form("dssd_x%d_ch%d", i+1, j+1));
			hist->Draw("colz");
			ftn1->SetParameter(0, -0.9);
			ftn1->SetParameter(1, 1173.0);
			ftn1->SetParLimits(1, 1170.0, 1176.0);
			if (i == 3)
			{
				if (j == 1 || (j >= 14 && j <= 29) || (j >= 32 && j <= 45) || j == 49)
				{
					cout << "low gain" << endl;
					ftn1->SetParLimits(0, -3.0, -0.5);
					hist->Fit(ftn1, "MQ", "", 200, 350);
				}
				else
				{
					cout << "normal gain" << endl;
					ftn1->SetParLimits(0, -1.1, -0.5);
					hist->Fit(ftn1, "MQ", "", 450, 750);
				}
			}
			else
			{
				ftn1->SetParLimits(0, -1.1, -0.5);
				hist->Fit(ftn1, "MQ", "", 450, 750);
			}

//			gain_X[i][j] = ftn1->GetParameter(0);
			

//			cout << "WASABI #" << i+1 << " X strip #" << j+1 << " : " << gain_X[i][j] << endl;
//			wasabi_gain << 0 << "	" << i << "	" << j << "	" << gain_X[i][j] << endl;

			ftn2->SetParameter(0, ftn1->GetParameter(0));
//			cvs->cd();
//			ftn1->Draw("same");
//			ftn2->Draw("same");
//			cvs->Update();
//			cvs->Modified();
			data_X[i][j][0] = abs(1173/ftn1->GetParameter(0));
			data_X[i][j][1] = abs(1332/ftn1->GetParameter(0));
		}
	}

	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t j = 0; j < 40; j++)
		{
			hist = (TH2D*) file->Get(Form("dssd_y%d_ch%d", i+1, j+1));
			hist->Draw("colz");
			if (i == 2)
			{
				if (j >= 5 && j <= 12)
				{
					cout << "low gain" << endl;
					ftn1->SetParameter(0, -2.0);
					ftn1->SetParLimits(0, -3.0, -1.8);
					hist->Fit(ftn1, "MQ", "", 200, 350);
				}
				else
				{
					ftn1->SetParameter(0, -0.9);
					cout << "normal gain" << endl;
					ftn1->SetParLimits(0, -1.1, -0.5);
					hist->Fit(ftn1, "MQ", "", 450, 750);
				}
			}
			else if (i == 3)
			{
				if (j >= 16 && j <= 39)
				{
					cout << "low gain" << endl;
					ftn1->SetParameter(0, -2.0);
					ftn1->SetParLimits(0, -3.0, -1.8);
					hist->Fit(ftn1, "MQ", "", 200, 350);
				}
				else
				{
					ftn1->SetParameter(0, -0.9);
					cout << "normal gain" << endl;
					ftn1->SetParLimits(0, -1.1, -0.5);
					hist->Fit(ftn1, "MQ", "", 450, 750);
				}
			}

			else if (i==4)
			{
				ftn1->SetParameter(0, -0.5);
				ftn1->SetParLimits(0, -0.65, -0.4);
				hist->Fit(ftn1, "MQ", "", 800, 1100);
			}
			else
			{
				ftn1->SetParameter(0, -0.9);
				ftn1->SetParLimits(0, -1.1, -0.5);
				hist->Fit(ftn1, "MQ", "", 450, 750);
			}

//			gain_Y[i][j] = ftn1->GetParameter(0);

//			cout << "WASABI #" << i+1 << " Y strip #" << j+1 << " : " << gain_Y[i][j] << endl;
//			wasabi_gain << 1 << "	" << i << "	" << j << "	" << gain_Y[i][j] << endl;

			ftn2->SetParameter(0, ftn1->GetParameter(0));
//			cvs->cd();
//			ftn1->Draw("same");
//			ftn2->Draw("same");
//			cvs->Update();
//			cvs->Modified();
			data_Y[i][j][0] = abs(1173/ftn1->GetParameter(0));
			data_Y[i][j][1] = abs(1332/ftn1->GetParameter(0));

		}
	}

	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t j = 0;j < 60; j++)
		{
			graph->SetPoint(0, data_X[i][j][0], 1173);
			graph->SetPoint(1, data_X[i][j][1], 1332);

			graph->Draw();
			graph->Fit(ftn3, "MQ");
			cvs->Update();
			cvs->Modified();
			gain_X[i][j] = ftn3->GetParameter(0);
			offset_X[i][j] = ftn3->GetParameter(1);
			cout << "WASABI #" << i+1 << " dssd X ch#" << j+1 << " gain : " << gain_X[i][j] << endl;	
			cout << "WASABI #" << i+1 << " dssd X ch#" << j+1 << " offset : " << offset_X[i][j] << endl;	
			wasabi_gain << 0 << "	" << i << "	" << j << "	" << gain_X[i][j] << "	" << offset_X[i][j] << endl;
		}

		for (Int_t j = 0; j < 40; j++)
		{
			graph->SetPoint(0, data_Y[i][j][0], 1173);
			graph->SetPoint(1, data_Y[i][j][1], 1332);

			graph->Draw();
			graph->Fit(ftn3, "MQ");
			cvs->Update();
			cvs->Modified();
			gain_Y[i][j] = ftn3->GetParameter(0);
			offset_Y[i][j] = ftn3->GetParameter(1);
			cout << "WASABI #" << i+1 << " dssd Y ch#" << j+1 << " gain : " << gain_Y[i][j] << endl;	
			cout << "WASABI #" << i+1 << " dssd Y ch#" << j+1 << " offset : " << offset_Y[i][j] << endl;	
			wasabi_gain << 1 << "	" << i << "	" << j << "	" << gain_Y[i][j] << "	" << offset_Y[i][j] << endl;
		}
	}

}
