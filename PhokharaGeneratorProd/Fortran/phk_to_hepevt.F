      subroutine phk_to_hepevt(xVertex, yVertex, zVertex)
cc      IMPLICIT REAL*8 (A-H,O-Z)
      include 'PhokharaGeneratorProd/phokhara_6.0.inc'
c      const FDouble&    xVertex,
c      const FDouble&    yVertex,
c      const FDouble&    zVertex,
      
      double precision xVertex,yVertex,zVertex

#include "seq/hepevt.inc"

      INTEGER NTYPE(5)
      INTEGER INDEX(40)
      REAL*8 QPHOT1(0:3),QPHOT2(0:3),PFINEL(0:3),PFINPOS(0:3)
      REAL*8 qph(40,0:3) 
      REAL*8 AMASS(5)
      integer i,nfpart ! number of final state particles
      
C..... PARTICLE MASS AND TYPE 
      nfpart = 0

      IF ( pion .EQ. 0 ) THEN  ! mu+ mu-
         NTYPE(1) =  13        ! mu+ 
         NTYPE(2) = -13        ! mu-
         AMASS(1) = MMU
         AMASS(2) = MMU
         nfpart = 2
      ELSE IF ( pion .EQ. 1 ) THEN ! pi+ pi-
         NTYPE(1) =  211        ! pi+ 
         NTYPE(2) = -211        ! pi-
         AMASS(1) = MPI
         AMASS(2) = MPI
         nfpart = 2
      ELSE IF ( pion .EQ. 2 ) THEN ! pi+ pi- pi0 pi0
         NTYPE(1) =  211        ! pi+ 
         NTYPE(2) = -211        ! pi-
         NTYPE(3) =  111        ! pi0
         NTYPE(4) =  111        ! pi0
         AMASS(1) = MPI
         AMASS(2) = MPI
         AMASS(3) = MPI0
         AMASS(4) = MPI0
         nfpart = 4
      ELSE IF ( pion .EQ. 3 ) THEN ! pi+ pi- pi+ pi-
         NTYPE(1) =  211        ! pi+ 
         NTYPE(2) = -211        ! pi-
         NTYPE(3) =  211        ! pi+ 
         NTYPE(4) = -211        ! pi-
         AMASS(1) = MPI
         AMASS(2) = MPI
         AMASS(3) = MPI
         AMASS(4) = MPI
         nfpart = 4
      ELSE IF ( pion .EQ. 4 ) THEN ! ppbar
         NTYPE(1) =  2212       ! p+
         NTYPE(2) = -2212       ! anti-p-
         AMASS(1) = MP
         AMASS(2) = MP
         nfpart = 2
      ELSE IF ( pion .EQ. 5 ) THEN ! nnbar
         NTYPE(1) =  2112       ! n0
         NTYPE(2) = -2112       ! anti-n0
         AMASS(1) = MNT
         AMASS(2) = MNT
         nfpart = 2
      ELSE IF ( pion .EQ. 6 ) THEN  ! K+ K-
         NTYPE(1) =  321        ! K+ 
         NTYPE(2) = -321        ! K-
         AMASS(1) = MKP
         AMASS(2) = MKP
         nfpart = 2
      ELSE IF ( pion .EQ. 7 ) THEN  ! K+ K-
         NTYPE(1) =  311        ! K0
         NTYPE(2) = -311        ! anti-K0
         AMASS(1) = MKN
         AMASS(2) = MKN
         nfpart = 2
      ELSE IF ( pion .EQ. 8 ) THEN  ! pi+pi-pi0
         NTYPE(1) =  211        ! pi+ 
         NTYPE(2) = -211        ! pi-
         NTYPE(3) =  111        ! pi0
         AMASS(1) = MPI
         AMASS(2) = MPI
         AMASS(3) = MPI0
         nfpart = 3
      ENDIF
      
C..... increase event number      
      NEVHEP = NEVHEP + 1

C..... Number of final particles
C      NHEP = nfpart
      NHEP = nfpart + nphoton

      
     
C start filling      
      DO I = 1, NHEP
         ISTHEP(I)   = 0
         JMOHEP(1,I) = 0
         JMOHEP(2,I) = 0
         JDAHEP(1,I) = 0
         JDAHEP(2,I) = 0
c         VHEP(1,I)   = 0.
c         VHEP(2,I)   = 0.
c         VHEP(3,I)   = 0.
         VHEP(1,I)   = xVertex
         VHEP(2,I)   = yVertex
         VHEP(3,I)   = zVertex
         VHEP(4,I)   = 0.

         IF ( I .LE. nfpart ) THEN   ! particles type
            IDHEP(I) = NTYPE(I)
         ELSE
            IDHEP(I) = 22       ! radiative photon
         ENDIF
      
         IF ( I.LE.nfpart) THEN     ! charged particles

            PHEP(1,I)   = momenta(6+(i-1),1) ! px / pi+, etc.
            PHEP(2,I)   = momenta(6+(i-1),2) ! py
            PHEP(3,I)   = momenta(6+(i-1),3) ! pz
            PHEP(4,I)   = momenta(6+(i-1),0) ! E
            PHEP(5,I)   = AMASS(i)           ! mass
         
c         ELSE IF ( I.EQ. 2) THEN

c            PHEP(1,I)   = momenta(7,1) ! px / pi-, etc.
c            PHEP(2,I)   = momenta(7,2) ! py
c            PHEP(3,I)   = momenta(7,3) ! pz
c            PHEP(4,I)   = momenta(7,0) ! E
c            PHEP(5,I)   = AMASS      ! mass

         ELSE IF ( I .EQ. nfpart+1) THEN

            PHEP(1,I)   = momenta(3,1) ! px : radiative gamma
            PHEP(2,I)   = momenta(3,2) ! py
            PHEP(3,I)   = momenta(3,3) ! pz
            PHEP(4,I)   = momenta(3,0) ! E
            PHEP(5,I)   = 0.                ! photn - mass

         ELSE IF ( I .EQ. nfpart+2) THEN

            PHEP(1,I)   = momenta(4,1) ! px : radiative gamma
            PHEP(2,I)   = momenta(4,2) ! py
            PHEP(3,I)   = momenta(4,3) ! pz
            PHEP(4,I)   = momenta(4,0) ! E
            PHEP(5,I)   = 0.                ! photn - mass

         ENDIF

c         WRITE(*,*) PHEP(1,I),PHEP(2,I),PHEP(3,I),PHEP(4,I),PHEP(5,I)
         
         ENDDO
      
      return
      end





