#if !defined(C3CCPROD_CCFORTRANSHOWERCORRECTOR_H)
#define C3CCPROD_CCFORTRANSHOWERCORRECTOR_H
// -*- C++ -*-
//
// Package:     <C3ccProd>
// Module:      CcFortranShowerCorrector
// 
/**\class CcFortranShowerCorrector CcFortranShowerCorrector.h C3ccProd/CcFortranShowerCorrector.h

 Description: <one line class summary>

 Usage:
    <usage>

*/
//
// Author:      
// Created:     Tue Nov 30 11:46:32 EST 2004
// $Id: CcFortranShowerCorrector.h,v 1.3 2008/02/19 17:21:41 bkh Exp $
//
// Revision history
//
// $Log: CcFortranShowerCorrector.h,v $
// Revision 1.3  2008/02/19 17:21:41  bkh
// Separate Endcap energy fix from mc smearing & error-inflation fix
//
// Revision 1.2  2007/03/16 15:02:21  bkh
// Parameter-controlled increase in sigmas, smearing in MC
//
// Revision 1.1  2004/11/30 21:15:30  cdj
// use CcFortranShowerCorrector to implement new CcShowerAttributes interface
//

// system include files

// user include files
#include "Experiment/fortran_types.h"
#include "C3cc/CcShowerCorrectorBase.h"

// forward declarations

class CcFortranShowerCorrector : public CcShowerCorrectorBase
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------

      // ---------- Constructors and destructor ----------------
      CcFortranShowerCorrector() {}
      virtual ~CcFortranShowerCorrector() {}

      // ---------- member functions ---------------------------

      // ---------- const member functions ---------------------
      virtual void
      gammaEnergyAndSigmas( const FReal&    eIn ,
			    const FReal&    theta ,
			    const FReal&    phi ,
			    const FInteger& ring ,
			    FReal&          eOut ,
			    FReal&          enErr ,
			    FReal&          thErr ,
			    FReal&          phErr ,
			    const FLogical&       isMC  ,
			    const FReal&          baGain ,
			    const FReal&          ecGain ,
			    const FLogical&       lfixit ,
			    const FLogical&       lfixEndcap  ) const  ;
      

      virtual void
      toBlockCoords( const FReal& aTh ,
		     const FReal& aPh ,
		     FReal&       aThBl ,
		     FReal&       aPhBl   ) const ;
      

      virtual void
      toPocketCoords( const FReal& aTh   ,
		      const FReal& aPh   ,
		      FReal&       aThP  ,
		      FReal&       aPhP  ,
		      FInteger&    aPock  ) const ;
      
      virtual void e9OverE25CutValues( const FReal& aEnergy ,
				       const FReal& aTheta  ,
				       const FReal& aPhi    ,
				       FReal&       aCut1   ,
				       FReal&       aCut5   ,
				       FReal&       aCut10   ) const ;

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      CcFortranShowerCorrector( const CcFortranShowerCorrector& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const CcFortranShowerCorrector& operator=( const CcFortranShowerCorrector& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "C3ccProd/Template/CcFortranShowerCorrector.cc"
//#endif

#endif /* C3CCPROD_CCFORTRANSHOWERCORRECTOR_H */
