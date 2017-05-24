default prompt off
exception continueEventLoop on
report level info



module sel RootHistogramModule
root file /nfs/tmp/ting/pipimumu/efficiency/evtgen/evtgen.root
root init



#run_file /nfs/tmp/ting/pipimumu/plots/decaytree/babayaga/chain_babayaga.tcl
run_file /orange1/ting/my_src/DumpDecayTreeProc/Test/chain_evtgen.tcl



setup_analysis

run_file $env(C3_SCRIPTS)/RunInfo.tcl
prod sel RunInfoProd

proc sel /nfs/tmp/ting/build/20080228_FULL/Linux/shlib/DumpDecayTreeProc





prod lss
proc lss

go

quit


