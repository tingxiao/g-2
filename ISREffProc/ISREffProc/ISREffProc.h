// -*- C++ -*-
#if !defined(ISREFFPROC_ISREFFPROC_H)
#define ISREFFPROC_ISREFFPROC_H
//
// Package:     <ISREffProc>
// Module:      ISREffProc
//
/**\class ISREffProc ISREffProc.h ISREffProc/ISREffProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Tue May  5 15:32:13 CDT 2015
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

class ISREffProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      ISREffProc( void );                      // anal1 
      virtual ~ISREffProc();                   // anal5 

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
      ISREffProc( const ISREffProc& );

      // ------------ assignment operator(s) ---------------------
      const ISREffProc& operator=( const ISREffProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (ISREffProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* ISREFFPROC_ISREFFPROC_H */
