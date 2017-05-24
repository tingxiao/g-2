// -*- C++ -*-
//
// Package:     TestPhokharaProc
// Module:      TestPhokharaProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Thu Jul 12 12:52:17 CDT 2012
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "TestPhokharaProc/TestPhokharaProc.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units
#include "HistogramInterface/HINtupleVarNames.h"
#include "HistogramInterface/HINtupleArray.h"
#include "HistogramInterface/HIHist1D.h"

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
#include "BeamSpot/BeamSpot.h"

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
static const char* const kFacilityString = "Processor.TestPhokharaProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
TestPhokharaProc::TestPhokharaProc( void )               // anal1
   : Processor( "TestPhokharaProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &TestPhokharaProc::event,    Stream::kEvent );
   bind( &TestPhokharaProc::beginRun, Stream::kBeginRun );
   //bind( &TestPhokharaProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

TestPhokharaProc::~TestPhokharaProc()                    // anal5
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
TestPhokharaProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
TestPhokharaProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------

enum {
nshower,
e1,px1,py1,pz1,x1,yy1,z1,
e2,px2,py2,pz2,x2,y2,z2,
pie1,pipx1,pipy1,pipz1,pix1,piy1,piz1,
pie2,pipx2,pipy2,pipz2,pix2,piy2,piz2,
mue1,mupx1,mupy1,mupz1,mux1,muy1,muz1,mue1_pimass,
mue2,mupx2,mupy2,mupz2,mux2,muy2,muz2,mue2_pimass,
ee1,epx1,epy1,epz1,ex1,ey1,ez1,ee1_pimass,
ee2,epx2,epy2,epz2,ex2,ey2,ez2,ee2_pimass,

pi0e,pi0px,pi0py,pi0pz,
xsize,ysize,zsize,
kVarNum};



void
TestPhokharaProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   HINtupleVarNames ntupleNames(kVarNum);

   ntupleNames.addVar(nshower,     "nshower");
   ntupleNames.addVar(e1,          "e1");
   ntupleNames.addVar(px1,         "px1");
   ntupleNames.addVar(py1,         "py1");
   ntupleNames.addVar(pz1,         "pz1");
   ntupleNames.addVar(x1,         "x1");
   ntupleNames.addVar(yy1,         "yy1");
   ntupleNames.addVar(z1,         "z1");
   ntupleNames.addVar(e2,          "e2");
   ntupleNames.addVar(px2,         "px2");
   ntupleNames.addVar(py2,         "py2");
   ntupleNames.addVar(pz2,         "pz2");
   ntupleNames.addVar(x2,         "x2");
   ntupleNames.addVar(y2,         "y2");
   ntupleNames.addVar(z2,         "z2");
   ntupleNames.addVar(pie1,          "pie1");
   ntupleNames.addVar(pipx1,         "pipx1");
   ntupleNames.addVar(pipy1,         "pipy1");
   ntupleNames.addVar(pipz1,         "pipz1");
   ntupleNames.addVar(pix1,         "pix1");
   ntupleNames.addVar(piy1,         "piy1");
   ntupleNames.addVar(piz1,         "piz1");
   ntupleNames.addVar(pie2,          "pie2");
   ntupleNames.addVar(pipx2,         "pipx2");
   ntupleNames.addVar(pipy2,         "pipy2");
   ntupleNames.addVar(pipz2,         "pipz2");
   ntupleNames.addVar(pix2,         "pix2");
   ntupleNames.addVar(piy2,         "piy2");
   ntupleNames.addVar(piz2,         "piz2");
   ntupleNames.addVar(mue1,          "mue1");
   ntupleNames.addVar(mupx1,         "mupx1");
   ntupleNames.addVar(mupy1,         "mupy1");
   ntupleNames.addVar(mupz1,         "mupz1");
   ntupleNames.addVar(mux1,         "mux1");
   ntupleNames.addVar(muy1,         "muy1");
   ntupleNames.addVar(muz1,         "muz1");
   ntupleNames.addVar(mue2,          "mue2");
   ntupleNames.addVar(mupx2,         "mupx2");
   ntupleNames.addVar(mupy2,         "mupy2");
   ntupleNames.addVar(mupz2,         "mupz2");
   ntupleNames.addVar(mux2,         "mux2");
   ntupleNames.addVar(muy2,         "muy2");
   ntupleNames.addVar(muz2,         "muz2");

   ntupleNames.addVar(ee1,          "ee1");
   ntupleNames.addVar(epx1,         "epx1");
   ntupleNames.addVar(epy1,         "epy1");
   ntupleNames.addVar(epz1,         "epz1");
   ntupleNames.addVar(ex1,         "ex1");
   ntupleNames.addVar(ey1,         "ey1");
   ntupleNames.addVar(ez1,         "ez1");
   ntupleNames.addVar(ee2,          "ee2");
   ntupleNames.addVar(epx2,         "epx2");
   ntupleNames.addVar(epy2,         "epy2");
   ntupleNames.addVar(epz2,         "epz2");
   ntupleNames.addVar(ex2,         "ex2");
   ntupleNames.addVar(ey2,         "ey2");
   ntupleNames.addVar(ez2,         "ez2");

   ntupleNames.addVar(xsize,         "xsize");
   ntupleNames.addVar(ysize,         "ysize");
   ntupleNames.addVar(zsize,         "zsize");
   ntupleNames.addVar(pi0e,          "pi0e");
   ntupleNames.addVar(pi0px,         "pi0px");
   ntupleNames.addVar(pi0py,         "pi0py");
   ntupleNames.addVar(pi0pz,         "pi0pz");
   ntupleNames.addVar(mue1_pimass,          "mue1_pimass");
   ntupleNames.addVar(mue2_pimass,          "mue2_pimass");
   ntupleNames.addVar(ee1_pimass,          "ee1_pimass");
   ntupleNames.addVar(ee2_pimass,          "ee2_pimass");


   m_showerTuple = iHistoManager.ntuple(10,"tuple", kVarNum, 10000, ntupleNames.names());

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
TestPhokharaProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   FAItem< MCDecayTree > decayTree;

   extract(iFrame.record(Stream::kEvent), decayTree, "Generator" );

 int n_shower = 0;
 double p_e = 0;
 double p_px = 0;
 double p_py = 0;
 double p_pz = 0;
 double p_x = 0;
 double p_y = 0;
 double p_z = 0;
 double n_e = 0;
 double n_px = 0;
 double n_py = 0;
 double n_pz = 0;
 double n_x = 0;
 double n_y = 0;
 double n_z = 0;
 double pi0_e = 0;
 double pi0_px = 0;
 double pi0_py = 0;
 double pi0_pz = 0;
 double ppi_e = 0;
 double ppi_px = 0;
 double ppi_py = 0;
 double ppi_pz = 0;
 double ppi_x = 0;
 double ppi_y = 0;
 double ppi_z = 0;
 double npi_e = 0;
 double npi_px = 0;
 double npi_py = 0;
 double npi_pz = 0;
 double npi_x = 0;
 double npi_y = 0;
 double npi_z = 0;
 double pmu_e = 0;
 double pmu_px = 0;
 double pmu_py = 0;
 double pmu_pz = 0;
 double pmu_x = 0;
 double pmu_y = 0;
 double pmu_z = 0;
 double nmu_e = 0;
 double nmu_px = 0;
 double nmu_py = 0;
 double nmu_pz = 0;
 double nmu_x = 0;
 double nmu_y = 0;
 double nmu_z = 0;
 double pmu_e_pimass = 0;
 double nmu_e_pimass = 0;
 double x_size = 0;
 double y_size = 0;
 double z_size = 0;

 double pe_e = 0;
 double pe_px = 0;
 double pe_py = 0;
 double pe_pz = 0;
 double pe_x = 0;
 double pe_y = 0;
 double pe_z = 0;
 double ne_e = 0;
 double ne_px = 0;
 double ne_py = 0;
 double ne_pz = 0;
 double ne_x = 0;
 double ne_y = 0;
 double ne_z = 0;
 double pe_e_pimass = 0;
 double ne_e_pimass = 0;


 float tuple[kVarNum];

 FAItem< BeamSpot > spot;
 extract( iFrame.record( Stream::kBeginRun ), spot );


 x_size = spot->size().x();
 y_size = spot->size().y();
 z_size = spot->size().z();

 for(MCDecayTree::const_pIterator it = decayTree->pBegin();
       it != decayTree->pEnd(); it++) {

   if( ( it->properties().PDGId() == 22 ) ) {
         const MCVertex* vphoVtx = it->productionVertex();
         const MCParticle& parent = (*vphoVtx).parent();

     if(parent.properties().PDGId() == 91 && n_shower == 1){
         n_e = it->energy();
         n_px = it->px();
         n_py = it->py();
         n_pz = it->pz();
         n_x = it->x();
         n_y = it->y();
         n_z = it->z();
         n_shower++;
      }

     else if(parent.properties().PDGId() == 91 && n_shower == 0){
         p_e = it->energy();
         p_px = it->px();
         p_py = it->py();
         p_pz = it->pz();
         p_x = it->x();
         p_y = it->y();
         p_z = it->z();
         n_shower++;
      }

   }

   else if( ( it->properties().PDGId() == 211 ) ) {
     ppi_px = it->px();
     ppi_py = it->py();
     ppi_pz = it->pz();
     ppi_x = it->x();
     ppi_y = it->y();
     ppi_z = it->z();
     ppi_e  = it->energy();
   }

   else if( ( it->properties().PDGId() == -211 ) ) {
     npi_px = it->px();
     npi_py = it->py();
     npi_pz = it->pz();
     npi_x = it->x();
     npi_y = it->y();
     npi_z = it->z();
     npi_e  = it->energy();
   }

   else if( ( it->properties().PDGId() == -13 ) ) {
     pmu_px = it->px();
     pmu_py = it->py();
     pmu_pz = it->pz();
     pmu_x = it->x();
     pmu_y = it->y();
     pmu_z = it->z();
     pmu_e  = it->energy();
     pmu_e_pimass = sqrt(pow(it->px(),2)+pow(it->py(),2)+pow(it->pz(),2)+pow(0.13957,2));
   }

   else if( ( it->properties().PDGId() == 13 ) ) {
     nmu_px = it->px();
     nmu_py = it->py();
     nmu_pz = it->pz();
     nmu_x = it->x();
     nmu_y = it->y();
     nmu_z = it->z();
     nmu_e  = it->energy();
     nmu_e_pimass = sqrt(pow(it->px(),2)+pow(it->py(),2)+pow(it->pz(),2)+pow(0.13957,2));
   }

   else if( ( it->properties().PDGId() == -11 ) ) {
     pe_px = it->px();
     pe_py = it->py();
     pe_pz = it->pz();
     pe_x = it->x();
     pe_y = it->y();
     pe_z = it->z();
     pe_e  = it->energy();
     pe_e_pimass = sqrt(pow(it->px(),2)+pow(it->py(),2)+pow(it->pz(),2)+pow(0.13957,2));
   }

   else if( ( it->properties().PDGId() == 11 ) ) {
     ne_px = it->px();
     ne_py = it->py();
     ne_pz = it->pz();
     ne_x = it->x();
     ne_y = it->y();
     ne_z = it->z();
     ne_e  = it->energy();
     ne_e_pimass = sqrt(pow(it->px(),2)+pow(it->py(),2)+pow(it->pz(),2)+pow(0.13957,2));
   }

   else if( ( it->properties().PDGId() == 111 ) ) {
     pi0_px = it->px();
     pi0_py = it->py();
     pi0_pz = it->pz();
     pi0_e  = it->energy();
   }
 }

   tuple[nshower] = n_shower;
   tuple[e1] = p_e;
   tuple[px1] = p_px;
   tuple[py1] = p_py;
   tuple[pz1] = p_pz;
   tuple[x1] = p_x;
   tuple[yy1] = p_y;
   tuple[z1] = p_z;
   tuple[e2] = n_e;
   tuple[px2] = n_px;
   tuple[py2] = n_py;
   tuple[pz2] = n_pz;
   tuple[x2] = n_x;
   tuple[y2] = n_y;
   tuple[z2] = n_z;
   tuple[pi0e] = pi0_e;
   tuple[pi0px] = pi0_px;
   tuple[pi0py] = pi0_py;
   tuple[pi0pz] = pi0_pz;

   tuple[pie1] = ppi_e;
   tuple[pipx1] = ppi_px;
   tuple[pipy1] = ppi_py;
   tuple[pipz1] = ppi_pz;
   tuple[pix1] = ppi_x;
   tuple[piy1] = ppi_y;
   tuple[piz1] = ppi_z;
   tuple[pie2] = npi_e;
   tuple[pipx2] = npi_px;
   tuple[pipy2] = npi_py;
   tuple[pipz2] = npi_pz;
   tuple[pix2] = npi_x;
   tuple[piy2] = npi_y;
   tuple[piz2] = npi_z;
   tuple[mue1] = pmu_e;
   tuple[mupx1] = pmu_px;
   tuple[mupy1] = pmu_py;
   tuple[mupz1] = pmu_pz;
   tuple[mux1] = pmu_x;
   tuple[muy1] = pmu_y;
   tuple[muz1] = pmu_z;
   tuple[mue2] = nmu_e;
   tuple[mupx2] = nmu_px;
   tuple[mupy2] = nmu_py;
   tuple[mupz2] = nmu_pz;
   tuple[mux2] = nmu_x;
   tuple[muy2] = nmu_y;
   tuple[muz2] = nmu_z;
   tuple[ee1] = pe_e;
   tuple[epx1] = pe_px;
   tuple[epy1] = pe_py;
   tuple[epz1] = pe_pz;
   tuple[ex1] = pe_x;
   tuple[ey1] = pe_y;
   tuple[ez1] = pe_z;
   tuple[ee2] = ne_e;
   tuple[epx2] = ne_px;
   tuple[epy2] = ne_py;
   tuple[epz2] = ne_pz;
   tuple[ex2] = ne_x;
   tuple[ey2] = ne_y;
   tuple[ez2] = ne_z;

   tuple[xsize] = x_size;
   tuple[ysize] = y_size;
   tuple[zsize] = z_size;
   tuple[mue1_pimass] = pmu_e_pimass;
   tuple[mue2_pimass] = nmu_e_pimass;

   (*m_showerTuple).fill(tuple);



   return ActionBase::kPassed;
}


ActionBase::ActionResult
TestPhokharaProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   FAItem< BeamSpot > spot;
   extract( iFrame.record( Stream::kBeginRun ), spot );

//   FAItem< BeamEnergy > beam_energy;
//   extract( iFrame.record( Stream::kBeginRun ), beam_energy );

//   FAItem< MagneticField > cleoBField;
//   extract( iFrame.record( Stream::kBeginRun ), cleoBField );

//   FitEvtSettings &settings(FitEvtSettings::instance());
//   settings.setField(*cleoBField);
//   settings.setBeamSpot(*spot);
//   settings.setLorVecCM( beam_energy->value() );
//   settings.setVerbose();

   return ActionBase::kPassed;
}


/*
ActionBase::ActionResult
TestPhokharaProc::endRun( Frame& iFrame )         // anal4 equiv.
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
