// TrackDataLite.h
// class to store track information from ntuple

#ifndef _TRACK_DATA_LITE_
#define _TRACK_DATA_LITE_

#include <TROOT.h>
#include <TObject.h>
#include <iostream>
#include <cmath>

class six_tr;
class eight_tr;
class four_tr;

class TrackDataLite
{
 public:
  TrackDataLite() {  return; }
  TrackDataLite( const int new_id,
	     const double new_px, const double new_py, const double new_pz, const double new_e, 
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

  /*
  TrackData ( const TrackData& new_td ) {
    *this = new_td;
  }

  ~TrackData{} { return; }
  */

  // accessor methods
  int const ID() const { return id; }
  double const X() const { return x; }
  double const Y() const { return y; }
  double const Z() const { return z; }
  double const Px() const { return px; }
  double const Py() const { return py; }
  double const Pz() const { return pz; }
  double const Pmag() const { return sqrt(px*px + py*py + pz*pz); }
  double const Pmag2() const { return (px*px + py*py + pz*pz); }
  double const E() const { return e; }
  double const Mass() const { return mass; }
  double const Charge() const { return charge; }
  double const Doca() const { return doca; }
  double const Z0() const { return z0; }
  double const ReChiSq() const { return reduced_chisq; }
  double const SigPi() const { return sigpi; }
  double const SigK() const { return sigk; }
  double const SigP() const { return sigp; }
  double const LLPi() const { return llpi; }
  double const LLK() const { return llk; }
  double const LLP() const { return llp; }
  double const DLPiK() const { return DLpik; }
  double const DLKP() const { return DLkp; }
  double const Ep() const { return ep; }
  double const MuDepth() const { return mu_depth; }

  // set methods
  void SetID(const int new_val) { id = new_val; }
  void SetX(const double new_val) { x = new_val; }
  void SetY(const double new_val) { y = new_val; }
  void SetZ(const double new_val) { z = new_val; }
  void SetPx(const double new_val) { px = new_val; }
  void SetPy(const double new_val) { py = new_val; }
  void SetPz(const double new_val) { pz = new_val; }
  void SetE(const double new_val) { e = new_val; }
  void SetMass(const double new_val) { mass = new_val; } 
  void SetCharge(const double new_val) { charge = new_val; }
  void SetDoca(const double new_val) { doca = new_val; }
  void SetZ0(const double new_val) { z0 = new_val; }
  void SetReChiSq(const double new_val) { reduced_chisq = new_val; }
  void SetSigPi(const double new_val) { sigpi = new_val; }
  void SetSigK(const double new_val) { sigk = new_val; }
  void SetSigP(const double new_val) { sigp = new_val; }
  void SetLLPi(const double new_val) { llpi = new_val; }
  void SetLLK(const double new_val) { llk = new_val; }
  void SetLLP(const double new_val) { llp = new_val; }
  void SetDLPiK(const double new_val) { DLpik = new_val; }
  void SetDLKP(const double new_val) { DLkp = new_val; }
  void SetEp(const double new_val) { ep = new_val; }
  void SetMuDepth(const double new_val) { mu_depth = new_val; }
  void SetAll( const int new_id, const double new_px, const double new_py, 
	       const double new_pz, const double new_e, 
	       const double new_x, const double new_y, const double new_z, 
	       const double new_mass, const double new_charge, const double new_doca, 
	       const double new_z0, const double new_reduced_chisq, const double new_sigpi, 
	       const double new_sigk, const double new_sigp, const double new_llpi, 
	       const double new_llk, const double new_llp, const double new_DLpik, 
	       const double new_DLkp, const double new_ep, const double new_mu_depth);
  void Print();
  
 private:
  int id;
  double px, py, pz, e;
  double x, y, z;
  double charge, mass;
  double doca, z0, reduced_chisq;
  double sigpi, sigk, sigp;
  double llpi, llk, llp;
  double DLpik, DLkp;
  double ep, mu_depth;
};



#endif
