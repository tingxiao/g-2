// -*- C++ -*-
//
// Package:     InclusiveProc
// Module:      InclusiveProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      pts/9
// Created:     Tue May  1 17:28:20 CDT 2012
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "InclusiveProc/InclusiveProc.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "HistogramInterface/HINtupleVarNames.h"
#include "HistogramInterface/HINtupleArray.h"
#include "HistogramInterface/HIHist1D.h"
#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
#include "Navigation/NavShowerServer.h"
#include "C3ccProd/CcFortranShowerCorrector.h"
#include "C3Mu/MuTrack.h"
#include "Navigation/NavMuonId.h"
#include "Navigation/NavTkShMatch.h"

//I added the following at the suggestion of the NavShower web page
#include "Navigation/NavConReg.h"
#include "KinematicTrajectory/KTKinematicData.h"
#include "Navigation/NavTkShMatch.h"
#include "C3cc/CcAssignedEnergyHit.h"

#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"
#include "Navigation/NavElecId.h"

#include "FitEvt/FitEvtSettings.h"
#include "FitEvt/FitEvt.h"
#include "BeamEnergy/BeamEnergy.h"
#include "MagField/MagneticField.h"
#include "MagField/MFFieldMap.h"
#include "BeamSpot/BeamSpot.h"
#include "CleoDB/DBEventHeader.h"
#include "TriggerData/TriggerData.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "Level4Proc/Level4Decision.h"

//RICH example
#include "Navigation/NavRich.h"
//Dedx example
#include "DedxInfo/DedxInfo.h"




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
static const char* const kFacilityString = "Processor.InclusiveProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
InclusiveProc::InclusiveProc( void )               // anal1
   : Processor( "InclusiveProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &InclusiveProc::event,    Stream::kEvent );
   //bind( &InclusiveProc::beginRun, Stream::kBeginRun );
   //bind( &InclusiveProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

InclusiveProc::~InclusiveProc()                    // anal5
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
InclusiveProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
InclusiveProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------

enum {
nt,                   // number of tracks
e1,th1,phi1,e9251,d1,
e2,th2,phi2,e9252,d2,
e3,th3,phi3,e9253,d3,
e4,th4,phi4,e9254,d4,
e5,th5,phi5,e9255,d5,
e6,th6,phi6,e9256,d6,
e7,th7,phi7,e9257,d7,
e8,th8,phi8,e9258,d8,
e9,th9,phi9,e9259,d9,
e10,th10,phi10,e92510,d10,
e11,th11,phi11,e92511,d11,
e12,th12,phi12,e92512,d12,
e13,th13,phi13,e92513,d13,
e14,th14,phi14,e92514,d14,
e15,th15,phi15,e92515,d15,
e16,th16,phi16,e92516,d16,
eop1,eop2,trte1,trpx1,trpy1,trpz1,
trte2,trpx2,trpy2,trpz2,charge1,charge2, // bhabha radiation
kVarNum};


void
InclusiveProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here
   HINtupleVarNames ntupleNames(kVarNum);

   ntupleNames.addVar(nt,          "nt");

   ntupleNames.addVar(e1,          "e1");
   ntupleNames.addVar(th1,        "th1");
   ntupleNames.addVar(phi1,       "phi1");
   ntupleNames.addVar(e9251,    "e9251");
   ntupleNames.addVar(d1,          "d1");

   ntupleNames.addVar(e2,          "e2");
   ntupleNames.addVar(th2,        "th2");
   ntupleNames.addVar(phi2,       "phi2");
   ntupleNames.addVar(e9252,    "e9252");
   ntupleNames.addVar(d2,          "d2");

   ntupleNames.addVar(e3,          "e3");
   ntupleNames.addVar(th3,        "th3");
   ntupleNames.addVar(phi3,       "phi3");
   ntupleNames.addVar(e9253,    "e9253");
   ntupleNames.addVar(d3,          "d3");

   ntupleNames.addVar(e4,          "e4");
   ntupleNames.addVar(th4,        "th4");
   ntupleNames.addVar(phi4,       "phi4");
   ntupleNames.addVar(e9254,    "e9254");
   ntupleNames.addVar(d4,          "d4");

   ntupleNames.addVar(e5,          "e5");
   ntupleNames.addVar(th5,        "th5");
   ntupleNames.addVar(phi5,       "phi5");
   ntupleNames.addVar(e9255,    "e9255");
   ntupleNames.addVar(d5,          "d5");

   ntupleNames.addVar(e6,          "e6");
   ntupleNames.addVar(th6,        "th6");
   ntupleNames.addVar(phi6,       "phi6");
   ntupleNames.addVar(e9256,    "e9256");
   ntupleNames.addVar(d6,          "d6");

   ntupleNames.addVar(e7,          "e7");
   ntupleNames.addVar(th7,        "th7");
   ntupleNames.addVar(phi7,       "phi7");
   ntupleNames.addVar(e9257,    "e9257");
   ntupleNames.addVar(d7,          "d7");

   ntupleNames.addVar(e8,          "e8");
   ntupleNames.addVar(th8,        "th8");
   ntupleNames.addVar(phi8,       "phi8");
   ntupleNames.addVar(e9258,    "e9258");
   ntupleNames.addVar(d8,          "d8");

   ntupleNames.addVar(e9,          "e9");
   ntupleNames.addVar(th9,        "th9");
   ntupleNames.addVar(phi9,       "phi9");
   ntupleNames.addVar(e9259,    "e9259");
   ntupleNames.addVar(d9,          "d9");

   ntupleNames.addVar(e10,          "e10");
   ntupleNames.addVar(th10,        "th10");
   ntupleNames.addVar(phi10,       "phi10");
   ntupleNames.addVar(e92510,    "e92510");
   ntupleNames.addVar(d10,          "d10");

   ntupleNames.addVar(e11,          "e11");
   ntupleNames.addVar(th11,        "th11");
   ntupleNames.addVar(phi11,       "phi11");
   ntupleNames.addVar(e92511,    "e92511");
   ntupleNames.addVar(d11,          "d11");

   ntupleNames.addVar(e12,          "e12");
   ntupleNames.addVar(th12,        "th12");
   ntupleNames.addVar(phi12,       "phi12");
   ntupleNames.addVar(e92512,    "e92512");
   ntupleNames.addVar(d12,          "d12");

   ntupleNames.addVar(e13,          "e13");
   ntupleNames.addVar(th13,        "th13");
   ntupleNames.addVar(phi13,       "phi13");
   ntupleNames.addVar(e92513,    "e92513");
   ntupleNames.addVar(d13,          "d13");

   ntupleNames.addVar(e14,          "e14");
   ntupleNames.addVar(th14,        "th14");
   ntupleNames.addVar(phi14,       "phi14");
   ntupleNames.addVar(e92514,    "e92514");
   ntupleNames.addVar(d14,          "d14");

   ntupleNames.addVar(e15,          "e15");
   ntupleNames.addVar(th15,        "th15");
   ntupleNames.addVar(phi15,       "phi15");
   ntupleNames.addVar(e92515,    "e92515");
   ntupleNames.addVar(d15,          "d15");

   ntupleNames.addVar(e16,          "e16");
   ntupleNames.addVar(th16,        "th16");
   ntupleNames.addVar(phi16,       "phi16");
   ntupleNames.addVar(e92516,    "e92516");
   ntupleNames.addVar(d16,          "d16");

   ntupleNames.addVar(eop1,         "eop1");
   ntupleNames.addVar(eop2,         "eop2");
   ntupleNames.addVar(trte1,        "trte1");
   ntupleNames.addVar(trpx1,        "trpx1");
   ntupleNames.addVar(trpy1,        "trpy1");
   ntupleNames.addVar(trpz1,        "trpz1");
   ntupleNames.addVar(trte2,        "trte2");
   ntupleNames.addVar(trpx2,        "trpx2");
   ntupleNames.addVar(trpy2,        "trpy2");
   ntupleNames.addVar(trpz2,        "trpz2");
   ntupleNames.addVar(charge1,      "charge1");
   ntupleNames.addVar(charge2,      "charge2");


   m_showerTuple = iHistoManager.ntuple(10,"tuple", kVarNum, 10000, ntupleNames.names());


}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
InclusiveProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   const int kMaxShower = 16;
   const int kMaxTrack = 2;
   int Nt = -1;
   double E[kMaxShower] = {-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.};
   double Theta[kMaxShower] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
   double Phi[kMaxShower] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
   double E925[kMaxShower] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
   double Distance[kMaxShower] = {-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.};

   double EOP[kMaxTrack] = {0.,0.};
   double PE[kMaxTrack] = {-100.,-100.};
   double PX[kMaxTrack] = {0.,0.};
   double PY[kMaxTrack] = {0.,0.};
   double PZ[kMaxTrack] = {0.,0.};

   int CHARGE[kMaxTrack] = {-100,-100};


   float tuple[kVarNum];
/////////////////////////////////////////// showers //////////////////////////////////////////////////////

   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ) , showerTable, "GoodThings" );

   FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
   FATable< NavShower >::const_iterator showerEnd = showerTable.end();

   int unmatchedShowers = 0;

   for ( FATable< NavShower >::const_iterator showerItr = showerBegin;
         showerItr != showerEnd ;
         ++showerItr )
   {
      const DABoolean unMatched( showerItr->noTrackMatch()  ) ;
      int j = unmatchedShowers++;

      if(j<kMaxShower && unMatched){

        E[j] = showerItr->attributes().energy();
        Theta[j] = showerItr->attributes().theta();
        Phi[j] = showerItr->attributes().phi();
        E925[j] = showerItr->attributes().x925();
        if(!showerItr->nearestMatchedShowers().empty()) 
           Distance[j] = showerItr->distance(*showerItr->nearestMatchedShowers().front() );

      }
   }

//////////////////////////////////// Bhabha radiation  /////////////////////////////////


   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable, "GoodThings" );

   FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();

   Nt = trackTable.size();
   if(trackTable.size() == kMaxTrack)  {

   int unmatchedtracks = 0;

   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;
         ++trackItr )
   {
      int i = unmatchedtracks++;
      CHARGE[i]=(*trackItr).electronFit()->charge();
      PE[i]=(*trackItr).electronFit()->energy();
      PX[i]=(*trackItr).electronFit()->px();
      PY[i]=(*trackItr).electronFit()->py();
      PZ[i]=(*trackItr).electronFit()->pz();
      EOP[i] = trackItr->elecId().eOverP();
   }
   }

   tuple[nt] = Nt;

   tuple[e1] = E[0];
   tuple[th1] = Theta[0];
   tuple[phi1] = Phi[0];
   tuple[e9251] = E925[0];
   tuple[d1] = Distance[0];

   tuple[e2] = E[1];
   tuple[th2] = Theta[1];
   tuple[phi2] = Phi[1];
   tuple[e9252] = E925[1];
   tuple[d2] = Distance[1];

   tuple[e3] = E[2];
   tuple[th3] = Theta[2];
   tuple[phi3] = Phi[2];
   tuple[e9253] = E925[2];
   tuple[d3] = Distance[2];

   tuple[e4] = E[3];
   tuple[th4] = Theta[3];
   tuple[phi4] = Phi[3];
   tuple[e9254] = E925[3];
   tuple[d4] = Distance[3];

   tuple[e5] = E[4];
   tuple[th5] = Theta[4];
   tuple[phi5] = Phi[4];
   tuple[e9255] = E925[4];
   tuple[d5] = Distance[4];

   tuple[e6] = E[5];
   tuple[th6] = Theta[5];
   tuple[phi6] = Phi[5];
   tuple[e9256] = E925[5];
   tuple[d6] = Distance[5];

   tuple[e7] = E[6];
   tuple[th7] = Theta[6];
   tuple[phi7] = Phi[6];
   tuple[e9257] = E925[6];
   tuple[d7] = Distance[6];

   tuple[e8] = E[7];
   tuple[th8] = Theta[7];
   tuple[phi8] = Phi[7];
   tuple[e9258] = E925[7];
   tuple[d8] = Distance[7];

   tuple[e9] = E[8];
   tuple[th9] = Theta[8];
   tuple[phi9] = Phi[8];
   tuple[e9259] = E925[8];
   tuple[d9] = Distance[8];

   tuple[e10] = E[9];
   tuple[th10] = Theta[9];
   tuple[phi10] = Phi[9];
   tuple[e92510] = E925[9];
   tuple[d10] = Distance[9];

   tuple[e11] = E[10];
   tuple[th11] = Theta[10];
   tuple[phi11] = Phi[10];
   tuple[e92511] = E925[10];
   tuple[d11] = Distance[10];

   tuple[e12] = E[11];
   tuple[th12] = Theta[11];
   tuple[phi12] = Phi[11];
   tuple[e92512] = E925[11];
   tuple[d12] = Distance[11];

   tuple[e13] = E[12];
   tuple[th13] = Theta[12];
   tuple[phi13] = Phi[12];
   tuple[e92513] = E925[12];
   tuple[d13] = Distance[12];

   tuple[e14] = E[13];
   tuple[th14] = Theta[13];
   tuple[phi14] = Phi[13];
   tuple[e92514] = E925[13];
   tuple[d14] = Distance[13];

   tuple[e15] = E[14];
   tuple[th15] = Theta[14];
   tuple[phi15] = Phi[14];
   tuple[e92515] = E925[14];
   tuple[d15] = Distance[14];

   tuple[e16] = E[15];
   tuple[th16] = Theta[15];
   tuple[phi16] = Phi[15];
   tuple[e92516] = E925[15];
   tuple[d16] = Distance[15];

   tuple[eop1] = EOP[0];
   tuple[eop2] = EOP[1];
   tuple[trte1] = PE[0];
   tuple[trpx1] = PX[0];
   tuple[trpy1] = PY[0];
   tuple[trpz1] = PZ[0];
   tuple[trte2] = PE[1];
   tuple[trpx2] = PX[1];
   tuple[trpy2] = PY[1];
   tuple[trpz2] = PZ[1];
   tuple[charge1] = CHARGE[0];
   tuple[charge2] = CHARGE[1];


   (*m_showerTuple).fill(tuple);




   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
InclusiveProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
InclusiveProc::endRun( Frame& iFrame )         // anal4 equiv.
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
