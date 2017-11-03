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
	TApplication theApp("test",0,0);

	if (argc < 3 || argc > 4)
	{
		cout << "Please type 'MakeSepPID #Z #Mass'." << endl;
		return 0;
	}

	Int_t zpro = atoi(argv[1]);
	Int_t mass = atoi(argv[2]);
	Double_t aoq = double(mass)/double(zpro);

	Double_t z_sig = 0.4;
	Double_t aoq_sig = 0.0015;

	EUAnaPID* beta = new EUAnaPID("../results/BuildBetaDecay/BuildBetaDecay.root");
	TH1D* hist_Z = new TH1D("Z", "", 500, 50, 55);
	TH1D* hist_A = new TH1D("Mass", "", 600, 2.6, 2.8);
	TH2D* hist = new TH2D("t-g", "", 2000, 0, 2000, 500, -1000, 1000);

	Long64_t nEnt = beta->fData->GetEntries();

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		beta->fData->GetEntry(iEnt);
		if (beta->deltaxy == 0 && beta->t>=0)
		{
			for (Int_t ihit = 0; ihit < beta->gchit; ihit++)
			{
				hist -> Fill(beta->gc_E[ihit], beta->gc_T[ihit]);
			}
		}
		
		if (beta->AoQ > aoq-3*aoq_sig && beta->AoQ < aoq+3*aoq_sig && beta->Zpro > zpro-3*z_sig && beta->Zpro < zpro+3*z_sig)
		{
			hist_Z -> Fill(beta->Zpro);
			hist_A -> Fill(beta->AoQ);
		}
		else continue;
	}

	
	Double_t z_mean = double(zpro);
	Double_t aoq_mean = aoq;

	beta->PIDFitting(hist_Z, z_mean, z_sig);
	beta->PIDFitting(hist_A, aoq_mean, aoq_sig);

	Double_t z_cut = z_sig*2;
	Double_t aoq_cut = aoq_sig*2;

	cout << "Z mean : " << z_mean << endl;
	cout << "Z 2sigma : " << z_cut << endl;
	cout << "Mass mean : " << aoq_mean << endl;
	cout << "Mass 2sigma : " << aoq_cut << endl;

	beta->MakeOutFile(zpro, mass, z_mean, z_cut, aoq_mean, aoq_cut);

	beta->GammaTimeCut(hist);
	TGraph* graph = new TGraph();
	ofstream gtc;
	gtc.open("../calib/beta_gamma_time_cut.dat");
	for (Int_t i = 0; i < 50; i++)
	{
		graph->SetPoint(i, (40*i+40*i+40)/2, beta->timecut[i]);
		gtc << beta->timecut[i] << endl;
	}
	gtc.close();

	TCanvas* cvs = new TCanvas("cvs", "", 500, 1500);
	cvs->Divide(1,3);
	cvs->cd(1);
	hist_Z->Draw();
	cvs->cd(2);
	hist_A->Draw();
	cvs->cd(3);
	hist->Draw("colz");
	graph->Draw("L");
	graph->SetLineColor(2);


	cvs->SaveAs(Form("../results/PID/Betadecay_%d_%d.pdf", zpro, mass));

	theApp.Run();
}
