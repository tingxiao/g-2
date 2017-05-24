// -*- C++ -*-
//
// Package:     InclusiveXXX3872Proc
// Module:      InclusiveXXX3872Proc
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      pts/16
// Created:     Mon Apr 16 20:14:38 CDT 2012
// $Id$
//
// Revision history
//
// $Log$
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "InclusiveXXX3872Proc/InclusiveXXX3872Proc.h"
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
static const char* const kFacilityString = "Processor.InclusiveXXX3872Proc" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.41 2006/02/08 19:38:02 wsun Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// static data member definitions
//



//
// constructors and destructor
//
InclusiveXXX3872Proc::InclusiveXXX3872Proc( void )               // anal1
   : Processor( "InclusiveXXX3872Proc" )
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &InclusiveXXX3872Proc::event,    Stream::kEvent );
   //bind( &InclusiveXXX3872Proc::beginRun, Stream::kBeginRun );
   //bind( &InclusiveXXX3872Proc::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)


}

InclusiveXXX3872Proc::~InclusiveXXX3872Proc()                    // anal5
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
InclusiveXXX3872Proc::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
InclusiveXXX3872Proc::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}


// ---------------- standard place to book histograms ---------------

enum {
e1,th1,phi1,e9251,      
e2,th2,phi2,e9252,
e3,th3,phi3,e9253,
e4,th4,phi4,e9254,
e5,th5,phi5,e9255,
e6,th6,phi6,e9256,
e7,th7,phi7,e9257,
e8,th8,phi8,e9258,
e9,th9,phi9,e9259,
e10,th10,phi10,e92510,
e11,th11,phi11,e92511,
e12,th12,phi12,e92512,
e13,th13,phi13,e92513,
e14,th14,phi14,e92514,
e15,th15,phi15,e92515,
e16,th16,phi16,e92516,

eop1,eop2,eop3,eop4,me1,me2,me3,me4,dedx1,dedx2,dedx3,dedx4,
trte1,trpx1,trpy1,trpz1,trte2,trpx2,trpy2,trpz2,
trte3,trpx3,trpy3,trpz3,trte4,trpx4,trpy4,trpz4,
id1,id2,id3,id4,charge1,charge2,charge3,charge4,
passed,peak,
kVarNum};


void
InclusiveXXX3872Proc::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

   HINtupleVarNames ntupleNames(kVarNum);

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

   ntupleNames.addVar(e11,          "e11");
   ntupleNames.addVar(th11,        "th11");
   ntupleNames.addVar(phi11,       "phi11");
   ntupleNames.addVar(e92511,    "e92511");

   ntupleNames.addVar(e12,          "e12");
   ntupleNames.addVar(th12,        "th12");
   ntupleNames.addVar(phi12,       "phi12");
   ntupleNames.addVar(e92512,    "e92512");

   ntupleNames.addVar(e13,          "e13");
   ntupleNames.addVar(th13,        "th13");
   ntupleNames.addVar(phi13,       "phi13");
   ntupleNames.addVar(e92513,    "e92513");

   ntupleNames.addVar(e14,          "e14");
   ntupleNames.addVar(th14,        "th14");
   ntupleNames.addVar(phi14,       "phi14");
   ntupleNames.addVar(e92514,    "e92514");

   ntupleNames.addVar(e15,          "e15");
   ntupleNames.addVar(th15,        "th15");
   ntupleNames.addVar(phi15,       "phi15");
   ntupleNames.addVar(e92515,    "e92515");

   ntupleNames.addVar(e16,          "e16");
   ntupleNames.addVar(th16,        "th16");
   ntupleNames.addVar(phi16,       "phi16");
   ntupleNames.addVar(e92516,    "e92516");

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

   ntupleNames.addVar(id1,          "id1");
   ntupleNames.addVar(id2,          "id2");
   ntupleNames.addVar(id3,          "id3");
   ntupleNames.addVar(id4,          "id4");
   ntupleNames.addVar(charge1,      "charge1");
   ntupleNames.addVar(charge2,      "charge2");
   ntupleNames.addVar(charge3,      "charge3");
   ntupleNames.addVar(charge4,      "charge4");

   ntupleNames.addVar(passed,      "passed");
   ntupleNames.addVar(peak,        "peak");

   m_showerTuple = iHistoManager.ntuple(10,"tuple", kVarNum, 10000, ntupleNames.names());



}



// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
InclusiveXXX3872Proc::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;
   const int kMaxTrack = 4;
   const int kMaxShower = 16;

   double E[kMaxShower] = {-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.,-100.};
   double Theta[kMaxShower] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
   double Phi[kMaxShower] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
   double E925[kMaxShower] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
   
   double ME[kMaxTrack] = {0.,0.,0.,0.};
   double EOP[kMaxTrack] = {0.,0.,0.,0};
   double DEDX[kMaxTrack] = {10000.,10000.,10000.,10000.};

   double PE[kMaxTrack] = {0.,0.,0.,0.};
   double PX[kMaxTrack] = {0.,0.,0.,0.};
   double PY[kMaxTrack] = {0.,0.,0.,0.};
   double PZ[kMaxTrack] = {0.,0.,0.,0.};

   int CHARGE[kMaxTrack] = {100,100,100,100};
   int ID[kMaxTrack] = {-100,-100,-100,-100};  //0:pi, 1:e, 2: mu

   double PASSED = 0;
   double PEAK = 0;

   float tuple[kVarNum];


/////////////////////////////////////////// showers //////////////////////////////////////////////////////

   FATable< NavShower > showerTable;
   extract( iFrame.record( Stream::kEvent ) , showerTable, "GoodThings" );

   FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
   FATable< NavShower >::const_iterator showerEnd = showerTable.end();

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
      }
   }





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
     PASSED = 1;
     PEAK = sqrt(pow((PE[0]+PE[1]+PE[2]+PE[3]),2)-pow((PX[0]+PX[1]+PX[2]+PX[3]),2)-pow((PY[0]+PY[1]+PY[2]+PY[3]),2)-pow((PZ[0]+PZ[1]+PZ[2]+PZ[3]),2));
   }

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

   tuple[e11] = E[10];
   tuple[th11] = Theta[10];
   tuple[phi11] = Phi[10];
   tuple[e92511] = E925[10];

   tuple[e12] = E[11];
   tuple[th12] = Theta[11];
   tuple[phi12] = Phi[11];
   tuple[e92512] = E925[11];

   tuple[e13] = E[12];
   tuple[th13] = Theta[12];
   tuple[phi13] = Phi[12];
   tuple[e92513] = E925[12];

   tuple[e14] = E[13];
   tuple[th14] = Theta[13];
   tuple[phi14] = Phi[13];
   tuple[e92514] = E925[13];

   tuple[e15] = E[14];
   tuple[th15] = Theta[14];
   tuple[phi15] = Phi[14];
   tuple[e92515] = E925[14];

   tuple[e16] = E[15];
   tuple[th16] = Theta[15];
   tuple[phi16] = Phi[15];
   tuple[e92516] = E925[15];



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

   tuple[id1] = ID[0];
   tuple[id2] = ID[1];
   tuple[id3] = ID[2];
   tuple[id4] = ID[3];
   tuple[charge1] = CHARGE[0];
   tuple[charge2] = CHARGE[1];
   tuple[charge3] = CHARGE[2];
   tuple[charge4] = CHARGE[3];
   tuple[passed] = PASSED;
   tuple[peak] = PEAK;


   (*m_showerTuple).fill(tuple);







   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
InclusiveXXX3872Proc::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
InclusiveXXX3872Proc::endRun( Frame& iFrame )         // anal4 equiv.
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
