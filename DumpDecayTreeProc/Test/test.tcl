source_format sel PDSSourceFormat
source create myChain

file add myHotStoreChain /nfs/tmp3/ting/g_MC/chi_c1/ee/pds/mcpass2out-0.pds beginrun startrun event endrun
file add myHotStoreChain /nfs/tmp3/ting/g_MC/chi_c1/ee/pds/mcpass2out-1.pds beginrun startrun event endrun
file add myHotStoreChain /nfs/tmp3/ting/g_MC/chi_c1/ee/pds/mcpass2out-2.pds beginrun startrun event endrun
file add myHotStoreChain /nfs/tmp3/ting/g_MC/chi_c1/ee/pds/mcpass2out-3.pds beginrun startrun event endrun
file add myHotStoreChain /nfs/tmp3/ting/g_MC/chi_c1/ee/pds/mcpass2out-4.pds beginrun startrun event endrun



source activate myChain beginrun startrun event endrun

