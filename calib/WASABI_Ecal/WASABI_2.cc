void WASABI_2(Int_t idssd, Int_t ich, Double_t gain, Double_t offset, Int_t range_L, Int_t range_U)
{
	cout << "Initial Information" << endl;
	cout << "DSSD : " << idssd+1 << endl;
	cout << "Channel : " << ich+1 << endl;
	cout << "Gain : " << gain << endl;
	cout << "Offset : " << offset << endl;
	cout << "Fit range : " << range_L << " to " << range_U << endl;


	TFile* file = new TFile("SiEcal_hist.root", "read");
	TH2D* hist;
	if (ich < 60)	hist = (TH2D*) file->Get(Form("dssd_x%d_ch%d", idssd+1, ich+1));
	if (ich >= 60)	hist = (TH2D*) file->Get(Form("dssd_y%d_ch%d", idssd+1, ich-60+1));

	TCanvas* cvs = new TCanvas("c1", "", 1200, 700);

	TF1* ftn1 = new TF1("ftn1", "[0]*x + [1]", 0, 1400);
	TF1* ftn2 = new TF1("ftn2", "[0]*x + [1]", 0, 1400);

	TGraph* graph = new TGraph();
	TF1* ftn3 = new TF1("ftn3", "[0]*x + [1]", 0, 1400);

	ofstream wasabi_gain;
	wasabi_gain.open (Form("WASABI_gain/WASABI_gain_%d_%d.dat", idssd, ich));

	hist->Draw("colz");
	ftn3->SetParameter(0, gain);
	ftn3->SetParameter(1, offset);
	ftn3->SetParLimits(0, gain-0.1, gain+0.1);
	ftn3->SetParLimits(1, offset-5, offset+5);
	hist->Fit(ftn3, "M0", "", range_L, range_U);


	gain = ftn3->GetParameter(0);
	offset = -(1173-ftn3->GetParameter(1))/(ftn3->GetParameter(0));

	if (ich < 60)	cout << "WASABI #" << idssd+1 << " X strip #" << ich+1 << " : " << gain << " " << offset << endl;
	if (ich >= 60)	cout << "WASABI #" << idssd+1 << " Y strip #" << ich-60+1 << " : " << gain << " " << offset << endl;
	wasabi_gain << gain << "	" << offset << endl;

	ftn1->SetParameter(0, ftn3->GetParameter(0));
	ftn1->SetParameter(1, ftn3->GetParameter(1));
	ftn2->SetParameter(0, ftn3->GetParameter(0));
	ftn2->SetParameter(1, ftn3->GetParameter(1)+159);
	ftn1->Draw("same");
	ftn2->Draw("same");
	ftn1->SetLineStyle(2);
	ftn2->SetLineStyle(2);
}
