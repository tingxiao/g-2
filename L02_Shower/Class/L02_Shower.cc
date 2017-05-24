// -*- C++ -*-
//
// Package:     L02_Shower
// Module:      L02_Shower
// 
// Description: Lesson 2: Showers
//
// Implementation:
//     use /cdat/daf9/jima/suez/tcl/L02_Shower.tcl
//
// Author:      James Alexander
// Created:     Wed Jan  1 08:01:30 EST 2003
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "L02_Shower/L02_Shower.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units
#include "HistogramInterface/HINtupleVarNames.h"
#include "HistogramInterface/HINtupleArray.h"
#include "HistogramInterface/HIHist1D.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"

#include "DedxInfo/DedxInfo.h"
#include "LabNet4Momentum/LabNet4Momentum.h"

#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"

#include "Navigation/NavPi0ToGG.h"
#include "PhotonDecays/PhdPi0.h"
//I added the following at the suggestion of the NavShower web page
#include "Navigation/NavConReg.h"
#include "KinematicTrajectory/KTKinematicData.h"
#include "Navigation/NavTkShMatch.h"
#include "C3cc/CcAssignedEnergyHit.h"

// STL classes
// You may have to uncomment some of these or other stl headers 
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.L02_Shower" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
L02_Shower::L02_Shower( void )               // anal1
   : Processor( "L02_Shower" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &L02_Shower::event,    Stream::kEvent );
   //bind( &L02_Shower::beginRun, Stream::kBeginRun );
   //bind( &L02_Shower::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

L02_Shower::~L02_Shower()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
L02_Shower::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
L02_Shower::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------

//m_psi = iHistoManager.histogram("psi mass (GeV)", 1000, 0.25,
//                                       0.35);



enum {knshower, kntrack, knp0,
e1,th1,ph1,e9251,barrel1,//psim1,
e2,th2,ph2,e9252,barrel2,//psim2,
e3,th3,ph3,e9253,barrel3,//psim3,
e4,th4,ph4,e9254,barrel4,//psim4,
e5,th5,ph5,e9255,barrel5,//psim5,
e6,th6,ph6,e9256,barrel6,//psim6,
e7,th7,ph7,e9257,barrel7,//psim7,
e8,th8,ph8,e9258,barrel8,//psim8,
e9,th9,ph9,e9259,barrel9,//psim9,
e10,th10,ph10,e92510,barrel10,//psim10,
e11,th11,ph11,e92511,barrel11,//psim11,
e12,th12,ph12,e92512,barrel12,//psim12,
e13,th13,ph13,e92513,barrel13,//psim13,
e14,th14,ph14,e92514,barrel14,//psim14,
e15,th15,ph15,e92515,barrel15, 
e16,th16,ph16,e92516,barrel16,
e17,th17,ph17,e92517,barrel17,
e18,th18,ph18,e92518,barrel18,
e19,th19,ph19,e92519,barrel19,
e20,th20,ph20,e92520,barrel20,

kte1,kpx1,kpy1,kpz1,kcharge1,
kte2,kpx2,kpy2,kpz2,kcharge2,
kte3,kpx3,kpy3,kpz3,kcharge3,
kte4,kpx4,kpy4,kpz4,kcharge4,
kte5,kpx5,kpy5,kpz5,kcharge5,
kte6,kpx6,kpy6,kpz6,kcharge6,
kte7,kpx7,kpy7,kpz7,kcharge7,
kte8,kpx8,kpy8,kpz8,kcharge8,
kte9,kpx9,kpy9,kpz9,kcharge9,
kte10,kpx10,kpy10,kpz10,kcharge10,
kte11,kpx11,kpy11,kpz11,kcharge11,
kte12,kpx12,kpy12,kpz12,kcharge12,
kte13,kpx13,kpy13,kpz13,kcharge13,
kte14,kpx14,kpy14,kpz14,kcharge14,
kte15,kpx15,kpy15,kpz15,kcharge15,

p0e1,p0px1,p0py1,p0pz1,p0chisq1,p0pullm1,p0hisid1,p0losid1,
p0e2,p0px2,p0py2,p0pz2,p0chisq2,p0pullm2,p0hisid2,p0losid2,
p0e3,p0px3,p0py3,p0pz3,p0chisq3,p0pullm3,p0hisid3,p0losid3,
p0e4,p0px4,p0py4,p0pz4,p0chisq4,p0pullm4,p0hisid4,p0losid4,
p0e5,p0px5,p0py5,p0pz5,p0chisq5,p0pullm5,p0hisid5,p0losid5,
p0e6,p0px6,p0py6,p0pz6,p0chisq6,p0pullm6,p0hisid6,p0losid6,
p0e7,p0px7,p0py7,p0pz7,p0chisq7,p0pullm7,p0hisid7,p0losid7,
p0e8,p0px8,p0py8,p0pz8,p0chisq8,p0pullm8,p0hisid8,p0losid8,
p0e9,p0px9,p0py9,p0pz9,p0chisq9,p0pullm9,p0hisid9,p0losid9,
p0e10,p0px10,p0py10,p0pz10,p0chisq10,p0pullm10,p0hisid10,p0losid10,
p0e11,p0px11,p0py11,p0pz11,p0chisq11,p0pullm11,p0hisid11,p0losid11,
p0e12,p0px12,p0py12,p0pz12,p0chisq12,p0pullm12,p0hisid12,p0losid12,
p0e13,p0px13,p0py13,p0pz13,p0chisq13,p0pullm13,p0hisid13,p0losid13,
p0e14,p0px14,p0py14,p0pz14,p0chisq14,p0pullm14,p0hisid14,p0losid14,
p0e15,p0px15,p0py15,p0pz15,p0chisq15,p0pullm15,p0hisid15,p0losid15,

//kRunNum, kEvtNum,
kVarNum};


void
L02_Shower::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;


//m_psi = iHistoManager.histogram("psi mass (GeV)", 1000, 2.5,
//                                       3.5);
//m_test = iHistoManager.histogram("test", 1000, 2.5,
//                                       3.5);

   HINtupleVarNames ntupleNames(kVarNum);
   ntupleNames.addVar(knshower,     "nshower");
   ntupleNames.addVar(kntrack,      "ntrack");
   ntupleNames.addVar(knp0,         "np0");

   ntupleNames.addVar(e1,          "e1");
   ntupleNames.addVar(th1,        "th1");
   ntupleNames.addVar(ph1,       "phi1");
   ntupleNames.addVar(e9251,    "e9251");
   ntupleNames.addVar(barrel1,   "barrel1");
  // ntupleNames.addVar(psim1,    "psim1");

   ntupleNames.addVar(e2,          "e2");
   ntupleNames.addVar(th2,        "th2");
   ntupleNames.addVar(ph2,       "phi2");
   ntupleNames.addVar(e9252,    "e9252");
   ntupleNames.addVar(barrel2,   "barrel2");
  // ntupleNames.addVar(psim2,    "psim2");

   ntupleNames.addVar(e3,          "e3");
   ntupleNames.addVar(th3,        "th3");
   ntupleNames.addVar(ph3,       "phi3");
   ntupleNames.addVar(e9253,    "e9253");
   ntupleNames.addVar(barrel3,   "barrel3");
  // ntupleNames.addVar(psim3,    "psim3");

   ntupleNames.addVar(e4,          "e4");
   ntupleNames.addVar(th4,        "th4");
   ntupleNames.addVar(ph4,       "phi4");
   ntupleNames.addVar(e9254,    "e9254");
   ntupleNames.addVar(barrel4,   "barrel4");
  //ntupleNames.addVar(psim4,    "psim4");

   ntupleNames.addVar(e5,          "e5");
   ntupleNames.addVar(th5,        "th5");
   ntupleNames.addVar(ph5,       "phi5");
   ntupleNames.addVar(e9255,    "e9255");
   ntupleNames.addVar(barrel5,   "barrel5");
  // ntupleNames.addVar(psim5,    "psim5");

   ntupleNames.addVar(e6,          "e6");
   ntupleNames.addVar(th6,        "th6");
   ntupleNames.addVar(ph6,       "phi6");
   ntupleNames.addVar(e9256,    "e9256");
   ntupleNames.addVar(barrel6,   "barrel6");
  // ntupleNames.addVar(psim6,    "psim6");

   ntupleNames.addVar(e7,          "e7");
   ntupleNames.addVar(th7,        "th7");
   ntupleNames.addVar(ph7,       "phi7");
   ntupleNames.addVar(e9257,    "e9257");
   ntupleNames.addVar(barrel7,   "barrel7");
  // ntupleNames.addVar(psim7,    "psim7");

   ntupleNames.addVar(e8,          "e8");
   ntupleNames.addVar(th8,        "th8");
   ntupleNames.addVar(ph8,       "phi8");
   ntupleNames.addVar(e9258,    "e9258");
   ntupleNames.addVar(barrel8,   "barrel8");
  // ntupleNames.addVar(psim1,    "psim1");

   ntupleNames.addVar(e9,          "e9");
   ntupleNames.addVar(th9,        "th9");
   ntupleNames.addVar(ph9,       "phi9");
   ntupleNames.addVar(e9259,    "e9259");
   ntupleNames.addVar(barrel9,   "barrel9");
  // ntupleNames.addVar(psim9,    "psim9");

   ntupleNames.addVar(e10,          "e10");
   ntupleNames.addVar(th10,        "th10");
   ntupleNames.addVar(ph10,       "phi10");
   ntupleNames.addVar(e92510,    "e92510");
   ntupleNames.addVar(barrel10,   "barrel10");
  // ntupleNames.addVar(psim10,    "psim10");

   ntupleNames.addVar(e11,          "e11");
   ntupleNames.addVar(th11,        "th11");
   ntupleNames.addVar(ph11,       "phi11");
   ntupleNames.addVar(e92511,    "e92511");
   ntupleNames.addVar(barrel11,   "barrel11");
//   ntupleNames.addVar(psim11,    "psim11");

   ntupleNames.addVar(e12,          "e12");
   ntupleNames.addVar(th12,        "th12");
   ntupleNames.addVar(ph12,       "phi12");
   ntupleNames.addVar(e92512,    "e92512");
   ntupleNames.addVar(barrel12,   "barrel12");
   //ntupleNames.addVar(psim12,    "psim12");

   ntupleNames.addVar(e13,          "e13");
   ntupleNames.addVar(th13,        "th13");
   ntupleNames.addVar(ph13,       "phi13");
   ntupleNames.addVar(e92513,    "e92513");
   ntupleNames.addVar(barrel13,   "barrel13");
  // ntupleNames.addVar(psim13,    "psim13");

   ntupleNames.addVar(e14,          "e14");
   ntupleNames.addVar(th14,        "th14");
   ntupleNames.addVar(ph14,       "phi14");
   ntupleNames.addVar(e92514,    "e92514");
   ntupleNames.addVar(barrel14,   "barrel14");
//   ntupleNames.addVar(psim14,    "psim14");

   ntupleNames.addVar(e15,          "e15");
   ntupleNames.addVar(th15,        "th15");
   ntupleNames.addVar(ph15,       "phi15");
   ntupleNames.addVar(e92515,    "e92515");
   ntupleNames.addVar(barrel15,   "barrel15");

   ntupleNames.addVar(e16,          "e16");
   ntupleNames.addVar(th16,        "th16");
   ntupleNames.addVar(ph16,       "phi16");
   ntupleNames.addVar(e92516,    "e92516");
   ntupleNames.addVar(barrel16,   "barrel16");

   ntupleNames.addVar(e17,          "e17");
   ntupleNames.addVar(th17,        "th17");
   ntupleNames.addVar(ph17,       "phi17");
   ntupleNames.addVar(e92517,    "e92517");
   ntupleNames.addVar(barrel17,   "barrel17");

   ntupleNames.addVar(e18,          "e18");
   ntupleNames.addVar(th18,        "th18");
   ntupleNames.addVar(ph18,       "phi18");
   ntupleNames.addVar(e92518,    "e92518");
   ntupleNames.addVar(barrel18,   "barrel18");

   ntupleNames.addVar(e19,          "e19");
   ntupleNames.addVar(th19,        "th19");
   ntupleNames.addVar(ph19,       "phi19");
   ntupleNames.addVar(e92519,    "e92519");
   ntupleNames.addVar(barrel19,   "barrel19");

   ntupleNames.addVar(e20,          "e20");
   ntupleNames.addVar(th20,        "th20");
   ntupleNames.addVar(ph20,       "phi20");
   ntupleNames.addVar(e92520,    "e92520");
   ntupleNames.addVar(barrel20,   "barrel20");


   ntupleNames.addVar(kte1,    "te1");
   ntupleNames.addVar(kpx1,    "px1");
   ntupleNames.addVar(kpy1,    "py1");
   ntupleNames.addVar(kpz1,    "pz1");
   ntupleNames.addVar(kcharge1, "charge1");
 
   ntupleNames.addVar(kte2,    "te2");
   ntupleNames.addVar(kpx2,    "px2");
   ntupleNames.addVar(kpy2,    "py2");
   ntupleNames.addVar(kpz2,    "pz2");
   ntupleNames.addVar(kcharge2, "charge2");


   ntupleNames.addVar(kte3,    "te3");
   ntupleNames.addVar(kpx3,    "px3");
   ntupleNames.addVar(kpy3,    "py3");
   ntupleNames.addVar(kpz3,    "pz3");
   ntupleNames.addVar(kcharge3, "charge3");


   ntupleNames.addVar(kte4,    "te4");
   ntupleNames.addVar(kpx4,    "px4");
   ntupleNames.addVar(kpy4,    "py4");
   ntupleNames.addVar(kpz4,    "pz4");
   ntupleNames.addVar(kcharge4, "charge4");


   ntupleNames.addVar(kte5,    "te5");
   ntupleNames.addVar(kpx5,    "px5");
   ntupleNames.addVar(kpy5,    "py5");
   ntupleNames.addVar(kpz5,    "pz5");
   ntupleNames.addVar(kcharge5, "charge5");


   ntupleNames.addVar(kte6,    "te6");
   ntupleNames.addVar(kpx6,    "px6");
   ntupleNames.addVar(kpy6,    "py6");
   ntupleNames.addVar(kpz6,    "pz6");
   ntupleNames.addVar(kcharge6, "charge6");


   ntupleNames.addVar(kte7,    "te7");
   ntupleNames.addVar(kpx7,    "px7");
   ntupleNames.addVar(kpy7,    "py7");
   ntupleNames.addVar(kpz7,    "pz7");
   ntupleNames.addVar(kcharge7, "charge7");


   ntupleNames.addVar(kte8,    "te8");
   ntupleNames.addVar(kpx8,    "px8");
   ntupleNames.addVar(kpy8,    "py8");
   ntupleNames.addVar(kpz8,    "pz8");
   ntupleNames.addVar(kcharge8, "charge8");


   ntupleNames.addVar(kte9,    "te9");
   ntupleNames.addVar(kpx9,    "px9");
   ntupleNames.addVar(kpy9,    "py9");
   ntupleNames.addVar(kpz9,    "pz9");
   ntupleNames.addVar(kcharge9, "charge9");


   ntupleNames.addVar(kte10,    "te10");
   ntupleNames.addVar(kpx10,    "px10");
   ntupleNames.addVar(kpy10,    "py10");
   ntupleNames.addVar(kpz10,    "pz10");
   ntupleNames.addVar(kcharge10, "charge10");


   ntupleNames.addVar(kte11,    "te11");
   ntupleNames.addVar(kpx11,    "px11");
   ntupleNames.addVar(kpy11,    "py11");
   ntupleNames.addVar(kpz11,    "pz11");
   ntupleNames.addVar(kcharge11, "charge11");


   ntupleNames.addVar(kte12,    "te12");
   ntupleNames.addVar(kpx12,    "px12");
   ntupleNames.addVar(kpy12,    "py12");
   ntupleNames.addVar(kpz12,    "pz12");
   ntupleNames.addVar(kcharge12, "charge12");


   ntupleNames.addVar(kte13,    "te13");
   ntupleNames.addVar(kpx13,    "px13");
   ntupleNames.addVar(kpy13,    "py13");
   ntupleNames.addVar(kpz13,    "pz13");
   ntupleNames.addVar(kcharge13, "charge13");


   ntupleNames.addVar(kte14,    "te14");
   ntupleNames.addVar(kpx14,    "px14");
   ntupleNames.addVar(kpy14,    "py14");
   ntupleNames.addVar(kpz14,    "pz14");
   ntupleNames.addVar(kcharge14, "charge14");


   ntupleNames.addVar(kte15,    "te15");
   ntupleNames.addVar(kpx15,    "px15");
   ntupleNames.addVar(kpy15,    "py15");
   ntupleNames.addVar(kpz15,    "pz15");
   ntupleNames.addVar(kcharge15, "charge15");

   ntupleNames.addVar(p0e1,     "p0e1");
   ntupleNames.addVar(p0px1,    "p0px1");
   ntupleNames.addVar(p0py1,    "p0py1");
   ntupleNames.addVar(p0pz1,    "p0pz1");
   ntupleNames.addVar(p0chisq1, "p0chisq1");
   ntupleNames.addVar(p0pullm1, "p0pullm1");
   ntupleNames.addVar(p0hisid1, "p0hisid1");
   ntupleNames.addVar(p0losid1, "p0losid1");

   ntupleNames.addVar(p0e2,     "p0e2");
   ntupleNames.addVar(p0px2,    "p0px2");
   ntupleNames.addVar(p0py2,    "p0py2");
   ntupleNames.addVar(p0pz2,    "p0pz2");
   ntupleNames.addVar(p0chisq2, "p0chisq2");
   ntupleNames.addVar(p0pullm2, "p0pullm2");
   ntupleNames.addVar(p0hisid2, "p0hisid2");
   ntupleNames.addVar(p0losid2, "p0losid2");

   ntupleNames.addVar(p0e3,     "p0e3");
   ntupleNames.addVar(p0px3,    "p0px3");
   ntupleNames.addVar(p0py3,    "p0py3");
   ntupleNames.addVar(p0pz3,    "p0pz3");
   ntupleNames.addVar(p0chisq3, "p0chisq3");
   ntupleNames.addVar(p0pullm3, "p0pullm3");
   ntupleNames.addVar(p0hisid3, "p0hisid3");
   ntupleNames.addVar(p0losid3, "p0losid3");

   ntupleNames.addVar(p0e4,     "p0e4");
   ntupleNames.addVar(p0px4,    "p0px4");
   ntupleNames.addVar(p0py4,    "p0py4");
   ntupleNames.addVar(p0pz4,    "p0pz4");
   ntupleNames.addVar(p0chisq4, "p0chisq4");
   ntupleNames.addVar(p0pullm4, "p0pullm4");
   ntupleNames.addVar(p0hisid4, "p0hisid4");
   ntupleNames.addVar(p0losid4, "p0losid4");

   ntupleNames.addVar(p0e5,     "p0e5");
   ntupleNames.addVar(p0px5,    "p0px5");
   ntupleNames.addVar(p0py5,    "p0py5");
   ntupleNames.addVar(p0pz5,    "p0pz5");
   ntupleNames.addVar(p0chisq5, "p0chisq5");
   ntupleNames.addVar(p0pullm5, "p0pullm5");
   ntupleNames.addVar(p0hisid5, "p0hisid5");
   ntupleNames.addVar(p0losid5, "p0losid5");

   ntupleNames.addVar(p0e6,     "p0e6");
   ntupleNames.addVar(p0px6,    "p0px6");
   ntupleNames.addVar(p0py6,    "p0py6");
   ntupleNames.addVar(p0pz6,    "p0pz6");
   ntupleNames.addVar(p0chisq6, "p0chisq6");
   ntupleNames.addVar(p0pullm6, "p0pullm6");
   ntupleNames.addVar(p0hisid6, "p0hisid6");
   ntupleNames.addVar(p0losid6, "p0losid6");

   ntupleNames.addVar(p0e7,     "p0e7");
   ntupleNames.addVar(p0px7,    "p0px7");
   ntupleNames.addVar(p0py7,    "p0py7");
   ntupleNames.addVar(p0pz7,    "p0pz7");
   ntupleNames.addVar(p0chisq7, "p0chisq7");
   ntupleNames.addVar(p0pullm7, "p0pullm7");
   ntupleNames.addVar(p0hisid7, "p0hisid7");
   ntupleNames.addVar(p0losid7, "p0losid7");

   ntupleNames.addVar(p0e8,     "p0e8");
   ntupleNames.addVar(p0px8,    "p0px8");
   ntupleNames.addVar(p0py8,    "p0py8");
   ntupleNames.addVar(p0pz8,    "p0pz8");
   ntupleNames.addVar(p0chisq8, "p0chisq8");
   ntupleNames.addVar(p0pullm8, "p0pullm8");
   ntupleNames.addVar(p0hisid8, "p0hisid8");
   ntupleNames.addVar(p0losid8, "p0losid8");

   ntupleNames.addVar(p0e9,     "p0e9");
   ntupleNames.addVar(p0px9,    "p0px9");
   ntupleNames.addVar(p0py9,    "p0py9");
   ntupleNames.addVar(p0pz9,    "p0pz9");
   ntupleNames.addVar(p0chisq9, "p0chisq9");
   ntupleNames.addVar(p0pullm9, "p0pullm9");
   ntupleNames.addVar(p0hisid9, "p0hisid9");
   ntupleNames.addVar(p0losid9, "p0losid9");

   ntupleNames.addVar(p0e10,     "p0e10");
   ntupleNames.addVar(p0px10,    "p0px10");
   ntupleNames.addVar(p0py10,    "p0py10");
   ntupleNames.addVar(p0pz10,    "p0pz10");
   ntupleNames.addVar(p0chisq10, "p0chisq10");
   ntupleNames.addVar(p0pullm10, "p0pullm10");
   ntupleNames.addVar(p0hisid10, "p0hisid10");
   ntupleNames.addVar(p0losid10, "p0losid10");

   ntupleNames.addVar(p0e11,     "p0e11");
   ntupleNames.addVar(p0px11,    "p0px11");
   ntupleNames.addVar(p0py11,    "p0py11");
   ntupleNames.addVar(p0pz11,    "p0pz11");
   ntupleNames.addVar(p0chisq11, "p0chisq11");
   ntupleNames.addVar(p0pullm11, "p0pullm11");
   ntupleNames.addVar(p0hisid11, "p0hisid11");
   ntupleNames.addVar(p0losid11, "p0losid11");

   ntupleNames.addVar(p0e12,     "p0e12");
   ntupleNames.addVar(p0px12,    "p0px12");
   ntupleNames.addVar(p0py12,    "p0py12");
   ntupleNames.addVar(p0pz12,    "p0pz12");
   ntupleNames.addVar(p0chisq12, "p0chisq12");
   ntupleNames.addVar(p0pullm12, "p0pullm12");
   ntupleNames.addVar(p0hisid12, "p0hisid12");
   ntupleNames.addVar(p0losid12, "p0losid12");

   ntupleNames.addVar(p0e13,     "p0e13");
   ntupleNames.addVar(p0px13,    "p0px13");
   ntupleNames.addVar(p0py13,    "p0py13");
   ntupleNames.addVar(p0pz13,    "p0pz13");
   ntupleNames.addVar(p0chisq13, "p0chisq13");
   ntupleNames.addVar(p0pullm13, "p0pullm13");
   ntupleNames.addVar(p0hisid13, "p0hisid13");
   ntupleNames.addVar(p0losid13, "p0losid13");

   ntupleNames.addVar(p0e14,     "p0e14");
   ntupleNames.addVar(p0px14,    "p0px14");
   ntupleNames.addVar(p0py14,    "p0py14");
   ntupleNames.addVar(p0pz14,    "p0pz14");
   ntupleNames.addVar(p0chisq14, "p0chisq14");
   ntupleNames.addVar(p0pullm14, "p0pullm14");
   ntupleNames.addVar(p0hisid14, "p0hisid14");
   ntupleNames.addVar(p0losid14, "p0losid14");

   ntupleNames.addVar(p0e15,     "p0e15");
   ntupleNames.addVar(p0px15,    "p0px15");
   ntupleNames.addVar(p0py15,    "p0py15");
   ntupleNames.addVar(p0pz15,    "p0pz15");
   ntupleNames.addVar(p0chisq15, "p0chisq15");
   ntupleNames.addVar(p0pullm15, "p0pullm15");
   ntupleNames.addVar(p0hisid15, "p0hisid15");
   ntupleNames.addVar(p0losid15, "p0losid15");



//   ntupleNames.addVar(kRunNum,    "RunNum");
//   ntupleNames.addVar(kEvtNum,    "EvtNum");

//   ntupleNames.addVar(psim,    "psim");




   m_showerTuple = iHistoManager.ntuple(10,"tuple", kVarNum, 10000, ntupleNames.names());

 

}

// Good track selection function
DABoolean isGoodTrack(const NavTrack& track) {
   const TRHelixFit& helix = *track.pionHelix();
   const TRTrackFitQuality& fitqual = *track.pionQuality();
   return (0.05 < (*track.pionFit()).pmag() && (*track.pionFit()).pmag() < 2.0
           && fabs(helix.d0()) < 0.005
           && fabs(helix.z0()) < 0.05
           && fitqual.chiSquare() < 100000
           && fitqual.ratioNumberHitsToExpected() > 0.5
           && ! fitqual.fitAbort());
}

// Pion particle ID by dE/dx
/*DABoolean isPion(const NavTrack& track) {
   const FAItem<DedxInfo>& dedxinfo = track.dedxInfo();
   return (dedxinfo.valid() && (*dedxinfo).valid()
           && fabs((*dedxinfo).piSigma()) < 3.0);
}
*/

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
L02_Shower::event( Frame& iFrame )          // anal3 equiv.
{
//   report( INFO, kFacilityString ) << "here in event()" << endl;
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   const int kMaxShower = 20;
   const int kMaxTrack = 15;
   const int kMaxPi0 = 15;
//   NavShower::Identifier SID[kMaxShower];
   double E[kMaxShower] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double Theta[kMaxShower] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double Phi[kMaxShower] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double E925[kMaxShower] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double Barrel[kMaxShower] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.}; 
//   double PsiM[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double PE[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double PX[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double PY[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double PZ[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double Charge[kMaxTrack] = {-2.,-2.,-2.,-2.,-2.,-2.,-2.,-2.,-2.,-2.,-2.,-2.,-2.,-2.,-2.};

   double P0E[kMaxPi0] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double P0PX[kMaxPi0] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double P0PY[kMaxPi0] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double P0PZ[kMaxPi0] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double P0CHISQ[kMaxPi0] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double P0PULLM[kMaxPi0] = {10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.,10.};
   int P0HISID[kMaxPi0] = {-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10};
   int P0LOSID[kMaxPi0] = {-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10};


   float tuple[kVarNum];

   //float psi = 2.7;
//   float tt = 0.2;
//   bool psi = false;

   // Extract total 4-momentum to get CM energy

   FAItem< LabNet4Momentum > labMomentum ;
   extract( iFrame.record( Stream::kStartRun ), labMomentum ) ;

   // Extract tracks
   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ), trackTable );

   // Set up loop
   FATable< NavTrack >::const_iterator trackBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackEnd = trackTable.end();

   int unmatchedTracks = 0;


   for (FATable< NavTrack >::const_iterator trackItr1 = trackBegin;
        trackItr1 != trackEnd ; ++trackItr1 ){
         if( isGoodTrack( *trackItr1 )  )  {

      const TDKinematicFit& KineData1 = *( *trackItr1 ).pionFit() ;

      int j = unmatchedTracks++;

      if(j<kMaxTrack){

      PE[j]=KineData1.lorentzMomentum().e();
      PX[j]=KineData1.lorentzMomentum().px();
      PY[j]=KineData1.lorentzMomentum().py();
      //E925[j]=showerItr->attributes().e9oe25();
      PZ[j]=KineData1.lorentzMomentum().pz();
      Charge[j]=KineData1.charge();
      }
   }
   }
   
    FATable<NavPi0ToGG> pi0Table;
    extract( iFrame.record( Stream::kEvent ) , pi0Table );
     
    FATable< NavPi0ToGG >::const_iterator pi0Begin = pi0Table.begin();
    FATable< NavPi0ToGG >::const_iterator pi0End = pi0Table.end();
    
    int numPi0 = 0;

    for (FATable< NavPi0ToGG >::const_iterator pi0Itr = pi0Begin;
         pi0Itr != pi0End ; ++pi0Itr) {
      if(pi0Itr.valid()
        && pi0Itr->pi0().fit()
        && pi0Itr->pi0().converged()
        && (pi0Itr->pi0().chisq() < 500)
        && (fabs(pi0Itr->pi0().pullMass()) < 3) ) {

        if(numPi0<kMaxPi0) {
          P0E[numPi0] = pi0Itr->pi0().energy();
          P0PX[numPi0] = pi0Itr->pi0().px();
          P0PY[numPi0] = pi0Itr->pi0().py();
          P0PZ[numPi0] = pi0Itr->pi0().pz();
          P0CHISQ[numPi0] = pi0Itr->pi0().chisq();
          P0PULLM[numPi0] = pi0Itr->pi0().pullMass();
          P0HISID[numPi0] = pi0Itr->hiEnShower().identifier();
          P0LOSID[numPi0] = pi0Itr->loEnShower().identifier();
//          P0HISID[numPi0] = hiShowerInd;
//          P0LOSID[numPi0] = loShowerInd;
           }

           // continue counting
           numPi0++;
        }

      } 

   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ) , showerTable, "GoodThings" );

   FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
   FATable< NavShower >::const_iterator showerEnd = showerTable.end();
  
   int unmatchedShowers = 0; 

   for (FATable< NavShower >::const_iterator showerItr = showerBegin; 
        showerItr != showerEnd ; ++showerItr ){
  
   if((showerItr->attributes().goodBarrel() ||
       showerItr->attributes().goodEndcap() ) ) {
      
      int j = unmatchedShowers++;

      if(j<kMaxShower){
      E[j]=showerItr->attributes().energy();
      Theta[j]=showerItr->attributes().theta();
      Phi[j]=showerItr->attributes().phi();
      //E925[j]=showerItr->attributes().e9oe25();
      E925[j]=showerItr->attributes().x925();
      Barrel[j]=(showerItr->attributes().goodBarrel()>0);
      }
   }
//   }
   } // end of loop of NavShowers

/*   // Extract tracks
   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ), trackTable );

   // Set up loop
   FATable< NavTrack >::const_iterator trackBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackEnd = trackTable.end();

   int unmatchedTracks = 0;
   
   for( FATable< NavTrack >::const_iterator trackItr1 = trackBegin ;
           trackItr1 != trackEnd ;
           ++trackItr1 )
      {
         // Proceed only if is good "kaon"
         if( isGoodTrack( *trackItr1 ) && isPion( *trackItr1 ) )
         {
            const TDKinematicFit& kineData1 = *( *trackItr1 ).pionFit();

            // Loop over *all* tracks since (a, b) != (b, a)
            for( FATable< NavTrack >::const_iterator trackItr2 = trackItr1+1 ;
                 trackItr2 != trackEnd ;
                 ++trackItr2 )
            {
               const TDKinematicFit& kineData2 = *( *trackItr2 ).pionFit() ;

               // Proceed if is good "pion" and opposite charge to track 1
               if( isGoodTrack( *trackItr2 ) &&
                   isPion( *trackItr2 ) &&
                   kineData2.charge() == -kineData1.charge() )
               {
  
                  int j = unmatchedTracks++;

                  const HepLorentzVector& v1 = kineData1.lorentzMomentum();
                  const HepLorentzVector& v2 = kineData2.lorentzMomentum();

                  // Total 4-vector.  Invariant mass would be tot.m().
                  HepLorentzVector tot( v1 + v2 ) ;

                  // D candidate energy
                  HepDouble psimass2 = pow((3.686-tot.e()),2)-pow(tot.e(),2)+pow(tot.m(),2);
                  HepDouble mass = sqrt(psimass2);
                  // Set "tot" energy to beam energy ("beam constraining")
                  // Now, tot.m() will give the beam-constrained mass.
//                  tot.setE( ( *labMomentum ).e() / 2. ) ;
                  // fill histogram with mbc and deltae.
//                  float trackTuple[knum_vars];
//                  trackTuple[psimass] = mass;
//                  m_trackTuple->fill(trackTuple);
               }
            }
         }
   }
*/

//   float tuple[kVarNum];

   tuple[knshower] = unmatchedShowers;
   tuple[kntrack] = unmatchedTracks;
   tuple[knp0] = numPi0;

   tuple[e1] = E[0];
   tuple[th1] = Theta[0];
   tuple[ph1] = Phi[0];
   tuple[e9251] = E925[0];
   tuple[barrel1] = Barrel[0];
   tuple[e2] = E[1];
   tuple[th2] = Theta[1];
   tuple[ph2] = Phi[1];
   tuple[e9252] = E925[1];
   tuple[barrel2] = Barrel[1];
   tuple[e3] = E[2];
   tuple[th3] = Theta[2];
   tuple[ph3] = Phi[2];
   tuple[e9253] = E925[2];
   tuple[barrel3] = Barrel[2];
   tuple[e4] = E[3];
   tuple[th4] = Theta[3];
   tuple[ph4] = Phi[3];
   tuple[e9254] = E925[3];
   tuple[barrel4] = Barrel[3];
   tuple[e5] = E[4];
   tuple[th5] = Theta[4];
   tuple[ph5] = Phi[4];
   tuple[e9255] = E925[4];
   tuple[barrel5] = Barrel[4];
   tuple[e6] = E[5];
   tuple[th6] = Theta[5];
   tuple[ph6] = Phi[5];
   tuple[e9256] = E925[5];
   tuple[barrel6] = Barrel[5];
   tuple[e7] = E[6];
   tuple[th7] = Theta[6];
   tuple[ph7] = Phi[6];
   tuple[e9257] = E925[6];
   tuple[barrel7] = Barrel[6];
   tuple[e8] = E[7];
   tuple[th8] = Theta[7];
   tuple[ph8] = Phi[7];
   tuple[e9258] = E925[7];
   tuple[barrel8] = Barrel[7];
   tuple[e9] = E[8];
   tuple[th9] = Theta[8];
   tuple[ph9] = Phi[8];
   tuple[e9259] = E925[8];
   tuple[barrel9] = Barrel[8];
   tuple[e10] = E[9];
   tuple[th10] = Theta[9];
   tuple[ph10] = Phi[9];
   tuple[e92510] = E925[9];
   tuple[barrel10] = Barrel[9];
   tuple[e11] = E[10];
   tuple[th11] = Theta[10];
   tuple[ph11] = Phi[10];
   tuple[e92511] = E925[10];
   tuple[barrel11] = Barrel[10];
   tuple[e12] = E[11];
   tuple[th12] = Theta[11];
   tuple[ph12] = Phi[11];
   tuple[e92512] = E925[11];
   tuple[barrel12] = Barrel[11];
   tuple[e13] = E[12];
   tuple[th13] = Theta[12];
   tuple[ph13] = Phi[12];
   tuple[e92513] = E925[12];
   tuple[barrel13] = Barrel[12];
   tuple[e14] = E[13];
   tuple[th14] = Theta[13];
   tuple[ph14] = Phi[13];
   tuple[e92514] = E925[13];
   tuple[barrel14] = Barrel[13];
   tuple[e15] = E[14];
   tuple[th15] = Theta[14];
   tuple[ph15] = Phi[14];
   tuple[e92515] = E925[14];
   tuple[barrel15] = Barrel[14];
   tuple[e16] = E[15];
   tuple[th16] = Theta[15];
   tuple[ph16] = Phi[15];
   tuple[e92516] = E925[15];
   tuple[barrel16] = Barrel[15];
   tuple[e17] = E[16];
   tuple[th17] = Theta[16];
   tuple[ph17] = Phi[16];
   tuple[e92517] = E925[16];
   tuple[barrel17] = Barrel[16];
   tuple[e18] = E[17];
   tuple[th18] = Theta[17];
   tuple[ph18] = Phi[17];
   tuple[e92518] = E925[17];
   tuple[barrel18] = Barrel[17];
   tuple[e19] = E[18];
   tuple[th19] = Theta[18];
   tuple[ph19] = Phi[18];
   tuple[e92519] = E925[18];
   tuple[barrel19] = Barrel[18];
   tuple[e20] = E[19];
   tuple[th20] = Theta[19];
   tuple[ph20] = Phi[19];
   tuple[e92520] = E925[19];
   tuple[barrel20] = Barrel[19];



   tuple[kte1] = PE[0];
   tuple[kpx1] = PX[0];
   tuple[kpy1] = PY[0];
   tuple[kpz1] = PZ[0];
   tuple[kcharge1] = Charge[0];
   tuple[kte2] = PE[1];
   tuple[kpx2] = PX[1];
   tuple[kpy2] = PY[1];
   tuple[kpz2] = PZ[1];
   tuple[kcharge2] = Charge[1];
   tuple[kte3] = PE[2];
   tuple[kpx3] = PX[2];
   tuple[kpy3] = PY[2];
   tuple[kpz3] = PZ[2];
   tuple[kcharge3] = Charge[2];
   tuple[kte4] = PE[3];
   tuple[kpx4] = PX[3];
   tuple[kpy4] = PY[3];
   tuple[kpz4] = PZ[3];
   tuple[kcharge4] = Charge[3];
   tuple[kte5] = PE[4];
   tuple[kpx5] = PX[4];
   tuple[kpy5] = PY[4];
   tuple[kpz5] = PZ[4];
   tuple[kcharge5] = Charge[4];
   tuple[kte6] = PE[5];
   tuple[kpx6] = PX[5];
   tuple[kpy6] = PY[5];
   tuple[kpz6] = PZ[5];
   tuple[kcharge6] = Charge[5];
   tuple[kte7] = PE[6];
   tuple[kpx7] = PX[6];
   tuple[kpy7] = PY[6];
   tuple[kpz7] = PZ[6];
   tuple[kcharge7] = Charge[6];
   tuple[kte8] = PE[7];
   tuple[kpx8] = PX[7];
   tuple[kpy8] = PY[7];
   tuple[kpz8] = PZ[7];
   tuple[kcharge8] = Charge[7];
   tuple[kte9] = PE[8];
   tuple[kpx9] = PX[8];
   tuple[kpy9] = PY[8];
   tuple[kpz9] = PZ[8];
   tuple[kcharge9] = Charge[8];
   tuple[kte10] = PE[9];
   tuple[kpx10] = PX[9];
   tuple[kpy10] = PY[9];
   tuple[kpz10] = PZ[9];
   tuple[kcharge10] = Charge[9];
   tuple[kte11] = PE[10];
   tuple[kpx11] = PX[10];
   tuple[kpy11] = PY[10];
   tuple[kpz11] = PZ[10];
   tuple[kcharge11] = Charge[10];
   tuple[kte12] = PE[11];
   tuple[kpx12] = PX[11];
   tuple[kpy12] = PY[11];
   tuple[kpz12] = PZ[11];
   tuple[kcharge12] = Charge[11];
   tuple[kte13] = PE[12];
   tuple[kpx13] = PX[12];
   tuple[kpy13] = PY[12];
   tuple[kpz13] = PZ[12];
   tuple[kcharge13] = Charge[12];
   tuple[kte14] = PE[13];
   tuple[kpx14] = PX[13];
   tuple[kpy14] = PY[13];
   tuple[kpz14] = PZ[13];
   tuple[kcharge14] = Charge[13];
   tuple[kte15] = PE[14];
   tuple[kpx15] = PX[14];
   tuple[kpy15] = PY[14];
   tuple[kpz15] = PZ[14];
   tuple[kcharge15] = Charge[14];

   tuple[p0e1] = P0E[0];
   tuple[p0px1] = P0PX[0];
   tuple[p0py1] = P0PY[0];
   tuple[p0pz1] = P0PZ[0];
   tuple[p0chisq1] = P0CHISQ[0];
   tuple[p0pullm1] = P0PULLM[0];
   tuple[p0hisid1] = P0HISID[0];
   tuple[p0losid1] = P0LOSID[0];

   tuple[p0e2] = P0E[1];
   tuple[p0px2] = P0PX[1];
   tuple[p0py2] = P0PY[1];
   tuple[p0pz2] = P0PZ[1];
   tuple[p0chisq2] = P0CHISQ[1];
   tuple[p0pullm2] = P0PULLM[1];
   tuple[p0hisid2] = P0HISID[1];
   tuple[p0losid2] = P0LOSID[1];

   tuple[p0e3] = P0E[2];
   tuple[p0px3] = P0PX[2];
   tuple[p0py3] = P0PY[2];
   tuple[p0pz3] = P0PZ[2];
   tuple[p0chisq3] = P0CHISQ[2];
   tuple[p0pullm3] = P0PULLM[2];
   tuple[p0hisid3] = P0HISID[2];
   tuple[p0losid3] = P0LOSID[2];

   tuple[p0e4] = P0E[3];
   tuple[p0px4] = P0PX[3];
   tuple[p0py4] = P0PY[3];
   tuple[p0pz4] = P0PZ[3];
   tuple[p0chisq4] = P0CHISQ[3];
   tuple[p0pullm4] = P0PULLM[3];
   tuple[p0hisid4] = P0HISID[3];
   tuple[p0losid4] = P0LOSID[3];

   tuple[p0e5] = P0E[4];
   tuple[p0px5] = P0PX[4];
   tuple[p0py5] = P0PY[4];
   tuple[p0pz5] = P0PZ[4];
   tuple[p0chisq5] = P0CHISQ[4];
   tuple[p0pullm5] = P0PULLM[4];
   tuple[p0hisid5] = P0HISID[4];
   tuple[p0losid5] = P0LOSID[4];

   tuple[p0e6] = P0E[5];
   tuple[p0px6] = P0PX[5];
   tuple[p0py6] = P0PY[5];
   tuple[p0pz6] = P0PZ[5];
   tuple[p0chisq6] = P0CHISQ[5];
   tuple[p0pullm6] = P0PULLM[5];
   tuple[p0hisid6] = P0HISID[5];
   tuple[p0losid6] = P0LOSID[5];

   tuple[p0e7] = P0E[6];
   tuple[p0px7] = P0PX[6];
   tuple[p0py7] = P0PY[6];
   tuple[p0pz7] = P0PZ[6];
   tuple[p0chisq7] = P0CHISQ[6];
   tuple[p0pullm7] = P0PULLM[6];
   tuple[p0hisid7] = P0HISID[6];
   tuple[p0losid7] = P0LOSID[6];

   tuple[p0e8] = P0E[7];
   tuple[p0px8] = P0PX[7];
   tuple[p0py8] = P0PY[7];
   tuple[p0pz8] = P0PZ[7];
   tuple[p0chisq8] = P0CHISQ[7];
   tuple[p0pullm8] = P0PULLM[7];
   tuple[p0hisid8] = P0HISID[7];
   tuple[p0losid8] = P0LOSID[7];

   tuple[p0e9] = P0E[8];
   tuple[p0px9] = P0PX[8];
   tuple[p0py9] = P0PY[8];
   tuple[p0pz9] = P0PZ[8];
   tuple[p0chisq9] = P0CHISQ[8];
   tuple[p0pullm9] = P0PULLM[8];
   tuple[p0hisid9] = P0HISID[8];
   tuple[p0losid9] = P0LOSID[8];

   tuple[p0e10] = P0E[9];
   tuple[p0px10] = P0PX[9];
   tuple[p0py10] = P0PY[9];
   tuple[p0pz10] = P0PZ[9];
   tuple[p0chisq10] = P0CHISQ[9];
   tuple[p0pullm10] = P0PULLM[9];
   tuple[p0hisid10] = P0HISID[9];
   tuple[p0losid10] = P0LOSID[9];

   tuple[p0e11] = P0E[10];
   tuple[p0px11] = P0PX[10];
   tuple[p0py11] = P0PY[10];
   tuple[p0pz11] = P0PZ[10];
   tuple[p0chisq11] = P0CHISQ[10];
   tuple[p0pullm11] = P0PULLM[10];
   tuple[p0hisid11] = P0HISID[10];
   tuple[p0losid11] = P0LOSID[10];

   tuple[p0e12] = P0E[11];
   tuple[p0px12] = P0PX[11];
   tuple[p0py12] = P0PY[11];
   tuple[p0pz12] = P0PZ[11];
   tuple[p0chisq12] = P0CHISQ[11];
   tuple[p0pullm12] = P0PULLM[11];
   tuple[p0hisid12] = P0HISID[11];
   tuple[p0losid12] = P0LOSID[11];

   tuple[p0e13] = P0E[12];
   tuple[p0px13] = P0PX[12];
   tuple[p0py13] = P0PY[12];
   tuple[p0pz13] = P0PZ[12];
   tuple[p0chisq13] = P0CHISQ[12];
   tuple[p0pullm13] = P0PULLM[12];
   tuple[p0hisid13] = P0HISID[12];
   tuple[p0losid13] = P0LOSID[12];

   tuple[p0e14] = P0E[13];
   tuple[p0px14] = P0PX[13];
   tuple[p0py14] = P0PY[13];
   tuple[p0pz14] = P0PZ[13];
   tuple[p0chisq14] = P0CHISQ[13];
   tuple[p0pullm14] = P0PULLM[13];
   tuple[p0hisid14] = P0HISID[13];
   tuple[p0losid14] = P0LOSID[13];

   tuple[p0e15] = P0E[14];
   tuple[p0px15] = P0PX[14];
   tuple[p0py15] = P0PY[14];
   tuple[p0pz15] = P0PZ[14];
   tuple[p0chisq15] = P0CHISQ[14];
   tuple[p0pullm15] = P0PULLM[14];
   tuple[p0hisid15] = P0HISID[14];
   tuple[p0losid15] = P0LOSID[14];




   (*m_showerTuple).fill(tuple);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
L02_Shower::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
L02_Shower::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

//
// const member functions
//

//
// static member functions
//
