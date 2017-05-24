#$ -o /orange1/ting/my_src/DumpDecayTreeProc/Test/babayaga.log

cd /orange1/ting/my_src/DumpDecayTreeProc/Test
source /nfs/cleo3/Offline/scripts/cleo3login
source /nfs/cleo3/scripts/cleo3def
c3rel 20080228_FULL

setenv USER_SHLIB /nfs/tmp/ting/build/20080228_FULL/Linux/shlib

suez -f babayaga.tcl

date

