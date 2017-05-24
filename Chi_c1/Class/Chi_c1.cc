// -*- C++ -*-
//
// Package:     Chi_c1
// Module:      Chi_c1
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      pts/7
// Created:     Mon May  2 13:43:14 CDT 2011
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Chi_c1/Chi_c1.h"
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

#include "Navigation/NavPi0ToGG.h"
#include "Navigation/NavEtaToGG.h"
#include "PhotonDecays/PhdPi0.h"
#include "PhotonDecays/PhdEtaToGG.h"
#include "Navigation/NavTkShMatch.h"
#include <PhotonDecays/PhdPi0.h>
#include <CleoDB/DBEventHeader.h>

#include "CleoDB/DBEventHeader.h"
#include "TriggerData/TriggerData.h"
#include "TriggerL1Data/TriggerL1Data.h"
#include "Level4Proc/Level4Decision.h"

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
static const char* const kFacilityString = "Processor.Chi_c1" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
Chi_c1::Chi_c1( void )               // anal1
   : Processor( "Chi_c1" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Chi_c1::event,    Stream::kEvent );
   bind( &Chi_c1::beginRun, Stream::kBeginRun );
   //bind( &Chi_c1::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

Chi_c1::~Chi_c1()                    // anal5
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
Chi_c1::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Chi_c1::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------

enum {
chisqv_ee,chisqf_ee,     // chisq of 4C fit without J/psi mass constraint (tracks are assumed as elections)
chisqv_mee,chisqf_mee,         // chisq of 4C fit after J/psi mass constraint
chisqv_mumu,chisqf_mumu,     // chisq of 4C fit without J/psi mass constraint (tracks are assumed as muons)
chisqv_mmumu,chisqf_mmumu,         // chisq of 4C fit after J/psi mass constraint
id1,id2,                 // identifier of photon, just for check temporarily

e1,th1,phi1,de1,dth1,dphi1,  // unfitted photon energy 
e2,th2,phi2,de2,dth2,dphi2,        
fe1_ee,fth1_ee,fphi1_ee,fe2_ee,fth2_ee,fphi2_ee,
fe1_mee,fth1_mee,fphi1_mee,fe2_mee,fth2_mee,fphi2_mee,   
fe1_mumu,fth1_mumu,fphi1_mumu,fe2_mumu,fth2_mumu,fphi2_mumu,
fe1_mmumu,fth1_mmumu,fphi1_mmumu,fe2_mmumu,fth2_mmumu,fphi2_mmumu,

e_beam,         // beam energy

eop1,eop2,me1,me2,
trte1_ee,trpx1_ee,trpy1_ee,trpz1_ee,trmag1_ee,trte2_ee,trpx2_ee,trpy2_ee,trpz2_ee,trmag2_ee,
trte1_mumu,trpx1_mumu,trpy1_mumu,trpz1_mumu,trmag1_mumu,trte2_mumu,trpx2_mumu,trpy2_mumu,trpz2_mumu,trmag2_mumu,
ftrte1_ee,ftrpx1_ee,ftrpy1_ee,ftrpz1_ee,ftrte2_ee,ftrpx2_ee,ftrpy2_ee,ftrpz2_ee,
ftrte1_mee,ftrpx1_mee,ftrpy1_mee,ftrpz1_mee,ftrte2_mee,ftrpx2_mee,ftrpy2_mee,ftrpz2_mee,
ftrte1_mumu,ftrpx1_mumu,ftrpy1_mumu,ftrpz1_mumu,ftrte2_mumu,ftrpx2_mumu,ftrpy2_mumu,ftrpz2_mumu,
ftrte1_mmumu,ftrpx1_mmumu,ftrpy1_mmumu,ftrpz1_mmumu,ftrte2_mmumu,ftrpx2_mmumu,ftrpy2_mmumu,ftrpz2_mmumu,

charge1,charge2,

pass1a,pass2a,pass3a,pass4ea,pass4mua,pass4ema,pass4muma, // saving photon energy to calculate efficiencies
pass1b,pass2b,pass3b,pass4eb,pass4mub,pass4emb,pass4mumb,

kVarNum};




void
Chi_c1::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   HINtupleVarNames ntupleNames(kVarNum);

   ntupleNames.addVar(chisqv_ee,       "chisqv_ee");
   ntupleNames.addVar(chisqf_ee,       "chisqf_ee");
   ntupleNames.addVar(chisqv_mee,      "chisqv_mee");
   ntupleNames.addVar(chisqf_mee,      "chisqf_mee");
   ntupleNames.addVar(chisqv_mumu,     "chisqv_mumu");
   ntupleNames.addVar(chisqf_mumu,     "chisqf_mumu");
   ntupleNames.addVar(chisqv_mmumu,    "chisqv_mmumu");
   ntupleNames.addVar(chisqf_mmumu,    "chisqf_mmumu");

   ntupleNames.addVar(id1,           "id1");
   ntupleNames.addVar(id2,           "id2");

   ntupleNames.addVar(e1,            "e1");
   ntupleNames.addVar(th1,           "th1");
   ntupleNames.addVar(phi1,          "phi1");
   ntupleNames.addVar(de1,           "de1");
   ntupleNames.addVar(dth1,          "dth1");
   ntupleNames.addVar(dphi1,         "dphi1");

   ntupleNames.addVar(e2,            "e2");
   ntupleNames.addVar(th2,           "th2");
   ntupleNames.addVar(phi2,          "phi2");
   ntupleNames.addVar(de2,           "de2");
   ntupleNames.addVar(dth2,          "dth2");
   ntupleNames.addVar(dphi2,         "dphi2");

   ntupleNames.addVar(fe1_ee,          "fe1_ee");
   ntupleNames.addVar(fth1_ee,         "fth1_ee");
   ntupleNames.addVar(fphi1_ee,        "fphi1_ee");
   ntupleNames.addVar(fe2_ee,          "fe2_ee");
   ntupleNames.addVar(fth2_ee,         "fth2_ee");
   ntupleNames.addVar(fphi2_ee,        "fphi2_ee");
   ntupleNames.addVar(fe1_mee,          "fe1_mee");
   ntupleNames.addVar(fth1_mee,         "fth1_mee");
   ntupleNames.addVar(fphi1_mee,        "fphi1_mee");
   ntupleNames.addVar(fe2_mee,          "fe2_mee");
   ntupleNames.addVar(fth2_mee,         "fth2_mee");
   ntupleNames.addVar(fphi2_mee,        "fphi2_mee");

   ntupleNames.addVar(fe1_mumu,          "fe1_mumu");
   ntupleNames.addVar(fth1_mumu,         "fth1_mumu");
   ntupleNames.addVar(fphi1_mumu,        "fphi1_mumu");
   ntupleNames.addVar(fe2_mumu,          "fe2_mumu");
   ntupleNames.addVar(fth2_mumu,         "fth2_mumu");
   ntupleNames.addVar(fphi2_mumu,        "fphi2_mumu");
   ntupleNames.addVar(fe1_mmumu,          "fe1_mmumu");
   ntupleNames.addVar(fth1_mmumu,         "fth1_mmumu");
   ntupleNames.addVar(fphi1_mmumu,        "fphi1_mmumu");
   ntupleNames.addVar(fe2_mmumu,          "fe2_mmumu");
   ntupleNames.addVar(fth2_mmumu,         "fth2_mmumu");
   ntupleNames.addVar(fphi2_mmumu,        "fphi2_mmumu");

   ntupleNames.addVar(e_beam,       "e_beam");

   ntupleNames.addVar(eop1,         "eop1");
   ntupleNames.addVar(eop2,         "eop2");
   ntupleNames.addVar(me1,          "me1");
   ntupleNames.addVar(me2,          "me2");

   ntupleNames.addVar(trte1_ee,        "trte1_ee");
   ntupleNames.addVar(trpx1_ee,        "trpx1_ee");
   ntupleNames.addVar(trpy1_ee,        "trpy1_ee");
   ntupleNames.addVar(trpz1_ee,        "trpz1_ee");
   ntupleNames.addVar(trmag1_ee,       "trmag1_ee");
   ntupleNames.addVar(trte2_ee,        "trte2_ee");
   ntupleNames.addVar(trpx2_ee,        "trpx2_ee");
   ntupleNames.addVar(trpy2_ee,        "trpy2_ee");
   ntupleNames.addVar(trpz2_ee,        "trpz2_ee");
   ntupleNames.addVar(trmag2_ee,       "trmag2_ee");

   ntupleNames.addVar(trte1_mumu,        "trte1_mumu");
   ntupleNames.addVar(trpx1_mumu,        "trpx1_mumu");
   ntupleNames.addVar(trpy1_mumu,        "trpy1_mumu");
   ntupleNames.addVar(trpz1_mumu,        "trpz1_mumu");
   ntupleNames.addVar(trmag1_mumu,       "trmag1_mumu");
   ntupleNames.addVar(trte2_mumu,        "trte2_mumu");
   ntupleNames.addVar(trpx2_mumu,        "trpx2_mumu");
   ntupleNames.addVar(trpy2_mumu,        "trpy2_mumu");
   ntupleNames.addVar(trpz2_mumu,        "trpz2_mumu");
   ntupleNames.addVar(trmag2_mumu,       "trmag2_mumu");

   ntupleNames.addVar(ftrte1_ee,       "ftrte1_ee");
   ntupleNames.addVar(ftrpx1_ee,       "ftrpx1_ee");
   ntupleNames.addVar(ftrpy1_ee,       "ftrpy1_ee");
   ntupleNames.addVar(ftrpz1_ee,       "ftrpz1_ee");
   ntupleNames.addVar(ftrte2_ee,       "ftrte2_ee");
   ntupleNames.addVar(ftrpx2_ee,       "ftrpx2_ee");
   ntupleNames.addVar(ftrpy2_ee,       "ftrpy2_ee");
   ntupleNames.addVar(ftrpz2_ee,       "ftrpz2_ee");
   ntupleNames.addVar(ftrte1_mee,       "ftrte1_mee");
   ntupleNames.addVar(ftrpx1_mee,       "ftrpx1_mee");
   ntupleNames.addVar(ftrpy1_mee,       "ftrpy1_mee");
   ntupleNames.addVar(ftrpz1_mee,       "ftrpz1_mee");
   ntupleNames.addVar(ftrte2_mee,       "ftrte2_mee");
   ntupleNames.addVar(ftrpx2_mee,       "ftrpx2_mee");
   ntupleNames.addVar(ftrpy2_mee,       "ftrpy2_mee");
   ntupleNames.addVar(ftrpz2_mee,       "ftrpz2_mee");

   ntupleNames.addVar(ftrte1_mumu,       "ftrte1_mumu");
   ntupleNames.addVar(ftrpx1_mumu,       "ftrpx1_mumu");
   ntupleNames.addVar(ftrpy1_mumu,       "ftrpy1_mumu");
   ntupleNames.addVar(ftrpz1_mumu,       "ftrpz1_mumu");
   ntupleNames.addVar(ftrte2_mumu,       "ftrte2_mumu");
   ntupleNames.addVar(ftrpx2_mumu,       "ftrpx2_mumu");
   ntupleNames.addVar(ftrpy2_mumu,       "ftrpy2_mumu");
   ntupleNames.addVar(ftrpz2_mumu,       "ftrpz2_mumu");
   ntupleNames.addVar(ftrte1_mmumu,       "ftrte1_mmumu");
   ntupleNames.addVar(ftrpx1_mmumu,       "ftrpx1_mmumu");
   ntupleNames.addVar(ftrpy1_mmumu,       "ftrpy1_mmumu");
   ntupleNames.addVar(ftrpz1_mmumu,       "ftrpz1_mmumu");
   ntupleNames.addVar(ftrte2_mmumu,       "ftrte2_mmumu");
   ntupleNames.addVar(ftrpx2_mmumu,       "ftrpx2_mmumu");
   ntupleNames.addVar(ftrpy2_mmumu,       "ftrpy2_mmumu");
   ntupleNames.addVar(ftrpz2_mmumu,       "ftrpz2_mmumu");

   ntupleNames.addVar(charge1,      "charge1");
   ntupleNames.addVar(charge2,      "charge2");

   ntupleNames.addVar(pass1a,      "pass1a");
   ntupleNames.addVar(pass2a,      "pass2a");
   ntupleNames.addVar(pass3a,      "pass3a");
   ntupleNames.addVar(pass4ea,      "pass4ea");
   ntupleNames.addVar(pass4mua,      "pass4mua");
   ntupleNames.addVar(pass4ema,      "pass4ema");
   ntupleNames.addVar(pass4muma,      "pass4muma");

   ntupleNames.addVar(pass1b,      "pass1b");
   ntupleNames.addVar(pass2b,      "pass2b");
   ntupleNames.addVar(pass3b,      "pass3b");
   ntupleNames.addVar(pass4eb,      "pass4eb");
   ntupleNames.addVar(pass4mub,      "pass4mub");
   ntupleNames.addVar(pass4emb,      "pass4emb");
   ntupleNames.addVar(pass4mumb,      "pass4mumb");

   m_showerTuple = iHistoManager.ntuple(10,"tuple", kVarNum, 10000, ntupleNames.names());

}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Chi_c1::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   double ChisqVee = -10.;
   double ChisqFee = -10.;
   double ChisqVmumu = -10.;
   double ChisqFmumu = -10.;
   double ChisqVmee = -10.;
   double ChisqFmee = -10.;
   double ChisqVmmumu = -10.;
   double ChisqFmmumu = -10.;

   double ID[2] = {-10.,-10.};

   double E[2] = {-10.,-10.};
   double Theta[2] = {-10.,-10.};
   double Phi[2] = {-10.,-10.};
   double DE[2] = {-10.,-10.};
   double DTheta[2] = {-10.,-10.};
   double DPhi[2] = {-10.,-10.};

   double FEee[2] = {-10.,-10.};
   double FThetaee[2] = {-10.,-10.};
   double FPhiee[2] = {-10.,-10.};
   double FEmee[2] = {-10.,-10.};
   double FThetamee[2] = {-10.,-10.};
   double FPhimee[2] = {-10.,-10.};
   double FEmumu[2] = {-10.,-10.};
   double FThetamumu[2] = {-10.,-10.};
   double FPhimumu[2] = {-10.,-10.};
   double FEmmumu[2] = {-10.,-10.};
   double FThetammumu[2] = {-10.,-10.};
   double FPhimmumu[2] = {-10.,-10.};

   double E_BEAM = -10.;

   double ME[2] = {-10.,-10.};
   double EOP[2] = {-10.,-10.};

   double PEee[2] = {-10.,-10.};
   double PXee[2] = {-10.,-10.};
   double PYee[2] = {-10.,-10.};
   double PZee[2] = {-10.,-10.};
   double PMAGee[2] = {-10.,-10.};
   double PEmumu[2] = {-10.,-10.};
   double PXmumu[2] = {-10.,-10.};
   double PYmumu[2] = {-10.,-10.};
   double PZmumu[2] = {-10.,-10.};
   double PMAGmumu[2] = {-10.,-10.};

   double FPEee[2] = {-10.,-10.};
   double FPXee[2] = {-10.,-10.};
   double FPYee[2] = {-10.,-10.};
   double FPZee[2] = {-10.,-10.};
   double FPEmee[2] = {-10.,-10.};
   double FPXmee[2] = {-10.,-10.};
   double FPYmee[2] = {-10.,-10.};
   double FPZmee[2] = {-10.,-10.};
   double FPEmumu[2] = {-10.,-10.};
   double FPXmumu[2] = {-10.,-10.};
   double FPYmumu[2] = {-10.,-10.};
   double FPZmumu[2] = {-10.,-10.};
   double FPEmmumu[2] = {-10.,-10.};
   double FPXmmumu[2] = {-10.,-10.};
   double FPYmmumu[2] = {-10.,-10.};
   double FPZmmumu[2] = {-10.,-10.};

   double CHARGE[2] = {-10.,-10.};

   double PASS1[2] = {-10.,-10.};  
   double PASS2[2] = {-10.,-10.};
   double PASS3[2] = {-10.,-10.};
   double PASS4E[2] = {-10.,-10.};
   double PASS4MU[2] = {-10.,-10.};
   double PASS4EM[2] = {-10.,-10.};
   double PASS4MUM[2] = {-10.,-10.};

   bool isPI0 = false;
   bool isETA = false;

   const double kJpsiMass = 3.096916;


   float tuple[kVarNum];


///////////////////////////////// beam energy ////////////////////////////////////

   FAItem< BeamEnergy > beam_energy;
   extract( iFrame.record( Stream::kBeginRun ), beam_energy );

   E_BEAM = beam_energy->value();

////////////////////////////// # of tracks == 2 /////////////////////////////////

   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable, "GoodThings" );

   FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();

   FAItem<TDKinematicFit> tr_ee[2];
   FAItem<TDKinematicFit> tr_mumu[2];
   KTKinematicData track_ee[2];


   int fittracks = 0;
   int i = 0;
   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;
         ++trackItr )
   {

      FAItem<TDKinematicFit> muonFit = trackItr->muonFit();
      FAItem<TDKinematicFit> electronFit = trackItr->electronFit();

      bool ISee = true;
      bool ISmumu = true;

      if(trackItr.valid()) {
        
        if(ISee || ISmumu)
          i = fittracks++;

        if(fittracks > 2)
            return ActionBase::kFailed;

        if(trackItr->trackShowerMatch().valid())
           ME[i] = trackItr->trackShowerMatch()->matchedEnergy();

        EOP[i] = trackItr->elecId().eOverP();
        if(electronFit.valid() && electronFit->pmag() > 1.2) {

          FATable<NavShower> brem(trackItr->bremShowers());

            HepDouble gamsx = 0., gamsy = 0., gamsz = 0.;

            for(FATable<NavShower>::const_iterator iGam=brem.begin();
                iGam != brem.end(); ++iGam) {
               gamsx += iGam->attributes().momentum().x();
               gamsy += iGam->attributes().momentum().y();
               gamsz += iGam->attributes().momentum().z();
            }

          CHARGE[i]=electronFit->charge();
          PEee[i]=sqrt(fabs( 0.000511*0.000511
                        + (electronFit->px()+gamsx)*(electronFit->px()+gamsx)
                        + (electronFit->py()+gamsy)*(electronFit->py()+gamsy)
                        + (electronFit->pz()+gamsz)*(electronFit->pz()+gamsz) ));
          PXee[i]=electronFit->px()+gamsx;
          PYee[i]=electronFit->py()+gamsy;
          PZee[i]=electronFit->pz()+gamsz;
          PMAGee[i]=sqrt(pow(PXee[i],2)+pow(PYee[i],2)+pow(PZee[i],2));
          tr_ee[i] = trackItr->electronFit();
          track_ee[i] = *tr_ee[i];
          track_ee[i].setMomentum(HepVector3D(PXee[i],PYee[i],PZee[i]));

        }
        else ISee = false;

        if(muonFit.valid() && muonFit->pmag() > 1.2) {

          CHARGE[i]=muonFit->charge();
          PEmumu[i]=muonFit->energy();
          PXmumu[i]=muonFit->px();
          PYmumu[i]=muonFit->py();
          PZmumu[i]=muonFit->pz();
          PMAGmumu[i]=muonFit->pmag();
          tr_mumu[i]=muonFit;
        }
        else ISmumu = false;
      }
   }

   if(fittracks != 2)
       return ActionBase::kFailed;

   if(CHARGE[0] != -CHARGE[1])
       return ActionBase::kFailed;


///////////////////////////////////// # of showers = 2 ////////////////////////////////

   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ) , showerTable, "GoodThings" );

   if(showerTable.size() < 2)
      return ActionBase::kFailed;

   FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
   FATable< NavShower >::const_iterator showerEnd = showerTable.end();

   FATable< NavShower >::const_iterator sh[2];


   int fitphotons = 0;

   for ( FATable< NavShower >::const_iterator showerItr = showerBegin;
         showerItr != showerEnd ;
         ++showerItr )
      {

       if(showerItr->attributes().e9oe25OK() &&  showerItr->attributes().goodBarrel() && showerItr->attributes().energy() > 0.1) {
//       if(showerItr->attributes().e9oe25OK() &&  (showerItr->attributes().goodBarrel() || showerItr->attributes().goodEndcap()) 
//                            && showerItr->attributes().energy() > 0.1) {


         int i = fitphotons++;

         if(fitphotons > 2)
            return ActionBase::kFailed;

         ID[i] = showerItr->identifier();
         E[i] = showerItr->attributes().energy();
         Theta[i] = showerItr->attributes().theta();
         Phi[i] = showerItr->attributes().phi();
         DE[i] = showerItr->attributes().errEnergy();
         DTheta[i] = showerItr->attributes().errTheta();
         DPhi[i] = showerItr->attributes().errPhi();
         sh[i] = showerItr;

       }
     }

   if(fitphotons != 2)
      return ActionBase::kFailed;

   PASS1[0] = E[0];
   PASS1[1] = E[1]; 
//////////////////////////////// photon not from pi0 ////////////////////////////////

   FATable<NavPi0ToGG> pi0Table;
   extract( iFrame.record( Stream::kEvent ) , pi0Table );

   FATable< NavPi0ToGG >::const_iterator pi0Begin = pi0Table.begin();
   FATable< NavPi0ToGG >::const_iterator pi0End = pi0Table.end();

   for (FATable< NavPi0ToGG >::const_iterator pi0Itr = pi0Begin;
        pi0Itr != pi0End ; ++pi0Itr) {

     if(pi0Itr.valid()
            && pi0Itr->pi0().fit()
            && pi0Itr->pi0().converged()
            && (pi0Itr->pi0().chisq() < 500)
            && (fabs(pi0Itr->pi0().pullMass()) < 3) ) {
        if(pi0Itr->hiEnShower().identifier() == ID[0] && pi0Itr->loEnShower().identifier() == ID[1]) 
            isPI0 = true;
        else if(pi0Itr->hiEnShower().identifier() == ID[1] && pi0Itr->loEnShower().identifier() == ID[0])
            isPI0 = true;
     }
   }
   if(!isPI0) {
     PASS2[0] = E[0];
     PASS2[1] = E[1];
   }

///////////////////////////////// photon not from eta /////////////////////////////////

   FATable<NavEtaToGG> etaTable;
   extract( iFrame.record( Stream::kEvent ) , etaTable );

   FATable< NavEtaToGG >::const_iterator etaBegin = etaTable.begin();
   FATable< NavEtaToGG >::const_iterator etaEnd = etaTable.end();

   for (FATable< NavEtaToGG >::const_iterator etaItr = etaBegin;
        etaItr != etaEnd ; ++etaItr) {

     if(etaItr.valid()
            && etaItr->eta().fit()
            && etaItr->eta().converged()
            && (etaItr->eta().chisq() < 500)
            && (fabs(etaItr->eta().pullMass()) < 3) ) {
        if(etaItr->hiEnShower().identifier() == ID[0] && etaItr->loEnShower().identifier() == ID[1])
            isETA = true;
        else if(etaItr->hiEnShower().identifier() == ID[1] && etaItr->loEnShower().identifier() == ID[0])
            isETA = true;
     }
   }
 
   if(!isETA){
     PASS3[0] = E[0];
     PASS3[1] = E[1];
   }

///////////////////////////////// kinematic fitting //////////////////////////////////

if(!isPI0 && !isETA) {

//// ee with no mass constraint ///////

   FitEvt psip_ee( "Psip_ee", FitEvt::k_P4VecCM );
   psip_ee.newPhoton(*sh[0]);
   psip_ee.newPhoton(*sh[1]);
   psip_ee.newTrack(track_ee[0]);
   psip_ee.newTrack(track_ee[1]);
   psip_ee.doTheFit();

   if( (psip_ee.chisqVtx()>0) && (psip_ee.chisqFit()>0) ) {
         ChisqVee = psip_ee.chisqVtx();
         ChisqFee = psip_ee.chisqFit();

         HepLorentzVector v0 (psip_ee.kdFitVec()[0]->lorentzMomentum());
         HepLorentzVector vg (psip_ee.kdFitVec()[1]->lorentzMomentum());
         HepLorentzVector v1 (psip_ee.kdFitVec()[2]->lorentzMomentum());
         HepLorentzVector v2 (psip_ee.kdFitVec()[3]->lorentzMomentum());

         FEee[0] = v0.e();
         FThetaee[0] = v0.theta();
         FPhiee[0] = v0.phi();
         FEee[1] = vg.e();
         FThetaee[1] = vg.theta();
         FPhiee[1] = vg.phi();

         FPEee[0]=v1.e();
         FPXee[0]=v1.px();
         FPYee[0]=v1.py();
         FPZee[0]=v1.pz();
         FPEee[1]=v2.e();
         FPXee[1]=v2.px();
         FPYee[1]=v2.py();
         FPZee[1]=v2.pz();

         PASS4E[0] = E[0];
         PASS4E[1] = E[1];

    }



//// ee with mass constraint /////

   FitEvt jpsi_ee( "Jpsi_ee", FitEvt::k_Mass, 0, kJpsiMass );
   jpsi_ee.newTrack(track_ee[0]);
   jpsi_ee.newTrack(track_ee[1]);
   jpsi_ee.doTheFit();

   if( (jpsi_ee.chisqVtx()>0) && (jpsi_ee.chisqFit()>0) ) {

      FitEvt psip_mee( "Psip_mee", FitEvt::k_P4VecCM );
      psip_mee.newPhoton(*sh[0]);
      psip_mee.newPhoton(*sh[1]);
      psip_mee.newKinDat(jpsi_ee.fitResult());
      psip_mee.doTheFit();

      if( (psip_mee.chisqVtx()>0) && (psip_mee.chisqFit()>0) ) {
         ChisqVmee = psip_mee.chisqVtx();
         ChisqFmee = psip_mee.chisqFit();

         HepLorentzVector v0 (psip_mee.kdFitVec()[0]->lorentzMomentum());
         HepLorentzVector vg (psip_mee.kdFitVec()[1]->lorentzMomentum());
         HepLorentzVector v1 (jpsi_ee.kdFitVec()[0]->lorentzMomentum());
         HepLorentzVector v2 (jpsi_ee.kdFitVec()[1]->lorentzMomentum());

         FEmee[0] = v0.e();
         FThetamee[0] = v0.theta();
         FPhimee[0] = v0.phi();
         FEmee[1] = vg.e();
         FThetamee[1] = vg.theta();
         FPhimee[1] = vg.phi();

         FPEmee[0]=v1.e();
         FPXmee[0]=v1.px();
         FPYmee[0]=v1.py();
         FPZmee[0]=v1.pz();
         FPEmee[1]=v2.e();
         FPXmee[1]=v2.px();
         FPYmee[1]=v2.py();
         FPZmee[1]=v2.pz();

         PASS4EM[0] = E[0];
         PASS4EM[1] = E[1];

      }
   }


//// mumu with no mass constraint ///////

   FitEvt psip_mumu( "Psip_mumu", FitEvt::k_P4VecCM );
   psip_mumu.newPhoton(*sh[0]);
   psip_mumu.newPhoton(*sh[1]);
   psip_mumu.newTrack(*tr_mumu[0]);
   psip_mumu.newTrack(*tr_mumu[1]);
   psip_mumu.doTheFit();

   if( (psip_mumu.chisqVtx()>0) && (psip_mumu.chisqFit()>0) ) {
         ChisqVmumu = psip_mumu.chisqVtx();
         ChisqFmumu = psip_mumu.chisqFit();

         HepLorentzVector v0 (psip_mumu.kdFitVec()[0]->lorentzMomentum());
         HepLorentzVector vg (psip_mumu.kdFitVec()[1]->lorentzMomentum());
         HepLorentzVector v1 (psip_mumu.kdFitVec()[2]->lorentzMomentum());
         HepLorentzVector v2 (psip_mumu.kdFitVec()[3]->lorentzMomentum());

         FEmumu[0] = v0.e();
         FThetamumu[0] = v0.theta();
         FPhimumu[0] = v0.phi();
         FEmumu[1] = vg.e();
         FThetamumu[1] = vg.theta();
         FPhimumu[1] = vg.phi();

         FPEmumu[0]=v1.e();
         FPXmumu[0]=v1.px();
         FPYmumu[0]=v1.py();
         FPZmumu[0]=v1.pz();
         FPEmumu[1]=v2.e();
         FPXmumu[1]=v2.px();
         FPYmumu[1]=v2.py();
         FPZmumu[1]=v2.pz();

         PASS4MU[0] = E[0];
         PASS4MU[1] = E[1];
    }

//// mumu with mass constraint /////

   FitEvt jpsi_mumu( "Jpsi_mumu", FitEvt::k_Mass, 0, kJpsiMass );
   jpsi_mumu.newTrack(*tr_mumu[0]);
   jpsi_mumu.newTrack(*tr_mumu[1]);
   jpsi_mumu.doTheFit();

   if( (jpsi_mumu.chisqVtx()>0) && (jpsi_mumu.chisqFit()>0) ) {

      FitEvt psip_mmumu( "Psip_mmumu", FitEvt::k_P4VecCM );
      psip_mmumu.newPhoton(*sh[0]);
      psip_mmumu.newPhoton(*sh[1]);
      psip_mmumu.newKinDat(jpsi_mumu.fitResult());
      psip_mmumu.doTheFit();

      if( (psip_mmumu.chisqVtx()>0) && (psip_mmumu.chisqFit()>0) ) {
         ChisqVmmumu = psip_mmumu.chisqVtx();
         ChisqFmmumu = psip_mmumu.chisqFit();

         HepLorentzVector v0 (psip_mmumu.kdFitVec()[0]->lorentzMomentum());
         HepLorentzVector vg (psip_mmumu.kdFitVec()[1]->lorentzMomentum());
         HepLorentzVector v1 (jpsi_mumu.kdFitVec()[0]->lorentzMomentum());
         HepLorentzVector v2 (jpsi_mumu.kdFitVec()[1]->lorentzMomentum());

         FEmmumu[0] = v0.e();
         FThetammumu[0] = v0.theta();
         FPhimmumu[0] = v0.phi();
         FEmmumu[1] = vg.e();
         FThetammumu[1] = vg.theta();
         FPhimmumu[1] = vg.phi();

         FPEmmumu[0]=v1.e();
         FPXmmumu[0]=v1.px();
         FPYmmumu[0]=v1.py();
         FPZmmumu[0]=v1.pz();
         FPEmmumu[1]=v2.e();
         FPXmmumu[1]=v2.px();
         FPYmmumu[1]=v2.py();
         FPZmmumu[1]=v2.pz();

         PASS4MUM[0] = E[0];
         PASS4MUM[1] = E[1];

      }
   }

}







   tuple[chisqv_ee] = ChisqVee;
   tuple[chisqf_ee] = ChisqFee;
   tuple[chisqv_mumu] = ChisqVmumu;
   tuple[chisqf_mumu] = ChisqFmumu;
   tuple[chisqv_mee] = ChisqVmee;
   tuple[chisqf_mee] = ChisqFmee;
   tuple[chisqv_mmumu] = ChisqVmmumu;
   tuple[chisqf_mmumu] = ChisqFmmumu;

   tuple[id1] = ID[0];
   tuple[id2] = ID[1];

   tuple[e1] = E[0];
   tuple[th1] = Theta[0];
   tuple[phi1] = Phi[0];
   tuple[e2] = E[1];
   tuple[th2] = Theta[1];
   tuple[phi2] = Phi[1];

   tuple[de1] = DE[0];
   tuple[dth1] = DTheta[0];
   tuple[dphi1] = DPhi[0];
   tuple[de2] = DE[1];
   tuple[dth2] = DTheta[1];
   tuple[dphi2] = DPhi[1];

   tuple[fe1_ee] = FEee[0];
   tuple[fth1_ee] = FThetaee[0];
   tuple[fphi1_ee] = FPhiee[0];
   tuple[fe2_ee] = FEee[1];
   tuple[fth2_ee] = FThetaee[1];
   tuple[fphi2_ee] = FPhiee[1];
   tuple[fe1_mee] = FEmee[0];
   tuple[fth1_mee] = FThetamee[0];
   tuple[fphi1_mee] = FPhimee[0];
   tuple[fe2_mee] = FEmee[1];
   tuple[fth2_mee] = FThetamee[1];
   tuple[fphi2_mee] = FPhimee[1];

   tuple[fe1_mumu] = FEmumu[0];
   tuple[fth1_mumu] = FThetamumu[0];
   tuple[fphi1_mumu] = FPhimumu[0];
   tuple[fe2_mumu] = FEmumu[1];
   tuple[fth2_mumu] = FThetamumu[1];
   tuple[fphi2_mumu] = FPhimumu[1];
   tuple[fe1_mmumu] = FEmmumu[0];
   tuple[fth1_mmumu] = FThetammumu[0];
   tuple[fphi1_mmumu] = FPhimmumu[0];
   tuple[fe2_mmumu] = FEmmumu[1];
   tuple[fth2_mmumu] = FThetammumu[1];
   tuple[fphi2_mmumu] = FPhimmumu[1];

   tuple[e_beam] = E_BEAM;

   tuple[charge1] = CHARGE[0];
   tuple[charge2] = CHARGE[1];
   tuple[eop1] = EOP[0];
   tuple[eop2] = EOP[1];
   tuple[me1] = ME[0];
   tuple[me2] = ME[1];
   tuple[trte1_ee] = PEee[0];
   tuple[trpx1_ee] = PXee[0];
   tuple[trpy1_ee] = PYee[0];
   tuple[trpz1_ee] = PZee[0];
   tuple[trmag1_ee] = PMAGee[0];
   tuple[trte2_ee] = PEee[1];
   tuple[trpx2_ee] = PXee[1];
   tuple[trpy2_ee] = PYee[1];
   tuple[trpz2_ee] = PZee[1];
   tuple[trmag2_ee] = PMAGee[1];
   tuple[trte1_mumu] = PEmumu[0];
   tuple[trpx1_mumu] = PXmumu[0];
   tuple[trpy1_mumu] = PYmumu[0];
   tuple[trpz1_mumu] = PZmumu[0];
   tuple[trmag1_mumu] = PMAGmumu[0];
   tuple[trte2_mumu] = PEmumu[1];
   tuple[trpx2_mumu] = PXmumu[1];
   tuple[trpy2_mumu] = PYmumu[1];
   tuple[trpz2_mumu] = PZmumu[1];
   tuple[trmag2_mumu] = PMAGmumu[1];

   tuple[ftrte1_ee] = FPEee[0];
   tuple[ftrpx1_ee] = FPXee[0];
   tuple[ftrpy1_ee] = FPYee[0];
   tuple[ftrpz1_ee] = FPZee[0];
   tuple[ftrte2_ee] = FPEee[1];
   tuple[ftrpx2_ee] = FPXee[1];
   tuple[ftrpy2_ee] = FPYee[1];
   tuple[ftrpz2_ee] = FPZee[1];
   tuple[ftrte1_mee] = FPEmee[0];
   tuple[ftrpx1_mee] = FPXmee[0];
   tuple[ftrpy1_mee] = FPYmee[0];
   tuple[ftrpz1_mee] = FPZmee[0];
   tuple[ftrte2_mee] = FPEmee[1];
   tuple[ftrpx2_mee] = FPXmee[1];
   tuple[ftrpy2_mee] = FPYmee[1];
   tuple[ftrpz2_mee] = FPZmee[1];
   tuple[ftrte1_mumu] = FPEmumu[0];
   tuple[ftrpx1_mumu] = FPXmumu[0];
   tuple[ftrpy1_mumu] = FPYmumu[0];
   tuple[ftrpz1_mumu] = FPZmumu[0];
   tuple[ftrte2_mumu] = FPEmumu[1];
   tuple[ftrpx2_mumu] = FPXmumu[1];
   tuple[ftrpy2_mumu] = FPYmumu[1];
   tuple[ftrpz2_mumu] = FPZmumu[1];
   tuple[ftrte1_mmumu] = FPEmmumu[0];
   tuple[ftrpx1_mmumu] = FPXmmumu[0];
   tuple[ftrpy1_mmumu] = FPYmmumu[0];
   tuple[ftrpz1_mmumu] = FPZmmumu[0];
   tuple[ftrte2_mmumu] = FPEmmumu[1];
   tuple[ftrpx2_mmumu] = FPXmmumu[1];
   tuple[ftrpy2_mmumu] = FPYmmumu[1];
   tuple[ftrpz2_mmumu] = FPZmmumu[1];

   tuple[pass1a] = PASS1[0];
   tuple[pass2a] = PASS2[0];
   tuple[pass3a] = PASS3[0];
   tuple[pass4ea] = PASS4E[0];
   tuple[pass4mua] = PASS4MU[0];
   tuple[pass4ema] = PASS4EM[0];
   tuple[pass4muma] = PASS4MUM[0];

   tuple[pass1b] = PASS1[1];
   tuple[pass2b] = PASS2[1];
   tuple[pass3b] = PASS3[1];
   tuple[pass4eb] = PASS4E[1];
   tuple[pass4mub] = PASS4MU[1];
   tuple[pass4emb] = PASS4EM[1];
   tuple[pass4mumb] = PASS4MUM[1];



   (*m_showerTuple).fill(tuple);


   return ActionBase::kPassed;
}


ActionBase::ActionResult
Chi_c1::beginRun( Frame& iFrame )       // anal2 equiv.
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
Chi_c1::endRun( Frame& iFrame )         // anal4 equiv.
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
