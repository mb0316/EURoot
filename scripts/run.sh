#!/bin/bash

runnum=$1

echo "$runnum"

cd ../bin
./AnaEURICA $runnum
./AnaWASABI $runnum
./AnaBeam $runnum
./MergeDet $runnum
./MergeBeam $runnum
