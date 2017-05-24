// -*- C++ -*-
//
// Package:     MissingMassProc
// Module:      MissingMassProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      pts/1
// Created:     Mon May 24 14:13:49 CDT 2010
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "MissingMassProc/MissingMassProc.h"
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

#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
#include "Navigation/NavShowerServer.h"
#include "C3ccProd/CcFortranShowerCorrector.h"

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

#include "LabNet4Momentum/LabNet4Momentum.h"

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
static const char* const kFacilityString = "Processor.MissingMassProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
MissingMassProc::MissingMassProc( void )               // anal1
   : Processor( "MissingMassProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &MissingMassProc::event,    Stream::kEvent );
   bind( &MissingMassProc::beginRun, Stream::kBeginRun );
   //bind( &MissingMassProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

MissingMassProc::~MissingMassProc()                    // anal5
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
MissingMassProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
MissingMassProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------

enum {
e,th,phi,e925, // ISR shower
chisqv11,
chisqf11,
chisqv21,chisqv22,
chisqf21,chisqf22,
chisqf31,chisqf32,chisqf33,
chisqf41,chisqf42,chisqf43,chisqf44,
eop11,
eop21,eop22,
eop31,eop32,eop33,
eop41,eop42,eop43,eop44,
kVarNum};


void
MissingMassProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here


   HINtupleVarNames ntupleNames(kVarNum);

   ntupleNames.addVar(e,          "e");
   ntupleNames.addVar(th,        "th");
   ntupleNames.addVar(phi,       "phi");
   ntupleNames.addVar(e925,     "e925");

   ntupleNames.addVar(chisqf11,   "chisqf11");
   ntupleNames.addVar(chisqf21,   "chisqf21");
   ntupleNames.addVar(chisqf31,   "chisqf31");
   ntupleNames.addVar(chisqf41,   "chisqf41");
   ntupleNames.addVar(chisqf22,   "chisqf22");
   ntupleNames.addVar(chisqf32,   "chisqf32");
   ntupleNames.addVar(chisqf42,   "chisqf42");
   ntupleNames.addVar(chisqf33,   "chisqf33");
   ntupleNames.addVar(chisqf43,   "chisqf43");
   ntupleNames.addVar(chisqf44,   "chisqf44");

   ntupleNames.addVar(chisqv11,   "chisqv11");
   ntupleNames.addVar(chisqv21,   "chisqv21");
   ntupleNames.addVar(chisqv22,   "chisqv22");


   ntupleNames.addVar(eop11,      "eop11");
   ntupleNames.addVar(eop21,      "eop21");
   ntupleNames.addVar(eop31,      "eop31");
   ntupleNames.addVar(eop41,      "eop41");
   ntupleNames.addVar(eop22,      "eop22");
   ntupleNames.addVar(eop32,      "eop32");
   ntupleNames.addVar(eop42,      "eop42");
   ntupleNames.addVar(eop33,      "eop33");
   ntupleNames.addVar(eop43,      "eop43");
   ntupleNames.addVar(eop44,      "eop44");

   m_showerTuple = iHistoManager.ntuple(10,"tuple", kVarNum, 10000, ntupleNames.names());

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
MissingMassProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   double E = -1000.;
   double Theta = 0.;
   double Phi = 0.;
   double E925 = 0.;

   double EOP1 = 0.;
   double EOP2[2] = {0.,0.};
   double EOP3[3] = {0.,0.,0.};
   double EOP4[4] = {0.,0.,0.,0.};
 
   double ChisqF1 = 1000000.;
   double ChisqF2[2] = {1000000.,1000000.};
   double ChisqF3[3] = {1000000.,1000000.,1000000.};
   double ChisqF4[4] = {1000000.,1000000.,1000000.,1000000.};

   double ChisqV1 = 1000000.;
   double ChisqV2[2] = {1000000.,1000000.};

   float tuple[kVarNum];

// if we're in MC, check to see if the trigger fired
   FAItem< DBEventHeader > eventHeader ;
   extract( iFrame.record( Stream::kEvent ), eventHeader ) ;

   double the_run = eventHeader->run();
   double the_evt = eventHeader->number();

   if( eventHeader->monteCarlo() ) {
      double L1Trigger = 0., L4Decision = 0.;

////////////////////////////////////////////////////////////////////////////
// Trigger L1
////////////////////////////////////////////////////////////////////////////
//   int l1Trigger = 0, l1Trigger_Sel = 0, l1Trigger_Hadron = 0;
//   int l1Trigger_MuPair = 0, l1Trigger_ElTrack = 0, l1Trigger_RadTau = 0;
//   int l1Trigger_TwoTrack = 0;

      FAItem< TriggerL1Data > trigDat;
      extract (iFrame.record(Stream::kEvent), trigDat);

// All possible trigger lines
// --------------------------
// DABoolean isHadron() const;  //Ax track > 2 & CB lo > 0
// DABoolean isMuPair() const;  //Hi track > 1 & Back-to-back, 1 vs. 3/24
// DABoolean isElTrack() const;  //Ax track > 0 & CB med > 0
// DABoolean isRadTau() const;  //Stereo (hi + low) track > 1 & CB lo > 0
// DABoolean isBarrelBhabha() const; //Back-to-back Hi CB clusters

// DABoolean isCBSingleHi() const;  //CB hi > 0
// DABoolean isCESingleHi() const;  //CE hi > 0
// DABoolean isEndcapBhabha() const; //CE hi clusters in opposite ends
// DABoolean isTwoTrack() const; //Ax track > 1
// DABoolean isPulser() const;  //Pulser trigger
// DABoolean isRandom() const;  //Random trigger
// DABoolean isMinBias() const; //Tracking or CB Timing bit (Ax>0 || CB lo>1)
      // Decode trigger line information //

      // L1 Accept if any trigger line fires
      if(trigDat->isHadron()) L1Trigger = 1.;
      if(trigDat->isRadTau()) L1Trigger = 2.;
      if(trigDat->isElTrack()) L1Trigger = 3.;
      if(trigDat->isBarrelBhabha()) L1Trigger = 4.;
      if(trigDat->isEndcapBhabha()) L1Trigger = 5.;
      if(trigDat->isMuPair()) L1Trigger = 6.;
      if(trigDat->isCBSingleHi()) L1Trigger = 7.;
      if(trigDat->isCESingleHi()) L1Trigger = 8.;
      if(trigDat->isPulser()) L1Trigger = 9.;
      if(trigDat->isRandom()) L1Trigger = 10.;
      if(trigDat->isTwoTrack()) L1Trigger = 11.;
      if(trigDat->isMinBias()) L1Trigger = 12.;
      if(trigDat->isPhotonA()) L1Trigger = 13.;
      if(trigDat->isPhotonB()) L1Trigger = 14.;
      if(trigDat->isPhotonC()) L1Trigger = 15.;
      if(trigDat->isPhotonD()) L1Trigger = 16.;
      // L1 Accept if any non-prescaled trigger line fires
//   if ( (trigDat->isHadron())       ||
//      (trigDat->isMuPair())       ||
//      (trigDat->isElTrack())      ||
//      (trigDat->isRadTau())       ||
//      (trigDat->isBarrelBhabha())  )
//   { l1Trigger_Sel = 1; }

////////////////////////////////////////////////////////////////////////////
// Software Trigger (L3 & L4)
////////////////////////////////////////////////////////////////////////////
      FAItem<Level4Decision > decision;
      extract(iFrame.record(Stream::kEvent), decision );

      switch( decision->decision() )
      {
         case Level4Decision::kKeepLevel3Garbage :
         {
            L4Decision = 1.;
            break;
         }
         case Level4Decision::kLevel3AutoAccept :
         {
            L4Decision = 2.;
            break;
         }
         case Level4Decision::kLevel4Keep :
         {
            L4Decision = 3.;
            break;
         }
      }

      if( (!L1Trigger) || (!L4Decision) )
         return ActionBase::kFailed;
   }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ) , showerTable, "GoodThings" );

   if(showerTable.size()==0)
      return ActionBase::kFailed;

   FATable< NavShower >::const_iterator showerBegin = showerTable.begin();

   E = showerBegin->attributes().energy();
   Theta = showerBegin->attributes().theta();
   Phi = showerBegin->attributes().phi();
   E925 = showerBegin->attributes().x925();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable, "GoodThings"  );

   if( trackTable.size() == 0)
      return ActionBase::kFailed;

   FATable< NavTrack >::const_iterator trackBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackEnd = trackTable.end();

   int unmatchedTracks = 0;

   for ( FATable< NavTrack >::const_iterator trackItr = trackBegin;
         trackItr != trackEnd ;
         ++trackItr )
     {
         FAItem<TDKinematicFit> pionFit = (*trackItr).pionFit();

         if(pionFit.valid()){

           FitEvt pipi( "Pipi", FitEvt::k_MissingMass,0,0.13957018 );
           pipi.newPhoton(*showerBegin);
           pipi.newTrack(*pionFit);
           pipi.doTheFit();

           if( (pipi.chisqVtx()>0) && (pipi.chisqFit()>0) ) {

              if( trackTable.size() == 1){
                ChisqF1 = pipi.chisqFit();                
                ChisqV1 = pipi.chisqVtx();
                EOP1 = trackItr->elecId().eOverP();
               
              }             

              if(trackTable.size() == 2){
                int j = unmatchedTracks++;
                ChisqF2[j] = pipi.chisqFit();
                ChisqV2[j] = pipi.chisqVtx();
                EOP2[j] = trackItr->elecId().eOverP();
              }

              if(trackTable.size() == 3){
                int j = unmatchedTracks++;
                ChisqF3[j] = pipi.chisqFit();
                EOP3[j] = trackItr->elecId().eOverP();
              }

              if(trackTable.size() == 4){
                int j = unmatchedTracks++;
                ChisqF4[j] = pipi.chisqFit();
                EOP4[j] = trackItr->elecId().eOverP();
              }
           }
         }
     }

   tuple[e] = E;
   tuple[th] = Theta;
   tuple[phi] = Phi;
   tuple[e925] = E925;

   tuple[chisqf11] = ChisqF1;
   tuple[chisqf21] = ChisqF2[0];
   tuple[chisqf22] = ChisqF2[1];
   tuple[chisqf31] = ChisqF3[0];
   tuple[chisqf32] = ChisqF3[1];
   tuple[chisqf33] = ChisqF3[2];
   tuple[chisqf41] = ChisqF4[0];
   tuple[chisqf42] = ChisqF4[1];
   tuple[chisqf43] = ChisqF4[2];
   tuple[chisqf44] = ChisqF4[3];

   tuple[chisqv11] = ChisqV1;
   tuple[chisqv21] = ChisqV2[0];
   tuple[chisqv22] = ChisqV2[1];


   tuple[eop11] = EOP1;
   tuple[eop21] = EOP2[0];
   tuple[eop22] = EOP2[1];
   tuple[eop31] = EOP3[0];
   tuple[eop32] = EOP3[1];
   tuple[eop33] = EOP3[2];
   tuple[eop41] = EOP4[0];
   tuple[eop42] = EOP4[1];
   tuple[eop43] = EOP4[2];
   tuple[eop44] = EOP4[3];

   (*m_showerTuple).fill(tuple);


   return ActionBase::kPassed;
}


ActionBase::ActionResult
MissingMassProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;
   FAItem< BeamSpot > spot;
   extract( iFrame.record( Stream::kBeginRun ), spot );

   FAItem< BeamEnergy > beam_energy;
   extract( iFrame.record( Stream::kBeginRun ), beam_energy );

   FAItem< MagneticField > cleoBField;
   extract( iFrame.record( Stream::kBeginRun ), cleoBField );

   FitEvtSettings &settings(FitEvtSettings::instance());
   settings.setField(*cleoBField);
   settings.setBeamSpot(*spot);
   settings.setLorVecCM( beam_energy->value() );
//   settings.setVerbose();

   return ActionBase::kPassed;
}


/*
ActionBase::ActionResult
MissingMassProc::endRun( Frame& iFrame )         // anal4 equiv.
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
