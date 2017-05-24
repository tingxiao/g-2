// -*- C++ -*-
//
// Package:     FirstTestProc
// Module:      FirstTestProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      tty7
// Created:     Wed Jun  3 16:52:23 CDT 2009
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "FirstTestProc/FirstTestProc.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
//I added the following at the suggestion of the NavShower web page
#include "Navigation/NavConReg.h"
#include "KinematicTrajectory/KTKinematicData.h"
#include "Navigation/NavTkShMatch.h"
#include "C3cc/CcAssignedEnergyHit.h"

#include "Navigation/NavTrack.h"
#include "TrackRoot/TRHelixFit.h"
#include "TrackRoot/TRTrackFitQuality.h"
#include "TrackRoot/TRSeedTrackQuality.h"
#include "TrackDelivery/TDKinematicFit.h"



// STL classes
// You may have to uncomment some of these or other stl headers 
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.FirstTestProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
FirstTestProc::FirstTestProc( void )               // anal1
   : Processor( "FirstTestProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &FirstTestProc::event,    Stream::kEvent );
   //bind( &FirstTestProc::beginRun, Stream::kBeginRun );
   //bind( &FirstTestProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

FirstTestProc::~FirstTestProc()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
FirstTestProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
FirstTestProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
FirstTestProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   m_Echarge = iHistoManager.histogram("total energy of charged particles", 500, 0., 1);
   m_Eshower = iHistoManager.histogram("total energy in calorimeter", 500, 0., 1);
   m_Eunshower = iHistoManager.histogram("total energy of unmathced showers in calorimeter", 500, 0., 1);
   m_Echarge1 = iHistoManager.histogram("energy of first highest energy track", 500, 0., 1);
   m_Echarge2 = iHistoManager.histogram("energy of second highest energy track", 500, 0., 1);
   m_Eshower1 = iHistoManager.histogram("energy of first highest energy shower", 500, 0., 1);
   m_Eshower2 = iHistoManager.histogram("energy of second highest energy shower", 500, 0., 1);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
FirstTestProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   // Create a table of tracks and fill it.
   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable );

   FATable< NavTrack >::const_iterator trackBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackEnd = trackTable.end();

   HepDouble maxtrack1 = -10;
   HepDouble maxtrack2 = -10;

   // Loop over tracks.
   for ( FATable< NavTrack >::const_iterator trackItr = trackBegin;
         trackItr != trackEnd ;
         ++trackItr )
   {
      const TDKinematicFit& kineData = *( *trackItr ).pionFit() ;
      const HepLorentzVector& v = kineData.lorentzMomentum();
      HepDouble trackenergy = v.e();
      m_Echarge->fill( trackenergy ) ;

      if (maxtrack1 < trackenergy){
         maxtrack1 = trackenergy;
     }
      if ((maxtrack2 < trackenergy) && (trackenergy < maxtrack1)){
         maxtrack2 = trackenergy;
     }
   }
      if (maxtrack1 > 0)
         m_Echarge1->fill( maxtrack1 ) ;
      if (maxtrack2 > 0)
         m_Echarge2->fill( maxtrack2 ) ;

   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ) , showerTable );

   FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
   FATable< NavShower >::const_iterator showerEnd = showerTable.end();

   HepDouble maxshower1 = -10;
   HepDouble maxshower2 = -10;

   for (FATable< NavShower >::const_iterator showerItr = showerBegin;
        showerItr != showerEnd ; ++showerItr ){

   if((showerItr->attributes().goodBarrel() ||
       showerItr->attributes().goodEndcap() ) && (showerItr->attributes().hot() == 0) ) {

       const HepLorentzVector& v1 =( *showerItr ).photon().lorentzMomentum();
       HepDouble showerenergy = v1.e();
       m_Eshower->fill( showerenergy );
       if (showerItr->noTrackMatch()){
          m_Eunshower->fill( showerenergy );
       }
       if (maxshower1 < showerenergy){
          maxshower1 = showerenergy;
       }
       if ((maxshower2 < showerenergy) && (showerenergy < maxshower1)){
          maxshower2 = showerenergy;
       }
   }
   } // end of loop of NavShowers

       if (maxshower1 > 0)
          m_Eshower1->fill( maxshower1 ) ;
       if (maxshower2 > 0)
          m_Eshower2->fill( maxshower2 ) ;





   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
FirstTestProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
FirstTestProc::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

//
// const member functions
//

//
// static member functions
//
