// -*- C++ -*-
#if !defined(DUMPDECAYTREEPROC_DUMPDECAYTREEPROC_H)
#define DUMPDECAYTREEPROC_DUMPDECAYTREEPROC_H
//
// Package:     <DumpDecayTreeProc>
// Module:      DumpDecayTreeProc
//
/**\class DumpDecayTreeProc DumpDecayTreeProc.h DumpDecayTreeProc/DumpDecayTreeProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      Hanna Mahlke-Krueger
// Created:     Mon Jun 18 16:02:36 EDT 2001
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

class DumpDecayTreeProc : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      DumpDecayTreeProc( void );                      // anal1 
      virtual ~DumpDecayTreeProc();                   // anal5 

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
      //virtual ActionBase::ActionResult geometry( Frame& iFrame);
      //virtual ActionBase::ActionResult hardware( Frame& iFrame);
      //virtual ActionBase::ActionResult user( Frame& iFrame);

      // ------------ const member functions ---------------------

      // ------------ static member functions --------------------

   protected:
      // ------------ protected member functions -----------------

      // ------------ protected const member functions -----------

   private:
      // ------------ Constructors and destructor ----------------
      DumpDecayTreeProc( const DumpDecayTreeProc& );

      // ------------ assignment operator(s) ---------------------
      const DumpDecayTreeProc& operator=( const DumpDecayTreeProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (DumpDecayTreeProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

   HIHist1D *h_ns;
   HIHist1D *h_e;
   HIHist1D *h_emax;
   HIHist1D *h_e_costh;
   HIHist1D *h_ns_fsr;
   HIHist1D *h_e_fsr;
   HIHist1D *h_e_costh_fsr;
   HIHist1D *h_e_costh_count;
   HIHist1D *h_mpipi;
   HIHist1D * h_pimass;
   HIHist1D * h_mumass;

   HIHist1D *h_fjpsipi;
   HIHist1D *h_fmumu;
   HIHist1D *h_fpipi;
   HIHist1D *h_fpipimumu;
   HIHist2D *h_fjpsipiplus2_fpipi2;
   HIHist2D *h_fjpsipiplus2_fjpsipiminus2;

      
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* DUMPDECAYTREEPROC_DUMPDECAYTREEPROC_H */
