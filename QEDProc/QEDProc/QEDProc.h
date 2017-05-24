// -*- C++ -*-
#if !defined(QEDPROC_QEDPROC_H)
#define QEDPROC_QEDPROC_H
//
// Package:     <QEDProc>
// Module:      QEDProc
//
/**\class QEDProc QEDProc.h QEDProc/QEDProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Mon Dec 10 16:45:47 CST 2012
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

class QEDProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      QEDProc( void );                      // anal1 
      virtual ~QEDProc();                   // anal5 

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
      QEDProc( const QEDProc& );

      // ------------ assignment operator(s) ---------------------
      const QEDProc& operator=( const QEDProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (QEDProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
   HIHist1D *h_e_ee;
   HIHist1D *h_e_mumu;
   HIHist1D *h_e_pipi;

   HIHist1D *h_qcosth_ee;
   HIHist1D *h_qcosth_mumu;
   HIHist1D *h_qcosth_pipi;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* QEDPROC_QEDPROC_H */
