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
            if (dssd->dssd_E_X[idssd][ix] > 4000 && dssd->dssd_T_X[idssd][ix][0] > -50000)
            {
                fire_x = 1;
                break;
            }
            else    continue;
        }
        for (iy = 0; iy < 40; iy++)
        {
            if (dssd->dssd_E_Y[idssd][iy] > 4000 && dssd->dssd_T_Y[idssd][iy][0] > -50000)
            {
                fire_y = 1;
                break;
            }
            else    continue;
        }
        if (fire_x == 1 && fire_y == 1)
        {
            temp_z = idssd;
        }

        if (temp_z == 4 && betaPL2_Beam_ADCR > 175) temp_z = -1;
        fire_x = 0;
        fire_y = 0;
    }

    if (temp_z > -1)
    {
        max_tempT = 50000;
        for (ix = 0; ix < 60; ix++)
        {
            if (dssd->dssd_T_X[temp_z][ix][0] > -10000 && dssd->dssd_T_X[temp_z][ix][0] < max_tempT && dssd->dssd_E_X[temp_z][ix] > 4000)
            {
                temp_x = ix;
                max_tempT = dssd->dssd_T_X[temp_z][ix][0];
            }
            else continue;
        }
        max_tempT = 50000;

        for (iy = 0; iy < 40; iy++)
        {
            if (dssd->dssd_T_Y[temp_z][iy][0] > -10000 && dssd->dssd_T_Y[temp_z][iy][0] < max_tempT && dssd->dssd_E_Y[temp_z][iy] > 4000)
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

void EUAnaBeta::GetBetaPos(EUDataSi *dssd, Int_t &ndssd)
{   
	fire = -1;
	for (ix = 0; ix < 60; ix++)
	{
		if (dssd->dssd_E_X[ndssd][ix] > 10 && dssd->dssd_E_X[ndssd][ix] <= 4000 && dssd->dssd_T_X[ndssd][ix][0] > -10000)
		{
			for (iy = 0; iy < 40; iy++)
			{
				if (dssd->dssd_E_Y[ndssd][iy] > 10 && dssd->dssd_E_Y[ndssd][iy] <= 4000 && dssd->dssd_T_Y[ndssd][iy][0] > -10000)
				{
					fire = 1;
					beta_x = ix;
					beta_y = iy;
					break;
				}
				else continue;
			}
		}
		else continue;
	}
	if (fire == 1)
	{
		beta_z = ndssd;
		beta_E_X = dssd->dssd_E_X[beta_z][beta_x];
		beta_E_Y = dssd->dssd_E_Y[beta_z][beta_y];
		beta_T_X = dssd->dssd_T_Y[beta_z][beta_x][0];
		beta_T_Y = dssd->dssd_T_Y[beta_z][beta_y][0];

		fire = 0;
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

void EUAnaBeta::CopyTS(EUTreeBeta *beta)
{   
    ts = beta->ts;
	eventid = beta->eventid;
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
    F11_PLl = dssd->bigrips_F11L;
    F7_PLl = dssd->bigrips_F7L;
    F11_PLr = dssd->bigrips_F11R;
    F7_PLr = dssd->bigrips_F7R;
}

void EUAnaBeta::CopyEURICA(EUDataGe *hpge)
{
    gchit = hpge->GeCluster_;
    for (Int_t ihit = 0; ihit < gchit; ihit++)
    {
        gc_ch[ihit] = hpge->GeCluster_channel[ihit];
        gc_T[ihit] = hpge->GeCluster_fTime[ihit];

        gc_E[ihit] = adc_gain[gc_ch[ihit]]*(hpge->GeCluster_fADCe[ihit]) + adc_offset[gc_ch[ihit]];
        gc_Ts[ihit] = tdcs_gain[gc_ch[ihit]]*(hpge->GeCluster_fTDCs[ihit]);
//      gc_Ts[ihit] = tdcs_gain[gc_ch[ihit]]*(hpge.GeCluster_fTDCs[ihit]) + tdcs_offset[gc_ch[ihit]];
        gc_Tl[ihit] = tdcl_gain*hpge->GeCluster_fTDCl[ihit];
//      gc_Tl[ihit] = tdcl_gain*hpge.GeCluster_fTDCl[ihit] + tdcl_offset;

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
	dssdhit = beta->dssdhit;
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
		beta_z = beta->beta_z;
		beta_x = beta->beta_x;
		beta_y = beta->beta_y;
		beta_E_X = beta->beta_E_X;
		beta_E_Y = beta->beta_E_Y;
		beta_T_X = beta->beta_T_X;
		beta_T_Y = beta->beta_T_Y;
	}
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
	dssdhit = 0;
	ion_z = -10;
	ion_x = -10;
	ion_y = -10;
	ion_E_X = 0;
	ion_E_Y = 0;
	ion_T_X = 0;
	ion_T_Y = 0;
	beta_z = -5;
	beta_x = -5;
	beta_y = -5;
	beta_E_X = 0;
	beta_E_Y = 0;
	beta_T_X = 0;
	beta_T_Y = 0;
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
		
void EUAnaBeta::AngleEURICA()
{
    for (Int_t i = 0; i < gchit; i++)
    {
        if (gc_ch[i] >= 0 && gc_ch[i] <= 6)
        {
            gc_cl[i] = 0;
            gc_ang[i] = 51;
        }
        if (gc_ch[i] >= 7 && gc_ch[i] <= 13)
        {
            gc_cl[i] = 1;
            gc_ang[i] = 51;
        }
        if (gc_ch[i] >= 14 && gc_ch[i] <= 20)
        {
            gc_cl[i] = 2;
            gc_ang[i] = 51;
        }
        if (gc_ch[i] >= 21 && gc_ch[i] <= 27)
        {
            gc_cl[i] = 3;
            gc_ang[i] = 129;
        }
        if (gc_ch[i] >= 28 && gc_ch[i] <= 34)
        {
            gc_cl[i] = 4;
            gc_ang[i] = 129;
        }
        if (gc_ch[i] >= 35 && gc_ch[i] <= 41)
        {
            gc_cl[i] = 5;
            gc_ang[i] = 129;
        }
        if (gc_ch[i] >= 42 && gc_ch[i] <= 48)
        {
            gc_cl[i] = 6;
            gc_ang[i] = 90;
        }
        if (gc_ch[i] >= 49 && gc_ch[i] <= 55)
        {
            gc_cl[i] = 7;
            gc_ang[i] = 90;
        }
        if (gc_ch[i] >= 56 && gc_ch[i] <= 62)
        {
            gc_cl[i] = 8;
            gc_ang[i] = 51;
        }
        if (gc_ch[i] >= 63 && gc_ch[i] <= 69)
        {
            gc_cl[i] = 9;
            gc_ang[i] = 51;
        }
        if (gc_ch[i] >= 70 && gc_ch[i] <= 76)
        {
            gc_cl[i] = 10;
            gc_ang[i] = 129;
        }
        if (gc_ch[i] >= 77 && gc_ch[i] <= 83)
        {
            gc_cl[i] = 11;
            gc_ang[i] = 129;
        }
    }
    for (Int_t i = 0; i < addhit; i++)
    {
        if (add_ch[i] >= 0 && add_ch[i] <= 6)
        {
            add_cl[i] = 0;
            add_ang[i] = 51;
        }
        if (add_ch[i] >= 7 && add_ch[i] <= 13)
        {
            add_cl[i] = 1;
            add_ang[i] = 51;
        }
        if (add_ch[i] >= 14 && add_ch[i] <= 20)
        {
            add_cl[i] = 2;
            add_ang[i] = 51;
        }
        if (add_ch[i] >= 21 && add_ch[i] <= 27)
        {
            add_cl[i] = 3;
            add_ang[i] = 129;
        }
        if (add_ch[i] >= 28 && add_ch[i] <= 34)
        {
            add_cl[i] = 4;
            add_ang[i] = 129;
        }
        if (add_ch[i] >= 35 && add_ch[i] <= 41)
        {
            add_cl[i] = 5;
            add_ang[i] = 129;
        }
        if (add_ch[i] >= 42 && add_ch[i] <= 48)
        {
            add_cl[i] = 6;
            add_ang[i] = 90;
        }
        if (add_ch[i] >= 49 && add_ch[i] <= 55)
        {
            add_cl[i] = 7;
            add_ang[i] = 90;
        }
        if (add_ch[i] >= 56 && add_ch[i] <= 62)
        {
            add_cl[i] = 8;
            add_ang[i] = 51;
        }
        if (add_ch[i] >= 63 && add_ch[i] <= 69)
        {
            add_cl[i] = 9;
            add_ang[i] = 51;
        }
        if (add_ch[i] >= 70 && add_ch[i] <= 76)
        {
            add_cl[i] = 10;
            add_ang[i] = 129;
        }
        if (add_ch[i] >= 77 && add_ch[i] <= 83)
        {
            add_cl[i] = 11;
            add_ang[i] = 129;
        }
    }
}

