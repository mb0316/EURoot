#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EUAna.h"
#include "EUAnaDecay.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "EUAnaPID.h"
#include "EUTreeDecay.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TF1.h"
#include "TTree.h"
#include "TString.h"
#include "TObjArray.h"
#include "TObjString.h"

using namespace std;
/*
EUAnaPID::EUAnaPID(const char* filename, TTree* tree):EUTreeDecay(filename)
{}
*/
EUAnaPID::EUAnaPID(const char* filename)
{
	TString filenameWithPath = filename;
	TObjArray* decomposite = filenameWithPath.Tokenize("/");
	TString openFile = ((TObjString *) decomposite ->Last()) -> GetString();

	TFile* file = new TFile(filename, "READ");
	ftree = (TTree*) file -> Get("tree");

	if (openFile == "BuildBetaDecay.root")
	{
		ftree->SetBranchAddress("t", &t);
		ftree->SetBranchAddress("deltaxy", &deltaxy);
		ftree->SetBranchAddress("Zpro", &Zpro);
		ftree->SetBranchAddress("AoQ", &AoQ);
		ftree->SetBranchAddress("gchit", &gchit);
		ftree->SetBranchAddress("gc_E", &gc_E);
		ftree->SetBranchAddress("gc_T", &gc_T);
	}
	if (openFile == "BuildIsoDecay.root")
	{
		ftree->SetBranchAddress("Zpro", &Zpro);
		ftree->SetBranchAddress("AoQ", &AoQ);
		ftree->SetBranchAddress("gchit", &gchit);
		ftree->SetBranchAddress("gc_E", gc_E);
		ftree->SetBranchAddress("gc_T", gc_T);
	}
}

EUAnaPID::~EUAnaPID()
{}

void EUAnaPID::PIDFitting(TH1D* hist, Double_t &mean, Double_t &sig)
{
	Double_t ampl = hist->GetMaximum();
	TF1* gaus = new TF1("gaussian", "gaus(0)", mean - mean/5, mean + mean/5);
	gaus -> SetParameters(ampl, mean, sig);
	hist->Fit(gaus, "MQ", "", mean-sig, mean+sig);
	mean = gaus -> GetParameter(1);
	sig = gaus -> GetParameter(2);
}

void EUAnaPID::MakeOutFile(const char* filename, Int_t &z, Int_t &mass, Double_t &zpro, Double_t &zpro_cut, Double_t &aoq, Double_t &aoq_cut)
{
	TString filenameWithPath = filename;
	TObjArray* decomposite = filenameWithPath.Tokenize("/");
	TString openFile = ((TObjString *) decomposite ->Last()) -> GetString();

	TFile* read = new TFile(filename, "READ");
	TFile* out;
	if (openFile == "BuildBetaDecay.root")	out  = new TFile(Form("../results/PID/Betadecay_%d_%d.root", z, mass), "RECREATE");
	if (openFile == "BuildIsoDecay.root")	out  = new TFile(Form("../results/PID/Isomerdecay_%d_%d.root", z, mass), "RECREATE");
	TTree* tree;
	tree = (TTree*) read -> Get("tree");
	tree -> CopyTree(Form("(AoQ <= %f) && (AoQ >= %f) && (Zpro <= %f) && (Zpro >= %f)", aoq + aoq_cut, aoq - aoq_cut, zpro + zpro_cut, zpro - zpro_cut)) -> Write();
	out -> Close();
}

void EUAnaPID::GammaTimeCut(TH2D* hist)
{
	TH1D* pro;
	TF1* gaus = new TF1("gaussian", "gaus(0)", -500, 500);
	
	for (Int_t i = 0; i < 50; i++)
	{
		pro = hist->ProjectionY("pro", 40*i, 40*i+40);
		gaus->SetParameters(pro->GetMaximum(), 0, 10.0);
		pro->Fit(gaus, "MQ", "", -250, 250);
		timecut[i] = 2*(gaus->GetParameter(2));
		pro->Clear();
		cout << 40*i << " keV time cut condition : " << timecut[i] << endl;
	}
}
