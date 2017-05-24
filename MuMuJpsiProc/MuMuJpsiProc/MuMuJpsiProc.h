// -*- C++ -*-
#if !defined(PPGPSIPPROC_PPGPSIPPROC_H)
#define PPGPSIPPROC_PPGPSIPPROC_H
//
// Package:     <MuMuJpsiProc>
// Module:      MuMuJpsiProc
//
/**\class MuMuJpsiProc MuMuJpsiProc.h MuMuJpsiProc/MuMuJpsiProc.h
 
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

#include <Experiment/Experiment.h>

// user include files
#include "Processor/Processor.h"
#include "HistogramInterface/HistogramPackage.h"
#include "FrameAccess/FATable.h"
#include "Navigation/NavTrack.h"
#include "Navigation/NavShower.h"

// forward declarations

class MuMuJpsiProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      MuMuJpsiProc( void );                      // anal1 
      virtual ~MuMuJpsiProc();                   // anal5 

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
      MuMuJpsiProc( const MuMuJpsiProc& );

      // ------------ assignment operator(s) ---------------------
      const MuMuJpsiProc& operator=( const MuMuJpsiProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (MuMuJpsiProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------
      int CompareKins( FAItem<KTKinematicData>  &k1, 
		       FAItem<KTKinematicData>  &k2) const;
/*
      int CompareKins( FAItem<TDKinematicFit>  &k1, 
		       FAItem<TDKinematicFit>  &k2) const;
*/
      int CompareKins( FAItem<TDKinematicFit>  k1, 
		       FAItem<TDKinematicFit>  k2) const;

      // ------------ data members -------------------------------
      double m_beam_x;  // beamspot location
      double m_beam_y;
      double m_beam_z;

      HINtuple *m_LEGammaNt;
      HIHist1D *h_ksfltsig;
      HIHist1D *h_mgg;

      HIHist1D *h_rec_before_nks;
      HIHist1D *h_rec_after_nks;
      HIHist1D *h_rec_before_fit;
      HIHist1D *h_rec_after_fit;

      HIHist1D *h_e9o25_sig;
      HIHist1D *h_e9o25_pi0;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* PPGPSIPPROC_PPGPSIPPROC_H */
