int an_func();

#ifndef __CINT__

#include "TApplication.h"
#include "TObject.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TNtuple.h"
#include "TRandom.h"
#include "TChain.h"
#include "TThread.h"
#include "TMath.h"
#include "pi0.h"
#include <iostream>

using namespace std;
                    


void LoadData(TChain &chain);

   
//______________________________________________________________________________
int main()
{
  return an_func();
}
#endif

int an_func()
{
   TChain chain("h10");
   LoadData(chain);

//   chain.Add("/home/tingxiao/my_src/sh/output.root/L02_Shower/nt10");
  
  class pi0 *an = new class pi0;

  an->Init(&chain);
  an->Begin(NULL);

  Long64_t num_events = chain.GetEntries();
  //Long64_t num_events = 5000000;

  cout << "number of events: " << num_events << endl;

  for(Long64_t i=0; i<num_events; i++) {
    an->Process(i);
  }

  an->Terminate();

  return 0;
}
