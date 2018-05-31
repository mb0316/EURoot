#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EUAnaBeta.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "EUDataSi.h"
#include "EUDataGe.h"
#include "EUDataBeam.h"
#include "EUTreeBeta.h"

EUAnaBeta::EUAnaBeta(TTree* tree):EUTreeBeta(tree)
{}

EUAnaBeta::~EUAnaBeta()
{}

void EUAnaBeta::GetCalib()
{
	ifstream adcfile("../calib/eurica_adc_calib.dat");
	ifstream tdcsfile("../calib/eurica_tdcs_calib.dat");
	ifstream tdclfile("../calib/eurica_tdcl_calib.dat");
	ifstream wasabifile("../calib/WASABI_gain.dat");
	ifstream overflowfile("../calib/eurica_overflow.dat");
	ifstream wasabiTfile("../calib/tzero.dat");

	for (Int_t i = 0; i < 84; i++)
	{
		adcfile >> adc_ch[i] >> adc_gain[i] >> adc_offset[i];
		tdcsfile >> tdcs_ch[i] >> tdcs_gain[i] >> tdcs_offset[i];
		overflowfile >> adc_ch[i] >> overflow[i];
	}
	tdclfile >> tdcl_gain >> tdcl_offset;

	Int_t numdssd, ich;
	Double_t temp_gain, temp_offset;

	for (Int_t i = 0; i < 500; i++)
	{
		wasabifile >> numdssd >> ich >> temp_gain >> temp_offset;
		if (ich < 60)
		{
			wasabi_gain_x[numdssd][ich] = temp_gain;
			wasabi_offset_x[numdssd][ich] = temp_offset;
		}
		if (ich >= 60)
		{
			wasabi_gain_y[numdssd][ich-60] = temp_gain;
			wasabi_offset_y[numdssd][ich-60] = temp_offset;
		}
	}

	for (Int_t i = 0; i < 40; i++)
	{
		wasabi_gain_y[4][i] = 1;
		wasabi_offset_y[4][i] = 0;
	}

	Double_t temp_T;
	for (Int_t i = 0; i < 500; i++)
	{
		wasabiTfile >> numdssd >> ich >> temp_T;
		if (ich < 60)	wasabi_Tzero_x[numdssd][ich] = temp_T;
		if (ich >= 60)	wasabi_Tzero_y[numdssd][ich-60] = temp_T;
	}

	adcfile.close();
	tdcsfile.close();
	tdclfile.close();
	wasabifile.close();
	overflowfile.close();
	wasabiTfile.close();
}

void EUAnaBeta::CalibBeam(Int_t &runnum)
{
	ifstream wasabiEcal("../calib/WASABI_gain_beam.dat");
	ifstream wasabiEcal_d1("../calib/WASABI_gain_beam_dssd1.dat");

	Int_t ndssd, nch;
	Double_t temp_gain, temp_offset;
	for (Int_t ich = 0; ich < 60; ich++)	wasabiEcal_d1 >> nch >> wasabi_gain_x[1][ich] >> wasabi_offset_x[1][ich];

	for (Int_t i = 0; i < 160; i++)
	{
		wasabiEcal >> ndssd >> nch >> temp_gain >> temp_offset;
		wasabi_gain_y[ndssd][nch] = temp_gain;
		wasabi_offset_y[ndssd][nch] = temp_offset;
	}

	ifstream euricaEcal;
	if (runnum < 1030)	euricaEcal.open ("../calib/EURICA_Ecal/BT_Ecal/1020.dat");	  
	if (runnum < 1045 && runnum >= 1030)	euricaEcal.open ("../calib/EURICA_Ecal/BT_Ecal/1030.dat");	  
	if (runnum < 1060 && runnum >= 1045)	euricaEcal.open ("../calib/EURICA_Ecal/BT_Ecal/1045.dat");	  
	if (runnum < 1075 && runnum >= 1060)	euricaEcal.open ("../calib/EURICA_Ecal/BT_Ecal/1060.dat");	  
	if (runnum < 1090 && runnum >= 1075)	euricaEcal.open ("../calib/EURICA_Ecal/BT_Ecal/1075.dat");	  
	if (runnum < 1105 && runnum >= 1090)	euricaEcal.open ("../calib/EURICA_Ecal/BT_Ecal/1090.dat");	  
	if (runnum < 1120 && runnum >= 1105)	euricaEcal.open ("../calib/EURICA_Ecal/BT_Ecal/1105.dat");	  
	if (runnum < 1130 && runnum >= 1120)	euricaEcal.open ("../calib/EURICA_Ecal/BT_Ecal/1120.dat");	  

	for (Int_t i = 0; i < 84; i++)	euricaEcal >> nch >> adc_gain[i] >> adc_offset[i];
}
	

void EUAnaBeta::CalibTzero(EUDataSi *dssd)
{
	for (idssd = 0; idssd < 5; idssd++)
	{
		for (ix = 0; ix < 60; ix++)	nw3tx[idssd][ix] = (dssd->w3tx[idssd][ix][0] - wasabi_Tzero_x[idssd][ix]);
		for (iy = 0; iy < 40; iy++)	nw3ty[idssd][iy] = (dssd->w3ty[idssd][iy][0] - wasabi_Tzero_y[idssd][iy]);
	}
}

void EUAnaBeta::GetIonPos(EUDataSi *dssd)
{
	temp_z = -1;
	max_tempT = 0;

	for (Int_t i = 0; i < 6; i++)
	{
		fire_x[i] = 0;
		fire_y[i] = 0;
		fire_z[i] = 0;
	}

	for (idssd = 0; idssd < 5; idssd++)
	{
		for (ix = 0; ix < 60; ix++)
		{
			if (abs(nw3tx[idssd][ix]) < max_tempTX[idssd])
			{
				fire_x[idssd] = 1;
				break;
			}
			else    continue;
		}

		for (iy = 0; iy < 40; iy++)
		{
			if (abs(nw3ty[idssd][iy]) < max_tempTY[idssd])
			{
				fire_y[idssd] = 1;
				break;
			}
			else    continue;
		}

		if (fire_x[idssd] == 1 && fire_y[idssd] == 1)	fire_z[idssd] = 1;

		if (fire_z[4] == 1 && dssd->betaPL2L < 50000 && dssd->betaPL2R < 50000) fire_z[5] = 1; 

	}

	for (Int_t i = 0; i < 5; i++)
	{
		if (fire_z[i] == 1 && fire_z[i+1] == 0)
		{
			temp_z = i;
			break;
		}
		else continue;
	}

	GetXY(temp_z, dssd);
	if (good_xy == 1)
	{
		ion_z = temp_z;
		ion_x = temp_x[temp_z];
		ion_y = temp_y[temp_z];
		ion_E_X = dssd->w3_ex[ion_z][ion_x];
		ion_T_X = nw3tx[ion_z][ion_x];
		ion_E_Y = dssd->w3_ey[ion_z][ion_y];
		ion_T_Y = nw3ty[ion_z][ion_y];
	}
	if (good_xy == 0)
	{
		ion_z = -1;
		ion_x = -10;
		ion_y = -10;
		ion_E_X = -50000;
		ion_E_Y = -50000;
		ion_T_X = -50000;
		ion_T_Y = -50000;
	}
}

int EUAnaBeta::GetXY(Int_t temp_z, EUDataSi* dssd)
{
	for (Int_t i = 0; i < 5; i++)
	{
		temp_x[i] = -1;
		temp_y[i] = -1;
	}

	good_xy = 0;
	if (temp_z > -1 && temp_z < 5)
	{
		for (idssd = 0; idssd <= temp_z; idssd++)
		{
			max_tempT = max_tempTX[idssd];
			for (ix = 0; ix < 60; ix++)
			{
//				if (dssd->w3_ex[idssd][ix] > 4100 && nw3tx[idssd][ix] > -1000 && nw3tx[idssd][ix]< max_tempT)
				if (nw3tx[idssd][ix] > -1000 && nw3tx[idssd][ix]< max_tempT)
				{
					temp_x[idssd] = ix;
					max_tempT = nw3tx[idssd][ix];
				}
				else continue;
			}

			max_tempT = max_tempTY[idssd];
			for (iy = 0; iy < 40; iy++)
			{
//				if (dssd->w3_ey[idssd][iy] > 4100 && nw3ty[idssd][iy]> -1000 && nw3ty[idssd][iy]< max_tempT)
				if (nw3ty[idssd][iy]> -1000 && nw3ty[idssd][iy]< max_tempT)
				{
					temp_y[idssd] = iy;
					max_tempT = nw3ty[idssd][iy];
				}
				else continue;
			}
		}
		//if (temp_x[temp_z] > -1 && temp_y[temp_z] > -1)	good_xy = 1;

		if (temp_x[temp_z] > -1 && temp_y[temp_z] > -1)
		{
			if (temp_z == 0) good_xy = 1;
			if (temp_z == 1 && abs(temp_x[temp_z] - temp_x[0]) <= 1 && abs(temp_y[0] - temp_y[temp_z]) <= 1) good_xy = 1;
			if ((temp_z == 2 || temp_z == 3) && abs(temp_x[temp_z] - temp_x[0]) <= 3 && abs(temp_y[temp_z] - temp_y[temp_z]) <= 3) good_xy = 1;
			if (temp_z ==4) good_xy = 1;
		}

	}

	return good_xy;
}

void EUAnaBeta::GetBetaPos(EUDataSi *dssd, TTree* tree)
{   
	fire = -1;
	temp_beta_pos.clear();
	temp_beta_z.clear();
	dssdhit = 0;
	for (Int_t idssd = 0; idssd < 5; idssd++)
	{
		for (ix = 0; ix < 60; ix++)
		{
//			if (dssd->w3_ex[idssd][ix] > 10 && dssd->w3_ex[idssd][ix] < 4100 && dssd->w3tx[idssd][ix][0] > -4000 && dssd->w3tx[idssd][ix][0] < 50000)
			if (dssd->w3_ex[idssd][ix] > 0 && dssd->w3tx[idssd][ix][0] > beta_T_X_cut_L[idssd] && dssd->w3tx[idssd][ix][0] < beta_T_X_cut_H[idssd])
			{
				for (iy = 0; iy < 40; iy++)
				{
//					if (dssd->w3_ey[idssd][iy] > 10 && dssd->w3_ey[idssd][iy] < 4100 && dssd->w3ty[idssd][iy][0] > -4000 && dssd->w3ty[idssd][iy][0] < 50000)
					if (dssd->w3_ey[idssd][iy] > 0 && dssd->w3ty[idssd][iy][0] > beta_T_Y_cut_L[idssd] && dssd->w3ty[idssd][iy][0] < beta_T_Y_cut_H[idssd])
					{
						fire = 1;
						dssdhit++;
						temp_beta_pos.push_back(pair<int, int> (ix, iy));
						temp_beta_z.push_back(idssd);
					}
					else continue;
				}
			}
			else continue;
		}
	}

	if (fire == 1 && dssdhit < 100)
	{
		for (Int_t i = 0; i < dssdhit; i++)
		{
			beta_z[i]  = temp_beta_z[i];
			if (beta_z[i] == 3)
			{
				beta_x[i] = temp_beta_pos[i].first;
				if (temp_beta_pos[i].second == 21)	beta_y[i] = 31;
				else if (temp_beta_pos[i].second == 31)	beta_y[i] = 21;
				else beta_y[i] = temp_beta_pos[i].second;
			}
			else if (beta_z[i] == 4)
			{
				beta_y[i] = temp_beta_pos[i].second;
				if (temp_beta_pos[i].first == 3)	beta_x[i] = 13;
				else if (temp_beta_pos[i].first == 13)	beta_x[i] = 3;
				else beta_x[i] = temp_beta_pos[i].first;
			}
			else
			{
				beta_x[i] = temp_beta_pos[i].first;
				beta_y[i] = temp_beta_pos[i].second;
			}
			beta_E_X[i] = dssd->w3_ex[beta_z[i]][beta_x[i]]*wasabi_gain_x[beta_z[i]][beta_x[i]] + wasabi_offset_x[beta_z[i]][beta_x[i]];
			beta_E_Y[i] = dssd->w3_ey[beta_z[i]][beta_y[i]]*wasabi_gain_y[beta_z[i]][beta_y[i]] + wasabi_offset_y[beta_z[i]][beta_y[i]];
			beta_T_X[i] = dssd->w3tx[beta_z[i]][beta_x[i]][0];
			beta_T_Y[i] = dssd->w3ty[beta_z[i]][beta_y[i]][0];
			beta_E_delta[i] = beta_E_X[i] - beta_E_Y[i];
			beta_good[i] = 0;
		}
	}
}

void EUAnaBeta::MapCorrel(std::map<Long64_t, Long64_t> &master_mts, std::map<Long64_t, Long64_t>::iterator &imaster_mts, std::map<Long64_t, Long64_t> &slave_mts, std::map<Long64_t, Long64_t>::iterator &islave_mts, std::map<Long64_t, Long64_t> &target_mts, Int_t lower_limit, Int_t upper_limit)
{
	for (imaster_mts = master_mts.begin(); imaster_mts != master_mts.end(); imaster_mts++)
	{
		islave_mts = slave_mts.lower_bound(imaster_mts->first - lower_limit);
		if (islave_mts != slave_mts.end() && islave_mts->first < imaster_mts->first+upper_limit)	target_mts.insert(pair<Long64_t, Long64_t> (imaster_mts->second, islave_mts->second));
	}
}

void EUAnaBeta::CopyTS(EUDataSi *dssd)
{   
	ts = dssd->EventInfo_timestamp[0];
}

void EUAnaBeta::CopyTS(EUDataGe *hpge)
{   
	ts = hpge->EventInfo_timestamp[0];
}

void EUAnaBeta::CopyTS(EUDataBeam *beam)
{   
	ts = beam->EventInfo_timestamp[0];
}

void EUAnaBeta::CopyTS(EUTreeBeta *beta)
{   
	ts = beta->ts;
	eventid = beta->eventid;
}

void EUAnaBeta::CopyBigRIPS(EUTreeBeta *beta)
{   
	AoQ = beta->AoQ;
	Zpro = beta->Zpro;
}

void EUAnaBeta::CopyBigRIPS(EUDataBeam *beam)
{   
	AoQ = beam->RIBeam_aoq37[0];
	Zpro = beam->RIBeam_zed[0];
}

void EUAnaBeta::CopyPL(EUDataSi *dssd)
{   
	vetoPL1 = dssd->vetoPL_front;
	vetoPL2 = dssd->vetoPL_back;
	F11_TDC_L= dssd->f11L;
	F11_TDC_R = dssd->f11R;
}

void EUAnaBeta::CopyPL(EUDataGe *hpge)
{
	F11_ADC_L = hpge->BigRIPSRaw_F11SCI_L[0];
	F11_ADC_R = hpge->BigRIPSRaw_F11SCI_R[0];
}

void EUAnaBeta::CopyPL(EUTreeBeta *beta)
{
	F11_ADC_L = beta->F11_ADC_L;
	F11_ADC_R = beta->F11_ADC_R;
	F11_TDC_L = beta->F11_TDC_L;
	F11_TDC_R = beta->F11_TDC_R;
}

void EUAnaBeta::CopyPL(EUTreeBeta *dssd, EUTreeBeta *hpge)
{
	F11_ADC_L = hpge->F11_ADC_L;
	F11_ADC_R = hpge->F11_ADC_R;
	F11_TDC_L = dssd->F11_TDC_L;
	F11_TDC_R = dssd->F11_TDC_R;
}

void EUAnaBeta::CopyEURICA(EUDataGe *hpge)
{
	temp_gchit = hpge->GeCluster_;
	for (Int_t ihit = 0; ihit < temp_gchit; ihit++)
	{
		temp_gc_ch[ihit] = hpge->GeCluster_channel[ihit];
		temp_gc_T[ihit] = hpge->GeCluster_fTime[ihit];

		temp_gc_E[ihit] = adc_gain[temp_gc_ch[ihit]]*(hpge->GeCluster_fADCe[ihit]) + adc_offset[temp_gc_ch[ihit]];
		temp_gc_Ts[ihit] = tdcs_gain[temp_gc_ch[ihit]]*(hpge->GeCluster_fTDCs[ihit]);
		temp_gc_Tl[ihit] = tdcl_gain*hpge->GeCluster_fTDCl[ihit];

	}


	gchit = 0;

	for (Int_t ihit = 0; ihit < temp_gchit; ihit++)
	{
		if (temp_gc_E[ihit] < overflow[temp_gc_ch[ihit]])
		{
			gc_ch[gchit] = temp_gc_ch[ihit];
			gc_E[gchit] = temp_gc_E[ihit];
			gc_T[gchit] = temp_gc_T[ihit];
			gc_Ts[gchit] = temp_gc_Ts[ihit];
			gc_Tl[gchit] = temp_gc_Tl[ihit];
			
			gchit++;
		}
		else continue;
	}

	Addback();

	lbhit = hpge->LaBr_;
	for (Int_t ihit = 0; ihit < lbhit; ihit++)
	{
		lb_ch[ihit] = hpge->LaBr_channel[ihit];
		lb_E[ihit] = hpge->LaBr_fEnergy[ihit];
		lb_Ts[ihit] = hpge->LaBr_fTime_srt[ihit];
		lb_Tl[ihit] = hpge->LaBr_fTime_lrt[ihit];
	}

	betaPL1_Beam_ADCL = hpge->BetaPlasticUp_ADC_L_Beam[0];
	betaPL1_Beta_ADCL = hpge->BetaPlasticUp_ADC_L_Beta[0];
	betaPL1_Beam_ADCR = hpge->BetaPlasticUp_ADC_R_Beam[0];
	betaPL1_Beta_ADCR = hpge->BetaPlasticUp_ADC_R_Beta[0];
	betaPL2_Beam_ADCL = hpge->BetaPlasticDown_ADC_L_Beam[0];
	betaPL2_Beta_ADCL = hpge->BetaPlasticDown_ADC_L_Beta[0];
	betaPL2_Beam_ADCR = hpge->BetaPlasticDown_ADC_R_Beam[0];
	betaPL2_Beta_ADCR = hpge->BetaPlasticDown_ADC_R_Beta[0];
	betaPL1_TLs = hpge->BetaPlasticUp_TDC_L_srt[0];
	betaPL1_TRs = hpge->BetaPlasticUp_TDC_R_srt[0];
	betaPL2_TLs = hpge->BetaPlasticDown_TDC_L_srt[0];
	betaPL2_TRs = hpge->BetaPlasticDown_TDC_R_srt[0];
	betaPL1_TLl = hpge->BetaPlasticUp_TDC_L_lrt[0];
	betaPL1_TRl = hpge->BetaPlasticUp_TDC_R_lrt[0];
	betaPL2_TLl = hpge->BetaPlasticDown_TDC_L_lrt[0];
	betaPL2_TRl = hpge->BetaPlasticDown_TDC_R_lrt[0];
}

void EUAnaBeta::CopyEURICA(EUTreeBeta *beta, Int_t opt)
{
	if (opt == 0)
	{
		gchit = beta->gchit;
		for (Int_t ihit = 0; ihit < gchit; ihit++)
		{
			gc_ch[ihit] = beta->gc_ch[ihit];
			gc_E[ihit] = adc_gain[gc_ch[ihit]]*(beta->gc_E[ihit]) + adc_offset[gc_ch[ihit]];
			gc_T[ihit] = beta->gc_T[ihit];
			gc_Tl[ihit] = beta->gc_Tl[ihit];
			gc_Ts[ihit] = beta->gc_Ts[ihit];
		}

		addhit = beta->addhit;
		for (Int_t ihit = 0; ihit < addhit; ihit++)
		{
			add_ch[ihit] = beta->add_ch[ihit];
			add_E[ihit] = adc_gain[add_ch[ihit]]*(beta->add_E[ihit]) + adc_offset[add_ch[ihit]];
			add_T[ihit] = beta->add_T[ihit];
		}

		lbhit = beta->lbhit;
		memcpy(lb_ch, beta->lb_ch, lbhit*sizeof(int));
		memcpy(lb_E, beta->lb_E, lbhit*sizeof(double));
		memcpy(lb_Ts, beta->lb_Ts, lbhit*sizeof(double));
		memcpy(lb_Tl, beta->lb_Tl, lbhit*sizeof(double));

		betaPL1_Beam_ADCL = beta->betaPL1_Beam_ADCL;
		betaPL1_Beta_ADCL = beta->betaPL1_Beta_ADCL;
		betaPL1_Beam_ADCR = beta->betaPL1_Beam_ADCR;
		betaPL1_Beta_ADCR = beta->betaPL1_Beta_ADCR;
		betaPL2_Beam_ADCL = beta->betaPL2_Beam_ADCL;
		betaPL2_Beta_ADCL = beta->betaPL2_Beta_ADCL;
		betaPL2_Beam_ADCR = beta->betaPL2_Beam_ADCR;
		betaPL2_Beta_ADCR = beta->betaPL2_Beta_ADCR;
		betaPL1_TLs = beta->betaPL1_TLs;
		betaPL1_TRs = beta->betaPL1_TRs;
		betaPL2_TLs = beta->betaPL2_TLs;
		betaPL2_TRs = beta->betaPL2_TRs;
		betaPL1_TLl = beta->betaPL1_TLl;
		betaPL1_TRl = beta->betaPL1_TRl;
		betaPL2_TLl = beta->betaPL2_TLl;
		betaPL2_TRl = beta->betaPL2_TRl;
	}
	if (opt == 1)
	{
		gchit = beta->gchit;
		memcpy(gc_ch, beta->gc_ch, gchit*sizeof(int));
		memcpy(gc_E, beta->gc_E, gchit*sizeof(double));
		memcpy(gc_T, beta->gc_T, gchit*sizeof(double));
		memcpy(gc_Ts, beta->gc_Ts, gchit*sizeof(double));
		memcpy(gc_Tl, beta->gc_Tl, gchit*sizeof(double));

		addhit = beta->addhit;
		memcpy(add_ch, beta->add_ch, addhit*sizeof(int));
		memcpy(add_E, beta->add_E, addhit*sizeof(double));
		memcpy(add_T, beta->add_T, addhit*sizeof(double));

		lbhit = beta->lbhit;
		memcpy(lb_ch, beta->lb_ch, lbhit*sizeof(int));
		memcpy(lb_E, beta->lb_E, lbhit*sizeof(double));
		memcpy(lb_Ts, beta->lb_Ts, lbhit*sizeof(double));
		memcpy(lb_Tl, beta->lb_Tl, lbhit*sizeof(double));

		betaPL1_Beam_ADCL = beta->betaPL1_Beam_ADCL;
		betaPL1_Beta_ADCL = beta->betaPL1_Beta_ADCL;
		betaPL1_Beam_ADCR = beta->betaPL1_Beam_ADCR;
		betaPL1_Beta_ADCR = beta->betaPL1_Beta_ADCR;
		betaPL2_Beam_ADCL = beta->betaPL2_Beam_ADCL;
		betaPL2_Beta_ADCL = beta->betaPL2_Beta_ADCL;
		betaPL2_Beam_ADCR = beta->betaPL2_Beam_ADCR;
		betaPL2_Beta_ADCR = beta->betaPL2_Beta_ADCR;
		betaPL1_TLs = beta->betaPL1_TLs;
		betaPL1_TRs = beta->betaPL1_TRs;
		betaPL2_TLs = beta->betaPL2_TLs;
		betaPL2_TRs = beta->betaPL2_TRs;
		betaPL1_TLl = beta->betaPL1_TLl;
		betaPL1_TRl = beta->betaPL1_TRl;
		betaPL2_TLl = beta->betaPL2_TLl;
		betaPL2_TRl = beta->betaPL2_TRl;
	}
}

void EUAnaBeta::CopyDSSD(EUTreeBeta *beta, Int_t opt)
{
	if (opt == 0)
	{
		if (eventid == 0)
		{
			ion_z = beta->ion_z;
			ion_x = beta->ion_x;
			ion_y = beta->ion_y;
			ion_E_X = beta->ion_E_X;
			ion_E_Y = beta->ion_E_Y;
			ion_T_X = beta->ion_T_X;
			ion_T_Y = beta->ion_T_Y;
		}

		if (eventid == 1)
		{
			dssdhit = beta->dssdhit;
			for (Int_t ihit = 0; ihit < dssdhit; ihit++)
			{
				beta_z[ihit] = beta->beta_z[ihit];
				beta_x[ihit] = beta->beta_x[ihit];
				beta_y[ihit] = beta->beta_y[ihit];
				if (beta_z[ihit] == 1)
				{
					beta_E_X[ihit] = wasabi_gain_x[1][beta_x[ihit]]*(beta->beta_E_X[ihit]) + wasabi_offset_x[1][beta_x[ihit]];
					beta_E_Y[ihit] = beta->beta_E_Y[ihit];
				}
				else
				{
					beta_E_X[ihit] = beta->beta_E_X[ihit];
					beta_E_Y[ihit] = wasabi_gain_y[beta_z[ihit]][beta_y[ihit]]*(beta->beta_E_Y[ihit]) + wasabi_offset_y[beta_z[ihit]][beta_y[ihit]];
				}
				beta_E_delta[ihit] = beta_E_X[ihit] - beta_E_Y[ihit];
				beta_good[ihit] = beta->beta_good[ihit];
				beta_T_X[ihit] = beta->beta_T_X[ihit];
				beta_T_Y[ihit] = beta->beta_T_Y[ihit];
			}
		}
	}
	if (opt == 1)
	{
		if (eventid == 0)
		{
			ion_z = beta->ion_z;
			ion_x = beta->ion_x;
			ion_y = beta->ion_y;
			ion_E_X = beta->ion_E_X;
			ion_E_Y = beta->ion_E_Y;
			ion_T_X = beta->ion_T_X;
			ion_T_Y = beta->ion_T_Y;
		}

		if (eventid == 1)
		{
			dssdhit = beta->dssdhit;
			for (Int_t ihit = 0; ihit < dssdhit; ihit++)
			{
				beta_z[ihit] = beta->beta_z[ihit];
				beta_x[ihit] = beta->beta_x[ihit];
				beta_y[ihit] = beta->beta_y[ihit];
				beta_E_X[ihit] = beta->beta_E_X[ihit];
				beta_E_Y[ihit] = beta->beta_E_Y[ihit];
				beta_E_delta[ihit] = beta->beta_E_delta[ihit];
				if (beta_E_delta[ihit] > deltaE_cut_L[beta_z[ihit]] && beta_E_delta[ihit] < deltaE_cut_U[beta_z[ihit]])	beta_good[ihit] = 2;
				else if (abs(beta_E_delta[ihit]) < 500)	beta_good[ihit] = 1;
				else	beta_good[ihit] = 0;
				beta_T_X[ihit] = beta->beta_T_X[ihit];
				beta_T_Y[ihit] = beta->beta_T_Y[ihit];
			}
		}

/*
		if (eventid == 1)
		{
			tem_dssdhit = beta->dssdhit;
			for (Int_t ihit = 0; ihit < tem_dssdhit; ihit++)
			{
					tem_beta_z[ihit] = beta->beta_z[ihit];
					tem_beta_x[ihit] = beta->beta_x[ihit];
					tem_beta_y[ihit] = beta->beta_y[ihit];
					tem_beta_E_X[ihit] = beta->beta_E_X[ihit];
					tem_beta_E_Y[ihit] = beta->beta_E_Y[ihit];
					tem_beta_E_delta[ihit] = beta->beta_E_delta[ihit];
					tem_beta_T_X[ihit] = beta->beta_T_X[ihit];
					tem_beta_T_Y[ihit] = beta->beta_T_Y[ihit];
			}

			dssdhit = 0;
			for (Int_t ihit = 0; ihit < tem_dssdhit; ihit++)
			{
				if (tem_beta_E_delta[ihit] > deltaE_cut_L[tem_beta_z[ihit]] && tem_beta_E_delta[ihit] < deltaE_cut_U[tem_beta_z[ihit]])
				{
					beta_z[dssdhit] = tem_beta_z[ihit];
					beta_x[dssdhit] = tem_beta_x[ihit];
					beta_y[dssdhit] = tem_beta_y[ihit];
					beta_E_X[dssdhit] = tem_beta_E_X[ihit];
					beta_E_Y[dssdhit] = tem_beta_E_Y[ihit];
					beta_E_delta[dssdhit] = tem_beta_E_delta[ihit];
					beta_T_X[dssdhit] = tem_beta_T_X[ihit];
					beta_T_Y[dssdhit] = tem_beta_T_Y[ihit];
					dssdhit++;
				}
				else continue;
			}
		}
*/
	}
}

void EUAnaBeta::ResetPL()
{
	F11_ADC_L = 0;
	F11_ADC_R = 0;
	F11_TDC_L = 0;
	F11_TDC_R = 0;
}

void EUAnaBeta::ResetEURICA()
{
	gchit = 0;
	addhit = 0;
	lbhit = 0;
}

void EUAnaBeta::ResetPID()
{
	AoQ = 0;
	Zpro = 0;
}

void EUAnaBeta::ResetDSSD()
{
	ion_z = -10;
	ion_x = -10;
	ion_y = -10;
	ion_E_X = -50000;
	ion_E_Y = -50000;
	ion_T_X = -50000;
	ion_T_Y = -50000;
	dssdhit = 0;
	for (Int_t i = 0; i < 50; i++)
	{
		beta_z[i] = -5;
		beta_x[i] = -5;
		beta_y[i] = -5;
		beta_E_X[i] = -50000;
		beta_E_Y[i] = -50000;
		beta_E_delta[i] = -50000;
		beta_T_X[i] = -50000;
		beta_T_Y[i] = -50000;
		beta_good[i] = -1;
	}
}

void EUAnaBeta::Addback()
{
	Int_t iclust, nclust, ncryst; //icryst[3];
	addhit = 0;
	for (Int_t i = 0; i  < 12; i++)
	{
		tempgchit[i] = 0;
		tempaddhit[i] = 0;
		for (Int_t j = 0; j < 7; j++)
		{
			tempCry[i][j] = 0;
			tempE[i][j] = 0;
			tempT[i][j] = 0;
		}
	}

	if (gchit == 1)
	{
		addhit = 1;
		add_ch[0] = int(gc_ch[0]/7)*7;
		add_E[0] = gc_E[0];
		add_T[0] = gc_T[0];
	}
	else
	{
		for (Int_t ihit = 0; ihit < gchit; ihit++)
		{
			nclust = int(gc_ch[ihit]/7);
			ncryst = gc_ch[ihit]%7;
			tempCry[nclust][tempgchit[nclust]] = ncryst;
			tempE[nclust][tempgchit[nclust]] = gc_E[ihit];
			tempT[nclust][tempgchit[nclust]] = gc_T[ihit];
			tempgchit[nclust]++;
		}

		for (iclust = 0; iclust < 12; iclust++)
		{
			if (tempgchit[iclust] == 1 && tempE[iclust][0] > 0)
			{
				add_ch[addhit] = iclust*7;
				add_E[addhit] = tempE[iclust][0];
				add_T[addhit] = tempT[iclust][0];
				addhit++;
			}

			else if (tempgchit[iclust] == 2)
			{
				if (Addback2hitCheck(iclust, tempCry[iclust][0], tempCry[iclust][1]) == 1)
				{
					add_ch[addhit] = iclust*7;
					add_E[addhit] = tempE[iclust][0] + tempE[iclust][1];
					add_T[addhit] = (tempT[iclust][0] + tempT[iclust][1])/2;
					addhit++;
				}
				else
				{
					for (Int_t i = 0; i < tempgchit[iclust]; i++)
					{
						add_ch[addhit] = iclust*7;
						add_E[addhit] = tempE[iclust][i];
						add_T[addhit] = tempT[iclust][i];
						addhit++;
					}
				}
			}

			else if (tempgchit[iclust] == 3)
			{
				if (Addback3hitCheck(iclust, tempCry[iclust][0], tempCry[iclust][1], tempCry[iclust][2]) == 1)
				{
					add_ch[addhit] = iclust*7;
					add_E[addhit] = tempE[iclust][0] + tempE[iclust][1] + tempE[iclust][2];
					add_T[addhit] = (tempT[iclust][0] + tempT[iclust][1] + tempT[iclust][2])/3;
					addhit++;
				}
				else if (Addback2hitCheck(iclust, tempCry[iclust][0], tempCry[iclust][1]) == 1)
				{
					add_ch[addhit] = iclust*7;
					add_E[addhit] = tempE[iclust][0] + tempE[iclust][1];
					add_T[addhit] = (tempT[iclust][0] + tempT[iclust][1])/2;
					addhit++;

					add_ch[addhit] = iclust*7;
					add_E[addhit] = tempE[iclust][2];
					add_T[addhit] = tempT[iclust][2];
					addhit++;
				}
				else if (Addback2hitCheck(iclust, tempCry[iclust][0], tempCry[iclust][2]) == 1)
				{
					add_ch[addhit] = iclust*7;
					add_E[addhit] = tempE[iclust][0] + tempE[iclust][2];
					add_T[addhit] = (tempT[iclust][0] + tempT[iclust][2])/2;
					addhit++;

					add_ch[addhit] = iclust*7;
					add_E[addhit] = tempE[iclust][1];
					add_T[addhit] = tempT[iclust][1];
					addhit++;
				}
				else if (Addback2hitCheck(iclust, tempCry[iclust][1], tempCry[iclust][2]) == 1)
				{
					add_ch[addhit] = iclust*7;
					add_E[addhit] = tempE[iclust][1] + tempE[iclust][2];
					add_T[addhit] = (tempT[iclust][1] + tempT[iclust][2])/2;
					addhit++;

					add_ch[addhit] = iclust*7;
					add_E[addhit] = tempE[iclust][0];
					add_T[addhit] = tempT[iclust][0];
					addhit++;
				}
				else
				{
					for (Int_t i = 0; i < tempgchit[iclust]; i++)
					{
						add_ch[addhit] = iclust*7;
						add_E[addhit] = tempE[iclust][i];
						add_T[addhit] = tempT[iclust][i];
						addhit++;
					}
				}
			}

			else
			{
				for (Int_t i = 0; i < tempgchit[iclust]; i++)
				{
					add_ch[addhit] = iclust*7;
					add_E[addhit] = tempE[iclust][i];
					add_T[addhit] = tempT[iclust][i];
					addhit++;
				}
			}


		}


	}

}
