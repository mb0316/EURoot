#!/bin/bash

cd ../bin

#Fully stripped
# MakeBetaMat #Z #Mass #Stat #Emax #Tstart #Tend
../condor_executable_simple.sh MakeBetaMat 51 138 0 2 0 4000
../condor_executable_simple.sh MakeBetaMat 51 139 0 2 0 4000
../condor_executable_simple.sh MakeBetaMat 51 140 1 2 0 4000
../condor_executable_simple.sh MakeBetaMat 52 139 0 2 0 4000
../condor_executable_simple.sh MakeBetaMat 52 140 0 2 0 4000
../condor_executable_simple.sh MakeBetaMat 52 141 0 2 0 4000
../condor_executable_simple.sh MakeBetaMat 52 142 1 2 0 4000
../condor_executable_simple.sh MakeBetaMat 53 141 0 2 0 4000
../condor_executable_simple.sh MakeBetaMat 53 142 0 2 0 4000
../condor_executable_simple.sh MakeBetaMat 53 143 0 2 0 4000
../condor_executable_simple.sh MakeBetaMat 53 144 0 2 0 4000
../condor_executable_simple.sh MakeBetaMat 54 143 0 2 0 4000
../condor_executable_simple.sh MakeBetaMat 54 144 0 2 0 4000
../condor_executable_simple.sh MakeBetaMat 54 145 0 2 0 4000
../condor_executable_simple.sh MakeBetaMat 54 146 0 2 0 4000
#../condor_executable_simple.sh MakeBetaMat 54 146 1 3 0 4000

#Proton like

