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
		cout << "Please type 'CalibTC #channel'." << endl;
		return 0;
	}

	Int_t ch_num = atoi(argv[1]);

	if (ch_num < 0 || ch_num > 83)
	{
		cout << "Wrong channel number. Please check again." << endl;
		return 0;
	}

	TH1D* hist_T = new TH1D("hist_T", "", 1000,-1000,1000);
	ifstream gcT_iso_twfile("../calib/isoT_TW.dat");
	Int_t temp_ch;
	Double_t temp_1, temp_2, temp_3;
	Double_t con1, con2, con3;
	for (Int_t i = 0; i < 84; i++)
	{
		gcT_iso_twfile >> temp_ch >> temp_1 >> temp_2 >> temp_3;
		if (temp_ch == ch_num)
		{
			con1 = temp_1;
			con2 = temp_2;
			con3 = temp_3;
			break;
		}
		else continue;
	}
	gcT_iso_twfile.close();
	Long64_t nEnt;


	for (Int_t ifile = 1007; ifile < 1130; ifile++)
	{
		EUAnaCalibTW* calib = new EUAnaCalibTW(Form("../results/MergeBeam/MergeBeam%04d.root", ifile));
		cout << ifile << endl;

		if (ifile == 1012 || ifile == 1049 || ifile == 1051 || ifile == 1063 || ifile == 1095 || ifile == 1110 || ifile == 1112 || ifile == 1113 || ifile == 1123)	continue;
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
						calib->TWCorrTime(calib->gc_E[ihit], calib->gc_T[ihit], con1, con2, con3);
						hist_T->Fill(calib->gc_T[ihit]);
					}

					else continue;
				}
			}
		}
		delete calib;
	}
	TCanvas* cvs1 = new TCanvas("cvs1", "", 800,400);
	hist_T->Draw();

	EUAnaCalibTW* calib = new EUAnaCalibTW("../results/MergeBeam/MergeBeam1060.root"); 
	ofstream isoTC;
	calib->MatchCenter(hist_T, con1);
	cout << ch_num << " : " << con1 << endl;

	isoTC.open ("../calib/isoT_TC.dat", ofstream::out | ofstream::app);
	isoTC << ch_num << "	" << con1 << endl;
	isoTC.close();

	cvs1->SaveAs(Form("../results/CalibTW/CalibTC%02d.pdf",ch_num));

//	theApp.Run();
}


