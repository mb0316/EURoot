void WASABI_6()
{
	TH1D* hist;
	TFile* file = new TFile("WASABI_T_hist_2.root","read");
	TCanvas* cvs = new TCanvas("cvs","",800,400);
	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t ix = 0; ix <60; ix++)
		{
			hist = (TH1D*) file->Get(Form("hist_X_%d_%d",idssd,ix));
			hist->Draw();
			hist->GetXaxis()->SetRangeUser(-1000,1000);
			cvs->Update();
			cvs->Modified();
		}
		for (Int_t iy = 0; iy <40; iy++)
		{
			hist = (TH1D*) file->Get(Form("hist_Y_%d_%d",idssd,iy));
			hist->Draw();
			hist->GetXaxis()->SetRangeUser(-1000,1000);
			cvs->Update();
			cvs->Modified();
		}
	}
}
