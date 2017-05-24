// -*- C++ -*-
//
// Package:     QEDProc
// Module:      QEDProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Mon Dec 10 16:45:47 CST 2012
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "QEDProc/QEDProc.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCDecayTree/MCVertex.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"

#include "MCBeam/MCBeamParameters.h"
#include "CesrCleoComm/CesrCrossingAngle.h"

#include "CLHEP/Vector/LorentzRotation.h"




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
static const char* const kFacilityString = "Processor.QEDProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
QEDProc::QEDProc( void )               // anal1
   : Processor( "QEDProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &QEDProc::event,    Stream::kEvent );
   //bind( &QEDProc::beginRun, Stream::kBeginRun );
   //bind( &QEDProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

QEDProc::~QEDProc()                    // anal5
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
QEDProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
QEDProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
QEDProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   h_e_ee = iHistoManager.histogram("e_ee", 100, 0, 5);
   h_qcosth_ee = iHistoManager.histogram("qcosth_ee", 200, -1, 1);
   h_e_mumu = iHistoManager.histogram("e_mumu", 100, 0, 5);
   h_qcosth_mumu = iHistoManager.histogram("qcosth_mumu", 200, -1, 1);
   h_e_pipi = iHistoManager.histogram("e_pipi", 100, 0, 5);
   h_qcosth_pipi = iHistoManager.histogram("qcosth_pipi", 200, -1, 1);



}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
QEDProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   // Let's extract the tree (no usage tag means we get the CLEOG tree)
   FAItem< MCDecayTree > decayTree;

///////////////////////////////////////////////////////////////////
// NOTE: The first extract line is for dumping the cleog-level 
//       decay tree, the later is for dumping the generator-level
//       decay tree.

//   extract(iFrame.record(Stream::kEvent), decayTree);

   extract(iFrame.record(Stream::kEvent), decayTree, "Generator" );

///////////////////////////////////////////////////////////////////

 double qcosth = 0;

 for(MCDecayTree::const_pIterator it = decayTree->pBegin();
       it != decayTree->pEnd(); it++) {

   if( ( it->properties().PDGId() == 11 ) ) {
     qcosth = -(it->pz()/it->pmag());
     h_qcosth_ee->fill(qcosth);
     h_e_ee->fill(it->energy());
   }
   else if( ( it->properties().PDGId() == -11 ) ) {
     qcosth = it->pz()/it->pmag();
     h_qcosth_ee->fill(qcosth);
     h_e_ee->fill(it->energy());
   }
   else if( ( it->properties().PDGId() == 13 ) ) {
     qcosth = -(it->pz()/it->pmag());
     h_qcosth_mumu->fill(qcosth);
     h_e_mumu->fill(it->energy());
   }
   else if( ( it->properties().PDGId() == -13 ) ) {
     qcosth = it->pz()/it->pmag();
     h_qcosth_mumu->fill(qcosth);
     h_e_mumu->fill(it->energy());
   }
   else if( ( it->properties().PDGId() == -211 ) ) {
     qcosth = -(it->pz()/it->pmag());
     h_qcosth_pipi->fill(qcosth);
     h_e_pipi->fill(it->energy());
   }
   else if( ( it->properties().PDGId() == 211 ) ) {
     qcosth = it->pz()/it->pmag();
     h_qcosth_pipi->fill(qcosth);
     h_e_pipi->fill(it->energy());
   }

 }



   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
QEDProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
QEDProc::endRun( Frame& iFrame )         // anal4 equiv.
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
