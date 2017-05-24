// -*- C++ -*-
//
// Package:     XXX3872Proc
// Module:      XXX3872Proc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      pts/13
// Created:     Tue Feb 15 11:42:41 CST 2011
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "XXX3872Proc/XXX3872Proc.h"
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
#include "Navigation/NavTkShMatch.h"

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
static const char* const kFacilityString = "Processor.XXX3872Proc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
XXX3872Proc::XXX3872Proc( void )               // anal1
   : Processor( "XXX3872Proc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &XXX3872Proc::event,    Stream::kEvent );
   bind( &XXX3872Proc::beginRun, Stream::kBeginRun );
   //bind( &XXX3872Proc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

XXX3872Proc::~XXX3872Proc()                    // anal5
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
XXX3872Proc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
XXX3872Proc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------

enum {
chisqv1,chisqf1,         //chisq of 4C fit, normal 4C fit
chisqv2,chisqf2,         //chisq of 4C fit, add. ISR
e0,th0,phi0,x9250,        // unfitted photon energy 
f1e1,f1th1,f1phi1,         // fitted photon energy (4C fit)
f2e1,f2th1,f2phi1,         // fitted photon energy (add.ISR fit)
f2e2,f2th2,f2phi2,         // fitted photon energy (add.ISR fit)

eop1,eop2,eop3,eop4,me1,me2,me3,me4,dedx1,dedx2,dedx3,dedx4,
mudepth1,mudepth2,mudepth3,mudepth4,
simple1mu1,simple1mu2,simple1mu3,simple1mu4,
simple2mu1,simple2mu2,simple2mu3,simple2mu4,
trte1,trpx1,trpy1,trpz1,trte2,trpx2,trpy2,trpz2,
trte3,trpx3,trpy3,trpz3,trte4,trpx4,trpy4,trpz4,
f1trte1,f1trpx1,f1trpy1,f1trpz1,f1trte2,f1trpx2,f1trpy2,f1trpz2,
f1trte3,f1trpx3,f1trpy3,f1trpz3,f1trte4,f1trpx4,f1trpy4,f1trpz4,  // 4C fit
f2trte1,f2trpx1,f2trpy1,f2trpz1,f2trte2,f2trpx2,f2trpy2,f2trpz2,
f2trte3,f2trpx3,f2trpy3,f2trpz3,f2trte4,f2trpx4,f2trpy4,f2trpz4,  // add.ISR
id1,id2,id3,id4,charge1,charge2,charge3,charge4,
passed1,passed2,passed3,passed4,passed5,
peak1,peak2,peak3,peak4,peak5,
kVarNum};



void
XXX3872Proc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   HINtupleVarNames ntupleNames(kVarNum);

   ntupleNames.addVar(chisqv1,       "chisqv1");
   ntupleNames.addVar(chisqf1,       "chisqf1");
   ntupleNames.addVar(chisqv2,       "chisqv2");
   ntupleNames.addVar(chisqf2,       "chisqf2");

   ntupleNames.addVar(e0,            "e0");
   ntupleNames.addVar(th0,           "th0");
   ntupleNames.addVar(phi0,          "phi0");
   ntupleNames.addVar(x9250,         "x9250");

   ntupleNames.addVar(f1e1,          "f1e1");
   ntupleNames.addVar(f1th1,         "f1th1");
   ntupleNames.addVar(f1phi1,        "f1phi1");
   ntupleNames.addVar(f2e1,          "f2e1");
   ntupleNames.addVar(f2th1,         "f2th1");
   ntupleNames.addVar(f2phi1,        "f2phi1");
   ntupleNames.addVar(f2e2,          "f2e2");
   ntupleNames.addVar(f2th2,         "f2th2");
   ntupleNames.addVar(f2phi2,        "f2phi2");

   ntupleNames.addVar(eop1,         "eop1");
   ntupleNames.addVar(eop2,         "eop2");
   ntupleNames.addVar(eop3,         "eop3");
   ntupleNames.addVar(eop4,         "eop4");
   ntupleNames.addVar(me1,          "me1");
   ntupleNames.addVar(me2,          "me2");
   ntupleNames.addVar(me3,          "me3");
   ntupleNames.addVar(me4,          "me4");
   ntupleNames.addVar(dedx1,        "dedx1");
   ntupleNames.addVar(dedx2,        "dedx2");
   ntupleNames.addVar(dedx3,        "dedx3");
   ntupleNames.addVar(dedx4,        "dedx4");

   ntupleNames.addVar(mudepth1,     "mudepth1");
   ntupleNames.addVar(mudepth2,     "mudepth2");
   ntupleNames.addVar(mudepth3,     "mudepth3");
   ntupleNames.addVar(mudepth4,     "mudepth4");

   ntupleNames.addVar(simple1mu1,   "simple1mu1");
   ntupleNames.addVar(simple1mu2,   "simple1mu2");
   ntupleNames.addVar(simple1mu3,   "simple1mu3");
   ntupleNames.addVar(simple1mu4,   "simple1mu4");
   ntupleNames.addVar(simple2mu1,   "simple2mu1");
   ntupleNames.addVar(simple2mu2,   "simple2mu2");
   ntupleNames.addVar(simple2mu3,   "simple2mu3");
   ntupleNames.addVar(simple2mu4,   "simple2mu4");

   ntupleNames.addVar(trte1,        "trte1");
   ntupleNames.addVar(trpx1,        "trpx1");
   ntupleNames.addVar(trpy1,        "trpy1");
   ntupleNames.addVar(trpz1,        "trpz1");
   ntupleNames.addVar(trte2,        "trte2");
   ntupleNames.addVar(trpx2,        "trpx2");
   ntupleNames.addVar(trpy2,        "trpy2");
   ntupleNames.addVar(trpz2,        "trpz2");
   ntupleNames.addVar(trte3,        "trte3");
   ntupleNames.addVar(trpx3,        "trpx3");
   ntupleNames.addVar(trpy3,        "trpy3");
   ntupleNames.addVar(trpz3,        "trpz3");
   ntupleNames.addVar(trte4,        "trte4");
   ntupleNames.addVar(trpx4,        "trpx4");
   ntupleNames.addVar(trpy4,        "trpy4");
   ntupleNames.addVar(trpz4,        "trpz4");

   ntupleNames.addVar(f1trte1,       "f1trte1");
   ntupleNames.addVar(f1trpx1,       "f1trpx1");
   ntupleNames.addVar(f1trpy1,       "f1trpy1");
   ntupleNames.addVar(f1trpz1,       "f1trpz1");
   ntupleNames.addVar(f1trte2,       "f1trte2");
   ntupleNames.addVar(f1trpx2,       "f1trpx2");
   ntupleNames.addVar(f1trpy2,       "f1trpy2");
   ntupleNames.addVar(f1trpz2,       "f1trpz2");
   ntupleNames.addVar(f1trte3,       "f1trte3");
   ntupleNames.addVar(f1trpx3,       "f1trpx3");
   ntupleNames.addVar(f1trpy3,       "f1trpy3");
   ntupleNames.addVar(f1trpz3,       "f1trpz3");
   ntupleNames.addVar(f1trte4,       "f1trte4");
   ntupleNames.addVar(f1trpx4,       "f1trpx4");
   ntupleNames.addVar(f1trpy4,       "f1trpy4");
   ntupleNames.addVar(f1trpz4,       "f1trpz4");
   ntupleNames.addVar(f2trte1,       "f2trte1");
   ntupleNames.addVar(f2trpx1,       "f2trpx1");
   ntupleNames.addVar(f2trpy1,       "f2trpy1");
   ntupleNames.addVar(f2trpz1,       "f2trpz1");
   ntupleNames.addVar(f2trte2,       "f2trte2");
   ntupleNames.addVar(f2trpx2,       "f2trpx2");
   ntupleNames.addVar(f2trpy2,       "f2trpy2");
   ntupleNames.addVar(f2trpz2,       "f2trpz2");
   ntupleNames.addVar(f2trte3,       "f2trte3");
   ntupleNames.addVar(f2trpx3,       "f2trpx3");
   ntupleNames.addVar(f2trpy3,       "f2trpy3");
   ntupleNames.addVar(f2trpz3,       "f2trpz3");
   ntupleNames.addVar(f2trte4,       "f2trte4");
   ntupleNames.addVar(f2trpx4,       "f2trpx4");
   ntupleNames.addVar(f2trpy4,       "f2trpy4");
   ntupleNames.addVar(f2trpz4,       "f2trpz4");

   ntupleNames.addVar(id1,          "id1");
   ntupleNames.addVar(id2,          "id2");
   ntupleNames.addVar(id3,          "id3");
   ntupleNames.addVar(id4,          "id4");
   ntupleNames.addVar(charge1,      "charge1");
   ntupleNames.addVar(charge2,      "charge2");
   ntupleNames.addVar(charge3,      "charge3");
   ntupleNames.addVar(charge4,      "charge4");
   ntupleNames.addVar(passed1,      "passed1");
   ntupleNames.addVar(passed2,      "passed2");
   ntupleNames.addVar(passed3,      "passed3");
   ntupleNames.addVar(passed4,      "passed4");
   ntupleNames.addVar(passed5,      "passed5");
   ntupleNames.addVar(peak1,        "peak1");
   ntupleNames.addVar(peak2,        "peak2");
   ntupleNames.addVar(peak3,        "peak3");
   ntupleNames.addVar(peak4,        "peak4");
   ntupleNames.addVar(peak5,        "peak5");

   m_showerTuple = iHistoManager.ntuple(10,"tuple", kVarNum, 10000, ntupleNames.names());



}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
XXX3872Proc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   const int kMaxTrack = 4;

   double ChisqV1 = 1000000.;
   double ChisqF1 = 1000000.;
   double ChisqV2 = 1000000.;
   double ChisqF2 = 1000000.;
   double TempChisqV2 = 1000000.;
   double TempChisqF2 = 1000000.;

   double E0 = 0.;
   double Theta0 = 0.;
   double Phi0 = 0.;
   double E9250 = 0.;
   double F1E1 = 0.;
   double F1Theta1 = 0.;
   double F1Phi1 = 0.;
   double F2E1 = 0.;
   double F2Theta1 = 0.;
   double F2Phi1 = 0.;
   double F2E2 = 0.;
   double F2Theta2 = 0.;
   double F2Phi2 = 0.;

   double ME[kMaxTrack] = {0.,0.,0.,0.};
   double EOP[kMaxTrack] = {0.,0.,0.,0};
   double DEDX[kMaxTrack] = {10000.,10000.,10000.,10000.};
   double MUDEPTH[kMaxTrack] = {0.,0.,0.,0.};
   int SIMPLE1MU[kMaxTrack] = {-1.,-1.,-1.,-1.};
   int SIMPLE2MU[kMaxTrack] = {-1.,-1.,-1.,-1.};

   double PE[kMaxTrack] = {0.,0.,0.,0.};
   double PX[kMaxTrack] = {0.,0.,0.,0.};
   double PY[kMaxTrack] = {0.,0.,0.,0.};
   double PZ[kMaxTrack] = {0.,0.,0.,0.};
   double F1PE[kMaxTrack] = {0.,0.,0.,0.};
   double F1PX[kMaxTrack] = {0.,0.,0.,0.};
   double F1PY[kMaxTrack] = {0.,0.,0.,0.};
   double F1PZ[kMaxTrack] = {0.,0.,0.,0.};
   double F2PE[kMaxTrack] = {0.,0.,0.,0.};
   double F2PX[kMaxTrack] = {0.,0.,0.,0.};
   double F2PY[kMaxTrack] = {0.,0.,0.,0.};
   double F2PZ[kMaxTrack] = {0.,0.,0.,0.};

   int CHARGE[kMaxTrack] = {100,100,100,100};
   int ID[kMaxTrack] = {-100,-100,-100,-100};  //0:pi, 1:e, 2: mu
   double PASSED1 = 0;
   double PASSED2 = 0;
   double PASSED3 = 0;
   double PASSED4 = 0;
   double PASSED5 = 0;
   double PEAK1 = 0;
   double PEAK2 = 0;
   double PEAK3 = 0;
   double PEAK4 = 0;
   double PEAK5 = 0;


   float tuple[kVarNum];

///////////////////////////////////// # of showers = 1 ////////////////////////////////

   int unmatchedShowers = 0;

   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ) , showerTable, "GoodThings" );

   FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
   FATable< NavShower >::const_iterator showerEnd = showerTable.end();

   FATable< NavShower >::const_iterator sh;

   for ( FATable< NavShower >::const_iterator showerItr = showerBegin;
         showerItr != showerEnd ;
         ++showerItr )
      {

         if(showerItr->attributes().x925() < 1)  continue;
         if(showerItr->attributes().energy()<0.05) continue;

         E0 = showerItr->attributes().energy();
         Theta0 = showerItr->attributes().theta();
         Phi0 = showerItr->attributes().phi();
         E9250 = showerItr->attributes().x925();
         sh = showerItr;

         unmatchedShowers++;
      }

   if(unmatchedShowers != 1)
      return ActionBase::kFailed;


//////////////////////////////////// # of tracks == 4 /////////////////////////////////


   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable, "GoodThings" );

   if(trackTable.size() != kMaxTrack)
       return ActionBase::kFailed;

   FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();

/////////////////////////////////// net charge == 0 ////////////////////////////////////

   int unmatchedtracks = 0;
   int charge_sum = 0;

   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;
         ++trackItr )
   {
      int i = unmatchedtracks++;
      CHARGE[i]=(*trackItr).pionFit()->charge();
      PE[i]=(*trackItr).pionFit()->energy();
      PX[i]=(*trackItr).pionFit()->px();
      PY[i]=(*trackItr).pionFit()->py();
      PZ[i]=(*trackItr).pionFit()->pz();
      charge_sum += CHARGE[i];
   }

   if(charge_sum != 0)
       return ActionBase::kFailed;

   PASSED1 = 1;
   PEAK1 = sqrt(pow((PE[0]+PE[1]+PE[2]+PE[3]),2)-pow((PX[0]+PX[1]+PX[2]+PX[3]),2)-pow((PY[0]+PY[1]+PY[2]+PY[3]),2)-pow((PZ[0]+PZ[1]+PZ[2]+PZ[3]),2));

//////////////////////////////////////////////////////////////////////////////////////////
/////////////////// tell pipi from ee or mumu using their energy  ////////////////////////
/////////////////// pipi: |e| < 0.5 , mumu or ee: |e| > 0.5 //////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

   unmatchedtracks = 0;
   int id_sum = 0;

   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;
         ++trackItr )
   {
      int i = unmatchedtracks++;
      PE[i]=(*trackItr).pionFit()->lorentzMomentum().e();

      if(trackItr->trackShowerMatch().valid())
         ME[i] = trackItr->trackShowerMatch()->matchedEnergy();

      EOP[i] = trackItr->elecId().eOverP();
      MUDEPTH[i] = trackItr->muonId().depth();
      SIMPLE1MU[i] = trackItr->muonId().simpleMuonId1();
      SIMPLE2MU[i] = trackItr->muonId().simpleMuonId2();

      FAItem<DedxInfo> the_dedx = (*trackItr).dedxInfo();

      if(PE[i] < 0.5) {
        FAItem<TDKinematicFit> pionFit = (*trackItr).pionFit();
        if( (pionFit.valid()) && (the_dedx.valid()) )  {
          ID[i] = 0;
          PE[i]=pionFit->energy();
          PX[i]=pionFit->px();
          PY[i]=pionFit->py();
          PZ[i]=pionFit->pz();
          DEDX[i]=the_dedx->piSigma();
        }
      }
      else if(PE[i]>= 0.5){
        if(EOP[i] > 0.8 && EOP[i] < 1.2) {
          FAItem<TDKinematicFit> electronFit = (*trackItr).electronFit();

          FATable<NavShower> brem(trackItr->bremShowers());
 
	    HepDouble gamsx = 0., gamsy = 0., gamsz = 0.;

	    for(FATable<NavShower>::const_iterator iGam=brem.begin();
		iGam != brem.end(); ++iGam) {
	       gamsx += iGam->attributes().momentum().x();
	       gamsy += iGam->attributes().momentum().y();
	       gamsz += iGam->attributes().momentum().z();
            }

          if( (electronFit.valid()) && (the_dedx.valid()) )  {
            ID[i] = 1;
            PE[i]=sqrt(fabs( 0.000511*0.000511
                        + (electronFit->px()+gamsx)*(electronFit->px()+gamsx)
                        + (electronFit->py()+gamsy)*(electronFit->py()+gamsy)
                        + (electronFit->pz()+gamsz)*(electronFit->pz()+gamsz) )); 
            PX[i]=electronFit->px()+gamsx;
            PY[i]=electronFit->py()+gamsy;
            PZ[i]=electronFit->pz()+gamsz;
            DEDX[i]=the_dedx->eSigma();
          }
        }
        else if(EOP[i] < 0.8) {
          FAItem<TDKinematicFit> muonFit = (*trackItr).muonFit();
          if( (muonFit.valid()) && (the_dedx.valid()) )  {
            ID[i] = 2;
            PE[i]=muonFit->energy();
            PX[i]=muonFit->px();
            PY[i]=muonFit->py();
            PZ[i]=muonFit->pz();
            DEDX[i]=the_dedx->muSigma();
          }
        }
      }

      id_sum += ID[i];
   }
   if(id_sum > 0) {
     PASSED2 = 1;
     PEAK2 = sqrt(pow((PE[0]+PE[1]+PE[2]+PE[3]),2)-pow((PX[0]+PX[1]+PX[2]+PX[3]),2)-pow((PY[0]+PY[1]+PY[2]+PY[3]),2)-pow((PZ[0]+PZ[1]+PZ[2]+PZ[3]),2));
   }

/*
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////// set cut |m(mumu or ee) - 3.097| < 100 MeV ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

   double m_Jpsi = 0;

   for(int i = 0; i < 4; i++) {
     if(ID[i] > 0) {
       for(int j = i+1; j < 4; j++ ) {
         if(ID[j] > 0 && ID[i] == ID[j]) {
            m_Jpsi = sqrt(pow((PE[i]+PE[j]),2)-pow((PX[i]+PX[j]),2)-pow((PY[i]+PY[j]),2)-pow((PZ[i]+PZ[j]),2));
            if(fabs(m_Jpsi-3.097) < 0.1)
              PASSED3 = 1;
         }
       }
     }
   }

   if(PASSED3)
     PEAK3 = sqrt(pow((PE[0]+PE[1]+PE[2]+PE[3]),2)-pow((PX[0]+PX[1]+PX[2]+PX[3]),2)-pow((PY[0]+PY[1]+PY[2]+PY[3]),2)-pow((PZ[0]+PZ[1]+PZ[2]+PZ[3]),2));
*/
////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// kinematic fitting  ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

   if(PASSED2) {

     FAItem<TDKinematicFit> tr[4];
     FAItem<KTKinematicData> track[4];
     unmatchedtracks = 0;

     for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
           trackItr != trackTableEnd ;
           ++trackItr )
       {
          int i = unmatchedtracks++;

          if(ID[i] == 0) {
            tr[i] = (*trackItr).pionFit();
            track[i] = *tr[i];
          }
          else if(ID[i] == 1) {
            tr[i] = (*trackItr).electronFit();
            track[i] = *tr[i];

            FATable<NavShower> brem(trackItr->bremShowers());
 
	    HepDouble gamsx = 0., gamsy = 0., gamsz = 0.;
	    for(FATable<NavShower>::const_iterator iGam=brem.begin();
		iGam != brem.end(); ++iGam) {
	       gamsx += iGam->attributes().momentum().x();
	       gamsy += iGam->attributes().momentum().y();
	       gamsz += iGam->attributes().momentum().z();
	    }
            track[i].setMomentum(tr[i]->px()+gamsx,tr[i]->py()+gamsy,tr[i]->pz()+gamsz);
          }
          else if(ID[i] == 2) {
            tr[i] = (*trackItr).muonFit();
            track[i] = *tr[i];
          }
       }



////////////////////////////////// 4C fit /////////////////////////////////////////////////////////////////////


   if(tr[0].valid() && tr[1].valid() && tr[2].valid() && tr[3].valid()) {

      // do the fit

      FitEvt pipitrtr1( "Pipitrtr1", FitEvt::k_P4VecCM );
      pipitrtr1.newPhoton(*sh);
      pipitrtr1.newTrack(track[0]);
      pipitrtr1.newTrack(track[1]);
      pipitrtr1.newTrack(track[2]);
      pipitrtr1.newTrack(track[3]);
      pipitrtr1.doTheFit();

      if( (pipitrtr1.chisqVtx()>0) && (pipitrtr1.chisqFit()>0) ) {
	
     	         HepLorentzVector v0 (pipitrtr1.kdFitVec()[0]->lorentzMomentum());
	         HepLorentzVector v1 (pipitrtr1.kdFitVec()[1]->lorentzMomentum());
	         HepLorentzVector v2 (pipitrtr1.kdFitVec()[2]->lorentzMomentum());
        	 HepLorentzVector v3 (pipitrtr1.kdFitVec()[3]->lorentzMomentum());
        	 HepLorentzVector v4 (pipitrtr1.kdFitVec()[4]->lorentzMomentum());

         	    ChisqV1 = pipitrtr1.chisqVtx();
	            ChisqF1 = pipitrtr1.chisqFit();

        	    F1E1 = v0.e();
	            F1Theta1 = v0.theta();
        	    F1Phi1 = v0.phi();

        	    F1PE[0]=v1.e();
	            F1PX[0]=v1.px();
       		    F1PY[0]=v1.py();
	            F1PZ[0]=v1.pz();
       		    F1PE[1]=v2.e();
        	    F1PX[1]=v2.px();
        	    F1PY[1]=v2.py();
	            F1PZ[1]=v2.pz();
       		    F1PE[2]=v3.e();
	            F1PX[2]=v3.px();
       		    F1PY[2]=v3.py();
        	    F1PZ[2]=v3.pz();
        	    F1PE[3]=v4.e();
	            F1PX[3]=v4.px();
       		    F1PY[3]=v4.py();
	            F1PZ[3]=v4.pz();

		      }			// if fit converge ends
	 	    }			// if FAItem.valid ends

      if(ChisqV1 < 1000000 && ChisqF1 < 1000000) {
         PASSED4 = 1;
         PEAK4 = sqrt(pow((F1PE[0]+F1PE[1]+F1PE[2]+F1PE[3]),2)-pow((F1PX[0]+F1PX[1]+F1PX[2]+F1PX[3]),2)
                 -pow((F1PY[0]+F1PY[1]+F1PY[2]+F1PY[3]),2)-pow((F1PZ[0]+F1PZ[1]+F1PZ[2]+F1PZ[3]),2));
      }

///////////////////////////////////////// fit 2: add.ISR ///////////////////////////////////////////////////////

FAItem< BeamSpot > spot;
extract( iFrame.record( Stream::kBeginRun ), spot );

HepVector3D momentum(0,0,0.001);
HepVector3D position(spot->center());
double mass = 0;
double charge = 0;

FAItem<TDKinematicFit> addISR;

if(tr[0].valid())       addISR = tr[0];
else if(tr[1].valid())  addISR = tr[1];
else if(tr[2].valid())  addISR = tr[2];
else if(tr[3].valid())  addISR = tr[3];
else                    return ActionBase::kFailed;


HepSymMatrix errMatrix((*addISR).errorMatrix());

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

     for ( FATable< NavShower >::const_iterator showerItr = showerBegin;
           showerItr != showerEnd ;
           ++showerItr )
        {

          if(showerItr->attributes().x925() < 1)  continue;
          if(showerItr->attributes().energy()<0.05) continue;

          if(tr[0].valid() && tr[1].valid() && tr[2].valid() && tr[3].valid()) {

          // do the fit

             FitEvt pipitrtr2( "Pipitrtr2", FitEvt::k_P4VecCM );
             pipitrtr2.newPhoton(*showerItr);
             pipitrtr2.newKinDat(undetected_shower);
             pipitrtr2.newTrack(track[0]);
             pipitrtr2.newTrack(track[1]);
             pipitrtr2.newTrack(track[2]);
             pipitrtr2.newTrack(track[3]);
             pipitrtr2.doTheFit();

             if(pipitrtr2.chisqVtx()>0) {
                PEAK3 = sqrt(pow((PE[0]+PE[1]+PE[2]+PE[3]),2)-pow((PX[0]+PX[1]+PX[2]+PX[3]),2)
                        -pow((PY[0]+PY[1]+PY[2]+PY[3]),2)-pow((PZ[0]+PZ[1]+PZ[2]+PZ[3]),2));

                if(pipitrtr2.chisqFit()>0) {

                HepLorentzVector v0 (pipitrtr2.kdFitVec()[0]->lorentzMomentum());
                HepLorentzVector vg (pipitrtr2.kdFitVec()[1]->lorentzMomentum());
                HepLorentzVector v1 (pipitrtr2.kdFitVec()[2]->lorentzMomentum());
                HepLorentzVector v2 (pipitrtr2.kdFitVec()[3]->lorentzMomentum());
                HepLorentzVector v3 (pipitrtr2.kdFitVec()[4]->lorentzMomentum());
                HepLorentzVector v4 (pipitrtr2.kdFitVec()[5]->lorentzMomentum());

                TempChisqV2 = pipitrtr2.chisqVtx();
                TempChisqF2 = pipitrtr2.chisqFit();

                if(TempChisqF2 < ChisqF2){

                   ChisqV2 = pipitrtr2.chisqVtx();
                   ChisqF2 = pipitrtr2.chisqFit();


                   F2E1 = v0.e();
                   F2Theta1 = v0.theta();
                   F2Phi1 = v0.phi();
                   F2E2 = vg.e();
                   F2Theta2 = vg.theta();
                   F2Phi2 = vg.phi();

                   F2PE[0]=v1.e();
                   F2PX[0]=v1.px();
                   F2PY[0]=v1.py();
                   F2PZ[0]=v1.pz();
                   F2PE[1]=v2.e();
                   F2PX[1]=v2.px();
                   F2PY[1]=v2.py();
                   F2PZ[1]=v2.pz();
                   F2PE[2]=v3.e();
                   F2PX[2]=v3.px();
                   F2PY[2]=v3.py();
                   F2PZ[2]=v3.pz();
                   F2PE[3]=v4.e();
                   F2PX[3]=v4.px();
                   F2PY[3]=v4.py();
                   F2PZ[3]=v4.pz();

                }                       // if found smaller chisqf ends
            }                           // if fit converge ends
            }                           // if vertex converge ends
          }                             // second for loop ends
	}                               // firstfor loop ends

      if(ChisqV2 < 1000000 && ChisqF2 < 1000000) {
         PASSED5 = 1;
//         PEAK4 = sqrt(pow((PE[0]+PE[1]+PE[2]+PE[3]),2)-pow((PX[0]+PX[1]+PX[2]+PX[3]),2)
//                 -pow((PY[0]+PY[1]+PY[2]+PY[3]),2)-pow((PZ[0]+PZ[1]+PZ[2]+PZ[3]),2));
         PEAK5 = sqrt(pow((F2PE[0]+F2PE[1]+F2PE[2]+F2PE[3]),2)-pow((F2PX[0]+F2PX[1]+F2PX[2]+F2PX[3]),2)
                 -pow((F2PY[0]+F2PY[1]+F2PY[2]+F2PY[3]),2)-pow((F2PZ[0]+F2PZ[1]+F2PZ[2]+F2PZ[3]),2));
      }

   }					//  if(PASSED2) ends




   tuple[chisqv1] = ChisqV1;
   tuple[chisqf1] = ChisqF1;
   tuple[chisqv2] = ChisqV2;
   tuple[chisqf2] = ChisqF2;

   tuple[e0] = E0;
   tuple[th0] = Theta0;
   tuple[phi0] = Phi0;
   tuple[x9250] = E9250;

   tuple[f1e1] = F1E1;
   tuple[f1th1] = F1Theta1;
   tuple[f1phi1] = F1Phi1;
   tuple[f2e1] = F2E1;
   tuple[f2th1] = F2Theta1;
   tuple[f2phi1] = F2Phi1;
   tuple[f2e2] = F2E2;
   tuple[f2th2] = F2Theta2;
   tuple[f2phi2] = F2Phi2;

   tuple[eop1] = EOP[0];
   tuple[eop2] = EOP[1];
   tuple[eop3] = EOP[2];
   tuple[eop4] = EOP[3];
   tuple[me1] = ME[0];
   tuple[me2] = ME[1];
   tuple[me3] = ME[2];
   tuple[me4] = ME[3];
   tuple[dedx1] = DEDX[0];
   tuple[dedx2] = DEDX[1];
   tuple[dedx3] = DEDX[2];
   tuple[dedx4] = DEDX[3];

   tuple[mudepth1] = MUDEPTH[0];
   tuple[mudepth2] = MUDEPTH[1];
   tuple[mudepth3] = MUDEPTH[2];
   tuple[mudepth4] = MUDEPTH[3];

   tuple[simple1mu1] = SIMPLE1MU[0];
   tuple[simple1mu2] = SIMPLE1MU[1];
   tuple[simple1mu3] = SIMPLE1MU[2];
   tuple[simple1mu4] = SIMPLE1MU[3];
   tuple[simple2mu1] = SIMPLE2MU[0];
   tuple[simple2mu2] = SIMPLE2MU[1];
   tuple[simple2mu3] = SIMPLE2MU[2];
   tuple[simple2mu4] = SIMPLE2MU[3];

   tuple[trte1] = PE[0];
   tuple[trpx1] = PX[0];
   tuple[trpy1] = PY[0];
   tuple[trpz1] = PZ[0];
   tuple[trte2] = PE[1];
   tuple[trpx2] = PX[1];
   tuple[trpy2] = PY[1];
   tuple[trpz2] = PZ[1];
   tuple[trte3] = PE[2];
   tuple[trpx3] = PX[2];
   tuple[trpy3] = PY[2];
   tuple[trpz3] = PZ[2];
   tuple[trte4] = PE[3];
   tuple[trpx4] = PX[3];
   tuple[trpy4] = PY[3];
   tuple[trpz4] = PZ[3];

   tuple[f1trte1] = F1PE[0];
   tuple[f1trpx1] = F1PX[0];
   tuple[f1trpy1] = F1PY[0];
   tuple[f1trpz1] = F1PZ[0];
   tuple[f1trte2] = F1PE[1];
   tuple[f1trpx2] = F1PX[1];
   tuple[f1trpy2] = F1PY[1];
   tuple[f1trpz2] = F1PZ[1];
   tuple[f1trte3] = F1PE[2];
   tuple[f1trpx3] = F1PX[2];
   tuple[f1trpy3] = F1PY[2];
   tuple[f1trpz3] = F1PZ[2];
   tuple[f1trte4] = F1PE[3];
   tuple[f1trpx4] = F1PX[3];
   tuple[f1trpy4] = F1PY[3];
   tuple[f1trpz4] = F1PZ[3];
   tuple[f2trte1] = F2PE[0];
   tuple[f2trpx1] = F2PX[0];
   tuple[f2trpy1] = F2PY[0];
   tuple[f2trpz1] = F2PZ[0];
   tuple[f2trte2] = F2PE[1];
   tuple[f2trpx2] = F2PX[1];
   tuple[f2trpy2] = F2PY[1];
   tuple[f2trpz2] = F2PZ[1];
   tuple[f2trte3] = F2PE[2];
   tuple[f2trpx3] = F2PX[2];
   tuple[f2trpy3] = F2PY[2];
   tuple[f2trpz3] = F2PZ[2];
   tuple[f2trte4] = F2PE[3];
   tuple[f2trpx4] = F2PX[3];
   tuple[f2trpy4] = F2PY[3];
   tuple[f2trpz4] = F2PZ[3];

   tuple[id1] = ID[0];
   tuple[id2] = ID[1];
   tuple[id3] = ID[2];
   tuple[id4] = ID[3];
   tuple[charge1] = CHARGE[0];
   tuple[charge2] = CHARGE[1];
   tuple[charge3] = CHARGE[2];
   tuple[charge4] = CHARGE[3];
   tuple[passed1] = PASSED1;
   tuple[passed2] = PASSED2;
   tuple[passed3] = PASSED3;
   tuple[passed4] = PASSED4;
   tuple[passed5] = PASSED5;
   tuple[peak1] = PEAK1;
   tuple[peak2] = PEAK2;
   tuple[peak3] = PEAK3;
   tuple[peak4] = PEAK4;
   tuple[peak5] = PEAK5;


   (*m_showerTuple).fill(tuple);




   return ActionBase::kPassed;
}


ActionBase::ActionResult
XXX3872Proc::beginRun( Frame& iFrame )       // anal2 equiv.
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
XXX3872Proc::endRun( Frame& iFrame )         // anal4 equiv.
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
