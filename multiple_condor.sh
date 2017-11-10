#!/bin/bash

for runnum in {1007..1129}
do
echo $runnum
./condor_executable_simple.sh run.sh $runnum
done
exit 0
