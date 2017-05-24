default prompt off
exception continueEventLoop on
report level info


module select LoadGeantModule
module select LoadHbookModule
module select HbookHistogramModule
hbook file /home/tingxiao/my_src/L02_Shower/Test/output.rzn
hbook init


run_file /nfs/tmp/ting/psps/chain/run0_chain.tcl

 


setup_analysis
prod sel GoodThingsProd
proc sel /nfs/tmp/ting/build/20080116_FULL/Linux/L02_Shower


prod lss
proc lss

go 

quit
