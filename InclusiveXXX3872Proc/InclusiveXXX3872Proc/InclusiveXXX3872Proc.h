// -*- C++ -*-
#if !defined(INCLUSIVEXXX3872PROC_INCLUSIVEXXX3872PROC_H)
#define INCLUSIVEXXX3872PROC_INCLUSIVEXXX3872PROC_H
//
// Package:     <InclusiveXXX3872Proc>
// Module:      InclusiveXXX3872Proc
//
/**\class InclusiveXXX3872Proc InclusiveXXX3872Proc.h InclusiveXXX3872Proc/InclusiveXXX3872Proc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      pts/16
// Created:     Mon Apr 16 20:14:38 CDT 2012
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

class InclusiveXXX3872Proc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      InclusiveXXX3872Proc( void );                      // anal1 
      virtual ~InclusiveXXX3872Proc();                   // anal5 

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
      InclusiveXXX3872Proc( const InclusiveXXX3872Proc& );

      // ------------ assignment operator(s) ---------------------
      const InclusiveXXX3872Proc& operator=( const InclusiveXXX3872Proc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (InclusiveXXX3872Proc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* INCLUSIVEXXX3872PROC_INCLUSIVEXXX3872PROC_H */
