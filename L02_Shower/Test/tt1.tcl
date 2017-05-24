default prompt off
exception continueEventLoop on
report level info


run_file $env(C3_CVSSRC)/BatchScripts/eventstore_batch_process.tcl
eventstore_batch_process myjob 20070109 20 skim qcd runs 219739 220729

module sel RootHistogramModule
root file /nfs/grp/nw/ting/psi/output_$subjob_id.root

root init

setup_analysis

prod sel GoodThingsProd
proc sel /cdat/tem/tingxiao/build/20080228_FULL/Linux/shlib/L02_Shower


eventstore_batch_process_go 
exit
