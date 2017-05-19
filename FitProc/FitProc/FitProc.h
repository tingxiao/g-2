// -*- C++ -*-
#if !defined(FITPROC_FITPROC_H)
#define FITPROC_FITPROC_H
//
// Package:     <FitProc>
// Module:      FitProc
//
/**\class FitProc FitProc.h FitProc/FitProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      pts/4
// Created:     Sun Sep 27 18:46:29 CDT 2009
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

class FitProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      FitProc( void );                      // anal1 
      virtual ~FitProc();                   // anal5 

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
      FitProc( const FitProc& );

      // ------------ assignment operator(s) ---------------------
      const FitProc& operator=( const FitProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (FitProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_showerTuple;
      CcFortranShowerCorrector* sh_corr  ;
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* FITPROC_FITPROC_H */
