#!/bin/bash

cd ../bin

#Fully stripped
# MakeBetaMat #Z #Mass #Stat #Emax #Tstart #Tend
../condor_executable_simple.sh MakeBetaIsoMat 51 138 0 2 1000 3000
../condor_executable_simple.sh MakeBetaIsoMat 51 139 0 2 0 500
../condor_executable_simple.sh MakeBetaIsoMat 51 140 1 2 0 500
../condor_executable_simple.sh MakeBetaIsoMat 52 138 1 2 0 500
../condor_executable_simple.sh MakeBetaIsoMat 52 139 0 2 0 500
../condor_executable_simple.sh MakeBetaIsoMat 52 140 0 2 0 500
../condor_executable_simple.sh MakeBetaIsoMat 52 141 0 2 0 500
../condor_executable_simple.sh MakeBetaIsoMat 52 142 1 2 0 500
../condor_executable_simple.sh MakeBetaIsoMat 53 141 0 2 0 500
../condor_executable_simple.sh MakeBetaIsoMat 53 142 0 2 0 500
../condor_executable_simple.sh MakeBetaIsoMat 53 143 0 2 0 500
../condor_executable_simple.sh MakeBetaIsoMat 53 144 0 2 0 500
../condor_executable_simple.sh MakeBetaIsoMat 54 143 0 2 0 500
../condor_executable_simple.sh MakeBetaIsoMat 54 144 0 2 0 500
../condor_executable_simple.sh MakeBetaIsoMat 54 145 0 2 0 500
../condor_executable_simple.sh MakeBetaIsoMat 54 146 0 2 0 500
#../condor_executable_simple.sh MakeBetaMat 54 146 1 3 0 4000

#Proton like

