// -*- C++ -*-
//
// Package:     <C3ccProd>
// Module:      CcFortranShowerCorrector
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Tue Nov 30 11:51:39 EST 2004
// $Id: CcFortranShowerCorrector.cc,v 1.3 2008/02/19 17:21:42 bkh Exp $
//
// Revision history
//
// $Log: CcFortranShowerCorrector.cc,v $
// Revision 1.3  2008/02/19 17:21:42  bkh
// Separate Endcap energy fix from mc smearing & error-inflation fix
//
// Revision 1.2  2007/03/16 15:02:22  bkh
// Parameter-controlled increase in sigmas, smearing in MC
//
// Revision 1.1  2004/11/30 21:15:31  cdj
// use CcFortranShowerCorrector to implement new CcShowerAttributes interface
//

#include "Experiment/Experiment.h"

// system include files
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

// user include files
//#include "Experiment/report.h"
#include "C3ccProd/CcFortranShowerCorrector.h"

extern "C"
void
ccgecs3_( const FReal&    eIn ,
	  const FReal&    theta ,
	  const FReal&    phi ,
	  const FInteger& ring ,
	  FReal&          eOut ,
	  FReal&          enErr ,
	  FReal&          thErr ,
	  FReal&          phErr ,
	  const FLogical&       isMC  ,
	  const FReal&          baGain ,
	  const FReal&          ecGain ,
	  const FLogical&       lfixit ,
	  const FLogical&       lfixEndcap     ) ;

extern "C"
void
ccblok_( const FReal& aTh ,
	 const FReal& aPh ,
	 FReal&       aThBl ,
	 FReal&       aPhBl   ) ;

extern "C"
void
ccpock_( const FReal& aTh   ,
	 const FReal& aPh   ,
	 FReal&       aThP  ,
	 FReal&       aPhP  ,
	 FInteger&    aPock  ) ;

extern "C"
void cce925_( const FReal& aEnergy ,
	      const FReal& aTheta  ,
	      const FReal& aPhi    ,
	      FReal&       aCut1   ,
	      FReal&       aCut5   ,
	      FReal&       aCut10   ) ;


//
// constants, enums and typedefs
//

static const char* const kFacilityString = "C3ccProd.CcFortranShowerCorrector" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: CcFortranShowerCorrector.cc,v 1.3 2008/02/19 17:21:42 bkh Exp $";
static const char* const kTagString = "$Name: v04_00_08 $";

//
// static data member definitions
//

//
// constructors and destructor
//
//CcFortranShowerCorrector::CcFortranShowerCorrector()
//{
//}

// CcFortranShowerCorrector::CcFortranShowerCorrector( const CcFortranShowerCorrector& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

//CcFortranShowerCorrector::~CcFortranShowerCorrector()
//{
//}

//
// assignment operators
//
// const CcFortranShowerCorrector& CcFortranShowerCorrector::operator=( const CcFortranShowerCorrector& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//

//
// const member functions
//
void
CcFortranShowerCorrector::gammaEnergyAndSigmas( 
   const FReal&    eIn ,
   const FReal&    theta ,
   const FReal&    phi ,
   const FInteger& ring ,
   FReal&          eOut ,
   FReal&          enErr ,
   FReal&          thErr ,
   FReal&          phErr ,
   const FLogical&       isMC  ,
   const FReal&          baGain ,
   const FReal&          ecGain ,
   const FLogical&       lfixit ,
   const FLogical&       lfixEndcap    ) const  
{
   ccgecs3_(eIn, theta, phi, ring,
	    eOut, enErr, thErr, phErr,
	    isMC, baGain, ecGain, lfixit, lfixEndcap );
}
      

void
CcFortranShowerCorrector::toBlockCoords( const FReal& aTh ,
					 const FReal& aPh ,
					 FReal&       aThBl ,
					 FReal&       aPhBl   ) const 
{
   ccblok_(aTh, aPh, aThBl, aPhBl);
}


void
CcFortranShowerCorrector::toPocketCoords( const FReal& aTh   ,
					  const FReal& aPh   ,
					  FReal&       aThP  ,
					  FReal&       aPhP  ,
					  FInteger&    aPock  ) const 
{
   ccpock_(aTh, aPh, aThP, aPhP, aPock );
}
      
void 
CcFortranShowerCorrector::e9OverE25CutValues( const FReal& aEnergy ,
					      const FReal& aTheta  ,
					      const FReal& aPhi    ,
					      FReal&       aCut1   ,
					      FReal&       aCut5   ,
					      FReal&       aCut10   ) const 
{
   cce925_(aEnergy, aTheta, aPhi, aCut1, aCut5, aCut10 );
}

//
// static member functions
//
