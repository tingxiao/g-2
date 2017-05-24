// -*- C++ -*-
#if !defined(PPGPSIPPROC_PPGPSIPPROC_H)
#define PPGPSIPPROC_PPGPSIPPROC_H
//
// Package:     <FivePiProc>
// Module:      FivePiProc
//
/**\class FivePiProc FivePiProc.h FivePiProc/FivePiProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Sean Dobbs
// Created:     Wed Jul  7 17:32:00 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
//

// system include files

// user include files
#include "Processor/Processor.h"
#include "HistogramInterface/HistogramPackage.h"
#include "FrameAccess/FATable.h"
#include "Navigation/NavTrack.h"
#include "Navigation/NavShower.h"

// forward declarations

class FivePiProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      FivePiProc( void );                      // anal1 
      virtual ~FivePiProc();                   // anal5 

      // ------------ member functions ---------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // methods for binding to streams (anal2-4 etc.)
      virtual ActionBase::ActionResult event( Frame& iFrame );
      virtual ActionBase::ActionResult beginRun( Frame& iFrame);
      //virtual ActionBase::ActionResult endRun( Frame& iFrame);

      // ------------ const member functions ---------------------

      // ------------ static member functions --------------------

   protected:
      // ------------ protected member functions -----------------
      double cangTrackShower(const NavShower &aShower,
			     const NavTrack &aTrack  );
      double calcDOCA( double iD,  double iPhi );

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      FivePiProc( const FivePiProc& );

      // ------------ assignment operator(s) ---------------------
      const FivePiProc& operator=( const FivePiProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (FivePiProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
	double m_beam_x;  // beamspot location
	double m_beam_y;
	double m_beam_z;
	
	HINtuple *m_LEGammaNt;

	HIHist1D *h_mpipi;
	HIHist1D *h_mpipi4;
	HIHist1D *h_mpipirec;
	HIHist1D *h_pion_mudepth;
	

	HIHist1D *h_pion_costh;
	HIHist1D *h_kaon_costh;
	HIHist1D *h_proton_costh;

	HIHist1D *h_pion_phi;
	HIHist2D *h_pion_p_costh;
	HIHist2D *h_pion_p_phi;
	HIHist2D *h_pion_costh_phi;

	HIHist1D *h_pion_p;
	HIHist1D *h_kaon_p;
	HIHist1D *h_proton_p;
	HIHist1D *h_pion_p_endcap;
	HIHist1D *h_kaon_p_endcap;
	HIHist1D *h_proton_p_endcap;

	HIHist1D *h_pion_mcpion_p;
	HIHist1D *h_pion_mckaon_p;
	HIHist1D *h_pion_mcproton_p;
	HIHist1D *h_pion_mcmuon_p;
	HIHist1D *h_kaon_mcpion_p;
	HIHist1D *h_kaon_mckaon_p;
	HIHist1D *h_kaon_mcproton_p;
	HIHist1D *h_proton_mcpion_p;
	HIHist1D *h_proton_mckaon_p;
	HIHist1D *h_proton_mcproton_p;

        HIHist1D *h_pion_eop;
        HIHist1D *h_pip_eop1;
        HIHist1D *h_pip_eop2;
        HIHist1D *h_pip_eop3;
        HIHist1D *h_pip_eop4;
        HIHist1D *h_pip_eop5;
        HIHist1D *h_pip_eop6;
        HIHist1D *h_pip_eop7;
        HIHist1D *h_pip_eop8;
        HIHist1D *h_pip_eop9;
        HIHist1D *h_pip_eop10;
        HIHist1D *h_pip_eop11;
        HIHist1D *h_pip_eop12;
        HIHist1D *h_pip_eop13;
        HIHist1D *h_pip_eop14;
        HIHist1D *h_pip_eop15;
        HIHist1D *h_pip_eop16;
        HIHist1D *h_pip_eop17;
        HIHist1D *h_pip_eop18;
        HIHist1D *h_pip_eop19;
        HIHist1D *h_pip_eop20;
        HIHist1D *h_pim_eop1;
        HIHist1D *h_pim_eop2;
        HIHist1D *h_pim_eop3;
        HIHist1D *h_pim_eop4;
        HIHist1D *h_pim_eop5;
        HIHist1D *h_pim_eop6;
        HIHist1D *h_pim_eop7;
        HIHist1D *h_pim_eop8;
        HIHist1D *h_pim_eop9;
        HIHist1D *h_pim_eop10;
        HIHist1D *h_pim_eop11;
        HIHist1D *h_pim_eop12;
        HIHist1D *h_pim_eop13;
        HIHist1D *h_pim_eop14;
        HIHist1D *h_pim_eop15;
        HIHist1D *h_pim_eop16;
        HIHist1D *h_pim_eop17;
        HIHist1D *h_pim_eop18;
        HIHist1D *h_pim_eop19;
       	HIHist1D *h_pim_eop20;

        HIHist2D *h_pip_matche_p;
        HIHist2D *h_pim_matche_p;

	HIHist1D *h_pion_matche;
	HIHist1D *h_pip_matche1;
	HIHist1D *h_pip_matche2;
	HIHist1D *h_pip_matche3;
	HIHist1D *h_pip_matche4;
	HIHist1D *h_pip_matche5;
	HIHist1D *h_pip_matche6;
	HIHist1D *h_pip_matche7;
	HIHist1D *h_pip_matche8;
	HIHist1D *h_pip_matche9;
	HIHist1D *h_pip_matche10;
	HIHist1D *h_pip_matche11;
	HIHist1D *h_pip_matche12;
	HIHist1D *h_pip_matche13;
	HIHist1D *h_pip_matche14;
	HIHist1D *h_pip_matche15;
	HIHist1D *h_pip_matche16;
	HIHist1D *h_pip_matche17;
	HIHist1D *h_pip_matche18;
	HIHist1D *h_pip_matche19;
	HIHist1D *h_pip_matche20;
	HIHist1D *h_pim_matche1;
	HIHist1D *h_pim_matche2;
	HIHist1D *h_pim_matche3;
	HIHist1D *h_pim_matche4;
	HIHist1D *h_pim_matche5;
	HIHist1D *h_pim_matche6;
	HIHist1D *h_pim_matche7;
	HIHist1D *h_pim_matche8;
	HIHist1D *h_pim_matche9;
	HIHist1D *h_pim_matche10;
	HIHist1D *h_pim_matche11;
	HIHist1D *h_pim_matche12;
	HIHist1D *h_pim_matche13;
	HIHist1D *h_pim_matche14;
	HIHist1D *h_pim_matche15;
	HIHist1D *h_pim_matche16;
	HIHist1D *h_pim_matche17;
	HIHist1D *h_pim_matche18;
	HIHist1D *h_pim_matche19;
	HIHist1D *h_pim_matche20;

        HIHist1D *h_pion_matche_eop;
        HIHist1D *h_pip_matche1_eop;
        HIHist1D *h_pip_matche2_eop;
        HIHist1D *h_pip_matche3_eop;
        HIHist1D *h_pip_matche4_eop;
        HIHist1D *h_pip_matche5_eop;
        HIHist1D *h_pip_matche6_eop;
        HIHist1D *h_pip_matche7_eop;
        HIHist1D *h_pip_matche8_eop;
        HIHist1D *h_pip_matche9_eop;
        HIHist1D *h_pip_matche10_eop;
        HIHist1D *h_pip_matche11_eop;
        HIHist1D *h_pip_matche12_eop;
        HIHist1D *h_pip_matche13_eop;
        HIHist1D *h_pip_matche14_eop;
        HIHist1D *h_pip_matche15_eop;
        HIHist1D *h_pip_matche16_eop;
        HIHist1D *h_pip_matche17_eop;
        HIHist1D *h_pip_matche18_eop;
        HIHist1D *h_pip_matche19_eop;
        HIHist1D *h_pip_matche20_eop;
        HIHist1D *h_pim_matche1_eop;
        HIHist1D *h_pim_matche2_eop;
        HIHist1D *h_pim_matche3_eop;
       	HIHist1D *h_pim_matche4_eop;
        HIHist1D *h_pim_matche5_eop;
        HIHist1D *h_pim_matche6_eop;
        HIHist1D *h_pim_matche7_eop;
        HIHist1D *h_pim_matche8_eop;
        HIHist1D *h_pim_matche9_eop;
        HIHist1D *h_pim_matche10_eop;
        HIHist1D *h_pim_matche11_eop;
        HIHist1D *h_pim_matche12_eop;
        HIHist1D *h_pim_matche13_eop;
        HIHist1D *h_pim_matche14_eop;
        HIHist1D *h_pim_matche15_eop;
        HIHist1D *h_pim_matche16_eop;
        HIHist1D *h_pim_matche17_eop;
        HIHist1D *h_pim_matche18_eop;
        HIHist1D *h_pim_matche19_eop;
        HIHist1D *h_pim_matche20_eop;

	HIHist1D *h_kaon_matche;
	HIHist1D *h_kp_matche1;
	HIHist1D *h_kp_matche2;
	HIHist1D *h_kp_matche3;
	HIHist1D *h_kp_matche4;
	HIHist1D *h_kp_matche5;
	HIHist1D *h_kp_matche6;
	HIHist1D *h_kp_matche7;
	HIHist1D *h_kp_matche8;
	HIHist1D *h_kp_matche9;
	HIHist1D *h_kp_matche10;
	HIHist1D *h_kp_matche11;
	HIHist1D *h_kp_matche12;
	HIHist1D *h_kp_matche13;
	HIHist1D *h_kp_matche14;
	HIHist1D *h_kp_matche15;
	HIHist1D *h_kp_matche16;
	HIHist1D *h_kp_matche17;
	HIHist1D *h_kp_matche18;
	HIHist1D *h_kp_matche19;
	HIHist1D *h_kp_matche20;
	HIHist1D *h_km_matche1;
	HIHist1D *h_km_matche2;
	HIHist1D *h_km_matche3;
	HIHist1D *h_km_matche4;
	HIHist1D *h_km_matche5;
	HIHist1D *h_km_matche6;
	HIHist1D *h_km_matche7;
	HIHist1D *h_km_matche8;
	HIHist1D *h_km_matche9;
	HIHist1D *h_km_matche10;
	HIHist1D *h_km_matche11;
	HIHist1D *h_km_matche12;
	HIHist1D *h_km_matche13;
	HIHist1D *h_km_matche14;
	HIHist1D *h_km_matche15;
	HIHist1D *h_km_matche16;
	HIHist1D *h_km_matche17;
	HIHist1D *h_km_matche18;
	HIHist1D *h_km_matche19;
	HIHist1D *h_km_matche20;

	HIHist1D *h_proton_matche;
	HIHist1D *h_pp_matche1;
	HIHist1D *h_pp_matche2;
	HIHist1D *h_pp_matche3;
	HIHist1D *h_pp_matche4;
	HIHist1D *h_pp_matche5;
	HIHist1D *h_pp_matche6;
	HIHist1D *h_pp_matche7;
	HIHist1D *h_pp_matche8;
	HIHist1D *h_pp_matche9;
	HIHist1D *h_pp_matche10;
	HIHist1D *h_pp_matche11;
	HIHist1D *h_pp_matche12;
	HIHist1D *h_pp_matche13;
	HIHist1D *h_pp_matche14;
	HIHist1D *h_pp_matche15;
	HIHist1D *h_pp_matche16;
	HIHist1D *h_pp_matche17;
	HIHist1D *h_pp_matche18;
	HIHist1D *h_pp_matche19;
	HIHist1D *h_pp_matche20;
	HIHist1D *h_pm_matche1;
	HIHist1D *h_pm_matche2;
	HIHist1D *h_pm_matche3;
	HIHist1D *h_pm_matche4;
	HIHist1D *h_pm_matche5;
	HIHist1D *h_pm_matche6;
	HIHist1D *h_pm_matche7;
	HIHist1D *h_pm_matche8;
	HIHist1D *h_pm_matche9;
	HIHist1D *h_pm_matche10;
	HIHist1D *h_pm_matche11;
	HIHist1D *h_pm_matche12;
	HIHist1D *h_pm_matche13;
	HIHist1D *h_pm_matche14;
	HIHist1D *h_pm_matche15;
	HIHist1D *h_pm_matche16;
	HIHist1D *h_pm_matche17;
	HIHist1D *h_pm_matche18;
	HIHist1D *h_pm_matche19;
	HIHist1D *h_pm_matche20;


	HIHist1D *h_pion_matche_endcap;
	HIHist1D *h_pion_matche1_endcap;
	HIHist1D *h_pion_matche2_endcap;
	HIHist1D *h_pion_matche3_endcap;
	HIHist1D *h_pion_matche4_endcap;
	HIHist1D *h_pion_matche5_endcap;
	HIHist1D *h_pion_matche6_endcap;
	HIHist1D *h_pion_matche7_endcap;
	HIHist1D *h_pion_matche8_endcap;
	HIHist1D *h_pion_matche9_endcap;
	HIHist1D *h_pion_matche10_endcap;
	HIHist1D *h_pion_matche11_endcap;
	HIHist1D *h_pion_matche12_endcap;
	HIHist1D *h_pion_matche13_endcap;
	HIHist1D *h_pion_matche14_endcap;
	HIHist1D *h_pion_matche15_endcap;
	HIHist1D *h_pion_matche16_endcap;
	HIHist1D *h_pion_matche17_endcap;
	HIHist1D *h_pion_matche18_endcap;
	HIHist1D *h_pion_matche19_endcap;
	HIHist1D *h_pion_matche20_endcap;

	HIHist1D *h_kaon_matche_endcap;
	HIHist1D *h_kaon_matche1_endcap;
	HIHist1D *h_kaon_matche2_endcap;
	HIHist1D *h_kaon_matche3_endcap;
	HIHist1D *h_kaon_matche4_endcap;
	HIHist1D *h_kaon_matche5_endcap;
	HIHist1D *h_kaon_matche6_endcap;
	HIHist1D *h_kaon_matche7_endcap;
	HIHist1D *h_kaon_matche8_endcap;
	HIHist1D *h_kaon_matche9_endcap;
	HIHist1D *h_kaon_matche10_endcap;
	HIHist1D *h_kaon_matche11_endcap;
	HIHist1D *h_kaon_matche12_endcap;
	HIHist1D *h_kaon_matche13_endcap;
	HIHist1D *h_kaon_matche14_endcap;
	HIHist1D *h_kaon_matche15_endcap;
	HIHist1D *h_kaon_matche16_endcap;
	HIHist1D *h_kaon_matche17_endcap;
	HIHist1D *h_kaon_matche18_endcap;
	HIHist1D *h_kaon_matche19_endcap;
	HIHist1D *h_kaon_matche20_endcap;

	HIHist1D *h_proton_matche_endcap;
	HIHist1D *h_proton_matche1_endcap;
	HIHist1D *h_proton_matche2_endcap;
	HIHist1D *h_proton_matche3_endcap;
	HIHist1D *h_proton_matche4_endcap;
	HIHist1D *h_proton_matche5_endcap;
	HIHist1D *h_proton_matche6_endcap;
	HIHist1D *h_proton_matche7_endcap;
	HIHist1D *h_proton_matche8_endcap;
	HIHist1D *h_proton_matche9_endcap;
	HIHist1D *h_proton_matche10_endcap;
	HIHist1D *h_proton_matche11_endcap;
	HIHist1D *h_proton_matche12_endcap;
	HIHist1D *h_proton_matche13_endcap;
	HIHist1D *h_proton_matche14_endcap;
	HIHist1D *h_proton_matche15_endcap;
	HIHist1D *h_proton_matche16_endcap;
	HIHist1D *h_proton_matche17_endcap;
	HIHist1D *h_proton_matche18_endcap;
	HIHist1D *h_proton_matche19_endcap;
	HIHist1D *h_proton_matche20_endcap;


 	HIHist1D *h_pion_matche_cut1;
	HIHist1D *h_pip_matche1_cut1;
	HIHist1D *h_pip_matche2_cut1;
	HIHist1D *h_pip_matche3_cut1;
	HIHist1D *h_pip_matche4_cut1;
	HIHist1D *h_pip_matche5_cut1;
	HIHist1D *h_pip_matche6_cut1;
	HIHist1D *h_pip_matche7_cut1;
	HIHist1D *h_pip_matche8_cut1;
	HIHist1D *h_pip_matche9_cut1;
	HIHist1D *h_pip_matche10_cut1;
	HIHist1D *h_pip_matche11_cut1;
	HIHist1D *h_pip_matche12_cut1;
	HIHist1D *h_pip_matche13_cut1;
	HIHist1D *h_pip_matche14_cut1;
	HIHist1D *h_pip_matche15_cut1;
	HIHist1D *h_pip_matche16_cut1;
	HIHist1D *h_pip_matche17_cut1;
	HIHist1D *h_pip_matche18_cut1;
	HIHist1D *h_pip_matche19_cut1;
	HIHist1D *h_pip_matche20_cut1;
	HIHist1D *h_pim_matche1_cut1;
	HIHist1D *h_pim_matche2_cut1;
	HIHist1D *h_pim_matche3_cut1;
	HIHist1D *h_pim_matche4_cut1;
	HIHist1D *h_pim_matche5_cut1;
	HIHist1D *h_pim_matche6_cut1;
	HIHist1D *h_pim_matche7_cut1;
	HIHist1D *h_pim_matche8_cut1;
	HIHist1D *h_pim_matche9_cut1;
	HIHist1D *h_pim_matche10_cut1;
	HIHist1D *h_pim_matche11_cut1;
	HIHist1D *h_pim_matche12_cut1;
	HIHist1D *h_pim_matche13_cut1;
	HIHist1D *h_pim_matche14_cut1;
	HIHist1D *h_pim_matche15_cut1;
	HIHist1D *h_pim_matche16_cut1;
	HIHist1D *h_pim_matche17_cut1;
	HIHist1D *h_pim_matche18_cut1;
	HIHist1D *h_pim_matche19_cut1;
	HIHist1D *h_pim_matche20_cut1;

 	HIHist1D *h_pion_matche_cut2;
	HIHist1D *h_pip_matche1_cut2;
	HIHist1D *h_pip_matche2_cut2;
	HIHist1D *h_pip_matche3_cut2;
	HIHist1D *h_pip_matche4_cut2;
	HIHist1D *h_pip_matche5_cut2;
	HIHist1D *h_pip_matche6_cut2;
	HIHist1D *h_pip_matche7_cut2;
	HIHist1D *h_pip_matche8_cut2;
	HIHist1D *h_pip_matche9_cut2;
	HIHist1D *h_pip_matche10_cut2;
	HIHist1D *h_pip_matche11_cut2;
	HIHist1D *h_pip_matche12_cut2;
	HIHist1D *h_pip_matche13_cut2;
	HIHist1D *h_pip_matche14_cut2;
	HIHist1D *h_pip_matche15_cut2;
	HIHist1D *h_pip_matche16_cut2;
	HIHist1D *h_pip_matche17_cut2;
	HIHist1D *h_pip_matche18_cut2;
	HIHist1D *h_pip_matche19_cut2;
	HIHist1D *h_pip_matche20_cut2;
	HIHist1D *h_pim_matche1_cut2;
	HIHist1D *h_pim_matche2_cut2;
	HIHist1D *h_pim_matche3_cut2;
	HIHist1D *h_pim_matche4_cut2;
	HIHist1D *h_pim_matche5_cut2;
	HIHist1D *h_pim_matche6_cut2;
	HIHist1D *h_pim_matche7_cut2;
	HIHist1D *h_pim_matche8_cut2;
	HIHist1D *h_pim_matche9_cut2;
	HIHist1D *h_pim_matche10_cut2;
	HIHist1D *h_pim_matche11_cut2;
	HIHist1D *h_pim_matche12_cut2;
	HIHist1D *h_pim_matche13_cut2;
	HIHist1D *h_pim_matche14_cut2;
	HIHist1D *h_pim_matche15_cut2;
	HIHist1D *h_pim_matche16_cut2;
	HIHist1D *h_pim_matche17_cut2;
	HIHist1D *h_pim_matche18_cut2;
	HIHist1D *h_pim_matche19_cut2;
	HIHist1D *h_pim_matche20_cut2;

 	HIHist1D *h_pion_matche_cut3;
	HIHist1D *h_pip_matche1_cut3;
	HIHist1D *h_pip_matche2_cut3;
	HIHist1D *h_pip_matche3_cut3;
	HIHist1D *h_pip_matche4_cut3;
	HIHist1D *h_pip_matche5_cut3;
	HIHist1D *h_pip_matche6_cut3;
	HIHist1D *h_pip_matche7_cut3;
	HIHist1D *h_pip_matche8_cut3;
	HIHist1D *h_pip_matche9_cut3;
	HIHist1D *h_pip_matche10_cut3;
	HIHist1D *h_pip_matche11_cut3;
	HIHist1D *h_pip_matche12_cut3;
	HIHist1D *h_pip_matche13_cut3;
	HIHist1D *h_pip_matche14_cut3;
	HIHist1D *h_pip_matche15_cut3;
	HIHist1D *h_pip_matche16_cut3;
	HIHist1D *h_pip_matche17_cut3;
	HIHist1D *h_pip_matche18_cut3;
	HIHist1D *h_pip_matche19_cut3;
	HIHist1D *h_pip_matche20_cut3;
	HIHist1D *h_pim_matche1_cut3;
	HIHist1D *h_pim_matche2_cut3;
	HIHist1D *h_pim_matche3_cut3;
	HIHist1D *h_pim_matche4_cut3;
	HIHist1D *h_pim_matche5_cut3;
	HIHist1D *h_pim_matche6_cut3;
	HIHist1D *h_pim_matche7_cut3;
	HIHist1D *h_pim_matche8_cut3;
	HIHist1D *h_pim_matche9_cut3;
	HIHist1D *h_pim_matche10_cut3;
	HIHist1D *h_pim_matche11_cut3;
	HIHist1D *h_pim_matche12_cut3;
	HIHist1D *h_pim_matche13_cut3;
	HIHist1D *h_pim_matche14_cut3;
	HIHist1D *h_pim_matche15_cut3;
	HIHist1D *h_pim_matche16_cut3;
	HIHist1D *h_pim_matche17_cut3;
	HIHist1D *h_pim_matche18_cut3;
	HIHist1D *h_pim_matche19_cut3;
	HIHist1D *h_pim_matche20_cut3;

 	HIHist1D *h_pion_matche_cut4;
	HIHist1D *h_pip_matche1_cut4;
	HIHist1D *h_pip_matche2_cut4;
	HIHist1D *h_pip_matche3_cut4;
	HIHist1D *h_pip_matche4_cut4;
	HIHist1D *h_pip_matche5_cut4;
	HIHist1D *h_pip_matche6_cut4;
	HIHist1D *h_pip_matche7_cut4;
	HIHist1D *h_pip_matche8_cut4;
	HIHist1D *h_pip_matche9_cut4;
	HIHist1D *h_pip_matche10_cut4;
	HIHist1D *h_pip_matche11_cut4;
	HIHist1D *h_pip_matche12_cut4;
	HIHist1D *h_pip_matche13_cut4;
	HIHist1D *h_pip_matche14_cut4;
	HIHist1D *h_pip_matche15_cut4;
	HIHist1D *h_pip_matche16_cut4;
	HIHist1D *h_pip_matche17_cut4;
	HIHist1D *h_pip_matche18_cut4;
	HIHist1D *h_pip_matche19_cut4;
	HIHist1D *h_pip_matche20_cut4;
	HIHist1D *h_pim_matche1_cut4;
	HIHist1D *h_pim_matche2_cut4;
	HIHist1D *h_pim_matche3_cut4;
	HIHist1D *h_pim_matche4_cut4;
	HIHist1D *h_pim_matche5_cut4;
	HIHist1D *h_pim_matche6_cut4;
	HIHist1D *h_pim_matche7_cut4;
	HIHist1D *h_pim_matche8_cut4;
	HIHist1D *h_pim_matche9_cut4;
	HIHist1D *h_pim_matche10_cut4;
	HIHist1D *h_pim_matche11_cut4;
	HIHist1D *h_pim_matche12_cut4;
	HIHist1D *h_pim_matche13_cut4;
	HIHist1D *h_pim_matche14_cut4;
	HIHist1D *h_pim_matche15_cut4;
	HIHist1D *h_pim_matche16_cut4;
	HIHist1D *h_pim_matche17_cut4;
	HIHist1D *h_pim_matche18_cut4;
	HIHist1D *h_pim_matche19_cut4;
	HIHist1D *h_pim_matche20_cut4;

 	HIHist1D *h_pion_matche_cut5;
	HIHist1D *h_pip_matche1_cut5;
	HIHist1D *h_pip_matche2_cut5;
	HIHist1D *h_pip_matche3_cut5;
	HIHist1D *h_pip_matche4_cut5;
	HIHist1D *h_pip_matche5_cut5;
	HIHist1D *h_pip_matche6_cut5;
	HIHist1D *h_pip_matche7_cut5;
	HIHist1D *h_pip_matche8_cut5;
	HIHist1D *h_pip_matche9_cut5;
	HIHist1D *h_pip_matche10_cut5;
	HIHist1D *h_pip_matche11_cut5;
	HIHist1D *h_pip_matche12_cut5;
	HIHist1D *h_pip_matche13_cut5;
	HIHist1D *h_pip_matche14_cut5;
	HIHist1D *h_pip_matche15_cut5;
	HIHist1D *h_pip_matche16_cut5;
	HIHist1D *h_pip_matche17_cut5;
	HIHist1D *h_pip_matche18_cut5;
	HIHist1D *h_pip_matche19_cut5;
	HIHist1D *h_pip_matche20_cut5;
	HIHist1D *h_pim_matche1_cut5;
	HIHist1D *h_pim_matche2_cut5;
	HIHist1D *h_pim_matche3_cut5;
	HIHist1D *h_pim_matche4_cut5;
	HIHist1D *h_pim_matche5_cut5;
	HIHist1D *h_pim_matche6_cut5;
	HIHist1D *h_pim_matche7_cut5;
	HIHist1D *h_pim_matche8_cut5;
	HIHist1D *h_pim_matche9_cut5;
	HIHist1D *h_pim_matche10_cut5;
	HIHist1D *h_pim_matche11_cut5;
	HIHist1D *h_pim_matche12_cut5;
	HIHist1D *h_pim_matche13_cut5;
	HIHist1D *h_pim_matche14_cut5;
	HIHist1D *h_pim_matche15_cut5;
	HIHist1D *h_pim_matche16_cut5;
	HIHist1D *h_pim_matche17_cut5;
	HIHist1D *h_pim_matche18_cut5;
	HIHist1D *h_pim_matche19_cut5;
	HIHist1D *h_pim_matche20_cut5;

	HIHist2D *h_pion_muall_p_costh;
	HIHist2D *h_pion_muall_p_phi;
	HIHist2D *h_pion_muall_costh_phi;
	HIHist2D *h_pip_muall_p_costh;
	HIHist2D *h_pip_muall_p_phi;
	HIHist2D *h_pip_muall_costh_phi;
	HIHist2D *h_pim_muall_p_costh;
	HIHist2D *h_pim_muall_p_phi;
	HIHist2D *h_pim_muall_costh_phi;

	HIHist2D *h_pion_mucut_p_costh;
	HIHist2D *h_pion_mucut_p_phi;
	HIHist2D *h_pion_mucut_costh_phi;
	HIHist2D *h_pip_mucut_p_costh;
	HIHist2D *h_pip_mucut_p_phi;
	HIHist2D *h_pip_mucut_costh_phi;
	HIHist2D *h_pim_mucut_p_costh;
	HIHist2D *h_pim_mucut_p_phi;
	HIHist2D *h_pim_mucut_costh_phi;
	
	HIHist2D *h_pip_muall_costh_phi_cut1;
	HIHist2D *h_pip_muall_costh_phi_cut2;
	HIHist2D *h_pip_muall_costh_phi_cut3;
	HIHist2D *h_pip_muall_costh_phi_cut4;
	HIHist2D *h_pip_muall_costh_phi_cut5;
	HIHist2D *h_pip_muall_costh_phi_cut6;
	HIHist2D *h_pip_muall_costh_phi_cut7;
	HIHist2D *h_pip_muall_costh_phi_cut8;
	HIHist2D *h_pip_muall_costh_phi_cut9;
	HIHist2D *h_pip_muall_costh_phi_cut10;
	HIHist2D *h_pip_muall_costh_phi_cut11;
	HIHist2D *h_pip_muall_costh_phi_cut12;
	HIHist2D *h_pip_muall_costh_phi_cut13;
	HIHist2D *h_pip_muall_costh_phi_cut14;
	HIHist2D *h_pip_muall_costh_phi_cut15;
	HIHist2D *h_pip_muall_costh_phi_cut16;
	HIHist2D *h_pip_muall_costh_phi_cut17;
	HIHist2D *h_pip_muall_costh_phi_cut18;
	HIHist2D *h_pip_muall_costh_phi_cut19;
	HIHist2D *h_pip_muall_costh_phi_cut20;
	HIHist2D *h_pim_muall_costh_phi_cut1;
	HIHist2D *h_pim_muall_costh_phi_cut2;
	HIHist2D *h_pim_muall_costh_phi_cut3;
	HIHist2D *h_pim_muall_costh_phi_cut4;
	HIHist2D *h_pim_muall_costh_phi_cut5;
	HIHist2D *h_pim_muall_costh_phi_cut6;
	HIHist2D *h_pim_muall_costh_phi_cut7;
	HIHist2D *h_pim_muall_costh_phi_cut8;
	HIHist2D *h_pim_muall_costh_phi_cut9;
	HIHist2D *h_pim_muall_costh_phi_cut10;
	HIHist2D *h_pim_muall_costh_phi_cut11;
	HIHist2D *h_pim_muall_costh_phi_cut12;
	HIHist2D *h_pim_muall_costh_phi_cut13;
	HIHist2D *h_pim_muall_costh_phi_cut14;
	HIHist2D *h_pim_muall_costh_phi_cut15;
	HIHist2D *h_pim_muall_costh_phi_cut16;
	HIHist2D *h_pim_muall_costh_phi_cut17;
	HIHist2D *h_pim_muall_costh_phi_cut18;
	HIHist2D *h_pim_muall_costh_phi_cut19;
	HIHist2D *h_pim_muall_costh_phi_cut20;

	HIHist2D *h_pip_mucut_costh_phi_cut1;
	HIHist2D *h_pip_mucut_costh_phi_cut2;
	HIHist2D *h_pip_mucut_costh_phi_cut3;
	HIHist2D *h_pip_mucut_costh_phi_cut4;
	HIHist2D *h_pip_mucut_costh_phi_cut5;
	HIHist2D *h_pip_mucut_costh_phi_cut6;
	HIHist2D *h_pip_mucut_costh_phi_cut7;
	HIHist2D *h_pip_mucut_costh_phi_cut8;
	HIHist2D *h_pip_mucut_costh_phi_cut9;
	HIHist2D *h_pip_mucut_costh_phi_cut10;
	HIHist2D *h_pip_mucut_costh_phi_cut11;
	HIHist2D *h_pip_mucut_costh_phi_cut12;
	HIHist2D *h_pip_mucut_costh_phi_cut13;
	HIHist2D *h_pip_mucut_costh_phi_cut14;
	HIHist2D *h_pip_mucut_costh_phi_cut15;
	HIHist2D *h_pip_mucut_costh_phi_cut16;
	HIHist2D *h_pip_mucut_costh_phi_cut17;
	HIHist2D *h_pip_mucut_costh_phi_cut18;
	HIHist2D *h_pip_mucut_costh_phi_cut19;
	HIHist2D *h_pip_mucut_costh_phi_cut20;
	HIHist2D *h_pim_mucut_costh_phi_cut1;
	HIHist2D *h_pim_mucut_costh_phi_cut2;
	HIHist2D *h_pim_mucut_costh_phi_cut3;
	HIHist2D *h_pim_mucut_costh_phi_cut4;
	HIHist2D *h_pim_mucut_costh_phi_cut5;
	HIHist2D *h_pim_mucut_costh_phi_cut6;
	HIHist2D *h_pim_mucut_costh_phi_cut7;
	HIHist2D *h_pim_mucut_costh_phi_cut8;
	HIHist2D *h_pim_mucut_costh_phi_cut9;
	HIHist2D *h_pim_mucut_costh_phi_cut10;
	HIHist2D *h_pim_mucut_costh_phi_cut11;
	HIHist2D *h_pim_mucut_costh_phi_cut12;
	HIHist2D *h_pim_mucut_costh_phi_cut13;
	HIHist2D *h_pim_mucut_costh_phi_cut14;
	HIHist2D *h_pim_mucut_costh_phi_cut15;
	HIHist2D *h_pim_mucut_costh_phi_cut16;
	HIHist2D *h_pim_mucut_costh_phi_cut17;
	HIHist2D *h_pim_mucut_costh_phi_cut18;
	HIHist2D *h_pim_mucut_costh_phi_cut19;
	HIHist2D *h_pim_mucut_costh_phi_cut20;

	
	HIHist1D *h_muon_p;
	HIHist1D *h_muon_costh;
	HIHist1D *h_muon_p_picut;
	HIHist1D *h_muon_costh_picut;

	HIHist2D *h_muon_p_mudepth;
	HIHist2D *h_muon_costh_mudepth;
	HIHist2D *h_muon_p_mudepth_picut;
	HIHist2D *h_muon_costh_mudepth_picut;

	HIHist2D *h_muon_muall_p_costh;
	HIHist2D *h_muon_muall_p_phi;
	HIHist2D *h_muon_muall_costh_phi;
	HIHist2D *h_muon_mucut_p_costh;
	HIHist2D *h_muon_mucut_p_phi;
	HIHist2D *h_muon_mucut_costh_phi;

	HIHist2D *h_muon_pimuall_p_costh;
	HIHist2D *h_muon_pimuall_p_phi;
	HIHist2D *h_muon_pimuall_costh_phi;
	HIHist2D *h_muon_pimucut_p_costh;
	HIHist2D *h_muon_pimucut_p_phi;
	HIHist2D *h_muon_pimucut_costh_phi;

	HIHist2D *h_muon_mucut2_p_costh;
	HIHist2D *h_muon_mucut2_p_phi;
	HIHist2D *h_muon_mucut2_costh_phi;

	HIHist2D *h_muon_pimucut2_p_costh;
	HIHist2D *h_muon_pimucut2_p_phi;
	HIHist2D *h_muon_pimucut2_costh_phi;
	


      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* PPGPSIPPROC_PPGPSIPPROC_H */
