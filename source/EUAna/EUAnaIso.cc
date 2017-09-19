#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EUAna.h"
#include "EUAnaIso.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "EUDataSi.h"
#include "EUDataGe.h"
#include "EUDataBeam.h"
#include "EUTreeIso.h"

EUAnaIso::EUAnaIso(TTree* tree):EUTreeIso(tree)
{
}

EUAnaIso::~EUAnaIso()
{}

void EUAnaIso::GeIsoTDCoffset()
{   
    for (Int_t ihit = 0; ihit < gchit; ihit++)
    {   
        gc_Ts[ihit] = gc_Ts[ihit] - art_iso_tdcs_offset[gc_ch[ihit]];
        gc_Tl[ihit] = gc_Tl[ihit] - art_iso_tdcl_offset[gc_ch[ihit]];
    }
}

void EUAnaIso::CopyTS(EUDataSi *dssd)
{   
    ts = dssd->EventInfo_timestamp[0];
}

void EUAnaIso::CopyBigRIPS(EUDataBeam *beam)
{
    AoQ = beam->RIBeam_aoq37[0];
    Zpro = beam->RIBeam_zed[0];
}

void EUAnaIso::CopyPL(EUDataSi *dssd)
{
    vetoPL1 = dssd->vetoPL_front;
    vetoPL2 = dssd->vetoPL_back;
    F11_TDC_L = dssd->bigrips_F11L;
    F7_PLl = dssd->bigrips_F7L;
    F11_TDC_R = dssd->bigrips_F11R;
    F7_PLr = dssd->bigrips_F7R;
}

void EUAnaIso::CopyPL(EUDataGe *hpge)
{
    F11_ADC_L = hpge->BigRIPSRaw_F11SCI_L[0];
    F11_ADC_R = hpge->BigRIPSRaw_F11SCI_R[0];
}

void EUAnaIso::CopyPL(EUTreeIso *iso)
{
    F11_ADC_L = iso->F11_ADC_L;
    F11_ADC_R = iso->F11_ADC_R;
    F11_TDC_L = iso->F11_TDC_L;
    F11_TDC_R = iso->F11_TDC_R;
}

void EUAnaIso::CopyEURICA(EUDataGe *hpge)
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

void EUAnaIso::ResetPL()
{
	F11_ADC_L = 0;
	F11_ADC_R = 0;
	F11_TDC_L = 0;
	F11_TDC_R = 0;
}

void EUAnaIso::ResetEURICA()
{   
    gchit = 0;
    addhit = 0;
    lbhit = 0;
}

void EUAnaIso::ResetPID()
{   
    AoQ = 0;
    Zpro = 0;
}

void EUAnaIso::Addback()
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

void EUAnaIso::AngleEURICA()
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

