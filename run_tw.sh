#!/bin/bash

rm calib/*TW.dat

cd bin

for chnum in {0..83}
do
echo $chnum
../condor_executable_simple.sh CalibTW $chnum
done
exit 0
