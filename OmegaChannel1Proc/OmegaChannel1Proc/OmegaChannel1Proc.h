// -*- C++ -*-
#if !defined(DUMPDECAYTREEPROC_DUMPDECAYTREEPROC_H)
#define DUMPDECAYTREEPROC_DUMPDECAYTREEPROC_H
//
// Package:     <OmegaChannel1Proc>
// Module:      OmegaChannel1Proc
//
/**\class OmegaChannel1Proc OmegaChannel1Proc.h OmegaChannel1Proc/OmegaChannel1Proc.h
 
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

class OmegaChannel1Proc : public Processor
{
      // ------------ friend classses and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      OmegaChannel1Proc( void );                      // anal1 
      virtual ~OmegaChannel1Proc();                   // anal5 

      // ------------ member functions ---------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // methods for binding to streams (anal2-4 etc.)
      virtual ActionBase::ActionResult event( Frame& iFrame );
      virtual ActionBase::ActionResult beginRun( Frame& iFrame);
      virtual ActionBase::ActionResult endRun( Frame& iFrame);
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
      OmegaChannel1Proc( const OmegaChannel1Proc& );

      // ------------ assignment operator(s) ---------------------
      const OmegaChannel1Proc& operator=( const OmegaChannel1Proc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (OmegaChannel1Proc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

//      int photonInDetector;
//      int photonAlongZ1;

//      HINtuple* m_ISRPsipNtuple;

//      HIHist1D *h_rec;
//      HIHist1D *h_costh;
//      HIHist1D *h_costh_chg;
//      HIHist1D *h_costh_neut;

//      HIHist1D *h_costh_pi;
//      HIHist1D *h_costh_proton;

      double m_PassedEvents;
      double m_FailedEvents;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* DUMPDECAYTREEPROC_DUMPDECAYTREEPROC_H */
