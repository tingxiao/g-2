#if !defined(C3CCPROD_CCEVENTSUMMARYPROXY_H)
#define C3CCPROD_CCEVENTSUMMARYPROXY_H
// -*- C++ -*-
//
// Package:     C3ccProd
// Module:      CcEventSummaryProxy
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Thu Feb 11 16:10:20 EST 1999
// $Id: CcEventSummaryProxy.h,v 1.2 2001/10/26 21:57:27 bkh Exp $
//
// Revision history
//
// $Log: CcEventSummaryProxy.h,v $
// Revision 1.2  2001/10/26 21:57:27  bkh
// Use beam energy from right place now
//
// Revision 1.1.1.1  1999/07/19 15:27:30  bkh
// imported C3ccProd sources
//
// Revision 1.1.1.1  1999/05/24 20:10:10  bkh
// imported C3ccProd sources
//
// Revision 1.1  1999/02/12 22:45:55  bkh
// New Cc Event Summary info for Lvl3, Pass1
//
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "C3cc/CcEventSummary.h"
#include "FrameAccess/FAItem.h"
#include "BeamEnergy/BeamEnergy.h"

// forward declarations

class CcEventSummaryProxy : public ProxyBindableTemplate< CcEventSummary >
{
      // friend classes and functions
   public:
      // constants, enums and typedefs
      typedef CcEventSummary value_type;

      // Constructors and destructor
      CcEventSummaryProxy();
      virtual ~CcEventSummaryProxy();
      // member functions

      void boundMethodStartRun( const Record& iRecord );

      // const member functions
      // static member functions
   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );
      // protected const member functions
   private:
      // Constructors and destructor
      CcEventSummaryProxy( const CcEventSummaryProxy& );
      // assignment operator(s)
      const CcEventSummaryProxy& operator=( const CcEventSummaryProxy& );
      // private member functions
      //this function has already been written for you
      void bind(
		void (CcEventSummaryProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );
      // private const member functions
      // data members
      value_type* m_CcEventSummary ;
      FAItem< BeamEnergy > m_eBeam ;
      // static data members
};

// inline function definitions

#endif /* C3CCPROD_CCEVENTSUMMARYPROXY_H */
