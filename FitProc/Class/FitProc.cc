// -*- C++ -*-
//
// Package:     FitProc
// Module:      FitProc
//
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      pts/4
// Created:     Sun Sep 27 18:46:29 CDT 2009
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "FitProc/FitProc.h"
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

#include "Navigation/NavShower.h"
#include "C3cc/CcShowerAttributes.h"
#include "Navigation/NavShowerServer.h"
#include "C3ccProd/CcFortranShowerCorrector.h"
#include "C3Mu/MuTrack.h"
#include "Navigation/NavMuonId.h"

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
#include "Navigation/NavElecId.h"

#include "FitEvt/FitEvtSettings.h"
#include "FitEvt/FitEvt.h"
#include "BeamEnergy/BeamEnergy.h"
#include "MagField/MagneticField.h"
#include "MagField/MFFieldMap.h"
#include "BeamSpot/BeamSpot.h"

#include "CleoDB/DBEventHeader.h"
#include "TriggerData/TriggerData.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "Level4Proc/Level4Decision.h"

#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "MCInfo/MCDecayTree/MCParticle.h"
#include "MCInfo/MCDecayTree/MCVertex.h"
#include "MCInfo/MCParticleProperty/MCParticleProperty.h"

//RICH example
#include "Navigation/NavRich.h"
//Dedx example
#include "DedxInfo/DedxInfo.h"



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
static const char* const kFacilityString = "Processor.FitProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
FitProc::FitProc( void )               // anal1
   : Processor( "FitProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the
   // code you've just written (the "action") to a stream,
   // your code won't get executed!

   bind( &FitProc::event,    Stream::kEvent );
   bind( &FitProc::beginRun, Stream::kBeginRun );
   //bind( &FitProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

FitProc::~FitProc()                    // anal5
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
FitProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
FitProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)

}


// ---------------- standard place to book histograms ---------------

enum {knshower, kntrack, //number of showers and tracks
kntrack1shower, kntrack2shower,  // number of showers matched to a track
chisqvpi1,chisqfpi1, //chisq of pion fit (additional FSR)
chisqvpi2,chisqfpi2, //chisq of pion fit (additional ISR)
chisqvmu1,chisqfmu1, //chisq of muon fit (additional FSR)
chisqvmu2,chisqfmu2, //chisq of muon fit (additional ISR)
chisqvk1,chisqfk1, //chisq of kaon fit (additional FSR)
chisqvk2,chisqfk2, //chisq of kaon fit (additional ISR)

e1,th1,phi1,e9251,       // unfitted photon energy
e2,th2,phi2,e9252,
e3,th3,phi3,e9253,
e4,th4,phi4,e9254,
e5,th5,phi5,e9255,
e6,th6,phi6,e9256,
e7,th7,phi7,e9257,
e8,th8,phi8,e9258,
e9,th9,phi9,e9259,
e10,th10,phi10,e92510,

e1pi,th1pi,phi1pi,e9251pi,	// unfitted additional FSR photon
e1mu,th1mu,phi1mu,e9251mu,

erre1,errth1,errphi1,	 // unfitted photon energy resolution
erre2,errth2,errphi2,
erre3,errth3,errphi3,
erre4,errth4,errphi4,
erre5,errth5,errphi5,
erre6,errth6,errphi6,
erre7,errth7,errphi7,
erre8,errth8,errphi8,
erre9,errth9,errphi9,
erre10,errth10,errphi10,


me1,eop1,me2,eop2,  //matched energy and E/p
mudepth1,mudepth2,  //muon depth

dd, // distance between the two showers matched to the two tracks
width1, width2, // width of the two showers matched to the two tracks

f1epi1,f1thpi1,f1phipi1,  // fitted photon energy fitted with pions (additional FSR)
f1epi2,f1thpi2,f1phipi2,  //additional FSR
f2epi1,f2thpi1,f2phipi1,  // fitted photon energy fitted with pions (additional ISR)
f2epi2,f2thpi2,f2phipi2,  //additional ISR
f1emu1,f1thmu1,f1phimu1,  // fitted photon energy fitted with muons (additional FSR)
f1emu2,f1thmu2,f1phimu2,  //additional FSR
f2emu1,f2thmu1,f2phimu1,  // fitted photon energy fitted with muons (additional ISR)
f2emu2,f2thmu2,f2phimu2,  //additional ISR
f1ek1,f1thk1,f1phik1,  // fitted photon energy fitted with kaons (additional FSR)
f1ek2,f1thk2,f1phik2,  //additional FSR
f2ek1,f2thk1,f2phik1,  // fitted photon energy fitted with kaons (additional ISR)
f2ek2,f2thk2,f2phik2,  //additional ISR

pite1,pipx1,pipy1,pipz1,pite2,pipx2,pipy2,pipz2,pisigma1,pill1,pisigma2,pill2,
f1pite1,f1pipx1,f1pipy1,f1pipz1,f1pite2,f1pipx2,f1pipy2,f1pipz2, //(additional FSR)
f2pite1,f2pipx1,f2pipy1,f2pipz1,f2pite2,f2pipx2,f2pipy2,f2pipz2, //(additional ISR)
mute1,mupx1,mupy1,mupz1,mute2,mupx2,mupy2,mupz2,musigma1,mull1,musigma2,mull2,
f1mute1,f1mupx1,f1mupy1,f1mupz1,f1mute2,f1mupx2,f1mupy2,f1mupz2, //(additional FSR)
f2mute1,f2mupx1,f2mupy1,f2mupz1,f2mute2,f2mupx2,f2mupy2,f2mupz2, //(additional ISR)
kte1,kpx1,kpy1,kpz1,kte2,kpx2,kpy2,kpz2,ksigma1,kll1,ksigma2,kll2,
f1kte1,f1kpx1,f1kpy1,f1kpz1,f1kte2,f1kpx2,f1kpy2,f1kpz2, //(additional FSR)
f2kte1,f2kpx1,f2kpy1,f2kpz1,f2kte2,f2kpx2,f2kpy2,f2kpz2, //(additional ISR)

errtr1px, errtr1py, errtr1pz, // track resolution
errtr2px, errtr2py, errtr2pz,

x1,yy1,z1, //ISR photon
pix1,piy1,piz1,pix2,piy2,piz2, // vertices

charge1, charge2, //charges of the 2 tracks
beam_e, // beam energy
m_trk,  //track mass variable
mmpi_gen, // m(pipi) at glevel
mmmu_gen, // m(mumu) at glevel, assuming pi mass


dpie1,dpipx1,dpipy1,dpipz1, // decay tree
dpie2,dpipx2,dpipy2,dpipz2,
dmue1,dmupx1,dmupy1,dmupz1,
dmue2,dmupx2,dmupy2,dmupz2,

the_run, the_number,

kVarNum};


void
FitProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   HINtupleVarNames ntupleNames(kVarNum);

   ntupleNames.addVar(knshower,       "knshower");
   ntupleNames.addVar(kntrack,       "kntrack");

   ntupleNames.addVar(kntrack1shower,       "kntrack1shower");
   ntupleNames.addVar(kntrack2shower,       "kntrack2shower");

   ntupleNames.addVar(chisqvpi1,       "chisqvpi1");
   ntupleNames.addVar(chisqfpi1,       "chisqfpi1");
   ntupleNames.addVar(chisqvpi2,       "chisqvpi2");
   ntupleNames.addVar(chisqfpi2,       "chisqfpi2");

   ntupleNames.addVar(chisqvmu1,       "chisqvmu1");
   ntupleNames.addVar(chisqfmu1,       "chisqfmu1");
   ntupleNames.addVar(chisqvmu2,       "chisqvmu2");
   ntupleNames.addVar(chisqfmu2,       "chisqfmu2");

   ntupleNames.addVar(chisqvk1,       "chisqvk1");
   ntupleNames.addVar(chisqfk1,       "chisqfk1");
   ntupleNames.addVar(chisqvk2,       "chisqvk2");
   ntupleNames.addVar(chisqfk2,       "chisqfk2");

   ntupleNames.addVar(e1pi,          "e1pi");
   ntupleNames.addVar(th1pi,        "th1pi");
   ntupleNames.addVar(phi1pi,       "phi1pi");
   ntupleNames.addVar(e9251pi,    "e9251pi");

   ntupleNames.addVar(e1mu,          "e1mu");
   ntupleNames.addVar(th1mu,        "th1mu");
   ntupleNames.addVar(phi1mu,       "phi1mu");
   ntupleNames.addVar(e9251mu,    "e9251mu");

   ntupleNames.addVar(e1,          "e1");
   ntupleNames.addVar(th1,        "th1");
   ntupleNames.addVar(phi1,       "phi1");
   ntupleNames.addVar(e9251,    "e9251");

   ntupleNames.addVar(e2,          "e2");
   ntupleNames.addVar(th2,        "th2");
   ntupleNames.addVar(phi2,       "phi2");
   ntupleNames.addVar(e9252,    "e9252");

   ntupleNames.addVar(e3,          "e3");
   ntupleNames.addVar(th3,        "th3");
   ntupleNames.addVar(phi3,       "phi3");
   ntupleNames.addVar(e9253,    "e9253");

   ntupleNames.addVar(e4,          "e4");
   ntupleNames.addVar(th4,        "th4");
   ntupleNames.addVar(phi4,       "phi4");
   ntupleNames.addVar(e9254,    "e9254");

   ntupleNames.addVar(e5,          "e5");
   ntupleNames.addVar(th5,        "th5");
   ntupleNames.addVar(phi5,       "phi5");
   ntupleNames.addVar(e9255,    "e9255");

   ntupleNames.addVar(e6,          "e6");
   ntupleNames.addVar(th6,        "th6");
   ntupleNames.addVar(phi6,       "phi6");
   ntupleNames.addVar(e9256,    "e9256");

   ntupleNames.addVar(e7,          "e7");
   ntupleNames.addVar(th7,        "th7");
   ntupleNames.addVar(phi7,       "phi7");
   ntupleNames.addVar(e9257,    "e9257");

   ntupleNames.addVar(e8,          "e8");
   ntupleNames.addVar(th8,        "th8");
   ntupleNames.addVar(phi8,       "phi8");
   ntupleNames.addVar(e9258,    "e9258");

   ntupleNames.addVar(e9,          "e9");
   ntupleNames.addVar(th9,        "th9");
   ntupleNames.addVar(phi9,       "phi9");
   ntupleNames.addVar(e9259,    "e9259");

   ntupleNames.addVar(e10,          "e10");
   ntupleNames.addVar(th10,        "th10");
   ntupleNames.addVar(phi10,       "phi10");
   ntupleNames.addVar(e92510,    "e92510");

   ntupleNames.addVar(erre1,          "erre1");
   ntupleNames.addVar(errth1,        "errth1");
   ntupleNames.addVar(errphi1,       "errphi1");

   ntupleNames.addVar(erre2,          "erre2");
   ntupleNames.addVar(errth2,        "errth2");
   ntupleNames.addVar(errphi2,       "errphi2");

   ntupleNames.addVar(erre3,          "erre3");
   ntupleNames.addVar(errth3,        "errth3");
   ntupleNames.addVar(errphi3,       "errphi3");

   ntupleNames.addVar(erre4,          "erre4");
   ntupleNames.addVar(errth4,        "errth4");
   ntupleNames.addVar(errphi4,	  "errphi4");

   ntupleNames.addVar(erre5,          "erre5");
   ntupleNames.addVar(errth5,        "errth5");
   ntupleNames.addVar(errphi5,       "errphi5");

   ntupleNames.addVar(erre6,          "erre6");
   ntupleNames.addVar(errth6,        "errth6");
   ntupleNames.addVar(errphi6,	  "errphi6");

   ntupleNames.addVar(erre7,          "erre7");
   ntupleNames.addVar(errth7,        "errth7");
   ntupleNames.addVar(errphi7,       "errphi7");

   ntupleNames.addVar(erre8,          "erre8");
   ntupleNames.addVar(errth8,        "errth8");
   ntupleNames.addVar(errphi8,       "errphi8");

   ntupleNames.addVar(erre9,          "erre9");
   ntupleNames.addVar(errth9,        "errth9");
   ntupleNames.addVar(errphi9,       "errphi9");

   ntupleNames.addVar(erre10,          "erre10");
   ntupleNames.addVar(errth10,        "errth10");
   ntupleNames.addVar(errphi10,       "errphi10");


   ntupleNames.addVar(me1,          "me1");
   ntupleNames.addVar(eop1,          "eop1");
   ntupleNames.addVar(me2,          "me2");
   ntupleNames.addVar(eop2,          "eop2");

   ntupleNames.addVar(mudepth1,      "mudepth1");
   ntupleNames.addVar(mudepth2,      "mudepth2");

   ntupleNames.addVar(dd,          "dd");
   ntupleNames.addVar(width1,          "width1");
   ntupleNames.addVar(width2,          "width2");

   ntupleNames.addVar(f1epi1,          "f1epi1");
   ntupleNames.addVar(f1thpi1,        "f1thpi1");
   ntupleNames.addVar(f1phipi1,       "f1phipi1");

   ntupleNames.addVar(f1epi2,          "f1epi2");
   ntupleNames.addVar(f1thpi2,        "f1thpi2");
   ntupleNames.addVar(f1phipi2,       "f1phipi2");

   ntupleNames.addVar(f2epi1,          "f2epi1");
   ntupleNames.addVar(f2thpi1,        "f2thpi1");
   ntupleNames.addVar(f2phipi1,       "f2phipi1");

   ntupleNames.addVar(f2epi2,          "f2epi2");
   ntupleNames.addVar(f2thpi2,        "f2thpi2");
   ntupleNames.addVar(f2phipi2,       "f2phipi2");

   ntupleNames.addVar(f1emu1,          "f1emu1");
   ntupleNames.addVar(f1thmu1,        "f1thmu1");
   ntupleNames.addVar(f1phimu1,       "f1phimu1");

   ntupleNames.addVar(f1emu2,          "f1emu2");
   ntupleNames.addVar(f1thmu2,        "f1thmu2");
   ntupleNames.addVar(f1phimu2,       "f1phimu2");

   ntupleNames.addVar(f2emu1,          "f2emu1");
   ntupleNames.addVar(f2thmu1,        "f2thmu1");
   ntupleNames.addVar(f2phimu1,       "f2phimu1");

   ntupleNames.addVar(f2emu2,          "f2emu2");
   ntupleNames.addVar(f2thmu2,        "f2thmu2");
   ntupleNames.addVar(f2phimu2,       "f2phimu2");

   ntupleNames.addVar(f1ek1,          "f1ek1");
   ntupleNames.addVar(f1thk1,        "f1thk1");
   ntupleNames.addVar(f1phik1,       "f1phik1");

   ntupleNames.addVar(f1ek2,          "f1ek2");
   ntupleNames.addVar(f1thk2,        "f1thk2");
   ntupleNames.addVar(f1phik2,       "f1phik2");

   ntupleNames.addVar(f2ek1,          "f2ek1");
   ntupleNames.addVar(f2thk1,        "f2thk1");
   ntupleNames.addVar(f2phik1,       "f2phik1");

   ntupleNames.addVar(f2ek2,          "f2ek2");
   ntupleNames.addVar(f2thk2,        "f2thk2");
   ntupleNames.addVar(f2phik2,       "f2phik2");

   ntupleNames.addVar(pite1,    "pite1");
   ntupleNames.addVar(pipx1,    "pipx1");
   ntupleNames.addVar(pipy1,    "pipy1");
   ntupleNames.addVar(pipz1,    "pipz1");
   ntupleNames.addVar(pite2,    "pite2");
   ntupleNames.addVar(pipx2,    "pipx2");
   ntupleNames.addVar(pipy2,    "pipy2");
   ntupleNames.addVar(pipz2,    "pipz2");

   ntupleNames.addVar(mute1,    "mute1");
   ntupleNames.addVar(mupx1,    "mupx1");
   ntupleNames.addVar(mupy1,    "mupy1");
   ntupleNames.addVar(mupz1,    "mupz1");
   ntupleNames.addVar(mute2,    "mute2");
   ntupleNames.addVar(mupx2,    "mupx2");
   ntupleNames.addVar(mupy2,    "mupy2");
   ntupleNames.addVar(mupz2,    "mupz2");


   ntupleNames.addVar(kte1,    "kte1");
   ntupleNames.addVar(kpx1,    "kpx1");
   ntupleNames.addVar(kpy1,    "kpy1");
   ntupleNames.addVar(kpz1,    "kpz1");
   ntupleNames.addVar(kte2,    "kte2");
   ntupleNames.addVar(kpx2,    "kpx2");
   ntupleNames.addVar(kpy2,    "kpy2");
   ntupleNames.addVar(kpz2,    "kpz2");

   ntupleNames.addVar(errtr1px,    "errtr1px");
   ntupleNames.addVar(errtr1py,    "errtr1py");
   ntupleNames.addVar(errtr1pz,    "errtr1pz");
   ntupleNames.addVar(errtr2px,    "errtr2px");
   ntupleNames.addVar(errtr2py,    "errtr2py");
   ntupleNames.addVar(errtr2pz,    "errtr2pz");

   ntupleNames.addVar(x1,    "x1");
   ntupleNames.addVar(yy1,    "yy1");
   ntupleNames.addVar(z1,    "z1");
   ntupleNames.addVar(pix1,    "pix1");
   ntupleNames.addVar(piy1,    "piy1");
   ntupleNames.addVar(piz1,    "piz1");
   ntupleNames.addVar(pix2,    "pix2");
   ntupleNames.addVar(piy2,    "piy2");
   ntupleNames.addVar(piz2,    "piz2");


   ntupleNames.addVar(pisigma1, "pisigma1");
   ntupleNames.addVar(pill1,    "pill1");
   ntupleNames.addVar(pisigma2, "pisigma2");
   ntupleNames.addVar(pill2,    "pill2");

   ntupleNames.addVar(musigma1, "musigma1");
   ntupleNames.addVar(mull1,    "mull1");
   ntupleNames.addVar(musigma2, "musigma2");
   ntupleNames.addVar(mull2,    "mull2");

   ntupleNames.addVar(ksigma1, "ksigma1");
   ntupleNames.addVar(kll1,    "kll1");
   ntupleNames.addVar(ksigma2, "ksigma2");
   ntupleNames.addVar(kll2,    "kll2");

   ntupleNames.addVar(f1pite1,    "f1pite1");
   ntupleNames.addVar(f1pipx1,    "f1pipx1");
   ntupleNames.addVar(f1pipy1,    "f1pipy1");
   ntupleNames.addVar(f1pipz1,    "f1pipz1");
   ntupleNames.addVar(f1pite2,    "f1pite2");
   ntupleNames.addVar(f1pipx2,    "f1pipx2");
   ntupleNames.addVar(f1pipy2,    "f1pipy2");
   ntupleNames.addVar(f1pipz2,    "f1pipz2");

   ntupleNames.addVar(f2pite1,    "f2pite1");
   ntupleNames.addVar(f2pipx1,    "f2pipx1");
   ntupleNames.addVar(f2pipy1,    "f2pipy1");
   ntupleNames.addVar(f2pipz1,    "f2pipz1");
   ntupleNames.addVar(f2pite2,    "f2pite2");
   ntupleNames.addVar(f2pipx2,    "f2pipx2");
   ntupleNames.addVar(f2pipy2,    "f2pipy2");
   ntupleNames.addVar(f2pipz2,    "f2pipz2");

   ntupleNames.addVar(f1mute1,    "f1mute1");
   ntupleNames.addVar(f1mupx1,    "f1mupx1");
   ntupleNames.addVar(f1mupy1,    "f1mupy1");
   ntupleNames.addVar(f1mupz1,    "f1mupz1");
   ntupleNames.addVar(f1mute2,    "f1mute2");
   ntupleNames.addVar(f1mupx2,    "f1mupx2");
   ntupleNames.addVar(f1mupy2,    "f1mupy2");
   ntupleNames.addVar(f1mupz2,    "f1mupz2");

   ntupleNames.addVar(f2mute1,    "f2mute1");
   ntupleNames.addVar(f2mupx1,    "f2mupx1");
   ntupleNames.addVar(f2mupy1,    "f2mupy1");
   ntupleNames.addVar(f2mupz1,    "f2mupz1");
   ntupleNames.addVar(f2mute2,    "f2mute2");
   ntupleNames.addVar(f2mupx2,    "f2mupx2");
   ntupleNames.addVar(f2mupy2,    "f2mupy2");
   ntupleNames.addVar(f2mupz2,    "f2mupz2");

   ntupleNames.addVar(f1kte1,    "f1kte1");
   ntupleNames.addVar(f1kpx1,    "f1kpx1");
   ntupleNames.addVar(f1kpy1,    "f1kpy1");
   ntupleNames.addVar(f1kpz1,    "f1kpz1");
   ntupleNames.addVar(f1kte2,    "f1kte2");
   ntupleNames.addVar(f1kpx2,    "f1kpx2");
   ntupleNames.addVar(f1kpy2,    "f1kpy2");
   ntupleNames.addVar(f1kpz2,    "f1kpz2");

   ntupleNames.addVar(f2kte1,    "f2kte1");
   ntupleNames.addVar(f2kpx1,    "f2kpx1");
   ntupleNames.addVar(f2kpy1,    "f2kpy1");
   ntupleNames.addVar(f2kpz1,    "f2kpz1");
   ntupleNames.addVar(f2kte2,    "f2kte2");
   ntupleNames.addVar(f2kpx2,    "f2kpx2");
   ntupleNames.addVar(f2kpy2,    "f2kpy2");
   ntupleNames.addVar(f2kpz2,    "f2kpz2");

   ntupleNames.addVar(charge1,    "charge1");
   ntupleNames.addVar(charge2,    "charge2");

   ntupleNames.addVar(beam_e,"beam_e");
   ntupleNames.addVar(m_trk,"m_trk");
   ntupleNames.addVar(mmpi_gen,"mmpi_gen");
   ntupleNames.addVar(mmmu_gen,"mmmu_gen");


   ntupleNames.addVar(the_run,"the_run");
   ntupleNames.addVar(the_number,"the_number");

   ntupleNames.addVar(dpie1,          "dpie1");
   ntupleNames.addVar(dpipx1,         "dpipx1");
   ntupleNames.addVar(dpipy1,         "dpipy1");
   ntupleNames.addVar(dpipz1,         "dpipz1");
   ntupleNames.addVar(dpie2,          "dpie2");
   ntupleNames.addVar(dpipx2,         "dpipx2");
   ntupleNames.addVar(dpipy2,         "dpipy2");
   ntupleNames.addVar(dpipz2,         "dpipz2");
   ntupleNames.addVar(dmue1,          "dmue1");
   ntupleNames.addVar(dmupx1,         "dmupx1");
   ntupleNames.addVar(dmupy1,         "dmupy1");
   ntupleNames.addVar(dmupz1,         "dmupz1");
   ntupleNames.addVar(dmue2,          "dmue2");
   ntupleNames.addVar(dmupx2,         "dmupx2");
   ntupleNames.addVar(dmupy2,         "dmupy2");
   ntupleNames.addVar(dmupz2,         "dmupz2");


   m_showerTuple = iHistoManager.ntuple(10,"tuple", kVarNum, 10000, ntupleNames.names());


}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
FitProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   const int kMaxTrack = 2;
   const int kMaxShower = 10;

   double ChisqVpi1 = 10000000.;
   double ChisqFpi1 = 10000000.;
   double ChisqVpi2 = 10000000.;
   double ChisqFpi2 = 10000000.;
   double ChisqVmu1 = 10000000.;
   double ChisqFmu1 = 10000000.;
   double ChisqVmu2 = 10000000.;
   double ChisqFmu2 = 10000000.;
   double ChisqVk1 = 10000000.;
   double ChisqFk1 = 10000000.;
   double ChisqVk2 = 10000000.;
   double ChisqFk2 = 10000000.;
   double TempChisqVpi1 = 10000000.;
   double TempChisqFpi1 = 10000000.;
   double TempChisqVmu1 = 10000000.;
   double TempChisqFmu1 = 10000000.;
   double TempChisqVk1 = 10000000.;
   double TempChisqFk1 = 10000000.;

   double BEAME = -10.;
   double TRKM = -10.;
   double MMPI_GEN = -10.;
   double MMMU_GEN = -10.;

   double E1PI = -10.;
   double Theta1PI = -10.;
   double Phi1PI = -10.;
   double E9251PI = -10.;

   double E1MU = -10.;
   double Theta1MU = -10.;
   double Phi1MU = -10.;
   double E9251MU = -10.;

   double E[kMaxShower] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double Theta[kMaxShower] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double Phi[kMaxShower] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double E925[kMaxShower] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double ERRE[kMaxShower] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double ERRTheta[kMaxShower] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};
   double ERRPhi[kMaxShower] = {-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.,-10.};

   double ME[kMaxTrack] = {0.,0.};
   double EOP[kMaxTrack] = {0.,0.};
   double MUDEPTH[kMaxTrack] = {0.,0.};

   double DD = -10.;
   double WIDTH[kMaxTrack] = {-10.,-10.};

   double KN[kMaxTrack] = {0.,0.};

   double PIF1E[kMaxTrack] = {-10.,-10.};
   double PIF1Theta[kMaxTrack] = {-10.,-10.};
   double PIF1Phi[kMaxTrack] = {-10.,-10.};
   double PIF2E[kMaxTrack] = {-10.,-10.};
   double PIF2Theta[kMaxTrack] = {-10.,-10.};
   double PIF2Phi[kMaxTrack] = {-10.,-10.};
   double MUF1E[kMaxTrack] = {-10.,-10.};
   double MUF1Theta[kMaxTrack] = {-10.,-10.};
   double MUF1Phi[kMaxTrack] = {-10.,-10.};
   double MUF2E[kMaxTrack] = {-10.,-10.};
   double MUF2Theta[kMaxTrack] = {-10.,-10.};
   double MUF2Phi[kMaxTrack] = {-10.,-10.};
   double KF1E[kMaxTrack] = {-10.,-10.};
   double KF1Theta[kMaxTrack] = {-10.,-10.};
   double KF1Phi[kMaxTrack] = {-10.,-10.};
   double KF2E[kMaxTrack] = {-10.,-10.};
   double KF2Theta[kMaxTrack] = {-10.,-10.};
   double KF2Phi[kMaxTrack] = {-10.,-10.};

   double X = -10;
   double Y = -10;
   double Z = -10;
   double PIX[kMaxTrack] = {-10.,-10.};
   double PIY[kMaxTrack] = {-10.,-10.};
   double PIZ[kMaxTrack] = {-10.,-10.};

   double ERRTRPX[kMaxTrack] = {-10.,-10.};
   double ERRTRPY[kMaxTrack] = {-10.,-10.};
   double ERRTRPZ[kMaxTrack] = {-10.,-10.};

   double PIPE[kMaxTrack] = {-10.,-10.};
   double PIPX[kMaxTrack] = {-10.,-10.};
   double PIPY[kMaxTrack] = {-10.,-10.};
   double PIPZ[kMaxTrack] = {-10.,-10.};
   double MUPE[kMaxTrack] = {-10.,-10.};
   double MUPX[kMaxTrack] = {-10.,-10.};
   double MUPY[kMaxTrack] = {-10.,-10.};
   double MUPZ[kMaxTrack] = {-10.,-10.};
   double KPE[kMaxTrack] = {-10.,-10.};
   double KPX[kMaxTrack] = {-10.,-10.};
   double KPY[kMaxTrack] = {-10.,-10.};
   double KPZ[kMaxTrack] = {-10.,-10.};

   double PPISIGMA[kMaxTrack] = {-1000.,-1000.};
   double PPILL[kMaxTrack] = {-1000.,-1000.};
   double PMUSIGMA[kMaxTrack] = {-1000.,-1000.};
   double PMULL[kMaxTrack] = {-1000.,-1000.};
   double PKSIGMA[kMaxTrack] = {-1000.,-1000.};
   double PKLL[kMaxTrack] = {-1000.,-1000.};

   double PIF1PE[kMaxTrack] = {-10.,-10.};
   double PIF1PX[kMaxTrack] = {-10.,-10.};
   double PIF1PY[kMaxTrack] = {-10.,-10.};
   double PIF1PZ[kMaxTrack] = {-10.,-10.};
   double PIF2PE[kMaxTrack] = {-10.,-10.};
   double PIF2PX[kMaxTrack] = {-10.,-10.};
   double PIF2PY[kMaxTrack] = {-10.,-10.};
   double PIF2PZ[kMaxTrack] = {-10.,-10.};
   double MUF1PE[kMaxTrack] = {-10.,-10.};
   double MUF1PX[kMaxTrack] = {-10.,-10.};
   double MUF1PY[kMaxTrack] = {-10.,-10.};
   double MUF1PZ[kMaxTrack] = {-10.,-10.};
   double MUF2PE[kMaxTrack] = {-10.,-10.};
   double MUF2PX[kMaxTrack] = {-10.,-10.};
   double MUF2PY[kMaxTrack] = {-10.,-10.};
   double MUF2PZ[kMaxTrack] = {-10.,-10.};
   double KF1PE[kMaxTrack] = {-10.,-10.};
   double KF1PX[kMaxTrack] = {-10.,-10.};
   double KF1PY[kMaxTrack] = {-10.,-10.};
   double KF1PZ[kMaxTrack] = {-10.,-10.};
   double KF2PE[kMaxTrack] = {-10.,-10.};
   double KF2PX[kMaxTrack] = {-10.,-10.};
   double KF2PY[kMaxTrack] = {-10.,-10.};
   double KF2PZ[kMaxTrack] = {-10.,-10.};

   double CHARGE[kMaxTrack] = {0.,0.};

   double theRun = -10;
   double theNumber = -10;

   double ppi_e = 0;
   double ppi_px = 0;
   double ppi_py = 0;
   double ppi_pz = 0;
   double npi_e = 0;
   double npi_px = 0;
   double npi_py = 0;
   double npi_pz = 0;
   double pmu_e = 0;
   double pmu_px = 0;
   double pmu_py = 0;
   double pmu_pz = 0;
   double nmu_e = 0;
   double nmu_px = 0;
   double nmu_py = 0;
   double nmu_pz = 0;


   float tuple[kVarNum];



// if we're in MC, check to see if the trigger fired
   FAItem< DBEventHeader > eventHeader ;
   extract( iFrame.record( Stream::kEvent ), eventHeader ) ;

   theRun = eventHeader->run();
   theNumber = eventHeader->number();

   if( eventHeader->monteCarlo() ) {
      double L1Trigger = 0., L4Decision = 0.;


////////////////////////////////////////////////////////////////////////////
// Trigger L1
////////////////////////////////////////////////////////////////////////////
//   int l1Trigger = 0, l1Trigger_Sel = 0, l1Trigger_Hadron = 0;
//   int l1Trigger_MuPair = 0, l1Trigger_ElTrack = 0, l1Trigger_RadTau = 0;
//   int l1Trigger_TwoTrack = 0;

      FAItem< TriggerL1Data > trigDat;
      extract (iFrame.record(Stream::kEvent), trigDat);

// All possible trigger lines
// --------------------------
// DABoolean isHadron() const;  //Ax track > 2 & CB lo > 0
// DABoolean isMuPair() const;  //Hi track > 1 & Back-to-back, 1 vs. 3/24
// DABoolean isElTrack() const;  //Ax track > 0 & CB med > 0
// DABoolean isRadTau() const;  //Stereo (hi + low) track > 1 & CB lo > 0
// DABoolean isBarrelBhabha() const; //Back-to-back Hi CB clusters

// DABoolean isCBSingleHi() const;  //CB hi > 0
// DABoolean isCESingleHi() const;  //CE hi > 0
// DABoolean isEndcapBhabha() const; //CE hi clusters in opposite ends
// DABoolean isTwoTrack() const; //Ax track > 1
// DABoolean isPulser() const;  //Pulser trigger
// DABoolean isRandom() const;  //Random trigger
// DABoolean isMinBias() const; //Tracking or CB Timing bit (Ax>0 || CB lo>1)
      // Decode trigger line information //

      // L1 Accept if any trigger line fires

      if(trigDat->isHadron()) L1Trigger = 1.;
      if(trigDat->isRadTau()) L1Trigger = 2.;
      if(trigDat->isElTrack()) L1Trigger = 3.;
      if(trigDat->isBarrelBhabha()) L1Trigger = 4.;
      if(trigDat->isEndcapBhabha()) L1Trigger = 5.;
      if(trigDat->isMuPair()) L1Trigger = 6.;
      if(trigDat->isCBSingleHi()) L1Trigger = 7.;
      if(trigDat->isCESingleHi()) L1Trigger = 8.;
      if(trigDat->isPulser()) L1Trigger = 9.;
      if(trigDat->isRandom()) L1Trigger = 10.;
      if(trigDat->isTwoTrack()) L1Trigger = 11.;
      if(trigDat->isMinBias()) L1Trigger = 12.;
      if(trigDat->isPhotonA()) L1Trigger = 13.;
      if(trigDat->isPhotonB()) L1Trigger = 14.;
      if(trigDat->isPhotonC()) L1Trigger = 15.;
      if(trigDat->isPhotonD()) L1Trigger = 16.;

      // L1 Accept if any non-prescaled trigger line fires
//   if ( (trigDat->isHadron())       ||
//      (trigDat->isMuPair())       ||
//      (trigDat->isElTrack())      ||
//      (trigDat->isRadTau())       ||
//      (trigDat->isBarrelBhabha())  )
//   { l1Trigger_Sel = 1; }

////////////////////////////////////////////////////////////////////////////
// Software Trigger (L3 & L4)
////////////////////////////////////////////////////////////////////////////
      FAItem<Level4Decision > decision;
      extract(iFrame.record(Stream::kEvent), decision );

      switch( decision->decision() )
      {
         case Level4Decision::kKeepLevel3Garbage :
         {
            L4Decision = 1.;
            break;
         }
         case Level4Decision::kLevel3AutoAccept :
         {
            L4Decision = 2.;
            break;
         }
         case Level4Decision::kLevel4Keep :
         {
            L4Decision = 3.;
            break;
         }
      }

      if( (!L1Trigger) || (!L4Decision) )
         return ActionBase::kFailed;
   }




////////////////////////////////////// decay tree  ///////////////////////////////////////


HepLorentzVector pip4v, pim4v;
if( eventHeader->monteCarlo() ) {
        FAItem< MCDecayTree > decayTree;
        extract(iFrame.record(Stream::kEvent), decayTree, "Generator" );
        const MCDecayTree& mcDecayTree(*decayTree);
        // report(INFO, kFacilityString) << mcDecayTree << endl;

        int ngam = 0;
        for(MCDecayTree::const_pIterator it = decayTree->pBegin();
            it != decayTree->pEnd(); it++) {

                if( it->properties().PDGId() == 211 )
                        pip4v = it->lorentzMomentum(); 
                else if( it->properties().PDGId() == -211 )
                        pim4v = it->lorentzMomentum(); 
                else if( ( it->properties().PDGId() == -13 ) ) {
                        pmu_px = it->px();
                        pmu_py = it->py();
                        pmu_pz = it->pz();
//     pmu_e  = it->energy();
                        pmu_e = sqrt(pow(it->px(),2)+pow(it->py(),2)+pow(it->pz(),2)+pow(0.13957,2)); // assume pi+ mass
                }
                else if( ( it->properties().PDGId() == 13 ) ) {
                        nmu_px = it->px();
                        nmu_py = it->py();
                        nmu_pz = it->pz();
//     nmu_e  = it->energy();
                        nmu_e = sqrt(pow(it->px(),2)+pow(it->py(),2)+pow(it->pz(),2)+pow(0.13957,2)); // assume pi- mass
                }
       	}


        MMPI_GEN = (pip4v + pim4v).m();

        MMMU_GEN = sqrt(pow((pmu_e+nmu_e),2)
                       -pow((pmu_px+nmu_px),2)
                       -pow((pmu_py+nmu_py),2)
                       -pow((pmu_pz+nmu_pz),2));

}



////////////////////////////////////// only 2 opposite charged tracks /////////////////////



   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable, "GoodThings"  );

   FATable< NavTrack >::const_iterator trackBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackEnd = trackTable.end();

   if(trackTable.size() != 2)
      return ActionBase::kFailed;

   FAItem<TDKinematicFit> tr1 = (*trackBegin).pionFit();
   FAItem<TDKinematicFit> tr2 = (*(trackBegin+1)).pionFit();

   CHARGE[0] = (*tr1).charge();
   CHARGE[1] = (*tr2).charge();

   if(CHARGE[0]!=-CHARGE[1] || CHARGE[0]==0)
      return ActionBase::kFailed;



   if(trackBegin->trackShowerMatch().valid() && (trackBegin+1)->trackShowerMatch().valid()) {
     DD = (trackBegin+1)->trackShowerMatch()->navShowers().front().distance(trackBegin->trackShowerMatch()->navShowers().front());
   }

//   FAItem<TDKinematicFit> trmu1 = (*trackBegin).muonFit();
//   FAItem<TDKinematicFit> trmu2 = (*(trackBegin+1)).muonFit();
//   FAItem<TDKinematicFit> trk1 = (*trackBegin).kaonFit();
//   FAItem<TDKinematicFit> trk2 = (*(trackBegin+1)).kaonFit();

//   if((*trmu1).charge()!=(*trmu2).charge() || (*trmu1).charge()==0)
//      return ActionBase::kFailed;

//   if((*trk1).charge()!=(*trk2).charge() || (*trk1).charge()==0)
//      return ActionBase::kFailed;


   int unmatchedTracks = 0;

   for ( FATable< NavTrack >::const_iterator trackItr = trackBegin;
         trackItr != trackEnd ;
         ++trackItr )
   {
      FAItem<DedxInfo> the_dedx = (*trackItr).dedxInfo();
      FAItem<NavRich> the_rich = (*trackItr).richInfo();
      FAItem<TDKinematicFit> pionFit = (*trackItr).pionFit();
      FAItem<TDKinematicFit> muonFit = (*trackItr).muonFit();
      FAItem<TDKinematicFit> kaonFit = (*trackItr).kaonFit();
      double cos_theta1 = pionFit->pz() / pionFit->pmag();
      double cos_theta2 = muonFit->pz() / muonFit->pmag();
      double cos_theta3 = kaonFit->pz() / kaonFit->pmag();

      int j = unmatchedTracks++;

      if(j < kMaxTrack){

      if(trackItr->trackShowerMatch().valid()) {
        ME[j] = trackItr->trackShowerMatch()->matchedEnergy();
        KN[j] = trackItr->trackShowerMatch()->navShowers().size();
        WIDTH[j] = trackItr->trackShowerMatch()->navShowers().front().attributes().width();
     }
      EOP[j] = trackItr->elecId().eOverP();
      MUDEPTH[j] = trackItr->muonId().depth();

//      if(EOP[j]>0.85)
//        return ActionBase::kFailed;

      if( (pionFit.valid()) && (the_dedx.valid()) )  {

        PIPE[j]=pionFit->lorentzMomentum().e();
        PIPX[j]=pionFit->px();
        PIPY[j]=pionFit->py();
        PIPZ[j]=pionFit->pz();
        PIX[j]=pionFit->x();
        PIY[j]=pionFit->y();
        PIZ[j]=pionFit->z();

        ERRTRPX[j]=sqrt(pionFit->errorMatrix()(KTKinematicData::kPx,KTKinematicData::kPx));
        ERRTRPY[j]=sqrt(pionFit->errorMatrix()(KTKinematicData::kPy,KTKinematicData::kPy));
        ERRTRPZ[j]=sqrt(pionFit->errorMatrix()(KTKinematicData::kPz,KTKinematicData::kPz));


        PPISIGMA[j]=the_dedx->piSigma();

        if ((the_rich.valid()) && (fabs(cos_theta1) < 0.8) && (the_rich->pionHypWasAnalyzed()))
          PPILL[j]=the_rich->pionLogLikelihood();
      }

      if( (muonFit.valid()) && (the_dedx.valid()) )  {

        MUPE[j]=muonFit->lorentzMomentum().e();
        MUPX[j]=muonFit->px();
        MUPY[j]=muonFit->py();
        MUPZ[j]=muonFit->pz();
        PMUSIGMA[j]=the_dedx->muSigma();

        if ((the_rich.valid()) && (fabs(cos_theta2) < 0.8) && (the_rich->muonHypWasAnalyzed()))
          PMULL[j]=the_rich->muonLogLikelihood();
      }

      if( (kaonFit.valid()) && (the_dedx.valid()) )  {

        KPE[j]=kaonFit->lorentzMomentum().e();
        KPX[j]=kaonFit->px();
        KPY[j]=kaonFit->py();
        KPZ[j]=kaonFit->pz();
        PKSIGMA[j]=the_dedx->kSigma();

        if ((the_rich.valid()) && (fabs(cos_theta3) < 0.8) && (the_rich->kaonHypWasAnalyzed()))
        PKLL[j]=the_rich->kaonLogLikelihood();
      }
      }
   }


/////////////////////////////// ISR shower E > 500 MeV //////////////////////////////////////

   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ) , showerTable, "GoodThings" );

   if(showerTable.size()==0)
      return ActionBase::kFailed;

   FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
   FATable< NavShower >::const_iterator showerEnd = showerTable.end();

   FATable< NavShower >::const_iterator fastest_shower = showerBegin;
   if(fastest_shower->attributes().x925() < 1)
      return ActionBase::kFailed;
   if(fastest_shower->attributes().energy() < 0.5)
      return ActionBase::kFailed;

   X = fastest_shower->attributes().position().x();
   Y = fastest_shower->attributes().position().y();
   Z = fastest_shower->attributes().position().z();

   int unmatchedShowers = 0;

   for ( FATable< NavShower >::const_iterator showerItr = showerBegin;
         showerItr != showerEnd ;
         ++showerItr )
   {

      int j = unmatchedShowers++;

      if(j<kMaxShower){

        E[j] = showerItr->attributes().energy();
        Theta[j] = showerItr->attributes().theta();
        Phi[j] = showerItr->attributes().phi();
        E925[j] = showerItr->attributes().x925();
        ERRE[j] = showerItr->attributes().errEnergy();
        ERRTheta[j] = showerItr->attributes().errTheta();
        ERRPhi[j] = showerItr->attributes().errPhi();

      }
   }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////// chisq fitting ///////////////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


FAItem<TDKinematicFit> pi1 = (*trackBegin).pionFit();
FAItem<TDKinematicFit> pi2 = (*(trackBegin+1)).pionFit();
FAItem<TDKinematicFit> mu1 = (*trackBegin).muonFit();
FAItem<TDKinematicFit> mu2 = (*(trackBegin+1)).muonFit();
FAItem<TDKinematicFit> k1 = (*trackBegin).kaonFit();
FAItem<TDKinematicFit> k2 = (*(trackBegin+1)).kaonFit();




/////////////////////////////////  situation 1  //////////////////////////////////////////////////////////////////

NavShowerServer *navsh_server = new NavShowerServer( iFrame.record(Stream::kEvent ) ) ;

//CcBasicShowerAttsArg basic_atts (fastest_shower->attributes().basicShowerAtts() );
CcFortranShowerCorrector *sh_corr = new CcFortranShowerCorrector ;

const CcShowerAttributes &atts = fastest_shower->attributes();

CcShowerAttributes new_atts ( atts.basicShowerAtts(),
				       *sh_corr,
				       atts.energy(),
				       10,
				       10,
				       atts.theta(),
				       atts.errTheta(),
				       atts.uncErrTheta(),
				       atts.phi(),
				       atts.errPhi(),
				       atts.uncErrPhi(),
				       atts.distance(),
				       atts.momentum(),
				       atts.position(),
				       atts.origin(),
				       atts.errMatMom(),
				       atts.errMatPos(),
				       atts.errMatOri(),
				       atts.status() );
NavShower *tmp_sh =  new NavShower( new_atts, *navsh_server )  ;


//cerr << "old error = " << fastest_shower->attributes().errEnergy()
//	      << "   new error = " << tmp_sh->attributes().errEnergy() << endl << endl;


////////////////////////////////// fit 1: add.FSR /////////////////////////////////////////////////////////////////////




if(showerTable.size() > 1){

   for ( FATable< NavShower >::const_iterator showerItr = showerBegin+1;
         showerItr != showerEnd ;
         ++showerItr ) {

   if(showerItr->attributes().x925() < 1)  continue;

   // do the pion fit

   FitEvt pipi1( "Pipi1", FitEvt::k_P4VecCM );
   pipi1.newPhoton(*tmp_sh);
   pipi1.newPhoton(*showerItr);
   pipi1.newTrack(*pi1);
   pipi1.newTrack(*pi2);
   pipi1.doTheFit();

   if( (pipi1.chisqVtx()>0) && (pipi1.chisqFit()>0) ) {
   // fit converged  -  save this event

      HepLorentzVector vgpi (pipi1.kdFitVec()[0]->lorentzMomentum());
      HepLorentzVector v0pi (pipi1.kdFitVec()[1]->lorentzMomentum());
      HepLorentzVector v1pi (pipi1.kdFitVec()[2]->lorentzMomentum());
      HepLorentzVector v2pi (pipi1.kdFitVec()[3]->lorentzMomentum());

      TempChisqVpi1 = pipi1.chisqVtx();
      TempChisqFpi1 = pipi1.chisqFit();

      if(TempChisqFpi1 < ChisqFpi1){

        ChisqVpi1 = pipi1.chisqVtx();
        ChisqFpi1 = pipi1.chisqFit();

        E1PI = showerItr->attributes().energy();
        Theta1PI = showerItr->attributes().theta();
        Phi1PI = showerItr->attributes().phi();
        E9251PI = showerItr->attributes().x925();

        PIF1E[0] = vgpi.e();
        PIF1Theta[0] = vgpi.theta();
        PIF1Phi[0] = vgpi.phi();

        PIF1E[1] = v0pi.e();
        PIF1Theta[1] = v0pi.theta();
        PIF1Phi[1] = v0pi.phi();

        PIF1PE[0]=v1pi.e();
        PIF1PX[0]=v1pi.px();
        PIF1PY[0]=v1pi.py();
        PIF1PZ[0]=v1pi.pz();

        PIF1PE[1]=v2pi.e();
        PIF1PX[1]=v2pi.px();
        PIF1PY[1]=v2pi.py();
        PIF1PZ[1]=v2pi.pz();
      }
   }

   // do the muon fit

   FitEvt mumu1( "Mumu1", FitEvt::k_P4VecCM );
   mumu1.newPhoton(*tmp_sh);
   mumu1.newPhoton(*showerItr);
   mumu1.newTrack(*mu1);
   mumu1.newTrack(*mu2);
   mumu1.doTheFit();


   if( (mumu1.chisqVtx()>0) && (mumu1.chisqFit()>0) ) {
   // fit converged  -  save this event

      HepLorentzVector vgmu (mumu1.kdFitVec()[0]->lorentzMomentum());
      HepLorentzVector v0mu (mumu1.kdFitVec()[1]->lorentzMomentum());
      HepLorentzVector v1mu (mumu1.kdFitVec()[2]->lorentzMomentum());
      HepLorentzVector v2mu (mumu1.kdFitVec()[3]->lorentzMomentum());

      TempChisqVmu1 = mumu1.chisqVtx();
      TempChisqFmu1 = mumu1.chisqFit();

      if(TempChisqFmu1 < ChisqFmu1){
        ChisqVmu1 = mumu1.chisqVtx();
        ChisqFmu1 = mumu1.chisqFit();

        E1MU = showerItr->attributes().energy();
        Theta1MU = showerItr->attributes().theta();
        Phi1MU = showerItr->attributes().phi();
        E9251MU = showerItr->attributes().x925();

        MUF1E[0] = vgmu.e();
        MUF1Theta[0] = vgmu.theta();
        MUF1Phi[0] = vgmu.phi();

        MUF1E[1] = v0mu.e();
        MUF1Theta[1] = v0mu.theta();
        MUF1Phi[1] = v0mu.phi();

        MUF1PE[0]=v1mu.e();
        MUF1PX[0]=v1mu.px();
        MUF1PY[0]=v1mu.py();
        MUF1PZ[0]=v1mu.pz();

        MUF1PE[1]=v2mu.e();
        MUF1PX[1]=v2mu.px();
        MUF1PY[1]=v2mu.py();
        MUF1PZ[1]=v2mu.pz();
     }
   }

   // do the kaon fit
   if ((*k1).charge()!=0 && (*k2).charge()!=0) {

   FitEvt kk1( "Kk1", FitEvt::k_P4VecCM );
   kk1.newPhoton(*tmp_sh);
   kk1.newPhoton(*showerItr);
   kk1.newTrack(*k1);
   kk1.newTrack(*k2);
   kk1.doTheFit();

   if( (kk1.chisqVtx()>0) && (kk1.chisqFit()>0) ) {
   // fit converged  -  save this event

      HepLorentzVector vgk (kk1.kdFitVec()[0]->lorentzMomentum());
      HepLorentzVector v0k (kk1.kdFitVec()[1]->lorentzMomentum());
      HepLorentzVector v1k (kk1.kdFitVec()[2]->lorentzMomentum());
      HepLorentzVector v2k (kk1.kdFitVec()[3]->lorentzMomentum());

      TempChisqVk1 = kk1.chisqVtx();
      TempChisqFk1 = kk1.chisqFit();

      if(TempChisqFk1 < ChisqFk1){
        ChisqVk1 = kk1.chisqVtx();
        ChisqFk1 = kk1.chisqFit();

        KF1E[0] = vgk.e();
        KF1Theta[0] = vgk.theta();
        KF1Phi[0] = vgk.phi();
 
        KF1E[1] = v0k.e();
        KF1Theta[1] = v0k.theta();
        KF1Phi[1] = v0k.phi();

        KF1PE[0]=v1k.e();
        KF1PX[0]=v1k.px();
        KF1PY[0]=v1k.py();
        KF1PZ[0]=v1k.pz();

        KF1PE[1]=v2k.e();
        KF1PX[1]=v2k.px();
        KF1PY[1]=v2k.py();
        KF1PZ[1]=v2k.pz();
      }
   }
  }
  }
}

///////////////////////////////  situation 2   ///////////////////////////////////////////////////////////////////


FAItem< BeamSpot > spot;
extract( iFrame.record( Stream::kBeginRun ), spot );

HepVector3D momentum(0,0,0.001);
HepVector3D position(spot->center());

FAItem< BeamEnergy > beam_energy;
extract( iFrame.record( Stream::kBeginRun ), beam_energy );
BEAME = beam_energy->value();

double mass = 0;
double charge = 0;

HepSymMatrix errMatrix((*mu1).errorMatrix());

HepSymMatrix errMatXyz(spot->errMat());

for(int i=1; i<=2; i++){
  for(int j=1; j<=2; j++)
    errMatrix(i,j) = 0;
  for(int k=3; k<=4; k++)
    errMatrix(i,k) = 0;
  for(int l=5; l<=7; l++)
    errMatrix(i,l) = 0;
}


for(int i=3; i<=4; i++){
  for(int j=1; j<=2; j++)
    errMatrix(i,j) = 0;
  for(int k=3; k<=4; k++)
    errMatrix(i,k) = 10;
  for(int l=5; l<=7; l++)
    errMatrix(i,l) = 0;

}

for(int i=5; i<=7; i++){
  for(int j=1; j<=4; j++)
    errMatrix(i,j) = 0;
}


errMatrix(5,5) = errMatXyz(1,1);
errMatrix(5,6) = errMatXyz(1,2);
errMatrix(5,7) = errMatXyz(1,3);
errMatrix(6,5) = errMatXyz(2,1);
errMatrix(6,6) = errMatXyz(2,2);
errMatrix(6,7) = errMatXyz(2,3);
errMatrix(7,5) = errMatXyz(3,1);
errMatrix(7,6) = errMatXyz(3,2);
errMatrix(7,7) = errMatXyz(3,3);


//cout << "undetected shower error:" << errMatrix << endl;

KTKinematicData undetected_shower(momentum, position, mass, charge, errMatrix);



///////////////////////////////////////// fit 2: add.ISR ///////////////////////////////////////////////////////

   // do the pion fit

   FitEvt pipi2( "Pipi2", FitEvt::k_P4VecCM );
   pipi2.newPhoton(*tmp_sh);
   pipi2.newKinDat(undetected_shower);
   pipi2.newTrack(*pi1);
   pipi2.newTrack(*pi2);
   pipi2.doTheFit();

//cout << pipi2.chisqVtx() << "  "  <<pipi2.chisqFit() << endl;

   if( (pipi2.chisqVtx()>0) && (pipi2.chisqFit()>0) ) {
   // fit converged  -  save this event

      const HepLorentzVector vgpi2 (pipi2.kdFitVec()[0]->lorentzMomentum());
      const HepLorentzVector v0pi2 (pipi2.kdFitVec()[1]->lorentzMomentum());
      const HepLorentzVector v1pi2 (pipi2.kdFitVec()[2]->lorentzMomentum());
      const HepLorentzVector v2pi2 (pipi2.kdFitVec()[3]->lorentzMomentum());

      ChisqVpi2 = pipi2.chisqVtx();
      ChisqFpi2 = pipi2.chisqFit();

      PIF2E[0] = vgpi2.e();
      PIF2Theta[0] = vgpi2.theta();
      PIF2Phi[0] = vgpi2.phi();

      PIF2E[1] = v0pi2.e();
      PIF2Theta[1] = v0pi2.theta();
      PIF2Phi[1] = v0pi2.phi();

      PIF2PE[0]=v1pi2.e();
      PIF2PX[0]=v1pi2.px();
      PIF2PY[0]=v1pi2.py();
      PIF2PZ[0]=v1pi2.pz();

      PIF2PE[1]=v2pi2.e();
      PIF2PX[1]=v2pi2.px();
      PIF2PY[1]=v2pi2.py();
      PIF2PZ[1]=v2pi2.pz();
   }


   // do the muon fit

   FitEvt mumu2( "Mumu2", FitEvt::k_P4VecCM );
   mumu2.newPhoton(*tmp_sh);
   mumu2.newKinDat(undetected_shower);
   mumu2.newTrack(*mu1);
   mumu2.newTrack(*mu2);
   mumu2.doTheFit();

   if( (mumu2.chisqVtx()>0) && (mumu2.chisqFit()>0) ) {
   // fit converged  -  save this event

      const HepLorentzVector vgmu2 (mumu2.kdFitVec()[0]->lorentzMomentum());
      const HepLorentzVector v0mu2 (mumu2.kdFitVec()[1]->lorentzMomentum());
      const HepLorentzVector v1mu2 (mumu2.kdFitVec()[2]->lorentzMomentum());
      const HepLorentzVector v2mu2 (mumu2.kdFitVec()[3]->lorentzMomentum());

      ChisqVmu2 = mumu2.chisqVtx();
      ChisqFmu2 = mumu2.chisqFit();

      MUF2E[0] = vgmu2.e();
      MUF2Theta[0] = vgmu2.theta();
      MUF2Phi[0] = vgmu2.phi();

      MUF2E[1] = v0mu2.e();
      MUF2Theta[1] = v0mu2.theta();
      MUF2Phi[1] = v0mu2.phi();

      MUF2PE[0]=v1mu2.e();
      MUF2PX[0]=v1mu2.px();
      MUF2PY[0]=v1mu2.py();
      MUF2PZ[0]=v1mu2.pz();

      MUF2PE[1]=v2mu2.e();
      MUF2PX[1]=v2mu2.px();
      MUF2PY[1]=v2mu2.py();
      MUF2PZ[1]=v2mu2.pz();
   }

   // do the kaon fit
   if ((*k1).charge()!=0 && (*k2).charge()!=0) {

   FitEvt kk2( "Kk2", FitEvt::k_P4VecCM );
   kk2.newPhoton(*tmp_sh);
   kk2.newKinDat(undetected_shower);
   kk2.newTrack(*k1);
   kk2.newTrack(*k2);
   kk2.doTheFit();

   if( (kk2.chisqVtx()>0) && (kk2.chisqFit()>0) ) {
   // fit converged  -  save this event

      const HepLorentzVector vgk2 (kk2.kdFitVec()[0]->lorentzMomentum());
      const HepLorentzVector v0k2 (kk2.kdFitVec()[1]->lorentzMomentum());
      const HepLorentzVector v1k2 (kk2.kdFitVec()[2]->lorentzMomentum());
      const HepLorentzVector v2k2 (kk2.kdFitVec()[3]->lorentzMomentum());

      ChisqVk2 = kk2.chisqVtx();
      ChisqFk2 = kk2.chisqFit();

      KF2E[0] = vgk2.e();
      KF2Theta[0] = vgk2.theta();
      KF2Phi[0] = vgk2.phi();

      KF2E[1] = v0k2.e();
      KF2Theta[1] = v0k2.theta();
      KF2Phi[1] = v0k2.phi();

      KF2PE[0]=v1k2.e();
      KF2PX[0]=v1k2.px();
      KF2PY[0]=v1k2.py();
      KF2PZ[0]=v1k2.pz();

      KF2PE[1]=v2k2.e();
      KF2PX[1]=v2k2.px();
      KF2PY[1]=v2k2.py();
      KF2PZ[1]=v2k2.pz();
   }
   }

delete tmp_sh;
delete navsh_server;
delete sh_corr;



   double s = pow((2*BEAME),2);
   double pppn = sqrt(pow((PIPX[0]+PIPX[1]),2)+pow((PIPY[0]+PIPY[1]),2)+pow((PIPZ[0]+PIPZ[1]),2));
   double pp2 = pow(PIPX[0],2)+pow(PIPY[0],2)+pow(PIPZ[0],2);
   double pn2 = pow(PIPX[1],2)+pow(PIPY[1],2)+pow(PIPZ[1],2);
   double mm = (pow((pow((sqrt(s)-pppn),2)-pp2-pn2),2)-4*pp2*pn2)/(4*pow((sqrt(s)-pppn),2));
//   if(PIPX[0]<1000 && PIPY[0]<1000 && PIPZ[0] < 1000 && PIPX[1]<1000 && PIPY[1]<1000 && PIPZ[1] < 1000)
   TRKM = sqrt(mm);

   tuple[the_run] = theRun;
   tuple[the_number] = theNumber;


   tuple[knshower] = unmatchedShowers;
   tuple[kntrack] = unmatchedTracks;

   tuple[chisqvpi1] = ChisqVpi1;
   tuple[chisqfpi1] = ChisqFpi1;
   tuple[chisqvpi2] = ChisqVpi2;
   tuple[chisqfpi2] = ChisqFpi2;

   tuple[chisqvmu1] = ChisqVmu1;
   tuple[chisqfmu1] = ChisqFmu1;
   tuple[chisqvmu2] = ChisqVmu2;
   tuple[chisqfmu2] = ChisqFmu2;

   tuple[chisqvk1] = ChisqVk1;
   tuple[chisqfk1] = ChisqFk1;
   tuple[chisqvk2] = ChisqVk2;
   tuple[chisqfk2] = ChisqFk2;

   tuple[e1pi] = E1PI;
   tuple[th1pi] = Theta1PI;
   tuple[phi1pi] = Phi1PI;
   tuple[e9251pi] = E9251PI;

   tuple[e1mu] = E1MU;
   tuple[th1mu] = Theta1MU;
   tuple[phi1mu] = Phi1MU;
   tuple[e9251mu] = E9251MU;

   tuple[e1] = E[0];
   tuple[th1] = Theta[0];
   tuple[phi1] = Phi[0];
   tuple[e9251] = E925[0];

   tuple[e2] = E[1];
   tuple[th2] = Theta[1];
   tuple[phi2] = Phi[1];
   tuple[e9252] = E925[1];

   tuple[e3] = E[2];
   tuple[th3] = Theta[2];
   tuple[phi3] = Phi[2];
   tuple[e9253] = E925[2];

   tuple[e4] = E[3];
   tuple[th4] = Theta[3];
   tuple[phi4] = Phi[3];
   tuple[e9254] = E925[3];

   tuple[e5] = E[4];
   tuple[th5] = Theta[4];
   tuple[phi5] = Phi[4];
   tuple[e9255] = E925[4];

   tuple[e6] = E[5];
   tuple[th6] = Theta[5];
   tuple[phi6] = Phi[5];
   tuple[e9256] = E925[5];

   tuple[e7] = E[6];
   tuple[th7] = Theta[6];
   tuple[phi7] = Phi[6];
   tuple[e9257] = E925[6];

   tuple[e8] = E[7];
   tuple[th8] = Theta[7];
   tuple[phi8] = Phi[7];
   tuple[e9258] = E925[7];

   tuple[e9] = E[8];
   tuple[th9] = Theta[8];
   tuple[phi9] = Phi[8];
   tuple[e9259] = E925[8];

   tuple[e10] = E[9];
   tuple[th10] = Theta[9];
   tuple[phi10] = Phi[9];
   tuple[e92510] = E925[9];

   tuple[erre1] = ERRE[0];
   tuple[errth1] = ERRTheta[0];
   tuple[errphi1] = ERRPhi[0];

   tuple[erre2] = ERRE[1];
   tuple[errth2] = ERRTheta[1];
   tuple[errphi2] = ERRPhi[1];

   tuple[erre3] = ERRE[2];
   tuple[errth3] = ERRTheta[2];
   tuple[errphi3] = ERRPhi[2];

   tuple[erre4] = ERRE[3];
   tuple[errth4] = ERRTheta[3];
   tuple[errphi4] = ERRPhi[3];

   tuple[erre5] = ERRE[4];
   tuple[errth5] = ERRTheta[4];
   tuple[errphi5] = ERRPhi[4];

   tuple[erre6] = ERRE[5];
   tuple[errth6] = ERRTheta[5];
   tuple[errphi6] = ERRPhi[5];

   tuple[erre7] = ERRE[6];
   tuple[errth7] = ERRTheta[6];
   tuple[errphi7] = ERRPhi[6];

   tuple[erre8] = ERRE[7];
   tuple[errth8] = ERRTheta[7];
   tuple[errphi8] = ERRPhi[7];

   tuple[erre9] = ERRE[8];
   tuple[errth9] = ERRTheta[8];
   tuple[errphi9] = ERRPhi[8];

   tuple[erre10] = ERRE[9];
   tuple[errth10] = ERRTheta[9];
   tuple[errphi10] = ERRPhi[9];


   tuple[f1epi1] = PIF1E[0];
   tuple[f1thpi1] = PIF1Theta[0];
   tuple[f1phipi1] = PIF1Phi[0];
   tuple[f1epi2] = PIF1E[1];
   tuple[f1thpi2] = PIF1Theta[1];
   tuple[f1phipi2] = PIF1Phi[1];
   tuple[f2epi1] = PIF2E[0];
   tuple[f2thpi1] = PIF2Theta[0];
   tuple[f2phipi1] = PIF2Phi[0];
   tuple[f2epi2] = PIF2E[1];
   tuple[f2thpi2] = PIF2Theta[1];
   tuple[f2phipi2] = PIF2Phi[1];

   tuple[f1emu1] = MUF1E[0];
   tuple[f1thmu1] = MUF1Theta[0];
   tuple[f1phimu1] = MUF1Phi[0];
   tuple[f1emu2] = MUF1E[1];
   tuple[f1thmu2] = MUF1Theta[1];
   tuple[f1phimu2] = MUF1Phi[1];
   tuple[f2emu1] = MUF2E[0];
   tuple[f2thmu1] = MUF2Theta[0];
   tuple[f2phimu1] = MUF2Phi[0];
   tuple[f2emu2] = MUF2E[1];
   tuple[f2thmu2] = MUF2Theta[1];
   tuple[f2phimu2] = MUF2Phi[1];

   tuple[f1ek1] = KF1E[0];
   tuple[f1thk1] = KF1Theta[0];
   tuple[f1phik1] = KF1Phi[0];
   tuple[f1ek2] = KF1E[1];
   tuple[f1thk2] = KF1Theta[1];
   tuple[f1phik2] = KF1Phi[1];
   tuple[f2ek1] = KF2E[0];
   tuple[f2thk1] = KF2Theta[0];
   tuple[f2phik1] = KF2Phi[0];
   tuple[f2ek2] = KF2E[1];
   tuple[f2thk2] = KF2Theta[1];
   tuple[f2phik2] = KF2Phi[1];

   tuple[x1] = X;
   tuple[yy1] = Y;
   tuple[z1] = Z;

   tuple[dd] = DD;


   if(CHARGE[0]==1 && CHARGE[1]==-1){
   tuple[me1] = ME[0];
   tuple[eop1] = EOP[0];
   tuple[me2] = ME[1];
   tuple[eop2] = EOP[1];

   tuple[width1] = WIDTH[0];
   tuple[width2] = WIDTH[1];

   tuple[mudepth1] = MUDEPTH[0];
   tuple[mudepth2] = MUDEPTH[1];
   tuple[kntrack1shower] = KN[0];
   tuple[kntrack2shower] = KN[1];

   tuple[errtr1px] = ERRTRPX[0];
   tuple[errtr1py] = ERRTRPY[0];
   tuple[errtr1pz] = ERRTRPZ[0];
   tuple[errtr2px] = ERRTRPX[1];
   tuple[errtr2py] = ERRTRPY[1];
   tuple[errtr2pz] = ERRTRPZ[1];

   tuple[pite1] = PIPE[0];
   tuple[pipx1] = PIPX[0];
   tuple[pipy1] = PIPY[0];
   tuple[pipz1] = PIPZ[0];
   tuple[pite2] = PIPE[1];
   tuple[pipx2] = PIPX[1];
   tuple[pipy2] = PIPY[1];
   tuple[pipz2] = PIPZ[1];

   tuple[pix1] = PIX[0];
   tuple[piy1] = PIY[0];
   tuple[piz1] = PIZ[0];
   tuple[pix2] = PIX[1];
   tuple[piy2] = PIY[1];
   tuple[piz2] = PIZ[1];

   tuple[mute1] = MUPE[0];
   tuple[mupx1] = MUPX[0];
   tuple[mupy1] = MUPY[0];
   tuple[mupz1] = MUPZ[0];
   tuple[mute2] = MUPE[1];
   tuple[mupx2] = MUPX[1];
   tuple[mupy2] = MUPY[1];
   tuple[mupz2] = MUPZ[1];

   tuple[kte1] = KPE[0];
   tuple[kpx1] = KPX[0];
   tuple[kpy1] = KPY[0];
   tuple[kpz1] = KPZ[0];
   tuple[kte2] = KPE[1];
   tuple[kpx2] = KPX[1];
   tuple[kpy2] = KPY[1];
   tuple[kpz2] = KPZ[1];

   tuple[pisigma1] = PPISIGMA[0];
   tuple[pill1] = PPILL[0];
   tuple[pisigma2] = PPISIGMA[1];
   tuple[pill2] = PPILL[1];

   tuple[musigma1] = PMUSIGMA[0];
   tuple[mull1] = PMULL[0];
   tuple[musigma2] = PMUSIGMA[1];
   tuple[mull2] = PMULL[1];

   tuple[ksigma1] = PKSIGMA[0];
   tuple[kll1] = PKLL[0];
   tuple[ksigma2] = PKSIGMA[1];
   tuple[kll2] = PKLL[1];

   tuple[f1pite1] = PIF1PE[0];
   tuple[f1pipx1] = PIF1PX[0];
   tuple[f1pipy1] = PIF1PY[0];
   tuple[f1pipz1] = PIF1PZ[0];
   tuple[f1pite2] = PIF1PE[1];
   tuple[f1pipx2] = PIF1PX[1];
   tuple[f1pipy2] = PIF1PY[1];
   tuple[f1pipz2] = PIF1PZ[1];

   tuple[f2pite1] = PIF2PE[0];
   tuple[f2pipx1] = PIF2PX[0];
   tuple[f2pipy1] = PIF2PY[0];
   tuple[f2pipz1] = PIF2PZ[0];
   tuple[f2pite2] = PIF2PE[1];
   tuple[f2pipx2] = PIF2PX[1];
   tuple[f2pipy2] = PIF2PY[1];
   tuple[f2pipz2] = PIF2PZ[1];

   tuple[f1mute1] = MUF1PE[0];
   tuple[f1mupx1] = MUF1PX[0];
   tuple[f1mupy1] = MUF1PY[0];
   tuple[f1mupz1] = MUF1PZ[0];
   tuple[f1mute2] = MUF1PE[1];
   tuple[f1mupx2] = MUF1PX[1];
   tuple[f1mupy2] = MUF1PY[1];
   tuple[f1mupz2] = MUF1PZ[1];

   tuple[f2mute1] = MUF2PE[0];
   tuple[f2mupx1] = MUF2PX[0];
   tuple[f2mupy1] = MUF2PY[0];
   tuple[f2mupz1] = MUF2PZ[0];
   tuple[f2mute2] = MUF2PE[1];
   tuple[f2mupx2] = MUF2PX[1];
   tuple[f2mupy2] = MUF2PY[1];
   tuple[f2mupz2] = MUF2PZ[1];

   tuple[f1kte1] = KF1PE[0];
   tuple[f1kpx1] = KF1PX[0];
   tuple[f1kpy1] = KF1PY[0];
   tuple[f1kpz1] = KF1PZ[0];
   tuple[f1kte2] = KF1PE[1];
   tuple[f1kpx2] = KF1PX[1];
   tuple[f1kpy2] = KF1PY[1];
   tuple[f1kpz2] = KF1PZ[1];

   tuple[f2kte1] = KF2PE[0];
   tuple[f2kpx1] = KF2PX[0];
   tuple[f2kpy1] = KF2PY[0];
   tuple[f2kpz1] = KF2PZ[0];
   tuple[f2kte2] = KF2PE[1];
   tuple[f2kpx2] = KF2PX[1];
   tuple[f2kpy2] = KF2PY[1];
   tuple[f2kpz2] = KF2PZ[1];

   tuple[charge1] = CHARGE[0];
   tuple[charge2] = CHARGE[1];
   }

   else if(CHARGE[1]==1 && CHARGE[0]==-1){
   tuple[me1] = ME[1];
   tuple[eop1] = EOP[1];
   tuple[me2] = ME[0];
   tuple[eop2] = EOP[0];

   tuple[width1] = WIDTH[1];
   tuple[width2] = WIDTH[0];

   tuple[mudepth1] = MUDEPTH[1];
   tuple[mudepth2] = MUDEPTH[0];
   tuple[kntrack1shower] = KN[1];
   tuple[kntrack2shower] = KN[0];

   tuple[errtr1px] = ERRTRPX[1];
   tuple[errtr1py] = ERRTRPY[1];
   tuple[errtr1pz] = ERRTRPZ[1];
   tuple[errtr2px] = ERRTRPX[0];
   tuple[errtr2py] = ERRTRPY[0];
   tuple[errtr2pz] = ERRTRPZ[0];


   tuple[pite1] = PIPE[1];
   tuple[pipx1] = PIPX[1];
   tuple[pipy1] = PIPY[1];
   tuple[pipz1] = PIPZ[1];
   tuple[pite2] = PIPE[0];
   tuple[pipx2] = PIPX[0];
   tuple[pipy2] = PIPY[0];
   tuple[pipz2] = PIPZ[0];

   tuple[pix1] = PIX[1];
   tuple[piy1] = PIY[1];
   tuple[piz1] = PIZ[1];
   tuple[pix2] = PIX[0];
   tuple[piy2] = PIY[0];
   tuple[piz2] = PIZ[0];

   tuple[mute1] = MUPE[1];
   tuple[mupx1] = MUPX[1];
   tuple[mupy1] = MUPY[1];
   tuple[mupz1] = MUPZ[1];
   tuple[mute2] = MUPE[0];
   tuple[mupx2] = MUPX[0];
   tuple[mupy2] = MUPY[0];
   tuple[mupz2] = MUPZ[0];

   tuple[kte1] = KPE[1];
   tuple[kpx1] = KPX[1];
   tuple[kpy1] = KPY[1];
   tuple[kpz1] = KPZ[1];
   tuple[kte2] = KPE[0];
   tuple[kpx2] = KPX[0];
   tuple[kpy2] = KPY[0];
   tuple[kpz2] = KPZ[0];

   tuple[pisigma1] = PPISIGMA[1];
   tuple[pill1] = PPILL[1];
   tuple[pisigma2] = PPISIGMA[0];
   tuple[pill2] = PPILL[0];

   tuple[musigma1] = PMUSIGMA[1];
   tuple[mull1] = PMULL[1];
   tuple[musigma2] = PMUSIGMA[0];
   tuple[mull2] = PMULL[0];

   tuple[ksigma1] = PKSIGMA[1];
   tuple[kll1] = PKLL[1];
   tuple[ksigma2] = PKSIGMA[0];
   tuple[kll2] = PKLL[0];

   tuple[f1pite1] = PIF1PE[1];
   tuple[f1pipx1] = PIF1PX[1];
   tuple[f1pipy1] = PIF1PY[1];
   tuple[f1pipz1] = PIF1PZ[1];
   tuple[f1pite2] = PIF1PE[0];
   tuple[f1pipx2] = PIF1PX[0];
   tuple[f1pipy2] = PIF1PY[0];
   tuple[f1pipz2] = PIF1PZ[0];

   tuple[f2pite1] = PIF2PE[1];
   tuple[f2pipx1] = PIF2PX[1];
   tuple[f2pipy1] = PIF2PY[1];
   tuple[f2pipz1] = PIF2PZ[1];
   tuple[f2pite2] = PIF2PE[0];
   tuple[f2pipx2] = PIF2PX[0];
   tuple[f2pipy2] = PIF2PY[0];
   tuple[f2pipz2] = PIF2PZ[0];

   tuple[f1mute1] = MUF1PE[1];
   tuple[f1mupx1] = MUF1PX[1];
   tuple[f1mupy1] = MUF1PY[1];
   tuple[f1mupz1] = MUF1PZ[1];
   tuple[f1mute2] = MUF1PE[0];
   tuple[f1mupx2] = MUF1PX[0];
   tuple[f1mupy2] = MUF1PY[0];
   tuple[f1mupz2] = MUF1PZ[0];

   tuple[f2mute1] = MUF2PE[1];
   tuple[f2mupx1] = MUF2PX[1];
   tuple[f2mupy1] = MUF2PY[1];
   tuple[f2mupz1] = MUF2PZ[1];
   tuple[f2mute2] = MUF2PE[0];
   tuple[f2mupx2] = MUF2PX[0];
   tuple[f2mupy2] = MUF2PY[0];
   tuple[f2mupz2] = MUF2PZ[0];

   tuple[f1kte1] = KF1PE[1];
   tuple[f1kpx1] = KF1PX[1];
   tuple[f1kpy1] = KF1PY[1];
   tuple[f1kpz1] = KF1PZ[1];
   tuple[f1kte2] = KF1PE[0];
   tuple[f1kpx2] = KF1PX[0];
   tuple[f1kpy2] = KF1PY[0];
   tuple[f1kpz2] = KF1PZ[0];

   tuple[f2kte1] = KF2PE[1];
   tuple[f2kpx1] = KF2PX[1];
   tuple[f2kpy1] = KF2PY[1];
   tuple[f2kpz1] = KF2PZ[1];
   tuple[f2kte2] = KF2PE[0];
   tuple[f2kpx2] = KF2PX[0];
   tuple[f2kpy2] = KF2PY[0];
   tuple[f2kpz2] = KF2PZ[0];

   tuple[charge1] = CHARGE[1];
   tuple[charge2] = CHARGE[0];

   }
   tuple[beam_e] = BEAME;
   tuple[m_trk] = TRKM;


   tuple[mmpi_gen] = MMPI_GEN;
   tuple[mmmu_gen] = MMMU_GEN;




   (*m_showerTuple).fill(tuple);



   return ActionBase::kPassed;
}


ActionBase::ActionResult
FitProc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   FAItem< BeamSpot > spot;
   extract( iFrame.record( Stream::kBeginRun ), spot );

   FAItem< BeamEnergy > beam_energy;
   extract( iFrame.record( Stream::kBeginRun ), beam_energy );

   FAItem< MagneticField > cleoBField;
   extract( iFrame.record( Stream::kBeginRun ), cleoBField );

   FitEvtSettings &settings(FitEvtSettings::instance());
   settings.setField(*cleoBField);
   settings.setBeamSpot(*spot);
   settings.setLorVecCM( beam_energy->value() );
//   settings.setVerbose();

   return ActionBase::kPassed;
}


/*
ActionBase::ActionResult
FitProc::endRun( Frame& iFrame )         // anal4 equiv.
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
