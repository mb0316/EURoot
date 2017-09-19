#include "EUAnaMat.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "TTree.h"
#include "TFile.h"
#include "TH2D.h"
#include "TStyle.h"

using namespace std;

EUAnaMat::EUAnaMat(TTree* tree, Int_t &type) //type 0 : beta decay, 1 : isomer
{
	tree->SetBranchAddress("addhit", &addhit);
	tree->SetBranchAddress("add_E", add_E);
	tree->SetBranchAddress("add_T", add_T);
	tree->SetBranchAddress("gchit", &gchit);
	tree->SetBranchAddress("gc_E", gc_E);
	tree->SetBranchAddress("gc_T", gc_T);

	if (type == 0)
	{
		tree->SetBranchAddress("t", &t);
		tree->SetBranchAddress("deltaxy", &deltaxy);
	}

	if (type == 1)
	{
		tree->SetBranchAddress("gc_Ts", gc_Ts);
		tree->SetBranchAddress("gc_Tl", gc_Tl);
	}

}

EUAnaMat::~EUAnaMat()
{}

void EUAnaMat::MakeGG(Int_t &mass, char* name, Int_t &type, Int_t &stat, Int_t &format, Int_t &tstart, Int_t &tend)
{
	gStyle->SetOptStat(0);
	TFile* file = new TFile(


}
