void EURICA_3()
{
	TFile* file = new TFile("../../results/BuildBetaDecay/BuildBetaDecay.root","read");
	TTree* tree = (TTree*) file->Get("tree");

	Int_t gchit, gc_ch[84];
	Double_t gc_E[84], gc_T[84];

	tree->SetBranchAddress("gchit", &gchit);
	tree->SetBranchAddress("gc_ch", gc_ch);
	tree->SetBranchAddress("gc_E", gc_E);
	tree->SetBranchAddress("gc_T", gc_T);

	Int_t temp_ch;
	Double_t gcT_beta_TW[84][3];
	ifstream calib;
	calib.open ("gcT_beta_TW.dat");
	
	for (Int_t i = 0; i < 84; i++)	calib >> temp_ch >> gcT_beta_TW[i][0] >> gcT_beta_TW[i][1] >> gcT_beta_TW[i][2];

	TH2D* hist = new TH2D("hist", "", 2000,0,2000,500,-1000,1000);
	Long64_t nEnt = tree->GetEntries();
	for (Long64_t ient = 0; ient < nEnt; ient++)
	{
		tree->GetEntry(ient);
		for (Int_t ihit = 0; ihit < gchit; ihit++)
		{
			if (gc_T[ihit] > -500E3 && gc_T[ihit] < 500E3)    gc_T[ihit] = -(gc_T[ihit] - gcT_beta_TW[gc_ch[ihit]][0] - gcT_beta_TW[gc_ch[ihit]][1]*TMath::Power(gc_E[ihit], -gcT_beta_TW[gc_ch[ihit]][2]));
			hist->Fill(gc_E[ihit], gc_T[ihit]);
		}
	}

	TH1D* pro;
	TF1* gaus = new TF1("gaussian", "gaus(0)", -500, 500);
	Double_t timecut[50];

	for (Int_t i = 0; i < 50; i++)
	{
		pro = hist->ProjectionY("pro", 40*i, 40*i+40);
		gaus->SetParameters(pro->GetMaximum(), 0, 10.0);
		pro->Fit(gaus, "MQ", "", -250, 150);
		timecut[i] = 4*(gaus->GetParameter(2));
		pro->Clear();
		cout << 40*i << " keV time cut condition : " << timecut[i] << endl;
	}
	TGraph* graph = new TGraph();
	ofstream gtc;
	gtc.open("beta_gamma_time_cut.dat");
	for (Int_t i = 0; i < 50; i++)
	{
		graph->SetPoint(i, (40*i+40*i+40)/2, timecut[i]);
		gtc << timecut[i] << endl;
	}
	gtc.close();

	TCanvas* cvs = new TCanvas("cvs", "", 800, 400);
	hist->Draw("colz");
	graph->Draw("L");
	graph->SetLineColor(2);
	graph->SetLineWidth(3);
	
}
