void EURICA_Ts_1()
{
	Int_t gchit, gc_ch[84];
	Double_t gc_E[84], gc_Ts[84];

	TFile* file = new TFile("../../results/BuildIsoDecay/BuildIsoDecay.root", "read");
	TTree* tree = (TTree*) file->Get("tree");
	tree->SetBranchAddress("gchit", &gchit);
	tree->SetBranchAddress("gc_ch", gc_ch);
	tree->SetBranchAddress("gc_E", gc_E);
	tree->SetBranchAddress("gc_Ts", gc_Ts);
	

	TH2D* hist[84];
	for (Int_t i = 0; i < 84; i++)	hist[i] = new TH2D(Form("hist%d", i), "", 1000, 0, 2000, 1000, 0, 2000);

	Long64_t nEnt = tree->GetEntries();

	for (Long64_t ient = 0; ient < nEnt; ient++)
	{
		tree->GetEntry(ient);
		for (Int_t ihit = 0; ihit < gchit; ihit++)	hist[gc_ch[ihit]] -> Fill(gc_E[ihit], gc_Ts[ihit]);
	}

	TFile* out = new TFile("TWhist_Ts.root", "RECREATE");
	out->cd();
	
	for (Int_t i = 0; i < 84; i++)	hist[i] -> Write();

	out->Close();
}
