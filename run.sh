#!/bin/bash

runnum=$1

echo "$runnum"

cd bin
./si_ge_merge $runnum
./beta_beam_merge $runnum
./betadecay $runnum
