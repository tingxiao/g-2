// -*- C++ -*-
//
// Package:     C3ccProd
// Module:      CcEventSummaryProxy
// 
// Description: 
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Thu Feb 11 16:10:21 EST 1999
// $Id: CcEventSummaryProxy.cc,v 1.4 2001/10/26 21:57:33 bkh Exp $
//
// Revision history
//
// $Log: CcEventSummaryProxy.cc,v $
// Revision 1.4  2001/10/26 21:57:33  bkh
// Use beam energy from right place now
//
// Revision 1.3  2000/04/17 20:00:45  bkh
// Elim checks of ptrs after new
//
// Revision 1.2  1999/12/31 22:30:16  bkh
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
// Revision 1.1  1999/02/12 22:45:59  bkh
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
#include "C3ccProd/CcEventSummaryProxy.h"

#include "C3cc/CcEnergyHit.h"
#include "C3cc/CcShowerAttributes.h"
#include "C3cc/CcQedEvent.h"

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
static const char* const kReport = "C3ccProd.CcEventSummaryProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
CcEventSummaryProxy::CcEventSummaryProxy()
   : m_CcEventSummary( 0 )
{
   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   bind( &CcEventSummaryProxy::boundMethodStartRun, Stream::kStartRun );
}

// CcEventSummaryProxy::CcEventSummaryProxy( const CcEventSummaryProxy& iproxy )
// {
//   *this = iproxy;
// }

CcEventSummaryProxy::~CcEventSummaryProxy()
{
   delete m_CcEventSummary ;
}

//
// member functions
//
void
CcEventSummaryProxy::invalidateCache()
{
   delete m_CcEventSummary ;
   m_CcEventSummary = 0 ;
}

const CcEventSummaryProxy::value_type*
CcEventSummaryProxy::faultHandler( const Record& iRecord,
				   const DataKey& iKey )
{
   assert( 0 == m_CcEventSummary );

   FATable< CcEnergyHit > hits ; 
   extract( iRecord, hits ); 

   FATable< CcShowerAttributes > shAt ; 
   extract( iRecord, shAt ); 

   FAItem< CcQedEvent > qedEvt ; 
   extract( iRecord, qedEvt ); 

   m_CcEventSummary = new CcEventSummary( hits, shAt, m_eBeam->value(), 
					  *qedEvt );
   
   return m_CcEventSummary ;
}

void
CcEventSummaryProxy::boundMethodStartRun( const Record& iRecord )
{
   report( DEBUG, kReport) <<"BoundMethodStartRun: " 
			   << iRecord.stream().value() << endl;
   extract( iRecord, m_eBeam ) ; 
}

//
// const member functions
//

//
// static member functions
//

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< CcEventSummary >;

PROXY_BIND_METHOD( CcEventSummaryProxy )
//-----------------------------------------------


