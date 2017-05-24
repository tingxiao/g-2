// -*- C++ -*-
#if !defined(TWOTRACKSISRPROC_TWOTRACKSISRPROC_H)
#define TWOTRACKSISRPROC_TWOTRACKSISRPROC_H
//
// Package:     <TwoTracksISRProc>
// Module:      TwoTracksISRProc
//
/**\class TwoTracksISRProc TwoTracksISRProc.h TwoTracksISRProc/TwoTracksISRProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Ting Xiao
// Created:     Fri Jun 26 18:02:00 EDT 2009
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

// forward declarations

class TwoTracksISRProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      TwoTracksISRProc( void );                      // anal1 
      virtual ~TwoTracksISRProc();                   // anal5 

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

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      TwoTracksISRProc( const TwoTracksISRProc& );

      // ------------ assignment operator(s) ---------------------
      const TwoTracksISRProc& operator=( const TwoTracksISRProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (TwoTracksISRProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple        ;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TWOTRACKSISRPROC_TWOTRACKSISRPROC_H */
