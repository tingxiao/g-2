// -*- C++ -*-
#if !defined(CHI_C1_CHI_C1_H)
#define CHI_C1_CHI_C1_H
//
// Package:     <Chi_c1>
// Module:      Chi_c1
//
/**\class Chi_c1 Chi_c1.h Chi_c1/Chi_c1.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      pts/7
// Created:     Mon May  2 13:43:15 CDT 2011
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

class Chi_c1 : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      Chi_c1( void );                      // anal1 
      virtual ~Chi_c1();                   // anal5 

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
      Chi_c1( const Chi_c1& );

      // ------------ assignment operator(s) ---------------------
      const Chi_c1& operator=( const Chi_c1& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (Chi_c1::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple;
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* CHI_C1_CHI_C1_H */
