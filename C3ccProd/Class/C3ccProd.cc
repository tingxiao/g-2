// -*- C++ -*-
//
// Package:     C3ccProd
// Module:      C3ccProd
// 
// Description:
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Fri May 21 11:41:34 EDT 1999
// $Id: C3ccProd.cc,v 1.12 2008/02/19 17:21:42 bkh Exp $
//
// Revision history
//
// $Log: C3ccProd.cc,v $
// Revision 1.12  2008/02/19 17:21:42  bkh
// Separate Endcap energy fix from mc smearing & error-inflation fix
//
// Revision 1.11  2007/03/16 15:02:22  bkh
// Parameter-controlled increase in sigmas, smearing in MC
//
// Revision 1.10  2003/07/30 20:45:41  bkh
// Throw exception if no rungains or hotlist unless new parameter RequireRunGainsHotList is explicitly set to false
//
// Revision 1.9  2002/06/14 18:22:11  cdj
// previous change now compiles under OSF1 (I don't know how it compiled under Solaris)
//
// Revision 1.8  2002/06/13 19:57:14  bkh
// Institute parameter control over use of event vertex
// (never mind that the event vertex object does not exist yet...
// not to worry, only structural code is set up and this will compile.)
//
// Revision 1.7  2002/03/21 19:29:11  bkh
// Accommodate changes in rowsums
//
// Revision 1.6  2000/05/16 18:39:26  bkh
// Moved to new producer
//
// Revision 1.5  2000/04/07 18:03:22  bkh
// Moved from C3ccReconProd
//
// Revision 1.4  2000/02/29 21:43:40  bkh
// Moved to C3ccReconProd
//
// Revision 1.3  1999/12/06 18:03:30  bkh
// Modify codes to return a msg & null ptr instead of crashing out when an error
//
// Revision 1.2  1999/09/14 17:44:15  bkh
// Proxy for object which triggers CC constants fetching
//
// Revision 1.1.1.1  1999/07/19 15:27:30  bkh
// imported C3ccProd sources
//
// Revision 1.2  1999/07/01 21:56:01  bkh
// Now construct from args object
//
// Revision 1.1.1.1  1999/05/24 20:10:10  bkh
// imported C3ccProd sources
//
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "C3ccProd/C3ccProd.h"
#include "Experiment/report.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
#include "DataHandler/ProxyFactoryFunction.h"
#include "DataHandler/ProxyFactoryArgument.h"

#include "C3ccProd/CcShowerAttributesProxy.h"
#include "C3ccProd/CcEventSummaryProxy.h"
#include "C3ccProd/CcQedEventProxy.h"

#include "CommandPattern/Parameter.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kReport = "C3ccProd.C3ccProd" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: C3ccProd.cc,v 1.12 2008/02/19 17:21:42 bkh Exp $";
static const char* const kTagString = "$Name: v04_00_08 $";

//
// static data member definitions
//

//
// constructors and destructor
//
C3ccProd::C3ccProd( void )               // anal1
   : Producer( "C3ccProd" ) ,
     m_useEventVertex( "UseEventVertex", this, false ),
     m_requireRunGainsHotList( "RequireRunGainsHotList", this, true ),
     m_fixShowers( "FixShowers", this, false ),
     m_fixEndcap( "FixEndcap", this, false )
{
   report( DEBUG, kReport ) << "here in ctor()" << endl;

   m_useEventVertex.setHelpString(
    " Boolean parm stating whether the event vertex is used as origin: default false \n ");

   m_requireRunGainsHotList.setHelpString(
    " Boolean parm to force exception thrown if no run gains or hot list; default: true \n ");

   m_fixShowers.setHelpString(
    " Boolean parm to force smearing of MC shower energies & MC & data sigmas; default: false \n ");
   m_fixEndcap.setHelpString(
    " Boolean parm to force fixing of ENDCAP shower energies; default: false \n ");

   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactoryArgument< CcShowerAttributesProxy,
			 const C3ccProd& >( *this ), 
			 UsageTag() );    // or UsageTag( "MyUsage" )

   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactory< CcEventSummaryProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )

   registerProxyFactory( Stream::kEvent, 
			 new ProxyFactory< CcQedEventProxy >, 
			 UsageTag() );    // or UsageTag( "MyUsage" )
}

// Proxy Registration Step 2:
// template instantiations for proxy factories
#include "DataHandler/Template/ProxyFactory.cc"
template class ProxyFactoryArgument< CcShowerAttributesProxy, const C3ccProd& > ;
template class ProxyFactory< CcEventSummaryProxy     > ;
template class ProxyFactory< CcQedEventProxy         > ;

// non-trivial proxyfactory producer method used above
// (if you want to use it, don't forget to declare this method 
//  in "producer.h"!)

// C3ccProd::C3ccProd( const C3ccProd& iC3ccProd )
// {
//    *this = iC3ccProd;
// }

C3ccProd::~C3ccProd()                    // anal5
{
   report( DEBUG, kReport ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
C3ccProd::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kReport ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
C3ccProd::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kReport ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
C3ccProd::hist_book( TBHistoManager& )
{
   report( DEBUG, kReport ) << "here in hist_book()" << endl;

   // book your histograms here

}

//
// const member functions
//

//
// static member functions
//
