      subroutine phk_to_hepevt
cc      IMPLICIT REAL*8 (A-H,O-Z)
      include 'PhokaraGeneratorProd/phokhara_6.0.inc'

#include "seq/hepevt.inc"

      INTEGER NTYPE(2)
      INTEGER INDEX(40)
      REAL*8 QPHOT1(0:3),QPHOT2(0:3),PFINEL(0:3),PFINPOS(0:3)
      REAL*8 qph(40,0:3) 
      REAL*8 AMASS
      integer i,nfpart ! number of final state particles
      
C..... PARTICLE MASS AND TYPE 
      nfpart = 0

      IF ( pion .EQ. 0 ) THEN  ! mu+ mu-
         AMASS    = ME
         NTYPE(1) =  13        ! mu+ 
         NTYPE(2) = -13        ! mu-
         nfpart = 2
      ENDIF

      IF ( pion .EQ. 1 ) THEN  ! pi+ pi-
         AMASS    = ME
         NTYPE(1) =  211        ! pi+ 
         NTYPE(2) = -211        ! pi-
         nfpart = 2
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
         VHEP(1,I)   = 0.
         VHEP(2,I)   = 0.
         VHEP(3,I)   = 0.
         VHEP(4,I)   = 0.

         IF ( I .LE. nfpart ) THEN   ! particles type
            IDHEP(I) = NTYPE(I)
         ELSE
            IDHEP(I) = 22       ! radiative photon
         ENDIF
      
         IF ( I.EQ.1) THEN

            PHEP(1,I)   = momenta(6,1) ! px / pi+, etc.
            PHEP(2,I)   = momenta(6,2) ! py
            PHEP(3,I)   = momenta(6,3) ! pz
            PHEP(4,I)   = momenta(6,0) ! E
            PHEP(5,I)   = AMASS     ! mass
         
         ELSE IF ( I.EQ. 2) THEN

            PHEP(1,I)   = momenta(7,1) ! px / pi-, etc.
            PHEP(2,I)   = momenta(7,2) ! py
            PHEP(3,I)   = momenta(7,3) ! pz
            PHEP(4,I)   = momenta(7,0) ! E
            PHEP(5,I)   = AMASS      ! mass

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





