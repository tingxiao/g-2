// -*- C++ -*-
//
// Package:     PureTrtrProc
// Module:      PureTrtrProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Mon May 20 11:58:31 CDT 2013
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "PureTrtrProc/PureTrtrProc.h"
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
static const char* const kFacilityString = "Processor.PureTrtrProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
PureTrtrProc::PureTrtrProc( void )               // anal1
   : Processor( "PureTrtrProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &PureTrtrProc::event,    Stream::kEvent );
   bind( &PureTrtrProc::beginRun, Stream::kBeginRun );
   //bind( &PureTrtrProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

PureTrtrProc::~PureTrtrProc()                    // anal5
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
PureTrtrProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
PureTrtrProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------

enum {
chisqvpi,chisqfpi, //chisq of pion 1C fit
chisqvmu,chisqfmu, //chisq of muon 1C fit
chisqvk,chisqfk, //chisq of kaon 1C fit

me1,eop1,me2,eop2,  //matched energy and E/p
mudepth1,mudepth2,  //muon depth

pite1,pipx1,pipy1,pipz1,pite2,pipx2,pipy2,pipz2,pisigma1,pill1,pisigma2,pill2,
fpite1,fpipx1,fpipy1,fpipz1,fpite2,fpipx2,fpipy2,fpipz2,
mute1,mupx1,mupy1,mupz1,mute2,mupx2,mupy2,mupz2,musigma1,mull1,musigma2,mull2,
fmute1,fmupx1,fmupy1,fmupz1,fmute2,fmupx2,fmupy2,fmupz2,
kte1,kpx1,kpy1,kpz1,kte2,kpx2,kpy2,kpz2,ksigma1,kll1,ksigma2,kll2,
fkte1,fkpx1,fkpy1,fkpz1,fkte2,fkpx2,fkpy2,fkpz2,

charge1, charge2, //charges of the 2 tracks
beam_e, // beam energy
m_trk,  //track mass variable

kVarNum};



void
PureTrtrProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here
   HINtupleVarNames ntupleNames(kVarNum);
   ntupleNames.addVar(chisqvpi,       "chisqvpi");
   ntupleNames.addVar(chisqfpi,       "chisqfpi");
   ntupleNames.addVar(chisqvmu,       "chisqvmu");
   ntupleNames.addVar(chisqfmu,       "chisqfmu");
   ntupleNames.addVar(chisqvk,       "chisqvk");
   ntupleNames.addVar(chisqfk,       "chisqfk");
   ntupleNames.addVar(me1,          "me1");
   ntupleNames.addVar(eop1,          "eop1");
   ntupleNames.addVar(me2,          "me2");
   ntupleNames.addVar(eop2,          "eop2");
   ntupleNames.addVar(mudepth1,      "mudepth1");
   ntupleNames.addVar(mudepth2,      "mudepth2");
   ntupleNames.addVar(pite1,    "pite1");
   ntupleNames.addVar(pipx1,    "pipx1");
   ntupleNames.addVar(pipy1,    "pipy1");
   ntupleNames.addVar(pipz1,    "pipz1");
   ntupleNames.addVar(pite2,    "pite2");
   ntupleNames.addVar(pipx2,    "pipx2");
   ntupleNames.addVar(pipy2,    "pipy2");
   ntupleNames.addVar(pipz2,    "pipz2");
   ntupleNames.addVar(mute1,    "mute1");
   ntupleNames.addVar(mupx1,    "mupx1");
   ntupleNames.addVar(mupy1,    "mupy1");
   ntupleNames.addVar(mupz1,    "mupz1");
   ntupleNames.addVar(mute2,    "mute2");
   ntupleNames.addVar(mupx2,    "mupx2");
   ntupleNames.addVar(mupy2,    "mupy2");
   ntupleNames.addVar(mupz2,    "mupz2");
   ntupleNames.addVar(kte1,    "kte1");
   ntupleNames.addVar(kpx1,    "kpx1");
   ntupleNames.addVar(kpy1,    "kpy1");
   ntupleNames.addVar(kpz1,    "kpz1");
   ntupleNames.addVar(kte2,    "kte2");
   ntupleNames.addVar(kpx2,    "kpx2");
   ntupleNames.addVar(kpy2,    "kpy2");
   ntupleNames.addVar(kpz2,    "kpz2");
   ntupleNames.addVar(pisigma1, "pisigma1");
   ntupleNames.addVar(pill1,    "pill1");
   ntupleNames.addVar(pisigma2, "pisigma2");
   ntupleNames.addVar(pill2,    "pill2");
   ntupleNames.addVar(musigma1, "musigma1");
   ntupleNames.addVar(mull1,    "mull1");
   ntupleNames.addVar(musigma2, "musigma2");
   ntupleNames.addVar(mull2,    "mull2");
   ntupleNames.addVar(ksigma1, "ksigma1");
   ntupleNames.addVar(kll1,    "kll1");
   ntupleNames.addVar(ksigma2, "ksigma2");
   ntupleNames.addVar(kll2,    "kll2");
   ntupleNames.addVar(fpite1,    "fpite1");
   ntupleNames.addVar(fpipx1,    "fpipx1");
   ntupleNames.addVar(fpipy1,    "fpipy1");
   ntupleNames.addVar(fpipz1,    "fpipz1");
   ntupleNames.addVar(fpite2,    "fpite2");
   ntupleNames.addVar(fpipx2,    "fpipx2");
   ntupleNames.addVar(fpipy2,    "fpipy2");
   ntupleNames.addVar(fpipz2,    "fpipz2");
   ntupleNames.addVar(fmute1,    "fmute1");
   ntupleNames.addVar(fmupx1,    "fmupx1");
   ntupleNames.addVar(fmupy1,    "fmupy1");
   ntupleNames.addVar(fmupz1,    "fmupz1");
   ntupleNames.addVar(fmute2,    "fmute2");
   ntupleNames.addVar(fmupx2,    "fmupx2");
   ntupleNames.addVar(fmupy2,    "fmupy2");
   ntupleNames.addVar(fmupz2,    "fmupz2");
   ntupleNames.addVar(fkte1,    "fkte1");
   ntupleNames.addVar(fkpx1,    "fkpx1");
   ntupleNames.addVar(fkpy1,    "fkpy1");
   ntupleNames.addVar(fkpz1,    "fkpz1");
   ntupleNames.addVar(fkte2,    "fkte2");
   ntupleNames.addVar(fkpx2,    "fkpx2");
   ntupleNames.addVar(fkpy2,    "fkpy2");
   ntupleNames.addVar(fkpz2,    "fkpz2");
   ntupleNames.addVar(charge1,    "charge1");
   ntupleNames.addVar(charge2,    "charge2");
   ntupleNames.addVar(beam_e,"beam_e");
   ntupleNames.addVar(m_trk,"m_trk");

   m_showerTuple = iHistoManager.ntuple(10,"tuple", kVarNum, 10000, ntupleNames.names());

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
PureTrtrProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   const int kMaxTrack = 2;
   const int kMaxShower = 10;

   double ChisqVpi = 1000000.;
   double ChisqFpi = 1000000.;
   double ChisqVmu = 1000000.;
   double ChisqFmu = 1000000.;
   double ChisqVk = 1000000.;
   double ChisqFk = 1000000.;
   double BEAME = 10000.;
   double TRKM = 10000.;
   double ME[kMaxTrack] = {10000.,10000.};
   double EOP[kMaxTrack] = {10000.,10000.};
   double MUDEPTH[kMaxTrack] = {0.,0.};
   double PIPE[kMaxTrack] = {10000.,10000.};
   double PIPX[kMaxTrack] = {10000.,10000.};
   double PIPY[kMaxTrack] = {10000.,10000.};
   double PIPZ[kMaxTrack] = {10000.,10000.};
   double MUPE[kMaxTrack] = {10000.,10000.};
   double MUPX[kMaxTrack] = {10000.,10000.};
   double MUPY[kMaxTrack] = {10000.,10000.};
   double MUPZ[kMaxTrack] = {10000.,10000.};
   double KPE[kMaxTrack] = {10000.,10000.};
   double KPX[kMaxTrack] = {10000.,10000.};
   double KPY[kMaxTrack] = {10000.,10000.};
   double KPZ[kMaxTrack] = {10000.,10000.};
   double PPISIGMA[kMaxTrack] = {10000.,10000.};
   double PPILL[kMaxTrack] = {10000.,10000.};
   double PMUSIGMA[kMaxTrack] = {10000.,10000.};
   double PMULL[kMaxTrack] = {10000.,10000.};
   double PKSIGMA[kMaxTrack] = {10000.,10000.};
   double PKLL[kMaxTrack] = {10000.,10000.};
   double PIFPE[kMaxTrack] = {10000.,10000.};
   double PIFPX[kMaxTrack] = {10000.,10000.};
   double PIFPY[kMaxTrack] = {10000.,10000.};
   double PIFPZ[kMaxTrack] = {10000.,10000.};
   double MUFPE[kMaxTrack] = {10000.,10000.};
   double MUFPX[kMaxTrack] = {10000.,10000.};
   double MUFPY[kMaxTrack] = {10000.,10000.};
   double MUFPZ[kMaxTrack] = {10000.,10000.};
   double KFPE[kMaxTrack] = {10000.,10000.};
   double KFPX[kMaxTrack] = {10000.,10000.};
   double KFPY[kMaxTrack] = {10000.,10000.};
   double KFPZ[kMaxTrack] = {10000.,10000.};
   double CHARGE[kMaxTrack] = {0.,0.};   

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

////////////////////////////////////// only 2 opposite charged tracks /////////////////////



   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable, "GoodThings"  );

   FATable< NavTrack >::const_iterator trackBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackEnd = trackTable.end();

   if(trackTable.size() != 2)
      return ActionBase::kFailed;

   FAItem<TDKinematicFit> tr1 = (*trackBegin).pionFit();
   FAItem<TDKinematicFit> tr2 = (*(trackBegin+1)).pionFit();

   CHARGE[0] = (*tr1).charge();
   CHARGE[1] = (*tr2).charge();

   if(CHARGE[0]!=-CHARGE[1])
      return ActionBase::kFailed;

   int unmatchedTracks = 0;

   for ( FATable< NavTrack >::const_iterator trackItr = trackBegin;
         trackItr != trackEnd ;
         ++trackItr )
   {
      FAItem<DedxInfo> the_dedx = (*trackItr).dedxInfo();
      FAItem<NavRich> the_rich = (*trackItr).richInfo();
      FAItem<TDKinematicFit> pionFit = (*trackItr).pionFit();
      FAItem<TDKinematicFit> muonFit = (*trackItr).muonFit();
      FAItem<TDKinematicFit> kaonFit = (*trackItr).kaonFit();
      double cos_theta1 = pionFit->pz() / pionFit->pmag();
      double cos_theta2 = muonFit->pz() / muonFit->pmag();
      double cos_theta3 = kaonFit->pz() / kaonFit->pmag();

      int j = unmatchedTracks++;

      if(j < kMaxTrack){

      if(trackItr->trackShowerMatch().valid())
        ME[j] = trackItr->trackShowerMatch()->matchedEnergy();

      EOP[j] = trackItr->elecId().eOverP();
      MUDEPTH[j] = trackItr->muonId().depth();
      if(EOP[j]>0.8)
        return ActionBase::kFailed;

      if( (pionFit.valid()) && (the_dedx.valid()) )  {

        PIPE[j]=pionFit->lorentzMomentum().e();
        PIPX[j]=pionFit->px();
        PIPY[j]=pionFit->py();
        PIPZ[j]=pionFit->pz();
        PPISIGMA[j]=the_dedx->piSigma();

        if ((the_rich.valid()) && (fabs(cos_theta1) < 0.8) && (the_rich->pionHypWasAnalyzed()))
          PPILL[j]=the_rich->pionLogLikelihood();
      }

      if( (muonFit.valid()) && (the_dedx.valid()) )  {

        MUPE[j]=muonFit->lorentzMomentum().e();
        MUPX[j]=muonFit->px();
        MUPY[j]=muonFit->py();
        MUPZ[j]=muonFit->pz();
        PMUSIGMA[j]=the_dedx->muSigma();

        if ((the_rich.valid()) && (fabs(cos_theta2) < 0.8) && (the_rich->muonHypWasAnalyzed()))
          PMULL[j]=the_rich->muonLogLikelihood();
      }

      if( (kaonFit.valid()) && (the_dedx.valid()) )  {

        KPE[j]=kaonFit->lorentzMomentum().e();
        KPX[j]=kaonFit->px();
        KPY[j]=kaonFit->py();
        KPZ[j]=kaonFit->pz();
        PKSIGMA[j]=the_dedx->kSigma();

        if ((the_rich.valid()) && (fabs(cos_theta3) < 0.8) && (the_rich->kaonHypWasAnalyzed()))
        PKLL[j]=the_rich->kaonLogLikelihood();
      }
      }
   }

   FAItem< BeamEnergy > beam_energy;
   extract( iFrame.record( Stream::kBeginRun ), beam_energy );
   BEAME = beam_energy->value();
   double s = pow((2*BEAME),2);
   double pppn = sqrt(pow((PIPX[0]+PIPX[1]),2)+pow((PIPY[0]+PIPY[1]),2)+pow((PIPZ[0]+PIPZ[1]),2));
   double pp2 = pow(PIPX[0],2)+pow(PIPY[0],2)+pow(PIPZ[0],2);
   double pn2 = pow(PIPX[1],2)+pow(PIPY[1],2)+pow(PIPZ[1],2);
   double mm = (pow((pow((sqrt(s)-pppn),2)-pp2-pn2),2)-4*pp2*pn2)/(4*pow((sqrt(s)-pppn),2));
   TRKM = sqrt(mm);   


/////////////////////////////// ISR shower E > 500 MeV //////////////////////////////////////

   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ) , showerTable, "GoodThings" );

   if(showerTable.size()==0)
      return ActionBase::kFailed;

   FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
   FATable< NavShower >::const_iterator showerEnd = showerTable.end();

   FATable< NavShower >::const_iterator fastest_shower = showerBegin;
   if(fastest_shower->attributes().x925() < 1)   
      return ActionBase::kFailed;
   if(fastest_shower->attributes().energy() < 0.5)   
      return ActionBase::kFailed;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////// 1C fit //////////////////////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   FAItem<TDKinematicFit> pi1 = (*trackBegin).pionFit();
   FAItem<TDKinematicFit> pi2 = (*(trackBegin+1)).pionFit();
   FAItem<TDKinematicFit> mu1 = (*trackBegin).muonFit();
   FAItem<TDKinematicFit> mu2 = (*(trackBegin+1)).muonFit();
   FAItem<TDKinematicFit> k1 = (*trackBegin).kaonFit();
   FAItem<TDKinematicFit> k2 = (*(trackBegin+1)).kaonFit();
   FAItem<DedxInfo> the_dedx1 = (*trackBegin).dedxInfo();
   FAItem<DedxInfo> the_dedx2 = (*(trackBegin+1)).dedxInfo();

   double TRE = 2*BEAME	- fastest_shower->attributes().energy();

   FitEvt pipi( "Pipi", FitEvt::k_Energy,0,TRE );
   pipi.newTrack(*pi1);
   pipi.newTrack(*pi2);
   pipi.doTheFit();

   if( (pipi.chisqVtx()>0) && (pipi.chisqFit()>0) && (pi1.valid()) && (the_dedx1.valid()) && (pi2.valid()) && (the_dedx2.valid())) {
     ChisqFpi = pipi.chisqFit();
     ChisqVpi = pipi.chisqVtx();
     HepLorentzVector v1pi (pipi.kdFitVec()[0]->lorentzMomentum());
     HepLorentzVector v2pi (pipi.kdFitVec()[1]->lorentzMomentum());
     PIFPE[0]=v1pi.e();
     PIFPX[0]=v1pi.px();
     PIFPY[0]=v1pi.py();
     PIFPZ[0]=v1pi.pz();
     PIFPE[1]=v2pi.e();
     PIFPX[1]=v2pi.px();
     PIFPY[1]=v2pi.py();
     PIFPZ[1]=v2pi.pz();
   }

   FitEvt mumu( "Mumu", FitEvt::k_Energy,0,TRE );
   mumu.newTrack(*mu1);
   mumu.newTrack(*mu2);
   mumu.doTheFit();

   if( (mumu.chisqVtx()>0) && (mumu.chisqFit()>0) && (mu1.valid()) && (the_dedx1.valid()) && (mu2.valid()) && (the_dedx2.valid())) {

     ChisqFmu = mumu.chisqFit();
     ChisqVmu = mumu.chisqVtx();
     HepLorentzVector v1mu (mumu.kdFitVec()[0]->lorentzMomentum());
     HepLorentzVector v2mu (mumu.kdFitVec()[1]->lorentzMomentum());
     MUFPE[0]=v1mu.e();
     MUFPX[0]=v1mu.px();
     MUFPY[0]=v1mu.py();
     MUFPZ[0]=v1mu.pz();
     MUFPE[1]=v2mu.e();
     MUFPX[1]=v2mu.px();
     MUFPY[1]=v2mu.py();
     MUFPZ[1]=v2mu.pz();
   }

   FitEvt kk( "Kk", FitEvt::k_Energy,0,TRE );
   kk.newTrack(*k1);
   kk.newTrack(*k2);
   kk.doTheFit();

   if( (kk.chisqVtx()>0) && (kk.chisqFit()>0) && (k1.valid()) && (the_dedx1.valid()) && (k2.valid()) && (the_dedx2.valid())) {

     ChisqFk = kk.chisqFit();
     ChisqVk = kk.chisqVtx();
     HepLorentzVector v1k (kk.kdFitVec()[0]->lorentzMomentum());
     HepLorentzVector v2k (kk.kdFitVec()[1]->lorentzMomentum());
     KFPE[0]=v1k.e();
     KFPX[0]=v1k.px();
     KFPY[0]=v1k.py();
     KFPZ[0]=v1k.pz();
     KFPE[1]=v2k.e();
     KFPX[1]=v2k.px();
     KFPY[1]=v2k.py();
     KFPZ[1]=v2k.pz();
   }

   tuple[chisqvpi] = ChisqVpi;
   tuple[chisqfpi] = ChisqFpi;
   tuple[chisqvmu] = ChisqVmu;
   tuple[chisqfmu] = ChisqFmu;
   tuple[chisqvk] = ChisqVk;
   tuple[chisqfk] = ChisqFk;

   if(CHARGE[0]==1 && CHARGE[1]==-1){
   tuple[me1] = ME[0];
   tuple[eop1] = EOP[0];
   tuple[me2] = ME[1];
   tuple[eop2] = EOP[1];

   tuple[mudepth1] = MUDEPTH[0];
   tuple[mudepth2] = MUDEPTH[1];

   tuple[pite1] = PIPE[0];
   tuple[pipx1] = PIPX[0];
   tuple[pipy1] = PIPY[0];
   tuple[pipz1] = PIPZ[0];
   tuple[pite2] = PIPE[1];
   tuple[pipx2] = PIPX[1];
   tuple[pipy2] = PIPY[1];
   tuple[pipz2] = PIPZ[1];

   tuple[mute1] = MUPE[0];
   tuple[mupx1] = MUPX[0];
   tuple[mupy1] = MUPY[0];
   tuple[mupz1] = MUPZ[0];
   tuple[mute2] = MUPE[1];
   tuple[mupx2] = MUPX[1];
   tuple[mupy2] = MUPY[1];
   tuple[mupz2] = MUPZ[1];

   tuple[kte1] = KPE[0];
   tuple[kpx1] = KPX[0];
   tuple[kpy1] = KPY[0];
   tuple[kpz1] = KPZ[0];
   tuple[kte2] = KPE[1];
   tuple[kpx2] = KPX[1];
   tuple[kpy2] = KPY[1];
   tuple[kpz2] = KPZ[1];

   tuple[pisigma1] = PPISIGMA[0];
   tuple[pill1] = PPILL[0];
   tuple[pisigma2] = PPISIGMA[1];
   tuple[pill2] = PPILL[1];

   tuple[musigma1] = PMUSIGMA[0];
   tuple[mull1] = PMULL[0];
   tuple[musigma2] = PMUSIGMA[1];
   tuple[mull2] = PMULL[1];
   tuple[ksigma1] = PKSIGMA[0];
   tuple[kll1] = PKLL[0];
   tuple[ksigma2] = PKSIGMA[1];
   tuple[kll2] = PKLL[1];

   tuple[fpite1] = PIFPE[0];
   tuple[fpipx1] = PIFPX[0];
   tuple[fpipy1] = PIFPY[0];
   tuple[fpipz1] = PIFPZ[0];
   tuple[fpite2] = PIFPE[1];
   tuple[fpipx2] = PIFPX[1];
   tuple[fpipy2] = PIFPY[1];
   tuple[fpipz2] = PIFPZ[1];

   tuple[fmute1] = MUFPE[0];
   tuple[fmupx1] = MUFPX[0];
   tuple[fmupy1] = MUFPY[0];
   tuple[fmupz1] = MUFPZ[0];
   tuple[fmute2] = MUFPE[1];
   tuple[fmupx2] = MUFPX[1];
   tuple[fmupy2] = MUFPY[1];
   tuple[fmupz2] = MUFPZ[1];

   tuple[fkte1] = KFPE[0];
   tuple[fkpx1] = KFPX[0];
   tuple[fkpy1] = KFPY[0];
   tuple[fkpz1] = KFPZ[0];
   tuple[fkte2] = KFPE[1];
   tuple[fkpx2] = KFPX[1];
   tuple[fkpy2] = KFPY[1];
   tuple[fkpz2] = KFPZ[1];

   tuple[charge1] = CHARGE[0];
   tuple[charge2] = CHARGE[1];
   }

   else if(CHARGE[1]==1 && CHARGE[0]==-1){
   tuple[me1] = ME[1];
   tuple[eop1] = EOP[1];
   tuple[me2] = ME[0];
   tuple[eop2] = EOP[0];

   tuple[mudepth1] = MUDEPTH[1];
   tuple[mudepth2] = MUDEPTH[0];

   tuple[pite1] = PIPE[1];
   tuple[pipx1] = PIPX[1];
   tuple[pipy1] = PIPY[1];
   tuple[pipz1] = PIPZ[1];
   tuple[pite2] = PIPE[0];
   tuple[pipx2] = PIPX[0];
   tuple[pipy2] = PIPY[0];
   tuple[pipz2] = PIPZ[0];

   tuple[mute1] = MUPE[1];
   tuple[mupx1] = MUPX[1];
   tuple[mupy1] = MUPY[1];
   tuple[mupz1] = MUPZ[1];
   tuple[mute2] = MUPE[0];
   tuple[mupx2] = MUPX[0];
   tuple[mupy2] = MUPY[0];
   tuple[mupz2] = MUPZ[0];

   tuple[kte1] = KPE[1];
   tuple[kpx1] = KPX[1];
   tuple[kpy1] = KPY[1];
   tuple[kpz1] = KPZ[1];
   tuple[kte2] = KPE[0];
   tuple[kpx2] = KPX[0];
   tuple[kpy2] = KPY[0];
   tuple[kpz2] = KPZ[0];

   tuple[pisigma1] = PPISIGMA[1];
   tuple[pill1] = PPILL[1];
   tuple[pisigma2] = PPISIGMA[0];
   tuple[pill2] = PPILL[0];

   tuple[musigma1] = PMUSIGMA[1];
   tuple[mull1] = PMULL[1];
   tuple[musigma2] = PMUSIGMA[0];
   tuple[mull2] = PMULL[0];

   tuple[ksigma1] = PKSIGMA[1];
   tuple[kll1] = PKLL[1];
   tuple[ksigma2] = PKSIGMA[0];
   tuple[kll2] = PKLL[0];

   tuple[fpite1] = PIFPE[1];
   tuple[fpipx1] = PIFPX[1];
   tuple[fpipy1] = PIFPY[1];
   tuple[fpipz1] = PIFPZ[1];
   tuple[fpite2] = PIFPE[0];
   tuple[fpipx2] = PIFPX[0];
   tuple[fpipy2] = PIFPY[0];
   tuple[fpipz2] = PIFPZ[0];

   tuple[fmute1] = MUFPE[1];
   tuple[fmupx1] = MUFPX[1];
   tuple[fmupy1] = MUFPY[1];
   tuple[fmupz1] = MUFPZ[1];
   tuple[fmute2] = MUFPE[0];
   tuple[fmupx2] = MUFPX[0];
   tuple[fmupy2] = MUFPY[0];
   tuple[fmupz2] = MUFPZ[0];

   tuple[fkte1] = KFPE[1];
   tuple[fkpx1] = KFPX[1];
   tuple[fkpy1] = KFPY[1];
   tuple[fkpz1] = KFPZ[1];
   tuple[fkte2] = KFPE[0];
   tuple[fkpx2] = KFPX[0];
   tuple[fkpy2] = KFPY[0];
   tuple[fkpz2] = KFPZ[0];

   tuple[charge1] = CHARGE[1];
   tuple[charge2] = CHARGE[0];
   }

   tuple[beam_e] = BEAME;
   tuple[m_trk] = TRKM;
   

   (*m_showerTuple).fill(tuple);


   return ActionBase::kPassed;
}


ActionBase::ActionResult
PureTrtrProc::beginRun( Frame& iFrame )       // anal2 equiv.
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
PureTrtrProc::endRun( Frame& iFrame )         // anal4 equiv.
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
