default prompt off
exception continueEventLoop on
report level info

#run_file /nfs/tmp/ting/pipimumu/plots/decaytree/babayaga/chain_babayaga.tcl
#run_file /orange1/ting/my_src/DumpDecayTreeProc/Test/test.tcl
run_file /nfs/tmp3/ting/g_MC/chi_c1/mumu/chain.tcl

#module sel RootHistogramModule
#root file /orange1/ting/my_src/DumpDecayTreeProc/Test/test.root
#root init



setup_analysis

run_file $env(C3_SCRIPTS)/RunInfo.tcl
prod sel RunInfoProd

proc sel /nfs/tmp/ting/build/20080228_FULL/Linux/shlib/DumpDecayTreeProc_g





prod lss
proc lss

go

quit


