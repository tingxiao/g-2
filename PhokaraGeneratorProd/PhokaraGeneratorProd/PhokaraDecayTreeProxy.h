// -*- C++ -*-
#if !defined(PACKAGE_PHOKARADECAYTREEPROXY_H)
#define PACKAGE_PHOKARADECAYTREEPROXY_H
//
// Package:     <package>
// Module:      PhokaraDecayTreeProxy
//
/**\class PhokaraDecayTreeProxy PhokaraDecayTreeProxy.h package/PhokaraDecayTreeProxy.h
 
 Description: <one line class summary>

 Usage:
    <usage>

*/


// system include files

// user include files
#include "ProxyBind/ProxyBindableTemplate.h"
#include "MCInfo/MCDecayTree/MCDecayTree.h"
#include "PhokaraGeneratorProd/PhokaraGeneratorProd.h"

// forward declarations

class PhokaraDecayTreeProxy : public ProxyBindableTemplate< MCDecayTree >
{
      // friend classes and functions

   public:
      // constants, enums and typedefs
      typedef MCDecayTree value_type;

      // Constructors and destructor
      PhokaraDecayTreeProxy( const PhokaraGeneratorProd* aProd );
      virtual ~PhokaraDecayTreeProxy();

      // member functions

      // use this form of a function when calling 'bind'
      // void boundMethod( const Record& iRecord );

      // const member functions

      // static member functions

   protected:
      // protected member functions
      virtual void invalidateCache() ;
      virtual const value_type* faultHandler( const Record& aRecord,
					      const DataKey& aKey );

      // protected const member functions

   private:
      // Constructors and destructor
      PhokaraDecayTreeProxy( const PhokaraDecayTreeProxy& );

      // assignment operator(s)
      const PhokaraDecayTreeProxy& operator=( const PhokaraDecayTreeProxy& );

      // private member functions

      //this function has already been written for you
      void bind(
		void (PhokaraDecayTreeProxy::*iMethod)( const Record& ),
		const Stream::Type& iStream );

      // private const member functions

      // data members
      value_type* m_PhokaraDecayTree ;

      const PhokaraGeneratorProd* m_producer ;

      // static data members

};

// inline function definitions

//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
// templated member function definitions
//# include "package/Template/PhokaraDecayTreeProxy.cc"
//#endif

#endif /* PACKAGE_PHOKARADECAYTREEPROXY_H */
