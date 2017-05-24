// -*- C++ -*-
//
// Package:     InclusivePiPiPhiProc
// Module:      InclusivePiPiPhiProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Sean Dobbs
// Created:     Wed Jul  7 17:32:00 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

//#include "Experiment/Experiment.h"

// system include files

// user include files
#include "InclusivePiPiPhiProc/InclusivePiPiPhiProc.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

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

#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"

#include <Navigation/NavRich.h> 
#include <Navigation/NavKs.h>
#include <DedxInfo/DedxInfo.h>
#include <Navigation/NavMuonId.h> 
#include <Navigation/NavElecId.h> 
#include <VXFitVeeCandidate/VXFitVeeKShort.h> 

//#include "/home/sdobbs/src/VFinderQualityObject/VFinderQualityObject/KsQuality.h"
#include <VFinderQualityObject/KsQuality.h>

#include "Navigation/NavPi0ToGG.h" 
#include "Navigation/NavEtaToGG.h" 
#include "PhotonDecays/PhdPi0.h"
#include "PhotonDecays/PhdEtaToGG.h"
#include "Navigation/NavTkShMatch.h"
#include "BeamEnergy/BeamEnergy.h"
#include "BeamSpot/BeamSpot.h"
#include <PhotonDecays/PhdPi0.h> 
#include <CleoDB/DBEventHeader.h> 

#include "TriggerL1DataProd/TriggerL1DataProd.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "Level4Proc/Level4Decision.h"

#include <FitEvt/FitEvt.h>
#include <FitEvt/FitEvtSettings.h>

// Histogram/Ntuple include files
#include "HistogramInterface/HIHist1D.h"
#include "HistogramInterface/HINtupleVarNames.h"
#include "HistogramInterface/HINtupleArray.h"


#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCDecayTree/MCVertex.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"



// STL classes
// You may have to uncomment some of these or other stl headers 
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

#include <iostream>
//#include <fstream>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.InclusivePiPiPhiProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//


static bool isGoodPion( const NavTrack& the_track )
{
   //DABoolean pass = false;
   FAItem<DedxInfo> the_dedx = the_track.dedxInfo();
   FAItem<NavRich> the_rich = the_track.richInfo();
   FAItem<TDKinematicFit> pionFit = the_track.pionFit();

   if(!pionFit.valid() || !the_dedx.valid()) return false;

   double cos_theta = pionFit->pz() / pionFit->pmag();

   // Dedx PID
   double pi_sig = the_dedx->piSigma();
   double p_sig = the_dedx->pSigma();
   double k_sig = the_dedx->kSigma();
   
   // require 2 sigma consistency for low-momentum tracks
   if( (pionFit->pmag() < 0.6) && (fabs(pi_sig) > 3) ) {
      return false;
   }
   
   double DL_pik = (pi_sig*pi_sig) - (k_sig*k_sig);
   double DL_pip = (pi_sig*pi_sig) - (p_sig*p_sig);   
  
   if(the_rich.valid() 
      && (pionFit->pmag() > 0.6)
      && (fabs(cos_theta) < 0.8) ) {
      double piLL = -1000;
      double kLL = -1000;
      double pLL = -1000;

      if( (the_rich->pionHypWasAnalyzed())
	  && (the_rich->pionNumberOfPhotonsInAverage() > 2) ) {
	 piLL = the_rich->pionLogLikelihood();
	 DL_pik += the_rich->pionLogLikelihood();
	 DL_pip += the_rich->pionLogLikelihood();
      }
      if(the_rich->kaonHypWasAnalyzed()		  
	 && (the_rich->kaonNumberOfPhotonsInAverage() > 2) ) {
	 kLL = the_rich->kaonLogLikelihood();
	 DL_pik -= the_rich->kaonLogLikelihood();
      }
      if(pionFit->pmag() > 1.5) {
	 if(the_rich->protonHypWasAnalyzed()		  
	    && (the_rich->protonNumberOfPhotonsInAverage() > 2) ) {
	    pLL = the_rich->protonLogLikelihood();
	    DL_pip -= the_rich->protonLogLikelihood();
	 }
      }
   }


   return ( ( DL_pik < 0. ) && ( DL_pip < 0. ) );
}


//make kaon selection
static bool isGoodKaon( const NavTrack& the_track )
{
   //DABoolean pass = false;
   FAItem<DedxInfo> the_dedx = the_track.dedxInfo();
   FAItem<NavRich> the_rich = the_track.richInfo();
   FAItem<TDKinematicFit> kaonFit = the_track.kaonFit();

   if(!kaonFit.valid() || !the_dedx.valid()) return false;

   double cos_theta = kaonFit->pz() / kaonFit->pmag();

   // Dedx PID
   double pi_sig = the_dedx->piSigma();
   double p_sig = the_dedx->pSigma();
   double k_sig = the_dedx->kSigma();

   // require 4 sigma consistency
   if( (kaonFit->pmag() < 0.6) && (fabs(k_sig) > 3) )
      return false;
   
   double DL_kpi = (k_sig*k_sig) - (pi_sig*pi_sig);
   double DL_kp = (k_sig*k_sig) - (p_sig*p_sig);

   if(the_rich.valid() 
      && (kaonFit->pmag() > 0.6)
      && (fabs(cos_theta) < 0.8) ) {
      double piLL = -1000;
      double kLL = -1000;
      double pLL = -1000;

      
      if( (the_rich->pionHypWasAnalyzed())
	  && (the_rich->pionNumberOfPhotonsInAverage() > 2) ) {
	 piLL = the_rich->pionLogLikelihood();
	 DL_kpi -= the_rich->pionLogLikelihood();
      }
      if(the_rich->kaonHypWasAnalyzed()		  
	 && (the_rich->kaonNumberOfPhotonsInAverage() > 2) ) {
	 kLL = the_rich->kaonLogLikelihood();
	 DL_kpi += the_rich->kaonLogLikelihood();
	 DL_kp  += the_rich->kaonLogLikelihood();
      }
      if(kaonFit->pmag() > 1.5) {
	 if(the_rich->protonHypWasAnalyzed()		  
	    && (the_rich->protonNumberOfPhotonsInAverage() > 2) ) {
	    pLL = the_rich->protonLogLikelihood();
	    DL_kp -= the_rich->protonLogLikelihood();
	 }
      }
   }


   return ( ( DL_kpi < -36. ) && ( DL_kp < -36. ) );
}

//make proton selection
static bool isGoodProton( const NavTrack& the_track )
{

   //DABoolean pass = false;
   FAItem<DedxInfo> the_dedx = the_track.dedxInfo();
   FAItem<NavRich> the_rich = the_track.richInfo();
   FAItem<TDKinematicFit> protonFit = the_track.protonFit();

   if(!protonFit.valid() || !the_dedx.valid()) return false;

   double cos_theta = protonFit->pz() / protonFit->pmag();

   // Dedx PID
   double pi_sig = the_dedx->piSigma();
   double p_sig = the_dedx->pSigma();
   double k_sig = the_dedx->kSigma();
   
   // require 3 sigma consistency
   if( (protonFit->pmag() < 1.2) && (fabs(p_sig) > 3) )
      return false;
   
   double DL_ppi = (p_sig*p_sig) - (pi_sig*pi_sig);
   double DL_pk  = (p_sig*p_sig) - (k_sig*k_sig);

   if(the_rich.valid() 
      && (protonFit->pmag() > 1.2)
      && (fabs(cos_theta) < 0.8) ) {
      
      if( (the_rich->pionHypWasAnalyzed())
	  && (the_rich->pionNumberOfPhotonsInAverage() > 2) ) {
	 DL_ppi -= the_rich->pionLogLikelihood();
      }
      if(the_rich->kaonHypWasAnalyzed()		  
	 && (the_rich->kaonNumberOfPhotonsInAverage() > 2) ) {
	 DL_pk -= the_rich->kaonLogLikelihood();
      }
      // if(protonFit->pmag() > 1.2) {
      if(the_rich->protonHypWasAnalyzed()		  
	 && (the_rich->protonNumberOfPhotonsInAverage() > 2) ) {
	DL_ppi += the_rich->protonLogLikelihood();
	DL_pk += the_rich->protonLogLikelihood();
      }
      //}
   }

   return ( ( DL_ppi < -9. ) && ( DL_pk < -9. ) );
}


//
// constructors and destructor
//
InclusivePiPiPhiProc::InclusivePiPiPhiProc( void )               // anal1
   : Processor( "InclusivePiPiPhiProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &InclusivePiPiPhiProc::event,    Stream::kEvent );
   bind( &InclusivePiPiPhiProc::beginRun, Stream::kBeginRun );
   //bind( &InclusivePiPiPhiProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

InclusivePiPiPhiProc::~InclusivePiPiPhiProc()                    // anal5
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
InclusivePiPiPhiProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)


   m_beam_x = 0.;
   m_beam_y = 0.;
   m_beam_z = 0.;
}

// -------------------- terminate method ----------------------------
void
InclusivePiPiPhiProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------

enum {
       k_pipi_Pi1_E, k_pipi_Pi1_Px, k_pipi_Pi1_Py, k_pipi_Pi1_Pz, 
       k_pipi_Pi2_E, k_pipi_Pi2_Px, k_pipi_Pi2_Py, k_pipi_Pi2_Pz, 
       k_pipi_Pi3_E, k_pipi_Pi3_Px, k_pipi_Pi3_Py, k_pipi_Pi3_Pz, 
       k_pipi_Pi4_E, k_pipi_Pi4_Px, k_pipi_Pi4_Py, k_pipi_Pi4_Pz, 
       k_pipi_Pi5_E, k_pipi_Pi5_Px, k_pipi_Pi5_Py, k_pipi_Pi5_Pz, 
       k_pipi_Pi6_E, k_pipi_Pi6_Px, k_pipi_Pi6_Py, k_pipi_Pi6_Pz, 
       k_pipi_Pi7_E, k_pipi_Pi7_Px, k_pipi_Pi7_Py, k_pipi_Pi7_Pz, 
       k_pipi_Pi8_E, k_pipi_Pi8_Px, k_pipi_Pi8_Py, k_pipi_Pi8_Pz, 

       k_kk_K1_E, k_kk_K1_Px, k_kk_K1_Py, k_kk_K1_Pz, 
       k_kk_K2_E, k_kk_K2_Px, k_kk_K2_Py, k_kk_K2_Pz, 

       k_charge_1, k_charge_2, k_charge_3, k_charge_4, k_charge_5, k_charge_6, k_charge_7, k_charge_8,
       k_kcharge_1, k_kcharge_2,
       k_EP_1, k_EP_2, k_EP_3, k_EP_4, k_EP_5, k_EP_6, k_EP_7, k_EP_8,
       k_kEP_1, k_kEP_2,
       k_mudepth_1, k_mudepth_2, k_mudepth_3, k_mudepth_4, k_mudepth_5, k_mudepth_6, k_mudepth_7, k_mudepth_8,

       kNumVars };


void
InclusivePiPiPhiProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here
   HINtupleVarNames ntNames(kNumVars);

   ntNames.addVar(k_charge_1, "Charge1");
   ntNames.addVar(k_charge_2, "Charge2");
   ntNames.addVar(k_charge_3, "Charge3");
   ntNames.addVar(k_charge_4, "Charge4");
   ntNames.addVar(k_charge_5, "Charge5");
   ntNames.addVar(k_charge_6, "Charge6");
   ntNames.addVar(k_charge_7, "Charge7");
   ntNames.addVar(k_charge_8, "Charge8");
   ntNames.addVar(k_kcharge_1, "KCharge1");
   ntNames.addVar(k_kcharge_2, "KCharge2");

   ntNames.addVar(k_pipi_Pi1_E, "PPi1E");
   ntNames.addVar(k_pipi_Pi1_Px, "PPi1Px");
   ntNames.addVar(k_pipi_Pi1_Py, "PPi1Py");
   ntNames.addVar(k_pipi_Pi1_Pz, "PPi1Pz");
   ntNames.addVar(k_pipi_Pi2_E, "PPi2E");
   ntNames.addVar(k_pipi_Pi2_Px, "PPi2Px");
   ntNames.addVar(k_pipi_Pi2_Py, "PPi2Py");
   ntNames.addVar(k_pipi_Pi2_Pz, "PPi2Pz");
   ntNames.addVar(k_pipi_Pi3_E, "PPi3E");
   ntNames.addVar(k_pipi_Pi3_Px, "PPi3Px");
   ntNames.addVar(k_pipi_Pi3_Py, "PPi3Py");
   ntNames.addVar(k_pipi_Pi3_Pz, "PPi3Pz");
   ntNames.addVar(k_pipi_Pi4_E, "PPi4E");
   ntNames.addVar(k_pipi_Pi4_Px, "PPi4Px");
   ntNames.addVar(k_pipi_Pi4_Py, "PPi4Py");
   ntNames.addVar(k_pipi_Pi4_Pz, "PPi4Pz");
   ntNames.addVar(k_pipi_Pi5_E, "PPi5E");
   ntNames.addVar(k_pipi_Pi5_Px, "PPi5Px");
   ntNames.addVar(k_pipi_Pi5_Py, "PPi5Py");
   ntNames.addVar(k_pipi_Pi5_Pz, "PPi5Pz");
   ntNames.addVar(k_pipi_Pi6_E, "PPi6E");
   ntNames.addVar(k_pipi_Pi6_Px, "PPi6Px");
   ntNames.addVar(k_pipi_Pi6_Py, "PPi6Py");
   ntNames.addVar(k_pipi_Pi6_Pz, "PPi6Pz");
   ntNames.addVar(k_pipi_Pi7_E, "PPi7E");
   ntNames.addVar(k_pipi_Pi7_Px, "PPi7Px");
   ntNames.addVar(k_pipi_Pi7_Py, "PPi7Py");
   ntNames.addVar(k_pipi_Pi7_Pz, "PPi7Pz");
   ntNames.addVar(k_pipi_Pi8_E, "PPi8E");
   ntNames.addVar(k_pipi_Pi8_Px, "PPi8Px");
   ntNames.addVar(k_pipi_Pi8_Py, "PPi8Py");
   ntNames.addVar(k_pipi_Pi8_Pz, "PPi8Pz");

   ntNames.addVar(k_kk_K1_E, "KK1E");
   ntNames.addVar(k_kk_K1_Px, "KK1Px");
   ntNames.addVar(k_kk_K1_Py, "KK1Py");
   ntNames.addVar(k_kk_K1_Pz, "KK1Pz");
   ntNames.addVar(k_kk_K2_E, "KK2E");
   ntNames.addVar(k_kk_K2_Px, "KK2Px");
   ntNames.addVar(k_kk_K2_Py, "KK2Py");
   ntNames.addVar(k_kk_K2_Pz, "KK2Pz");

   ntNames.addVar(k_EP_1, "EoP1");
   ntNames.addVar(k_EP_2, "EoP2");
   ntNames.addVar(k_EP_3, "EoP3");
   ntNames.addVar(k_EP_4, "EoP4");
   ntNames.addVar(k_EP_5, "EoP5");
   ntNames.addVar(k_EP_6, "EoP6");
   ntNames.addVar(k_EP_7, "EoP7");
   ntNames.addVar(k_EP_8, "EoP8");

   ntNames.addVar(k_kEP_1, "kEoP1");
   ntNames.addVar(k_kEP_2, "kEoP2");

   ntNames.addVar(k_mudepth_1, "mudepth1");
   ntNames.addVar(k_mudepth_2, "mudepth2");
   ntNames.addVar(k_mudepth_3, "mudepth3");
   ntNames.addVar(k_mudepth_4, "mudepth4");
   ntNames.addVar(k_mudepth_5, "mudepth5");
   ntNames.addVar(k_mudepth_6, "mudepth6");
   ntNames.addVar(k_mudepth_7, "mudepth7");
   ntNames.addVar(k_mudepth_8, "mudepth8");


   h_mpipikk = iHistoManager.histogram(1, "mpipikk", 200, 0., 4.);

   m_LEGammaNt = iHistoManager.ntuple( 25, "LE Gammas",
				       kNumVars, 50000, ntNames.names());


}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
InclusivePiPiPhiProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;


   const int kMaxTrack = 10;




   double kPE[kMaxTrack-8] = {-10.,-10.};   // kaons
   double kPPx[kMaxTrack-8] = {-10.,-10.};
   double kPPy[kMaxTrack-8] = {-10.,-10.};
   double kPPz[kMaxTrack-8] = {-10.,-10.};
   double kCharge[kMaxTrack-8] = {-10.,-10.};
   double kEOP[kMaxTrack-8] = {-10.,-10.};

   double PE[kMaxTrack-2] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};   // pions
   double PPx[kMaxTrack-2] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double PPy[kMaxTrack-2] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double PPz[kMaxTrack-2] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double Charge[kMaxTrack-2] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double EOP[kMaxTrack-2] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double MuDepth[kMaxTrack-2] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};


   float ntVal[kNumVars];

   // save the run and event numbers
   FAItem< DBEventHeader > eventHeader ;
   extract( iFrame.record( Stream::kEvent ), eventHeader ) ;

   int the_run = eventHeader->run();
   int the_evt = eventHeader->number();


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
//	(trigDat->isMuPair())       ||
//	(trigDat->isElTrack())      ||
//	(trigDat->isRadTau())       || 
//	(trigDat->isBarrelBhabha())  )
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




   // Create a table of tracks and fill it.
   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable, "GoodThings" );

   FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();

   // Loop over tracks.
   int numTrack=0;
   //int numFit=0;
   //double tCharge=0;
   //int numPi0=0;
   //int numEta=0;
   //int numKs=0;


   //FAItem<TDKinematicFit> tagk1, tagk2;
   //FAItem<TDKinematicFit> pi1, pi2;
   FAItem<TDKinematicFit> k1, k2;
   //FAItem<TDKinematicFit> p1, p2;
   int good_phi = 0;
   double best_tag = 0.;
   //vector< FAItem<TDKinematicFit> > good_tracks;
   //vector< FAItem<TDKinematicFit> > fourpi_tracks;
   vector< FAItem<TDKinematicFit> > pion_tracks;
   vector< FAItem<TDKinematicFit> > kaon_tracks;
   //vector< FAItem<TDKinematicFit> > proton_tracks;


   // Search for the two kaons from phi decay
   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;
         ++trackItr )
   {
      FAItem<TDKinematicFit> kaonFit = trackItr->kaonFit();

      if( isGoodKaon( *trackItr ) ) {
        kaon_tracks.push_back(kaonFit);
      }
   }

   if( (kaon_tracks.size()<2) )
      return ActionBase::kFailed;



   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;
         ++trackItr )
   {
      FAItem<TDKinematicFit> kaonFit = trackItr->kaonFit();

      for ( FATable< NavTrack >::const_iterator trackItr2 = trackItr+1;
            trackItr2 != trackTableEnd ;
            ++trackItr2 )
      {
         FAItem<TDKinematicFit> kaonFit2 = trackItr2->kaonFit();

         if( isGoodKaon( *trackItr ) && isGoodKaon( *trackItr2 ) && kaonFit2->charge() == -kaonFit->charge() ) {

           // check phi tag
           const HepLorentzVector &kv1 = kaonFit->lorentzMomentum();
           const HepLorentzVector &kv2 = kaonFit2->lorentzMomentum();

           HepLorentzVector kk = kv1 + kv2;


           double mm = sqrt(fabs( pow(kk.e(),2) - pow(kk.px(),2) - pow(kk.py(),2) - pow(kk.pz(),2) ));
//           double mm = sqrt(fabs(pow( (kaonFit->energy()+kaonFit2->energy()) ,2 ) - pow((kaonFit->px()+kaonFit2->px()),2) 
//                               - pow((kaonFit->py()+kaonFit2->py()),2) - pow((kaonFit->pz()+kaonFit2->pz()),2)) );


           if( fabs( mm-1.019461 ) < 0.5 ) {
               good_phi = 1;
           }
           if( fabs( mm-1.019461 ) < fabs( best_tag-1.019461) ) {
               k1 = kaonFit;
               k2 = kaonFit2;
               best_tag = mm;
               kEOP[0] = trackItr->elecId().eOverP();
               kEOP[1] = trackItr2->elecId().eOverP();
           }
        }
      }
   }

   if(!good_phi)
      return ActionBase::kFailed;



   kPE[0] = k1->energy();
   kPPx[0] = k1->px();
   kPPy[0] = k1->py();
   kPPz[0] = k1->pz();
   kCharge[0] = k1->charge();

   kPE[1] = k2->energy();
   kPPx[1] = k2->px();
   kPPy[1] = k2->py();
   kPPz[1] = k2->pz();
   kCharge[1] = k2->charge();


   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;
         ++trackItr )
   {
       if(trackItr->kaonFit() == k1 || trackItr->kaonFit() == k2)
         continue;

       if( isGoodPion( *trackItr ) && numTrack < (kMaxTrack-2)) {
          FAItem<TDKinematicFit> pionFit = trackItr->pionFit();
          pion_tracks.push_back(pionFit);
          PE[numTrack] = pionFit->energy();
          PPx[numTrack] = pionFit->px();
          PPy[numTrack] = pionFit->py();
          PPz[numTrack] = pionFit->pz();
          Charge[numTrack] = pionFit->charge();
          EOP[numTrack] = trackItr->elecId().eOverP();
          MuDepth[numTrack] = trackItr->muonId().depth();

          numTrack++;  // number of good pions
       }
   }


   if( pion_tracks.size()<2 )
      return ActionBase::kFailed;



   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;
         ++trackItr )
   {
      if(trackItr->kaonFit() == k1 || trackItr->kaonFit() == k2)
         continue;
      FAItem<TDKinematicFit> pionFit = trackItr->pionFit();

      for ( FATable< NavTrack >::const_iterator trackItr2 = trackItr+1;
            trackItr2 != trackTableEnd ;
            ++trackItr2 )
      {
          if(trackItr2->kaonFit() == k1 || trackItr2->kaonFit() == k2)
             continue;
          FAItem<TDKinematicFit> pionFit2 = trackItr2->pionFit();


          if( isGoodPion( *trackItr ) && isGoodPion( *trackItr2 ) && pionFit->charge() == -pionFit2->charge() ) {

            const HepLorentzVector &pipikk1 = pionFit->lorentzMomentum();
            const HepLorentzVector &pipikk2 = pionFit2->lorentzMomentum();
            const HepLorentzVector &pipikk3 = k1->lorentzMomentum();
            const HepLorentzVector &pipikk4 = k2->lorentzMomentum();

            HepLorentzVector pipikk = pipikk1 + pipikk2 + pipikk3 + pipikk4;

            double m_pipikk = sqrt(fabs( pow(pipikk.e(),2) - pow(pipikk.px(),2)
                                       - pow(pipikk.py(),2) - pow(pipikk.pz(),2) ));
            if(kEOP[0]<0.85 && kEOP[1]<0.85 && trackItr->elecId().eOverP()<0.85 && trackItr2->elecId().eOverP()<0.85)
              h_mpipikk->fill(m_pipikk);
          }
      }
   }



   // Fill ntuple
   ntVal[k_kk_K1_E] = kPE[0];
   ntVal[k_kk_K1_Px] = kPPx[0];
   ntVal[k_kk_K1_Py] = kPPy[0];
   ntVal[k_kk_K1_Pz] = kPPz[0];
   ntVal[k_kk_K2_E] = kPE[1];
   ntVal[k_kk_K2_Px] = kPPx[1];
   ntVal[k_kk_K2_Py] = kPPy[1];
   ntVal[k_kk_K2_Pz] = kPPz[1];

   ntVal[k_pipi_Pi1_E] = PE[0];
   ntVal[k_pipi_Pi1_Px] = PPx[0];
   ntVal[k_pipi_Pi1_Py] = PPy[0];
   ntVal[k_pipi_Pi1_Pz] = PPz[0];
   ntVal[k_pipi_Pi2_E] = PE[1];
   ntVal[k_pipi_Pi2_Px] = PPx[1];
   ntVal[k_pipi_Pi2_Py] = PPy[1];
   ntVal[k_pipi_Pi2_Pz] = PPz[1];
   ntVal[k_pipi_Pi3_E] = PE[2];
   ntVal[k_pipi_Pi3_Px] = PPx[2];
   ntVal[k_pipi_Pi3_Py] = PPy[2];
   ntVal[k_pipi_Pi3_Pz] = PPz[2];
   ntVal[k_pipi_Pi4_E] = PE[3];
   ntVal[k_pipi_Pi4_Px] = PPx[3];
   ntVal[k_pipi_Pi4_Py] = PPy[3];
   ntVal[k_pipi_Pi4_Pz] = PPz[3];
   ntVal[k_pipi_Pi5_E] = PE[4];
   ntVal[k_pipi_Pi5_Px] = PPx[4];
   ntVal[k_pipi_Pi5_Py] = PPy[4];
   ntVal[k_pipi_Pi5_Pz] = PPz[4];
   ntVal[k_pipi_Pi6_E] = PE[5];
   ntVal[k_pipi_Pi6_Px] = PPx[5];
   ntVal[k_pipi_Pi6_Py] = PPy[5];
   ntVal[k_pipi_Pi6_Pz] = PPz[5];
   ntVal[k_pipi_Pi7_E] = PE[6];
   ntVal[k_pipi_Pi7_Px] = PPx[6];
   ntVal[k_pipi_Pi7_Py] = PPy[6];
   ntVal[k_pipi_Pi7_Pz] = PPz[6];
   ntVal[k_pipi_Pi8_E] = PE[7];
   ntVal[k_pipi_Pi8_Px] = PPx[7];
   ntVal[k_pipi_Pi8_Py] = PPy[7];
   ntVal[k_pipi_Pi8_Pz] = PPz[7];

   ntVal[k_charge_1] = Charge[0];
   ntVal[k_charge_2] = Charge[1];
   ntVal[k_charge_3] = Charge[2];
   ntVal[k_charge_4] = Charge[3];
   ntVal[k_charge_5] = Charge[4];
   ntVal[k_charge_6] = Charge[5];
   ntVal[k_charge_7] = Charge[6];
   ntVal[k_charge_8] = Charge[7];

   ntVal[k_kcharge_1] = kCharge[0];
   ntVal[k_kcharge_2] = kCharge[1];

   ntVal[k_EP_1] = EOP[0];
   ntVal[k_EP_2] = EOP[1];
   ntVal[k_EP_3] = EOP[2];
   ntVal[k_EP_4] = EOP[3];
   ntVal[k_EP_5] = EOP[4];
   ntVal[k_EP_6] = EOP[5];
   ntVal[k_EP_7] = EOP[6];
   ntVal[k_EP_8] = EOP[7];

   ntVal[k_kEP_1] = kEOP[0];
   ntVal[k_kEP_2] = kEOP[1];

   ntVal[k_mudepth_1] = MuDepth[0];
   ntVal[k_mudepth_2] = MuDepth[1];
   ntVal[k_mudepth_3] = MuDepth[2];
   ntVal[k_mudepth_4] = MuDepth[3];
   ntVal[k_mudepth_5] = MuDepth[4];
   ntVal[k_mudepth_6] = MuDepth[5];
   ntVal[k_mudepth_7] = MuDepth[6];
   ntVal[k_mudepth_8] = MuDepth[7];



   m_LEGammaNt->fill(ntVal);
   

   //cerr << "ntuple: " << ntVal[k_Jpsi_VtxChisq] << " " << ntVal[k_Jpsi_FitChisq] << endl;
       
   return ActionBase::kPassed;
}


ActionBase::ActionResult
InclusivePiPiPhiProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   FAItem< BeamSpot > spot;
   extract( iFrame.record( Stream::kBeginRun ), spot );

   if(spot.valid()) {
      m_beam_x = spot->center().x();
      m_beam_y = spot->center().y();
      m_beam_z = spot->center().z();
   } else {
      m_beam_x = 0.;
      m_beam_y = 0.;
      m_beam_z = 0.;
   }     

   report( DEBUG, kFacilityString ) <<
      "BeamSpot x,y,z = " <<
      m_beam_x << ", " <<
      m_beam_y << ", " <<
      m_beam_z << endl ;


   FAItem< BeamEnergy > beam_energy;
   extract( iFrame.record( Stream::kBeginRun ), beam_energy );

   FAItem< MagneticField > cleoBField;
   extract( iFrame.record( Stream::kBeginRun ), cleoBField );


   cerr << "BeamSpot x,y,z = " <<
      m_beam_x << ", " <<
      m_beam_y << ", " <<
      m_beam_z << endl ;
   cerr << cleoBField->BField() <<  " " << beam_energy->value() << endl;

   FitEvtSettings &settings(FitEvtSettings::instance());
   settings.setField(*cleoBField);
   settings.setBeamSpot(*spot);
   settings.setLorVecCM( beam_energy->value() ); 
   //settings.setLorVecCM( kCME/2. ); 


   return ActionBase::kPassed;
}


/*
ActionBase::ActionResult
InclusivePiPiPhiProc::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/


// return 1 if they are they same kinematical object
int InclusivePiPiPhiProc::CompareKins( FAItem<KTKinematicData>  &k1, 
			       FAItem<KTKinematicData>  &k2) const
{
   if( (k1->position()==k2->position()) 
       && (k1->momentum()==k2->momentum()) )
    return 1;
  else 
    return 0;

}
/*
// return 1 if they are they same kinematical object
int InclusivePiPiPhiProc::CompareKins( FAItem<TDKinematicFit>  &k1, 
			       FAItem<TDKinematicFit>  &k2) const
{
   if( (k1->position()==k2->position()) 
       && (k1->momentum()==k2->momentum()) )
    return 1;
  else 
    return 0;

}
*/
// return 1 if they are they same kinematical object
int InclusivePiPiPhiProc::CompareKins( FAItem<TDKinematicFit>  k1, 
			       FAItem<TDKinematicFit>  k2) const
{
   if( (k1->position()==k2->position()) 
       && (k1->momentum()==k2->momentum()) )
    return 1;
  else 
    return 0;

}

double InclusivePiPiPhiProc::calcDOCA( double iD,
		       	     double iPhi )
{
   double dx ( -iD*sin(iPhi) - m_beam_x ) ;
   double dy (  iD*cos(iPhi) - m_beam_y ) ;
   double doca = sqrt( dx*dx + dy*dy ) ;

   if(isnan(doca))
      return -2.;
   else if(doca < 1e-5)
      return 1e-5;
   else
      return doca;
}


//
// const member functions
//

//
// static member functions
//
