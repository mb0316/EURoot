#include "wasabi.h"

void WASABI_0()
{
	Int_t w3_ex[5][60], w3_ey[5][40], w3tx[5][60], w3ty[5][40], f11L;

	TFile* outfile = new TFile("../../data/WASABI_Calib/w3.root", "RECREATE");
	TTree* tree = new TTree("w3", "tree");
	tree->Branch("w3_ex", w3_ex, "w3_ex[5][60]/I");
	tree->Branch("w3_ey", w3_ey, "w3_ey[5][40]/I");
	tree->Branch("w3tx", w3tx, "w3tx[5][60]/I");
	tree->Branch("w3ty", w3ty, "w3ty[5][40]/I");
	tree->Branch("f11L", &f11L);


	TFile* file;

	char wasabifile[100];

	wasabi dssd;
	Long64_t nEnt;

	for (Int_t i = 1016; i < 1130; i++)
	{
		if (i == 1024 || i == 1027 || (i >= 1041 && i <= 1044) || i == 1049 || (i>=1110 && i <=1119)) continue;
		else
		{

			sprintf(wasabifile, Form("../../data/w3_data_%d.root",i));
			file = new TFile(wasabifile, "READ");

			dssd.GetTree(wasabifile);
			nEnt = dssd.fChain->GetEntries();

			cout << i << " data file entries : " << nEnt << endl;

			for (Long64_t ient = 0; ient < nEnt; ient++)
			{
				dssd.fChain->GetEntry(ient);
				for (Int_t idssd = 0; idssd < 5; idssd++)
				{
					for (Int_t ix = 0; ix < 60; ix++)
					{
						w3_ex[idssd][ix] = dssd.w3_ex[idssd][ix];
						w3tx[idssd][ix] = dssd.w3tx[idssd][ix][0];
					}

					for (Int_t iy = 0; iy < 40; iy++)
					{
						w3_ey[idssd][iy] = dssd.w3_ey[idssd][iy];
						w3ty[idssd][iy] = dssd.w3ty[idssd][iy][0];
					}
				}
				f11L = dssd.f11L;	
				tree->Fill();
			}
		}
	
	}

	outfile->cd();
	tree->Write();
	outfile->Close();

}		
