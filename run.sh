#!/bin/bash

EUPATH=`pwd`

cd bin
./si_ge_merge 1060
./beta_beam_merge 1060
./betadecay 1060
