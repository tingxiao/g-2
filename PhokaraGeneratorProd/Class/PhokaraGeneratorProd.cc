// -*- C++ -*-
//
// Package:     <PhokaraGeneratorProd>
// Module:      PhokaraGeneratorProd
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>


#include "Experiment/Experiment.h"
#include "Experiment/fortran_types.h"


// system include files

// user include files
#include "PhokaraGeneratorProd/PhokaraGeneratorProd.h"
#include "PhokaraGeneratorProd/PhokaraDecayTreeProxy.h"
#include "Experiment/report.h"

#include "DataHandler/RecordMethods.h"
#include "DataHandler/ProxyFactory.h"
#include "DataHandler/ProxyFactoryFunction.h"

// STL classes
// You may have to uncomment some of these or other stl headers
// depending on what other header files you include (e.g. FrameAccess etc.)!
#include <string>
#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "PhokaraGeneratorProd.PhokaraGeneratorProd" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PhokaraGeneratorProd.cc,v 1.4 2009/07/04 12:00:00 sdobbs Exp $";
static const char* const kTagString = "$Name: v01_00_01 $";

//
// static data member definitions
//

//
// constructors and destructor
//

// sdobbs, CHANGE THIS!
PhokaraGeneratorProd::PhokaraGeneratorProd( void )               // anal1
   : Producer( "PhokaraGeneratorProd" ) ,
     m_Menu("PhokaraParameters", this),
     m_mode ( "Mode" , &m_Menu,  "None" ),
     m_nmax  ( "NMax" , &m_Menu,  10000 ),
     m_nlo  ( "NLO" , &m_Menu,  0 ),
     m_nlofsr ( "NLOFSR" , &m_Menu,  0 ),
     m_fsrmode ( "FSRMode" , &m_Menu,  1 ),
     m_vacpolrz ( "VacuumPolarization" , &m_Menu,  1 ),
     m_tagged ( "TaggedPhotons" , &m_Menu,  1 ),
     m_FFpion ( "FFpion" , &m_Menu,  1 ),
     m_F0model ( "F0model" , &m_Menu,  0 ),

     m_wcutoff ( "W" , &m_Menu,  0.0001 ),
     m_q2min ( "Q2min" , &m_Menu,  0.0447 ),
     m_q2max ( "Q2max" , &m_Menu,  10. ),
     m_egmin ( "Egmin" , &m_Menu,  0.1 ),
     m_gam1angcut ( "Gam1AngleCut" , &m_Menu,  0. ),
     m_gam2angcut ( "Gam2AngleCut" , &m_Menu,  180. ),
     m_pi1angcut ( "Pi1AngleCut" , &m_Menu,  0. ),
     m_pi2angcut ( "Pi2AngleCut" , &m_Menu,  180. )

{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;
   m_mode.setHelpString("Mode: MuMu, PiPi, 2Pi2Pi0, 4Pi, PPbar, NNbar, KK, K0K0, PiPiPi0, LambLamb" ) ;
   m_nmax.setHelpString("NMax: Number of events used to calculate weights");

   m_nlo.setHelpString("NLO: Born calc (0), NLO calc (1)");
   m_nlofsr.setHelpString("NLOFSR: Yes (1), No (0) ");
   m_fsrmode.setHelpString("FSRMode: ISR only (0), ISR+FSR (1), ISR+FSR w/ interference (2)");
   m_vacpolrz.setHelpString("VacuumPolarization: Yes (1), No (0) ");
   m_tagged.setHelpString("TaggedPhotons: Tagged Photons (0), Untagged Photons(1)");
   m_FFpion.setHelpString("FFpion, pi+pi- form factor: KS (0), GS (1)");
   m_F0model.setHelpString("F0model: f0+f0(600): KK model(0), no structure(1), no f0+f0(600)(2), f0 KLOE(3)");

   m_wcutoff.setHelpString("W, soft photon cutoff");
   m_q2min.setHelpString("Q2min: Minimum inv. mass squared of fermions");
   m_q2max.setHelpString("Q2max: Maximum inv. mass squared of fermions");
   m_egmin.setHelpString("Egmin: Minimum photon/missing energy");
   m_gam1angcut.setHelpString("Gam1AngleCut: Minimum photon angle/missing momentum angle");
   m_gam2angcut.setHelpString("Gam2AngleCut: Maximum photon angle/missing momentum angle");
   m_pi1angcut.setHelpString("Pi1AngleCut: Minimum fermion angle");
   m_pi2angcut.setHelpString("Pi2AngleCut: Maximum fermion angle");


   registerProxyFactory( 
      Stream::kEvent, 
      new ProxyFactoryFunction< PhokaraGeneratorProd, PhokaraDecayTreeProxy >(
	 *this, 
	 &PhokaraGeneratorProd::makeMyProxy ),
      UsageTag("Generator") );    // or UsageTag( "MyUsage" )
}

ProxyBase*
PhokaraGeneratorProd::makeMyProxy()
{ 
   return new PhokaraDecayTreeProxy( this );
}

// Proxy Registration Step 2:
// template instantiations for proxy factories
#include "DataHandler/Template/ProxyFactoryFunction.cc"
template class ProxyFactoryFunction< PhokaraGeneratorProd, PhokaraDecayTreeProxy >;

// non-trivial proxyfactory producer method used above
// (if you want to use it, don't forget to declare this method 
//  in "producer.h"!)

// PhokaraGeneratorProd::PhokaraGeneratorProd( const PhokaraGeneratorProd& iPhokaraGeneratorProd )
// {
//    *this = iPhokaraGeneratorProd;
// }

PhokaraGeneratorProd::~PhokaraGeneratorProd()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// assignment operators
//
// const PhokaraGeneratorProd& PhokaraGeneratorProd::operator=( const PhokaraGeneratorProd& iPhokaraGeneratorProd )
// {
//   if( this != &iPhokaraGeneratorProd ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( iPhokaraGeneratorProd );
//   }
//
//   return *this;
// }

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
PhokaraGeneratorProd::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)
}

extern "C"
void 
phk_finishup_() ;

// -------------------- terminate method ----------------------------
void
PhokaraGeneratorProd::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;
   
   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
   phk_finishup_();
}

// ---------------- standard place to book histograms ---------------
void
PhokaraGeneratorProd::hist_book( HIHistoManager& )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here

}

//
// const member functions
//

//
// static member functions
//
