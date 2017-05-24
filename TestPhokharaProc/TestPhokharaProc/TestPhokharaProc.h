// -*- C++ -*-
#if !defined(TESTPHOKHARAPROC_TESTPHOKHARAPROC_H)
#define TESTPHOKHARAPROC_TESTPHOKHARAPROC_H
//
// Package:     <TestPhokharaProc>
// Module:      TestPhokharaProc
//
/**\class TestPhokharaProc TestPhokharaProc.h TestPhokharaProc/TestPhokharaProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Thu Jul 12 12:52:17 CDT 2012
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

class TestPhokharaProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      TestPhokharaProc( void );                      // anal1 
      virtual ~TestPhokharaProc();                   // anal5 

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
      TestPhokharaProc( const TestPhokharaProc& );

      // ------------ assignment operator(s) ---------------------
      const TestPhokharaProc& operator=( const TestPhokharaProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (TestPhokharaProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple;

/*
   HIHist1D *h_ns;
   HIHist1D *h_e;
   HIHist1D *h_emax;
   HIHist1D *h_e_costh;
   HIHist1D *h_ns_fsr;
   HIHist1D *h_e_fsr;
   HIHist1D *h_e_costh_fsr;
   HIHist1D *h_e_costh_count;
   HIHist1D *h_mpipi;
*/

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* TESTPHOKHARAPROC_TESTPHOKHARAPROC_H */
