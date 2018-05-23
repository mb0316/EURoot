#include "wasabi.h"

void WASABI_0()
{
	TFile* outfile = new TFile("WASABI_map.root", "RECREATE");
	TH1D* hist_E_X[5][60];
	TH1D* hist_T_X[5][60];
	TH1D* hist_E_Y[5][40];
	TH1D* hist_T_Y[5][40];

	TH1D* hist_ADC_X[5][60];
	TH1D* hist_TDC_X[5][60];
	TH1D* hist_ADC_Y[5][40];
	TH1D* hist_TDC_Y[5][40];
	

	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t ix = 0; ix < 60; ix++)
		{
			hist_E_X[i][ix] = new TH1D(Form("hist_E_X_%d_%d", i, ix), "", 1000, 0, 10000);
			hist_T_X[i][ix] = new TH1D(Form("hist_T_X_%d_%d", i, ix), "", 11000, -10000, 100000);
			hist_ADC_X[i][ix] = new TH1D(Form("hist_ADC_X_%d_%d", i, ix), "", 1000, 0, 10000);
			hist_TDC_X[i][ix] = new TH1D(Form("hist_TDC_X_%d_%d", i, ix), "", 11000, -10000, 100000);
		}
		
		for (Int_t iy = 0; iy < 40; iy++)
		{
			hist_E_Y[i][iy] = new TH1D(Form("hist_E_Y_%d_%d", i, iy), "", 1000, 0, 10000);
			hist_T_Y[i][iy] = new TH1D(Form("hist_T_Y_%d_%d", i, iy), "", 11000, -10000, 100000);
			hist_ADC_Y[i][iy] = new TH1D(Form("hist_ADC_Y_%d_%d", i, iy), "", 1000, 0, 10000);
			hist_TDC_Y[i][iy] = new TH1D(Form("hist_TDC_Y_%d_%d", i, iy), "", 11000, -10000, 100000);
		}	
	}

	TFile* file;
	char wasabifile[100];

	wasabi dssd;
	Long64_t nEnt;

	ifstream adc_map;
	ifstream tdc_map;

	Int_t cADC[5][100][2], cTDC[5][100][2];
	Int_t temp_d, temp_c, temp_C, temp_id, temp_ic;

	adc_map.open ("n_ADC_table_142Te_exp.dat");
	tdc_map.open ("n_TDC_table_142Te_exp.dat");

	for (Int_t i = 0; i < 500; i++)
	{
		adc_map >> temp_d >> temp_c >> temp_C >> temp_id >> temp_ic;
		cADC[temp_id][temp_ic][0] = temp_d;
		cADC[temp_id][temp_ic][1] = temp_c;
		if (i < 499)
		{
			tdc_map >> temp_d >> temp_c >> temp_C >> temp_id >> temp_ic;
			cTDC[temp_id][temp_ic][0] = temp_d;
			cTDC[temp_id][temp_ic][1] = temp_c;
		}
	}

	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t ic = 0; ic < 100; ic++)
		{
			if (cTDC[i][ic][0] > 5 || cTDC[i][ic][0] < 0) cout << i << " " << ic << " " << cTDC[i][ic][0] << " " << cTDC[i][ic][1] << endl;
		}
	}

	for (Int_t i = 1060; i < 1061; i++)
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
						hist_E_X[idssd][ix] -> Fill(dssd.w3_ex[idssd][ix]);
						hist_T_X[idssd][ix] -> Fill(dssd.w3_tx[idssd][ix][0]);
						hist_ADC_X[idssd][ix] -> Fill(dssd.ADC[cADC[idssd][ix][0]][cADC[idssd][ix][1]]);
						hist_TDC_X[idssd][ix] -> Fill(dssd.TDC[cTDC[idssd][ix][0]][cTDC[idssd][ix][1]][0]);
					}

					for (Int_t iy = 0; iy < 40; iy++)
					{
						hist_E_Y[idssd][iy] -> Fill(dssd.w3_ey[idssd][iy]);
						hist_T_Y[idssd][iy] -> Fill(dssd.w3_ty[idssd][iy][0]);
						hist_ADC_Y[idssd][iy] -> Fill(dssd.ADC[cADC[idssd][iy+60][0]][cADC[idssd][iy+60][1]]);
						if (idssd == 1 && iy == 39) continue;
						else hist_TDC_Y[idssd][iy] -> Fill(dssd.TDC[cTDC[idssd][iy+60][0]][cTDC[idssd][iy+60][1]][0]);
					}
				}
			}
		}
	
	}

	outfile->cd();
	
	for (Int_t i = 0; i < 5; i++)
	{
		for (Int_t ix = 0; ix < 60; ix++)
		{
			hist_E_X[i][ix]->Write();
			hist_T_X[i][ix]->Write();
			hist_ADC_X[i][ix]->Write();
			hist_TDC_X[i][ix]->Write();
		}
		
		for (Int_t iy = 0; iy < 40; iy++)
		{
			hist_E_Y[i][iy]->Write();
			hist_T_Y[i][iy]->Write();
			hist_ADC_Y[i][iy]->Write();
			hist_TDC_Y[i][iy]->Write();
		}	
	}

	outfile->Close();
}		
