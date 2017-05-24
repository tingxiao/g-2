// -*- C++ -*-
#if !defined(PURETRTRPROC_PURETRTRPROC_H)
#define PURETRTRPROC_PURETRTRPROC_H
//
// Package:     <PureTrtrProc>
// Module:      PureTrtrProc
//
/**\class PureTrtrProc PureTrtrProc.h PureTrtrProc/PureTrtrProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Mon May 20 11:58:31 CDT 2013
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

class PureTrtrProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      PureTrtrProc( void );                      // anal1 
      virtual ~PureTrtrProc();                   // anal5 

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
      PureTrtrProc( const PureTrtrProc& );

      // ------------ assignment operator(s) ---------------------
      const PureTrtrProc& operator=( const PureTrtrProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (PureTrtrProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple;
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* PURETRTRPROC_PURETRTRPROC_H */
