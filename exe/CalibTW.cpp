#include "TROOT.h"
#include "TApplication.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TTree.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"
#include "EUAnaCalibTW.h"
#include "EUTreeBeta.h"
#include "TSystem.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

int main (int argc, char* argv[])
{
	TApplication theApp("test",0,0);

	if (argc < 1 || argc > 1)
	{
		cout << "Please type 'CalibTW'." << endl;
		return 0;
	}

	int run_num = 1060;

	TString datafile = Form("../results/MergeBeam/MergeBeam%04d.root", run_num);

	EUAnaCalibTW* calib = new EUAnaCalibTW(datafile.Data());

	TH2D* hist_isoT[84];
	for (Int_t i = 0; i < 84; i++)	hist_isoT[i] = new TH2D(Form("hist_isoT%d",i), "", 4000,0,4000,500,20500,22000);
	
	Long64_t nEnt = calib->fData->GetEntries();

	for (Long64_t ient = 0; ient < nEnt; ient++)
	{
		calib->fData->GetEntry(ient);

		for (Int_t ihit = 0; ihit < calib->gchit; ihit++)
		{
			if (calib->eventid == 0)	hist_isoT[calib->gc_ch[ihit]]->Fill(calib->gc_E[ihit], calib->gc_T[ihit]);
//			if (calib->eventid == 0)	hist->Fill(calib->gc_E[ihit], calib->gc_T[ihit]);
			else continue;
		}
	}


	Double_t con1, con2, con3;
	TCanvas* cvs1 = new TCanvas("cvs1","",800,400);
	TGraphErrors* graph = new TGraphErrors();
	for (Int_t i = 0; i < 84; i++)
	{
		if (i == 50 || i == 72)	continue;
		else
		{
//			TGraphErrors* graph = new TGraphErrors();
			calib->GetProEnergy(graph, hist_isoT[i], 100);
			con1 = 21500;
			con2 = -5000;
			con3 = 1.5;

			gSystem->ProcessEvents();
			cvs1->cd();
			gSystem->ProcessEvents();
			cvs1->Update();
			gSystem->ProcessEvents();
			cvs1->Modified();
			gSystem->ProcessEvents();
			graph->Draw();		
			gSystem->ProcessEvents();
			sleep(1);

			calib->GetTW(graph, con1, con2, con3);
			cout << i << " " << con1 << " " << con2 << " " << con3 << endl;
			graph->Clear();
//			delete graph;
		}
	}
//	TCanvas* cvs2 = new TCanvas("cvs2","",800,400);
//	graph->Draw();
//	TCanvas* cvs1 = new TCanvas("cvs1","",800,400);
//	hist->Draw("colz");
	theApp.Run();
}

	
