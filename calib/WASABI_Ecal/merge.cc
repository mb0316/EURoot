#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "eurica.h"
#include "wasabi.h"
#include "TTree.h"

using namespace std;

void merge()
{
	char dssdfile[100];
	char hpgefile[100];

	sprintf(dssdfile, "/home/mb0316/EURICA/EURoot/data/WASABI_Calib/WASABI_SiCalib_tot.root");
	sprintf(hpgefile, "/home/mb0316/EURICA/EURoot/data/WASABI_Calib/SiCalib_tot.root");


	TFile* gefile = new TFile(Form("%s", dssdfile), "READ");
	TFile* sifile = new TFile(Form("%s", hpgefile), "READ");

	wasabi dssd;
	eurica hpge(hpgefile);

	dssd.GetTree(dssdfile);

	map<Long64_t, Long64_t> mtsd, mtsg;
	map<Long64_t, Long64_t>::iterator imtsd, imtsg;

	map<Long64_t, Long64_t> mvdg;
	map<Long64_t, Long64_t>::iterator imvdg;

	Long64_t dEntry, gEntry;

	cout << "Start checking timestamp correlation between WASABI and EURICA" << endl;
	cout << "WASABI" << endl;
	dssd.GetTsEntry(mtsd);
	cout << "EURICA" << endl;
	hpge.GetTsEntry(mtsg);
	cout << mtsd.size() << " events for WASABI" << endl;
	cout << mtsg.size() << " events for EURICA" << endl;

	Long64_t tsl = -10;
	Long64_t tsh = 20;
	Long64_t ts1 = 0;
	Long64_t ts2 = 0;
	Int_t dts;
	cout << "Start matching TS." << endl;
	for (imtsd = mtsd.begin(); imtsd != mtsd.end(); imtsd++)
	{
		ts1 = imtsd -> first + tsl;
		ts2 = ts1 + tsh;
		imtsg = mtsg.lower_bound(ts1);
		if (imtsg != mtsg.end() && imtsg -> first < ts2)
		{
			dts = (imtsd -> first) - (imtsg -> first);
			mvdg[imtsd -> second] = imtsg -> second;
		}
	}
	cout << "The size of matching TS : " << mvdg.size() << endl;

	TFile* out = new TFile("/home/mb0316/EURICA/EURoot/data/WASABI_Calib/GeSiCorr.root", "RECREATE");
	TTree* tree = new TTree("data", "data");

	Int_t gehit;
	Int_t ge_ch[84];
	Double_t ge_E[84];
	Double_t ge_T[84];
	Int_t addhit;
	Int_t add_ch[84];
	Double_t add_E[84];
	Double_t add_T[84];
	Int_t beta_E_X[5][60];
	Int_t beta_E_Y[5][40];
	Int_t beta_E[5][100];
	Int_t beta_T_X[5][60][3];
	Int_t beta_T_Y[5][40][3];
	Int_t beta_T[5][100];

	tree -> Branch("gehit", &gehit, "gehit/I");
	tree -> Branch("ge_ch", ge_ch, "ge_ch[gehit]/I");
	tree -> Branch("ge_E", ge_E, "ge_E[gehit]/D");
	tree -> Branch("ge_T", ge_T, "ge_T[gehit]/D");
	tree -> Branch("addhit", &gehit, "addhit/I");
	tree -> Branch("add_ch", add_ch, "add_ch[addhit]/I");
	tree -> Branch("add_E", add_E, "add_E[addhit]/D");
	tree -> Branch("add_T", add_T, "add_T[addhit]/D");
	tree -> Branch("beta_E_X", beta_E_X, "beta_E_X[5][60]/I");
	tree -> Branch("beta_T_X", beta_T_X, "beta_T_X[5][60][3]/I");
	tree -> Branch("beta_E_Y", beta_E_Y, "beta_E_Y[5][40]/I");
	tree -> Branch("beta_T_Y", beta_T_Y, "beta_T_Y[5][40][3]/I");
	tree -> Branch("beta_E", beta_E, "beta_E[5][100]/I");
	tree -> Branch("beta_T", beta_T, "beta_T[5][100]/I");

	for (imvdg = mvdg.begin(); imvdg != mvdg.end(); imvdg++)
	{
		dssd.GetEntry(imvdg -> first);
		memcpy(beta_E_X, dssd.dssd_E_X, sizeof(dssd.dssd_E_X));
		memcpy(beta_T_X, dssd.dssd_T_X, sizeof(dssd.dssd_T_X));
		memcpy(beta_E_Y, dssd.dssd_E_Y, sizeof(dssd.dssd_E_Y));
		memcpy(beta_T_Y, dssd.dssd_T_Y, sizeof(dssd.dssd_T_Y));
		for (Int_t iSi = 0; iSi < 5; iSi++)
		{
			for (Int_t iSt = 0; iSt < 100; iSt++)
			{
				beta_E[iSi][iSt] = dssd.DSSD_E[iSi][iSt];
				beta_T[iSi][iSt] = dssd.DSSD_T[iSi][iSt][0];
			}

		}

		hpge.GetEntry(imvdg -> second);
		gehit = hpge.GeCluster_;
		for (Int_t i = 0; i < gehit; i++)
		{
			ge_ch[i] = hpge.GeCluster_channel[i];
			ge_E[i] = hpge.GeCluster_fEnergy[i];
			ge_T[i] = hpge.GeCluster_fTime[i];
		}
		addhit = hpge.GeAddback_;
		for (Int_t i = 0; i < addhit; i++)
		{
			add_ch[i] = hpge.GeAddback_channel[i];
			add_E[i] = hpge.GeAddback_fEnergy[i];
			add_T[i] = hpge.GeAddback_fTime[i];
		}	
		tree -> Fill();	
	}	

	
	out -> cd();
	tree -> Write();
	cout << "Tree has been saved." << endl;
	out -> Close();
	cout << "All work has been finished." << endl;


}	
