void WASABI_8()
{
	TH1D* hist;
	TCanvas* cvs = new TCanvas("cvs", "", 800, 400);
	TF1* ftn = new TF1("ftn", "gaus(0)", -300, 300);
	Double_t tzero[40];
	Double_t max, mean;

	TFile* file = new TFile("hist_BT_3rd_Y.root", "read");
	for (Int_t i = 0; i < 40; i++)
	{
		hist = (TH1D*) file->Get(Form("hist%d", i));
		cvs->cd();
		hist->Draw();
		max = hist->GetMaximum();
		mean = hist->GetBinCenter(hist->GetMaximumBin());
		hist->Fit(ftn,"MQ", "", mean - 100, mean + 80);
		cout << i << " " << ftn->GetParameter(1) << endl;
		tzero[i] = ftn->GetParameter(1);
		cvs->Update();
		cvs->Modified();

	}

	ifstream calib_ori;
	calib_ori.open("../tzero.dat");
	Double_t tzero_ori[5][100];
	Int_t ndssd, nch;
	for (Int_t i = 0; i < 500; i++)
		calib_ori >> ndssd >> nch >> tzero_ori[ndssd][nch];
	calib_ori.close();
	for (Int_t i = 0; i < 40; i++)	
		tzero_ori[2][i+60] = tzero_ori[2][i+60] + tzero[i];

	ofstream calib;
	calib.open("../tzero.dat");
	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t ich = 0; ich < 100; ich++)
			calib << idssd << "	" << ich << "	" << tzero_ori[idssd][ich] << endl;
	}

}
