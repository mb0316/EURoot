#!/bin/bash
echo 'Install EURoot.'

EUPATH=`pwd`
echo "Creating ${EUPATH}/build directory."
mkdir build
echo "Creating ${EUPATH}/bin directory."
mkdir bin

echo 'Build files will be stored at the following directory:'
cd build/
pwd
cmake ..
make

cp ${EUPATH}/build/exe/AnaBeam ${EUPATH}/bin/
cp ${EUPATH}/build/exe/AnaEURICA ${EUPATH}/bin/
cp ${EUPATH}/build/exe/AnaWASABI ${EUPATH}/bin/
cp ${EUPATH}/build/exe/BuildBetaDecay ${EUPATH}/bin/
cp ${EUPATH}/build/exe/BuildIsoDecay ${EUPATH}/bin/
cp ${EUPATH}/build/exe/CalibTW ${EUPATH}/bin/
cp ${EUPATH}/build/exe/CalibTC ${EUPATH}/bin/
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

echo 'Installation has been finished.'
