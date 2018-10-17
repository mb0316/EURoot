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

void EUAnaMat::MakeBGG(Int_t &stat, Int_t &mode, Int_t &tstart, Int_t &tend)
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

	if (stat == 0)	delta_cut = 1;
	else if (stat == 1)	delta_cut = 2;

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		ftree->GetEntry(iEnt);
		if (t >= tstart && t <= tend && deltaxy < delta_cut && gchit<50)
		{
			for (Int_t ihit = 0; ihit < addhit; ihit++)
			{
				if (add_E[ihit] < 2000)	Eregion1 = int(50 - (2000 - add_E[ihit])/40);
				else if (add_E[ihit] >= 2000)	Eregion1 = 49;
				for (Int_t jhit = 0; jhit < addhit; jhit++)
				{
					if (add_E[addhit-jhit-1] < 2000)	Eregion2 = int(50 - (2000 - add_E[addhit-jhit-1])/40);
					else if (add_E[addhit-jhit-1] >= 2000)	Eregion2 = 49;

					if (abs(add_T[ihit]) < beta_time_cut[Eregion1] && abs(add_T[ihit] - add_T[addhit-jhit-1]) < 200 && abs(add_T[addhit-jhit-1]) < beta_time_cut[Eregion2]  && !(add_E[ihit]==add_E[addhit-jhit-1])) gg_a -> Fill(add_E[ihit], add_E[addhit-jhit-1]);
				}

			}

			for (Int_t ihit = 0; ihit < gchit; ihit++)
			{
				if (gc_E[ihit] < 2000)	Eregion1 = int(50 - (2000 - gc_E[ihit])/40);
				else if (gc_E[ihit] >= 2000)	Eregion1 = 49;
				for (Int_t jhit = 0; jhit < gchit; jhit++)
				{
					if (gc_E[gchit-jhit-1] < 2000)	Eregion2 = int(50 - (2000 - gc_E[gchit-jhit-1])/40);
					else if (gc_E[gchit-jhit-1] >= 2000)	Eregion2 = 49;

					if (abs(gc_T[ihit]) < beta_time_cut[Eregion1] && abs(gc_T[ihit] - gc_T[gchit-jhit-1]) < 200 && abs(gc_T[gchit-jhit-1]) < beta_time_cut[Eregion2]  && !(gc_E[ihit]==gc_E[gchit-jhit-1])) gg_g -> Fill(gc_E[ihit], gc_E[gchit-jhit-1]);
				}

			}

		}
	}
}

void EUAnaMat::MakeBIGG(Int_t &stat, Int_t &mode, Int_t &tstart, Int_t &tend)
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

	if (stat == 0)	delta_cut = 1;
	else if (stat == 1)	delta_cut = 2;

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		ftree->GetEntry(iEnt);
		if (t >= tstart && t <= tend && deltaxy < delta_cut && gchit<50)
		{
			for (Int_t ihit = 0; ihit < addhit; ihit++)
			{
				if (add_E[ihit] < 2000)	Eregion1 = int(50 - (2000 - add_E[ihit])/40);
				else if (add_E[ihit] >= 2000)	Eregion1 = 49;
				for (Int_t jhit = 0; jhit < addhit; jhit++)
				{
					if (add_E[addhit-jhit-1] < 2000)	Eregion2 = int(50 - (2000 - add_E[addhit-jhit-1])/40);
					else if (add_E[addhit-jhit-1] >= 2000)	Eregion2 = 49;

					if (add_T[ihit] > beta_time_cut[Eregion1] && add_T[ihit] < 100000 && abs(add_T[ihit] - add_T[addhit-jhit-1]) < 200 && add_T[addhit-jhit-1] > beta_time_cut[Eregion2] && add_T[addhit-jhit-1] < 100000 && !(add_E[ihit]==add_E[addhit-jhit-1])) gg_a -> Fill(add_E[ihit], add_E[addhit-jhit-1]);
				}

			}

			for (Int_t ihit = 0; ihit < gchit; ihit++)
			{
				if (gc_E[ihit] < 2000)	Eregion1 = int(50 - (2000 - gc_E[ihit])/40);
				else if (gc_E[ihit] >= 2000)	Eregion1 = 49;
				for (Int_t jhit = 0; jhit < gchit; jhit++)
				{
					if (gc_E[gchit-jhit-1] < 2000)	Eregion2 = int(50 - (2000 - gc_E[gchit-jhit-1])/40);
					else if (gc_E[gchit-jhit-1] >= 2000)	Eregion2 = 49;

					if (gc_T[ihit] > beta_time_cut[Eregion1] && gc_T[ihit] < 100000 && abs(gc_T[ihit] - gc_T[gchit-jhit-1]) < 200 && gc_T[gchit-jhit-1] > beta_time_cut[Eregion2] && gc_T[gchit-jhit-1] < 100000 && !(gc_E[ihit]==gc_E[gchit-jhit-1])) gg_g -> Fill(gc_E[ihit], gc_E[gchit-jhit-1]);
				}

			}

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

void EUAnaMat::MakeBTG(Int_t &stat, Int_t &mode)
{
	gStyle->SetOptStat(0);
	Int_t Emax;
	if (mode == 0)	Emax = 1024;
	if (mode == 1)	Emax = 2048;
	if (mode == 2)	Emax = 4096;
	if (mode == 3)	Emax = 8192;

	if (stat == 0)	delta_cut = 1;
	else if (stat == 1) delta_cut = 2;

	tg_a = new TH2D("tg_a", "", 4096, 0, 4096, 4096, 0, Emax);
	tg_g = new TH2D("tg_g", "", 4096, 0, 4096, 4096, 0, Emax);
	gcT_E = new TH2D("gcT_E","",1000,0,1000,500,-1000,1000);
	addT_E = new TH2D("addT_E","",1000,0,1000,500,-1000,1000);
	Long64_t nEnt = ftree->GetEntries();
	Int_t Eregion = 100;

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		ftree->GetEntry(iEnt);
		if (t>= 0 && deltaxy < delta_cut)
		{
			for (Int_t ihit = 0; ihit < addhit; ihit++)
			{
				if (add_E[ihit] < 2000)  Eregion = int(50 - (2000 - add_E[ihit])/40);
				if (add_E[ihit] >= 2000) Eregion = 49;
				if (abs(add_T[ihit]) < beta_time_cut[Eregion])
				{
					tg_a -> Fill(t, add_E[ihit]);
					addT_E->Fill(add_E[ihit], add_T[ihit]);
				}
			}
			for (Int_t ihit = 0; ihit < gchit; ihit++)
			{
				if (gc_E[ihit] < 2000)  Eregion = int(50 - (2000 - gc_E[ihit])/40);
				if (gc_E[ihit] >= 2000) Eregion = 49;
				if (abs(gc_T[ihit]) < beta_time_cut[Eregion])
				{
					tg_g -> Fill(t, gc_E[ihit]);
					gcT_E->Fill(gc_E[ihit], gc_T[ihit]);
				}
			}
		}
		else continue;
	}
}

void EUAnaMat::MakeBITG(Int_t &stat, Int_t &mode)
{
	gStyle->SetOptStat(0);
	Int_t Emax;
	if (mode == 0)	Emax = 1024;
	if (mode == 1)	Emax = 2048;
	if (mode == 2)	Emax = 4096;
	if (mode == 3)	Emax = 8192;

	if (stat == 0)	delta_cut = 1;
	else if (stat == 1) delta_cut = 2;

	tg_a = new TH2D("tg_a", "", 4096, 0, 10240, 4096, 0, Emax);
	tg_g = new TH2D("tg_g", "", 4096, 0, 10240, 4096, 0, Emax);
	gcT_E = new TH2D("gcT_E","",1000,0,1000,500,-1000,1000);
	addT_E = new TH2D("addT_E","",1000,0,1000,500,-1000,1000);
	Long64_t nEnt = ftree->GetEntries();

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		ftree->GetEntry(iEnt);
		if (t>= 0 && deltaxy < delta_cut)
		{
			for (Int_t ihit = 0; ihit < addhit; ihit++)
			{
				if (add_T[ihit] > 300 && add_T[ihit] < 10240)
				{
					tg_a -> Fill(add_T[ihit], add_E[ihit]);
					addT_E->Fill(add_E[ihit], add_T[ihit]);
				}
			}
			for (Int_t ihit = 0; ihit < gchit; ihit++)
			{
				if (gc_T[ihit] > 300 && gc_T[ihit] < 10240)
				{
					tg_g -> Fill(gc_T[ihit], gc_E[ihit]);
					gcT_E->Fill(gc_E[ihit], gc_T[ihit]);
				}
			}
		}
		else continue;
	}
}

void EUAnaMat::MakeITG(Int_t &mode1)
{
	gStyle->SetOptStat(0);
	Int_t Emax, Tch;
	if (mode1 == 0)	Emax = 1024;
	if (mode1 == 1)	Emax = 2048;
	if (mode1 == 2)	Emax = 4096;
	if (mode1 == 3)	Emax = 8192;

	tg_g = new TH2D("tg_g", "", 4096, 0, 10240, 4096, 0, Emax);
	Long64_t nEnt = ftree->GetEntries();

        Int_t Eregion = 100;

	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		ftree->GetEntry(iEnt);
		for (Int_t ihit = 0; ihit < gchit; ihit++)
		{
                        if (gc_E[ihit] < 2000)  Eregion = int(50 - (2000 - gc_E[ihit])/40);
                        if (gc_E[ihit] >= 2000) Eregion = 49;
			if (gc_T[ihit] < 10240 && gc_T[ihit] >= iso_time_cut[Eregion])	tg_g -> Fill(gc_T[ihit], gc_E[ihit]);
			else continue;
		}
	}
}

void EUAnaMat::MakeDecayCurve(Int_t &stat)
{
	if (stat == 0)	delta_cut = 1;
	else if (stat == 1) delta_cut = 2;

	decay = new TH1F("hist_decay", "", 5000,0,5000);

	Long64_t nEnt = ftree->GetEntries();
	Int_t Eregion = 100;
	for (Long64_t iEnt = 0; iEnt < nEnt; iEnt++)
	{
		ftree->GetEntry(iEnt);
		if (t>= 0 && deltaxy < delta_cut)
		{
			for (Int_t ihit = 0; ihit < addhit; ihit++)
			{
				if (add_E[ihit] < 2000)  Eregion = int(50 - (2000 - add_E[ihit])/40);
				if (add_E[ihit] >= 2000) Eregion = 49;
				if (abs(add_T[ihit]) < beta_time_cut[Eregion]) decay->Fill(t);
			}
		}
		else continue;
	}
}
