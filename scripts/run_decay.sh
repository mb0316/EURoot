#!/bin/bash

cd ../bin

for chnum in {1007..1129}
do
echo $chnum
../condor_executable_simple.sh BuildBetaDecay $chnum
done
exit 0
