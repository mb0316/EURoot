#include "eurica.h"

void EURICA_Effcal_1()
{
	TFile* outfile = new TFile("EURICA_ADC.root", "RECREATE");
	TFile* file[7];
	char euricafile[7][100];

	TH1D* hist_1 = new TH1D("GeCluster", "", 2000, 0, 2000);
	TH1D* hist_2 = new TH1D("GeAddback", "", 2000, 0, 2000);

	eurica hpge;

	ofstream log;
	log.open ("trig_info.dat");

	Long64_t nEnt, trigcnt;
	Bool_t flag;

	for (Int_t i = 0; i < 7; i++)
	{
		sprintf(euricafile[i], Form("../../data/EURICA_Calib/efficiency/eu152_ba133_1khz_%04d.root", i+1));
		file[i] = new TFile(Form("%s", euricafile[i]), "READ");

		hpge.GetTree(euricafile[i]);
		nEnt = hpge.fChain->GetEntries();
		cout << nEnt << " entries." << endl;
		trigcnt = 0;
		flag = 0;

		for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
		{
			hpge.fChain->GetEntry(iEnt);
			for (Int_t ihit = 0; ihit < hpge.GeCluster_; ihit++)
			{
				if (hpge.GeCluster_fTime[ihit] > -75000 && hpge.GeCluster_fTime[ihit] < 24000)
				{
					hist_1->Fill(hpge.GeCluster_fEnergy[ihit]);
					flag = 1;
				}
			}
			for (Int_t ihit = 0; ihit < hpge.GeAddback_; ihit++)
			{
				if (hpge.GeAddback_fTime[ihit] > -75000 && hpge.GeCluster_fTime[ihit] < 24000) hist_2->Fill(hpge.GeAddback_fEnergy[ihit]);
			}
			if (flag == 1) trigcnt++;
			flag = 0;
		}

		log << i+1 << "	" << nEnt << "	" << trigcnt << endl;
	}
	TCanvas* cvs = new TCanvas("cvs", "", 800, 600);
	hist_1->Draw();
	hist_2->Draw();
	
	cvs->SetLogz();

	outfile->cd();
	hist_1->Write();
	hist_2->Write();
	outfile->Close();
}
