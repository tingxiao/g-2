default prompt off
exception continueEventLoop on
report level info

module sel RootHistogramModule
root file /orange1/ting/my_src/FirstTestProc/Test/cluster.root
root init



run_file /orange1/ting/my_src/FirstTestProc/Test/chain/chain0.tcl
run_file /orange1/ting/my_src/FirstTestProc/Test/chain/chain1.tcl
run_file /orange1/ting/my_src/FirstTestProc/Test/chain/chain2.tcl
run_file /orange1/ting/my_src/FirstTestProc/Test/chain/chain3.tcl
run_file /orange1/ting/my_src/FirstTestProc/Test/chain/chain4.tcl
run_file /orange1/ting/my_src/FirstTestProc/Test/chain/chain5.tcl
run_file /orange1/ting/my_src/FirstTestProc/Test/chain/chain6.tcl
run_file /orange1/ting/my_src/FirstTestProc/Test/chain/chain7.tcl
run_file /orange1/ting/my_src/FirstTestProc/Test/chain/chain8.tcl
run_file /orange1/ting/my_src/FirstTestProc/Test/chain/chain9.tcl




setup_analysis
prod sel GoodThingsProd
proc sel  /nfs/tmp/ting/build/20080228_FULL/Linux/shlib/FirstTestProc


prod lss
proc lss

go

quit

