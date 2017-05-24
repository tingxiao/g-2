// TrackData.cxx
// class to store track information from ntuple

#include "TrackDataLite.h"

using namespace std;

void TrackDataLite::SetAll( const int new_id, const double new_px, const double new_py, 
			const double new_pz, const double new_e, 
			const double new_x, const double new_y, const double new_z, 
			const double new_mass, const double new_charge, const double new_doca, 
			const double new_z0, const double new_reduced_chisq, const double new_sigpi, 
			const double new_sigk, const double new_sigp, const double new_llpi, 
			const double new_llk, const double new_llp, const double new_DLpik, 
			const double new_DLkp, const double new_ep, const double new_mu_depth) 
{
  id = new_id;
  px = new_px;
  py = new_py;
  pz = new_pz;
  e = new_e;
  x = new_x;
  y = new_y;
  z = new_z;
  mass = new_mass;
  charge = new_charge;
  doca = new_doca;
  z0 = new_z0;
  reduced_chisq = new_reduced_chisq;
  sigpi = new_sigpi;
  sigk  = new_sigk;
  sigp  = new_sigp;
  llpi  = new_llpi;
  llk   = new_llk;
  llp   = new_llp;
  DLpik = new_DLpik;
  DLkp  = new_DLkp;
  ep    = new_ep;
  mu_depth = new_mu_depth;
}

void TrackDataLite::Print()
{
  cout<<"TRACK "<<id<<endl;
  cout<<"p: ( "<<e<<", "<<px<<", "<<py<<", "<<pz<<" )  chg: "<<charge<<endl;
  cout<<"x: ( "<<x<<", "<<y<<", "<<z<<" )  mass: "<<mass<<endl;
  cout<<"doca: "<<doca<<"  z0: "<<z0<<"  chi^2/dof: "<<reduced_chisq<<endl;
  cout<<"sig(pi): "<<sigpi<<"  sig(K): "<<sigk<<"  sig(p): "<<sigp<<endl;
  cout<<"ll(pi): "<<llpi<<"  ll(k): "<<llk<<"  ll(p): "<<llp<<endl;
  cout<<"DL(pi-k): "<<DLpik<<"  DL(k-p): "<<DLkp<<endl;
  cout<<"E/p: "<<ep<<"  mu depth: "<<mu_depth<<endl;
}
