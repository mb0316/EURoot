#!/bin/bash

cd ../bin

for chnum in {1016..1129}
do
echo $chnum
../condor_executable_simple.sh BuildIsoDecay $chnum
done
exit 0
