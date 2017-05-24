// -*- C++ -*-
//
// Package:     ISREffProc
// Module:      ISREffProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Tue May  5 15:32:13 CDT 2015
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "ISREffProc/ISREffProc.h"
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
#include "C3Mu/MuTrack.h"
#include "Navigation/NavMuonId.h"

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

#include "MCBeam/MCTrueRfBucket.h"
#include "MCTriggerPhase/MCTriggerPhase.h"

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
static const char* const kFacilityString = "Processor.ISREffProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
ISREffProc::ISREffProc( void )               // anal1
   : Processor( "ISREffProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &ISREffProc::event,    Stream::kEvent );
   bind( &ISREffProc::beginRun, Stream::kBeginRun );
   //bind( &ISREffProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

ISREffProc::~ISREffProc()                    // anal5
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
ISREffProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
ISREffProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------

enum {
knshower, // number of ISR shower (0 or 1)
fknshower,fknshower_pi, // number of expected shower (0 or 1)
knshower10, // number of showers (up to 10)
e1,th1,phi1, e9oe25, x925, // probed ISR photon

e2,th2,phi2,e9252, // other photons, to look for pi0
e3,th3,phi3,e9253,
e4,th4,phi4,e9254,
e5,th5,phi5,e9255,
e6,th6,phi6,e9256,
e7,th7,phi7,e9257,
e8,th8,phi8,e9258,
e9,th9,phi9,e9259,
e10,th10,phi10,e92510,

pisigma1,musigma1,ksigma1,pill1,mull1,kll1, // for rejecting kaons
pisigma2,musigma2,ksigma2,pill2,mull2,kll2,
me1,me2,
mudepth1,mudepth2,
charge1,charge2,

fe1,fth1,fphi1, // reconstructed photon
fe1_pi,fth1_pi,fphi1_pi, // reconstructed photon
trte1,trpx1,trpy1,trpz1,trte2,trpx2,trpy2,trpz2, // electrons
pite1,pipx1,pipy1,pipz1,pite2,pipx2,pipy2,pipz2, // pions
chisqvtx,chisqfit, // 1C fit for electrons
chisqvtx_pi,chisqfit_pi, // 1C fit for pions
eop1,eop2,
kVarNum};


void
ISREffProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   HINtupleVarNames ntupleNames(kVarNum);

   ntupleNames.addVar(knshower,       "knshower");
   ntupleNames.addVar(fknshower,       "fknshower");
   ntupleNames.addVar(fknshower_pi,       "fknshower_pi");
   ntupleNames.addVar(knshower10,       "knshower10");

   ntupleNames.addVar(e1,          "e1");
   ntupleNames.addVar(th1,        "th1");
   ntupleNames.addVar(phi1,	  "phi1");
   ntupleNames.addVar(e9oe25,     "e9oe25"); //  E9/E25
   ntupleNames.addVar(x925,     "x925"); //    scaled E9/E25

   ntupleNames.addVar(e2,          "e2");
   ntupleNames.addVar(th2,        "th2");
   ntupleNames.addVar(phi2,	  "phi2");
   ntupleNames.addVar(e9252,    "e9252");

   ntupleNames.addVar(e3,          "e3");
   ntupleNames.addVar(th3,        "th3");
   ntupleNames.addVar(phi3,       "phi3");
   ntupleNames.addVar(e9253,    "e9253");

   ntupleNames.addVar(e4,          "e4");
   ntupleNames.addVar(th4,        "th4");
   ntupleNames.addVar(phi4,	  "phi4");
   ntupleNames.addVar(e9254,    "e9254");

   ntupleNames.addVar(e5,          "e5");
   ntupleNames.addVar(th5,        "th5");
   ntupleNames.addVar(phi5,       "phi5");
   ntupleNames.addVar(e9255,    "e9255");

   ntupleNames.addVar(e6,          "e6");
   ntupleNames.addVar(th6,        "th6");
   ntupleNames.addVar(phi6,	  "phi6");
   ntupleNames.addVar(e9256,    "e9256");

   ntupleNames.addVar(e7,          "e7");
   ntupleNames.addVar(th7,        "th7");
   ntupleNames.addVar(phi7,       "phi7");
   ntupleNames.addVar(e9257,    "e9257");

   ntupleNames.addVar(e8,          "e8");
   ntupleNames.addVar(th8,        "th8");
   ntupleNames.addVar(phi8,       "phi8");
   ntupleNames.addVar(e9258,    "e9258");

   ntupleNames.addVar(e9,          "e9");
   ntupleNames.addVar(th9,        "th9");
   ntupleNames.addVar(phi9,	  "phi9");
   ntupleNames.addVar(e9259,    "e9259");

   ntupleNames.addVar(e10,          "e10");
   ntupleNames.addVar(th10,        "th10");
   ntupleNames.addVar(phi10,       "phi10");
   ntupleNames.addVar(e92510,    "e92510");

   ntupleNames.addVar(fe1,          "fe1");
   ntupleNames.addVar(fth1,        "fth1");
   ntupleNames.addVar(fphi1,	  "fphi1");

   ntupleNames.addVar(fe1_pi,          "fe1_pi");
   ntupleNames.addVar(fth1_pi,        "fth1_pi");
   ntupleNames.addVar(fphi1_pi,	  "fphi1_pi");

   ntupleNames.addVar(pisigma1, "pisigma1");
   ntupleNames.addVar(musigma1, "musigma1");
   ntupleNames.addVar(ksigma1, "ksigma1");
   ntupleNames.addVar(pill1,    "pill1");
   ntupleNames.addVar(mull1,    "mull1");
   ntupleNames.addVar(kll1,    "kll1");

   ntupleNames.addVar(pisigma2, "pisigma2");
   ntupleNames.addVar(musigma2, "musigma2");
   ntupleNames.addVar(ksigma2, "ksigma2");
   ntupleNames.addVar(pill2,    "pill2");
   ntupleNames.addVar(mull2,    "mull2");
   ntupleNames.addVar(kll2,    "kll2");

   ntupleNames.addVar(trte1,    "trte1");
   ntupleNames.addVar(trpx1,    "trpx1");
   ntupleNames.addVar(trpy1,    "trpy1");
   ntupleNames.addVar(trpz1,    "trpz1");
   ntupleNames.addVar(trte2,    "trte2");
   ntupleNames.addVar(trpx2,    "trpx2");
   ntupleNames.addVar(trpy2,    "trpy2");
   ntupleNames.addVar(trpz2,    "trpz2");

   ntupleNames.addVar(pite1,    "pite1");
   ntupleNames.addVar(pipx1,    "pipx1");
   ntupleNames.addVar(pipy1,    "pipy1");
   ntupleNames.addVar(pipz1,    "pipz1");
   ntupleNames.addVar(pite2,    "pite2");
   ntupleNames.addVar(pipx2,    "pipx2");
   ntupleNames.addVar(pipy2,    "pipy2");
   ntupleNames.addVar(pipz2,    "pipz2");

   ntupleNames.addVar(me1,    "me1");
   ntupleNames.addVar(me2,    "me2");
   ntupleNames.addVar(mudepth1,    "mudepth1");
   ntupleNames.addVar(mudepth2,    "mudepth2");
   ntupleNames.addVar(charge1,    "charge1");
   ntupleNames.addVar(charge2,    "charge2");

   ntupleNames.addVar(chisqvtx,          "chisqvtx");
   ntupleNames.addVar(chisqfit,          "chisqfit");

   ntupleNames.addVar(chisqvtx_pi,          "chisqvtx_pi");
   ntupleNames.addVar(chisqfit_pi,          "chisqfit_pi");

   ntupleNames.addVar(eop1,    "eop1");
   ntupleNames.addVar(eop2,    "eop2");

   m_showerTuple = iHistoManager.ntuple(10,"tuple", kVarNum, 10000, ntupleNames.names());

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
ISREffProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   const int kMaxTrack = 2;
   const int kMaxShower = 10;

   int KNISR = 0;
   int FKNISR = 0;
   int FKNISR_PI = 0;

   double E = -10.;
   double Theta = -10.;
   double Phi = -10.;
   double E9OE25 = -10.;
   double X925 = -10.;

   double FE = -10.;
   double FTheta = -10.;
   double FPhi = -10.;

   double FE_PI = -10.;
   double FTheta_PI = -10.;
   double FPhi_PI = -10.;

   double E10[kMaxShower] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double Theta10[kMaxShower] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double Phi10[kMaxShower] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double E92510[kMaxShower] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};

   double PPISIGMA[kMaxTrack] = {-1000.,-1000.};
   double PMUSIGMA[kMaxTrack] = {-1000.,-1000.};
   double PKSIGMA[kMaxTrack] = {-1000.,-1000.};

   double PPILL[kMaxTrack] = {-1000.,-1000.};
   double PMULL[kMaxTrack] = {-1000.,-1000.};
   double PKLL[kMaxTrack] = {-1000.,-1000.};

   double TRPE[kMaxTrack] = {-1000.,-1000.};
   double TRPX[kMaxTrack] = {-1000.,-1000.};
   double TRPY[kMaxTrack] = {-1000.,-1000.};
   double TRPZ[kMaxTrack] = {-1000.,-1000.};

   double PIPE[kMaxTrack] = {-1000.,-1000.};
   double PIPX[kMaxTrack] = {-1000.,-1000.};
   double PIPY[kMaxTrack] = {-1000.,-1000.};
   double PIPZ[kMaxTrack] = {-1000.,-1000.};

   double ME[kMaxTrack] = {-10.,-10.};
   double MUDEPTH[kMaxTrack] = {0.,0.};
   double CHARGE[kMaxTrack] = {0.,0.};

   double CHISQVTX = 10000000.;
   double CHISQFIT = 10000000.;

   double CHISQVTX_PI = 10000000.;
   double CHISQFIT_PI = 10000000.;

   double LABPE = -1000.;
   double LABPX = -1000.;
   double LABPY = -1000.;
   double LABPZ = -1000.;

   double EOP = -10.;
   double EOP2[kMaxTrack] = {-10.,-10.};

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

      if(trigDat->isHadron()) {
        L1Trigger = 1.;
      }
      if(trigDat->isRadTau()) {
        L1Trigger = 2.;
      }
      if(trigDat->isElTrack()) {
        L1Trigger = 3.;
      }
      if(trigDat->isBarrelBhabha()) {
        L1Trigger = 4.;
      }
      if(trigDat->isEndcapBhabha()) {
        L1Trigger = 5.;
      }
      if(trigDat->isMuPair()) {
        L1Trigger = 6.;
      }
      if(trigDat->isCBSingleHi()) {
        L1Trigger = 7.;
      }
      if(trigDat->isCESingleHi()) {
        L1Trigger = 8.;
      }
      if(trigDat->isPulser()) {
        L1Trigger = 9.;
      }
      if(trigDat->isRandom()) {
        L1Trigger = 10.;
      }
      if(trigDat->isTwoTrack()) {
        L1Trigger = 11.;
      }
      if(trigDat->isMinBias()) {
        L1Trigger = 12.;
      }
      if(trigDat->isPhotonA()) {
        L1Trigger = 13.;
      }
      if(trigDat->isPhotonB()) {
        L1Trigger = 14.;
      }
      if(trigDat->isPhotonC()) {
        L1Trigger = 15.;
      }
      if(trigDat->isPhotonD()) {
        L1Trigger = 16.;
      }

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

   int unmatchedShowers = 0;

   if(showerTable.size()!=0) {

     FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
     FATable< NavShower >::const_iterator showerEnd = showerTable.end();

     FATable< NavShower >::const_iterator fastest_shower = showerBegin;

//     if(fastest_shower->attributes().x925() < 1)
//        return ActionBase::kFailed;
//     if(fastest_shower->attributes().energy() < 0.5)
//        return ActionBase::kFailed;

     E = fastest_shower->attributes().energy();
     Theta = fastest_shower->attributes().theta();
     Phi = fastest_shower->attributes().phi();
     E9OE25 = fastest_shower->attributes().e9oe25();
     X925 = fastest_shower->attributes().x925();
     KNISR++;

     for ( FATable< NavShower >::const_iterator showerItr = showerBegin;
           showerItr != showerEnd ;
           ++showerItr )
     {

        int j = unmatchedShowers++;

        if(j<kMaxShower){

          E10[j] = showerItr->attributes().energy();
          Theta10[j] = showerItr->attributes().theta();
          Phi10[j] = showerItr->attributes().phi();
          E92510[j] = showerItr->attributes().x925();
        }
     }



   }
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

   if( trackTable.size() != 2)
      return ActionBase::kFailed;

   FATable< NavTrack >::const_iterator trackBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackEnd = trackTable.end();

   FAItem<TDKinematicFit> electron1 = (*trackBegin).electronFit();
   FAItem<TDKinematicFit> electron2 = (*(trackBegin+1)).electronFit();

   FAItem<TDKinematicFit> pion1 = (*trackBegin).pionFit();
   FAItem<TDKinematicFit> pion2 = (*(trackBegin+1)).pionFit();

   int j = 0;

   for ( FATable< NavTrack >::const_iterator trackItr = trackBegin;
         trackItr != trackEnd ;
         ++trackItr )
   {

      FAItem<DedxInfo> the_dedx = (*trackItr).dedxInfo();
      FAItem<NavRich> the_rich = (*trackItr).richInfo();
      FAItem<TDKinematicFit> electronFit = (*trackItr).electronFit();
      FAItem<TDKinematicFit> pionFit = (*trackItr).pionFit();
      FAItem<TDKinematicFit> muonFit = (*trackItr).muonFit();
      FAItem<TDKinematicFit> kaonFit = (*trackItr).kaonFit();

      double cos_theta01 = pionFit->pz() / pionFit->pmag();
      double cos_theta02 = muonFit->pz() / muonFit->pmag();
      double cos_theta03 = kaonFit->pz() / kaonFit->pmag();

//      double cos_theta = electronFit->pz() / electronFit->pmag();
//      double pt = sqrt(pow(electronFit->px(),2)+pow(electronFit->py(),2));

//      if((pt<0.16) || (fabs(cos_theta) > 0.75))
//         return ActionBase::kFailed;

//      EOP = trackItr->elecId().eOverP();
//      if(EOP<0.85)
//         return ActionBase::kFailed;

      if(j<kMaxTrack){

        CHARGE[j]=electronFit->charge();

        if(CHARGE[j] == 0)
          return ActionBase::kFailed;

        TRPE[j]=electronFit->lorentzMomentum().e();
        TRPX[j]=electronFit->px();
        TRPY[j]=electronFit->py();
        TRPZ[j]=electronFit->pz();

        PIPE[j]=pionFit->lorentzMomentum().e();
        PIPX[j]=pionFit->px();
        PIPY[j]=pionFit->py();
       	PIPZ[j]=pionFit->pz();

        EOP2[j] = trackItr->elecId().eOverP();

        if(trackItr->trackShowerMatch().valid())
          ME[j] = trackItr->trackShowerMatch()->matchedEnergy();

        MUDEPTH[j] = trackItr->muonId().depth();

        if( (pionFit.valid()) && (the_dedx.valid()) )  {

          PPISIGMA[j]=the_dedx->piSigma();

          if ((the_rich.valid()) && (fabs(cos_theta01) < 0.8) && (the_rich->pionHypWasAnalyzed()))
            PPILL[j]=the_rich->pionLogLikelihood();
        }

        if( (muonFit.valid()) && (the_dedx.valid()) )  {

          PMUSIGMA[j]=the_dedx->muSigma();

          if ((the_rich.valid()) && (fabs(cos_theta02) < 0.8) && (the_rich->muonHypWasAnalyzed()))
            PMULL[j]=the_rich->muonLogLikelihood();
        }

        if( (kaonFit.valid()) && (the_dedx.valid()) )  {

          PKSIGMA[j]=the_dedx->kSigma();

          if ((the_rich.valid()) && (fabs(cos_theta03) < 0.8) && (the_rich->kaonHypWasAnalyzed()))
            PKLL[j]=the_rich->kaonLogLikelihood();
        }

      }
      j++;
   }

   if(CHARGE[0]!=-CHARGE[1])
      return ActionBase::kFailed;

/////////////////////////////////////////////////////////////////////////

   if (electron1.valid() && electron2.valid()) {

      FitEvt ee( "Ee", FitEvt::k_MissingMass,0,0 );
      ee.newTrack(*electron1);
      ee.newTrack(*electron2);
      ee.doTheFit();

      if( (ee.chisqVtx()>0) && (ee.chisqFit()>0) ) {

         CHISQVTX = ee.chisqVtx();
         CHISQFIT = ee.chisqFit();

         FE = LABPE - TRPE[0] - TRPE[1];
         FPhi = atan2((LABPY - TRPY[0] - TRPY[1]),(LABPX - TRPX[0] - TRPX[1]));
         FTheta = acos((LABPZ - TRPZ[0] - TRPZ[1])/FE);

         FKNISR++;
      }
   }

////////////////////////////////////////////////////////////////////////////

   if (pion1.valid() && pion2.valid()) {

      FitEvt pipi( "Pipi", FitEvt::k_MissingMass,0,0 );
      pipi.newTrack(*pion1);
      pipi.newTrack(*pion2);
      pipi.doTheFit();

      if( (pipi.chisqVtx()>0) && (pipi.chisqFit()>0) ) {

         CHISQVTX_PI = pipi.chisqVtx();
         CHISQFIT_PI = pipi.chisqFit();

         FE_PI = LABPE - PIPE[0] - PIPE[1];
         FPhi_PI = atan2((LABPY - PIPY[0] - PIPY[1]),(LABPX - PIPX[0] - PIPX[1]));
         FTheta_PI = acos((LABPZ - PIPZ[0] - PIPZ[1])/FE_PI);

         FKNISR_PI++;
      }
   }

////////////////////////////////////////////////////////////////////////////






   tuple[knshower] = KNISR;
   tuple[fknshower] = FKNISR;
   tuple[fknshower_pi] = FKNISR_PI;
   tuple[knshower10] = unmatchedShowers;

   tuple[e1] = E;
   tuple[th1] = Theta;
   tuple[phi1] = Phi;
   tuple[e9oe25] = E9OE25;
   tuple[x925] = X925;

   tuple[fe1] = FE;
   tuple[fth1] = FTheta;
   tuple[fphi1] = FPhi;

   tuple[fe1_pi] = FE_PI;
   tuple[fth1_pi] = FTheta_PI;
   tuple[fphi1_pi] = FPhi_PI;

   tuple[e2] = E10[1];
   tuple[th2] = Theta10[1];
   tuple[phi2] = Phi10[1];
   tuple[e9252] = E92510[1];

   tuple[e3] = E10[2];
   tuple[th3] = Theta10[2];
   tuple[phi3] = Phi10[2];
   tuple[e9253] = E92510[2];

   tuple[e4] = E10[3];
   tuple[th4] = Theta10[3];
   tuple[phi4] = Phi10[3];
   tuple[e9254] = E92510[3];

   tuple[e5] = E10[4];
   tuple[th5] = Theta10[4];
   tuple[phi5] = Phi10[4];
   tuple[e9255] = E92510[4];

   tuple[e6] = E10[5];
   tuple[th6] = Theta10[5];
   tuple[phi6] = Phi10[5];
   tuple[e9256] = E92510[5];

   tuple[e7] = E10[6];
   tuple[th7] = Theta10[6];
   tuple[phi7] = Phi10[6];
   tuple[e9257] = E92510[6];

   tuple[e8] = E10[7];
   tuple[th8] = Theta10[7];
   tuple[phi8] = Phi10[7];
   tuple[e9258] = E92510[7];

   tuple[e9] = E10[8];
   tuple[th9] = Theta10[8];
   tuple[phi9] = Phi10[8];
   tuple[e9259] = E92510[8];

   tuple[e10] = E10[9];
   tuple[th10] = Theta10[9];
   tuple[phi10] = Phi10[9];
   tuple[e92510] = E92510[9];

   tuple[chisqvtx] = CHISQVTX;
   tuple[chisqfit] = CHISQFIT;

   tuple[chisqvtx_pi] = CHISQVTX_PI;
   tuple[chisqfit_pi] = CHISQFIT_PI;

  if(CHARGE[0]==1 && CHARGE[1]==-1){
   tuple[trte1] = TRPE[0];
   tuple[trpx1] = TRPX[0];
   tuple[trpy1] = TRPY[0];
   tuple[trpz1] = TRPZ[0];
   tuple[trte2] = TRPE[1];
   tuple[trpx2] = TRPX[1];
   tuple[trpy2] = TRPY[1];
   tuple[trpz2] = TRPZ[1];
   tuple[pite1] = PIPE[0];
   tuple[pipx1] = PIPX[0];
   tuple[pipy1] = PIPY[0];
   tuple[pipz1] = PIPZ[0];
   tuple[pite2] = PIPE[1];
   tuple[pipx2] = PIPX[1];
   tuple[pipy2] = PIPY[1];
   tuple[pipz2] = PIPZ[1];
   tuple[eop1] = EOP2[0];
   tuple[eop2] = EOP2[1];
   tuple[me1] = ME[0];
   tuple[me2] = ME[1];
   tuple[mudepth1] = MUDEPTH[0];
   tuple[mudepth2] = MUDEPTH[1];
   tuple[pisigma1] = PPISIGMA[0];
   tuple[musigma1] = PMUSIGMA[0];
   tuple[ksigma1] = PKSIGMA[0];
   tuple[pill1] = PPILL[0];
   tuple[mull1] = PMULL[0];
   tuple[kll1] = PKLL[0];
   tuple[pisigma2] = PPISIGMA[1];
   tuple[musigma2] = PMUSIGMA[1];
   tuple[ksigma2] = PKSIGMA[1];
   tuple[pill2] = PPILL[1];
   tuple[mull2] = PMULL[1];
   tuple[kll2] = PKLL[1];
   tuple[charge1] = CHARGE[0];
   tuple[charge2] = CHARGE[1];
  }

  else if(CHARGE[0]==-1 && CHARGE[1]==1){
   tuple[trte1] = TRPE[1];
   tuple[trpx1] = TRPX[1];
   tuple[trpy1] = TRPY[1];
   tuple[trpz1] = TRPZ[1];
   tuple[trte2] = TRPE[0];
   tuple[trpx2] = TRPX[0];
   tuple[trpy2] = TRPY[0];
   tuple[trpz2] = TRPZ[0];
   tuple[pite1] = PIPE[1];
   tuple[pipx1] = PIPX[1];
   tuple[pipy1] = PIPY[1];
   tuple[pipz1] = PIPZ[1];
   tuple[pite2] = PIPE[0];
   tuple[pipx2] = PIPX[0];
   tuple[pipy2] = PIPY[0];
   tuple[pipz2] = PIPZ[0];
   tuple[eop1] = EOP2[1];
   tuple[eop2] = EOP2[0];
   tuple[me1] = ME[1];
   tuple[me2] = ME[0];
   tuple[mudepth1] = MUDEPTH[1];
   tuple[mudepth2] = MUDEPTH[0];
   tuple[pisigma1] = PPISIGMA[1];
   tuple[musigma1] = PMUSIGMA[1];
   tuple[ksigma1] = PKSIGMA[1];
   tuple[pill1] = PPILL[1];
   tuple[mull1] = PMULL[1];
   tuple[kll1] = PKLL[1];
   tuple[pisigma2] = PPISIGMA[0];
   tuple[musigma2] = PMUSIGMA[0];
   tuple[ksigma2] = PKSIGMA[0];
   tuple[pill2] = PPILL[0];
   tuple[mull2] = PMULL[0];
   tuple[kll2] = PKLL[0];
   tuple[charge1] = CHARGE[1];
   tuple[charge2] = CHARGE[0];
  }


   (*m_showerTuple).fill(tuple);





   return ActionBase::kPassed;
}


ActionBase::ActionResult
ISREffProc::beginRun( Frame& iFrame )       // anal2 equiv.
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
ISREffProc::endRun( Frame& iFrame )         // anal4 equiv.
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
