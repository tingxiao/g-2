// -*- C++ -*-
#if !defined(Z3900PROC_Z3900PROC_H)
#define Z3900PROC_Z3900PROC_H
//
// Package:     <Z3900Proc>
// Module:      Z3900Proc
//
/**\class Z3900Proc Z3900Proc.h Z3900Proc/Z3900Proc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Tue Mar 26 11:49:17 CDT 2013
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

class Z3900Proc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      Z3900Proc( void );                      // anal1 
      virtual ~Z3900Proc();                   // anal5 

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
      Z3900Proc( const Z3900Proc& );

      // ------------ assignment operator(s) ---------------------
      const Z3900Proc& operator=( const Z3900Proc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (Z3900Proc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple;
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* Z3900PROC_Z3900PROC_H */
