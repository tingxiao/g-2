#if !defined(C3CCPROD_CCSHOWERATTRIBUTESPROXY_H)
#define C3CCPROD_CCSHOWERATTRIBUTESPROXY_H
// -*- C++ -*-
//
// Package:     C3ccProd
// Module:      CcShowerAttributesProxy
// 
// Description: Proxy to "handle" CcShowerAttributes
//
// Usage:
//
// Author:      Brian K. Heltsley
// Created:     Thu May 28 15:02:22 EDT 1998
// $Id: CcShowerAttributesProxy.h,v 1.7 2004/11/30 21:15:31 cdj Exp $
//
// Revision history
//
// $Log: CcShowerAttributesProxy.h,v $
// Revision 1.7  2004/11/30 21:15:31  cdj
// use CcFortranShowerCorrector to implement new CcShowerAttributes interface
//
// Revision 1.6  2003/09/22 18:31:44  cdj
// removed the need to bind to a beginrun change in CcShowerAttributesProxy (avoids a bad 'feature' in Suez that occurs when processing two MC files with the same run number back to back)
//
// Revision 1.5  2003/07/30 20:45:38  bkh
// Throw exception if no rungains or hotlist unless new parameter RequireRunGainsHotList is explicitly set to false
//
// Revision 1.4  2002/06/13 19:57:09  bkh
// Institute parameter control over use of event vertex
// (never mind that the event vertex object does not exist yet...
// not to worry, only structural code is set up and this will compile.)
//
// Revision 1.3  2002/05/01 21:16:34  bkh
// Pass in hot list if present
//
// Revision 1.2  2001/07/23 17:43:29  bkh
// Put in access to run gains if they are there
//
// Revision 1.1.1.1  1999/07/19 15:27:30  bkh
// imported C3ccProd sources
//
// Revision 1.1.1.1  1999/05/24 20:10:10  bkh
// imported C3ccProd sources
//
// Revision 1.1  1998/07/14 22:09:51  bkh
// Makes a producer library now for CcShowerAttributesProxy
//
// Revision 1.1.1.1  1998/07/03 19:01:03  bkh
// import Ccfc sources
//
//

// system include files
#include <memory>

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "C3cc/CcShowerAttributes.h"
#include "C3ccProd/C3ccProd.h"
#include "CommandPattern/Parameter.h"

class CcShowerCorrectorBase;

// forward declarations
#if !( defined(LOOSES_NESTED_CLASS_DECLARATION_BUG) && defined(FRAMEACCESS_FAPTRTABLE_H) )
template < class T > class FAPtrTable ;
#endif /* LOOSES_NESTED_CLASS_DECLARATION_BUG && FRAMEACCESS_FAPTRTABLE_H */


class CcShowerAttributesProxy :  public ProxyBindableTemplate< FAPtrTable< CcShowerAttributes > >
{
      // friend classes and functions
   public:
      // constants, enums and typedefs
      typedef FAPtrTable< CcShowerAttributes > value_type ;

      // Constructors and destructor
      CcShowerAttributesProxy( const C3ccProd& aProd );
      virtual ~CcShowerAttributesProxy();

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
      CcShowerAttributesProxy( const CcShowerAttributesProxy& );

      // assignment operator(s)
      const CcShowerAttributesProxy& operator=( const CcShowerAttributesProxy& );

      // private member functions
      // private const member functions
      void bind(
                void (CcShowerAttributesProxy::*iMethod)( const Record& ),
                const Stream::Type& iStream );


      // data members
      value_type* m_ptrTable ;
      auto_ptr<CcShowerCorrectorBase> m_corrector;

      const C3ccProd& m_prod ;

      // static data members
};

// inline function definitions

#endif /* C3CCPROD_CCSHOWERATTRIBUTESPROXY_H */
