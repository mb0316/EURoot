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
EUAnaMat::EUAnaMat(const char* filename, int mode)
{
	ifstream data;
	TFile* file = new TFile(filename, "READ");

	if (mode == 0)
	{
		data.open("../calib/beta_gamma_time_cut.dat");
		for (Int_t i = 0; i < 50; i++)
		{
			data >> beta_time_cut[i];
			cout << beta_time_cut[i] << endl;
		}
		ftree = (TTree*) file->Get("tree");
		ftree->SetBranchAddress("gchit", &gchit);
		ftree->SetBranchAddress("gc_E", gc_E);
		ftree->SetBranchAddress("gc_T", gc_T);
		ftree->SetBranchAddress("addhit", &addhit);
		ftree->SetBranchAddress("add_E", add_E);
		ftree->SetBranchAddress("add_T", add_T);
		ftree->SetBranchAddress("deltaxy", &deltaxy);
		ftree->SetBranchAddress("t", &t);
		ftree->SetBranchAddress("beta_flag", &beta_flag);
	}
	if (mode == 1)
	{
		data.open("../calib/iso_gamma_time_cut.dat");
		for (Int_t i = 0; i < 50; i++)
		{
			data >> iso_time_cut[i];
			cout << iso_time_cut[i] << endl;
		}
		ftree = (TTree*) file->Get("tree");
		ftree->SetBranchAddress("gchit", &gchit);
		ftree->SetBranchAddress("gc_E", gc_E);
		ftree->SetBranchAddress("gc_T", gc_T);
	}
	
}

EUAnaMat::~EUAnaMat()
{}

void EUAnaMat::MakeBGG(Int_t &stat, Int_t &mode, Int_t &tstart, Int_t &tend, Int_t &flag)
{

	gStyle->SetOptStat(0);
	Int_t Emax;
	if (mode == 0)	Emax = 1024;
	if (mode == 1)	Emax = 2048;
	if (mode == 2)	Emax = 4096;
	if (mode == 3)	Emax = 8192;
	gg_a = new TH2D("gg_a", "", 4096, 0, Emax, 4096, 0, Emax);
	gg_g = new TH2D("gg_g", "", 4096, 0, Emax, 4096, 0, Emax);
	Long64_t nEnt = ftree->GetEntries();
	Int_t Eregion1 = 100;
	Int_t Eregion2 = 100;

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		ftree->GetEntry(iEnt);
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
							if (abs(add_T[ihit] - add_T[addhit-jhit-1]) < 200 && abs(add_T[addhit-jhit-1]) < beta_time_cut[Eregion2]  && !(add_E[ihit]==add_E[addhit-jhit-1]) && beta_flag >= flag) gg_a -> Fill(add_E[ihit], add_E[addhit-jhit-1]);
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
							if (abs(gc_T[ihit] - gc_T[gchit-jhit-1]) < 200 && abs(gc_T[gchit-jhit-1]) < beta_time_cut[Eregion2]  && !(gc_E[ihit]==gc_E[gchit-jhit-1]) && beta_flag >= flag) gg_g -> Fill(gc_E[ihit], gc_E[gchit-jhit-1]);
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
			if (t >= tstart && t <= tend && deltaxy < 2)
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
							if (abs(add_T[ihit] - add_T[addhit-jhit-1]) < 200 && abs(add_T[addhit-jhit-1]) < beta_time_cut[Eregion2]  && !(add_E[ihit]==add_E[addhit-jhit-1]) && beta_flag >= flag) gg_a -> Fill(add_E[ihit], add_E[addhit-jhit-1]);
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
							if (abs(gc_T[ihit] - gc_T[gchit-jhit-1]) < 200 && abs(gc_T[gchit-jhit-1]) < beta_time_cut[Eregion2]  && !(gc_E[ihit]==gc_E[gchit-jhit-1]) && beta_flag >= flag) gg_g -> Fill(gc_E[ihit], gc_E[gchit-jhit-1]);
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

void EUAnaMat::MakeIGG(Int_t &mode, Int_t &tend)
{

	gStyle->SetOptStat(0);
	Int_t Emax;
	if (mode == 0)	Emax = 1024;
	if (mode == 1)	Emax = 2048;
	if (mode == 2)	Emax = 4096;
	if (mode == 3)	Emax = 8192;

	gg_g = new TH2D("gg_g", "", 4096, 0, Emax, 4096, 0, Emax);
	Long64_t nEnt = ftree->GetEntries();
	Int_t Eregion1 = 100;
	Int_t Eregion2 = 100;

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		ftree->GetEntry(iEnt);
		for (Int_t ihit = 0; ihit < gchit; ihit++)
		{
			if (gc_E[ihit] < 2000)	Eregion1 = int(50 - (2000 - gc_E[ihit])/40);
			if (gc_E[ihit] >= 2000)	Eregion1 = 49;
			for (Int_t jhit = 0; jhit < gchit; jhit++)
			{
				if (gc_E[gchit-jhit-1] < 2000)	Eregion2 = int(50 - (2000 - gc_E[gchit-jhit-1])/40);
				if (gc_E[gchit-jhit-1] >= 2000)	Eregion2 = 49;

				if (gc_T[ihit] >= iso_time_cut[Eregion1] && gc_T[ihit] <= tend)
				{
					if (abs(gc_T[ihit] - gc_T[gchit-jhit-1]) < 200 && gc_T[gchit-jhit-1] >= iso_time_cut[Eregion2] && gc_T[gchit-jhit-1] <= tend  && !(gc_E[ihit]==gc_E[gchit-jhit-1])) gg_g -> Fill(gc_E[ihit], gc_E[gchit-jhit-1]);
					else continue;
				}
				else continue;
			}

		}

	}
}

void EUAnaMat::MakeBTG(Int_t &stat, Int_t &mode, Int_t &flag)
{
	gStyle->SetOptStat(0);
	Int_t Emax;
	if (mode == 0)	Emax = 1024;
	if (mode == 1)	Emax = 2048;
	if (mode == 2)	Emax = 4096;
	if (mode == 3)	Emax = 8192;

	tg_a = new TH2D("tg_a", "", 4096, 0, 4096, 4096, 0, Emax);
	tg_g = new TH2D("tg_g", "", 4096, 0, 4096, 4096, 0, Emax);
	Long64_t nEnt = ftree->GetEntries();
	Int_t Eregion = 100;

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		ftree->GetEntry(iEnt);
		if (stat == 0)
		{
			if (t>= 0 && deltaxy == 0 && beta_flag >= flag)
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
			if (t>= 0 && deltaxy < 2 && beta_flag >= flag)
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

void EUAnaMat::MakeITG(Int_t &mode1, Int_t &mode2)
{
	gStyle->SetOptStat(0);
	Int_t Emax, Tch;
	if (mode1 == 0)	Emax = 1024;
	if (mode1 == 1)	Emax = 2048;
	if (mode1 == 2)	Emax = 4096;
	if (mode1 == 3)	Emax = 8192;

	if (mode2 == 0) Tch = 1;	
	if (mode2 == 1)	Tch = 2;
	if (mode2 == 2)	Tch = 5;
	if (mode2 == 3) Tch = 10;

	tg_g = new TH2D("tg_g", "", 4096, -500, 4096*Tch-500, 4096, 0, Emax);
	Long64_t nEnt = ftree->GetEntries();

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		ftree->GetEntry(iEnt);
		for (Int_t ihit = 0; ihit < gchit; ihit++)
		{
			if (gc_T[ihit] > -500 && gc_T[ihit] < 4096*Tch-500)	tg_g -> Fill(gc_T[ihit], gc_E[ihit]);
			else continue;
		}
	}
}
