void WASABI_3rd_Y_calib()
{
	TFile* file = new TFile("WASABI_T_hist_3rd_Y.root","read");

	TH2D* hist;
	TH1D* pro;
	TF1* ftn = new TF1("ftn","gaus(0)",-3000,-1000);

	Double_t mean, max;
	TCanvas* cvs = new TCanvas("cvs", "", 800, 400);
	for (Int_t i = 0; i < 40; i++)
	{
		hist = (TH2D*) file->Get(Form("hist_Y%d",i));
		
		pro = hist->ProjectionY("pro",150,175,"");
		pro->GetXaxis()->SetRangeUser(-3000,-1000);
		max = pro->GetMaximum();
		mean = pro->GetBinCenter(pro->GetMaximumBin());

		pro->Fit(ftn, "MQ", "", mean-80, mean+80);
		mean = ftn->GetParameter(1);
		cout << "2	" << i+60 << "	" << mean << endl;

		cvs->cd();
		pro->Draw();
		cvs->Update();
		cvs->Modified();
	}
}
