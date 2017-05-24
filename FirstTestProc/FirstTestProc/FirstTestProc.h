// -*- C++ -*-
#if !defined(FIRSTTESTPROC_FIRSTTESTPROC_H)
#define FIRSTTESTPROC_FIRSTTESTPROC_H
//
// Package:     <FirstTestProc>
// Module:      FirstTestProc
//
/**\class FirstTestProc FirstTestProc.h FirstTestProc/FirstTestProc.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      tty7
// Created:     Wed Jun  3 16:52:23 CDT 2009
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
#include "FrameAccess/FAInserter.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"
#include "HistogramInterface/HIHist1D.h"


// forward declarations

class FirstTestProc : public Processor
{
      // ------------ friend classes and functions --------------

   public:
      // ------------ constants, enums and typedefs --------------

      // ------------ Constructors and destructor ----------------
      FirstTestProc( void );                      // anal1 
      virtual ~FirstTestProc();                   // anal5 

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
      FirstTestProc( const FirstTestProc& );

      // ------------ assignment operator(s) ---------------------
      const FirstTestProc& operator=( const FirstTestProc& );

      // ------------ private member functions -------------------
      void bind( 
         ActionBase::ActionResult (FirstTestProc::*iMethod)( Frame& ),
	      const Stream::Type& iStream );

      // ------------ private const member functions -------------

      // ------------ data members -------------------------------
      HIHist1D* m_Echarge;
      HIHist1D* m_Eshower;
      HIHist1D* m_Eunshower;
      HIHist1D* m_Echarge1;
      HIHist1D* m_Echarge2;
      HIHist1D* m_Eshower1;
      HIHist1D* m_Eshower2;

      // ------------ static data members ------------------------

};

// inline function definitions

#endif /* FIRSTTESTPROC_FIRSTTESTPROC_H */
