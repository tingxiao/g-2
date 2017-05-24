// -*- C++ -*-
#if !defined(TREFFPROC_TREFFPROC_H)
#define TREFFPROC_TREFFPROC_H
//
// Package:     <LooseTrEffProc>
// Module:      LooseTrEffProc
//
/**\class LooseTrEffProc LooseTrEffProc.h LooseTrEffProc/LooseTrEffProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      pts/1
// Created:     Wed May 12 17:15:38 CDT 2010
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

class LooseTrEffProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      LooseTrEffProc( void );                      // anal1 
      virtual ~LooseTrEffProc();                   // anal5 

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
      LooseTrEffProc( const LooseTrEffProc& );

      // ------------ assignment operator(s) ---------------------
      const LooseTrEffProc& operator=( const LooseTrEffProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (LooseTrEffProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TREFFPROC_TREFFPROC_H */
