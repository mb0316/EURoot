#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "EUTreeGe.h"
#include "EUTreeSi.h"
#include "EUTreeBeam.h"
#include "EUAnaBeta.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "EUAnaBeta.h"
#include "TObjectTable.h"
#include "TSystem.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Please type 'betamerge #run'." << endl;
		return 0;
	}


	int runB = atoi(argv[1]);
	char bigripsfile[100];
	char dssdfile[100];
	char hpgefile[100];

	sprintf(bigripsfile, "../data/bigrips_run%04d.root", runB);
	sprintf(dssdfile, "../data/WASABI%04d.root", runB);
	sprintf(hpgefile, "../data/go4_%04d.root", runB);

	EUTreeSi dssd;
	EUTreeGe hpge;
	EUTreeBeam beam;
	EUAnaBeta ana;


	dssd.GetTree(dssdfile);
	hpge.GetTree(hpgefile);
	beam.GetTree(bigripsfile);

	map<Long64_t, Long64_t> mtsb;	//beam timestamp, first : ts, second : entry
	map<Long64_t, Long64_t> mtsd;	//dssd timestamp, first : ts, second : entry
	map<Long64_t, Long64_t> mtsg;	//ge timestamp, firt : ts, second : entry
	map<Long64_t, Long64_t>::iterator imtsb;
	map<Long64_t, Long64_t>::iterator imtsd;
	map<Long64_t, Long64_t>::iterator imtsg;

	map<Long64_t, Long64_t> mvdg;	//dssd & ge timestamp, first : dssd entry, second : ge entry
	map<Long64_t, Long64_t>::iterator imvdg;

	map<Long64_t, Long64_t> mvtot;	//beam & dssd timestamp, first : dssd entry, second : beam entry
	map<Long64_t, Long64_t>::iterator imvtot;

	map<Long64_t, pair<Long64_t, Long64_t>> tstot; //beam & dssd & ge timestamp, first : dssd entry, second.first : beam entry, second.second : ge entry
	map<Long64_t, pair<Long64_t, Long64_t>>::iterator itstot;

	//	FILE *cintout = fopen("cint.out", "a+t");
	//	gSystem->RedirectOutput("cint.out", "a");

	cout << "Start checking timestamp correlation between BigRIPS, WASABI and EURICA" << endl;
	cout << "BigRIPS" << endl;
	beam.GetTsEntry(mtsb);
	//	gObjectTable->Print();
	cout << "WASABI" << endl;
	dssd.GetTsEntry(mtsd);
	//	gObjectTable->Print();
	cout << "EURICA" << endl;
	hpge.GetTsEntry(mtsg);
	//	gObjectTable->Print();
	cout << mtsb.size() << " events for BigRIPS" << endl;
	cout << mtsd.size() << " events for WASABI" << endl;
	cout << mtsg.size() << " events for EURICA" << endl;

	//	gSystem->RedirectOutput(0);

	Long64_t ts_dg_l = -10;		//timestamp low limit window for dssd & gc
	Long64_t ts_bd_l = -100;	//timestamp low limit window for beam & dssd
	Long64_t ts_dg_h = 10;		//timestamp high limit window for dssd & gc
	Long64_t ts_bd_h = 100;		//timestamp high limit window for beam & dssd
	cout << "Start matching TS." << endl;

	// timestamp correlation between dssd & ge
	for (imtsd = mtsd.begin(); imtsd != mtsd.end(); imtsd++)
	{
		imtsg = mtsg.lower_bound(imtsd -> first + ts_dg_l);
		if (imtsg != mtsg.end() && imtsg -> first < imtsd -> first + ts_dg_h)	mvdg[imtsd -> second] = imtsg -> second;
	}
	mtsg.clear();

	// timestamp correlation between beam & dssd
	for (imtsd = mtsd.begin(); imtsd != mtsd.end(); imtsd++)
	{
		imtsb = mtsb.lower_bound(imtsd -> first + ts_bd_l);
		if (imtsb != mtsb.end() && imtsb -> first < imtsd->first+ts_bd_h)	mvtot[imtsd -> second] = imtsb -> second;
	}
	mtsb.clear();
	mtsd.clear();

	// total timestamp correlation
	for (imvtot = mvtot.begin(); imvtot != mvtot.end(); imvtot++)
	{
		imvdg = mvdg.find(imvtot->first);
		if (imvdg != mvdg.end())	tstot[imvtot->first] = pair<Long64_t, Long64_t> (imvtot->second, imvdg->second);
	}

	cout << "The size of matching TS between WASABI & EURICA : " << mvdg.size() << endl;
	cout << "The size of matching TS between BigRIPS & WASABI : " << mvtot.size() << endl;
	cout << "The size of matching TS : " << tstot.size() << endl;

	mvtot.clear();

	TFile* out = new TFile(Form("../results/BetaMergeData/BetaMerge%04d.root", runB), "RECREATE");
	TTree* tree = new TTree("tree", "tree");

	cout << "Start analyzing and copying data." << endl;

	ana.MakeBetaTree(tree);
	ana.GetCalib();
	Long64_t ent = 0;

	for (imvdg = mvdg.begin(); imvdg != mvdg.end(); imvdg++)
	{
		ent++;
		if (ent%1000 == 0)
		{
			printf("%lld entry done.", ent);
			fflush(stdout);
			printf("\r");
		}
		ana.ResetPID();
		dssd.GetEntry(imvdg->first);
		ana.CopyTS(dssd);
		ana.CopyPL(dssd);
		itstot = tstot.find(imvdg->first);
		if ((itstot != tstot.end()) && ((ana.F11_PLl > -50000 && ana.F11_PLr > -50000) || (ana.F7_PLl > -50000 && ana.F7_PLr > -50000)) && (ana.vetoPL1 < -10000 || ana.vetoPL2 < -10000))
		{
			hpge.GetEntry(itstot->second.second);
			ana.ResetEURICA();
			ana.CopyEURICA(hpge);
			ana.eventid = 0;
			ana.GetIonPos(dssd);
			beam.GetEntry(itstot->second.first);
			ana.CopyBigRIPS(beam);
			tree -> Fill();	
		}
		//			else if (ana.F11_PLr < -50000 || ana.F11_PLl < -50000)
		//			if (dssd.IF_BETA == 1)
		else if (ana.vetoPL1 < -10000 || ana.vetoPL2 < -10000)
		{
			ana.eventid = 1;
			ana.ResetDSSD();
			ana.temp_beta.clear();
			ana.GetBetaPos(dssd);
			hpge.GetEntry(imvdg->second);
			for (Int_t ihit = 0; ihit < 5; ihit++)
			{
				//					dssd.GetEntry(imtsd -> second);
				//					ana.beta_z = ana.temp_beta_z[ihit];
				ana.itemp_beta = ana.temp_beta.find(ihit);
				if (ana.itemp_beta != ana.temp_beta.end())
				{
					ana.beta_z = ihit;
					for (UInt_t jhit = 0; jhit < ana.itemp_beta -> second.size(); jhit++)
					{
						ana.beta_x = ana.itemp_beta -> second[jhit].first;
						ana.beta_y = ana.itemp_beta -> second[jhit].second;
						ana.beta_E_X = dssd.dssd_E_X[ana.beta_z][ana.beta_x];
						ana.beta_E_Y = dssd.dssd_E_Y[ana.beta_z][ana.beta_y];
						ana.beta_T_X = dssd.dssd_T_Y[ana.beta_z][ana.beta_x][0];
						ana.beta_T_Y = dssd.dssd_T_Y[ana.beta_z][ana.beta_y][0];
						ana.ResetEURICA();
						ana.CopyEURICA(hpge);
						tree -> Fill();
					}
				}
			}

		}
	}	

	out -> cd();
	tree -> Write();
	cout << "Tree has been saved." << endl;
	out -> Close();
	cout << "All work has been finished." << endl;
}	
