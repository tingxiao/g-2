// -*- C++ -*-
//
// Package:     DumpDecayTreeProc
// Module:      DumpDecayTreeProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Hanna Mahlke-Krueger
// Created:     Mon Jun 18 16:02:36 EDT 2001
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "DumpDecayTreeProc/DumpDecayTreeProc.h"
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
static const char* const kFacilityString = "Processor.DumpDecayTreeProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.17 2000/12/04 19:11:11 cdj Exp $";
static const char* const kTagString = "$Name: v03_06_00 $";

//
// static data member definitions
//

//
// constructors and destructor
//
DumpDecayTreeProc::DumpDecayTreeProc( void )               // anal1
   : Processor( "DumpDecayTreeProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &DumpDecayTreeProc::event,    Stream::kEvent );
   //bind( &DumpDecayTreeProc::beginRun, Stream::kBeginRun );
   //bind( &DumpDecayTreeProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

}

DumpDecayTreeProc::~DumpDecayTreeProc()                    // anal5
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
DumpDecayTreeProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
DumpDecayTreeProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

// ---------------- standard place to book histograms ---------------
void
DumpDecayTreeProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   h_fjpsipiplus2_fpipi2 = iHistoManager.histogram("fjpsipiplus2_fpipi2", 80, 10, 18, 150, 0, 1.5);
   h_fjpsipiplus2_fjpsipiminus2 = iHistoManager.histogram("fjpsipiplus2_fjpsipiminus2",80, 10, 18, 80, 10, 18);
   h_fmumu = iHistoManager.histogram("fmumu",100, 3, 3.2);
   h_fpipimumu = iHistoManager.histogram("fpipimumu", 300, 3.2, 5.2);
   h_fpipi = iHistoManager.histogram("fpipi", 60, 0.2, 1.4);
   h_fjpsipi = iHistoManager.histogram("fjpsipi", 100, 3.2, 4.2);

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
DumpDecayTreeProc::event( Frame& iFrame )          // anal3 equiv.
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
 double ppie, ppipx, ppipy, ppipz, npie, npipx, npipy, npipz, pmue, pmupx, pmupy, pmupz, nmue, nmupx, nmupy, nmupz;
 double mpipi, jpsipip, jpsipin, mmumu, mpipimumu;
 bool found_pi_plus=false, found_pi_minus=false, found_mu_plus=false, found_mu_minus=false;

 for(MCDecayTree::const_pIterator it = decayTree->pBegin();
       it != decayTree->pEnd(); it++) {

   if( ( it->properties().PDGId() == 211 ) ) {
     found_pi_plus = true;
     ppie = it->energy();
     ppipx = it->px();
     ppipy = it->py();
     ppipz = it->pz();
   }

   if( ( it->properties().PDGId() == -211 ) ) {
     found_pi_minus = true;
     npie = it->energy();
     npipx = it->px();
     npipy = it->py();
     npipz = it->pz();
   }

   if( ( it->properties().PDGId() == -13 ) ) {
     found_mu_plus = true;
     pmue = it->energy();
     pmupx = it->px();
     pmupy = it->py();
     pmupz = it->pz();
   }

   if( ( it->properties().PDGId() == 13 ) ) {
     found_mu_minus = true;
     nmue = it->energy();
     nmupx = it->px();
     nmupy = it->py();
     nmupz = it->pz();
   }
 }

 if(found_pi_plus && found_pi_minus && found_mu_plus && found_mu_minus) {
   mpipi = sqrt(pow((ppie+npie),2) - pow((ppipx+npipx),2) - pow((ppipy+npipy),2) - pow((ppipz+npipz),2));
   mmumu = sqrt(pow((pmue+nmue),2) - pow((pmupx+nmupx),2) - pow((pmupy+nmupy),2) - pow((pmupz+nmupz),2));
   jpsipip = sqrt(pow((pmue+nmue+ppie),2) - pow((pmupx+nmupx+ppipx),2) - pow((pmupy+nmupy+ppipy),2) - pow((pmupz+nmupz+ppipz),2));
   jpsipin = sqrt(pow((pmue+nmue+npie),2) - pow((pmupx+nmupx+npipx),2) - pow((pmupy+nmupy+npipy),2) - pow((pmupz+nmupz+npipz),2));
   mpipimumu = sqrt(pow((ppie+npie+pmue+nmue),2) - pow((ppipx+npipx+pmupx+nmupx),2) 
                  - pow((ppipy+npipy+pmupy+nmupy),2) - pow((ppipz+npipz+pmupz+nmupz),2));
 }
  
   h_fmumu->fill(mmumu);
   h_fpipi->fill(mpipi);
   h_fpipimumu->fill(mpipimumu);
   h_fjpsipiplus2_fpipi2->fill(jpsipip*jpsipip,mpipi*mpipi);
   h_fjpsipiplus2_fjpsipiminus2->fill(jpsipip*jpsipip,jpsipin*jpsipin);
   if(jpsipip>jpsipin)
     h_fjpsipi->fill(jpsipip);
   else
     h_fjpsipi->fill(jpsipin);

   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
DumpDecayTreeProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
DumpDecayTreeProc::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

  TCanvas *c1 = new TCanvas("c1", "babayaga", 300, 300, 800, 600);

  h_ns->Draw();
  c1->Print("babayaga.ps(");
  h_e1->Draw();
  c1->Print("babayaga.ps)");

  TFile outf("babayaga.root", "recreate");
  h_ns->Write();
  h_e1->Write();
  h_e2->Write();
  h_e3->Write();
//  h_e1_costh->Write();
//  h_e2_costh->Write();
//  h_e3_costh->Write();

  outf.Close();





   return ActionBase::kPassed;
}

*/
//
// const member functions
//

//
// static member functions
//

