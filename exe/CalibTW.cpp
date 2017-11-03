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
//	TApplication theApp("test",0,0);

	if (argc < 2 || argc > 2)
	{
		cout << "Please type 'CalibTW #channel'." << endl;
		return 0;
	}

	Int_t ch_num = atoi(argv[1]);

	if (ch_num < 0 || ch_num > 83)
	{
		cout << "Wrong channel number. Please check again." << endl;
		return 0;
	}

	TH2D* hist_isoT = new TH2D("hist_isoT", "", 2000,0,2000,500,20500,22000);
	TH2D* hist_betaT = new TH2D("hist_betaT", "", 2000,0,2000,500,20500,22000);
//	TH2D* hist_Ts = new TH2D("hist_Ts", "", 2000,0,2000,100,0,1000);
//	TH2D* hist_Tl = new TH2D("hist_Tl", "", 2000,0,2000,100,4000,5000);
	
	Long64_t nEnt;


	for (Int_t ifile = 1007; ifile < 1130; ifile++)
	{
		EUAnaCalibTW* calib = new EUAnaCalibTW(Form("../results/MergeBeam/MergeBeam%04d.root", ifile));
		cout << ifile << endl;

		if (ifile == 1012 || ifile == 1049 || ifile == 1051 || ifile == 1063 || ifile == 1095 || ifile == 1110 || ifile == 1112 || ifile == 1113 && ifile == 1123)	continue;
		else if (ifile > 1023 && ifile < 1028)	continue;
		else if (ifile > 1040 && ifile < 1045)	continue;
		else
		{
			nEnt = calib->fData->GetEntries();
			for (Long64_t ient = 0; ient < nEnt; ient++)
			{
				calib->fData->GetEntry(ient);

				for (Int_t ihit = 0; ihit < calib->gchit; ihit++)
				{
					if (calib->eventid == 0 && calib->gc_ch[ihit] == ch_num)
					{
						hist_isoT->Fill(calib->gc_E[ihit], calib->gc_T[ihit]);
//						hist_Ts->Fill(calib->gc_E[ihit], calib->gc_Ts[ihit]);
//						hist_Tl->Fill(calib->gc_E[ihit], calib->gc_Tl[ihit]);
					}
					if (calib->eventid == 1 && calib->gc_ch[ihit] == ch_num)	hist_betaT->Fill(calib->gc_E[ihit], calib->gc_T[ihit]);

					else continue;
				}
			}
		}
		delete calib;
	}

	EUAnaCalibTW* calib = new EUAnaCalibTW("../results/MergeBeam/MergeBeam1060.root"); 
//	Double_t con1[4] = {21500, 21600, 400, 4620};
//	Double_t con2[4] = {-2000, -2000, -2000, 2000};
//	Double_t con3[4] = {0.6, 0.6, 0.6, 0.6};
	Double_t con1[2] = {21500, 21600};
	Double_t con2[2] = {-2000, -2000};
	Double_t con3[2] = {0.6, 0.6};
	TCanvas* cvs1 = new TCanvas("cvs1","",500,1000);
	cvs1 -> Divide(1,2);
	TCanvas* cvs2 = new TCanvas("cvs2","",500,1000);
	cvs2 -> Divide(1,2);
	TGraphErrors* graph[2];
//	TGraphErrors* graph[4];

	ofstream isoT;
	ofstream betaT;
//	ofstream gcTs;
//	ofstream gcTl;

//	for (Int_t i = 0; i < 4; i++)
	for (Int_t i = 0; i < 2; i++)
	{	
		graph[i] = new TGraphErrors(Form("graph%d",i));

		if (i == 0)
		{
			calib->GetProEnergy(graph[0], hist_isoT, 50);
			gSystem->ProcessEvents();
			cvs2->cd(i+1);
			hist_isoT->Draw("colz");
			gSystem->ProcessEvents();
//			calib->GetTW(hist_isoT, con1[i], con2[i], con3[i]);
		}
		if (i == 1)
		{
			calib->GetProEnergy(graph[1], hist_betaT, 50);
			gSystem->ProcessEvents();
			cvs2->cd(i+1);
			hist_betaT->Draw("colz");
			gSystem->ProcessEvents();
//			calib->GetTW(hist_betaT, con1[i], con2[i], con3[i]);
		}
/*
		if (i == 2)
		{
			calib->GetProEnergy(graph[2], hist_Ts, 60);
			gSystem->ProcessEvents();
			cvs2->cd(i+1);
			hist_Ts->Draw("colz");
			gSystem->ProcessEvents();
//			calib->GetTW(hist_Ts, con1[i], con2[i], con3[i]);
		}

		if (i == 3)
		{
			calib->GetProEnergy(graph[3], hist_Tl, 60);
			gSystem->ProcessEvents();
			cvs2->cd(i+1);
			hist_Tl->Draw("colz");
			gSystem->ProcessEvents();
//			calib->GetTW(hist_Tl, con1[i], con2[i], con3[i]);
		}
*/
		calib->GetTW(graph[i], con1[i], con2[i], con3[i]);
		cout << i << " " << con1[i] << " " << con2[i] << " " << con3[i] << endl;
		gSystem->ProcessEvents();
		cvs1->cd(i+1);
		gSystem->ProcessEvents();
		graph[i]->Draw();		
	}

	isoT.open ("../calib/isoT_TW.dat", ofstream::out | ofstream::app);
	isoT << ch_num << "	" << con1[0] << "	" << con2[0] << "	" << con3[0] << endl;
	isoT.close();

	betaT.open ("../calib/betaT_TW.dat", ofstream::out | ofstream::app);
	betaT << ch_num << "	" << con1[1] << "	" << con2[1] << "	" << con3[1] << endl;
	betaT.close();
/*
	gcTs.open ("../calib/gcTs_TW.dat", ofstream::out | ofstream::app);
	gcTs << ch_num << "	" << con1[2] << "	" << con2[2] << "	" << con3[2] << endl;
	gcTs.close();

	gcTl.open ("../calib/gcTl_TW.dat", ofstream::out | ofstream::app);
	gcTl << ch_num << "	" << con1[3] << "	" << con2[3] << "	" << con3[3] << endl;
	gcTl.close();
*/
	cvs1->SaveAs(Form("../results/CalibTW/CalibTW%02d.pdf",ch_num));

//	theApp.Run();
}


