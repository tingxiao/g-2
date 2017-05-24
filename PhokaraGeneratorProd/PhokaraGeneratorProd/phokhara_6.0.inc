      implicit none 
c --- couplings, masses, momenta ---
      double precision pi,gev2nbarn,gev2pbarn,alpha,me,mmu,
     & mpi,mpi0,Sp,ebeam,rmass(10),momenta(15,0:3),mp,mnt,mKp,mKn,
     & mlamb
c --- Kaons masses and gamms
      double precision m_phi0_Kp,g_phi0_Kp,m_phi1_Kp,g_phi1_Kp,m_om0_Kp,
     & g_om0_Kp,m_om1_Kp,g_om1_Kp,m_om2_Kp,g_om2_Kp,m_rho0_Kp,g_rho0_Kp,
     & m_rho1_Kp,g_rho1_Kp,m_rho2_Kp,g_rho2_Kp
c --- Pions pi+pi- masses and gamms
      double precision m_rho0_pion,g_rho0_pion,m_rho1_pion,g_rho1_pion,
     & m_rho2_pion,g_rho2_pion,m_rho3_pion,g_rho3_pion,m_om0_pion,
     & g_om0_pion    
c --- Lambdas
      double precision alpha_lamb,ratio_lamb      
c --- cuts ---     
      double precision Emin,gmin,phot1cut,phot2cut,pi1cut,pi2cut,
     & piphcut,accecut,q2min,w,q2_max_c,ver_s,q2_min_c
c --- histograms ---
      character*20 title(20)
      double precision xlow(20),xup(20)
      integer bins(20),iprint
c --- Maxima ---
      double precision Mmax(2),gross(2),klein(2),tr(2),count(2)
c --- flags --
      integer nlo,tagged,pion,fsr,fsrnlo,ivac,FF_Pion,f0_model
c ---
      complex*16 cvac_s,cvac_s_pi,cvac_s_phi
c ---
      integer*8 nges,nm
      integer nphoton
      integer naccept
c ---
      common /ctes/pi,gev2nbarn,gev2pbarn,alpha,me,mmu,mpi,mpi0,Sp,mp,
     & ebeam,ver_s,rmass,momenta,cvac_s,mnt,mKp,mKn,cvac_s_pi,
     & cvac_s_phi,mlamb
      common/mass_gamm_Kp/m_phi0_Kp,g_phi0_Kp,m_phi1_Kp,g_phi1_Kp,
     & m_om0_Kp,g_om0_Kp,m_om1_Kp,g_om1_Kp,m_om2_Kp,g_om2_Kp,
     & m_rho0_Kp,g_rho0_Kp,m_rho1_Kp,g_rho1_Kp,m_rho2_Kp,g_rho2_Kp
      common/mass_gamm_pion/m_rho0_pion,g_rho0_pion,m_rho1_pion,
     & g_rho1_pion,m_rho2_pion,g_rho2_pion,m_rho3_pion,g_rho3_pion,
     & m_om0_pion,g_om0_pion
      common/lambda_par/ alpha_lamb,ratio_lamb
      common/cuts/Emin,gmin,phot1cut,phot2cut,pi1cut,pi2cut,
     & piphcut,accecut,q2min,w,q2_max_c,q2_min_c
      common /histo/   xlow,xup,bins,title
      common /maxima/  Mmax,gross,klein,tr,count,iprint
      common/flags/ nlo,tagged,pion,fsr,fsrnlo,ivac,FF_Pion,f0_model
      common/stats/ nges,nm,nphoton,naccept
