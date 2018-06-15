#include "eurica.h"

void EURICA_OF_3()
{
	ifstream opencal("../eurica_overflow.dat");
	char openfile[100];
	sprintf(openfile, "../../data/EURICA_Calib/eu152run_0003.root");
	TFile* file = new TFile("../../data/EURICA_Calib/eu152run_0003.root", "READ");
	eurica hpge;
	hpge.GetTree(openfile);

	Double_t adc_ch[84];
	Double_t overflow[84];
	TH1D* hist = new TH1D("hist", "", 10000,0,10000);	

	for (Int_t i = 0; i < 84; i++)
	{
		opencal >> adc_ch[i] >> overflow[i];
	}

	Long64_t nEnt = hpge.fChain->GetEntries();

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		hpge.fChain->GetEntry(iEnt);
		for (Int_t ihit = 0; ihit < hpge.GeCluster_; ihit++)
		{
			if (hpge.GeCluster_fEnergy[ihit] < overflow[hpge.GeCluster_channel[ihit]]) hist->Fill(hpge.GeCluster_fEnergy[ihit]);
		}
	}

	TCanvas* cvs = new TCanvas("cvs", "", 800, 400);
	cvs->SetLogy();
	hist->Draw();
}
	
