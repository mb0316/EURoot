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
    F11_PLl = dssd->bigrips_F11L;
    F7_PLl = dssd->bigrips_F7L;
    F11_PLr = dssd->bigrips_F11R;
    F7_PLr = dssd->bigrips_F7R;
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

