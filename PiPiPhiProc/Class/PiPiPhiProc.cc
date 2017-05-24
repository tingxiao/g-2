// -*- C++ -*-
//
// Package:     PiPiPhiProc
// Module:      PiPiPhiProc
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
#include "PiPiPhiProc/PiPiPhiProc.h"
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
static const char* const kFacilityString = "Processor.PiPiPhiProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.33 2002/12/18 01:45:06 cdj Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// static data member definitions
//

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
//   if( (kaonFit->pmag() < 0.6) && (fabs(k_sig) > 3) )
//      return false;
   
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


   return ( ( DL_kpi < 0. ) && ( DL_kp < 0. ) );
}


//
// constructors and destructor
//
PiPiPhiProc::PiPiPhiProc( void )               // anal1
   : Processor( "PiPiPhiProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &PiPiPhiProc::event,    Stream::kEvent );
   bind( &PiPiPhiProc::beginRun, Stream::kBeginRun );
   //bind( &PiPiPhiProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

PiPiPhiProc::~PiPiPhiProc()                    // anal5
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
PiPiPhiProc::init( void )          // anal1 "Interactive"
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
PiPiPhiProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------

enum { k_NShower, k_NTrack, k_TCharge, 
       k_Energy_1, k_Barrel_1, k_Theta_1, k_Phi_1, k_Split_1, k_X925_1,
       k_Energy_2, k_Barrel_2, k_Theta_2, k_Phi_2, k_Split_2, k_X925_2,
       k_Energy_3, k_Barrel_3, k_Theta_3, k_Phi_3, k_Split_3, k_X925_3,
       k_Energy_4, k_Barrel_4, k_Theta_4, k_Phi_4, k_Split_4, k_X925_4,
       k_Energy_5, k_Barrel_5, k_Theta_5, k_Phi_5, k_Split_5, k_X925_5,
       k_Energy_6, k_Barrel_6, k_Theta_6, k_Phi_6, k_Split_6, k_X925_6,

       k_TE_1, k_Px_1, k_Py_1, k_Pz_1, 
       k_kTE_1, k_kPx_1, k_kPy_1, k_kPz_1, 
       k_pTE_1, k_pPx_1, k_pPy_1, k_pPz_1, 
         k_Chg_1, k_DOCA_1, k_Z0_1, k_ReChiSq_1, k_EID_1, k_MuID_1,
         k_LLpi_1, k_LLk_1, k_LLp_1, k_LLe_1, k_LLmu_1, 
         k_SigPi_1, k_SigK_1, k_SigP_1, k_SigE_1, k_SigMu_1,
         k_DL_pip_1, k_DL_pik_1, k_DL_pie_1, k_DL_pimu_1, k_DL_pk_1,
       k_TE_2, k_Px_2, k_Py_2, k_Pz_2, 
       k_kTE_2, k_kPx_2, k_kPy_2, k_kPz_2, 
       k_pTE_2, k_pPx_2, k_pPy_2, k_pPz_2, 
         k_Chg_2, k_DOCA_2, k_Z0_2, k_ReChiSq_2, k_EID_2, k_MuID_2,
         k_LLpi_2, k_LLk_2, k_LLp_2, k_LLe_2, k_LLmu_2, 
         k_SigPi_2, k_SigK_2, k_SigP_2, k_SigE_2, k_SigMu_2,
         k_DL_pip_2, k_DL_pik_2, k_DL_pie_2, k_DL_pimu_2, k_DL_pk_2,
       k_TE_3, k_Px_3, k_Py_3, k_Pz_3, 
       k_kTE_3, k_kPx_3, k_kPy_3, k_kPz_3, 
       k_pTE_3, k_pPx_3, k_pPy_3, k_pPz_3, 
         k_Chg_3, k_DOCA_3, k_Z0_3, k_ReChiSq_3, k_EID_3, k_MuID_3,
         k_LLpi_3, k_LLk_3, k_LLp_3, k_LLe_3, k_LLmu_3, 
         k_SigPi_3, k_SigK_3, k_SigP_3, k_SigE_3, k_SigMu_3,
         k_DL_pip_3, k_DL_pik_3, k_DL_pie_3, k_DL_pimu_3, k_DL_pk_3,
       k_TE_4, k_Px_4, k_Py_4, k_Pz_4, 
       k_kTE_4, k_kPx_4, k_kPy_4, k_kPz_4, 
       k_pTE_4, k_pPx_4, k_pPy_4, k_pPz_4, 
         k_Chg_4, k_DOCA_4, k_Z0_4, k_ReChiSq_4, k_EID_4, k_MuID_4,
         k_LLpi_4, k_LLk_4, k_LLp_4, k_LLe_4, k_LLmu_4, 
         k_SigPi_4, k_SigK_4, k_SigP_4, k_SigE_4, k_SigMu_4,
         k_DL_pip_4, k_DL_pik_4, k_DL_pie_4, k_DL_pimu_4, k_DL_pk_4,
       k_TE_5, k_Px_5, k_Py_5, k_Pz_5, 
       k_kTE_5, k_kPx_5, k_kPy_5, k_kPz_5, 
       k_pTE_5, k_pPx_5, k_pPy_5, k_pPz_5, 
         k_Chg_5, k_DOCA_5, k_Z0_5, k_ReChiSq_5, k_EID_5, k_MuID_5,
         k_LLpi_5, k_LLk_5, k_LLp_5, k_LLe_5, k_LLmu_5, 
         k_SigPi_5, k_SigK_5, k_SigP_5, k_SigE_5, k_SigMu_5,
         k_DL_pip_5, k_DL_pik_5, k_DL_pie_5, k_DL_pimu_5, k_DL_pk_5,
       k_TE_6, k_Px_6, k_Py_6, k_Pz_6, 
       k_kTE_6, k_kPx_6, k_kPy_6, k_kPz_6, 
       k_pTE_6, k_pPx_6, k_pPy_6, k_pPz_6, 
         k_Chg_6, k_DOCA_6, k_Z0_6, k_ReChiSq_6, k_EID_6, k_MuID_6,
         k_LLpi_6, k_LLk_6, k_LLp_6, k_LLe_6, k_LLmu_6, 
         k_SigPi_6, k_SigK_6, k_SigP_6, k_SigE_6, k_SigMu_6,
         k_DL_pip_6, k_DL_pik_6, k_DL_pie_6, k_DL_pimu_6, k_DL_pk_6,

       k_pipi_Pi1_E, k_pipi_Pi1_Px, k_pipi_Pi1_Py, k_pipi_Pi1_Pz, 
       k_pipi_Pi2_E, k_pipi_Pi2_Px, k_pipi_Pi2_Py, k_pipi_Pi2_Pz, 
       k_pipi_Pi3_E, k_pipi_Pi3_Px, k_pipi_Pi3_Py, k_pipi_Pi3_Pz, 
       k_pipi_Pi4_E, k_pipi_Pi4_Px, k_pipi_Pi4_Py, k_pipi_Pi4_Pz, 
       k_pipi_Pi5_E, k_pipi_Pi5_Px, k_pipi_Pi5_Py, k_pipi_Pi5_Pz, 
       k_pipi_Pi6_E, k_pipi_Pi6_Px, k_pipi_Pi6_Py, k_pipi_Pi6_Pz, 
       k_pipi_Psip_VtxChisq, k_pipi_Psip_FitChisq, 

       k_kk_K1_E, k_kk_K1_Px, k_kk_K1_Py, k_kk_K1_Pz, 
       k_kk_K2_E, k_kk_K2_Px, k_kk_K2_Py, k_kk_K2_Pz, 
       k_kk_Pi1_E, k_kk_Pi1_Px, k_kk_Pi1_Py, k_kk_Pi1_Pz, 
       k_kk_Pi2_E, k_kk_Pi2_Px, k_kk_Pi2_Py, k_kk_Pi2_Pz, 
       k_kk_Pi3_E, k_kk_Pi3_Px, k_kk_Pi3_Py, k_kk_Pi3_Pz, 
       k_kk_Pi4_E, k_kk_Pi4_Px, k_kk_Pi4_Py, k_kk_Pi4_Pz, 
       k_kk_Psip_VtxChisq, k_kk_Psip_FitChisq, 

       k_matchE_1, k_matchE_2, k_matchE_3, k_matchE_4, k_matchE_5, k_matchE_6,
       k_mudepth_1, k_mudepth_2, k_mudepth_3, k_mudepth_4, k_mudepth_5, k_mudepth_6,

       k_EP_1, k_EP_2, k_EP_3, k_EP_4, k_EP_5, k_EP_6, 

       kNumVars };


void
PiPiPhiProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here
   HINtupleVarNames ntNames(kNumVars);

   ntNames.addVar(k_NShower, "NShower");
   ntNames.addVar(k_NTrack, "NTrack");
   ntNames.addVar(k_TCharge, "TCharge");

   ntNames.addVar(k_Energy_1, "E1");
   ntNames.addVar(k_Barrel_1, "Barrel1");
   ntNames.addVar(k_Theta_1, "Theta1");
   ntNames.addVar(k_Phi_1, "Phi1");
   ntNames.addVar(k_Split_1, "Split1");
   ntNames.addVar(k_X925_1, "X9251");
   ntNames.addVar(k_Energy_2, "E2");
   ntNames.addVar(k_Barrel_2, "Barrel2");
   ntNames.addVar(k_Theta_2, "Theta2");
   ntNames.addVar(k_Phi_2, "Phi2");
   ntNames.addVar(k_Split_2, "Split2");
   ntNames.addVar(k_X925_2, "X9252");
   ntNames.addVar(k_Energy_3, "E3");
   ntNames.addVar(k_Barrel_3, "Barrel3");
   ntNames.addVar(k_Theta_3, "Theta3");
   ntNames.addVar(k_Phi_3, "Phi3");
   ntNames.addVar(k_Split_3, "Split3");
   ntNames.addVar(k_X925_3, "X9253");
   ntNames.addVar(k_Energy_4, "E4");
   ntNames.addVar(k_Barrel_4, "Barrel4");
   ntNames.addVar(k_Theta_4, "Theta4");
   ntNames.addVar(k_Phi_4, "Phi4");
   ntNames.addVar(k_Split_4, "Split4");
   ntNames.addVar(k_X925_4, "X9254");
   ntNames.addVar(k_Energy_5, "E5");
   ntNames.addVar(k_Barrel_5, "Barrel5");
   ntNames.addVar(k_Theta_5, "Theta5");
   ntNames.addVar(k_Phi_5, "Phi5");
   ntNames.addVar(k_Split_5, "Split5");
   ntNames.addVar(k_X925_5, "X9255");
   ntNames.addVar(k_Energy_6, "E6");
   ntNames.addVar(k_Barrel_6, "Barrel6");
   ntNames.addVar(k_Theta_6, "Theta6");
   ntNames.addVar(k_Phi_6, "Phi6");
   ntNames.addVar(k_Split_6, "Split6");
   ntNames.addVar(k_X925_6, "X9256");



   // track data
   ntNames.addVar(k_TE_1, "TE1");
   ntNames.addVar(k_Px_1, "Px1");
   ntNames.addVar(k_Py_1, "Py1");
   ntNames.addVar(k_Pz_1, "Pz1");
   ntNames.addVar(k_kTE_1, "kTE1");
   ntNames.addVar(k_kPx_1, "kPx1");
   ntNames.addVar(k_kPy_1, "kPy1");
   ntNames.addVar(k_kPz_1, "kPz1");
   ntNames.addVar(k_pTE_1, "pTE1");
   ntNames.addVar(k_pPx_1, "pPx1");
   ntNames.addVar(k_pPy_1, "pPy1");
   ntNames.addVar(k_pPz_1, "pPz1");
   ntNames.addVar(k_Chg_1, "Chg1"); 
   ntNames.addVar(k_DOCA_1, "DOCA1");
   ntNames.addVar(k_Z0_1, "Z01");
   ntNames.addVar(k_ReChiSq_1, "Rchisq1");
   ntNames.addVar(k_EID_1, "EID1");
   ntNames.addVar(k_MuID_1, "MuID1");
   ntNames.addVar(k_LLpi_1, "LLpi1");
   ntNames.addVar(k_LLk_1, "LLk1");
   ntNames.addVar(k_LLp_1, "LLp1");
   ntNames.addVar(k_LLe_1, "LLe1");
   ntNames.addVar(k_LLmu_1, "LLmu1");
   ntNames.addVar(k_SigPi_1, "SigPi1");
   ntNames.addVar(k_SigK_1, "SigK1");
   ntNames.addVar(k_SigP_1, "SigP1");
   ntNames.addVar(k_SigE_1, "SigE1");
   ntNames.addVar(k_SigMu_1, "SigMu1");
   ntNames.addVar(k_DL_pip_1, "DLpip1");
   ntNames.addVar(k_DL_pik_1, "DLpik1");
   ntNames.addVar(k_DL_pk_1, "DLpk1");
   ntNames.addVar(k_DL_pie_1, "DLpie1");
   ntNames.addVar(k_DL_pimu_1, "DLpimu1");
   ntNames.addVar(k_TE_2, "TE2"); 
   ntNames.addVar(k_Px_2, "Px2"); 
   ntNames.addVar(k_Py_2, "Py2"); 
   ntNames.addVar(k_Pz_2, "Pz2"); 
   ntNames.addVar(k_kTE_2, "kTE2"); 
   ntNames.addVar(k_kPx_2, "kPx2"); 
   ntNames.addVar(k_kPy_2, "kPy2"); 
   ntNames.addVar(k_kPz_2, "kPz2"); 
   ntNames.addVar(k_pTE_2, "pTE2"); 
   ntNames.addVar(k_pPx_2, "pPx2"); 
   ntNames.addVar(k_pPy_2, "pPy2"); 
   ntNames.addVar(k_pPz_2, "pPz2"); 
   ntNames.addVar(k_Chg_2, "Chg2"); 
   ntNames.addVar(k_DOCA_2, "DOCA2");
   ntNames.addVar(k_Z0_2, "Z02");
   ntNames.addVar(k_ReChiSq_2, "Rchisq2");
   ntNames.addVar(k_EID_2, "EID2");
   ntNames.addVar(k_MuID_2, "MuID2");
   ntNames.addVar(k_LLpi_2, "LLpi2");
   ntNames.addVar(k_LLk_2, "LLk2");
   ntNames.addVar(k_LLp_2, "LLp2");
   ntNames.addVar(k_LLe_2, "LLe2");
   ntNames.addVar(k_LLmu_2, "LLmu2");
   ntNames.addVar(k_SigPi_2, "SigPi2");
   ntNames.addVar(k_SigK_2, "SigK2");
   ntNames.addVar(k_SigP_2, "SigP2");
   ntNames.addVar(k_SigE_2, "SigE2");
   ntNames.addVar(k_SigMu_2, "SigMu2");
   ntNames.addVar(k_DL_pip_2, "DLpip2");
   ntNames.addVar(k_DL_pik_2, "DLpik2");
   ntNames.addVar(k_DL_pk_2, "DLpk2");
   ntNames.addVar(k_DL_pie_2, "DLpie2");
   ntNames.addVar(k_DL_pimu_2, "DLpimu2");
   ntNames.addVar(k_TE_3, "TE3"); 
   ntNames.addVar(k_Px_3, "Px3"); 
   ntNames.addVar(k_Py_3, "Py3"); 
   ntNames.addVar(k_Pz_3, "Pz3"); 
   ntNames.addVar(k_kTE_3, "kTE3"); 
   ntNames.addVar(k_kPx_3, "kPx3"); 
   ntNames.addVar(k_kPy_3, "kPy3"); 
   ntNames.addVar(k_kPz_3, "kPz3"); 
   ntNames.addVar(k_pTE_3, "pTE3"); 
   ntNames.addVar(k_pPx_3, "pPx3"); 
   ntNames.addVar(k_pPy_3, "pPy3"); 
   ntNames.addVar(k_pPz_3, "pPz3"); 
   ntNames.addVar(k_Chg_3, "Chg3"); 
   ntNames.addVar(k_DOCA_3, "DOCA3");
   ntNames.addVar(k_Z0_3, "Z03");
   ntNames.addVar(k_ReChiSq_3, "Rchisq3");
   ntNames.addVar(k_EID_3, "EID3");
   ntNames.addVar(k_MuID_3, "MuID3");
   ntNames.addVar(k_LLpi_3, "LLpi3");
   ntNames.addVar(k_LLk_3, "LLk3");
   ntNames.addVar(k_LLp_3, "LLp3");
   ntNames.addVar(k_LLe_3, "LLe3");
   ntNames.addVar(k_LLmu_3, "LLmu3");
   ntNames.addVar(k_SigPi_3, "SigPi3");
   ntNames.addVar(k_SigK_3, "SigK3");
   ntNames.addVar(k_SigP_3, "SigP3");
   ntNames.addVar(k_SigE_3, "SigE3");
   ntNames.addVar(k_SigMu_3, "SigMu3");
   ntNames.addVar(k_DL_pip_3, "DLpip3");
   ntNames.addVar(k_DL_pik_3, "DLpik3");
   ntNames.addVar(k_DL_pk_3, "DLpk3");
   ntNames.addVar(k_DL_pie_3, "DLpie3");
   ntNames.addVar(k_DL_pimu_3, "DLpimu3");
   ntNames.addVar(k_TE_4, "TE4"); 
   ntNames.addVar(k_Px_4, "Px4"); 
   ntNames.addVar(k_Py_4, "Py4"); 
   ntNames.addVar(k_Pz_4, "Pz4"); 
   ntNames.addVar(k_kTE_4, "kTE4"); 
   ntNames.addVar(k_kPx_4, "kPx4"); 
   ntNames.addVar(k_kPy_4, "kPy4"); 
   ntNames.addVar(k_kPz_4, "kPz4"); 
   ntNames.addVar(k_pTE_4, "pTE4"); 
   ntNames.addVar(k_pPx_4, "pPx4"); 
   ntNames.addVar(k_pPy_4, "pPy4"); 
   ntNames.addVar(k_pPz_4, "pPz4"); 
   ntNames.addVar(k_Chg_4, "Chg4"); 
   ntNames.addVar(k_DOCA_4, "DOCA4");
   ntNames.addVar(k_Z0_4, "Z04");
   ntNames.addVar(k_ReChiSq_4, "Rchisq4");
   ntNames.addVar(k_EID_4, "EID4");
   ntNames.addVar(k_MuID_4, "MuID4");
   ntNames.addVar(k_LLpi_4, "LLpi4");
   ntNames.addVar(k_LLk_4, "LLk4");
   ntNames.addVar(k_LLp_4, "LLp4");
   ntNames.addVar(k_LLe_4, "LLe4");
   ntNames.addVar(k_LLmu_4, "LLmu4");
   ntNames.addVar(k_SigPi_4, "SigPi4");
   ntNames.addVar(k_SigK_4, "SigK4");
   ntNames.addVar(k_SigP_4, "SigP4");
   ntNames.addVar(k_SigE_4, "SigE4");
   ntNames.addVar(k_SigMu_4, "SigMu4");
   ntNames.addVar(k_DL_pip_4, "DLpip4");
   ntNames.addVar(k_DL_pik_4, "DLpik4");
   ntNames.addVar(k_DL_pk_4, "DLpk4");
   ntNames.addVar(k_DL_pie_4, "DLpie4");
   ntNames.addVar(k_DL_pimu_4, "DLpimu4");
   ntNames.addVar(k_TE_5, "TE5"); 
   ntNames.addVar(k_Px_5, "Px5"); 
   ntNames.addVar(k_Py_5, "Py5"); 
   ntNames.addVar(k_Pz_5, "Pz5"); 
   ntNames.addVar(k_kTE_5, "kTE5"); 
   ntNames.addVar(k_kPx_5, "kPx5"); 
   ntNames.addVar(k_kPy_5, "kPy5"); 
   ntNames.addVar(k_kPz_5, "kPz5"); 
   ntNames.addVar(k_pTE_5, "pTE5"); 
   ntNames.addVar(k_pPx_5, "pPx5"); 
   ntNames.addVar(k_pPy_5, "pPy5"); 
   ntNames.addVar(k_pPz_5, "pPz5"); 
   ntNames.addVar(k_Chg_5, "Chg5"); 
   ntNames.addVar(k_DOCA_5, "DOCA5");
   ntNames.addVar(k_Z0_5, "Z05");
   ntNames.addVar(k_ReChiSq_5, "Rchisq5");
   ntNames.addVar(k_EID_5, "EID5");
   ntNames.addVar(k_MuID_5, "MuID5");
   ntNames.addVar(k_LLpi_5, "LLpi5");
   ntNames.addVar(k_LLk_5, "LLk5");
   ntNames.addVar(k_LLp_5, "LLp5");
   ntNames.addVar(k_LLe_5, "LLe5");
   ntNames.addVar(k_LLmu_5, "LLmu5");
   ntNames.addVar(k_SigPi_5, "SigPi5");
   ntNames.addVar(k_SigK_5, "SigK5");
   ntNames.addVar(k_SigP_5, "SigP5");
   ntNames.addVar(k_SigE_5, "SigE5");
   ntNames.addVar(k_SigMu_5, "SigMu5");
   ntNames.addVar(k_DL_pip_5, "DLpip5");
   ntNames.addVar(k_DL_pik_5, "DLpik5");
   ntNames.addVar(k_DL_pk_5, "DLpk5");
   ntNames.addVar(k_DL_pie_5, "DLpie5");
   ntNames.addVar(k_DL_pimu_5, "DLpimu5");
   ntNames.addVar(k_TE_6, "TE6"); 
   ntNames.addVar(k_Px_6, "Px6"); 
   ntNames.addVar(k_Py_6, "Py6"); 
   ntNames.addVar(k_Pz_6, "Pz6"); 
   ntNames.addVar(k_kTE_6, "kTE6"); 
   ntNames.addVar(k_kPx_6, "kPx6"); 
   ntNames.addVar(k_kPy_6, "kPy6"); 
   ntNames.addVar(k_kPz_6, "kPz6"); 
   ntNames.addVar(k_pTE_6, "pTE6"); 
   ntNames.addVar(k_pPx_6, "pPx6"); 
   ntNames.addVar(k_pPy_6, "pPy6"); 
   ntNames.addVar(k_pPz_6, "pPz6"); 
   ntNames.addVar(k_Chg_6, "Chg6"); 
   ntNames.addVar(k_DOCA_6, "DOCA6");
   ntNames.addVar(k_Z0_6, "Z06");
   ntNames.addVar(k_ReChiSq_6, "Rchisq6");
   ntNames.addVar(k_EID_6, "EID6");
   ntNames.addVar(k_MuID_6, "MuID6");
   ntNames.addVar(k_LLpi_6, "LLpi6");
   ntNames.addVar(k_LLk_6, "LLk6");
   ntNames.addVar(k_LLp_6, "LLp6");
   ntNames.addVar(k_LLe_6, "LLe6");
   ntNames.addVar(k_LLmu_6, "LLmu6");
   ntNames.addVar(k_SigPi_6, "SigPi6");
   ntNames.addVar(k_SigK_6, "SigK6");
   ntNames.addVar(k_SigP_6, "SigP6");
   ntNames.addVar(k_SigE_6, "SigE6");
   ntNames.addVar(k_SigMu_6, "SigMu6");
   ntNames.addVar(k_DL_pip_6, "DLpip6");
   ntNames.addVar(k_DL_pik_6, "DLpik6");
   ntNames.addVar(k_DL_pk_6, "DLpk6");
   ntNames.addVar(k_DL_pie_6, "DLpie6");
   ntNames.addVar(k_DL_pimu_6, "DLpimu6");

   ntNames.addVar(k_EP_1, "EoP1");
   ntNames.addVar(k_EP_2, "EoP2");
   ntNames.addVar(k_EP_3, "EoP3");
   ntNames.addVar(k_EP_4, "EoP4");
   ntNames.addVar(k_EP_5, "EoP5");
   ntNames.addVar(k_EP_6, "EoP6");


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

   ntNames.addVar(k_pipi_Psip_VtxChisq, "PPsipVtx");
   ntNames.addVar(k_pipi_Psip_FitChisq, "PPsipFit");

   ntNames.addVar(k_kk_K1_E, "KK1E");
   ntNames.addVar(k_kk_K1_Px, "KK1Px");
   ntNames.addVar(k_kk_K1_Py, "KK1Py");
   ntNames.addVar(k_kk_K1_Pz, "KK1Pz");
   ntNames.addVar(k_kk_K2_E, "KK2E");
   ntNames.addVar(k_kk_K2_Px, "KK2Px");
   ntNames.addVar(k_kk_K2_Py, "KK2Py");
   ntNames.addVar(k_kk_K2_Pz, "KK2Pz");
   ntNames.addVar(k_kk_Pi1_E, "KPi1E");
   ntNames.addVar(k_kk_Pi1_Px, "KPi1Px");
   ntNames.addVar(k_kk_Pi1_Py, "KPi1Py");
   ntNames.addVar(k_kk_Pi1_Pz, "KPi1Pz");
   ntNames.addVar(k_kk_Pi2_E, "KPi2E");
   ntNames.addVar(k_kk_Pi2_Px, "KPi2Px");
   ntNames.addVar(k_kk_Pi2_Py, "KPi2Py");
   ntNames.addVar(k_kk_Pi2_Pz, "KPi2Pz");
   ntNames.addVar(k_kk_Pi3_E, "KPi3E");
   ntNames.addVar(k_kk_Pi3_Px, "KPi3Px");
   ntNames.addVar(k_kk_Pi3_Py, "KPi3Py");
   ntNames.addVar(k_kk_Pi3_Pz, "KPi3Pz");
   ntNames.addVar(k_kk_Pi4_E, "KPi4E");
   ntNames.addVar(k_kk_Pi4_Px, "KPi4Px");
   ntNames.addVar(k_kk_Pi4_Py, "KPi4Py");
   ntNames.addVar(k_kk_Pi4_Pz, "KPi4Pz");

   ntNames.addVar(k_kk_Psip_VtxChisq, "KPsipVtx");
   ntNames.addVar(k_kk_Psip_FitChisq, "KPsipFit");

   ntNames.addVar(k_matchE_1, "matchE1");
   ntNames.addVar(k_matchE_2, "matchE2");
   ntNames.addVar(k_matchE_3, "matchE3");
   ntNames.addVar(k_matchE_4, "matchE4");
   ntNames.addVar(k_matchE_5, "matchE5");
   ntNames.addVar(k_matchE_6, "matchE6");

   ntNames.addVar(k_mudepth_1, "mudepth1");
   ntNames.addVar(k_mudepth_2, "mudepth2");
   ntNames.addVar(k_mudepth_3, "mudepth3");
   ntNames.addVar(k_mudepth_4, "mudepth4");
   ntNames.addVar(k_mudepth_5, "mudepth5");
   ntNames.addVar(k_mudepth_6, "mudepth6");


   m_LEGammaNt = iHistoManager.ntuple( 25, "LE Gammas",
				       kNumVars, 50000, ntNames.names());


   h_ksfltsig = iHistoManager.histogram("ksfltsig", 60, -5., 15.);   
   h_mgg = iHistoManager.histogram("mgg", 100, 0., 1.);   

   h_rec_before_nks = iHistoManager.histogram("recbfnks",  100, 3.05, 3.15);   
   h_rec_after_nks = iHistoManager.histogram("recafnks",  100, 3.05, 3.15);   
   h_rec_before_fit = iHistoManager.histogram("recbffit",  100, 3.05, 3.15);   
   h_rec_after_fit = iHistoManager.histogram("recaffit",  100, 3.05, 3.15);   

   h_e9o25_sig = iHistoManager.histogram("e9o25sig",  50, 0.6, 1.1);
   h_e9o25_pi0 = iHistoManager.histogram("e9o25piz",  50, 0.6, 1.1);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
PiPiPhiProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;


   const int kMaxShower = 10, kMaxTrack = 10;
   const int kMaxPi0 = 10;
   const int kMaxEta = 10;


   NavShower::Identifier SID[kMaxShower];
   double E[kMaxShower] = 
           {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10., -10.};  

   double Theta[kMaxShower] =
               {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10., -10.};  

   double Phi[kMaxShower] = 
             {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10., -10.};  

   double Split[kMaxShower] = {-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.,-1.};
 
   double Barrel[kMaxShower] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};

//   double XP[2] = {-10.,-10.}, XPT[2];

   double X925[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};

   double PE[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double PPx[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double PPy[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double PPz[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double kPE[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double kPPx[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double kPPy[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double kPPz[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double pPE[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double pPPx[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double pPPy[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double pPPz[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double Charge[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,
			       -10.};
   double Z0[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double ReChiSq[kMaxTrack] = {1000.,1000.,1000.,1000.,1000.,1000.,1000.,1000.,
				   1000.,1000.};
   double DOCA[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double EID[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double MUID[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};

   double PISIG[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double KSIG[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double PSIG[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double ESIG[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double MUSIG[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double PILL[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double KLL[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double PLL[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double ELL[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double MULL[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double DLPIK[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double DLPIP[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double DLPK[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double DLPIE[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double DLPIMU[kMaxTrack] = {-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,-1000.,
				 -1000.,-1000.,-1000.};
   double MatchE[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};

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
   double EP[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double MuDepth[kMaxTrack] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double KsE[kMaxEta] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double KsPX[kMaxEta] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double KsPY[kMaxEta] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double KsPZ[kMaxEta] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double KsX[kMaxEta] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double KsY[kMaxEta] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double KsZ[kMaxEta] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double KsM[kMaxEta] = {-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.};
   double KsChiSq[kMaxEta] = {-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.};
   double KsFltDst[kMaxEta] = {-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.};
   double KsFltSig[kMaxEta] = {-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.};
   double KsPipTID[kMaxEta] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double KsPimTID[kMaxEta] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};


   float ntVal[kNumVars];
//   double EMax = 0.;
   double DL_pk, DL_ppi, neutralEnergy = 0.;


   /**
   // Let's extract the tree (no usage tag means we get the CLEOG tree)
   FAItem< MCDecayTree > decayTree;
   extract(iFrame.record(Stream::kEvent), decayTree, "Generator" );
   //extract(iFrame.record(Stream::kEvent), decayTree );
   const MCDecayTree& mcDecayTree(*decayTree);

   bool found_f2 = false;
   for(MCDecayTree::const_pIterator it = decayTree->pBegin();
       it != decayTree->pEnd(); it++) {
     if( ( it->properties().PDGId() == 225 ) ) 
       found_f2 = true;
   }

   if(!found_f2)
     return ActionBase::kFailed;
   **/

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
   int numTrack=0, numFit=0;
   double tCharge=0;
   int numPi0=0;
   int numEta=0;
   int numKs=0;

   FAItem<TDKinematicFit> tagpi1, tagpi2;
   FAItem<TDKinematicFit> pi1, pi2;
   FAItem<TDKinematicFit> k1, k2;
   FAItem<TDKinematicFit> p1, p2;
   int good_phi = 0; 
   double best_tag = 1.0;
   vector< FAItem<TDKinematicFit> > good_tracks;
   //vector< FAItem<TDKinematicFit> > fourpi_tracks;
   vector< FAItem<TDKinematicFit> > pion_tracks;
   vector< FAItem<TDKinematicFit> > kaon_tracks;
   //vector< FAItem<TDKinematicFit> > proton_tracks;

   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;
         ++trackItr )
   {
      FAItem<TDKinematicFit> pionFit = trackItr->pionFit();
      FAItem<TRTrackFitQuality> pionQuality = trackItr->pionQuality();
      FAItem<TRHelixFit> pionHelix = trackItr->pionHelix();
      FAItem<TDKinematicFit> kaonFit = trackItr->kaonFit();
      FAItem<TRTrackFitQuality> kaonQuality = trackItr->kaonQuality();
      FAItem<TRHelixFit> kaonHelix = trackItr->kaonHelix();
      FAItem<TDKinematicFit> protonFit = trackItr->protonFit();
      FAItem<TRTrackFitQuality> protonQuality = trackItr->protonQuality();
      FAItem<TRHelixFit> protonHelix = trackItr->protonHelix();
      FAItem<DedxInfo> the_dedx = trackItr->dedxInfo();
      FAItem<NavRich> the_rich = trackItr->richInfo();
      double piLL = -1000;
      double kLL = -1000;
      double pLL = -1000;
      double eLL = -1000;
      double muLL = -1000;
      double DL_pk = -1000;
      double DL_pik = -1000;
      double DL_pip = -1000;
      double DL_pie = -1000;
      double DL_pimu = -1000;
      double pi_sig = -1000;
      double k_sig = -1000;
      double p_sig = -1000;
      double e_sig = -1000;
      double mu_sig = -1000;

      if(trackItr.valid() 
	 && pionFit.valid()
	 && pionHelix.valid() ) {
	 numTrack++;
	 
	 // require 50 MeV < p < 1.8 Gev tracks
	 //if((pionFit->pmag() > 0.05) && (pionFit->pmag() < 1.8)) {

	    // PID
	    if(the_dedx.valid()) {
	       pi_sig = the_dedx->piSigma();
	       p_sig = the_dedx->pSigma();
	       k_sig = the_dedx->kSigma();
	       e_sig = the_dedx->eSigma();
	       mu_sig = the_dedx->muSigma();
	       
	       // if the pion is more like a kaon
	       DL_pik = (pi_sig*pi_sig) - (k_sig*k_sig);

	       // if the proton is more like a kaon
	       DL_pip = (pi_sig*pi_sig) - (p_sig*p_sig);

	       DL_pie = (pi_sig*pi_sig) - (e_sig*e_sig);
	       DL_pimu = (pi_sig*pi_sig) - (mu_sig*mu_sig);

	       DL_pk = (p_sig*p_sig) - (k_sig*k_sig);

	       // if RICH is good, use combined info
	       if(the_rich.valid() 
		  && (pionFit->pmag() > 0.6)
		  && (fabs(protonHelix->cotTheta()) < 1.33) )  //|cos th|<0.8
	       {
		  if( (the_rich->pionHypWasAnalyzed())
		      && (the_rich->pionNumberOfPhotonsInAverage() > 2) ) 
		  {
		     piLL = the_rich->pionLogLikelihood();
		     DL_pik += the_rich->pionLogLikelihood();
		     DL_pip += the_rich->pionLogLikelihood();
		     DL_pie += the_rich->pionLogLikelihood();
		     DL_pimu += the_rich->pionLogLikelihood();
		  }

		  if(the_rich->kaonHypWasAnalyzed()		  
		     && (the_rich->kaonNumberOfPhotonsInAverage() > 2) ) 
		  {
		     kLL = the_rich->kaonLogLikelihood();
		     DL_pik -= the_rich->kaonLogLikelihood();
		     DL_pk -= the_rich->kaonLogLikelihood();
		  }
		  if(the_rich->protonHypWasAnalyzed()		  
		     && (the_rich->protonNumberOfPhotonsInAverage() > 2) ) 
		  {
		     pLL = the_rich->protonLogLikelihood();
		     DL_pip -= the_rich->protonLogLikelihood();
		     DL_pk += the_rich->protonLogLikelihood();
		  }
		  if(the_rich->electronHypWasAnalyzed()		  
		     && (the_rich->electronNumberOfPhotonsInAverage() > 2) ) 
		  {
		     eLL = the_rich->electronLogLikelihood();
		     DL_pie -= the_rich->electronLogLikelihood();
		  }
		  if(the_rich->muonHypWasAnalyzed()		  
		     && (the_rich->muonNumberOfPhotonsInAverage() > 2) ) 
		  {
		     muLL = the_rich->muonLogLikelihood();
		     DL_pimu -= the_rich->muonLogLikelihood();
		  }
		  
	       }
	    }

	    
	    if(numFit < kMaxTrack) {
	       PE[numFit] = pionFit->energy();
	       PPx[numFit] = pionFit->px();
	       PPy[numFit] = pionFit->py();
	       PPz[numFit] = pionFit->pz();
	       if(kaonFit.valid()) {
		  kPE[numFit] = kaonFit->energy();
		  kPPx[numFit] = kaonFit->px();
		  kPPy[numFit] = kaonFit->py();
		  kPPz[numFit] = kaonFit->pz();
	       }
	       if(protonFit.valid()) {
		  pPE[numFit] = protonFit->energy();
		  pPPx[numFit] = protonFit->px();
		  pPPy[numFit] = protonFit->py(); 
		  pPPz[numFit] = protonFit->pz();
	       }
	       Charge[numFit] = pionFit->charge(); 
	       Z0[numFit] = pionHelix->z0() - m_beam_z;  // beam spot corrected
	       DOCA[numFit] = calcDOCA(pionHelix->d0(), pionHelix->phi0());

	       PISIG[numFit] = pi_sig;
	       KSIG[numFit] = k_sig;
	       PSIG[numFit] = p_sig;
	       ESIG[numFit] = e_sig;
	       MUSIG[numFit] = mu_sig;
	       PILL[numFit] = piLL;
	       KLL[numFit] = kLL;
	       PLL[numFit] = pLL;
	       ELL[numFit] = eLL;
	       MULL[numFit] = muLL;
	       DLPIK[numFit] = DL_pik;
	       DLPIP[numFit] = DL_pip;
	       DLPIE[numFit] = DL_pie;
	       DLPIMU[numFit] = DL_pimu;
	       DLPK[numFit] = DL_pk;
 	       EID[numFit] = trackItr->elecId().simpleElecId2();
	       MUID[numFit] = trackItr->muonId().simpleMuonId1();
 	       if(pionQuality->degreesOfFreedom() != 0.)
		  ReChiSq[numFit] = pionQuality->chiSquare() /  
		     pionQuality->degreesOfFreedom(); 

	       EP[numFit] = trackItr->elecId().eOverP();
	       MuDepth[numFit] = trackItr->muonId().depth();
	       if(trackItr->trackShowerMatch().valid())
		  MatchE[numFit] = trackItr->trackShowerMatch()->matchedEnergy();
	    }
	    
	    tCharge += pionFit->charge();
	    numFit++;  // number of good tracks


//            if(trackItr->elecId().eOverP() < 0.8) {
            good_tracks.push_back(pionFit);
            if( isGoodKaon( *trackItr ) )
	        kaon_tracks.push_back(kaonFit);
            else
	        pion_tracks.push_back(pionFit);
//            }


	    // check phi tag
	    const HepLorentzVector &piv1 = pionFit->lorentzMomentum();
	    FATable< NavTrack >::const_iterator trackItr2 = trackItr;
            //double best_tag = 1.0;
            
            while( ++trackItr2 != trackTableEnd ) {
               
               FAItem<TDKinematicFit> pionFit2 = trackItr2->pionFit();
               FAItem<TRTrackFitQuality> pionQuality2 = trackItr2->pionQuality();
               FAItem<TRHelixFit> pionHelix2 = trackItr2->pionHelix();
               
               if( pionFit2.valid()
                   && pionHelix2.valid() ) {
                  if( pionFit2->charge() != -pionFit->charge() ) 
                     continue;
                  
                  const HepLorentzVector &piv2 = trackItr2->pionFit()->lorentzMomentum();
                  
                  HepLorentzVector pipi = piv1 + piv2;
                  
                  double mm = sqrt(fabs( pow(3.686-pipi.e(),2) - pow(pipi.px(),2)
                                         - pow(pipi.py(),2) - pow(pipi.pz(),2) ));

		  //cerr << "tagged Jpsi: " << mm << endl;
                  
                  //if( fabs( mm-1.019461 ) < 0.01 ) {
		  if( fabs( mm-1.019461 ) < 0.05 ) {
                     good_phi = 1;
		     if( fabs( mm-1.019461 ) < fabs( best_tag-1.019461) ) {
			tagpi1 = pionFit;
			tagpi2 = pionFit2;
			best_tag = mm;
		     }
                  }

               }
            }

//	 }
      }
   }

   
   // REQUIRE: ntrack = 2 OR ntrack = 4
   //if( (numFit != 2) && (numFit != 4) )
   //if( (numFit != 2) && (numFit != 4) && (numFit != 6) )
   //if( (numFit != 6) )
   if( (numFit != 4) )
      return ActionBase::kFailed;

//   if(!good_phi)
//      return ActionBase::kFailed;
   
/*
   if( (numFit < 2) )
      return ActionBase::kFailed;
*/
   if( tCharge != 0 )
      return ActionBase::kFailed;

   // Create a table of showers and fill it.
   FATable< NavShower > showerTable;
   FATable< NavShower > showerSATable;   // SplitoffProd approved
   extract( iFrame.record( Stream::kEvent ) , showerTable, "GoodThings" );
   //extract( iFrame.record( Stream::kEvent ) , showerSATable, "SplitoffApproved" );

   FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
   FATable< NavShower >::const_iterator showerEnd = showerTable.end();
   
   // Loop over showers.
   int unmatchedShowers = 0;
   int numPi0G = 0, numPi0GCut = 0;
   double tEnergy = 0.0;
   int hiEnShFnd = 0;

   //NavShower fastest_shower;
   FATable< NavShower >::const_iterator fastest_shower;
   
   vector< const NavShower * > showerList;


   for (FATable< NavShower >::const_iterator showerItr = showerBegin; 
        showerItr != showerEnd ; ++showerItr) {
      //if(showerItr->attributes().e9oe25OK()
//	 && (showerItr->attributes().goodBarrel() ||
     if( ( showerItr->attributes().goodBarrel() 
	   ||  showerItr->attributes().goodEndcap() )
	 && (showerItr->attributes().energy()>0.03)  // min E = 30 MeV
//	 && (showerItr->attributes().energy()>0.06)  // min E = 60 MeV
//	 && (showerItr->attributes().bigEnergy()>0.01)) {
	 && ( showerItr->attributes().x925() > 0.9 ) ) {

	 if(unmatchedShowers == 0)
	    fastest_shower = showerItr;
	 //fastest_shower = *showerItr;
	 
	 int j = unmatchedShowers++;

	 showerList.push_back(&(*showerItr));

	 neutralEnergy += showerItr->attributes().energy();
 
//	 if(showerItr->attributes().energy() >= 1.)
	 if(showerItr->attributes().energy() >= 0.6)
	    hiEnShFnd = 1;

	 if(j<kMaxShower) {
	    SID[j] = showerItr->identifier();

	    E[j] = showerItr->attributes().energy();
	    Theta[j] = showerItr->attributes().theta();
	    Phi[j] = showerItr->attributes().phi();

 	    Barrel[j] = (showerItr->attributes().goodBarrel()>0);
	    Split[j] = 1.;
	    X925[j] = showerItr->attributes().x925();
/*
	    // see if the shower is SplitoffProc approved
	    for (FATable<NavShower>::const_iterator sh2Itr = showerSATable.begin(); 
		 sh2Itr != showerSATable.end(); ++sh2Itr) {
	       if(showerItr->identifier() == sh2Itr->identifier())
		  Split[j] = 1.;
	    }
	    if(Split[j] < 0.)
	       Split[j] = 0.;
*/
	 }
      }
   }


      
   //if( (unmatchedShowers < 1) )
   // return ActionBase::kFailed;


   if( good_tracks.size()==4 ) {

   const double kJpsiMass = 3.096916;
   const double kKsMass = 0.497648;

   //double PiPiJpsi4V[4] = {-10., -10., -10., -10.};
   //double PiPiPsip4V[4] = {-10., -10., -10., -10.};
   //double PiPiShower4V[4] = {-10., -10., -10., -10.};
   //double PiPiK14V[4] = {-10., -10., -10., -10.};
   //double PiPiK24V[4] = {-10., -10., -10., -10.};
   double PiPiPi14V[4] = {-10., -10., -10., -10.};
   double PiPiPi24V[4] = {-10., -10., -10., -10.};
   double PiPiPi34V[4] = {-10., -10., -10., -10.};
   double PiPiPi44V[4] = {-10., -10., -10., -10.};
   double PiPiPi54V[4] = {-10., -10., -10., -10.};
   double PiPiPi64V[4] = {-10., -10., -10., -10.};
   double jpsi_pipi_vtxchisq=1000000., jpsi_pipi_fitchisq=1000000.;
   double psip_pipi_vtxchisq=1000000., psip_pipi_fitchisq=1000000.;
   double KKJpsi4V[4] = {-10., -10., -10., -10.};
   double KKPsip4V[4] = {-10., -10., -10., -10.};
   double KKShower4V[4] = {-10., -10., -10., -10.};
   double KKK14V[4] = {-10., -10., -10., -10.};
   double KKK24V[4] = {-10., -10., -10., -10.};
   double KKPi14V[4] = {-10., -10., -10., -10.};
   double KKPi24V[4] = {-10., -10., -10., -10.};
   double KKPi34V[4] = {-10., -10., -10., -10.};
   double KKPi44V[4] = {-10., -10., -10., -10.};
   double jpsi_kk_vtxchisq=1000000., jpsi_kk_fitchisq=1000000.;
   double psip_kk_vtxchisq=1000000., psip_kk_fitchisq=1000000.;

   

   FitEvt psip( "Psip", FitEvt::k_P4VecCM );
   for(int i=0; i<4; ++i) 
     psip.newTrack(*good_tracks[i]);
   psip.doTheFit();

   if( (psip.chisqVtx()>0) && (psip.chisqFit()>0) ) {
     // save data
     psip_pipi_vtxchisq = psip.chisqVtx();
     psip_pipi_fitchisq = psip.chisqFit();
     /*
     PiPiPsip4V[0] = psip.fitResult().energy();
     PiPiPsip4V[1] = psip.fitResult().px();
     PiPiPsip4V[2] = psip.fitResult().py();
     PiPiPsip4V[3] = psip.fitResult().pz();
     PiPiShower4V[0] = jpsi.kdFitVec()[2]->energy();
     PiPiShower4V[1] = jpsi.kdFitVec()[2]->px();
     PiPiShower4V[2] = jpsi.kdFitVec()[2]->py();
     PiPiShower4V[3] = jpsi.kdFitVec()[2]->pz();
     */

     HepLorentzVector v0pi (psip.kdFitVec()[0]->lorentzMomentum());
     HepLorentzVector v1pi (psip.kdFitVec()[1]->lorentzMomentum());
     HepLorentzVector v2pi (psip.kdFitVec()[2]->lorentzMomentum());
     HepLorentzVector v3pi (psip.kdFitVec()[3]->lorentzMomentum());
//     HepLorentzVector v4pi (psip.kdFitVec()[4]->lorentzMomentum());
//     HepLorentzVector v5pi (psip.kdFitVec()[5]->lorentzMomentum());


     PiPiPi14V[0] = v0pi.e();
     PiPiPi14V[1] = v0pi.px();
     PiPiPi14V[2] = v0pi.py();
     PiPiPi14V[3] = v0pi.pz();
     PiPiPi24V[0] = v1pi.e();
     PiPiPi24V[1] = v1pi.px();
     PiPiPi24V[2] = v1pi.py();
     PiPiPi24V[3] = v1pi.pz();
     PiPiPi34V[0] = v2pi.e();
     PiPiPi34V[1] = v2pi.px();
     PiPiPi34V[2] = v2pi.py();
     PiPiPi34V[3] = v2pi.pz();
     PiPiPi44V[0] = v3pi.e();
     PiPiPi44V[1] = v3pi.px();
     PiPiPi44V[2] = v3pi.py();
     PiPiPi44V[3] = v3pi.pz();
/*
     PiPiPi54V[0] = v4pi.e();
     PiPiPi54V[1] = v4pi.px();
     PiPiPi54V[2] = v4pi.py();
     PiPiPi54V[3] = v4pi.pz();
     PiPiPi64V[0] = v5pi.e();
     PiPiPi64V[1] = v5pi.px();
     PiPiPi64V[2] = v5pi.py();
     PiPiPi64V[3] = v5pi.pz();
*/

     PiPiPi14V[0] = good_tracks[0]->energy();
     PiPiPi14V[1] = good_tracks[0]->px();
     PiPiPi14V[2] = good_tracks[0]->py();
     PiPiPi14V[3] = good_tracks[0]->pz();
     PiPiPi24V[0] = good_tracks[1]->energy();
     PiPiPi24V[1] = good_tracks[1]->px();
     PiPiPi24V[2] = good_tracks[1]->py();
     PiPiPi24V[3] = good_tracks[1]->pz();
     PiPiPi34V[0] = good_tracks[2]->energy();
     PiPiPi34V[1] = good_tracks[2]->px();
     PiPiPi34V[2] = good_tracks[2]->py();
     PiPiPi34V[3] = good_tracks[2]->pz();
     PiPiPi44V[0] = good_tracks[3]->energy();
     PiPiPi44V[1] = good_tracks[3]->px();
     PiPiPi44V[2] = good_tracks[3]->py();
     PiPiPi44V[3] = good_tracks[3]->pz();
/*
     PiPiPi54V[0] = good_tracks[4]->energy();
     PiPiPi54V[1] = good_tracks[4]->px();
     PiPiPi54V[2] = good_tracks[4]->py();
     PiPiPi54V[3] = good_tracks[4]->pz();
     PiPiPi64V[0] = good_tracks[5]->energy();
     PiPiPi64V[1] = good_tracks[5]->px();
     PiPiPi64V[2] = good_tracks[5]->py();
     PiPiPi64V[3] = good_tracks[5]->pz();
*/
   }

   

   // do fit for K+K-
   if( (kaon_tracks.size()==2) && (pion_tracks.size()==2) ) {
     FitEvt psipkk( "Psip", FitEvt::k_P4VecCM );
     for(int i=0; i<2; ++i) 
       psipkk.newTrack(*kaon_tracks[i]);
     for(int i=0; i<2; ++i) 
       psipkk.newTrack(*pion_tracks[i]);
     psipkk.doTheFit();

     if( (psip.chisqVtx()>0) && (psip.chisqFit()>0) ) {
       psip_kk_vtxchisq = psipkk.chisqVtx();
       psip_kk_fitchisq = psipkk.chisqFit();
/*       
       KKJpsi4V[0] = jpsi.fitResult().energy();
       KKJpsi4V[1] = jpsi.fitResult().px();
       KKJpsi4V[2] = jpsi.fitResult().py();
       KKJpsi4V[3] = jpsi.fitResult().pz();
       KKPsip4V[0] = psip.fitResult().energy();
       KKPsip4V[1] = psip.fitResult().px();
       KKPsip4V[2] = psip.fitResult().py();
       KKPsip4V[3] = psip.fitResult().pz();
       KKShower4V[0] = jpsi.kdFitVec()[2]->energy();
       KKShower4V[1] = jpsi.kdFitVec()[2]->px();
       KKShower4V[2] = jpsi.kdFitVec()[2]->py();
       KKShower4V[3] = jpsi.kdFitVec()[2]->pz();
*/       
       KKK14V[0] = kaon_tracks[0]->energy();
       KKK14V[1] = kaon_tracks[0]->px();
       KKK14V[2] = kaon_tracks[0]->py();
       KKK14V[3] = kaon_tracks[0]->pz();
       KKK24V[0] = kaon_tracks[1]->energy();
       KKK24V[1] = kaon_tracks[1]->px();
       KKK24V[2] = kaon_tracks[1]->py();
       KKK24V[3] = kaon_tracks[1]->pz();
       KKPi14V[0] = pion_tracks[0]->energy();
       KKPi14V[1] = pion_tracks[0]->px();
       KKPi14V[2] = pion_tracks[0]->py();
       KKPi14V[3] = pion_tracks[0]->pz();
       KKPi24V[0] = pion_tracks[1]->energy();
       KKPi24V[1] = pion_tracks[1]->px();
       KKPi24V[2] = pion_tracks[1]->py();
       KKPi24V[3] = pion_tracks[1]->pz();
/*
       KKPi34V[0] = pion_tracks[2]->energy();
       KKPi34V[1] = pion_tracks[2]->px();
       KKPi34V[2] = pion_tracks[2]->py();
       KKPi34V[3] = pion_tracks[2]->pz();
       KKPi44V[0] = pion_tracks[3]->energy();
       KKPi44V[1] = pion_tracks[3]->px();
       KKPi44V[2] = pion_tracks[3]->py();
       KKPi44V[3] = pion_tracks[3]->pz();
*/       
     }
   }



   // Fill ntuple
   ntVal[k_NShower] = unmatchedShowers;
   ntVal[k_NTrack] = numFit;
   ntVal[k_TCharge] = tCharge;


   // Photon Quantities
   ntVal[k_Energy_1] = E[0];
   ntVal[k_Barrel_1] = Barrel[0];
   ntVal[k_Theta_1] = Theta[0];
   ntVal[k_Phi_1] = Phi[0];
   ntVal[k_Split_1] = Split[0];
   ntVal[k_X925_1] = X925[0];
   ntVal[k_Energy_2] = E[1];
   ntVal[k_Barrel_2] = Barrel[1];
   ntVal[k_Theta_2] = Theta[1];
   ntVal[k_Phi_2] = Phi[1];
   ntVal[k_Split_2] = Split[1];
   ntVal[k_X925_2] = X925[1];
   ntVal[k_Energy_3] = E[2];
   ntVal[k_Barrel_3] = Barrel[2];
   ntVal[k_Theta_3] = Theta[2];
   ntVal[k_Phi_3] = Phi[2];
   ntVal[k_Split_3] = Split[2];
   ntVal[k_X925_3] = X925[2];
   ntVal[k_Energy_4] = E[3];
   ntVal[k_Barrel_4] = Barrel[3];
   ntVal[k_Theta_4] = Theta[3];
   ntVal[k_Phi_4] = Phi[3];
   ntVal[k_Split_4] = Split[3];
   ntVal[k_X925_4] = X925[3];
   ntVal[k_Energy_5] = E[4];
   ntVal[k_Barrel_5] = Barrel[4];
   ntVal[k_Theta_5] = Theta[4];
   ntVal[k_Phi_5] = Phi[4];
   ntVal[k_Split_5] = Split[4];
   ntVal[k_X925_6] = X925[4];
   ntVal[k_Energy_6] = E[5];
   ntVal[k_Barrel_6] = Barrel[5];
   ntVal[k_Theta_6] = Theta[5];
   ntVal[k_Phi_6] = Phi[5];
   ntVal[k_Split_6] = Split[5];
   ntVal[k_X925_6] = X925[5];

   // track data
   ntVal[k_TE_1] = PE[0];
   ntVal[k_Px_1] = PPx[0];
   ntVal[k_Py_1] = PPy[0];
   ntVal[k_Pz_1] = PPz[0];
   ntVal[k_kTE_1] = kPE[0];
   ntVal[k_kPx_1] = kPPx[0];
   ntVal[k_kPy_1] = kPPy[0];
   ntVal[k_kPz_1] = kPPz[0];
   ntVal[k_pTE_1] = pPE[0];
   ntVal[k_pPx_1] = pPPx[0];
   ntVal[k_pPy_1] = pPPy[0];
   ntVal[k_pPz_1] = pPPz[0];
   ntVal[k_Chg_1] = Charge[0];
   ntVal[k_DOCA_1] = DOCA[0];
   ntVal[k_Z0_1] = Z0[0];
   ntVal[k_ReChiSq_1] = ReChiSq[0];
   ntVal[k_EID_1] = EID[0]; 
   ntVal[k_MuID_1] = MUID[0];
   ntVal[k_LLpi_1] = PILL[0];
   ntVal[k_LLk_1] = KLL[0];
   ntVal[k_LLp_1] = PLL[0];
   ntVal[k_LLe_1] = ELL[0];
   ntVal[k_LLmu_1] = MULL[0];
   ntVal[k_SigPi_1] = PISIG[0];
   ntVal[k_SigK_1] = KSIG[0];
   ntVal[k_SigP_1] = PSIG[0];
   ntVal[k_SigE_1] = ESIG[0];
   ntVal[k_SigMu_1] = MUSIG[0];
   ntVal[k_DL_pik_1] = DLPIK[0];
   ntVal[k_DL_pip_1] = DLPIP[0];
   ntVal[k_DL_pie_1] = DLPIE[0];
   ntVal[k_DL_pimu_1] = DLPIMU[0];
   ntVal[k_DL_pk_1] = DLPK[0];
   ntVal[k_TE_2] = PE[1];
   ntVal[k_Px_2] = PPx[1];
   ntVal[k_Py_2] = PPy[1];
   ntVal[k_Pz_2] = PPz[1];
   ntVal[k_kTE_2] = kPE[1];
   ntVal[k_kPx_2] = kPPx[1];
   ntVal[k_kPy_2] = kPPy[1];
   ntVal[k_kPz_2] = kPPz[1];
   ntVal[k_pTE_2] = pPE[1];
   ntVal[k_pPx_2] = pPPx[1];
   ntVal[k_pPy_2] = pPPy[1];
   ntVal[k_pPz_2] = pPPz[1];
   ntVal[k_Chg_2] = Charge[1];
   ntVal[k_DOCA_2] = DOCA[1];
   ntVal[k_Z0_2] = Z0[1];
   ntVal[k_ReChiSq_2] = ReChiSq[1];
   ntVal[k_EID_2] = EID[1]; 
   ntVal[k_MuID_2] = MUID[1];
   ntVal[k_LLpi_2] = PILL[1];
   ntVal[k_LLk_2] = KLL[1];
   ntVal[k_LLp_2] = PLL[1];
   ntVal[k_LLe_2] = ELL[1];
   ntVal[k_LLmu_2] = MULL[1];
   ntVal[k_SigPi_2] = PISIG[1];
   ntVal[k_SigK_2] = KSIG[1];
   ntVal[k_SigP_2] = PSIG[1];
   ntVal[k_SigE_2] = ESIG[1];
   ntVal[k_SigMu_2] = MUSIG[1];
   ntVal[k_DL_pip_2] = DLPIP[1];
   ntVal[k_DL_pik_2] = DLPIK[1];
   ntVal[k_DL_pie_2] = DLPIE[1];
   ntVal[k_DL_pimu_2] = DLPIMU[1];
   ntVal[k_DL_pk_2] = DLPK[1];
   ntVal[k_TE_3] = PE[2];
   ntVal[k_Px_3] = PPx[2];
   ntVal[k_Py_3] = PPy[2];
   ntVal[k_Pz_3] = PPz[2];
   ntVal[k_kTE_3] = kPE[2];
   ntVal[k_kPx_3] = kPPx[2];
   ntVal[k_kPy_3] = kPPy[2];
   ntVal[k_kPz_3] = kPPz[2];
   ntVal[k_pTE_3] = pPE[2];
   ntVal[k_pPx_3] = pPPx[2];
   ntVal[k_pPy_3] = pPPy[2];
   ntVal[k_pPz_3] = pPPz[2];
   ntVal[k_Chg_3] = Charge[2];
   ntVal[k_DOCA_3] = DOCA[2];
   ntVal[k_Z0_3] = Z0[2];
   ntVal[k_ReChiSq_3] = ReChiSq[2];
   ntVal[k_EID_3] = EID[2]; 
   ntVal[k_MuID_3] = MUID[2];
   ntVal[k_LLpi_3] = PILL[2];
   ntVal[k_LLk_3] = KLL[2];
   ntVal[k_LLp_3] = PLL[2];
   ntVal[k_LLe_3] = ELL[2];
   ntVal[k_LLmu_3] = MULL[2];
   ntVal[k_SigPi_3] = PISIG[2];
   ntVal[k_SigK_3] = KSIG[2];
   ntVal[k_SigP_3] = PSIG[2];
   ntVal[k_SigE_3] = ESIG[2];
   ntVal[k_SigMu_3] = MUSIG[2];
   ntVal[k_DL_pip_3] = DLPIP[2];
   ntVal[k_DL_pik_3] = DLPIK[2];
   ntVal[k_DL_pie_3] = DLPIE[2];
   ntVal[k_DL_pimu_3] = DLPIMU[2];
   ntVal[k_DL_pk_3] = DLPK[2];
   ntVal[k_TE_4] = PE[3];
   ntVal[k_Px_4] = PPx[3];
   ntVal[k_Py_4] = PPy[3];
   ntVal[k_Pz_4] = PPz[3];
   ntVal[k_kTE_4] = kPE[3];
   ntVal[k_kPx_4] = kPPx[3];
   ntVal[k_kPy_4] = kPPy[3];
   ntVal[k_kPz_4] = kPPz[3];
   ntVal[k_pTE_4] = pPE[3];
   ntVal[k_pPx_4] = pPPx[3];
   ntVal[k_pPy_4] = pPPy[3];
   ntVal[k_pPz_4] = pPPz[3];
   ntVal[k_Chg_4] = Charge[3];
   ntVal[k_DOCA_4] = DOCA[3];
   ntVal[k_Z0_4] = Z0[3];
   ntVal[k_ReChiSq_4] = ReChiSq[3];
   ntVal[k_EID_4] = EID[3]; 
   ntVal[k_MuID_4] = MUID[3];
   ntVal[k_LLpi_4] = PILL[3];
   ntVal[k_LLk_4] = KLL[3];
   ntVal[k_LLp_4] = PLL[3];
   ntVal[k_LLe_4] = ELL[3];
   ntVal[k_LLmu_4] = MULL[3];
   ntVal[k_SigPi_4] = PISIG[3];
   ntVal[k_SigK_4] = KSIG[3];
   ntVal[k_SigP_4] = PSIG[3];
   ntVal[k_SigE_4] = ESIG[3];
   ntVal[k_SigMu_4] = MUSIG[3];
   ntVal[k_DL_pik_4] = DLPIK[3];
   ntVal[k_DL_pip_4] = DLPIP[3];
   ntVal[k_DL_pie_4] = DLPIE[3];
   ntVal[k_DL_pimu_4] = DLPIMU[3];
   ntVal[k_DL_pk_4] = DLPK[3];
   ntVal[k_TE_5] = PE[4];
   ntVal[k_Px_5] = PPx[4];
   ntVal[k_Py_5] = PPy[4];
   ntVal[k_Pz_5] = PPz[4];
   ntVal[k_kTE_5] = kPE[4];
   ntVal[k_kPx_5] = kPPx[4];
   ntVal[k_kPy_5] = kPPy[4];
   ntVal[k_kPz_5] = kPPz[4];
   ntVal[k_pTE_5] = pPE[4];
   ntVal[k_pPx_5] = pPPx[4];
   ntVal[k_pPy_5] = pPPy[4];
   ntVal[k_pPz_5] = pPPz[4];
   ntVal[k_Chg_5] = Charge[4];
   ntVal[k_DOCA_5] = DOCA[4];
   ntVal[k_Z0_5] = Z0[4];
   ntVal[k_ReChiSq_5] = ReChiSq[4];
   ntVal[k_EID_5] = EID[4]; 
   ntVal[k_MuID_5] = MUID[4];
   ntVal[k_LLpi_5] = PILL[4];
   ntVal[k_LLk_5] = KLL[4];
   ntVal[k_LLp_5] = PLL[4];
   ntVal[k_LLe_5] = ELL[4];
   ntVal[k_LLmu_5] = MULL[4];
   ntVal[k_SigPi_5] = PISIG[4];
   ntVal[k_SigK_5] = KSIG[4];
   ntVal[k_SigP_5] = PSIG[4];
   ntVal[k_SigE_5] = ESIG[4];
   ntVal[k_SigMu_5] = MUSIG[4];
   ntVal[k_DL_pik_5] = DLPIK[4];
   ntVal[k_DL_pip_5] = DLPIP[4];
   ntVal[k_DL_pie_5] = DLPIE[4];
   ntVal[k_DL_pimu_5] = DLPIMU[4];
   ntVal[k_DL_pk_5] = DLPK[4];
   ntVal[k_TE_6] = PE[5];
   ntVal[k_Px_6] = PPx[5];
   ntVal[k_Py_6] = PPy[5];
   ntVal[k_Pz_6] = PPz[5];
   ntVal[k_kTE_6] = kPE[5];
   ntVal[k_kPx_6] = kPPx[5];
   ntVal[k_kPy_6] = kPPy[5];
   ntVal[k_kPz_6] = kPPz[5];
   ntVal[k_pTE_6] = pPE[5];
   ntVal[k_pPx_6] = pPPx[5];
   ntVal[k_pPy_6] = pPPy[5];
   ntVal[k_pPz_6] = pPPz[5];
   ntVal[k_Chg_6] = Charge[5];
   ntVal[k_DOCA_6] = DOCA[5];
   ntVal[k_Z0_6] = Z0[5];
   ntVal[k_ReChiSq_6] = ReChiSq[5];
   ntVal[k_EID_6] = EID[5]; 
   ntVal[k_LLpi_6] = PILL[5];
   ntVal[k_LLk_6] = KLL[5];
   ntVal[k_LLp_6] = PLL[5];
   ntVal[k_LLe_6] = ELL[5];
   ntVal[k_LLmu_6] = MULL[5];
   ntVal[k_SigPi_6] = PISIG[5];
   ntVal[k_SigK_6] = KSIG[5];
   ntVal[k_SigP_6] = PSIG[5];
   ntVal[k_SigE_6] = ESIG[5];
   ntVal[k_SigMu_6] = MUSIG[5];
   ntVal[k_DL_pik_6] = DLPIK[5];
   ntVal[k_DL_pip_6] = DLPIP[5];
   ntVal[k_DL_pie_6] = DLPIE[5];
   ntVal[k_DL_pimu_6] = DLPIMU[5];
   ntVal[k_DL_pk_6] = DLPK[5];


   ntVal[k_EP_1] = EP[0];
   ntVal[k_EP_2] = EP[1];
   ntVal[k_EP_3] = EP[2];
   ntVal[k_EP_4] = EP[3];
   ntVal[k_EP_5] = EP[4];
   ntVal[k_EP_6] = EP[5];



   ntVal[k_pipi_Pi1_E] = PiPiPi14V[0];
   ntVal[k_pipi_Pi1_Px] = PiPiPi14V[1];
   ntVal[k_pipi_Pi1_Py] = PiPiPi14V[2];
   ntVal[k_pipi_Pi1_Pz] = PiPiPi14V[3];
   ntVal[k_pipi_Pi2_E] = PiPiPi24V[0];
   ntVal[k_pipi_Pi2_Px] = PiPiPi24V[1];
   ntVal[k_pipi_Pi2_Py] = PiPiPi24V[2];
   ntVal[k_pipi_Pi2_Pz] = PiPiPi24V[3];
   ntVal[k_pipi_Pi3_E] = PiPiPi34V[0];
   ntVal[k_pipi_Pi3_Px] = PiPiPi34V[1];
   ntVal[k_pipi_Pi3_Py] = PiPiPi34V[2];
   ntVal[k_pipi_Pi3_Pz] = PiPiPi34V[3];
   ntVal[k_pipi_Pi4_E] = PiPiPi44V[0];
   ntVal[k_pipi_Pi4_Px] = PiPiPi44V[1];
   ntVal[k_pipi_Pi4_Py] = PiPiPi44V[2];
   ntVal[k_pipi_Pi4_Pz] = PiPiPi44V[3];
   ntVal[k_pipi_Pi5_E] = PiPiPi54V[0];
   ntVal[k_pipi_Pi5_Px] = PiPiPi54V[1];
   ntVal[k_pipi_Pi5_Py] = PiPiPi54V[2];
   ntVal[k_pipi_Pi5_Pz] = PiPiPi54V[3];
   ntVal[k_pipi_Pi6_E] = PiPiPi64V[0];
   ntVal[k_pipi_Pi6_Px] = PiPiPi64V[1];
   ntVal[k_pipi_Pi6_Py] = PiPiPi64V[2];
   ntVal[k_pipi_Pi6_Pz] = PiPiPi64V[3];
/*   
   ntVal[k_pipi_Jpsi_E] = PiPiJpsi4V[0];
   ntVal[k_pipi_Jpsi_Px] = PiPiJpsi4V[1];
   ntVal[k_pipi_Jpsi_Py] = PiPiJpsi4V[2];
   ntVal[k_pipi_Jpsi_Pz] = PiPiJpsi4V[3];
   ntVal[k_pipi_Psip_E] = PiPiPsip4V[0];
   ntVal[k_pipi_Psip_Px] = PiPiPsip4V[1];
   ntVal[k_pipi_Psip_Py] = PiPiPsip4V[2];
   ntVal[k_pipi_Psip_Pz] = PiPiPsip4V[3];
   ntVal[k_pipi_K1_E] = PiPiK14V[0];
   ntVal[k_pipi_K1_Px] = PiPiK14V[1];
   ntVal[k_pipi_K1_Py] = PiPiK14V[2];
   ntVal[k_pipi_K1_Pz] = PiPiK14V[3];
   ntVal[k_pipi_K2_E] = PiPiK24V[0];
   ntVal[k_pipi_K2_Px] = PiPiK24V[1];
   ntVal[k_pipi_K2_Py] = PiPiK24V[2];
   ntVal[k_pipi_K2_Pz] = PiPiK24V[3];
   ntVal[k_pipi_Shower_E] = PiPiShower4V[0];
   ntVal[k_pipi_Shower_Px] = PiPiShower4V[1];
   ntVal[k_pipi_Shower_Py] = PiPiShower4V[2];
   ntVal[k_pipi_Shower_Pz] = PiPiShower4V[3];
   ntVal[k_pipi_Jpsi_VtxChisq] = jpsi_pipi_vtxchisq;
   ntVal[k_pipi_Jpsi_FitChisq] = jpsi_pipi_fitchisq;
*/ 
   ntVal[k_pipi_Psip_VtxChisq] = psip_pipi_vtxchisq;
   ntVal[k_pipi_Psip_FitChisq] = psip_pipi_fitchisq;

   ntVal[k_kk_K1_E] = KKK14V[0];
   ntVal[k_kk_K1_Px] = KKK14V[1];
   ntVal[k_kk_K1_Py] = KKK14V[2];
   ntVal[k_kk_K1_Pz] = KKK14V[3];
   ntVal[k_kk_K2_E] = KKK24V[0];
   ntVal[k_kk_K2_Px] = KKK24V[1];
   ntVal[k_kk_K2_Py] = KKK24V[2];
   ntVal[k_kk_K2_Pz] = KKK24V[3];
   ntVal[k_kk_Pi1_E] = KKPi14V[0];
   ntVal[k_kk_Pi1_Px] = KKPi14V[1];
   ntVal[k_kk_Pi1_Py] = KKPi14V[2];
   ntVal[k_kk_Pi1_Pz] = KKPi14V[3];
   ntVal[k_kk_Pi2_E] = KKPi24V[0];
   ntVal[k_kk_Pi2_Px] = KKPi24V[1];
   ntVal[k_kk_Pi2_Py] = KKPi24V[2];
   ntVal[k_kk_Pi2_Pz] = KKPi24V[3];
   ntVal[k_kk_Pi3_E] = KKPi34V[0];
   ntVal[k_kk_Pi3_Px] = KKPi34V[1];
   ntVal[k_kk_Pi3_Py] = KKPi34V[2];
   ntVal[k_kk_Pi3_Pz] = KKPi34V[3];
   ntVal[k_kk_Pi4_E] = KKPi44V[0];
   ntVal[k_kk_Pi4_Px] = KKPi44V[1];
   ntVal[k_kk_Pi4_Py] = KKPi44V[2];
   ntVal[k_kk_Pi4_Pz] = KKPi44V[3];
/*
   ntVal[k_kk_Jpsi_E] = KKJpsi4V[0];
   ntVal[k_kk_Jpsi_Px] = KKJpsi4V[1];
   ntVal[k_kk_Jpsi_Py] = KKJpsi4V[2];
   ntVal[k_kk_Jpsi_Pz] = KKJpsi4V[3];
   ntVal[k_kk_Psip_E] = KKPsip4V[0];
   ntVal[k_kk_Psip_Px] = KKPsip4V[1];
   ntVal[k_kk_Psip_Py] = KKPsip4V[2];
   ntVal[k_kk_Psip_Pz] = KKPsip4V[3];
   ntVal[k_kk_Shower_E] = KKShower4V[0];
   ntVal[k_kk_Shower_Px] = KKShower4V[1];
   ntVal[k_kk_Shower_Py] = KKShower4V[2];
   ntVal[k_kk_Shower_Pz] = KKShower4V[3];
   ntVal[k_kk_Jpsi_VtxChisq] = jpsi_kk_vtxchisq;
   ntVal[k_kk_Jpsi_FitChisq] = jpsi_kk_fitchisq;
*/ 
   ntVal[k_kk_Psip_VtxChisq] = psip_kk_vtxchisq;
   ntVal[k_kk_Psip_FitChisq] = psip_kk_fitchisq;

   ntVal[k_matchE_1] = MatchE[0];
   ntVal[k_matchE_2] = MatchE[1];
   ntVal[k_matchE_3] = MatchE[2];
   ntVal[k_matchE_4] = MatchE[3];
   ntVal[k_matchE_5] = MatchE[4];
   ntVal[k_matchE_6] = MatchE[5];

   ntVal[k_mudepth_1] = MuDepth[0];
   ntVal[k_mudepth_2] = MuDepth[1];
   ntVal[k_mudepth_3] = MuDepth[2];
   ntVal[k_mudepth_4] = MuDepth[3];
   ntVal[k_mudepth_5] = MuDepth[4];
   ntVal[k_mudepth_6] = MuDepth[5];


   m_LEGammaNt->fill(ntVal);
   
   }

   //cerr << "ntuple: " << ntVal[k_Jpsi_VtxChisq] << " " << ntVal[k_Jpsi_FitChisq] << endl;
       
   return ActionBase::kPassed;
}


ActionBase::ActionResult
PiPiPhiProc::beginRun( Frame& iFrame )       // anal2 equiv.
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
PiPiPhiProc::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/


// return 1 if they are they same kinematical object
int PiPiPhiProc::CompareKins( FAItem<KTKinematicData>  &k1, 
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
int PiPiPhiProc::CompareKins( FAItem<TDKinematicFit>  &k1, 
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
int PiPiPhiProc::CompareKins( FAItem<TDKinematicFit>  k1, 
			       FAItem<TDKinematicFit>  k2) const
{
   if( (k1->position()==k2->position()) 
       && (k1->momentum()==k2->momentum()) )
    return 1;
  else 
    return 0;

}

double PiPiPhiProc::calcDOCA( double iD,
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
