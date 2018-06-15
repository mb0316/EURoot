#!/bin/bash
echo 'Install EURoot.'

EUPATH=`pwd`
echo "Creating ${EUPATH}/build directory."
mkdir build
echo "Creating ${EUPATH}/bin directory."
mkdir bin

echo "Creating ${EUPATH}/data directory."
mkdir -p data/EURICA_Calib
mkdir -p data/WASABI_Calib
mkdir -p data/LaBr_Calib 

echo "Creating ${EUPATH}/results directory."
mkdir -p results/AnaBeam
mkdir -p results/AnaWASABI
mkdir -p results/AnaEURICA
mkdir -p results/MergeDet
mkdir -p results/MergeBeam
mkdir -p results/BuildBetaDecay
mkdir -p results/BuildIsoDecay
mkdir -p results/PID
mkdir -p results/MAT

echo 'Build files will be stored at the following directory:'
cd build/
pwd
cmake ..
make -j

cp ${EUPATH}/build/exe/AnaBeam ${EUPATH}/bin/
cp ${EUPATH}/build/exe/AnaEURICA ${EUPATH}/bin/
cp ${EUPATH}/build/exe/AnaWASABI ${EUPATH}/bin/
cp ${EUPATH}/build/exe/BuildBetaDecay ${EUPATH}/bin/
cp ${EUPATH}/build/exe/BuildIsoDecay ${EUPATH}/bin/
cp ${EUPATH}/build/exe/MakeBetaMat ${EUPATH}/bin/
cp ${EUPATH}/build/exe/MakeIsoMat ${EUPATH}/bin/
cp ${EUPATH}/build/exe/MakeOneTree ${EUPATH}/bin/
cp ${EUPATH}/build/exe/MakeSepPID ${EUPATH}/bin/
cp ${EUPATH}/build/exe/MergeBeam ${EUPATH}/bin/
cp ${EUPATH}/build/exe/MergeDet ${EUPATH}/bin/

echo 'Executable programs will be stored at the following directory:'
cd ../bin/
pwd

echo 'Following exe programs exist:'
ls
