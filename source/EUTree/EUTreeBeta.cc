#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EUTreeBeta.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>


EUTreeBeta::EUTreeBeta(const char* filename, TTree *tree)
{
	if (tree == 0)
	{
		f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
		if (!f || !f->IsOpen())
		{
			f = new TFile(filename);
		}
		f->GetObject("tree",tree);

	}
	Init(tree);
}

EUTreeBeta::EUTreeBeta(TTree* tree)
{
	tree -> Branch("ts", &ts, "ts/L");
	tree -> Branch("eventid", &eventid, "eventid/I");
        tree -> Branch("AoQ", &AoQ, "AoQ/D");
        tree -> Branch("Zpro", &Zpro, "Zpro/D");
        tree -> Branch("ion_z", &ion_z, "ion_z/I");
        tree -> Branch("ion_x", &ion_x, "ion_x/I");
        tree -> Branch("ion_y", &ion_y, "ion_y/I");
        tree -> Branch("ion_E_X", &ion_E_X, "ion_E_X/D");
        tree -> Branch("ion_E_Y", &ion_E_Y, "ion_E_Y/D");
        tree -> Branch("ion_T_X", &ion_T_X, "ion_T_X/D");
        tree -> Branch("ion_T_Y", &ion_T_Y, "ion_T_Y/D");
        tree -> Branch("dssdhit", &dssdhit, "dssdhit/I");
	tree -> Branch("beta_z", beta_z, "beta_z[dssdhit]/I");
	tree -> Branch("beta_x", beta_x, "beta_x[dssdhit]/I");
	tree -> Branch("beta_y", beta_y, "beta_y[dssdhit]/I");
	tree -> Branch("beta_E_X", beta_E_X, "beta_E_X[dssdhit]/D");
	tree -> Branch("beta_E_Y", beta_E_Y, "beta_E_Y[dssdhit]/D");
	tree -> Branch("beta_E_delta", beta_E_delta, "beta_E_delta[dssdhit]/D");
	tree -> Branch("beta_T_X", beta_T_X, "beta_T_X[dssdhit]/D");
	tree -> Branch("beta_T_Y", beta_T_Y, "beta_T_Y[dssdhit]/D");

	tree -> Branch("gchit", &gchit, "gchit/I");
	tree -> Branch("gc_ch", gc_ch, "gc_ch[gchit]/I");
	tree -> Branch("gc_E", gc_E, "gc_E[gchit]/D");
	tree -> Branch("gc_T", gc_T, "gc_T[gchit]/D");
	tree -> Branch("gc_Ts", gc_Ts, "gc_Ts[gchit]/D");
	tree -> Branch("gc_Tl", gc_Tl, "gc_Tl[gchit]/D");
	tree -> Branch("addhit", &addhit, "addhit/I");
	tree -> Branch("add_ch", add_ch, "add_ch[addhit]/I");
	tree -> Branch("add_E", add_E, "add_E[addhit]/D");
	tree -> Branch("add_T", add_T, "add_T[addhit]/D");
	tree -> Branch("lbhit", &lbhit, "lbhit/I");
	tree -> Branch("lb_ch", lb_ch, "lb_ch[lbhit]/I");
	tree -> Branch("lb_E", lb_E, "lb_E[lbhit]/D");
	tree -> Branch("lb_Ts", lb_Ts, "lb_Ts[lbhit]/D");
	tree -> Branch("lb_Tl", lb_Tl, "lb_Tl[lbhit]/D");
	tree -> Branch("betaPL1_Beta_ADCL", &betaPL1_Beta_ADCL, "betaPL1_Beta_ADCL/I");
	tree -> Branch("betaPL1_Beam_ADCL", &betaPL1_Beam_ADCL, "betaPL1_Beam_ADCL/I");
	tree -> Branch("betaPL1_Beta_ADCR", &betaPL1_Beta_ADCR, "betaPL1_Beta_ADCR/I");
	tree -> Branch("betaPL1_Beam_ADCR", &betaPL1_Beam_ADCR, "betaPL1_Beam_ADCR/I");
	tree -> Branch("betaPL1_TLs", &betaPL1_TLs, "betaPL1_TLs/D");
	tree -> Branch("betaPL1_TRs", &betaPL1_TRs, "betaPL1_TRs/D");
	tree -> Branch("betaPL1_TLl", &betaPL1_TLl, "betaPL1_TLl/D");
	tree -> Branch("betaPL1_TRl", &betaPL1_TRl, "betaPL1_TRl/D");
	tree -> Branch("betaPL2_Beta_ADCL", &betaPL2_Beta_ADCL, "betaPL2_Beta_ADCL/I");
	tree -> Branch("betaPL2_Beam_ADCL", &betaPL2_Beam_ADCL, "betaPL2_Beam_ADCL/I");
	tree -> Branch("betaPL2_Beta_ADCR", &betaPL2_Beta_ADCR, "betaPL2_Beta_ADCR/I");
	tree -> Branch("betaPL2_Beam_ADCR", &betaPL2_Beam_ADCR, "betaPL2_Beam_ADCR/I");
	tree -> Branch("betaPL2_TLs", &betaPL2_TLs, "betaPL2_TLs/D");
	tree -> Branch("betaPL2_TRs", &betaPL2_TRs, "betaPL2_TRs/D");
	tree -> Branch("betaPL2_TLl", &betaPL2_TLl, "betaPL2_TLl/D");
	tree -> Branch("betaPL2_TRl", &betaPL2_TRl, "betaPL2_TRl/D");
        tree -> Branch("F11_ADC_L", &F11_ADC_L, "F11_ADC_L/I");
        tree -> Branch("F11_ADC_R", &F11_ADC_R, "F11_ADC_R/I");
        tree -> Branch("F11_TDC_L", &F11_TDC_L, "F11_TDC_L/I");
        tree -> Branch("F11_TDC_R", &F11_TDC_R, "F11_TDC_R/I");
}

EUTreeBeta::~EUTreeBeta()
{
	fData->Delete();
	delete f;
}

Int_t EUTreeBeta::GetEntry(Long64_t entry)
{
	// Read contents of entry.
	if (!fData) return 0;
	return fData->GetEntry(entry);
}

void EUTreeBeta::Init(TTree *tree)
{
	if (!tree) return;
	fData = tree;
	fCurrent = -1;
	fData->SetMakeClass(1);

	fData->SetBranchAddress("ts", &ts, &b_ts);
	fData->SetBranchAddress("eventid", &eventid, &b_eventid);
        fData->SetBranchAddress("AoQ", &AoQ, &b_AoQ);
        fData->SetBranchAddress("Zpro", &Zpro, &b_Zpro);
        fData->SetBranchAddress("ion_z", &ion_z, &b_ion_z);
        fData->SetBranchAddress("ion_x", &ion_x, &b_ion_x);
        fData->SetBranchAddress("ion_y", &ion_y, &b_ion_y);
        fData->SetBranchAddress("ion_E_X", &ion_E_X, &b_ion_E_X);
        fData->SetBranchAddress("ion_E_Y", &ion_E_Y, &b_ion_E_Y);
        fData->SetBranchAddress("ion_T_X", &ion_T_X, &b_ion_T_X);
        fData->SetBranchAddress("ion_T_Y", &ion_T_Y, &b_ion_T_X);
        fData->SetBranchAddress("dssdhit", &dssdhit, &b_dssdhit);
	fData->SetBranchAddress("beta_z", beta_z, &b_beta_z);
	fData->SetBranchAddress("beta_x", beta_x, &b_beta_x);
	fData->SetBranchAddress("beta_y", beta_y, &b_beta_y);
	fData->SetBranchAddress("beta_E_X", beta_E_X, &b_beta_E_X);
	fData->SetBranchAddress("beta_E_Y", beta_E_Y, &b_beta_E_Y);
	fData->SetBranchAddress("beta_E_delta", beta_E_delta, &b_beta_E_delta);
	fData->SetBranchAddress("beta_T_X", beta_T_X, &b_beta_T_X);
	fData->SetBranchAddress("beta_T_Y", beta_T_Y, &b_beta_T_Y);

	fData->SetBranchAddress("gchit", &gchit, &b_gchit);
	fData->SetBranchAddress("gc_ch", gc_ch, &b_gc_ch);
	fData->SetBranchAddress("gc_E", gc_E, &b_gc_E);
	fData->SetBranchAddress("gc_T", gc_T, &b_gc_T);
	fData->SetBranchAddress("gc_Ts", gc_Ts, &b_gc_Ts);
	fData->SetBranchAddress("gc_Tl", gc_Tl, &b_gc_Tl);
	fData->SetBranchAddress("addhit", &addhit, &b_addhit);
	fData->SetBranchAddress("add_ch", add_ch, &b_add_ch);
	fData->SetBranchAddress("add_E", add_E, &b_add_E);
	fData->SetBranchAddress("add_T", add_T, &b_add_T);
	fData->SetBranchAddress("lbhit", &lbhit, &b_lbhit);
	fData->SetBranchAddress("lb_ch", &lb_ch, &b_lb_ch);
	fData->SetBranchAddress("lb_E", lb_E, &b_lb_E);
	fData->SetBranchAddress("lb_Ts", lb_Ts, &b_lb_Ts);
	fData->SetBranchAddress("lb_Tl", lb_Tl, &b_lb_Tl);
	fData->SetBranchAddress("betaPL1_Beta_ADCL", &betaPL1_Beta_ADCL, &b_betaPL1_Beta_ADCL);
	fData->SetBranchAddress("betaPL1_Beam_ADCL", &betaPL1_Beam_ADCL, &b_betaPL1_Beam_ADCL);
	fData->SetBranchAddress("betaPL1_Beta_ADCR", &betaPL1_Beta_ADCR, &b_betaPL1_Beta_ADCR);
	fData->SetBranchAddress("betaPL1_Beam_ADCR", &betaPL1_Beam_ADCR, &b_betaPL1_Beam_ADCR);
	fData->SetBranchAddress("betaPL1_TLs", &betaPL1_TLs, &b_betaPL1_TLs);
	fData->SetBranchAddress("betaPL1_TRs", &betaPL1_TRs, &b_betaPL1_TRs);
	fData->SetBranchAddress("betaPL1_TLl", &betaPL1_TLl, &b_betaPL1_TLl);
	fData->SetBranchAddress("betaPL1_TRl", &betaPL1_TRl, &b_betaPL1_TRl);
	fData->SetBranchAddress("betaPL2_Beta_ADCL", &betaPL2_Beta_ADCL, &b_betaPL2_Beta_ADCL);
	fData->SetBranchAddress("betaPL2_Beam_ADCL", &betaPL2_Beam_ADCL, &b_betaPL2_Beam_ADCL);
	fData->SetBranchAddress("betaPL2_Beta_ADCR", &betaPL2_Beta_ADCR, &b_betaPL2_Beta_ADCR);
	fData->SetBranchAddress("betaPL2_Beam_ADCR", &betaPL2_Beam_ADCR, &b_betaPL2_Beam_ADCR);
	fData->SetBranchAddress("betaPL2_TLs", &betaPL2_TLs, &b_betaPL2_TLs);
	fData->SetBranchAddress("betaPL2_TRs", &betaPL2_TRs, &b_betaPL2_TRs);
	fData->SetBranchAddress("betaPL2_TLl", &betaPL2_TLl, &b_betaPL2_TLl);
	fData->SetBranchAddress("betaPL2_TRl", &betaPL2_TRl, &b_betaPL2_TRl);
        fData->SetBranchAddress("F11_ADC_L", &F11_ADC_L, &b_F11_ADC_L);
        fData->SetBranchAddress("F11_ADC_R", &F11_ADC_R, &b_F11_ADC_R);
        fData->SetBranchAddress("F11_TDC_L", &F11_TDC_L, &b_F11_TDC_L);
        fData->SetBranchAddress("F11_TDC_R", &F11_TDC_R, &b_F11_TDC_R);
}

void EUTreeBeta::GetTsEntry(std::map<Long64_t, Long64_t> &mts)
{
	Long64_t nentries = fData->GetEntriesFast();
	std::cout << nentries << std::endl;
	for (Long64_t jentry = 0; jentry<nentries; jentry++)
	{
		fData->GetEntry(jentry);
		mts.insert(std::pair<Long64_t, Long64_t> (ts, jentry));
	}
}

void EUTreeBeta::GetTsEntry(std::map<Long64_t, Long64_t> &mts1, std::map<Long64_t, Long64_t> &mts2)
{
	Long64_t nentries = fData->GetEntriesFast();
	for (Long64_t jentry = 0; jentry<nentries; jentry++)
	{
		fData->GetEntry(jentry);
		if (eventid == 0)	mts1.insert(std::pair<Long64_t, Long64_t> (ts, jentry));
		if (eventid == 1)	mts2.insert(std::pair<Long64_t, Long64_t> (ts, jentry));

	}
}

