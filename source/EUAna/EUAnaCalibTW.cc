#include "EUTreeBeta.h"
#include "EUAnaCalibTW.h"
#include "TFile.h"
#include "TTree.h"
#include "TGraphErrors.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TF1.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;


EUAnaCalibTW::EUAnaCalibTW(const char* filename, TTree* tree) : EUTreeBeta(filename)
{}

EUAnaCalibTW::~EUAnaCalibTW()
{}

void EUAnaCalibTW::GetProEnergy(TGraphErrors* graph, TH2D* hist, Int_t bin)
{
	TH1D* pro;
	TF1* gaus = new TF1("gaus", "gaus(0)", 0, 50000);

	Double_t max;
	Double_t mean;
	Double_t stdv;
	Double_t start;
	Double_t end;

	for (Int_t i = 0; i < int(4000/bin); i++)
	{
		start = i*bin;
		end = bin + i*bin;
		pro = hist->ProjectionY("proX", start, end, "");
		max = pro->GetMaximum();
		mean = pro->GetBinCenter(pro->GetMaximumBin());
		stdv = pro->GetStdDev();
		gaus->SetParameters(max, mean, stdv);

//		pro->Fit("gaus", "MQ", "", mean - mean/5, mean + mean/5);
		pro->Fit(gaus, "MQ0");

		graph->SetPoint(i, (start+end)/2, gaus->GetParameter(1));
		graph->SetPointError(i, bin/2, 2.35*(gaus->GetParameter(2)));
	}

	delete gaus;

}

void EUAnaCalibTW::GetTW(TGraphErrors* graph, Double_t &con1, Double_t &con2, Double_t &con3)
{
	TF1* ftn = new TF1("twcorr", "[0]+[1]*TMath::Power(x, -[2])", 50, 3000);
	ftn->SetParameters(con1, con2, con3);

	graph->Fit(ftn, "MQ", "", 30, 2500);

	con1 = ftn->GetParameter(0);
	con2 = ftn->GetParameter(1);
	con3 = ftn->GetParameter(2);

}
