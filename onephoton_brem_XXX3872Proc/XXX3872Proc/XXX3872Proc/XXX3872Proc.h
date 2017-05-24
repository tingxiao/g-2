// -*- C++ -*-
#if !defined(XXX3872PROC_XXX3872PROC_H)
#define XXX3872PROC_XXX3872PROC_H
//
// Package:     <XXX3872Proc>
// Module:      XXX3872Proc
//
/**\class XXX3872Proc XXX3872Proc.h XXX3872Proc/XXX3872Proc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      pts/13
// Created:     Tue Feb 15 11:42:42 CST 2011
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

class XXX3872Proc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      XXX3872Proc( void );                      // anal1 
      virtual ~XXX3872Proc();                   // anal5 

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
      XXX3872Proc( const XXX3872Proc& );

      // ------------ assignment operator(s) ---------------------
      const XXX3872Proc& operator=( const XXX3872Proc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (XXX3872Proc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* XXX3872PROC_XXX3872PROC_H */
