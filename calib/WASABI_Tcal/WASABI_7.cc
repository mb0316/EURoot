void WASABI_7()
{
	TFile* file = new TFile("../../results/AnaWASABI/AnaWASABI1060.root","read");

	TTree* tree = (TTree*) file->Get("tree");
	Int_t dssdhit, ion_x, ion_y, ion_z;
	Double_t ion_T_Y, ion_E_Y;

	tree->SetBranchAddress("dssdhit", &dssdhit);
	tree->SetBranchAddress("ion_z", &ion_z);
	tree->SetBranchAddress("ion_y", & ion_y);
	tree->SetBranchAddress("ion_T_Y", &ion_T_Y);

	TH1D* hist[40];
	for (Int_t i = 0; i < 40; i++)	hist[i] = new TH1D(Form("hist%d",i), "", 100, -300, 300);

	Long64_t nEnt = tree->GetEntries();
	cout << nEnt << " entries." << endl;

	for (Long64_t ient = 0; ient < nEnt; ient++)
	{
		tree->GetEntry(ient);
		if (ion_z == 2 && ion_y > -1 && ion_y < 40)	hist[ion_y] -> Fill(ion_T_Y);
	}

	TCanvas* cvs = new TCanvas("cvs", "", 800, 400);
	TF1* ftn = new TF1("ftn", "gaus(0)", -300, 300);
	Double_t tzero[40];
	Double_t max, mean;

	for (Int_t i = 0; i < 40; i++)
	{
		cvs->cd();
		hist[i]->Draw();
		max = hist[i]->GetMaximum();
		mean = hist[i]->GetBinCenter(hist[i]->GetMaximumBin());
		hist[i]->Fit(ftn,"MQ", "", mean - 200, mean + 200);
		cout << i << " " << ftn->GetParameter(1) << endl;
		tzero[i] = ftn->GetParameter(1);
		cvs->Update();
		cvs->Modified();
	}

	ifstream calib_ori;
	calib_ori.open("../tzero.dat");
	Double_t tzero_ori[5][100];
	Int_t ndssd, nch;
	for (Int_t i = 0; i < 500; i++)
		calib_ori >> ndssd >> nch >> tzero_ori[ndssd][nch];
	calib_ori.close();
	for (Int_t i = 0; i < 40; i++)	
		tzero_ori[2][i+60] = tzero_ori[2][i+60] + tzero[i];

	ofstream calib;
	calib.open("../tzero.dat");
	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (Int_t ich = 0; ich < 100; ich++)
			calib << idssd << "	" << ich << "	" << tzero_ori[idssd][ich] << endl;
	}

}
