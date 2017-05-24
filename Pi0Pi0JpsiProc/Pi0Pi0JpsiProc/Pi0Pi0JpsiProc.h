// -*- C++ -*-
#if !defined(PI0PI0JPSIPROC_PI0PI0JPSIPROC_H)
#define PI0PI0JPSIPROC_PI0PI0JPSIPROC_H
//
// Package:     <Pi0Pi0JpsiProc>
// Module:      Pi0Pi0JpsiProc
//
/**\class Pi0Pi0JpsiProc Pi0Pi0JpsiProc.h Pi0Pi0JpsiProc/Pi0Pi0JpsiProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Wed Mar 27 18:55:25 CDT 2013
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

class Pi0Pi0JpsiProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      Pi0Pi0JpsiProc( void );                      // anal1 
      virtual ~Pi0Pi0JpsiProc();                   // anal5 

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
      Pi0Pi0JpsiProc( const Pi0Pi0JpsiProc& );

      // ------------ assignment operator(s) ---------------------
      const Pi0Pi0JpsiProc& operator=( const Pi0Pi0JpsiProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (Pi0Pi0JpsiProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HINtuple* m_showerTuple;
      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* PI0PI0JPSIPROC_PI0PI0JPSIPROC_H */
