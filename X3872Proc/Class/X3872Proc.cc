// -*- C++ -*-
//
// Package:     X3872Proc
// Module:      X3872Proc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      tty7
// Created:     Thu Dec  2 12:26:42 CST 2010
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "X3872Proc/X3872Proc.h"
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
static const char* const kFacilityString = "Processor.X3872Proc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
X3872Proc::X3872Proc( void )               // anal1
   : Processor( "X3872Proc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &X3872Proc::event,    Stream::kEvent );
   bind( &X3872Proc::beginRun, Stream::kBeginRun );
   //bind( &X3872Proc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

X3872Proc::~X3872Proc()                    // anal5
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
X3872Proc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
X3872Proc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------

enum {
chisqv,chisqf,         //chisq of 4C fit
e,th,phi,             // unfitted photon energy
fe,fth,fphi,         // fitted photon energy
eop1,eop2,eop3,eop4,me1,me2,me3,me4,
trte1,trpx1,trpy1,trpz1,trte2,trpx2,trpy2,trpz2, 
trte3,trpx3,trpy3,trpz3,trte4,trpx4,trpy4,trpz4,
ftrte1,ftrpx1,ftrpy1,ftrpz1,ftrte2,ftrpx2,ftrpy2,ftrpz2, 
ftrte3,ftrpx3,ftrpy3,ftrpz3,ftrte4,ftrpx4,ftrpy4,ftrpz4,
id1,id2,id3,id4,charge1,charge2,charge3,charge4,
passed,
kVarNum};

void
X3872Proc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   HINtupleVarNames ntupleNames(kVarNum);

   ntupleNames.addVar(chisqv,       "chisqv");
   ntupleNames.addVar(chisqf,       "chisqf");
   ntupleNames.addVar(e,            "e");
   ntupleNames.addVar(th,           "th");
   ntupleNames.addVar(phi,          "phi");
   ntupleNames.addVar(fe,           "fe");
   ntupleNames.addVar(fth,          "fth");
   ntupleNames.addVar(fphi,         "fphi");
   ntupleNames.addVar(eop1,         "eop1");
   ntupleNames.addVar(eop2,         "eop2");
   ntupleNames.addVar(eop3,         "eop3");
   ntupleNames.addVar(eop4,         "eop4");
   ntupleNames.addVar(me1,          "me1");
   ntupleNames.addVar(me2,          "me2");
   ntupleNames.addVar(me3,          "me3");
   ntupleNames.addVar(me4,          "me4");
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
   ntupleNames.addVar(ftrte1,       "ftrte1");
   ntupleNames.addVar(ftrpx1,       "ftrpx1");
   ntupleNames.addVar(ftrpy1,       "ftrpy1");
   ntupleNames.addVar(ftrpz1,       "ftrpz1");
   ntupleNames.addVar(ftrte2,       "ftrte2");
   ntupleNames.addVar(ftrpx2,       "ftrpx2");
   ntupleNames.addVar(ftrpy2,       "ftrpy2");
   ntupleNames.addVar(ftrpz2,       "ftrpz2");
   ntupleNames.addVar(ftrte3,       "ftrte3");
   ntupleNames.addVar(ftrpx3,       "ftrpx3");
   ntupleNames.addVar(ftrpy3,       "ftrpy3");
   ntupleNames.addVar(ftrpz3,       "ftrpz3");
   ntupleNames.addVar(ftrte4,       "ftrte4");
   ntupleNames.addVar(ftrpx4,       "ftrpx4");
   ntupleNames.addVar(ftrpy4,       "ftrpy4");
   ntupleNames.addVar(ftrpz4,       "ftrpz4");
   ntupleNames.addVar(id1,          "id1");
   ntupleNames.addVar(id2,          "id2");
   ntupleNames.addVar(id3,          "id3");
   ntupleNames.addVar(id4,          "id4");
   ntupleNames.addVar(charge1,      "charge1");
   ntupleNames.addVar(charge2,      "charge2");
   ntupleNames.addVar(charge3,      "charge3");
   ntupleNames.addVar(charge4,      "charge4");
   ntupleNames.addVar(passed,       "passed");


   m_showerTuple = iHistoManager.ntuple(10,"tuple", kVarNum, 10000, ntupleNames.names());

}

// Pion particle ID by dE/dx
DABoolean isPion(const NavTrack& track) {
   const FAItem<DedxInfo>& dedxinfo = track.dedxInfo();
   return (dedxinfo.valid() && (*dedxinfo).valid()
           && fabs((*dedxinfo).piSigma()) < 3.0);
}


// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
X3872Proc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

   const int kMaxTrack = 4;

   double ChisqV = 1000000.;
   double ChisqF = 1000000.;
   double TempChisqV = 1000000.;
   double TempChisqF = 1000000.;

   double E = 0.;
   double Theta = 0.;
   double Phi = 0.;
   double FE = 0.;
   double FTheta = 0.;
   double FPhi = 0.;

   double ME[kMaxTrack] = {0.,0.,0.,0.};
   double EOP[kMaxTrack] = {0.,0.,0.,0};

   double PE[kMaxTrack] = {0.,0.,0.,0.};  
   double PX[kMaxTrack] = {0.,0.,0.,0.};
   double PY[kMaxTrack] = {0.,0.,0.,0.};
   double PZ[kMaxTrack] = {0.,0.,0.,0.};
   double FPE[kMaxTrack] = {0.,0.,0.,0.};
   double FPX[kMaxTrack] = {0.,0.,0.,0.};
   double FPY[kMaxTrack] = {0.,0.,0.,0.};
   double FPZ[kMaxTrack] = {0.,0.,0.,0.};

   double CHARGE[kMaxTrack] = {0.,0.,0.,0.};
   double ID[kMaxTrack] = {0.,0.,0.,0.};  //0:pi, 1:e, 2: mu

   double PASSED = 0;

   float tuple[kVarNum];

   FATable< NavTrack > trackTable;
   extract( iFrame.record( Stream::kEvent ) , trackTable, "GoodThings" );

   FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
   FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();

   if(trackTable.size() != kMaxTrack)
       return ActionBase::kFailed;

   int unmatchedElectrons = 0;

   for ( FATable< NavTrack >::const_iterator electronItr = trackTableBegin;
         electronItr != trackTableEnd ;
         ++electronItr )
   {
      int i = unmatchedElectrons++;
      if((electronItr->elecId().eOverP()>0.8) && (electronItr->elecId().eOverP()<1.2)) {

         if(electronItr->trackShowerMatch().valid())
            ME[i] = electronItr->trackShowerMatch()->matchedEnergy();

         EOP[i] = electronItr->elecId().eOverP();

         FAItem<TDKinematicFit> eFit1 = (*electronItr).electronFit();
         int unmatchedElectrons2 = 1;
         if(eFit1.valid()){
           for ( FATable< NavTrack >::const_iterator electronItr2 = electronItr+1;
                 electronItr2 != trackTableEnd ;
                 ++electronItr2 )
           {
              int j = unmatchedElectrons2++;
              if((electronItr2->elecId().eOverP()>0.8) && (electronItr2->elecId().eOverP()<1.2)) {

                if(electronItr2->trackShowerMatch().valid())
                   ME[i+j] = electronItr2->trackShowerMatch()->matchedEnergy();

                EOP[i+j] = electronItr2->elecId().eOverP();

                FAItem<TDKinematicFit> eFit2 = (*electronItr2).electronFit();
                if(eFit2.valid()){

                  double m_jpi = sqrt(pow((eFit1->lorentzMomentum().e()+eFit2->lorentzMomentum().e()),2)-pow((eFit1->px()+eFit2->px()),2)
                                     -pow((eFit1->py()+eFit2->py()),2)-pow((eFit1->pz()+eFit2->pz()),2));

                  if((fabs(m_jpi-3.097)<0.1) && ((eFit1->charge()+eFit2->charge())==0)) {
                    PE[i]=eFit1->lorentzMomentum().e();
                    PX[i]=eFit1->px();
                    PY[i]=eFit1->py();
                    PZ[i]=eFit1->pz();
                    CHARGE[i]=eFit1->charge();
                    ID[i]=1;
                    PE[i+j]=eFit2->lorentzMomentum().e();
                    PX[i+j]=eFit2->px();
                    PY[i+j]=eFit2->py();
                    PZ[i+j]=eFit2->pz();
                    CHARGE[i+j]=eFit2->charge();
                    ID[i+j]=1;
                  }
                }
              }
           }
         }
      }
   }


   int unmatchedMuons = 0;

   for ( FATable< NavTrack >::const_iterator muonItr = trackTableBegin;
         muonItr != trackTableEnd ;
         ++muonItr )
   {
      int i = unmatchedMuons++;
      if(muonItr->elecId().eOverP()<=0.8) {

         if(muonItr->trackShowerMatch().valid())
            ME[i] = muonItr->trackShowerMatch()->matchedEnergy();

         EOP[i] = muonItr->elecId().eOverP();

         FAItem<TDKinematicFit> muFit1 = (*muonItr).muonFit();
         int unmatchedMuons2 = 1;
         if(muFit1.valid()){
           for ( FATable< NavTrack >::const_iterator muonItr2 = muonItr+1;
                 muonItr2 != trackTableEnd ;
                 ++muonItr2 )
           {
              int j = unmatchedMuons2++;
              if(muonItr2->elecId().eOverP()<=0.8) {

                if(muonItr2->trackShowerMatch().valid())
                   ME[i+j] = muonItr2->trackShowerMatch()->matchedEnergy();

                EOP[i+j] = muonItr2->elecId().eOverP();

                FAItem<TDKinematicFit> muFit2 = (*muonItr2).muonFit();
                if(muFit2.valid()){
                  double m_jpi = sqrt(pow((muFit1->lorentzMomentum().e()+muFit2->lorentzMomentum().e()),2)-pow((muFit1->px()+muFit2->px()),2)
                                     -pow((muFit1->py()+muFit2->py()),2)-pow((muFit1->pz()+muFit2->pz()),2));

                  if((fabs(m_jpi-3.097)<0.1) && ((muFit1->charge()+muFit2->charge())==0)) {
                    PE[i]=muFit1->lorentzMomentum().e();
                    PX[i]=muFit1->px();
                    PY[i]=muFit1->py();
                    PZ[i]=muFit1->pz();
                    CHARGE[i]=muFit1->charge();
                    ID[i]=2;
                    PE[i+j]=muFit2->lorentzMomentum().e();
                    PX[i+j]=muFit2->px();
                    PY[i+j]=muFit2->py();
                    PZ[i+j]=muFit2->pz();
                    CHARGE[i+j]=muFit2->charge();
                    ID[i+j]=2;
                  }
                }
              }
           }
         }
      }
   }




   double sum_id = ID[0]+ID[1]+ID[2]+ID[3];

   if(sum_id == 0)
       return ActionBase::kFailed;

   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ) , showerTable, "GoodThings" );

   if(showerTable.size()==0)
      return ActionBase::kFailed;

   FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
   FATable< NavShower >::const_iterator showerEnd = showerTable.end();

   for ( FATable< NavShower >::const_iterator showerItr = showerBegin;
         showerItr != showerEnd ;
         ++showerItr )
   {
      if(showerItr->attributes().x925() < 1)  continue;

      int unmatchedTracks = 0;
      if(sum_id == 2) {
         for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
               trackItr != trackTableEnd ;
               ++trackItr )
         {
            int i = unmatchedTracks++;
            int unmatchedTracks2 = 1;
            if(isPion(*trackItr) && ID[i] == 0) {

              if(trackItr->trackShowerMatch().valid())
                 ME[i] = trackItr->trackShowerMatch()->matchedEnergy();

              EOP[i] = trackItr->elecId().eOverP();

              FAItem<TDKinematicFit> pi1 = (*trackItr).pionFit();
              for ( FATable< NavTrack >::const_iterator trackItr2 = trackItr+1;
                    trackItr2 != trackTableEnd ;
                    ++trackItr2 )
              {
                 int j = unmatchedTracks2++;
                 if(isPion(*trackItr2) && ID[i+j] == 0) {

                   if(trackItr2->trackShowerMatch().valid())
                      ME[i+j] = trackItr2->trackShowerMatch()->matchedEnergy();

                   EOP[i+j] = trackItr2->elecId().eOverP();

                   FAItem<TDKinematicFit> pi2 = (*trackItr2).pionFit();
                   if((pi1->charge()+pi2->charge())!=0)
                      return ActionBase::kFailed;
                   int unmatchedTracks3 = 0;
                   for ( FATable< NavTrack >::const_iterator trackItr3 = trackTableBegin;
                         trackItr3 != trackTableEnd ;
                         ++trackItr3 )
                   {
                      int k = unmatchedTracks3++;
                      if(ID[k] == 1) {
                         FAItem<TDKinematicFit> e1 = (*trackItr3).electronFit();
                         int unmatchedTracks4 = 1;
                         for ( FATable< NavTrack >::const_iterator trackItr4 = trackItr3+1;
                               trackItr4 != trackTableEnd ;
                               ++trackItr4 )
                         { 
                            int l = unmatchedTracks4++;
                            if(ID[k+l] == 1) { 
                               FAItem<TDKinematicFit> e2 = (*trackItr4).electronFit();

                               // do the fit

                               FitEvt pipiee( "Pipiee", FitEvt::k_P4VecCM );
                               pipiee.newPhoton(*showerItr);
                               pipiee.newTrack(*pi1);
                               pipiee.newTrack(*pi2);
                               pipiee.newTrack(*e1);
                               pipiee.newTrack(*e2);
                               pipiee.doTheFit();

                               if( (pipiee.chisqVtx()>0) && (pipiee.chisqFit()>0) ) {

                                 HepLorentzVector vg (pipiee.kdFitVec()[0]->lorentzMomentum());
                                 HepLorentzVector v1pi (pipiee.kdFitVec()[1]->lorentzMomentum());
                                 HepLorentzVector v2pi (pipiee.kdFitVec()[2]->lorentzMomentum());
                                 HepLorentzVector v1e (pipiee.kdFitVec()[3]->lorentzMomentum());
                                 HepLorentzVector v2e (pipiee.kdFitVec()[4]->lorentzMomentum());

                                 PASSED = 1;

                                 TempChisqV = pipiee.chisqVtx();
                                 TempChisqF = pipiee.chisqFit();

                                 if(TempChisqF < ChisqF){

                                   ChisqV = pipiee.chisqVtx();
                                   ChisqF = pipiee.chisqFit();

                                   E = showerItr->attributes().energy();
                                   Theta = showerItr->attributes().theta();
                                   Phi = showerItr->attributes().phi();

                                   FE = vg.e();
                                   FTheta = vg.theta();
                                   FPhi = vg.phi();

                                   PE[i]=pi1->lorentzMomentum().e();
                                   PX[i]=pi1->px();
                                   PY[i]=pi1->py();
                                   PZ[i]=pi1->pz();
                                   CHARGE[i]=pi1->charge();
                                   PE[i+j]=pi2->lorentzMomentum().e();
                                   PX[i+j]=pi2->px();
                                   PY[i+j]=pi2->py();
                                   PZ[i+j]=pi2->pz();
                                   CHARGE[i+j]=pi2->charge();


                                   FPE[i]=v1pi.e();
                                   FPX[i]=v1pi.px();
                                   FPY[i]=v1pi.py();
                                   FPZ[i]=v1pi.pz();

                                   FPE[i+j]=v2pi.e();
                                   FPX[i+j]=v2pi.px();
                                   FPY[i+j]=v2pi.py();
                                   FPZ[i+j]=v2pi.pz();

                                   FPE[k]=v1e.e();
                                   FPX[k]=v1e.px();
                                   FPY[k]=v1e.py();
                                   FPZ[k]=v1e.pz();

                                   FPE[k+l]=v2e.e();
                                   FPX[k+l]=v2e.px();
                                   FPY[k+l]=v2e.py();
                                   FPZ[k+l]=v2e.pz();

                                }
                              }
                            }
                         }
                      }
                   }
                 }
              }
            }
         }
      }

      else if(sum_id == 4) {
         for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
               trackItr != trackTableEnd ;
               ++trackItr )
         {
            int i = unmatchedTracks++;
            int unmatchedTracks2 = 1;
            if(isPion(*trackItr) && ID[i] == 0) {
              FAItem<TDKinematicFit> pi1 = (*trackItr).pionFit();
              for ( FATable< NavTrack >::const_iterator trackItr2 = trackItr+1;
                    trackItr2 != trackTableEnd ;
                    ++trackItr2 )
              {
                 int j = unmatchedTracks2++;
                 if(isPion(*trackItr2) && ID[i+j] == 0) {
                   FAItem<TDKinematicFit> pi2 = (*trackItr2).pionFit();
                   if((pi1->charge()+pi2->charge())!=0)
                      return ActionBase::kFailed;
                   int unmatchedTracks3 = 0;
                   for ( FATable< NavTrack >::const_iterator trackItr3 = trackTableBegin;
                         trackItr3 != trackTableEnd ;
                         ++trackItr3 )
                   {
                      int k = unmatchedTracks3++;
                      if(ID[k] == 2) {
                         FAItem<TDKinematicFit> mu1 = (*trackItr3).muonFit();
                         int unmatchedTracks4 = 1;
                         for ( FATable< NavTrack >::const_iterator trackItr4 = trackItr3+1;
                               trackItr4 != trackTableEnd ;
                               ++trackItr4 )
                         {
                            int l = unmatchedTracks4++;
                            if(ID[k+l] == 2) {
                               FAItem<TDKinematicFit> mu2 = (*trackItr4).muonFit();

                               // do the fit

                               FitEvt pipimumu( "Pipimumu", FitEvt::k_P4VecCM );
                               pipimumu.newPhoton(*showerItr);
                               pipimumu.newTrack(*pi1);
                               pipimumu.newTrack(*pi2);
                               pipimumu.newTrack(*mu1);
                               pipimumu.newTrack(*mu2);
                               pipimumu.doTheFit();

                               if( (pipimumu.chisqVtx()>0) && (pipimumu.chisqFit()>0) ) {

                                 HepLorentzVector vg (pipimumu.kdFitVec()[0]->lorentzMomentum());
                                 HepLorentzVector v1pi (pipimumu.kdFitVec()[1]->lorentzMomentum());
                                 HepLorentzVector v2pi (pipimumu.kdFitVec()[2]->lorentzMomentum());
                                 HepLorentzVector v1mu (pipimumu.kdFitVec()[3]->lorentzMomentum());
                                 HepLorentzVector v2mu (pipimumu.kdFitVec()[4]->lorentzMomentum());

                                 PASSED = 1;

                                 TempChisqV = pipimumu.chisqVtx();
                                 TempChisqF = pipimumu.chisqFit();

                                 if(TempChisqF < ChisqF){

                                   ChisqV = pipimumu.chisqVtx();
                                   ChisqF = pipimumu.chisqFit();

                                   E = showerItr->attributes().energy();
                                   Theta = showerItr->attributes().theta();
                                   Phi = showerItr->attributes().phi();

                                   FE = vg.e();
                                   FTheta = vg.theta();
                                   FPhi = vg.phi();

                                   PE[i]=pi1->lorentzMomentum().e();
                                   PX[i]=pi1->px();
                                   PY[i]=pi1->py();
                                   PZ[i]=pi1->pz();
                                   CHARGE[i]=pi1->charge();
                                   PE[i+j]=pi2->lorentzMomentum().e();
                                   PX[i+j]=pi2->px();
                                   PY[i+j]=pi2->py();
                                   PZ[i+j]=pi2->pz();
                                   CHARGE[i+j]=pi2->charge();

                                   FPE[i]=v1pi.e();
                                   FPX[i]=v1pi.px();
                                   FPY[i]=v1pi.py();
                                   FPZ[i]=v1pi.pz();

                                   FPE[i+j]=v2pi.e();
                                   FPX[i+j]=v2pi.px();
                                   FPY[i+j]=v2pi.py();
                                   FPZ[i+j]=v2pi.pz();

                                   FPE[k]=v1mu.e();
                                   FPX[k]=v1mu.px();
                                   FPY[k]=v1mu.py();
                                   FPZ[k]=v1mu.pz();

                                   FPE[k+l]=v2mu.e();
                                   FPX[k+l]=v2mu.px();
                                   FPY[k+l]=v2mu.py();
                                   FPZ[k+l]=v2mu.pz();
                                }
                              }
                            }
                         }
                      }
                   }
                 }
              }
            }
         }
      }

   }


   tuple[chisqv] = ChisqV;
   tuple[chisqf] = ChisqF;
   tuple[e] = E;
   tuple[th] = Theta;
   tuple[phi] = Phi;
   tuple[fe] = FE;
   tuple[fth] = FTheta;
   tuple[fphi] = FPhi;
   tuple[eop1] = EOP[0];
   tuple[eop2] = EOP[1];
   tuple[eop3] = EOP[2];
   tuple[eop4] = EOP[3];
   tuple[me1] = ME[0];
   tuple[me2] = ME[1];
   tuple[me3] = ME[2];
   tuple[me4] = ME[3];
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
   tuple[ftrte1] = FPE[0];
   tuple[ftrpx1] = FPX[0];
   tuple[ftrpy1] = FPY[0];
   tuple[ftrpz1] = FPZ[0];
   tuple[ftrte2] = FPE[1];
   tuple[ftrpx2] = FPX[1];
   tuple[ftrpy2] = FPY[1];
   tuple[ftrpz2] = FPZ[1];
   tuple[ftrte3] = FPE[2];
   tuple[ftrpx3] = FPX[2];
   tuple[ftrpy3] = FPY[2];
   tuple[ftrpz3] = FPZ[2];
   tuple[ftrte4] = FPE[3];
   tuple[ftrpx4] = FPX[3];
   tuple[ftrpy4] = FPY[3];
   tuple[ftrpz4] = FPZ[3];
   tuple[id1] = ID[0];
   tuple[id2] = ID[1];
   tuple[id3] = ID[2];
   tuple[id4] = ID[3];
   tuple[charge1] = CHARGE[0];
   tuple[charge2] = CHARGE[1];
   tuple[charge3] = CHARGE[2];
   tuple[charge4] = CHARGE[3];
   tuple[passed] = PASSED;

   (*m_showerTuple).fill(tuple);


   return ActionBase::kPassed;
}


ActionBase::ActionResult
X3872Proc::beginRun( Frame& iFrame )       // anal2 equiv.
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
X3872Proc::endRun( Frame& iFrame )         // anal4 equiv.
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
