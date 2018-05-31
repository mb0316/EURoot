void EURICA_Ecal_3(Int_t runnum)
{
	TFile* file[15];
	TTree* tree[15];

	Int_t ifile;

	Int_t gchit, gc_ch[84];
	Double_t gc_E[84];

	Int_t nfile=0;
	Int_t numfile;
	if (runnum == 1016)	numfile = 14;
	else if (runnum == 1120)	numfile = 10;
	else	numfile = 15;

	for (Int_t i = 0; i < numfile; i++)
	{
		ifile = runnum+i;
		if (ifile == 1049 || ifile == 1051 || ifile == 1095 || ifile == 1110 || ifile == 1113 || ifile == 1123) continue;
		else if (ifile >= 1130) continue;
		else if (ifile > 1023 && ifile < 1028)  continue;
		else if (ifile > 1040 && ifile < 1045)  continue;
		else
		{
			file[nfile] = new TFile(Form("~/EURICA/EURoot/results/AnaEURICA/AnaEURICA%d.root",ifile),"read");
			tree[nfile] = (TTree*) file[nfile]->Get("tree");

			tree[nfile]->SetBranchAddress("gchit", &gchit);
			tree[nfile]->SetBranchAddress("gc_ch", gc_ch);
			tree[nfile]->SetBranchAddress("gc_E", gc_E);
			nfile++;
			cout << ifile << " done." << endl;
		}
	}
	Double_t oripeak[4] = {218.6, 376.6, 511, 1460.8};
	TH1D* hist[84];
	for (Int_t i = 0; i < 84; i++)	hist[i] = new TH1D(Form("hist%d",i), "", 1500,0,1500);


	Long64_t nEnt;

	TGraph* graph = new TGraph();
	TF1* ftn = new TF1("ftn","gaus(0)+[3]*x", 0, 1500);
	TF1* ftn2 = new TF1("ftn2", "[0]*x+[1]", 0, 1500);

	for (Int_t i = 0; i < nfile; i++)
	{
		nEnt = tree[i]->GetEntries();
		cout << i << " " << nEnt << endl;
		for (Long64_t ient = 0; ient < nEnt; ient++)
		{
			tree[i]->GetEntry(ient);
			for (Int_t ihit = 0; ihit < gchit; ihit++)	hist[gc_ch[ihit]]->Fill(gc_E[ihit]);
		}
	}

	TCanvas* cvs = new TCanvas("cvs", "", 800, 400);
	cvs->SetLogy();
	TCanvas* cvs2 = new TCanvas("cvs2", "", 800, 600);
	ofstream calibfile;
	if (runnum == 1016)	calibfile.open (Form("BT_Ecal/%d.dat", 1020));
	else	calibfile.open (Form("BT_Ecal/%d.dat", runnum));

	for (Int_t ich = 0; ich < 84; ich++)
	{
		for (Int_t i= 0; i < 4; i++)
		{
			hist[ich]->GetXaxis()->SetRangeUser(oripeak[i]-10, oripeak[i]+10);
//		ftn->SetParameter(0, hist->GetBinContent(int(oripeak[i])));
			ftn->SetParameter(0, hist[ich]->GetMaximum());
			ftn->SetParameter(1, oripeak[i]);
			ftn->SetParameter(2, 0.8);
			ftn->SetParLimits(2, 0.5, 1.5);

			if (i == 3)	ftn->SetParLimits(0, 0, 1000000);
			hist[ich]->Fit(ftn, "MQ", "", oripeak[i] - 5, oripeak[i] + 7);

//			cout << oripeak[i] << " " << ftn->GetParameter(1) << endl;
/*
			cvs->cd();
			cvs->Update();
			cvs->Modified();
			sleep(1);
*/
			graph->SetPoint(i, oripeak[i], ftn->GetParameter(1));
		}

		graph->Draw();

		ftn2->SetParameters(1.0, 0.0);

		graph->Fit(ftn2, "MQ");

		cout << ich << " " << ftn2->GetParameter(0) << " " << ftn2->GetParameter(1) << endl;
		calibfile << ich << "	" << ftn2->GetParameter(0) << "	" << ftn2->GetParameter(1) << endl;
	}
}
