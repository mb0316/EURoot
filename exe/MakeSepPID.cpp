#include "TTree.h"
#include "EUTreeDecay.h"
#include "EUAnaPID.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "TFile.h"
#include "TH1D.h"
#include <fstream>
#include <map>
#include "TApplication.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TGraph.h"

using namespace std;

int main (int argc, char* argv[])
{
//	TApplication theApp("test",0,0);

	if (argc < 4 || argc > 5)
	{
		cout << "Please type 'MakeSepPID #Z #Mass #Q'." << endl;
		return 0;
	}

	Int_t zpro = atoi(argv[1]);
	Int_t mass = atoi(argv[2]);
	Int_t qch = atoi(argv[3]);
	Double_t aoq = double(mass)/double(qch);

	cout << "Proton number : " << zpro << endl;
	cout << "A/Q : " << aoq << endl;

	Double_t z_sig = 0.15;
	Double_t aoq_sig = 0.001;

	Double_t z_mean, aoq_mean, z_cut, aoq_cut;
	TString filename;
	filename = "../results/BuildBetaDecay/BuildBetaDecay.root";

	TFile* out  = new TFile(Form("../results/PID/Betadecay_%d_%d.root", zpro, mass), "RECREATE");
	TTree* tree = new TTree("tree", "tree");
	EUTreeDecay* decay = new EUTreeDecay(filename);
	EUAnaPID* pid = new EUAnaPID(tree);

	//	EUAnaPID* beta = new EUAnaPID("../results/BuildBetaDecay/BuildBetaDecay.root");
	TH1D* hist_Z = new TH1D("Z", "", 1000, 50, 55);
	TH1D* hist_A = new TH1D("Mass", "", 1000, 2.6, 2.8);
//	TH2D* hist = new TH2D("t-g", "", 2000, 0, 2000, 500, -1000, 1000);

	Long64_t nEnt = decay->fData->GetEntries();

	if (zpro == qch)
	{
		for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
		{
			decay->fData->GetEntry(iEnt);

			if (iEnt%1000==0)
			{
				printf("%lld entry.", iEnt);
				fflush(stdout);
				printf("\r");
			}

			if (decay->AoQ > aoq-2*aoq_sig && decay->AoQ < aoq+2*aoq_sig && decay->Zpro > zpro-2*z_sig && decay->Zpro < zpro+2*z_sig)
			{
				hist_Z -> Fill(decay->Zpro);
				hist_A -> Fill(decay->AoQ);
			}
			else continue;
		}

		z_mean = double(zpro);
		aoq_mean = aoq;

		pid->PIDFitting(hist_Z, z_mean, z_sig);
		pid->PIDFitting(hist_A, aoq_mean, aoq_sig);

		z_cut = z_sig*3;
		aoq_cut = aoq_sig*3;
	}
	else if (zpro != aoq)
	{
		z_mean = double(zpro);
		aoq_mean = aoq-0.001;
		z_cut = z_sig*2;
		aoq_cut = aoq_sig*2;
	}

	cout << "Z mean : " << z_mean << endl;
	cout << "Z 3sigma : " << z_cut << endl;
	cout << "Mass mean : " << aoq_mean << endl;
	cout << "Mass 3sigma : " << aoq_cut << endl;

	pid->GetCalib();
	Double_t rad = 2;

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		decay->fData->GetEntry(iEnt);

		if (iEnt%1000==0)
		{
			printf("%lld entry.", iEnt);
			fflush(stdout);
			printf("\r");
		}

		rad = TMath::Power((decay->Zpro-z_mean)/z_cut,2) + TMath::Power((decay->AoQ-aoq_mean)/aoq_cut,2);
		if (rad <= 1)
		{
			pid->CopyData(decay); 
			pid->TWCor();
			tree->Fill();
		}
		rad = 2;
	}

	out->cd();
	tree->Write();
	out->Close();

	TCanvas* cvs = new TCanvas("cvs", "", 500, 1500);
	cvs->Divide(1,2);
	cvs->cd(1);
	hist_Z->Draw();
	cvs->cd(2);
	hist_A->Draw();


	cvs->SaveAs(Form("../results/PID/Betadecay_%d_%d.pdf", zpro, mass));
//	theApp.Run();
	return 0;
}
