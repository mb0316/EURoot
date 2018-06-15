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


void EURICA_Tcal_lr()
{
	gStyle -> SetOptStat(0);
	TFile* file = new TFile("EURICA_TDC.root", "READ");
	TH2D* hist_tot = (TH2D*) file -> Get("TDCl");

	TH1D* hist = new TH1D();
	hist = hist_tot -> ProjectionY("proY");

	Int_t nbins = hist -> GetNbinsX();
	Int_t peakvalue = 7797;
	Int_t deltapeak = 1637;
	Double_t maxbin = 0;
	Double_t max = 0;
	Double_t ori_peak[64] = {0};

	TF1* fcn = new TF1("fitting", "gaus(0)", 0, 5000);
	TCanvas* can = new TCanvas();

	for (Int_t ifit = 0; ifit < 64; ifit++)
	{
		hist -> GetXaxis() -> SetRange(peakvalue*(nbins/140E3) + ifit*deltapeak*(nbins/140E3) - 50, peakvalue*(nbins/140E3) + ifit*deltapeak*(nbins/140E3) + 50);
		maxbin = hist -> GetMaximumBin();
//		cout << ifit << " " << maxbin << endl;
		max = hist -> GetBinContent(maxbin);
		cout << ifit << " " << maxbin << " " << max << endl;
		fcn -> SetParameters(max, maxbin*(140E3/nbins), 2*(140E3/nbins));
		hist -> Fit(fcn, "MQ", "", maxbin*(140E3/nbins) - 100, maxbin*(140E3/nbins) + 100);	
		ori_peak[ifit] = fcn -> GetParameter(1);
/*
		can -> cd();
		hist -> Draw();
		fcn -> Draw("same");
		can -> Modified();
		can -> Update();
		sleep(1);
*/
		maxbin = 0;
		max = 0;
	}

	Double_t gain = 0;
	Double_t offset = 0;
	TF1* linear = new TF1("linearfit", "[0]*x+[1]", 0, 140E3);
	TGraphErrors* graph = new TGraphErrors();
	TH2D* calib_hist = new TH2D("calib", "", 84, 0, 84, 100000, 0, 100000);
	TH2D* dum = new TH2D("dummy", "", 14000, 0, 140E3, 100000, 0, 100000);
//	TCanvas* cvs = new TCanvas();
	ofstream outfile("../eurica_tdcl_calib.dat");

	for (Int_t i = 0; i < 64; i++)
	{
		graph -> SetPoint(i, ori_peak[i], 1280+1280*i);
	}
//		cvs -> cd();
	graph -> Fit(linear, "MQ", 0, 140E3);
	gain = linear -> GetParameter(0);
	offset = linear -> GetParameter(1);
	cout << gain << " " << offset << endl;
	outfile << gain << "	" << offset << endl;
	outfile.close();
	

	Int_t count = 0;
	Double_t recount = 0;
	TFile* out = new TFile("caltdcl.root", "RECREATE");
	for (Int_t i = 0; i < 84; i++)
	{
		for (Int_t j = 0; j < nbins; j++)
		{
			count = hist_tot -> GetBinContent(i+1, j+1);
			recount = (gain*j*(140E3/nbins) + offset);
			calib_hist -> Fill(i, recount, count);
//			rehist[i] -> Fill(j/10, recount);
			
		}
	}

	can -> cd();
	calib_hist -> Draw("colz");
	can -> SetLogz();
	calib_hist -> GetYaxis() -> SetRange(0, 100000);
	TCanvas* c3 = new TCanvas();
	dum -> Draw();
	linear -> Draw("same");


}


