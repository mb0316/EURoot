#!/bin/bash

cd ../bin

for chnum in {37..73}
do
echo $chnum
../condor_root_simple.sh ~/EURICA/EURoot/calib/WASABI_Ecal/merge.cc\($chnum\)
done
exit 0
