// -*- C++ -*-
#if !defined(ETAPI0JPSIPROC_ETAPI0JPSIPROC_H)
#define ETAPI0JPSIPROC_ETAPI0JPSIPROC_H
//
// Package:     <EtaPi0JpsiProc>
// Module:      EtaPi0JpsiProc
//
/**\class EtaPi0JpsiProc EtaPi0JpsiProc.h EtaPi0JpsiProc/EtaPi0JpsiProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Fri Apr  5 11:30:52 CDT 2013
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

class EtaPi0JpsiProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      EtaPi0JpsiProc( void );                      // anal1 
      virtual ~EtaPi0JpsiProc();                   // anal5 

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
      EtaPi0JpsiProc( const EtaPi0JpsiProc& );

      // ------------ assignment operator(s) ---------------------
      const EtaPi0JpsiProc& operator=( const EtaPi0JpsiProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (EtaPi0JpsiProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple;
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* ETAPI0JPSIPROC_ETAPI0JPSIPROC_H */
