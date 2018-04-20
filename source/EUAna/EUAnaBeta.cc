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

	for (Int_t i = 0; i < 84; i++)
	{
		adcfile >> adc_ch[i] >> adc_gain[i] >> adc_offset[i];
		tdcsfile >> tdcs_ch[i] >> tdcs_gain[i] >> tdcs_offset[i];
		overflowfile >> adc_ch[i] >> overflow[i];
	}
	tdclfile >> tdcl_gain >> tdcl_offset;

	Int_t iden, numdssd, ich;
	Double_t temp_gain, temp_offset;

	for (Int_t i = 0; i < 500; i++)
	{
		wasabifile >> iden >> numdssd >> ich >> temp_gain >> temp_offset;
		if (iden == 0)
		{
			wasabi_gain_x[numdssd][ich] = abs(temp_gain);
			wasabi_offset_x[numdssd][ich] = temp_offset;
		}
		if (iden == 1)
		{
			wasabi_gain_y[numdssd][ich] = abs(temp_gain);
			wasabi_offset_y[numdssd][ich] = temp_offset;
		}
	}

	adcfile.close();
	tdcsfile.close();
	tdclfile.close();
	wasabifile.close();
	overflowfile.close();
}
/*
void EUAnaBeta::GetIonPos(EUDataSi *dssd)
{
	for (Int_t i = 0; i < 5; i++)
	{
		fire_z[i] = 0;
		fire_x[i] = 0;
		fire_y[i] = 0;
	}
	temp_z = -1;
	temp_x = -1;
	temp_y = -1;
	max_tempT = 0;

	for (idssd = 0; idssd < 5; idssd++)
	{
		for (ix = 0; ix < 60; ix++)
		{
			if (dssd->dssd_E_X[idssd][ix] > 4000 && dssd->dssd_T_X[idssd][ix][0] > -50000)
			{
				fire_x[idssd] = 1;
				break;
			}
			else    continue;
		}
	}
	for (idssd = 0; idssd < 5; idssd++)
	{
		for (iy = 0; iy < 40; iy++)
		{
			if (dssd->dssd_E_Y[idssd][iy] > 4000 && dssd->dssd_T_Y[idssd][iy][0] > -50000)
			{
				fire_y[idssd] = 1;
				break;
			}
			else    continue;
		}
	}

	for (Int_t i = 0; i < 5; i++)
	{
		if (fire_x[i] == 1 && fire_y[i] == 1)
		{
			fire_z[i] = 1;
		}
	}
	if (dssd->betaPL2L > -50000 && dssd->betaPL2R > -50000) fire_z[5] = 1;
	else fire_z[5] = 0;

	fire_z[6] = 0;

	if (fire_z[0] == 1)
	{
		for (Int_t i = 0; i < 6; i++)
		{
			if (fire_z[i] == 1 && fire_z[i+1] == 0)
			{
				temp_z = i;
				break;
			}
		}
	}

	if (temp_z > -1 && temp_z < 5)
	{
		max_tempT = 50000;
		for (ix = 0; ix < 60; ix++)
		{
			if (dssd->dssd_T_X[temp_z][ix][0] > -2000 && dssd->dssd_T_X[temp_z][ix][0] < max_tempT && dssd->dssd_E_X[temp_z][ix] > 4000)
			{
				temp_x = ix;
				max_tempT = dssd->dssd_T_X[temp_z][ix][0];
			}
			else continue;
		}
		max_tempT = 50000;

		for (iy = 0; iy < 40; iy++)
		{
			if (dssd->dssd_T_Y[temp_z][iy][0] > -2000 && dssd->dssd_T_Y[temp_z][iy][0] < max_tempT && dssd->dssd_E_Y[temp_z][iy] > 4000)
			{
				temp_y = iy;
				max_tempT = dssd->dssd_T_Y[temp_z][iy][0];
			}
			else continue;
		}
	}


	ion_z = temp_z;
	ion_x = temp_x;
	ion_y = temp_y;
	ion_E_X = dssd->dssd_E_X[temp_z][temp_x];
	ion_T_X = dssd->dssd_T_X[temp_z][temp_x][0];
	ion_E_Y = dssd->dssd_E_Y[temp_z][temp_y];
	ion_T_Y = dssd->dssd_T_Y[temp_z][temp_y][0];

}
*/

void EUAnaBeta::GetIonPos(EUDataSi *dssd)
{
	temp_z = -1;
	temp_x = -1;
	temp_y = -1;
	max_tempT = 0;
	fire_x = -1;
	fire_y = -1;

	for (idssd = 0; idssd < 5; idssd++)
	{
		for (ix = 0; ix < 60; ix++)
		{
			if (dssd->dssd_E_X[idssd][ix] > 5000 && dssd->dssd_T_X[idssd][ix][0] > -2000)
			{
				fire_x = 1;
				break;
			}
			else    continue;
		}

		for (iy = 0; iy < 40; iy++)
		{
			if (dssd->dssd_E_Y[idssd][iy] > 5000 && dssd->dssd_T_Y[idssd][iy][0] > -2000)
			{
				fire_y = 1;
				break;
			}
			else    continue;
		}

		if (fire_x == 1 && fire_y == 1)	temp_z = idssd;

		if (temp_z == 4 && dssd->betaPL2L > -50000 && dssd->betaPL2R > -50000) temp_z = 5; 
		fire_x = 0;
		fire_y = 0;

	}

	if (temp_z > -1 && temp_z < 5)
	{

		if (temp_z == 0 || temp_z == 1)
		{
			max_tempT = 50000;
			for (ix = 0; ix < 60; ix++)
			{
//				if (dssd->dssd_T_X[temp_z][ix][0] > -2000 && dssd->dssd_T_X[temp_z][ix][0] < max_tempT && dssd->dssd_E_X[temp_z][ix] > 4000)
				if (dssd->dssd_T_X[temp_z][ix][0] > -10000 && dssd->dssd_T_X[temp_z][ix][0] < max_tempT && dssd->dssd_T_X[temp_z][ix][0] < 750 && dssd->dssd_E_X[temp_z][ix] > 5000)
				{
					temp_x = ix;
					max_tempT = dssd->dssd_T_X[temp_z][ix][0];
				}
				else continue;
			}
			max_tempT = 50000;

			for (iy = 0; iy < 40; iy++)
			{
//				if (dssd->dssd_T_Y[temp_z][iy][0] > -2000 && dssd->dssd_T_Y[temp_z][iy][0] < max_tempT && dssd->dssd_E_Y[temp_z][iy] > 4000)
				if (dssd->dssd_T_Y[temp_z][iy][0] > -10000 && dssd->dssd_T_Y[temp_z][iy][0] < max_tempT && dssd->dssd_T_Y[temp_z][iy][0] < 500 && dssd->dssd_E_Y[temp_z][iy] > 5000)
				{
					temp_y = iy;
					max_tempT = dssd->dssd_T_Y[temp_z][iy][0];
				}
				else continue;
			}
		}

		else
		{
			max_tempT = 50000;
			for (ix = 0; ix < 60; ix++)
			{
				if (dssd->dssd_T_X[temp_z][ix][0] > -2000 && dssd->dssd_T_X[temp_z][ix][0] < max_tempT && dssd->dssd_E_X[temp_z][ix] > 5000)
				{
					temp_x = ix;
					max_tempT = dssd->dssd_T_X[temp_z][ix][0];
				}
				else continue;
			}
			max_tempT = 50000;

			for (iy = 0; iy < 40; iy++)
			{
				if (dssd->dssd_T_Y[temp_z][iy][0] > -2000 && dssd->dssd_T_Y[temp_z][iy][0] < max_tempT && dssd->dssd_E_Y[temp_z][iy] > 5000)
				{
					temp_y = iy;
					max_tempT = dssd->dssd_T_Y[temp_z][iy][0];
				}
				else continue;
			}
		}

	}


	ion_z = temp_z;
	ion_x = temp_x;
	ion_y = temp_y;
	ion_E_X = dssd->dssd_E_X[temp_z][temp_x];
	ion_T_X = dssd->dssd_T_X[temp_z][temp_x][0];
	ion_E_Y = dssd->dssd_E_Y[temp_z][temp_y];
	ion_T_Y = dssd->dssd_T_Y[temp_z][temp_y][0];

}


//void EUAnaBeta::GetBetaPos(EUDataSi *dssd, Int_t &ndssd, TTree* tree)
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
			if (dssd->dssd_E_X[idssd][ix] > 10 && dssd->dssd_T_X[idssd][ix][0] > -50000)
			{
				for (iy = 0; iy < 40; iy++)
				{
					if (dssd->dssd_E_Y[idssd][iy] > 10 && dssd->dssd_T_Y[idssd][iy][0] > -50000)
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

	if (fire == 1 && dssdhit <= 50)
	{
//		for (Int_t i = 0; i < temp_beta_pos.size(); i++)
		for (Int_t i = 0; i < dssdhit; i++)
		{
			beta_z[i]  = temp_beta_z[i];
			beta_x[i] = temp_beta_pos[i].first;
			beta_y[i] = temp_beta_pos[i].second;
			beta_E_X[i] = dssd->dssd_E_X[beta_z[i]][beta_x[i]]*abs(wasabi_gain_x[beta_z[i]][beta_x[i]]) + wasabi_offset_x[beta_z[i]][beta_x[i]];
			beta_E_Y[i] = dssd->dssd_E_Y[beta_z[i]][beta_y[i]]*abs(wasabi_gain_y[beta_z[i]][beta_y[i]]) + wasabi_offset_y[beta_z[i]][beta_y[i]];
			beta_T_X[i] = dssd->dssd_T_Y[beta_z[i]][beta_x[i]][0];
			beta_T_Y[i] = dssd->dssd_T_Y[beta_z[i]][beta_y[i]][0];
			beta_E_delta[i] = beta_E_X[i] - beta_E_Y[i];
		}
	}
}
/*

void EUAnaBeta::GetBetaPos(EUDataSi *dssd, Int_t &ndssd, TTree* tree)
{   
	fire = -1;
	temp_beta_pos.clear();
	dssdhit = 0;
	for (ix = 0; ix < 60; ix++)
	{
		if (dssd->dssd_E_X[ndssd][ix] > 10 && dssd->dssd_T_X[ndssd][ix][0] > -50000)
		{
			for (iy = 0; iy < 40; iy++)
			{
				if (dssd->dssd_E_Y[ndssd][iy] > 10 && dssd->dssd_T_Y[ndssd][iy][0] > -50000)
				{
					fire = 1;
					dssdhit++;
					temp_beta_pos.push_back(pair<int, int> (ix, iy));
				}
				else continue;
			}
		}
		else continue;
	}

	if (fire == 1)
	{
		for (Int_t i = 0; i < temp_beta_pos.size(); i++)
		{
			beta_z  = ndssd;
			beta_x = temp_beta_pos[i].first;
			beta_y = temp_beta_pos[i].second;
			beta_E_X = dssd->dssd_E_X[beta_z][beta_x]*abs(wasabi_gain_x[beta_z][beta_x]) + wasabi_offset_x[beta_z][beta_x];
			beta_E_Y = dssd->dssd_E_Y[beta_z][beta_y]*abs(wasabi_gain_y[beta_z][beta_y]) + wasabi_offset_y[beta_z][beta_y];
			beta_T_X = dssd->dssd_T_Y[beta_z][beta_x][0];
			beta_T_Y = dssd->dssd_T_Y[beta_z][beta_y][0];
			beta_E_delta = beta_E_X - beta_E_Y;
			tree->Fill();
		}
	}
}
*/

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
	F11_TDC_L= dssd->bigrips_F11L;
	F7_PLl = dssd->bigrips_F7L;
	F11_TDC_R = dssd->bigrips_F11R;
	F7_PLr = dssd->bigrips_F7R;
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
		//      gc_Ts[ihit] = tdcs_gain[gc_ch[ihit]]*(hpge.GeCluster_fTDCs[ihit]) + tdcs_offset[gc_ch[ihit]];
		temp_gc_Tl[ihit] = tdcl_gain*hpge->GeCluster_fTDCl[ihit];
		//      gc_Tl[ihit] = tdcl_gain*hpge.GeCluster_fTDCl[ihit] + tdcl_offset;

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
/*
	for (Int_t ihit = 0; ihit < temp_addhit; ihit++)
	{
		if (temp_add_E[ihit] < overflow[temp_add_ch[ihit]])
		{
			add_ch[addhit] = temp_add_ch[ihit];
			add_E[addhit] = temp_add_E[ihit];
			add_T[addhit] = temp_add_T[ihit];
			add_Ts[addhit] = temp_add_Ts[ihit];
			add_Tl[addhit] = temp_add_Tl[ihit];
			
			addhit++;
		}
		else continue;
	}
*/		
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

void EUAnaBeta::CopyEURICA(EUTreeBeta *beta)
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

void EUAnaBeta::CopyDSSD(EUTreeBeta *beta)
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
		memcpy(beta_z, beta->beta_z, dssdhit*sizeof(int));
		memcpy(beta_x, beta->beta_x, dssdhit*sizeof(int));
		memcpy(beta_y, beta->beta_y, dssdhit*sizeof(int));
		memcpy(beta_E_X, beta->beta_E_X, dssdhit*sizeof(double));
		memcpy(beta_E_Y, beta->beta_E_Y, dssdhit*sizeof(double));
		memcpy(beta_E_delta, beta->beta_E_delta, dssdhit*sizeof(double));
		memcpy(beta_T_X, beta->beta_T_X, dssdhit*sizeof(int));
		memcpy(beta_T_Y, beta->beta_T_Y, dssdhit*sizeof(int));
		
	}
/*
	if (eventid == 1)
	{
		dssdhit = beta->dssdhit;
		beta_z = beta->beta_z;
		beta_x = beta->beta_x;
		beta_y = beta->beta_y;
		beta_E_X = beta->beta_E_X;
		beta_E_Y = beta->beta_E_Y;
		beta_E_delta = beta->beta_E_delta;
		beta_T_X = beta->beta_T_X;
		beta_T_Y = beta->beta_T_Y;
	}
*/
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
