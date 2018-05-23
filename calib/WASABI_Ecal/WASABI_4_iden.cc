void WASABI_4_iden(Int_t idssd, Int_t ich, Double_t lrange1, Double_t urange1, Double_t lrange2, Double_t urange2)
{
	TFile* file = new TFile("SiEcal_calib_hist.root", "READ");
	TH1D* hist;

	TF1* ftn1 = new TF1("ftn1", "gaus(0)", 0, 1500);
	TF1* ftn2 = new TF1("ftn2", "gaus(0)", 0, 1500);

	TCanvas* cvs = new TCanvas("cvs", "", 1200, 500);
	TCanvas* cvs1 = new TCanvas("cvs1", "", 800, 500);

	Double_t max, mean;

	TGraph* graph = new TGraph();
	TF1* ftn3 = new TF1("ftn3", "[0]*x+[1]", 1000, 1500);
	Double_t ngain[5][100];
	Double_t noffset[5][100];


	if (ich < 60)	hist = (TH1D*) file->Get(Form("dssd_x%d_ch%d", idssd+1, ich+1));
	else	hist = (TH1D*) file->Get(Form("dssd_y%d_ch%d", idssd+1, ich-60+1));

	hist->GetXaxis()->SetRangeUser(1050, 1250);
	max = hist->GetMaximum();
	mean = hist->GetBinCenter(hist->GetMaximumBin());
	cout << max << " " << mean << endl;
	hist->Fit(ftn1, "M", "", mean-lrange1, mean+urange1);


	hist->GetXaxis()->SetRangeUser(1250, 1450);
	max = hist->GetMaximum();
	mean = hist->GetBinCenter(hist->GetMaximumBin());
	cout << max << " " << mean << endl;
	hist->Fit(ftn2, "M", "", mean-lrange2, mean+urange2);

	cvs->cd();
	hist->Draw();
	ftn1->Draw("same");
	ftn2->Draw("same");
	hist->GetXaxis()->SetRangeUser(1000,1500);

	graph->SetPoint(0, ftn1->GetParameter(1), 1173.2);
	graph->SetPoint(1, ftn2->GetParameter(1), 1332.5);

	ftn3->SetParameters(1.0, 1173.2-ftn1->GetParameter(1));
	graph->Fit(ftn3, "MQ");
	cvs1->cd();
	graph->Draw();
	cout << idssd << " " << ich << " " << ftn3->GetParameter(0) << " " << ftn3->GetParameter(1) << endl;

	ofstream calib;
	calib.open (Form("WASABI_gain/WASABI_gain_spec_%d_%d.dat", idssd, ich));
	calib << ftn3->GetParameter(0) << "	" << ftn3->GetParameter(1) << "	" << ftn1->GetParameter(2) <<endl;
}
