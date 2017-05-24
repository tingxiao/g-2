default prompt off
exception continueEventLoop on
report level info




module sel RootHistogramModule
root file /home/tingxiao/my_src/L02_Shower/Test/output.root
root init



 
module sel EventStoreModule
eventstore in 20070109 physics qcd dataset data42



setup_analysis
prod sel GoodThingsProd
proc sel /cdat/tem/tingxiao/build/20080228_FULL/Linux/shlib/L02_Shower


go 5000 
exit
