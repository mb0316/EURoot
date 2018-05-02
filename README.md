# EURoot

This software is for EURICA analysis.

##Directories
calib : Store all calibration macro files.
exe : Store executable source codes. After compiling, building, and installation, bin directory will be created for executable files.
scripts : Store script files in bash shell. These scripts allocate jobs to HTCondors.
source : Store source codes including header and source files. Classes : EUTree, EUData, EUAna

##Classes
EUData : Tree information of root data files for BigRIPS, WASABI, and EURICA.
EUTree : Tree inforamtion of analyzed root data files.
EUAna : Analysis functions.

##Installation
1. Install CMake and ROOT6 in advance.
2. Run install.sh script.
3. CMake will automatically compile, build, and install the software.
4. After finish, please check created bin and build directories.

##Order of scripts
###For beta-delayed analysis
1. Move to script directory.
2. Run multiple_condor.sh.
3. Run run_decay.sh.
4. Run run_decay.sh.
5. Run run_beta_pid.sh.
6. Run run_beta_mat.sh.

**All works are handled by HTCondor. Please check all jobs are finished by HTCondor then move to the next step.
