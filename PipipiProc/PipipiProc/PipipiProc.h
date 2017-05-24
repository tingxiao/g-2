// -*- C++ -*-
#if !defined(PIPIPIPROC_PIPIPIPROC_H)
#define PIPIPIPROC_PIPIPIPROC_H
//
// Package:     <PipipiProc>
// Module:      PipipiProc
//
/**\class PipipiProc PipipiProc.h PipipiProc/PipipiProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      pts/14
// Created:     Wed Apr  7 11:35:18 CDT 2010
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
#include "C3ccProd/CcFortranShowerCorrector.h"

// forward declarations

class PipipiProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      PipipiProc( void );                      // anal1 
      virtual ~PipipiProc();                   // anal5 

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
      PipipiProc( const PipipiProc& );

      // ------------ assignment operator(s) ---------------------
      const PipipiProc& operator=( const PipipiProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (PipipiProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple;
      CcFortranShowerCorrector* sh_corr  ;


      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* PIPIPIPROC_PIPIPIPROC_H */
