default prompt off
exception continueEventLoop on

module sel RootHistogramModule
root file ~/my_src/FitProc/Test/test.root
root init

run_file /nfs/tmp/ting/pipimumu/data/data43/chain/run0_chain.tcl

setup_analysis

run_file $env(C3_SCRIPTS)/RunInfo.tcl
prod sel RunInfoProd

prod sel GoodThingsProd
proc sel /nfs/tmp/ting/build/20080228_FULL/Linux/shlib/FitProc

prod lss
proc lss

go 100000
quit



