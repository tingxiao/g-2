default prompt off
exception continueEventLoop on
report level info

module sel RootHistogramModule
root file /home/tingxiao/my_src/L02_Shower/Test/output.root
root init



run_file /nfs/tmp/ting/psps/chain/run0_chain.tcl

 


setup_analysis
prod sel GoodThingsProd
proc sel /yellow1/ting/build/20080116_FULL/Linux/shlib/L02_Shower


prod lss
proc lss

go 

quit
