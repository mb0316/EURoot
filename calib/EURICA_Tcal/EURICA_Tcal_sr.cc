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


void EURICA_Tcal_sr()
{
	gStyle -> SetOptStat(0);
	TFile* file = new TFile("EURICA_TDC.root", "READ");
	TH2D* hist_tot = (TH2D*) file -> Get("TDCs");

	TH1D* hist[84];
	for (Int_t i = 0; i < 84; i++)
	{
		hist[i] = hist_tot -> ProjectionY(Form("hist_X%d", i), i+1, i+1);
	}
//	TCanvas* c5 = new TCanvas();
//	hist[3] -> Draw();



	Int_t maxbin = 0;
	Int_t max = 0;
	Double_t peaks[12] = {1000, 1250, 1500, 1800, 2150, 2400, 2600, 2900, 3200, 3500, 3800, 4100};
	Double_t repeaks[12] = {80, 160, 240, 320, 400, 480, 560, 640, 720, 800, 880, 960};
//	Double_t cal[8][84] = {0};
	Double_t cal = 0;
	Double_t ori_peak[12][84] = {0};
	Double_t mean = 0;
	Double_t dev = 0;
	TF1* fcn = new TF1("fitting", "gaus(0)", 0, 5000);
	TCanvas* can = new TCanvas();

	for (Int_t ihist = 0; ihist < 84; ihist++)
	{
		if (hist[ihist] -> GetEntries() == 0 || ihist == 60) cout << ihist << " channel is dead." << endl;

		else
		{
			for (Int_t ifit = 0; ifit < 12; ifit++)
			{
				if (ifit == 0)
				{
					hist[ihist] -> GetXaxis() -> SetRange(peaks[ifit] - 130, peaks[ifit] + 130);
					maxbin = hist[ihist] -> GetMaximumBin();
					max =  hist[ihist] -> GetBinContent(maxbin);
					fcn -> SetParameters(max, maxbin, 0.7);
					hist[ihist] -> Fit(fcn, "MQ", "", maxbin - 20, maxbin + 20);
					mean = fcn -> GetParameter(1);
					cal = peaks[ifit]/mean;
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
					cout << ihist << " " << ifit << " " << mean << endl;
					maxbin = 0;
					max = 0;
					mean = 0;
				}
				else
				{
					hist[ihist] -> GetXaxis() -> SetRange(peaks[ifit]/cal - 130, peaks[ifit]/cal + 130);
					maxbin = hist[ihist] -> GetMaximumBin();
					max =  hist[ihist] -> GetBinContent(maxbin);
					fcn -> SetParameters(max, maxbin, 0.7);
					hist[ihist] -> Fit(fcn, "MQ", "", maxbin - 20, maxbin + 20);
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
					cout << ihist << " " << ifit << " " << mean << endl;
					maxbin = 0;
					max = 0;
					mean = 0;
				}
			}
		}
	}


	Double_t gain[84] = {0};
	Double_t offset[84] = {0};
	TF1* linear[84];
	TGraphErrors* graph[84];
	TH2D* calib_hist = new TH2D("calib", ";HPGe channel; Time (ns)", 84, 0, 84, 4000, 0, 4000);
	TH2D* dum = new TH2D("dummy", ";TDCs channel;Time (ns)", 4000, 0, 4000, 2000, 0, 2000);
//	TCanvas* cvs = new TCanvas();
	ofstream outfile("../eurica_tdcs_calib.dat");

	for (Int_t i = 0; i < 84; i++)
	{
		graph[i] = new TGraphErrors();
		linear[i] = new TF1(Form("linear%d", i), "[0]*x+[1]", 0, 30000);
		for (Int_t j = 0; j < 12; j++)
		{
			graph[i] -> SetPoint(j, ori_peak[j][i], repeaks[j]);
		}
//		cvs -> cd();
		graph[i] -> Fit(linear[i], "MQ", 0, 15000);
//		graph[i] -> Draw();
//		graph[i] -> SetMarkerSize(31);
//		can -> Modified();
//		can -> Update();
//		sleep(1);
		gain[i] = linear[i] -> GetParameter(0);
		offset[i] = linear[i] -> GetParameter(1);
		cout << i << " " << gain[i] << " " << offset[i] << endl;
		outfile << i << "	" << gain[i] << "	" << offset[i] << endl;
	}
	outfile.close();
	

	Int_t count = 0;
	Double_t recount = 0;
	TFile* out = new TFile("caltdcs.root", "RECREATE");
	TH1D* rehist[84];
	for (Int_t i = 0; i < 84; i++)
	{
		rehist[i] = new TH1D(Form("rehist_%d", i), "", 4000, 0, 4000);
		for (Int_t j = 0; j < 4000; j++)
		{
			count = hist[i] -> GetBinContent(j+1);
			recount = (gain[i]*j + offset[i]);
			calib_hist -> Fill(i, recount, count);
//			rehist[i] -> Fill(j/10, recount);
			
		}
	}

	can -> cd();
	calib_hist -> Draw("colz");
	can -> SetLogz();
	calib_hist -> GetYaxis() -> SetRange(0, 1200);
	TCanvas* c3 = new TCanvas();
	dum -> Draw();
	for (Int_t i = 0; i < 84; i++)
	{
		linear[i] -> Draw("same");
	}



}


