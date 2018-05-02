#include "eurica.h"

void EURICA_OF_1()
{
	TFile* outfile = new TFile("EURICA_E.root", "RECREATE");
	char euricafile[100];
	sprintf(euricafile, "/home/mb0316/EURICA/EURoot/data/EURICA_Calib/eu152run_0003.root");
	TFile* file = new TFile(Form("%s", euricafile), "READ");

	eurica hpge;
	hpge.GetTree(euricafile);

	TH2D* hist = new TH2D("Energy_ch", "", 84, 0, 84, 10000, 0, 10000);

	Long64_t nEnt = hpge.fChain->GetEntries();

	cout << nEnt << " entries." << endl;

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		hpge.fChain->GetEntry(iEnt);
		for (Int_t ihit = 0; ihit < hpge.GeCluster_; ihit++) hist->Fill(hpge.GeCluster_channel[ihit], hpge.GeCluster_fEnergy[ihit]);
	}

	TCanvas* cvs = new TCanvas("cvs", "", 800, 600);
	hist->Draw("colz");
	cvs->SetLogz();

	outfile->cd();
	hist->Write();
	outfile->Close();

}
