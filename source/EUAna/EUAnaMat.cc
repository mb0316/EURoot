#include "EUTree.h"
#include "EUAnaMat.h"
#include "EUTreeDecay.h"
#include "EUTreeIso.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "TTree.h"
#include "TFile.h"
#include "TH2D.h"
#include "TStyle.h"

using namespace std;

//EUAnaMat::EUAnaMat(TTree* tree, Int_t &type) //type 0 : beta decay, 1 : isomer
EUAnaMat::EUAnaMat(const char* filename, TTree* tree) : EUTreeDecay(filename)
{
	ifstream gtc;
	gtc.open("../calib/beta_gamma_time_cut.dat");
	for (Int_t i = 0; i < 50; i++)
	{
		gtc >> beta_time_cut[i];
		cout << beta_time_cut[i] << endl;
	}
}

EUAnaMat::~EUAnaMat()
{}

void EUAnaMat::MakeBGG(Int_t &stat, Int_t &tstart, Int_t &tend)
{

	gStyle->SetOptStat(0);
	gg_a = new TH2D("gg_a", "", 4096, 0, 4096, 4096, 0, 4096);
	gg_g = new TH2D("gg_g", "", 4096, 0, 4096, 4096, 0, 4096);
	Long64_t nEnt = fData->GetEntries();
	Int_t Eregion1 = 100;
	Int_t Eregion2 = 100;

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		fData->GetEntry(iEnt);
		if (stat == 0) //good statistics
		{
			if (t >= tstart && t <= tend && deltaxy == 0)
			{
				for (Int_t ihit = 0; ihit < addhit; ihit++)
				{
					if (add_E[ihit] < 2000)	Eregion1 = int(50 - (2000 - add_E[ihit])/40);
					if (add_E[ihit] >= 2000)	Eregion1 = 49;
					for (Int_t jhit = 0; jhit < addhit; jhit++)
					{
						if (add_E[addhit-jhit-1] < 2000)	Eregion2 = int(50 - (2000 - add_E[addhit-jhit-1])/40);
						if (add_E[addhit-jhit-1] >= 2000)	Eregion2 = 49;

						if (abs(add_T[ihit]) < beta_time_cut[Eregion1])
						{
							if (abs(add_T[ihit] - add_T[addhit-jhit-1]) < 200 && abs(add_T[addhit-jhit-1]) < beta_time_cut[Eregion2]  && !(add_E[ihit]==add_E[addhit-jhit-1])) gg_a -> Fill(add_E[ihit], add_E[addhit-jhit-1]);
							else continue;
						}
						else continue;
					}

				}

				for (Int_t ihit = 0; ihit < gchit; ihit++)
				{
					if (gc_E[ihit] < 2000)	Eregion1 = int(50 - (2000 - gc_E[ihit])/40);
					if (gc_E[ihit] >= 2000)	Eregion1 = 49;
					for (Int_t jhit = 0; jhit < gchit; jhit++)
					{
						if (gc_E[gchit-jhit-1] < 2000)	Eregion2 = int(50 - (2000 - gc_E[gchit-jhit-1])/40);
						if (gc_E[gchit-jhit-1] >= 2000)	Eregion2 = 49;

						if (abs(gc_T[ihit]) < beta_time_cut[Eregion1])
						{
							if (abs(gc_T[ihit] - gc_T[gchit-jhit-1]) < 200 && abs(gc_T[gchit-jhit-1]) < beta_time_cut[Eregion2]  && !(gc_E[ihit]==gc_E[gchit-jhit-1])) gg_g -> Fill(gc_E[ihit], gc_E[gchit-jhit-1]);
							else continue;
						}
						else continue;
					}

				}

			}
			else continue;
		}
		if (stat == 1) //bad statistics
		{
			if (t >= tstart && t <= tend && deltaxy <= 1)
			{
				for (Int_t ihit = 0; ihit < addhit; ihit++)
				{
					if (add_E[ihit] < 2000)	Eregion1 = int(50 - (2000 - add_E[ihit])/40);
					if (add_E[ihit] >= 2000)	Eregion1 = 49;
					for (Int_t jhit = 0; jhit < addhit; jhit++)
					{
						if (add_E[addhit-jhit-1] < 2000)	Eregion2 = int(50 - (2000 - add_E[addhit-jhit-1])/40);
						if (add_E[addhit-jhit-1] >= 2000)	Eregion2 = 49;

						if (abs(add_T[ihit]) < beta_time_cut[Eregion1])
						{
							if (abs(add_T[ihit] - add_T[addhit-jhit-1]) < 200 && abs(add_T[addhit-jhit-1]) < beta_time_cut[Eregion2]  && !(add_E[ihit]==add_E[addhit-jhit-1])) gg_a -> Fill(add_E[ihit], add_E[addhit-jhit-1]);
							else continue;
						}
						else continue;
					}

				}

				for (Int_t ihit = 0; ihit < gchit; ihit++)
				{
					if (gc_E[ihit] < 2000)	Eregion1 = int(50 - (2000 - gc_E[ihit])/40);
					if (gc_E[ihit] >= 2000)	Eregion1 = 49;
					for (Int_t jhit = 0; jhit < gchit; jhit++)
					{
						if (gc_E[gchit-jhit-1] < 2000)	Eregion2 = int(50 - (2000 - gc_E[gchit-jhit-1])/40);
						if (gc_E[gchit-jhit-1] >= 2000)	Eregion2 = 49;

						if (abs(gc_T[ihit]) < beta_time_cut[Eregion1])
						{
							if (abs(gc_T[ihit] - gc_T[gchit-jhit-1]) < 200 && abs(gc_T[gchit-jhit-1]) < beta_time_cut[Eregion2]  && !(gc_E[ihit]==gc_E[gchit-jhit-1])) gg_g -> Fill(gc_E[ihit], gc_E[gchit-jhit-1]);
							else continue;
						}
						else continue;
					}

				}

			}
			else continue;
		}
	}
}

void EUAnaMat::MakeBTG(Int_t &stat)
{
	tg_a = new TH2D("tg_a", "", 4096, 0, 4096, 4096, 0, 4096);
	tg_g = new TH2D("tg_g", "", 4096, 0, 4096, 4096, 0, 4096);
	Long64_t nEnt = fData->GetEntries();
	Int_t Eregion = 100;

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		fData->GetEntry(iEnt);
		if (stat == 0)
		{
			if (t>= 0 && deltaxy == 0)
			{
				for (Int_t ihit = 0; ihit < addhit; ihit++)
				{
					if (add_E[ihit] < 2000)  Eregion = int(50 - (2000 - add_E[ihit])/40);
					if (add_E[ihit] >= 2000) Eregion = 49;
					if (abs(add_T[ihit]) < beta_time_cut[Eregion])	tg_a -> Fill(t, add_E[ihit]);
				}
				for (Int_t ihit = 0; ihit < gchit; ihit++)
				{
					if (gc_E[ihit] < 2000)  Eregion = int(50 - (2000 - gc_E[ihit])/40);
					if (gc_E[ihit] >= 2000) Eregion = 49;
					if (abs(gc_T[ihit]) < beta_time_cut[Eregion])	tg_g -> Fill(t, gc_E[ihit]);
				}
			}
			else continue;
		}
		if (stat == 1)
		{
			if (t>= 0 && deltaxy == 1)
			{
				for (Int_t ihit = 0; ihit < addhit; ihit++)
				{
					if (add_E[ihit] < 2000)  Eregion = int(50 - (2000 - add_E[ihit])/40);
					if (add_E[ihit] >= 2000) Eregion = 49;
					if (abs(add_T[ihit]) < beta_time_cut[Eregion])	tg_a -> Fill(t, add_E[ihit]);
				}
				for (Int_t ihit = 0; ihit < gchit; ihit++)
				{
					if (gc_E[ihit] < 2000)  Eregion = int(50 - (2000 - gc_E[ihit])/40);
					if (gc_E[ihit] >= 2000) Eregion = 49;
					if (abs(gc_T[ihit]) < beta_time_cut[Eregion])	tg_g -> Fill(t, gc_E[ihit]);
				}
			}
			else continue;
		}

	}
}

