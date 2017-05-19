// -*- C++ -*-
//
// Package:     Bin50_JpsiPiPiProc
// Module:      Bin50_JpsiPiPiProc_DONT_TOUCH2
// 
// Description: DONT TOUCH THIS FILE!
//
//              Factory method to create processor Bin50_JpsiPiPiProc:
//              creates a new Bin50_JpsiPiPiProc instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      Sean Dobbs
// Created:     Wed Jul  7 17:32:00 EDT 2004
// $Id$
//
// Revision history
//
// $Log$
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif             

// user include files
#include "Bin50_JpsiPiPiProc/Bin50_JpsiPiPiProc.h"

// STL classes
#include <string>

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor_DONT_TOUCH2.cc,v 1.4 1998/12/01 21:11:59 mkl Exp $";
static const char* const kTagString = "$Name: v06_08_00 $";

//
// function definitions
//

extern "C" {
   Processor* makeProcessor( void );
   const char* versionString( void );
}

Processor*
makeProcessor( void )
{
   return new Bin50_JpsiPiPiProc;
}

const char*
versionString( void )
{
   return kTagString;
}

