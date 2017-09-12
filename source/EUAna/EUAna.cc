#include "TROOT.h"
#include "TClonesArray.h"
#include "TChain.h"
#include "TFile.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <map>
#include "TMath.h"
#include "EUAna.h"
#include "EUDataSi.h"
#include "EUDataBeam.h"
#include "EUDataGe.h"
#include "EUTreeBeta.h"
#include "EUTreeIso.h"
#include "EUTreeDecay.h"

using namespace std;

EUAna::EUAna()
{}

EUAna::~EUAna()
{}

void EUAna::GetCalib()
{
	ifstream adcfile("../calib/eurica_adc_calib.dat");
	ifstream tdcsfile("../calib/eurica_tdcs_calib.dat");
	ifstream tdclfile("../calib/eurica_tdcl_calib.dat");
	ifstream gcT_iso_twfile("../calib/twcor_iso_DGFt.dat");
	ifstream tdcs_iso_twfile("../calib/twcor_iso_TDCs.dat");
	ifstream tdcl_iso_twfile("../calib/twcor_iso_TDCl.dat");
	ifstream gcT_beta_twfile("../calib/twcor_beta_DGFt.dat");
	ifstream art_iso_tdcsfile("../calib/ge_iso_tdcs_offset.dat");
	ifstream art_beta_tdcsfile("../calib/ge_beta_tdcs_offset.dat");
	ifstream art_iso_tdclfile("../calib/ge_iso_tdcl_offset.dat");
	ifstream art_beta_tdclfile("../calib/ge_beta_tdcl_offset.dat");
	
	for (Int_t i = 0; i < 84; i++)
	{
		adcfile >> adc_ch[i] >> adc_gain[i] >> adc_offset[i];
//		cout << "adc :" << " " << adc_ch[i] << " " << adc_gain[i] << " " << adc_offset[i] << endl;
		tdcsfile >> tdcs_ch[i] >> tdcs_gain[i] >> tdcs_offset[i];
		gcT_iso_twfile >> gcT_iso_twc[i][0] >> gcT_iso_twc[i][1] >> gcT_iso_twc[i][2] >> gcT_iso_twc[i][3];
		tdcs_iso_twfile >> tdcs_iso_twc[i][0] >> tdcs_iso_twc[i][1] >> tdcs_iso_twc[i][2] >> tdcs_iso_twc[i][3];
		tdcl_iso_twfile >> tdcl_iso_twc[i][0] >> tdcl_iso_twc[i][1] >> tdcl_iso_twc[i][2] >> tdcl_iso_twc[i][3];
		gcT_beta_twfile >> gcT_beta_twc[i][0] >> gcT_beta_twc[i][1] >> gcT_beta_twc[i][2] >> gcT_beta_twc[i][3];
//		cout << gcT_beta_twc[i][0] << gcT_beta_twc[i][1] << gcT_beta_twc[2] << gcT_beta_twc[3] << endl;
		art_iso_tdcsfile >> art_iso_tdcs_offset[i];
		art_iso_tdclfile >> art_iso_tdcl_offset[i];
		art_beta_tdcsfile >> art_beta_tdcs_offset[i];
		art_beta_tdclfile >> art_beta_tdcl_offset[i];
//		cout << "tdcs :" << " " << tdcs_ch[i] << " " << tdcs_gain[i] << " " << tdcs_offset[i] << endl;
	}
	tdclfile >> tdcl_gain >> tdcl_offset;

	adcfile.close();
	tdcsfile.close();
	gcT_iso_twfile.close();
	tdcs_iso_twfile.close();
	tdcl_iso_twfile.close();
	gcT_beta_twfile.close();
	art_iso_tdcsfile.close();
	art_beta_tdcsfile.close();
	art_iso_tdclfile.close();
	art_beta_tdclfile.close();
//	cout << "tdcl :"  << " " << tdcl_gain << " " << tdcl_offset << endl;
}

int EUAna::Addback2hitCheck(Int_t iclust, Int_t icryst1, Int_t icryst2)
{
	if (Addback_hitpattern[tempCry[iclust][icryst1]][tempCry[iclust][icryst2]] == 1 || tempE[iclust][icryst1]+tempE[iclust][icryst2] > 150 || abs(tempT[iclust][icryst1]-tempT[iclust][icryst2]) < 100)
	{
		return 1;
	}
	else return 0;
}

int EUAna::Addback3hitCheck(Int_t iclust, Int_t icryst1, Int_t icryst2, Int_t icryst3)
{
	if (Addback2hitCheck(iclust, icryst1, icryst2) == 1)
	{
		if (Addback2hitCheck(iclust, icryst1, icryst3) == 1 || Addback2hitCheck(iclust, icryst2, icryst3) == 1)
		{
			return 1;
		}
		else return 0;
	}
	else return 0;
}

const int EUAna::Addback_hitpattern[7][7] = {{0, 1, 0, 0, 0, 1, 1}, {1, 0, 1, 0, 0, 0, 1}, {0, 1, 0, 1, 0, 0, 1}, {0, 0, 1, 0, 1, 0, 1}, {0, 0, 0, 1, 0, 1, 1}, {1, 0, 0, 0, 1, 0, 1}, {1, 1, 1, 1, 1, 1, 1}};
