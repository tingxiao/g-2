// -*- C++ -*-
#if !defined(PPGPSIPPROC_PPGPSIPPROC_H)
#define PPGPSIPPROC_PPGPSIPPROC_H
//
// Package:     <Bin20_JpsiPiPiProc>
// Module:      Bin20_JpsiPiPiProc
//
/**\class Bin20_JpsiPiPiProc Bin20_JpsiPiPiProc.h Bin20_JpsiPiPiProc/Bin20_JpsiPiPiProc.h
 
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

class Bin20_JpsiPiPiProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      Bin20_JpsiPiPiProc( void );                      // anal1 
      virtual ~Bin20_JpsiPiPiProc();                   // anal5 

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
      Bin20_JpsiPiPiProc( const Bin20_JpsiPiPiProc& );

      // ------------ assignment operator(s) ---------------------
      const Bin20_JpsiPiPiProc& operator=( const Bin20_JpsiPiPiProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (Bin20_JpsiPiPiProc::*iMethod)( Frame& ),
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
        HIHist1D *h_pip_eop21;
        HIHist1D *h_pip_eop22;
        HIHist1D *h_pip_eop23;
        HIHist1D *h_pip_eop24;
        HIHist1D *h_pip_eop25;
        HIHist1D *h_pip_eop26;
        HIHist1D *h_pip_eop27;
        HIHist1D *h_pip_eop28;
        HIHist1D *h_pip_eop29;
        HIHist1D *h_pip_eop30;
        HIHist1D *h_pip_eop31;
        HIHist1D *h_pip_eop32;
        HIHist1D *h_pip_eop33;
        HIHist1D *h_pip_eop34;
        HIHist1D *h_pip_eop35;
        HIHist1D *h_pip_eop36;
        HIHist1D *h_pip_eop37;
        HIHist1D *h_pip_eop38;
        HIHist1D *h_pip_eop39;
       	HIHist1D *h_pip_eop40;
        HIHist1D *h_pip_eop41;
        HIHist1D *h_pip_eop42;
        HIHist1D *h_pip_eop43;
        HIHist1D *h_pip_eop44;
        HIHist1D *h_pip_eop45;
        HIHist1D *h_pip_eop46;
        HIHist1D *h_pip_eop47;
        HIHist1D *h_pip_eop48;
        HIHist1D *h_pip_eop49;
        HIHist1D *h_pip_eop50;
        HIHist1D *h_pip_eop51;
        HIHist1D *h_pip_eop52;
        HIHist1D *h_pip_eop53;
        HIHist1D *h_pip_eop54;
        HIHist1D *h_pip_eop55;
        HIHist1D *h_pip_eop56;
        HIHist1D *h_pip_eop57;
        HIHist1D *h_pip_eop58;
        HIHist1D *h_pip_eop59;
        HIHist1D *h_pip_eop60;
        HIHist1D *h_pip_eop61;
        HIHist1D *h_pip_eop62;
        HIHist1D *h_pip_eop63;
        HIHist1D *h_pip_eop64;
        HIHist1D *h_pip_eop65;
        HIHist1D *h_pip_eop66;
        HIHist1D *h_pip_eop67;
        HIHist1D *h_pip_eop68;
        HIHist1D *h_pip_eop69;
        HIHist1D *h_pip_eop70;
        HIHist1D *h_pip_eop71;
        HIHist1D *h_pip_eop72;
        HIHist1D *h_pip_eop73;
        HIHist1D *h_pip_eop74;
        HIHist1D *h_pip_eop75;
        HIHist1D *h_pip_eop76;
        HIHist1D *h_pip_eop77;
        HIHist1D *h_pip_eop78;
        HIHist1D *h_pip_eop79;
        HIHist1D *h_pip_eop80;
        HIHist1D *h_pip_eop81;
        HIHist1D *h_pip_eop82;
        HIHist1D *h_pip_eop83;
        HIHist1D *h_pip_eop84;
        HIHist1D *h_pip_eop85;
        HIHist1D *h_pip_eop86;
        HIHist1D *h_pip_eop87;
        HIHist1D *h_pip_eop88;
        HIHist1D *h_pip_eop89;
        HIHist1D *h_pip_eop90;
        HIHist1D *h_pip_eop91;
        HIHist1D *h_pip_eop92;
        HIHist1D *h_pip_eop93;
        HIHist1D *h_pip_eop94;
        HIHist1D *h_pip_eop95;
        HIHist1D *h_pip_eop96;
        HIHist1D *h_pip_eop97;
        HIHist1D *h_pip_eop98;
        HIHist1D *h_pip_eop99;
        HIHist1D *h_pip_eop100;

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
        HIHist1D *h_pim_eop21;
        HIHist1D *h_pim_eop22;
        HIHist1D *h_pim_eop23;
        HIHist1D *h_pim_eop24;
        HIHist1D *h_pim_eop25;
        HIHist1D *h_pim_eop26;
        HIHist1D *h_pim_eop27;
        HIHist1D *h_pim_eop28;
        HIHist1D *h_pim_eop29;
        HIHist1D *h_pim_eop30;
        HIHist1D *h_pim_eop31;
        HIHist1D *h_pim_eop32;
        HIHist1D *h_pim_eop33;
        HIHist1D *h_pim_eop34;
        HIHist1D *h_pim_eop35;
        HIHist1D *h_pim_eop36;
        HIHist1D *h_pim_eop37;
        HIHist1D *h_pim_eop38;
        HIHist1D *h_pim_eop39;
        HIHist1D *h_pim_eop40;
        HIHist1D *h_pim_eop41;
        HIHist1D *h_pim_eop42;
        HIHist1D *h_pim_eop43;
        HIHist1D *h_pim_eop44;
        HIHist1D *h_pim_eop45;
        HIHist1D *h_pim_eop46;
        HIHist1D *h_pim_eop47;
        HIHist1D *h_pim_eop48;
        HIHist1D *h_pim_eop49;
        HIHist1D *h_pim_eop50;
        HIHist1D *h_pim_eop51;
        HIHist1D *h_pim_eop52;
        HIHist1D *h_pim_eop53;
        HIHist1D *h_pim_eop54;
        HIHist1D *h_pim_eop55;
        HIHist1D *h_pim_eop56;
        HIHist1D *h_pim_eop57;
        HIHist1D *h_pim_eop58;
        HIHist1D *h_pim_eop59;
        HIHist1D *h_pim_eop60;
        HIHist1D *h_pim_eop61;
        HIHist1D *h_pim_eop62;
        HIHist1D *h_pim_eop63;
        HIHist1D *h_pim_eop64;
        HIHist1D *h_pim_eop65;
        HIHist1D *h_pim_eop66;
        HIHist1D *h_pim_eop67;
        HIHist1D *h_pim_eop68;
        HIHist1D *h_pim_eop69;
        HIHist1D *h_pim_eop70;
        HIHist1D *h_pim_eop71;
        HIHist1D *h_pim_eop72;
        HIHist1D *h_pim_eop73;
        HIHist1D *h_pim_eop74;
        HIHist1D *h_pim_eop75;
        HIHist1D *h_pim_eop76;
        HIHist1D *h_pim_eop77;
        HIHist1D *h_pim_eop78;
        HIHist1D *h_pim_eop79;
        HIHist1D *h_pim_eop80;
        HIHist1D *h_pim_eop81;
        HIHist1D *h_pim_eop82;
        HIHist1D *h_pim_eop83;
        HIHist1D *h_pim_eop84;
        HIHist1D *h_pim_eop85;
        HIHist1D *h_pim_eop86;
        HIHist1D *h_pim_eop87;
        HIHist1D *h_pim_eop88;
        HIHist1D *h_pim_eop89;
        HIHist1D *h_pim_eop90;
        HIHist1D *h_pim_eop91;
        HIHist1D *h_pim_eop92;
        HIHist1D *h_pim_eop93;
        HIHist1D *h_pim_eop94;
        HIHist1D *h_pim_eop95;
        HIHist1D *h_pim_eop96;
        HIHist1D *h_pim_eop97;
        HIHist1D *h_pim_eop98;
        HIHist1D *h_pim_eop99;
        HIHist1D *h_pim_eop100;

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
        HIHist1D *h_pip_matche21;
        HIHist1D *h_pip_matche22;
        HIHist1D *h_pip_matche23;
        HIHist1D *h_pip_matche24;
        HIHist1D *h_pip_matche25;
        HIHist1D *h_pip_matche26;
        HIHist1D *h_pip_matche27;
        HIHist1D *h_pip_matche28;
        HIHist1D *h_pip_matche29;
        HIHist1D *h_pip_matche30;
        HIHist1D *h_pip_matche31;
        HIHist1D *h_pip_matche32;
        HIHist1D *h_pip_matche33;
        HIHist1D *h_pip_matche34;
        HIHist1D *h_pip_matche35;
        HIHist1D *h_pip_matche36;
        HIHist1D *h_pip_matche37;
        HIHist1D *h_pip_matche38;
        HIHist1D *h_pip_matche39;
        HIHist1D *h_pip_matche40;
        HIHist1D *h_pip_matche41;
        HIHist1D *h_pip_matche42;
        HIHist1D *h_pip_matche43;
        HIHist1D *h_pip_matche44;
        HIHist1D *h_pip_matche45;
        HIHist1D *h_pip_matche46;
        HIHist1D *h_pip_matche47;
        HIHist1D *h_pip_matche48;
        HIHist1D *h_pip_matche49;
        HIHist1D *h_pip_matche50;
        HIHist1D *h_pip_matche51;
        HIHist1D *h_pip_matche52;
        HIHist1D *h_pip_matche53;
        HIHist1D *h_pip_matche54;
        HIHist1D *h_pip_matche55;
        HIHist1D *h_pip_matche56;
        HIHist1D *h_pip_matche57;
        HIHist1D *h_pip_matche58;
        HIHist1D *h_pip_matche59;
        HIHist1D *h_pip_matche60;
        HIHist1D *h_pip_matche61;
        HIHist1D *h_pip_matche62;
        HIHist1D *h_pip_matche63;
        HIHist1D *h_pip_matche64;
        HIHist1D *h_pip_matche65;
        HIHist1D *h_pip_matche66;
        HIHist1D *h_pip_matche67;
        HIHist1D *h_pip_matche68;
        HIHist1D *h_pip_matche69;
        HIHist1D *h_pip_matche70;
        HIHist1D *h_pip_matche71;
        HIHist1D *h_pip_matche72;
        HIHist1D *h_pip_matche73;
        HIHist1D *h_pip_matche74;
        HIHist1D *h_pip_matche75;
        HIHist1D *h_pip_matche76;
        HIHist1D *h_pip_matche77;
        HIHist1D *h_pip_matche78;
        HIHist1D *h_pip_matche79;
        HIHist1D *h_pip_matche80;
        HIHist1D *h_pip_matche81;
        HIHist1D *h_pip_matche82;
        HIHist1D *h_pip_matche83;
        HIHist1D *h_pip_matche84;
        HIHist1D *h_pip_matche85;
        HIHist1D *h_pip_matche86;
        HIHist1D *h_pip_matche87;
        HIHist1D *h_pip_matche88;
        HIHist1D *h_pip_matche89;
        HIHist1D *h_pip_matche90;
        HIHist1D *h_pip_matche91;
        HIHist1D *h_pip_matche92;
        HIHist1D *h_pip_matche93;
        HIHist1D *h_pip_matche94;
        HIHist1D *h_pip_matche95;
        HIHist1D *h_pip_matche96;
        HIHist1D *h_pip_matche97;
        HIHist1D *h_pip_matche98;
        HIHist1D *h_pip_matche99;
        HIHist1D *h_pip_matche100;

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
        HIHist1D *h_pim_matche21;
        HIHist1D *h_pim_matche22;
        HIHist1D *h_pim_matche23;
        HIHist1D *h_pim_matche24;
        HIHist1D *h_pim_matche25;
        HIHist1D *h_pim_matche26;
        HIHist1D *h_pim_matche27;
        HIHist1D *h_pim_matche28;
        HIHist1D *h_pim_matche29;
        HIHist1D *h_pim_matche30;
        HIHist1D *h_pim_matche31;
        HIHist1D *h_pim_matche32;
        HIHist1D *h_pim_matche33;
        HIHist1D *h_pim_matche34;
        HIHist1D *h_pim_matche35;
        HIHist1D *h_pim_matche36;
        HIHist1D *h_pim_matche37;
        HIHist1D *h_pim_matche38;
        HIHist1D *h_pim_matche39;
        HIHist1D *h_pim_matche40;
        HIHist1D *h_pim_matche41;
        HIHist1D *h_pim_matche42;
        HIHist1D *h_pim_matche43;
        HIHist1D *h_pim_matche44;
        HIHist1D *h_pim_matche45;
        HIHist1D *h_pim_matche46;
        HIHist1D *h_pim_matche47;
        HIHist1D *h_pim_matche48;
        HIHist1D *h_pim_matche49;
        HIHist1D *h_pim_matche50;
        HIHist1D *h_pim_matche51;
        HIHist1D *h_pim_matche52;
        HIHist1D *h_pim_matche53;
        HIHist1D *h_pim_matche54;
        HIHist1D *h_pim_matche55;
        HIHist1D *h_pim_matche56;
        HIHist1D *h_pim_matche57;
        HIHist1D *h_pim_matche58;
        HIHist1D *h_pim_matche59;
        HIHist1D *h_pim_matche60;
        HIHist1D *h_pim_matche61;
        HIHist1D *h_pim_matche62;
        HIHist1D *h_pim_matche63;
        HIHist1D *h_pim_matche64;
        HIHist1D *h_pim_matche65;
        HIHist1D *h_pim_matche66;
        HIHist1D *h_pim_matche67;
        HIHist1D *h_pim_matche68;
        HIHist1D *h_pim_matche69;
        HIHist1D *h_pim_matche70;
        HIHist1D *h_pim_matche71;
        HIHist1D *h_pim_matche72;
        HIHist1D *h_pim_matche73;
        HIHist1D *h_pim_matche74;
        HIHist1D *h_pim_matche75;
        HIHist1D *h_pim_matche76;
        HIHist1D *h_pim_matche77;
        HIHist1D *h_pim_matche78;
        HIHist1D *h_pim_matche79;
        HIHist1D *h_pim_matche80;
        HIHist1D *h_pim_matche81;
        HIHist1D *h_pim_matche82;
        HIHist1D *h_pim_matche83;
        HIHist1D *h_pim_matche84;
        HIHist1D *h_pim_matche85;
        HIHist1D *h_pim_matche86;
        HIHist1D *h_pim_matche87;
        HIHist1D *h_pim_matche88;
        HIHist1D *h_pim_matche89;
        HIHist1D *h_pim_matche90;
        HIHist1D *h_pim_matche91;
        HIHist1D *h_pim_matche92;
        HIHist1D *h_pim_matche93;
        HIHist1D *h_pim_matche94;
        HIHist1D *h_pim_matche95;
        HIHist1D *h_pim_matche96;
        HIHist1D *h_pim_matche97;
        HIHist1D *h_pim_matche98;
        HIHist1D *h_pim_matche99;
        HIHist1D *h_pim_matche100;


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
        HIHist1D *h_pip_matche21_eop;
        HIHist1D *h_pip_matche22_eop;
        HIHist1D *h_pip_matche23_eop;
        HIHist1D *h_pip_matche24_eop;
        HIHist1D *h_pip_matche25_eop;
        HIHist1D *h_pip_matche26_eop;
        HIHist1D *h_pip_matche27_eop;
        HIHist1D *h_pip_matche28_eop;
        HIHist1D *h_pip_matche29_eop;
        HIHist1D *h_pip_matche30_eop;
        HIHist1D *h_pip_matche31_eop;
        HIHist1D *h_pip_matche32_eop;
        HIHist1D *h_pip_matche33_eop;
        HIHist1D *h_pip_matche34_eop;
        HIHist1D *h_pip_matche35_eop;
        HIHist1D *h_pip_matche36_eop;
        HIHist1D *h_pip_matche37_eop;
        HIHist1D *h_pip_matche38_eop;
        HIHist1D *h_pip_matche39_eop;
        HIHist1D *h_pip_matche40_eop;
        HIHist1D *h_pip_matche41_eop;
        HIHist1D *h_pip_matche42_eop;
        HIHist1D *h_pip_matche43_eop;
        HIHist1D *h_pip_matche44_eop;
        HIHist1D *h_pip_matche45_eop;
        HIHist1D *h_pip_matche46_eop;
        HIHist1D *h_pip_matche47_eop;
        HIHist1D *h_pip_matche48_eop;
        HIHist1D *h_pip_matche49_eop;
        HIHist1D *h_pip_matche50_eop;
        HIHist1D *h_pip_matche51_eop;
        HIHist1D *h_pip_matche52_eop;
        HIHist1D *h_pip_matche53_eop;
        HIHist1D *h_pip_matche54_eop;
        HIHist1D *h_pip_matche55_eop;
        HIHist1D *h_pip_matche56_eop;
        HIHist1D *h_pip_matche57_eop;
        HIHist1D *h_pip_matche58_eop;
        HIHist1D *h_pip_matche59_eop;
        HIHist1D *h_pip_matche60_eop;
        HIHist1D *h_pip_matche61_eop;
        HIHist1D *h_pip_matche62_eop;
        HIHist1D *h_pip_matche63_eop;
        HIHist1D *h_pip_matche64_eop;
        HIHist1D *h_pip_matche65_eop;
        HIHist1D *h_pip_matche66_eop;
        HIHist1D *h_pip_matche67_eop;
        HIHist1D *h_pip_matche68_eop;
        HIHist1D *h_pip_matche69_eop;
        HIHist1D *h_pip_matche70_eop;
        HIHist1D *h_pip_matche71_eop;
        HIHist1D *h_pip_matche72_eop;
        HIHist1D *h_pip_matche73_eop;
        HIHist1D *h_pip_matche74_eop;
        HIHist1D *h_pip_matche75_eop;
        HIHist1D *h_pip_matche76_eop;
        HIHist1D *h_pip_matche77_eop;
        HIHist1D *h_pip_matche78_eop;
        HIHist1D *h_pip_matche79_eop;
        HIHist1D *h_pip_matche80_eop;
        HIHist1D *h_pip_matche81_eop;
        HIHist1D *h_pip_matche82_eop;
        HIHist1D *h_pip_matche83_eop;
        HIHist1D *h_pip_matche84_eop;
        HIHist1D *h_pip_matche85_eop;
        HIHist1D *h_pip_matche86_eop;
        HIHist1D *h_pip_matche87_eop;
        HIHist1D *h_pip_matche88_eop;
        HIHist1D *h_pip_matche89_eop;
        HIHist1D *h_pip_matche90_eop;
        HIHist1D *h_pip_matche91_eop;
        HIHist1D *h_pip_matche92_eop;
        HIHist1D *h_pip_matche93_eop;
        HIHist1D *h_pip_matche94_eop;
        HIHist1D *h_pip_matche95_eop;
        HIHist1D *h_pip_matche96_eop;
        HIHist1D *h_pip_matche97_eop;
        HIHist1D *h_pip_matche98_eop;
        HIHist1D *h_pip_matche99_eop;
        HIHist1D *h_pip_matche100_eop;

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
        HIHist1D *h_pim_matche21_eop;
        HIHist1D *h_pim_matche22_eop;
        HIHist1D *h_pim_matche23_eop;
        HIHist1D *h_pim_matche24_eop;
        HIHist1D *h_pim_matche25_eop;
        HIHist1D *h_pim_matche26_eop;
        HIHist1D *h_pim_matche27_eop;
        HIHist1D *h_pim_matche28_eop;
        HIHist1D *h_pim_matche29_eop;
        HIHist1D *h_pim_matche30_eop;
        HIHist1D *h_pim_matche31_eop;
        HIHist1D *h_pim_matche32_eop;
        HIHist1D *h_pim_matche33_eop;
        HIHist1D *h_pim_matche34_eop;
        HIHist1D *h_pim_matche35_eop;
        HIHist1D *h_pim_matche36_eop;
        HIHist1D *h_pim_matche37_eop;
        HIHist1D *h_pim_matche38_eop;
        HIHist1D *h_pim_matche39_eop;
        HIHist1D *h_pim_matche40_eop;
        HIHist1D *h_pim_matche41_eop;
        HIHist1D *h_pim_matche42_eop;
        HIHist1D *h_pim_matche43_eop;
        HIHist1D *h_pim_matche44_eop;
        HIHist1D *h_pim_matche45_eop;
        HIHist1D *h_pim_matche46_eop;
        HIHist1D *h_pim_matche47_eop;
        HIHist1D *h_pim_matche48_eop;
        HIHist1D *h_pim_matche49_eop;
        HIHist1D *h_pim_matche50_eop;
        HIHist1D *h_pim_matche51_eop;
        HIHist1D *h_pim_matche52_eop;
        HIHist1D *h_pim_matche53_eop;
        HIHist1D *h_pim_matche54_eop;
        HIHist1D *h_pim_matche55_eop;
        HIHist1D *h_pim_matche56_eop;
        HIHist1D *h_pim_matche57_eop;
        HIHist1D *h_pim_matche58_eop;
        HIHist1D *h_pim_matche59_eop;
        HIHist1D *h_pim_matche60_eop;
        HIHist1D *h_pim_matche61_eop;
        HIHist1D *h_pim_matche62_eop;
        HIHist1D *h_pim_matche63_eop;
        HIHist1D *h_pim_matche64_eop;
        HIHist1D *h_pim_matche65_eop;
        HIHist1D *h_pim_matche66_eop;
        HIHist1D *h_pim_matche67_eop;
        HIHist1D *h_pim_matche68_eop;
        HIHist1D *h_pim_matche69_eop;
        HIHist1D *h_pim_matche70_eop;
        HIHist1D *h_pim_matche71_eop;
        HIHist1D *h_pim_matche72_eop;
        HIHist1D *h_pim_matche73_eop;
        HIHist1D *h_pim_matche74_eop;
        HIHist1D *h_pim_matche75_eop;
        HIHist1D *h_pim_matche76_eop;
        HIHist1D *h_pim_matche77_eop;
        HIHist1D *h_pim_matche78_eop;
        HIHist1D *h_pim_matche79_eop;
        HIHist1D *h_pim_matche80_eop;
        HIHist1D *h_pim_matche81_eop;
        HIHist1D *h_pim_matche82_eop;
        HIHist1D *h_pim_matche83_eop;
        HIHist1D *h_pim_matche84_eop;
        HIHist1D *h_pim_matche85_eop;
        HIHist1D *h_pim_matche86_eop;
        HIHist1D *h_pim_matche87_eop;
        HIHist1D *h_pim_matche88_eop;
        HIHist1D *h_pim_matche89_eop;
        HIHist1D *h_pim_matche90_eop;
        HIHist1D *h_pim_matche91_eop;
        HIHist1D *h_pim_matche92_eop;
        HIHist1D *h_pim_matche93_eop;
        HIHist1D *h_pim_matche94_eop;
        HIHist1D *h_pim_matche95_eop;
        HIHist1D *h_pim_matche96_eop;
        HIHist1D *h_pim_matche97_eop;
        HIHist1D *h_pim_matche98_eop;
        HIHist1D *h_pim_matche99_eop;
        HIHist1D *h_pim_matche100_eop;

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
