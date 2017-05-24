c ======================================================================== c
c                                                                          c
c Monte Carlo event generator for simulation of hadron or muon production  c
c with radiated photons in e+e- collisions at high luminosity              c
c meson factories                                                          c
c                                                                          c 
c                         PHOKHARA version 6.0                             c
c                           (December 2006)                                c
c                                                                          c
c simulates the production of two, three or four pions, two muons,         c
c two nucleons, two kaons or two lambdas (with their subsequent decays     c
c into pion and proton) together  with one or two hard photons emitted     c
c from the initial state (ISR); it includes virtual and soft photon        c
c corrections to single photon emission. It includes FSR emission,         c
c and ISR-FSR interference of  one  photon in  the two pion, two charged   c
c kaon and two muon modes. Emission of two photons, one from the initial   c
c state and the other from the final state, together with the appropriate  c
c virtual corrections, is also included in the two pion, two charged kaon  c
c and  two muon modes.                                                     c
c                                                                          c
c ------------------------------------------------------------------------ c
c   The program is based on the following publications:                    c
c                                                                          c
c Started as EVA:                                                          c
c                                                                          c
c     S.Binner, J.H.Kuehn and K.Melnikov, PLB459(1999)279 [hep-ph/9902399] c
c                                                                          c
c Includes NLO corrections to ISR for large angle photons from             c
c                                                                          c 
c     G.Rodrigo, A.Gehrmann, M.Guilleaume and J.H.Kuehn,                   c 
c         Eur.Phys.J.C22(2001)81 [hep-ph/0106132]                          c
c     G.Rodrigo, APPB32(2001)3833 [hep-ph/0111151]                         c
c     G.Rodrigo, H.Czyz, J.H.Kuehn and M.Szopa,                            c
c         Eur.Phys.J.C24(2002)71 [hep-ph/0112184]                          c
c                                                                          c
c and NLO corrections to ISR for small angle photons                       c
c                                                                          c
c     J.H.Kuehn and G.Rodrigo, Eur.Phys.J.C25(2002)215 [hep-ph/0204283]    c
c                                                                          c
c The implementation of four pion final states follows                     c
c                                                                          c
c     H.Czyz and J.H.Kuehn, Eur.Phys.J.C18(2001)497 [hep-ph/0008262]       c
c                                                                          c
c with improvements described in                                           c
c                                                                          c
c     H.Czyz, A.Grzelinska, J.H.Kuehn and G.Rodrigo,                       c
c         Eur.Phys.J.C27(2003)563 [hep-ph/0212225]                         c
c                                                                          c
c where the actual implementation of FSR and the complete  description  of c
c upgrades from PHOKHARA 1.0 to PHOKHARA 2.0 is presented. This paper pre- c
c sents also a lot of physical analysis concerning  the  radiative  return c
c method.                                                                  c
c                                                                          c
c The implementation of IFSNLO -- a simultaneous emission  of  one  photon c
c from initial state and one photon from  final  state  (plus  appropriate c
c radiative corrections) -- is presented in                                c
c                                                                          c
c     H.Czyz, A.Grzelinska, J.H.Kuehn and G.Rodrigo,                       c
c         Eur.Phys.J.C33 (2003) 333 [hep-ph/0308312].                      c
c     for pions                                                            c
c  and in                                                                  c
c     H.Czyz, A.Grzelinska, J.H.Kuehn and G.Rodrigo,                       c
c         Eur. Phys. J. C39 (2005) 411 [hep-ph/0404078].                   c
c     for muons                                                            c
c                                                                          c
c where the physical significance of these corrections  is  discussed  and c 
c the upgrade to PHOKHARA 3.0 and PHOKHARA 4.0 is described.               c
c                                                                          c
c Implementation of two-nucleon final states can be found in               c
c                                                                          c
c  H. Czyz, J.H. Kuhn, E. Nowak and G. Rodrigo,                            c
c         Eur. Phys. J. C35 (2004) 527 [hep-ph/0403062].                   c
c                                                                          c
c where also a method of separation of nucleon form-factors is proposed.   c   
c                                                                          c
c The upgrades to PHOKHARA 5.0 contain the implementation of radiative     c
c phi decay contribution to e+e- -> pi+ pi- gamma (gamma) reaction         c
c                                                                          c
c  H.Czyz, A.Grzelinska, J.H.Kuehn                                         c
c         Phys. Lett. B611 (2005) 116 [hep-ph/0412239].                    c
c                                                                          c
c and also pi+ pi- pi0,                                                    c
c   in PHOKHARA 5.1 the model for  pi+ pi- pi0 current and one of the      c
c   models describing the radiative phi decay contribution                 c
c   to e+e- -> pi+ pi- gamma (gamma) reaction was changed                   c 
c     H.Czyz, A.Grzelinska, J.H.Kuehn and G.Rodrigo,                       c
c           Eur. Phys. J. C47 (2006) 617 [hep-ph/0512180]                  c
c   and             K+K-, K \barK                                          c
c      - in preparation.                                                   c
c                                                                          c
c  The upgrade to PHOKHARA 6.0 contain the modelling of                   c
c  the  e+e- -> Lambda (-> pi- proton) ani-Lambda (-> pi+ anti-proton)     c
c  implemented at LO.                                                      c
c                                                                          c
c    H.Czyz, A.Grzelinska, J.H.Kuehn  hep-ph/0702122                       c
c                                                                          c
c Further reading concerning the radiative return method and the PHOKHARA  c
c event generator:                                                         c
c                                                                          c
c     J.H.Kuehn,                                                           c
c        Nucl.Phys.Proc.Suppl.98(2001)289 [hep-ph/0101100];                c
c        Eur. Phys. J. 33 (2004) S659                                      c
c        Nucl.Phys.Proc.Suppl. 144 (2005) 214.                             c
c     H.Czyz, J.H.Kuehn and G.Rodrigo,                                     c
c        hep-ph/0205097;                                                   c
c        Nucl.Phys.Proc.Suppl.123(2003)167 [hep-ph/0210287];               c
c        Nucl.Phys.Proc.Suppl.116(2003)249 [hep-ph/0211186];               c
c     H.Czyz, A.Grzelinska,                                                c
c        Acta Phys.Polon.B34 (2003) 5219 [hep-ph/0310341];                 c
c        hep-ph/0402030;                                                   c
c     G.Rodrigo,                                                           c
c        hep-ph/0311158;                                                   c
c     H.Czyz, A.Grzelinska, J.H.Kuehn and G.Rodrigo,                       c
c        Nucl.Phys.Proc.Suppl. 131 (2004) 39  [hep-ph/0312217].            c
c     H.Czyz and E. Nowak-Kubat,                                           c
c        Acta Phys.Polon.B34 (2003) 5231 [hep-ph/0310335];                 c
c        Acta Phys.Polon.B36 (2005) 3425 [hep-ph/0510287];                 c 
c        Phys. Lett. B634 (2006) 493 [hep-ph/0601169];                     c
c     H.Czyz, A.Grzelinska and E. Nowak-Kubat,                             c
c        Acta Phys.Polon.B36 (2005) 3403 [ep-ph/0510208];                  c
c     H.Czyz,                                                              c
c        Nucl.Phys.Proc.Suppl. 162 (2006) 76 [hep-ph/0606227];             c  
c ======================================================================== c
c     version 6.0: (c) December 2006, http://ific.uv.es/~rodrigo/phokhara/ c
c ======================================================================== c

      include 'phokhara_6.0.inc'
      double precision qqmin,qqmax,
     &  cos1min,cos1max,cos2min,cos2max,cos3min,cos3max,
     &  dsigm1,dsigm2,sigma1,sigma2,sigma,dsigm,Ar(14),Ar_r(0:13)
      integer nm,i,s_seed(0:104)
      integer*8 nges,k,j
      character outfile*20

c --- reads the seed ------
      open(9,file='seed.dat',type='old')
      read(9,*)s_seed
      call rlxdresetf(s_seed)
cc      call rlxdinit(1,32767)    
c --- input parameters ----------------------------

      call input(nges,nm,outfile)

c --- open output file for generated momenta ------
      if(iprint.ne.0) open (10,file=outfile,type='new')

c --- print run data ------------------------------
      write (*,*) '----------------------------------------------------'
      if (pion.eq.0) then 
         write (*,*) '     PHOKHARA 6.0 : e^+ e^- -> mu^+ mu^- gamma'
      elseif (pion.eq.1) then
         write (*,*) '     PHOKHARA 6.0: e^+ e^- -> pi^+ pi^- gamma'    
      elseif (pion.eq.2) then
         write (*,*) 
     1    '   PHOKHARA 6.0: e^+ e^- -> pi^+ pi^- 2pi^0 gamma'        
      elseif (pion.eq.3) then
         write (*,*) 
     1    '   PHOKHARA 6.0: e^+ e^- -> 2pi^+ 2pi^- gamma' 
      elseif (pion.eq.4) then
         write (*,*) 
     1    '   PHOKHARA 6.0: e^+ e^- -> p pbar gamma' 
      elseif (pion.eq.5) then
         write (*,*) 
     1    '   PHOKHARA 6.0: e^+ e^- -> n nbar gamma'                
      elseif (pion.eq.6) then
         write (*,*) 
     1    '   PHOKHARA 6.0: e^+ e^- -> K^+ K^- gamma'                
      elseif (pion.eq.7) then
         write (*,*) 
     1    '   PHOKHARA 6.0: e^+ e^- -> K_0 K_0bar gamma'                
      elseif (pion.eq.8) then
         write (*,*)
     1    '   PHOKHARA 6.0: e^+ e^- -> pi^+ pi^- pi^0 gamma'                
      elseif (pion.eq.9) then
         write (*,*) 'PHOKHARA 6.0 : e^+ e^- ->'
      write (*,*)'  Lambda (-> pi^- p) Lambda bar (-> pi^+ pbar) gamma'
      else 
         write (*,*) '     PHOKHARA 6.0: not yet implemented'
         stop        
      endif
c --------------------------------
      write (*,*) '----------------------------------------------------'
      write (*,100)   'cms total energy                       = ',
     &                 dSqrt(Sp),' GeV  '
      if (tagged.eq.0) then 
        if((gmin/2.d0/ebeam).lt.0.0098d0)then
             write(*,*)' minimal missing energy set to small'
             stop
        endif
        write (*,100) 'minimal tagged photon energy           = ',
     &                 gmin,' GeV  '
        write (*,110) 'angular cuts on tagged photon          = ',
     &                 phot1cut,',',phot2cut
      else
        if((gmin/2.d0/ebeam).lt.0.0098d0)then
             write(*,*)' minimal missing energy set to small'
             stop
        endif
        write (*,100) 'minimal missing energy                 = ',
     &                 gmin,' GeV  '
        write (*,110) 'angular cuts on missing momentum       = ',
     &                 phot1cut,',',phot2cut      
      endif
c --------------------------------
      if (pion.eq.0) then 
         write (*,110)'angular cuts on muons                  = ',
     &                 pi1cut,',',pi2cut
      elseif (pion.eq.4) then 
         write (*,110)'angular cuts on protons                = ',
     &                 pi1cut,',',pi2cut
      elseif (pion.eq.5) then 
         write (*,110)'angular cuts on neutrons               = ',
     &                 pi1cut,',',pi2cut
      elseif ((pion.eq.6).or.(pion.eq.7)) then 
         write (*,110)'angular cuts on kaons                  = ',
     &                 pi1cut,',',pi2cut
      elseif (pion.eq.9) then 
         write (*,110)'angular cuts on pions and protons      = ',
     &                 pi1cut,',',pi2cut
      else
         write (*,110)'angular cuts on pions                  = ',
     &                 pi1cut,',',pi2cut
      endif
      if (tagged.eq.0) then
         if (pion.eq.0) then  
         write (*,100)'min. muons-tagged photon inv.mass^2    = ',
     &                 q2min,' GeV^2' 
         elseif (pion.eq.4) then  
         write (*,100)'min. protons-tagged photon inv.mass^2  = ',
     &                 q2min,' GeV^2' 
         elseif (pion.eq.5) then  
         write (*,100)'min. neutrons-tagged photon inv.mass^2 = ',
     &                 q2min,' GeV^2' 
         elseif ((pion.eq.6).or.(pion.eq.7)) then  
         write (*,100)'min. kaons-tagged photon inv.mass^2    = ',
     &                 q2min,' GeV^2' 
         elseif (pion.eq.9) then  
         write (*,100)' min. lambdas-tagged photon inv.mass^2 = ',
     &                 q2min,' GeV^2' 
         else
         write (*,100)'min. pions-tagged photon inv.mass^2    = ',	 
     &                 q2min,' GeV^2' 
         endif
      endif
c
c --- book histograms -----------------------------
      call inithisto

c --- set cuts ------------------------------------
      if (tagged.eq.0) then 
      cos1min = dCos(phot2cut*pi/180.d0)     ! photon1 angle cuts in the 
      cos1max = dCos(phot1cut*pi/180.d0)     ! LAB rest frame            
      else
      cos1min = -1.d0                            
      cos1max =  1.d0                                                 
      gmin = gmin/2.d0
      endif
      cos2min = -1.d0                        ! photon2 angle limits      
      cos2max =  1.d0                        !                           
      cos3min = -1.d0                        ! hadrons/muons angle limits    
      cos3max =  1.d0                        ! in their rest frame            
      if (pion.eq.0) then                    ! virtual photon energy cut 
         qqmin = 4.d0*mmu*mmu
      elseif (pion.eq.1) then
         qqmin = 4.d0*mpi*mpi
      elseif (pion.eq.2) then 
         qqmin = 4.d0*(mpi+mpi0)**2
      elseif (pion.eq.3) then 
         qqmin = 16.d0*mpi*mpi
      elseif (pion.eq.4) then 
         qqmin = 4.d0*mp*mp
      elseif (pion.eq.5) then 
         qqmin = 4.d0*mnt*mnt
      elseif (pion.eq.6) then 
         qqmin = 4.d0*mKp*mKp
      elseif (pion.eq.7) then 
         qqmin = 4.d0*mKn*mKn
      elseif (pion.eq.8) then
         qqmin = (2.d0*mpi+mpi0)**2
      elseif (pion.eq.9) then
         qqmin = 4.d0*mlamb*mlamb
      else
         continue
      endif
      qqmax = Sp-2.d0*dSqrt(Sp)*gmin         ! if only one photon 
      if (q2_max_c.lt.qqmax) qqmax=q2_max_c  ! external cuts      
c -------------------
      if ( (q2_min_c.gt.qqmin).and.
     & (q2_min_c.lt. (Sp*(1.d0-2.d0*(gmin/dSqrt(Sp)+w))) ) )then 
          qqmin=q2_min_c
      else
         write(*,*)'------------------------------'
         write(*,*)' Q^2_min TOO SMALL'
         write(*,*)' Q^2_min CHANGE BY PHOKHARA = ',qqmin,' GeV^2'
         write(*,*)'------------------------------'
      endif       
c -------------------
      if(qqmax.le.qqmin)then
         write(*,*)' Q^2_max to small '
         write(*,*)' Q^2_max = ',qqmax
         write(*,*)' Q^2_min = ',qqmin
         stop
      endif
c -------------------
      if (pion.eq.0) then
         write(*,100) 'minimal muon-pair invariant mass^2     = ',
     &                 qqmin,' GeV^2'
         write(*,100) 'maximal muon-pair invariant mass^2     = ',
     &                 qqmax,' GeV^2'
      elseif (pion.eq.1) then
         write(*,100) 'minimal pion-pair invariant mass^2     = ',
     &                 qqmin,' GeV^2'
         write(*,100) 'maximal pion-pair invariant mass^2     = ',
     &                 qqmax,' GeV^2'
      elseif (pion.eq.4) then
         write(*,100) 'minimal proton-pair invariant mass^2   = ',
     &                 qqmin,' GeV^2'
         write(*,100) 'maximal proton-pair invariant mass^2   = ',
     &                 qqmax,' GeV^2'
      elseif (pion.eq.5) then
         write(*,100) 'minimal neutron-pair invariant mass^2  = ',
     &                 qqmin,' GeV^2'
         write(*,100) 'maximal neutron-pair invariant mass^2  = ',
     &                 qqmax,' GeV^2'
      elseif ((pion.eq.6).or.(pion.eq.7)) then
         write(*,100) 'minimal kaon-pair invariant mass^2     = ',
     &                 qqmin,' GeV^2'
         write(*,100) 'maximal kaon-pair invariant mass^2     = ',
     &                 qqmax,' GeV^2'
      elseif(pion.eq.8)then
         write(*,100) 'minimal three-pion invariant mass^2    = ',
     &                 qqmin,' GeV^2'
         write(*,100) 'maximal three-pion invariant mass^2    = ',
     &                 qqmax,' GeV^2'     
      elseif(pion.eq.9)then
         write(*,100) 'minimal lambda-pair invariant mass^2  = ',
     &                 qqmin,' GeV^2'
         write(*,100) 'maximal lambda-pair invariant mass^2  = ',
     &                 qqmax,' GeV^2'     
      else
         write(*,100) 'minimal four-pion invariant mass^2     = ',
     &                 qqmin,' GeV^2'
         write(*,100) 'maximal four-pion invariant mass^2     = ',
     &                 qqmax,' GeV^2'
      endif
c -------------------
      if (nlo.eq.0) then 
         write (*,*) 'Born'
         if(fsrnlo.ne.0)then
           write(*,*)
     1  'WRONG FSRNLO flag - only fsrnlo=0 allowed for Born'
           stop
         endif
      endif
c -------------------
      if((pion.eq.9).and.(nlo.ne.0)) then
        write(*,*)'WRONG NLO flag - only Born allowed for Lambdas'
        write(*,*)'If you feel that you need NLO'
        write(*,*)'please contact the authors'
        stop
      endif
c -------------------
      if (nlo.eq.1) write (*,100) 
     &                'NLO:    soft photon cutoff w           = ',w
      if ((pion.le.1).or.(pion.eq.6)) then
c
      if(((fsr.eq.1).or.(fsr.eq.2)).and.(fsrnlo.eq.0))then
        continue
      elseif((fsr.eq.1).and.(fsrnlo.eq.1))then
        continue
      elseif((fsr.eq.0).and.(fsrnlo.eq.0))then
        continue
      else
        write(*,*)'WRONG combination of FSR, FSRNLO flags'
        stop
      endif
c ------------------
      if (fsr.eq.0) then
         write(*,*) 'ISR only'
      elseif (fsr.eq.1) then
         write(*,*) 'ISR+FSR'
      elseif (fsr.eq.2) then
         if (nlo.eq.0) then
            write(*,*) 'ISR+INT+FSR'
         else
         write(*,*)
     1   'WRONG FSR flag: interference is included only for nlo=0'
         stop
         endif
      else
         write(*,*)'WRONG FSR flag', fsr
         stop
      endif
         if(fsrnlo.eq.1) then
            write(*,*)'IFSNLO included'
         endif
      else
       if((fsr.eq.0).and.(fsrnlo.eq.0))then
         write(*,*)'ISR only'
       else
       write(*,*)'FSR is implemented only for pi+pi-, mu+mu- and K+K-
     1 modes'
       stop
       endif
      endif
c ------------------
      if(ivac.eq.0)then
        write(*,*)'Vacuum polarization is NOT included'
      elseif(ivac.eq.1)then
        write(*,*)'Vacuum polarization is included' 
      else
        write(*,*)'WRONG vacuum polarization switch'
        stop      
      endif
c -----------------
      if(pion.eq.1)then
        if(FF_pion.eq.0)then
          write(*,*)'Kuhn-Santamaria PionFormFactor'
        elseif(FF_pion.eq.1)then
          write(*,*)'Gounaris-Sakurai PionFormFactor'
        else
        write(*,*)'WRONG PionFormFactor switch'
        stop      
        endif
c ------
        if(fsr.ne.0)then
         if(f0_model.eq.0)then
           write(*,*)'f0+f0(600): K+K- model'
         elseif(f0_model.eq.1)then
           write(*,*)'f0+f0(600): "no structure" model'
         elseif(f0_model.eq.2)then
           write(*,*)'NO f0+f0(600)'
         elseif(f0_model.eq.3)then
           write(*,*)'only f0, KLOE: Cesare Bini-private communication'
         else
         write(*,*)'WRONG f0+f0(600) switch'
         stop      
         endif
        endif
      endif
c
c =================================================
c --- finding the maximum -------------------------
      k = nm                        
      do i = 1,2
         Mmax(i) = 1.d0
         gross(i) = 0.d0
         klein(i) = 0.d0      
      enddo 
      if (nlo.eq.0) Mmax(2)=0.d0   ! only 1 photon events generated
      
      do i = 1,2        ! initializing the MC loop
      tr(1) = 0.d0      
      tr(2) = 0.d0
      count(1) = 0.d0
      count(2) = 0.d0

c =================================================
c --- beginning the MC loop event generation ------
      do j = 1,k

         call ranlxdf(Ar_r,1)
         Ar(1) = Ar_r(0)

         if (Ar(1).le.(Mmax(1)/(Mmax(1)+Mmax(2)))) then 
            count(1) = count(1)+1.d0
            call gen_1ph(i,qqmin,qqmax,cos1min,cos1max,
     &	         cos3min,cos3max) 
         else
            count(2) = count(2)+1.d0
            call gen_2ph(i,qqmin,cos1min,cos1max,
     &           cos2min,cos2max,cos3min,cos3max)
         endif
       
      enddo
c --- end of the MC loop --------------------------
c =================================================
c --- for the second run ---
      k = nges
      if (i.eq.1) then
         Mmax(1) = gross(1)+.05d0*Sqrt(gross(1)*gross(1))
         Mmax(2) = gross(2)+(.03d0+.02d0*Sp)*Sqrt(gross(2)*gross(2)) 
c 
         if((pion.eq.1).and.(fsrnlo.eq.1)) Mmax(2)=Mmax(2)*1.5d0
         if((pion.eq.0).and.(fsrnlo.eq.1)) Mmax(2)=Mmax(2)*1.5d0

         if((pion.eq.0).and.(fsr.eq.1).and.(fsrnlo.eq.0)) 
     1                                     Mmax(2)=Mmax(2)*1.2d0
         if((pion.eq.2).or.(pion.eq.3))then
          Mmax(1)=Mmax(1)*1.1d0
          Mmax(2)=Mmax(2)*1.1d0
         endif

         if(pion.eq.8)then
          Mmax(1)=Mmax(1)*1.08d0
          Mmax(2)=Mmax(2)*1.1d0
         endif
      endif

      enddo       
c --- end of the second run -----------------------
c =================================================
      if(pion.eq.9)then
         Mmax(1) = Mmax(1) * (1.d0 + alpha_lamb)**2 * ratio_lamb**2
      endif 
c --- save histograms -----------------------------
      call endhisto()
c --- value of the cross section ------------------
      if (nlo.eq.0) then 
            sigma = Mmax(1)/count(1)*tr(1)
            dsigm = 
     1      Mmax(1)*dSqrt((tr(1)/count(1)-(tr(1)/count(1))**2)/count(1))
      else
            sigma1 = Mmax(1)/count(1)*tr(1)
            sigma2 = Mmax(2)/count(2)*tr(2)
            dsigm1= 
     1      Mmax(1)*dSqrt((tr(1)/count(1)-(tr(1)/count(1))**2)/count(1))
            dsigm2= 
     1      Mmax(2)*dSqrt((tr(2)/count(2)-(tr(2)/count(2))**2)/count(2))

         sigma = sigma1+sigma2
         dsigm = dSqrt(dsigm1**2+dsigm2**2)
      endif
c --- output --------------------------------------
      write (*,*) '----------------------------------------------------'      
      write (*,*) int(tr(1)+tr(2)),' total events accepted of '
      write (*,*) int(nges),       ' total events generated'
      write (*,*) int(tr(1)),      ' one photon events accepted of '
      write (*,*) int(count(1)),   ' events generated'
      write (*,*) int(tr(2)),      ' two photon events accepted of '
      write (*,*) int(count(2)),   ' events generated'
      write (*,*)
      if (nlo.ne.0) write (*,*) 'sigma1(nbarn) = ',sigma1,' +- ',dsigm1
      if (nlo.ne.0) write (*,*) 'sigma2(nbarn) = ',sigma2,' +- ',dsigm2
      write (*,*) 'sigma (nbarn) = ',sigma, ' +- ',dsigm
      write (*,*)
      write (*,*) 'maximum1 = ',gross(1),'  minimum1 = ',klein(1)
      write (*,*) 'Mmax1    = ',Mmax(1)            
      write (*,*) 'maximum2 = ',gross(2),'  minimum2 = ',klein(2)
      write (*,*) 'Mmax2    = ',Mmax(2)            
      write (*,*) '----------------------------------------------------'
 100  format (a42,f10.6,a6)
 110  format (a42,f6.1,a1,f6.1)
c --- saves the new seed --------------------------

      close (9,DISP='delete')
      open(9,file='seed.dat',type='new')

      call rlxdgetf(s_seed)
      write(9,*)s_seed

      end
c!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
c this part contains vacuum polarization procedures taken from
c  http://www-com.physik.hu-berlin.de/fjeger/alphaQEDn.uu
c look also comments in the included file:
c
      include 'vac_pol_hc1.f'
c
c to change to different procedure a user should supply complex*16 function
c dggvap(..,..) with '..' to be real*8, plus possibly also some initialization
c in the procedure 'input'   
c
c!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
c =================================================
c --- print the momenta of the generated event ----
c =================================================
c
c Mode mu^+ mu^- (pion=0)           |  Mode pi^+ pi^-  (pion=1)
c                                   |
c Mode    2pi^0 pi^+ pi^- (pion=2)  |  Mode    2pi^+ 2pi^-     (pion=3)
c q1,q2 - four momenta of pi^0      |  q1,q4 - four momenta of pi^+ 
c q3    - four momentum of pi^-     |  q2,q3 - four momenta of pi^-
c q4    - four momentum of pi^+     |
c                                   |   Mode pi^+ pi^- pi^0 (pion=8)
c Mode    p + pbar (pion=4)         |   q1 - four momentum of pi^+
c Mode    n + nbar (pion=5)         |   q2 - four momentum of pi^-
c Mode    K^+ + K^-(pion=6)         |   q3 - four momentum of pi^0
c Mode    K^0 + K^0bar (pion=7)
c
c Mode  lambda (-> pi^- p) lambda bar (-> pi^+ pbar) (pion=9)

      subroutine writeevent()
      include 'phokhara_6.0.inc'

      write(10,*),'-------------------------------------------'
      write(10,*),'Photon1:',momenta(3,0),momenta(3,1),
     &   momenta(3,2),momenta(3,3)
      write(10,*),'Photon2:',momenta(4,0),momenta(4,1),
     &   momenta(4,2),momenta(4,3)
      if (pion.eq.0) then 
         write(10,*),'Mu+:    ',momenta(6,0),momenta(6,1),
     &      momenta(6,2),momenta(6,3)
         write(10,*),'Mu-:    ',momenta(7,0),momenta(7,1),
     &      momenta(7,2),momenta(7,3)
      elseif(pion.eq.1)then
         write(10,*),'Pi+:    ',momenta(6,0),momenta(6,1),
     &      momenta(6,2),momenta(6,3)
         write(10,*),'Pi-:    ',momenta(7,0),momenta(7,1),
     &      momenta(7,2),momenta(7,3)
      elseif(pion.eq.2)then
         write(10,*),'Pi0:    ',momenta(6,0),momenta(6,1),
     &      momenta(6,2),momenta(6,3)
         write(10,*),'Pi0:    ',momenta(7,0),momenta(7,1),
     &      momenta(7,2),momenta(7,3)
         write(10,*),'Pi-:    ',momenta(8,0),momenta(8,1),
     &      momenta(8,2),momenta(8,3)
         write(10,*),'Pi+:    ',momenta(9,0),momenta(9,1),
     &      momenta(9,2),momenta(9,3)
      elseif(pion.eq.3)then
         write(10,*),'Pi+:    ',momenta(6,0),momenta(6,1),
     &      momenta(6,2),momenta(6,3)
         write(10,*),'Pi-:    ',momenta(7,0),momenta(7,1),
     &      momenta(7,2),momenta(7,3)
         write(10,*),'Pi-:    ',momenta(8,0),momenta(8,1),
     &      momenta(8,2),momenta(8,3)
         write(10,*),'Pi+:    ',momenta(9,0),momenta(9,1),
     &      momenta(9,2),momenta(9,3)
      elseif(pion.eq.4)then
         write(10,*),'Pbar:    ',momenta(6,0),momenta(6,1),
     &      momenta(6,2),momenta(6,3)
         write(10,*),'P:    ',momenta(7,0),momenta(7,1),
     &      momenta(7,2),momenta(7,3)
      elseif(pion.eq.5)then
         write(10,*),'Nbar:    ',momenta(6,0),momenta(6,1),
     &      momenta(6,2),momenta(6,3)
         write(10,*),'N:    ',momenta(7,0),momenta(7,1),
     &      momenta(7,2),momenta(7,3)
      elseif(pion.eq.6)then
         write(10,*),'K+:    ',momenta(6,0),momenta(6,1),
     &      momenta(6,2),momenta(6,3)
         write(10,*),'K-:    ',momenta(7,0),momenta(7,1),
     &      momenta(7,2),momenta(7,3)
      elseif(pion.eq.7)then
         write(10,*),'K0:    ',momenta(6,0),momenta(6,1),
     &      momenta(6,2),momenta(6,3)
         write(10,*),'K0bar:    ',momenta(7,0),momenta(7,1),
     &      momenta(7,2),momenta(7,3)
      elseif(pion.eq.8)then
         write(10,*),'Pi+:    ',momenta(6,0),momenta(6,1),
     &      momenta(6,2),momenta(6,3)
         write(10,*),'Pi-:    ',momenta(7,0),momenta(7,1),
     &      momenta(7,2),momenta(7,3)
         write(10,*),'Pi0:    ',momenta(8,0),momenta(8,1),
     &      momenta(8,2),momenta(8,3)
      elseif(pion.eq.9)then
         write(10,*),'Lambda bar:    ',momenta(6,0),momenta(6,1),
     &      momenta(6,2),momenta(6,3)
         write(10,*),'Lambda:    ',momenta(7,0),momenta(7,1),
     &      momenta(7,2),momenta(7,3)
         write(10,*),'Pi+:    ',momenta(8,0),momenta(8,1),
     &      momenta(8,2),momenta(8,3)
         write(10,*),'Pbar:   ',momenta(9,0),momenta(9,1),
     &      momenta(9,2),momenta(9,3)
         write(10,*),'Pi-:    ',momenta(10,0),momenta(10,1),
     &      momenta(10,2),momenta(10,3)
         write(10,*),'P:    ',momenta(11,0),momenta(11,1),
     &      momenta(11,2),momenta(11,3)
      else
       continue
      endif 
      return
      end
c ======================================================================
c --- generates one photon ---------------------------------------------
c ======================================================================
      subroutine gen_1ph(i,qqmin,qqmax,cos1min,cos1max,
     &                   cos3min,cos3max)
      include 'phokhara_6.0.inc'
      complex*16 Leptonic(0:3,0:3),Hadronic(0:3,0:3)
      double precision qqmin,qqmax,qq,q0p,q2p,q0b,q2b,jac0,
     &  cos1min,cos1max,cos1,phi1,jac1,cos3min,cos3max,cos3,phi3,jac4,
     &  Ar(14),Ar_r(0:13),z,inte,helicityampLO,Matrix,amplit 
      real*8 costhm_ll,phim_ll,costhp_ll,phip_ll
      integer i,ru
      logical accepted      
      common/Lept_ee/Leptonic

      call ranlxdf(Ar_r,7)
      do ru=0,6
       Ar(ru+1)=Ar_r(ru)
      enddo      

c --- get the variables ---------------------------
      call qquadrat(qqmin,qqmax,cos3min,cos3max,Ar
     1,qq,q0p,q2p,q0b,q2b,cos3,phi3,jac0)
      call photonangles1(cos1min,cos1max,Ar,cos1,phi1,jac1)
      z = Mmax(1)*Ar(6)  
             
c --- 4-momenta in the CMS frame ---
      call leptonmomenta1(qq,cos1,phi1)
      call LeptonicTensor1ISR(qq,cos1,Leptonic)
      if((pion.le.1).or.(pion.eq.4).or.(pion.eq.5).or.(pion.eq.6)
     1              .or.(pion.eq.7).or.(pion.eq.9))then
       call hadronmomenta(qq,cos3,phi3)
       call HadronicTensorISR(qq,q0p,q2p,q0b,q2b,Hadronic)
      elseif((pion.eq.2).or.(pion.eq.3))then
       call hadronmomenta_1(4)
       call HadronicTensorISR(qq,q0p,q2p,q0b,q2b,Hadronic)
      elseif(pion.eq.8)then
       call hadronmomenta_1(3)
       call HadronicTensorISR(qq,q0p,q2p,q0b,q2b,Hadronic)
      endif      
      if(pion.eq.9)then
       call pionanglesLamb(cos3min,cos3max,costhm_ll,phim_ll,costhp_ll,
     1                     phip_ll)
       call hadronmomenta_Lamb(qq,cos3,phi3,costhm_ll,phim_ll,costhp_ll,
     1                         phip_ll)
      endif
c --- tests cuts ---
      call testcuts(1,accepted)
c --- value of the integrand ---
      if (accepted) then
c ---
        amplit = Matrix(Leptonic,Hadronic)
        inte = gev2nbarn * amplit * jac0*jac1/(4.d0*pi*Sp)
        if(fsr.ne.0) inte = inte+gev2nbarn*helicityampLO(qq)*
     1               jac0*jac1/(4.d0*pi*Sp)
c ---
         if (inte.gt.gross(1)) gross(1) = inte
         if (inte.lt.klein(1)) klein(1) = inte
c --- in the second rund ---
         if (i.eq.2) then
            if (Mmax(1).lt.inte) write(*,*) 'Warning! Max(1) too small!'
            if (inte.lt.0.d0)    write(*,*) 'Warning! negative weight'
c --- event accepted? ---
            if (z.le.inte) then

               if((pion.eq.9).and.(alpha_lamb.ne.0.d0))then
                  call test_spin(qq,Hadronic,amplit,accepted)
                  if (accepted) then 
                     tr(1) = tr(1) + 1.d0
                     call addiere(1.d0,qq,1)
                  endif
               else
                  tr(1) = tr(1) + 1.d0
                  call addiere(1.d0,qq,1)
               endif

               if (iprint.ne.0) call writeevent()
            endif 
         endif
      else
         inte = 0.d0
      endif
      return
      end
c ======================================================================
c --- generates two photons --------------------------------------------
c ======================================================================
      subroutine gen_2ph(i,qqmin,cos1min,cos1max,
     &   cos2min,cos2max,cos3min,cos3max)
      include 'phokhara_6.0.inc'
      double precision qqmin,qqmax,qq,jac0,q0p,q2p,q0b,q2b,
     &  cos1min,cos1max,cos1,phi1,jac1,sin1,cos12,
     &  cos2min,cos2max,cos2,phi2,jac2,sin2,
     &  w1,w2,w1min,jac3,cos3min,cos3max,cos3,phi3,jac4,
     &  Ar(14),Ar_r(0:13),z,inte,helicityamp
      integer i,ru
      logical accepted      

      call ranlxdf(Ar_r,12)
      do ru=0,11
         Ar(ru+1) = Ar_r(ru)
      enddo
      
c --- get the variables -----------------------------------------------
c --- one of the photons is generated inside the angular cuts and -----
c --- the other is generated everywhere -------------------------------
      if (Ar(12).lt.0.5d0) then
         call photonangles1(cos1min,cos1max,Ar,cos1,phi1,jac1)
         call photonangles2(cos2min,cos2max,Ar,cos2,phi2,jac2)  
         if (cos2.lt.cos1min.or.cos2.gt.cos1max) jac1=2.d0*jac1
       else
         call photonangles1(cos2min,cos2max,Ar,cos1,phi1,jac1)
         call photonangles2(cos1min,cos1max,Ar,cos2,phi2,jac2)  
         if (cos1.lt.cos1min.or.cos1.gt.cos1max) jac2=2.d0*jac2
      endif  
         sin1 = dSqrt(1.d0-cos1*cos1)
         sin2 = dSqrt(1.d0-cos2*cos2)
         cos12 = sin1*sin2*dCos(phi1-phi2)+cos1*cos2
         w1min = gmin/dSqrt(Sp)
         qqmax = Sp*(1.d0-2.d0*(w1min+w)+2.d0*w1min*w*(1.d0-cos12))
         if(q2_max_c.lt.qqmax)qqmax= q2_max_c  ! external cuts         
      call qquadrat2(qqmin,qqmax,Ar,qq,jac0)
      call photonenergy2(qq,cos1min,cos1max,cos1,cos2,cos12
     &                        ,Ar,w1,w2,jac3)
      if((pion.le.1).or.(pion.eq.4).or.(pion.eq.5).or.(pion.eq.6)
     1              .or.(pion.eq.7))then
       call pionangles(cos3min,cos3max,Ar,cos3,phi3,jac4)
      elseif((pion.eq.2).or.(pion.eq.3))then
       call pionangles_1(qq,q0p,q2p,q0b,q2b,jac4)
      elseif(pion.eq.8)then
       call pionangles_2(qq,q0p,q2p,jac4)
      endif      
c
      z = Mmax(2)*Ar(6)         
c       
c --- 4-momenta in the CMS frame ------
      call leptonmomenta2(qq,w1,w2,cos1,phi1,cos2,phi2)
      if((pion.le.1).or.(pion.eq.4).or.(pion.eq.5).or.(pion.eq.6)
     1              .or.(pion.eq.7))then
       call hadronmomenta(qq,cos3,phi3)
      elseif((pion.eq.2).or.(pion.eq.3))then
       call hadronmomenta_1(4)
      elseif(pion.eq.8)then
       call hadronmomenta_1(3)
      endif      
c --- tests cuts ---
      call testcuts(2,accepted)
c --- value of the integrand ---
      if (accepted) then
c --- helicity amplitudes ---
         inte = gev2nbarn*helicityamp(qq,q0p,q2p,q0b,q2b)*
     &       jac0*jac1*jac2*jac3*jac4/(4.d0*pi*Sp)
c ---     
         if (inte.gt.gross(2)) gross(2) = inte
         if (inte.lt.klein(2)) klein(2) = inte
c --- in the second rund ---
         if (i.eq.2) then
            if (Mmax(2).lt.inte) write(*,*) 'Warning! Max(2) too small!'
            if (inte.lt.0.d0)    write(*,*) 'Warning! negative weight'
c --- event accepted? ---
            if (z.le.inte) then
                  tr(2) = tr(2) + 1.d0
               if (iprint.ne.0) call writeevent()
c --- add to the histogrammes ---
               call addiere(1.d0,qq,2)
            endif
         endif
      else
         inte = 0.d0
      endif
      return
      end
c ======================================================================
c --- input parameters -------------------------------------------------
c ======================================================================
      subroutine input(nges,nm,outfile)
      include 'phokhara_6.0.inc'
      integer nm,i
      integer*8 nges
      character outfile*20
      double precision E,lll
      double precision gam1,gam2,coupl,a1m,a1g,rhom_4,rhog_4,
     1       rho1m,rho1g,rho2m,rho2g,omm_4,omg_4,aa,bb1,bb2,f0m,f0g,
     2       pim_4,sgo_pom,sgo,fpi,gfun,rhom2,rho1m2,rho2m2,omm2,rhomg,
     3       rho1mg,rho2mg,ommg,a1m2,con,amrop,gamrop,sig,amrop_2,amropg
      real*8 c_phi0_Kp,c_phi1_Kp,c_rho0_Kp,c_rho1_Kp,c_rho2_Kp,c_om0_Kp
     1      ,c_om1_Kp,c_om2_Kp,c_0_pion,c_1_pion,c_2_pion,c_3_pion
     2      ,c_n_pion,c_om_pion,eta_phi
      real*8 omm0_3pi,omg0_3pi,omm1_3pi,omg1_3pi,omm2_3pi,omg2_3pi,
     1       phim0_3pi,phig0_3pi,rhom0m_3pi,rhog0m_3pi,rhom0p_3pi,
     2       rhog0p_3pi,rhom0z_3pi,rhog0z_3pi,rhom1m_3pi,rhog1m_3pi,
     2       rhom1p_3pi,rhog1p_3pi,rhom1z_3pi,rhog1z_3pi,rhom2m_3pi,
     3       rhog2m_3pi,rhom2p_3pi,rhog2p_3pi,rhom2z_3pi,rhog2z_3pi,
     3       aa_3pi,bb_3pi,dd_3pi,ee_3pi,gg_3pi,jj_3pi,kk_3pi
c
      real*8 betarho_pp, betaomega_pp,betaphi_pp,alphaphi_pp,mrho_pp,
     &       momega_pp,mphi_pp,gammarho_pp,theta_pp,gam_pp
      real*8 mm_ph,gg_ph,Br_phi_ee,mm_f0,gg_f0,c_phi_KK_f0_pi,c_phi_gam
     2      ,mm_f0_600,gg_f0_600,c_phi_KK_f0_600_pi,phas_rho_f0
     3      ,phas_f0_f0600,aa_phi,Br_phi_KK
      real*8 mm_f0_exp,phas_rho_f0_exp,c_f0_KK_exp,c_f0_pipi_exp,
     1       ff_phi_exp,c_phi_KK,rho_phi_exp,lamb_phi_exp
      real*8 mm_phi_lam,mm_om_lam,mu_lamb,phase_f2_lamb
      complex*16 dggvap,phas1,phas2,BW_om
c
      real*8 p1(4),p2(4),dme,el_m2              ! inteface to helicity amp
      common /cp1p2/p1,p2,dme,el_m2
c 4pi commons
      common /had_par/ gam1,gam2,coupl,a1m,a1g,rhom_4,rhog_4,rho1m,rho1g
     1      ,rho2m,rho2g,omm_4,omg_4,aa,bb1,bb2,f0m,f0g,pim_4,sgo
      common /cbwgrho/ rhom2,rho1m2,rho2m2,omm2,rhomg,rho1mg,rho2mg,ommg
      common /cbwga1/ a1m2,con 
      common /anom/amrop,gamrop,sig,amrop_2,amropg
c Proton and Neutron FormFactor common
      common /protparam/ betarho_pp, betaomega_pp,betaphi_pp, 
     &alphaphi_pp,mrho_pp,momega_pp,mphi_pp,gammarho_pp,theta_pp,gam_pp
c Kaons common
      common/param_Kp/c_phi0_Kp,c_phi1_Kp,c_rho0_Kp,c_rho1_Kp,c_rho2_Kp,
     1                c_om0_Kp,c_om1_Kp,c_om2_Kp,eta_phi
c Pi+ Pi- commons
      common/param_pion/c_0_pion,c_1_pion,c_2_pion,c_3_pion,c_n_pion,
     1                  c_om_pion
      common/param_PFF/aa_phi,mm_ph,gg_ph
      common/param_f0/mm_f0,gg_f0,c_phi_KK_f0_pi,c_phi_gam,mm_f0_600,
     1                gg_f0_600,c_phi_KK_f0_600_pi
      common/phases_f0/phas1,phas2
      common/param_f0_exp/mm_f0_exp,phas_rho_f0_exp,c_f0_KK_exp,
     1      c_f0_pipi_exp,ff_phi_exp,c_phi_KK,rho_phi_exp,lamb_phi_exp
c 3pi commons
      common/mass_3pi/omm0_3pi,omg0_3pi,omm1_3pi,omg1_3pi,omm2_3pi,
     1                omg2_3pi,phim0_3pi,phig0_3pi 
      common/rho_3pi/rhom0m_3pi,rhog0m_3pi,rhom0p_3pi,rhog0p_3pi,
     1      rhom0z_3pi,rhog0z_3pi,rhom1m_3pi,rhog1m_3pi,rhom1p_3pi,
     2      rhog1p_3pi,rhom1z_3pi,rhog1z_3pi,rhom2m_3pi,rhog2m_3pi,
     3      rhom2p_3pi,rhog2p_3pi,rhom2z_3pi,rhog2z_3pi
      common/formf_3pi/aa_3pi,bb_3pi,dd_3pi,ee_3pi,gg_3pi,jj_3pi,kk_3pi
c Lambda (Lambda bar) 
      common/lambparam/mm_phi_lam,mm_om_lam,mu_lamb,phase_f2_lamb
c
c --- input file ---------------------------------
      open(7,file='input_6.0.dat',type='old')
      open(8,file='const_and_model_param.dat',type='old')
c --- input generation parameters ----------------
      read(7,*)           !                                   
      read(7,*) nges      ! number of generated events        
      read(7,*) nm        ! events to determine the maximum   
      read(7,*) outfile   ! output file                       
      read(7,*) iprint    ! printing(1), nonprinting(0) generated events
      read(7,*) nlo       ! Born(0), NLO(1)
      read(7,*) w         ! soft photon cutoff                
      read(7,*) pion      ! mu+mu-(0),pi+pi-(1),2pi0pi+pi-(2),2pi+2pi-(3),ppbar(4),nnbar(5),K+K-(6),K0K0bar(7),pi+pi-pi0(8), Lamb Lambbar->pi-pi+ppbar(9) 
      read(7,*) fsr       ! ISR only(0), ISR+FSR(1), ISR+INT+FSR(2)
      read(7,*) fsrnlo    ! yes(1), no(0)
      read(7,*) ivac      ! yes(1), no(0)
      read(7,*) tagged    ! tagged photons(0), untagged photons(1)
      read(7,*) FF_Pion   ! KS Pionformfactor(0), GS Pionformfactor(1)
      read(7,*) f0_model  ! f0+f0(600): KK model(0), no structure(1), no f0+f0(600)(2), f0 KLOE(3)
c --- input collider parameters -------------------
      read(7,*)           !                                   
      read(7,*) E         ! CMS-energy                        
c --- input experimental cuts ---------------------
      read(7,*)           !                                   
      read(7,*) q2min     ! minimal  hadrons(muons)-gamma-inv mass squared     
      read(7,*) q2_min_c  ! minimal inv. mass squared of the hadrons(muons)
      read(7,*) q2_max_c  ! maximal inv. mass squared of the hadrons(muons)
      read(7,*) gmin      ! minimal photon energy/missing energy             
      read(7,*) phot1cut  ! minimal photon angle/missing momentum angle
      read(7,*) phot2cut  ! maximal photon angle/missing momentum angle
      read(7,*) pi1cut    ! minimal hadrons(muons) angle
      read(7,*) pi2cut    ! maximal hadrons(muons) angle
c --- read histogram paremeters -------------------
      read(7,*)           !                                                   
      do i = 1,20         ! read title, limits and bins       
         read(7,*) title(i)
         read(7,*) xlow(i),xup(i),bins(i)
      enddo
c
c --- input couplings, masses and meson widths ---
      read(8,*)           !                                   
      read(8,*) alpha     ! 1/alpha (QED)                     
      read(8,*) me        ! Electron mass   
      read(8,*) mp        ! Proton mass 
      read(8,*) mnt       ! Neutron mass                                      
      read(8,*) mmu       ! Muon mass                         
      read(8,*) mpi       ! Charged pion mass                         
      read(8,*) mpi0      ! Neutral pion mass                         
      read(8,*) mKp       ! Charged kaon mass                         
      read(8,*) mKn       ! Neutral kaon mass                         
      read(8,*) mlamb     ! Lambda mass

c --- fix constants -------------------------------
 
      alpha = 1.d0/alpha
      Sp = E*E                                ! CMS-energy squared
      ebeam = dSqrt(Sp)/2.d0                  ! beam energy
      pi = 4.d0*dAtan(1.d0)   
      gev2nbarn = .389379292d6               ! from GeV^2 to nbarn
      gev2pbarn = .389379292d9

      dme   = me                             ! inteface to helicity amp
      el_m2 = me**2
c
c p1 - positron, p2 - electron four momenta
c
      p1(1) = ebeam
      p1(2) = 0.d0
      p1(3) = 0.d0
      p1(4) = sqrt(ebeam**2-el_m2)
      p2(1) = ebeam
      p2(2) = 0.d0
      p2(3) = 0.d0
      p2(4) = -p1(4)
      do i=1,4
         momenta(1,i-1) = p1(i)
         momenta(2,i-1) = p2(i)
      enddo
      call init_ha
c 
c PDG 2004
c**************************
      read(8,*)
      read(8,*)  mm_ph 
      read(8,*)  gg_ph  
      read(8,*)  Br_phi_ee 
      read(8,*)  Br_phi_KK 
c**************************

      if(ivac.eq.0)then
       cvac_s = dcmplx(1.d0,0.d0)
       cvac_s_pi = dcmplx(1.d0,0.d0)
       cvac_s_phi = dcmplx(0.d0,0.d0)
       aa_phi = 0.d0
      elseif(ivac.eq.1)then
       call constants() 
       if((pion.eq.0).or.(pion.eq.1))then
         cvac_s_pi = 1.d0/(1.d0-dggvap(Sp,0.d0))
         aa_phi = 3.d0 * Br_phi_ee * gg_ph / mm_ph / alpha
         cvac_s_phi = aa_phi * BW_om(mm_ph,gg_ph,Sp,1)      
         if(pion.eq.0)then
            cvac_s = cvac_s_pi - cvac_s_phi
         else
            cvac_s = dcmplx(1.d0,0.d0)
         endif
       else
         cvac_s = 1.d0/(1.d0-dggvap(Sp,0.d0))
         aa_phi = 0.d0
       endif
      else
       write(6,*)'WRONG vac_pol switch'
       stop
      endif
c
c initial state vertex corrections to 1 photon FSR 
c                - constant so calculated here, used for fsrnlo = 1
      ver_s = 0.d0
      if (fsrnlo.eq.1)then
        lll = log(Sp/el_m2)
        ver_s = 2.d0*alpha/pi*( 
     1     (lll-1.d0)*log(2.d0*w) + 0.75d0*lll -1.d0 +pi**2/6.d0)
      endif
c
c 2 pi mode -----------
c
      if(pion.eq.1)then

c -----------------------------------------------------------------
      if(f0_model.eq.0)then
c phi_f0-pipi (K+K- model) Phys.Rev.D56(1997)4084, Phys.Lett.B331(1994)418, 
c                          hep-ph/0001064, Phys.Lett.B611(2005)116
        read(8,*)
        read(8,*) c_phi_gam
        read(8,*) mm_f0
        read(8,*) gg_f0
        read(8,*) c_phi_KK_f0_pi
c phi_f0(600)-pipi
        read(8,*) mm_f0_600
        read(8,*) gg_f0_600
        read(8,*) c_phi_KK_f0_600_pi
c phases : 1. rho and (f0 + f0(600)), 2. f0 and f0(600) 
        read(8,*) phas_f0_f0600
        phas2 = exp(dcmplx(0.d0,phas_f0_f0600*pi/180.d0))
c -----------------------------------------------------------------    
      elseif(f0_model.eq.1)then
c phi_f0-pipi ("no structure" model) hep-ph/0001064
        do i=1,10
           read(8,*) 
        enddo
        read(8,*) c_phi_gam 
        read(8,*) mm_f0
        read(8,*) gg_f0
        read(8,*) c_phi_KK_f0_pi
c phi_f0(600)-pipi
        read(8,*) mm_f0_600 
        read(8,*) gg_f0_600 
        read(8,*) c_phi_KK_f0_600_pi 
c phases : 1. rho and (f0 + f0(600)), 2. f0 and f0(600) 
        read(8,*) phas_rho_f0
        read(8,*) phas_f0_f0600
        phas1 = exp(dcmplx(0.d0,phas_rho_f0*pi/180.d0))
        phas2 = exp(dcmplx(0.d0,phas_f0_f0600*pi/180.d0))
c -----------------------------------------------------------------
      elseif(f0_model.eq.3)then
c KLOE model: mail; hep-ph/9703367; hep-ph/9706363; NP B315,465;
        do i=1,20
           read(8,*) 
        enddo
        read(8,*) mm_f0_exp
        read(8,*) phas_rho_f0_exp
        read(8,*) c_f0_KK_exp
        read(8,*) c_f0_pipi_exp
        ff_phi_exp = sqrt(Br_phi_ee*gg_ph * 3.d0/4.d0/pi/alpha**2
     1                   / mm_ph)  !  \ f_phi

        rho_phi_exp = sqrt(1.d0 - 4.d0*(mKp/mm_ph)**2)
        lamb_phi_exp = log((1.d0+rho_phi_exp)**2 *(mm_ph/mKp)**2/4.d0) 

        c_phi_KK = sqrt( 48.d0 * pi / mm_ph / rho_phi_exp**3
     1           * Br_phi_KK*gg_ph)
      endif

        if(FF_pion.eq.0)then  !------------- KS PionFormFactor ---------
              if(f0_model.eq.0)then
                  do i=1,16
                      read(8,*) 
                  enddo
               elseif(f0_model.eq.1)then
                  do i=1,6
                      read(8,*) 
                  enddo
               elseif(f0_model.eq.2)then
                  do i=1,25
                      read(8,*) 
                  enddo
               elseif(f0_model.eq.3)then
                      read(8,*) 
               endif
           read(8,*) c_0_pion
           read(8,*) c_1_pion
           read(8,*) c_2_pion
           read(8,*) c_3_pion
           read(8,*) c_n_pion
           read(8,*) c_om_pion
           read(8,*) m_rho0_pion
           read(8,*) g_rho0_pion
           read(8,*) m_rho1_pion
           read(8,*) g_rho1_pion
           read(8,*) m_rho2_pion
           read(8,*) g_rho2_pion
           m_rho3_pion = 0.7755d0*sqrt(7.d0)
           g_rho3_pion = 0.2d0*m_rho3_pion
           read(8,*) m_om0_pion
           read(8,*) g_om0_pion
        elseif(FF_pion.eq.1)then  !------------- GS PionFormFactor ---------
               if(f0_model.eq.0)then
                  do i=1,31
                      read(8,*) 
                  enddo
               elseif(f0_model.eq.1)then
                  do i=1,21
                      read(8,*) 
                  enddo
               elseif(f0_model.eq.2)then
                  do i=1,40
                      read(8,*) 
                  enddo
               elseif(f0_model.eq.3)then
                  do i=1,16
                      read(8,*) 
                  enddo
               endif
           read(8,*) c_0_pion
           read(8,*) c_1_pion
           read(8,*) c_2_pion
           read(8,*) c_3_pion
           read(8,*) c_n_pion
           read(8,*) c_om_pion
           read(8,*) m_rho0_pion
           read(8,*) g_rho0_pion
           read(8,*) m_rho1_pion
           read(8,*) g_rho1_pion
           read(8,*) m_rho2_pion
           read(8,*) g_rho2_pion
           m_rho3_pion = 0.7755d0*sqrt(7.d0) !!!
           g_rho3_pion = 0.2d0*m_rho3_pion   !!!
           read(8,*) m_om0_pion
           read(8,*) g_om0_pion     
        endif
      endif
c
c 4 pi mode ------------
c
      if((pion.eq.2).or.(pion.eq.3))then

        if(pion.eq.2)then
          rmass(1)= mpi0
          rmass(2)= mpi0
          rmass(3)= mpi
          rmass(4)= mpi
        elseif(pion.eq.3)then
        do i=1,4
          rmass(i)= mpi
        enddo
        else
         continue
        endif
c
c filling commons for 4pi modes
c
c hadronic current parameters: the pion mass (pim_4) which is fixed below
c                  is used in the parametrisation of the hadronic current 
c                  and NOT in the phasespace generation. As we assume isospin 
c                  invariance pi+ and pi0  masses are equal.  
            do i=1,55
               read(8,*)
            enddo
        read(8,*) gam1
        read(8,*) gam2 
        read(8,*) fpi
          coupl = sqrt(6.d0)/fpi**2  ! normalization change /sqrt(2)
        read(8,*) a1m
        read(8,*) a1g
        read(8,*) rhom_4
        read(8,*) rhog_4 
        read(8,*) rho1m
        read(8,*) rho1g
        read(8,*) rho2m
        read(8,*) rho2g
        read(8,*) omm_4
        read(8,*) omg_4
        read(8,*) aa ! to compare with Finkemeier (no omega)
        read(8,*) bb1 
        read(8,*) bb2 
        read(8,*) f0m
        read(8,*) f0g
        read(8,*) pim_4
        read(8,*) sgo_pom
c       sgo_pom = 1.4d0
        sgo   = sgo_pom/sqrt(2.d0)
        rhom2  = rhom_4**2
        rho1m2 = rho1m**2
        rho2m2 = rho2m**2
        omm2   = omm_4**2
        rhomg  = rhom_4*rhog_4
        rho1mg = rho1m*rho1g
        rho2mg = rho2m*rho2g
        ommg   = omm_4*omg_4
c
        a1m2 = a1m**2
        con  = a1g*a1m/gfun(a1m2)
c
        read(8,*) amrop
        read(8,*) gamrop
        read(8,*) sig
        amrop_2 = amrop**2
        amropg  = amrop*gamrop
      endif
c
c Proton and Neutron formfactors parameters  ---------
c
      if((pion.eq.4).or.(pion.eq.5))then
            do i=1,79
               read(8,*)
            enddo
        read(8,*) betarho_pp
        read(8,*) betaomega_pp
        read(8,*) betaphi_pp
        read(8,*) alphaphi_pp
        read(8,*) mrho_pp
        read(8,*) momega_pp
        read(8,*) mphi_pp
        read(8,*) gammarho_pp 
        theta_pp = pi/4.D0
        read(8,*) gam_pp
      endif
c
c Kaon K+K- mode  and Kaon K0K0bar mode, parameters from hep-ph/0409080
c
      if((pion.eq.6).or.(pion.eq.7))then
            do i=1,89
               read(8,*)
            enddo
        read(8,*) c_phi0_Kp
        read(8,*) c_phi1_Kp
        read(8,*) c_rho0_Kp
        read(8,*) c_rho1_Kp
        read(8,*) c_rho2_Kp
        read(8,*) c_om0_Kp
        read(8,*) c_om1_Kp
        read(8,*) c_om2_Kp
        read(8,*) m_phi0_Kp
        read(8,*) g_phi0_Kp
        read(8,*) m_phi1_Kp
        read(8,*) g_phi1_Kp
        read(8,*) m_om0_Kp
        read(8,*) g_om0_Kp
        read(8,*) m_om1_Kp
        read(8,*) g_om1_Kp
        read(8,*) m_om2_Kp
        read(8,*) g_om2_Kp
        read(8,*) m_rho0_Kp
        read(8,*) g_rho0_Kp
        read(8,*) m_rho1_Kp
        read(8,*) g_rho1_Kp
        read(8,*) m_rho2_Kp
        read(8,*) g_rho2_Kp

        read(8,*) eta_phi ! only for K0 K0bar
      endif
c
c 3 pi mode ---------
c
      if(pion.eq.8)then
        rmass(1) = mpi
        rmass(2) = mpi
        rmass(3) = mpi0

c ----------------------------------------------
c rho_0 +\rho_1*phi + om_2*rho_2 +  fixed rho*omega(full form of Czyz+Kuhn 
c Eur.Phys.J.C18(2001)497);
c    constrained fit
c    chi^2= 320.870727
c
            do i=1,115
               read(8,*)
            enddo
        read(8,*) omm0_3pi
        read(8,*) omg0_3pi
        read(8,*) omm1_3pi
        read(8,*) omg1_3pi         
        read(8,*) omm2_3pi
        read(8,*) omg2_3pi
        read(8,*) phim0_3pi
        read(8,*) phig0_3pi

        read(8,*) rhom0m_3pi  ! - 
        read(8,*) rhog0m_3pi  ! -
        read(8,*) rhom0p_3pi  ! + 
        read(8,*) rhog0p_3pi  ! +
        read(8,*) rhom0z_3pi  ! 0
        read(8,*) rhog0z_3pi  ! 0
        read(8,*) rhom1m_3pi  ! -
        read(8,*) rhog1m_3pi  ! -
        read(8,*) rhom1p_3pi  ! + 
        read(8,*) rhog1p_3pi  ! + 
        read(8,*) rhom1z_3pi  ! 0
        read(8,*) rhog1z_3pi  ! 0
        read(8,*) rhom2m_3pi  ! -
        read(8,*) rhog2m_3pi  ! -
        read(8,*) rhom2p_3pi  ! + 
        read(8,*) rhog2p_3pi  ! + 
        read(8,*) rhom2z_3pi  ! 0
        read(8,*) rhog2z_3pi  ! 0

        read(8,*) aa_3pi
        read(8,*) bb_3pi
        read(8,*) dd_3pi
        read(8,*) ee_3pi
c
        gg_3pi  = 1.d0/sqrt(2.d0) *1.55d0 *12.924d0 *0.266d0
     1        * 0.1846845502d0*0.77609d0**2
c
        read(8,*) jj_3pi
        read(8,*) kk_3pi
      endif
c
c Lambda (-> pi^- p) Lambda bar (-> pi^+ pbar)  parameters  ---------
c
      if(pion.eq.9)then
            do i=1,148
               read(8,*)
            enddo 
        read(8,*) mm_phi_lam
        read(8,*) mm_om_lam
        read(8,*) mu_lamb
        read(8,*) alpha_lamb
        read(8,*) phase_f2_lamb
        read(8,*) ratio_lamb
c
      endif
c
      return
      end
c***********************************************************************
      subroutine init_ha
      implicit none
      complex*16 qpl(2,2),qmi(2,2),gampl(2,2),gammi(2,2),k1pl(2,2),
     1           k1mi(2,2),k2pl(2,2),k2mi(2,2),eck1pl(2,2),eck1mi(2,2),
     2        eck2pl(2,2),eck2mi(2,2),I(2,2),sigpl(4,2,2),sigmi(4,2,2), 
     3        gampl_ma(2,2),gammi_ma(2,2)
      integer i1,i2,i3
c
      common/matri/qpl,qmi,gampl,gammi,k1pl,k1mi,k2pl,k2mi,eck1pl,
     1             eck1mi,eck2pl,eck2mi,I,sigpl,sigmi,gampl_ma,gammi_ma
c
      I(1,1)=dcmplx(1.d0,0.d0)
      I(1,2)=dcmplx(0.d0,0.d0)
      I(2,1)=dcmplx(0.d0,0.d0)
      I(2,2)=dcmplx(1.d0,0.d0)
c
      do i1 = 1,2
       do i2 = 1,2
        sigpl(1,i1,i2) = I(i1,i2)
        sigmi(1,i1,i2) = I(i1,i2)
       enddo
      enddo
c
      do i1 = 1,2
       sigpl(2,i1,i1)=dcmplx(0.d0,0.d0)
       sigpl(3,i1,i1)=dcmplx(0.d0,0.d0)
       sigpl(4,i1,i1)=dcmplx((-1.d0)**(i1+1),0.d0)
      enddo
c
       sigpl(2,1,2)=dcmplx(1.d0,0.d0)
       sigpl(2,2,1)=dcmplx(1.d0,0.d0)
       sigpl(3,1,2)=dcmplx(0.d0,-1.d0)
       sigpl(3,2,1)=dcmplx(0.d0,1.d0)
       sigpl(4,1,2)=dcmplx(0.d0,0.d0)
       sigpl(4,2,1)=dcmplx(0.d0,0.d0)
c
      do i3 = 2,4
       do i1 = 1,2
        do i2 = 1,2
         sigmi(i3,i1,i2) = -sigpl(i3,i1,i2)
        enddo
       enddo
      enddo
      return
      end 
c ========================================================================
c ------------------------------------------------------------------------
c --- Generates: photon virtuality Q2 using a two-component substitution -
c used in one photon emission
c ------------------------------------------------------------------------
      subroutine qquadrat(qqmin,qqmax,cosmin,cosmax,Ar
     1,qq,q0p,q2p,q0b,q2b,costheta,phi,jacobian)
      include 'phokhara_6.0.inc'
      double precision qqmin,qqmax,Ar(14),qq,jacobian,fak1c,
     &  x,a,b,c,amin,amax,bmin,bmax,fak1,fak2,p,y,ppp,jac4,vv,eqt,
     &  cosmin,cosmax,costheta,phi,delcos,vol1,vol2,vol3,cmin,cmax,
     &  delyy,yy,ymin,ea,q0p,q2p,q0b,q2b
      real*8 pionFF,dps
      
      x = Ar(1)      
c
c --- muons -----------------------------------------------------
c --- the Q2 distribution is peaked at threshold and Q2->Sp (soft photon). 
      if (pion.eq.0) then
c
c  isr only
      if(fsr.eq.0)then
      fak1 = -1.d0/Sp
      amin = fak1*dLog(Sp-qqmin)
      amax = fak1*dLog(Sp-qqmax)
      a = amax-amin
      bmin = dLog(qqmin/Sp)/Sp
      b    = dLog(qqmax/qqmin)/Sp
c --- which substitution? ---
      p = Ar(7)      
      ppp  = a/(a+b)
      if(p.lt.ppp)then
         y  = amin+a*x
         qq = Sp-dExp(y/fak1)                                       
      else
         y  = bmin+b*x
         qq = Sp*exp(Sp*y)
      endif
      jacobian = (a+b)/(1.d0/(Sp*(Sp-qq)) + 1.d0/Sp/qq)  
c
      call pionangles(cosmin,cosmax,Ar,costheta,phi,jac4)
c
      jacobian = jacobian*jac4      
c
c isr+fsr+int
      else
c
      fak1 = -1.d0/Sp
      amin = fak1*dLog(Sp-qqmin)
      a = fak1 *dLog((Sp-qqmax)/(Sp-qqmin))
      delcos = (cosmax-cosmin)
      vol1 = a*delcos
c
      bmin = dLog(qqmin/Sp)/Sp
      b    = dLog(qqmax/qqmin)/Sp
      vol2 = b*delcos
c
      vv = sqrt(1.d0-4.d0*mpi**2/Sp)
      delyy = log((1.d0+vv*cosmax)*(1.d0-vv*cosmin)
     1          /(1.d0-vv*cosmax)/(1.d0+vv*cosmin)) /vv
      vol3 = a*delyy 
c
      phi = 2.d0*pi*Ar(5)
c
c --- three channels ---
c 1. soft photon + angles flat
c 2.  1/q2       + angles flat
c 3. soft photon + angles fsr collinear
c
      p = Ar(7)      
      ppp  = vol1/(vol1+vol2+vol3)
      if(p.lt.ppp)then
         y  = amin+a*x
         qq = Sp-dExp(y/fak1)                                       
         costheta = cosmin+delcos*Ar(4)
      elseif(p.lt.((vol1+vol2)/(vol1+vol2+vol3)))then
         y  = bmin+b*x
         qq = Sp*exp(Sp*y)
         costheta = cosmin+delcos*Ar(4)
      else
         y  = amin+a*x
         qq = Sp-dExp(y/fak1) 
         ymin = log((1.d0+vv*cosmin)/(1.d0-vv*cosmin)) /vv
         yy = ymin + delyy *Ar(4)
         ea = exp(vv*yy)
         costheta = (ea-1.d0)/(1.d0+ea)/vv
      endif
c
      jacobian = 2.d0*pi*(vol1+vol2+vol3)/( (1.d0/(Sp*(Sp-qq)) +
     &     1.d0/Sp/qq) 
     &    +1.d0/(Sp*(Sp-qq))
     &  * (1.d0/(1.d0-vv*costheta)+1.d0/(1.d0+vv*costheta)) )
c
      endif
c
c --- 2 pions -----------------------------------------------------
c --- the Q2 distribution is peaked at Q2=rho and w mass^2       
c --- resonances (pion form factor) and at Q2->Sp (soft photon). 
c
      elseif(pion.eq.1)then
c
c  isr only
      if(fsr.eq.0)then
c
        call qquadrat_1(qqmin,qqmax,x,Ar(7),
     1                           m_rho0_pion,g_rho0_pion,qq,jacobian)
c
        call pionangles(cosmin,cosmax,Ar,costheta,phi,jac4)
c
      jacobian = jacobian*jac4      
c
c isr+fsr+int
      else
c
      fak1 = -1.d0/Sp
      amin = fak1*dLog(Sp-qqmin)
      a = fak1 *dLog((Sp-qqmax)/(Sp-qqmin))
      delcos = (cosmax-cosmin)
      vol1 = a*delcos
c
      fak2 = 1.d0/g_rho0_pion/m_rho0_pion
      bmin = fak2*dAtan((qqmin-m_rho0_pion**2)*fak2)
      bmax = fak2*dAtan((qqmax-m_rho0_pion**2)*fak2)
      b = bmax-bmin
      vol2 = b*delcos
c
      vv = sqrt(1.d0-4.d0*mpi**2/Sp)
      delyy = log((1.d0+vv*cosmax)*(1.d0-vv*cosmin)
     1          /(1.d0-vv*cosmax)/(1.d0+vv*cosmin)) /vv
      vol3 = a*delyy 
c
      phi = 2.d0*pi*Ar(5)
c
c --- three channels ---
c 1. soft photon + angles flat
c 2. BW q2       + angles flat
c 3. soft photon + angles fsr collinear
c
      p = Ar(7)      
      ppp  = vol1/(vol1+vol2+vol3)
      if(p.lt.ppp)then
         y  = amin+a*x
         qq = Sp-dExp(y/fak1)                                       
         costheta = cosmin+delcos*Ar(4)
      elseif(p.lt.((vol1+vol2)/(vol1+vol2+vol3)))then
         y  = bmin+b*x
         qq = m_rho0_pion*(m_rho0_pion+g_rho0_pion*dTan(y/fak2))                    
         costheta = cosmin+delcos*Ar(4)
      else
         y  = amin+a*x
         qq = Sp-dExp(y/fak1) 
         ymin = log((1.d0+vv*cosmin)/(1.d0-vv*cosmin)) /vv
         yy = ymin + delyy *Ar(4)
         ea = exp(vv*yy)
         costheta = (ea-1.d0)/(1.d0+ea)/vv
      endif
c
      jacobian = 2.d0*pi*(vol1+vol2+vol3)/( (1.d0/(Sp*(Sp-qq)) +
     &     1.d0/(((qq-m_rho0_pion**2)**2+(g_rho0_pion*m_rho0_pion)**2))) 
     &    +1.d0/(Sp*(Sp-qq))
     &  * (1.d0/(1.d0-vv*costheta)+1.d0/(1.d0+vv*costheta)) )
c
      endif
c
c --- 4 pions -----------------------------------------------------
      elseif((pion.eq.2).or.(pion.eq.3))then
        call qquadrat_1(qqmin,qqmax,x,Ar(7),1.5d0,0.5d0,qq,jacobian)
c
       call pionangles_1(qq,q0p,q2p,q0b,q2b,jac4)
      jacobian = jacobian*jac4      
c
c----PPbar and NNbar----------------------------------------------
      elseif((pion.eq.4).or.(pion.eq.5)) then 
      fak1 = -1.d0/Sp
      amin = fak1*dLog(Sp-qqmin)
      amax = fak1*dLog(Sp-qqmax)
      a = amax-amin
      bmin = dLog(qqmin/Sp)/Sp
      b    = dLog(qqmax/qqmin)/Sp
c --- which substitution? ---
      p = Ar(7)      
      ppp  = a/(a+b)
      if(p.lt.ppp)then
         y  = amin+a*x
         qq = Sp-dExp(y/fak1)                                       
      else
         y  = bmin+b*x
         qq = Sp*exp(Sp*y)
      endif
      jacobian = (a+b)/(1.d0/(Sp*(Sp-qq)) + 1.d0/Sp/qq)  
c
      call pionangles(cosmin,cosmax,Ar,costheta,phi,jac4)
c
      jacobian = jacobian*jac4 
c 
c ---- K^+K^- and K0K0bar---------------------------------------------
      elseif((pion.eq.6).or.(pion.eq.7))then

      fak1 = -1.d0/Sp
      amin = fak1*dLog(Sp-qqmin)
      amax = fak1*dLog(Sp-qqmax)
      a = amax-amin
      fak2 = 1.d0/g_phi0_Kp/m_phi0_Kp
      bmin = fak2*dAtan((qqmin-m_phi0_Kp**2)*fak2)
      bmax = fak2*dAtan((qqmax-m_phi0_Kp**2)*fak2)
      b = bmax-bmin
      cmin = dLog(qqmin/Sp)*Sp
      c = dLog(qqmax/qqmin)*Sp
c --- three channels ---
c  1.  1/Sp/(Sp-qq)
c  2.  BW
c  3.  Sp/qq
      p = Ar(7)      
      ppp  = a/(a+b+c)
c
      if(p.lt.ppp)then
         y  = amin+a*x
         qq = Sp-dExp(y/fak1)                                       
      elseif(p.lt.((a+b)/(a+b+c)))then
         y  = bmin+b*x
         qq = m_phi0_Kp*(m_phi0_Kp+g_phi0_Kp*dTan(y/fak2))
      else
         y  = cmin+c*x
         qq = Sp*exp(y/Sp)
      endif

      jacobian = (a+b+c)/( (1.d0/(Sp*(Sp-qq)) +
     &     1.d0/(((qq-m_phi0_Kp**2)**2+(g_phi0_Kp*m_phi0_Kp)**2))) +
     2     1.d0/(qq/Sp) )
c
      call pionangles(cosmin,cosmax,Ar,costheta,phi,jac4)
c
      jacobian = jacobian*jac4      
c       
c --- 3 pions -----------------------------------------------------
c
      elseif(pion.eq.8)then
       call qquadrat_2(qq,qqmax,qqmin,x,Ar(7),jac4)  
       call pionangles_2(qq,q0p,q2p,jacobian)
c
       jacobian = jacobian*jac4
c
c--- Lambda (Lambda bar) -------------------------
      elseif(pion.eq.9) then 
      fak1 = -1.d0/Sp
      amin = fak1*dLog(Sp-qqmin)
      amax = fak1*dLog(Sp-qqmax)
      a = amax-amin
      bmin = dLog(qqmin/Sp)/Sp
      b    = dLog(qqmax/qqmin)/Sp
c --- which substitution? ---
      p = Ar(7)      
      ppp  = a/(a+b)
      if(p.lt.ppp)then
         y  = amin+a*x
         qq = Sp-dExp(y/fak1)                                       
      else
         y  = bmin+b*x
         qq = Sp*exp(Sp*y)
      endif
      jacobian = (a+b)/(1.d0/(Sp*(Sp-qq)) + 1.d0/Sp/qq)  
c
      call pionangles(cosmin,cosmax,Ar,costheta,phi,jac4)

      pionFF = 4.d0*pi*alpha
      dps = dSqrt(1.d0-4.d0*mlamb*mlamb/qq)/(32.d0*pi*pi)!Phase space factors

      jacobian = jacobian * jac4 * pionFF * dps

      else
       continue
      endif
      return
      end
c ========================================================================
c --- Generates: photon virtuality Q2 using a two-component substitution -
c used in 2 photon part
c ------------------------------------------------------------------------
      subroutine qquadrat2(qqmin,qqmax,Ar,qq,jacobian)
      include 'phokhara_6.0.inc'
      double precision qqmin,qqmax,Ar(14),qq,jacobian,x,a,b,amin,amax
     1      ,bmin,bmax,fak1,fak2,p,y,ppp,c,cmin,d,dmin,dmax,fak3,mm_1,
     2      gg_1,const_1,const_2

      x = Ar(1)      
c --- flat ---
c      a = qqmax-qqmin
c      qq = qqmin+a*x
c      jacobian = a

c --- muons -----------------------------------------------------
c --- the Q2 distribution is peaked at threshold and Q2->Sp (soft photon). 
      if (pion.eq.0) then
      fak1 = -1.d0/Sp
      amin = fak1*dLog(Sp-qqmin)
      amax = fak1*dLog(Sp-qqmax)
      a = amax-amin
      bmin = dLog(qqmin/Sp)/Sp
      b    = dLog(qqmax/qqmin)/Sp
c --- which substitution? ---
      p = Ar(7)      
      ppp  = a/(a+b)
      if(p.lt.ppp)then
         y  = amin+a*x
         qq = Sp-dExp(y/fak1)                                       
      else
         y  = bmin+b*x
         qq = Sp*exp(Sp*y)
      endif
      jacobian = (a+b)/(1.d0/(Sp*(Sp-qq)) + 1.d0/Sp/qq)  
c --- 2 pions -----------------------------------------------------
c --- the Q2 distribution is peaked at Q2=rho and w mass^2       
c --- resonances (pion form factor) and at Q2->Sp (soft photon). 
      elseif(pion.eq.1)then
        call qquadrat_1(qqmin,qqmax,x,Ar(7),
     1                          m_rho0_pion,g_rho0_pion,qq,jacobian)
c
c --- 4 pions -----------------------------------------------------
      elseif((pion.eq.2).or.(pion.eq.3))then
        call qquadrat_1(qqmin,qqmax,x,Ar(7),1.5d0,0.5d0,qq,jacobian)
c
c-------- PPbar and NNbar ------------------------------------------
      elseif ((pion.eq.4).or.(pion.eq.5)) then
      fak1 = -1.d0/Sp
      amin = fak1*dLog(Sp-qqmin)
      amax = fak1*dLog(Sp-qqmax)
      a = amax-amin
      bmin = dLog(qqmin/Sp)/Sp
      b    = dLog(qqmax/qqmin)/Sp
c --- which substitution? ---
      p = Ar(7)      
      ppp  = a/(a+b)
      if(p.lt.ppp)then
         y  = amin+a*x
         qq = Sp-dExp(y/fak1)                                       
      else
         y  = bmin+b*x
         qq = Sp*exp(Sp*y)
      endif
      jacobian = (a+b)/(1.d0/(Sp*(Sp-qq)) + 1.d0/Sp/qq)  
c 
c ---- K^+K^- and K0K0bar ---------------------------------------------
      elseif((pion.eq.6).or.(pion.eq.7))then

      fak1 = -1.d0/Sp
      amin = fak1*dLog(Sp-qqmin)
      amax = fak1*dLog(Sp-qqmax)
      a = amax-amin
c -----------
      const_2 = 2.d0
      fak2 = 1.d0/g_phi0_Kp/m_phi0_Kp
      bmin = const_2*fak2*dAtan((qqmin-m_phi0_Kp**2)*fak2)
      bmax = const_2*fak2*dAtan((qqmax-m_phi0_Kp**2)*fak2)
      b = bmax-bmin
c -----------
      cmin = dLog(qqmin/Sp)*Sp
      c = dLog(qqmax/qqmin)*Sp
c ------------
      const_1 = 10.d0
      mm_1 = 1.05d0
      gg_1 = 0.05d0
      fak3 = 1.d0/gg_1/mm_1
      dmin = const_1*fak3*dAtan((qqmin-mm_1**2)*fak3)
      dmax = const_1*fak3*dAtan((qqmax-mm_1**2)*fak3)
      d = dmax-dmin
c --- four channels ---
c  1.  1/Sp/(Sp-qq)
c  2.  BW m_phi0_Kp
c  3.  Sp/qq
c  4.  BW mm_1
      p = Ar(7)      
      ppp  = a+b+c+d
c
      if(p.lt.a/ppp)then
         y  = amin+a*x
         qq = Sp-dExp(y/fak1)                                       
      elseif(p.lt.((a+b)/ppp))then
         y  = bmin+b*x
         qq = m_phi0_Kp*(m_phi0_Kp+g_phi0_Kp*dTan(y/fak2/const_2))
      elseif(p.lt.((a+b+c)/ppp))then
         y  = cmin+c*x
         qq = Sp*exp(y/Sp)
      else
         y  = dmin+d*x
         qq = mm_1*(mm_1+gg_1*dTan(y/fak3/const_1))
      endif

      jacobian = ppp/( 1.d0/(Sp*(Sp-qq)) +
     &     const_2/(((qq-m_phi0_Kp**2)**2+(g_phi0_Kp*m_phi0_Kp)**2)) +
     2     1.d0/(qq/Sp) +
     3     const_1/((qq-mm_1**2)**2+(gg_1*mm_1)**2)  )
c
c --- 3 pions -----------------------------------------------------
c
      elseif(pion.eq.8)then
       call qquadrat_2a(qq,qqmax,qqmin,x,Ar(7),jacobian)  
      else
       continue
      endif
c
      return
      end
c *******************************************************************
c
      subroutine qquadrat_1(qqmin,qqmax,x,p,mmm,ggg,qq,jacobian)
      include 'phokhara_6.0.inc'
      double precision qqmin,qqmax,Ar(14),qq,jacobian,mmm,ggg,
     &  x,a,b,amin,amax,bmin,bmax,fak1,fak2,p,y,ppp
c
      fak1 = -1.d0/Sp
      amin = fak1*dLog(Sp-qqmin)
      amax = fak1*dLog(Sp-qqmax)
      a = amax-amin
      fak2 = 1.d0/ggg/mmm
      bmin = fak2*dAtan((qqmin-mmm**2)*fak2)
      bmax = fak2*dAtan((qqmax-mmm**2)*fak2)
      b = bmax-bmin
c --- two channels ---
      ppp  = a/(a+b)
c
      if(p.lt.ppp)then
         y  = amin+a*x
         qq = Sp-dExp(y/fak1)                                       
      else
         y  = bmin+b*x
         qq = mmm*(mmm+ggg*dTan(y/fak2))                    
      endif
      jacobian = (a+b)/( (1.d0/(Sp*(Sp-qq)) +
     &     1.d0/(((qq-mmm**2)**2+(ggg*mmm)**2))) )
c
      return
      end
c ---------------------------------------------------------------------
c   3 pi 1ph
c ---------------------------------------------------------------------

      subroutine qquadrat_2(qq,qqmax,qqmin,x,p,jac)
      include 'phokhara_6.0.inc'

      real*8 jac,xx_om0_max,xx_om0_min,xx_om1_max,xx_om1_min,
     1   xx_phi0_max,xx_phi0_min,xx_ss_max,xx_ss_min,d_om0,d_om1,d_phi0,
     2   d_ss,vv_3pi,yy_3pi,const_1,const_2,const_3,const_ss
      real*8 qq,qqmax,qqmin,x,p,aa,omm1_3pi_BW,omg1_3pi_BW,omm0_3pi,
     1   omg0_3pi,omm1_3pi,omg1_3pi,omm2_3pi,omg2_3pi,phim0_3pi,
     2   phig0_3pi,mm_1_p,mg_1_p,const_1_p,xx_1_p_min,xx_1_p_max,
     3   d_1_p,mm_2_p,mg_2_p,const_2_p,xx_2_p_min,xx_2_p_max,d_2_p,
     4   const_om2,xx_om2_max,xx_om2_min,d_om2

      common /mass_3pi/ omm0_3pi,omg0_3pi,omm1_3pi,omg1_3pi,omm2_3pi,
     1                  omg2_3pi,phim0_3pi,phig0_3pi 

c \om_0 -----------------------------
      if(Sp.lt.25.d0)then
       const_1 = 1000.d0*(omg0_3pi/omm0_3pi)**2
      else
       const_1 = 410000.d0*(omg0_3pi/omm0_3pi)**2
      endif

      xx_om0_max = const_1*omm0_3pi**3/omg0_3pi * 
     1             dAtan((qqmax/omm0_3pi**2-1.d0)*omm0_3pi/omg0_3pi)
      xx_om0_min = const_1*omm0_3pi**3/omg0_3pi * 
     1             dAtan((qqmin/omm0_3pi**2-1.d0)*omm0_3pi/omg0_3pi)
      d_om0 = xx_om0_max - xx_om0_min 

c \phi_0 -----------------------------
      if(Sp.lt.25.d0)then
       const_2 =  20000.d0*(phig0_3pi/phim0_3pi)**2
      else
       const_2 =  240000.d0*(phig0_3pi/phim0_3pi)**2 
      endif

      xx_phi0_max = const_2*phim0_3pi**3/phig0_3pi * 
     1            dAtan((qqmax/phim0_3pi**2-1.d0)*phim0_3pi/phig0_3pi)
      xx_phi0_min = const_2*phim0_3pi**3/phig0_3pi * 
     1            dAtan((qqmin/phim0_3pi**2-1.d0)*phim0_3pi/phig0_3pi)
      d_phi0 = xx_phi0_max - xx_phi0_min

c \om_1 ----- only for sqrt(s) = 10.52  \Gamma_om_1 = omg1 * 2
      const_3 = 6500.d0*(2.d0*omg1_3pi/omm1_3pi)**2

      xx_om1_max = const_3*omm1_3pi**3/(2.d0*omg1_3pi) * 
     1   dAtan((qqmax/omm1_3pi**2-1.d0)*omm1_3pi/(2.d0*omg1_3pi))
      xx_om1_min = const_3*omm1_3pi**3/2.d0/omg1_3pi * 
     1   dAtan((qqmin/omm1_3pi**2-1.d0)*omm1_3pi/2.d0/omg1_3pi)
      d_om1 = xx_om1_max - xx_om1_min

c Sp/(Sp-qq) ----------------------------
       xx_ss_max = -Sp * dLog((Sp-qqmax)/Sp) 
       xx_ss_min = -Sp * dLog((Sp-qqmin)/Sp)
       d_ss = xx_ss_max - xx_ss_min

c--------------------------------------
      if(Sp.lt.25.d0)then

       const_ss = 1.d0
      else      
       const_ss = 22.5d0
      endif

      aa = const_ss*(qqmax - qqmin)

c      qq = qqmin + x * aa
c      jac = aa
c --------------------------------------

      if(Sp.lt.25.d0)then

       vv_3pi = aa + d_ss + d_om0 + d_phi0

      if(p.lt.(d_ss/vv_3pi))then
          yy_3pi = xx_ss_min + x * d_ss
          qq = Sp * ( 1.d0 - dExp(-yy_3pi/Sp))
      elseif(p.lt.((d_om0+d_ss)/vv_3pi))then
         yy_3pi = xx_om0_min + x * d_om0
         qq = omg0_3pi*omm0_3pi 
     2      * dTan(yy_3pi*omg0_3pi/omm0_3pi**3/const_1)
     1      + omm0_3pi**2
      elseif(p.lt.((d_om0+d_phi0+d_ss)/vv_3pi))then
         yy_3pi = xx_phi0_min + x * d_phi0
         qq = phig0_3pi*phim0_3pi 
     2      * dTan(yy_3pi*phig0_3pi/phim0_3pi**3/const_2)
     1      + phim0_3pi**2
      else
          qq = qqmin + x * aa/const_ss
      endif

      jac = vv_3pi/(const_ss + Sp/(Sp-qq) + 
     3  const_1/((qq/omm0_3pi**2-1.d0)**2+(omg0_3pi/omm0_3pi)**2) +
     2  const_2/((qq/phim0_3pi**2-1.d0)**2+(phig0_3pi/phim0_3pi)**2))

      else
 
       vv_3pi = d_ss + d_om0 + d_phi0 + aa + d_om1  

      if(p.lt.(d_ss/vv_3pi))then
          yy_3pi = xx_ss_min + x * d_ss
          qq = Sp * ( 1.d0 - dExp(-yy_3pi/Sp))
      elseif(p.lt.((d_om0+d_ss)/vv_3pi))then
         yy_3pi = xx_om0_min + x * d_om0
         qq = omg0_3pi*omm0_3pi 
     2      * dTan(yy_3pi*omg0_3pi/omm0_3pi**3/const_1)
     1      + omm0_3pi**2
      elseif(p.lt.((d_om0+d_phi0+d_ss)/vv_3pi))then
         yy_3pi = xx_phi0_min + x * d_phi0
         qq = phig0_3pi*phim0_3pi 
     2      * dTan(yy_3pi*phig0_3pi/phim0_3pi**3/const_2)
     1      + phim0_3pi**2
      elseif(p.lt.((d_om0+d_phi0+d_ss+d_om1)/vv_3pi))then
         yy_3pi = xx_om1_min + x * d_om1  
         qq = 2.d0*omg1_3pi*omm1_3pi*dTan(yy_3pi*2.d0*omg1_3pi/
     1            omm1_3pi**3/const_3) + omm1_3pi**2
      else
          qq = qqmin + x * aa/const_ss
      endif

      jac = vv_3pi/( const_ss + Sp/(Sp-qq) + 
     3  const_1/((qq/omm0_3pi**2-1.d0)**2+(omg0_3pi/omm0_3pi)**2) +
     2  const_2/((qq/phim0_3pi**2-1.d0)**2+(phig0_3pi/phim0_3pi)**2)+ 
     1  const_3/((qq/omm1_3pi**2-1.d0)**2
     4                            +(2.d0*omg1_3pi/omm1_3pi)**2) )

      endif

      return
      end
c ---------------------------------------------------------------------
c   3 pi 2ph
c ---------------------------------------------------------------------

      subroutine qquadrat_2a(qq,qqmax,qqmin,x,p,jac)
      include 'phokhara_6.0.inc'

      real*8 jac,xx_om0_max,xx_om0_min,xx_om1_max,xx_om1_min,
     1   xx_phi0_max,xx_phi0_min,xx_ss_max,xx_ss_min,d_om0,d_om1,d_phi0,
     2   d_ss,vv_3pi,yy_3pi,const_1,const_2,const_3,const_ss
      real*8 qq,qqmax,qqmin,x,p,aa,omm1_3pi_BW,omg1_3pi_BW,omm0_3pi,
     1   omg0_3pi,omm1_3pi,omg1_3pi,omm2_3pi,omg2_3pi,phim0_3pi,
     2   phig0_3pi,mm_1_p,mg_1_p,const_1_p,xx_1_p_min,xx_1_p_max,d_1_p,
     3   mm_2_p,mg_2_p,const_2_p,xx_2_p_min,xx_2_p_max,d_2_p,
     4   const_om2,xx_om2_max,xx_om2_min,d_om2

      common /mass_3pi/ omm0_3pi,omg0_3pi,omm1_3pi,omg1_3pi,omm2_3pi,
     1                  omg2_3pi,phim0_3pi,phig0_3pi 

c \om_0 -----------------------------
      if(Sp.lt.25.d0)then
       const_1 = 1100.d0*(omg0_3pi/omm0_3pi)**2
      else  
       const_1 = 1100000.d0*(omg0_3pi/omm0_3pi)**2
      endif

      xx_om0_max = const_1*omm0_3pi**3/omg0_3pi * 
     1             dAtan((qqmax/omm0_3pi**2-1.d0)*omm0_3pi/omg0_3pi)
      xx_om0_min = const_1*omm0_3pi**3/omg0_3pi * 
     1             dAtan((qqmin/omm0_3pi**2-1.d0)*omm0_3pi/omg0_3pi)
      d_om0 = xx_om0_max - xx_om0_min 

c \phi_0 -----------------------------
      if(Sp.lt.25.d0)then
       const_2 =  10000.d0*(phig0_3pi/phim0_3pi)**2
      else
       const_2 =  300000.d0*(phig0_3pi/phim0_3pi)**2 
      endif

      xx_phi0_max = const_2*phim0_3pi**3/phig0_3pi * 
     1            dAtan((qqmax/phim0_3pi**2-1.d0)*phim0_3pi/phig0_3pi)
      xx_phi0_min = const_2*phim0_3pi**3/phig0_3pi * 
     1            dAtan((qqmin/phim0_3pi**2-1.d0)*phim0_3pi/phig0_3pi)
      d_phi0 = xx_phi0_max - xx_phi0_min

c \om_1 ----- only for sqrt(s)= 10.52  \Gamma_om_1 = omg1 * 2
      const_3 = 6000.d0*(2.d0*omg1_3pi/omm1_3pi)**2

      xx_om1_max = const_3*omm1_3pi**3/(2.d0*omg1_3pi) * 
     1   dAtan((qqmax/omm1_3pi**2-1.d0)*omm1_3pi/(2.d0*omg1_3pi))
      xx_om1_min = const_3*omm1_3pi**3/2.d0/omg1_3pi * 
     1   dAtan((qqmin/omm1_3pi**2-1.d0)*omm1_3pi/2.d0/omg1_3pi)
      d_om1 = xx_om1_max - xx_om1_min

c Sp/(Sp-qq) ----------------------------
       xx_ss_max = -Sp * dLog((Sp-qqmax)/Sp) 
       xx_ss_min = -Sp * dLog((Sp-qqmin)/Sp)
       d_ss = xx_ss_max - xx_ss_min

c--------------------------------------
      if(Sp.lt.25.d0)then

       const_ss = 1.d0
      else      
       const_ss = 44.d0
      endif

      aa = const_ss*(qqmax - qqmin)

c      qq = qqmin + x * aa
c      jac = aa
c --------------------------------------

      if(Sp.lt.25.d0)then

       vv_3pi = aa + d_ss + d_om0 + d_phi0

      if(p.lt.(d_ss/vv_3pi))then
          yy_3pi = xx_ss_min + x * d_ss
          qq = Sp * ( 1.d0 - dExp(-yy_3pi/Sp))
      elseif(p.lt.((d_om0+d_ss)/vv_3pi))then
         yy_3pi = xx_om0_min + x * d_om0
         qq = omg0_3pi*omm0_3pi 
     2      * dTan(yy_3pi*omg0_3pi/omm0_3pi**3/const_1)
     1      + omm0_3pi**2
      elseif(p.lt.((d_om0+d_phi0+d_ss)/vv_3pi))then
         yy_3pi = xx_phi0_min + x * d_phi0
         qq = phig0_3pi*phim0_3pi 
     2      * dTan(yy_3pi*phig0_3pi/phim0_3pi**3/const_2)
     1      + phim0_3pi**2
      else
          qq = qqmin + x * aa/const_ss
      endif

      jac = vv_3pi/(const_ss + Sp/(Sp-qq) + 
     3  const_1/((qq/omm0_3pi**2-1.d0)**2+(omg0_3pi/omm0_3pi)**2) +
     2  const_2/((qq/phim0_3pi**2-1.d0)**2+(phig0_3pi/phim0_3pi)**2))

      else
 
       vv_3pi = d_ss + d_om0 + d_phi0 + aa + d_om1  

      if(p.lt.(d_ss/vv_3pi))then
          yy_3pi = xx_ss_min + x * d_ss
          qq = Sp * ( 1.d0 - dExp(-yy_3pi/Sp))
      elseif(p.lt.((d_om0+d_ss)/vv_3pi))then
         yy_3pi = xx_om0_min + x * d_om0
         qq = omg0_3pi*omm0_3pi 
     2      * dTan(yy_3pi*omg0_3pi/omm0_3pi**3/const_1)
     1      + omm0_3pi**2
      elseif(p.lt.((d_om0+d_phi0+d_ss)/vv_3pi))then
         yy_3pi = xx_phi0_min + x * d_phi0
         qq = phig0_3pi*phim0_3pi 
     2      * dTan(yy_3pi*phig0_3pi/phim0_3pi**3/const_2)
     1      + phim0_3pi**2
      elseif(p.lt.((d_om0+d_phi0+d_ss+d_om1)/vv_3pi))then
         yy_3pi = xx_om1_min + x * d_om1  
         qq = 2.d0*omg1_3pi*omm1_3pi*dTan(yy_3pi*2.d0*omg1_3pi/
     1            omm1_3pi**3/const_3) + omm1_3pi**2
      else
          qq = qqmin + x * aa/const_ss
      endif

      jac = vv_3pi/( const_ss + Sp/(Sp-qq) + 
     3  const_1/((qq/omm0_3pi**2-1.d0)**2+(omg0_3pi/omm0_3pi)**2)+
     2  const_2/((qq/phim0_3pi**2-1.d0)**2+(phig0_3pi/phim0_3pi)**2)+ 
     1  const_3/((qq/omm1_3pi**2-1.d0)**2
     4                            +(2.d0*omg1_3pi/omm1_3pi)**2) )

      endif
 
      return
      end
c ========================================================================
c --- Generates: real photon costheta and phi angles in the e^+e^- CMS ---
c ------------------------------------------------------------------------
      subroutine photonangles1(cosmin,cosmax,Ar,costheta,phi,jacobian)
      include 'phokhara_6.0.inc'
      double precision cosmin,cosmax,Ar(14),costheta,phi,jacobian,x,b,
     1       cmin,cmax,y

      x   = Ar(2)
      phi = 2.d0*pi*Ar(3)
c --- flat ---
c      costheta = cosmin+(cosmax-cosmin)*x
c      jacobian = 2.d0*pi*(cosmax-cosmin)
c --- peaked at costheta = +-1 ---
      b = dSqrt(1.d0-4.d0*me*me/Sp)
      cmin = dLog((1.d0+b*cosmin)/(1.d0-b*cosmin))/(2.d0*b)
      cmax = dLog((1.d0+b*cosmax)/(1.d0-b*cosmax))/(2.d0*b)
      y = cmin+x*(cmax-cmin)
      costheta = dTanh(b*y)/b
      jacobian = 2.d0*pi*(1.d0-b*b*costheta*costheta)*(cmax-cmin)
      return
      end
c ========================================================================
c --- Generates: real photon costheta and phi angles in the e^+e^- CMS ---
c ------------------------------------------------------------------------
      subroutine photonangles2(cosmin,cosmax,Ar,costheta,phi,jacobian)
      include 'phokhara_6.0.inc'
      double precision cosmin,cosmax,Ar(14),costheta,phi,jacobian,x,b,
     1                 cmin,cmax,y

      x   = Ar(10)
      phi = 2.d0*pi*Ar(11)

c --- flat ---
c      costheta = cosmin+(cosmax-cosmin)*x
c      jacobian = 2.d0*pi*(cosmax-cosmin)
c --- peaked at costheta = +-1 ---
      b = dSqrt(1.d0-4.d0*me*me/Sp)
      cmin = dLog((1.d0+b*cosmin)/(1.d0-b*cosmin))/(2.d0*b)
      cmax = dLog((1.d0+b*cosmax)/(1.d0-b*cosmax))/(2.d0*b)
      y = cmin+x*(cmax-cmin)
      costheta = dTanh(b*y)/b
      jacobian = 2.d0*pi*(1.d0-b*b*costheta*costheta)*(cmax-cmin)
      return
      end      
c ========================================================================
c --- Generates: real photon energy in the e^+e^- CMS normalized to the --
c --- CMS energy ---------------------------------------------------------
c ------------------------------------------------------------------------
      subroutine photonenergy2(qq,c1min,c1max,cos1,cos2,cos12,Ar
     &                        ,w1,w2,jacobian)
      include 'phokhara_6.0.inc'
      double precision qq,c1min,c1max,cos1,cos2,cos12,Ar(14),
     &  w1,w2,jacobian,x,wmin,q2,qqb,w1max,w2max,u,umin,umax

      x = Ar(9)
      
c --- flat ---
c      w2 = w+(w2max-w)*x
c      jacobian = (w2max-w)
c --- peaked at w1, w2 = w ---

      wmin = gmin/dSqrt(Sp)
      q2 = qq/Sp
      qqb = Sp*(1.d0-4.d0*wmin+2.d0*wmin*wmin*(1.d0-cos12))

c --- photon 2 inside the angular cuts, photon 1 outside ---
c --- then w2 > wmin and w1 > w ----------------------------
      if(((cos1.gt.c1max).or.(cos1.lt.c1min)).and.
     &   ((cos2.le.c1max).and.(cos2.ge.c1min))) then

         w2max = (1.d0-q2-2.d0*w)/(2.d0*(1.d0-w*(1.d0-cos12)))         
         umin = dLog(wmin/(1.d0-q2-2.d0*wmin))
         umax = dLog(w2max/(1.d0-q2-2.d0*w2max))
         u  = umin+x*(umax-umin)
         w2 = (1.d0-q2)/(2.d0+dExp(-u))
         w1 = (1.d0-q2-2.d0*w2)/(2.d0*(1.d0-w2*(1.d0-cos12)))
	 jacobian = 1.d0/2.d0 * w2*w2*w1*w1 * (umax-umin)/(1.d0-q2)
            
c --- photon 1 inside the angular cuts, photon 2 outside ---
c --- then w1 > wmin and w2 > w ----------------------------
      elseif(((cos2.gt.c1max).or.(cos2.lt.c1min)).and.
     &   ((cos1.le.c1max).and.(cos1.ge.c1min))) then

         w1max = (1.d0-q2-2.d0*w)/(2.d0*(1.d0-w*(1.d0-cos12)))         
         umin = dLog(wmin/(1.d0-q2-2.d0*wmin))
         umax = dLog(w1max/(1.d0-q2-2.d0*w1max))
         u  = umin+x*(umax-umin)
         w1 = (1.d0-q2)/(2.d0+dExp(-u))
         w2 = (1.d0-q2-2.d0*w1)/(2.d0*(1.d0-w1*(1.d0-cos12)))            
         jacobian = 1.d0/2.d0 * w2*w2*w1*w1 * (umax-umin)/(1.d0-q2)

c --- both photons pass the angular cuts ---
      elseif(((cos2.le.c1max).and.(cos2.ge.c1min)).and.
     &   ((cos1.le.c1max).and.(cos1.ge.c1min))) then

         if(qq.le.qqb)then
	   
            w1max = (1.d0-q2-2.d0*w)/(2.d0*(1.d0-w*(1.d0-cos12)))         
            umin = dLog(w/(1.d0-q2-2.d0*w))
            umax = dLog(w1max/(1.d0-q2-2.d0*w1max))
            u  = umin+x*(umax-umin)
            w1 = (1.d0-q2)/(2.d0+dExp(-u))
            w2 = (1.d0-q2-2.d0*w1)/(2.d0*(1.d0-w1*(1.d0-cos12)))            
            jacobian = 1.d0/2.d0 * w2*w2*w1*w1 * (umax-umin)/(1.d0-q2)

         else

            if(Ar(8).lt.0.5d0)then

            w2max = (1.d0-q2-2.d0*w)/(2.d0*(1.d0-w*(1.d0-cos12)))         
            umin = dLog(wmin/(1.d0-q2-2.d0*wmin))
            umax = dLog(w2max/(1.d0-q2-2.d0*w2max))
            u  = umin+x*(umax-umin)
            w2 = (1.d0-q2)/(2.d0+dExp(-u))
            w1 = (1.d0-q2-2.d0*w2)/(2.d0*(1.d0-w2*(1.d0-cos12)))            
            jacobian = w2*w2*w1*w1* (umax-umin)/(1.d0-q2)
	      
            else

            w1max = (1.d0-q2-2.d0*w)/(2.d0*(1.d0-w*(1.d0-cos12)))         
            umin = dLog(wmin/(1.d0-q2-2.d0*wmin))
            umax = dLog(w1max/(1.d0-q2-2.d0*w1max))
            u  = umin+x*(umax-umin)
            w1 = (1.d0-q2)/(2.d0+dExp(-u))
            w2 = (1.d0-q2-2.d0*w1)/(2.d0*(1.d0-w1*(1.d0-cos12)))            
            jacobian = w2*w2*w1*w1* (umax-umin)/(1.d0-q2)

            endif

         endif

      endif
      return
      end
c ------------------------------------------------------------------
c    lepton four-momenta: one real photon                           
c ------------------------------------------------------------------
      subroutine leptonmomenta1(qq,costheta,phi)
      include 'phokhara_6.0.inc'
      double precision qq,q2,E,costheta,sintheta,phi
      integer i

      q2 = qq/Sp
      sintheta = dSqrt(1.d0-costheta*costheta)
c --- real photon1 ---
      E = (1.d0-q2)*dSqrt(Sp)/2.d0
      momenta(3,0) = E
      momenta(3,1) = E*sintheta*dCos(phi)
      momenta(3,2) = E*sintheta*dSin(phi)
      momenta(3,3) = E*costheta
c --- real photon2 ---
      momenta(4,0) = 0.d0
      momenta(4,1) = 0.d0
      momenta(4,2) = 0.d0
      momenta(4,3) = 0.d0
c --- virtual photon ---
      momenta(5,0) = (1.d0+q2)*dSqrt(Sp)/2.d0
      do i = 1,3
        momenta(5,i) = -momenta(3,i)
      enddo
      return
      end
c ------------------------------------------------------------------
c    lepton four-momenta: two real photons                          
c ------------------------------------------------------------------
      subroutine leptonmomenta2(qq,w1,w2,cos1,phi1,cos2,phi2)
      include 'phokhara_6.0.inc'
      double precision qq,w1,w2,cos1,sin1,phi1,cos2,sin2,phi2,E1,E2
      integer i

      sin1 = dSqrt(1.d0-cos1*cos1)
      sin2 = dSqrt(1.d0-cos2*cos2)
c --- real photon1 ---
      E1 = w1*dSqrt(Sp)
      momenta(3,0) = E1
      momenta(3,1) = E1*sin1*dCos(phi1)
      momenta(3,2) = E1*sin1*dSin(phi1)
      momenta(3,3) = E1*cos1
c --- real photon2 ---
      E2 = w2*dSqrt(Sp)      
      momenta(4,0) = E2
      momenta(4,1) = E2*sin2*dCos(phi2)
      momenta(4,2) = E2*sin2*dSin(phi2)
      momenta(4,3) = E2*cos2
c --- virtual photon ---
      momenta(5,0) = dSqrt(Sp)-E1-E2
      do i = 1,3
        momenta(5,i) = -momenta(3,i)-momenta(4,i)
      enddo
      return
      end
c ========================================================================
c --- Generates: pion costheta and phi angles in the Q2 CMS system, ------
c afterwards boosted into the e^+ e^- CMS --------------------------------
c used in 2 photon emission
c ------------------------------------------------------------------------
      subroutine pionangles(cosmin,cosmax,Ar,costheta,phi,jacobian)
      include 'phokhara_6.0.inc'
      double precision cosmin,cosmax,Ar(14),costheta,phi,jacobian,x 

      x   = Ar(4)
      phi = 2.d0*pi*Ar(5)

c --- flat ---
      costheta = cosmin+(cosmax-cosmin)*x
      jacobian = 2.d0*pi*(cosmax-cosmin)
      return
      end
c ========================================================================
c --- Generates: pion costheta and phi angles in Lambda rest-frame
c ------------------------------------------------------------------------
      subroutine pionanglesLamb(cosmin,cosmax,costhm,phim,
     1                          costhp,phip)
      include 'phokhara_6.0.inc'
      double precision jacobian,x1,x2,jac1,jac2,cosmin,cosmax,x
      real*8 costhm,phim,costhp,phip,rr1_ll(0:3)

      call ranlxdf(rr1_ll,4)
      x1   = rr1_ll(0)
      x2   = rr1_ll(1)
      phim = 2.d0*pi*rr1_ll(2)
      phip = 2.d0*pi*rr1_ll(3)
      
c --- flat ---
      costhm = cosmin+(cosmax-cosmin)*x1
      jac1 = 2.d0*pi*(cosmax-cosmin)
c --- flat ---
      costhp = cosmin+(cosmax-cosmin)*x2
      jac2 = 2.d0*pi*(cosmax-cosmin)
c 
      jacobian = jac1 * jac2

      return
      end
c *******************************************************************
c this subroutine generates  4 massive particle phase space 
c in q=q1+q2+q3+q4 rest frame (bosted afterwards into e^+e^- CMS)
c
c Mode    2pi^0 pi^+ pi^- (pion=2) |   Mode    2pi^+ 2pi^-     (pion=3)
c q1,q2 - four momenta of pi^0     |   q1,q4 - four momenta of pi^+ 
c q3    - four momentum of pi^-    |   q2,q3 - four momenta of pi^-
c q4    - four momentum of pi^+    |
c ------------------------------------------------------------------
      subroutine pionangles_1(qq2,q0p,q2p,q0b,q2b,fac)
      include 'phokhara_6.0.inc'
      integer ip0,i,ru
      double precision Arp(8),Arp_r(0:7)
      double precision q1(4),q2(4),q3(4),q4(4),pom_v(4) 
      double precision q0,q2p,q2p_min,q2p_max,dx1,q0p,x2min,x2max,dx2,
     1       q2b,q0b,qq2,phi1,costh1,sinth1,cosphi1,sinphi1,phi2,costh2,
     2       sinth2,cosphi2,sinphi2,phi3,costh3,sinth3,cosphi3,sinphi3,
     3       rm12,e1,vq1,rm22,e2,vq2,e3,vq3,q2pp,appr1,fac
c
      call ranlxdf(Arp_r,8)
      do ru=0,7
         Arp(ru+1) = Arp_r(ru)
      enddo
c
      q0    = sqrt(qq2)
      q2p_min = (rmass(2)+rmass(3)+rmass(4))**2
      q2p_max = (q0-rmass(1))**2
      if(pion.eq.2)then
       call chann1(Arp(1),q2p_min,q2p_max,q2p,dx1,ip0)
      else
       dx1    = q2p_max - q2p_min
       q2p    = q2p_min + dx1*Arp(1)
      endif
c
      q0p   = sqrt(q2p)
c
      x2min = (rmass(3)+rmass(4))**2
      x2max = (q0p-rmass(2))**2
      dx2   = x2max - x2min
c
      q2b   = x2min + dx2*Arp(2)
      q0b   = sqrt(q2b)
c
      phi1    = 2.d0*pi*Arp(3)
      costh1  = -1.d0 + 2.d0*Arp(4)
      sinth1  = 2.d0*sqrt(Arp(4)*(1.d0-Arp(4)))
      cosphi1 = cos(phi1)
      sinphi1 = sin(phi1)
c
      phi2    = 2.d0*pi*Arp(5)
      costh2  = -1.d0 + 2.d0*Arp(6)
      sinth2  = 2.d0*sqrt(Arp(6)*(1.d0-Arp(6)))
      cosphi2 = cos(phi2)
      sinphi2 = sin(phi2)
c
      phi3    = 2.d0*pi*Arp(7)
      costh3  = -1.d0 + 2.d0*Arp(8)
      sinth3  = 2.d0*sqrt(Arp(8)*(1.d0-Arp(8)))
      cosphi3 = cos(phi3)
      sinphi3 = sin(phi3)
c
c calculating q1 in Q rest frame
c
      rm12 = rmass(1)**2
      e1  = (qq2-q2p+rm12)/2.d0/q0
      vq1 = sqrt(e1**2-rm12)
      q1(1) =  e1
      q1(2) =  vq1 * sinth1 * cosphi1      
      q1(3) =  vq1 * sinth1 * sinphi1      
      q1(4) =  vq1 * costh1
c
c calculating q2 in Q' rest frame
c
      rm22 = rmass(2)**2
      e2  = (q2p-q2b+rm22)/2.d0/q0p
      vq2 = sqrt(e2**2-rm22)
      q2(1) =  e2
      q2(2) =  vq2 * sinth2 * cosphi2      
      q2(3) =  vq2 * sinth2 * sinphi2      
      q2(4) =  vq2 * costh2
c
c calculating q3 and q4 in Q" rest frame
c    
      e3  = (q2b+rmass(3)**2-rmass(4)**2)/2.d0/q0b
      vq3 = sqrt(e3**2-rmass(3)**2)
      q3(1) =  e3
      q3(2) =  vq3 * sinth3 * cosphi3      
      q3(3) =  vq3 * sinth3 * sinphi3      
      q3(4) =  vq3 * costh3
      q4(1) =  q0b - e3
      q4(2) = -q3(2)
      q4(3) = -q3(3)
      q4(4) = -q3(4)
c
c boosting q3 and q4 into Q' rest frame
c
      call boost1(q0p,q0b,e2,vq2,costh2,sinth2,cosphi2,sinphi2,q3)
      call boost1(q0p,q0b,e2,vq2,costh2,sinth2,cosphi2,sinphi2,q4)
c
c boosting q2,q3 and q4 into Q rest frame
c
      call boost1(q0,q0p,e1,vq1,costh1,sinth1,cosphi1,sinphi1,q2)
      call boost1(q0,q0p,e1,vq1,costh1,sinth1,cosphi1,sinphi1,q3)
      call boost1(q0,q0p,e1,vq1,costh1,sinth1,cosphi1,sinphi1,q4)
c
      fac = dx1 * dx2 * (4.d0*pi)**3
      if(pion.eq.2)then
        do i=1,4
         pom_v(i) = q1(i)+q3(i)+q4(i)
        enddo
        q2pp = pom_v(1)**2 - pom_v(2)**2- pom_v(3)**2- pom_v(4)**2
        fac = fac/appr1(q2p,q2pp)
        if(ip0.eq.2)then
        do i=1,4
          pom_v(i) = q1(i)
          q1(i)    = q2(i)
          q2(i)    = pom_v(i)
        enddo
        endif    
      endif
c
c filling the four momenta
c
      do i =0,3
       momenta(6,i) = q1(i+1)
       momenta(7,i) = q2(i+1)
       momenta(8,i) = q3(i+1)
       momenta(9,i) = q4(i+1)
      enddo
c
      return
      end
c *******************************************************************
c this subroutine generates  3 massive particle phase space 
c in q=q1+q2+q3 rest frame (bosted afterwards into e^+e^- CMS)
c
c Mode   pi^+ pi^- pi^0 (pion=4)
c q1    - four momentum of pi^+
c q2    - four momentum of pi^-
c q3    - four momentum of pi^0
c
      subroutine pionangles_2(qq2,q0p,q2p,fac)
      include 'phokhara_6.0.inc'

      real*8 rr,rr_r(0:5),qq2,q1,q2,q3,fac,rlam,a,b,c,x1min,q0,x1max,
     1   dx1,q2p,q0p,pp,xx2,phi1,costh1,sinth1,cosphi1,sinphi1,phi2,
     2   costh2,sinth2,cosphi2,sinphi2,e1,e2,vq1,vq2,x2min,x2max,const2,
     3   dx2,vv_3pi,const_1_p,mm_1_p,mg_1_p,d_1_p,xx_1_p_max,xx_1_p_min
      real*8 gg_1,mm_1,const_s,pom,q12p,q13p,q23p,
     1       qq12_3pi,qq13_3pi,qq23_3pi
      integer i,jj,ru
c
      dimension rr(6),q1(4),q2(4),q3(4)
      common/qqij_3pi/qq12_3pi,qq13_3pi,qq23_3pi
c
      call ranlxdf(rr_r,6)
      do ru=0,5
         rr(ru+1) = rr_r(ru)
      enddo

      pp = rr(6)

      x1min = (rmass(3)+rmass(2))**2  
      q0    = sqrt(qq2)
      x1max = (q0-rmass(1))**2      
      dx1   = x1max - x1min         
c
      if(Sp.lt.4.d0)then
        q2p    = x1min + dx1*rr(1)  
      else
c ---------------------------------------------
      const2 = 1000.d0

      x2min = Sp*log(x1min/Sp)
      dx2 = Sp*log(x1max/x1min)

      mm_1_p = 1.5d0
      mg_1_p = 0.25d0
      const_1_p = 100.d0 *(mg_1_p/mm_1_p)**2

      xx_1_p_max =  const_1_p*mm_1_p**3/mg_1_p * 
     1   dAtan((x1max/mm_1_p**2-1.d0)*mm_1_p/mg_1_p)
      xx_1_p_min = const_1_p*mm_1_p**3/mg_1_p * 
     1   dAtan((x1min/mm_1_p**2-1.d0)*mm_1_p/mg_1_p)
      d_1_p = xx_1_p_max - xx_1_p_min

      vv_3pi = dx1 + const2*dx2 + d_1_p

       if(pp.lt.(dx1/vv_3pi)) then
          q2p = x1min + dx1*rr(1)       
       elseif(pp.lt.((dx1+d_1_p)/vv_3pi)) then
          xx2 = xx_1_p_min + d_1_p * rr(1)
          q2p = mg_1_p*mm_1_p*dTan(xx2*mg_1_p/
     1            mm_1_p**3/const_1_p) + mm_1_p**2
       else
          xx2 = x2min + dx2*rr(1)
          q2p = Sp*exp(xx2/Sp)
       endif

      endif

c ---------------------------------------------
      q0p   = sqrt(q2p)
c
      phi1    = 2.d0*pi*rr(2)
      costh1  = -1.d0 + 2.d0*rr(3)
      sinth1  = 2.d0*sqrt(abs(rr(3)*(1.d0-rr(3))))
      cosphi1 = cos(phi1)
      sinphi1 = sin(phi1)
c
      phi2    = 2.d0*pi*rr(4)
      costh2  = -1.d0 + 2.d0*rr(5)
      sinth2  = 2.d0*sqrt(abs(rr(5)*(1.d0-rr(5))))
      cosphi2 = cos(phi2)
      sinphi2 = sin(phi2)
c calculating q1 in Q rest frame
c
      e1  = (qq2-q2p+rmass(1)**2)/2.d0/q0
      vq1 = sqrt(abs(e1**2-rmass(1)**2))
      q1(1) =  e1
      q1(2) =  vq1 * sinth1 * cosphi1      
      q1(3) =  vq1 * sinth1 * sinphi1      
      q1(4) =  vq1 * costh1
c
c calculating q2 and q3 in Q' rest frame
c
      e2  = (q2p+rmass(2)**2-rmass(3)**2)/2.d0/q0p

      vq2 = sqrt(abs(e2**2-rmass(2)**2))
      q2(1) =  e2
      q2(2) =  vq2 * sinth2 * cosphi2      
      q2(3) =  vq2 * sinth2 * sinphi2      
      q2(4) =  vq2 * costh2

      q3(1) =  q0p-q2(1)
      q3(2) = -q2(2)
      q3(3) = -q2(3)
      q3(4) = -q2(4)
c
c boosting q2 and q3 into Q rest frame
c
      call boost1(q0,q0p,e1,vq1,costh1,sinth1,cosphi1,sinphi1,q2)
      call boost1(q0,q0p,e1,vq1,costh1,sinth1,cosphi1,sinphi1,q3)

c ----------------------
      qq12_3pi =  (q1(1) + q2(1))**2
      do jj=2,4
       qq12_3pi = qq12_3pi - (q1(jj) + q2(jj))**2
      enddo
      qq13_3pi =  (q1(1) + q3(1))**2
      do jj=2,4
       qq13_3pi = qq13_3pi - (q1(jj) + q3(jj))**2
      enddo
      qq23_3pi = (q2(1) + q3(1))**2
      do jj=2,4
       qq23_3pi = qq23_3pi - (q2(jj) + q3(jj))**2
      enddo
c
c calculating the weight
c
      if(Sp.lt.4.d0)then
       fac =  (4.d0*pi)**2*dx1 
      else
       fac =  (4.d0*pi)**2*vv_3pi/( 1.d0 
     1    + const2*Sp/q2p
     2    + const_1_p/((q2p/mm_1_p**2-1.d0)**2 +(mg_1_p/mm_1_p)**2) ) 
      endif
c
c     filling the four momenta
c
      do i=0,3
         momenta(6,i) = q1(i+1)
         momenta(7,i) = q2(i+1)
         momenta(8,i) = q3(i+1)
      enddo

      return
      end
c *******************************************************************
c generation of the 3pi invariant mass: flat + omega Breit-Wigner
c *******************************************************************
      subroutine chann1(rrr,q2p_min,q2p_max,q2p,dx1,ip0)
      implicit none
      double precision rrr,q2p_min,q2p_max,q2p,dx1,dm,dg,dm2,dmg,rr1(1),
     1       rr1_r(0:2),vol1,vol2,vol3,vol4,vol,r1_test,r2_test,r3_test,
     2       xx,x_min,x_max
      integer ip0 
c
      dm = 0.782d0
      dg = 0.0085d0
c
      dm2 = dm**2
      dmg = dm*dg
c
      x_min = dm2 *atan((q2p_min-dm2)/dmg)
      x_max = dm2 *atan((q2p_max-dm2)/dmg)
      vol2 = x_max-x_min
      vol1 = q2p_max - q2p_min
      vol3 = vol1
      vol4 = vol2
      vol = vol1 + vol2 + vol3 + vol4
c
      r1_test = vol1/vol
      r2_test = (vol1+vol2)/vol
      r3_test = (vol1+vol2+vol3)/vol
c
      call ranlxdf(rr1_r,1)
      rr1(1) = rr1_r(0)
c
      if(rr1(1).lt.r1_test)then
       q2p = q2p_min + vol1*rrr
       ip0 = 1
      elseif(rr1(1).lt.r2_test)then
       xx = x_min + vol2*rrr
       q2p = dm2 + dmg*tan(xx/dm2) 
       ip0 = 1
      elseif(rr1(1).lt.r3_test)then
       q2p = q2p_min + vol1*rrr
       ip0 = 2
      else
       xx = x_min + vol2*rrr
       q2p = dm2 + dmg*tan(xx/dm2) 
       ip0 = 2
      endif
      dx1 = vol
c
      return
      end
c *******************************************************************
c
      real*8 function appr1(qq12,qq22)
      implicit none
      double precision dm,dg,dm2,dm3g,dmg2,qq12,qq22
c
      dm = 0.782d0
      dg = 0.0085d0
      dm2 = dm**2
      dm3g = dm2*dm*dg
      dmg2 = dm2*dg**2
      appr1 = 2.d0+dm3g/((qq12-dm2)**2+dmg2)+dm3g/((qq22-dm2)**2+dmg2)
c
      return
      end
c ------------------------------------------------------------------
c     hadron four momenta                                            
c ------------------------------------------------------------------
      subroutine hadronmomenta(qq,costheta,phi)
      include 'phokhara_6.0.inc'
      double precision qq,p,costheta,sintheta,phi,m2,
     &        cmsvector(0:3),boostvector(0:3),labvector(0:3)
      integer i
      
      sintheta = dSqrt(1.d0-costheta*costheta)
      if (pion.eq.0) then 
         m2 = mmu*mmu
      elseif (pion.eq.4) then 
         m2 = mp*mp
      elseif (pion.eq.5) then 
         m2 = mnt*mnt
      elseif (pion.eq.6) then 
         m2 = mKp*mKp
      elseif (pion.eq.7) then
         m2 = mKn*mKn
      elseif (pion.eq.9) then
         m2 = mlamb*mlamb
      else
         m2 = mpi*mpi
      endif
c --- pions/muons/protons/neutrons/kaons/lambdas in the qq-rest frame ---
c --- pi^+/mu^+/pbar/nbar/K^+/K^0/lambda bar ---
      momenta(6,0) = dSqrt(qq)/2.d0
      p            = momenta(6,0)*dSqrt(1.d0-4.d0*m2/qq)
      momenta(6,1) = p*sintheta*dCos(phi)
      momenta(6,2) = p*sintheta*dSin(phi)
      momenta(6,3) = p*costheta
c --- pi^-/mu^-/p/n/K^-/K^0bar/lambda---
      momenta(7,0) = momenta(6,0) 
      do i = 1,3
        momenta(7,i) = -momenta(6,i)
      enddo
c --- boost the hadron momenta into the e^+ e^- CMS ---
      call hadronmomenta_1(2)
      return
      end
c ------------------------------------------------------------------
c        boost four momenta from Q rest frame to e^+ e^- CMS             
c ------------------------------------------------------------------
      subroutine hadronmomenta_1(Np)
      include 'phokhara_6.0.inc'
      double precision p,costheta,sintheta,phi,m2,
     &        cmsvector(0:3),boostvector(0:3),labvector(0:3),
     1        q1(4),q2(4),q3(4),q4(4)
      integer i,j,Np
c      
c --- boost the hadron momenta into the e^+ e^- CMS ---
c
      do i =0,3
         boostvector(i) = momenta(5,i)
      enddo   
c
      do j=1,Np
         do i =0,3
            cmsvector(i) = momenta(5+j,i)
         enddo   
         call boost(cmsvector,boostvector,labvector)
         do i =0,3
            momenta(5+j,i) = labvector(i) 
         enddo         
      enddo
      return
      end
c --------------------------------------------------------------------
c        hadron four momenta pi^- p (pi^+ pbar) (pion=9)  
c        boost from Lambda (Lambda bar) rest frame to Q rest frame 
c        boost from Q rest frame to e^+ e^- CMS             
c --------------------------------------------------------------------
      subroutine hadronmomenta_Lamb(qq,costheta,phi,costhm,phim,costhp,
     1                                                            phip)
      include 'phokhara_6.0.inc'
      double precision qq,p,costheta,sintheta,phi,m2,
     2        cmsvector(0:3),boostvector(0:3),labvector(0:3)
      real*8 costhm,phim,sinthm,costhp,phip,sinthp,e1pi,e1p,vpp1,
     1        pom1(1:2,0:3),wyn1,qq1l(0:3),veclamb1(0:3),veclamb2(0:3),
     2        vecpom(4)
      integer i,j
      common /veclamb/ veclamb1,veclamb2
      
      sintheta = dSqrt(1.d0-costheta*costheta)
      m2 = mlamb*mlamb
      p        = dSqrt(qq)/2.d0 * dSqrt(1.d0-4.d0*m2/qq)

c ----------- 
      sinthm = dSqrt(1.d0-costhm*costhm)
      e1pi = (mlamb**2 - mp**2 + mpi**2)/2.d0/mlamb
      e1p  = (mlamb**2 + mp**2 - mpi**2)/2.d0/mlamb
      vpp1 = Sqrt(abs(e1pi**2-mpi**2))

      veclamb2(0) = 0
      veclamb2(1) = sinthm*Cos(phim)
      veclamb2(2) = sinthm*Sin(phim)
      veclamb2(3) = costhm
      do i=1,4
         vecpom(i) = veclamb2(i-1)
      enddo
c               Lambda rest frame to qq-rest frame
         call boost1(Sqrt(qq),mlamb,dSqrt(qq)/2.d0,p,costheta,sintheta,
     1                                      Cos(phi),Sin(phi),vecpom)
      do i=1,4
         veclamb2(i-1) = vecpom(i)  
      enddo

      sinthp = dSqrt(1.d0-costhp*costhp)

      veclamb1(0) = 0
      veclamb1(1) = sinthp*Cos(phip)
      veclamb1(2) = sinthp*Sin(phip)
      veclamb1(3) = costhp
      do i=1,4
         vecpom(i) = veclamb1(i-1)
      enddo
c               Lambda bar rest frame to qq-rest frame
         call boost1(Sqrt(qq),mlamb,dSqrt(qq)/2.d0,-p,costheta,sintheta,
     1                                       Cos(phi),Sin(phi),vecpom)
      do i=1,4
         veclamb1(i-1) = vecpom(i)  
      enddo

c --- Lambda rest frame --
c --- pion^- 
      momenta(10,0) = e1pi
      momenta(10,1) = vpp1 * sinthm * Cos(phim)
      momenta(10,2) = vpp1 * sinthm * Sin(phim)
      momenta(10,3) = vpp1 * costhm

c --- proton
      momenta(11,0) = e1p
      do i = 1,3
        momenta(11,i) = -momenta(10,i)
      enddo

c --- Lambda bar rest frame --
c --- pion^+ 
      momenta(8,0) = e1pi
      momenta(8,1) = vpp1 * sinthp * Cos(phip)
      momenta(8,2) = vpp1 * sinthp * Sin(phip)
      momenta(8,3) = vpp1 * costhp

c --- proton bar
      momenta(9,0) = e1p 
      do i = 1,3
        momenta(9,i) = -momenta(8,i)
      enddo

c --- boost the hadron momenta from Lambda rest frame to qq-rest frame
      do j=10,11         
         do i=0,3
            vecpom(i+1)=momenta(j,i)
         enddo
         call boost1(Sqrt(qq),mlamb,
     1      Sqrt(qq)/2.d0,p,costheta,sintheta,Cos(phi),Sin(phi),vecpom)
         do i=0,3
            momenta(j,i)=vecpom(i+1)
         enddo
      enddo

c --- boost the hadron momenta from Lambda bar rest frame to qq-rest frame
      do j=8,9         
         do i=0,3
            vecpom(i+1)=momenta(j,i)
         enddo
         call boost1(Sqrt(qq),mlamb,
     1     Sqrt(qq)/2.d0,-p,costheta,sintheta,Cos(phi),Sin(phi),vecpom)
         do i=0,3
            momenta(j,i)=vecpom(i+1)
         enddo
      enddo

c --- boost the hadron momenta into the e^+ e^- CMS ---
         do i = 0,3
            boostvector(i) = momenta(5,i)
         enddo   

      do i = 0,3
          cmsvector(i) = veclamb1(i)
      enddo   
        call boost(cmsvector,boostvector,labvector)
      do i = 0,3
        veclamb1(i) = labvector(i) 
        cmsvector(i) = veclamb2(i)
      enddo   
      call boost(cmsvector,boostvector,labvector)
      do i = 0,3
         veclamb2(i) = labvector(i) 
      enddo   
 
      do j = 8,11
         do i = 0,3
            cmsvector(i) = momenta(j,i)
         enddo   
         call boost(cmsvector,boostvector,labvector)
         do i = 0,3
            momenta(j,i) = labvector(i) 
         enddo   
      enddo
      return
      end
c -----------------------------------------------------------
c     boost cmsvector by boostvector into labvector          
c -----------------------------------------------------------
      subroutine boost(cmsvector,boostvector,labvector)
      implicit none
      double precision cmsvector(0:3),boostvector(0:3),labvector(0:3),
     1   m(0:3,0:3),E,p,beta,gamma,costheta,sintheta,cosphi,sinphi
      integer i,j
      
      E = boostvector(0)
      p = dSqrt(boostvector(1)**2+boostvector(2)**2+
     &    boostvector(3)**2)
      beta  = p/E
      gamma = 1.d0/dSqrt(1.d0-beta*beta)
      costheta = boostvector(3)/p
      sintheta = sqrt(boostvector(1)**2+boostvector(2)**2)/p
      if(sintheta.ne.0.d0)then
        cosphi   = boostvector(1)/(p*sintheta)
        sinphi   = boostvector(2)/(p*sintheta)
      else
        cosphi = 1.d0
        sinphi = 0.d0
      endif

        m(0,0) = gamma
        m(0,1) = 0.d0
        m(0,2) = 0.d0
        m(0,3) = beta*gamma
        m(1,0) = beta*gamma*sintheta*cosphi
        m(1,1) = costheta*cosphi
        m(1,2) = -sinphi
        m(1,3) = gamma*sintheta*cosphi
        m(2,0) = beta*gamma*sintheta*sinphi
        m(2,1) = costheta*sinphi
        m(2,2) = cosphi
        m(2,3) = gamma*sintheta*sinphi
        m(3,0) = beta*gamma*costheta
        m(3,1) = -sintheta
        m(3,2) = 0.d0
        m(3,3) = gamma*costheta

      do i=0,3
         labvector(i) = 0.d0
         do j=0,3
            labvector(i) = labvector(i)+m(i,j)*cmsvector(j)
         enddo
      enddo

      return
      end
c ----------------------------------------------------------------------
c this subroutine boost fourvector qq from Q' rest frame to Q rest frame
c           Q' = Q - q1
c
      subroutine boost1(q0,q0p,e1,vq1,c1,s1,cf1,sf1,qq)
      implicit none
      double precision q0,q0p,e1,vq1,c1,s1,cf1,sf1,qq1(4),qq(4)
     1                ,transf(4,4),fac1,fac2
      integer i,j
c
      fac1 = (q0-e1)/q0p
      fac2 = -vq1/q0p
c
      transf(1,1) =  fac1
      transf(2,1) =  fac2 * s1 * cf1      
      transf(3,1) =  fac2 * s1 * sf1     
      transf(4,1) =  fac2 * c1      
      transf(1,2) =  0.d0      
      transf(2,2) =  c1 * cf1     
      transf(3,2) =  c1 * sf1      
      transf(4,2) = -s1      
      transf(1,3) =  0.d0      
      transf(2,3) = -sf1      
      transf(3,3) =  cf1      
      transf(4,3) =  0.d0     
      transf(1,4) =  fac2     
      transf(2,4) =  fac1 * s1 * cf1     
      transf(3,4) =  fac1 * s1 * sf1  
      transf(4,4) =  fac1 * c1   
c
        do i=1,4
          qq1(i) = 0.d0
          do j = 1,4
             qq1(i) = qq1(i) + transf(i,j)*qq(j)
          enddo
        enddo
c
      do i=1,4
        qq(i) = qq1(i)
      enddo
c
      return
      end
c ========================================================================
c --- Spin Lambda test
c ------------------------------------------------------------------------
      subroutine test_spin(qq,Hadronic,amplit,accepted)
      include 'phokhara_6.0.inc'
      double precision Matrix,qq,amplit
      real*8 rr_ll,ff_min_ll,ff_max_ll,ff_ll,ff_spin_ll
      complex*16 Leptonic(0:3,0:3),Hadronic(0:3,0:3),
     1           HadronicLamb(0:3,0:3)
      logical accepted
      integer n,i,j,ij,mj
      common/Lept_ee/Leptonic

      call ranlxdf(rr_ll,1)  

      accepted = .true.

      call HadroLamb(qq,Hadronic,HadronicLamb)

       ff_min_ll = 0.d0
       ff_max_ll = (1.d0 + alpha_lamb)**2
       ff_ll = ff_min_ll + (ff_max_ll - ff_min_ll) * rr_ll

       ff_spin_ll = Matrix(Leptonic,HadronicLamb) / amplit * 4.d0

       accepted = (accepted.and.(ff_ll.lt.ff_spin_ll))
      return
      end
c ========================================================================
c --- Test experimental cuts ---------------------------------------------
c ------------------------------------------------------------------------
      subroutine testcuts(n,accepted)
      include 'phokhara_6.0.inc'
      double precision piplab,pimlab,m2,phot1,invmom(0:3),invm2
      integer n,i,j,ij,mj
      logical accepted,accept(3:4)

      accepted = .true.
c -----------------------------------------
c --- angular cuts on the hadrons/muons ---
      mj = 6
      if ((pion.le.1).or.(pion.eq.4).or.(pion.eq.5).or.
     1    (pion.eq.6).or.(pion.eq.7)) j = 7
      if ((pion.eq.2).or.(pion.eq.3)) j = 9 
      if (pion.eq.8) j = 8
c      if (pion.eq.9) j = 7 ! Lambda (Lambda bar) 
       if (pion.eq.9) then  ! pi^-p pi^+pbar
             mj = 8
             j = 11 
       endif

      do i = mj,j
      piplab = dacos(momenta(i,3)/
     &         dSqrt(momenta(i,1)**2+momenta(i,2)**2+momenta(i,3)**2))
     &         *180.d0/pi
      accepted = (accepted.and.(piplab.ge.pi1cut.and.piplab.le.pi2cut))
      enddo 
c -------------------------------------------------------------
c    tagged photons: one photon is tagged, a second photon is 
c    generated everywhere
c -------------------------------------------------------------
      if (tagged.eq.0) then 
      
c --- one of the photons has energy > gmin ---
      accepted = (accepted.and.
     &           (momenta(3,0).ge.gmin.or.momenta(4,0).ge.gmin))

c --- invariant mass of the tagged photon and the pions
c --- (muons,protons,neutrons,kaons) ---
      if (n.eq.2) then 
      do i = 3,4
         accept(i) = .false.
         phot1 = dacos(momenta(i,3)/momenta(i,0))*180.d0/pi
         if (momenta(i,0).ge.gmin.and.
     &      (phot1.ge.phot1cut.and.phot1.le.phot2cut)) then 
            do ij = 0,3
             invmom(ij) = momenta(i,ij)+momenta(5,ij)
            enddo 
            invm2 = invmom(0)**2-invmom(1)**2-invmom(2)**2-invmom(3)**2
            accept(i) = (invm2.ge.q2min)
         endif
      enddo
      accepted = (accepted.and.(accept(3).or.accept(4)))
      endif            
c -------------------------------------------------------------------
c    untagged photons: tag the pions/muons/protons/neutrons/kaons and 
c    look for the missing energy-momentum
c -------------------------------------------------------------------
      else 
      
c --- the missing energy > gmin ---
      accepted=(accepted.and.
     &         ((momenta(3,0)+momenta(4,0)).ge.2.d0*gmin))

c --- missing momentum ---
      piplab = dacos(-momenta(5,3)/
     &         dSqrt(momenta(5,1)**2+momenta(5,2)**2+momenta(5,3)**2))
     &         *180.d0/pi
      accepted = (accepted.and.
     &           (piplab.ge.phot1cut.and.piplab.le.phot2cut))
c -------------------------------------------------------------
      endif
      end
c ====================================================================
c --- Matrix element squared: contract Leptonic and Hadronic tensors -
c --------------------------------------------------------------------
      double precision function Matrix(Leptonic,Hadronic)
      include 'phokhara_6.0.inc'       
      complex*16 Leptonic(0:3,0:3),Hadronic(0:3,0:3)
      double precision metric1,metric2
      integer mu,nu
      
      Matrix = 0.d0
      do mu = 0,3
         metric1 = 1.d0
         if (mu.eq.0) metric1 = -1.d0
         do nu = 0,3
             metric2 = 1.d0
             if (nu.eq.0) metric2 = -1.d0               
             Matrix = Matrix + metric1*metric2*
     &          Leptonic(mu,nu)*Hadronic(mu,nu) 
         enddo
      enddo
      end
c **********************************************************************
c --- Metric tensor ----------------------------------------------------
      double precision function metric(mu,nu)
      implicit none 
      integer mu,nu
      if (mu.ne.nu) then 
         metric = 0.d0
      else 
         if (mu.eq.0) then 
             metric = 1.d0
	 else
	     metric = -1.d0
	 endif
      endif
      end 
c =======================================================================
c     Leptonic tensor for the process                                     
c                                                                         
c         e^+(p1) + e^-(p2) ---->  photon^* + photon                      
c                                                                         
c     ISR at the NLO: virtual corrections + soft photons                  
c                                                                         
c     Sp : CMS energy squared
c     qq : virtuality of the photon coupled to the hadronic system        
c     cosphoton: cosinus of the hard photon-positron angle                
c          in the e^+ e^- CMS system                                       
c     w  : soft photon energy normalized to the CMS energy                 
c ------------------------------------------------------------------------
c                                                                         
c         a00 : coefficient of g(mu,nu)                                   
c         a11 :      "      p1(mu)*p1(nu)/s                               
c         a22 :      "      p2(mu)*p2(nu)/s                               
c         a12 :      "      (p1(mu)*p2(nu)+p2(mu)*p1(nu))/s               
c ------------------------------------------------------------------------
c (c) German Rodrigo 2000                                                 
c ------------------------------------------------------------------------
      subroutine LeptonicTensor1ISR(qq,cosphoton,Leptonic)
      include 'phokhara_6.0.inc' 
      complex*16 Leptonic(0:3,0:3),dggvap,BW_om
      double precision qq,cosphoton,aa_phi,mm_ph,gg_ph,
     &  a00,a11,a22,a12,am1,dps,metric,vac_qq
      integer mu,nu
      common/param_PFF/aa_phi,mm_ph,gg_ph

      dps = (1.d0-qq/Sp)/(32.d0*pi*pi)        ! Phase space factors
c --- vacpol(qq)
      if(ivac.eq.0)then
       vac_qq = 1.d0
      else
c ****************************
c only pi+pi-
       if((pion.eq.0).or.(pion.eq.1))then
         vac_qq = cdabs( 1.d0/(1.d0-dggvap(qq,0.d0))
     1                 - aa_phi*BW_om(mm_ph,gg_ph,qq,1))**2
       else
         vac_qq = cdabs(1.d0/(1.d0-dggvap(qq,0.d0)))**2 
       endif
      endif

c --- ISR ---
      call Bornvirtualsoft(qq,cosphoton,a00,a11,a22,a12,am1)
      do mu = 0,3
         do nu = 0,3
           Leptonic(mu,nu) = dcmplx((a00*metric(mu,nu)+
     &        a11*momenta(1,mu)*momenta(1,nu)/Sp+
     &        a22*momenta(2,mu)*momenta(2,nu)/Sp+
     &        a12*(momenta(1,mu)*momenta(2,nu)+
     &             momenta(2,mu)*momenta(1,nu))/Sp),
     &         pi*am1/Sp*(momenta(1,mu)*momenta(2,nu)-
     &             momenta(2,mu)*momenta(1,nu)))*dps*vac_qq
         enddo
      enddo
      return
      end
c **********************************************************************
c 
      subroutine Bornvirtualsoft(qq,cosphoton,a00,a11,a22,a12,am1)
      include 'phokhara_6.0.inc'
      double precision qq,cosphoton,a00,a11,a22,a12,am1,app,m2,q2,uq2,
     1  b,x,y1,y2,globalfactor,a00NLO,a11NLO,a22NLO,a12NLO,api,
     &  t1,t2,t3,t4,t5,t6,t7,t8,t9,s1,t10,t11,t12,t13,t14,Ny1,Ny2,z,
     &  soft,coll,extramass
      complex*16 cdilog,dcmplx
       
      m2 = me*me/Sp
      q2 = qq/Sp
      uq2 = 1.d0-q2
      b = dSqrt(1.d0-4.d0*m2)
      x = b*cosphoton
      y1 = uq2*(1.d0-x)/2.d0
      y2 = uq2*(1.d0+x)/2.d0
      globalfactor = (4.d0*pi*alpha/Sp)**2/(q2*q2)

c --- LO ---
      a00 = ( 2.d0*m2*Q2*uq2*uq2/(y1*y2)-
     &  (2.d0*q2+y1*y1+y2*y2) )/(y1*y2)
      a11 = (8.d0*m2/y2-4.d0*q2/y1)/y2
      a22 = (8.d0*m2/y1-4.d0*q2/y2)/y1
      a12 = -8.d0*m2/(y1*y2)
      am1 = 0.d0

c --- NLO ---
      if (nlo.ne.0) then    
         api = alpha/pi      
         t1 = dLog(m2)
         t2 = dLog(m2/q2)      
         t3 = pi*pi/3.d0
         t4 = dLog(y1/q2)
         t5 = dLog(y2/q2)
         t6 = dLog(q2)
         t7 = dreal(cdilog(dcmplx(1.d0-1.d0/q2)))
         t8 = dreal(cdilog(dcmplx(-y1/q2)))-t7+dLog(q2+y1)*dLog(y1/q2)
         t9 = dreal(cdilog(dcmplx(-y2/q2)))-t7+dLog(q2+y2)*dLog(y2/q2) 
         s1 = y1*y1+y2*y2      
         t10 = dLog(y1/m2)
	 t11 = dLog(y2/m2)
         t12 = dreal(cdilog(dcmplx(1.d0-y1/m2)))
	 t13 = dreal(cdilog(dcmplx(1.d0-y2/m2)))
         t14 = dreal(cdilog(dcmplx(1.d0-q2)))
         Ny1 = t6*t10+t14+t12-t3/2.d0
         Ny2 = t6*t11+t14+t13-t3/2.d0	 

      a00NLO = ( -q2*uq2/2.d0-y1*y2+
     &  y1/2.d0*(4.d0-y1-3.d0*(1.d0+q2)/(1.d0-y2))*t4+
     &  y2/2.d0*(4.d0-y2-3.d0*(1.d0+q2)/(1.d0-y1))*t5-
     &  (q2+2.d0*y1*y2/uq2)*t6-
     &  (1.d0+(1.d0-y2)**2+y1*q2/y2)*t8-
     &  (1.d0+(1.d0-y1)**2+y2*q2/y1)*t9 )/(y1*y2)

      a11NLO = ( (1.d0+q2)**2*(1.d0/(1.d0-y1)-1.d0/uq2)-
     &  4.d0*(1.d0-y2)*y1/uq2-q2*(1.d0+2.d0/y2)*t4-
     &  q2*(2.d0-3.d0*y1)*(1.d0-y2)**2/(y1*(1.d0-y1)**2)*t5-
     &  2.d0*q2/uq2*((1.d0-y2)*(1.d0/y2+q2/y1+2.d0*y1/uq2)+
     &  2.d0*q2/uq2)*t6-2.d0*q2*(1.d0+1.d0/(y2*y2))*t8-
     &  2.d0*q2*(3.d0+2.d0*q2/y1+q2*q2/(y1*y1))*t9 )/(y1*y2)

      a22NLO = ( (1.d0+q2)**2*(1.d0/(1.d0-y2)-1.d0/uq2)-
     &  4.d0*(1.d0-y1)*y2/uq2-q2*(1.d0+2.d0/y1)*t5-
     &  q2*(2.d0-3.d0*y2)*(1.d0-y1)**2/(y2*(1.d0-y2)**2)*t4-
     &  2.d0*q2/uq2*((1.d0-y1)*(1.d0/y1+q2/y2+2.d0*y2/uq2)+
     &  2.d0*q2/uq2)*t6-2.d0*q2*(1.d0+1.d0/(y1*y1))*t9-
     &  2.d0*q2*(3.d0+2.d0*q2/y2+q2*q2/(y2*y2))*t8 )/(y1*y2)

      a12NLO = ( q2/(1.d0-y1)+q2/(1.d0-y2)-(4.d0*q2+(y1-y2)**2)/uq2-
     &  2.d0*q2/(1.d0-y2)*(1.d0-y1+q2/y2-q2/(2.d0*(1.d0-y2)))*t4-
     &  2.d0*q2/(1.d0-y1)*(1.d0-y2+q2/y1-q2/(2.d0*(1.d0-y1)))*t5-
     &  2.d0*q2*(q2/(y1*y2)+(1.d0+q2-2.d0*y1*y2)/(uq2*uq2))*t6-
     &  2.d0*q2*(1.d0+q2/y2+q2/(y2*y2))*t8-
     &  2.d0*q2*(1.d0+q2/y1+q2/(y1*y1))*t9 )/(y1*y2) 

      am1 = q2*(2.d0*dLog(1.d0-y1)/y1+(1.d0-q2)/(1.d0-y1)+
     &  q2/(1.d0-y1)**2-2.d0*dLog(1.d0-y2)/y2-(1.d0-q2)/(1.d0-y2)-
     &  q2/(1.d0-y2)**2)/(y1*y2) 

c --- NLO mass corrections       
      z = (1.d0-3.d0*q2)/q2
      app = m2 * ( - q2*(t6*dLog(y1**4/(m2*m2*q2))+
     &  4.d0*t14+t12-t3/2.d0) - uq2*(1.d0-t10+
     &  (m2/y1)*(t12-t3/2.d0)) )/(y1*y1)+ q2*extramass(m2,y1,z)/2.d0
     &    + m2 * ( - q2*(t6*dLog(y2**4/(m2*m2*q2))+
     &  4.d0*t14+t13-t3/2.d0) - uq2*(1.d0-t11+
     &  (m2/y2)*(t13-t3/2.d0)) )/(y2*y2)+ q2*extramass(m2,y2,z)/2.d0

      a00NLO = a00NLO - app 
c      a11NLO = a11NLO - 4.d0*q2*app/uq2**2 
c      a22NLO = a22NLO - 4.d0*q2*app/uq2**2
c      a12NLO = a12NLO - 4.d0*q2*app/uq2**2

      z = (3.d0-8.d0*q2+6.d0*q2*q2)/(1.d0-2.d0*q2*q2)
      a11NLO = a11NLO + q2/uq2 * ( 
     &  4.d0*m2/(y1*y1) * (1.d0-t10+(m2/y1)*(t12-t3/2.d0)) - 
     &  extramass(m2,y1,1.d0)+2.d0*m2*q2/(y1*(m2*uq2-y1))*
     &  (t10/q2+t6/uq2+(1.d0+m2/(m2*uq2-y1))*Ny1)) + 
     &  1.d0/uq2 * ( 4.d0*m2*uq2/(y2*y2)* 
     &  (t6*dLog(y2**4/(m2*m2*q2))+4.d0*t14+2.d0*t13-t3)+ 
     &  4.d0*m2*q2/(y2*y2)*(1.d0-t11+(1.d0+m2/y2)*(t13-t3/2.d0))-
     &  (1.d0-2.d0*q2*q2)/q2*extramass(m2,y2,z)+
     &  2.d0*m2/(y2*(m2*uq2-y2))*
     &  (t11/q2+t6/uq2+(3.d0+m2/(m2*uq2-y2))*Ny2))

      a22NLO = a22NLO + q2/uq2 * ( 
     &  4.d0*m2/(y2*y2) * (1.d0-t11+(m2/y2)*(t13-t3/2.d0)) - 
     &  extramass(m2,y2,1.d0)+2.d0*m2*q2/(y2*(m2*uq2-y2))*
     &  (t11/q2+t6/uq2+(1.d0+m2/(m2*uq2-y2))*Ny2)) + 
     &  1.d0/uq2 * ( 4.d0*m2*uq2/(y1*y1)* 
     &  (t6*dLog(y1**4/(m2*m2*q2))+4.d0*t14+2.d0*t12-t3)+ 
     &  4.d0*m2*q2/(y1*y1)*(1.d0-t10+(1.d0+m2/y1)*(t12-t3/2.d0))-
     &  (1.d0-2.d0*q2*q2)/q2*extramass(m2,y1,z)+
     &  2.d0*m2/(y1*(m2*uq2-y1))*
     &  (t10/q2+t6/uq2+(3.d0+m2/(m2*uq2-y1))*Ny1))

      z = 1.d0/uq2
      a12NLO = a12NLO + q2/uq2 * ( 
     &  4.d0*m2/(y1*y1)*(1.d0-t10+(.5d0+m2/y1)*(t12-t3/2.d0))-
     &  uq2/q2*extramass(m2,y1,z)+2.d0*m2/(y1*(m2*uq2-y1))*
     &  (t10/q2+t6/uq2+(2.d0+m2/(m2*uq2-y1))*Ny1) +
     &  4.d0*m2/(y2*y2)*(1.d0-t11+(.5d0+m2/y2)*(t13-t3/2.d0))-
     &  uq2/q2*extramass(m2,y2,z)+2.d0*m2/(y2*(m2*uq2-y2))*
     &  (t11/q2+t6/uq2+(2.d0+m2/(m2*uq2-y2))*Ny2) )

c --- soft and collinear logs 
      soft = -dLog(4.d0*w*w)*(1.d0+t1)
      coll = (-1.5d0*t2-2.d0+t3)

c --- final result
      a00 = a00 + api*(a00*(soft+coll)+a00NLO)
      a11 = a11 + api*(a11*(soft+coll)+a11NLO)
      a22 = a22 + api*(a22*(soft+coll)+a22NLO)
      a12 = a12 + api*(a12*(soft+coll)+a12NLO)                   
      am1 = api*am1
      endif 

      a00 = globalfactor * a00
      a11 = globalfactor * a11
      a22 = globalfactor * a22
      a12 = globalfactor * a12
      am1 = globalfactor * am1
      return 
      end
c **********************************************************************
      double precision function extramass(m2,y,z)
      implicit none
      double precision m2,y,z
      integer n
      extramass = (1.d0+z*dLog(y/m2))/y
      if ((m2-y)**2.le.m2*m2/4.d0) then 
         do n = 0,4
            extramass = extramass - (1.d0/(dble(n)+2.d0)+
     &         z/(dble(n)+1.d0))*(m2-y)**n/(m2**(n+1))
         enddo
      else
         extramass = extramass + (1.d0+z*dLog(y/m2))/(m2-y) +
     &      m2*dLog(y/m2)/(m2-y)**2
      endif
      end
c ============================================================================
c     Hadronic Tensor for the process                                     
c                                                                         
c     photon^* (Q2) -----> mu^+ mu^-, pi^+ pi^-, 2pi^0 pi^+ pi^-, 2pi^+ 2pi^-, 
c                          p pbar, n nbar, K^+ K^-, K^0 K^0bar, pi^+ pi^- pi^0,
c                          lambda lambdabar
c ----------------------------------------------------------------------------
      subroutine HadronicTensorISR(qq,q0p,q2p,q0b,q2b,Hadronic)
      include 'phokhara_6.0.inc'       
      double precision qq,pionFF,q0p,q2p,q0b,q2b,metric,PionFormFactor2,
     1    dps,q1(4),q2(4),q3(4),q4(4),rlam,a,b,c,KaonFormFactor2,mmu1
      complex*16 Hadronic(0:3,0:3),hadr(4),hadr_3pi(4)
      real*8 protGE2,protGM2,tau_pp
      real*8 lambGE2,lambGM2,tau_ll,t1_ll,aa_ll,qqp_ll(0:3),qqm_ll(0:3)
      real*8 mm_phi_lam,mm_om_lam,mu_lamb,phase_f2_lamb
      integer mu,nu,i
      complex*16 protF1,protF2,GM_pp,GE_pp,lambF1,lambF2,GM_ll,GE_ll
      common/lambF1F2/lambF1,lambF2,tau_ll,GM_ll,GE_ll,lambGM2,lambGE2,
     1                t1_ll,aa_ll,qqp_ll,qqm_ll
      common/lambparam/mm_phi_lam,mm_om_lam,mu_lamb,phase_f2_lamb
c
      rlam(a,b,c) = sqrt( (1.d0-(b+c)**2/a) * (1.d0-(b-c)**2/a) )
c
c --- muons ---      
      if (pion.eq.0)  then 
      pionFF = 16.d0*pi*alpha
      dps =  dSqrt(1.d0-4.d0*mmu*mmu/qq)/(32.d0*pi*pi)  ! Phase space factors
      do mu = 0,3
         do nu = 0,3
           Hadronic(mu,nu) = pionFF*(momenta(6,mu)*momenta(7,nu)+
     &        momenta(7,mu)*momenta(6,nu)-qq/2.d0*metric(mu,nu))*dps
         enddo
      enddo
     
c --- pions pi^+ pi^- ---        
      elseif(pion.eq.1)then
      
      pionFF = 4.d0*pi*alpha*PionFormFactor2(qq)
      dps =  dSqrt(1.d0-4.d0*mpi*mpi/qq)/(32.d0*pi*pi)  ! Phase space factors
      do mu = 0,3
         do nu = 0,3
            Hadronic(mu,nu) = pionFF*(momenta(6,mu)-momenta(7,mu))*
     &         (momenta(6,nu)-momenta(7,nu))*dps 
         enddo
      enddo
c
c --- pions 2pi^0 pi^+ pi^- --- pion=2
c --- pions 2pi^+ 2pi^-     --- pion=3
c        
      elseif((pion.eq.2).or.(pion.eq.3))then
c
      do i =0,3
       q1(i+1) = momenta(6,i)  
       q2(i+1) = momenta(7,i) 
       q3(i+1) = momenta(8,i)  
       q4(i+1) = momenta(9,i) 
      enddo
c
      pionFF = 4.d0*pi*alpha
c
c          Phase space factors
c
      dps = 1.d0/(2.d0*pi)**2/(32.d0*pi**2)**3
     1     * rlam(qq,q0p,rmass(1)) 
     2     * rlam(q2p,q0b,rmass(2)) 
     3     * rlam(q2b,rmass(3),rmass(4))
c
c --- pions 2pi^0 pi^+ pi^-
c
       if(pion.eq.2)then
        dps = dps * 0.5d0
c
        call had3(qq,q1,q2,q3,q4,hadr)
       endif
c
c --- pions 2pi^+ 2pi^-  
c
       if(pion.eq.3)then
        dps = dps * 0.25d0
c
        call had2(qq,q1,q2,q3,q4,hadr)
       endif
c
      do mu = 0,3
         do nu = 0,3
           Hadronic(mu,nu) = pionFF*hadr(mu+1)*conjg(hadr(nu+1))*dps 
         enddo
      enddo
c
c----- PPbar (pion=4) and  NNbar (pion=5) ----------------
      elseif ((pion.eq.4).or.(pion.eq.5))  then 

      call  ProtonFormFactor(qq,protF1,protF2)
      
      if (pion.eq.4) mmu1 = mp
      if (pion.eq.5) mmu1 = mnt

      tau_pp = qq/4.D0/mmu1**2
      protGM2=cdabs(protF1+protF2)**2
      protGE2=cdabs(protF1+tau_pp*protF2)**2

      pionFF = 4.d0*pi*alpha
      dps =  dSqrt(1.d0-4.d0*mmu1**2/qq)/(32.d0*pi*pi)  ! Phase space factors
      do mu = 0,3
         do nu = 0,3
          Hadronic(mu,nu) = pionFF*dps*2.D0*(
     &      (momenta(7,mu)-momenta(6,mu))*(momenta(7,nu)-momenta(6,nu))
     &     *( protGE2 - protGM2 )/(tau_pp - 1.D0)
     &     -(momenta(7,mu)-momenta(6,mu))*(momenta(7,nu)-momenta(6,nu))
     &     *protGM2 - metric(mu,nu)*protGM2*qq 
     &     +(momenta(7,mu)+momenta(6,mu))*(momenta(7,nu)+momenta(6,nu))
     &     *protGM2 )
         enddo
      enddo
c
c ---- kaons K^+ K^- --------------
      elseif(pion.eq.6)then
      
      pionFF = 4.d0*pi*alpha*KaonFormFactor2(qq)
      dps =  dSqrt(1.d0-4.d0*mKp*mKp/qq)/(32.d0*pi*pi)  ! Phase space factors
      do mu = 0,3
         do nu = 0,3
            Hadronic(mu,nu) = pionFF*(momenta(6,mu)-momenta(7,mu))*
     &         (momenta(6,nu)-momenta(7,nu))*dps 
         enddo
      enddo
c
c ---- kaons K^0 K^0bar -----------
      elseif(pion.eq.7)then
      
      pionFF = 4.d0*pi*alpha*KaonFormFactor2(qq)
      dps =  dSqrt(1.d0-4.d0*mKn*mKn/qq)/(32.d0*pi*pi)  ! Phase space factors
      do mu = 0,3
         do nu = 0,3
            Hadronic(mu,nu) = pionFF*(momenta(6,mu)-momenta(7,mu))*
     &         (momenta(6,nu)-momenta(7,nu))*dps 
         enddo
      enddo
c
c ---- 3 pions : pi^+ pi^- pi^0 --------------
      elseif(pion.eq.8)then

      do i =0,3
       q1(i+1) = momenta(6,i)  
       q2(i+1) = momenta(7,i) 
       q3(i+1) = momenta(8,i)  
      enddo
c
c        Phase space factors
c
      dps = 1.d0/(2.d0*pi)/(32.d0*pi**2)**2
     1    * rlam(qq,q0p,rmass(1)) * rlam(q2p,rmass(2),rmass(3))

       pionFF = 4.d0*pi*alpha

       call had_3pi(qq,q1,q2,q3,hadr_3pi)

      do mu = 0,3
         do nu = 0,3
           Hadronic(mu,nu) = pionFF * hadr_3pi(mu+1)
     1                     * conjg(hadr_3pi(nu+1)) * dps 
         enddo
      enddo
c
c----- Lambda (Lambda bar) pion=9  ----------------
      elseif (pion.eq.9)  then 

      call  LambdaFormFactor(qq,tau_ll,lambF1,lambF2)

      GM_ll = lambF1+lambF2
      GE_ll = ( lambF1+tau_ll*lambF2 ) 
     1      * exp(dcmplx(0.d0,phase_f2_lamb*pi/180.d0))
      lambGM2=cdabs(GM_ll)**2
      lambGE2=cdabs(GE_ll)**2
      t1_ll = tau_ll - 1.D0
      aa_ll = - 2.d0/t1_ll* (tau_ll * lambGM2 - lambGE2)
      do i=0,3
         qqp_ll(i) = momenta(6,i)+momenta(7,i)
         qqm_ll(i) = (momenta(7,i)-momenta(6,i))/2.d0
      enddo

      do mu = 0,3
         do nu = 0,3
          Hadronic(mu,nu) = 2.d0* lambGM2* (qqp_ll(mu) * qqp_ll(nu) 
     1    - metric(mu,nu)*qq) + 4.d0 * aa_ll * qqm_ll(mu)*qqm_ll(nu) 
         enddo
      enddo

      else
       continue
      endif
c
      return
      end
c ----------------------------------------------------------------------------
      subroutine HadroLamb(qq,Hadronic,HadronicLamb)
      include 'phokhara_6.0.inc'       
      double precision qq,metric
      real*8 lambGE2,lambGM2,tau_ll,t1_ll,veclamb1(0:3),veclamb1_d(0:3),
     1       veclamb2(0:3),veclamb2_d(0:3),qqp_ll(0:3),qqp_d_ll(0:3),
     2       qqm_ll(0:3),qqm_d_ll(0:3),aa_ll,alS1pS2_ll(0:3),
     3       veceps_qp_qm_S_ll(0:3),tenseps_qp_qm_ll(0:3,0:3)
      real*8 qqpS1_ll,qqpS2_ll,S1S2_ll,scal_qS1qS2_ll
      complex*16 HadronicLamb(0:3,0:3),lambF1,lambF2,Hadronic(0:3,0:3),
     1           GM_ll,GE_ll,lambGMGEc,lambTT,lambGMmGE2,iiM_ll
      integer mu,nu,jj
      common/veclamb/veclamb1,veclamb2
      common/skalLamb/qqpS1_ll,qqpS2_ll,S1S2_ll
      common/lambF1F2/lambF1,lambF2,tau_ll,GM_ll,GE_ll,lambGM2,lambGE2,
     1                t1_ll,aa_ll,qqp_ll,qqm_ll

      call skalarLamb()
      
      lambGMGEc = GM_ll*conjg(GE_ll)
      lambGMmGE2= cdabs(GM_ll-GE_ll)**2 / mlamb**2/t1_ll**2
      lambTT = (tau_ll*lambGM2 - lambGMGEc)/t1_ll
      iiM_ll = (0.d0,1.d0) / mlamb / t1_ll 

      scal_qS1qS2_ll = - lambGM2 * 0.5d0 
     1                 * alpha_lamb * ( qqpS1_ll + qqpS2_ll ) 

      veclamb1_d(0) = veclamb1(0)
      veclamb2_d(0) = veclamb2(0)
      qqp_d_ll(0)   = qqp_ll(0)
      qqm_d_ll(0)   = qqm_ll(0)
      alS1pS2_ll(0) = alpha_lamb*( veclamb1_d(0) - veclamb2_d(0) )
      do jj = 1,3
         veclamb1_d(jj) = - veclamb1(jj)
         veclamb2_d(jj) = - veclamb2(jj)
         qqp_d_ll(jj)   = - qqp_ll(jj)
         qqm_d_ll(jj)   = - qqm_ll(jj)
         alS1pS2_ll(jj) = alpha_lamb*( veclamb1_d(jj) - veclamb2_d(jj) )
      enddo 

      call Fcoeff_aabb_ll(qqp_d_ll,qqm_d_ll,alS1pS2_ll,scal_qS1qS2_ll,
     1                    veceps_qp_qm_S_ll,tenseps_qp_qm_ll)

      do mu = 0,3
         do nu = 0,3

          HadronicLamb(mu,nu) =   
     1    Hadronic(mu,nu) * 0.25d0  - iiM_ll 
     2 * ( - lambGMGEc        * veceps_qp_qm_S_ll(mu) * qqm_ll(nu)
     3     + conjg(lambGMGEc) * veceps_qp_qm_S_ll(nu) * qqm_ll(mu) 
     4     + tenseps_qp_qm_ll(mu,nu) ) 
     5 - alpha_lamb**2 
     2 * (  lambGM2 * 0.5d0 *( qqpS2_ll*(qqp_ll(mu)*veclamb1(nu)
     3 + qqp_ll(nu)*veclamb1(mu) ) + qqpS1_ll*( qqp_ll(mu)*veclamb2(nu)
     3 + qqp_ll(nu)*veclamb2(mu) ) - S1S2_ll* qqp_ll(mu)* qqp_ll(nu)
     4 - qq*( veclamb1(mu)*veclamb2(nu)+veclamb1(nu)*veclamb2(mu) ) )
     5 + lambGM2* ( 0.5d0*qq*S1S2_ll - qqpS1_ll*qqpS2_ll )*metric(mu,nu) 
     6 + ( lambGMmGE2 * qqpS1_ll * qqpS2_ll 
     7 - aa_ll*S1S2_ll ) * qqm_ll(mu)*qqm_ll(nu) + conjg(lambTT) 
     8 * ( qqpS2_ll * qqm_ll(mu)*veclamb1(nu) - qqpS1_ll * qqm_ll(mu) 
     9 * veclamb2(nu) ) +  lambTT * ( qqpS2_ll * qqm_ll(nu)
     1 * veclamb1(mu) - qqpS1_ll * qqm_ll(nu) * veclamb2(mu) ) )

         enddo
      enddo

      return
      end
c **********************************************************************
      subroutine Fcoeff_aabb_ll(qqp,qqm,alS1pS2,scal,vec,tens)
      implicit none
      real*8 qqp(0:3),qqm(0:3),alS1pS2(0:3),vec(0:3),tens(0:3,0:3),
     1       scal
      integer jj
      
c --- epsylon uper indeces ---------------------------------------------
c      epsyl(0,1,2,3) = 1.d0          epsyl(0,1,3,2) = -1.d0
c      epsyl(0,2,3,1) = 1.d0          epsyl(0,2,1,3) = -1.d0
c      epsyl(0,3,1,2) = 1.d0          epsyl(0,3,2,1) = -1.d0
c      epsyl(1,0,3,2) = 1.d0          epsyl(1,0,2,3) = -1.d0
c      epsyl(1,2,0,3) = 1.d0          epsyl(1,2,3,0) = -1.d0
c      epsyl(1,3,2,0) = 1.d0          epsyl(1,3,0,2) = -1.d0
c      epsyl(2,1,3,0) = 1.d0          epsyl(2,1,0,3) = -1.d0
c      epsyl(2,0,1,3) = 1.d0          epsyl(2,0,3,1) = -1.d0
c      epsyl(2,3,0,1) = 1.d0          epsyl(2,3,1,0) = -1.d0
c      epsyl(3,1,0,2) = 1.d0          epsyl(3,1,2,0) = -1.d0
c      epsyl(3,0,2,1) = 1.d0          epsyl(3,0,1,2) = -1.d0
c      epsyl(3,2,1,0) = 1.d0          epsyl(3,2,0,1) = -1.d0

      vec(0) = qqp(1)*qqm(3)*alS1pS2(2) + qqp(2)*qqm(1)*alS1pS2(3)
     1       + qqp(3)*qqm(2)*alS1pS2(1) - qqp(1)*qqm(2)*alS1pS2(3)
     2       - qqp(2)*qqm(3)*alS1pS2(1) - qqp(3)*qqm(1)*alS1pS2(2)

      vec(1) = qqp(0)*qqm(2)*alS1pS2(3) + qqp(2)*qqm(3)*alS1pS2(0)
     1       + qqp(3)*qqm(0)*alS1pS2(2) - qqp(0)*qqm(3)*alS1pS2(2)
     2       - qqp(2)*qqm(0)*alS1pS2(3) - qqp(3)*qqm(2)*alS1pS2(0)

      vec(2) = qqp(0)*qqm(3)*alS1pS2(1) + qqp(1)*qqm(0)*alS1pS2(3)
     1       + qqp(3)*qqm(1)*alS1pS2(0) - qqp(0)*qqm(1)*alS1pS2(3)
     2       - qqp(1)*qqm(3)*alS1pS2(0) - qqp(3)*qqm(0)*alS1pS2(1)

      vec(3) = qqp(0)*qqm(1)*alS1pS2(2) + qqp(1)*qqm(2)*alS1pS2(0)
     1       + qqp(2)*qqm(0)*alS1pS2(1) - qqp(0)*qqm(2)*alS1pS2(1)
     2       - qqp(1)*qqm(0)*alS1pS2(2) - qqp(2)*qqm(1)*alS1pS2(0)
       
      do jj = 0,3
         tens(jj,jj) = 0.d0
      enddo

      tens(0,1) = scal * ( qqp(2) * qqm(3) - qqp(2) * qqm(3) )
      tens(1,0) = - tens(0,1)

      tens(0,2) = scal * ( qqp(3) * qqm(1) - qqp(1) * qqm(3) )
      tens(2,0) = - tens(0,2)  

      tens(0,3) = scal * ( qqp(1) * qqm(2) - qqp(2) * qqm(1) )
      tens(3,0) = - tens(0,3)

      tens(1,2) = scal * ( qqp(0) * qqm(3) - qqp(3) * qqm(0) )
      tens(2,1) = - tens(1,2)

      tens(1,3) = scal * ( qqp(2) * qqm(0) - qqp(0) * qqm(2) )
      tens(3,1) = - tens(1,3)

      tens(2,3) = scal * ( qqp(0) * qqm(1) - qqp(1) * qqm(0) )
      tens(3,2) = - tens(2,3)

      return
      end
c **********************************************************************
      subroutine skalarLamb()
      include 'phokhara_6.0.inc'       

      real*8 veclamb1(0:3),veclamb2(0:3),qqp_ll(0:3)
      real*8 qqpS1_ll,qqpS2_ll,S1S2_ll
      integer i
      common /veclamb/ veclamb1,veclamb2
      common /skalLamb/ qqpS1_ll,qqpS2_ll,S1S2_ll

      do i=0,3
         qqp_ll(i) = momenta(6,i)+momenta(7,i)
      enddo
c ------
      qqpS1_ll  = qqp_ll(0) * veclamb1(0)
      qqpS2_ll  = qqp_ll(0) * veclamb2(0)
      S1S2_ll   = veclamb1(0) * veclamb2(0)
      do i=1,3
         qqpS1_ll  = qqpS1_ll  - qqp_ll(i) * veclamb1(i)
         qqpS2_ll  = qqpS2_ll  - qqp_ll(i) * veclamb2(i)
         S1S2_ll   = S1S2_ll   - veclamb1(i) * veclamb2(i)
      enddo
c ------
      return
      end
c **********************************************************************
      subroutine LambdaFormFactor(qq,tau_ll,lambF1,lambF2) 
      include 'phokhara_6.0.inc'       
      real*8 qq,tau_ll,mm_phi_lam2,mm_om_lam2,mm_om1_lam2,mm_om2_lam2,
     1       mm_phi1_lam2,mm_phi2_lam2,const_model_lamb
      real*8 mm_phi_lam,mm_om_lam,mu_lamb,phase_f2_lamb    
      complex*16 lambF1,lambF2,F1om_ll,F1phi_ll,F2om_ll,F2phi_ll
      common/lambparam/mm_phi_lam,mm_om_lam,mu_lamb,phase_f2_lamb

      const_model_lamb = 0.9d0

      mm_om_lam2  = mm_om_lam**2
      mm_om1_lam2 = mm_om_lam2 + 1.d0/const_model_lamb
      mm_om2_lam2 = mm_om_lam2 + 2.d0/const_model_lamb

      mm_phi_lam2  = mm_phi_lam**2
      mm_phi1_lam2 = mm_phi_lam2 + 1.d0/const_model_lamb   
      mm_phi2_lam2 = mm_phi_lam2 + 2.d0/const_model_lamb   

      tau_ll = qq/4.d0/mlamb**2

      F1om_ll  = mm_om_lam2 * mm_om1_lam2 /(mm_om_lam2-qq)
     1         / (mm_om1_lam2-qq)
      F1phi_ll = mm_phi_lam2 * mm_phi1_lam2 /(mm_phi_lam2-qq)
     1         / (mm_phi1_lam2-qq)

      F2om_ll  = mm_om_lam2 * mm_om1_lam2 * mm_om2_lam2
     1         /(mm_om_lam2-qq)/(mm_om1_lam2-qq)/(mm_om2_lam2-qq)

      F2phi_ll = mm_phi_lam2 * mm_phi1_lam2 * mm_phi2_lam2
     1         /(mm_phi_lam2-qq)/(mm_phi1_lam2-qq)/(mm_phi2_lam2-qq)

      lambF1 = ( F1om_ll - F1phi_ll ) / 3.d0
      lambF2 = - ( F2om_ll + mu_lamb*F2phi_ll ) / 3.d0

      return
      end
c **********************************************************************
      double precision function PionFormFactor2(a)
      include 'phokhara_6.0.inc'       
      double precision a
      complex*16 PionFormFactor
       
      PionFormFactor2= PionFormFactor(a)*dconjg(PionFormFactor(a))
c
      return
      end
c **********************************************************************
      complex*16 function PionFormFactor(a)
      include 'phokhara_6.0.inc'       
      double precision a         
      real*8 mm_ph,gg_ph,aa_phi,c_0_pion,c_1_pion,c_2_pion,c_3_pion,
     1       c_n_pion,c_om_pion
      complex*16 BW,BW_rho,BW_GS,BW_om,c_sum,appr_sum
      common/param_pion/c_0_pion,c_1_pion,c_2_pion,c_3_pion,c_n_pion,
     1                  c_om_pion   
      common/param_PFF/aa_phi,mm_ph,gg_ph

      c_sum = appr_sum(a)

      if(FF_Pion.eq.0)then
      PionFormFactor = 
     1   c_0_pion*BW_rho(m_rho0_pion,g_rho0_pion,a,1)/
     2     (1.d0+c_om_pion)*
     1     (1.d0+c_om_pion*BW_rho(m_om0_pion,g_om0_pion,a,1)) 
     4 + c_1_pion*BW_rho(m_rho1_pion,g_rho1_pion,a,1) 
     3 + c_2_pion*BW_rho(m_rho2_pion,g_rho2_pion,a,1) 
     4 + c_3_pion*BW_rho(m_rho3_pion,g_rho3_pion,a,1) 
     5 + c_sum

      elseif(FF_Pion.eq.1)then
      PionFormFactor = 
     1   c_0_pion*BW_GS(m_rho0_pion,g_rho0_pion,a,1)/
     2     (1.d0+c_om_pion)*
     1     (1.d0+c_om_pion*BW_rho(m_om0_pion,g_om0_pion,a,1)) 
     2 + c_1_pion*BW_GS(m_rho1_pion,g_rho1_pion,a,1) 
     3 + c_2_pion*BW_GS(m_rho2_pion,g_rho2_pion,a,1) 
     4 + c_3_pion*BW_rho(m_rho3_pion,g_rho3_pion,a,1) 
     5 + c_sum
      endif

      return
      end
c **********************************************************************
      complex*16 function PionFormFactor_3pi(qq2)
      include 'phokhara_6.0.inc'       

      real*8 qq2,omm_PDG,omg_PDG,qq12_3pi,qq13_3pi,qq23_3pi
      real*8 omm0_3pi,omg0_3pi,omm1_3pi,omg1_3pi,omm2_3pi,omg2_3pi,
     1  phim0_3pi,phig0_3pi,rhom0m_3pi,rhog0m_3pi,rhom0p_3pi,rhog0p_3pi,
     1  rhom0z_3pi,rhog0z_3pi,rhom1m_3pi,rhog1m_3pi,rhom1p_3pi,
     2  rhog1p_3pi,rhom1z_3pi,rhog1z_3pi,rhom2m_3pi,rhog2m_3pi,
     3  rhom2p_3pi,rhog2p_3pi,rhom2z_3pi,rhog2z_3pi,
     4  aa_3pi,bb_3pi,dd_3pi,ee_3pi,gg_3pi,jj_3pi,kk_3pi
      complex*16 RR_3pi,HH_3pi,RRro_3pi

      common/mass_3pi/omm0_3pi,omg0_3pi,omm1_3pi,omg1_3pi,omm2_3pi,
     1                omg2_3pi,phim0_3pi,phig0_3pi 
      common/rho_3pi/rhom0m_3pi,rhog0m_3pi,rhom0p_3pi,rhog0p_3pi,
     1      rhom0z_3pi,rhog0z_3pi,rhom1m_3pi,rhog1m_3pi,rhom1p_3pi,
     2      rhog1p_3pi,rhom1z_3pi,rhog1z_3pi,rhom2m_3pi,rhog2m_3pi,
     3      rhom2p_3pi,rhog2p_3pi,rhom2z_3pi,rhog2z_3pi
      common/formf_3pi/aa_3pi,bb_3pi,dd_3pi,ee_3pi,gg_3pi,jj_3pi,kk_3pi
      common/qqij_3pi/qq12_3pi,qq13_3pi,qq23_3pi

c PDG 2004
       omm_PDG = 0.78259d0
       omg_PDG = 0.00849d0

       PionFormFactor_3pi = 
     1 ( aa_3pi * RR_3pi(omm0_3pi,omg0_3pi,qq2) 
     2  + bb_3pi * RR_3pi(phim0_3pi,phig0_3pi,qq2) ) *
     2    HH_3pi(rhom0m_3pi,rhog0m_3pi,
     3                      rhom0p_3pi,rhog0p_3pi,rhom0z_3pi,rhog0z_3pi)
     4 + dd_3pi * RR_3pi(omm2_3pi,omg2_3pi,qq2) * 
     5    HH_3pi(rhom2m_3pi,rhog2m_3pi,
     8                      rhom2p_3pi,rhog2p_3pi,rhom2z_3pi,rhog2z_3pi)
     5 + ee_3pi * RR_3pi(phim0_3pi,phig0_3pi,qq2) *
     4    HH_3pi(rhom1m_3pi,rhog1m_3pi,
     7                      rhom1p_3pi,rhog1p_3pi,rhom1z_3pi,rhog1z_3pi) 
     8 + gg_3pi 
     1  * (RRro_3pi(qq2,0.77609d0,0.14446d0)/0.77609d0**2
     2      -0.1d0*RRro_3pi(qq2,1.7d0,0.26d0)/1.7d0**2)
     9    *RR_3pi(omm_PDG,omg_PDG,qq12_3pi)/omm_PDG**2  
     6 + jj_3pi * RR_3pi(omm1_3pi,omg1_3pi,qq2) *
     2    HH_3pi(rhom0m_3pi,rhog0m_3pi,
     3                      rhom0p_3pi,rhog0p_3pi,rhom0z_3pi,rhog0z_3pi)
     6 + kk_3pi * RR_3pi(omm2_3pi,omg2_3pi,qq2) *
     2    HH_3pi(rhom0m_3pi,rhog0m_3pi,
     3                      rhom0p_3pi,rhog0p_3pi,rhom0z_3pi,rhog0z_3pi)

      return
      end
c **********************************************************************
      double precision function KaonFormFactor2(a)
      include 'phokhara_6.0.inc'              
      double precision a
      complex*16 KaonFormFactor

      KaonFormFactor2 = KaonFormFactor(a)*dconjg(KaonFormFactor(a))
c
      return
      end
c **********************************************************************
      complex*16 function KaonFormFactor(a)
      include 'phokhara_6.0.inc'       
      double precision a
      real*8 c_phi0_Kp,c_phi1_Kp,c_rho0_Kp,c_rho1_Kp,c_rho2_Kp
     1      ,c_om0_Kp,c_om1_Kp,c_om2_Kp,eta_phi
      complex*16 BW_K,BW_om,BW_rho

      common/param_Kp/c_phi0_Kp,c_phi1_Kp,c_rho0_Kp,c_rho1_Kp,c_rho2_Kp,
     1                c_om0_Kp,c_om1_Kp,c_om2_Kp,eta_phi

      if(pion.eq.6)then
         KaonFormFactor = 
     1   0.5d0 * ( c_rho0_Kp * BW_rho(m_rho0_Kp,g_rho0_Kp,a,1) +
     5             c_rho1_Kp * BW_rho(m_rho1_Kp,g_rho1_Kp,a,1) + 
     2             c_rho2_Kp * BW_rho(m_rho2_Kp,g_rho2_Kp,a,1) )
     3 + 1.d0/6.d0 * ( c_om0_Kp * BW_om(m_om0_Kp,g_om0_Kp,a,1) +
     1                 c_om1_Kp * BW_om(m_om1_Kp,g_om1_Kp,a,1) + 
     2                 c_om2_Kp * BW_om(m_om2_Kp,g_om2_Kp,a,1) ) 
     4 + 1.d0/3.d0 * ( c_phi0_Kp * BW_K(m_phi0_Kp,g_phi0_Kp,a,1) +
     1                 c_phi1_Kp*BW_K(m_phi1_Kp,g_phi1_Kp,a,1) )
      elseif(pion.eq.7)then
         KaonFormFactor = 
     1 - 0.5d0 * ( c_rho0_Kp * BW_rho(m_rho0_Kp,g_rho0_Kp,a,1) +
     5             c_rho1_Kp * BW_rho(m_rho1_Kp,g_rho1_Kp,a,1) + 
     2             c_rho2_Kp * BW_rho(m_rho2_Kp,g_rho2_Kp,a,1) )
     3 + 1.d0/6.d0 * ( c_om0_Kp * BW_om(m_om0_Kp,g_om0_Kp,a,1) +
     1                 c_om1_Kp * BW_om(m_om1_Kp,g_om1_Kp,a,1) + 
     2                 c_om2_Kp * BW_om(m_om2_Kp,g_om2_Kp,a,1) ) 
     4 + 1.d0/3.d0*( eta_phi*c_phi0_Kp*BW_K(m_phi0_Kp,g_phi0_Kp,a,1) +
     1               c_phi1_Kp*BW_K(m_phi1_Kp,g_phi1_Kp,a,1) )

      endif

      return
      end
c **********************************************************************
      complex*16 function BW_om(m,breite,x,k)
      implicit none       
      integer k
      double precision m,breite,x
      complex *16 i
      i=(0.d0,1.d0)

      if(k.eq.1)then
         BW_om=m*m/(m*m-x-i*m*breite)
      else
         BW_om=m*m/(m*m-x+i*m*breite)
      endif
      return
      end
c **********************************************************************
      complex*16 function BW_K(m,breite,x,k)
      include 'phokhara_6.0.inc'       
      integer k
      double precision m,breite,x,g
      complex *16 i

      if(pion.eq.6) g=breite*m*m/x*((x-4.d0*mKp*mKp)/
     &     (m*m-4.d0*mKp*mKp))**(1.5d0)
      if(pion.eq.7) g=breite*m*m/x*((x-4.d0*mKn*mKn)/
     &     (m*m-4.d0*mKn*mKn))**(1.5d0)

      i=(0.d0,1.d0)
      if(k.eq.1)then
         BW_K=m*m/(m*m-x-i*sqrt(x)*g)
      else
         BW_K=m*m/(m*m-x+i*sqrt(x)*g)
      endif
      return
      end
c **********************************************************************
      complex*16 function BW_rho(m,breite,x,k)
      include 'phokhara_6.0.inc'              
      integer k
      double precision m,breite,x,g
      complex *16 i

         g=breite*m*m/x*((x-4.d0*mpi*mpi)/
     &     (m*m-4.d0*mpi*mpi))**(1.5d0)

      i=(0.d0,1.d0)
      if(k.eq.1)then
         BW_rho=m*m/(m*m-x-i*sqrt(x)*g)
      else
         BW_rho=m*m/(m*m-x+i*sqrt(x)*g)
      endif
      return
      end
c **********************************************************************
      complex*16 function RR_3pi(mm,mmg,qq2)
      implicit none
      real*8 mm,mmg,qq2
      complex*16 i

      i = dcmplx(0.d0,1.d0)
      RR_3pi = 1.d0/(qq2/mm**2 - 1.d0 + i*mmg/mm)
      return
      end
c **********************************************************************
      complex*16 function BW_GS(m,breite,x,k)
      include 'phokhara_6.0.inc'       
      integer k
      double precision m,breite,x,g,HH_GS,dd,p_rho
      complex *16 i

         g=breite*m*m/x*((x-4.d0*mpi*mpi)/
     &     (m*m-4.d0*mpi*mpi))**(1.5d0)

      i=(0.d0,1.d0)

      p_rho = sqrt(m*m-4.d0*mpi*mpi) / 2.d0

      dd = 3.d0/2.d0/pi * mpi**2 / p_rho**2 
     1   * log( ( m + 2.d0*p_rho )**2 / 4.d0/mpi**2 )
     2   + m/2.d0/pi/p_rho 
     3   - mpi**2 * m /pi/p_rho**3

      if(k.eq.1)then
         BW_GS=(m*m+dd*breite*m)/(m*m-x+HH_GS(m,breite,x)-i*sqrt(x)*g)
      else
         BW_GS=(m*m+dd*breite*m)/(m*m-x+HH_GS(m,breite,x)+i*sqrt(x)*g)
      endif
  
      return
      end
c **********************************************************************
      double precision function HH_GS(m,breite,x)
      include 'phokhara_6.0.inc'       
      double precision breite,x,HH_p,poch,vv_rho,m

      vv_rho = sqrt( 1.d0 - 4.d0*mpi**2/m**2 ) 

      poch = m**2 * breite / pi / (m**2-4.d0*mpi**2)**(1.5d0)
     1     * ( vv_rho**2 + vv_rho/2.d0*(3.d0-vv_rho**2) 
     2       * log( (1.d0+vv_rho)**2/4.d0/mpi**2 * m**2) )
      
      HH_GS = HH_p(m,breite,x) - HH_p(m,breite,m**2) 
     1   - ( x - m**2 ) * poch

      return
      end
c **********************************************************************
      double precision function HH_p(m,breite,par)
      include 'phokhara_6.0.inc'       
      double precision breite,par,vv,m

      vv = sqrt( 1.d0 - 4.d0*mpi**2/par )

      HH_p = m**2 * breite * par / pi / (m**2-4.d0*mpi**2)**(1.5d0)
     1     * vv**3 * log( (1.d0+vv)**2 / 4.d0 / mpi**2 * par )

      return
      end
c **********************************************************************
      complex*16 function HH_3pi(rhomm,rhogm,rhomp,rhogp,rhomz,rhogz)
      include 'phokhara_6.0.inc'       
      real*8 rhomm,rhogm,rhomp,rhogp,rhomz,rhogz,
     1       qq12_3pi,qq13_3pi,qq23_3pi
      complex*16 RRro_3pi
      integer ii
      common/qqij_3pi/qq12_3pi,qq13_3pi,qq23_3pi

      HH_3pi= RRro_3pi(qq12_3pi,rhomz,rhogz)
     1      + RRro_3pi(qq13_3pi,rhomp,rhogp)
     2      + RRro_3pi(qq23_3pi,rhomm,rhogm)

      return
      end
c **********************************************************************
      complex*16 function RRro_3pi(qq,mm,mmg)
      implicit none
      double precision qq,mm,mmg,Gam_3pi
      complex*16 i

      i = dcmplx(0.d0,1.d0)
       RRro_3pi=1.d0/(qq/mm**2-1.d0+i*sqrt(qq)*Gam_3pi(qq,mm,mmg)/mm**2)
      return
      end
c ***********************************************************************
      double precision function Gam_3pi(qq,mm,mmg)
      include 'phokhara_6.0.inc'       
      real*8 qq,mm,mmg,qq12_3pi,qq13_3pi,qq23_3pi

      integer ii

      common/qqij_3pi/qq12_3pi,qq13_3pi,qq23_3pi

      if(qq.eq.qq12_3pi) then

       Gam_3pi = mmg*mm**2 / qq*sqrt( ( ( qq - 4.d0*rmass(1)**2 )/
     1           ( mm**2 - 4.d0*rmass(1)**2 ) ) **3 )

       if(qq.lt.(4.d0*rmass(1)**2))then
         if((abs(qq-4.d0*rmass(1)**2)/qq).lt.1.d-10)then
           Gam_3pi = 0.d0
         else
           write(*,*)'qq = ',qq
           write(*,*)'4*rmass(1)**2 = ',4.d0*rmass(1)**2
         endif
       endif

      else
       Gam_3pi = mmg*mm**2 / qq*sqrt( ( ( qq - (rmass(1)+rmass(3))**2 )/
     1           ( mm**2 - ( rmass(1) + rmass(3) )**2 ) )**3 )

       if(qq.lt.(rmass(1)+rmass(3))**2)then
         if((abs(qq-(rmass(1)+rmass(3))**2)/qq).lt.1.d-10)then
           Gam_3pi = 0.d0
         else
           write(*,'(1x,a,1pd23.16)')'qq = ',qq
           write(*,'(1x,a,1pd23.16)')'(rmass(1)+rmass(3))**2 = ',
     1                                (rmass(1)+rmass(3))**2
         endif
       endif

      endif

      return
      end
c **********************************************************************
      complex*16 function appr_sum(qq)
      include 'phokhara_6.0.inc'       
      real*8 qq,appr_r,appr_i,q_ss
      real*8 aa,bb,cc,tt,dd,ee,ff,gg,hh,jj,kk,ll,mm,nn,oo,pp,rr,ss,uu
     
      q_ss = sqrt(qq)
c ---------------------------------------
c imaginary part
c (imaginary part - to be used for 2*mpi < sqrt(s) < 1.9 GeV
      if(q_ss.lt.1.9d0)then             
       tt = q_ss-2.d0*mpi
       aa = -0.000718099867d0
       bb = 1.49883073d0
       cc = -0.599502161d0
       dd = 3.01291361d0
       ee = 0.000112440192d0
       ff = 16.8164504d0
       gg = -4.81600874d0
       hh = 5.54036557d0
       jj = -3.2948141d0
       kk = 0.916269688d0
c
       appr_i = aa*tt**bb
     1 *(1.d0+cc*tt+dd*tt**2+gg*tt**3+hh*tt**4
     1  +jj*tt**5 +kk*tt**6
     2 +ee*tt**ff)
      elseif(q_ss.lt.2.6d0)then
c (imaginary part - to be used for 1.9 GeV < sqrt(s) < 2.6 GeV
c
       aa = -0.039071345d0
       bb = 0.0129735898d0
       cc = 2.30479409d0
       dd = -0.513327099d0
       ee = -1.45771258d0
       ff = 25.2344274d0
       gg = -0.55843411d0
       hh = -43.3152678d0
       jj = -0.328423868d0
       kk = 113.986304d0
       tt = q_ss-cc
      appr_i = (aa +tt*bb+tt**2*dd+tt**3*gg+tt**4*jj)
     1       /(1.d0+tt*ee+tt**2*ff+tt**3*hh+tt**4*kk)
      elseif(q_ss.lt.11.d0)then
c (imaginary part - to be used for 2.6 GeV < sqrt(s) < 10.6 GeV
c
        aa = -0.433813582d0
        bb = -0.00309846176d0
        cc = 2.42660454d0
        dd = -189.541887d0
        ee = 7.73108923d0
        appr_i = aa*(1.d0/q_ss-bb)**cc*(1.d0 + dd/q_ss**ee)
       else
        write(6,*)' this function is to be used  below sqrt(s) = 11 GeV'
        stop
       endif
c ---------------------------------------
c  real part
c ---------------------------------------
c below a fitted function 
c (real part - to be used for sqrt(s) < 2.35 GeV
c
      if(q_ss.lt.2.35d0)then             
       aa = -0.0235588194d0
       bb = 0.0509353703d0
       cc = -2.53568629d0
       dd =-0.0410886763d0
       ee =2.37249385d0
       ff =0.012325431d0
       gg =-0.800187742d0
       hh =-0.000404693395d0
       jj =-0.05464375d0
       kk =0.000491537627d0
       ll =0.012346788d0
       mm =0.000197618d0
       nn =0.0171119177d0
       oo =2.64910139d-05
       pp =0.0270500914d0
       rr = -0.000478819839d0
c
      appr_r = (aa+ bb*(q_ss-1.2d0)+ dd*(q_ss-1.2d0)**2
     1 + ff*(q_ss-1.2d0)**3+ hh*(q_ss-1.2d0)**4
     1 + kk*(q_ss-1.2d0)**5+ mm*(q_ss-1.2d0)**6
     1 + oo*(q_ss-1.2d0)**7+ rr*(q_ss-1.2d0)**8 )
     1  /(1.d0+ cc*(q_ss-1.2d0)+ ee*(q_ss-1.2d0)**2
     1 + gg*(q_ss-1.2d0)**3+ jj*(q_ss-1.2d0)**4
     1 + ll*(q_ss-1.2d0)**5+ nn*(q_ss-1.2d0)**6 
     1 + pp*(q_ss-1.2d0)**7 )
      elseif(q_ss.lt.3.09d0)then
c
      aa = 0.113336875d0
      bb = -0.24255157d0
      cc = -3.45189001d0
      dd = -24.9323934d0
      ee = -80.9049411d0
      ff = 14.8839941d0
      gg = 111.231181d0
      hh = 402.100665d0
      jj = -95.4007448d0
      kk = 687.517122d0
      ll = 66.258075d0
      mm = 409.908489d0
      nn = 234.397174d0
      oo = -154.63515d0
      pp = 130.735593d0
      rr = -175.517676d0
      ss = -47.3948306d0
      tt = 87.7912501d0
      uu = 0.999466217d0
c
      if ((1.d0/q_ss**2-aa).ge.0.d0)then
      appr_r = (1.d0/q_ss**2-aa)**uu
      else
      appr_r = -(-1.d0/q_ss**2+aa)**uu
      endif
      appr_r = appr_r
     1 *(bb+cc*(q_ss-2.9d0)+dd*(q_ss-2.9d0)**2
     2 +ee*(q_ss-2.9d0)**3+jj*(q_ss-2.9d0)**4+ll*(q_ss-2.9d0)**5
     2 +nn*(q_ss-2.9d0)**6+pp*(q_ss-2.9d0)**7+ss*(q_ss-2.9d0)**8 )
     3 /(1.d0+ff*(q_ss-2.9d0)+gg*(q_ss-2.9d0)**2
     4 +hh*(q_ss-2.9d0)**3+kk*(q_ss-2.9d0)**4+mm*(q_ss-2.9d0)**5
     2 +oo*(q_ss-2.9d0)**6+rr*(q_ss-2.9d0)**7+tt*(q_ss-2.9d0)**8 )
      elseif(q_ss.lt.11d0)then
c
c below a fitted function 
c (real part - to be used for 3.09 GeV < sqrt(s) < 10.6 GeV
      aa = 0.315023275d0
      bb = 49.4458006d0
      cc = 219.202125d0
      dd = 85.4051109d0
      ee = 3254.82596d0
      ff = -4817.48097d0
      gg = -7126.62555d0
c
      appr_r = 1.d0/q_ss**2*
     1 (aa+bb/q_ss**2+dd/q_ss**4+ff/q_ss**6)
     2 /(1.d0+cc/q_ss**2+ee/q_ss**4+gg/q_ss**6)
      else
       continue
      endif     
c ---------------------------------------
      appr_sum = dcmplx(appr_r,appr_i)
c
      return
      end
c **********************************************************************
c this is a code of hadronic current \gamma^* pi+ pi- pi0 
c calculated in e+e- CMS

      subroutine had_3pi(qq,q1,q2,q3,hadr)
      implicit none

      double precision q1,q2,q3,qq
      complex*16 hadr(4),PionFormFactor_3pi,Factor
      dimension q1(4),q2(4),q3(4)

      Factor = PionFormFactor_3pi(qq)

      hadr(1) = (  q1(2)* ( q2(3)*q3(4)-q2(4)*q3(3) )
     1           - q2(2)* ( q1(3)*q3(4)-q1(4)*q3(3) )
     2           + q3(2)* ( q1(3)*q2(4)-q1(4)*q2(3) ) )  * Factor
      hadr(2) = - ( - q1(1)* ( q2(3)*q3(4)-q2(4)*q3(3) ) 
     1            + q2(1)* ( q1(3)*q3(4)-q1(4)*q3(3) )
     2            - q3(1)* ( q1(3)*q2(4)-q1(4)*q2(3) ) )  * Factor
      hadr(3) = - (   q1(1)* ( q2(2)*q3(4)-q2(4)*q3(2) )
     1            - q2(1)* ( q1(2)*q3(4)-q1(4)*q3(2) )
     2            + q3(1)* ( q1(2)*q2(4)-q1(4)*q2(2) ) )  * Factor
      hadr(4) = - ( - q1(1)* ( q2(2)*q3(3)-q2(3)*q3(2) )
     1            + q2(1)* ( q1(2)*q3(3)-q1(3)*q3(2) )
     2            - q3(1)* ( q1(2)*q2(3)-q1(3)*q2(2) ) )  * Factor

      return
      end
c **********************************************************************
c this is a code of hadronic current rho(0) -> 2pi+ 2pi- 
c
      subroutine had2(qq2,q1,q2,q3,q4,hadr)
      implicit none
      real*8 q1,q2,q3,q4,qq2
      integer i
      dimension q1(4),q2(4),q3(4),q4(4)
      complex*16 hadr(4),hadr1(4),hadr2(4),hadr3(4),hadr4(4)
c
      call had3(qq2,q1,q2,q3,q4,hadr1)
      call had3(qq2,q4,q2,q3,q1,hadr2)
      call had3(qq2,q1,q3,q2,q4,hadr3)
      call had3(qq2,q4,q3,q2,q1,hadr4)
      do i=1,4
       hadr(i) = hadr1(i)+hadr2(i)+hadr3(i)+hadr4(i)
      enddo
c       
      return
      end
c*************************************************************************
c this is a code of hadronic current rho(0) -> pi+ pi- 2pi0
c
c the current was obtained in h1_t_f0_cvc.f(log)
c it was called 'had2' in 'test_fp_flat1_cvc.f' program
c
      subroutine had3(qq2,q1,q2,q3,q4,hadr)
      implicit none
      real*8 q1,q2,q3,q4,q2m4,q3m1,q4m1,q3m2,q123,q124,qq,q3m4,q134
     1      ,q234,q2p4,q1p3,q2p3,q1p4,q1p2,q3p4,gam1,gam2,coupl,a1m
     2      ,a1g,rhom,rhog,rho1m,rho1g,rho2m,rho2g,omm,omg,aa
     3      ,bb1,bb2,f0m,f0g,pim,sgo,q_3m2,q_2m4,q_4m1,q_3m1,q1_2m4
     4      ,q1_3m2,q3_2m4,q2_3m1,q2_4m1,q3_4m1,q4_3m1,q4_3m2,qmq3_2 
     5      ,qmq4_2,q_q3,q134_2,q234_2,q34,q24,q23,q14,q13,q12,q4_234
     6      ,q3_234,q2_234,q4_134,q3_134,q1_134,fac3,q2p3_4m1
     7      ,q2p4_3m1,q1p4_3m2,q1p3_2m4,q1p2_3m4,q1p4_2,q2p3_2,q1p2_2
     8      ,q1p3_2,q3p4_2,q2p4_2,q_q4,qq2
      integer i
      complex*16 hadr(4),cfac(4),tt(4,4,4),ss(4,4,4,4)
      complex*16 bwga1,bwgrho,bwgrho_t,bwgf0,c0,c1,c2,c3,c4,c5,c6
      complex*16 c1_t,c2_t,c3_t,c4_t,anom_bwg
      dimension q1(4),q2(4),q3(4),q4(4),q2m4(4),q3m1(4),q4m1(4),q3m2(4)
      dimension q123(4),q124(4),qq(4),q3m4(4),q134(4),q234(4)
      dimension q2p4(4),q1p3(4),q2p3(4),q1p4(4),q1p2(4),q3p4(4)
c
      common /had_par/ gam1,gam2,coupl,a1m,a1g,rhom,rhog,rho1m,rho1g
     1                ,rho2m,rho2g,omm,omg,aa,bb1,bb2,f0m,f0g,pim,sgo
c
c     the dot products:
c
      do i=1,4
        q2m4(i) = q2(i)-q4(i)
        q3m1(i) = q3(i)-q1(i)
        q3m4(i) = q3(i)-q4(i)
        q4m1(i) = q4(i)-q1(i)
        q3m2(i) = q3(i)-q2(i)
        q2p4(i) = q2(i)+q4(i)
        q1p3(i) = q1(i)+q3(i)
        q1p2(i) = q1(i)+q2(i)
        q2p3(i) = q2(i)+q3(i)
        q1p4(i) = q1(i)+q4(i)
        q3p4(i) = q3(i)+q4(i)
        q123(i) = q2p3(i)+q1(i)
        q124(i) = q2p4(i)+q1(i)
        qq(i)   = q123(i) + q4(i)
      enddo
      q_3m2  = qq(1)*q3m2(1)-qq(2)*q3m2(2)-qq(3)*q3m2(3)-qq(4)*q3m2(4)
      q_2m4  = qq(1)*q2m4(1)-qq(2)*q2m4(2)-qq(3)*q2m4(3)-qq(4)*q2m4(4)
      q_4m1  = qq(1)*q4m1(1)-qq(2)*q4m1(2)-qq(3)*q4m1(3)-qq(4)*q4m1(4)
      q_3m1  = qq(1)*q3m1(1)-qq(2)*q3m1(2)-qq(3)*q3m1(3)-qq(4)*q3m1(4)
      q1_2m4 = q1(1)*q2m4(1)-q1(2)*q2m4(2)-q1(3)*q2m4(3)-q1(4)*q2m4(4)      
      q1_3m2 = q1(1)*q3m2(1)-q1(2)*q3m2(2)-q1(3)*q3m2(3)-q1(4)*q3m2(4)      
      q3_2m4 = q3(1)*q2m4(1)-q3(2)*q2m4(2)-q3(3)*q2m4(3)-q3(4)*q2m4(4)      
      q2_3m1 = q2(1)*q3m1(1)-q2(2)*q3m1(2)-q2(3)*q3m1(3)-q2(4)*q3m1(4)      
      q2_4m1 = q2(1)*q4m1(1)-q2(2)*q4m1(2)-q2(3)*q4m1(3)-q2(4)*q4m1(4)      
      q3_4m1 = q3(1)*q4m1(1)-q3(2)*q4m1(2)-q3(3)*q4m1(3)-q3(4)*q4m1(4)      
      q4_3m1 = q4(1)*q3m1(1)-q4(2)*q3m1(2)-q4(3)*q3m1(3)-q4(4)*q3m1(4)      
      q4_3m2 = q4(1)*q3m2(1)-q4(2)*q3m2(2)-q4(3)*q3m2(3)-q4(4)*q3m2(4)      
      qmq3_2 = q124(1)**2 -q124(2)**2 -q124(3)**2 -q124(4)**2
      qmq4_2 = q123(1)**2 -q123(2)**2 -q123(3)**2 -q123(4)**2
      q_q3   = qq(1)*q3(1)-qq(2)*q3(2)-qq(3)*q3(3)-qq(4)*q3(4)
      q_q4   = qq(1)*q4(1)-qq(2)*q4(2)-qq(3)*q4(3)-qq(4)*q4(4)
      q2p4_2 = q2p4(1)**2 - q2p4(2)**2 - q2p4(3)**2 - q2p4(4)**2
      q3p4_2 = q3p4(1)**2 - q3p4(2)**2 - q3p4(3)**2 - q3p4(4)**2
      q1p3_2 = q1p3(1)**2 - q1p3(2)**2 - q1p3(3)**2 - q1p3(4)**2
      q1p2_2 = q1p2(1)**2 - q1p2(2)**2 - q1p2(3)**2 - q1p2(4)**2
      q2p3_2 = q2p3(1)**2 - q2p3(2)**2 - q2p3(3)**2 - q2p3(4)**2
      q1p4_2 = q1p4(1)**2 - q1p4(2)**2 - q1p4(3)**2 - q1p4(4)**2
      q1p2_3m4 = q1p2(1)*q3m4(1)
     1          -q1p2(2)*q3m4(2)-q1p2(3)*q3m4(3)-q1p2(4)*q3m4(4)
      q1p3_2m4 = q1_2m4 + q3_2m4
      q1p4_3m2 = q1_3m2 + q4_3m2 
      q2p4_3m1 = q2_3m1 + q4_3m1
      q2p3_4m1 = q2_4m1 + q3_4m1 
c
      c0 = bwgrho(qq2)*coupl
c
      c1_t = bwgrho_t(q2p4_2)
      c2_t = bwgrho_t(q1p3_2)
      c3_t = bwgrho_t(q2p3_2)
      c4_t = bwgrho_t(q1p4_2)
c
      c5 = bwga1(qmq3_2)
      c6 = bwga1(qmq4_2)
c
      tt(1,2,4) = c5*c1_t*gam1
      tt(2,1,4) = c5*c4_t*gam1
      tt(2,3,1) = c6*c2_t*gam1
      tt(1,2,3) = c6*c3_t*gam1
      ss(3,4,1,2) = bwgrho(q3p4_2)*bwgf0(q1p2_2)*gam2
c
      cfac(1) =  tt(1,2,3) * (-1.d0 - q1_3m2/qmq4_2 )
     1         + tt(1,2,4) * ( 1.d0 - q1_2m4/qmq3_2 )
     2         + tt(2,1,4) * ( 3.d0 + q2_4m1/qmq3_2 )
     3         + tt(2,3,1) * (-3.d0 - q2_3m1/qmq4_2 )
c
      cfac(2) =  tt(1,2,3) * (-3.d0 - q1_3m2/qmq4_2 )
     1         + tt(1,2,4) * ( 3.d0 - q1_2m4/qmq3_2 )
     2         + tt(2,1,4) * ( 1.d0 + q2_4m1/qmq3_2 )
     3         + tt(2,3,1) * (-1.d0 - q2_3m1/qmq4_2 )
c
      cfac(3) =  tt(1,2,3) * ( 1.d0 - q1_3m2/qmq4_2 )
     1         + tt(1,2,4) * ( 1.d0 + q1_2m4/qmq3_2 )
     2         + tt(2,1,4) * ( 1.d0 - q2_4m1/qmq3_2 )
     3         + tt(2,3,1) * ( 1.d0 - q2_3m1/qmq4_2 )
     4      -3.d0*ss(3,4,1,2)
c
      cfac(4) =  tt(1,2,3) 
     1 *(1.d0 -2.d0/qq2*(q_q4*q1_3m2/qmq4_2 +q_3m2) +q1_3m2/qmq4_2 )
     2         + tt(1,2,4) 
     3 *(-1.d0-2.d0/qq2*(q1_2m4/qmq3_2*q_q3 +q_2m4) +q1_2m4/qmq3_2 )
     4         + tt(2,1,4) 
     5 *(-1.d0+2.d0/qq2*(q_q3*q2_4m1/qmq3_2 +q_4m1) -q2_4m1/qmq3_2 )
     6         + tt(2,3,1)
     7 *(1.d0 -2.d0/qq2*(q2_3m1/qmq4_2*q_q4 +q_3m1) +q2_3m1/qmq4_2 )
     8   +3.d0*ss(3,4,1,2)/qq2*q1p2_3m4
c
      do i=1,4
        cfac(i) = cfac(i)*c0
      enddo
c
      do i=1,4
        hadr(i) =  q1(i)  *cfac(1) + q2(i)*cfac(2) 
     1           + q3m4(i)*cfac(3) + qq(i)*cfac(4)
      enddo
c
c  from here Omega current
c
      fac3 = sgo * 1475.98d0*12.924d0 * 0.266d0 *rhom**2
c
c     the dot products:
      do i=1,4
        q134(i) = q1p3(i)+q4(i)
        q234(i) = q2p4(i)+q3(i)
      enddo
c
      q1_134 = q1(1)*q134(1)-q1(2)*q134(2)-q1(3)*q134(3)-q1(4)*q134(4)      
      q3_134 = q3(1)*q134(1)-q3(2)*q134(2)-q3(3)*q134(3)-q3(4)*q134(4)      
      q4_134 = q4(1)*q134(1)-q4(2)*q134(2)-q4(3)*q134(3)-q4(4)*q134(4)      
      q2_234 = q2(1)*q234(1)-q2(2)*q234(2)-q2(3)*q234(3)-q2(4)*q234(4)      
      q3_234 = q3(1)*q234(1)-q3(2)*q234(2)-q3(3)*q234(3)-q3(4)*q234(4)      
      q4_234 = q4(1)*q234(1)-q4(2)*q234(2)-q4(3)*q234(3)-q4(4)*q234(4)      
      q12    = q1(1)*q2(1)  - q1(2)*q2(2) - q1(3)*q2(3) - q1(4)*q2(4)
      q13    = q1(1)*q3(1)  - q1(2)*q3(2) - q1(3)*q3(3) - q1(4)*q3(4)
      q14    = q1(1)*q4(1)  - q1(2)*q4(2) - q1(3)*q4(3) - q1(4)*q4(4)
      q23    = q2(1)*q3(1)  - q2(2)*q3(2) - q2(3)*q3(3) - q2(4)*q3(4)
      q24    = q2(1)*q4(1)  - q2(2)*q4(2) - q2(3)*q4(3) - q2(4)*q4(4)
      q34    = q3(1)*q4(1)  - q3(2)*q4(2) - q3(3)*q4(3) - q3(4)*q4(4)
      q234_2 = q234(1)**2-q234(2)**2-q234(3)**2-q234(4)**2      
      q134_2 = q134(1)**2-q134(2)**2-q134(3)**2-q134(4)**2      
c 
      cfac(1) = anom_bwg(qq2,q134_2) *(q3_134*q24 -q4_134*q23)
      cfac(2) = anom_bwg(qq2,q234_2) *(q3_234*q14 -q4_234*q13)
      cfac(3) = anom_bwg(qq2,q134_2) *(q4_134*q12 -q1_134*q24)
     1        + anom_bwg(qq2,q234_2) *(q4_234*q12 -q2_234*q14)
      cfac(4) = anom_bwg(qq2,q134_2) *(q1_134*q23 -q3_134*q12)
     1        + anom_bwg(qq2,q234_2) *(q2_234*q13 -q3_234*q12)
c
      do i =1,4
        hadr(i) = hadr(i) + fac3* (q1(i)*cfac(1) + q2(i)*cfac(2)
     1                            + q3(i)*cfac(3) + q4(i)*cfac(4) )
      enddo
c
      return
      end
c*************************************************************************
      real*8 function gfun(q1_2)
      implicit none
      real*8 gam1,gam2,coupl,a1m,a1g,rhom_4,rhog_4,rho1m,rho1g,rho2m
     1      ,rho2g,omm_4,omg_4,aa,bb1,bb2,f0m,f0g,pim_4,sgo,q1_2,c1
c
      common /had_par/ gam1,gam2,coupl,a1m,a1g,rhom_4,rhog_4
     1                ,rho1m,rho1g,rho2m,rho2g,omm_4,omg_4
     2                ,aa,bb1,bb2,f0m,f0g,pim_4,sgo
c
      if(q1_2.gt.((rhom_4+pim_4)**2))then
        gfun = q1_2*1.623d0 + 10.38d0 - 9.32d0/q1_2 + 0.65d0/q1_2**2
      else
        c1   = q1_2 - 9.d0*pim_4**2
        gfun = 4.1d0 *c1**3 *(1.d0 - 3.3d0*c1 + 5.8d0*c1**2)
      endif
c
      return
      end
c*************************************************************************
      complex*16 function bwgrho(q1_2)
      implicit none
      real*8 gam1,gam2,coupl,a1m,a1g,rhom,rhog,rho1m,rho1g,rho2m,rho2g
     1      ,omm,omg,aa,bb1,bb2,f0m,f0g,pim,sgo,rhom2,rho1m2,rho2m2
     2      ,omm2,rhomg,rho1mg,rho2mg,ommg,c1,c2,q1_2
     3      ,gamrho,gamrho1,gamrho2,gamom     
      complex*16 cbw,cbw1,cbw2,cbwo
c
      common /had_par/ gam1,gam2,coupl,a1m,a1g,rhom,rhog,rho1m,rho1g
     1                ,rho2m,rho2g,omm,omg,aa,bb1,bb2,f0m,f0g,pim,sgo
      common /cbwgrho/rhom2,rho1m2,rho2m2,omm2,rhomg,rho1mg,rho2mg,ommg
c
      c2     = 4.d0*pim**2/q1_2
c       
      c1     = rhom2/q1_2
      gamrho  = rhomg*sqrt(abs(c1*((1.d0-c2)/(c1-c2))**3))
      c1      = rho1m2/q1_2
      gamrho1 = rho1mg*sqrt(abs(c1*((1.d0-c2)/(c1-c2))**3))
      c1      = rho2m2/q1_2
      gamrho2 = rho2mg*sqrt(abs(c1*((1.d0-c2)/(c1-c2))**3))
      c1      = omm2/q1_2
      gamom   = ommg*sqrt(abs(c1*((1.d0-c2)/(c1-c2))**3))
c      
      cbw   = dcmplx(rhom2,0.d0)/dcmplx(rhom2-q1_2,-gamrho)
      cbw1  = dcmplx(rho1m2,0.d0)/dcmplx(rho1m2-q1_2,-gamrho1)
      cbw2  = dcmplx(rho2m2,0.d0)/dcmplx(rho2m2-q1_2,-gamrho2)
      cbwo  = dcmplx(omm2,0.d0)/dcmplx(omm2-q1_2,-gamom)
      bwgrho = ( cbw *(1.d0+aa*cbwo)/(1.d0+aa)
     1          + bb1*cbw1+bb2*cbw2)/(1.d0+bb1+bb2)
c
      return
      end
c*************************************************************************
      complex*16 function bwgrho_t(q1_2)
      implicit none
      real*8 pim,rhom,rhog,beta,rho1m,rho1g,rhom2,rhomg,rho1m2,rho1mg
     1      ,c1,c2,q1_2,gamrho,gamrho1
c
      complex*16 cbw,cbw1,cbw2,cbwo
c
      pim   = 0.13956995d0
      rhom  = 0.773d0
      rhog  = 0.145d0
      beta  = -0.145d0
      rho1m = 1.37d0
      rho1g = 0.51d0 
c
       rhom2  = rhom**2
       rhomg  = rhom*rhog
       rho1m2 = rho1m**2
       rho1mg = rho1m*rho1g
c
      c2     = 4.d0*pim**2/q1_2
c       
      c1     = rhom2/q1_2
      gamrho  = rhomg*sqrt(abs(c1*((1.d0-c2)/(c1-c2))**3))
      c1     = rho1m2/q1_2
      gamrho1  = rho1mg*sqrt(abs(c1*((1.d0-c2)/(c1-c2))**3))
c      
      cbw    = dcmplx(rhom2,0.d0)/dcmplx(rhom2-q1_2,-gamrho)
      cbw1   = dcmplx(rho1m2,0.d0)/dcmplx(rho1m2-q1_2,-gamrho1)

      bwgrho_t = (cbw+beta*cbw1)/(1.d0+beta) 
c
      return
      end
c*************************************************************************
      complex*16 function bwga1(q1_2)
      implicit none
      real*8 a1m2,con,q1_2,ggm,gfun
c
      common /cbwga1/ a1m2,con 
c
      ggm = gfun(q1_2)*con 
      bwga1 = dcmplx(a1m2,0.d0)/dcmplx(a1m2-q1_2,-ggm)     
c
      return
      end
c ************************************************************************
      complex*16 function bwgf0(q1_2)
      implicit none
      real*8 gam1,gam2,coupl,a1m,a1g,rhom,rhog,rho1m,rho1g,rho2m,rho2g
     1      ,omm,omg,aa,bb1,bb2,f0m,f0g,pim,sgo,f0m2,q1_2,f0mg
c
      common /had_par/ gam1,gam2,coupl,a1m,a1g,rhom,rhog,rho1m,rho1g
     1                ,rho2m,rho2g,omm,omg,aa,bb1,bb2,f0m,f0g,pim,sgo
c
      f0m2  = f0m**2
      f0mg  = f0m*f0g
      bwgf0 = dcmplx(f0m2,-f0mg)/dcmplx(f0m2-q1_2,-f0mg)     
c
      return
      end
c*************************************************************************
      complex*16 function anom_bwg(q1_2,q2_2)
      implicit none
      real*8 gam1,gam2,coupl,a1m,a1g,rhom,rhog,rho1m,rho1g,rho2m,rho2g
     1     ,omm,omg,aa,bb1,bb2,f0m,f0g,pim,sgo,rhom2,rho1m2,rho2m2
     2     ,omm2,rhomg,rho1mg,rho2mg,ommg,amrop,gamrop,sig,amrop_2
     3     ,amropg,q1_2,q2_2
c
      common /had_par/ gam1,gam2,coupl,a1m,a1g,rhom,rhog,rho1m,rho1g
     1                ,rho2m,rho2g,omm,omg,aa,bb1,bb2,f0m,f0g,pim,sgo
      common /cbwgrho/ rhom2,rho1m2,rho2m2,omm2,rhomg,rho1mg,rho2mg
     1                ,ommg
      common /anom/amrop,gamrop,sig,amrop_2,amropg
c
      anom_bwg = (dcmplx(1.d0,0.d0)/dcmplx(rhom2-q1_2,-rhomg)
     1         + dcmplx(sig,0.d0)/dcmplx(amrop_2-q1_2,-amropg) )
     2     * dcmplx(1.d0,0.d0)/dcmplx(omm2-q2_2,-ommg)
c
c dumping factor added in omega part: to be substituted with a formfactor
c
      if(q1_2.gt.(2.2d0)**2)anom_bwg = anom_bwg * (2.2d0**2/q1_2)**2
      return
      end
c*************************************************************************
c ---- complex dilogarithm -----------------------------------------------
c ------------------------------------------------------------------------
       complex function cdilog*16(z)                                    
       implicit none                                   
       complex*16 z,zl,coef,dilog1,u,caux                               
       real*8 pi,sign                                                   
       integer n,i 
       pi=3.141592653589793238462643d0                                  
       zl=z                                                             
       dilog1=dcmplx(pi**2/6.d0)                                        
       if(dreal(zl).eq.1.and.dimag(zl).eq.0.) then                      
          cdilog=dilog1                                                    
          return                                                           
       else if (cdabs(zl).lt.1.d-2) then   
          n=-40./dlog(cdabs(zl))                                           
          caux=(0.d0,0.d0)                                                 
          do i=1,n                                                         
             caux=caux+zl**i/dble(i**2)                                       
          enddo                                                           
          cdilog=caux                                                      
          return                                                           
       else if(cdabs(zl).lt.1.) then                                    
          sign=1.d0                                                       
          coef=dcmplx(dble(0.))                                           
       else                                                            
          coef=-cdlog(-zl)**2/2.d0-dilog1                                 
          sign=-1.d0                                                      
          zl=1.d0/zl                                                      
       endif                                                          
       if(dreal(zl).gt.0.5) then                   
          coef=coef+sign*(dilog1-cdlog(zl)*cdlog(1.d0-zl))                
          sign=-sign                                                      
          zl=1.d0-zl                                                      
       else   
       endif  
       u=-cdlog(1.d0-zl)                                               
       cdilog=u-u**2/4.d0+u**3/36.d0-u**5/3600.d0+u**7/211680.d0       
     &  -u**9/10886400.d0+u**11*5.d0/2634508800.d0                     
       cdilog=cdilog-u**13*691.d0/2730.d0/6227020800.d0                
       cdilog=cdilog+u**15*7.d0/6.d0/1.307674368d12                    
       cdilog=cdilog-u**17*3617.d0/510.d0/3.5568742810d14              
       cdilog=cdilog+u**19*43867.d0/798.d0/1.2164510041d17              
       cdilog=cdilog-u**21*174611.d0/330.d0/5.1090942172d19            
       cdilog=sign*cdilog+coef                                         
       return                                                          
       end                                                             
c ========================================================================
c --- all about the histogrammes -----------------------------------------

      subroutine addiere(wgt,qq,i)
      include 'phokhara_6.0.inc'
      double precision wgt,qq,qq_inv,q_sum(0:3)
      integer i,j
c
      if (i.eq.1) call addhisto(1,qq,wgt)      ! one photon events
      if (i.eq.2) call addhisto(2,qq,wgt)      ! two photon events
c
      return
      end
c ------------------------------------------------------
c     create histograms                                 
c ------------------------------------------------------
      subroutine inithisto
      include 'phokhara_6.0.inc'
      integer i,j
      double precision histo(20,200),error(20,200)
      common/histograms/histo,error
c --- book the histograms ----
      do i=1,20
        do j=1,200
         histo(i,j)= 0.d0
         error(i,j)= 0.d0
        enddo
      enddo
      return 
      end
c ------------------------------------------------------
c     add value to histo i at x                         
c ------------------------------------------------------
      subroutine addhisto(i,x,value)   
      include 'phokhara_6.0.inc'
      double precision x,value,histo(20,200),error(20,200)
      integer i,j
      common/histograms/histo,error
c --- add --------------------
      j = 1+(x-xlow(i))/(xup(i)-xlow(i))*bins(i)
      if (j.ge.1.and.j.le.bins(i)) then 
         histo(i,j)=histo(i,j)+value
      endif
      end
c ------------------------------------------------------
c     save histograms                      
c ------------------------------------------------------
      subroutine endhisto()
      include 'phokhara_6.0.inc'
      double precision h,histo(20,200),error(20,200),x
      integer i,j
      common/histograms/histo,error    
c --- fill histograms --------

c      open(21,file='1ph_data.dat',type='new')
c      open(22,file='2ph_data.dat',type='new')

      do i=1,2
c        write(*,*)i
        do j=1,bins(i)
           x = xlow(i)+(j-.5d0)*(xup(i)-xlow(i))/dble(bins(i))
           if (count(i).ne.0.d0) then 
              error(i,j) = Mmax(i)*dSqrt((histo(i,j)/count(i)-
     &	                   (histo(i,j)/count(i))**2)/count(i))
              histo(i,j) = Mmax(i)/count(i)*histo(i,j)
              histo(i,j)=histo(i,j)*dble(bins(i))/(xup(i)-xlow(i))
              error(i,j)=error(i,j)*dble(bins(i))/(xup(i)-xlow(i))
           endif
c        write (*,*) x,histo(i,j),error(i,j)
c        if(i.eq.1) write (21,*) x,histo(i,j),error(i,j)
c        if(i.eq.2) write (22,*) x,histo(i,j),error(i,j)
        enddo
      enddo
c
      return
      end
c ************************************************************************
c from here helicity amplitudes: H.C. 04.07.2001
c muons added : H.C. 04.10.2001
c 
c p1 - positron four momenta, p2 electron four momenta
c ************************************************************************
c one photon
c ************************************************************************
      double precision function helicityampLO(qq)
      include 'phokhara_6.0.inc'     
      double precision qq,rk1(4),q(4),dps,amp_h,ampLO,ampLOm
      complex*16 gam(4),gammu(4,2,2),v1(2,2),v2(2,2),up1(2,2),up2(2,2)
     1          ,gammu_ma(4,2,2)
      integer i1,ic1,ic2
c
      call gam1(gam,gammu,gammu_ma,v1,v2,up1,up2,qq)
c
      do i1=1,4
         rk1(i1) = momenta(3,i1-1)
         q(i1)   = momenta(5,i1-1)
      enddo
c --- muons ---
      if(pion.eq.0)then
       dps = (1.d0-qq/Sp)/(32.d0*pi*pi)        ! Phase space factors
       dps = dps*dSqrt(1.d0-4.d0*mmu*mmu/qq)/(32.d0*pi*pi) 
c      
       amp_h = ((4.d0*pi*alpha)**3)
     1 *ampLOm(qq,rk1,gam,gammu,gammu_ma,v1,v2,up1,up2,q)/4.d0 
c --- kaons K+K-
      elseif(pion.eq.6)then
       dps = (1.d0-qq/Sp)/(32.d0*pi*pi)        ! Phase space factors
       dps = dps*dSqrt(1.d0-4.d0*mKp*mKp/qq)/(32.d0*pi*pi) 
       amp_h = 
     1 ((4.d0*pi*alpha)**3)*ampLO(qq,rk1,gam,q)/4.d0
      else 
c --- two pions ---
       dps = (1.d0-qq/Sp)/(32.d0*pi*pi)        ! Phase space factors
       dps = dps*dSqrt(1.d0-4.d0*mpi*mpi/qq)/(32.d0*pi*pi) 
       amp_h = 
     1 ((4.d0*pi*alpha)**3)*ampLO(qq,rk1,gam,q)/4.d0
c 
      endif
       helicityampLO = amp_h*dps
      return
      end
c---------------------------------------------------------------------
c-----------------FSR virtual+soft correction -pions and kaons K^+K^-
c---------------------------------------------------------------------
      real*8 function vertLO(qq)
      include 'phokhara_6.0.inc'     
      complex*16 cdilog,pod1,pod2,wsp1,wsp2
      real*8 betapi,mpi2,qq,vert,pod3

      if(pion.eq.1)then
        mpi2 = mpi**2
      elseif(pion.eq.6)then
        mpi2 = mKp**2
      endif

      betapi = Sqrt(1.d0 - 4.d0*mpi2/qq)
      pod1 = dcmplx(2.d0*betapi/(1.d0+betapi),0.d0)
      pod3 = qq*(1.d0+betapi)**2/4.d0/mpi2

      vertLO = alpha/pi*( (3.d0*qq-4.d0*mpi2)/qq/betapi
     $       * Log(pod3) - 2.d0 
     $       - Log(qq/mpi2)
     $       - (1.d0+betapi**2)/betapi
     $       * ( Log(pod3)* Log( (1.d0+betapi)/2.d0)
     $        + 2.d0*cdilog(pod1)
     $        - pi**2/2.d0 ) ) 
     $       + 2.d0*alpha/pi*( (1.d0+betapi**2)/2.d0/betapi*Log(pod3)
     $       - 1.d0 )*( Log(2.d0*w) + 1.d0 
     $                  + 1.d0/(1.d0-Sp/qq)*Log(Sp/qq) )
      return
      end
c----------------------------------------------------------
c-----------------FSR virtual+soft correction -muons ------
c----------------------------------------------------------
      real*8 function vertLO_mu(qq)
      include 'phokhara_6.0.inc'     
      complex*16 cdilog,pod1,pod2,wsp1,wsp2
      real*8 betamu,mmu2,qq,vert,pod3

      mmu2 = mmu**2
      betamu = Sqrt(1.d0 - 4.d0*mmu2/qq)
      pod1 = dcmplx(2.d0*betamu/(1.d0+betamu),0.d0)
      pod3 = qq*(1.d0+betamu)**2/4.d0/mmu2

      vertLO_mu = alpha/pi*( (2.5d0*qq-6.d0*mmu2)/qq/betamu
     $       * Log(pod3) - 2.d0 
     $       - Log(qq/mmu2)
     $       - (1.d0+betamu**2)/betamu
     $       * ( Log(pod3)* Log( (1.d0+betamu)/2.d0)
     $        + 2.d0*cdilog(pod1)
     $        - pi**2/2.d0 ) ) 
     $       + 2.d0*alpha/pi*( (1.d0+betamu**2)/2.d0/betamu*Log(pod3)
     $       - 1.d0 )*( Log(2.d0*w) + 1.d0 
     $                  + 1.d0/(1.d0-Sp/qq)*Log(Sp/qq) )
      return
      end
c----------------------------------------------------------
c-----------------FSR virtual correction F2 part -muons ---
c----------------------------------------------------------
      complex*16 function vert_ma(qq)
      include 'phokhara_6.0.inc'     
      real*8 betamu,mmu2,qq,pod3

      mmu2 = mmu**2
      betamu = Sqrt(1.d0 - 4.d0*mmu2/qq)
      pod3 = qq*(1.d0+betamu)**2/4.d0/mmu2
c
      vert_ma = alpha/pi*mmu/2.d0/qq/betamu*dcmplx(-Log(pod3),pi)
c
      return
      end
c*****************************************************************************
c
      real*8 function ampLO(qq,rk1,gam,q)
      include 'phokhara_6.0.inc'     
      complex*16 p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam,cvac_qq,dggvap
      complex*16 epsk1(2,4),epsk2(2,4),BW_om
      complex*16 gam(4),gam_ma(4),eck1(4),eck2(4)
      complex*16 ma(2,2),mb(2,2),ddpl(2,2),ddmi(2,2)
     1          ,ma_ma(2,2),mb_ma(2,2)
      complex*16 uupp1(1,2),uupp2(1,2),vv1(2,1),vv2(2,1)
      integer i
      real*8 qq,dme,el_m2,ebppb,vacuumpolarization,vertLO,ver_f
      real*8 rk1(4),rk2(4),p1(4),p2(4),q(4),aa_phi,mm_ph,gg_ph
c
      common/iloczs1/p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam
      common/matri1/ma,mb,ma_ma,mb_ma
      common /cp1p2/p1,p2,dme,el_m2
      common/param_PFF/aa_phi,mm_ph,gg_ph
c     
      ampLO = 0.d0
      call pol_vec(rk1,epsk1)
      call skalar1LO(rk1)
      call skalar1aLO(gam,gam_ma)
      ebppb = p1(1)+p1(4)

      if(fsrnlo.eq.1)then
       ver_f = vertLO(qq)
      endif
c
c vacuum polarization
c
      if(ivac.eq.0)then
       cvac_qq = dcmplx(1.d0,0.d0)
      else
c ************ c only pi+pi-    
        if(pion.eq.1)then
          cvac_qq = 1.d0/(1.d0-dggvap(qq,0.d0))
     1            - aa_phi * BW_om(mm_ph,gg_ph,qq,1)
        else
          cvac_qq = 1.d0/(1.d0-dggvap(qq,0.d0))
        endif
      endif
c
c sum over photon polarizations
c
      do i=1,2
                  eck1(1)=epsk1(i,1)
                  eck1(2)=epsk1(i,2)
                  eck1(3)=epsk1(i,3)
                  eck1(4)=epsk1(i,4)
c
           call skalar2LO(rk1,eck1)
           call blocksLO(qq)
           call ddvec(rk1,eck1,uupp1,uupp2,vv1,vv2,ddpl,ddmi,qq)
c
c ddmi is an A type matrix; ddpl is a B type matrix 
c
c the FSR - corrected if fsrnlo=1 (ver_s calculated in subroutine input)
c           for fsrnlo = 0 ver_s =0
c
      ampLO = ampLO
     1         +((dme*cdabs(ddpl(1,1)-ddmi(1,1)))**2
     1         +(dme*cdabs(ddpl(2,2)-ddmi(2,2)))**2
     2         +(cdabs(-ebppb*ddmi(2,1)+el_m2/ebppb*ddpl(2,1)))**2
     3         +(cdabs(ebppb*ddpl(1,2)-el_m2/ebppb*ddmi(1,2)))**2)
     4         *(1.d0 + ver_s)*cdabs(cvac_s)**2
c ISR+correction FSR 
        if(fsrnlo.eq.1)then
        ampLO = ampLO + ( (dme*cdabs(mb(1,1)-ma(1,1)))**2
     1          +(dme*cdabs(mb(2,2)-ma(2,2)))**2
     2          +(cdabs(-ebppb*ma(2,1)+el_m2/ebppb*mb(2,1)))**2
     3          +(cdabs(ebppb*mb(1,2)-el_m2/ebppb*ma(1,2)))**2 )
     4          * ver_f* cdabs(cvac_qq)**2
        endif
c
c the FSR x ISR 
      if(fsr.eq.2)then
      ampLO = ampLO
     4         +2.d0*dreal(
     5    dconjg(dme*(mb(1,1)-ma(1,1))*cvac_qq)
     5              *dme*(ddpl(1,1)-ddmi(1,1))*cvac_s
     6   +dconjg(dme*(mb(2,2)-ma(2,2))*cvac_qq)
     6              *dme*(ddpl(2,2)-ddmi(2,2))*cvac_s
     7   +dconjg((-ebppb*ma(2,1)+el_m2/ebppb*mb(2,1))*cvac_qq)*
     8    (-ebppb*ddmi(2,1)+el_m2/ebppb*ddpl(2,1))*cvac_s
     9   +dconjg((ebppb*mb(1,2)-el_m2/ebppb*ma(1,2))*cvac_qq)*
     1    (ebppb*ddpl(1,2)-el_m2/ebppb*ddmi(1,2))*cvac_s )
c
      endif
c
      enddo
c
      return
      end
c********************************************************************
c used for muonic mode
c
      real*8 function ampLOm(qq,rk1,gam,gammu,gammu_ma,v1,v2,up1,up2,q)
c
      include 'phokhara_6.0.inc'     
      complex*16 p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam,ver_ma,vert_ma
      complex*16 epsk1(2,4),epsk2(2,4),cvac_qq,dggvap
      complex*16 gam(4),eck1(4),eck2(4),gammu(4,2,2),gammu_ma(4,2,2)
     1          ,v1(2,2),v2(2,2),up1(2,2),up2(2,2),gam_ma(4)
      complex*16 ma(2,2),mb(2,2),ddpl(2,2),ddmi(2,2)
     1          ,ma_ma(2,2),mb_ma(2,2)
      complex*16 uupp1(1,2),uupp2(1,2),vv1(2,1),vv2(2,1)
      complex*16 BW_om
      integer i,ic1,ic2,imu
      real*8 qq,dme,el_m2,ebppb,vacuumpolarization,ver_f
      real*8 rk1(4),rk2(4),p1(4),p2(4),q(4)
      real*8 vertLO_mu,aa_phi,mm_ph,gg_ph
c
      common/iloczs1/p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam
      common/matri1/ma,mb,ma_ma,mb_ma
      common /cp1p2/p1,p2,dme,el_m2
      common/param_PFF/aa_phi,mm_ph,gg_ph
c     
      ampLOm = 0.d0
      call pol_vec(rk1,epsk1)
      ebppb = p1(1)+p1(4)
      call skalar1LO(rk1)

      if(fsrnlo.eq.1)then
       ver_f  = vertLO_mu(qq)
       ver_ma = vert_ma(qq)
      endif
c
c vacuum polarization
c
      if(ivac.eq.0)then
          cvac_qq = dcmplx(1.d0,0.d0)
      else
          cvac_qq = 1.d0/(1.d0-dggvap(qq,0.d0))
     1            - aa_phi * BW_om(mm_ph,gg_ph,qq,1)
      endif
c
c sum over mu+,mu- polarizations
c
      do ic1=1,2
      do ic2=1,2
c
c the spinors
c
         uupp2(1,1) = up2(1,ic1)
         uupp2(1,2) = up2(2,ic1)
         uupp1(1,1) = up1(1,ic1)
         uupp1(1,2) = up1(2,ic1)
    
         vv1(1,1) = v1(1,ic2)                 
         vv1(2,1) = v1(2,ic2)                 
         vv2(1,1) = v2(1,ic2)                 
         vv2(2,1) = v2(2,ic2)                 
c
c now gam is the muon current (no emission)
c
       do imu=1,4
        gam(imu) = gammu(imu,ic1,ic2)
        gam_ma(imu) = gammu_ma(imu,ic1,ic2)
       enddo
      call skalar1aLO(gam,gam_ma)
c
c sum over photon polarizations
c
      do i=1,2
c                  eck1(1)=rk1(1)
c                  eck1(2)=rk1(2)
c                  eck1(3)=rk1(3)
c                  eck1(4)=rk1(4)
                  eck1(1)=epsk1(i,1)
                  eck1(2)=epsk1(i,2)
                  eck1(3)=epsk1(i,3)
                  eck1(4)=epsk1(i,4)
c
           call skalar2LO(rk1,eck1)
           call blocksLO(qq)
           call ddvec(rk1,eck1,uupp1,uupp2,vv1,vv2,ddpl,ddmi,qq)
c
c ddmi is an A type matrix; ddpl is a B type matrix 
c
c the FSR - corrected if fsrnlo=1 (ver_s calculated in subroutine input)
c           for fsrnlo = 0 ver_s =0
c
      ampLOm = ampLOm
     1         +( (dme*cdabs(ddpl(1,1)-ddmi(1,1)))**2
     1         +(dme*cdabs(ddpl(2,2)-ddmi(2,2)))**2
     2         +(cdabs(-ebppb*ddmi(2,1)+el_m2/ebppb*ddpl(2,1)))**2
     3         +(cdabs(ebppb*ddpl(1,2)-el_m2/ebppb*ddmi(1,2)))**2 )
     4         *(1.d0 + ver_s)*cdabs(cvac_s)**2
c
c ISR+correction FSR 
c in the amplitudes 'magnetic' amplitude added at difference from pion case
c 
        if(fsrnlo.eq.1)then
        ampLOm = ampLOm + ( (dme*cdabs(mb(1,1)-ma(1,1)))**2
     1          +(dme*cdabs(mb(2,2)-ma(2,2)))**2
     2          +(cdabs(-ebppb*ma(2,1)+el_m2/ebppb*mb(2,1)))**2
     3          +(cdabs(ebppb*mb(1,2)-el_m2/ebppb*ma(1,2)))**2 )
     4          * ver_f* cdabs(cvac_qq)**2
      ampLOm = ampLOm
     4         +2.d0*dreal(ver_ma*(
     5    dconjg(dme*(mb(1,1)-ma(1,1)))*dme*(mb_ma(1,1)-ma_ma(1,1))
     6   +dconjg(dme*(mb(2,2)-ma(2,2)))*dme*(mb_ma(2,2)-ma_ma(2,2))
     7   +dconjg((-ebppb*ma(2,1)+el_m2/ebppb*mb(2,1)))*
     8    (-ebppb*ma_ma(2,1)+el_m2/ebppb*mb_ma(2,1))
     9   +dconjg((ebppb*mb(1,2)-el_m2/ebppb*ma(1,2)))*
     1    (ebppb*mb_ma(1,2)-el_m2/ebppb*ma_ma(1,2))))* cdabs(cvac_qq)**2
        endif
c
      if(fsr.eq.2)then
c
c the FSR x ISR 
      ampLOm = ampLOm
     4         +2.d0*dreal(
     5    dconjg(dme*(mb(1,1)-ma(1,1))*cvac_qq)
     5     *dme*(ddpl(1,1)-ddmi(1,1))*cvac_s
     6   +dconjg(dme*(mb(2,2)-ma(2,2))*cvac_qq)
     6     *dme*(ddpl(2,2)-ddmi(2,2))*cvac_s
     7   +dconjg((-ebppb*ma(2,1)+el_m2/ebppb*mb(2,1))*cvac_qq)*
     8    (-ebppb*ddmi(2,1)+el_m2/ebppb*ddpl(2,1))*cvac_s
     9   +dconjg((ebppb*mb(1,2)-el_m2/ebppb*ma(1,2))*cvac_qq)*
     1    (ebppb*ddpl(1,2)-el_m2/ebppb*ddmi(1,2))*cvac_s)
c
      endif
c
      enddo
      enddo
      enddo
c
      return
      end
c*****************************************************************************
c     matrices and scalar products; mi=minus, pl=plus,
c     eck1=epsilon*(k1) etc.
c
      subroutine skalar1LO(rk1) 
      include 'phokhara_6.0.inc'     
      complex*16 gam(4),eck1(4),eck2(4),pi1eck1,pi2eck1
      complex*16 qpl(2,2),qmi(2,2),gampl(2,2),gammi(2,2),k1pl(2,2),
     1          k1mi(2,2),k2pl(2,2),k2mi(2,2),eck1pl(2,2),eck1mi(2,2),
     2        eck2pl(2,2),eck2mi(2,2),I(2,2),sigpl(4,2,2),sigmi(4,2,2) 
     3       ,gampl_ma(2,2),gammi_ma(2,2)
      real*8 p1(4),p2(4),rk1(4),rk2(4),q(4)
      real*8 rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2,dme,el_m2
     1      ,rat1,cos1,rk1pi1,rk1pi2
      integer i1
c
      common/matri/qpl,qmi,gampl,gammi,k1pl,k1mi,k2pl,k2mi,eck1pl,
     1             eck1mi,eck2pl,eck2mi,I,sigpl,sigmi,gampl_ma,gammi_ma
      common/iloczs2/rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2
      common /cp1p2/p1,p2,dme,el_m2
      common/iloczs3/pi1eck1,pi2eck1,rk1pi1,rk1pi2
c
      rat1 = el_m2/(p1(1)+p1(4))
c
      cos1 = rk1(4) / rk1(1)
c
      rk1p1 = rk1(1) * ( rat1 + p1(4) * (1.d0 - cos1) )
      rk1p2 = rk1(1) * ( rat1 + p1(4) * (1.d0 + cos1) )
c
      rk1pi1 = rk1(1)*momenta(6,0)      
      rk1pi2 = rk1(1)*momenta(7,0)
      do i1 =1,3
       rk1pi1 = rk1pi1 - rk1(i1+1)*momenta(6,i1)
       rk1pi2 = rk1pi2 - rk1(i1+1)*momenta(7,i1)
      enddo     
c
      call plus(rk1,k1pl)
      call minus(rk1,k1mi)
c
      return
      end
c*****************************************************************************
c     matrices and scalar products; mi=minus, pl=plus,
c     eck1=epsilon*(k1) etc.
c
      subroutine skalar1aLO(gam,gam_ma)
      include 'phokhara_6.0.inc'     
      complex*16 gam(4),gam_ma(4),gampl_ma(2,2),gammi_ma(2,2)
      complex*16 qpl(2,2),qmi(2,2),gampl(2,2),gammi(2,2),k1pl(2,2),
     1          k1mi(2,2),k2pl(2,2),k2mi(2,2),eck1pl(2,2),eck1mi(2,2),
     2        eck2pl(2,2),eck2mi(2,2),I(2,2),sigpl(4,2,2),sigmi(4,2,2) 
c
      common/matri/qpl,qmi,gampl,gammi,k1pl,k1mi,k2pl,k2mi,eck1pl,
     1             eck1mi,eck2pl,eck2mi,I,sigpl,sigmi,gampl_ma,gammi_ma
c
      call cplus(gam,gampl)
      call cminus(gam,gammi)
c
      if((pion.eq.0).and.(fsrnlo.eq.1))then
       call cplus(gam_ma,gampl_ma)
       call cminus(gam_ma,gammi_ma)
      endif
c
      return
      end
c*****************************************************************************
c     matrices and scalar products; mi=minus, pl=plus,
c     eck1=epsilon*(k1) etc.
c
      subroutine skalar2LO(rk1,eck1)
      include 'phokhara_6.0.inc'     
      complex*16 gam(4),eck1(4),eck2(4),p1eck1,p1eck2,p2eck1,p2eck2
     1          ,p1gam,p2gam,dd(4)
      complex*16 qpl(2,2),qmi(2,2),gampl(2,2),gammi(2,2),k1pl(2,2),
     1          k1mi(2,2),k2pl(2,2),k2mi(2,2),eck1pl(2,2),eck1mi(2,2),
     2          eck2pl(2,2),eck2mi(2,2),I(2,2)
     3         ,sigpl(4,2,2),sigmi(4,2,2),ddpl(2,2),ddmi(2,2) 
     3       ,gampl_ma(2,2),gammi_ma(2,2)
      complex*16 pi1eck1,pi2eck1,f1,BW
      real*8 rk1pi1,rk1pi2,dme,el_m2,p1(4),p2(4),rk1(4),rk2(4),q(4)
      integer i1
c
      common/iloczs1/p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam
      common/matri/qpl,qmi,gampl,gammi,k1pl,k1mi,k2pl,k2mi,eck1pl,
     1             eck1mi,eck2pl,eck2mi,I,sigpl,sigmi,gampl_ma,gammi_ma
      common /cp1p2/p1,p2,dme,el_m2
      common/iloczs3/pi1eck1,pi2eck1,rk1pi1,rk1pi2
c
      call cplus(eck1,eck1pl)
      call cminus(eck1,eck1mi)
c
c     scalar products multiplied by 2, not reflected in their names !
c
      p1eck1=2.d0*(p1(1)*eck1(1)-p1(2)*eck1(2)-p1(3)*eck1(3)-
     1            p1(4)*eck1(4))
      p2eck1=2.d0*(p2(1)*eck1(1)-p2(2)*eck1(2)-p2(3)*eck1(3)-
     1            p2(4)*eck1(4))  
c
      pi1eck1 = momenta(6,0)*eck1(1)      
      pi2eck1 = momenta(7,0)*eck1(1)      
      do i1 =1,3
       pi1eck1 = pi1eck1 - momenta(6,i1)*eck1(i1+1)
       pi2eck1 = pi2eck1 - momenta(7,i1)*eck1(i1+1)
      enddo
c
      return
      end
c*****************************************************************************
      subroutine blocksLO(qq)
      include 'phokhara_6.0.inc'         
      complex*16 p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam
     1          ,pi1eck1,pi2eck1
      complex*16 qpl(2,2),qmi(2,2),gampl(2,2),gammi(2,2),k1pl(2,2),
     1          k1mi(2,2),k2pl(2,2),k2mi(2,2),eck1pl(2,2),eck1mi(2,2),
     2        eck2pl(2,2),eck2mi(2,2),I(2,2),sigpl(4,2,2),sigmi(4,2,2)
     3       ,gampl_ma(2,2),gammi_ma(2,2)
      complex*16 m1(2,2),m2(2,2),m3(2,2),m4(2,2),m5(2,2),m6(2,2),
     1         n1(2,2),n2(2,2),n3(2,2),n4(2,2),n5(2,2),n6(2,2),n7(2,2),
     2         n8(2,2),n9(2,2),n10(2,2),n11(2,2),n12(2,2)
      complex*16 block1(2,2),block2(2,2),block3(2,2),block4(2,2),
     1          block5(2,2),block6(2,2),block7(2,2),block8(2,2),
     2          block9(2,2),block10(2,2),block11(2,2),block12(2,2)
      complex*16 m1amp1(2,2),mamp1a(2,2),m2amp1(2,2),mamp1b(2,2),
     1           m1amp2(2,2),mamp2a(2,2),m2amp2(2,2),mamp2b(2,2),
     2           m1amp3(2,2),mamp3a(2,2),m2amp3(2,2),mamp3b(2,2), 
     3           m1amp4(2,2),mamp4a(2,2),m2amp4(2,2),mamp4b(2,2),
     4           m1amp5(2,2),mamp5a(2,2),m2amp5(2,2),mamp5b(2,2),
     5           m1amp6(2,2),mamp6a(2,2),m2amp6(2,2),mamp6b(2,2),
     6  m1amp3_ma(2,2),m1amp4_ma(2,2),m2amp3_ma(2,2),m2amp4_ma(2,2)
      complex*16 ma(2,2),mb(2,2),ma_ma(2,2),mb_ma(2,2)
      real*8 qq,rk1pi1,rk1pi2
c
      common/iloczs1/p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam
      common/matri/qpl,qmi,gampl,gammi,k1pl,k1mi,k2pl,k2mi,eck1pl,
     1             eck1mi,eck2pl,eck2mi,I,sigpl,sigmi,gampl_ma,gammi_ma
      common/matri1/ma,mb,ma_ma,mb_ma
      common/iloczs3/pi1eck1,pi2eck1,rk1pi1,rk1pi2
      common/blocks1/block1,block2,block3,block4
c
      call conmat(p2eck1,I,m1)
      call conmat(p1eck1,I,m3)
c
      call matr(eck1mi,k1pl,n5)
      call matr(eck1pl,k1mi,n6)
      call matr(k1pl,eck1mi,n11)
      call matr(k1mi,eck1pl,n12)
c
      call minmat(n5,m3,block5)
      call minmat(n6,m3,block6)
      call minmat(m1,n11,block9)
      call minmat(m1,n12,block10)
c
      call matr(block5,gammi,m1amp3)
      call matr(block6,gampl,m2amp3)
c
      call matr(gammi,block9,m1amp4)
      call matr(gampl,block10,m2amp4)
c
c     adding matrices of the type A and B
c
      call plumatLO(qq,m1amp3,m1amp4,ma)
      call plumatLO(qq,m2amp3,m2amp4,mb)
c
c additional part for muon FSR
c     
      if(pion.eq.0)then
c
c additional part for muon FSR
c     
       call conmat(2.d0*pi1eck1,I,m5)
       call conmat(2.d0*pi2eck1,I,m6)
       call dodmat(m5,n11,block1)
       call dodmat(m5,n12,block2)
       call dodmat(m6,n5,block3)
       call dodmat(m6,n6,block4)
c
c additional part for muon FSRNLO - 'magnetic' amplitude constructed here
c     
       if(fsrnlo.eq.1)then
        call matr(block5,gammi_ma,m1amp3_ma)
        call matr(block6,gampl_ma,m2amp3_ma)
c
        call matr(gammi_ma,block9,m1amp4_ma)
        call matr(gampl_ma,block10,m2amp4_ma)
c
c     adding matrices of the type A and B
c
        call plumatLO(qq,m1amp3_ma,m1amp4_ma,ma_ma)
        call plumatLO(qq,m2amp3_ma,m2amp4_ma,mb_ma)
       endif
c
      endif
c
      return
      end
c**************************************************************************
      subroutine ddvec(rk1,eck1,uupp1,uupp2,vv1,vv2,ddpl,ddmi,qq)
      include 'phokhara_6.0.inc'     
      complex*16 gam(4),eck1(4),eck2(4),dd(4)
      complex*16 qpl(2,2),qmi(2,2),gampl(2,2),gammi(2,2),k1pl(2,2),
     1          k1mi(2,2),k2pl(2,2),k2mi(2,2),eck1pl(2,2),eck1mi(2,2),
     2          eck2pl(2,2),eck2mi(2,2),I(2,2),sigpl(4,2,2),sigmi(4,2,2)
     3         ,ddpl(2,2),ddmi(2,2),gampl_ma(2,2),gammi_ma(2,2)
      complex*16 block1(2,2),block2(2,2),block3(2,2),block4(2,2)
      complex*16 uupp1(1,2),uupp2(1,2),vv1(2,1),vv2(2,1)
      complex*16 pi1eck1,pi2eck1,f1,wyn1,wyn2,PionFormFactor,
     1           KaonFormFactor,BW_om,phas2
      complex*16 mm1a(2,2),mm1b(2,2),mma(2,2),mm2a(2,2),mm2b(2,2)
     1          ,mmb(2,2),F_phi_KK,Fun_phi,phas1,F_phi_no,F_phi_exp
      real*8 rk1pi1,rk1pi2,qq,aa_phi,mm_ph,gg_ph,phas_rho_f0_exp,
     1       mm_f0_exp,c_f0_KK_exp,c_f0_pipi_exp,ff_phi_exp,c_phi_KK,
     2       rho_phi_exp,lamb_phi_exp,phas_rho_f0

      real*8 rk1(4),rk2(4),q(4),mass_2pi
      integer i1,jj
c
      common/matri/qpl,qmi,gampl,gammi,k1pl,k1mi,k2pl,k2mi,eck1pl,
     1             eck1mi,eck2pl,eck2mi,I,sigpl,sigmi,gampl_ma,gammi_ma
      common/iloczs3/pi1eck1,pi2eck1,rk1pi1,rk1pi2
      common/blocks1/block1,block2,block3,block4
      common/phases_f0/phas1,phas2
      common/param_PFF/aa_phi,mm_ph,gg_ph
      common/param_f0_exp/mm_f0_exp,phas_rho_f0_exp,c_f0_KK_exp,
     1       c_f0_pipi_exp,ff_phi_exp,c_phi_KK,rho_phi_exp,lamb_phi_exp
c
c D vector constructed : FSR
c
c pi+ pi-
      if(pion.eq.1)then
        f1 = PionFormFactor(Sp)/Sp
       
      if(f0_model.eq.0)then
        Fun_phi = F_phi_KK(qq,Sp)
        phas_rho_f0 = 75.d0*dSqrt(qq-4.d0*mpi**2)
        phas1 = exp(dcmplx(0.d0,phas_rho_f0*pi/180.d0))
      elseif(f0_model.eq.1)then
         Fun_phi = F_phi_no(qq,Sp)
      elseif(f0_model.eq.2)then
         Fun_phi = (0.d0,0.d0)
      elseif(f0_model.eq.3)then
         Fun_phi = - F_phi_exp(qq,Sp)    
         phas1 = exp(dcmplx(0.d0,
     1           phas_rho_f0_exp*dSqrt(1.d0-4.d0*mpi**2/qq)*pi/180.d0))

      endif

      do i1=1,4
       dd(i1) = 
     1( ((momenta(6,i1-1)+rk1(i1)-momenta(7,i1-1))*pi1eck1/rk1pi1
     2  +(momenta(7,i1-1)+rk1(i1)-momenta(6,i1-1))*pi2eck1/rk1pi2
     3  -2.d0*eck1(i1))*f1 )*(cvac_s_pi-cvac_s_phi)
     4  + phas1 * Fun_phi/Sp* 
     6   ( (rk1pi1+rk1pi2)*eck1(i1) - (pi1eck1+pi2eck1)*rk1(i1) )
     7                      * cvac_s_pi
      enddo
c
c kaons K+K-
      elseif(pion.eq.6)then
       f1 = KaonFormFactor(Sp)/Sp
      do i1=1,4
       dd(i1) = 
     1    ((momenta(6,i1-1)+rk1(i1)-momenta(7,i1-1))*pi1eck1/rk1pi1
     2    +(momenta(7,i1-1)+rk1(i1)-momenta(6,i1-1))*pi2eck1/rk1pi2
     3         -2.d0*eck1(i1))*f1
      enddo
c
c muons
      else
      do i1=1,4
       call matr2(i1,block3,sigmi,mm1a)
       call matr2(i1,block4,sigpl,mm1b)
       call matr1(i1,sigmi,block1,mm2a)
       call matr1(i1,sigpl,block2,mm2b)
       call plumat1_LO(Sp,mm1a,mm2a,mma)
       call plumat1_LO(Sp,mm1b,mm2b,mmb)
       call stal(uupp1,mma,vv1,wyn1)
       call stal(uupp2,mmb,vv2,wyn2)
       dd(i1) = wyn1+wyn2
      enddo
      endif
c
      call cplus(dd,ddpl)
      call cminus(dd,ddmi)
c
      return
      end
c *************************************************************************
      complex*16 function F_phi_KK(qq,xx)
      include 'phokhara_6.0.inc'     
      real*8 mm_ph,gg_ph,mm_f0,gg_f0,c_phi_KK_f0_pi,qq,aa_phi,
     1       c_phi_gam,mm_f0_600,gg_f0_600,c_phi_KK_f0_600_pi,xx
      complex*16 ff0_II,phas1,phas2,i,ff
      common/param_PFF/aa_phi,mm_ph,gg_ph
      common/param_f0/mm_f0,gg_f0,c_phi_KK_f0_pi,c_phi_gam,
     1                mm_f0_600,gg_f0_600,c_phi_KK_f0_600_pi
      common/phases_f0/phas1,phas2

      i = (0.d0,1.d0)
      ff = ( c_phi_KK_f0_pi / (mm_f0**2-qq-i*mm_f0*gg_f0)
     1   + phas2 * c_phi_KK_f0_600_pi
     3           / (mm_f0_600**2-qq-i*mm_f0_600*gg_f0_600) )
     2   / 2.d0 / pi**2 / mKp**2 * ff0_II(qq) 

      F_phi_KK =   c_phi_gam/(xx-mm_ph**2+i*mm_ph*gg_ph)*ff

      return
      end
c *************************************************************************
      complex*16 function ff0_II(qq)
      include 'phokhara_6.0.inc'         
      real*8 qq,aa,bb,amb,mm_ph,gg_ph,aa_phi
      complex*16 ff_f0,gg_f0
      common/param_PFF/aa_phi,mm_ph,gg_ph
c------
      aa = (mm_ph/mKp)**2
      bb = qq/mKp**2
      amb = aa-bb
      ff0_II = 0.5d0/amb-2.d0/amb**2*(ff_f0(1.d0/bb)-ff_f0(1.d0/aa))
     1    +aa/amb**2*(gg_f0(1.d0/bb)-gg_f0(1.d0/aa))
      return
      end
c ************************************************************************
      complex*16 function ff_f0(xx)
      include 'phokhara_6.0.inc'         
      real*8 xx
c------
      if(xx.ge.0.25d0)then
       ff_f0 = -asin(0.5d0/sqrt(xx))**2
      else
       ff_f0 = 0.25*( log((1.d0+sqrt(1.d0-4.d0*xx))**2/4.d0/xx)
     1            -dcmplx(0.d0,-pi))**2
      endif
      return
      end
c ************************************************************************
      complex*16 function gg_f0(xx)
      include 'phokhara_6.0.inc'
      real*8 xx
c------
      if(xx.ge.0.25d0)then
       gg_f0 = sqrt(4.d0*xx-1.d0)*asin(0.5d0/sqrt(xx))
      else
       gg_f0 = 0.5*sqrt(1.d0-4.d0*xx)
     1     *( log((1.d0+sqrt(1.d0-4.d0*xx))**2/4.d0/xx)
     1            -dcmplx(0.d0,-pi))
      endif
      return
      end
c *************************************************************************
      complex*16 function F_phi_no(qq,xx)
      include 'phokhara_6.0.inc'     
      real*8 mm_ph,gg_ph,mm_f0,gg_f0,c_phi_KK_f0_pi,qq,aa_phi,
     1       c_phi_gam,mm_f0_600,gg_f0_600,c_phi_KK_f0_600_pi,xx
      complex*16 phas1,phas2,i,ff
      common/param_PFF/aa_phi,mm_ph,gg_ph
      common/param_f0/mm_f0,gg_f0,c_phi_KK_f0_pi,c_phi_gam,
     1                mm_f0_600,gg_f0_600,c_phi_KK_f0_600_pi
      common/phases_f0/phas1,phas2

      i = (0.d0,1.d0)
      ff = ( c_phi_KK_f0_pi / (mm_f0**2-qq-i*mm_f0*gg_f0)
     1   + phas2 * c_phi_KK_f0_600_pi
     3           / (mm_f0_600**2-qq-i*mm_f0_600*gg_f0_600) ) 

      F_phi_no =   c_phi_gam/(xx-mm_ph**2+i*mm_ph*gg_ph)*ff

      return
      end
c *************************************************************************
      complex*16 function F_phi_exp(qq,xx)
      include 'phokhara_6.0.inc' 
      real*8 aa_phi,mm_ph,gg_ph,qq
      real*8 mm_f0_exp,phas_rho_f0_exp,c_f0_KK_exp,c_f0_pipi_exp,
     1       ff_phi_exp,c_phi_KK,rho_phi_exp,lamb_phi_exp,xx
      complex*16 i,D_f0_exp,gg_mm_exp,BW_om,D_phi_exp
      common/param_PFF/aa_phi,mm_ph,gg_ph
      common/param_f0_exp/mm_f0_exp,phas_rho_f0_exp,c_f0_KK_exp,
     1      c_f0_pipi_exp,ff_phi_exp,c_phi_KK,rho_phi_exp,lamb_phi_exp

      i = (0.d0,1.d0)

      D_phi_exp = BW_om(mm_ph,gg_ph,xx,1)

      F_phi_exp = ff_phi_exp * 2.d0 / (xx-qq) * D_phi_exp 
     1          * c_f0_pipi_exp 
c g(m)
     3          * c_phi_KK * c_f0_KK_exp / 8.d0 / pi**2
     4          * gg_mm_exp(qq,rho_phi_exp,lamb_phi_exp) 
c 1/D_f0
     2          /D_f0_exp(qq)
      return
      end
c *************************************************************************
      complex*16 function gg_mm_exp(qq,rho_phi_exp,lamb_phi_exp)
      include 'phokhara_6.0.inc'

      real*8 qq,rho_phi_exp,aa_phi,mm_ph,gg_ph,rho_m_exp,
     1       lamb_m_exp,lamb_phi_exp
      complex*16 i
      common/param_PFF/aa_phi,mm_ph,gg_ph

      i = (0.d0,1.d0)

      rho_m_exp = sqrt(1.d0 - 4.d0*mKp**2/qq)

      if(sqrt(qq).lt.(2.d0*mKp))then

      rho_m_exp = sqrt(-1.d0 + 4.d0*mKp**2/qq)

         gg_mm_exp = 1.d0 + mm_ph**2/(mm_ph**2-qq)
     1           * ( 2.d0 * rho_m_exp * dAtan(1.d0/rho_m_exp)
     2             - rho_phi_exp*lamb_phi_exp + i*pi* rho_phi_exp
     3             - 4.d0*(mKp/mm_ph)**2
     4             * ( (pi+i*lamb_phi_exp)**2/4.d0 
     5                - (dAtan(1.d0/rho_m_exp))**2 ) )   

      else

      rho_m_exp = sqrt(1.d0 - 4.d0*mKp**2/qq)
      lamb_m_exp = log((1.d0+rho_m_exp)**2 *qq/4.d0/mKp**2) 

      gg_mm_exp = 1.d0 +  mm_ph**2/(mm_ph**2-qq)
     1        * ( rho_m_exp*(lamb_m_exp-i*pi)
     2          - rho_phi_exp*(lamb_phi_exp-i*pi)
     3          - (mKp/mm_ph)**2
     4          * ( (pi+i*lamb_phi_exp)**2 - (pi+i*lamb_m_exp)**2 ) )

      endif

      return
      end
c *************************************************************************
      complex*16 function D_f0_exp(qq)
      include 'phokhara_6.0.inc'

      real*8 qq,m_KKp_exp,m_pip_exp,mm_f0_exp,phas_rho_f0_exp,
     2       c_f0_KK_exp,c_f0_pipi_exp,ff_phi_exp,c_phi_KK,rho_phi_exp,
     1       lamb_phi_exp
      complex*16 PP_ab
      common/param_f0_exp/mm_f0_exp,phas_rho_f0_exp,c_f0_KK_exp,
     1      c_f0_pipi_exp,ff_phi_exp,c_phi_KK,rho_phi_exp,lamb_phi_exp

c m_\pi^+ = m_\pi^-
c m_K^+ = m_K^-
      m_KKp_exp = 4.d0*mKp**2
      m_pip_exp   = 4.d0*mpi**2

      D_f0_exp = mm_f0_exp**2 - qq + c_f0_KK_exp**2/16.d0/pi *
     1( dreal(PP_ab(mm_f0_exp**2,m_KKp_exp)) - PP_ab(qq,m_KKp_exp) )
     2                             + c_f0_pipi_exp**2/16.d0/pi *
     1( dreal(PP_ab(mm_f0_exp**2,m_pip_exp)) - PP_ab(qq,m_pip_exp) )

      return
      end
c *************************************************************************
      complex*16 function PP_ab(mm,mm_p)
      include 'phokhara_6.0.inc'

      real*8 mm,mm_p,rho_ab
      complex*16 i

      i = (0.d0,1.d0)

      if(mm.gt.mm_p)then
        rho_ab = sqrt(1.d0-mm_p/mm)

         PP_ab = 1.d0/pi * sqrt(1.d0 - mm_p/mm)
     1         * log(mm_p/(sqrt(mm)+sqrt(mm-mm_p))**2)
     2         + i * rho_ab
      else

        rho_ab = sqrt(-1.d0+mm_p/mm)
        PP_ab = rho_ab * (-1.d0 + 2.d0/pi * dAtan(sqrt(mm_p/mm-1.d0)) )
      endif

      return
      end
c**************************************************************************
c     addind 2 matrices: with proper denominators
c     for one photon initial state emission
c
      subroutine plumatLO(qq,mat1,mat2,mat3)  
      implicit none
      real*8 qq,rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2
      integer i,j
      complex*16 mat1(2,2),mat2(2,2),mat3(2,2)
c
      common/iloczs2/rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2
c
      do i=1,2
         do j=1,2
            mat3(i,j)=  0.5d0*mat1(i,j)/rk1p1/qq
     1                 +0.5d0*mat2(i,j)/rk1p2/qq
         enddo
      enddo
      end
c**************************************************************************
c     addind 2 matrices: with proper denominators
c     for one photon final state emission (muons)
c
      subroutine plumat1_LO(dev,mat1,mat2,mat3)      
      implicit none
      complex*16 mat1(2,2),mat2(2,2),mat3(2,2)
      complex*16 pi1eck1,pi2eck1
      real*8 rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2,rk1pi1,rk1pi2,
     1       dev
      integer i,j
c
      common/iloczs2/rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2
      common/iloczs3/pi1eck1,pi2eck1,rk1pi1,rk1pi2
c
      do i=1,2
         do j=1,2
            mat3(i,j)=  0.5d0*mat1(i,j)/rk1pi2/dev
     1                 -0.5d0*mat2(i,j)/rk1pi1/dev
         enddo
      enddo
      end
c**************************************************************************
c     multiplication of the 1x2 2x2 2x1 matrics
c 
      subroutine stal(mat1,mat2,mat3,wyn)
      implicit none
      complex*16  mat1(1,2),mat2(2,2),mat3(2,1),wyn,matp(1,2)
      integer i,k
c
      wyn = (0.d0,0.d0)
      do i=1,2
         matp(1,i) = (0.d0,0.d0)
      enddo
c
      do i=1,2
         do k=1,2
            matp(1,i) = matp(1,i)+mat1(1,k)*mat2(k,i)
         enddo
      enddo
c
      do i=1,2
         wyn = wyn + matp(1,i)*mat3(i,1)
      enddo
      return
      end
c ------------------------------------------------------------------------
c ************************************************************************
c two photons
c ************************************************************************
c ------------------------------------------------------------------------

      double precision function helicityamp(qq,q0p,q2p,q0b,q2b)
      include 'phokhara_6.0.inc'     
      double precision qq,rk1(4),rk2(4),q(4),dps,amp_h,amp,rlam
     1                ,pionFF,q0p,q2p,q0b,q2b,a,b,c,mmu_1
      complex*16 gam(4),gammu(4,2,2),v1(2,2),v2(2,2),up1(2,2),up2(2,2)
     1          ,gammu_ma(4,2,2)
      complex*16 uupp1(1,2),uupp2(1,2),vv1(2,1),vv2(2,1)
      integer i1,ic1,ic2
c
      rlam(a,b,c) = sqrt( (1.d0-(b+c)**2/a) * (1.d0-(b-c)**2/a) )

      call gam1(gam,gammu,gammu_ma,v1,v2,up1,up2,qq)
      do i1=1,4
         rk1(i1) = momenta(3,i1-1)
         rk2(i1) = momenta(4,i1-1)
         q(i1)   = momenta(5,i1-1)
      enddo
c
      dps = Sp/(4.d0*(2.d0*pi)**5)  ! Phase space factors
c
c --- muons ---
      if(pion.eq.0)then
      mmu_1=mmu      
      call fermionamp
     &      (mmu_1,gammu,v1,v2,up1,up2,q,qq,rk1,rk2,dps,amp_h)

c
c --- 2 pions ---
      elseif(pion.eq.1)then
      dps = dps*dSqrt(1.d0-4.d0*mpi*mpi/qq)/(32.d0*pi*pi) 
      amp_h = ((4.d0*pi*alpha)**4/qq**2)*
     1                 amp(rk1,rk2,gam,q,qq,uupp1,uupp2,vv1,vv2)/4.d0
c
c --- 4 pions ---
      elseif((pion.eq.2).or.(pion.eq.3))then
c
c          Phase space factors
c
      dps = dps/(2.d0*pi)**2/(32.d0*pi**2)**3
     1     * rlam(qq,q0p,rmass(1)) 
     2     * rlam(q2p,q0b,rmass(2)) 
     3     * rlam(q2b,rmass(3),rmass(4))
c
c --- pions 2pi^0 pi^+ pi^-
       if(pion.eq.2)then
        dps = dps * 0.5d0
       endif
c
c --- pions 2pi^+ 2pi^-  
       if(pion.eq.3)then
        dps = dps * 0.25d0
       endif
      amp_h = ((4.d0*pi*alpha)**4/qq**2)*
     1                  amp(rk1,rk2,gam,q,qq,uupp1,uupp2,vv1,vv2)/4.d0
c
c----- PPbar ---------------
      elseif(pion.eq.4)then
      mmu_1=mp
      call fermionamp
     &      (mmu_1,gammu,v1,v2,up1,up2,q,qq,rk1,rk2,dps,amp_h)
c
c----- NNbar ---------------
      elseif(pion.eq.5)then
      mmu_1=mnt
      call fermionamp
     &      (mmu_1,gammu,v1,v2,up1,up2,q,qq,rk1,rk2,dps,amp_h)
c 
c --- kaons K^+ K^- ---
      elseif(pion.eq.6)then
      dps = dps*dSqrt(1.d0-4.d0*mKp*mKp/qq)/(32.d0*pi*pi) 
      amp_h = ((4.d0*pi*alpha)**4/qq**2)*
     1                 amp(rk1,rk2,gam,q,qq,uupp1,uupp2,vv1,vv2)/4.d0
c
c --- kaons K^0 K^0bar ---
      elseif(pion.eq.7)then
      dps = dps*dSqrt(1.d0-4.d0*mKn*mKn/qq)/(32.d0*pi*pi) 
      amp_h = ((4.d0*pi*alpha)**4/qq**2)*
     1                 amp(rk1,rk2,gam,q,qq,uupp1,uupp2,vv1,vv2)/4.d0
c
c --- pions pi^0 pi^+ pi^-
      elseif(pion.eq.8)then
c
c        Phase space factors
c
      dps = dps/(2.d0*pi)/(32.d0*pi**2)**2
     1    * rlam(qq,q0p,rmass(1))
     2    * rlam(q2p,rmass(2),rmass(3))

      amp_h = ((4.d0*pi*alpha)**4/qq**2)*
     1                  amp(rk1,rk2,gam,q,qq,uupp1,uupp2,vv1,vv2)/4.d0
      else
       continue
      endif
c
      helicityamp = amp_h*dps
      return
      end
c*****************************************************************************
      subroutine fermionamp
     &      (mmu_1,gammu,v1,v2,up1,up2,q,qq,rk1,rk2,dps,amp_h)
      include 'phokhara_6.0.inc'     
      double precision qq,rk1(4),rk2(4),q(4),dps,amp_h,amp,mmu_1
      complex*16 gam(4),gammu(4,2,2),v1(2,2),v2(2,2),up1(2,2),up2(2,2)
      complex*16 uupp1(1,2),uupp2(1,2),vv1(2,1),vv2(2,1)
      integer i1,ic1,ic2

      dps = dps*dSqrt(1.d0-4.d0*mmu_1*mmu_1/qq)/(32.d0*pi*pi)
      amp_h = 0.d0

      do ic1=1,2
      do ic2=1,2
c
c the spinors
c
         if(fsrnlo.eq.1)then
          uupp2(1,1) = up2(1,ic1)
          uupp2(1,2) = up2(2,ic1)
          uupp1(1,1) = up1(1,ic1)
          uupp1(1,2) = up1(2,ic1)
    
          vv1(1,1) = v1(1,ic2)                 
          vv1(2,1) = v1(2,ic2)                 
          vv2(1,1) = v2(1,ic2)                 
          vv2(2,1) = v2(2,ic2)
         endif                 
c
c now gam is the muon current (no emission)
c
        do i1=1,4
         gam(i1)=gammu(i1,ic1,ic2)
        enddo

        amp_h = amp_h + amp(rk1,rk2,gam,q,qq,uupp1,uupp2,vv1,vv2)

      enddo
      enddo
      amp_h = ((4.d0*pi*alpha)**4/qq**2)*amp_h/4.d0

      return
      end
c*****************************************************************************
c the 2pi(pion=1) and mu+, mu-(pion=0) currents + 4pi currents
c
      subroutine gam1(gam,gammu,gammu_ma,v1,v2,up1,up2,qq)
      include 'phokhara_6.0.inc'       
      integer mu,ic1,ic2,ic3,i
      real*8 qq,th1,th2,sphi1,cphi1,sphi2,cphi2,cth1d2,sth1d2,
     &       cth2d2,sth2d2,sq1,sq2,em1,em2,pm1,pm2,sth1,sth2,
     &       q1(4),q2(4),q3(4),q4(4)
      complex*16 PionFormFactor,KaonFormFactor
     1      ,gam(4),f1,gammu(4,2,2),gammu_ma(4,2,2)
     &      ,v1(2,2),v2(2,2),up1(2,2),up2(2,2),ex1,ex2,sss

      real*8 mmu1
      complex*16 gammu1(4,2,2),gammu2(2,2),protF1,protF2 
      integer iic
c
c --- muons ---   
c  four different combinations of \mu^+, \mu^- helicities
c ++,+-,-+,-- ; v1(i,1)==v1(i,+),v1(i,2)==v1(i,-) etc.
c see notes p.4-6   
c
      if (pion.eq.0)then 
      mmu1=mmu
      call spinors(mmu1,up1,up2,v1,v2) 
c
c sign change compared to the previous version (see notes p.4)
c does inluence only interference
c
       do ic1=1,2
       do ic2=1,2
c
c LO muon current
c
        gammu(1,ic1,ic2) = -(up1(1,ic1)*v1(1,ic2)+up1(2,ic1)*v1(2,ic2)
     &                    +up2(1,ic1)*v2(1,ic2)+up2(2,ic1)*v2(2,ic2))
        gammu(2,ic1,ic2) = -(-up1(1,ic1)*v1(2,ic2)-up1(2,ic1)*v1(1,ic2)
     &                     +up2(1,ic1)*v2(2,ic2)+up2(2,ic1)*v2(1,ic2))
        gammu(3,ic1,ic2) = -dcmplx(0.d0,1.d0)* 
     &                    (up1(1,ic1)*v1(2,ic2)-up1(2,ic1)*v1(1,ic2)
     &                    -up2(1,ic1)*v2(2,ic2)+up2(2,ic1)*v2(1,ic2))
        gammu(4,ic1,ic2) = -(-up1(1,ic1)*v1(1,ic2)+up1(2,ic1)*v1(2,ic2)
     &                     +up2(1,ic1)*v2(1,ic2)-up2(2,ic1)*v2(2,ic2))
c
c 'magnetic' current for muons FSR virtual corrections to ISR amplitude 
c
        if(fsrnlo.eq.1)then
          sss = -(up1(1,ic1)*v2(1,ic2)+up1(2,ic1)*v2(2,ic2)
     &           +up2(1,ic1)*v1(1,ic2)+up2(2,ic1)*v1(2,ic2))
          do ic3 =0,3
         gammu_ma(ic3+1,ic1,ic2) = (momenta(6,ic3)-momenta(7,ic3))*sss
          enddo
        endif
       enddo
       enddo
c
      elseif((pion.eq.1).or.(pion.eq.6).or.(pion.eq.7))then
c 
c --- 2 pions, kaons K^+K^-, K0K0bar ---

        if(pion.eq.1)f1 = PionFormFactor(qq)
        if((pion.eq.6).or.(pion.eq.7))f1 = KaonFormFactor(qq)
      do mu = 0,3
         gam(mu+1) = (momenta(6,mu)-momenta(7,mu))*f1
      enddo             
c
c --- pions 2pi^0 pi^+ pi^- --- pion=2
c --- pions 2pi^+ 2pi^-     --- pion=3
c        
      elseif((pion.eq.2).or.(pion.eq.3))then
c
      do i =0,3
       q1(i+1) = momenta(6,i)  
       q2(i+1) = momenta(7,i) 
       q3(i+1) = momenta(8,i)  
       q4(i+1) = momenta(9,i) 
      enddo
c
c --- pions 2pi^0 pi^+ pi^-
c
       if(pion.eq.2)  call had3(qq,q1,q2,q3,q4,gam)
c
c --- pions 2pi^+ 2pi^-  
c
       if(pion.eq.3)  call had2(qq,q1,q2,q3,q4,gam)
c
c ---- PPbar (pion=4) and NNbar (pion=5)  ----
c
      elseif ((pion.eq.4).or.(pion.eq.5)) then

      if(pion.eq.4)  mmu1 = mp
      if(pion.eq.5)  mmu1 = mnt     

      call spinors(mmu1,up1,up2,v1,v2)
      call ProtonFormFactor(qq,protF1,protF2)
c
c --- no minus sign due to treating proton as a particle 
c --- and antiproton as a antiparticle
c
       do ic1=1,2
       do ic2=1,2
       gammu1(1,ic1,ic2) = (up1(1,ic1)*v1(1,ic2)+up1(2,ic1)*v1(2,ic2)
     &                    +up2(1,ic1)*v2(1,ic2)+up2(2,ic1)*v2(2,ic2))
       gammu1(2,ic1,ic2) = (-up1(1,ic1)*v1(2,ic2)-up1(2,ic1)*v1(1,ic2)
     &                     +up2(1,ic1)*v2(2,ic2)+up2(2,ic1)*v2(1,ic2))
       gammu1(3,ic1,ic2) = dcmplx(0.d0,1.d0)* 
     &                    (up1(1,ic1)*v1(2,ic2)-up1(2,ic1)*v1(1,ic2)
     &                    -up2(1,ic1)*v2(2,ic2)+up2(2,ic1)*v2(1,ic2))
       gammu1(4,ic1,ic2) = (-up1(1,ic1)*v1(1,ic2)+up1(2,ic1)*v1(2,ic2)
     &                     +up2(1,ic1)*v2(1,ic2)-up2(2,ic1)*v2(2,ic2))
    
       gammu2(ic1,ic2) = (up1(1,ic1)*v2(1,ic2)+up1(2,ic1)*v2(2,ic2)
     &                    +up2(1,ic1)*v1(1,ic2)+up2(2,ic1)*v1(2,ic2))
         do iic=1,4
       gammu(iic,ic1,ic2) =  gammu1(iic,ic1,ic2) * (protF1+protF2)
     &                   + protF2 * (momenta(6,iic-1)-momenta(7,iic-1))
     &                   * gammu2(ic1,ic2)/2.D0/mmu1
         enddo
       enddo
       enddo
c
c c --- pions pi^0 pi^+ pi^-
c
      elseif(pion.eq.8)then

      do i =0,3
       q1(i+1) = momenta(6,i)  
       q2(i+1) = momenta(7,i) 
       q3(i+1) = momenta(8,i)  
      enddo

       call had_3pi(qq,q1,q2,q3,gam)

      else
       write(6,*)'wrong "pions" switch'
       stop
      endif
      return
      end
c ***************************************************************************
      subroutine  spinors(mmu1,up1,up2,v1,v2)
      include 'phokhara_6.0.inc'      
       real*8 th1,th2,sphi1,cphi1,sphi2,cphi2,cth1d2,sth1d2,
     &       cth2d2,sth2d2,sq1,sq2,em1,em2,pm1,pm2,sth1,sth2,mmu1
      complex*16 v1(2,2),v2(2,2),up1(2,2),up2(2,2),ex1,ex2
   
        em1 = momenta(7,0)
        em2 = momenta(6,0)
        pm1 = sqrt(em1**2-mmu1**2)
        pm2 = sqrt(em2**2-mmu1**2)
        sq1 = sqrt(em1+pm1)
        sq2 = sqrt(em2+pm2)
        th1 = acos(momenta(7,3)/pm1)
        th2 = acos(momenta(6,3)/pm2)
        cth1d2 = cos(th1/2.d0)
        cth2d2 = cos(th2/2.d0)
c
         v1(2,1)= -sq2*cth2d2
         v1(1,2)= mmu1/sq2*cth2d2
         v2(2,1)= v1(1,2)
         v2(1,2)= v1(2,1)
c
         up1(1,1) = mmu1/sq1*cth1d2
         up1(2,2) = sq1*cth1d2
         up2(1,1) = up1(2,2)
         up2(2,2) = up1(1,1)
c
        if((th2.eq.0.d0).or.(th2.eq.pi))then
         v1(1,1)= 0.d0
         v1(2,2)= 0.d0
         v2(1,1)= 0.d0
         v2(2,2)= 0.d0
        else
c
         sth2  = sin(th2)
         sth2d2= sin(th2/2.d0)
         cphi2 = momenta(6,1)/pm2/sth2
         sphi2 = momenta(6,2)/pm2/sth2
         ex2 = cphi2+dcmplx(0.d0,1.d0)*sphi2
c
         v1(1,1)= sq2*sth2d2/ex2
         v1(2,2)= mmu1/sq2*ex2*sth2d2
         v2(1,1)= -mmu1/sq2/ex2*sth2d2
         v2(2,2)= -sq2*ex2*sth2d2
        endif
c
        if((th1.eq.0.d0).or.(th1.eq.pi))then
         up1(1,2)=0.d0
         up1(2,1)=0.d0
         up2(1,2)=0.d0
         up2(2,1)=0.d0
        else
         sth1  = sin(th1)
         sth1d2= sin(th1/2.d0)
         cphi1 = momenta(7,1)/pm1/sth1
         sphi1 = momenta(7,2)/pm1/sth1
         ex1 = cphi1+dcmplx(0.d0,1.d0)*sphi1
c
         up1(1,2)= -sq1*ex1*sth1d2
         up1(2,1)= mmu1/sq1/ex1*sth1d2
         up2(1,2)= -mmu1/sq1*ex1*sth1d2
         up2(2,1)= sq1/ex1*sth1d2
        endif

         return
         end
c---------------------------------------------------------------------
c subroutine ProtonFormFactor includes proton (pion=4) 
c and neutron (pion=5) formractors as well
c---------------------------------------------------------------------
      subroutine ProtonFormFactor(qq,protF1,protF2)
      include 'phokhara_6.0.inc'
      complex*16 protF1,protF2,F1ss,F1vv,F2ss,F2vv,alphafun_pp,
     &           meson_pp,gfun_pp,ex_pp
      real*8 qq
      real*8 betarho_pp, betaomega_pp,betaphi_pp, alphaphi_pp,mrho_pp,
     & momega_pp,mphi_pp,gammarho_pp,theta_pp,gam_pp

      common /protparam/ betarho_pp, betaomega_pp,betaphi_pp, 
     &alphaphi_pp,mrho_pp,momega_pp,mphi_pp,gammarho_pp,theta_pp,gam_pp


      ex_pp = cos(theta_pp)+dcmplx(0.d0,1.d0)*sin(theta_pp)

      alphafun_pp = sqrt((qq-4.D0*mpi**2)/qq)* ( -dcmplx(0.d0,1.d0) 
     &     + 2.D0/pi*log( (sqrt(qq-4.D0*mpi**2)+sqrt(qq))/(2.D0*mpi) ))
      gfun_pp = 1.D0/(1.D0-gam_pp*qq*ex_pp)**2
       
      meson_pp = (mrho_pp**2+8.D0*gammarho_pp*mpi/pi)
     &   /(qq-mrho_pp**2+(qq-4.D0*mpi**2)*gammarho_pp*alphafun_pp/mpi)
  
      F1ss = (1.D0-betaomega_pp-betaphi_pp)
     &    - betaomega_pp*momega_pp**2
     &    /(qq-momega_pp**2) - betaphi_pp*mphi_pp**2/(qq-mphi_pp**2)
 
      F1vv =  (1.D0-betarho_pp) - betarho_pp*meson_pp

      F2ss = (0.12D0+alphaphi_pp) * momega_pp**2/(qq-momega_pp**2)
     &     - alphaphi_pp*mphi_pp**2/(qq-mphi_pp**2) 
    
      F2vv = - 3.706D0*meson_pp

      F1ss = 0.5D0 * gfun_pp * F1ss
      F1vv = 0.5D0 * gfun_pp * F1vv
      F2ss = 0.5D0 * gfun_pp * F2ss
      F2vv = 0.5D0 * gfun_pp * F2vv     

      if(pion.eq.4) then
      protF1 = F1ss+F1vv
      protF2 = F2ss+F2vv
      endif
 
      if(pion.eq.5) then
      protF1 = F1ss-F1vv
      protF2 = F2ss-F2vv
      endif

      return
      end
c ***************************************************************************
c     matrices and scalar products; mi=minus, pl=plus,
c     eck1=epsilon*(k1) etc.
c
      subroutine skalar1(rk1,rk2,gam,q)
      include 'phokhara_6.0.inc'
      real*8 dme,el_m2,p1,p2,q,rk1,rk2,rat1,cos1,cos2,
     1       rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2,
     2       rk2pi1,rk2pi2,rk1pi1,rk1pi2,qqa1,qqa2
      integer i1
      complex*16 gam,eck1,eck2,p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam
      complex*16 qpl(2,2),qmi(2,2),gampl(2,2),gammi(2,2),k1pl(2,2),
     1        k1mi(2,2),k2pl(2,2),k2mi(2,2),eck1pl(2,2),eck1mi(2,2),
     2        eck2pl(2,2),eck2mi(2,2),I(2,2),sigpl(4,2,2),sigmi(4,2,2) 
     3        ,pi1eck2,pi2eck2,pi1eck1,pi2eck1  
     3       ,gampl_ma(2,2),gammi_ma(2,2)
c
      dimension p1(4),p2(4),rk1(4),rk2(4),gam(4),q(4),eck1(4),eck2(4)
c
      common/iloczs1/p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam
      common/matri/qpl,qmi,gampl,gammi,k1pl,k1mi,k2pl,k2mi,eck1pl,
     1             eck1mi,eck2pl,eck2mi,I,sigpl,sigmi,gampl_ma,gammi_ma
      common/iloczs2/rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2
      common /cp1p2/p1,p2,dme,el_m2
c
      common/iloczs3/pi1eck1,pi2eck1,rk1pi1,rk1pi2
      common/iloczs4/pi1eck2,pi2eck2,rk2pi1,rk2pi2
      common/cqqa12/qqa1,qqa2
c
      rat1 = el_m2/(p1(1)+p1(4))
c
      cos1 = rk1(4) / rk1(1)
      cos2 = rk2(4) / rk2(1)
c
      rk1p1 = rk1(1) * ( rat1 + p1(4) * (1.d0 - cos1) )
      rk1p2 = rk1(1) * ( rat1 + p1(4) * (1.d0 + cos1) )
c
      rk2p1 = rk2(1) * ( rat1 + p1(4) * (1.d0 - cos2) ) 
      rk2p2 = rk2(1) * ( rat1 + p1(4) * (1.d0 + cos2) )
c
      rk1rk2 = rk1(1)*rk2(1) - rk1(2)*rk2(2) - rk1(3)*rk2(3) -
     1          rk1(4)*rk2(4)
c
      anaw1 = rk1rk2 - rk1p1 - rk2p1
      anaw2 = rk1rk2 - rk1p2 - rk2p2
c
      call plus(q,qpl)
      call minus(q,qmi)
c
      call cplus(gam,gampl)
      call cminus(gam,gammi)
c
      call plus(rk1,k1pl)
      call minus(rk1,k1mi)
c
      call plus(rk2,k2pl)
      call minus(rk2,k2mi)
c     
c     scalar products multiplied by 2, not reflected in their names !
c
      p1gam=2.d0*(p1(1)*gam(1)-p1(2)*gam(2)-p1(3)*gam(3)-
     1            p1(4)*gam(4))
      p2gam=2.d0*(p2(1)*gam(1)-p2(2)*gam(2)-p2(3)*gam(3)-
     1            p2(4)*gam(4))      
c
      rk1pi1 = rk1(1)*momenta(6,0)      
      rk1pi2 = rk1(1)*momenta(7,0)
      do i1 =1,3
       rk1pi1 = rk1pi1 - rk1(i1+1)*momenta(6,i1)
       rk1pi2 = rk1pi2 - rk1(i1+1)*momenta(7,i1)
      enddo     

      rk2pi1 = rk2(1)*momenta(6,0)      
      rk2pi2 = rk2(1)*momenta(7,0)
      do i1 =1,3
       rk2pi1 = rk2pi1 - rk2(i1+1)*momenta(6,i1)
       rk2pi2 = rk2pi2 - rk2(i1+1)*momenta(7,i1)
      enddo     
c
      if(fsrnlo.eq.1) call qqa1qqa2(rk1,rk2)

      return
      end
c *************************************************************************
c     matrices and scalar products; mi=minus, pl=plus,
c     eck1=epsilon*(k1) etc.
c
      subroutine skalar2(rk1,rk2,gam,q,eck1,eck2,qq)
      include 'phokhara_6.0.inc' 
      double precision qq
      real*8 dme,el_m2,p1,p2,q,rk1,rk2
      real*8 rk2pi1,rk2pi2,rk1pi1,rk1pi2,qqa1,qqa2
      integer i1
      complex*16 gam,eck1,eck2,p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam
      complex*16 qpl(2,2),qmi(2,2),gampl(2,2),gammi(2,2),k1pl(2,2),
     1          k1mi(2,2),k2pl(2,2),k2mi(2,2),eck1pl(2,2),eck1mi(2,2),
     2        eck2pl(2,2),eck2mi(2,2),I(2,2),sigpl(4,2,2),sigmi(4,2,2) 
     3       ,gampl_ma(2,2),gammi_ma(2,2)
      complex*16 pi1eck2,pi2eck2,pi1eck1,pi2eck1,gam1pimi(2,2),
     1           gam1pipl(2,2),gam2pimi(2,2),gam2pipl(2,2)

      dimension p1(4),p2(4),rk1(4),rk2(4),gam(4),q(4),eck1(4),eck2(4)
c
      common/iloczs1/p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam
      common/matri/qpl,qmi,gampl,gammi,k1pl,k1mi,k2pl,k2mi,eck1pl,
     1             eck1mi,eck2pl,eck2mi,I,sigpl,sigmi,gampl_ma,gammi_ma
      common /cp1p2/p1,p2,dme,el_m2
c
      common/iloczs3/pi1eck1,pi2eck1,rk1pi1,rk1pi2
      common/iloczs4/pi1eck2,pi2eck2,rk2pi1,rk2pi2
      common/cqqa12/qqa1,qqa2
c
      call cplus(eck1,eck1pl)
      call cminus(eck1,eck1mi)
c
      call cplus(eck2,eck2pl)
      call cminus(eck2,eck2mi)
c     
c     scalar products multiplied by 2, not reflected in their names !
c
      p1eck1=2.d0*(p1(1)*eck1(1)-p1(2)*eck1(2)-p1(3)*eck1(3)-
     1            p1(4)*eck1(4))
      p1eck2=2.d0*(p1(1)*eck2(1)-p1(2)*eck2(2)-p1(3)*eck2(3)-
     1            p1(4)*eck2(4))
      p2eck1=2.d0*(p2(1)*eck1(1)-p2(2)*eck1(2)-p2(3)*eck1(3)-
     1            p2(4)*eck1(4))
      p2eck2=2.d0*(p2(1)*eck2(1)-p2(2)*eck2(2)-p2(3)*eck2(3)-
     1            p2(4)*eck2(4))
c
      pi1eck1 = momenta(6,0)*eck1(1)      
      pi2eck1 = momenta(7,0)*eck1(1)      
      do i1 =1,3
       pi1eck1 = pi1eck1 - momenta(6,i1)*eck1(i1+1)
       pi2eck1 = pi2eck1 - momenta(7,i1)*eck1(i1+1)
      enddo

      pi1eck2 = momenta(6,0)*eck2(1)      
      pi2eck2 = momenta(7,0)*eck2(1)      
      do i1 =1,3
       pi1eck2 = pi1eck2 - momenta(6,i1)*eck2(i1+1)
       pi2eck2 = pi2eck2 - momenta(7,i1)*eck2(i1+1)
      enddo

      if((fsrnlo.eq.1).and.((pion.eq.1).or.(pion.eq.6))) 
     1                            call picurr(rk1,rk2,eck1,eck2,qq)
      
      return
      end
c ************************************************************************
      subroutine qqa1qqa2(rk1,rk2)

      include 'phokhara_6.0.inc'       
      double precision rk1(4),rk2(4)
      real*8 qqa1,qqa2,prad1(4),prad2(4)
      integer i1,i2
      common/cqqa12/qqa1,qqa2

      do i1=1,4
       prad1(i1) = momenta(6,i1-1)+momenta(7,i1-1)+rk1(i1)
       prad2(i1) = momenta(6,i1-1)+momenta(7,i1-1)+rk2(i1)
      enddo
     
      qqa1 = prad1(1)**2
      qqa2 = prad2(1)**2
      do i1=1,3
       qqa1 = qqa1 - prad1(i1+1)**2
       qqa2 = qqa2 - prad2(i1+1)**2
      enddo

      return
      end
c ************************************************************************
      subroutine picurr(rk1,rk2,eck1,eck2,qq)
      include 'phokhara_6.0.inc'       
      double precision rk1(4),rk2(4),qq
      complex*16 eck1(4),eck2(4),pi1eck2,pi2eck2,pi1eck1,pi2eck1
      complex*16 gam1pi(4),gam2pi(4)
      complex*16 gam1pimi(2,2),gam1pipl(2,2),gam2pimi(2,2),gam2pipl(2,2)
      complex*16 f1,f2,PionFormFactor,KaonFormFactor,ii,
     1           Fun_phi1,Fun_phi2,F_phi_KK,phas1,phas2,F_phi_no,
     2           BW_om,cvac_qqa1,cvac_qqa2,dggvap,F_phi_exp
      real*8 rk2pi1,rk2pi2,rk1pi1,rk1pi2,qqa1,qqa2,prad1(4),prad2(4),
     1       aa_phi,mm_ph,gg_ph,phas_rho_f0_exp,mm_f0_exp,c_f0_KK_exp,
     1       c_f0_pipi_exp,ff_phi_exp,c_phi_KK,
     2       rho_phi_exp,lamb_phi_exp,phas_rho_f0

      integer i1,i2
c
      common/iloczs3/pi1eck1,pi2eck1,rk1pi1,rk1pi2
      common/iloczs4/pi1eck2,pi2eck2,rk2pi1,rk2pi2
      common/matri3/gam1pimi,gam1pipl,gam2pimi,gam2pipl
      common/phases_f0/phas1,phas2
      common/cqqa12/qqa1,qqa2
      common/param_PFF/aa_phi,mm_ph,gg_ph
      common/param_f0_exp/mm_f0_exp,phas_rho_f0_exp,c_f0_KK_exp,
     1      c_f0_pipi_exp,ff_phi_exp,c_phi_KK,rho_phi_exp,lamb_phi_exp

c --- pi+ pi- ---
      if(pion.eq.1)then

      if(ivac.eq.0)then
        cvac_qqa1 = dcmplx(1.d0,0.d0) 
        cvac_qqa2 = dcmplx(1.d0,0.d0)
      else
        cvac_qqa1 = 1.d0/(1.d0-dggvap(qqa1,0.d0))
        cvac_qqa2 = 1.d0/(1.d0-dggvap(qqa2,0.d0))
      endif

      f1 = PionFormFactor(qqa1)
c ---- f0 + f0(600)
      if(rk1(1).ge.gmin) then
        if(f0_model.eq.0)then
           Fun_phi1 = F_phi_KK(qq,qqa1)
           phas_rho_f0 = 75.d0*dSqrt(qq-4.d0*mpi**2)
           phas1 = exp(dcmplx(0.d0,phas_rho_f0*pi/180.d0))
        elseif(f0_model.eq.1)then
           Fun_phi1 = F_phi_no(qq,qqa1)
        elseif(f0_model.eq.2)then
           Fun_phi1 = (0.d0,0.d0)
        elseif(f0_model.eq.3)then
           Fun_phi1 = - F_phi_exp(qq,qqa1)    
           phas1 = exp(dcmplx(0.d0,
     1           phas_rho_f0_exp*dSqrt(1.d0-4.d0*mpi**2/qq)*pi/180.d0))
        endif
      else
         Fun_phi1 = (0.d0,0.d0)
      endif

         do i1=1,4
         gam1pi(i1) = 
     1   ( (momenta(6,i1-1)+rk1(i1)-momenta(7,i1-1))*pi1eck1/rk1pi1
     2   + (momenta(7,i1-1)+rk1(i1)-momenta(6,i1-1))*pi2eck1/rk1pi2
     3    - 2.d0*eck1(i1) )*f1 
     5   * ( cvac_qqa1 - aa_phi*BW_om(mm_ph,gg_ph,qqa1,1) )
     4   + phas1 * Fun_phi1 * 
     6      ( (rk1pi1+rk1pi2)*eck1(i1) - (pi1eck1+pi2eck1)*rk1(i1) )
     7   * cvac_qqa1
         enddo

         f2 = PionFormFactor(qqa2)
c ---- f0 + f0(600)
      if(rk2(1).ge.gmin) then
        if(f0_model.eq.0)then
           Fun_phi2 = F_phi_KK(qq,qqa2)
           phas_rho_f0 = 75.d0*dSqrt(qq-4.d0*mpi**2)
           phas1 = exp(dcmplx(0.d0,phas_rho_f0*pi/180.d0))
        elseif(f0_model.eq.1)then
           Fun_phi2 = F_phi_no(qq,qqa2)
        elseif(f0_model.eq.2)then
           Fun_phi2 = (0.d0,0.d0)
        elseif(f0_model.eq.3)then
           Fun_phi2 = - F_phi_exp(qq,qqa2)    
           phas1 = exp(dcmplx(0.d0,
     1           phas_rho_f0_exp*dSqrt(1.d0-4.d0*mpi**2/qq)*pi/180.d0))
        endif
      else
        Fun_phi2 = (0.d0,0.d0)
      endif

         do i1=1,4
         gam2pi(i1) = 
     1   ( (momenta(6,i1-1)+rk2(i1)-momenta(7,i1-1))*pi1eck2/rk2pi1
     2   + (momenta(7,i1-1)+rk2(i1)-momenta(6,i1-1))*pi2eck2/rk2pi2
     3             - 2.d0*eck2(i1) )*f2
     5   * ( cvac_qqa2 - aa_phi*BW_om(mm_ph,gg_ph,qqa2,1) )
     4   + phas1 * Fun_phi2 * 
     6      ( (rk2pi1+rk2pi2)*eck2(i1) - (pi1eck2+pi2eck2)*rk2(i1) )
     7   * cvac_qqa2
         enddo

c --- K+ K- ---
      elseif(pion.eq.6) then
      f1 = KaonFormFactor(qqa1)
         do i1=1,4
         gam1pi(i1) = 
     1   ( (momenta(6,i1-1)+rk1(i1)-momenta(7,i1-1))*pi1eck1/rk1pi1
     2   + (momenta(7,i1-1)+rk1(i1)-momenta(6,i1-1))*pi2eck1/rk1pi2
     3             - 2.d0*eck1(i1) )*f1
         enddo
      f2 = KaonFormFactor(qqa2)
         do i1=1,4
         gam2pi(i1) = 
     1   ( (momenta(6,i1-1)+rk2(i1)-momenta(7,i1-1))*pi1eck2/rk2pi1
     2   + (momenta(7,i1-1)+rk2(i1)-momenta(6,i1-1))*pi2eck2/rk2pi2
     3             - 2.d0*eck2(i1) )*f2
         enddo
       endif

       call cplus(gam1pi,gam1pipl)
       call cminus(gam1pi,gam1pimi)

       call cplus(gam2pi,gam2pipl)
       call cminus(gam2pi,gam2pimi)
      return
      end
c****************************************************************************
c     multiplication of the 2x2 matrices
c
      subroutine matr(mat1,mat2,mat3)
      implicit none
      integer i,j,k
      complex*16  mat1(2,2),mat2(2,2),mat3(2,2)
c
      do i=1,2
         do j=1,2
            mat3(i,j)=(0.d0,0.d0)
         enddo
      enddo
c   
      do i=1,2
         do j=1,2
            do k=1,2
               mat3(i,j)=mat3(i,j)+mat1(i,k)*mat2(k,j)
            enddo
         enddo
      enddo
c
      end
c****************************************************************************
c     multiplication of the 4x2x2 and 2x2 matrices with the (4)index fixed
c     mu - is this index; the result is 2x2 matrix
c
      subroutine matr1(mu,mat1,mat2,mat3)
      implicit none
      complex*16  mat1(4,2,2),mat2(2,2),mat3(2,2)
      integer i,j,k,mu
c
      do i=1,2
         do j=1,2
            mat3(i,j)=(0.d0,0.d0)
         enddo
      enddo
c   
      do i=1,2
         do j=1,2
            do k=1,2
               mat3(i,j)=mat3(i,j)+mat1(mu,i,k)*mat2(k,j)
            enddo
         enddo
      enddo
c
      end
c****************************************************************************
c     multiplication of the 2x2 and 4x2x2 matrices with the (4)index fixed
c     mu - is this index; the result is 2x2 matrix
c
      subroutine matr2(mu,mat1,mat2,mat3)
      implicit none
      complex*16  mat1(2,2),mat2(4,2,2),mat3(2,2)
      integer i,j,k,mu
c
      do i=1,2
         do j=1,2
            mat3(i,j)=(0.d0,0.d0)
         enddo
      enddo
c   
      do i=1,2
         do j=1,2
            do k=1,2
               mat3(i,j)=mat3(i,j)+mat1(i,k)*mat2(mu,k,j)
            enddo
         enddo
      enddo
c
      end
c****************************************************************************
c     multiplication of a 2x2 matrix by a constant
c
      subroutine conmat(alfa,mat,amat)
      implicit none
      integer i,j
      complex*16 alfa
      complex*16 mat(2,2),amat(2,2)
c
      do i=1,2
         do j=1,2
            amat(i,j)=alfa*mat(i,j)
         enddo
      enddo
c
      end
c****************************************************************************
c     2x2 matrix subtraction
c
      subroutine minmat(mat1,mat2,mat3)
      implicit none
      integer i,j
      complex*16 mat1(2,2),mat2(2,2),mat3(2,2)
c
      do i=1,2
         do j=1,2
            mat3(i,j)=mat1(i,j)-mat2(i,j)
         enddo
      enddo
c
      end
c****************************************************************************
c     2x2 matrix adding two matrices
c
      subroutine dodmat(mat1,mat2,mat3)
      implicit none
      integer i,j
      complex*16 mat1(2,2),mat2(2,2),mat3(2,2)
c
      do i=1,2
         do j=1,2
            mat3(i,j)=mat1(i,j)+mat2(i,j)
         enddo
      enddo
c
      end
c****************************************************************************
c     addind 6 matrices: with proper denominators
c
      subroutine plumat(mat1,mat2,mat3,mat4,mat5,mat6,mat7)      
      implicit none
      real*8 rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2
      integer i,j
      complex*16 mat1(2,2),mat2(2,2),mat3(2,2),mat4(2,2),mat5(2,2),
     1          mat6(2,2),mat7(2,2)
c
      common/iloczs2/rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2
c
      do i=1,2
         do j=1,2
            mat7(i,j)= -0.25d0*mat1(i,j)/rk2p1/anaw1
     1                 -0.25d0*mat2(i,j)/rk1p1/anaw1
     2                 +0.25d0*mat3(i,j)/rk1p1/rk2p2
     3                 +0.25d0*mat4(i,j)/rk2p1/rk1p2
     4                 -0.25d0*mat5(i,j)/rk2p2/anaw2
     5                 -0.25d0*mat6(i,j)/rk1p2/anaw2
         enddo
      enddo
c
      end
c****************************************************************************

      subroutine blocks(rk1,rk2)
c
      include 'phokhara_6.0.inc'       
      double precision rk1(4),rk2(4)
      complex*16 p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam
      complex*16 qpl(2,2),qmi(2,2),gampl(2,2),gammi(2,2),k1pl(2,2),
     1          k1mi(2,2),k2pl(2,2),k2mi(2,2),eck1pl(2,2),eck1mi(2,2),
     2         eck2pl(2,2),eck2mi(2,2),I(2,2),sigpl(4,2,2),sigmi(4,2,2)
     3       ,gampl_ma(2,2),gammi_ma(2,2)
      complex*16 m1(2,2),m2(2,2),m3(2,2),m4(2,2),m5(2,2),m6(2,2),
     1          n1(2,2),n2(2,2),n3(2,2),n4(2,2),n5(2,2),n6(2,2),n7(2,2),
     2          n8(2,2),n9(2,2),n10(2,2),n11(2,2),n12(2,2)
      complex*16 block1(2,2),block2(2,2),block3(2,2),block4(2,2),
     1          block5(2,2),block6(2,2),block7(2,2),block8(2,2),
     2          block9(2,2),block10(2,2),block11(2,2),block12(2,2)
      complex*16 m1amp1(2,2),mamp1a(2,2),m2amp1(2,2),mamp1b(2,2),
     1           m1amp2(2,2),mamp2a(2,2),m2amp2(2,2),mamp2b(2,2),
     2           m1amp3(2,2),mamp3a(2,2),m2amp3(2,2),mamp3b(2,2), 
     3           m1amp4(2,2),mamp4a(2,2),m2amp4(2,2),mamp4b(2,2),
     4           m1amp5(2,2),mamp5a(2,2),m2amp5(2,2),mamp5b(2,2),
     5           m1amp6(2,2),mamp6a(2,2),m2amp6(2,2),mamp6b(2,2)
      complex*16 m1amp7pi1(2,2),m2amp7pi1(2,2),m1amp8pi1(2,2),
     1           m2amp8pi1(2,2),m1amp7pi2(2,2),m2amp7pi2(2,2),
     2           m1amp8pi2(2,2),m2amp8pi2(2,2)
      complex*16 gam1pimi(2,2),gam1pipl(2,2),gam2pimi(2,2),gam2pipl(2,2)
      complex*16 mapi1(2,2),mbpi1(2,2),mapi2(2,2),mbpi2(2,2)
      complex*16 ma(2,2),mb(2,2),ma_ma(2,2),mb_ma(2,2)
      integer i1,i2
c
      common/iloczs1/p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam
      common/matri/qpl,qmi,gampl,gammi,k1pl,k1mi,k2pl,k2mi,eck1pl,
     1             eck1mi,eck2pl,eck2mi,I,sigpl,sigmi,gampl_ma,gammi_ma
      common/matri1/ma,mb,ma_ma,mb_ma
      common/matri2/mapi1,mbpi1,mapi2,mbpi2
      common/matri3/gam1pimi,gam1pipl,gam2pimi,gam2pipl
c
c two photons ISR
c
      call conmat(p2eck1,I,m1)
      call conmat(p2eck2,I,m2)
      call conmat(p1eck1,I,m3)
      call conmat(p1eck2,I,m4)
      call conmat(p2gam,I,m5)
      call conmat(p1gam,I,m6)
c
      call matr(qpl,gammi,n1)
      call matr(qmi,gampl,n2)
      call matr(gammi,qpl,n3)
      call matr(gampl,qmi,n4)
      call matr(eck1mi,k1pl,n5)
      call matr(eck1pl,k1mi,n6)
      call matr(eck2mi,k2pl,n7)
      call matr(eck2pl,k2mi,n8)
      call matr(k2pl,eck2mi,n9)
      call matr(k2mi,eck2pl,n10)
      call matr(k1pl,eck1mi,n11)
      call matr(k1mi,eck1pl,n12)
c
      call minmat(n7,m4,block1)
      call minmat(n8,m4,block2)
      call minmat(m5,n1,block3)
      call minmat(m5,n2,block4)
      call minmat(n5,m3,block5)
      call minmat(n6,m3,block6)
      call minmat(m2,n9,block7)
      call minmat(m2,n10,block8)
      call minmat(m1,n11,block9)
      call minmat(m1,n12,block10)
      call minmat(n3,m6,block11)
      call minmat(n4,m6,block12)
c
c     m1amp1=macierz powstala w wyniku mnozenia pierwszych dwoch 
c     macierzy, z pierwszego czlony w ampl1
c     mamp1a=macierz powstala w wyniku wymnozenia wszystkich macierzy
c     w pierwszym czlonie amp1 itd.
c
c mnozenie macierzy dla amp1
      call matr(block1,eck1mi,m1amp1)
      call matr(m1amp1,block3,mamp1a)
      call matr(block2,eck1pl,m2amp1)
      call matr(m2amp1,block4,mamp1b)
c
c mnozenie macierzy dla amp2
      call matr(block5,eck2mi,m1amp2)
      call matr(m1amp2,block3,mamp2a)
      call matr(block6,eck2pl,m2amp2)
      call matr(m2amp2,block4,mamp2b)
c
c mnozenie macierzy dla amp3
      call matr(block5,gammi,m1amp3)
      call matr(m1amp3,block7,mamp3a)
      call matr(block6,gampl,m2amp3)
      call matr(m2amp3,block8,mamp3b)
c
c mnozenie macierzy dla amp4
      call matr(block1,gammi,m1amp4)
      call matr(m1amp4,block9,mamp4a)
      call matr(block2,gampl,m2amp4)
      call matr(m2amp4,block10,mamp4b)
c
c mnozenie macierzy dla amp5
      call matr(block11,eck1mi,m1amp5)
      call matr(m1amp5,block7,mamp5a)
      call matr(block12,eck1pl,m2amp5)
      call matr(m2amp5,block8,mamp5b)
c
c mnozenie macierzy dla amp6
      call matr(block11,eck2mi,m1amp6)
      call matr(m1amp6,block9,mamp6a)
      call matr(block12,eck2pl,m2amp6)
      call matr(m2amp6,block10,mamp6b)
c
c dodawanie macierzy typu a i typu b
      call plumat(mamp1a,mamp2a,mamp3a,mamp4a,mamp5a,mamp6a,ma)
      call plumat(mamp1b,mamp2b,mamp3b,mamp4b,mamp5b,mamp6b,mb)
c
c pions : the two photons 1ISR and 1FSR
c
      if((fsrnlo.eq.1).and.((pion.eq.1).or.(pion.eq.6))) then

c k1 emitted from final state
      call matr(block1,gam1pimi,m1amp7pi1)
      call matr(block2,gam1pipl,m2amp7pi1)

      call matr(gam1pimi,block7,m1amp8pi1)
      call matr(gam1pipl,block8,m2amp8pi1)
c
      call plumat1(m1amp7pi1,m1amp8pi1,mapi1)
      call plumat1(m2amp7pi1,m2amp8pi1,mbpi1)

c k2 emitted from final state
      call matr(block5,gam2pimi,m1amp7pi2)
      call matr(block6,gam2pipl,m2amp7pi2)
c
      call matr(gam2pimi,block9,m1amp8pi2)
      call matr(gam2pipl,block10,m2amp8pi2)
c
      call plumat2(m1amp7pi2,m1amp8pi2,mapi2)
      call plumat2(m2amp7pi2,m2amp8pi2,mbpi2)

      endif
c
      return
      end
c*************************************************************************

       subroutine blocks_mu(uupp1,uupp2,vv1,vv2) 
      include 'phokhara_6.0.inc'     
      real*8 rk2pi1,rk2pi2,rk1pi1,rk1pi2,qqa1,qqa2
      complex*16 mapi1(2,2),mbpi1(2,2),mapi2(2,2),mbpi2(2,2)
      complex*16 uupp1(1,2),uupp2(1,2),vv1(2,1),vv2(2,1)
      complex*16 wyn1_k1,wyn1_k2,wyn2_k1,wyn2_k2,dd_k1(4),dd_k2(4),
     1           ddpl_k1(2,2),ddpl_k2(2,2),ddmi_k1(2,2),ddmi_k2(2,2)
      complex*16 m1(2,2),m2(2,2),m3(2,2),m4(2,2),m5(2,2),m6(2,2),
     1           m7(2,2),m8(2,2),n1(2,2),n2(2,2),n3(2,2),n4(2,2),
     2           n5(2,2),n6(2,2),n7(2,2),n8(2,2)
      complex*16 block1(2,2),block2(2,2),block3(2,2),block4(2,2),
     1          block5(2,2),block6(2,2),block7(2,2),block8(2,2),
     2          block9(2,2),block10(2,2),block11(2,2),block12(2,2),
     3          block13(2,2),block14(2,2),block15(2,2),block16(2,2)
      complex*16 m1amp3(2,2),m2amp3(2,2),m1amp4(2,2),m2amp4(2,2),
     4           m1amp5(2,2),m2amp5(2,2),m1amp6(2,2),m2amp6(2,2)
      complex*16 mm1a(2,2),mm1b(2,2),mm2a(2,2),mm2b(2,2),
     1           mm3a(2,2),mm3b(2,2),mm4a(2,2),mm4b(2,2),
     2           mmb_k1(2,2),mmb_k2(2,2),mma_k1(2,2),mma_k2(2,2)
      complex*16 qpl(2,2),qmi(2,2),gampl(2,2),gammi(2,2),k1pl(2,2),
     1          k1mi(2,2),k2pl(2,2),k2mi(2,2),eck1pl(2,2),eck1mi(2,2),
     2        eck2pl(2,2),eck2mi(2,2),I(2,2),sigpl(4,2,2),sigmi(4,2,2),
     3        gampl_ma(2,2),gammi_ma(2,2)
      complex*16 p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam
      complex*16 pi1eck2,pi2eck2,pi1eck1,pi2eck1
      integer i1

      common/matri2/mapi1,mbpi1,mapi2,mbpi2
      common/cqqa12/qqa1,qqa2
      common/matri/qpl,qmi,gampl,gammi,k1pl,k1mi,k2pl,k2mi,eck1pl,
     1            eck1mi,eck2pl,eck2mi,I,sigpl,sigmi,gampl_ma,gammi_ma
      common/iloczs1/p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam
      common/iloczs3/pi1eck1,pi2eck1,rk1pi1,rk1pi2
      common/iloczs4/pi1eck2,pi2eck2,rk2pi1,rk2pi2
c
c the two photons: one ISR, one FSR (muons)
c
c k1 FSR
c
c muons + k1
       call conmat(2.d0*pi1eck1,I,m1)
       call conmat(2.d0*pi2eck1,I,m2)
       call matr(eck1mi,k1pl,n1)
       call matr(eck1pl,k1mi,n2)
       call matr(k1pl,eck1mi,n3)
       call matr(k1mi,eck1pl,n4)
       call dodmat(m1,n3,block1)
       call dodmat(m1,n4,block2)
       call dodmat(m2,n1,block3)
       call dodmat(m2,n2,block4)

      do i1=1,4
       call matr2(i1,block3,sigmi,mm1a)
       call matr2(i1,block4,sigpl,mm1b)
       call matr1(i1,sigmi,block1,mm2a)
       call matr1(i1,sigpl,block2,mm2b)
c 
       call plumat1_LO(qqa1,mm1a,mm2a,mma_k1)
       call plumat1_LO(qqa1,mm1b,mm2b,mmb_k1)
       call stal(uupp1,mma_k1,vv1,wyn1_k1)
       call stal(uupp2,mmb_k1,vv2,wyn2_k1)
       dd_k1(i1) = wyn1_k1+wyn2_k1
      enddo
c
      call cplus(dd_k1,ddpl_k1)
      call cminus(dd_k1,ddmi_k1)

c e+ e- + k2
      call conmat(p2eck2,I,m4)
      call conmat(p1eck2,I,m3)
c
      call matr(eck2mi,k2pl,n5)
      call matr(eck2pl,k2mi,n6)
      call matr(k2pl,eck2mi,n7)
      call matr(k2mi,eck2pl,n8)
c
      call minmat(n5,m3,block5)
      call minmat(n6,m3,block6)
      call minmat(m4,n7,block7)
      call minmat(m4,n8,block8)
c
      call matr(block5,ddmi_k1,m1amp3)
      call matr(block6,ddpl_k1,m2amp3)
c
      call matr(ddmi_k1,block7,m1amp4)
      call matr(ddpl_k1,block8,m2amp4)
c
c     adding matrices of the type A and B
c
      call plumatLO_2(m1amp3,m1amp4,mapi1)
      call plumatLO_2(m2amp3,m2amp4,mbpi1)

c k2 FSR
c
c muons + k2
       call conmat(2.d0*pi1eck2,I,m5)
       call conmat(2.d0*pi2eck2,I,m6)
       call dodmat(m5,n7,block9)
       call dodmat(m5,n8,block10)
       call dodmat(m6,n5,block11)
       call dodmat(m6,n6,block12)

      do i1=1,4
       call matr2(i1,block11,sigmi,mm3a)
       call matr2(i1,block12,sigpl,mm3b)
       call matr1(i1,sigmi,block9,mm4a)
       call matr1(i1,sigpl,block10,mm4b)
       call plumat1_LO_2(mm3a,mm4a,mma_k2)
       call plumat1_LO_2(mm3b,mm4b,mmb_k2)
       call stal(uupp1,mma_k2,vv1,wyn1_k2)
       call stal(uupp2,mmb_k2,vv2,wyn2_k2)
       dd_k2(i1) = wyn1_k2+wyn2_k2
      enddo
c
      call cplus(dd_k2,ddpl_k2)
      call cminus(dd_k2,ddmi_k2)

c e+ e- + k1
      call conmat(p2eck1,I,m7)
      call conmat(p1eck1,I,m8)

      call minmat(n1,m8,block13)
      call minmat(n2,m8,block14)
      call minmat(m7,n3,block15)
      call minmat(m7,n4,block16)
c
      call matr(block13,ddmi_k2,m1amp5)
      call matr(block14,ddpl_k2,m2amp5)
c
      call matr(ddmi_k2,block15,m1amp6)
      call matr(ddpl_k2,block16,m2amp6)
c
c     adding matrices of the type A and B
c
      call plumatLO(qqa2,m1amp5,m1amp6,mapi2)
      call plumatLO(qqa2,m2amp5,m2amp6,mbpi2)

      return
      end
c*****************************************************************************
c polarization vector definitions
c
      subroutine pol_vec(rk,epsk)
      implicit none
      real*8 rk(4),cth1,sth1,cphi1,sphi1
      complex*16 epsk(2,4)
      integer i
c
      cth1 = rk(4)/rk(1)
      sth1 = sqrt(1.d0-cth1**2)
c
      if(sth1.ne.0.d0)then
        cphi1 = rk(2)/sth1/rk(1)
        sphi1 = rk(3)/sth1/rk(1)
      else
        if(cth1.gt.0.d0)then
           cphi1 = 1.d0
           sphi1 = 0.d0
        else
           cphi1 = -1.d0
           sphi1 = 0.d0
        endif
      endif
c
c      do i=1,4
c        epsk(1,i)=rk(i)
c        epsk(2,i)=rk(i)
c      enddo
c
c helicity basis (the complex conjugated polarization vectors)
c
      epsk(1,1)=dcmplx(0.d0,0.d0)
      epsk(1,2)=dcmplx(cth1*cphi1,-sphi1)/dsqrt(2.D0)
      epsk(1,3)=dcmplx(cth1*sphi1,cphi1)/dsqrt(2.D0)
      epsk(1,4)=dcmplx(-sth1,0.d0)/dsqrt(2.D0)
      epsk(2,1)=dcmplx(0.d0,0.d0)
      epsk(2,2)=dcmplx(-cth1*cphi1,-sphi1)/dsqrt(2.D0)
      epsk(2,3)=dcmplx(-cth1*sphi1,cphi1)/dsqrt(2.D0)
      epsk(2,4)=dcmplx(sth1,0.d0)/dsqrt(2.D0)
c
c
c cartesian basis
c
c      epsk(1,1)=dcmplx(0.d0,0.d0)
c      epsk(1,2)=dcmplx(cth1*cphi1,0.d0)
c      epsk(1,3)=dcmplx(cth1*sphi1,0.d0)
c      epsk(1,4)=dcmplx(-sth1,0.d0)
c      epsk(2,1)=dcmplx(0.d0,0.d0)
c      epsk(2,2)=dcmplx(-sphi1,0.d0)
c      epsk(2,3)=dcmplx(cphi1,0.d0)
c      epsk(2,4)=dcmplx(0.d0,0.d0)
c
      return
      end
c**************************************************************************
c
      real*8 function amp(rk1,rk2,gam,q,qq,uupp1,uupp2,vv1,vv2)
      include 'phokhara_6.0.inc'     
      double precision qq
      real*8 rk1,rk2,p1,p2,dme,el_m2,q,ebppb,vac_qq,vac_qqa1,vac_qqa2
      real*8 qqa1,qqa2,aa_phi,mm_ph,gg_ph
      integer i,j
      complex*16 uupp1(1,2),uupp2(1,2),vv1(2,1),vv2(2,1)
      complex*16 p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam
      complex*16 epsk1(2,4),epsk2(2,4),BW_om
      complex*16 gam(4),eck1(4),eck2(4),dggvap
      complex*16 ma(2,2),mb(2,2),ma_ma(2,2),mb_ma(2,2)
      complex*16 mapi1(2,2),mbpi1(2,2),mapi2(2,2),mbpi2(2,2)
c
      dimension rk1(4),rk2(4),p1(4),p2(4),q(4)
c
      common/iloczs1/p1eck1,p1eck2,p2eck1,p2eck2,p1gam,p2gam
      common/matri1/ma,mb,ma_ma,mb_ma
      common/matri2/mapi1,mbpi1,mapi2,mbpi2
      common /cp1p2/p1,p2,dme,el_m2
      common/cqqa12/qqa1,qqa2
      common/param_PFF/aa_phi,mm_ph,gg_ph
c     
      amp = 0.d0
      call pol_vec(rk1,epsk1)
      call pol_vec(rk2,epsk2)
c
      call skalar1(rk1,rk2,gam,q)
      ebppb = p1(1)+p1(4)
c
c vacuum polarization
      if(ivac.eq.0)then
       vac_qq   = 1.d0
       vac_qqa1 = 1.d0
       vac_qqa2 = 1.d0
      else
       call qqa1qqa2(rk1,rk2)
c ************ c
        if(pion.eq.0)then
           vac_qq   = cdabs(1.d0/(1.d0-dggvap(qq,0.d0))
     1              - aa_phi * BW_om(mm_ph,gg_ph,qq,1))**2               
           vac_qqa1 =  cdabs(1.d0/(1.d0-dggvap(qqa1,0.d0))
     1              - aa_phi * BW_om(mm_ph,gg_ph,qqa1,1))**2               
           vac_qqa2 =  cdabs(1.d0/(1.d0-dggvap(qqa2,0.d0))
     1              - aa_phi * BW_om(mm_ph,gg_ph,qqa2,1))**2               
        elseif(pion.eq.1)then
           vac_qq   = cdabs(1.d0/(1.d0-dggvap(qq,0.d0))
     1              - aa_phi * BW_om(mm_ph,gg_ph,qq,1))**2               
           vac_qqa1 = 1.d0
           vac_qqa2 = 1.d0
        else
           vac_qq   = cdabs(1.d0/(1.d0-dggvap(qq,0.d0)))**2
        endif

      endif
c
      do i=1,2
         do j=1,2
                  eck1(1)=epsk1(i,1)
                  eck1(2)=epsk1(i,2)
                  eck1(3)=epsk1(i,3)
                  eck1(4)=epsk1(i,4)
c                  
                  eck2(1)=epsk2(j,1)
                  eck2(2)=epsk2(j,2)
                  eck2(3)=epsk2(j,3)
                  eck2(4)=epsk2(j,4)
c
                  call skalar2(rk1,rk2,gam,q,eck1,eck2,qq)
c pions : the two photons ISR and the two photons 1ISR and 1FSR
c muons : the two photons ISR
                  call blocks(rk1,rk2)

      amp = amp+((dme*cdabs(mb(1,1)-ma(1,1)))**2
     1         +(dme*cdabs(mb(2,2)-ma(2,2)))**2
     2         +(cdabs(-ebppb*ma(2,1)+el_m2/ebppb*mb(2,1)))**2
     3         +(cdabs(ebppb*mb(1,2)-el_m2/ebppb*ma(1,2)))**2)
     4           * vac_qq
c
c muons : the two photons 1ISR and 1FSR
      if((pion.eq.0).and.(fsrnlo.eq.1))then
        call blocks_mu(uupp1,uupp2,vv1,vv2) 
      endif
c the two photons 1ISR and 1FSR
      if(fsrnlo.eq.1) then
      amp = amp+( ((dme*cdabs(mbpi1(1,1)-mapi1(1,1)))**2
     1         +(dme*cdabs(mbpi1(2,2)-mapi1(2,2)))**2
     2         +(cdabs(-ebppb*mapi1(2,1)+el_m2/ebppb*mbpi1(2,1)))**2
     3         +(cdabs(ebppb*mbpi1(1,2)-el_m2/ebppb*mapi1(1,2)))**2)
     4          *vac_qqa1
     4         +((dme*cdabs(mbpi2(1,1)-mapi2(1,1)))**2
     1         +(dme*cdabs(mbpi2(2,2)-mapi2(2,2)))**2
     2         +(cdabs(-ebppb*mapi2(2,1)+el_m2/ebppb*mbpi2(2,1)))**2
     3         +(cdabs(ebppb*mbpi2(1,2)-el_m2/ebppb*mapi2(1,2)))**2)
     4          *vac_qqa2 )* qq**2
      endif

         enddo
      enddo
c
      return
      end
c*************************************************************************
      subroutine plus(vect,mat)
      implicit none
      double precision vect(4)
      complex*16 mat(2,2)
         mat(1,1) = vect(1)-vect(4)
         mat(1,2) = dcmplx(-vect(2),vect(3))
         mat(2,1) = dcmplx(-vect(2),-vect(3))
         mat(2,2) = vect(1)+vect(4)
      return
      end
c**************************************************************************
      subroutine minus(vect,mat)
      implicit none
      double precision vect(4)
      complex*16 mat(2,2)
         mat(1,1) = vect(1)+vect(4)
         mat(1,2) = dcmplx(vect(2),-vect(3))
         mat(2,1) = dcmplx(vect(2),vect(3))
         mat(2,2) = vect(1)-vect(4)
      return
      end   
c**************************************************************************
      subroutine cplus(vect,mat)
      implicit none
      complex*16 vect(4),mat(2,2)
         mat(1,1) = vect(1)-vect(4)
         mat(1,2) = -vect(2)+dcmplx(0.d0,1.d0)*vect(3)
         mat(2,1) = -vect(2)-dcmplx(0.d0,1.d0)*vect(3)
         mat(2,2) = vect(1)+vect(4)
      return
      end
c**************************************************************************
      subroutine cminus(vect,mat)
      implicit none
      complex*16 vect(4),mat(2,2)
         mat(1,1) = vect(1)+vect(4)
         mat(1,2) = vect(2)-dcmplx(0.d0,1.d0)*vect(3)
         mat(2,1) = vect(2)+dcmplx(0.d0,1.d0)*vect(3)
         mat(2,2) = vect(1)-vect(4)
      return
      end   
c**************************************************************************
      subroutine plumat1(mat1,mat2,mat3)
      implicit none
      complex*16 mat1(2,2),mat2(2,2),mat3(2,2)
      complex*16 gam1pimi(2,2),gam1pipl(2,2),gam2pimi(2,2)
     1 ,gam2pipl(2,2)
      real*8 qqa1,qqa2,rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2
      integer i,j
c
      common/matri3/gam1pimi,gam1pipl,gam2pimi,gam2pipl
      common/iloczs2/rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2
      common/cqqa12/qqa1,qqa2

      do i=1,2
         do j=1,2
            mat3(i,j)=  0.5d0*mat1(i,j)/rk2p1/qqa1
     1                 +0.5d0*mat2(i,j)/rk2p2/qqa1
         enddo
      enddo
c
      end
c**************************************************************************
      subroutine plumat2(mat1,mat2,mat3)
      implicit none
      complex*16 mat1(2,2),mat2(2,2),mat3(2,2)
      complex*16 gam1pimi(2,2),gam1pipl(2,2),gam2pimi(2,2)
     1           ,gam2pipl(2,2)
      real*8 qqa1,qqa2,rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2
      integer i,j
c
      common/matri3/gam1pimi,gam1pipl,gam2pimi,gam2pipl
      common/iloczs2/rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2
      common/cqqa12/qqa1,qqa2
 
      do i=1,2
         do j=1,2
            mat3(i,j)=  0.5d0*mat1(i,j)/rk1p1/qqa2
     1                 +0.5d0*mat2(i,j)/rk1p2/qqa2
         enddo
      enddo
c
      end      
c**************************************************************************
c     addind 2 matrices: for k2 initial state emission
c
      subroutine plumatLO_2(mat1,mat2,mat3)      
      implicit none
      real*8 rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2
      integer i,j
      complex*16 mat1(2,2),mat2(2,2),mat3(2,2)
c
      common/iloczs2/rk1p1,rk1p2,rk2p1,rk2p2,rk1rk2,anaw1,anaw2
c
      do i=1,2
         do j=1,2
            mat3(i,j)=  0.5d0*mat1(i,j)/rk2p1
     1                 +0.5d0*mat2(i,j)/rk2p2
         enddo
      enddo
c
      end
c**************************************************************************
c     addind 2 matrices: with proper denominators
c     for k2 photon final state emission (muons)
c
      subroutine plumat1_LO_2(mat1,mat2,mat3)
      implicit none
      complex*16 mat1(2,2),mat2(2,2),mat3(2,2),pi1eck2,pi2eck2  
      real*8 rk2pi1,rk2pi2
      integer i,j
c
      common/iloczs4/pi1eck2,pi2eck2,rk2pi1,rk2pi2
c
      do i=1,2
         do j=1,2
            mat3(i,j)=  0.5d0*mat1(i,j)/rk2pi2
     1                 -0.5d0*mat2(i,j)/rk2pi1
         enddo
      enddo
c
      end
c ========================================================================
c === PHOKHARA 6.0, (c) December 2006 ====================================
c ========================================================================
