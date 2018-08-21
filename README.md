# EURoot

This software is for EURICA analysis.

## Directories
calib : Store all calibration macro files.

exe : Store executable source codes. After compiling, building, and installation, bin directory will be created for executable files.

scripts : Store script files in bash shell. These scripts allocate jobs to HTCondors.

source : Store source codes including header and source files. Classes : EUTree, EUData, EUAna

## Classes
EUData : Tree information of root data files for BigRIPS, WASABI, and EURICA.

EUTree : Tree inforamtion of analyzed root data files.

EUAna : Analysis functions.

## Installation
1. Install CMake and ROOT6 in advance.
2. Run install.sh script.
3. CMake will automatically compile, build, and install the software.
4. After finish, please check created bin and build directories.

## Calibrations
1. Move to calib/ directory.
2. Run all calibration source codes.

EURICA_Ecal : Energy calibration of EURICA.

EURICA_Effcal : Efficiency calibration of EURICA.

EURICA_Overflow : Get overflow value for each EURICA channel to remove.

EURICA_TWcal : Time-walk correction for EURICA. This must be done after MergeBeam process.

EURICA_Tcal : Channnel to time calibration for analog EURICA TDC.

WASABI_Ecal : Energy calibration for WASABI using source data.

WASABI_Ecal_Beam : Energy calibration for selected layers of WASABI using beam data.

WASABI_Mapping : Check the channel mapping of WASABI.

WASABI_Tcal : Timing calibration for ion implantation in WASABI.

WASABI_Tcal_beta : Timing calibration for beta events in WASABI.


Please follow procedures explained in each README file.

## Executable codes
AnaBeam : BigRIPS analysis.

AnaWASABI : WASABI analysis. Tzero, energy calibrations are used. Algorithms for ion implantation and beta hit positions.'

AnaEURICA : EURICA analysis. Calibrate energy, timing of EURICA.

MergeDet : Merge analyzed WASABI and EURICA data. WASABI and EURICA energy are calibrated by beam data in this process.

MergeBeam : Merge BigRIPS and detector data.

BuildBetaDecay : Beta decay analysis. Ion and beta correlation using TS will be anlyzed in this process. Time-walk correction is adopted in this process. Before run this program, run EURICA_TWcal first.

BuildIsoDecay : Isomeric decay analysis. Time-walk correction is adopted in this process. Before run this program, run EURICA_TWcal first.

MakeOneTree : Make a root file storing all run data.

MakeSepPID : Make each root file for each isotope.

MakeMAT : Make coincident matrix data files.

## Order of scripts
1. Move to script directory.
2. Run multiple_condor.sh.

### For beta-delayed analysis
3. Run run_decay.sh.
4. Run run_beta_pid.sh.
5. Run run_beta_mat.sh.

### For isomeric decay analysis
3. Run run_iso_decay.sh.
4. Run run_iso_pid.sh.
5. Run run_iso_mat.sh.

**`All works are handled by HTCondor. Please check all jobs are finished by HTCondor then move to the next step.`**
