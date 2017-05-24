#if !defined(C3CCPROD_CCQEDEVENTPROXY_H)
#define C3CCPROD_CCQEDEVENTPROXY_H
// -*- C++ -*-
//
// Package:     C3ccProd
// Module:      CcQedEventProxy
// 
// Description:
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Thu Feb 11 17:17:51 EST 1999
// $Id: CcQedEventProxy.h,v 1.4 2003/02/05 19:04:44 bkh Exp $
//
// Revision history
//
// $Log: CcQedEventProxy.h,v $
// Revision 1.4  2003/02/05 19:04:44  bkh
// Cache bfield object
//
// Revision 1.3  2001/08/31 22:44:53  bkh
// Use BeamEnergy now
//
// Revision 1.2  2001/07/25 21:53:36  bkh
// Get beam energy correctly
//
// Revision 1.1.1.1  1999/07/19 15:27:30  bkh
// imported C3ccProd sources
//
// Revision 1.1.1.1  1999/05/24 20:10:10  bkh
// imported C3ccProd sources
//
// Revision 1.1  1999/02/12 22:45:56  bkh
// New Cc Event Summary info for Lvl3, Pass1
//
//

// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "C3cc/CcQedEvent.h"
#include "FrameAccess/FAItem.h"
#include "BeamEnergy/BeamEnergy.h"
#include "MagField/MagneticField.h"

// forward declarations

class CcQedEventProxy : public ProxyBindableTemplate< CcQedEvent >
{
      // friend classes and functions
   public:
      // constants, enums and typedefs
      typedef CcQedEvent value_type;

      // Constructors and destructor
      CcQedEventProxy();
      virtual ~CcQedEventProxy();

      void boundMethodStartRun( const Record& iRecord );

      // member functions
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
      CcQedEventProxy( const CcQedEventProxy& );
      // assignment operator(s)
      const CcQedEventProxy& operator=( const CcQedEventProxy& );
      // private member functions
      // private const member functions

      //this function has already been written for you
      void bind(
		void (CcQedEventProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );

      // data members
      value_type* m_CcQedEvent ;
      FAItem< BeamEnergy    > m_eBeam ;
      FAItem< MagneticField > m_bField ;

      // static data members
};

// inline function definitions

#endif /* C3CCPROD_CCQEDEVENTPROXY_H */
