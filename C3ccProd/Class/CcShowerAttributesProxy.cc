// -*- C++ -*-
//
// Package:     C3ccProd
// Module:      CcShowerAttributesProxy
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Thu May 28 15:02:23 EDT 1998
// $Id: CcShowerAttributesProxy.cc,v 1.21 2008/02/19 17:21:42 bkh Exp $
//
// Revision history
//
// $Log: CcShowerAttributesProxy.cc,v $
// Revision 1.21  2008/02/19 17:21:42  bkh
// Separate Endcap energy fix from mc smearing & error-inflation fix
//
// Revision 1.20  2007/03/16 15:02:22  bkh
// Parameter-controlled increase in sigmas, smearing in MC
//
// Revision 1.19  2004/11/30 21:15:31  cdj
// use CcFortranShowerCorrector to implement new CcShowerAttributes interface
//
// Revision 1.18  2003/09/22 18:31:46  cdj
// removed the need to bind to a beginrun change in CcShowerAttributesProxy (avoids a bad 'feature' in Suez that occurs when processing two MC files with the same run number back to back)
//
// Revision 1.17  2003/08/01 21:22:29  bkh
// Use EventVertex as shower origin if requested by parameter setting
//
// Revision 1.16  2003/07/30 20:45:41  bkh
// Throw exception if no rungains or hotlist unless new parameter RequireRunGainsHotList is explicitly set to false
//
// Revision 1.15  2002/06/13 19:57:15  bkh
// Institute parameter control over use of event vertex
// (never mind that the event vertex object does not exist yet...
// not to worry, only structural code is set up and this will compile.)
//
// Revision 1.14  2002/05/01 21:24:49  bkh
// Add one message per job if hot list or run gains are being used
//
// Revision 1.13  2002/05/01 21:16:40  bkh
// Pass in hot list if present
//
// Revision 1.12  2002/03/26 22:18:18  bkh
// optimize by caching end() iterator
//
// Revision 1.11  2002/03/21 19:29:12  bkh
// Accommodate changes in rowsums
//
// Revision 1.10  2001/09/02 20:22:21  bkh
// Suppress warning until run corrections are ready
//
// Revision 1.9  2001/07/24 16:41:30  bkh
// Extract DBEventHeader from event where it resides
//
// Revision 1.8  2001/07/23 17:43:35  bkh
// Put in access to run gains if they are there
//
// Revision 1.7  2001/05/24 21:15:38  bkh
// Detect if MC or not and pass flag
//
// Revision 1.6  2001/05/17 19:50:18  bkh
// Add dummy argument to constructor of shower attributes
//
// Revision 1.5  2001/04/04 17:24:58  bkh
// Make Error matrix on origin 4x4 not 3x3
//
// Revision 1.4  2000/04/17 20:00:47  bkh
// Elim checks of ptrs after new
//
// Revision 1.3  1999/12/31 22:30:19  bkh
// Eliminate use of obsolete valid()
// Only ignore channels with "noisy" pedestal, not all "bad"
// Replace "bad" gains with nearest good gains
//
// Revision 1.2  1999/09/03 20:29:53  bkh
// Initialize error matrix on vertex with zeros
//
// Revision 1.1.1.1  1999/07/19 15:27:31  bkh
// imported C3ccProd sources
//
// Revision 1.1.1.1  1999/05/24 20:10:10  bkh
// imported C3ccProd sources
//
// Revision 1.3  1998/10/15 17:41:42  bkh
// eliminate secondary id's
//
// Revision 1.2  1998/07/17 18:54:30  bkh
// Add cellid of biggest crystal, also assumed origin of photon
//
// Revision 1.1  1998/07/14 22:10:07  bkh
// Makes a producer library now for CcShowerAttributesProxy
//
// Revision 1.1.1.1  1998/07/03 19:01:05  bkh
// import Ccfc sources
//
//

#include "Experiment/Experiment.h"

// system include files
#include <assert.h>

#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <map>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"
#include "FrameAccess/FAPtrTable.h"

#include "C3cc/CcBasicShowerAttsArg.h"
#include "C3cc/CcShowerAttributes.h"
#include "C3ccProd/CcShowerAttributesProxy.h"

#include "CLHEP/Geometry/Point3D.h"
#include "CLHEP/Matrix/SymMatrix.h"

#include "CleoDB/DBEventHeader.h"

#include "C3cc/CcRunGain.h"
#include "C3ccProd/CcFortranShowerCorrector.h"

#include "EventVertex/EventVertex.h"

#include "DAException/DAException.h"

#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD

// STL classes
#include <map>

//
// constants, enums and typedefs
//

static const char* const kReport = "C3ccProd.CcShowerAttributesProxy" ;

//
// static data member definitions
//

//
// constructors and destructor
//
CcShowerAttributesProxy::CcShowerAttributesProxy( const C3ccProd& aProd ) : 
   m_ptrTable( new value_type ) ,
   m_corrector( new CcFortranShowerCorrector ),
   m_prod    ( aProd )
{
}

// CcShowerAttributesProxy::CcShowerAttributesProxy( const CcShowerAttributesProxy& iproxy )
// {
//   *this = iproxy;
// }

CcShowerAttributesProxy::~CcShowerAttributesProxy()
{
//
// have to delete contents of FAPtrTable
//
   if ( 0 != m_ptrTable ) {
      (*m_ptrTable).eraseAll() ;
      delete m_ptrTable ;
   }
}

//
// assignment operators
//
// const CcShowerAttributesProxy& CcShowerAttributesProxy::operator=( const CcShowerAttributesProxy& iproxy )
// {
//   if( this != &iproxy ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iproxy );
//   }
//
//   return *this;
// }

//
// member functions
//
void
CcShowerAttributesProxy::invalidateCache()
{
   if ( 0 != m_ptrTable ) {
      (*m_ptrTable).eraseAll() ;
   }
}

const CcShowerAttributesProxy::value_type*
CcShowerAttributesProxy::faultHandler( const Record& iRecord,
				       const DataKey& iKey )
{
// ---------- sample implementation ---------------------

   // be assertive: table should be empty 
   // else it's a programming error
   assert( 0 == (*m_ptrTable).size() );

   // ---------- fill FAPtrTable with new items ----------------

   FAItem< DBEventHeader > dbHead ;
   extract( iRecord,       dbHead ) ;

   const DABoolean isMC ( dbHead->monteCarlo() ) ;

   const DABoolean lfixit ( m_prod.fixShowers() ) ;

   const DABoolean lfixend ( m_prod.fixEndcap() ) ;

   // get the table out of the dictionary
   FATable< CcBasicShowerAttsArg > basic   ;
   extract( iRecord,               basic ) ; 

   HepPoint3D   origin  ( 0,0,0 ) ;
   HepSymMatrix errMatO ( 3 , 0 ) ;

   if( m_prod.useEventVertex() )
   {
      FAItem< EventVertex > iVtx ;
      extract( iRecord,     iVtx ) ;
      origin  = iVtx->vertexPosition() ;
      errMatO = iVtx->vertexErrMatrix() ;
   }

   //if this is MC, no run gain needed
   static const CcRunGain kDummyRunGain;
   const CcRunGain* pRunGain = &kDummyRunGain;
   if( !isMC && m_prod.requireRunGainsHotList() )
   {
      try 
      {
	 FAItem< CcRunGain >  runGain   ;
	 extract( iRecord.frame().record(Stream::kBeginRun) ,   runGain ) ;
	 pRunGain = &(*runGain);
	 
	 static DABoolean firstRunGain=true;
	 if( firstRunGain )
	 {
	    report( INFO, kReport ) 
	       << "Running with CC run-to-run corrections" << endl ;
	    firstRunGain = false ;
	 }
      } 
      catch( DAExceptionBase& iException ) 
      {
	 report( ERROR, kReport ) 
	    << "No CcRunGains available! If doing post-Pass2 analysis\n" 
	    << "use official scripts; if doing pre-Pass2 processing, do\n"
	    << "param C3ccProd RequireRunGainsHotList false"
	    << endl ;
	 throw ;
      }
   }

   FAItem< CcHotList >  hotList ;
   if( m_prod.requireRunGainsHotList() )
   {
      static DABoolean firstHotList ( true ) ;
   
      try 
      {
	 extract( iRecord.frame().record(Stream::kBeginRun) ,   hotList ) ;
      } 
      catch( DAExceptionBase& iException )
      {
	 report( ERROR, kReport ) 
	    << "No CcHotlist available! If doing post-Pass2 analysis\n" 
	    << "use official scripts; if doing pre-Pass2 processing, do\n"
	    << "param C3ccProd RequireRunGainsHotList false"
	    << endl ;
	 firstHotList = false ;
	 throw ;
      }
      if( firstHotList )
      {
	 report( INFO, kReport ) 
	    << "Running with CC hot list suppression available" << endl ;
	 firstHotList = false ;
      }
   }

   FATable< CcBasicShowerAttsArg >::const_iterator bEnd ( basic.end() ) ;
   for ( FATable< CcBasicShowerAttsArg >::const_iterator item 
	    ( basic.begin() ) ; item != bEnd ; ++item ) 
   {
      CcShowerAttributes* tmp ( new CcShowerAttributes(
	 (*item), *m_corrector, 
	 origin, errMatO, isMC, *pRunGain, &(*hotList), lfixit, lfixend ) ) ;

      (*m_ptrTable).insert( tmp ) ;
   }

   return m_ptrTable ;
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
template class ProxyBindableTemplate< FAPtrTable< CcShowerAttributes > >;

PROXY_BIND_METHOD( CcShowerAttributesProxy )


