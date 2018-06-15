#include "eurica.h"

void EURICA_Tcal_1()
{
	TFile* outfile = new TFile("EURICA_TDC.root", "RECREATE");
	char srfile[100];
	char lrfile[100];
	sprintf(srfile, "../../data/EURICA_Calib/ge_srtdc_cal0001.root");
	sprintf(lrfile, "../../data/EURICA_Calib/ge_lrtdc_cal0001.root");
	TFile* sfile = new TFile(Form("%s", srfile), "READ");

	eurica hpge;
	hpge.GetTree(srfile);

	TH2D* hist_sr = new TH2D("TDCs", "", 84, 0, 84, 5000, 0, 5000);
	TH2D* hist_lr = new TH2D("TDCl", "", 84, 0, 84, 14000, 0, 140000);

	Long64_t nEnt = hpge.fChain->GetEntries();

	cout << nEnt << " entries." << endl;

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		hpge.fChain->GetEntry(iEnt);
		for (Int_t ihit = 0; ihit < hpge.GeCluster_; ihit++) hist_sr->Fill(hpge.GeCluster_channel[ihit], hpge.GeCluster_fTDCs[ihit]);
	}

	TCanvas* cvs1 = new TCanvas("cvs1", "", 800, 600);
	hist_sr->Draw("colz");
	cvs1->SetLogz();

	TFile* lfile = new TFile(Form("%s", lrfile), "READ");
	hpge.GetTree(lrfile);

	nEnt = hpge.fChain->GetEntries();

	cout << nEnt << " entries." << endl;

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		hpge.fChain->GetEntry(iEnt);
		for (Int_t ihit = 0; ihit < hpge.GeCluster_; ihit++) hist_lr->Fill(hpge.GeCluster_channel[ihit], hpge.GeCluster_fTDCl[ihit]);
	}

	TCanvas* cvs2 = new TCanvas("cvs2", "", 800, 600);
	hist_lr->Draw("colz");
	cvs2->SetLogz();


	outfile->cd();
	hist_sr->Write();
	hist_lr->Write();
	outfile->Close();

}
