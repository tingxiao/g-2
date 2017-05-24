// -*- C++ -*-
#if !defined(PHOKARAGENERATORPROD_PHOKARAGENERATORPROD_H)
#define PHOKARAGENERATORPROD_PHOKARAGENERATORPROD_H
//
// Package:     <PhokharaGeneratorProd>
// Module:      PhokharaGeneratorProd
//
/**\class PhokharaGeneratorProd PhokharaGeneratorProd.h PhokharaGeneratorProd/PhokharaGeneratorProd.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/

// system include files

// user include files
#include "Processor/Producer.h"
#include "HistogramInterface/HistogramPackage.h"
#include "CommandPattern/Menu.h"
#include "CommandPattern/Parameter.h"
//#include "CommandPattern/Menu.h"

// forward declarations

class PhokharaGeneratorProd : public Producer
{
      // ------------ friend classses and functions ---------------

   public:
      // ------------ constants, enums and typedefs ---------------

      // ------------ Constructors and destructor -----------------
      PhokharaGeneratorProd( void );                      // anal1 
      virtual ~PhokharaGeneratorProd();                   // anal5 

      // ------------ member functions ----------------------------

      // methods for beginning/end "Interactive"
      virtual void init( void );             // anal1 "Interactive"
      virtual void terminate( void );        // anal5 "Interactive"

      // standard place for booking histograms
      virtual void hist_book( HIHistoManager& );                  

      // ------------ const member functions ----------------------

//    generator mode
      const string& getMode() const 
      { return m_mode.value() ; } 


      const double& getNMax() const
      { return m_nmax.value() ; }


      const double& getNLO() const
      { return m_nlo.value() ; }

      const double& getNLOFSR() const
      { return m_nlofsr.value() ; }

      const double& getFSRMode() const
      { return m_fsrmode.value() ; }

      const double& getVacuumPolarization() const
      { return m_vacpolrz.value() ; }

      const double& getTagged() const
      { return m_tagged.value() ; }

      const double& getFFpion() const
      { return m_FFpion.value() ; }

      const double& getF0model() const
      { return m_F0model.value() ; }

      const double& getWCutoff() const
      { return m_wcutoff.value() ; }

      const double& getQ2Min() const
      { return m_q2min.value() ; }

      const double& getQ2Max() const
      { return m_q2max.value() ; }

      const double& getEgMin() const
      { return m_egmin.value() ; }

      const double& getGam1AngCut() const
      { return m_gam1angcut.value() ; }

      const double& getGam2AngCut() const
      { return m_gam2angcut.value() ; }

      const double& getPi1AngCut() const
      { return m_pi1angcut.value() ; }

      const double& getPi2AngCut() const
      { return m_pi2angcut.value() ; }


      // ------------ static member functions ---------------------

   protected:
      // ------------ protected member functions ------------------

      // ------------ protected const member functions ------------

   private:
      // ------------ Constructors and destructor -----------------
      PhokharaGeneratorProd( const PhokharaGeneratorProd& );

      // ------------ assignment operator(s) ----------------------
      const PhokharaGeneratorProd& operator=( const PhokharaGeneratorProd& );

      // ------------ private member functions --------------------

      ProxyBase* makeMyProxy() ;

      // ------------ private const member functions --------------

      // ------------ data members --------------------------------

      Menu              m_Menu;
      Parameter<string> m_mode ;  
      Parameter<int> m_nmax;           

      Parameter<int> m_nlo;           
      Parameter<int> m_nlofsr;           
      Parameter<int> m_fsrmode;           
      Parameter<int> m_vacpolrz;           
      Parameter<int> m_tagged;           
      Parameter<int> m_FFpion;           
      Parameter<int> m_F0model;           
      Parameter<double> m_wcutoff;           
      Parameter<double> m_q2min;           
      Parameter<double> m_q2max;           
      Parameter<double> m_egmin;           
      Parameter<double> m_gam1angcut;           
      Parameter<double> m_gam2angcut;           
      Parameter<double> m_pi1angcut;           
      Parameter<double> m_pi2angcut;           


      // ------------ static data members -------------------------

};

// inline function definitions

#endif /* PHOKARAGENERATORPROD_PHOKARAGENERATORPROD_H */
