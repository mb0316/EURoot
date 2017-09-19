#ifndef EUANACALIBTW_H
#define EUANACALIBTW_H

#include "EUAnaCalib.h"
#include "EUTreeBeta.h"

#include "TTree.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TH2D.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


class EUAnaCalibTW : public EUAnaCalib, public EUTreeBeta
{
	public :
		EUAnaCalibTW(const char* filename, TTree* tree=0);
		~EUAnaCalibTW();

		void GetProEnergy(TGraphErrors* graph, TH2D* hist, Int_t bin);
		void GetTW(TGraphErrors* graph, Double_t &con1, Double_t &con2, Double_t &con3);
};

#endif
