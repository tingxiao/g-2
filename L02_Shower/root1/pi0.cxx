#define pi0_cxx
// The class definition in pi0.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called everytime a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("pi0.C")
// Root > T->Process("pi0.C","some options")
// Root > T->Process("pi0.C+")
//

#include "pi0.h"
#include <TStyle.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TFile.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <TCanvas.h>
#include "TrackDataLite.h"
#include "TrackDataLite2.h"


void pi0::Begin(TTree *tree)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).
   for (int i=0; i<20; i++) {
     showers[i] = new TrackDataLite();
}
   for (int i=0; i<15; i++) {
     tracks[i] = new TrackDataLite();
}
   for (int i=0; i<15; i++) {
     pi0s[i] = new TrackDataLite2();
}



   h_nt = new TH1D("nt","number of tracks", 15, 0., 15);
   h_ns = new TH1D("ns","number of showers", 20, 0., 20);
   h_np = new TH1D("np","number of pi0s", 15, 0., 15);


   h_e = new TH1D("e", "energies", 360, 0, 0.5);
   h_e_log = new TH1D("e_log", "energies", 200, 3.4, 6.9);
   h_e_all = new TH1D("e_all", "energies", 300, 0, 1.);
   h_mgg = new TH1D("mgg", "M(#gamma#gamma)", 600, 0.05, 0.6);

   h_mpsi = new TH1D("mpsi", "J/psi mass(pi+pi-)", 500, 2.5, 3.5);
   h_mpsi2 = new TH1D("mpsi2", "J/psi mass in 3.097(0.01) range", 500, 2.5, 3.5);
   h_mpsi00 = new TH1D("mpsi00", "J/psi(pi0pi0) mass", 500, 2.5, 3.5);


//   TString option = GetOption();

}

void pi0::SlaveBegin(TTree *tree)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   Init(tree);

   TString option = GetOption();

}

Bool_t pi0::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either TTree::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.

   // WARNING when a selector is used with a TChain, you must use
   //  the pointer to the current TTree to call GetEntry(entry).
   //  The entry is always the local entry number in the current tree.
   //  Assuming that fChain is the pointer to the TChain being processed,
   //  use fChain->GetTree()->GetEntry(entry).
   int pi0_shower[20] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0};
   int good_pi0[15] = {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1};


   fChain->GetEntry(entry);


   showers[0]->SetAll (1,e1*sin(th1)*cos(phi1),e1*sin(th1)*sin(phi1),e1*cos(th1),e1,0,0,0,barrel1,e9251,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[1]->SetAll (2,e2*sin(th2)*cos(phi2),e2*sin(th2)*sin(phi2),e2*cos(th2),e2,0,0,0,barrel2,e9252,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[2]->SetAll (3,e3*sin(th3)*cos(phi3),e3*sin(th3)*sin(phi3),e3*cos(th3),e3,0,0,0,barrel3,e9253,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[3]->SetAll (4,e4*sin(th4)*cos(phi4),e4*sin(th4)*sin(phi4),e4*cos(th4),e4,0,0,0,barrel4,e9254,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[4]->SetAll (5,e5*sin(th5)*cos(phi5),e5*sin(th5)*sin(phi5),e5*cos(th5),e5,0,0,0,barrel5,e9255,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[5]->SetAll (6,e6*sin(th6)*cos(phi6),e6*sin(th6)*sin(phi6),e6*cos(th6),e6,0,0,0,barrel6,e9256,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[6]->SetAll (7,e7*sin(th7)*cos(phi7),e7*sin(th7)*sin(phi7),e7*cos(th7),e7,0,0,0,barrel7,e9257,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[7]->SetAll (8,e8*sin(th8)*cos(phi8),e8*sin(th8)*sin(phi8),e8*cos(th8),e8,0,0,0,barrel8,e9258,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[8]->SetAll (9,e9*sin(th9)*cos(phi9),e9*sin(th9)*sin(phi9),e9*cos(th9),e9,0,0,0,barrel9,e9259,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[9]->SetAll (10,e10*sin(th10)*cos(phi10),e10*sin(th10)*sin(phi10),e10*cos(th10),e10,0,0,0,barrel10,e92510,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[10]->SetAll (11,e11*sin(th11)*cos(phi11),e11*sin(th11)*sin(phi11),e11*cos(th11),e11,0,0,0,barrel11,e92511,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[11]->SetAll (12,e12*sin(th12)*cos(phi12),e12*sin(th12)*sin(phi12),e12*cos(th12),e12,0,0,0,barrel12,e92512,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[12]->SetAll (13,e13*sin(th13)*cos(phi13),e13*sin(th13)*sin(phi13),e13*cos(th13),e13,0,0,0,barrel13,e92513,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[13]->SetAll (14,e14*sin(th14)*cos(phi14),e14*sin(th14)*sin(phi14),e14*cos(th14),e14,0,0,0,barrel14,e92514,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[14]->SetAll (15,e15*sin(th15)*cos(phi15),e15*sin(th15)*sin(phi15),e15*cos(th15),e15,0,0,0,barrel15,e92515,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[15]->SetAll (16,e16*sin(th16)*cos(phi16),e16*sin(th16)*sin(phi16),e16*cos(th16),e16,0,0,0,barrel16,e92516,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[16]->SetAll (17,e17*sin(th17)*cos(phi17),e17*sin(th17)*sin(phi17),e17*cos(th17),e17,0,0,0,barrel17,e92517,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[17]->SetAll (18,e18*sin(th18)*cos(phi18),e18*sin(th18)*sin(phi18),e18*cos(th18),e18,0,0,0,barrel18,e92518,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[18]->SetAll (19,e19*sin(th19)*cos(phi19),e19*sin(th19)*sin(phi19),e19*cos(th19),e19,0,0,0,barrel19,e92519,0,0,0,0,0,0,0,0,0,0,0,0,0);
   showers[19]->SetAll (20,e20*sin(th20)*cos(phi20),e20*sin(th20)*sin(phi20),e20*cos(th20),e20,0,0,0,barrel20,e92520,0,0,0,0,0,0,0,0,0,0,0,0,0);

   tracks[0]->SetAll (1,px1,py1,pz1,te1,0,0,0,0,charge1,0,0,0,0,0,0,0,0,0,0,0,0,0);
   tracks[1]->SetAll (2,px2,py2,pz2,te2,0,0,0,0,charge2,0,0,0,0,0,0,0,0,0,0,0,0,0);
   tracks[2]->SetAll (3,px3,py3,pz3,te3,0,0,0,0,charge3,0,0,0,0,0,0,0,0,0,0,0,0,0);
   tracks[3]->SetAll (4,px4,py4,pz4,te4,0,0,0,0,charge4,0,0,0,0,0,0,0,0,0,0,0,0,0);
   tracks[4]->SetAll (5,px5,py5,pz5,te5,0,0,0,0,charge5,0,0,0,0,0,0,0,0,0,0,0,0,0);
   tracks[5]->SetAll (6,px6,py6,pz6,te6,0,0,0,0,charge6,0,0,0,0,0,0,0,0,0,0,0,0,0);
   tracks[6]->SetAll (7,px7,py7,pz7,te7,0,0,0,0,charge7,0,0,0,0,0,0,0,0,0,0,0,0,0);
   tracks[7]->SetAll (8,px8,py8,pz8,te8,0,0,0,0,charge8,0,0,0,0,0,0,0,0,0,0,0,0,0);
   tracks[8]->SetAll (9,px9,py9,pz9,te9,0,0,0,0,charge9,0,0,0,0,0,0,0,0,0,0,0,0,0);
   tracks[9]->SetAll (10,px10,py10,pz10,te10,0,0,0,0,charge10,0,0,0,0,0,0,0,0,0,0,0,0,0);
   tracks[10]->SetAll (11,px11,py11,pz11,te11,0,0,0,0,charge11,0,0,0,0,0,0,0,0,0,0,0,0,0);
   tracks[11]->SetAll (12,px12,py12,pz12,te12,0,0,0,0,charge12,0,0,0,0,0,0,0,0,0,0,0,0,0);
   tracks[12]->SetAll (13,px13,py13,pz13,te13,0,0,0,0,charge13,0,0,0,0,0,0,0,0,0,0,0,0,0);
   tracks[13]->SetAll (14,px14,py14,pz14,te14,0,0,0,0,charge14,0,0,0,0,0,0,0,0,0,0,0,0,0);
   tracks[14]->SetAll (15,px15,py15,pz15,te15,0,0,0,0,charge15,0,0,0,0,0,0,0,0,0,0,0,0,0);


   pi0s[0]->SetAll (1,p0px1,p0py1,p0pz1,p0e1,p0chisq1,p0pullm1,p0hisid1,p0losid1,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   pi0s[1]->SetAll (2,p0px2,p0py2,p0pz2,p0e2,p0chisq2,p0pullm2,p0hisid2,p0losid2,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   pi0s[2]->SetAll (3,p0px3,p0py3,p0pz3,p0e3,p0chisq3,p0pullm3,p0hisid3,p0losid3,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   pi0s[3]->SetAll (4,p0px4,p0py4,p0pz4,p0e4,p0chisq4,p0pullm4,p0hisid4,p0losid4,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   pi0s[4]->SetAll (5,p0px5,p0py5,p0pz5,p0e5,p0chisq5,p0pullm5,p0hisid5,p0losid5,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   pi0s[5]->SetAll (6,p0px6,p0py6,p0pz6,p0e6,p0chisq6,p0pullm6,p0hisid6,p0losid6,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   pi0s[6]->SetAll (7,p0px7,p0py7,p0pz7,p0e7,p0chisq7,p0pullm7,p0hisid7,p0losid7,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   pi0s[7]->SetAll (8,p0px8,p0py8,p0pz8,p0e8,p0chisq8,p0pullm8,p0hisid8,p0losid8,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   pi0s[8]->SetAll (9,p0px9,p0py9,p0pz9,p0e9,p0chisq9,p0pullm9,p0hisid9,p0losid9,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   pi0s[9]->SetAll (10,p0px10,p0py10,p0pz10,p0e10,p0chisq10,p0pullm10,p0hisid10,p0losid10,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   pi0s[10]->SetAll (11,p0px11,p0py11,p0pz11,p0e11,p0chisq11,p0pullm11,p0hisid11,p0losid11,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   pi0s[11]->SetAll (12,p0px12,p0py12,p0pz12,p0e12,p0chisq12,p0pullm12,p0hisid12,p0losid12,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   pi0s[12]->SetAll (13,p0px13,p0py13,p0pz13,p0e13,p0chisq13,p0pullm13,p0hisid13,p0losid13,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   pi0s[13]->SetAll (14,p0px14,p0py14,p0pz14,p0e14,p0chisq14,p0pullm14,p0hisid14,p0losid14,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
   pi0s[14]->SetAll (15,p0px15,p0py15,p0pz15,p0e15,p0chisq15,p0pullm15,p0hisid15,p0losid15,0,0,0,0,0,0,0,0,0,0,0,0,0,0);


   h_nt->Fill(ntrack);
   h_ns->Fill(nshower);
   h_np->Fill(np0);
   if(ntrack > 15)  ntrack = 15;

   bool psi = false;

   for(int i=0; i<ntrack-1; i++)
     for(int j=i+1; j<ntrack; j++)
       if(tracks[i]->Charge() == -tracks[j]->Charge()){
           double psimass = sqrt( pow(3.686-tracks[i]->E()-tracks[j]->E(),2)
                                  -pow(tracks[i]->Px()+tracks[j]->Px(),2)
                                  -pow(tracks[i]->Py()+tracks[j]->Py(),2)
                                  -pow(tracks[i]->Pz()+tracks[j]->Pz(),2) );
            h_mpsi->Fill(psimass);
            if( fabs(psimass-3.097) <= 0.01){
               psi = true;
//            h_mpsi2->Fill(psimass);
            }
        }

  if(psi)
        return kFALSE;


  if(np0 > 15)  np0 = 15;

   for(int i=0; i<np0; i++)
     {
      if (good_pi0[i] && pi0s[i]->E()>0.){
      double losh1 = pi0s[i]->Lo();
      double hish1 = pi0s[i]->Hi();
      for(int j=0; j<np0; j++)
        {
         if (good_pi0[j] && pi0s[j]->E()>0.){
         double losh2 = pi0s[j]->Lo();
         double hish2 = pi0s[j]->Hi();
        
         if (losh1 == losh2)
            {if (pi0s[i]->PullM() < pi0s[j]->PullM())  good_pi0[j] = 0;}
         if (losh1 == hish2)
            {if (pi0s[i]->PullM() < pi0s[j]->PullM())  good_pi0[j] = 0;}
         if (hish1 == losh2)
            {if (pi0s[i]->PullM() < pi0s[j]->PullM())  good_pi0[j] = 0;}
         if (hish1 == hish2)
            {if (pi0s[i]->PullM() < pi0s[j]->PullM())  good_pi0[j] = 0;}

         }
        }
      }
     }
       
   bool psi2 = false;

   for(int i=0; i<np0-1; i++)
     for(int j=i+1; j<np0; j++)
       if( pi0s[i]->E()>0. && pi0s[j]->E()>0. && good_pi0[i] && good_pi0[j]){     
             double psi00mass = sqrt( pow(3.686-pi0s[i]->E()-pi0s[j]->E(),2)
                                  -pow(pi0s[i]->Px()+pi0s[j]->Px(),2)
                                  -pow(pi0s[i]->Py()+pi0s[j]->Py(),2)
                                  -pow(pi0s[i]->Pz()+pi0s[j]->Pz(),2) );
                 h_mpsi00->Fill(psi00mass);
            if( fabs(psi00mass-3.097) <= 0.02){
               psi2 = true;
            h_mpsi2->Fill(psi00mass);
            }
      }
  if(psi2)
        return kFALSE;


  if(nshower > 20)  nshower = 20;

  for(int i=0; i<nshower-1; i++)
     for(int j=i+1; j<nshower; j++)
        if( (showers[i]->E()>0.) && (showers[j]->E()>0.) && (showers[i]->Charge()>1.) && (showers[j]->Charge()>1.) ) {
           // look for pi0's
          if( (showers[i]->Mass()==1) || (showers[j]->Mass()==1)){          

            double mm = sqrt( pow(showers[i]->E()+showers[j]->E(),2)
                             - pow(showers[i]->Px()+showers[j]->Px(),2)
                             - pow(showers[i]->Py()+showers[j]->Py(),2)
                             - pow(showers[i]->Pz()+showers[j]->Pz(),2) );
            h_mgg->Fill(mm);

           if(fabs(mm-0.135) < 0.015){
              pi0_shower[i] = 1;
              pi0_shower[j] = 1;
           }
          }
          }

    for(int i=0; i<nshower; i++) {
    if(pi0_shower[i]) continue;

    if( showers[i]->Charge()>1. && showers[i]->Mass()==1){
    h_e->Fill(showers[i]->E());
    h_e_log->Fill(log(1000.*showers[i]->E()));
    h_e_all->Fill(showers[i]->E());
    }
  }


   return kTRUE;
}

void pi0::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void pi0::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
  TCanvas *c1 = new TCanvas("c1", "showers analysis", 300, 300, 800, 600);
//  h_mpsi00->Draw();
//  c1->Print("out.ps");

  h_e->Draw();
  c1->Print("out.ps(");
  h_e_log->Draw();
  c1->Print("out.ps");
  h_e_all->Draw();
  c1->Print("out.ps");
  h_nt->Draw();
  c1->Print("out.ps");
  h_ns->Draw();
  c1->Print("out.ps");
  h_np->Draw();
  c1->Print("out.ps");
  h_mpsi->Draw();
  c1->Print("out.ps");
  h_mpsi2->Draw();
  c1->Print("out.ps");
  h_mpsi00->Draw();
  c1->Print("out.ps");
  h_mgg->Draw();
  c1->Print("out.ps)");

  TFile outf("out.root", "recreate");
  h_e->Write();
  h_e_log->Write();
  h_e_all->Write();
  h_nt->Write();
  h_ns->Write();
  h_np->Write();
  h_mpsi->Write();
  h_mpsi00->Write();
  h_mgg->Write();

  outf.Close();

}
