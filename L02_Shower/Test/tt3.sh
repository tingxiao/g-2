#$ -l arch=lx24-x86

#$ -j y

cd /home/tingxiao/my_src/L02_Shower/Test
source /nfs/cleo3/Offline/scripts/cleo3login
source /nfs/cleo3/scripts/cleo3def
c3rel 20080228_FULL

setenv USER_SHLIB /cdat/tem/tingxiao/build/20080228_FULL/Linux/shlib

suez -f tt3.tcl


