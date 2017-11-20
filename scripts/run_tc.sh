#!/bin/bash

rm ../calib/*TC.dat

cd ../bin

for chnum in {0..83}
do
echo $chnum
../condor_executable_simple.sh CalibTC $chnum
done
exit 0
