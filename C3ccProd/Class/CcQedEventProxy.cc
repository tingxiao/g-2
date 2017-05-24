// -*- C++ -*-
//
// Package:     C3ccProd
// Module:      CcQedEventProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Thu Feb 11 17:17:52 EST 1999
// $Id: CcQedEventProxy.cc,v 1.5 2003/02/05 19:04:55 bkh Exp $
//
// Revision history
//
// $Log: CcQedEventProxy.cc,v $
// Revision 1.5  2003/02/05 19:04:55  bkh
// Cache bfield object and send to CcQedEvent
//
// Revision 1.4  2001/07/25 21:53:41  bkh
// Get beam energy correctly
//
// Revision 1.3  2000/04/17 20:00:46  bkh
// Elim checks of ptrs after new
//
// Revision 1.2  1999/12/31 22:30:18  bkh
// Eliminate use of obsolete valid()
// Only ignore channels with "noisy" pedestal, not all "bad"
// Replace "bad" gains with nearest good gains
//
// Revision 1.1.1.1  1999/07/19 15:27:31  bkh
// imported C3ccProd sources
//
// Revision 1.1.1.1  1999/05/24 20:10:10  bkh
// imported C3ccProd sources
//
// Revision 1.1  1999/02/12 22:46:00  bkh
// New Cc Event Summary info for Lvl3, Pass1
//
//

#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

#include "C3ccProd/CcQedEventProxy.h"

#include "C3cc/CcShowerAttributes.h" 

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kReport = "C3ccProd.CcQedEventProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
CcQedEventProxy::CcQedEventProxy()
   : m_CcQedEvent( 0 )
{
   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   bind( &CcQedEventProxy::boundMethodStartRun, Stream::kStartRun );
}

// CcQedEventProxy::CcQedEventProxy( const CcQedEventProxy& iproxy )
// {
//   *this = iproxy;
// }

CcQedEventProxy::~CcQedEventProxy()
{
   delete m_CcQedEvent ;
}

//
// member functions
//
void
CcQedEventProxy::invalidateCache()
{
   delete m_CcQedEvent ;
   m_CcQedEvent = 0 ;
}

const CcQedEventProxy::value_type*
CcQedEventProxy::faultHandler( const Record&  iRecord ,
			       const DataKey& iKey      )
{
   assert( 0 == m_CcQedEvent );

   FATable< CcShowerAttributes > shAt ; 
   extract( iRecord, shAt ); 

   m_CcQedEvent = new CcQedEvent( shAt,
				  m_eBeam->value(),
				  m_bField->BField().z() );

   return m_CcQedEvent ;
}

//
// const member functions
//

//
// static member functions
//

void
CcQedEventProxy::boundMethodStartRun( const Record& iRecord )
{
   report( DEBUG, kReport) <<"BoundMethodStartRun: " 
			   << iRecord.stream().value() << endl;
   extract( iRecord, m_eBeam ) ; 
   extract( iRecord, m_bField ) ; 
}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< CcQedEvent >;

PROXY_BIND_METHOD( CcQedEventProxy )
//-----------------------------------------------


