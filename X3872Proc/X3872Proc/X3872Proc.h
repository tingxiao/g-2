// -*- C++ -*-
#if !defined(X3872PROC_X3872PROC_H)
#define X3872PROC_X3872PROC_H
//
// Package:     <X3872Proc>
// Module:      X3872Proc
//
/**\class X3872Proc X3872Proc.h X3872Proc/X3872Proc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      tty7
// Created:     Thu Dec  2 12:26:42 CST 2010
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

class X3872Proc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      X3872Proc( void );                      // anal1 
      virtual ~X3872Proc();                   // anal5 

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
      X3872Proc( const X3872Proc& );

      // ------------ assignment operator(s) ---------------------
      const X3872Proc& operator=( const X3872Proc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (X3872Proc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* X3872PROC_X3872PROC_H */
