#if !defined(C3CCPROD_C3CCPROD_H)
#define C3CCPROD_C3CCPROD_H
// -*- C++ -*-
//
// Package:     C3ccProd
// Module:      C3ccProd
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Fri May 21 11:41:34 EDT 1999
// $Id: C3ccProd.h,v 1.5 2008/02/19 17:21:41 bkh Exp $
//
// Revision history
//
// $Log: C3ccProd.h,v $
// Revision 1.5  2008/02/19 17:21:41  bkh
// Separate Endcap energy fix from mc smearing & error-inflation fix
//
// Revision 1.4  2007/03/16 15:02:21  bkh
// Parameter-controlled increase in sigmas, smearing in MC
//
// Revision 1.3  2003/07/30 20:45:37  bkh
// Throw exception if no rungains or hotlist unless new parameter RequireRunGainsHotList is explicitly set to false
//
// Revision 1.2  2002/06/13 19:57:09  bkh
// Institute parameter control over use of event vertex
// (never mind that the event vertex object does not exist yet...
// not to worry, only structural code is set up and this will compile.)
//
// Revision 1.1.1.1  1999/07/19 15:27:30  bkh
// imported C3ccProd sources
//
// Revision 1.1.1.1  1999/05/24 20:10:10  bkh
// imported C3ccProd sources
//
//

// system include files

// user include files
#include "Processor/Producer.h"
#include "ToolBox/HistogramPackage.h"
#include "CommandPattern/Parameter.h"

// forward declarations

class C3ccProd : public Producer
{
      // ------------ friend classses and functions ---------------
   public:
      // ------------ constants, enums and typedefs ---------------
      // ------------ Constructors and destructor -----------------
      C3ccProd( void );                      // anal1 
      virtual ~C3ccProd();                   // anal5 

      // ------------ member functions ----------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( TBHistoManager& );                  

      // ------------ const member functions ----------------------

      DABoolean useEventVertex() const { return m_useEventVertex.value(); } ;
      DABoolean requireRunGainsHotList() const {return m_requireRunGainsHotList.value(); } ;
      DABoolean fixShowers() const {return m_fixShowers.value(); } ;
      DABoolean fixEndcap() const {return m_fixEndcap.value(); } ;

      // ------------ static member functions ---------------------
   protected:
      // ------------ protected member functions ------------------
      // ------------ protected const member functions ------------
   private:
      // ------------ Constructors and destructor -----------------
      C3ccProd( const C3ccProd& );
      // ------------ assignment operator(s) ----------------------
      const C3ccProd& operator=( const C3ccProd& );
      // ------------ private member functions --------------------
      // ------------ private const member functions --------------
      // ------------ data members --------------------------------

      Parameter< DABoolean >  m_useEventVertex ;
      Parameter< DABoolean >  m_requireRunGainsHotList ;
      Parameter< DABoolean >  m_fixShowers ;
      Parameter< DABoolean >  m_fixEndcap ;
      // ------------ static data members -------------------------
};

// inline function definitions

#endif /* C3CCPROD_C3CCPROD_H */
