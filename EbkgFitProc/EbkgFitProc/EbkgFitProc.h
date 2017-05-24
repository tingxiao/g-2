// -*- C++ -*-
#if !defined(FITPROC_FITPROC_H)
#define FITPROC_FITPROC_H
//
// Package:     <EbkgFitProc>
// Module:      EbkgFitProc
//
/**\class EbkgFitProc EbkgFitProc.h EbkgFitProc/EbkgFitProc.h
 
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

class EbkgFitProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      EbkgFitProc( void );                      // anal1 
      virtual ~EbkgFitProc();                   // anal5 

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
      EbkgFitProc( const EbkgFitProc& );

      // ------------ assignment operator(s) ---------------------
      const EbkgFitProc& operator=( const EbkgFitProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (EbkgFitProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------

      HINtuple* m_showerTuple;
      CcFortranShowerCorrector* sh_corr  ;
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* FITPROC_FITPROC_H */
