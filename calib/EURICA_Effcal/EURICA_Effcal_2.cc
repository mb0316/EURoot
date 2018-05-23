#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TGraphErrors.h"
#include "TF1.h"


void EURICA_Effcal_2()
{
	gStyle -> SetOptStat(0);
	TH1D* hist[2];

	TFile* file_gc = new TFile("EURICA_ADC.root", "READ");
	hist[0] = (TH1D*) file_gc -> Get("GeCluster");
	hist[1] = (TH1D*) file_gc -> Get("GeAddback");
/*
	Double_t eu_peaks[10] = {39.91, 45.7, 121.77, 244.66, 344.28, 778.90, 867.38, 964.06, 1112.08, 1408.01};//Eu152 peaks
	Double_t eu_peaks_nb[10] = {0.591, 0.149, 0.284, 0.076, 0.265, 0.129, 0.0423, 0.146, 0.1367, 0.2087};//Eu152 branching ratio for each peak

	Double_t ba_peaks[5] = {80.99, 275.925, 302.851, 356.013, 383.848};//Ba133 peaks
	Double_t ba_peaks_nb[5] = {0.341, 0.07, 0.1834, 0.6205, 0.0894};//Ba133 branching ration for each peak
*/

	Double_t eu_peaks[9] = {45.7, 121.77, 244.66, 344.28, 778.90, 867.38, 964.06, 1112.08, 1408.01};//Eu152 peaks
	Double_t eu_peaks_nb[9] = {0.149, 0.284, 0.076, 0.265, 0.129, 0.0423, 0.146, 0.1367, 0.2087};//Eu152 branching ratio for each peak

	Double_t ba_peaks[5] = {80.99, 275.925, 302.851, 356.013, 383.848};//Ba133 peaks
	Double_t ba_peaks_nb[5] = {0.341, 0.07, 0.1834, 0.6205, 0.0894};//Ba133 branching ration for each peak

	TF1* gaus_on = new TF1("gaus_on", "gaus(0)", 0, 5000);
	TF1* bg = new TF1("bg", "[0]*x + [1]", 0, 5000);

	Double_t netcount_eu[2][9];//save the netarea calculated by the area of the gaussian for each peak
	Double_t neterror_eu[2][9];//save the error for each netarea
	Double_t peaks_eu[2][9];//save the peak value with the fitting result
	Double_t peakerrors_eu[2][9];//save the error for each peak

	Double_t netcount_ba[2][5];//save the netarea calculated by the area of the gaussian for each peak
	Double_t neterror_ba[2][5];//save the error for each netarea
	Double_t peaks_ba[2][5];//save the peak value with the fitting result
	Double_t peakerrors_ba[2][5];//save the error for each peak

	Double_t peak, ampl, peakerror, amplerror, deverror;
	Double_t dev = 1.0;
	Double_t pi = TMath::Pi();
	TCanvas* c1 = new TCanvas("fitting", "");


	//fitting procedure for Eu152
	for (Int_t ihist = 0; ihist < 2; ihist++)
	{
		for (Int_t i = 0; i < 9; i++)
		{
			TF1* gaus = new TF1("gaus", "gaus(0) + [3]*x + [4]", 0, 5000);//fitting each peak
			peak = eu_peaks[i];
			hist[ihist] -> GetXaxis() -> SetRange(peak-50, peak+50);
			ampl = hist[ihist] -> GetBinContent(peak+1);
			gaus -> SetParameters(ampl, peak, dev, 0, 0);
//			if (i == 0) hist[ihist] -> Fit(gaus, "MQ", "", peak-1, peak+4);
			if (i == 0) hist[ihist] -> Fit(gaus, "MQ", "", peak-4, peak+5);
			else hist[ihist] -> Fit(gaus, "MQ", "", peak-7, peak+5);
			peaks_eu[ihist][i] = gaus -> GetParameter(1);
			peakerrors_eu[ihist][i] = gaus -> GetParError(1);
			ampl = gaus -> GetParameter(0);
			dev = gaus -> GetParameter(2);
			amplerror = (gaus -> GetParError(0))/ampl;
			deverror = (gaus -> GetParError(2))/ampl;
			if (i == 0)		netcount_eu[ihist][i] = sqrt(2*pi)*ampl*dev;
			else		netcount_eu[ihist][i] = sqrt(2*pi)*ampl*dev;
			neterror_eu[ihist][i] = sqrt(amplerror*amplerror + deverror*deverror)*sqrt(2*pi)*ampl*dev;
			peakerrors_eu[ihist][i] = sqrt(peakerror*peakerror + dev*dev/netcount_eu[ihist][i]);
			gaus_on -> SetParameters(gaus -> GetParameter(0), peak, dev);
			bg -> SetParameters(gaus -> GetParameter(3), gaus -> GetParameter(4));
			cout << peaks_eu[ihist][i] << "+-" << peakerrors_eu[ihist][i] << " keV : " << netcount_eu[ihist][i] << " +- " << neterror_eu[ihist][i] << endl;
			peak = 0;
			ampl = 0;
			amplerror = 0;
			deverror = 0;
			dev = 1.0;
/*
			c1 -> cd();
			hist[ihist] -> Draw();
			gaus_on -> Draw("same");
			bg -> Draw("same");
			c1 -> Modified();
			c1 -> Update();
			sleep(1);
*/
			delete gaus;
		}

		//fitting procedure for Ba133
		for (Int_t i = 0; i < 5; i++)
		{
			TF1* gaus = new TF1("gaus", "gaus(0) + [3]*x + [4]", 0, 5000);//fitting each peak
			peak = ba_peaks[i];
			hist[ihist] -> GetXaxis() -> SetRange(peak-50, peak+50);
			ampl = hist[ihist] -> GetBinContent(peak+1);
			gaus -> SetParameters(ampl, peak, dev, 0, 0);
			hist[ihist] -> Fit(gaus, "MQ", "", peak-7, peak+5);
			peaks_ba[ihist][i] = gaus -> GetParameter(1);
			peakerrors_ba[ihist][i] = gaus -> GetParError(1);
			ampl = gaus -> GetParameter(0);
			dev = gaus -> GetParameter(2);
			amplerror = (gaus -> GetParError(0))/ampl;
			deverror = (gaus -> GetParError(2))/ampl;
			netcount_ba[ihist][i] = sqrt(2*pi)*ampl*dev;
			neterror_ba[ihist][i] = sqrt(amplerror*amplerror + deverror*deverror)*sqrt(2*pi)*ampl*dev;
			peakerrors_ba[ihist][i] = sqrt(peakerror*peakerror + dev*dev/netcount_ba[ihist][i]);
			gaus_on -> SetParameters(gaus -> GetParameter(0), peak, dev);
			bg -> SetParameters(gaus -> GetParameter(3), gaus -> GetParameter(4));
			cout << peaks_ba[ihist][i] << "+-" << peakerrors_ba[ihist][i] << " keV : " << netcount_ba[ihist][i] << " +- " << neterror_ba[ihist][i] << endl;
			peak = 0;
			ampl = 0;
			amplerror = 0;
			deverror = 0;
			dev = 1.0;
/*
			c1 -> cd();
			hist[ihist] -> Draw();
			gaus_on -> Draw("same");
			bg -> Draw("same");
			c1 -> Modified();
			c1 -> Update();
			sleep(1);
*/
			delete gaus;
		}
	}
//	Double_t activity_eu = 10.6E3; //decay/s
	Double_t activity_eu = 18579; //decay/s
//	Double_t activity_ba = 13.4E3; //decay/s
	Double_t activity_ba = 15281; //decay/s
//	Int_t numtrigger = 5216418; //trigger number with fired gamma rays
	Int_t numtrigger = 32408508; //trigger number with fired gamma rays
//	Int_t numtrigger = 11875627;
	Double_t gatew = 100E-6; //s
//	Double_t gatew = 75E-6; //s

	Double_t betaT_eu = activity_eu*numtrigger*gatew; //eu152 locates at upstream PL
//	Double_t betaT_ba = activity_ba*numtrigger*gatew*0.65; //ba133 locates at downstream PL, considering the factor between Eu & Ba
	Double_t betaT_ba = activity_ba*numtrigger*gatew;

	Double_t eff[2][14];//save the abs eff for each peak
	Double_t eff_error[2][14];//save the error for each abs eff
	TGraphErrors* graph_gc = new TGraphErrors();
	TGraphErrors* graph_add = new TGraphErrors();


	//calculating the efficiency
	for (Int_t ihist = 0; ihist < 2; ihist++)
	{
		for (Int_t i = 0; i < 14; i++)
		{
			if (i < 9)
			{
				eff[ihist][i] = (netcount_eu[ihist][i]/eu_peaks_nb[i])/betaT_eu*100;
				eff_error[ihist][i] = (neterror_eu[ihist][i]/netcount_eu[ihist][i])*eff[ihist][i];
				cout << eff[ihist][i] << " " << eff_error[ihist][i] << endl;
				if (ihist == 0)
				{
					graph_gc -> SetPoint(i, peaks_eu[ihist][i], eff[ihist][i]);
					graph_gc -> SetPointError(i, peakerrors_eu[ihist][i], eff_error[ihist][i]);
				}
				if (ihist == 1)
				{
					graph_add -> SetPoint(i, peaks_eu[ihist][i], eff[ihist][i]);
					graph_add -> SetPointError(i, peakerrors_eu[ihist][i], eff_error[ihist][i]);
				}

			}
			else
			{			
				eff[ihist][i] = (netcount_ba[ihist][i-9]/ba_peaks_nb[i-9])/betaT_ba*100;
				eff_error[ihist][i] = (neterror_ba[ihist][i-9]/netcount_ba[ihist][i-9])*eff[ihist][i];
				cout << eff[ihist][i] << " " << eff_error[ihist][i] << endl;
				if (ihist == 0)
				{
					graph_gc -> SetPoint(i, peaks_ba[ihist][i-9], eff[ihist][i]);
					graph_gc -> SetPointError(i, peakerrors_ba[ihist][i-9], eff_error[ihist][i]);
				}
				if (ihist == 1)
				{
					graph_add -> SetPoint(i, peaks_ba[ihist][i-9], eff[ihist][i]);
					graph_add -> SetPointError(i, peakerrors_ba[ihist][i-9], eff_error[ihist][i]);
				}
			}
		}
	}
//plot the abs efficiency graph
	TH2D* dummy = new TH2D("dum", "", 1500, 0, 1500, 26, 4, 26);
	TCanvas* c2 = new TCanvas("eff", "");
	dummy -> Draw();
	graph_gc -> Draw("same,P");
	graph_gc -> SetMarkerStyle(26);
	graph_add -> Draw("same,P");
	graph_add -> SetMarkerStyle(25);

//fitting the efficiency curve
	TF1* eff_ftn_gc = new TF1("emp_gc", "exp((([0]+[1]*log(x/100))**(-[5]) + ([2]+[3]*log(x/1000)+[4]*(log(x/1000)*log(x/1000)))**(-[5]))**(-1/[5]))", 0, 2000);
	eff_ftn_gc -> SetParameters(2.78, 0.82, 2.03, -0.6, -0.025, 6.0);
	TF1* eff_ftn_add = new TF1("emp_add", "exp((([0]+[1]*log(x/100))**(-[5]) + ([2]+[3]*log(x/1000)+[4]*(log(x/1000)*log(x/1000)))**(-[5]))**(-1/[5]))", 0, 2000);
	eff_ftn_add -> SetParameters(2.78, 0.82, 2.03, -0.6, -0.025, 6.0);
//	eff_ftn -> SetParLimits(0, 2.5, 3.0);
//	eff_ftn -> SetParLimits(1, 0.7, 1.0);
//	eff_ftn -> SetParLimits(2, 1.8, 2.2);
//	eff_ftn -> SetParLimits(3, -0.8, -0.4);
//	eff_ftn -> SetParLimits(4, -0.03, -0.02);
//	eff_ftn -> SetParLimits(5,  5, 7);
	
	graph_gc -> Fit(eff_ftn_gc, "M0", "", 30, 1500);
	graph_add -> Fit(eff_ftn_add, "M0", "", 30, 1500);

	eff_ftn_gc->Draw("same");
	eff_ftn_add->Draw("same");

	eff_ftn_gc->SetLineColor(4);
	eff_ftn_gc->SetLineStyle(2);

	TFile* outgc = new TFile("eff_data_gc.root", "recreate");
	outgc -> cd();
	eff_ftn_gc -> Write();
	outgc -> Close();

	TFile* outadd = new TFile("eff_data_add.root", "recreate");
	outadd -> cd();
	eff_ftn_add -> Write();
	outadd -> Close();
}
