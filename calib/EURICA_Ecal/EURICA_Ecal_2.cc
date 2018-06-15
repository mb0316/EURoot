#include "TTree.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TFile.h"
#include "TH2D.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include <iostream>
#include <fstream>
#include "TStyle.h"

using namespace std;


void EURICA_Ecal_2()
{
	gStyle -> SetOptStat(0);
	TFile* file = new TFile("EURICA_ADC.root", "READ");
	TH2D* hist_tot = (TH2D*) file -> Get("ADC_ch");

	TH1D* hist[84];
	for (Int_t i = 0; i < 84; i++)
	{
		hist[i] = hist_tot -> ProjectionY(Form("hist_X%d", i), i+1, i+1);
	}
//	TCanvas* c5 = new TCanvas();
//	hist[3] -> Draw();



	Int_t maxbin = 0;
	Int_t max = 0;
	Double_t peaks[8] = {1217.7, 2446.6, 3442.8, 7789.0, 8673.8, 9640.6, 11120.8, 14080.1};
	Double_t repeaks[8] = {121.77, 244.66, 344.28, 778.90, 867.38, 964.06, 1112.08, 1408.01};
	Double_t cal = 0;
	Double_t ori_peak[8][84] = {0};
	Double_t mean = 0;
	Double_t dev = 0;
	TF1* fcn = new TF1("fitting", "gaus(0) + [3]*x + [4]", 0, 50000);
	TCanvas* can = new TCanvas();

	for (Int_t ihist = 0; ihist < 84; ihist++)
	{
		if (hist[ihist] -> GetEntries() == 0) cout << ihist << " crystal is dead." << endl;
		else
		{
		
		if (ihist == 54)
		{
			for (Int_t ifit = 0; ifit < 8; ifit++)
			{
				if (ifit == 0)
				{
					hist[ihist] -> GetXaxis() -> SetRangeUser(1.75*peaks[ifit] - 700, 1.75*peaks[ifit] + 700);
					maxbin = hist[ihist] -> GetMaximumBin();
					max =  hist[ihist] -> GetBinContent(maxbin);
					fcn -> SetParameters(max, maxbin, 0.7, 0.0, 0.0);
					hist[ihist] -> Fit(fcn, "MQ", "", maxbin - 100, maxbin + 100);
					mean = fcn -> GetParameter(1);
					cal = 1.75*peaks[ifit]/mean;
					ori_peak[ifit][ihist] = mean;
					dev = fcn -> GetParameter(2);
/*
					can -> cd();
					hist[ihist] -> Draw();
					fcn -> Draw("same");
					can -> Modified();
					can -> Update();
					sleep(1);
*/
					maxbin = 0;
					max = 0;
					mean = 0;
				}
				else
				{
					hist[ihist] -> GetXaxis() -> SetRangeUser(1.75*peaks[ifit]/cal - 500, 1.75*peaks[ifit]/cal + 500);
					maxbin = hist[ihist] -> GetMaximumBin();
					max =  hist[ihist] -> GetBinContent(maxbin);
					fcn -> SetParameters(max, maxbin, 0.7, 0.0, 0.0);
					hist[ihist] -> Fit(fcn, "MQ", "", maxbin - 100, maxbin + 100);
					mean = fcn -> GetParameter(1);
					ori_peak[ifit][ihist] = mean;
					dev = fcn -> GetParameter(2);
/*
					can -> cd();
					hist[ihist] -> Draw();
					fcn -> Draw("same");
					can -> Modified();
					can -> Update();
					sleep(1);
*/
					maxbin = 0;
					max = 0;
					mean = 0;
				}
			}
			
		
		}

		else
		{
			for (Int_t ifit = 0; ifit < 8; ifit++)
			{
				if (ifit == 0)
				{
					hist[ihist] -> GetXaxis() -> SetRange(peaks[ifit] - 700, peaks[ifit] + 700);
					maxbin = hist[ihist] -> GetMaximumBin();
					max =  hist[ihist] -> GetBinContent(maxbin);
					fcn -> SetParameters(max, maxbin, 0.7, 0.0, 0.0);
					hist[ihist] -> Fit(fcn, "MQ", "", maxbin - 100, maxbin + 100);
					mean = fcn -> GetParameter(1);
					cal = peaks[ifit]/mean;
					ori_peak[ifit][ihist] = mean;
					dev = fcn -> GetParameter(2);
//					can -> cd();
//					hist[ihist] -> Draw();
//					fcn -> Draw("same");
//					can -> Modified();
//					can -> Update();
//					sleep(1);
					maxbin = 0;
					max = 0;
					mean = 0;
				}
				else
				{
					hist[ihist] -> GetXaxis() -> SetRange(peaks[ifit]/cal - 500, peaks[ifit]/cal + 500);
					maxbin = hist[ihist] -> GetMaximumBin();
					max =  hist[ihist] -> GetBinContent(maxbin);
					fcn -> SetParameters(max, maxbin, 0.7, 0.0, 0.0);
					hist[ihist] -> Fit(fcn, "MQ", "", maxbin - 100, maxbin + 100);
					mean = fcn -> GetParameter(1);
					ori_peak[ifit][ihist] = mean;
					dev = fcn -> GetParameter(2);
//					can -> cd();
//					hist[ihist] -> Draw();
//					fcn -> Draw("same");
//					can -> Modified();
//					can -> Update();
//					sleep(1);
					maxbin = 0;
					max = 0;
					mean = 0;
				}
			}
		}
		}
	}


	Double_t gain[84] = {0};
	Double_t offset[84] = {0};
	TF1* linear[84];
	TGraphErrors* graph[84];
	TH2D* calib_hist = new TH2D("calib", "", 84, 0, 84, 3000, 0, 3000);
	TH2D* dum = new TH2D("dummy", "", 30000, 0, 30000, 3000, 0, 3000);
	TCanvas* cvs = new TCanvas();
	ofstream outfile("../eurica_adc_calib.dat");

	for (Int_t i = 0; i < 84; i++)
	{
		graph[i] = new TGraphErrors();
		linear[i] = new TF1(Form("linear%d", i), "[0]*x+[1]", 0, 30000);
		for (Int_t j = 0; j < 8; j++)
		{
			graph[i] -> SetPoint(j, ori_peak[j][i], repeaks[j]);
		}
		cvs -> cd();
		graph[i] -> Fit(linear[i], "MQ", 0, 15000);
/*
		graph[i] -> Draw();
		graph[i] -> SetMarkerSize(31);
		can -> Modified();
		can -> Update();
		sleep(1);
*/
		gain[i] = linear[i] -> GetParameter(0);
		offset[i] = linear[i] -> GetParameter(1);
		cout << i << " " << gain[i] << " " << offset[i] << endl;
		outfile << i << "	" << gain[i] << "	" << offset[i] << endl;
	}
	outfile.close();
	

	Int_t count = 0;
	Double_t recount = 0;
	TFile* out = new TFile("calhist.root", "RECREATE");
	TH1D* rehist[84];
	for (Int_t i = 0; i < 84; i++)
	{
		rehist[i] = new TH1D(Form("rehist_%d", i), "", 3000, 0, 3000);
		for (Int_t j = 0; j < 30000; j++)
		{
			count = hist[i] -> GetBinContent(j+1);
			recount = (gain[i]*j + offset[i]);
			calib_hist -> Fill(i, recount, count);
		}
	}

	can -> cd();
	calib_hist -> Draw("colz");
	can -> SetLogz();
	calib_hist -> GetYaxis() -> SetRange(0, 15000);
	TCanvas* c3 = new TCanvas();
	dum -> Draw();
	for (Int_t i = 0; i < 84; i++)
	{
		linear[i] -> Draw("same");
	}

	out->cd();
	calib_hist->Write();
	out->Close();

}
