// -*- C++ -*-
//
// Package:     <package>
// Module:      PhokaraDecayTreeProxy
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>


#include "Experiment/Experiment.h"

// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>

#include <memory>  //for auto_ptr

// user include files
#include "Experiment/report.h"
#include "Experiment/fortran_types.h"

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"           
#include "FrameAccess/FATable.h"

#include "PhokaraGeneratorProd/PhokaraDecayTreeProxy.h"
#include "ProxyBind/ProxyBoundMethodAction.h" //need for PROXY_BIND_METHOD
#include "MCBeam/MCBeamParameters.h"
#include "MCBeam/MCBeamParticles.h"
#include "MCBeam/MCEventVertex.h"
#include "HepEvtDTInterface/HepEvtDTInterface.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
#include <vector>
//#include <set>
#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "package.PhokaraDecayTreeProxy" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PhokaraDecayTreeProxy.cc,v 1.5 2006/06/05 13:22:37 gregor Exp $";
static const char* const kTagString = "$Name: v01_00_04 $";

//
// static data member definitions
//

//
// constructors and destructor
//
PhokaraDecayTreeProxy::PhokaraDecayTreeProxy( const PhokaraGeneratorProd* aProd )
   : m_PhokaraDecayTree( 0 ) ,
     m_producer         ( aProd )
{
   //bind 'auxilliary' functions that you want called when a
   // new Record on the particular Stream appears
   //bind( &PhokaraDecayTreeProxy::boundMethod, Stream::kBeginRun );
  
}

// PhokaraDecayTreeProxy::PhokaraDecayTreeProxy( const PhokaraDecayTreeProxy& iproxy )
// {
//   *this = iproxy;
// }

PhokaraDecayTreeProxy::~PhokaraDecayTreeProxy()
{
   delete m_PhokaraDecayTree ;
}

//
// assignment operators
//
// const PhokaraDecayTreeProxy& PhokaraDecayTreeProxy::operator=( const PhokaraDecayTreeProxy& iproxy )
// {
//   if( this != &iproxy ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iproxy );
//   }
//
//   return *this;
// }

//
// member functions
//
void
PhokaraDecayTreeProxy::invalidateCache()
{
   delete m_PhokaraDecayTree ;
   m_PhokaraDecayTree = 0 ;
}

extern "C"
void
phk_init_( const FInteger& nMode,
	   const FDouble& eBeamIn,
	   const FInteger& nMax,

	   const FInteger& nNLO,
	   const FInteger& nNLOFSR,
	   const FInteger& nFSRMode,
	   const FInteger& nVacPolrz,
	   const FInteger& nTagged,
	   const FInteger& nFFpion,
	   const FInteger& nF0model,

	   const FDouble& uWcut,
	   const FDouble& uQ2min,
	   const FDouble& uQ2max,
	   const FDouble& uEgmin,
	   const FDouble& uGam1Ang,
	   const FDouble& uGam2Ang,
	   const FDouble& uPi1Ang,
	   const FDouble& uPi2Ang
);


extern "C"
void
phk_event_( );


extern "C"
void
phk_to_hepevt_() ;



/**
extern "C"
void
bby_event_( const FDouble& eBeam  ) ;

extern "C"
void
bby_to_hepevt_() ;

extern "C"
void      
bby_init_(  const FInteger&   ich , 
	    const FDouble&    eBeam,
	    const FDouble&    angleMin,
	    const FDouble&    angleMax,
	    const FDouble&    energyMin,
	    const FDouble&    acollMax );
**/


const PhokaraDecayTreeProxy::value_type*
PhokaraDecayTreeProxy::faultHandler( const Record& iRecord,
				      const DataKey& iKey )
{
   static DABoolean first (true) ;
   if( first )
   {
      first = false ;

      FAItem<MCBeamParameters>                               beamParms ;
      extract( iRecord.frame().record( Stream::kStartRun ) , beamParms ) ;
      const FDouble ebeam ( beamParms->electronBeamEnergy() ) ;

      const string mode ( m_producer->getMode() ) ;
      report( DEBUG, kFacilityString) << "Mode  = " << mode.c_str() << endl;

      // sdobbs: CHANGE THIS!!
      FInteger ich = -1;
      if( mode == "MuMu") {
	ich = 0;
      } else if( mode == "PiPi") {
	ich = 1;
      } else if( mode == "2Pi2Pi0") {
	ich = 2;
      } else if( mode == "4Pi") {
	ich = 3;
      } else if( mode == "PPbar") {
	ich = 4;
      } else if( mode == "NNbar") {
	ich = 5;
      } else if( mode == "KK") {
	ich = 6;
      } else if( mode == "K0K0") {
	ich = 7;
      } else if( mode == "PiPiPi0") {
	ich = 8;
      } else if( mode == "LambLamb") {
	ich = 9;
      } 

      if( ich < -1 )
      {
	 report( ERROR, kFacilityString ) << "No Mode selected, exiting..." << endl ;
	 assert( false ) ;
      }


      const FInteger nMax( m_producer->getNMax() );
      const FInteger NLO( m_producer->getNLO() );
      const FInteger NLOFSR( m_producer->getNLOFSR() );
      const FInteger FSRMode( m_producer->getFSRMode() );
      const FInteger VacuumPolariz( m_producer->getVacuumPolarization() );
      const FInteger Tagged( m_producer->getTagged() );
      const FInteger FFpion( m_producer->getFFpion() );
      const FInteger F0model( m_producer->getF0model() );
      const FDouble WCutoff( m_producer->getWCutoff() );
      const FDouble Q2Min( m_producer->getQ2Min() );
      const FDouble Q2Max( m_producer->getQ2Max() );
      const FDouble EgMin( m_producer->getEgMin() );
      const FDouble Gam1AngCut( m_producer->getGam1AngCut() );
      const FDouble Gam2AngCut( m_producer->getGam2AngCut() );
      const FDouble Pi1AngCut( m_producer->getPi1AngCut() );
      const FDouble Pi2AngCut( m_producer->getPi2AngCut() );


      /* set parameters */
      //bby_init_( ich , ebeam, angleMin, angleMax, energyMin, acollinarityMax );
      phk_init_( ich, ebeam, nMax, NLO, NLOFSR, FSRMode, VacuumPolariz, Tagged, FFpion, 
		 F0model, WCutoff, Q2Min, Q2Max, EgMin, Gam1AngCut, Gam2AngCut,
		 Pi1AngCut, Pi2AngCut );
   }

   // be assertive: there should be no cached data at this point, else
   // it's a programming error
   assert( 0 == m_PhokaraDecayTree );

   // get the particle properties
   FAItem<MCParticlePropertyStore>                    properties;
   extract( iRecord.frame().record(Stream::kPhysics), properties, "UserMCParticleProperties" );

   FAItem<MCBeamParticles> beamParticles   ;
   extract( iRecord,       beamParticles ) ;

   FAItem<MCEventVertex>   eventVertex     ;
   extract( iRecord,       eventVertex   ) ;

   const HepPoint3D&         point        ( *eventVertex ) ; 
   const HepLorentzVector&   lorMom       ( beamParticles->totalMomentum() ) ;
   const HepLorentzRotation& boostCMToLab ( beamParticles->boostFromCMToLab() ) ;
   const HepLorentzRotation& boostLabToCM ( beamParticles->boostFromLabToCM() ) ;

   static const Integer kVirtualPhotonQQId ( 0 ) ;
   const MCParticleProperty& vPhotonProperty ( properties->getUsingQQId( kVirtualPhotonQQId ) ) ;
   
   MCParticle* vPhoton = new MCParticle( vPhotonProperty, lorMom, point );

   const HepLorentzVector cmLor ( boostLabToCM*lorMom ) ;
   
   const FDouble event_ebeam ( cmLor.e()/2. ) ;
   phk_event_( ) ;


   MCDecayTree* myTree ( new MCDecayTree( vPhoton, true ) )   ;
   auto_ptr<MCDecayTree> p_PhokaraDecayTree ( myTree ) ;

   HepEvtDTInterface* hepevt = HepEvtDTInterface::instance( "Babayaga" );
   //HepEvtDTInterface* hepevt = HepEvtDTInterface::instance( "Phokara" );
   hepevt->resetCommons( eventVertex->t() );
   hepevt->setMCDecayTree( myTree ) ;

   phk_to_hepevt_() ;
   hepevt->attachHepEvtToParticle(vPhoton ) ; // convert from commons to tree
   

   // now boost back to lab
   MCVertex* vtx ( &*vPhoton->vBegin() ) ;
   for( MCVertex::pIterator pIt ( vtx->pBegin() ) ; pIt != vtx->pEnd() ; ++pIt )
   {
      MCParticle& par ( *pIt ) ;
      par.setPosition( point ) ;
      HepLorentzVector mom ( par.lorentzMomentum() );

      par.setMomentum( HepVector3D(Hep3Vector(boostCMToLab*mom) ) ) ;
   }
   /**/

   report( DEBUG, kFacilityString) << *myTree <<endl;

   return ( m_PhokaraDecayTree = p_PhokaraDecayTree.release() ) ;
}

//
// const member functions
//

//
// static member functions
//

//
// 'bound' functions
//

//void
//PhokaraDecayTreeProxy::boundMethod( const Record& iRecord )
//{
//   report( INFO, kFacilityString) <<"BoundMethod: " <<iRecord.stream().value() << endl;
//}

//-----------------------------------------------
// DO NOT DELETE
#include "ProxyBind/Template/ProxyBindableTemplate.cc"
template class ProxyBindableTemplate< MCDecayTree >;

PROXY_BIND_METHOD( PhokaraDecayTreeProxy )
//-----------------------------------------------

