// -*- C++ -*-
#if !defined(INCLUSIVEPROC_INCLUSIVEPROC_H)
#define INCLUSIVEPROC_INCLUSIVEPROC_H
//
// Package:     <InclusiveProc>
// Module:      InclusiveProc
//
/**\class InclusiveProc InclusiveProc.h InclusiveProc/InclusiveProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      pts/9
// Created:     Tue May  1 17:28:20 CDT 2012
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

class InclusiveProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      InclusiveProc( void );                      // anal1 
      virtual ~InclusiveProc();                   // anal5 

      // ------------ member functions ---------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // methods for binding to streams (anal2-4 etc.)
      virtual ActionBase::ActionResult event( Frame& iFrame );
      //virtual ActionBase::ActionResult beginRun( Frame& iFrame);
      //virtual ActionBase::ActionResult endRun( Frame& iFrame);

      // ------------ const member functions ---------------------

      // ------------ static member functions --------------------

   protected:
      // ------------ protected member functions -----------------

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      InclusiveProc( const InclusiveProc& );

      // ------------ assignment operator(s) ---------------------
      const InclusiveProc& operator=( const InclusiveProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (InclusiveProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
     HINtuple* m_showerTuple;
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* INCLUSIVEPROC_INCLUSIVEPROC_H */
