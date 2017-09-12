#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "eurica.h"
#include "wasabi.h"
#include "bigrips.h"
#include "betamerge.h"
#include "isomerge.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "BMana.h"

using namespace std;

int main(int argc, char* argv[])
//int main()
{

	if (argc < 2)
	{
		cout << "Please type 'Isomermerge #run'." << endl;
		return 0;
	}


	int runB = atoi(argv[1]);
//	int runD = atoi(argv[2]);
//	int runE = atoi(argv[2]);
	char bigripsfile[100];
	char dssdfile[100];
	char hpgefile[100];

	sprintf(bigripsfile, "../data/te142/rootfiles/bigrips/yagi/bigrips_run%04d.root", runB);
	sprintf(dssdfile, "../data/te142/rootfiles/sistopper/WASABI%04d.root", runB);
	sprintf(hpgefile, "../data/te142/rootfiles/euroball/go4_%04d.root", runB);
	wasabi dssd;
	eurica hpge;
	bigrips beam;
	BMana ana;


	dssd.GetTree(dssdfile);
	hpge.GetTree(hpgefile);
	beam.GetTree(bigripsfile);

//	map<Long64_t, Long64_t> mtsb, mtsg;
	map<Long64_t, Long64_t> mtsb, mtsd, mtsg;
	map<Long64_t, Long64_t>::iterator imtsb;
	map<Long64_t, Long64_t>::iterator imtsd;
	map<Long64_t, Long64_t>::iterator imtsg;

	map<Long64_t, Long64_t> mvdg;
	map<Long64_t, Long64_t>::iterator imvdg;
	map<Long64_t, pair<Long64_t, Long64_t> > mts;
	map<Long64_t, pair<Long64_t, Long64_t> >::iterator imts;

//	Long64_t dEntry, gEntry, bEntry;

//	TH1D* hist_DGts = new TH1D("DSSD_GE_TS", "", 20, -10, 10);
//	TH1D* hist_BDts = new TH1D("BEAM_DSSD_TS", "", 60, -30, 30);


	cout << "Start checking timestamp correlation between BigRIPS and EURICA" << endl;
	cout << "BigRIPS" << endl;
	beam.GetTsEntry(mtsb);
	cout << "WASABI" << endl;
	dssd.GetTsEntry(mtsd);
	cout << "EURICA" << endl;
	hpge.GetTsEntry(mtsg);
	cout << mtsb.size() << " events for BigRIPS" << endl;
	cout << mtsd.size() << " events for WASABI" << endl;
	cout << mtsg.size() << " events for EURICA" << endl;

	Long64_t ts1l = -10;
	Long64_t ts2l = -100;
	Long64_t ts1h = 10;
	Long64_t ts2h = 100;
	Long64_t ts11 = 0;
	Long64_t ts12 = 0;
	Long64_t ts21 = 0;
	Long64_t ts22 = 0;
//	Int_t dtsBD, dtsDG;
	cout << "Start matching TS." << endl;
/*
	for (imtsg = mtsg.begin(); imtsg != mtsg.end(); imtsg++)
	{
		ts11 = imtsg -> first + ts2l;
		ts21 = imtsg -> first + ts2h;
		imtsb = mtsb.lower_bound(ts11);
		if (imtsb != mtsb.end() && imtsb -> first < ts21)
		{
			mts[imtsb -> second] = imtsg -> second;
		}
	}
*/
	for (imtsd = mtsd.begin(); imtsd != mtsd.end(); imtsd++)
	{
		ts11 = imtsd -> first + ts1l;
		ts21 = imtsd -> first + ts1h;
		imtsg = mtsg.lower_bound(ts11);
		if (imtsg != mtsg.end() && imtsg -> first < ts21)
		{
			ts12 = imtsd -> first + ts2l;
			ts22 = imtsd -> first + ts2h;
			imtsb = mtsb.lower_bound(ts12);
			if (imtsb != mtsb.end() && imtsb -> first < ts22)
			{
//				dts = (imtsd -> first) - (imtsg -> first);
//				mvdg[imtsd -> second] = imtsg -> second;
				mts[imtsb -> second] = pair<Long64_t, Long64_t> (imtsd -> second, imtsg -> second);
//				dtsBD = (imtsb -> first) - (imtsd -> first);
//				dtsDG = (imtsd -> first) - (imtsg -> first);
//				hist_BDts -> Fill(dtsBD);
//				hist_DGts -> Fill(dtsDG);
			}
		}
	}

	cout << "The size of matching TS : " << mts.size() << endl;
/*
	TCanvas* c1 = new TCanvas("c1", "", 1000, 700);
	c1 -> Divide(2, 1);
	c1 -> cd(1);
	hist_BDts -> Draw();
	c1 -> cd(2);
	hist_DGts -> Draw();
*/
	TFile* out = new TFile(Form("./IsoMergeData/IsoMerge%04d.root", runB), "RECREATE");
//	TFile* out = new TFile(Form("IsoMerge%04d.root", runB), "RECREATE");
	TTree* tree = new TTree("tree", "tree");

	cout << "Start analyzing and copying data." << endl;

	ana.MakeIsomerTree(tree);
	ana.GetCalib();
	Long64_t ent = 0;
	for (imts = mts.begin(); imts != mts.end(); imts++)
	{
		ent++;
		if (ent%1000 == 0)	cout << ent << " entry." << endl;
		dssd.GetEntry(imts->second.first);
		ana.CopyTS(dssd);
		ana.CopyPL(dssd);
		if (ana.F11_PLl > -50000 && ana.F11_PLr > -50000 && ana.vetoPL1 < -10000 && ana.vetoPL2 < -10000)
		{
			beam.GetEntry(imts->first);
			ana.CopyBigRIPS(beam);
			hpge.GetEntry(imts->second.second);
			ana.CopyEURICA(hpge);
//			ana.Slewcor();
//			ana.GeTDCoffset();
			tree -> Fill();	
		}
		else continue;
	}	

	
	out -> cd();
	tree -> Write();
	cout << "Tree has been saved." << endl;
	out -> Close();
	cout << "All work has been finished." << endl;

}	
