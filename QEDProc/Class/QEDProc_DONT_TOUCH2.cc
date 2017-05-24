// -*- C++ -*-
//
// Package:     QEDProc
// Module:      QEDProc_DONT_TOUCH2
// 
// Description: DONT TOUCH THIS FILE!
//
//              Factory method to create processor QEDProc:
//              creates a new QEDProc instance each time 
//              it is called; it is used by Suez 
//              to create a Processor after loading in 
//              the code from a shared library.
//
// Implementation:
//
// Author:      
// Created:     Mon Dec 10 16:45:47 CST 2012
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
#include "QEDProc/QEDProc.h"

// STL classes
#include <string>

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor_DONT_TOUCH2.cc,v 1.4 1998/12/01 21:11:59 mkl Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

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
   return new QEDProc;
}

const char*
versionString( void )
{
   return kTagString;
}

