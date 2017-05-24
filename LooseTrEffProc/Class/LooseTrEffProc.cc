// -*- C++ -*-
//
// Package:     LooseTrEffProc
// Module:      LooseTrEffProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      pts/1
// Created:     Wed May 12 17:15:38 CDT 2010
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "LooseTrEffProc/LooseTrEffProc.h"
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
static const char* const kFacilityString = "Processor.LooseTrEffProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
LooseTrEffProc::LooseTrEffProc( void )               // anal1
   : Processor( "LooseTrEffProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &LooseTrEffProc::event,    Stream::kEvent );
   bind( &LooseTrEffProc::beginRun, Stream::kBeginRun );
   //bind( &LooseTrEffProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

LooseTrEffProc::~LooseTrEffProc()                    // anal5
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
LooseTrEffProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
LooseTrEffProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------

enum {
e,th,phi,e925, // ISR shower
n1track, n2track, // 1 or 2 tracks
n1tag,n1tag1,n1tag2, // only 1 tagged track
n2tag, n2probe1, n2probe2, // 2 tagged tracks
pite0,pipx0,pipy0,pipz0, // the first track to be found
pite1,pipx1,pipy1,pipz1, // the second track to be calculated
pite2,pipx2,pipy2,pipz2, // the second track to be found
pite3,pipx3,pipy3,pipz3, // the first track to be calculated
pisigma1,pisigma2,ksigma1,ksigma2,// pid
costh1,costh2,  // the angle between the calculated and probed tracks
eop1,eop2,  // E/p
chisqvtx0,chisqfit0, // missing energy fit, 1 track only
chisqvtx1,chisqfit1, // missing energy fit, first track in 2 tracks events
chisqvtx2,chisqfit2, // missing energy fit, second track in 2 tracks events
kVarNum};

void
LooseTrEffProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   HINtupleVarNames ntupleNames(kVarNum);

   ntupleNames.addVar(e,          "e");
   ntupleNames.addVar(th,        "th");
   ntupleNames.addVar(phi,       "phi");
   ntupleNames.addVar(e925,     "e925");

   ntupleNames.addVar(n1track,     "n1track");
   ntupleNames.addVar(n2track,     "n2track");

   ntupleNames.addVar(n1tag,     "n1tag");
   ntupleNames.addVar(n1tag1,     "n1tag1");
   ntupleNames.addVar(n1tag2,     "n1tag2");
   ntupleNames.addVar(n2tag,     "n2tag");
   ntupleNames.addVar(n2probe1,   "n2probe1");
   ntupleNames.addVar(n2probe2,   "n2probe2");

   ntupleNames.addVar(pite0,    "pite0");
   ntupleNames.addVar(pipx0,    "pipx0");
   ntupleNames.addVar(pipy0,    "pipy0");
   ntupleNames.addVar(pipz0,    "pipz0");
   ntupleNames.addVar(pite1,    "pite1");
   ntupleNames.addVar(pipx1,    "pipx1");
   ntupleNames.addVar(pipy1,    "pipy1");
   ntupleNames.addVar(pipz1,    "pipz1");
   ntupleNames.addVar(pite2,    "pite2");
   ntupleNames.addVar(pipx2,    "pipx2");
   ntupleNames.addVar(pipy2,    "pipy2");
   ntupleNames.addVar(pipz2,    "pipz2");
   ntupleNames.addVar(pite3,    "pite3");
   ntupleNames.addVar(pipx3,    "pipx3");
   ntupleNames.addVar(pipy3,    "pipy3");
   ntupleNames.addVar(pipz3,    "pipz3");

   ntupleNames.addVar(pisigma1, "pisigma1");
   ntupleNames.addVar(pisigma2, "pisigma2");
   ntupleNames.addVar(ksigma1, "ksigma1");
   ntupleNames.addVar(ksigma2, "ksigma2");


   ntupleNames.addVar(costh1,   "costh1");
   ntupleNames.addVar(costh2,   "costh2");

   ntupleNames.addVar(eop1,          "eop1");
   ntupleNames.addVar(eop2,          "eop2");

   ntupleNames.addVar(chisqvtx0,          "chisqvtx0");
   ntupleNames.addVar(chisqfit0,          "chisqfit0");
   ntupleNames.addVar(chisqvtx1,          "chisqvtx1");
   ntupleNames.addVar(chisqfit1,          "chisqfit1");
   ntupleNames.addVar(chisqvtx2,          "chisqvtx2");
   ntupleNames.addVar(chisqfit2,          "chisqfit2");


   m_showerTuple = iHistoManager.ntuple(10,"tuple", kVarNum, 10000, ntupleNames.names());
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
LooseTrEffProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   double E = -1000.;
   double Theta = 0.;
   double Phi = 0.;
   double E925 = 0.;

   bool N1TRACK = 0;
   bool N2TRACK = 0;
   bool N1TAG = 0;
   bool N1TAG1 = 0;
   bool N1TAG2 = 0;

   bool N2TAG = 0;
   bool N2PROBE1 = 0;
   bool N2PROBE2 = 0;

   double PIPE0 = -1000.;
   double PIPX0 = -1000.;
   double PIPY0 = -1000.;
   double PIPZ0 = -1000.;
   double PIPE1 = -1000.;
   double PIPX1 = -1000.;
   double PIPY1 = -1000.;
   double PIPZ1 = -1000.;
   double PIPE2 = -1000.;
   double PIPX2 = -1000.;
   double PIPY2 = -1000.;
   double PIPZ2 = -1000.;
   double PIPE3 = -1000.;
   double PIPX3 = -1000.;
   double PIPY3 = -1000.;
   double PIPZ3 = -1000.;

   double LABPE = -1000.;
   double LABPX = -1000.;
   double LABPY = -1000.;
   double LABPZ = -1000.;

   double CHARGE0 = 0.;
   double CHARGE1 = 0.;
   double CHARGE2 = 0.;
   double CHARGE3 = 0.;

   double PISIGMA1 = -1000.;
   double PISIGMA2 = -1000.;
   double KSIGMA1 = -1000.;
   double KSIGMA2 = -1000.;


   double COSTH1 = 0.;
   double COSTH2 = 0.;

   double EOP1 = 0.;
   double EOP2 = 0.;

   double CHISQVTX0 = 1000.;
   double CHISQFIT0 = 1000.;
   double CHISQVTX1 = 1000.;
   double CHISQFIT1 = 1000.;
   double CHISQVTX2 = 1000.;
   double CHISQFIT2 = 1000.;


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

   // Extract total 4-momentum to get CM energy
   FAItem< LabNet4Momentum > labMomentum ;
   extract( iFrame.record( Stream::kStartRun ), labMomentum ) ;

   LABPE= (*labMomentum).e();
   LABPX= (*labMomentum).px();
   LABPY= (*labMomentum).py();
   LABPZ= (*labMomentum).pz();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable, "GoodThings"  );

   if( trackTable.size() == 0)
      return ActionBase::kFailed;

   FATable< NavTrack >::const_iterator trackBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackEnd = trackTable.end();

   FAItem<TDKinematicFit> pi1 = (*trackBegin).pionFit();
   FAItem<DedxInfo> the_dedx1 = (*trackBegin).dedxInfo();


   if( trackTable.size() == 1){
     N1TRACK = 1;

     if(pi1.valid()){
       PIPE0=pi1->lorentzMomentum().e();
       PIPX0=pi1->px();
       PIPY0=pi1->py();
       PIPZ0=pi1->pz();
       CHARGE0=pi1->charge();
       EOP1 = trackBegin->elecId().eOverP();
       if(the_dedx1.valid() )  {
         PISIGMA1=the_dedx1->piSigma();
         KSIGMA1=the_dedx1->kSigma();
       }


        FitEvt pipi( "Pipi", FitEvt::k_MissingMass,0,0.13957018 );
        pipi.newPhoton(*showerBegin);
        pipi.newTrack(*pi1);
        pipi.doTheFit();

        if( (pipi.chisqVtx()>0) && (pipi.chisqFit()>0) && (pipi.chisqVtx()<15) && (pipi.chisqFit()<4)) {
           N1TAG = 1;
           CHISQVTX0 = pipi.chisqVtx();
           CHISQFIT0 = pipi.chisqFit();
           PIPE1 = LABPE - PIPE0 - E;
           PIPX1 = LABPX - PIPX0 - E*sin(Theta)*cos(Phi);
           PIPY1 = LABPY - PIPY0 - E*sin(Theta)*sin(Phi);
           PIPZ1 = LABPZ - PIPZ0 - E*cos(Theta);
           CHARGE1 = -CHARGE0;
        }
     }
   }

   if( trackTable.size() == 2){
     N2TRACK = 1;
     FAItem<TDKinematicFit> pi2 = (*(trackBegin+1)).pionFit();
     FAItem<DedxInfo> the_dedx2 = (*(trackBegin+1)).dedxInfo();

     if(pi1.valid()){

        PIPE0=pi1->lorentzMomentum().e();
        PIPX0=pi1->px();
        PIPY0=pi1->py();
        PIPZ0=pi1->pz();
        CHARGE0=pi1->charge();
        EOP1 = trackBegin->elecId().eOverP();
        if(the_dedx1.valid() )  {
          PISIGMA1=the_dedx1->piSigma();
          KSIGMA1=the_dedx1->kSigma();
        }


        FitEvt pipi1( "Pipi1", FitEvt::k_MissingMass,0,0.13957018 );
        pipi1.newPhoton(*showerBegin);
        pipi1.newTrack(*pi1);
        pipi1.doTheFit();

        if( (pipi1.chisqVtx()>0) && (pipi1.chisqFit()>0) && (pipi1.chisqVtx()<15) && (pipi1.chisqFit()<4)) {
           N1TAG1 = 1;
           CHISQVTX1 = pipi1.chisqVtx();
           CHISQFIT1 = pipi1.chisqFit();
           PIPE1 = LABPE - PIPE0 - E;
           PIPX1 = LABPX - PIPX0 - E*sin(Theta)*cos(Phi);
           PIPY1 = LABPY - PIPY0 - E*sin(Theta)*sin(Phi);
           PIPZ1 = LABPZ - PIPZ0 - E*cos(Theta);
           CHARGE1 = -CHARGE0;
        }
     }

     if(pi2.valid()){

        PIPE2 = pi2->lorentzMomentum().e();
        PIPX2=pi2->px();
        PIPY2=pi2->py();
        PIPZ2=pi2->pz();
        CHARGE2 = pi2->charge();
        EOP2 = (trackBegin+1)->elecId().eOverP();
        if(the_dedx2.valid() )  {
          PISIGMA2=the_dedx2->piSigma();
          KSIGMA2=the_dedx2->kSigma();
        }

        FitEvt pipi2( "Pipi2", FitEvt::k_MissingMass,0,0.13957018 );
        pipi2.newPhoton(*showerBegin);
        pipi2.newTrack(*pi2);
        pipi2.doTheFit();

        if( (pipi2.chisqVtx()>0) && (pipi2.chisqFit()>0) && (pipi2.chisqVtx()<15) && (pipi2.chisqFit()<4)) {
           N1TAG2 = 1;
           CHISQVTX2 = pipi2.chisqVtx();
           CHISQFIT2 = pipi2.chisqFit();
           PIPE3 = LABPE - PIPE2 - E;
           PIPX3 = LABPX - PIPX2 - E*sin(Theta)*cos(Phi);
           PIPY3 = LABPY - PIPY2 - E*sin(Theta)*sin(Phi);
           PIPZ3 = LABPZ - PIPZ2 - E*cos(Theta);
           CHARGE3 = -CHARGE2;
        }
     }

     if(N1TAG1 && N1TAG2) {
        N2TAG = 1;
        COSTH1 = (PIPX1*PIPX2+PIPY1*PIPY2+PIPZ1*PIPZ2)/(sqrt(pow(PIPX1,2)+pow(PIPY1,2)+pow(PIPZ1,2))*sqrt(pow(PIPX2,2)+pow(PIPY2,2)+pow(PIPZ2,2)));
        if((COSTH1 > 0.8) && (CHARGE1 == CHARGE2))
          N2PROBE1 = 1;
        COSTH2 = (PIPX3*PIPX0+PIPY3*PIPY0+PIPZ3*PIPZ0)/(sqrt(pow(PIPX3,2)+pow(PIPY3,2)+pow(PIPZ3,2))*sqrt(pow(PIPX0,2)+pow(PIPY0,2)+pow(PIPZ0,2)));
        if((COSTH2 > 0.8) && (CHARGE3 == CHARGE0))
          N2PROBE2 = 1;
     }
   }





   tuple[e] = E;
   tuple[th] = Theta;
   tuple[phi] = Phi;
   tuple[e925] = E925;
   tuple[n1track] = N1TRACK;
   tuple[n2track] = N2TRACK;
   tuple[n1tag] = N1TAG;
   tuple[n1tag1] = N1TAG1;
   tuple[n1tag2] = N1TAG2;
   tuple[n2tag] = N2TAG;
   tuple[n2probe1] = N2PROBE1;
   tuple[n2probe2] = N2PROBE2;

   tuple[pite0] = PIPE0;
   tuple[pipx0] = PIPX0;
   tuple[pipy0] = PIPY0;
   tuple[pipz0] = PIPZ0;
   tuple[pite1] = PIPE1;
   tuple[pipx1] = PIPX1;
   tuple[pipy1] = PIPY1;
   tuple[pipz1] = PIPZ1;
   tuple[pite2] = PIPE2;
   tuple[pipx2] = PIPX2;
   tuple[pipy2] = PIPY2;
   tuple[pipz2] = PIPZ2;
   tuple[pite3] = PIPE3;
   tuple[pipx3] = PIPX3;
   tuple[pipy3] = PIPY3;
   tuple[pipz3] = PIPZ3;

   tuple[pisigma1] = PISIGMA1;
   tuple[pisigma2] = PISIGMA2;
   tuple[ksigma1] = KSIGMA1;
   tuple[ksigma2] = KSIGMA2;

   tuple[costh1] = COSTH1;
   tuple[costh2] = COSTH2;
   tuple[eop1] = EOP1;
   tuple[eop2] = EOP2;

   tuple[chisqvtx0] = CHISQVTX0;
   tuple[chisqfit0] = CHISQFIT0;
   tuple[chisqvtx1] = CHISQVTX1;
   tuple[chisqfit1] = CHISQFIT1;
   tuple[chisqvtx2] = CHISQVTX2;
   tuple[chisqfit2] = CHISQFIT2;


   (*m_showerTuple).fill(tuple);

   return ActionBase::kPassed;
}


ActionBase::ActionResult
LooseTrEffProc::beginRun( Frame& iFrame )       // anal2 equiv.
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
LooseTrEffProc::endRun( Frame& iFrame )         // anal4 equiv.
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
