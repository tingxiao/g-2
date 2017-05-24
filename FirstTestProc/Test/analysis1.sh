#$ -o /orange1/ting/my_src/FirstTestProc/Test/log/sub1.log
#$ -j y


cd /orange1/ting/my_src/FirstTestProc/Test
source /nfs/cleo3/Offline/scripts/cleo3logins
source /nfs/cleo3/scripts/cleo3defs
c3rel 20080228_FULL


suez -f analysis1.tcl


date
pwd

exit

