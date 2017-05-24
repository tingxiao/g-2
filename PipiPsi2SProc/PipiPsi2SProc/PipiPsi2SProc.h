// -*- C++ -*-
#if !defined(PIPIPSI2SPROC_PIPIPSI2SPROC_H)
#define PIPIPSI2SPROC_PIPIPSI2SPROC_H
//
// Package:     <PipiPsi2SProc>
// Module:      PipiPsi2SProc
//
/**\class PipiPsi2SProc PipiPsi2SProc.h PipiPsi2SProc/PipiPsi2SProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Fri Apr  5 17:39:24 CDT 2013
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

class PipiPsi2SProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      PipiPsi2SProc( void );                      // anal1 
      virtual ~PipiPsi2SProc();                   // anal5 

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
      PipiPsi2SProc( const PipiPsi2SProc& );

      // ------------ assignment operator(s) ---------------------
      const PipiPsi2SProc& operator=( const PipiPsi2SProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (PipiPsi2SProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple;
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* PIPIPSI2SPROC_PIPIPSI2SPROC_H */
