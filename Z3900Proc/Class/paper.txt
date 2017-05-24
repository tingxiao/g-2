// -*- C++ -*-
//
// Package:     Z3900Proc
// Module:      Z3900Proc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Tue Mar 26 11:49:17 CDT 2013
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "Z3900Proc/Z3900Proc.h"
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
static const char* const kFacilityString = "Processor.Z3900Proc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
Z3900Proc::Z3900Proc( void )               // anal1
   : Processor( "Z3900Proc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &Z3900Proc::event,    Stream::kEvent );
   bind( &Z3900Proc::beginRun, Stream::kBeginRun );
   //bind( &Z3900Proc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

Z3900Proc::~Z3900Proc()                    // anal5
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
Z3900Proc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
Z3900Proc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------

enum {
chisqv1,chisqf1,         //chisq of 4C fit, normal 4C fit
chisqv2,chisqf2,         //chisq of J/psi mass fit
eop1,eop2,eop3,eop4,me1,me2,me3,me4,dedx1,dedx2,dedx3,dedx4,
trte1,trpx1,trpy1,trpz1,trte2,trpx2,trpy2,trpz2,
trte3,trpx3,trpy3,trpz3,trte4,trpx4,trpy4,trpz4,
f1trte1,f1trpx1,f1trpy1,f1trpz1,f1trte2,f1trpx2,f1trpy2,f1trpz2,
f1trte3,f1trpx3,f1trpy3,f1trpz3,f1trte4,f1trpx4,f1trpy4,f1trpz4,  // 4C fit
id1,id2,id3,id4,charge1,charge2,charge3,charge4,
mudepth1,mudepth2,mudepth3,mudepth4,  //muon depth 
passed1,passed2,passed3,
peak1,peak2,peak3,
kVarNum};

void
Z3900Proc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   HINtupleVarNames ntupleNames(kVarNum);

   ntupleNames.addVar(chisqv1,       "chisqv1");
   ntupleNames.addVar(chisqf1,       "chisqf1");
   ntupleNames.addVar(chisqv2,       "chisqv2");
   ntupleNames.addVar(chisqf2,       "chisqf2");
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
   ntupleNames.addVar(peak1,        "peak1");
   ntupleNames.addVar(peak2,        "peak2");
   ntupleNames.addVar(peak3,        "peak3");
   ntupleNames.addVar(mudepth1,      "mudepth1");
   ntupleNames.addVar(mudepth2,      "mudepth2");
   ntupleNames.addVar(mudepth3,      "mudepth3");
   ntupleNames.addVar(mudepth4,      "mudepth4");

   m_showerTuple = iHistoManager.ntuple(10,"tuple", kVarNum, 10000, ntupleNames.names());



}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
Z3900Proc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   const int kMaxTrack = 4;

   double ChisqV1 = 10000000.;
   double ChisqF1 = 10000000.;
   double ChisqV2 = 10000000.;
   double ChisqF2 = 10000000.;
   double ME[kMaxTrack] = {10000.,10000.,10000.,10000.};
   double EOP[kMaxTrack] = {10000.,10000.,10000.,10000};
   double DEDX[kMaxTrack] = {10000.,10000.,10000.,10000.};
   double PE[kMaxTrack] = {0.,0.,0.,0.};
   double PX[kMaxTrack] = {0.,0.,0.,0.};
   double PY[kMaxTrack] = {0.,0.,0.,0.};
   double PZ[kMaxTrack] = {0.,0.,0.,0.};
   double F1PE[kMaxTrack] = {0.,0.,0.,0.};
   double F1PX[kMaxTrack] = {0.,0.,0.,0.};
   double F1PY[kMaxTrack] = {0.,0.,0.,0.};
   double F1PZ[kMaxTrack] = {0.,0.,0.,0.};
   int CHARGE[kMaxTrack] = {100,100,100,100};
   int ID[kMaxTrack] = {-100,-100,-100,-100};  //0:pi, 1:e, 2: mu
   double PASSED1 = 0;
   double PASSED2 = 0;
   double PASSED3 = 0;
   double PEAK1 = 0;
   double PEAK2 = 0;
   double PEAK3 = 0;
   double MUDEPTH[kMaxTrack] = {0.,0.,0.,0.};

   const double kJpsiMass = 3.096916;

   float tuple[kVarNum];




//////////////////////////////////// # of showers == 0 //////////////////////////////
/*
   int unmatchedShowers = 0;

   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ) , showerTable, "GoodThings" );

   FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
   FATable< NavShower >::const_iterator showerEnd = showerTable.end();

   for ( FATable< NavShower >::const_iterator showerItr = showerBegin;
         showerItr != showerEnd ;
         ++showerItr )
      {

         if(showerItr->attributes().x925() < 1)  continue;
         if(showerItr->attributes().energy()<0.05) continue;
         unmatchedShowers++;
      }

   if(unmatchedShowers > 0)
      return ActionBase::kFailed;

*/
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
      MUDEPTH[i] = trackItr->muonId().depth();
   }

   if(charge_sum != 0)
       return ActionBase::kFailed;

   PASSED1 = 1;
   PEAK1 = sqrt(pow((PE[0]+PE[1]+PE[2]+PE[3]),2)-pow((PX[0]+PX[1]+PX[2]+PX[3]),2)-
                pow((PY[0]+PY[1]+PY[2]+PY[3]),2)-pow((PZ[0]+PZ[1]+PZ[2]+PZ[3]),2));

//////////////////////////////////////////////////////////////////////////////////////////
/////////////////// tell pipi from ee or mumu using their energy  ////////////////////////
/////////////////// pipi: |e| < 1.0 , mumu or ee: |e| > 1.0 //////////////////////////////
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
      FAItem<DedxInfo> the_dedx = (*trackItr).dedxInfo();
      if(PE[i] < 1.0) {
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
      else if(PE[i]>= 1.0){
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
//        else
//          return ActionBase::kFailed;
      }

      id_sum += ID[i];
   }
   if(id_sum > 0) {
     PASSED2 = 1;
     PEAK2 = sqrt(pow((PE[0]+PE[1]+PE[2]+PE[3]),2)-pow((PX[0]+PX[1]+PX[2]+PX[3]),2)
                  -pow((PY[0]+PY[1]+PY[2]+PY[3]),2)-pow((PZ[0]+PZ[1]+PZ[2]+PZ[3]),2));
   }


////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// kinematic fitting  ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/*
   if(PASSED2) {

     FAItem<TDKinematicFit> tr[4];
     KTKinematicData track_pip, track_pim, track_mup, track_mum,track_ep, track_em;
     unmatchedtracks = 0;

     for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
           trackItr != trackTableEnd ;
           ++trackItr )
       {
          int i = unmatchedtracks++;

          if(ID[i] == 0) {
            tr[i] = (*trackItr).pionFit();
            if(CHARGE[i]>0)
              track_pip = *tr[i];
            else if(CHARGE[i]<0)
              track_pim = *tr[i];
          }
          else if(ID[i] == 1) {
            tr[i] = (*trackItr).electronFit();
            if(CHARGE[i]>0) {
              track_ep = *tr[i];

              FATable<NavShower> brem(trackItr->bremShowers());
 
              HepDouble gamsx = 0., gamsy = 0., gamsz = 0.;
              for(FATable<NavShower>::const_iterator iGam=brem.begin();
                  iGam != brem.end(); ++iGam) {
                 gamsx += iGam->attributes().momentum().x();
                 gamsy += iGam->attributes().momentum().y();
                 gamsz += iGam->attributes().momentum().z();
              }
              track_ep.setMomentum(HepVector3D(tr[i]->px()+gamsx,tr[i]->py()+gamsy,tr[i]->pz()+gamsz));
            }
            else if(CHARGE[i]<0) {
              track_em = *tr[i];

              FATable<NavShower> brem(trackItr->bremShowers());
 
              HepDouble gamsx = 0., gamsy = 0., gamsz = 0.;
              for(FATable<NavShower>::const_iterator iGam=brem.begin();
                  iGam != brem.end(); ++iGam) {
                 gamsx += iGam->attributes().momentum().x();
                 gamsy += iGam->attributes().momentum().y();
                 gamsz += iGam->attributes().momentum().z();
              }
              track_em.setMomentum(HepVector3D(tr[i]->px()+gamsx,tr[i]->py()+gamsy,tr[i]->pz()+gamsz));
            }
          }


          else if(ID[i] == 2) {
            tr[i] = (*trackItr).muonFit();
            if(CHARGE[i]>0)
              track_mup = *tr[i];
            else if(CHARGE[i]<0)
              track_mum = *tr[i];
          }
       }

////////////////////////////////// 4C fit with J/psi mass constrain /////////////////////////////////////////////////////////////////

   if(tr[0].valid() && tr[1].valid() && tr[2].valid() && tr[3].valid()) {

      // do the fit
     if(id_sum == 2) {
       FitEvt jpsi_ee( "Jpsi_ee", FitEvt::k_Mass, 0, kJpsiMass );
       jpsi_ee.newTrack(track_ep);
       jpsi_ee.newTrack(track_em);
       jpsi_ee.doTheFit();
     
       if( (jpsi_ee.chisqVtx()>0) && (jpsi_ee.chisqFit()>0) ) {
         FitEvt pipiee( "Pipiee", FitEvt::k_P4VecCM );
         pipiee.newTrack(track_pip);
         pipiee.newTrack(track_pim);
         pipiee.newKinDat(jpsi_ee.fitResult());

         pipiee.doTheFit();

         if( (pipiee.chisqVtx()>0) && (pipiee.chisqFit()>0) ) {

                 HepLorentzVector v1 (jpsi_ee.kdFitVec()[0]->lorentzMomentum());
                 HepLorentzVector v2 (jpsi_ee.kdFitVec()[1]->lorentzMomentum());
                 HepLorentzVector v3 (pipiee.kdFitVec()[0]->lorentzMomentum());
                 HepLorentzVector v4 (pipiee.kdFitVec()[1]->lorentzMomentum());

                    ChisqV1 = pipiee.chisqVtx();
                    ChisqF1 = pipiee.chisqFit();
                    ChisqV2 = jpsi_ee.chisqVtx();
                    ChisqF2 = jpsi_ee.chisqFit();

                    for(int j=0; j<4; j++) {
                      if(ID[j]==0 && CHARGE[j]>0) {
                         F1PE[j]=v3.e();
                         F1PX[j]=v3.px();
                         F1PY[j]=v3.py();
                         F1PZ[j]=v3.pz();
                      }
                      else if(ID[j]==0 && CHARGE[j]<0) {
                         F1PE[j]=v4.e();
                         F1PX[j]=v4.px();
                         F1PY[j]=v4.py();
                         F1PZ[j]=v4.pz();
                      }
                      else if(ID[j]==1 && CHARGE[j]>0) {
                         F1PE[j]=v1.e();
                         F1PX[j]=v1.px();
                         F1PY[j]=v1.py();
                         F1PZ[j]=v1.pz();
                      }
                      else if(ID[j]==1 && CHARGE[j]<0) {
                         F1PE[j]=v2.e();
                         F1PX[j]=v2.px();
                         F1PY[j]=v2.py();
                         F1PZ[j]=v2.pz();
                      }

                    }

        }               // if 4C fit converge ends
      }               // if mass fit converge ends
    }                 // if id_sum ends


     else if(id_sum == 4) {
       FitEvt jpsi_mumu( "Jpsi_mumu", FitEvt::k_Mass, 0, kJpsiMass );
       jpsi_mumu.newTrack(track_mup);
       jpsi_mumu.newTrack(track_mum);
       jpsi_mumu.doTheFit();

       if( (jpsi_mumu.chisqVtx()>0) && (jpsi_mumu.chisqFit()>0) ) {
         FitEvt pipimumu( "Pipimumu", FitEvt::k_P4VecCM );
         pipimumu.newTrack(track_pip);
         pipimumu.newTrack(track_pim);
         pipimumu.newKinDat(jpsi_mumu.fitResult());
         pipimumu.doTheFit();

         if( (pipimumu.chisqVtx()>0) && (pipimumu.chisqFit()>0) ) {

                 HepLorentzVector v1 (jpsi_mumu.kdFitVec()[0]->lorentzMomentum());
                 HepLorentzVector v2 (jpsi_mumu.kdFitVec()[1]->lorentzMomentum());
                 HepLorentzVector v3 (pipimumu.kdFitVec()[0]->lorentzMomentum());
                 HepLorentzVector v4 (pipimumu.kdFitVec()[1]->lorentzMomentum());

                    ChisqV1 = pipimumu.chisqVtx();
                    ChisqF1 = pipimumu.chisqFit();
                    ChisqV2 = jpsi_mumu.chisqVtx();
                    ChisqF2 = jpsi_mumu.chisqFit();

                    for(int j=0; j<4; j++) {
                      if(ID[j]==0 && CHARGE[j]>0) {
                         F1PE[j]=v3.e();
                         F1PX[j]=v3.px();
                         F1PY[j]=v3.py();
                         F1PZ[j]=v3.pz();
                      }
                      else if(ID[j]==0 && CHARGE[j]<0) {
                         F1PE[j]=v4.e();
                         F1PX[j]=v4.px();
                         F1PY[j]=v4.py();
                         F1PZ[j]=v4.pz();
                      }
                      else if(ID[j]==2 && CHARGE[j]>0) {
                         F1PE[j]=v1.e();
                         F1PX[j]=v1.px();
                         F1PY[j]=v1.py();
                         F1PZ[j]=v1.pz();
                      }
                      else if(ID[j]==2 && CHARGE[j]<0) {
                         F1PE[j]=v2.e();
                         F1PX[j]=v2.px();
                         F1PY[j]=v2.py();
                         F1PZ[j]=v2.pz();
                      }

                    }



        }               // if 4C fit converge ends
      }               // if mass fit converge ends
    }                 // if id_sum ends

   }                   // if FAItem.valid ends


   if(ChisqV1 < 1000000 && ChisqF1 < 1000000) {
      PASSED3 = 1;
      PEAK3 = sqrt(pow((F1PE[0]+F1PE[1]+F1PE[2]+F1PE[3]),2)-pow((F1PX[0]+F1PX[1]+F1PX[2]+F1PX[3]),2)
              -pow((F1PY[0]+F1PY[1]+F1PY[2]+F1PY[3]),2)-pow((F1PZ[0]+F1PZ[1]+F1PZ[2]+F1PZ[3]),2));
   }

*/

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// kinematic fitting  ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

   if(PASSED2) {

     FAItem<TDKinematicFit> tr[4];
     KTKinematicData track[4];
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
            track[i].setMomentum(HepVector3D(tr[i]->px()+gamsx,tr[i]->py()+gamsy,tr[i]->pz()+gamsz));
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
      pipitrtr1.newTrack(track[0]);
      pipitrtr1.newTrack(track[1]);
      pipitrtr1.newTrack(track[2]);
      pipitrtr1.newTrack(track[3]);
      pipitrtr1.doTheFit();

      if( (pipitrtr1.chisqVtx()>0) && (pipitrtr1.chisqFit()>0) ) {
        
                 HepLorentzVector v1 (pipitrtr1.kdFitVec()[0]->lorentzMomentum());
                 HepLorentzVector v2 (pipitrtr1.kdFitVec()[1]->lorentzMomentum());
                 HepLorentzVector v3 (pipitrtr1.kdFitVec()[2]->lorentzMomentum());
                 HepLorentzVector v4 (pipitrtr1.kdFitVec()[3]->lorentzMomentum());

                    ChisqV1 = pipitrtr1.chisqVtx();
                    ChisqF1 = pipitrtr1.chisqFit();

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



                      }                 // if fit converge ends
                    }                   // if FAItem.valid ends

      if(ChisqV1 < 1000000 && ChisqF1 < 1000000) {
         PASSED3 = 1;
         PEAK3 = sqrt(pow((F1PE[0]+F1PE[1]+F1PE[2]+F1PE[3]),2)-pow((F1PX[0]+F1PX[1]+F1PX[2]+F1PX[3]),2)
                 -pow((F1PY[0]+F1PY[1]+F1PY[2]+F1PY[3]),2)-pow((F1PZ[0]+F1PZ[1]+F1PZ[2]+F1PZ[3]),2));
      }

   }                                    //  if(PASSED2) ends

   tuple[chisqv1] = ChisqV1;
   tuple[chisqf1] = ChisqF1;
   tuple[chisqv2] = ChisqV2;
   tuple[chisqf2] = ChisqF2;
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
   tuple[peak1] = PEAK1;
   tuple[peak2] = PEAK2;
   tuple[peak3] = PEAK3;
   tuple[mudepth1] = MUDEPTH[0];
   tuple[mudepth2] = MUDEPTH[1];
   tuple[mudepth3] = MUDEPTH[2];
   tuple[mudepth4] = MUDEPTH[3];

   (*m_showerTuple).fill(tuple);
    




   return ActionBase::kPassed;
}


ActionBase::ActionResult
Z3900Proc::beginRun( Frame& iFrame )       // anal2 equiv.
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

   return ActionBase::kPassed;
}


/*
ActionBase::ActionResult
Z3900Proc::endRun( Frame& iFrame )         // anal4 equiv.
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
