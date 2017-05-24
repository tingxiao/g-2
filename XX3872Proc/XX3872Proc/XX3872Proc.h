// -*- C++ -*-
#if !defined(XX3872PROC_XX3872PROC_H)
#define XX3872PROC_XX3872PROC_H
//
// Package:     <XX3872Proc>
// Module:      XX3872Proc
//
/**\class XX3872Proc XX3872Proc.h XX3872Proc/XX3872Proc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      pts/13
// Created:     Fri Feb  4 10:21:00 CST 2011
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

class XX3872Proc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      XX3872Proc( void );                      // anal1 
      virtual ~XX3872Proc();                   // anal5 

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
      XX3872Proc( const XX3872Proc& );

      // ------------ assignment operator(s) ---------------------
      const XX3872Proc& operator=( const XX3872Proc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (XX3872Proc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple;
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* XX3872PROC_XX3872PROC_H */
