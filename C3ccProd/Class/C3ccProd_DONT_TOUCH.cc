// -*- C++ -*-
//
// Package:     C3ccProd
// Module:      C3ccProd_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Factory method to create processor C3ccProd:
//              creates a new C3ccProd instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      Brian K. Heltsley
// Created:     Mon Jul 19 11:08:47 EDT 1999
// $Id: C3ccProd_DONT_TOUCH.cc,v 1.1.1.1 1999/07/19 15:27:30 bkh Exp $
//
// Revision history
//
// $Log: C3ccProd_DONT_TOUCH.cc,v $
// Revision 1.1.1.1  1999/07/19 15:27:30  bkh
// imported C3ccProd sources
//
//
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "C3ccProd/C3ccProd.h"

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: C3ccProd_DONT_TOUCH.cc,v 1.1.1.1 1999/07/19 15:27:30 bkh Exp $";
static const char* const kTagString = "$Name: v04_00_08 $";

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
   return new C3ccProd;
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
