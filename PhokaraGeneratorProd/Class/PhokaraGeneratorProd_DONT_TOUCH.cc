// -*- C++ -*-
//
// Package:     <PhokaraGeneratorProd>
// Module:      PhokaraGeneratorProd_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Factory method to create processor PhokaraGeneratorProd:
//              creates a new PhokaraGeneratorProd instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//

 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "PhokaraGeneratorProd/PhokaraGeneratorProd.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: PhokaraGeneratorProd_DONT_TOUCH.cc,v 1.1 2009/07/04 12:00:00 sdobbs Exp $";
static const char* const kTagString = "$Name: v01_00_01 $";

//
// function definitions
//

extern "C" {
   Producer* makeProducer( void );
   const char* versionString( void );
}

Producer*
makeProducer( void )
{
   return new PhokaraGeneratorProd;
}

const char*
versionString( void )
{
   return kTagString;
}

//
// static data member definitions
//

//
// member functions
//

//
// const member functions
//

//
// static member functions
//
