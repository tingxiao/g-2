// -*- C++ -*-
//
// Package:     OmegaChannel1Proc
// Module:      OmegaChannel1Proc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Ting Xiao
// Created:     Wed Mar 28 12:13:21 EST 2018
// $Id$
//
// Revision history
//
// $Log$
// Select Omega->Lambda+K in MC
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "OmegaChannel1Proc/OmegaChannel1Proc.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

// MC include files
#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCDecayTree/MCVertex.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"
#include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
#include "MCBeam/MCBeamParticles.h"

#include "KinematicTrajectory/KTKinematicData.h" 
#include "RandomModule/RandomGenerator.h"


//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.OmegaChannel1Proc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

// it opens the file for writing
//    ofstream fout;
//    ofstream fout1;

//
// static data member definitions
//
// Some handy typedefs for accessing MC information
typedef MCDecayTree::const_vIterator MCVertexConstIt;
typedef MCDecayTree::const_pIterator MCPartConstIt;
typedef MCVertex::const_pIterator    MCChildConstIt;

//
// constructors and destructor
//
OmegaChannel1Proc::OmegaChannel1Proc( void )               // anal1
   : Processor( "OmegaChannel1Proc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &OmegaChannel1Proc::event,    Stream::kEvent );
   bind( &OmegaChannel1Proc::beginRun, Stream::kBeginRun );
   bind( &OmegaChannel1Proc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

OmegaChannel1Proc::~OmegaChannel1Proc()                    // anal5
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
OmegaChannel1Proc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
OmegaChannel1Proc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
void
OmegaChannel1Proc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
OmegaChannel1Proc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   UInt32 runNumber   = iFrame.syncValue().runNumber();
   // Let's extract the tree (no usage tag means we get the CLEOG tree)
// Accessing Beam info
   FAItem<MCBeamParticles> beamParticles;
   extract(iFrame.record(Stream::kEvent), beamParticles);
   const MCParticle positron = beamParticles->positron();
   const HepLorentzVector  positronP4 = positron.lorentzMomentum();

   FAItem< MCDecayTree > decayTree;
//   extract(iFrame.record(Stream::kEvent), decayTree, "Generator" );
   extract(iFrame.record(Stream::kEvent), decayTree );

   // Get a reference to it
   const MCDecayTree& mcDecayTree(*decayTree);

   // Let's just try to print it out
   //report(INFO, kFacilityString) << "About to dump decay tree" << endl;
   //report(INFO, kFacilityString) << mcDecayTree << endl;


   MCPartConstIt MCPartTreeBegin = decayTree->pBegin();
   MCPartConstIt MCPartTreeEnd = decayTree->pEnd();

   bool channel1_found = false;
   int count = 0;
//   int nparts=0;

   //m_run = runNumber;


/*
   for(MCPartConstIt partItr = MCPartTreeBegin; 
       partItr != MCPartTreeEnd; ++partItr, ++nparts)
   {
      // Get the properties of this particle
      const MCParticleProperty& properties = partItr->properties();
      int id =  properties.PDGId();

      const MCVertex* psiVtx = (*partItr).productionVertex();

      cerr << " parent vertex = " << psiVtx << endl;

      if(!psiVtx) continue;
      const MCParticle& parent = (*psiVtx).parent();
      const MCParticleProperty& parentProp = parent.properties();

      if( partItr->deathVertex() ) {
	if ( abs(id) == 3334 ) {   // Omega

	  for(MCChildConstIt partItr2 = partItr->deathVertex()->pBegin();
	      partItr2 != partItr->deathVertex()->pEnd(); partItr2++ ) {
	    const MCParticleProperty& properties2 = partItr2->properties();
	    
	    cerr << " particle = " << properties2.PDGId() << endl;
	    
	    if( (abs(properties2.PDGId())==3122 ) || (abs(properties2.PDGId())==321 ) ) { // Lambda or K
              channel1_found = true;
            }
	  }
	}
      }
   }
*/

   for(MCDecayTree::const_pIterator it = decayTree->pBegin();
       it != decayTree->pEnd(); it++) {

       if( ( abs(it->properties().PDGId()) == 321 ) ) { // found K
         cerr << "Found K!" << endl;
         for(MCDecayTree::const_pIterator it2 = decayTree->pBegin();
             it2 != decayTree->pEnd(); it2++) {

             if( ( abs(it2->properties().PDGId()) == 3122 ) ) { // found Lambda0
               cerr << "Found Lambda!" << endl;
               cerr << (*it->productionVertex()).parent().properties().PDGId() << endl;
               cerr << (*it2->productionVertex()).parent().properties().PDGId() << endl << endl;
               if((*it->productionVertex()).parent().properties().PDGId() == (*it2->productionVertex()).parent().properties().PDGId()) {
                   channel1_found = true;
                   count++;
               }
            }
          }
       }

       cerr << it->properties().PDGId() << endl;
   }

  cerr << endl;

  if(!channel1_found || count != 2) {
     m_FailedEvents  += 1;
     return ActionBase::kFailed;
  }

  m_PassedEvents +=1;
  return ActionBase::kPassed;
}


ActionBase::ActionResult
OmegaChannel1Proc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;
   m_PassedEvents = 0;
   m_FailedEvents = 0;
   //m_run = 0;

   return ActionBase::kPassed;
}

ActionBase::ActionResult
OmegaChannel1Proc::endRun( Frame& iFrame )         // anal4 equiv.
{

   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;
   report( INFO, kFacilityString ) 
      //<< "Events accepted within (1+(cosTheta^2))! " <<m_PassedEvents <<" for run "<<m_run<< endl;
      << "Events accepted: " <<m_PassedEvents << endl;
   report( INFO, kFacilityString ) 
      << "Events not accepted: " <<m_FailedEvents << endl;
   //<< "Events not accepted within (1+(cosTheta^2))! " <<m_FailedEvents <<" for run "<<m_run<< endl;

   return ActionBase::kPassed;
}


//
// const member functions
//

//
// static member functions
//
