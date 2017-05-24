// -*- C++ -*-
//
// Package:     EtaPi0JpsiProc
// Module:      EtaPi0JpsiProc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      
// Created:     Fri Apr  5 11:30:52 CDT 2013
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "EtaPi0JpsiProc/EtaPi0JpsiProc.h"
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
static const char* const kFacilityString = "Processor.EtaPi0JpsiProc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
EtaPi0JpsiProc::EtaPi0JpsiProc( void )               // anal1
   : Processor( "EtaPi0JpsiProc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &EtaPi0JpsiProc::event,    Stream::kEvent );
   bind( &EtaPi0JpsiProc::beginRun, Stream::kBeginRun );
   //bind( &EtaPi0JpsiProc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

EtaPi0JpsiProc::~EtaPi0JpsiProc()                    // anal5
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
EtaPi0JpsiProc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
EtaPi0JpsiProc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------
enum {
chisqv1,chisqf1,         //chisq of 4C fit, normal 4C fit

eop1,eop2,me1,me2,dedx1,dedx2, // 2 leptons
trte1,trpx1,trpy1,trpz1,trte2,trpx2,trpy2,trpz2,
f1trte1,f1trpx1,f1trpy1,f1trpz1,f1trte2,f1trpx2,f1trpy2,f1trpz2,
id1,id2,charge1,charge2,

f1pi0te,f1pi0px,f1pi0py,f1pi0pz,                   // fitted pi0 energy and momenta 
pi0hie,pi0loe,                                 // and its photon energies
f1etate,f1etapx,f1etapy,f1etapz,                   // fitted eta energy and momenta 
etahie,etaloe,                                 // and its photon energies

passed2,passed3,
peak2,peak3,
kVarNum};


void
EtaPi0JpsiProc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here
   HINtupleVarNames ntupleNames(kVarNum);

   ntupleNames.addVar(chisqv1,       "chisqv1");
   ntupleNames.addVar(chisqf1,       "chisqf1");
   ntupleNames.addVar(eop1,         "eop1");
   ntupleNames.addVar(eop2,         "eop2");
   ntupleNames.addVar(me1,          "me1");
   ntupleNames.addVar(me2,          "me2");
   ntupleNames.addVar(dedx1,        "dedx1");
   ntupleNames.addVar(dedx2,        "dedx2");
   ntupleNames.addVar(trte1,        "trte1");
   ntupleNames.addVar(trpx1,        "trpx1");
   ntupleNames.addVar(trpy1,        "trpy1");
   ntupleNames.addVar(trpz1,        "trpz1");
   ntupleNames.addVar(trte2,        "trte2");
   ntupleNames.addVar(trpx2,        "trpx2");
   ntupleNames.addVar(trpy2,        "trpy2");
   ntupleNames.addVar(trpz2,        "trpz2");
   ntupleNames.addVar(f1trte1,       "f1trte1");
   ntupleNames.addVar(f1trpx1,       "f1trpx1");
   ntupleNames.addVar(f1trpy1,       "f1trpy1");
   ntupleNames.addVar(f1trpz1,       "f1trpz1");
   ntupleNames.addVar(f1trte2,       "f1trte2");
   ntupleNames.addVar(f1trpx2,       "f1trpx2");
   ntupleNames.addVar(f1trpy2,       "f1trpy2");
   ntupleNames.addVar(f1trpz2,       "f1trpz2");
   ntupleNames.addVar(id1,          "id1");
   ntupleNames.addVar(id2,          "id2");
   ntupleNames.addVar(charge1,      "charge1");
   ntupleNames.addVar(charge2,      "charge2");
   ntupleNames.addVar(f1pi0te,    "f1pi0te");
   ntupleNames.addVar(f1pi0px,    "f1pi0px");
   ntupleNames.addVar(f1pi0py,    "f1pi0py");
   ntupleNames.addVar(f1pi0pz,    "f1pi0pz");
   ntupleNames.addVar(pi0hie,    "pi0hie");
   ntupleNames.addVar(pi0loe,    "pi0loe");
   ntupleNames.addVar(f1etate,    "f1etate");
   ntupleNames.addVar(f1etapx,    "f1etapx");
   ntupleNames.addVar(f1etapy,    "f1etapy");
   ntupleNames.addVar(f1etapz,    "f1etapz");
   ntupleNames.addVar(etahie,    "etahie");
   ntupleNames.addVar(etaloe,    "etaloe");
   ntupleNames.addVar(passed2,      "passed2");
   ntupleNames.addVar(passed3,      "passed3");
   ntupleNames.addVar(peak2,        "peak2");
   ntupleNames.addVar(peak3,        "peak3");

   m_showerTuple = iHistoManager.ntuple(10,"tuple", kVarNum, 10000, ntupleNames.names());


}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
EtaPi0JpsiProc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   const int kMaxTrack = 2;

   double ChisqV1 = 1000000.;
   double ChisqF1 = 1000000.;
   double ME[kMaxTrack] = {10000.,10000.};
   double EOP[kMaxTrack] = {10000.,10000.};
   double DEDX[kMaxTrack] = {10000.,10000.};
   double PE[kMaxTrack] = {0.,0.};
   double PX[kMaxTrack] = {0.,0.};
   double PY[kMaxTrack] = {0.,0.};
   double PZ[kMaxTrack] = {0.,0.};
   double F1PE[kMaxTrack] = {0.,0.};
   double F1PX[kMaxTrack] = {0.,0.};
   double F1PY[kMaxTrack] = {0.,0.};
   double F1PZ[kMaxTrack] = {0.,0.};
   double CHARGE[kMaxTrack] = {100.,100.};
   double ID[kMaxTrack] = {0.,0.};  //1:e, 2: mu
   double F1PI0PE = 0.;
   double F1PI0PX = 0.;
   double F1PI0PY = 0.;
   double F1PI0PZ = 0.;
   double PI0HIE = 0.;
   double PI0LOE = 0.;
   double F1ETAPE = 0.;
   double F1ETAPX = 0.;
   double F1ETAPY = 0.;
   double F1ETAPZ = 0.;
   double ETAHIE = 0.;
   double ETALOE = 0.;
   double PASSED2 = 0;
   double PASSED3 = 0;
   double PEAK2 = 0;
   double PEAK3 = 0;


   float tuple[kVarNum];

//////////////////////////////////// # of tracks == 2 /////////////////////////////////


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
      CHARGE[i]=(*trackItr).muonFit()->charge();
      charge_sum += CHARGE[i];
   }

   if(charge_sum != 0)
       return ActionBase::kFailed;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////// lepton energy cut |e| > 1 GeV //////////////////////////////////////
/////////////////// ee: 0.8<E/p<1.2, mumu: E/p<0.8 ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

   unmatchedtracks = 0;
   int id_sum = 0;

   for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
         trackItr != trackTableEnd ;
         ++trackItr )
   {
      int i = unmatchedtracks++;
      PE[i]=(*trackItr).muonFit()->lorentzMomentum().e();

      if(trackItr->trackShowerMatch().valid())
         ME[i] = trackItr->trackShowerMatch()->matchedEnergy();

      EOP[i] = trackItr->elecId().eOverP();
      FAItem<DedxInfo> the_dedx = (*trackItr).dedxInfo();

      if(PE[i] > 1.0){

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
     PEAK2 = sqrt(pow((PE[0]+PE[1]),2)-pow((PX[0]+PX[1]),2)
                  -pow((PY[0]+PY[1]),2)-pow((PZ[0]+PZ[1]),2));
   }

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// kinematic fitting  ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

   if(PASSED2) {

     FAItem<TDKinematicFit> tr[2];
     KTKinematicData track[2];
     unmatchedtracks = 0;

     for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
           trackItr != trackTableEnd ;
           ++trackItr )
       {
          int i = unmatchedtracks++;
          if(ID[i] == 1) {
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

     if(tr[0].valid() && tr[1].valid()) {

       FATable<NavPi0ToGG> pi0Table;
       extract( iFrame.record( Stream::kEvent ) , pi0Table );
 
       FATable< NavPi0ToGG >::const_iterator pi0Begin = pi0Table.begin();
       FATable< NavPi0ToGG >::const_iterator pi0End = pi0Table.end();

       FATable<NavEtaToGG> etaTable;
       extract( iFrame.record( Stream::kEvent ) , etaTable );
  
       FATable< NavEtaToGG >::const_iterator etaBegin = etaTable.begin();
       FATable< NavEtaToGG >::const_iterator etaEnd = etaTable.end();


       for (FATable< NavPi0ToGG >::const_iterator pi0Itr = pi0Begin;
            pi0Itr != pi0End ; ++pi0Itr) {

         if(pi0Itr.valid()
            && pi0Itr->pi0().fit()
            && pi0Itr->pi0().converged()
            && (pi0Itr->pi0().chisq() < 500)
            && (fabs(pi0Itr->pi0().pullMass()) < 3) ) {

            for (FATable< NavEtaToGG >::const_iterator etaItr = etaBegin; 
                 etaItr != etaEnd ; ++etaItr) {

              if(etaItr.valid() 
                 && etaItr->eta().fit()
                 && etaItr->eta().converged()
                 && (etaItr->eta().chisq() < 500)
                 && (fabs(etaItr->eta().pullMass()) < 3) 
                 && (etaItr->hiEnShower().identifier() != pi0Itr->hiEnShower().identifier())
                 && (etaItr->hiEnShower().identifier() != pi0Itr->loEnShower().identifier())
                 && (etaItr->loEnShower().identifier() != pi0Itr->hiEnShower().identifier()) 
                 && (etaItr->loEnShower().identifier() != pi0Itr->loEnShower().identifier()) ) {

                 FitEvt pipi( "Pipi", FitEvt::k_P4VecCM );
                 pipi.newPi0(pi0Itr->hiEnShower(),pi0Itr->loEnShower(), FitEvtSettings::instance().beamSpotKD());
                 pipi.newPi0(etaItr->hiEnShower(),etaItr->loEnShower(), FitEvtSettings::instance().beamSpotKD());
                 pipi.newTrack(track[0]);
                 pipi.newTrack(track[1]);
                 pipi.doTheFit();

                 if( (pipi.chisqVtx()>0) && (pipi.chisqFit()>0) ) {
 
                   const HepLorentzVector vpi0 (pipi.kdFitVec()[0]->lorentzMomentum());
                   const HepLorentzVector veta (pipi.kdFitVec()[1]->lorentzMomentum());
                   const HepLorentzVector v1pi (pipi.kdFitVec()[2]->lorentzMomentum());
                   const HepLorentzVector v2pi (pipi.kdFitVec()[3]->lorentzMomentum());

                   double TempChisqF = pipi.chisqFit();
                   if(TempChisqF < ChisqF1){
                     ChisqV1 = pipi.chisqVtx();
                     ChisqF1 = pipi.chisqFit();

                     F1PI0PE=vpi0.e();
                     F1PI0PX=vpi0.px();
                     F1PI0PY=vpi0.py();
                     F1PI0PZ=vpi0.pz();
                     F1ETAPE=veta.e();
                     F1ETAPX=veta.px();
                     F1ETAPY=veta.py();
                     F1ETAPZ=veta.pz();
                     F1PE[0]=v1pi.e();
                     F1PX[0]=v1pi.px();
                     F1PY[0]=v1pi.py();
                     F1PZ[0]=v1pi.pz();
                     F1PE[1]=v2pi.e();
                     F1PX[1]=v2pi.px();
                     F1PY[1]=v2pi.py();
                     F1PZ[1]=v2pi.pz();
                     PI0HIE = pi0Itr->hiEnShower().attributes().energy(); // before fitting value
                     PI0LOE = pi0Itr->loEnShower().attributes().energy(); // before fitting value
                     ETAHIE = etaItr->hiEnShower().attributes().energy(); // before fitting value
                     ETALOE = etaItr->loEnShower().attributes().energy(); // before fitting value
                   }
                 }
              }
            }
         }
       }
     }
     if(ChisqV1 < 100000 && ChisqF1 < 100000) {
         PASSED3 = 1;
         PEAK3 = sqrt(pow((F1PE[0]+F1PE[1]+F1PI0PE+F1ETAPE),2)-pow((F1PX[0]+F1PX[1]+F1PI0PX+F1ETAPX),2)
                 -pow((F1PY[0]+F1PY[1]+F1PI0PY+F1ETAPY),2)-pow((F1PZ[0]+F1PZ[1]+F1PI0PZ+F1ETAPZ),2));
     }
   }

   tuple[chisqv1] = ChisqV1;
   tuple[chisqf1] = ChisqF1;
   tuple[eop1] = EOP[0];
   tuple[eop2] = EOP[1];
   tuple[me1] = ME[0];
   tuple[me2] = ME[1];
   tuple[dedx1] = DEDX[0];
   tuple[dedx2] = DEDX[1];
   tuple[trte1] = PE[0];
   tuple[trpx1] = PX[0];
   tuple[trpy1] = PY[0];
   tuple[trpz1] = PZ[0];
   tuple[trte2] = PE[1];
   tuple[trpx2] = PX[1];
   tuple[trpy2] = PY[1];
   tuple[trpz2] = PZ[1];
   tuple[f1trte1] = F1PE[0];
   tuple[f1trpx1] = F1PX[0];
   tuple[f1trpy1] = F1PY[0];
   tuple[f1trpz1] = F1PZ[0];
   tuple[f1trte2] = F1PE[1];
   tuple[f1trpx2] = F1PX[1];
   tuple[f1trpy2] = F1PY[1];
   tuple[f1trpz2] = F1PZ[1];
   tuple[f1pi0te] = F1PI0PE;
   tuple[f1pi0px] = F1PI0PX;
   tuple[f1pi0py] = F1PI0PY;
   tuple[f1pi0pz] = F1PI0PZ;
   tuple[f1etate] = F1ETAPE;
   tuple[f1etapx] = F1ETAPX;
   tuple[f1etapy] = F1ETAPY;
   tuple[f1etapz] = F1ETAPZ;
   tuple[pi0hie] = PI0HIE;
   tuple[etahie] = ETAHIE;
   tuple[pi0loe] = PI0LOE;
   tuple[etaloe] = ETALOE;
   tuple[id1] = ID[0];
   tuple[id2] = ID[1];
   tuple[charge1] = CHARGE[0];
   tuple[charge2] = CHARGE[1];
   tuple[passed2] = PASSED2;
   tuple[passed3] = PASSED3;
   tuple[peak2] = PEAK2;
   tuple[peak3] = PEAK3;

   (*m_showerTuple).fill(tuple);

   return ActionBase::kPassed;
}


ActionBase::ActionResult
EtaPi0JpsiProc::beginRun( Frame& iFrame )       // anal2 equiv.
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

   return ActionBase::kPassed;
}


/*
ActionBase::ActionResult
EtaPi0JpsiProc::endRun( Frame& iFrame )         // anal4 equiv.
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
