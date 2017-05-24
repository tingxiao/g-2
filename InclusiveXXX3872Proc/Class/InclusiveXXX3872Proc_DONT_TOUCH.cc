// -*- C++ -*-
//
// Package:     InclusiveXXX3872Proc
// Module:      InclusiveXXX3872Proc_DONT_TOUCH
// 
// Description: DONT TOUCH THIS FILE
//
//              Definition of bind action
//
// Implementation:
//
// Author:      pts/16
// Created:     Mon Apr 16 20:14:38 CDT 2012
// $Id$
//
// Revision history
//
// $Log$
 
#include "Experiment/Experiment.h"

// system include files
#if defined(AMBIGUOUS_STRING_FUNCTIONS_BUG)
#include <string>
#endif /* AMBIGUOUS_STRING_FUNCTIONS_BUG */            

// user include files
#include "InclusiveXXX3872Proc/InclusiveXXX3872Proc.h"
#include "Processor/Action.h"                

// STL classes

//
// constants, enums and typedefs
//
// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor_DONT_TOUCH.cc,v 1.5 1998/12/01 21:11:58 mkl Exp $";
static const char* const kTagString = "$Name: v07_03_00 $";

//
// function definitions
//

//
// static data member definitions
//

//
// member functions
//
// ---------------- binding method to stream -------------------
void
InclusiveXXX3872Proc::bind(
   ActionBase::ActionResult (InclusiveXXX3872Proc::*iMethod)( Frame& ),
   const Stream::Type& iStream )
{
   bindAction( iStream, new Action<InclusiveXXX3872Proc>( iMethod, this ) );
}

//
// const member functions
//

//
// static member functions
//
