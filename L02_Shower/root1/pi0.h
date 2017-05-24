//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Aug 29 15:14:07 2008 by ROOT version 5.10/00
// from TTree nt10/tuple
// found on file: output.root
//////////////////////////////////////////////////////////

#ifndef pi0_h
#define pi0_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH1D.h>
#include <TH1F.h>
#include "TrackDataLite.h"
#include "TrackDataLite2.h"

class pi0 : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leave types
   Float_t         nshower;
   Float_t         ntrack;
   Float_t         np0;
   Float_t         e1;
   Float_t         th1;
   Float_t         phi1;
   Float_t         e9251;
   Float_t         barrel1;
   Float_t         e2;
   Float_t         th2;
   Float_t         phi2;
   Float_t         e9252;
   Float_t         barrel2;
   Float_t         e3;
   Float_t         th3;
   Float_t         phi3;
   Float_t         e9253;
   Float_t         barrel3;
   Float_t         e4;
   Float_t         th4;
   Float_t         phi4;
   Float_t         e9254;
   Float_t         barrel4;
   Float_t         e5;
   Float_t         th5;
   Float_t         phi5;
   Float_t         e9255;
   Float_t         barrel5;
   Float_t         e6;
   Float_t         th6;
   Float_t         phi6;
   Float_t         e9256;
   Float_t         barrel6;
   Float_t         e7;
   Float_t         th7;
   Float_t         phi7;
   Float_t         e9257;
   Float_t         barrel7;
   Float_t         e8;
   Float_t         th8;
   Float_t         phi8;
   Float_t         e9258;
   Float_t         barrel8;
   Float_t         e9;
   Float_t         th9;
   Float_t         phi9;
   Float_t         e9259;
   Float_t         barrel9;
   Float_t         e10;
   Float_t         th10;
   Float_t         phi10;
   Float_t         e92510;
   Float_t         barrel10;
   Float_t         e11;
   Float_t         th11;
   Float_t         phi11;
   Float_t         e92511;
   Float_t         barrel11;
   Float_t         e12;
   Float_t         th12;
   Float_t         phi12;
   Float_t         e92512;
   Float_t         barrel12;
   Float_t         e13;
   Float_t         th13;
   Float_t         phi13;
   Float_t         e92513;
   Float_t         barrel13;
   Float_t         e14;
   Float_t         th14;
   Float_t         phi14;
   Float_t         e92514;
   Float_t         barrel14;
   Float_t         e15;
   Float_t         th15;
   Float_t         phi15;
   Float_t         e92515;
   Float_t         barrel15;
   Float_t         e16;
   Float_t         th16;
   Float_t         phi16;
   Float_t         e92516;
   Float_t         barrel16;
   Float_t         e17;
   Float_t         th17;
   Float_t         phi17;
   Float_t         e92517;
   Float_t         barrel17;
   Float_t         e18;
   Float_t         th18;
   Float_t         phi18;
   Float_t         e92518;
   Float_t         barrel18;
   Float_t         e19;
   Float_t         th19;
   Float_t         phi19;
   Float_t         e92519;
   Float_t         barrel19;
   Float_t         e20;
   Float_t         th20;
   Float_t         phi20;
   Float_t         e92520;
   Float_t         barrel20;
   Float_t         te1;
   Float_t         px1;
   Float_t         py1;
   Float_t         pz1;
   Float_t         charge1;
   Float_t         te2;
   Float_t         px2;
   Float_t         py2;
   Float_t         pz2;
   Float_t         charge2;
   Float_t         te3;
   Float_t         px3;
   Float_t         py3;
   Float_t         pz3;
   Float_t         charge3;
   Float_t         te4;
   Float_t         px4;
   Float_t         py4;
   Float_t         pz4;
   Float_t         charge4;
   Float_t         te5;
   Float_t         px5;
   Float_t         py5;
   Float_t         pz5;
   Float_t         charge5;
   Float_t         te6;
   Float_t         px6;
   Float_t         py6;
   Float_t         pz6;
   Float_t         charge6;
   Float_t         te7;
   Float_t         px7;
   Float_t         py7;
   Float_t         pz7;
   Float_t         charge7;
   Float_t         te8;
   Float_t         px8;
   Float_t         py8;
   Float_t         pz8;
   Float_t         charge8;
   Float_t         te9;
   Float_t         px9;
   Float_t         py9;
   Float_t         pz9;
   Float_t         charge9;
   Float_t         te10;
   Float_t         px10;
   Float_t         py10;
   Float_t         pz10;
   Float_t         charge10;
   Float_t         te11;
   Float_t         px11;
   Float_t         py11;
   Float_t         pz11;
   Float_t         charge11;
   Float_t         te12;
   Float_t         px12;
   Float_t         py12;
   Float_t         pz12;
   Float_t         charge12;
   Float_t         te13;
   Float_t         px13;
   Float_t         py13;
   Float_t         pz13;
   Float_t         charge13;
   Float_t         te14;
   Float_t         px14;
   Float_t         py14;
   Float_t         pz14;
   Float_t         charge14;
   Float_t         te15;
   Float_t         px15;
   Float_t         py15;
   Float_t         pz15;
   Float_t         charge15;
   Float_t         p0e1;
   Float_t         p0px1;
   Float_t         p0py1;
   Float_t         p0pz1;
   Float_t         p0chisq1;
   Float_t         p0pullm1;
   Float_t         p0hisid1;
   Float_t         p0losid1;
   Float_t         p0e2;
   Float_t         p0px2;
   Float_t         p0py2;
   Float_t         p0pz2;
   Float_t         p0chisq2;
   Float_t         p0pullm2;
   Float_t         p0hisid2;
   Float_t         p0losid2;
   Float_t         p0e3;
   Float_t         p0px3;
   Float_t         p0py3;
   Float_t         p0pz3;
   Float_t         p0chisq3;
   Float_t         p0pullm3;
   Float_t         p0hisid3;
   Float_t         p0losid3;
   Float_t         p0e4;
   Float_t         p0px4;
   Float_t         p0py4;
   Float_t         p0pz4;
   Float_t         p0chisq4;
   Float_t         p0pullm4;
   Float_t         p0hisid4;
   Float_t         p0losid4;
   Float_t         p0e5;
   Float_t         p0px5;
   Float_t         p0py5;
   Float_t         p0pz5;
   Float_t         p0chisq5;
   Float_t         p0pullm5;
   Float_t         p0hisid5;
   Float_t         p0losid5;
   Float_t         p0e6;
   Float_t         p0px6;
   Float_t         p0py6;
   Float_t         p0pz6;
   Float_t         p0chisq6;
   Float_t         p0pullm6;
   Float_t         p0hisid6;
   Float_t         p0losid6;
   Float_t         p0e7;
   Float_t         p0px7;
   Float_t         p0py7;
   Float_t         p0pz7;
   Float_t         p0chisq7;
   Float_t         p0pullm7;
   Float_t         p0hisid7;
   Float_t         p0losid7;
   Float_t         p0e8;
   Float_t         p0px8;
   Float_t         p0py8;
   Float_t         p0pz8;
   Float_t         p0chisq8;
   Float_t         p0pullm8;
   Float_t         p0hisid8;
   Float_t         p0losid8;
   Float_t         p0e9;
   Float_t         p0px9;
   Float_t         p0py9;
   Float_t         p0pz9;
   Float_t         p0chisq9;
   Float_t         p0pullm9;
   Float_t         p0hisid9;
   Float_t         p0losid9;
   Float_t         p0e10;
   Float_t         p0px10;
   Float_t         p0py10;
   Float_t         p0pz10;
   Float_t         p0chisq10;
   Float_t         p0pullm10;
   Float_t         p0hisid10;
   Float_t         p0losid10;
   Float_t         p0e11;
   Float_t         p0px11;
   Float_t         p0py11;
   Float_t         p0pz11;
   Float_t         p0chisq11;
   Float_t         p0pullm11;
   Float_t         p0hisid11;
   Float_t         p0losid11;
   Float_t         p0e12;
   Float_t         p0px12;
   Float_t         p0py12;
   Float_t         p0pz12;
   Float_t         p0chisq12;
   Float_t         p0pullm12;
   Float_t         p0hisid12;
   Float_t         p0losid12;
   Float_t         p0e13;
   Float_t         p0px13;
   Float_t         p0py13;
   Float_t         p0pz13;
   Float_t         p0chisq13;
   Float_t         p0pullm13;
   Float_t         p0hisid13;
   Float_t         p0losid13;
   Float_t         p0e14;
   Float_t         p0px14;
   Float_t         p0py14;
   Float_t         p0pz14;
   Float_t         p0chisq14;
   Float_t         p0pullm14;
   Float_t         p0hisid14;
   Float_t         p0losid14;
   Float_t         p0e15;
   Float_t         p0px15;
   Float_t         p0py15;
   Float_t         p0pz15;
   Float_t         p0chisq15;
   Float_t         p0pullm15;
   Float_t         p0hisid15;
   Float_t         p0losid15;

   // List of branches
   TBranch        *b_nshower;   //!
   TBranch        *b_ntrack;   //!
   TBranch        *b_np0;   //!
   TBranch        *b_e1;   //!
   TBranch        *b_th1;   //!
   TBranch        *b_phi1;   //!
   TBranch        *b_e9251;   //!
   TBranch        *b_barrel1;   //!
   TBranch        *b_e2;   //!
   TBranch        *b_th2;   //!
   TBranch        *b_phi2;   //!
   TBranch        *b_e9252;   //!
   TBranch        *b_barrel2;   //!
   TBranch        *b_e3;   //!
   TBranch        *b_th3;   //!
   TBranch        *b_phi3;   //!
   TBranch        *b_e9253;   //!
   TBranch        *b_barrel3;   //!
   TBranch        *b_e4;   //!
   TBranch        *b_th4;   //!
   TBranch        *b_phi4;   //!
   TBranch        *b_e9254;   //!
   TBranch        *b_barrel4;   //!
   TBranch        *b_e5;   //!
   TBranch        *b_th5;   //!
   TBranch        *b_phi5;   //!
   TBranch        *b_e9255;   //!
   TBranch        *b_barrel5;   //!
   TBranch        *b_e6;   //!
   TBranch        *b_th6;   //!
   TBranch        *b_phi6;   //!
   TBranch        *b_e9256;   //!
   TBranch        *b_barrel6;   //!
   TBranch        *b_e7;   //!
   TBranch        *b_th7;   //!
   TBranch        *b_phi7;   //!
   TBranch        *b_e9257;   //!
   TBranch        *b_barrel7;   //!
   TBranch        *b_e8;   //!
   TBranch        *b_th8;   //!
   TBranch        *b_phi8;   //!
   TBranch        *b_e9258;   //!
   TBranch        *b_barrel8;   //!
   TBranch        *b_e9;   //!
   TBranch        *b_th9;   //!
   TBranch        *b_phi9;   //!
   TBranch        *b_e9259;   //!
   TBranch        *b_barrel9;   //!
   TBranch        *b_e10;   //!
   TBranch        *b_th10;   //!
   TBranch        *b_phi10;   //!
   TBranch        *b_e92510;   //!
   TBranch        *b_barrel10;   //!
   TBranch        *b_e11;   //!
   TBranch        *b_th11;   //!
   TBranch        *b_phi11;   //!
   TBranch        *b_e92511;   //!
   TBranch        *b_barrel11;   //!
   TBranch        *b_e12;   //!
   TBranch        *b_th12;   //!
   TBranch        *b_phi12;   //!
   TBranch        *b_e92512;   //!
   TBranch        *b_barrel12;   //!
   TBranch        *b_e13;   //!
   TBranch        *b_th13;   //!
   TBranch        *b_phi13;   //!
   TBranch        *b_e92513;   //!
   TBranch        *b_barrel13;   //!
   TBranch        *b_e14;   //!
   TBranch        *b_th14;   //!
   TBranch        *b_phi14;   //!
   TBranch        *b_e92514;   //!
   TBranch        *b_barrel14;   //!
   TBranch        *b_e15;   //!
   TBranch        *b_th15;   //!
   TBranch        *b_phi15;   //!
   TBranch        *b_e92515;   //!
   TBranch        *b_barrel15;   //!
   TBranch        *b_e16;   //!
   TBranch        *b_th16;   //!
   TBranch        *b_phi16;   //!
   TBranch        *b_e92516;   //!
   TBranch        *b_barrel16;   //!
   TBranch        *b_e17;   //!
   TBranch        *b_th17;   //!
   TBranch        *b_phi17;   //!
   TBranch        *b_e92517;   //!
   TBranch        *b_barrel17;   //!
   TBranch        *b_e18;   //!
   TBranch        *b_th18;   //!
   TBranch        *b_phi18;   //!
   TBranch        *b_e92518;   //!
   TBranch        *b_barrel18;   //!
   TBranch        *b_e19;   //!
   TBranch        *b_th19;   //!
   TBranch        *b_phi19;   //!
   TBranch        *b_e92519;   //!
   TBranch        *b_barrel19;   //!
   TBranch        *b_e20;   //!
   TBranch        *b_th20;   //!
   TBranch        *b_phi20;   //!
   TBranch        *b_e92520;   //!
   TBranch        *b_barrel20;   //!
   TBranch        *b_te1;   //!
   TBranch        *b_px1;   //!
   TBranch        *b_py1;   //!
   TBranch        *b_pz1;   //!
   TBranch        *b_charge1;   //!
   TBranch        *b_te2;   //!
   TBranch        *b_px2;   //!
   TBranch        *b_py2;   //!
   TBranch        *b_pz2;   //!
   TBranch        *b_charge2;   //!
   TBranch        *b_te3;   //!
   TBranch        *b_px3;   //!
   TBranch        *b_py3;   //!
   TBranch        *b_pz3;   //!
   TBranch        *b_charge3;   //!
   TBranch        *b_te4;   //!
   TBranch        *b_px4;   //!
   TBranch        *b_py4;   //!
   TBranch        *b_pz4;   //!
   TBranch        *b_charge4;   //!
   TBranch        *b_te5;   //!
   TBranch        *b_px5;   //!
   TBranch        *b_py5;   //!
   TBranch        *b_pz5;   //!
   TBranch        *b_charge5;   //!
   TBranch        *b_te6;   //!
   TBranch        *b_px6;   //!
   TBranch        *b_py6;   //!
   TBranch        *b_pz6;   //!
   TBranch        *b_charge6;   //!
   TBranch        *b_te7;   //!
   TBranch        *b_px7;   //!
   TBranch        *b_py7;   //!
   TBranch        *b_pz7;   //!
   TBranch        *b_charge7;   //!
   TBranch        *b_te8;   //!
   TBranch        *b_px8;   //!
   TBranch        *b_py8;   //!
   TBranch        *b_pz8;   //!
   TBranch        *b_charge8;   //!
   TBranch        *b_te9;   //!
   TBranch        *b_px9;   //!
   TBranch        *b_py9;   //!
   TBranch        *b_pz9;   //!
   TBranch        *b_charge9;   //!
   TBranch        *b_te10;   //!
   TBranch        *b_px10;   //!
   TBranch        *b_py10;   //!
   TBranch        *b_pz10;   //!
   TBranch        *b_charge10;   //!
   TBranch        *b_te11;   //!
   TBranch        *b_px11;   //!
   TBranch        *b_py11;   //!
   TBranch        *b_pz11;   //!
   TBranch        *b_charge11;   //!
   TBranch        *b_te12;   //!
   TBranch        *b_px12;   //!
   TBranch        *b_py12;   //!
   TBranch        *b_pz12;   //!
   TBranch        *b_charge12;   //!
   TBranch        *b_te13;   //!
   TBranch        *b_px13;   //!
   TBranch        *b_py13;   //!
   TBranch        *b_pz13;   //!
   TBranch        *b_charge13;   //!
   TBranch        *b_te14;   //!
   TBranch        *b_px14;   //!
   TBranch        *b_py14;   //!
   TBranch        *b_pz14;   //!
   TBranch        *b_charge14;   //!
   TBranch        *b_te15;   //!
   TBranch        *b_px15;   //!
   TBranch        *b_py15;   //!
   TBranch        *b_pz15;   //!
   TBranch        *b_charge15;   //!
   TBranch        *b_p0e1;   //!
   TBranch        *b_p0px1;   //!
   TBranch        *b_p0py1;   //!
   TBranch        *b_p0pz1;   //!
   TBranch        *b_p0chisq1;   //!
   TBranch        *b_p0pullm1;   //!
   TBranch        *b_p0hisid1;   //!
   TBranch        *b_p0losid1;   //!
   TBranch        *b_p0e2;   //!
   TBranch        *b_p0px2;   //!
   TBranch        *b_p0py2;   //!
   TBranch        *b_p0pz2;   //!
   TBranch        *b_p0chisq2;   //!
   TBranch        *b_p0pullm2;   //!
   TBranch        *b_p0hisid2;   //!
   TBranch        *b_p0losid2;   //!
   TBranch        *b_p0e3;   //!
   TBranch        *b_p0px3;   //!
   TBranch        *b_p0py3;   //!
   TBranch        *b_p0pz3;   //!
   TBranch        *b_p0chisq3;   //!
   TBranch        *b_p0pullm3;   //!
   TBranch        *b_p0hisid3;   //!
   TBranch        *b_p0losid3;   //!
   TBranch        *b_p0e4;   //!
   TBranch        *b_p0px4;   //!
   TBranch        *b_p0py4;   //!
   TBranch        *b_p0pz4;   //!
   TBranch        *b_p0chisq4;   //!
   TBranch        *b_p0pullm4;   //!
   TBranch        *b_p0hisid4;   //!
   TBranch        *b_p0losid4;   //!
   TBranch        *b_p0e5;   //!
   TBranch        *b_p0px5;   //!
   TBranch        *b_p0py5;   //!
   TBranch        *b_p0pz5;   //!
   TBranch        *b_p0chisq5;   //!
   TBranch        *b_p0pullm5;   //!
   TBranch        *b_p0hisid5;   //!
   TBranch        *b_p0losid5;   //!
   TBranch        *b_p0e6;   //!
   TBranch        *b_p0px6;   //!
   TBranch        *b_p0py6;   //!
   TBranch        *b_p0pz6;   //!
   TBranch        *b_p0chisq6;   //!
   TBranch        *b_p0pullm6;   //!
   TBranch        *b_p0hisid6;   //!
   TBranch        *b_p0losid6;   //!
   TBranch        *b_p0e7;   //!
   TBranch        *b_p0px7;   //!
   TBranch        *b_p0py7;   //!
   TBranch        *b_p0pz7;   //!
   TBranch        *b_p0chisq7;   //!
   TBranch        *b_p0pullm7;   //!
   TBranch        *b_p0hisid7;   //!
   TBranch        *b_p0losid7;   //!
   TBranch        *b_p0e8;   //!
   TBranch        *b_p0px8;   //!
   TBranch        *b_p0py8;   //!
   TBranch        *b_p0pz8;   //!
   TBranch        *b_p0chisq8;   //!
   TBranch        *b_p0pullm8;   //!
   TBranch        *b_p0hisid8;   //!
   TBranch        *b_p0losid8;   //!
   TBranch        *b_p0e9;   //!
   TBranch        *b_p0px9;   //!
   TBranch        *b_p0py9;   //!
   TBranch        *b_p0pz9;   //!
   TBranch        *b_p0chisq9;   //!
   TBranch        *b_p0pullm9;   //!
   TBranch        *b_p0hisid9;   //!
   TBranch        *b_p0losid9;   //!
   TBranch        *b_p0e10;   //!
   TBranch        *b_p0px10;   //!
   TBranch        *b_p0py10;   //!
   TBranch        *b_p0pz10;   //!
   TBranch        *b_p0chisq10;   //!
   TBranch        *b_p0pullm10;   //!
   TBranch        *b_p0hisid10;   //!
   TBranch        *b_p0losid10;   //!
   TBranch        *b_p0e11;   //!
   TBranch        *b_p0px11;   //!
   TBranch        *b_p0py11;   //!
   TBranch        *b_p0pz11;   //!
   TBranch        *b_p0chisq11;   //!
   TBranch        *b_p0pullm11;   //!
   TBranch        *b_p0hisid11;   //!
   TBranch        *b_p0losid11;   //!
   TBranch        *b_p0e12;   //!
   TBranch        *b_p0px12;   //!
   TBranch        *b_p0py12;   //!
   TBranch        *b_p0pz12;   //!
   TBranch        *b_p0chisq12;   //!
   TBranch        *b_p0pullm12;   //!
   TBranch        *b_p0hisid12;   //!
   TBranch        *b_p0losid12;   //!
   TBranch        *b_p0e13;   //!
   TBranch        *b_p0px13;   //!
   TBranch        *b_p0py13;   //!
   TBranch        *b_p0pz13;   //!
   TBranch        *b_p0chisq13;   //!
   TBranch        *b_p0pullm13;   //!
   TBranch        *b_p0hisid13;   //!
   TBranch        *b_p0losid13;   //!
   TBranch        *b_p0e14;   //!
   TBranch        *b_p0px14;   //!
   TBranch        *b_p0py14;   //!
   TBranch        *b_p0pz14;   //!
   TBranch        *b_p0chisq14;   //!
   TBranch        *b_p0pullm14;   //!
   TBranch        *b_p0hisid14;   //!
   TBranch        *b_p0losid14;   //!
   TBranch        *b_p0e15;   //!
   TBranch        *b_p0px15;   //!
   TBranch        *b_p0py15;   //!
   TBranch        *b_p0pz15;   //!
   TBranch        *b_p0chisq15;   //!
   TBranch        *b_p0pullm15;   //!
   TBranch        *b_p0hisid15;   //!
   TBranch        *b_p0losid15;   //!

   pi0(TTree *tree=0) { }
   virtual ~pi0() { }
   virtual Int_t   Version() const { return 1; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   TrackDataLite *showers[20];
   TrackDataLite *tracks[15];
   TrackDataLite2 *pi0s[15];

   TH1D *h_e;
   TH1D *h_e_all;
   TH1D *h_e_log;
   TH1D *h_mgg;
   TH1D *h_nt;
   TH1D *h_ns;
   TH1D *h_np;
   TH1D *h_mpsi;
   TH1D *h_mpsi2;
   TH1D *h_mpsi00;



//   ClassDef(pi0,0);
};

#endif

#ifdef pi0_cxx
void pi0::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses of the tree
   // will be set. It is normaly not necessary to make changes to the
   // generated code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running with PROOF.

   // Set branch addresses
   if (tree == 0) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nshower",&nshower);
   fChain->SetBranchAddress("ntrack",&ntrack);
   fChain->SetBranchAddress("np0",&np0);
   fChain->SetBranchAddress("e1",&e1);
   fChain->SetBranchAddress("th1",&th1);
   fChain->SetBranchAddress("phi1",&phi1);
   fChain->SetBranchAddress("e9251",&e9251);
   fChain->SetBranchAddress("barrel1",&barrel1);
   fChain->SetBranchAddress("e2",&e2);
   fChain->SetBranchAddress("th2",&th2);
   fChain->SetBranchAddress("phi2",&phi2);
   fChain->SetBranchAddress("e9252",&e9252);
   fChain->SetBranchAddress("barrel2",&barrel2);
   fChain->SetBranchAddress("e3",&e3);
   fChain->SetBranchAddress("th3",&th3);
   fChain->SetBranchAddress("phi3",&phi3);
   fChain->SetBranchAddress("e9253",&e9253);
   fChain->SetBranchAddress("barrel3",&barrel3);
   fChain->SetBranchAddress("e4",&e4);
   fChain->SetBranchAddress("th4",&th4);
   fChain->SetBranchAddress("phi4",&phi4);
   fChain->SetBranchAddress("e9254",&e9254);
   fChain->SetBranchAddress("barrel4",&barrel4);
   fChain->SetBranchAddress("e5",&e5);
   fChain->SetBranchAddress("th5",&th5);
   fChain->SetBranchAddress("phi5",&phi5);
   fChain->SetBranchAddress("e9255",&e9255);
   fChain->SetBranchAddress("barrel5",&barrel5);
   fChain->SetBranchAddress("e6",&e6);
   fChain->SetBranchAddress("th6",&th6);
   fChain->SetBranchAddress("phi6",&phi6);
   fChain->SetBranchAddress("e9256",&e9256);
   fChain->SetBranchAddress("barrel6",&barrel6);
   fChain->SetBranchAddress("e7",&e7);
   fChain->SetBranchAddress("th7",&th7);
   fChain->SetBranchAddress("phi7",&phi7);
   fChain->SetBranchAddress("e9257",&e9257);
   fChain->SetBranchAddress("barrel7",&barrel7);
   fChain->SetBranchAddress("e8",&e8);
   fChain->SetBranchAddress("th8",&th8);
   fChain->SetBranchAddress("phi8",&phi8);
   fChain->SetBranchAddress("e9258",&e9258);
   fChain->SetBranchAddress("barrel8",&barrel8);
   fChain->SetBranchAddress("e9",&e9);
   fChain->SetBranchAddress("th9",&th9);
   fChain->SetBranchAddress("phi9",&phi9);
   fChain->SetBranchAddress("e9259",&e9259);
   fChain->SetBranchAddress("barrel9",&barrel9);
   fChain->SetBranchAddress("e10",&e10);
   fChain->SetBranchAddress("th10",&th10);
   fChain->SetBranchAddress("phi10",&phi10);
   fChain->SetBranchAddress("e92510",&e92510);
   fChain->SetBranchAddress("barrel10",&barrel10);
   fChain->SetBranchAddress("e11",&e11);
   fChain->SetBranchAddress("th11",&th11);
   fChain->SetBranchAddress("phi11",&phi11);
   fChain->SetBranchAddress("e92511",&e92511);
   fChain->SetBranchAddress("barrel11",&barrel11);
   fChain->SetBranchAddress("e12",&e12);
   fChain->SetBranchAddress("th12",&th12);
   fChain->SetBranchAddress("phi12",&phi12);
   fChain->SetBranchAddress("e92512",&e92512);
   fChain->SetBranchAddress("barrel12",&barrel12);
   fChain->SetBranchAddress("e13",&e13);
   fChain->SetBranchAddress("th13",&th13);
   fChain->SetBranchAddress("phi13",&phi13);
   fChain->SetBranchAddress("e92513",&e92513);
   fChain->SetBranchAddress("barrel13",&barrel13);
   fChain->SetBranchAddress("e14",&e14);
   fChain->SetBranchAddress("th14",&th14);
   fChain->SetBranchAddress("phi14",&phi14);
   fChain->SetBranchAddress("e92514",&e92514);
   fChain->SetBranchAddress("barrel14",&barrel14);
   fChain->SetBranchAddress("e15",&e15);
   fChain->SetBranchAddress("th15",&th15);
   fChain->SetBranchAddress("phi15",&phi15);
   fChain->SetBranchAddress("e92515",&e92515);
   fChain->SetBranchAddress("barrel15",&barrel15);
   fChain->SetBranchAddress("e16",&e16);
   fChain->SetBranchAddress("th16",&th16);
   fChain->SetBranchAddress("phi16",&phi16);
   fChain->SetBranchAddress("e92516",&e92516);
   fChain->SetBranchAddress("barrel16",&barrel16);
   fChain->SetBranchAddress("e17",&e17);
   fChain->SetBranchAddress("th17",&th17);
   fChain->SetBranchAddress("phi17",&phi17);
   fChain->SetBranchAddress("e92517",&e92517);
   fChain->SetBranchAddress("barrel17",&barrel17);
   fChain->SetBranchAddress("e18",&e18);
   fChain->SetBranchAddress("th18",&th18);
   fChain->SetBranchAddress("phi18",&phi18);
   fChain->SetBranchAddress("e92518",&e92518);
   fChain->SetBranchAddress("barrel18",&barrel18);
   fChain->SetBranchAddress("e19",&e19);
   fChain->SetBranchAddress("th19",&th19);
   fChain->SetBranchAddress("phi19",&phi19);
   fChain->SetBranchAddress("e92519",&e92519);
   fChain->SetBranchAddress("barrel19",&barrel19);
   fChain->SetBranchAddress("e20",&e20);
   fChain->SetBranchAddress("th20",&th20);
   fChain->SetBranchAddress("phi20",&phi20);
   fChain->SetBranchAddress("e92520",&e92520);
   fChain->SetBranchAddress("barrel20",&barrel20);
   fChain->SetBranchAddress("te1",&te1);
   fChain->SetBranchAddress("px1",&px1);
   fChain->SetBranchAddress("py1",&py1);
   fChain->SetBranchAddress("pz1",&pz1);
   fChain->SetBranchAddress("charge1",&charge1);
   fChain->SetBranchAddress("te2",&te2);
   fChain->SetBranchAddress("px2",&px2);
   fChain->SetBranchAddress("py2",&py2);
   fChain->SetBranchAddress("pz2",&pz2);
   fChain->SetBranchAddress("charge2",&charge2);
   fChain->SetBranchAddress("te3",&te3);
   fChain->SetBranchAddress("px3",&px3);
   fChain->SetBranchAddress("py3",&py3);
   fChain->SetBranchAddress("pz3",&pz3);
   fChain->SetBranchAddress("charge3",&charge3);
   fChain->SetBranchAddress("te4",&te4);
   fChain->SetBranchAddress("px4",&px4);
   fChain->SetBranchAddress("py4",&py4);
   fChain->SetBranchAddress("pz4",&pz4);
   fChain->SetBranchAddress("charge4",&charge4);
   fChain->SetBranchAddress("te5",&te5);
   fChain->SetBranchAddress("px5",&px5);
   fChain->SetBranchAddress("py5",&py5);
   fChain->SetBranchAddress("pz5",&pz5);
   fChain->SetBranchAddress("charge5",&charge5);
   fChain->SetBranchAddress("te6",&te6);
   fChain->SetBranchAddress("px6",&px6);
   fChain->SetBranchAddress("py6",&py6);
   fChain->SetBranchAddress("pz6",&pz6);
   fChain->SetBranchAddress("charge6",&charge6);
   fChain->SetBranchAddress("te7",&te7);
   fChain->SetBranchAddress("px7",&px7);
   fChain->SetBranchAddress("py7",&py7);
   fChain->SetBranchAddress("pz7",&pz7);
   fChain->SetBranchAddress("charge7",&charge7);
   fChain->SetBranchAddress("te8",&te8);
   fChain->SetBranchAddress("px8",&px8);
   fChain->SetBranchAddress("py8",&py8);
   fChain->SetBranchAddress("pz8",&pz8);
   fChain->SetBranchAddress("charge8",&charge8);
   fChain->SetBranchAddress("te9",&te9);
   fChain->SetBranchAddress("px9",&px9);
   fChain->SetBranchAddress("py9",&py9);
   fChain->SetBranchAddress("pz9",&pz9);
   fChain->SetBranchAddress("charge9",&charge9);
   fChain->SetBranchAddress("te10",&te10);
   fChain->SetBranchAddress("px10",&px10);
   fChain->SetBranchAddress("py10",&py10);
   fChain->SetBranchAddress("pz10",&pz10);
   fChain->SetBranchAddress("charge10",&charge10);
   fChain->SetBranchAddress("te11",&te11);
   fChain->SetBranchAddress("px11",&px11);
   fChain->SetBranchAddress("py11",&py11);
   fChain->SetBranchAddress("pz11",&pz11);
   fChain->SetBranchAddress("charge11",&charge11);
   fChain->SetBranchAddress("te12",&te12);
   fChain->SetBranchAddress("px12",&px12);
   fChain->SetBranchAddress("py12",&py12);
   fChain->SetBranchAddress("pz12",&pz12);
   fChain->SetBranchAddress("charge12",&charge12);
   fChain->SetBranchAddress("te13",&te13);
   fChain->SetBranchAddress("px13",&px13);
   fChain->SetBranchAddress("py13",&py13);
   fChain->SetBranchAddress("pz13",&pz13);
   fChain->SetBranchAddress("charge13",&charge13);
   fChain->SetBranchAddress("te14",&te14);
   fChain->SetBranchAddress("px14",&px14);
   fChain->SetBranchAddress("py14",&py14);
   fChain->SetBranchAddress("pz14",&pz14);
   fChain->SetBranchAddress("charge14",&charge14);
   fChain->SetBranchAddress("te15",&te15);
   fChain->SetBranchAddress("px15",&px15);
   fChain->SetBranchAddress("py15",&py15);
   fChain->SetBranchAddress("pz15",&pz15);
   fChain->SetBranchAddress("charge15",&charge15);
   fChain->SetBranchAddress("p0e1",&p0e1);
   fChain->SetBranchAddress("p0px1",&p0px1);
   fChain->SetBranchAddress("p0py1",&p0py1);
   fChain->SetBranchAddress("p0pz1",&p0pz1);
   fChain->SetBranchAddress("p0chisq1",&p0chisq1);
   fChain->SetBranchAddress("p0pullm1",&p0pullm1);
   fChain->SetBranchAddress("p0hisid1",&p0hisid1);
   fChain->SetBranchAddress("p0losid1",&p0losid1);
   fChain->SetBranchAddress("p0e2",&p0e2);
   fChain->SetBranchAddress("p0px2",&p0px2);
   fChain->SetBranchAddress("p0py2",&p0py2);
   fChain->SetBranchAddress("p0pz2",&p0pz2);
   fChain->SetBranchAddress("p0chisq2",&p0chisq2);
   fChain->SetBranchAddress("p0pullm2",&p0pullm2);
   fChain->SetBranchAddress("p0hisid2",&p0hisid2);
   fChain->SetBranchAddress("p0losid2",&p0losid2);
   fChain->SetBranchAddress("p0e3",&p0e3);
   fChain->SetBranchAddress("p0px3",&p0px3);
   fChain->SetBranchAddress("p0py3",&p0py3);
   fChain->SetBranchAddress("p0pz3",&p0pz3);
   fChain->SetBranchAddress("p0chisq3",&p0chisq3);
   fChain->SetBranchAddress("p0pullm3",&p0pullm3);
   fChain->SetBranchAddress("p0hisid3",&p0hisid3);
   fChain->SetBranchAddress("p0losid3",&p0losid3);
   fChain->SetBranchAddress("p0e4",&p0e4);
   fChain->SetBranchAddress("p0px4",&p0px4);
   fChain->SetBranchAddress("p0py4",&p0py4);
   fChain->SetBranchAddress("p0pz4",&p0pz4);
   fChain->SetBranchAddress("p0chisq4",&p0chisq4);
   fChain->SetBranchAddress("p0pullm4",&p0pullm4);
   fChain->SetBranchAddress("p0hisid4",&p0hisid4);
   fChain->SetBranchAddress("p0losid4",&p0losid4);
   fChain->SetBranchAddress("p0e5",&p0e5);
   fChain->SetBranchAddress("p0px5",&p0px5);
   fChain->SetBranchAddress("p0py5",&p0py5);
   fChain->SetBranchAddress("p0pz5",&p0pz5);
   fChain->SetBranchAddress("p0chisq5",&p0chisq5);
   fChain->SetBranchAddress("p0pullm5",&p0pullm5);
   fChain->SetBranchAddress("p0hisid5",&p0hisid5);
   fChain->SetBranchAddress("p0losid5",&p0losid5);
   fChain->SetBranchAddress("p0e6",&p0e6);
   fChain->SetBranchAddress("p0px6",&p0px6);
   fChain->SetBranchAddress("p0py6",&p0py6);
   fChain->SetBranchAddress("p0pz6",&p0pz6);
   fChain->SetBranchAddress("p0chisq6",&p0chisq6);
   fChain->SetBranchAddress("p0pullm6",&p0pullm6);
   fChain->SetBranchAddress("p0hisid6",&p0hisid6);
   fChain->SetBranchAddress("p0losid6",&p0losid6);
   fChain->SetBranchAddress("p0e7",&p0e7);
   fChain->SetBranchAddress("p0px7",&p0px7);
   fChain->SetBranchAddress("p0py7",&p0py7);
   fChain->SetBranchAddress("p0pz7",&p0pz7);
   fChain->SetBranchAddress("p0chisq7",&p0chisq7);
   fChain->SetBranchAddress("p0pullm7",&p0pullm7);
   fChain->SetBranchAddress("p0hisid7",&p0hisid7);
   fChain->SetBranchAddress("p0losid7",&p0losid7);
   fChain->SetBranchAddress("p0e8",&p0e8);
   fChain->SetBranchAddress("p0px8",&p0px8);
   fChain->SetBranchAddress("p0py8",&p0py8);
   fChain->SetBranchAddress("p0pz8",&p0pz8);
   fChain->SetBranchAddress("p0chisq8",&p0chisq8);
   fChain->SetBranchAddress("p0pullm8",&p0pullm8);
   fChain->SetBranchAddress("p0hisid8",&p0hisid8);
   fChain->SetBranchAddress("p0losid8",&p0losid8);
   fChain->SetBranchAddress("p0e9",&p0e9);
   fChain->SetBranchAddress("p0px9",&p0px9);
   fChain->SetBranchAddress("p0py9",&p0py9);
   fChain->SetBranchAddress("p0pz9",&p0pz9);
   fChain->SetBranchAddress("p0chisq9",&p0chisq9);
   fChain->SetBranchAddress("p0pullm9",&p0pullm9);
   fChain->SetBranchAddress("p0hisid9",&p0hisid9);
   fChain->SetBranchAddress("p0losid9",&p0losid9);
   fChain->SetBranchAddress("p0e10",&p0e10);
   fChain->SetBranchAddress("p0px10",&p0px10);
   fChain->SetBranchAddress("p0py10",&p0py10);
   fChain->SetBranchAddress("p0pz10",&p0pz10);
   fChain->SetBranchAddress("p0chisq10",&p0chisq10);
   fChain->SetBranchAddress("p0pullm10",&p0pullm10);
   fChain->SetBranchAddress("p0hisid10",&p0hisid10);
   fChain->SetBranchAddress("p0losid10",&p0losid10);
   fChain->SetBranchAddress("p0e11",&p0e11);
   fChain->SetBranchAddress("p0px11",&p0px11);
   fChain->SetBranchAddress("p0py11",&p0py11);
   fChain->SetBranchAddress("p0pz11",&p0pz11);
   fChain->SetBranchAddress("p0chisq11",&p0chisq11);
   fChain->SetBranchAddress("p0pullm11",&p0pullm11);
   fChain->SetBranchAddress("p0hisid11",&p0hisid11);
   fChain->SetBranchAddress("p0losid11",&p0losid11);
   fChain->SetBranchAddress("p0e12",&p0e12);
   fChain->SetBranchAddress("p0px12",&p0px12);
   fChain->SetBranchAddress("p0py12",&p0py12);
   fChain->SetBranchAddress("p0pz12",&p0pz12);
   fChain->SetBranchAddress("p0chisq12",&p0chisq12);
   fChain->SetBranchAddress("p0pullm12",&p0pullm12);
   fChain->SetBranchAddress("p0hisid12",&p0hisid12);
   fChain->SetBranchAddress("p0losid12",&p0losid12);
   fChain->SetBranchAddress("p0e13",&p0e13);
   fChain->SetBranchAddress("p0px13",&p0px13);
   fChain->SetBranchAddress("p0py13",&p0py13);
   fChain->SetBranchAddress("p0pz13",&p0pz13);
   fChain->SetBranchAddress("p0chisq13",&p0chisq13);
   fChain->SetBranchAddress("p0pullm13",&p0pullm13);
   fChain->SetBranchAddress("p0hisid13",&p0hisid13);
   fChain->SetBranchAddress("p0losid13",&p0losid13);
   fChain->SetBranchAddress("p0e14",&p0e14);
   fChain->SetBranchAddress("p0px14",&p0px14);
   fChain->SetBranchAddress("p0py14",&p0py14);
   fChain->SetBranchAddress("p0pz14",&p0pz14);
   fChain->SetBranchAddress("p0chisq14",&p0chisq14);
   fChain->SetBranchAddress("p0pullm14",&p0pullm14);
   fChain->SetBranchAddress("p0hisid14",&p0hisid14);
   fChain->SetBranchAddress("p0losid14",&p0losid14);
   fChain->SetBranchAddress("p0e15",&p0e15);
   fChain->SetBranchAddress("p0px15",&p0px15);
   fChain->SetBranchAddress("p0py15",&p0py15);
   fChain->SetBranchAddress("p0pz15",&p0pz15);
   fChain->SetBranchAddress("p0chisq15",&p0chisq15);
   fChain->SetBranchAddress("p0pullm15",&p0pullm15);
   fChain->SetBranchAddress("p0hisid15",&p0hisid15);
   fChain->SetBranchAddress("p0losid15",&p0losid15);
}

Bool_t pi0::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. Typically here the branch pointers
   // will be retrieved. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed.

   // Get branch pointers
   b_nshower = fChain->GetBranch("nshower");
   b_ntrack = fChain->GetBranch("ntrack");
   b_np0 = fChain->GetBranch("np0");
   b_e1 = fChain->GetBranch("e1");
   b_th1 = fChain->GetBranch("th1");
   b_phi1 = fChain->GetBranch("phi1");
   b_e9251 = fChain->GetBranch("e9251");
   b_barrel1 = fChain->GetBranch("barrel1");
   b_e2 = fChain->GetBranch("e2");
   b_th2 = fChain->GetBranch("th2");
   b_phi2 = fChain->GetBranch("phi2");
   b_e9252 = fChain->GetBranch("e9252");
   b_barrel2 = fChain->GetBranch("barrel2");
   b_e3 = fChain->GetBranch("e3");
   b_th3 = fChain->GetBranch("th3");
   b_phi3 = fChain->GetBranch("phi3");
   b_e9253 = fChain->GetBranch("e9253");
   b_barrel3 = fChain->GetBranch("barrel3");
   b_e4 = fChain->GetBranch("e4");
   b_th4 = fChain->GetBranch("th4");
   b_phi4 = fChain->GetBranch("phi4");
   b_e9254 = fChain->GetBranch("e9254");
   b_barrel4 = fChain->GetBranch("barrel4");
   b_e5 = fChain->GetBranch("e5");
   b_th5 = fChain->GetBranch("th5");
   b_phi5 = fChain->GetBranch("phi5");
   b_e9255 = fChain->GetBranch("e9255");
   b_barrel5 = fChain->GetBranch("barrel5");
   b_e6 = fChain->GetBranch("e6");
   b_th6 = fChain->GetBranch("th6");
   b_phi6 = fChain->GetBranch("phi6");
   b_e9256 = fChain->GetBranch("e9256");
   b_barrel6 = fChain->GetBranch("barrel6");
   b_e7 = fChain->GetBranch("e7");
   b_th7 = fChain->GetBranch("th7");
   b_phi7 = fChain->GetBranch("phi7");
   b_e9257 = fChain->GetBranch("e9257");
   b_barrel7 = fChain->GetBranch("barrel7");
   b_e8 = fChain->GetBranch("e8");
   b_th8 = fChain->GetBranch("th8");
   b_phi8 = fChain->GetBranch("phi8");
   b_e9258 = fChain->GetBranch("e9258");
   b_barrel8 = fChain->GetBranch("barrel8");
   b_e9 = fChain->GetBranch("e9");
   b_th9 = fChain->GetBranch("th9");
   b_phi9 = fChain->GetBranch("phi9");
   b_e9259 = fChain->GetBranch("e9259");
   b_barrel9 = fChain->GetBranch("barrel9");
   b_e10 = fChain->GetBranch("e10");
   b_th10 = fChain->GetBranch("th10");
   b_phi10 = fChain->GetBranch("phi10");
   b_e92510 = fChain->GetBranch("e92510");
   b_barrel10 = fChain->GetBranch("barrel10");
   b_e11 = fChain->GetBranch("e11");
   b_th11 = fChain->GetBranch("th11");
   b_phi11 = fChain->GetBranch("phi11");
   b_e92511 = fChain->GetBranch("e92511");
   b_barrel11 = fChain->GetBranch("barrel11");
   b_e12 = fChain->GetBranch("e12");
   b_th12 = fChain->GetBranch("th12");
   b_phi12 = fChain->GetBranch("phi12");
   b_e92512 = fChain->GetBranch("e92512");
   b_barrel12 = fChain->GetBranch("barrel12");
   b_e13 = fChain->GetBranch("e13");
   b_th13 = fChain->GetBranch("th13");
   b_phi13 = fChain->GetBranch("phi13");
   b_e92513 = fChain->GetBranch("e92513");
   b_barrel13 = fChain->GetBranch("barrel13");
   b_e14 = fChain->GetBranch("e14");
   b_th14 = fChain->GetBranch("th14");
   b_phi14 = fChain->GetBranch("phi14");
   b_e92514 = fChain->GetBranch("e92514");
   b_barrel14 = fChain->GetBranch("barrel14");
   b_e15 = fChain->GetBranch("e15");
   b_th15 = fChain->GetBranch("th15");
   b_phi15 = fChain->GetBranch("phi15");
   b_e92515 = fChain->GetBranch("e92515");
   b_barrel15 = fChain->GetBranch("barrel15");
   b_e16 = fChain->GetBranch("e16");
   b_th16 = fChain->GetBranch("th16");
   b_phi16 = fChain->GetBranch("phi16");
   b_e92516 = fChain->GetBranch("e92516");
   b_barrel16 = fChain->GetBranch("barrel16");
   b_e17 = fChain->GetBranch("e17");
   b_th17 = fChain->GetBranch("th17");
   b_phi17 = fChain->GetBranch("phi17");
   b_e92517 = fChain->GetBranch("e92517");
   b_barrel17 = fChain->GetBranch("barrel17");
   b_e18 = fChain->GetBranch("e18");
   b_th18 = fChain->GetBranch("th18");
   b_phi18 = fChain->GetBranch("phi18");
   b_e92518 = fChain->GetBranch("e92518");
   b_barrel18 = fChain->GetBranch("barrel18");
   b_e19 = fChain->GetBranch("e19");
   b_th19 = fChain->GetBranch("th19");
   b_phi19 = fChain->GetBranch("phi19");
   b_e92519 = fChain->GetBranch("e92519");
   b_barrel19 = fChain->GetBranch("barrel19");
   b_e20 = fChain->GetBranch("e20");
   b_th20 = fChain->GetBranch("th20");
   b_phi20 = fChain->GetBranch("phi20");
   b_e92520 = fChain->GetBranch("e92520");
   b_barrel20 = fChain->GetBranch("barrel20");
   b_te1 = fChain->GetBranch("te1");
   b_px1 = fChain->GetBranch("px1");
   b_py1 = fChain->GetBranch("py1");
   b_pz1 = fChain->GetBranch("pz1");
   b_charge1 = fChain->GetBranch("charge1");
   b_te2 = fChain->GetBranch("te2");
   b_px2 = fChain->GetBranch("px2");
   b_py2 = fChain->GetBranch("py2");
   b_pz2 = fChain->GetBranch("pz2");
   b_charge2 = fChain->GetBranch("charge2");
   b_te3 = fChain->GetBranch("te3");
   b_px3 = fChain->GetBranch("px3");
   b_py3 = fChain->GetBranch("py3");
   b_pz3 = fChain->GetBranch("pz3");
   b_charge3 = fChain->GetBranch("charge3");
   b_te4 = fChain->GetBranch("te4");
   b_px4 = fChain->GetBranch("px4");
   b_py4 = fChain->GetBranch("py4");
   b_pz4 = fChain->GetBranch("pz4");
   b_charge4 = fChain->GetBranch("charge4");
   b_te5 = fChain->GetBranch("te5");
   b_px5 = fChain->GetBranch("px5");
   b_py5 = fChain->GetBranch("py5");
   b_pz5 = fChain->GetBranch("pz5");
   b_charge5 = fChain->GetBranch("charge5");
   b_te6 = fChain->GetBranch("te6");
   b_px6 = fChain->GetBranch("px6");
   b_py6 = fChain->GetBranch("py6");
   b_pz6 = fChain->GetBranch("pz6");
   b_charge6 = fChain->GetBranch("charge6");
   b_te7 = fChain->GetBranch("te7");
   b_px7 = fChain->GetBranch("px7");
   b_py7 = fChain->GetBranch("py7");
   b_pz7 = fChain->GetBranch("pz7");
   b_charge7 = fChain->GetBranch("charge7");
   b_te8 = fChain->GetBranch("te8");
   b_px8 = fChain->GetBranch("px8");
   b_py8 = fChain->GetBranch("py8");
   b_pz8 = fChain->GetBranch("pz8");
   b_charge8 = fChain->GetBranch("charge8");
   b_te9 = fChain->GetBranch("te9");
   b_px9 = fChain->GetBranch("px9");
   b_py9 = fChain->GetBranch("py9");
   b_pz9 = fChain->GetBranch("pz9");
   b_charge9 = fChain->GetBranch("charge9");
   b_te10 = fChain->GetBranch("te10");
   b_px10 = fChain->GetBranch("px10");
   b_py10 = fChain->GetBranch("py10");
   b_pz10 = fChain->GetBranch("pz10");
   b_charge10 = fChain->GetBranch("charge10");
   b_te11 = fChain->GetBranch("te11");
   b_px11 = fChain->GetBranch("px11");
   b_py11 = fChain->GetBranch("py11");
   b_pz11 = fChain->GetBranch("pz11");
   b_charge11 = fChain->GetBranch("charge11");
   b_te12 = fChain->GetBranch("te12");
   b_px12 = fChain->GetBranch("px12");
   b_py12 = fChain->GetBranch("py12");
   b_pz12 = fChain->GetBranch("pz12");
   b_charge12 = fChain->GetBranch("charge12");
   b_te13 = fChain->GetBranch("te13");
   b_px13 = fChain->GetBranch("px13");
   b_py13 = fChain->GetBranch("py13");
   b_pz13 = fChain->GetBranch("pz13");
   b_charge13 = fChain->GetBranch("charge13");
   b_te14 = fChain->GetBranch("te14");
   b_px14 = fChain->GetBranch("px14");
   b_py14 = fChain->GetBranch("py14");
   b_pz14 = fChain->GetBranch("pz14");
   b_charge14 = fChain->GetBranch("charge14");
   b_te15 = fChain->GetBranch("te15");
   b_px15 = fChain->GetBranch("px15");
   b_py15 = fChain->GetBranch("py15");
   b_pz15 = fChain->GetBranch("pz15");
   b_charge15 = fChain->GetBranch("charge15");
   b_p0e1 = fChain->GetBranch("p0e1");
   b_p0px1 = fChain->GetBranch("p0px1");
   b_p0py1 = fChain->GetBranch("p0py1");
   b_p0pz1 = fChain->GetBranch("p0pz1");
   b_p0chisq1 = fChain->GetBranch("p0chisq1");
   b_p0pullm1 = fChain->GetBranch("p0pullm1");
   b_p0hisid1 = fChain->GetBranch("p0hisid1");
   b_p0losid1 = fChain->GetBranch("p0losid1");
   b_p0e2 = fChain->GetBranch("p0e2");
   b_p0px2 = fChain->GetBranch("p0px2");
   b_p0py2 = fChain->GetBranch("p0py2");
   b_p0pz2 = fChain->GetBranch("p0pz2");
   b_p0chisq2 = fChain->GetBranch("p0chisq2");
   b_p0pullm2 = fChain->GetBranch("p0pullm2");
   b_p0hisid2 = fChain->GetBranch("p0hisid2");
   b_p0losid2 = fChain->GetBranch("p0losid2");
   b_p0e3 = fChain->GetBranch("p0e3");
   b_p0px3 = fChain->GetBranch("p0px3");
   b_p0py3 = fChain->GetBranch("p0py3");
   b_p0pz3 = fChain->GetBranch("p0pz3");
   b_p0chisq3 = fChain->GetBranch("p0chisq3");
   b_p0pullm3 = fChain->GetBranch("p0pullm3");
   b_p0hisid3 = fChain->GetBranch("p0hisid3");
   b_p0losid3 = fChain->GetBranch("p0losid3");
   b_p0e4 = fChain->GetBranch("p0e4");
   b_p0px4 = fChain->GetBranch("p0px4");
   b_p0py4 = fChain->GetBranch("p0py4");
   b_p0pz4 = fChain->GetBranch("p0pz4");
   b_p0chisq4 = fChain->GetBranch("p0chisq4");
   b_p0pullm4 = fChain->GetBranch("p0pullm4");
   b_p0hisid4 = fChain->GetBranch("p0hisid4");
   b_p0losid4 = fChain->GetBranch("p0losid4");
   b_p0e5 = fChain->GetBranch("p0e5");
   b_p0px5 = fChain->GetBranch("p0px5");
   b_p0py5 = fChain->GetBranch("p0py5");
   b_p0pz5 = fChain->GetBranch("p0pz5");
   b_p0chisq5 = fChain->GetBranch("p0chisq5");
   b_p0pullm5 = fChain->GetBranch("p0pullm5");
   b_p0hisid5 = fChain->GetBranch("p0hisid5");
   b_p0losid5 = fChain->GetBranch("p0losid5");
   b_p0e6 = fChain->GetBranch("p0e6");
   b_p0px6 = fChain->GetBranch("p0px6");
   b_p0py6 = fChain->GetBranch("p0py6");
   b_p0pz6 = fChain->GetBranch("p0pz6");
   b_p0chisq6 = fChain->GetBranch("p0chisq6");
   b_p0pullm6 = fChain->GetBranch("p0pullm6");
   b_p0hisid6 = fChain->GetBranch("p0hisid6");
   b_p0losid6 = fChain->GetBranch("p0losid6");
   b_p0e7 = fChain->GetBranch("p0e7");
   b_p0px7 = fChain->GetBranch("p0px7");
   b_p0py7 = fChain->GetBranch("p0py7");
   b_p0pz7 = fChain->GetBranch("p0pz7");
   b_p0chisq7 = fChain->GetBranch("p0chisq7");
   b_p0pullm7 = fChain->GetBranch("p0pullm7");
   b_p0hisid7 = fChain->GetBranch("p0hisid7");
   b_p0losid7 = fChain->GetBranch("p0losid7");
   b_p0e8 = fChain->GetBranch("p0e8");
   b_p0px8 = fChain->GetBranch("p0px8");
   b_p0py8 = fChain->GetBranch("p0py8");
   b_p0pz8 = fChain->GetBranch("p0pz8");
   b_p0chisq8 = fChain->GetBranch("p0chisq8");
   b_p0pullm8 = fChain->GetBranch("p0pullm8");
   b_p0hisid8 = fChain->GetBranch("p0hisid8");
   b_p0losid8 = fChain->GetBranch("p0losid8");
   b_p0e9 = fChain->GetBranch("p0e9");
   b_p0px9 = fChain->GetBranch("p0px9");
   b_p0py9 = fChain->GetBranch("p0py9");
   b_p0pz9 = fChain->GetBranch("p0pz9");
   b_p0chisq9 = fChain->GetBranch("p0chisq9");
   b_p0pullm9 = fChain->GetBranch("p0pullm9");
   b_p0hisid9 = fChain->GetBranch("p0hisid9");
   b_p0losid9 = fChain->GetBranch("p0losid9");
   b_p0e10 = fChain->GetBranch("p0e10");
   b_p0px10 = fChain->GetBranch("p0px10");
   b_p0py10 = fChain->GetBranch("p0py10");
   b_p0pz10 = fChain->GetBranch("p0pz10");
   b_p0chisq10 = fChain->GetBranch("p0chisq10");
   b_p0pullm10 = fChain->GetBranch("p0pullm10");
   b_p0hisid10 = fChain->GetBranch("p0hisid10");
   b_p0losid10 = fChain->GetBranch("p0losid10");
   b_p0e11 = fChain->GetBranch("p0e11");
   b_p0px11 = fChain->GetBranch("p0px11");
   b_p0py11 = fChain->GetBranch("p0py11");
   b_p0pz11 = fChain->GetBranch("p0pz11");
   b_p0chisq11 = fChain->GetBranch("p0chisq11");
   b_p0pullm11 = fChain->GetBranch("p0pullm11");
   b_p0hisid11 = fChain->GetBranch("p0hisid11");
   b_p0losid11 = fChain->GetBranch("p0losid11");
   b_p0e12 = fChain->GetBranch("p0e12");
   b_p0px12 = fChain->GetBranch("p0px12");
   b_p0py12 = fChain->GetBranch("p0py12");
   b_p0pz12 = fChain->GetBranch("p0pz12");
   b_p0chisq12 = fChain->GetBranch("p0chisq12");
   b_p0pullm12 = fChain->GetBranch("p0pullm12");
   b_p0hisid12 = fChain->GetBranch("p0hisid12");
   b_p0losid12 = fChain->GetBranch("p0losid12");
   b_p0e13 = fChain->GetBranch("p0e13");
   b_p0px13 = fChain->GetBranch("p0px13");
   b_p0py13 = fChain->GetBranch("p0py13");
   b_p0pz13 = fChain->GetBranch("p0pz13");
   b_p0chisq13 = fChain->GetBranch("p0chisq13");
   b_p0pullm13 = fChain->GetBranch("p0pullm13");
   b_p0hisid13 = fChain->GetBranch("p0hisid13");
   b_p0losid13 = fChain->GetBranch("p0losid13");
   b_p0e14 = fChain->GetBranch("p0e14");
   b_p0px14 = fChain->GetBranch("p0px14");
   b_p0py14 = fChain->GetBranch("p0py14");
   b_p0pz14 = fChain->GetBranch("p0pz14");
   b_p0chisq14 = fChain->GetBranch("p0chisq14");
   b_p0pullm14 = fChain->GetBranch("p0pullm14");
   b_p0hisid14 = fChain->GetBranch("p0hisid14");
   b_p0losid14 = fChain->GetBranch("p0losid14");
   b_p0e15 = fChain->GetBranch("p0e15");
   b_p0px15 = fChain->GetBranch("p0px15");
   b_p0py15 = fChain->GetBranch("p0py15");
   b_p0pz15 = fChain->GetBranch("p0pz15");
   b_p0chisq15 = fChain->GetBranch("p0chisq15");
   b_p0pullm15 = fChain->GetBranch("p0pullm15");
   b_p0hisid15 = fChain->GetBranch("p0hisid15");
   b_p0losid15 = fChain->GetBranch("p0losid15");

   return kTRUE;
}

#endif // #ifdef pi0_cxx
