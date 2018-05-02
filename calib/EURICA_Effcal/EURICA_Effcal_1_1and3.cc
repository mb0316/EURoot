#include "eurica.h"

void EURICA_Effcal_1_1and3()
{
	TFile* outfile = new TFile("EURICA_ADC.root", "RECREATE");
	char euricafile1[100];
	char euricafile2[100];
	sprintf(euricafile1, "/home/mb0316/EURICA/EURoot/data/EURICA_Calib/eu152_ba133_1khz_clock0001.root");
	sprintf(euricafile2, "/home/mb0316/EURICA/EURoot/data/EURICA_Calib/eu152_ba133_1khz_clock0003.root");
	TFile* file1 = new TFile(Form("%s", euricafile1), "READ");
	TFile* file2 = new TFile(Form("%s", euricafile2), "READ");

	TH1D* hist_1 = new TH1D("GeCluster", "", 2000, 0, 2000);
	TH1D* hist_2 = new TH1D("GeAddback", "", 2000, 0, 2000);

	eurica hpge;

	hpge.GetTree(euricafile1);
	Long64_t nEnt = hpge.fChain->GetEntries();
	cout << nEnt << " entries." << endl;
	Long64_t trigcnt = 0;
	Bool_t flag = 0;

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		hpge.fChain->GetEntry(iEnt);
		for (Int_t ihit = 0; ihit < hpge.GeCluster_; ihit++)
		{
			hist_1->Fill(hpge.GeCluster_fEnergy[ihit]);
			if (hpge.GeCluster_fEnergy[ihit] > 3500) flag = 1;
		}
		for (Int_t ihit = 0; ihit < hpge.GeAddback_; ihit++) hist_2->Fill(hpge.GeAddback_fEnergy[ihit]);
		if (hpge.GeCluster_ > 0 && flag == 1) trigcnt++;
		flag = 0;
	}

	hpge.GetTree(euricafile2);
	nEnt = hpge.fChain->GetEntries();
	cout << nEnt << " entries." << endl;

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		hpge.fChain->GetEntry(iEnt);
		for (Int_t ihit = 0; ihit < hpge.GeCluster_; ihit++)
		{
			hist_1->Fill(hpge.GeCluster_fEnergy[ihit]);
			if (hpge.GeCluster_fEnergy[ihit] > 3500) flag = 1;
		}
		for (Int_t ihit = 0; ihit < hpge.GeAddback_; ihit++) hist_2->Fill(hpge.GeAddback_fEnergy[ihit]);
		if (hpge.GeCluster_ > 0 && flag == 1) trigcnt++;
		flag = 0;
	}

	TCanvas* cvs = new TCanvas("cvs", "", 800, 600);
	hist_1->Draw();
	hist_2->Draw();
	
	cvs->SetLogz();

	outfile->cd();
	hist_1->Write();
	hist_2->Write();
	outfile->Close();

	cout << "Number of trigger : " << trigcnt << endl;
}
