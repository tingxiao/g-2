// -*- C++ -*-
#if !defined(MISSINGMASSPROC_MISSINGMASSPROC_H)
#define MISSINGMASSPROC_MISSINGMASSPROC_H
//
// Package:     <MissingMassProc>
// Module:      MissingMassProc
//
/**\class MissingMassProc MissingMassProc.h MissingMassProc/MissingMassProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      pts/1
// Created:     Mon May 24 14:13:49 CDT 2010
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

class MissingMassProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      MissingMassProc( void );                      // anal1 
      virtual ~MissingMassProc();                   // anal5 

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
      MissingMassProc( const MissingMassProc& );

      // ------------ assignment operator(s) ---------------------
      const MissingMassProc& operator=( const MissingMassProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (MissingMassProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* MISSINGMASSPROC_MISSINGMASSPROC_H */
