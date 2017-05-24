// -*- C++ -*-
//
// Package:     Bin20_JpsiPiPiProc
// Module:      Bin20_JpsiPiPiProc
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

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Bin20_JpsiPiPiProc/Bin20_JpsiPiPiProc.h"
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

#include "Navigation/NavPi0ToGG.h" 
#include "Navigation/NavEtaToGG.h" 
#include "Navigation/NavTkShMatch.h"
#include "BeamEnergy/BeamEnergy.h"
#include "BeamSpot/BeamSpot.h"
#include <PhotonDecays/PhdPi0.h> 

#include <CleoDB/DBEventHeader.h> 

// Histogram/Ntuple include files
#include "HistogramInterface/HIHist1D.h"
#include "HistogramInterface/HINtupleVarNames.h"
#include "HistogramInterface/HINtupleArray.h"

#include <FitEvt/FitEvt.h>
#include <FitEvt/FitEvtSettings.h>

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
//ofstream *outf;

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.Bin20_JpsiPiPiProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

/*
//make proton selection
static DABoolean is_proton ( const NavTrack &the_track )
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

   return ( ( DL_ppi < 0. ) && ( DL_pk < 0. ) );
}
*/

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
   
   // require 3 sigma consistency for low-momentum tracks
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


   return ( ( DL_pik < -9. ) && ( DL_pip < -9. ) );
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

   // require 3 sigma consistency
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


   return ( ( DL_kpi < -9. ) && ( DL_kp < -9. ) );
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
Bin20_JpsiPiPiProc::Bin20_JpsiPiPiProc( void )               // anal1
   : Processor( "Bin20_JpsiPiPiProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Bin20_JpsiPiPiProc::event,    Stream::kEvent );
   bind( &Bin20_JpsiPiPiProc::beginRun, Stream::kBeginRun );
   //bind( &Bin20_JpsiPiPiProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

Bin20_JpsiPiPiProc::~Bin20_JpsiPiPiProc()                    // anal5
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
Bin20_JpsiPiPiProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)


   m_beam_x = 0.;
   m_beam_y = 0.;
   m_beam_z = 0.;

   //   outf = new ofstream("pis.out")
}

// -------------------- terminate method ----------------------------
void
Bin20_JpsiPiPiProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------

enum { k_NShower, k_NTrack, k_TCharge, k_NPi0, k_NEta,
       k_Energy_1, k_Barrel_1, k_Theta_1, k_Phi_1,
       k_Energy_2, k_Barrel_2, k_Theta_2, k_Phi_2,
       k_Energy_3, k_Barrel_3, k_Theta_3, k_Phi_3,
       k_Energy_4, k_Barrel_4, k_Theta_4, k_Phi_4,
       k_Energy_5, k_Barrel_5, k_Theta_5, k_Phi_5,
       k_Energy_6, k_Barrel_6, k_Theta_6, k_Phi_6,

       k_TE_1, k_Px_1, k_Py_1, k_Pz_1, 
       k_ETE_1, k_EPx_1, k_EPy_1, k_EPz_1, 
       k_MuTE_1, k_MuPx_1, k_MuPy_1, k_MuPz_1, 
         k_Chg_1, k_DOCA_1, k_Z0_1, k_ReChiSq_1, k_EID_1, k_MuID_1,
         k_LLpi_1, k_LLk_1, k_LLp_1, k_SigPi_1, k_SigK_1, k_SigP_1,
         k_DL_pip_1, k_DL_pik_1, 
         k_EP_1, k_DptMu_1,
       k_TE_2, k_Px_2, k_Py_2, k_Pz_2, 
       k_ETE_2, k_EPx_2, k_EPy_2, k_EPz_2, 
       k_MuTE_2, k_MuPx_2, k_MuPy_2, k_MuPz_2, 
         k_Chg_2, k_DOCA_2, k_Z0_2, k_ReChiSq_2, k_EID_2, k_MuID_2,
         k_LLpi_2, k_LLk_2, k_LLp_2, k_SigPi_2, k_SigK_2, k_SigP_2,
         k_DL_pip_2, k_DL_pik_2, 
         k_EP_2, k_DptMu_2,
       k_TE_3, k_Px_3, k_Py_3, k_Pz_3, 
       k_ETE_3, k_EPx_3, k_EPy_3, k_EPz_3, 
       k_MuTE_3, k_MuPx_3, k_MuPy_3, k_MuPz_3, 
         k_Chg_3, k_DOCA_3, k_Z0_3, k_ReChiSq_3, k_EID_3, k_MuID_3,
         k_LLpi_3, k_LLk_3, k_LLp_3, k_SigPi_3, k_SigK_3, k_SigP_3,
         k_DL_pip_3, k_DL_pik_3, 
         k_EP_3, k_DptMu_3,
       k_TE_4, k_Px_4, k_Py_4, k_Pz_4, 
       k_ETE_4, k_EPx_4, k_EPy_4, k_EPz_4, 
       k_MuTE_4, k_MuPx_4, k_MuPy_4, k_MuPz_4, 
         k_Chg_4, k_DOCA_4, k_Z0_4, k_ReChiSq_4, k_EID_4, k_MuID_4,
         k_LLpi_4, k_LLk_4, k_LLp_4, k_SigPi_4, k_SigK_4, k_SigP_4,
         k_DL_pip_4, k_DL_pik_4, 
         k_EP_4, k_DptMu_4,

       k_NeutE,

       k_RunNum, k_EvtNum,     

       k_pipi_Jpsi_E, k_pipi_Jpsi_Px, k_pipi_Jpsi_Py, k_pipi_Jpsi_Pz, 
       k_pipi_Jpsi_VtxChisq, k_pipi_Jpsi_FitChisq, 
       k_pipi_Psip_VtxChisq, k_pipi_Psip_FitChisq, 
       k_pipi_E, k_pipi_Px, k_pipi_Py, k_pipi_Pz, 
       k_pipi_VtxChisq, k_pipi_FitChisq, 

       kNumVars };


void
Bin20_JpsiPiPiProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here
   HINtupleVarNames ntNames(kNumVars);

   ntNames.addVar(k_NShower, "NShower");
   ntNames.addVar(k_NTrack, "NTrack");
   ntNames.addVar(k_TCharge, "TCharge");
   ntNames.addVar(k_NPi0, "NPi0");
   ntNames.addVar(k_NEta, "NEta");

   ntNames.addVar(k_Energy_1, "E1");
   ntNames.addVar(k_Barrel_1, "Barrel1");
   ntNames.addVar(k_Theta_1, "Theta1");
   ntNames.addVar(k_Phi_1, "Phi1");
   ntNames.addVar(k_Energy_2, "E2");
   ntNames.addVar(k_Barrel_2, "Barrel2");
   ntNames.addVar(k_Theta_2, "Theta2");
   ntNames.addVar(k_Phi_2, "Phi2");
   ntNames.addVar(k_Energy_3, "E3");
   ntNames.addVar(k_Barrel_3, "Barrel3");
   ntNames.addVar(k_Theta_3, "Theta3");
   ntNames.addVar(k_Phi_3, "Phi3");
   ntNames.addVar(k_Energy_4, "E4");
   ntNames.addVar(k_Barrel_4, "Barrel4");
   ntNames.addVar(k_Theta_4, "Theta4");
   ntNames.addVar(k_Phi_4, "Phi4");
   ntNames.addVar(k_Energy_5, "E5");
   ntNames.addVar(k_Barrel_5, "Barrel5");
   ntNames.addVar(k_Theta_5, "Theta5");
   ntNames.addVar(k_Phi_5, "Phi5");
   ntNames.addVar(k_Energy_6, "E6");
   ntNames.addVar(k_Barrel_6, "Barrel6");
   ntNames.addVar(k_Theta_6, "Theta6");
   ntNames.addVar(k_Phi_6, "Phi6");


   // track data
   ntNames.addVar(k_TE_1, "TE1");
   ntNames.addVar(k_Px_1, "Px1");
   ntNames.addVar(k_Py_1, "Py1");
   ntNames.addVar(k_Pz_1, "Pz1");
   ntNames.addVar(k_ETE_1, "ETE1");
   ntNames.addVar(k_EPx_1, "EPx1");
   ntNames.addVar(k_EPy_1, "EPy1");
   ntNames.addVar(k_EPz_1, "EPz1");
   ntNames.addVar(k_MuTE_1, "MuTE1");
   ntNames.addVar(k_MuPx_1, "MuPx1");
   ntNames.addVar(k_MuPy_1, "MuPy1");
   ntNames.addVar(k_MuPz_1, "MuPz1");
   ntNames.addVar(k_Chg_1, "Chg1"); 
   ntNames.addVar(k_DOCA_1, "DOCA1");
   ntNames.addVar(k_Z0_1, "Z01");
   ntNames.addVar(k_ReChiSq_1, "Rchisq1");
   ntNames.addVar(k_EID_1, "EID1");
   ntNames.addVar(k_MuID_1, "MuID1");
   ntNames.addVar(k_LLpi_1, "LLpi1");
   ntNames.addVar(k_LLk_1, "LLk1");
   ntNames.addVar(k_LLp_1, "LLp1");
   ntNames.addVar(k_SigPi_1, "SigPi1");
   ntNames.addVar(k_SigK_1, "SigK1");
   ntNames.addVar(k_SigP_1, "SigP1");
   ntNames.addVar(k_DL_pip_1, "DLppi1");
   ntNames.addVar(k_DL_pik_1, "DLpk1");
   ntNames.addVar(k_DptMu_1, "DptMu1");
   ntNames.addVar(k_EP_1, "EP1");
   ntNames.addVar(k_TE_2, "TE2"); 
   ntNames.addVar(k_Px_2, "Px2"); 
   ntNames.addVar(k_Py_2, "Py2"); 
   ntNames.addVar(k_Pz_2, "Pz2"); 
   ntNames.addVar(k_ETE_2, "ETE2");
   ntNames.addVar(k_EPx_2, "EPx2");
   ntNames.addVar(k_EPy_2, "EPy2");
   ntNames.addVar(k_EPz_2, "EPz2");
   ntNames.addVar(k_MuTE_2, "MuTE2");
   ntNames.addVar(k_MuPx_2, "MuPx2");
   ntNames.addVar(k_MuPy_2, "MuPy2");
   ntNames.addVar(k_MuPz_2, "MuPz2");
   ntNames.addVar(k_Chg_2, "Chg2"); 
   ntNames.addVar(k_DOCA_2, "DOCA2");
   ntNames.addVar(k_Z0_2, "Z02");
   ntNames.addVar(k_ReChiSq_2, "Rchisq2");
   ntNames.addVar(k_EID_2, "EID2");
   ntNames.addVar(k_MuID_2, "MuID2");
   ntNames.addVar(k_LLpi_2, "LLpi2");
   ntNames.addVar(k_LLk_2, "LLk2");
   ntNames.addVar(k_LLp_2, "LLp2");
   ntNames.addVar(k_SigPi_2, "SigPi2");
   ntNames.addVar(k_SigK_2, "SigK2");
   ntNames.addVar(k_SigP_2, "SigP2");
   ntNames.addVar(k_DL_pip_2, "DLppi2");
   ntNames.addVar(k_DL_pik_2, "DLpk2");
   ntNames.addVar(k_DptMu_2, "DptMu2");
   ntNames.addVar(k_EP_2, "EP2");
   ntNames.addVar(k_TE_3, "TE3");
   ntNames.addVar(k_Px_3, "Px3");
   ntNames.addVar(k_Py_3, "Py3");
   ntNames.addVar(k_Pz_3, "Pz3");
   ntNames.addVar(k_ETE_3, "ETE3");
   ntNames.addVar(k_EPx_3, "EPx3");
   ntNames.addVar(k_EPy_3, "EPy3");
   ntNames.addVar(k_EPz_3, "EPz3");
   ntNames.addVar(k_MuTE_3, "MuTE3");
   ntNames.addVar(k_MuPx_3, "MuPx3");
   ntNames.addVar(k_MuPy_3, "MuPy3");
   ntNames.addVar(k_MuPz_3, "MuPz3");
   ntNames.addVar(k_Chg_3, "Chg3"); 
   ntNames.addVar(k_DOCA_3, "DOCA3");
   ntNames.addVar(k_Z0_3, "Z03");
   ntNames.addVar(k_ReChiSq_3, "Rchisq3");
   ntNames.addVar(k_EID_3, "EID3");
   ntNames.addVar(k_MuID_3, "MuID3");
   ntNames.addVar(k_LLpi_3, "LLpi3");
   ntNames.addVar(k_LLk_3, "LLk3");
   ntNames.addVar(k_LLp_3, "LLp3");
   ntNames.addVar(k_SigPi_3, "SigPi3");
   ntNames.addVar(k_SigK_3, "SigK3");
   ntNames.addVar(k_SigP_3, "SigP3");
   ntNames.addVar(k_DL_pip_3, "DLppi3");
   ntNames.addVar(k_DL_pik_3, "DLpk3");
   ntNames.addVar(k_DptMu_3, "DptMu3");
   ntNames.addVar(k_EP_3, "EP3");
   ntNames.addVar(k_TE_4, "TE4"); 
   ntNames.addVar(k_Px_4, "Px4"); 
   ntNames.addVar(k_Py_4, "Py4"); 
   ntNames.addVar(k_Pz_4, "Pz4"); 
   ntNames.addVar(k_ETE_4, "ETE4");
   ntNames.addVar(k_EPx_4, "EPx4");
   ntNames.addVar(k_EPy_4, "EPy4");
   ntNames.addVar(k_EPz_4, "EPz4");
   ntNames.addVar(k_MuTE_4, "MuTE4");
   ntNames.addVar(k_MuPx_4, "MuPx4");
   ntNames.addVar(k_MuPy_4, "MuPy4");
   ntNames.addVar(k_MuPz_4, "MuPz4");
   ntNames.addVar(k_Chg_4, "Chg4"); 
   ntNames.addVar(k_DOCA_4, "DOCA4");
   ntNames.addVar(k_Z0_4, "Z04");
   ntNames.addVar(k_ReChiSq_4, "Rchisq4");
   ntNames.addVar(k_EID_4, "EID4");
   ntNames.addVar(k_MuID_4, "MuID4");
   ntNames.addVar(k_LLpi_4, "LLpi4");
   ntNames.addVar(k_LLk_4, "LLk4");
   ntNames.addVar(k_LLp_4, "LLp4");
   ntNames.addVar(k_SigPi_4, "SigPi4");
   ntNames.addVar(k_SigK_4, "SigK4");
   ntNames.addVar(k_SigP_4, "SigP4");
   ntNames.addVar(k_DL_pip_4, "DLppi4");
   ntNames.addVar(k_DL_pik_4, "DLpk4");
   ntNames.addVar(k_EP_4, "EP4");
   ntNames.addVar(k_DptMu_4, "DptMu4");

   ntNames.addVar(k_RunNum, "RunNum");
   ntNames.addVar(k_EvtNum, "EvtNum");

   ntNames.addVar(k_NeutE, "NeutE");


   ntNames.addVar(k_pipi_Jpsi_E, "JpsiE");
   ntNames.addVar(k_pipi_Jpsi_Px, "JpsiPx");
   ntNames.addVar(k_pipi_Jpsi_Py, "JpsiPy");
   ntNames.addVar(k_pipi_Jpsi_Pz, "JpsiPz");
   ntNames.addVar(k_pipi_E, "PipiE");
   ntNames.addVar(k_pipi_Px, "PipiPx");
   ntNames.addVar(k_pipi_Py, "PipiPy");
   ntNames.addVar(k_pipi_Pz, "PipiPz");

   ntNames.addVar(k_pipi_VtxChisq, "PipiVtx");
   ntNames.addVar(k_pipi_FitChisq, "PipiFit");
   ntNames.addVar(k_pipi_Jpsi_VtxChisq, "JpsiVtx");
   ntNames.addVar(k_pipi_Jpsi_FitChisq, "JpsiFit");
   ntNames.addVar(k_pipi_Psip_VtxChisq, "PsipVtx");
   ntNames.addVar(k_pipi_Psip_FitChisq, "PsipFit");



   //m_LEGammaNt = iHistoManager.ntuple( 25, "LE Gammas",
   //kNumVars, 50000, ntNames.names());

   //h_mjpsi = iHistoManager.histogram(1, "mjpsi", 800, 2.5, 3.3);

   h_mpipi = iHistoManager.histogram(1, "mpipi", 200, 0., 4.);
   h_mpipi4 = iHistoManager.histogram(2, "mpipi4", 200, 0., 4.);
   h_mpipirec = iHistoManager.histogram(3, "mpipirec",  100, 3.05, 3.15);   
   h_pion_mudepth = iHistoManager.histogram(4, "pion_mudepth", 75, 0., 15.);   

   h_pion_p = iHistoManager.histogram(5, "pion momentum", 150, 0., 3.);
   h_kaon_p = iHistoManager.histogram(6, "kaon momentum", 150, 0., 3.);
   h_proton_p = iHistoManager.histogram(7, "proton momentum", 150, 0., 3.);
   h_pion_p_endcap = iHistoManager.histogram(11, "pion momentum", 150, 0., 3.);
   h_kaon_p_endcap = iHistoManager.histogram(12, "kaon momentum", 150, 0., 3.);
   h_proton_p_endcap = iHistoManager.histogram(13, "proton momentum", 150, 0., 3.);

   h_pion_mcpion_p = iHistoManager.histogram(21, "pion momentum", 150, 0., 3.);
   h_pion_mckaon_p = iHistoManager.histogram(22, "pion momentum", 150, 0., 3.);
   h_pion_mcproton_p = iHistoManager.histogram(23, "pion momentum", 150, 0., 3.);
   h_kaon_mcpion_p = iHistoManager.histogram(24, "kaon momentum", 150, 0., 3.);
   h_kaon_mckaon_p = iHistoManager.histogram(25, "kaon momentum", 150, 0., 3.);
   h_kaon_mcproton_p = iHistoManager.histogram(26, "kaon momentum", 150, 0., 3.);
   h_proton_mcpion_p = iHistoManager.histogram(27, "proton momentum", 150, 0., 3.);
   h_proton_mckaon_p = iHistoManager.histogram(28, "proton momentum", 150, 0., 3.);
   h_proton_mcproton_p = iHistoManager.histogram(29, "proton momentum", 150, 0., 3.);
   h_pion_mcmuon_p = iHistoManager.histogram(30, "pion momentum", 150, 0., 3.);


   h_pion_costh = iHistoManager.histogram(51, "pion cos theta", 100, 0., 1.);
   h_kaon_costh = iHistoManager.histogram(52, "kaon cos theta", 100, 0., 1.);
   h_proton_costh = iHistoManager.histogram(53, "proton cos theta", 100, 0., 1.);

   h_pion_phi = iHistoManager.histogram(55, "pion phi", 90, -180., 180.);
   h_pion_p_costh = iHistoManager.histogram(56, "pion p v. costh", 100, 0., 2., 100, 0., 1.);
   h_pion_p_phi = iHistoManager.histogram(57, "pion p v. phi", 100, 0., 2., 90, -180., 180.);
   h_pion_costh_phi = iHistoManager.histogram(58, "pion costh v. phi", 100, 0., 1., 90, -180., 180.);

   h_pion_eop = iHistoManager.histogram(500, "pion E/p", 2000, 0., 2);

   h_pip_eop1 = iHistoManager.histogram(501, "pi+ E/p, p=0-20 MeV", 2000, 0., 2);
   h_pip_eop2 = iHistoManager.histogram(502, "pi+ E/p, p=20-40 MeV", 2000, 0., 2);
   h_pip_eop3 = iHistoManager.histogram(503, "pi+ E/p, p=40-60 MeV", 2000, 0., 2);
   h_pip_eop4 = iHistoManager.histogram(504, "pi+ E/p, p=60-80 MeV", 2000, 0., 2);
   h_pip_eop5 = iHistoManager.histogram(505, "pi+ E/p, p=80-100 MeV", 2000, 0., 2);
   h_pip_eop6 = iHistoManager.histogram(506, "pi+ E/p, p=100-120 MeV", 2000, 0., 2);
   h_pip_eop7 = iHistoManager.histogram(507, "pi+ E/p, p=120-140 MeV", 2000, 0., 2);
   h_pip_eop8 = iHistoManager.histogram(508, "pi+ E/p, p=140-160 MeV", 2000, 0., 2);
   h_pip_eop9 = iHistoManager.histogram(509, "pi+ E/p, p=160-180 MeV", 2000, 0., 2);
   h_pip_eop10 = iHistoManager.histogram(510, "pi+ E/p, p=180-200 MeV", 2000, 0., 2);
   h_pip_eop11 = iHistoManager.histogram(511, "pi+ E/p, p=200-220 MeV", 2000, 0., 2);
   h_pip_eop12 = iHistoManager.histogram(512, "pi+ E/p, p=220-240 MeV", 2000, 0., 2);
   h_pip_eop13 = iHistoManager.histogram(513, "pi+ E/p, p=240-260 MeV", 2000, 0., 2);
   h_pip_eop14 = iHistoManager.histogram(514, "pi+ E/p, p=260-280 MeV", 2000, 0., 2);
   h_pip_eop15 = iHistoManager.histogram(515, "pi+ E/p, p=280-300 MeV", 2000, 0., 2);
   h_pip_eop16 = iHistoManager.histogram(516, "pi+ E/p, p=300-800 MeV", 2000, 0., 2);
   h_pip_eop17 = iHistoManager.histogram(517, "pi+ E/p, p=320-850 MeV", 2000, 0., 2);
   h_pip_eop18 = iHistoManager.histogram(518, "pi+ E/p, p=340-900 MeV", 2000, 0., 2);
   h_pip_eop19 = iHistoManager.histogram(519, "pi+ E/p, p=360-950 MeV", 2000, 0., 2);
   h_pip_eop20 = iHistoManager.histogram(520, "pi+ E/p, p=380-400 MeV", 2000, 0., 2);
   h_pip_eop21 = iHistoManager.histogram(521, "pi+ E/p, p=400-420 MeV", 2000, 0., 2);
   h_pip_eop22 = iHistoManager.histogram(522, "pi+ E/p, p=420-440 MeV", 2000, 0., 2);
   h_pip_eop23 = iHistoManager.histogram(523, "pi+ E/p, p=440-460 MeV", 2000, 0., 2);
   h_pip_eop24 = iHistoManager.histogram(524, "pi+ E/p, p=460-480 MeV", 2000, 0., 2);
   h_pip_eop25 = iHistoManager.histogram(525, "pi+ E/p, p=480-500 MeV", 2000, 0., 2);
   h_pip_eop26 = iHistoManager.histogram(526, "pi+ E/p, p=500-520 MeV", 2000, 0., 2);
   h_pip_eop27 = iHistoManager.histogram(527, "pi+ E/p, p=520-540 MeV", 2000, 0., 2);
   h_pip_eop28 = iHistoManager.histogram(528, "pi+ E/p, p=540-560 MeV", 2000, 0., 2);
   h_pip_eop29 = iHistoManager.histogram(529, "pi+ E/p, p=560-580 MeV", 2000, 0., 2);
   h_pip_eop30 = iHistoManager.histogram(530, "pi+ E/p, p=580-600 MeV", 2000, 0., 2);
   h_pip_eop31 = iHistoManager.histogram(531, "pi+ E/p, p=600-620 MeV", 2000, 0., 2);
   h_pip_eop32 = iHistoManager.histogram(532, "pi+ E/p, p=620-640 MeV", 2000, 0., 2);
   h_pip_eop33 = iHistoManager.histogram(533, "pi+ E/p, p=640-660 MeV", 2000, 0., 2);
   h_pip_eop34 = iHistoManager.histogram(534, "pi+ E/p, p=660-680 MeV", 2000, 0., 2);
   h_pip_eop35 = iHistoManager.histogram(535, "pi+ E/p, p=680-700 MeV", 2000, 0., 2);
   h_pip_eop36 = iHistoManager.histogram(536, "pi+ E/p, p=700-720 MeV", 2000, 0., 2);
   h_pip_eop37 = iHistoManager.histogram(537, "pi+ E/p, p=720-740 MeV", 2000, 0., 2);
   h_pip_eop38 = iHistoManager.histogram(538, "pi+ E/p, p=740-760 MeV", 2000, 0., 2);
   h_pip_eop39 = iHistoManager.histogram(539, "pi+ E/p, p=760-780 MeV", 2000, 0., 2);
   h_pip_eop40 = iHistoManager.histogram(540, "pi+ E/p, p=780-800 MeV", 2000, 0., 2);
   h_pip_eop41 = iHistoManager.histogram(541, "pi+ E/p, p=800-820 MeV", 2000, 0., 2);
   h_pip_eop42 = iHistoManager.histogram(542, "pi+ E/p, p=820-840 MeV", 2000, 0., 2);
   h_pip_eop43 = iHistoManager.histogram(543, "pi+ E/p, p=840-860 MeV", 2000, 0., 2);
   h_pip_eop44 = iHistoManager.histogram(544, "pi+ E/p, p=860-880 MeV", 2000, 0., 2);
   h_pip_eop45 = iHistoManager.histogram(545, "pi+ E/p, p=880-900 MeV", 2000, 0., 2);
   h_pip_eop46 = iHistoManager.histogram(546, "pi+ E/p, p=900-920 MeV", 2000, 0., 2);
   h_pip_eop47 = iHistoManager.histogram(547, "pi+ E/p, p=920-940 MeV", 2000, 0., 2);
   h_pip_eop48 = iHistoManager.histogram(548, "pi+ E/p, p=940-960 MeV", 2000, 0., 2);
   h_pip_eop49 = iHistoManager.histogram(549, "pi+ E/p, p=960-980 MeV", 2000, 0., 2);
   h_pip_eop50 = iHistoManager.histogram(550, "pi+ E/p, p=980-1000 MeV", 2000, 0., 2);
   h_pip_eop51 = iHistoManager.histogram(551, "pi+ E/p, p=1000-1020 MeV", 2000, 0., 2);
   h_pip_eop52 = iHistoManager.histogram(552, "pi+ E/p, p=1020-1040 MeV", 2000, 0., 2);
   h_pip_eop53 = iHistoManager.histogram(553, "pi+ E/p, p=1040-1060 MeV", 2000, 0., 2);
   h_pip_eop54 = iHistoManager.histogram(554, "pi+ E/p, p=1060-1080 MeV", 2000, 0., 2);
   h_pip_eop55 = iHistoManager.histogram(555, "pi+ E/p, p=1080-1100 MeV", 2000, 0., 2);
   h_pip_eop56 = iHistoManager.histogram(556, "pi+ E/p, p=1100-1120 MeV", 2000, 0., 2);
   h_pip_eop57 = iHistoManager.histogram(557, "pi+ E/p, p=1120-1140 MeV", 2000, 0., 2);
   h_pip_eop58 = iHistoManager.histogram(558, "pi+ E/p, p=1140-1160 MeV", 2000, 0., 2);
   h_pip_eop59 = iHistoManager.histogram(559, "pi+ E/p, p=1160-1180 MeV", 2000, 0., 2);
   h_pip_eop60 = iHistoManager.histogram(560, "pi+ E/p, p=1180-1200 MeV", 2000, 0., 2);
   h_pip_eop61 = iHistoManager.histogram(561, "pi+ E/p, p=1200-1220 MeV", 2000, 0., 2);
   h_pip_eop62 = iHistoManager.histogram(562, "pi+ E/p, p=1220-1240 MeV", 2000, 0., 2);
   h_pip_eop63 = iHistoManager.histogram(563, "pi+ E/p, p=1240-1260 MeV", 2000, 0., 2);
   h_pip_eop64 = iHistoManager.histogram(564, "pi+ E/p, p=1260-1280 MeV", 2000, 0., 2);
   h_pip_eop65 = iHistoManager.histogram(565, "pi+ E/p, p=1280-1300 MeV", 2000, 0., 2);
   h_pip_eop66 = iHistoManager.histogram(566, "pi+ E/p, p=1300-1320 MeV", 2000, 0., 2);
   h_pip_eop67 = iHistoManager.histogram(567, "pi+ E/p, p=1320-1340 MeV", 2000, 0., 2);
   h_pip_eop68 = iHistoManager.histogram(568, "pi+ E/p, p=1340-1360 MeV", 2000, 0., 2);
   h_pip_eop69 = iHistoManager.histogram(569, "pi+ E/p, p=1360-1380 MeV", 2000, 0., 2);
   h_pip_eop70 = iHistoManager.histogram(570, "pi+ E/p, p=1380-1400 MeV", 2000, 0., 2);
   h_pip_eop71 = iHistoManager.histogram(571, "pi+ E/p, p=1400-1420 MeV", 2000, 0., 2);
   h_pip_eop72 = iHistoManager.histogram(572, "pi+ E/p, p=1420-1440 MeV", 2000, 0., 2);
   h_pip_eop73 = iHistoManager.histogram(573, "pi+ E/p, p=1440-1460 MeV", 2000, 0., 2);
   h_pip_eop74 = iHistoManager.histogram(574, "pi+ E/p, p=1460-1480 MeV", 2000, 0., 2);
   h_pip_eop75 = iHistoManager.histogram(575, "pi+ E/p, p=1480-1500 MeV", 2000, 0., 2);
   h_pip_eop76 = iHistoManager.histogram(576, "pi+ E/p, p=1500-1520 MeV", 2000, 0., 2);
   h_pip_eop77 = iHistoManager.histogram(577, "pi+ E/p, p=1520-1540 MeV", 2000, 0., 2);
   h_pip_eop78 = iHistoManager.histogram(578, "pi+ E/p, p=1540-1560 MeV", 2000, 0., 2);
   h_pip_eop79 = iHistoManager.histogram(579, "pi+ E/p, p=1560-1580 MeV", 2000, 0., 2);
   h_pip_eop80 = iHistoManager.histogram(580, "pi+ E/p, p=1580-1600 MeV", 2000, 0., 2);
   h_pip_eop81 = iHistoManager.histogram(581, "pi+ E/p, p=1600-1620 MeV", 2000, 0., 2);
   h_pip_eop82 = iHistoManager.histogram(582, "pi+ E/p, p=1620-1640 MeV", 2000, 0., 2);
   h_pip_eop83 = iHistoManager.histogram(583, "pi+ E/p, p=1640-1660 MeV", 2000, 0., 2);
   h_pip_eop84 = iHistoManager.histogram(584, "pi+ E/p, p=1660-1680 MeV", 2000, 0., 2);
   h_pip_eop85 = iHistoManager.histogram(585, "pi+ E/p, p=1680-1700 MeV", 2000, 0., 2);
   h_pip_eop86 = iHistoManager.histogram(586, "pi+ E/p, p=1700-1720 MeV", 2000, 0., 2);
   h_pip_eop87 = iHistoManager.histogram(587, "pi+ E/p, p=1720-1740 MeV", 2000, 0., 2);
   h_pip_eop88 = iHistoManager.histogram(588, "pi+ E/p, p=1740-1760 MeV", 2000, 0., 2);
   h_pip_eop89 = iHistoManager.histogram(589, "pi+ E/p, p=1760-1780 MeV", 2000, 0., 2);
   h_pip_eop90 = iHistoManager.histogram(590, "pi+ E/p, p=1780-1800 MeV", 2000, 0., 2);
   h_pip_eop91 = iHistoManager.histogram(591, "pi+ E/p, p=1800-1820 MeV", 2000, 0., 2);
   h_pip_eop92 = iHistoManager.histogram(592, "pi+ E/p, p=1820-1840 MeV", 2000, 0., 2);
   h_pip_eop93 = iHistoManager.histogram(593, "pi+ E/p, p=1840-1860 MeV", 2000, 0., 2);
   h_pip_eop94 = iHistoManager.histogram(594, "pi+ E/p, p=1860-1880 MeV", 2000, 0., 2);
   h_pip_eop95 = iHistoManager.histogram(595, "pi+ E/p, p=1880-1900 MeV", 2000, 0., 2);
   h_pip_eop96 = iHistoManager.histogram(596, "pi+ E/p, p=1900-1920 MeV", 2000, 0., 2);
   h_pip_eop97 = iHistoManager.histogram(597, "pi+ E/p, p=1920-1940 MeV", 2000, 0., 2);
   h_pip_eop98 = iHistoManager.histogram(598, "pi+ E/p, p=1940-1960 MeV", 2000, 0., 2);
   h_pip_eop99 = iHistoManager.histogram(599, "pi+ E/p, p=1960-1980 MeV", 2000, 0., 2);
   h_pip_eop100 = iHistoManager.histogram(600, "pi+ E/p, p=1980-2000 MeV", 2000, 0., 2);

   h_pim_eop1 = iHistoManager.histogram(601, "pi- E/p, p=0-20 MeV", 2000, 0., 2);
   h_pim_eop2 = iHistoManager.histogram(602, "pi- E/p, p=20-40 MeV", 2000, 0., 2);
   h_pim_eop3 = iHistoManager.histogram(603, "pi- E/p, p=40-60 MeV", 2000, 0., 2);
   h_pim_eop4 = iHistoManager.histogram(604, "pi- E/p, p=60-80 MeV", 2000, 0., 2);
   h_pim_eop5 = iHistoManager.histogram(605, "pi- E/p, p=80-100 MeV", 2000, 0., 2);
   h_pim_eop6 = iHistoManager.histogram(606, "pi- E/p, p=100-120 MeV", 2000, 0., 2);
   h_pim_eop7 = iHistoManager.histogram(607, "pi- E/p, p=120-140 MeV", 2000, 0., 2);
   h_pim_eop8 = iHistoManager.histogram(608, "pi- E/p, p=140-160 MeV", 2000, 0., 2);
   h_pim_eop9 = iHistoManager.histogram(609, "pi- E/p, p=160-180 MeV", 2000, 0., 2);
   h_pim_eop10 = iHistoManager.histogram(610, "pi- E/p, p=180-200 MeV", 2000, 0., 2);
   h_pim_eop11 = iHistoManager.histogram(611, "pi- E/p, p=200-220 MeV", 2000, 0., 2);
   h_pim_eop12 = iHistoManager.histogram(612, "pi- E/p, p=220-240 MeV", 2000, 0., 2);
   h_pim_eop13 = iHistoManager.histogram(613, "pi- E/p, p=240-260 MeV", 2000, 0., 2);
   h_pim_eop14 = iHistoManager.histogram(614, "pi- E/p, p=260-280 MeV", 2000, 0., 2);
   h_pim_eop15 = iHistoManager.histogram(615, "pi- E/p, p=280-300 MeV", 2000, 0., 2);
   h_pim_eop16 = iHistoManager.histogram(616, "pi- E/p, p=300-800 MeV", 2000, 0., 2);
   h_pim_eop17 = iHistoManager.histogram(617, "pi- E/p, p=320-850 MeV", 2000, 0., 2);
   h_pim_eop18 = iHistoManager.histogram(618, "pi- E/p, p=340-900 MeV", 2000, 0., 2);
   h_pim_eop19 = iHistoManager.histogram(619, "pi- E/p, p=360-950 MeV", 2000, 0., 2);
   h_pim_eop20 = iHistoManager.histogram(620, "pi- E/p, p=380-400 MeV", 2000, 0., 2);
   h_pim_eop21 = iHistoManager.histogram(621, "pi- E/p, p=400-420 MeV", 2000, 0., 2);
   h_pim_eop22 = iHistoManager.histogram(622, "pi- E/p, p=420-440 MeV", 2000, 0., 2);
   h_pim_eop23 = iHistoManager.histogram(623, "pi- E/p, p=440-460 MeV", 2000, 0., 2);
   h_pim_eop24 = iHistoManager.histogram(624, "pi- E/p, p=460-480 MeV", 2000, 0., 2);
   h_pim_eop25 = iHistoManager.histogram(625, "pi- E/p, p=480-500 MeV", 2000, 0., 2);
   h_pim_eop26 = iHistoManager.histogram(626, "pi- E/p, p=500-520 MeV", 2000, 0., 2);
   h_pim_eop27 = iHistoManager.histogram(627, "pi- E/p, p=520-540 MeV", 2000, 0., 2);
   h_pim_eop28 = iHistoManager.histogram(628, "pi- E/p, p=540-560 MeV", 2000, 0., 2);
   h_pim_eop29 = iHistoManager.histogram(629, "pi- E/p, p=560-580 MeV", 2000, 0., 2);
   h_pim_eop30 = iHistoManager.histogram(630, "pi- E/p, p=580-600 MeV", 2000, 0., 2);
   h_pim_eop31 = iHistoManager.histogram(631, "pi- E/p, p=600-620 MeV", 2000, 0., 2);
   h_pim_eop32 = iHistoManager.histogram(632, "pi- E/p, p=620-640 MeV", 2000, 0., 2);
   h_pim_eop33 = iHistoManager.histogram(633, "pi- E/p, p=640-660 MeV", 2000, 0., 2);
   h_pim_eop34 = iHistoManager.histogram(634, "pi- E/p, p=660-680 MeV", 2000, 0., 2);
   h_pim_eop35 = iHistoManager.histogram(635, "pi- E/p, p=680-700 MeV", 2000, 0., 2);
   h_pim_eop36 = iHistoManager.histogram(636, "pi- E/p, p=700-720 MeV", 2000, 0., 2);
   h_pim_eop37 = iHistoManager.histogram(637, "pi- E/p, p=720-740 MeV", 2000, 0., 2);
   h_pim_eop38 = iHistoManager.histogram(638, "pi- E/p, p=740-760 MeV", 2000, 0., 2);
   h_pim_eop39 = iHistoManager.histogram(639, "pi- E/p, p=760-780 MeV", 2000, 0., 2);
   h_pim_eop40 = iHistoManager.histogram(640, "pi- E/p, p=780-800 MeV", 2000, 0., 2);
   h_pim_eop41 = iHistoManager.histogram(641, "pi- E/p, p=800-820 MeV", 2000, 0., 2);
   h_pim_eop42 = iHistoManager.histogram(642, "pi- E/p, p=820-840 MeV", 2000, 0., 2);
   h_pim_eop43 = iHistoManager.histogram(643, "pi- E/p, p=840-860 MeV", 2000, 0., 2);
   h_pim_eop44 = iHistoManager.histogram(644, "pi- E/p, p=860-880 MeV", 2000, 0., 2);
   h_pim_eop45 = iHistoManager.histogram(645, "pi- E/p, p=880-900 MeV", 2000, 0., 2);
   h_pim_eop46 = iHistoManager.histogram(646, "pi- E/p, p=900-920 MeV", 2000, 0., 2);
   h_pim_eop47 = iHistoManager.histogram(647, "pi- E/p, p=920-940 MeV", 2000, 0., 2);
   h_pim_eop48 = iHistoManager.histogram(648, "pi- E/p, p=940-960 MeV", 2000, 0., 2);
   h_pim_eop49 = iHistoManager.histogram(649, "pi- E/p, p=960-980 MeV", 2000, 0., 2);
   h_pim_eop50 = iHistoManager.histogram(650, "pi- E/p, p=980-1000 MeV", 2000, 0., 2);
   h_pim_eop51 = iHistoManager.histogram(651, "pi- E/p, p=1000-1020 MeV", 2000, 0., 2);
   h_pim_eop52 = iHistoManager.histogram(652, "pi- E/p, p=1020-1040 MeV", 2000, 0., 2);
   h_pim_eop53 = iHistoManager.histogram(653, "pi- E/p, p=1040-1060 MeV", 2000, 0., 2);
   h_pim_eop54 = iHistoManager.histogram(654, "pi- E/p, p=1060-1080 MeV", 2000, 0., 2);
   h_pim_eop55 = iHistoManager.histogram(655, "pi- E/p, p=1080-1100 MeV", 2000, 0., 2);
   h_pim_eop56 = iHistoManager.histogram(656, "pi- E/p, p=1100-1120 MeV", 2000, 0., 2);
   h_pim_eop57 = iHistoManager.histogram(657, "pi- E/p, p=1120-1140 MeV", 2000, 0., 2);
   h_pim_eop58 = iHistoManager.histogram(658, "pi- E/p, p=1140-1160 MeV", 2000, 0., 2);
   h_pim_eop59 = iHistoManager.histogram(659, "pi- E/p, p=1160-1180 MeV", 2000, 0., 2);
   h_pim_eop60 = iHistoManager.histogram(660, "pi- E/p, p=1180-1200 MeV", 2000, 0., 2);
   h_pim_eop61 = iHistoManager.histogram(661, "pi- E/p, p=1200-1220 MeV", 2000, 0., 2);
   h_pim_eop62 = iHistoManager.histogram(662, "pi- E/p, p=1220-1240 MeV", 2000, 0., 2);
   h_pim_eop63 = iHistoManager.histogram(663, "pi- E/p, p=1240-1260 MeV", 2000, 0., 2);
   h_pim_eop64 = iHistoManager.histogram(664, "pi- E/p, p=1260-1280 MeV", 2000, 0., 2);
   h_pim_eop65 = iHistoManager.histogram(665, "pi- E/p, p=1280-1300 MeV", 2000, 0., 2);
   h_pim_eop66 = iHistoManager.histogram(666, "pi- E/p, p=1300-1320 MeV", 2000, 0., 2);
   h_pim_eop67 = iHistoManager.histogram(667, "pi- E/p, p=1320-1340 MeV", 2000, 0., 2);
   h_pim_eop68 = iHistoManager.histogram(668, "pi- E/p, p=1340-1360 MeV", 2000, 0., 2);
   h_pim_eop69 = iHistoManager.histogram(669, "pi- E/p, p=1360-1380 MeV", 2000, 0., 2);
   h_pim_eop70 = iHistoManager.histogram(670, "pi- E/p, p=1380-1400 MeV", 2000, 0., 2);
   h_pim_eop71 = iHistoManager.histogram(671, "pi- E/p, p=1400-1420 MeV", 2000, 0., 2);
   h_pim_eop72 = iHistoManager.histogram(672, "pi- E/p, p=1420-1440 MeV", 2000, 0., 2);
   h_pim_eop73 = iHistoManager.histogram(673, "pi- E/p, p=1440-1460 MeV", 2000, 0., 2);
   h_pim_eop74 = iHistoManager.histogram(674, "pi- E/p, p=1460-1480 MeV", 2000, 0., 2);
   h_pim_eop75 = iHistoManager.histogram(675, "pi- E/p, p=1480-1500 MeV", 2000, 0., 2);
   h_pim_eop76 = iHistoManager.histogram(676, "pi- E/p, p=1500-1520 MeV", 2000, 0., 2);
   h_pim_eop77 = iHistoManager.histogram(677, "pi- E/p, p=1520-1540 MeV", 2000, 0., 2);
   h_pim_eop78 = iHistoManager.histogram(678, "pi- E/p, p=1540-1560 MeV", 2000, 0., 2);
   h_pim_eop79 = iHistoManager.histogram(679, "pi- E/p, p=1560-1580 MeV", 2000, 0., 2);
   h_pim_eop80 = iHistoManager.histogram(680, "pi- E/p, p=1580-1600 MeV", 2000, 0., 2);
   h_pim_eop81 = iHistoManager.histogram(681, "pi- E/p, p=1600-1620 MeV", 2000, 0., 2);
   h_pim_eop82 = iHistoManager.histogram(682, "pi- E/p, p=1620-1640 MeV", 2000, 0., 2);
   h_pim_eop83 = iHistoManager.histogram(683, "pi- E/p, p=1640-1660 MeV", 2000, 0., 2);
   h_pim_eop84 = iHistoManager.histogram(684, "pi- E/p, p=1660-1680 MeV", 2000, 0., 2);
   h_pim_eop85 = iHistoManager.histogram(685, "pi- E/p, p=1680-1700 MeV", 2000, 0., 2);
   h_pim_eop86 = iHistoManager.histogram(686, "pi- E/p, p=1700-1720 MeV", 2000, 0., 2);
   h_pim_eop87 = iHistoManager.histogram(687, "pi- E/p, p=1720-1740 MeV", 2000, 0., 2);
   h_pim_eop88 = iHistoManager.histogram(688, "pi- E/p, p=1740-1760 MeV", 2000, 0., 2);
   h_pim_eop89 = iHistoManager.histogram(689, "pi- E/p, p=1760-1780 MeV", 2000, 0., 2);
   h_pim_eop90 = iHistoManager.histogram(690, "pi- E/p, p=1780-1800 MeV", 2000, 0., 2);
   h_pim_eop91 = iHistoManager.histogram(691, "pi- E/p, p=1800-1820 MeV", 2000, 0., 2);
   h_pim_eop92 = iHistoManager.histogram(692, "pi- E/p, p=1820-1840 MeV", 2000, 0., 2);
   h_pim_eop93 = iHistoManager.histogram(693, "pi- E/p, p=1840-1860 MeV", 2000, 0., 2);
   h_pim_eop94 = iHistoManager.histogram(694, "pi- E/p, p=1860-1880 MeV", 2000, 0., 2);
   h_pim_eop95 = iHistoManager.histogram(695, "pi- E/p, p=1880-1900 MeV", 2000, 0., 2);
   h_pim_eop96 = iHistoManager.histogram(696, "pi- E/p, p=1900-1920 MeV", 2000, 0., 2);
   h_pim_eop97 = iHistoManager.histogram(697, "pi- E/p, p=1920-1940 MeV", 2000, 0., 2);
   h_pim_eop98 = iHistoManager.histogram(698, "pi- E/p, p=1940-1960 MeV", 2000, 0., 2);
   h_pim_eop99 = iHistoManager.histogram(699, "pi- E/p, p=1960-1980 MeV", 2000, 0., 2);
   h_pim_eop100 = iHistoManager.histogram(700, "pi- E/p, p=1980-2000 MeV", 2000, 0., 2);


   h_pip_matche_p = iHistoManager.histogram(481, "pi+ matched energy vs. p", 200, 0., 2., 200, 0., 2.);
   h_pim_matche_p = iHistoManager.histogram(482, "pi- matched energy vs. p", 200, 0., 2., 200, 0., 2.);

   h_pion_matche = iHistoManager.histogram(100, "pion matched energy", 200, 0., 2.);

   h_pip_matche1 = iHistoManager.histogram(101, "pi+ matched energy, p=0-20 MeV", 200, 0., 2);
   h_pip_matche2 = iHistoManager.histogram(102, "pi+ matched energy, p=20-40 MeV", 200, 0., 2);
   h_pip_matche3 = iHistoManager.histogram(103, "pi+ matched energy, p=40-60 MeV", 200, 0., 2);
   h_pip_matche4 = iHistoManager.histogram(104, "pi+ matched energy, p=60-80 MeV", 200, 0., 2);
   h_pip_matche5 = iHistoManager.histogram(105, "pi+ matched energy, p=80-100 MeV", 200, 0., 2);
   h_pip_matche6 = iHistoManager.histogram(106, "pi+ matched energy, p=100-120 MeV", 200, 0., 2);
   h_pip_matche7 = iHistoManager.histogram(107, "pi+ matched energy, p=120-140 MeV", 200, 0., 2);
   h_pip_matche8 = iHistoManager.histogram(108, "pi+ matched energy, p=140-160 MeV", 200, 0., 2);
   h_pip_matche9 = iHistoManager.histogram(109, "pi+ matched energy, p=160-180 MeV", 200, 0., 2);
   h_pip_matche10 = iHistoManager.histogram(110, "pi+ matched energy, p=180-200 MeV", 200, 0., 2);
   h_pip_matche11 = iHistoManager.histogram(111, "pi+ matched energy, p=200-220 MeV", 200, 0., 2);
   h_pip_matche12 = iHistoManager.histogram(112, "pi+ matched energy, p=220-240 MeV", 200, 0., 2);
   h_pip_matche13 = iHistoManager.histogram(113, "pi+ matched energy, p=240-260 MeV", 200, 0., 2);
   h_pip_matche14 = iHistoManager.histogram(114, "pi+ matched energy, p=260-280 MeV", 200, 0., 2);
   h_pip_matche15 = iHistoManager.histogram(115, "pi+ matched energy, p=280-300 MeV", 200, 0., 2);
   h_pip_matche16 = iHistoManager.histogram(116, "pi+ matched energy, p=300-800 MeV", 200, 0., 2);
   h_pip_matche17 = iHistoManager.histogram(117, "pi+ matched energy, p=320-850 MeV", 200, 0., 2);
   h_pip_matche18 = iHistoManager.histogram(118, "pi+ matched energy, p=340-900 MeV", 200, 0., 2);
   h_pip_matche19 = iHistoManager.histogram(119, "pi+ matched energy, p=360-950 MeV", 200, 0., 2);
   h_pip_matche20 = iHistoManager.histogram(120, "pi+ matched energy, p=380-400 MeV", 200, 0., 2);
   h_pip_matche21 = iHistoManager.histogram(121, "pi+ matched energy, p=400-420 MeV", 200, 0., 2);
   h_pip_matche22 = iHistoManager.histogram(122, "pi+ matched energy, p=420-440 MeV", 200, 0., 2);
   h_pip_matche23 = iHistoManager.histogram(123, "pi+ matched energy, p=440-460 MeV", 200, 0., 2);
   h_pip_matche24 = iHistoManager.histogram(124, "pi+ matched energy, p=460-480 MeV", 200, 0., 2);
   h_pip_matche25 = iHistoManager.histogram(125, "pi+ matched energy, p=480-500 MeV", 200, 0., 2);
   h_pip_matche26 = iHistoManager.histogram(126, "pi+ matched energy, p=500-520 MeV", 200, 0., 2);
   h_pip_matche27 = iHistoManager.histogram(127, "pi+ matched energy, p=520-540 MeV", 200, 0., 2);
   h_pip_matche28 = iHistoManager.histogram(128, "pi+ matched energy, p=540-560 MeV", 200, 0., 2);
   h_pip_matche29 = iHistoManager.histogram(129, "pi+ matched energy, p=560-580 MeV", 200, 0., 2);
   h_pip_matche30 = iHistoManager.histogram(130, "pi+ matched energy, p=580-600 MeV", 200, 0., 2);
   h_pip_matche31 = iHistoManager.histogram(131, "pi+ matched energy, p=600-620 MeV", 200, 0., 2);
   h_pip_matche32 = iHistoManager.histogram(132, "pi+ matched energy, p=620-640 MeV", 200, 0., 2);
   h_pip_matche33 = iHistoManager.histogram(133, "pi+ matched energy, p=640-660 MeV", 200, 0., 2);
   h_pip_matche34 = iHistoManager.histogram(134, "pi+ matched energy, p=660-680 MeV", 200, 0., 2);
   h_pip_matche35 = iHistoManager.histogram(135, "pi+ matched energy, p=680-700 MeV", 200, 0., 2);
   h_pip_matche36 = iHistoManager.histogram(136, "pi+ matched energy, p=700-720 MeV", 200, 0., 2);
   h_pip_matche37 = iHistoManager.histogram(137, "pi+ matched energy, p=720-740 MeV", 200, 0., 2);
   h_pip_matche38 = iHistoManager.histogram(138, "pi+ matched energy, p=740-760 MeV", 200, 0., 2);
   h_pip_matche39 = iHistoManager.histogram(139, "pi+ matched energy, p=760-780 MeV", 200, 0., 2);
   h_pip_matche40 = iHistoManager.histogram(140, "pi+ matched energy, p=780-800 MeV", 200, 0., 2);
   h_pip_matche41 = iHistoManager.histogram(141, "pi+ matched energy, p=800-820 MeV", 200, 0., 2);
   h_pip_matche42 = iHistoManager.histogram(142, "pi+ matched energy, p=820-840 MeV", 200, 0., 2);
   h_pip_matche43 = iHistoManager.histogram(143, "pi+ matched energy, p=840-860 MeV", 200, 0., 2);
   h_pip_matche44 = iHistoManager.histogram(144, "pi+ matched energy, p=860-880 MeV", 200, 0., 2);
   h_pip_matche45 = iHistoManager.histogram(145, "pi+ matched energy, p=880-900 MeV", 200, 0., 2);
   h_pip_matche46 = iHistoManager.histogram(146, "pi+ matched energy, p=900-920 MeV", 200, 0., 2);
   h_pip_matche47 = iHistoManager.histogram(147, "pi+ matched energy, p=920-940 MeV", 200, 0., 2);
   h_pip_matche48 = iHistoManager.histogram(148, "pi+ matched energy, p=940-960 MeV", 200, 0., 2);
   h_pip_matche49 = iHistoManager.histogram(149, "pi+ matched energy, p=960-980 MeV", 200, 0., 2);
   h_pip_matche50 = iHistoManager.histogram(150, "pi+ matched energy, p=980-1000 MeV", 200, 0., 2);
   h_pip_matche51 = iHistoManager.histogram(151, "pi+ matched energy, p=1000-1020 MeV", 200, 0., 2);
   h_pip_matche52 = iHistoManager.histogram(152, "pi+ matched energy, p=1020-1040 MeV", 200, 0., 2);
   h_pip_matche53 = iHistoManager.histogram(153, "pi+ matched energy, p=1040-1060 MeV", 200, 0., 2);
   h_pip_matche54 = iHistoManager.histogram(154, "pi+ matched energy, p=1060-1080 MeV", 200, 0., 2);
   h_pip_matche55 = iHistoManager.histogram(155, "pi+ matched energy, p=1080-1100 MeV", 200, 0., 2);
   h_pip_matche56 = iHistoManager.histogram(156, "pi+ matched energy, p=1100-1120 MeV", 200, 0., 2);
   h_pip_matche57 = iHistoManager.histogram(157, "pi+ matched energy, p=1120-1140 MeV", 200, 0., 2);
   h_pip_matche58 = iHistoManager.histogram(158, "pi+ matched energy, p=1140-1160 MeV", 200, 0., 2);
   h_pip_matche59 = iHistoManager.histogram(159, "pi+ matched energy, p=1160-1180 MeV", 200, 0., 2);
   h_pip_matche60 = iHistoManager.histogram(160, "pi+ matched energy, p=1180-1200 MeV", 200, 0., 2);
   h_pip_matche61 = iHistoManager.histogram(161, "pi+ matched energy, p=1200-1220 MeV", 200, 0., 2);
   h_pip_matche62 = iHistoManager.histogram(162, "pi+ matched energy, p=1220-1240 MeV", 200, 0., 2);
   h_pip_matche63 = iHistoManager.histogram(163, "pi+ matched energy, p=1240-1260 MeV", 200, 0., 2);
   h_pip_matche64 = iHistoManager.histogram(164, "pi+ matched energy, p=1260-1280 MeV", 200, 0., 2);
   h_pip_matche65 = iHistoManager.histogram(165, "pi+ matched energy, p=1280-1300 MeV", 200, 0., 2);
   h_pip_matche66 = iHistoManager.histogram(166, "pi+ matched energy, p=1300-1320 MeV", 200, 0., 2);
   h_pip_matche67 = iHistoManager.histogram(167, "pi+ matched energy, p=1320-1340 MeV", 200, 0., 2);
   h_pip_matche68 = iHistoManager.histogram(168, "pi+ matched energy, p=1340-1360 MeV", 200, 0., 2);
   h_pip_matche69 = iHistoManager.histogram(169, "pi+ matched energy, p=1360-1380 MeV", 200, 0., 2);
   h_pip_matche70 = iHistoManager.histogram(170, "pi+ matched energy, p=1380-1400 MeV", 200, 0., 2);
   h_pip_matche71 = iHistoManager.histogram(171, "pi+ matched energy, p=1400-1420 MeV", 200, 0., 2);
   h_pip_matche72 = iHistoManager.histogram(172, "pi+ matched energy, p=1420-1440 MeV", 200, 0., 2);
   h_pip_matche73 = iHistoManager.histogram(173, "pi+ matched energy, p=1440-1460 MeV", 200, 0., 2);
   h_pip_matche74 = iHistoManager.histogram(174, "pi+ matched energy, p=1460-1480 MeV", 200, 0., 2);
   h_pip_matche75 = iHistoManager.histogram(175, "pi+ matched energy, p=1480-1500 MeV", 200, 0., 2);
   h_pip_matche76 = iHistoManager.histogram(176, "pi+ matched energy, p=1500-1520 MeV", 200, 0., 2);
   h_pip_matche77 = iHistoManager.histogram(177, "pi+ matched energy, p=1520-1540 MeV", 200, 0., 2);
   h_pip_matche78 = iHistoManager.histogram(178, "pi+ matched energy, p=1540-1560 MeV", 200, 0., 2);
   h_pip_matche79 = iHistoManager.histogram(179, "pi+ matched energy, p=1560-1580 MeV", 200, 0., 2);
   h_pip_matche80 = iHistoManager.histogram(180, "pi+ matched energy, p=1580-1600 MeV", 200, 0., 2);
   h_pip_matche81 = iHistoManager.histogram(181, "pi+ matched energy, p=1600-1620 MeV", 200, 0., 2);
   h_pip_matche82 = iHistoManager.histogram(182, "pi+ matched energy, p=1620-1640 MeV", 200, 0., 2);
   h_pip_matche83 = iHistoManager.histogram(183, "pi+ matched energy, p=1640-1660 MeV", 200, 0., 2);
   h_pip_matche84 = iHistoManager.histogram(184, "pi+ matched energy, p=1660-1680 MeV", 200, 0., 2);
   h_pip_matche85 = iHistoManager.histogram(185, "pi+ matched energy, p=1680-1700 MeV", 200, 0., 2);
   h_pip_matche86 = iHistoManager.histogram(186, "pi+ matched energy, p=1700-1720 MeV", 200, 0., 2);
   h_pip_matche87 = iHistoManager.histogram(187, "pi+ matched energy, p=1720-1740 MeV", 200, 0., 2);
   h_pip_matche88 = iHistoManager.histogram(188, "pi+ matched energy, p=1740-1760 MeV", 200, 0., 2);
   h_pip_matche89 = iHistoManager.histogram(189, "pi+ matched energy, p=1760-1780 MeV", 200, 0., 2);
   h_pip_matche90 = iHistoManager.histogram(190, "pi+ matched energy, p=1780-1800 MeV", 200, 0., 2);
   h_pip_matche91 = iHistoManager.histogram(191, "pi+ matched energy, p=1800-1820 MeV", 200, 0., 2);
   h_pip_matche92 = iHistoManager.histogram(192, "pi+ matched energy, p=1820-1840 MeV", 200, 0., 2);
   h_pip_matche93 = iHistoManager.histogram(193, "pi+ matched energy, p=1840-1860 MeV", 200, 0., 2);
   h_pip_matche94 = iHistoManager.histogram(194, "pi+ matched energy, p=1860-1880 MeV", 200, 0., 2);
   h_pip_matche95 = iHistoManager.histogram(195, "pi+ matched energy, p=1880-1900 MeV", 200, 0., 2);
   h_pip_matche96 = iHistoManager.histogram(196, "pi+ matched energy, p=1900-1920 MeV", 200, 0., 2);
   h_pip_matche97 = iHistoManager.histogram(197, "pi+ matched energy, p=1920-1940 MeV", 200, 0., 2);
   h_pip_matche98 = iHistoManager.histogram(198, "pi+ matched energy, p=1940-1960 MeV", 200, 0., 2);
   h_pip_matche99 = iHistoManager.histogram(199, "pi+ matched energy, p=1960-1980 MeV", 200, 0., 2);
   h_pip_matche100 = iHistoManager.histogram(200, "pi+ matched energy, p=1980-200 MeV", 200, 0., 2);

   h_pim_matche1 = iHistoManager.histogram(201, "pi- matched energy, p=0-20 MeV", 200, 0., 2);
   h_pim_matche2 = iHistoManager.histogram(202, "pi- matched energy, p=20-40 MeV", 200, 0., 2);
   h_pim_matche3 = iHistoManager.histogram(203, "pi- matched energy, p=40-60 MeV", 200, 0., 2);
   h_pim_matche4 = iHistoManager.histogram(204, "pi- matched energy, p=60-80 MeV", 200, 0., 2);
   h_pim_matche5 = iHistoManager.histogram(205, "pi- matched energy, p=80-100 MeV", 200, 0., 2);
   h_pim_matche6 = iHistoManager.histogram(206, "pi- matched energy, p=100-120 MeV", 200, 0., 2);
   h_pim_matche7 = iHistoManager.histogram(207, "pi- matched energy, p=120-140 MeV", 200, 0., 2);
   h_pim_matche8 = iHistoManager.histogram(208, "pi- matched energy, p=140-160 MeV", 200, 0., 2);
   h_pim_matche9 = iHistoManager.histogram(209, "pi- matched energy, p=160-180 MeV", 200, 0., 2);
   h_pim_matche10 = iHistoManager.histogram(210, "pi- matched energy, p=180-200 MeV", 200, 0., 2);
   h_pim_matche11 = iHistoManager.histogram(211, "pi- matched energy, p=200-220 MeV", 200, 0., 2);
   h_pim_matche12 = iHistoManager.histogram(212, "pi- matched energy, p=220-240 MeV", 200, 0., 2);
   h_pim_matche13 = iHistoManager.histogram(213, "pi- matched energy, p=240-260 MeV", 200, 0., 2);
   h_pim_matche14 = iHistoManager.histogram(214, "pi- matched energy, p=260-280 MeV", 200, 0., 2);
   h_pim_matche15 = iHistoManager.histogram(215, "pi- matched energy, p=280-300 MeV", 200, 0., 2);
   h_pim_matche16 = iHistoManager.histogram(216, "pi- matched energy, p=300-800 MeV", 200, 0., 2);
   h_pim_matche17 = iHistoManager.histogram(217, "pi- matched energy, p=320-850 MeV", 200, 0., 2);
   h_pim_matche18 = iHistoManager.histogram(218, "pi- matched energy, p=340-900 MeV", 200, 0., 2);
   h_pim_matche19 = iHistoManager.histogram(219, "pi- matched energy, p=360-950 MeV", 200, 0., 2);
   h_pim_matche20 = iHistoManager.histogram(220, "pi- matched energy, p=380-400 MeV", 200, 0., 2);
   h_pim_matche21 = iHistoManager.histogram(221, "pi- matched energy, p=400-420 MeV", 200, 0., 2);
   h_pim_matche22 = iHistoManager.histogram(222, "pi- matched energy, p=420-440 MeV", 200, 0., 2);
   h_pim_matche23 = iHistoManager.histogram(223, "pi- matched energy, p=440-460 MeV", 200, 0., 2);
   h_pim_matche24 = iHistoManager.histogram(224, "pi- matched energy, p=460-480 MeV", 200, 0., 2);
   h_pim_matche25 = iHistoManager.histogram(225, "pi- matched energy, p=480-500 MeV", 200, 0., 2);
   h_pim_matche26 = iHistoManager.histogram(226, "pi- matched energy, p=500-520 MeV", 200, 0., 2);
   h_pim_matche27 = iHistoManager.histogram(227, "pi- matched energy, p=520-540 MeV", 200, 0., 2);
   h_pim_matche28 = iHistoManager.histogram(228, "pi- matched energy, p=540-560 MeV", 200, 0., 2);
   h_pim_matche29 = iHistoManager.histogram(229, "pi- matched energy, p=560-580 MeV", 200, 0., 2);
   h_pim_matche30 = iHistoManager.histogram(230, "pi- matched energy, p=580-600 MeV", 200, 0., 2);
   h_pim_matche31 = iHistoManager.histogram(231, "pi- matched energy, p=600-620 MeV", 200, 0., 2);
   h_pim_matche32 = iHistoManager.histogram(232, "pi- matched energy, p=620-640 MeV", 200, 0., 2);
   h_pim_matche33 = iHistoManager.histogram(233, "pi- matched energy, p=640-660 MeV", 200, 0., 2);
   h_pim_matche34 = iHistoManager.histogram(234, "pi- matched energy, p=660-680 MeV", 200, 0., 2);
   h_pim_matche35 = iHistoManager.histogram(235, "pi- matched energy, p=680-700 MeV", 200, 0., 2);
   h_pim_matche36 = iHistoManager.histogram(236, "pi- matched energy, p=700-720 MeV", 200, 0., 2);
   h_pim_matche37 = iHistoManager.histogram(237, "pi- matched energy, p=720-740 MeV", 200, 0., 2);
   h_pim_matche38 = iHistoManager.histogram(238, "pi- matched energy, p=740-760 MeV", 200, 0., 2);
   h_pim_matche39 = iHistoManager.histogram(239, "pi- matched energy, p=760-780 MeV", 200, 0., 2);
   h_pim_matche40 = iHistoManager.histogram(240, "pi- matched energy, p=780-800 MeV", 200, 0., 2);
   h_pim_matche41 = iHistoManager.histogram(241, "pi- matched energy, p=800-820 MeV", 200, 0., 2);
   h_pim_matche42 = iHistoManager.histogram(242, "pi- matched energy, p=820-840 MeV", 200, 0., 2);
   h_pim_matche43 = iHistoManager.histogram(243, "pi- matched energy, p=840-860 MeV", 200, 0., 2);
   h_pim_matche44 = iHistoManager.histogram(244, "pi- matched energy, p=860-880 MeV", 200, 0., 2);
   h_pim_matche45 = iHistoManager.histogram(245, "pi- matched energy, p=880-900 MeV", 200, 0., 2);
   h_pim_matche46 = iHistoManager.histogram(246, "pi- matched energy, p=900-920 MeV", 200, 0., 2);
   h_pim_matche47 = iHistoManager.histogram(247, "pi- matched energy, p=920-940 MeV", 200, 0., 2);
   h_pim_matche48 = iHistoManager.histogram(248, "pi- matched energy, p=940-960 MeV", 200, 0., 2);
   h_pim_matche49 = iHistoManager.histogram(249, "pi- matched energy, p=960-980 MeV", 200, 0., 2);
   h_pim_matche50 = iHistoManager.histogram(250, "pi- matched energy, p=980-1000 MeV", 200, 0., 2);
   h_pim_matche51 = iHistoManager.histogram(251, "pi- matched energy, p=1000-1020 MeV", 200, 0., 2);
   h_pim_matche52 = iHistoManager.histogram(252, "pi- matched energy, p=1020-1040 MeV", 200, 0., 2);
   h_pim_matche53 = iHistoManager.histogram(253, "pi- matched energy, p=1040-1060 MeV", 200, 0., 2);
   h_pim_matche54 = iHistoManager.histogram(254, "pi- matched energy, p=1060-1080 MeV", 200, 0., 2);
   h_pim_matche55 = iHistoManager.histogram(255, "pi- matched energy, p=1080-1100 MeV", 200, 0., 2);
   h_pim_matche56 = iHistoManager.histogram(256, "pi- matched energy, p=1100-1120 MeV", 200, 0., 2);
   h_pim_matche57 = iHistoManager.histogram(257, "pi- matched energy, p=1120-1140 MeV", 200, 0., 2);
   h_pim_matche58 = iHistoManager.histogram(258, "pi- matched energy, p=1140-1160 MeV", 200, 0., 2);
   h_pim_matche59 = iHistoManager.histogram(259, "pi- matched energy, p=1160-1180 MeV", 200, 0., 2);
   h_pim_matche60 = iHistoManager.histogram(260, "pi- matched energy, p=1180-1200 MeV", 200, 0., 2);
   h_pim_matche61 = iHistoManager.histogram(261, "pi- matched energy, p=1200-1220 MeV", 200, 0., 2);
   h_pim_matche62 = iHistoManager.histogram(262, "pi- matched energy, p=1220-1240 MeV", 200, 0., 2);
   h_pim_matche63 = iHistoManager.histogram(263, "pi- matched energy, p=1240-1260 MeV", 200, 0., 2);
   h_pim_matche64 = iHistoManager.histogram(264, "pi- matched energy, p=1260-1280 MeV", 200, 0., 2);
   h_pim_matche65 = iHistoManager.histogram(265, "pi- matched energy, p=1280-1300 MeV", 200, 0., 2);
   h_pim_matche66 = iHistoManager.histogram(266, "pi- matched energy, p=1300-1320 MeV", 200, 0., 2);
   h_pim_matche67 = iHistoManager.histogram(267, "pi- matched energy, p=1320-1340 MeV", 200, 0., 2);
   h_pim_matche68 = iHistoManager.histogram(268, "pi- matched energy, p=1340-1360 MeV", 200, 0., 2);
   h_pim_matche69 = iHistoManager.histogram(269, "pi- matched energy, p=1360-1380 MeV", 200, 0., 2);
   h_pim_matche70 = iHistoManager.histogram(270, "pi- matched energy, p=1380-1400 MeV", 200, 0., 2);
   h_pim_matche71 = iHistoManager.histogram(271, "pi- matched energy, p=1400-1420 MeV", 200, 0., 2);
   h_pim_matche72 = iHistoManager.histogram(272, "pi- matched energy, p=1420-1440 MeV", 200, 0., 2);
   h_pim_matche73 = iHistoManager.histogram(273, "pi- matched energy, p=1440-1460 MeV", 200, 0., 2);
   h_pim_matche74 = iHistoManager.histogram(274, "pi- matched energy, p=1460-1480 MeV", 200, 0., 2);
   h_pim_matche75 = iHistoManager.histogram(275, "pi- matched energy, p=1480-1500 MeV", 200, 0., 2);
   h_pim_matche76 = iHistoManager.histogram(276, "pi- matched energy, p=1500-1520 MeV", 200, 0., 2);
   h_pim_matche77 = iHistoManager.histogram(277, "pi- matched energy, p=1520-1540 MeV", 200, 0., 2);
   h_pim_matche78 = iHistoManager.histogram(278, "pi- matched energy, p=1540-1560 MeV", 200, 0., 2);
   h_pim_matche79 = iHistoManager.histogram(279, "pi- matched energy, p=1560-1580 MeV", 200, 0., 2);
   h_pim_matche80 = iHistoManager.histogram(280, "pi- matched energy, p=1580-1600 MeV", 200, 0., 2);
   h_pim_matche81 = iHistoManager.histogram(281, "pi- matched energy, p=1600-1620 MeV", 200, 0., 2);
   h_pim_matche82 = iHistoManager.histogram(282, "pi- matched energy, p=1620-1640 MeV", 200, 0., 2);
   h_pim_matche83 = iHistoManager.histogram(283, "pi- matched energy, p=1640-1660 MeV", 200, 0., 2);
   h_pim_matche84 = iHistoManager.histogram(284, "pi- matched energy, p=1660-1680 MeV", 200, 0., 2);
   h_pim_matche85 = iHistoManager.histogram(285, "pi- matched energy, p=1680-1700 MeV", 200, 0., 2);
   h_pim_matche86 = iHistoManager.histogram(286, "pi- matched energy, p=1700-1720 MeV", 200, 0., 2);
   h_pim_matche87 = iHistoManager.histogram(287, "pi- matched energy, p=1720-1740 MeV", 200, 0., 2);
   h_pim_matche88 = iHistoManager.histogram(288, "pi- matched energy, p=1740-1760 MeV", 200, 0., 2);
   h_pim_matche89 = iHistoManager.histogram(289, "pi- matched energy, p=1760-1780 MeV", 200, 0., 2);
   h_pim_matche90 = iHistoManager.histogram(290, "pi- matched energy, p=1780-1800 MeV", 200, 0., 2);
   h_pim_matche91 = iHistoManager.histogram(291, "pi- matched energy, p=1800-1820 MeV", 200, 0., 2);
   h_pim_matche92 = iHistoManager.histogram(292, "pi- matched energy, p=1820-1840 MeV", 200, 0., 2);
   h_pim_matche93 = iHistoManager.histogram(293, "pi- matched energy, p=1840-1860 MeV", 200, 0., 2);
   h_pim_matche94 = iHistoManager.histogram(294, "pi- matched energy, p=1860-1880 MeV", 200, 0., 2);
   h_pim_matche95 = iHistoManager.histogram(295, "pi- matched energy, p=1880-1900 MeV", 200, 0., 2);
   h_pim_matche96 = iHistoManager.histogram(296, "pi- matched energy, p=1900-1920 MeV", 200, 0., 2);
   h_pim_matche97 = iHistoManager.histogram(297, "pi- matched energy, p=1920-1940 MeV", 200, 0., 2);
   h_pim_matche98 = iHistoManager.histogram(298, "pi- matched energy, p=1940-1960 MeV", 200, 0., 2);
   h_pim_matche99 = iHistoManager.histogram(299, "pi- matched energy, p=1960-1980 MeV", 200, 0., 2);
   h_pim_matche100 = iHistoManager.histogram(300, "pi- matched energy, p=1980-2000 MeV", 200, 0., 2);

   h_pion_matche_eop = iHistoManager.histogram(700, "pion matched energy after E/p cut", 200, 0., 2.);

   h_pip_matche1_eop = iHistoManager.histogram(701, "pi+ matched energy after e/p cut, p=0-20 MeV", 200, 0., 2);
   h_pip_matche2_eop = iHistoManager.histogram(702, "pi+ matched energy after e/p cut, p=20-40 MeV", 200, 0., 2);
   h_pip_matche3_eop = iHistoManager.histogram(703, "pi+ matched energy after e/p cut, p=40-60 MeV", 200, 0., 2);
   h_pip_matche4_eop = iHistoManager.histogram(704, "pi+ matched energy after e/p cut, p=60-80 MeV", 200, 0., 2);
   h_pip_matche5_eop = iHistoManager.histogram(705, "pi+ matched energy after e/p cut, p=80-100 MeV", 200, 0., 2);
   h_pip_matche6_eop = iHistoManager.histogram(706, "pi+ matched energy after e/p cut, p=100-120 MeV", 200, 0., 2);
   h_pip_matche7_eop = iHistoManager.histogram(707, "pi+ matched energy after e/p cut, p=120-140 MeV", 200, 0., 2);
   h_pip_matche8_eop = iHistoManager.histogram(708, "pi+ matched energy after e/p cut, p=140-160 MeV", 200, 0., 2);
   h_pip_matche9_eop = iHistoManager.histogram(709, "pi+ matched energy after e/p cut, p=160-180 MeV", 200, 0., 2);
   h_pip_matche10_eop = iHistoManager.histogram(710, "pi+ matched energy after e/p cut, p=180-200 MeV", 200, 0., 2);
   h_pip_matche11_eop = iHistoManager.histogram(711, "pi+ matched energy after e/p cut, p=200-220 MeV", 200, 0., 2);
   h_pip_matche12_eop = iHistoManager.histogram(712, "pi+ matched energy after e/p cut, p=220-240 MeV", 200, 0., 2);
   h_pip_matche13_eop = iHistoManager.histogram(713, "pi+ matched energy after e/p cut, p=240-260 MeV", 200, 0., 2);
   h_pip_matche14_eop = iHistoManager.histogram(714, "pi+ matched energy after e/p cut, p=260-280 MeV", 200, 0., 2);
   h_pip_matche15_eop = iHistoManager.histogram(715, "pi+ matched energy after e/p cut, p=280-300 MeV", 200, 0., 2);
   h_pip_matche16_eop = iHistoManager.histogram(716, "pi+ matched energy after e/p cut, p=300-800 MeV", 200, 0., 2);
   h_pip_matche17_eop = iHistoManager.histogram(717, "pi+ matched energy after e/p cut, p=320-850 MeV", 200, 0., 2);
   h_pip_matche18_eop = iHistoManager.histogram(718, "pi+ matched energy after e/p cut, p=340-900 MeV", 200, 0., 2);
   h_pip_matche19_eop = iHistoManager.histogram(719, "pi+ matched energy after e/p cut, p=360-950 MeV", 200, 0., 2);
   h_pip_matche20_eop = iHistoManager.histogram(720, "pi+ matched energy after e/p cut, p=380-400 MeV", 200, 0., 2);
   h_pip_matche21_eop = iHistoManager.histogram(721, "pi+ matched energy after e/p cut, p=400-420 MeV", 200, 0., 2);
   h_pip_matche22_eop = iHistoManager.histogram(722, "pi+ matched energy after e/p cut, p=420-440 MeV", 200, 0., 2);
   h_pip_matche23_eop = iHistoManager.histogram(723, "pi+ matched energy after e/p cut, p=440-460 MeV", 200, 0., 2);
   h_pip_matche24_eop = iHistoManager.histogram(724, "pi+ matched energy after e/p cut, p=460-480 MeV", 200, 0., 2);
   h_pip_matche25_eop = iHistoManager.histogram(725, "pi+ matched energy after e/p cut, p=480-500 MeV", 200, 0., 2);
   h_pip_matche26_eop = iHistoManager.histogram(726, "pi+ matched energy after e/p cut, p=500-520 MeV", 200, 0., 2);
   h_pip_matche27_eop = iHistoManager.histogram(727, "pi+ matched energy after e/p cut, p=520-540 MeV", 200, 0., 2);
   h_pip_matche28_eop = iHistoManager.histogram(728, "pi+ matched energy after e/p cut, p=540-560 MeV", 200, 0., 2);
   h_pip_matche29_eop = iHistoManager.histogram(729, "pi+ matched energy after e/p cut, p=560-580 MeV", 200, 0., 2);
   h_pip_matche30_eop = iHistoManager.histogram(730, "pi+ matched energy after e/p cut, p=580-600 MeV", 200, 0., 2);
   h_pip_matche31_eop = iHistoManager.histogram(731, "pi+ matched energy after e/p cut, p=600-620 MeV", 200, 0., 2);
   h_pip_matche32_eop = iHistoManager.histogram(732, "pi+ matched energy after e/p cut, p=620-640 MeV", 200, 0., 2);
   h_pip_matche33_eop = iHistoManager.histogram(733, "pi+ matched energy after e/p cut, p=640-660 MeV", 200, 0., 2);
   h_pip_matche34_eop = iHistoManager.histogram(734, "pi+ matched energy after e/p cut, p=660-680 MeV", 200, 0., 2);
   h_pip_matche35_eop = iHistoManager.histogram(735, "pi+ matched energy after e/p cut, p=680-700 MeV", 200, 0., 2);
   h_pip_matche36_eop = iHistoManager.histogram(736, "pi+ matched energy after e/p cut, p=700-720 MeV", 200, 0., 2);
   h_pip_matche37_eop = iHistoManager.histogram(737, "pi+ matched energy after e/p cut, p=720-740 MeV", 200, 0., 2);
   h_pip_matche38_eop = iHistoManager.histogram(738, "pi+ matched energy after e/p cut, p=740-760 MeV", 200, 0., 2);
   h_pip_matche39_eop = iHistoManager.histogram(739, "pi+ matched energy after e/p cut, p=760-780 MeV", 200, 0., 2);
   h_pip_matche40_eop = iHistoManager.histogram(740, "pi+ matched energy after e/p cut, p=780-800 MeV", 200, 0., 2);
   h_pip_matche41_eop = iHistoManager.histogram(741, "pi+ matched energy after e/p cut, p=800-820 MeV", 200, 0., 2);
   h_pip_matche42_eop = iHistoManager.histogram(742, "pi+ matched energy after e/p cut, p=820-840 MeV", 200, 0., 2);
   h_pip_matche43_eop = iHistoManager.histogram(743, "pi+ matched energy after e/p cut, p=840-860 MeV", 200, 0., 2);
   h_pip_matche44_eop = iHistoManager.histogram(744, "pi+ matched energy after e/p cut, p=860-880 MeV", 200, 0., 2);
   h_pip_matche45_eop = iHistoManager.histogram(745, "pi+ matched energy after e/p cut, p=880-900 MeV", 200, 0., 2);
   h_pip_matche46_eop = iHistoManager.histogram(746, "pi+ matched energy after e/p cut, p=900-920 MeV", 200, 0., 2);
   h_pip_matche47_eop = iHistoManager.histogram(747, "pi+ matched energy after e/p cut, p=920-940 MeV", 200, 0., 2);
   h_pip_matche48_eop = iHistoManager.histogram(748, "pi+ matched energy after e/p cut, p=940-960 MeV", 200, 0., 2);
   h_pip_matche49_eop = iHistoManager.histogram(749, "pi+ matched energy after e/p cut, p=960-980 MeV", 200, 0., 2);
   h_pip_matche50_eop = iHistoManager.histogram(750, "pi+ matched energy after e/p cut, p=980-1000 MeV", 200, 0., 2);
   h_pip_matche51_eop = iHistoManager.histogram(751, "pi+ matched energy after e/p cut, p=1000-1020 MeV", 200, 0., 2);
   h_pip_matche52_eop = iHistoManager.histogram(752, "pi+ matched energy after e/p cut, p=1020-1040 MeV", 200, 0., 2);
   h_pip_matche53_eop = iHistoManager.histogram(753, "pi+ matched energy after e/p cut, p=1040-1060 MeV", 200, 0., 2);
   h_pip_matche54_eop = iHistoManager.histogram(754, "pi+ matched energy after e/p cut, p=1060-1080 MeV", 200, 0., 2);
   h_pip_matche55_eop = iHistoManager.histogram(755, "pi+ matched energy after e/p cut, p=1080-1100 MeV", 200, 0., 2);
   h_pip_matche56_eop = iHistoManager.histogram(756, "pi+ matched energy after e/p cut, p=1100-1120 MeV", 200, 0., 2);
   h_pip_matche57_eop = iHistoManager.histogram(757, "pi+ matched energy after e/p cut, p=1120-1140 MeV", 200, 0., 2);
   h_pip_matche58_eop = iHistoManager.histogram(758, "pi+ matched energy after e/p cut, p=1140-1160 MeV", 200, 0., 2);
   h_pip_matche59_eop = iHistoManager.histogram(759, "pi+ matched energy after e/p cut, p=1160-1180 MeV", 200, 0., 2);
   h_pip_matche60_eop = iHistoManager.histogram(760, "pi+ matched energy after e/p cut, p=1180-1200 MeV", 200, 0., 2);
   h_pip_matche61_eop = iHistoManager.histogram(761, "pi+ matched energy after e/p cut, p=1200-1220 MeV", 200, 0., 2);
   h_pip_matche62_eop = iHistoManager.histogram(762, "pi+ matched energy after e/p cut, p=1220-1240 MeV", 200, 0., 2);
   h_pip_matche63_eop = iHistoManager.histogram(763, "pi+ matched energy after e/p cut, p=1240-1260 MeV", 200, 0., 2);
   h_pip_matche64_eop = iHistoManager.histogram(764, "pi+ matched energy after e/p cut, p=1260-1280 MeV", 200, 0., 2);
   h_pip_matche65_eop = iHistoManager.histogram(765, "pi+ matched energy after e/p cut, p=1280-1300 MeV", 200, 0., 2);
   h_pip_matche66_eop = iHistoManager.histogram(766, "pi+ matched energy after e/p cut, p=1300-1320 MeV", 200, 0., 2);
   h_pip_matche67_eop = iHistoManager.histogram(767, "pi+ matched energy after e/p cut, p=1320-1340 MeV", 200, 0., 2);
   h_pip_matche68_eop = iHistoManager.histogram(768, "pi+ matched energy after e/p cut, p=1340-1360 MeV", 200, 0., 2);
   h_pip_matche69_eop = iHistoManager.histogram(769, "pi+ matched energy after e/p cut, p=1360-1380 MeV", 200, 0., 2);
   h_pip_matche70_eop = iHistoManager.histogram(770, "pi+ matched energy after e/p cut, p=1380-1400 MeV", 200, 0., 2);
   h_pip_matche71_eop = iHistoManager.histogram(771, "pi+ matched energy after e/p cut, p=1400-1420 MeV", 200, 0., 2);
   h_pip_matche72_eop = iHistoManager.histogram(772, "pi+ matched energy after e/p cut, p=1420-1440 MeV", 200, 0., 2);
   h_pip_matche73_eop = iHistoManager.histogram(773, "pi+ matched energy after e/p cut, p=1440-1460 MeV", 200, 0., 2);
   h_pip_matche74_eop = iHistoManager.histogram(774, "pi+ matched energy after e/p cut, p=1460-1480 MeV", 200, 0., 2);
   h_pip_matche75_eop = iHistoManager.histogram(775, "pi+ matched energy after e/p cut, p=1480-1500 MeV", 200, 0., 2);
   h_pip_matche76_eop = iHistoManager.histogram(776, "pi+ matched energy after e/p cut, p=1500-1520 MeV", 200, 0., 2);
   h_pip_matche77_eop = iHistoManager.histogram(777, "pi+ matched energy after e/p cut, p=1520-1540 MeV", 200, 0., 2);
   h_pip_matche78_eop = iHistoManager.histogram(778, "pi+ matched energy after e/p cut, p=1540-1560 MeV", 200, 0., 2);
   h_pip_matche79_eop = iHistoManager.histogram(779, "pi+ matched energy after e/p cut, p=1560-1580 MeV", 200, 0., 2);
   h_pip_matche80_eop = iHistoManager.histogram(780, "pi+ matched energy after e/p cut, p=1580-1600 MeV", 200, 0., 2);
   h_pip_matche81_eop = iHistoManager.histogram(781, "pi+ matched energy after e/p cut, p=1600-1620 MeV", 200, 0., 2);
   h_pip_matche82_eop = iHistoManager.histogram(782, "pi+ matched energy after e/p cut, p=1620-1640 MeV", 200, 0., 2);
   h_pip_matche83_eop = iHistoManager.histogram(783, "pi+ matched energy after e/p cut, p=1640-1660 MeV", 200, 0., 2);
   h_pip_matche84_eop = iHistoManager.histogram(784, "pi+ matched energy after e/p cut, p=1660-1680 MeV", 200, 0., 2);
   h_pip_matche85_eop = iHistoManager.histogram(785, "pi+ matched energy after e/p cut, p=1680-1700 MeV", 200, 0., 2);
   h_pip_matche86_eop = iHistoManager.histogram(786, "pi+ matched energy after e/p cut, p=1700-1720 MeV", 200, 0., 2);
   h_pip_matche87_eop = iHistoManager.histogram(787, "pi+ matched energy after e/p cut, p=1720-1740 MeV", 200, 0., 2);
   h_pip_matche88_eop = iHistoManager.histogram(788, "pi+ matched energy after e/p cut, p=1740-1760 MeV", 200, 0., 2);
   h_pip_matche89_eop = iHistoManager.histogram(789, "pi+ matched energy after e/p cut, p=1760-1780 MeV", 200, 0., 2);
   h_pip_matche90_eop = iHistoManager.histogram(790, "pi+ matched energy after e/p cut, p=1780-1800 MeV", 200, 0., 2);
   h_pip_matche91_eop = iHistoManager.histogram(791, "pi+ matched energy after e/p cut, p=1800-1820 MeV", 200, 0., 2);
   h_pip_matche92_eop = iHistoManager.histogram(792, "pi+ matched energy after e/p cut, p=1820-1840 MeV", 200, 0., 2);
   h_pip_matche93_eop = iHistoManager.histogram(793, "pi+ matched energy after e/p cut, p=1840-1860 MeV", 200, 0., 2);
   h_pip_matche94_eop = iHistoManager.histogram(794, "pi+ matched energy after e/p cut, p=1860-1880 MeV", 200, 0., 2);
   h_pip_matche95_eop = iHistoManager.histogram(795, "pi+ matched energy after e/p cut, p=1880-1900 MeV", 200, 0., 2);
   h_pip_matche96_eop = iHistoManager.histogram(796, "pi+ matched energy after e/p cut, p=1900-1920 MeV", 200, 0., 2);
   h_pip_matche97_eop = iHistoManager.histogram(797, "pi+ matched energy after e/p cut, p=1920-1940 MeV", 200, 0., 2);
   h_pip_matche98_eop = iHistoManager.histogram(798, "pi+ matched energy after e/p cut, p=1940-1960 MeV", 200, 0., 2);
   h_pip_matche99_eop = iHistoManager.histogram(799, "pi+ matched energy after e/p cut, p=1960-1980 MeV", 200, 0., 2);
   h_pip_matche100_eop = iHistoManager.histogram(800, "pi+ matched energy after e/p cut, p=1980-200 MeV", 200, 0., 2);

   h_pim_matche1_eop = iHistoManager.histogram(801, "pi- matched energy after e/p cut, p=0-20 MeV", 200, 0., 2);
   h_pim_matche2_eop = iHistoManager.histogram(802, "pi- matched energy after e/p cut, p=20-40 MeV", 200, 0., 2);
   h_pim_matche3_eop = iHistoManager.histogram(803, "pi- matched energy after e/p cut, p=40-60 MeV", 200, 0., 2);
   h_pim_matche4_eop = iHistoManager.histogram(804, "pi- matched energy after e/p cut, p=60-80 MeV", 200, 0., 2);
   h_pim_matche5_eop = iHistoManager.histogram(805, "pi- matched energy after e/p cut, p=80-100 MeV", 200, 0., 2);
   h_pim_matche6_eop = iHistoManager.histogram(806, "pi- matched energy after e/p cut, p=100-120 MeV", 200, 0., 2);
   h_pim_matche7_eop = iHistoManager.histogram(807, "pi- matched energy after e/p cut, p=120-140 MeV", 200, 0., 2);
   h_pim_matche8_eop = iHistoManager.histogram(808, "pi- matched energy after e/p cut, p=140-160 MeV", 200, 0., 2);
   h_pim_matche9_eop = iHistoManager.histogram(809, "pi- matched energy after e/p cut, p=160-180 MeV", 200, 0., 2);
   h_pim_matche10_eop = iHistoManager.histogram(810, "pi- matched energy after e/p cut, p=180-200 MeV", 200, 0., 2);
   h_pim_matche11_eop = iHistoManager.histogram(811, "pi- matched energy after e/p cut, p=200-220 MeV", 200, 0., 2);
   h_pim_matche12_eop = iHistoManager.histogram(812, "pi- matched energy after e/p cut, p=220-240 MeV", 200, 0., 2);
   h_pim_matche13_eop = iHistoManager.histogram(813, "pi- matched energy after e/p cut, p=240-260 MeV", 200, 0., 2);
   h_pim_matche14_eop = iHistoManager.histogram(814, "pi- matched energy after e/p cut, p=260-280 MeV", 200, 0., 2);
   h_pim_matche15_eop = iHistoManager.histogram(815, "pi- matched energy after e/p cut, p=280-300 MeV", 200, 0., 2);
   h_pim_matche16_eop = iHistoManager.histogram(816, "pi- matched energy after e/p cut, p=300-800 MeV", 200, 0., 2);
   h_pim_matche17_eop = iHistoManager.histogram(817, "pi- matched energy after e/p cut, p=320-850 MeV", 200, 0., 2);
   h_pim_matche18_eop = iHistoManager.histogram(818, "pi- matched energy after e/p cut, p=340-900 MeV", 200, 0., 2);
   h_pim_matche19_eop = iHistoManager.histogram(819, "pi- matched energy after e/p cut, p=360-950 MeV", 200, 0., 2);
   h_pim_matche20_eop = iHistoManager.histogram(820, "pi- matched energy after e/p cut, p=380-400 MeV", 200, 0., 2);
   h_pim_matche21_eop = iHistoManager.histogram(821, "pi- matched energy after e/p cut, p=400-420 MeV", 200, 0., 2);
   h_pim_matche22_eop = iHistoManager.histogram(822, "pi- matched energy after e/p cut, p=420-440 MeV", 200, 0., 2);
   h_pim_matche23_eop = iHistoManager.histogram(823, "pi- matched energy after e/p cut, p=440-460 MeV", 200, 0., 2);
   h_pim_matche24_eop = iHistoManager.histogram(824, "pi- matched energy after e/p cut, p=460-480 MeV", 200, 0., 2);
   h_pim_matche25_eop = iHistoManager.histogram(825, "pi- matched energy after e/p cut, p=480-500 MeV", 200, 0., 2);
   h_pim_matche26_eop = iHistoManager.histogram(826, "pi- matched energy after e/p cut, p=500-520 MeV", 200, 0., 2);
   h_pim_matche27_eop = iHistoManager.histogram(827, "pi- matched energy after e/p cut, p=520-540 MeV", 200, 0., 2);
   h_pim_matche28_eop = iHistoManager.histogram(828, "pi- matched energy after e/p cut, p=540-560 MeV", 200, 0., 2);
   h_pim_matche29_eop = iHistoManager.histogram(829, "pi- matched energy after e/p cut, p=560-580 MeV", 200, 0., 2);
   h_pim_matche30_eop = iHistoManager.histogram(830, "pi- matched energy after e/p cut, p=580-600 MeV", 200, 0., 2);
   h_pim_matche31_eop = iHistoManager.histogram(831, "pi- matched energy after e/p cut, p=600-620 MeV", 200, 0., 2);
   h_pim_matche32_eop = iHistoManager.histogram(832, "pi- matched energy after e/p cut, p=620-640 MeV", 200, 0., 2);
   h_pim_matche33_eop = iHistoManager.histogram(833, "pi- matched energy after e/p cut, p=640-660 MeV", 200, 0., 2);
   h_pim_matche34_eop = iHistoManager.histogram(834, "pi- matched energy after e/p cut, p=660-680 MeV", 200, 0., 2);
   h_pim_matche35_eop = iHistoManager.histogram(835, "pi- matched energy after e/p cut, p=680-700 MeV", 200, 0., 2);
   h_pim_matche36_eop = iHistoManager.histogram(836, "pi- matched energy after e/p cut, p=700-720 MeV", 200, 0., 2);
   h_pim_matche37_eop = iHistoManager.histogram(837, "pi- matched energy after e/p cut, p=720-740 MeV", 200, 0., 2);
   h_pim_matche38_eop = iHistoManager.histogram(838, "pi- matched energy after e/p cut, p=740-760 MeV", 200, 0., 2);
   h_pim_matche39_eop = iHistoManager.histogram(839, "pi- matched energy after e/p cut, p=760-780 MeV", 200, 0., 2);
   h_pim_matche40_eop = iHistoManager.histogram(840, "pi- matched energy after e/p cut, p=780-800 MeV", 200, 0., 2);
   h_pim_matche41_eop = iHistoManager.histogram(841, "pi- matched energy after e/p cut, p=800-820 MeV", 200, 0., 2);
   h_pim_matche42_eop = iHistoManager.histogram(842, "pi- matched energy after e/p cut, p=820-840 MeV", 200, 0., 2);
   h_pim_matche43_eop = iHistoManager.histogram(843, "pi- matched energy after e/p cut, p=840-860 MeV", 200, 0., 2);
   h_pim_matche44_eop = iHistoManager.histogram(844, "pi- matched energy after e/p cut, p=860-880 MeV", 200, 0., 2);
   h_pim_matche45_eop = iHistoManager.histogram(845, "pi- matched energy after e/p cut, p=880-900 MeV", 200, 0., 2);
   h_pim_matche46_eop = iHistoManager.histogram(846, "pi- matched energy after e/p cut, p=900-920 MeV", 200, 0., 2);
   h_pim_matche47_eop = iHistoManager.histogram(847, "pi- matched energy after e/p cut, p=920-940 MeV", 200, 0., 2);
   h_pim_matche48_eop = iHistoManager.histogram(848, "pi- matched energy after e/p cut, p=940-960 MeV", 200, 0., 2);
   h_pim_matche49_eop = iHistoManager.histogram(849, "pi- matched energy after e/p cut, p=960-980 MeV", 200, 0., 2);
   h_pim_matche50_eop = iHistoManager.histogram(850, "pi- matched energy after e/p cut, p=980-1000 MeV", 200, 0., 2);
   h_pim_matche51_eop = iHistoManager.histogram(851, "pi- matched energy after e/p cut, p=1000-1020 MeV", 200, 0., 2);
   h_pim_matche52_eop = iHistoManager.histogram(852, "pi- matched energy after e/p cut, p=1020-1040 MeV", 200, 0., 2);
   h_pim_matche53_eop = iHistoManager.histogram(853, "pi- matched energy after e/p cut, p=1040-1060 MeV", 200, 0., 2);
   h_pim_matche54_eop = iHistoManager.histogram(854, "pi- matched energy after e/p cut, p=1060-1080 MeV", 200, 0., 2);
   h_pim_matche55_eop = iHistoManager.histogram(855, "pi- matched energy after e/p cut, p=1080-1100 MeV", 200, 0., 2);
   h_pim_matche56_eop = iHistoManager.histogram(856, "pi- matched energy after e/p cut, p=1100-1120 MeV", 200, 0., 2);
   h_pim_matche57_eop = iHistoManager.histogram(857, "pi- matched energy after e/p cut, p=1120-1140 MeV", 200, 0., 2);
   h_pim_matche58_eop = iHistoManager.histogram(858, "pi- matched energy after e/p cut, p=1140-1160 MeV", 200, 0., 2);
   h_pim_matche59_eop = iHistoManager.histogram(859, "pi- matched energy after e/p cut, p=1160-1180 MeV", 200, 0., 2);
   h_pim_matche60_eop = iHistoManager.histogram(860, "pi- matched energy after e/p cut, p=1180-1200 MeV", 200, 0., 2);
   h_pim_matche61_eop = iHistoManager.histogram(861, "pi- matched energy after e/p cut, p=1200-1220 MeV", 200, 0., 2);
   h_pim_matche62_eop = iHistoManager.histogram(862, "pi- matched energy after e/p cut, p=1220-1240 MeV", 200, 0., 2);
   h_pim_matche63_eop = iHistoManager.histogram(863, "pi- matched energy after e/p cut, p=1240-1260 MeV", 200, 0., 2);
   h_pim_matche64_eop = iHistoManager.histogram(864, "pi- matched energy after e/p cut, p=1260-1280 MeV", 200, 0., 2);
   h_pim_matche65_eop = iHistoManager.histogram(865, "pi- matched energy after e/p cut, p=1280-1300 MeV", 200, 0., 2);
   h_pim_matche66_eop = iHistoManager.histogram(866, "pi- matched energy after e/p cut, p=1300-1320 MeV", 200, 0., 2);
   h_pim_matche67_eop = iHistoManager.histogram(867, "pi- matched energy after e/p cut, p=1320-1340 MeV", 200, 0., 2);
   h_pim_matche68_eop = iHistoManager.histogram(868, "pi- matched energy after e/p cut, p=1340-1360 MeV", 200, 0., 2);
   h_pim_matche69_eop = iHistoManager.histogram(869, "pi- matched energy after e/p cut, p=1360-1380 MeV", 200, 0., 2);
   h_pim_matche70_eop = iHistoManager.histogram(870, "pi- matched energy after e/p cut, p=1380-1400 MeV", 200, 0., 2);
   h_pim_matche71_eop = iHistoManager.histogram(871, "pi- matched energy after e/p cut, p=1400-1420 MeV", 200, 0., 2);
   h_pim_matche72_eop = iHistoManager.histogram(872, "pi- matched energy after e/p cut, p=1420-1440 MeV", 200, 0., 2);
   h_pim_matche73_eop = iHistoManager.histogram(873, "pi- matched energy after e/p cut, p=1440-1460 MeV", 200, 0., 2);
   h_pim_matche74_eop = iHistoManager.histogram(874, "pi- matched energy after e/p cut, p=1460-1480 MeV", 200, 0., 2);
   h_pim_matche75_eop = iHistoManager.histogram(875, "pi- matched energy after e/p cut, p=1480-1500 MeV", 200, 0., 2);
   h_pim_matche76_eop = iHistoManager.histogram(876, "pi- matched energy after e/p cut, p=1500-1520 MeV", 200, 0., 2);
   h_pim_matche77_eop = iHistoManager.histogram(877, "pi- matched energy after e/p cut, p=1520-1540 MeV", 200, 0., 2);
   h_pim_matche78_eop = iHistoManager.histogram(878, "pi- matched energy after e/p cut, p=1540-1560 MeV", 200, 0., 2);
   h_pim_matche79_eop = iHistoManager.histogram(879, "pi- matched energy after e/p cut, p=1560-1580 MeV", 200, 0., 2);
   h_pim_matche80_eop = iHistoManager.histogram(880, "pi- matched energy after e/p cut, p=1580-1600 MeV", 200, 0., 2);
   h_pim_matche81_eop = iHistoManager.histogram(881, "pi- matched energy after e/p cut, p=1600-1620 MeV", 200, 0., 2);
   h_pim_matche82_eop = iHistoManager.histogram(882, "pi- matched energy after e/p cut, p=1620-1640 MeV", 200, 0., 2);
   h_pim_matche83_eop = iHistoManager.histogram(883, "pi- matched energy after e/p cut, p=1640-1660 MeV", 200, 0., 2);
   h_pim_matche84_eop = iHistoManager.histogram(884, "pi- matched energy after e/p cut, p=1660-1680 MeV", 200, 0., 2);
   h_pim_matche85_eop = iHistoManager.histogram(885, "pi- matched energy after e/p cut, p=1680-1700 MeV", 200, 0., 2);
   h_pim_matche86_eop = iHistoManager.histogram(886, "pi- matched energy after e/p cut, p=1700-1720 MeV", 200, 0., 2);
   h_pim_matche87_eop = iHistoManager.histogram(887, "pi- matched energy after e/p cut, p=1720-1740 MeV", 200, 0., 2);
   h_pim_matche88_eop = iHistoManager.histogram(888, "pi- matched energy after e/p cut, p=1740-1760 MeV", 200, 0., 2);
   h_pim_matche89_eop = iHistoManager.histogram(889, "pi- matched energy after e/p cut, p=1760-1780 MeV", 200, 0., 2);
   h_pim_matche90_eop = iHistoManager.histogram(890, "pi- matched energy after e/p cut, p=1780-1800 MeV", 200, 0., 2);
   h_pim_matche91_eop = iHistoManager.histogram(891, "pi- matched energy after e/p cut, p=1800-1820 MeV", 200, 0., 2);
   h_pim_matche92_eop = iHistoManager.histogram(892, "pi- matched energy after e/p cut, p=1820-1840 MeV", 200, 0., 2);
   h_pim_matche93_eop = iHistoManager.histogram(893, "pi- matched energy after e/p cut, p=1840-1860 MeV", 200, 0., 2);
   h_pim_matche94_eop = iHistoManager.histogram(894, "pi- matched energy after e/p cut, p=1860-1880 MeV", 200, 0., 2);
   h_pim_matche95_eop = iHistoManager.histogram(895, "pi- matched energy after e/p cut, p=1880-1900 MeV", 200, 0., 2);
   h_pim_matche96_eop = iHistoManager.histogram(896, "pi- matched energy after e/p cut, p=1900-1920 MeV", 200, 0., 2);
   h_pim_matche97_eop = iHistoManager.histogram(897, "pi- matched energy after e/p cut, p=1920-1940 MeV", 200, 0., 2);
   h_pim_matche98_eop = iHistoManager.histogram(898, "pi- matched energy after e/p cut, p=1940-1960 MeV", 200, 0., 2);
   h_pim_matche99_eop = iHistoManager.histogram(899, "pi- matched energy after e/p cut, p=1960-1980 MeV", 200, 0., 2);
   h_pim_matche100_eop = iHistoManager.histogram(900, "pi- matched energy after e/p cut, p=1980-2000 MeV", 200, 0., 2);


   h_kaon_matche = iHistoManager.histogram(2000, "kaon matched energy", 200, 0., 2.);
   h_kp_matche1 = iHistoManager.histogram(2001, "K+ matched energy, p=0-100 MeV", 200, 0., 2.);
   h_kp_matche2 = iHistoManager.histogram(2002, "K+ matched energy, p=100-200 MeV", 200, 0., 2.);
   h_kp_matche3 = iHistoManager.histogram(2003, "K+ matched energy, p=200-300 MeV", 200, 0., 2.);
   h_kp_matche4 = iHistoManager.histogram(2004, "K+ matched energy, p=300-400 MeV", 200, 0., 2.);
   h_kp_matche5 = iHistoManager.histogram(2005, "K+ matched energy, p=400-500 MeV", 200, 0., 2.);
   h_kp_matche6 = iHistoManager.histogram(2006, "K+ matched energy, p=500-600 MeV", 200, 0., 2.);
   h_kp_matche7 = iHistoManager.histogram(2007, "K+ matched energy, p=600-700 MeV", 200, 0., 2.);
   h_kp_matche8 = iHistoManager.histogram(2008, "K+ matched energy, p=700-800 MeV", 200, 0., 2.);
   h_kp_matche9 = iHistoManager.histogram(2009, "K+ matched energy, p=800-900 MeV", 200, 0., 2.);
   h_kp_matche10 = iHistoManager.histogram(2100, "K+ matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_kp_matche11 = iHistoManager.histogram(2101, "K+ matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_kp_matche12 = iHistoManager.histogram(2102, "K+ matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_kp_matche13 = iHistoManager.histogram(2103, "K+ matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_kp_matche14 = iHistoManager.histogram(2104, "K+ matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_kp_matche15 = iHistoManager.histogram(2105, "K+ matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_kp_matche16 = iHistoManager.histogram(2106, "K+ matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_kp_matche17 = iHistoManager.histogram(2107, "K+ matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_kp_matche18 = iHistoManager.histogram(2108, "K+ matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_kp_matche19 = iHistoManager.histogram(2109, "K+ matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_kp_matche20 = iHistoManager.histogram(2200, "K+ matched energy, p=1900-2000 MeV", 200, 0., 2.);
   h_km_matche1 = iHistoManager.histogram(2201, "K- matched energy, p=0-100 MeV", 200, 0., 2.);
   h_km_matche2 = iHistoManager.histogram(2202, "K- matched energy, p=100-200 MeV", 200, 0., 2.);
   h_km_matche3 = iHistoManager.histogram(2203, "K- matched energy, p=200-300 MeV", 200, 0., 2.);
   h_km_matche4 = iHistoManager.histogram(2204, "K- matched energy, p=300-400 MeV", 200, 0., 2.);
   h_km_matche5 = iHistoManager.histogram(2205, "K- matched energy, p=400-500 MeV", 200, 0., 2.);
   h_km_matche6 = iHistoManager.histogram(2206, "K- matched energy, p=500-600 MeV", 200, 0., 2.);
   h_km_matche7 = iHistoManager.histogram(2207, "K- matched energy, p=600-700 MeV", 200, 0., 2.);
   h_km_matche8 = iHistoManager.histogram(2208, "K- matched energy, p=700-800 MeV", 200, 0., 2.);
   h_km_matche9 = iHistoManager.histogram(2209, "K- matched energy, p=800-900 MeV", 200, 0., 2.);
   h_km_matche10 = iHistoManager.histogram(2300, "K- matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_km_matche11 = iHistoManager.histogram(2301, "K- matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_km_matche12 = iHistoManager.histogram(2302, "K- matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_km_matche13 = iHistoManager.histogram(2303, "K- matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_km_matche14 = iHistoManager.histogram(2304, "K- matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_km_matche15 = iHistoManager.histogram(2305, "K- matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_km_matche16 = iHistoManager.histogram(2306, "K- matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_km_matche17 = iHistoManager.histogram(2307, "K- matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_km_matche18 = iHistoManager.histogram(2308, "K- matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_km_matche19 = iHistoManager.histogram(2309, "K- matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_km_matche20 = iHistoManager.histogram(2400, "K- matched energy, p=1900-2000 MeV", 200, 0., 2.);

   h_proton_matche = iHistoManager.histogram(3000, "proton matched energy", 200, 0., 2.);
   h_pp_matche1 = iHistoManager.histogram(3001, "proton matched energy, p=0-100 MeV", 200, 0., 2.);
   h_pp_matche2 = iHistoManager.histogram(3002, "proton matched energy, p=100-200 MeV", 200, 0., 2.);
   h_pp_matche3 = iHistoManager.histogram(3003, "proton matched energy, p=200-300 MeV", 200, 0., 2.);
   h_pp_matche4 = iHistoManager.histogram(3004, "proton matched energy, p=300-400 MeV", 200, 0., 2.);
   h_pp_matche5 = iHistoManager.histogram(3005, "proton matched energy, p=400-500 MeV", 200, 0., 2.);
   h_pp_matche6 = iHistoManager.histogram(3006, "proton matched energy, p=500-600 MeV", 200, 0., 2.);
   h_pp_matche7 = iHistoManager.histogram(3007, "proton matched energy, p=600-700 MeV", 200, 0., 2.);
   h_pp_matche8 = iHistoManager.histogram(3008, "proton matched energy, p=700-800 MeV", 200, 0., 2.);
   h_pp_matche9 = iHistoManager.histogram(3009, "proton matched energy, p=800-900 MeV", 200, 0., 2.);
   h_pp_matche10 = iHistoManager.histogram(3100, "proton matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_pp_matche11 = iHistoManager.histogram(3101, "proton matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_pp_matche12 = iHistoManager.histogram(3102, "proton matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_pp_matche13 = iHistoManager.histogram(3103, "proton matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_pp_matche14 = iHistoManager.histogram(3104, "proton matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_pp_matche15 = iHistoManager.histogram(3105, "proton matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_pp_matche16 = iHistoManager.histogram(3106, "proton matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_pp_matche17 = iHistoManager.histogram(3107, "proton matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_pp_matche18 = iHistoManager.histogram(3108, "proton matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_pp_matche19 = iHistoManager.histogram(3109, "proton matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_pp_matche20 = iHistoManager.histogram(3200, "proton matched energy, p=1900-2000 MeV", 200, 0., 2.);
   h_pm_matche1 = iHistoManager.histogram(3201, "anti-proton matched energy, p=0-100 MeV", 200, 0., 2.);
   h_pm_matche2 = iHistoManager.histogram(3202, "anti-proton matched energy, p=100-200 MeV", 200, 0., 2.);
   h_pm_matche3 = iHistoManager.histogram(3203, "anti-proton matched energy, p=200-300 MeV", 200, 0., 2.);
   h_pm_matche4 = iHistoManager.histogram(3204, "anti-proton matched energy, p=300-400 MeV", 200, 0., 2.);
   h_pm_matche5 = iHistoManager.histogram(3205, "anti-proton matched energy, p=400-500 MeV", 200, 0., 2.);
   h_pm_matche6 = iHistoManager.histogram(3206, "anti-proton matched energy, p=500-600 MeV", 200, 0., 2.);
   h_pm_matche7 = iHistoManager.histogram(3207, "anti-proton matched energy, p=600-700 MeV", 200, 0., 2.);
   h_pm_matche8 = iHistoManager.histogram(3208, "anti-proton matched energy, p=700-800 MeV", 200, 0., 2.);
   h_pm_matche9 = iHistoManager.histogram(3209, "anti-proton matched energy, p=800-900 MeV", 200, 0., 2.);
   h_pm_matche10 = iHistoManager.histogram(3300, "anti-proton matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_pm_matche11 = iHistoManager.histogram(3301, "anti-proton matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_pm_matche12 = iHistoManager.histogram(3302, "anti-proton matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_pm_matche13 = iHistoManager.histogram(3303, "anti-proton matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_pm_matche14 = iHistoManager.histogram(3304, "anti-proton matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_pm_matche15 = iHistoManager.histogram(3305, "anti-proton matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_pm_matche16 = iHistoManager.histogram(3306, "anti-proton matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_pm_matche17 = iHistoManager.histogram(3307, "anti-proton matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_pm_matche18 = iHistoManager.histogram(3308, "anti-proton matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_pm_matche19 = iHistoManager.histogram(3309, "anti-proton matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_pm_matche20 = iHistoManager.histogram(3400, "anti-proton matched energy, p=1900-2000 MeV", 200, 0., 2.);


   h_pion_matche_endcap = iHistoManager.histogram(1500, "pion matched energy", 200, 0., 2.);
   h_pion_matche1_endcap = iHistoManager.histogram(1501, "pion matched energy, p=0-100 MeV", 200, 0., 2.);
   h_pion_matche2_endcap = iHistoManager.histogram(1502, "pion matched energy, p=100-200 MeV", 200, 0., 2.);
   h_pion_matche3_endcap = iHistoManager.histogram(1503, "pion matched energy, p=200-300 MeV", 200, 0., 2.);
   h_pion_matche4_endcap = iHistoManager.histogram(1504, "pion matched energy, p=300-400 MeV", 200, 0., 2.);
   h_pion_matche5_endcap = iHistoManager.histogram(1505, "pion matched energy, p=400-500 MeV", 200, 0., 2.);
   h_pion_matche6_endcap = iHistoManager.histogram(1506, "pion matched energy, p=500-600 MeV", 200, 0., 2.);
   h_pion_matche7_endcap = iHistoManager.histogram(1507, "pion matched energy, p=600-700 MeV", 200, 0., 2.);
   h_pion_matche8_endcap = iHistoManager.histogram(1508, "pion matched energy, p=700-800 MeV", 200, 0., 2.);
   h_pion_matche9_endcap = iHistoManager.histogram(1509, "pion matched energy, p=800-900 MeV", 200, 0., 2.);
   h_pion_matche10_endcap = iHistoManager.histogram(1600, "pion matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_pion_matche11_endcap = iHistoManager.histogram(1601, "pion matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_pion_matche12_endcap = iHistoManager.histogram(1602, "pion matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_pion_matche13_endcap = iHistoManager.histogram(1603, "pion matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_pion_matche14_endcap = iHistoManager.histogram(1604, "pion matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_pion_matche15_endcap = iHistoManager.histogram(1605, "pion matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_pion_matche16_endcap = iHistoManager.histogram(1606, "pion matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_pion_matche17_endcap = iHistoManager.histogram(1607, "pion matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_pion_matche18_endcap = iHistoManager.histogram(1608, "pion matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_pion_matche19_endcap = iHistoManager.histogram(1609, "pion matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_pion_matche20_endcap = iHistoManager.histogram(1700, "pion matched energy, p=1900-2000 MeV", 200, 0., 2.);

   h_kaon_matche_endcap = iHistoManager.histogram(2500, "kaon matched energy", 200, 0., 2.);
   h_kaon_matche1_endcap = iHistoManager.histogram(2501, "kaon matched energy, p=0-100 MeV", 200, 0., 2.);
   h_kaon_matche2_endcap = iHistoManager.histogram(2502, "kaon matched energy, p=100-200 MeV", 200, 0., 2.);
   h_kaon_matche3_endcap = iHistoManager.histogram(2503, "kaon matched energy, p=200-300 MeV", 200, 0., 2.);
   h_kaon_matche4_endcap = iHistoManager.histogram(2504, "kaon matched energy, p=300-400 MeV", 200, 0., 2.);
   h_kaon_matche5_endcap = iHistoManager.histogram(2505, "kaon matched energy, p=400-500 MeV", 200, 0., 2.);
   h_kaon_matche6_endcap = iHistoManager.histogram(2506, "kaon matched energy, p=500-600 MeV", 200, 0., 2.);
   h_kaon_matche7_endcap = iHistoManager.histogram(2507, "kaon matched energy, p=600-700 MeV", 200, 0., 2.);
   h_kaon_matche8_endcap = iHistoManager.histogram(2508, "kaon matched energy, p=700-800 MeV", 200, 0., 2.);
   h_kaon_matche9_endcap = iHistoManager.histogram(2509, "kaon matched energy, p=800-900 MeV", 200, 0., 2.);
   h_kaon_matche10_endcap = iHistoManager.histogram(2600, "kaon matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_kaon_matche11_endcap = iHistoManager.histogram(2601, "kaon matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_kaon_matche12_endcap = iHistoManager.histogram(2602, "kaon matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_kaon_matche13_endcap = iHistoManager.histogram(2603, "kaon matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_kaon_matche14_endcap = iHistoManager.histogram(2604, "kaon matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_kaon_matche15_endcap = iHistoManager.histogram(2605, "kaon matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_kaon_matche16_endcap = iHistoManager.histogram(2606, "kaon matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_kaon_matche17_endcap = iHistoManager.histogram(2607, "kaon matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_kaon_matche18_endcap = iHistoManager.histogram(2608, "kaon matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_kaon_matche19_endcap = iHistoManager.histogram(2609, "kaon matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_kaon_matche20_endcap = iHistoManager.histogram(2700, "kaon matched energy, p=1900-2000 MeV", 200, 0., 2.);

   h_proton_matche_endcap = iHistoManager.histogram(3500, "proton matched energy", 200, 0., 2.);
   h_proton_matche1_endcap = iHistoManager.histogram(3501, "proton matched energy, p=0-100 MeV", 200, 0., 2.);
   h_proton_matche2_endcap = iHistoManager.histogram(3502, "proton matched energy, p=100-200 MeV", 200, 0., 2.);
   h_proton_matche3_endcap = iHistoManager.histogram(3503, "proton matched energy, p=200-300 MeV", 200, 0., 2.);
   h_proton_matche4_endcap = iHistoManager.histogram(3504, "proton matched energy, p=300-400 MeV", 200, 0., 2.);
   h_proton_matche5_endcap = iHistoManager.histogram(3505, "proton matched energy, p=400-500 MeV", 200, 0., 2.);
   h_proton_matche6_endcap = iHistoManager.histogram(3506, "proton matched energy, p=500-600 MeV", 200, 0., 2.);
   h_proton_matche7_endcap = iHistoManager.histogram(3507, "proton matched energy, p=600-700 MeV", 200, 0., 2.);
   h_proton_matche8_endcap = iHistoManager.histogram(3508, "proton matched energy, p=700-800 MeV", 200, 0., 2.);
   h_proton_matche9_endcap = iHistoManager.histogram(3509, "proton matched energy, p=800-900 MeV", 200, 0., 2.);
   h_proton_matche10_endcap = iHistoManager.histogram(3600, "proton matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_proton_matche11_endcap = iHistoManager.histogram(3601, "proton matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_proton_matche12_endcap = iHistoManager.histogram(3602, "proton matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_proton_matche13_endcap = iHistoManager.histogram(3603, "proton matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_proton_matche14_endcap = iHistoManager.histogram(3604, "proton matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_proton_matche15_endcap = iHistoManager.histogram(3605, "proton matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_proton_matche16_endcap = iHistoManager.histogram(3606, "proton matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_proton_matche17_endcap = iHistoManager.histogram(3607, "proton matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_proton_matche18_endcap = iHistoManager.histogram(3608, "proton matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_proton_matche19_endcap = iHistoManager.histogram(3609, "proton matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_proton_matche20_endcap = iHistoManager.histogram(3700, "proton matched energy, p=1900-2000 MeV", 200, 0., 2.);

   // cos theta cuts
   h_pion_matche_cut1 = iHistoManager.histogram(1100, "pion matched energy", 200, 0., 2.);
   h_pip_matche1_cut1 = iHistoManager.histogram(1101, "pi+ matched energy, p=0-100 MeV", 200, 0., 2.);
   h_pip_matche2_cut1 = iHistoManager.histogram(1102, "pi+ matched energy, p=100-200 MeV", 200, 0., 2.);
   h_pip_matche3_cut1 = iHistoManager.histogram(1103, "pi+ matched energy, p=200-300 MeV", 200, 0., 2.);
   h_pip_matche4_cut1 = iHistoManager.histogram(1104, "pi+ matched energy, p=300-400 MeV", 200, 0., 2.);
   h_pip_matche5_cut1 = iHistoManager.histogram(1105, "pi+ matched energy, p=400-500 MeV", 200, 0., 2.);
   h_pip_matche6_cut1 = iHistoManager.histogram(1106, "pi+ matched energy, p=500-600 MeV", 200, 0., 2.);
   h_pip_matche7_cut1 = iHistoManager.histogram(1107, "pi+ matched energy, p=600-700 MeV", 200, 0., 2.);
   h_pip_matche8_cut1 = iHistoManager.histogram(1108, "pi+ matched energy, p=700-800 MeV", 200, 0., 2.);
   h_pip_matche9_cut1 = iHistoManager.histogram(1109, "pi+ matched energy, p=800-900 MeV", 200, 0., 2.);
   h_pip_matche10_cut1 = iHistoManager.histogram(1110, "pi+ matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_pip_matche11_cut1 = iHistoManager.histogram(1111, "pi+ matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_pip_matche12_cut1 = iHistoManager.histogram(1112, "pi+ matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_pip_matche13_cut1 = iHistoManager.histogram(1113, "pi+ matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_pip_matche14_cut1 = iHistoManager.histogram(1114, "pi+ matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_pip_matche15_cut1 = iHistoManager.histogram(1115, "pi+ matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_pip_matche16_cut1 = iHistoManager.histogram(1116, "pi+ matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_pip_matche17_cut1 = iHistoManager.histogram(1117, "pi+ matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_pip_matche18_cut1 = iHistoManager.histogram(1118, "pi+ matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_pip_matche19_cut1 = iHistoManager.histogram(1119, "pi+ matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_pip_matche20_cut1 = iHistoManager.histogram(1120, "pi+ matched energy, p=1900-2000 MeV", 200, 0., 2.);
   h_pim_matche1_cut1 = iHistoManager.histogram(1121, "pi- matched energy, p=0-100 MeV", 200, 0., 2.);
   h_pim_matche2_cut1 = iHistoManager.histogram(1122, "pi- matched energy, p=100-200 MeV", 200, 0., 2.);
   h_pim_matche3_cut1 = iHistoManager.histogram(1123, "pi- matched energy, p=200-300 MeV", 200, 0., 2.);
   h_pim_matche4_cut1 = iHistoManager.histogram(1124, "pi- matched energy, p=300-400 MeV", 200, 0., 2.);
   h_pim_matche5_cut1 = iHistoManager.histogram(1125, "pi- matched energy, p=400-500 MeV", 200, 0., 2.);
   h_pim_matche6_cut1 = iHistoManager.histogram(1126, "pi- matched energy, p=500-600 MeV", 200, 0., 2.);
   h_pim_matche7_cut1 = iHistoManager.histogram(1127, "pi- matched energy, p=600-700 MeV", 200, 0., 2.);
   h_pim_matche8_cut1 = iHistoManager.histogram(1128, "pi- matched energy, p=700-800 MeV", 200, 0., 2.);
   h_pim_matche9_cut1 = iHistoManager.histogram(1129, "pi- matched energy, p=800-900 MeV", 200, 0., 2.);
   h_pim_matche10_cut1 = iHistoManager.histogram(1130, "pi- matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_pim_matche11_cut1 = iHistoManager.histogram(1131, "pi- matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_pim_matche12_cut1 = iHistoManager.histogram(1132, "pi- matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_pim_matche13_cut1 = iHistoManager.histogram(1133, "pi- matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_pim_matche14_cut1 = iHistoManager.histogram(1134, "pi- matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_pim_matche15_cut1 = iHistoManager.histogram(1135, "pi- matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_pim_matche16_cut1 = iHistoManager.histogram(1136, "pi- matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_pim_matche17_cut1 = iHistoManager.histogram(1137, "pi- matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_pim_matche18_cut1 = iHistoManager.histogram(1138, "pi- matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_pim_matche19_cut1 = iHistoManager.histogram(1139, "pi- matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_pim_matche20_cut1 = iHistoManager.histogram(1140, "pi- matched energy, p=1900-2000 MeV", 200, 0., 2.);

   h_pion_matche_cut2 = iHistoManager.histogram(2100, "pion matched energy", 200, 0., 2.);
   h_pip_matche1_cut2 = iHistoManager.histogram(2101, "pi+ matched energy, p=0-100 MeV", 200, 0., 2.);
   h_pip_matche2_cut2 = iHistoManager.histogram(2102, "pi+ matched energy, p=100-200 MeV", 200, 0., 2.);
   h_pip_matche3_cut2 = iHistoManager.histogram(2103, "pi+ matched energy, p=200-300 MeV", 200, 0., 2.);
   h_pip_matche4_cut2 = iHistoManager.histogram(2104, "pi+ matched energy, p=300-400 MeV", 200, 0., 2.);
   h_pip_matche5_cut2 = iHistoManager.histogram(2105, "pi+ matched energy, p=400-500 MeV", 200, 0., 2.);
   h_pip_matche6_cut2 = iHistoManager.histogram(2106, "pi+ matched energy, p=500-600 MeV", 200, 0., 2.);
   h_pip_matche7_cut2 = iHistoManager.histogram(2107, "pi+ matched energy, p=600-700 MeV", 200, 0., 2.);
   h_pip_matche8_cut2 = iHistoManager.histogram(2108, "pi+ matched energy, p=700-800 MeV", 200, 0., 2.);
   h_pip_matche9_cut2 = iHistoManager.histogram(2109, "pi+ matched energy, p=800-900 MeV", 200, 0., 2.);
   h_pip_matche10_cut2 = iHistoManager.histogram(2110, "pi+ matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_pip_matche11_cut2 = iHistoManager.histogram(2111, "pi+ matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_pip_matche12_cut2 = iHistoManager.histogram(2112, "pi+ matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_pip_matche13_cut2 = iHistoManager.histogram(2113, "pi+ matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_pip_matche14_cut2 = iHistoManager.histogram(2114, "pi+ matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_pip_matche15_cut2 = iHistoManager.histogram(2115, "pi+ matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_pip_matche16_cut2 = iHistoManager.histogram(2116, "pi+ matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_pip_matche17_cut2 = iHistoManager.histogram(2117, "pi+ matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_pip_matche18_cut2 = iHistoManager.histogram(2118, "pi+ matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_pip_matche19_cut2 = iHistoManager.histogram(2119, "pi+ matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_pip_matche20_cut2 = iHistoManager.histogram(2120, "pi+ matched energy, p=1900-2000 MeV", 200, 0., 2.);
   h_pim_matche1_cut2 = iHistoManager.histogram(2121, "pi- matched energy, p=0-100 MeV", 200, 0., 2.);
   h_pim_matche2_cut2 = iHistoManager.histogram(2122, "pi- matched energy, p=100-200 MeV", 200, 0., 2.);
   h_pim_matche3_cut2 = iHistoManager.histogram(2123, "pi- matched energy, p=200-300 MeV", 200, 0., 2.);
   h_pim_matche4_cut2 = iHistoManager.histogram(2124, "pi- matched energy, p=300-400 MeV", 200, 0., 2.);
   h_pim_matche5_cut2 = iHistoManager.histogram(2125, "pi- matched energy, p=400-500 MeV", 200, 0., 2.);
   h_pim_matche6_cut2 = iHistoManager.histogram(2126, "pi- matched energy, p=500-600 MeV", 200, 0., 2.);
   h_pim_matche7_cut2 = iHistoManager.histogram(2127, "pi- matched energy, p=600-700 MeV", 200, 0., 2.);
   h_pim_matche8_cut2 = iHistoManager.histogram(2128, "pi- matched energy, p=700-800 MeV", 200, 0., 2.);
   h_pim_matche9_cut2 = iHistoManager.histogram(2129, "pi- matched energy, p=800-900 MeV", 200, 0., 2.);
   h_pim_matche10_cut2 = iHistoManager.histogram(2130, "pi- matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_pim_matche11_cut2 = iHistoManager.histogram(2131, "pi- matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_pim_matche12_cut2 = iHistoManager.histogram(2132, "pi- matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_pim_matche13_cut2 = iHistoManager.histogram(2133, "pi- matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_pim_matche14_cut2 = iHistoManager.histogram(2134, "pi- matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_pim_matche15_cut2 = iHistoManager.histogram(2135, "pi- matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_pim_matche16_cut2 = iHistoManager.histogram(2136, "pi- matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_pim_matche17_cut2 = iHistoManager.histogram(2137, "pi- matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_pim_matche18_cut2 = iHistoManager.histogram(2138, "pi- matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_pim_matche19_cut2 = iHistoManager.histogram(2139, "pi- matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_pim_matche20_cut2 = iHistoManager.histogram(2140, "pi- matched energy, p=1900-2000 MeV", 200, 0., 2.);

   h_pion_matche_cut3 = iHistoManager.histogram(3100, "pion matched energy", 200, 0., 2.);
   h_pip_matche1_cut3 = iHistoManager.histogram(3101, "pi+ matched energy, p=0-100 MeV", 200, 0., 2.);
   h_pip_matche2_cut3 = iHistoManager.histogram(3102, "pi+ matched energy, p=100-200 MeV", 200, 0., 2.);
   h_pip_matche3_cut3 = iHistoManager.histogram(3103, "pi+ matched energy, p=200-300 MeV", 200, 0., 2.);
   h_pip_matche4_cut3 = iHistoManager.histogram(3104, "pi+ matched energy, p=300-400 MeV", 200, 0., 2.);
   h_pip_matche5_cut3 = iHistoManager.histogram(3105, "pi+ matched energy, p=400-500 MeV", 200, 0., 2.);
   h_pip_matche6_cut3 = iHistoManager.histogram(3106, "pi+ matched energy, p=500-600 MeV", 200, 0., 2.);
   h_pip_matche7_cut3 = iHistoManager.histogram(3107, "pi+ matched energy, p=600-700 MeV", 200, 0., 2.);
   h_pip_matche8_cut3 = iHistoManager.histogram(3108, "pi+ matched energy, p=700-800 MeV", 200, 0., 2.);
   h_pip_matche9_cut3 = iHistoManager.histogram(3109, "pi+ matched energy, p=800-900 MeV", 200, 0., 2.);
   h_pip_matche10_cut3 = iHistoManager.histogram(3110, "pi+ matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_pip_matche11_cut3 = iHistoManager.histogram(3111, "pi+ matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_pip_matche12_cut3 = iHistoManager.histogram(3112, "pi+ matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_pip_matche13_cut3 = iHistoManager.histogram(3113, "pi+ matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_pip_matche14_cut3 = iHistoManager.histogram(3114, "pi+ matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_pip_matche15_cut3 = iHistoManager.histogram(3115, "pi+ matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_pip_matche16_cut3 = iHistoManager.histogram(3116, "pi+ matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_pip_matche17_cut3 = iHistoManager.histogram(3117, "pi+ matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_pip_matche18_cut3 = iHistoManager.histogram(3118, "pi+ matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_pip_matche19_cut3 = iHistoManager.histogram(3119, "pi+ matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_pip_matche20_cut3 = iHistoManager.histogram(3120, "pi+ matched energy, p=1900-2000 MeV", 200, 0., 2.);
   h_pim_matche1_cut3 = iHistoManager.histogram(3121, "pi- matched energy, p=0-100 MeV", 200, 0., 2.);
   h_pim_matche2_cut3 = iHistoManager.histogram(3122, "pi- matched energy, p=100-200 MeV", 200, 0., 2.);
   h_pim_matche3_cut3 = iHistoManager.histogram(3123, "pi- matched energy, p=200-300 MeV", 200, 0., 2.);
   h_pim_matche4_cut3 = iHistoManager.histogram(3124, "pi- matched energy, p=300-400 MeV", 200, 0., 2.);
   h_pim_matche5_cut3 = iHistoManager.histogram(3125, "pi- matched energy, p=400-500 MeV", 200, 0., 2.);
   h_pim_matche6_cut3 = iHistoManager.histogram(3126, "pi- matched energy, p=500-600 MeV", 200, 0., 2.);
   h_pim_matche7_cut3 = iHistoManager.histogram(3127, "pi- matched energy, p=600-700 MeV", 200, 0., 2.);
   h_pim_matche8_cut3 = iHistoManager.histogram(3128, "pi- matched energy, p=700-800 MeV", 200, 0., 2.);
   h_pim_matche9_cut3 = iHistoManager.histogram(3129, "pi- matched energy, p=800-900 MeV", 200, 0., 2.);
   h_pim_matche10_cut3 = iHistoManager.histogram(3130, "pi- matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_pim_matche11_cut3 = iHistoManager.histogram(3131, "pi- matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_pim_matche12_cut3 = iHistoManager.histogram(3132, "pi- matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_pim_matche13_cut3 = iHistoManager.histogram(3133, "pi- matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_pim_matche14_cut3 = iHistoManager.histogram(3134, "pi- matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_pim_matche15_cut3 = iHistoManager.histogram(3135, "pi- matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_pim_matche16_cut3 = iHistoManager.histogram(3136, "pi- matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_pim_matche17_cut3 = iHistoManager.histogram(3137, "pi- matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_pim_matche18_cut3 = iHistoManager.histogram(3138, "pi- matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_pim_matche19_cut3 = iHistoManager.histogram(3139, "pi- matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_pim_matche20_cut3 = iHistoManager.histogram(3140, "pi- matched energy, p=1900-2000 MeV", 200, 0., 2.);

   h_pion_matche_cut4 = iHistoManager.histogram(4100, "pion matched energy", 200, 0., 2.);
   h_pip_matche1_cut4 = iHistoManager.histogram(4101, "pi+ matched energy, p=0-100 MeV", 200, 0., 2.);
   h_pip_matche2_cut4 = iHistoManager.histogram(4102, "pi+ matched energy, p=100-200 MeV", 200, 0., 2.);
   h_pip_matche3_cut4 = iHistoManager.histogram(4103, "pi+ matched energy, p=200-300 MeV", 200, 0., 2.);
   h_pip_matche4_cut4 = iHistoManager.histogram(4104, "pi+ matched energy, p=300-400 MeV", 200, 0., 2.);
   h_pip_matche5_cut4 = iHistoManager.histogram(4105, "pi+ matched energy, p=400-500 MeV", 200, 0., 2.);
   h_pip_matche6_cut4 = iHistoManager.histogram(4106, "pi+ matched energy, p=500-600 MeV", 200, 0., 2.);
   h_pip_matche7_cut4 = iHistoManager.histogram(4107, "pi+ matched energy, p=600-700 MeV", 200, 0., 2.);
   h_pip_matche8_cut4 = iHistoManager.histogram(4108, "pi+ matched energy, p=700-800 MeV", 200, 0., 2.);
   h_pip_matche9_cut4 = iHistoManager.histogram(4109, "pi+ matched energy, p=800-900 MeV", 200, 0., 2.);
   h_pip_matche10_cut4 = iHistoManager.histogram(4110, "pi+ matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_pip_matche11_cut4 = iHistoManager.histogram(4111, "pi+ matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_pip_matche12_cut4 = iHistoManager.histogram(4112, "pi+ matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_pip_matche13_cut4 = iHistoManager.histogram(4113, "pi+ matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_pip_matche14_cut4 = iHistoManager.histogram(4114, "pi+ matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_pip_matche15_cut4 = iHistoManager.histogram(4115, "pi+ matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_pip_matche16_cut4 = iHistoManager.histogram(4116, "pi+ matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_pip_matche17_cut4 = iHistoManager.histogram(4117, "pi+ matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_pip_matche18_cut4 = iHistoManager.histogram(4118, "pi+ matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_pip_matche19_cut4 = iHistoManager.histogram(4119, "pi+ matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_pip_matche20_cut4 = iHistoManager.histogram(4120, "pi+ matched energy, p=1900-2000 MeV", 200, 0., 2.);
   h_pim_matche1_cut4 = iHistoManager.histogram(4121, "pi- matched energy, p=0-100 MeV", 200, 0., 2.);
   h_pim_matche2_cut4 = iHistoManager.histogram(4122, "pi- matched energy, p=100-200 MeV", 200, 0., 2.);
   h_pim_matche3_cut4 = iHistoManager.histogram(4123, "pi- matched energy, p=200-300 MeV", 200, 0., 2.);
   h_pim_matche4_cut4 = iHistoManager.histogram(4124, "pi- matched energy, p=300-400 MeV", 200, 0., 2.);
   h_pim_matche5_cut4 = iHistoManager.histogram(4125, "pi- matched energy, p=400-500 MeV", 200, 0., 2.);
   h_pim_matche6_cut4 = iHistoManager.histogram(4126, "pi- matched energy, p=500-600 MeV", 200, 0., 2.);
   h_pim_matche7_cut4 = iHistoManager.histogram(4127, "pi- matched energy, p=600-700 MeV", 200, 0., 2.);
   h_pim_matche8_cut4 = iHistoManager.histogram(4128, "pi- matched energy, p=700-800 MeV", 200, 0., 2.);
   h_pim_matche9_cut4 = iHistoManager.histogram(4129, "pi- matched energy, p=800-900 MeV", 200, 0., 2.);
   h_pim_matche10_cut4 = iHistoManager.histogram(4130, "pi- matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_pim_matche11_cut4 = iHistoManager.histogram(4131, "pi- matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_pim_matche12_cut4 = iHistoManager.histogram(4132, "pi- matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_pim_matche13_cut4 = iHistoManager.histogram(4133, "pi- matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_pim_matche14_cut4 = iHistoManager.histogram(4134, "pi- matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_pim_matche15_cut4 = iHistoManager.histogram(4135, "pi- matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_pim_matche16_cut4 = iHistoManager.histogram(4136, "pi- matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_pim_matche17_cut4 = iHistoManager.histogram(4137, "pi- matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_pim_matche18_cut4 = iHistoManager.histogram(4138, "pi- matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_pim_matche19_cut4 = iHistoManager.histogram(4139, "pi- matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_pim_matche20_cut4 = iHistoManager.histogram(4140, "pi- matched energy, p=1900-2000 MeV", 200, 0., 2.);

   h_pion_matche_cut5 = iHistoManager.histogram(5100, "pion matched energy", 200, 0., 2.);
   h_pip_matche1_cut5 = iHistoManager.histogram(5101, "pi+ matched energy, p=0-100 MeV", 200, 0., 2.);
   h_pip_matche2_cut5 = iHistoManager.histogram(5102, "pi+ matched energy, p=100-200 MeV", 200, 0., 2.);
   h_pip_matche3_cut5 = iHistoManager.histogram(5103, "pi+ matched energy, p=200-300 MeV", 200, 0., 2.);
   h_pip_matche4_cut5 = iHistoManager.histogram(5104, "pi+ matched energy, p=300-400 MeV", 200, 0., 2.);
   h_pip_matche5_cut5 = iHistoManager.histogram(5105, "pi+ matched energy, p=400-500 MeV", 200, 0., 2.);
   h_pip_matche6_cut5 = iHistoManager.histogram(5106, "pi+ matched energy, p=500-600 MeV", 200, 0., 2.);
   h_pip_matche7_cut5 = iHistoManager.histogram(5107, "pi+ matched energy, p=600-700 MeV", 200, 0., 2.);
   h_pip_matche8_cut5 = iHistoManager.histogram(5108, "pi+ matched energy, p=700-800 MeV", 200, 0., 2.);
   h_pip_matche9_cut5 = iHistoManager.histogram(5109, "pi+ matched energy, p=800-900 MeV", 200, 0., 2.);
   h_pip_matche10_cut5 = iHistoManager.histogram(5110, "pi+ matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_pip_matche11_cut5 = iHistoManager.histogram(5111, "pi+ matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_pip_matche12_cut5 = iHistoManager.histogram(5112, "pi+ matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_pip_matche13_cut5 = iHistoManager.histogram(5113, "pi+ matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_pip_matche14_cut5 = iHistoManager.histogram(5114, "pi+ matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_pip_matche15_cut5 = iHistoManager.histogram(5115, "pi+ matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_pip_matche16_cut5 = iHistoManager.histogram(5116, "pi+ matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_pip_matche17_cut5 = iHistoManager.histogram(5117, "pi+ matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_pip_matche18_cut5 = iHistoManager.histogram(5118, "pi+ matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_pip_matche19_cut5 = iHistoManager.histogram(5119, "pi+ matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_pip_matche20_cut5 = iHistoManager.histogram(5120, "pi+ matched energy, p=1900-2000 MeV", 200, 0., 2.);
   h_pim_matche1_cut5 = iHistoManager.histogram(5121, "pi- matched energy, p=0-100 MeV", 200, 0., 2.);
   h_pim_matche2_cut5 = iHistoManager.histogram(5122, "pi- matched energy, p=100-200 MeV", 200, 0., 2.);
   h_pim_matche3_cut5 = iHistoManager.histogram(5123, "pi- matched energy, p=200-300 MeV", 200, 0., 2.);
   h_pim_matche4_cut5 = iHistoManager.histogram(5124, "pi- matched energy, p=300-400 MeV", 200, 0., 2.);
   h_pim_matche5_cut5 = iHistoManager.histogram(5125, "pi- matched energy, p=400-500 MeV", 200, 0., 2.);
   h_pim_matche6_cut5 = iHistoManager.histogram(5126, "pi- matched energy, p=500-600 MeV", 200, 0., 2.);
   h_pim_matche7_cut5 = iHistoManager.histogram(5127, "pi- matched energy, p=600-700 MeV", 200, 0., 2.);
   h_pim_matche8_cut5 = iHistoManager.histogram(5128, "pi- matched energy, p=700-800 MeV", 200, 0., 2.);
   h_pim_matche9_cut5 = iHistoManager.histogram(5129, "pi- matched energy, p=800-900 MeV", 200, 0., 2.);
   h_pim_matche10_cut5 = iHistoManager.histogram(5130, "pi- matched energy, p=900-1000 MeV", 200, 0., 2.);
   h_pim_matche11_cut5 = iHistoManager.histogram(5131, "pi- matched energy, p=1000-1100 MeV", 200, 0., 2.);
   h_pim_matche12_cut5 = iHistoManager.histogram(5132, "pi- matched energy, p=1100-1200 MeV", 200, 0., 2.);
   h_pim_matche13_cut5 = iHistoManager.histogram(5133, "pi- matched energy, p=1200-1300 MeV", 200, 0., 2.);
   h_pim_matche14_cut5 = iHistoManager.histogram(5134, "pi- matched energy, p=1300-1400 MeV", 200, 0., 2.);
   h_pim_matche15_cut5 = iHistoManager.histogram(5135, "pi- matched energy, p=1400-1500 MeV", 200, 0., 2.);
   h_pim_matche16_cut5 = iHistoManager.histogram(5136, "pi- matched energy, p=1500-1600 MeV", 200, 0., 2.);
   h_pim_matche17_cut5 = iHistoManager.histogram(5137, "pi- matched energy, p=1600-1700 MeV", 200, 0., 2.);
   h_pim_matche18_cut5 = iHistoManager.histogram(5138, "pi- matched energy, p=1700-1800 MeV", 200, 0., 2.);
   h_pim_matche19_cut5 = iHistoManager.histogram(5139, "pi- matched energy, p=1800-1900 MeV", 200, 0., 2.);
   h_pim_matche20_cut5 = iHistoManager.histogram(5140, "pi- matched energy, p=1900-2000 MeV", 200, 0., 2.);


   h_pion_muall_p_costh = iHistoManager.histogram(61, "pion p v. costh", 20, 0., 2., 20, 0., 1.);
   h_pion_muall_p_phi = iHistoManager.histogram(62, "pion p v. phi", 20, 0., 2., 45, -22.5, 22.5);
   h_pion_muall_costh_phi = iHistoManager.histogram(63, "pion costh v. phi", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_p_costh = iHistoManager.histogram(64, "pi+ p v. costh", 20, 0., 2., 20, 0., 1.);
   h_pip_muall_p_phi = iHistoManager.histogram(65, "pi+ p v. phi", 20, 0., 2., 45, -22.5, 22.5);
   h_pip_muall_costh_phi = iHistoManager.histogram(66, "pi+ costh v. phi", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_p_costh = iHistoManager.histogram(67, "pi- p v. costh", 20, 0., 2., 20, 0., 1.);
   h_pim_muall_p_phi = iHistoManager.histogram(68, "pi- p v. phi", 20, 0., 2., 45, -22.5, 22.5);
   h_pim_muall_costh_phi = iHistoManager.histogram(69, "pi- costh v. phi", 20, 0., 1., 45, -22.5, 22.5);

   h_pion_mucut_p_costh = iHistoManager.histogram(71, "pion p v. costh, muon cut", 20, 0., 2., 20, 0., 1.);
   h_pion_mucut_p_phi = iHistoManager.histogram(72, "pion p v. phi, muon cut", 20, 0., 2., 45, -22.5, 22.5);
   h_pion_mucut_costh_phi = iHistoManager.histogram(73, "pion costh v. phi, muon cut", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_p_costh = iHistoManager.histogram(74, "pi+ p v. costh, muon cut", 20, 0., 2., 20, 0., 1.);
   h_pip_mucut_p_phi = iHistoManager.histogram(75, "pi+ p v. phi, muon cut", 20, 0., 2., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi = iHistoManager.histogram(76, "pi+ costh v. phi, muon cut", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_p_costh = iHistoManager.histogram(77, "pi- p v. costh, muon cut", 20, 0., 2., 20, 0., 1.);
   h_pim_mucut_p_phi = iHistoManager.histogram(78, "pi- p v. phi, muon cut", 20, 0., 2., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi = iHistoManager.histogram(79, "pi- costh v. phi, muon cut", 20, 0., 1., 45, -22.5, 22.5);
   
   h_pip_muall_costh_phi_cut1 = iHistoManager.histogram(1201, "pi+ costh v. phi, all events, cut 1", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut2 = iHistoManager.histogram(1202, "pi+ costh v. phi, all events, cut 2", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut3 = iHistoManager.histogram(1203, "pi+ costh v. phi, all events, cut 3", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut4 = iHistoManager.histogram(1204, "pi+ costh v. phi, all events, cut 4", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut5 = iHistoManager.histogram(1205, "pi+ costh v. phi, all events, cut 5", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut6 = iHistoManager.histogram(1206, "pi+ costh v. phi, all events, cut 6", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut7 = iHistoManager.histogram(1207, "pi+ costh v. phi, all events, cut 7", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut8 = iHistoManager.histogram(1208, "pi+ costh v. phi, all events, cut 8", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut9 = iHistoManager.histogram(1209, "pi+ costh v. phi, all events, cut 9", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut10 = iHistoManager.histogram(1210, "pi+ costh v. phi, all events, cut 10", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut11 = iHistoManager.histogram(1211, "pi+ costh v. phi, all events, cut 11", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut12 = iHistoManager.histogram(1212, "pi+ costh v. phi, all events, cut 12", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut13 = iHistoManager.histogram(1213, "pi+ costh v. phi, all events, cut 13", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut14 = iHistoManager.histogram(1214, "pi+ costh v. phi, all events, cut 14", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut15 = iHistoManager.histogram(1215, "pi+ costh v. phi, all events, cut 15", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut16 = iHistoManager.histogram(1216, "pi+ costh v. phi, all events, cut 16", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut17 = iHistoManager.histogram(1217, "pi+ costh v. phi, all events, cut 17", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut18 = iHistoManager.histogram(1218, "pi+ costh v. phi, all events, cut 18", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut19 = iHistoManager.histogram(1219, "pi+ costh v. phi, all events, cut 19", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_muall_costh_phi_cut20 = iHistoManager.histogram(1220, "pi+ costh v. phi, all events, cut 20", 20, 0., 1., 45, -22.5, 22.5);

   h_pim_muall_costh_phi_cut1 = iHistoManager.histogram(1221, "pi- costh v. phi, all events, cut 1", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut2 = iHistoManager.histogram(1222, "pi- costh v. phi, all events, cut 2", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut3 = iHistoManager.histogram(1223, "pi- costh v. phi, all events, cut 3", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut4 = iHistoManager.histogram(1224, "pi- costh v. phi, all events, cut 4", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut5 = iHistoManager.histogram(1225, "pi- costh v. phi, all events, cut 5", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut6 = iHistoManager.histogram(1226, "pi- costh v. phi, all events, cut 6", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut7 = iHistoManager.histogram(1227, "pi- costh v. phi, all events, cut 7", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut8 = iHistoManager.histogram(1228, "pi- costh v. phi, all events, cut 8", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut9 = iHistoManager.histogram(1229, "pi- costh v. phi, all events, cut 9", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut10 = iHistoManager.histogram(1230, "pi- costh v. phi, all events, cut 10", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut11 = iHistoManager.histogram(1231, "pi- costh v. phi, all events, cut 11", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut12 = iHistoManager.histogram(1232, "pi- costh v. phi, all events, cut 12", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut13 = iHistoManager.histogram(1233, "pi- costh v. phi, all events, cut 13", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut14 = iHistoManager.histogram(1234, "pi- costh v. phi, all events, cut 14", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut15 = iHistoManager.histogram(1235, "pi- costh v. phi, all events, cut 15", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut16 = iHistoManager.histogram(1236, "pi- costh v. phi, all events, cut 16", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut17 = iHistoManager.histogram(1237, "pi- costh v. phi, all events, cut 17", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut18 = iHistoManager.histogram(1238, "pi- costh v. phi, all events, cut 18", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut19 = iHistoManager.histogram(1239, "pi- costh v. phi, all events, cut 19", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_muall_costh_phi_cut20 = iHistoManager.histogram(1240, "pi- costh v. phi, all events, cut 20", 20, 0., 1., 45, -22.5, 22.5);


  h_pip_mucut_costh_phi_cut1 = iHistoManager.histogram(1301, "pi+ costh v. phi, all events, cut 1", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut2 = iHistoManager.histogram(1302, "pi+ costh v. phi, all events, cut 2", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut3 = iHistoManager.histogram(1303, "pi+ costh v. phi, all events, cut 3", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut4 = iHistoManager.histogram(1304, "pi+ costh v. phi, all events, cut 4", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut5 = iHistoManager.histogram(1305, "pi+ costh v. phi, all events, cut 5", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut6 = iHistoManager.histogram(1306, "pi+ costh v. phi, all events, cut 6", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut7 = iHistoManager.histogram(1307, "pi+ costh v. phi, all events, cut 7", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut8 = iHistoManager.histogram(1308, "pi+ costh v. phi, all events, cut 8", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut9 = iHistoManager.histogram(1309, "pi+ costh v. phi, all events, cut 9", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut10 = iHistoManager.histogram(1310, "pi+ costh v. phi, all events, cut 10", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut11 = iHistoManager.histogram(1311, "pi+ costh v. phi, all events, cut 11", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut12 = iHistoManager.histogram(1312, "pi+ costh v. phi, all events, cut 12", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut13 = iHistoManager.histogram(1313, "pi+ costh v. phi, all events, cut 13", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut14 = iHistoManager.histogram(1314, "pi+ costh v. phi, all events, cut 14", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut15 = iHistoManager.histogram(1315, "pi+ costh v. phi, all events, cut 15", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut16 = iHistoManager.histogram(1316, "pi+ costh v. phi, all events, cut 16", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut17 = iHistoManager.histogram(1317, "pi+ costh v. phi, all events, cut 17", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut18 = iHistoManager.histogram(1318, "pi+ costh v. phi, all events, cut 18", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut19 = iHistoManager.histogram(1319, "pi+ costh v. phi, all events, cut 19", 20, 0., 1., 45, -22.5, 22.5);
   h_pip_mucut_costh_phi_cut20 = iHistoManager.histogram(1320, "pi+ costh v. phi, all events, cut 20", 20, 0., 1., 45, -22.5, 22.5);

   h_pim_mucut_costh_phi_cut1 = iHistoManager.histogram(1321, "pi- costh v. phi, all events, cut 1", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut2 = iHistoManager.histogram(1322, "pi- costh v. phi, all events, cut 2", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut3 = iHistoManager.histogram(1323, "pi- costh v. phi, all events, cut 3", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut4 = iHistoManager.histogram(1324, "pi- costh v. phi, all events, cut 4", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut5 = iHistoManager.histogram(1325, "pi- costh v. phi, all events, cut 5", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut6 = iHistoManager.histogram(1326, "pi- costh v. phi, all events, cut 6", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut7 = iHistoManager.histogram(1327, "pi- costh v. phi, all events, cut 7", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut8 = iHistoManager.histogram(1328, "pi- costh v. phi, all events, cut 8", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut9 = iHistoManager.histogram(1329, "pi- costh v. phi, all events, cut 9", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut10 = iHistoManager.histogram(1330, "pi- costh v. phi, all events, cut 10", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut11 = iHistoManager.histogram(1331, "pi- costh v. phi, all events, cut 11", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut12 = iHistoManager.histogram(1332, "pi- costh v. phi, all events, cut 12", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut13 = iHistoManager.histogram(1333, "pi- costh v. phi, all events, cut 13", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut14 = iHistoManager.histogram(1334, "pi- costh v. phi, all events, cut 14", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut15 = iHistoManager.histogram(1335, "pi- costh v. phi, all events, cut 15", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut16 = iHistoManager.histogram(1336, "pi- costh v. phi, all events, cut 16", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut17 = iHistoManager.histogram(1337, "pi- costh v. phi, all events, cut 17", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut18 = iHistoManager.histogram(1338, "pi- costh v. phi, all events, cut 18", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut19 = iHistoManager.histogram(1339, "pi- costh v. phi, all events, cut 19", 20, 0., 1., 45, -22.5, 22.5);
   h_pim_mucut_costh_phi_cut20 = iHistoManager.histogram(1340, "pi- costh v. phi, all events, cut 20", 20, 0., 1., 45, -22.5, 22.5);

   // mc muons

   h_muon_p = iHistoManager.histogram(9001, "muon momentum", 150, 0., 3.);
   h_muon_costh = iHistoManager.histogram(9002, "muon cos theta", 100, 0., 1.);
   h_muon_p_picut = iHistoManager.histogram(9003, "muon momentum - pion cut", 150, 0., 3.);
   h_muon_costh_picut = iHistoManager.histogram(9004, "muon cos theta - pion cut", 100, 0., 1.);

   h_muon_p_mudepth = iHistoManager.histogram(9005, "muon momentum v. mu depth", 50, 0., 2., 70, 0, 14);
   h_muon_costh_mudepth = iHistoManager.histogram(9006, "muon cos theta v. mu depth", 50, 0., 1., 70, 0, 14);
   h_muon_p_mudepth_picut = iHistoManager.histogram(9007, "muon momentum v. mu depth - pion cut", 50, 0., 2., 70, 0, 14);
   h_muon_costh_mudepth_picut = iHistoManager.histogram(9008, "muon cos theta v. mu depth - pion cut", 50, 0., 1., 70, 0, 14);

   h_muon_muall_p_costh = iHistoManager.histogram(9010, "muon p v. costh", 20, 0., 2., 20, 0., 1.);
   h_muon_muall_p_phi = iHistoManager.histogram(9011, "muon p v. phi", 20, 0., 2., 45, -22.5, 22.5);
   h_muon_muall_costh_phi = iHistoManager.histogram(9012, "muon costh v. phi", 20, 0., 1., 45, -22.5, 22.5);
   h_muon_mucut_p_costh = iHistoManager.histogram(9013, "muon p v. costh, muon cut", 20, 0., 2., 20, 0., 1.);
   h_muon_mucut_p_phi = iHistoManager.histogram(9014, "muon p v. phi, muon cut", 20, 0., 2., 45, -22.5, 22.5);
   h_muon_mucut_costh_phi = iHistoManager.histogram(9015, "muon costh v. phi, muon cut", 20, 0., 1., 45, -22.5, 22.5);
   h_muon_mucut2_p_costh = iHistoManager.histogram(9016, "muon p v. costh, muon cut", 20, 0., 2., 20, 0., 1.);
   h_muon_mucut2_p_phi = iHistoManager.histogram(9017, "muon p v. phi, muon cut", 20, 0., 2., 45, -22.5, 22.5);
   h_muon_mucut2_costh_phi = iHistoManager.histogram(9018, "muon costh v. phi, muon cut", 20, 0., 1., 45, -22.5, 22.5);

   h_muon_pimuall_p_costh = iHistoManager.histogram(9020, "muon p v. costh - pion cut", 20, 0., 2., 20, 0., 1.);
   h_muon_pimuall_p_phi = iHistoManager.histogram(9021, "muon p v. phi - pion cut", 20, 0., 2., 45, -22.5, 22.5);
   h_muon_pimuall_costh_phi = iHistoManager.histogram(9022, "muon costh v. phi - pion cut", 20, 0., 1., 45, -22.5, 22.5);
   h_muon_pimucut_p_costh = iHistoManager.histogram(9023, "muon p v. costh, muon cut - pion cut", 20, 0., 2., 20, 0., 1.);
   h_muon_pimucut_p_phi = iHistoManager.histogram(9024, "muon p v. phi, muon cut - pion cut", 20, 0., 2., 45, -22.5, 22.5);
   h_muon_pimucut_costh_phi = iHistoManager.histogram(9025, "muon costh v. phi, muon cut - pion cut", 20, 0., 1., 45, -22.5, 22.5);
   h_muon_pimucut2_p_costh = iHistoManager.histogram(9026, "muon p v. costh, muon cut - pion cut", 20, 0., 2., 20, 0., 1.);
   h_muon_pimucut2_p_phi = iHistoManager.histogram(9027, "muon p v. phi, muon cut - pion cut", 20, 0., 2., 45, -22.5, 22.5);
   h_muon_pimucut2_costh_phi = iHistoManager.histogram(9028, "muon costh v. phi, muon cut - pion cut", 20, 0., 1., 45, -22.5, 22.5);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Bin20_JpsiPiPiProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;


   const int kMaxShower = 10, kMaxTrack = 10;
   const int kMaxPi0 = 10;
   const int kMaxEta = 10;

   NavTrack::Identifier pip_TID;
   NavTrack::Identifier pim_TID;

   NavShower::Identifier SID[kMaxShower];
   double E[kMaxShower] = 
           {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10., -10.};  

   double BigE[kMaxShower] = 
              {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10., -10.};  

   double E9E25[kMaxShower] =
               {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10., -10.};  

   double Theta[kMaxShower] =
               {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10., -10.};  

   double Phi[kMaxShower] = 
             {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10., -10.};  

   double Cang[kMaxShower] = {-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.};
   double Split[kMaxShower] = {-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.};

   double Barrel[kMaxShower] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};

//   double XP[2] = {-10.,-10.}, XPT[2];

   double PE[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double PPx[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double PPy[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double PPz[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double EE[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double EPx[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double EPy[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double EPz[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double MuE[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double MuPx[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double MuPy[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double MuPz[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double Charge[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,
			       -10.};
   double D0[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double Z0[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double HitFrac[kMaxTrack] = {100.,100.,100.,100.,100.,100.,100.,100.,100.,100.};
   double ReChiSq[kMaxTrack] = {1000.,1000.,1000.,1000.,1000.,1000.,1000.,1000.,
				   1000.,1000.};
   double DOCA[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double EID[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double MUID[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double EP[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double MuDepth[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};


   double PISIG[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double KSIG[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double PSIG[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double PILL[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double KLL[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double PLL[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double DLPIP[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double DLPIK[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double P0E[kMaxPi0] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double P0PX[kMaxPi0] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double P0PY[kMaxPi0] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double P0PZ[kMaxPi0] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double P0PullM[kMaxPi0] = {-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.};
   double P0HiSID[kMaxPi0] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double P0LoSID[kMaxPi0] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double EtaE[kMaxEta] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double EtaPX[kMaxEta] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double EtaPY[kMaxEta] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double EtaPZ[kMaxEta] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double EtaPullM[kMaxEta] = {-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.};
   double EtaHiSID[kMaxEta] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double EtaLoSID[kMaxEta] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};

   float ntVal[kNumVars];
//   double EMax = 0.;
   int m,n,p;
   int i,j,k,l;
   double DL_pik, DL_pip, neutralEnergy = 0;

   FAItem< DBEventHeader > eventHeader ;
   extract( iFrame.record( Stream::kEvent ), eventHeader ) ;

   double the_run = eventHeader->run();
   double the_evt = eventHeader->number();
   bool is_mc = eventHeader->monteCarlo();



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


   // Create a table of tracks and fill it.
   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable, "GoodThings" );
   //extract( iFrame.record( Stream::kEvent ) , trackTable );

   FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();

   // Loop over tracks.
   int numTrack=0;

   bool found_jpsi = false;
   double pipi_recmass = 10.;
   double delta_pipi_recmass = 10.;
   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;  ++trackItr ) {
	   FAItem<TDKinematicFit> pionFit = trackItr->pionFit();
	   FAItem<TRHelixFit> pionHelix = trackItr->pionHelix();

	   // count tracks
	   if(trackItr.valid() 
	      && pionFit.valid()
	      && pionHelix.valid() ) {
		   // require 50 MeV < p < 2.2 Gev tracks - potential QED contamination
		   //  4.26 / 2 = 2.13
		   if((pionFit->pmag() < 0.05) || (pionFit->pmag() > 2.2)) continue;

		   // it's a good track!
		   numTrack++;
	   }
   }

   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;  ++trackItr ) {
	   FAItem<TDKinematicFit> pionFit = trackItr->pionFit();
	   FAItem<TRHelixFit> pionHelix = trackItr->pionHelix();

	   // count tracks
	   if(trackItr.valid() 
	      && pionFit.valid()
	      && pionHelix.valid() ) {
		   // require 50 MeV < p < 2.2 Gev tracks - potential QED contamination
		   //  4.26 / 2 = 2.13
		   if((pionFit->pmag() < 0.05) || (pionFit->pmag() > 2.2)) continue;

		   // it's a good track!
		   //numTrack++;

		   /*
		   // reject events with a stiff muon
		   //if(trackItr->muonId().depth() > 5.) 
		   if(trackItr->muonId().depth() > 3.) 
			   return ActionBase::kFailed;
		   */
		   
		   // check 
		   for ( FATable< NavTrack >::const_iterator trackItr2 = trackItr+1;
			 trackItr2 != trackTableEnd ;  ++trackItr2 ) {
			   FAItem<TDKinematicFit> pionFit2 = trackItr2->pionFit();
			   FAItem<TRHelixFit> pionHelix2 = trackItr2->pionHelix();
			   if(trackItr2.valid() 
			      && pionFit2.valid()
			      && pionHelix2.valid() ) {

				   if((pionFit2->pmag() < 0.05) || (pionFit2->pmag() > 2.2)) continue;

				   double mmpipi = sqrt(pow(2.*beam_energy->value()
							    -pionFit->energy()-pionFit2->energy(),2)
							- pow(pionFit->px()+pionFit2->px(),2)
							- pow(pionFit->py()+pionFit2->py(),2)
							- pow(pionFit->pz()+pionFit2->pz(),2));
				   double mpipi = sqrt(pow(pionFit->energy()+pionFit2->energy(),2)
						       - pow(pionFit->px()+pionFit2->px(),2)
						       - pow(pionFit->py()+pionFit2->py(),2)
						       - pow(pionFit->pz()+pionFit2->pz(),2));
				   
				   
				   h_mpipi->fill( mpipi );
				   if( numTrack <= 4 ) {
					   h_mpipi4->fill( mpipi );
					   
					   if( fabs(mpipi - 3.1) < 0.05 )
						   found_jpsi = true;
				   }

				   double delta_mmpipi = fabs(3.097 - mmpipi);
				   //if( delta_mmpipi > 0.015 ) continue;
				   if( mmpipi > 3.105 || mmpipi < 3.092 ) continue;
				   if( delta_mmpipi < delta_pipi_recmass ) {
					   if( numTrack <= 4 ) 
						   found_jpsi = true;
					   pipi_recmass = mmpipi;
					   delta_pipi_recmass = delta_mmpipi;

					   if( pionFit->charge() > 0. ) {
						   pip_TID = trackItr->identifier();
						   pim_TID = trackItr2->identifier();
					   } else {
						   pip_TID = trackItr2->identifier();
						   pim_TID = trackItr->identifier();
					   }
				   }
			   }
		   }
	   }
   }


   //if(numTrack < 2)
   if(numTrack < 3)
	   return ActionBase::kFailed;
   //if(!found_jpsi)
   if(found_jpsi)
   	   return ActionBase::kFailed;


   h_mpipirec->fill(pipi_recmass);

   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;  ++trackItr )  {
      double tr_en, tr_px, tr_py, tr_pz, tr_chg;
      double tr_z0, tr_rechisq, tr_doca;
      FAItem<TDKinematicFit> pionFit = trackItr->pionFit();
      //FAItem<TDKinematicFit> electronFit = trackItr->electronFit();
      //FAItem<TDKinematicFit> muonFit = trackItr->muonFit();
      FAItem<TRTrackFitQuality> pionQuality = trackItr->pionQuality();
      FAItem<TRHelixFit> pionHelix = trackItr->pionHelix();
      //FAItem<TDKinematicFit> protonFit = trackItr->protonFit();
      //FAItem<TRTrackFitQuality> protonQuality = trackItr->protonQuality();
      //FAItem<TRHelixFit> protonHelix = trackItr->protonHelix();
      //FAItem<DedxInfo> the_dedx = trackItr->dedxInfo();
      //FAItem<NavRich> the_rich = trackItr->richInfo();

      if (trackItr->identifier() == pip_TID || trackItr->identifier() == pim_TID ) continue;

      if(trackItr.valid() 
	 && pionFit.valid()
	 && pionHelix.valid() ) {
	      //numTrack++;
	 
	 // require 50 MeV < p < 2.2 Gev tracks - potential QED contamination
	 //  4.26 / 2 = 2.13
	      //if((pionFit->pmag() > 0.05) && (pionFit->pmag() < 2.2)) {
	 if((pionFit->pmag() > 0.05) && (pionFit->pmag() < 2.)) {
		 //cerr << "track: " << numTrack << " " << pionFit->lorentzMomentum() << endl;

		 if(!trackItr->trackShowerMatch().valid())  continue;
		 //if(trackItr->trackShowerMatch()->eOverP() > 0.85)  continue;
		 //if(trackItr->trackShowerMatch()->eOverP() > 0.8)  continue;

		 double costh = fabs( pionFit->pz() / pionFit->pmag() );
		 //bool is_barrel = costh < 0.81;
		 bool is_barrel = costh < 0.75;
		 bool is_endcap = (costh > 0.85) && (costh < 0.93);

		 //double phi = atan2( pionFit->py(), pionFit->px() ) * 180./3.1459;
		 double phi = fmod( atan2( pionFit->py(), pionFit->px() ) * 180./3.1459, 22.5 );


		 int pdg_id = 0;
		 if(is_mc) {
			 if(trackItr->mcTag().valid()) {
				 pdg_id = abs(trackItr->mcTag()->properties().PDGId());
			 }
		 }

		 
		 // plots of muons
		 if( pdg_id == 13 ) {
			 /*
			 FAItem< MCDecayTree > decayTree;
			 if(is_mc) {
				 extract(iFrame.record(Stream::kEvent), decayTree);
				 //extract(iFrame.record(Stream::kEvent), decayTree, "Generator" );
				 const MCDecayTree& mcDecayTree(*decayTree);
				 
				 report(INFO, kFacilityString) << "About to dump decay tree" << endl;
				 report(INFO, kFacilityString) << mcDecayTree << endl;
			 } 
			 */

			 double p = pionFit->pmag();
			 double mudepth = trackItr->muonId().depth();
			 
			 h_muon_p->fill( p );
			 h_muon_costh->fill( costh );
			 h_muon_p_mudepth->fill( p, mudepth );
			 h_muon_costh_mudepth->fill( costh, mudepth );
			 
			 h_muon_muall_p_costh->fill( p, costh );
			 h_muon_muall_p_phi->fill( p, phi );
			 h_muon_muall_costh_phi->fill( costh, phi );

			 if( mudepth > 1. ) {
				 h_muon_mucut_p_costh->fill( p, costh );
				 h_muon_mucut_p_phi->fill( p, phi );
				 h_muon_mucut_costh_phi->fill( costh, phi );
			 }

			 if( mudepth > 5. ) {
				 h_muon_mucut2_p_costh->fill( p, costh );
				 h_muon_mucut2_p_phi->fill( p, phi );
				 h_muon_mucut2_costh_phi->fill( costh, phi );
			 }


			 if(isGoodPion(*trackItr)) {
			 if(is_barrel) {
				 h_muon_p_picut->fill( p );
				 h_muon_costh_picut->fill( costh );
				 h_muon_p_mudepth_picut->fill( p, mudepth );
				 h_muon_costh_mudepth_picut->fill( costh, mudepth );
			 
				 h_muon_pimuall_p_costh->fill( p, costh );
				 h_muon_pimuall_p_phi->fill( p, phi );
				 h_muon_pimuall_costh_phi->fill( costh, phi );
				 
				 if( mudepth > 1. ) {
					 h_muon_pimucut_p_costh->fill( p, costh );
					 h_muon_pimucut_p_phi->fill( p, phi );
					 h_muon_pimucut_costh_phi->fill( costh, phi );
				 }
				 
				 if( mudepth > 5. ) {
					 h_muon_pimucut2_p_costh->fill( p, costh );
					 h_muon_pimucut2_p_phi->fill( p, phi );
					 h_muon_pimucut2_costh_phi->fill( costh, phi );
				 }
			 }
			 }
		 }

		 //if(isGoodPion(*trackItr)) {
		 //	 h_pion_costh->fill( costh );
		 //} 
		 if(isGoodKaon(*trackItr)) {
			 h_kaon_costh->fill( costh );
		 } 
		 if(isGoodProton(*trackItr)) {
			 h_proton_costh->fill( costh );
		 }


		 // BARREL

		 if(is_barrel) {
		 if(isGoodPion(*trackItr)) {
			 double p = pionFit->pmag();
			 double mudepth = trackItr->muonId().depth();
			 h_pion_mudepth->fill( trackItr->muonId().depth() );

			 h_pion_p->fill( p );
			 h_pion_costh->fill( costh );
			 h_pion_phi->fill( phi );
			 
			 h_pion_p_costh->fill( p, costh );
			 h_pion_p_phi->fill( p, phi );
			 h_pion_costh_phi->fill( costh, phi );

			 // MC
			 if( pdg_id == 211 )
				 h_pion_mcpion_p->fill( p );
			 else if( pdg_id == 321 )
				 h_pion_mckaon_p->fill( p );
			 else if( pdg_id == 2212 )
				 h_pion_mcproton_p->fill( p );
                         else if( pdg_id == 13 )
                                 h_pion_mcmuon_p->fill( p );

                         h_pion_eop->fill( trackItr->trackShowerMatch()->eOverP() );
			 h_pion_matche->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                         if(trackItr->trackShowerMatch()->eOverP() < 0.8)
                           h_pion_matche_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );


			 h_pion_muall_p_costh->fill( p, costh );
			 h_pion_muall_p_phi->fill( p, phi );
			 h_pion_muall_costh_phi->fill( costh, phi );

			 if( mudepth > 1. ) {
				 h_pion_mucut_p_costh->fill( p, costh );
				 h_pion_mucut_p_phi->fill( p, phi );
				 h_pion_mucut_costh_phi->fill( costh, phi );
			 }
		 
			 if( pionFit->charge() > 0. ) {
				 h_pip_muall_p_costh->fill( p, costh );
				 h_pip_muall_p_phi->fill( p, phi );
				 h_pip_muall_costh_phi->fill( costh, phi );
				 
				 if( mudepth > 1. ) {
					 h_pip_mucut_p_costh->fill( p, costh );
					 h_pip_mucut_p_phi->fill( p, phi );
					 h_pip_mucut_costh_phi->fill( costh, phi );
				 }
				 
                                 h_pip_matche_p->fill( p, trackItr->trackShowerMatch()->matchedEnergy() );

				 if( p>0. && p<0.02 ) {
				 	h_pip_matche1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop1->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche1_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.02 && p<0.04 ) {
					h_pip_matche2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop2->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche2_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.04 && p<0.06 ) {
					h_pip_matche3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop3->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche3_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.06 && p<0.08 ) {
					h_pip_matche4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop4->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche4_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.08 && p<0.10 ) {
					h_pip_matche5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop5->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche5_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.10 && p<0.12 ) {
					h_pip_matche6->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop6->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche6_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.12 && p<0.14 ) {
					h_pip_matche7->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop7->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche7_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.14 && p<0.16 ) {
					h_pip_matche8->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop8->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche8_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.16 && p<0.18 ) {
					h_pip_matche9->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop9->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche9_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.18 && p<0.20 ) {
					h_pip_matche10->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop10->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche10_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.20 && p<0.22 ) {
					h_pip_matche11->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop11->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche11_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.22 && p<0.24 ) {
					h_pip_matche12->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop12->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche12_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.24 && p<0.26 ) {
					h_pip_matche13->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop13->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche13_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.26 && p<0.28 ) {
					h_pip_matche14->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop14->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche14_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.28 && p<0.30 ) {
					h_pip_matche15->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop15->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche15_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.30 && p<0.32 ) {
					h_pip_matche16->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop16->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche16_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.32 && p<0.34 ) {
					h_pip_matche17->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop17->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche17_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.34 && p<0.36 ) {
					h_pip_matche18->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop18->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche18_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.36 && p<0.38 ) {
					h_pip_matche19->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop19->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche19_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.38 && p<0.40 ) {
					h_pip_matche20->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop20->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche20_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.40 && p<0.42 ) {
					h_pip_matche21->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop21->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche21_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.42 && p<0.44 ) {
					h_pip_matche22->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop22->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche22_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.44 && p<0.46 ) {
					h_pip_matche23->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop23->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche23_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.46 && p<0.48 ) {
					h_pip_matche24->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop24->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche24_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.48 && p<0.50 ) {
					h_pip_matche25->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop25->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche25_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.50 && p<0.52 ) {
					h_pip_matche26->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop26->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche26_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.52 && p<0.54 ) {
					h_pip_matche27->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop27->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche27_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.54 && p<0.56 ) {
					h_pip_matche28->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop28->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche28_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.56 && p<0.58 ) {
					h_pip_matche29->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop29->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche29_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.58 && p<0.60 ) {
					h_pip_matche30->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop30->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche30_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.60 && p<0.62 ) {
					h_pip_matche31->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop31->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche31_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.62 && p<0.64 ) {
					h_pip_matche32->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop32->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche32_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.64 && p<0.66 ) {
					h_pip_matche33->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop33->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche33_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.66 && p<0.68 ) {
					h_pip_matche34->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop34->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche34_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.68 && p<0.70 ) {
					h_pip_matche35->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop35->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche35_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.70 && p<0.72 ) {
					h_pip_matche36->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop36->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche36_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.72 && p<0.74 ) {
					h_pip_matche37->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop37->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche37_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.74 && p<0.76 ) {
					h_pip_matche38->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop38->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche38_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.76 && p<0.78 ) {
					h_pip_matche39->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop39->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche39_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.78 && p<0.80 ) {
					h_pip_matche40->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop40->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche40_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.80 && p<0.82 ) {
					h_pip_matche41->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop41->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche41_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.82 && p<0.84 ) {
					h_pip_matche42->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop42->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche42_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.84 && p<0.86 ) {
					h_pip_matche43->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop43->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche43_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.86 && p<0.88 ) {
					h_pip_matche44->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop44->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche44_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.88 && p<0.90 ) {
					h_pip_matche45->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop45->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche45_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.90 && p<0.92 ) {
					h_pip_matche46->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop46->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche46_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.92 && p<0.94 ) {
					h_pip_matche47->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop47->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche47_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.94 && p<0.96 ) {
					h_pip_matche48->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop48->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche48_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.96 && p<0.98 ) {
					h_pip_matche49->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop49->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche49_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.98 && p<1.00 ) {
					h_pip_matche50->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop50->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche50_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.00 && p<1.02 ) {
					h_pip_matche51->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop51->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche51_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.02 && p<1.04 ) {
					h_pip_matche52->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop52->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche52_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.04 && p<1.06 ) {
					h_pip_matche53->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop53->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche53_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.06 && p<1.08 ) {
					h_pip_matche54->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop54->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche54_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.08 && p<1.10 ) {
					h_pip_matche55->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop55->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche55_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.10 && p<1.12 ) {
					h_pip_matche56->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop56->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche56_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.12 && p<1.14 ) {
					h_pip_matche57->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop57->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche57_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.14 && p<1.16 ) {
					h_pip_matche58->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop58->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche58_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.16 && p<1.18 ) {
					h_pip_matche59->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop59->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche59_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.18 && p<1.20 ) {
					h_pip_matche60->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop60->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche60_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.20 && p<1.22 ) {
					h_pip_matche61->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop61->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche61_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.22 && p<1.24 ) {
					h_pip_matche62->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop62->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche62_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.24 && p<1.26 ) {
					h_pip_matche63->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop63->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche63_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.26 && p<1.28 ) {
					h_pip_matche64->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop64->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche64_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.28 && p<1.30 ) {
					h_pip_matche65->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop65->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche65_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.30 && p<1.32 ) {
					h_pip_matche66->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop66->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche66_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.32 && p<1.34 ) {
					h_pip_matche67->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop67->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche67_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.34 && p<1.36 ) {
					h_pip_matche68->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop68->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche68_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.36 && p<1.38 ) {
					h_pip_matche69->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop69->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche69_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.38 && p<1.40 ) {
					h_pip_matche70->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop70->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche70_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.40 && p<1.42 ) {
					h_pip_matche71->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop71->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche71_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.42 && p<1.44 ) {
					h_pip_matche72->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop72->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche72_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.44 && p<1.46 ) {
					h_pip_matche73->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop73->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche73_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.46 && p<1.48 ) {
					h_pip_matche74->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop74->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche74_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.48 && p<1.50 ) {
					h_pip_matche75->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop75->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche75_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.50 && p<1.52 ) {
					h_pip_matche76->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop76->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche76_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.52 && p<1.54 ) {
					h_pip_matche77->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop77->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche77_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.54 && p<1.56 ) {
					h_pip_matche78->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop78->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche78_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.56 && p<1.58 ) {
					h_pip_matche79->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop79->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche79_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.58 && p<1.60 ) {
					h_pip_matche80->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop80->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche80_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.60 && p<1.62 ) {
					h_pip_matche81->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop81->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche81_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.62 && p<1.64 ) {
					h_pip_matche82->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop82->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche82_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.64 && p<1.66 ) {
					h_pip_matche83->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop83->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche83_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.66 && p<1.68 ) {
					h_pip_matche84->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop84->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche84_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.68 && p<1.70 ) {
					h_pip_matche85->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop85->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche85_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.70 && p<1.72 ) {
					h_pip_matche86->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop86->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche86_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.72 && p<1.74 ) {
					h_pip_matche87->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop87->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche87_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.74 && p<1.76 ) {
					h_pip_matche88->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop88->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche88_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.76 && p<1.78 ) {
					h_pip_matche89->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop89->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche89_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.78 && p<1.80 ) {
					h_pip_matche90->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop90->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche90_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.80 && p<1.82 ) {
					h_pip_matche91->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop91->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche91_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.82 && p<1.84 ) {
					h_pip_matche92->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop92->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche92_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.84 && p<1.86 ) {
					h_pip_matche93->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop93->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche93_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.86 && p<1.88 ) {
					h_pip_matche94->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop94->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche94_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.88 && p<1.90 ) {
					h_pip_matche95->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop95->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche95_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.90 && p<1.92 ) {
					h_pip_matche96->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop96->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche96_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.92 && p<1.94 ) {
					h_pip_matche97->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop97->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche97_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.94 && p<1.96 ) {
					h_pip_matche98->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop98->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche98_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.96 && p<1.98 ) {
					h_pip_matche99->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop99->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche99_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.98 && p<2.00 ) {
					h_pip_matche100->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pip_eop100->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pip_matche100_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 }





			 } else {
				 h_pim_muall_p_costh->fill( p, costh );
				 h_pim_muall_p_phi->fill( p, phi );
				 h_pim_muall_costh_phi->fill( costh, phi );
				 
				 if( mudepth > 1. ) {
					 h_pim_mucut_p_costh->fill( p, costh );
					 h_pim_mucut_p_phi->fill( p, phi );
					 h_pim_mucut_costh_phi->fill( costh, phi );
				 }

                                         h_pim_matche_p->fill( p, trackItr->trackShowerMatch()->matchedEnergy() );

				 if( p>0. && p<0.02 ) {
				 	h_pim_matche1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop1->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche1_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.02 && p<0.04 ) {
					h_pim_matche2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop2->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche2_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.04 && p<0.06 ) {
					h_pim_matche3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop3->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche3_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.06 && p<0.08 ) {
					h_pim_matche4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop4->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche4_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.08 && p<0.10 ) {
					h_pim_matche5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop5->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche5_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.10 && p<0.12 ) {
					h_pim_matche6->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop6->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche6_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.12 && p<0.14 ) {
					h_pim_matche7->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop7->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche7_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.14 && p<0.16 ) {
					h_pim_matche8->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop8->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche8_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.16 && p<0.18 ) {
					h_pim_matche9->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop9->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche9_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.18 && p<0.20 ) {
					h_pim_matche10->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop10->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche10_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.20 && p<0.22 ) {
					h_pim_matche11->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop11->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche11_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.22 && p<0.24 ) {
					h_pim_matche12->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop12->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche12_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.24 && p<0.26 ) {
					h_pim_matche13->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop13->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche13_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.26 && p<0.28 ) {
					h_pim_matche14->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop14->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche14_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.28 && p<0.30 ) {
					h_pim_matche15->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop15->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche15_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.30 && p<0.32 ) {
					h_pim_matche16->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop16->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche16_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.32 && p<0.34 ) {
					h_pim_matche17->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop17->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche17_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.34 && p<0.36 ) {
					h_pim_matche18->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop18->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche18_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.36 && p<0.38 ) {
					h_pim_matche19->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop19->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche19_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.38 && p<0.40 ) {
					h_pim_matche20->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop20->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche20_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.40 && p<0.42 ) {
					h_pim_matche21->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop21->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche21_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.42 && p<0.44 ) {
					h_pim_matche22->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop22->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche22_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.44 && p<0.46 ) {
					h_pim_matche23->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop23->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche23_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.46 && p<0.48 ) {
					h_pim_matche24->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop24->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche24_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.48 && p<0.50 ) {
					h_pim_matche25->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop25->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche25_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.50 && p<0.52 ) {
					h_pim_matche26->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop26->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche26_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.52 && p<0.54 ) {
					h_pim_matche27->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop27->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche27_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.54 && p<0.56 ) {
					h_pim_matche28->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop28->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche28_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.56 && p<0.58 ) {
					h_pim_matche29->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop29->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche29_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.58 && p<0.60 ) {
					h_pim_matche30->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop30->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche30_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.60 && p<0.62 ) {
					h_pim_matche31->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop31->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche31_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.62 && p<0.64 ) {
					h_pim_matche32->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop32->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche32_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.64 && p<0.66 ) {
					h_pim_matche33->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop33->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche33_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.66 && p<0.68 ) {
					h_pim_matche34->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop34->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche34_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.68 && p<0.70 ) {
					h_pim_matche35->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop35->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche35_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.70 && p<0.72 ) {
					h_pim_matche36->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop36->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche36_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.72 && p<0.74 ) {
					h_pim_matche37->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop37->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche37_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.74 && p<0.76 ) {
					h_pim_matche38->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop38->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche38_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.76 && p<0.78 ) {
					h_pim_matche39->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop39->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche39_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.78 && p<0.80 ) {
					h_pim_matche40->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop40->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche40_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.80 && p<0.82 ) {
					h_pim_matche41->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop41->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche41_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.82 && p<0.84 ) {
					h_pim_matche42->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop42->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche42_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.84 && p<0.86 ) {
					h_pim_matche43->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop43->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche43_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.86 && p<0.88 ) {
					h_pim_matche44->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop44->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche44_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.88 && p<0.90 ) {
					h_pim_matche45->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop45->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche45_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.90 && p<0.92 ) {
					h_pim_matche46->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop46->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche46_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.92 && p<0.94 ) {
					h_pim_matche47->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop47->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche47_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.94 && p<0.96 ) {
					h_pim_matche48->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop48->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche48_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.96 && p<0.98 ) {
					h_pim_matche49->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop49->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche49_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>0.98 && p<1.00 ) {
					h_pim_matche50->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop50->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche50_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.00 && p<1.02 ) {
					h_pim_matche51->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop51->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche51_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.02 && p<1.04 ) {
					h_pim_matche52->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop52->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche52_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.04 && p<1.06 ) {
					h_pim_matche53->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop53->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche53_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.06 && p<1.08 ) {
					h_pim_matche54->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop54->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche54_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.08 && p<1.10 ) {
					h_pim_matche55->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop55->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche55_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.10 && p<1.12 ) {
					h_pim_matche56->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop56->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche56_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.12 && p<1.14 ) {
					h_pim_matche57->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop57->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche57_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.14 && p<1.16 ) {
					h_pim_matche58->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop58->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche58_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.16 && p<1.18 ) {
					h_pim_matche59->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop59->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche59_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.18 && p<1.20 ) {
					h_pim_matche60->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop60->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche60_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.20 && p<1.22 ) {
					h_pim_matche61->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop61->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche61_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.22 && p<1.24 ) {
					h_pim_matche62->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop62->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche62_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.24 && p<1.26 ) {
					h_pim_matche63->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop63->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche63_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.26 && p<1.28 ) {
					h_pim_matche64->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop64->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche64_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.28 && p<1.30 ) {
					h_pim_matche65->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop65->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche65_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.30 && p<1.32 ) {
					h_pim_matche66->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop66->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche66_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.32 && p<1.34 ) {
					h_pim_matche67->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop67->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche67_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.34 && p<1.36 ) {
					h_pim_matche68->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop68->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche68_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.36 && p<1.38 ) {
					h_pim_matche69->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop69->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche69_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.38 && p<1.40 ) {
					h_pim_matche70->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop70->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche70_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.40 && p<1.42 ) {
					h_pim_matche71->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop71->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche71_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.42 && p<1.44 ) {
					h_pim_matche72->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop72->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche72_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.44 && p<1.46 ) {
					h_pim_matche73->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop73->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche73_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.46 && p<1.48 ) {
					h_pim_matche74->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop74->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche74_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.48 && p<1.50 ) {
					h_pim_matche75->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop75->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche75_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.50 && p<1.52 ) {
					h_pim_matche76->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop76->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche76_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.52 && p<1.54 ) {
					h_pim_matche77->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop77->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche77_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.54 && p<1.56 ) {
					h_pim_matche78->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop78->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche78_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.56 && p<1.58 ) {
					h_pim_matche79->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop79->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche79_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.58 && p<1.60 ) {
					h_pim_matche80->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop80->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche80_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.60 && p<1.62 ) {
					h_pim_matche81->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop81->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche81_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.62 && p<1.64 ) {
					h_pim_matche82->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop82->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche82_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.64 && p<1.66 ) {
					h_pim_matche83->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop83->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche83_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.66 && p<1.68 ) {
					h_pim_matche84->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop84->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche84_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.68 && p<1.70 ) {
					h_pim_matche85->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop85->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche85_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.70 && p<1.72 ) {
					h_pim_matche86->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop86->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche86_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.72 && p<1.74 ) {
					h_pim_matche87->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop87->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche87_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.74 && p<1.76 ) {
					h_pim_matche88->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop88->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche88_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.76 && p<1.78 ) {
					h_pim_matche89->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop89->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche89_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.78 && p<1.80 ) {
					h_pim_matche90->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop90->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche90_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.80 && p<1.82 ) {
					h_pim_matche91->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop91->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche91_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.82 && p<1.84 ) {
					h_pim_matche92->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop92->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche92_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.84 && p<1.86 ) {
					h_pim_matche93->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop93->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche93_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.86 && p<1.88 ) {
					h_pim_matche94->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop94->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche94_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.88 && p<1.90 ) {
					h_pim_matche95->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop95->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche95_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.90 && p<1.92 ) {
					h_pim_matche96->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop96->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche96_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.92 && p<1.94 ) {
					h_pim_matche97->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop97->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche97_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.94 && p<1.96 ) {
					h_pim_matche98->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop98->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche98_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.96 && p<1.98 ) {
					h_pim_matche99->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop99->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche99_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 } 
				 else if( p>1.98 && p<2.00 ) {
					h_pim_matche100->fill( trackItr->trackShowerMatch()->matchedEnergy() );
                                         	h_pim_eop100->fill( trackItr->trackShowerMatch()->eOverP() );
	                                        if( trackItr->trackShowerMatch()->eOverP() < 0.8)
                                                  	h_pim_matche100_eop->fill( trackItr->trackShowerMatch()->matchedEnergy() );
				 }




			 }
		 }
		 if(isGoodKaon(*trackItr)) {	
			 double p = pionFit->pmag();
			 h_kaon_p->fill( p );
		 
			 // MC
			 if( pdg_id == 211 )
				 h_kaon_mcpion_p->fill( p );
			 else if( pdg_id == 321 )
				 h_kaon_mckaon_p->fill( p );
			 else if( pdg_id == 2212 )
				 h_kaon_mcproton_p->fill( p );

			 h_kaon_matche->fill( trackItr->trackShowerMatch()->matchedEnergy() );

			 if( pionFit->charge() > 0. ) {
			 if( p>0. && p<0.1 )
				 h_kp_matche1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_kp_matche2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_kp_matche3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_kp_matche4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_kp_matche5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_kp_matche6->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_kp_matche7->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_kp_matche8->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_kp_matche9->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_kp_matche10->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_kp_matche11->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_kp_matche12->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_kp_matche13->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_kp_matche14->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_kp_matche15->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_kp_matche16->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_kp_matche17->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_kp_matche18->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_kp_matche19->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_kp_matche20->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 } else {
			 if( p>0. && p<0.1 )
				 h_km_matche1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_km_matche2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_km_matche3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_km_matche4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_km_matche5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_km_matche6->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_km_matche7->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_km_matche8->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_km_matche9->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_km_matche10->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_km_matche11->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_km_matche12->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_km_matche13->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_km_matche14->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_km_matche15->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_km_matche16->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_km_matche17->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_km_matche18->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_km_matche19->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_km_matche20->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 }
		 }
		 if(isGoodProton(*trackItr)) { 
			 double p = pionFit->pmag();
			 h_proton_p->fill( p );

			 // MC
			 if( pdg_id == 211 )
				 h_proton_mcpion_p->fill( p );
			 else if( pdg_id == 321 )
				 h_proton_mckaon_p->fill( p );
			 else if( pdg_id == 2212 )
				 h_proton_mcproton_p->fill( p );

			 h_proton_matche->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 if( pionFit->charge() > 0.) {
			 if( p>0. && p<0.1 )
				 h_pp_matche1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_pp_matche2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_pp_matche3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_pp_matche4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_pp_matche5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_pp_matche6->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_pp_matche7->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_pp_matche8->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_pp_matche9->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_pp_matche10->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_pp_matche11->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_pp_matche12->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_pp_matche13->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_pp_matche14->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_pp_matche15->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_pp_matche16->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_pp_matche17->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_pp_matche18->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_pp_matche19->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_pp_matche20->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 } else {
			 if( p>0. && p<0.1 )
				 h_pm_matche1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_pm_matche2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_pm_matche3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_pm_matche4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_pm_matche5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_pm_matche6->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_pm_matche7->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_pm_matche8->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_pm_matche9->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_pm_matche10->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_pm_matche11->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_pm_matche12->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_pm_matche13->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_pm_matche14->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_pm_matche15->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_pm_matche16->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_pm_matche17->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_pm_matche18->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_pm_matche19->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_pm_matche20->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 }
		 }
		 }

		 // ENDCAP

		 if(is_endcap) {
		 if(isGoodPion(*trackItr)) {
			 double p = pionFit->pmag();
			 h_pion_p_endcap->fill( p );

			 h_pion_matche_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 if( p>0. && p<0.1 )
				 h_pion_matche1_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_pion_matche2_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_pion_matche3_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_pion_matche3_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_pion_matche4_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_pion_matche5_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_pion_matche6_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_pion_matche7_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_pion_matche8_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_pion_matche10_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_pion_matche11_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_pion_matche12_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_pion_matche13_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_pion_matche14_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_pion_matche15_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_pion_matche16_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_pion_matche17_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_pion_matche18_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_pion_matche19_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_pion_matche20_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
		 }
		 if(isGoodKaon(*trackItr)) {
			 double p = pionFit->pmag();
			 h_kaon_p_endcap->fill( p );

			 h_kaon_matche_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 if( p>0. && p<0.1 )
				 h_kaon_matche1_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_kaon_matche2_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_kaon_matche3_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_kaon_matche3_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_kaon_matche4_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_kaon_matche5_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_kaon_matche6_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_kaon_matche7_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_kaon_matche8_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_kaon_matche10_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_kaon_matche11_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_kaon_matche12_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_kaon_matche13_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_kaon_matche14_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_kaon_matche15_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_kaon_matche16_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_kaon_matche17_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_kaon_matche18_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_kaon_matche19_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_kaon_matche20_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );

		 }
		 if(isGoodProton(*trackItr)) { 
			 double p = pionFit->pmag();
			 h_proton_p_endcap->fill( p );

			 h_proton_matche_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 if( p>0. && p<0.1 )
				 h_proton_matche1_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_proton_matche2_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_proton_matche3_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_proton_matche3_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_proton_matche4_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_proton_matche5_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_proton_matche6_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_proton_matche7_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_proton_matche8_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_proton_matche10_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_proton_matche11_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_proton_matche12_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_proton_matche13_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_proton_matche14_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_proton_matche15_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_proton_matche16_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_proton_matche17_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_proton_matche18_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_proton_matche19_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_proton_matche20_endcap->fill( trackItr->trackShowerMatch()->matchedEnergy() );

		 }
		 }

		 // cuts?
		 //double p = pionFit->pmag();
		 if(costh < 0.2) {
		 if(isGoodPion(*trackItr)) {
			 if( pionFit->charge() > 0. ) {
			 if( p>0. && p<0.1 )
				 h_pip_matche1_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_pip_matche2_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_pip_matche3_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_pip_matche4_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_pip_matche5_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_pip_matche6_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_pip_matche7_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_pip_matche8_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_pip_matche9_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_pip_matche10_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_pip_matche11_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_pip_matche12_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_pip_matche13_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_pip_matche14_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_pip_matche15_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_pip_matche16_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_pip_matche17_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_pip_matche18_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_pip_matche19_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_pip_matche20_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 } else {
			 if( p>0. && p<0.1 )
				 h_pim_matche1_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_pim_matche2_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_pim_matche3_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_pim_matche4_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_pim_matche5_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_pim_matche6_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_pim_matche7_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_pim_matche8_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_pim_matche9_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_pim_matche10_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_pim_matche11_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_pim_matche12_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_pim_matche13_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_pim_matche14_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_pim_matche15_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_pim_matche16_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_pim_matche17_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_pim_matche18_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_pim_matche19_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_pim_matche20_cut1->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 }
		 }
		 }

		 if(costh > 0.2 && costh < 0.4) {
		 if(isGoodPion(*trackItr)) {
			 if( pionFit->charge() > 0. ) {
			 if( p>0. && p<0.1 )
				 h_pip_matche1_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_pip_matche2_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_pip_matche3_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_pip_matche4_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_pip_matche5_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_pip_matche6_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_pip_matche7_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_pip_matche8_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_pip_matche9_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_pip_matche10_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_pip_matche11_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_pip_matche12_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_pip_matche13_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_pip_matche14_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_pip_matche15_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_pip_matche16_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_pip_matche17_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_pip_matche18_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_pip_matche19_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_pip_matche20_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 } else {
			 if( p>0. && p<0.1 )
				 h_pim_matche1_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_pim_matche2_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_pim_matche3_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_pim_matche4_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_pim_matche5_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_pim_matche6_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_pim_matche7_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_pim_matche8_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_pim_matche9_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_pim_matche10_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_pim_matche11_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_pim_matche12_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_pim_matche13_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_pim_matche14_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_pim_matche15_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_pim_matche16_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_pim_matche17_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_pim_matche18_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_pim_matche19_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_pim_matche20_cut2->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 }
		 }
		 }

		 if(costh > 0.4 && costh < 0.6) {
		 if(isGoodPion(*trackItr)) {
			 if( pionFit->charge() > 0. ) {
			 if( p>0. && p<0.1 )
				 h_pip_matche1_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_pip_matche2_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_pip_matche3_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_pip_matche4_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_pip_matche5_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_pip_matche6_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_pip_matche7_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_pip_matche8_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_pip_matche9_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_pip_matche10_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_pip_matche11_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_pip_matche12_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_pip_matche13_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_pip_matche14_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_pip_matche15_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_pip_matche16_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_pip_matche17_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_pip_matche18_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_pip_matche19_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_pip_matche20_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 } else {
			 if( p>0. && p<0.1 )
				 h_pim_matche1_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_pim_matche2_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_pim_matche3_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_pim_matche4_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_pim_matche5_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_pim_matche6_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_pim_matche7_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_pim_matche8_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_pim_matche9_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_pim_matche10_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_pim_matche11_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_pim_matche12_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_pim_matche13_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_pim_matche14_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_pim_matche15_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_pim_matche16_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_pim_matche17_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_pim_matche18_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_pim_matche19_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_pim_matche20_cut3->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 }
		 }
		 }

		 if(costh > 0.6 && costh < 0.75) {
		 if(isGoodPion(*trackItr)) {
			 if( pionFit->charge() > 0. ) {
			 if( p>0. && p<0.1 )
				 h_pip_matche1_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_pip_matche2_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_pip_matche3_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_pip_matche4_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_pip_matche5_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_pip_matche6_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_pip_matche7_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_pip_matche8_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_pip_matche9_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_pip_matche10_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_pip_matche11_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_pip_matche12_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_pip_matche13_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_pip_matche14_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_pip_matche15_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_pip_matche16_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_pip_matche17_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_pip_matche18_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_pip_matche19_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_pip_matche20_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 } else {
			 if( p>0. && p<0.1 )
				 h_pim_matche1_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_pim_matche2_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_pim_matche3_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_pim_matche4_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_pim_matche5_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_pim_matche6_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_pim_matche7_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_pim_matche8_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_pim_matche9_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_pim_matche10_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_pim_matche11_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_pim_matche12_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_pim_matche13_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_pim_matche14_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_pim_matche15_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_pim_matche16_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_pim_matche17_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_pim_matche18_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_pim_matche19_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_pim_matche20_cut4->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 }
		 }
		 }

		 if(costh > 0.6 && costh < 0.81) {
		 if(isGoodPion(*trackItr)) {
			 if( pionFit->charge() > 0. ) {
			 if( p>0. && p<0.1 )
				 h_pip_matche1_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_pip_matche2_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_pip_matche3_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_pip_matche4_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_pip_matche5_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_pip_matche6_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_pip_matche7_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_pip_matche8_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_pip_matche9_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_pip_matche10_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_pip_matche11_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_pip_matche12_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_pip_matche13_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_pip_matche14_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_pip_matche15_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_pip_matche16_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_pip_matche17_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_pip_matche18_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_pip_matche19_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_pip_matche20_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 } else {
			 if( p>0. && p<0.1 )
				 h_pim_matche1_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.1 && p<0.2 )
				 h_pim_matche2_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.2 && p<0.3 )
				 h_pim_matche3_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.3 && p<0.4 )
				 h_pim_matche4_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.4 && p<0.5 )
				 h_pim_matche5_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.5 && p<0.6 )
				 h_pim_matche6_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.6 && p<0.7 )
				 h_pim_matche7_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.7 && p<0.8 )
				 h_pim_matche8_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.8 && p<0.9 )
				 h_pim_matche9_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>0.9 && p<1.0 )
				 h_pim_matche10_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.0 && p<1.1 )
				 h_pim_matche11_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.1 && p<1.2 )
				 h_pim_matche12_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.2 && p<1.3 )
				 h_pim_matche13_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.3 && p<1.4 )
				 h_pim_matche14_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.4 && p<1.5 )
				 h_pim_matche15_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.5 && p<1.6 )
				 h_pim_matche16_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.6 && p<1.7 )
				 h_pim_matche17_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.7 && p<1.8 )
				 h_pim_matche18_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.8 && p<1.9 )
				 h_pim_matche19_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 else if( p>1.9 && p<2. )
				 h_pim_matche20_cut5->fill( trackItr->trackShowerMatch()->matchedEnergy() );
			 }
		 }
		 }

	 }
      }
   }
   
   return ActionBase::kPassed;
}


ActionBase::ActionResult
Bin20_JpsiPiPiProc::beginRun( Frame& iFrame )       // anal2 equiv.
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

   return ActionBase::kPassed;
}


/*
ActionBase::ActionResult
Bin20_JpsiPiPiProc::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/


double Bin20_JpsiPiPiProc::calcDOCA( double iD,
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
