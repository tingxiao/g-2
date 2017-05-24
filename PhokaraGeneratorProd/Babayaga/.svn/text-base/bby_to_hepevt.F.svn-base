      subroutine bby_to_hepevt
      IMPLICIT REAL*8 (A-H,O-Z)
#include "seq/hepevt.inc"
      INTEGER NTYPE(2)
      INTEGER INDEX(40)
      REAL*8 QPHOT1(0:3),QPHOT2(0:3),PFINEL(0:3),PFINPOS(0:3)
      REAL*8 qph(40,0:3) 
      common/allphotons/qph
      common/allleptons/PFINEL,PFINPOS,QPHOT1,QPHOT2
      COMMON/CONST/ALPHA,CONVFAC,PI,AME,AMMU,AMPI
      COMMON/CHANNEL/ICH
      
C..... PARTICLE MASS AND TYPE 
      

      IF ( ICH .EQ. 1 ) THEN ! MuPair
         AMASS    = AME
         NTYPE(1) =  11        ! e- 
         NTYPE(2) = -11        ! e+

      ELSE IF ( ICH .EQ. 2 ) THEN ! MuPair
         AMASS    = AMMU
         NTYPE(1) =  13        ! mu- 
         NTYPE(2) = -13        ! mu+

      ELSE IF ( ICH .EQ. 3 ) THEN ! GamGam
         AMASS    =  0.
         NTYPE(1) =  22       ! gamma
         NTYPE(2) =  22       ! gamma
                           
      ELSE IF ( ICH .EQ. 4 ) THEN ! PiPair
         AMASS    = AMPI
         NTYPE(1) = -211       ! pi-
         NTYPE(2) =  211       ! pi+

      ENDIF                    ! BhaBha
*         AMASS    = AME
*         NTYPE(1) =  11        ! electron
*         NTYPE(2) = -11        ! positron
*      ENDIF

      
C..... increase event number      
      NEVHEP = NEVHEP + 1

C..... Number of final particles
      NHEP = 2

C..... get number of radiative photons
C..... PHOTON saved in qph array in this way
C..... 0  - 10  ISR from electron/mu-
C..... 11 - 20  ISR from positron/mu+
C..... 21 - 30  FSR from electron/mu-
C..... 31 - 40  FSR from positron/mu+

      DO i = 1, 40
         if ( qph(i,0) .gt. 0. ) then
            NHEP = NHEP + 1
            INDEX(NHEP-2) = i ! save the index of photon
         endif
      ENDDO
         

     
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

         IF ( I .LE. 2 ) THEN   ! particles type
            IDHEP(I) = NTYPE(I)
         ELSE
            IDHEP(I) = 22       ! radiative photon
         ENDIF
      
         IF ( I.EQ.1) THEN

            PHEP(1,I)   = PFINEL(1) ! px electron/mu-/pi-  or gamma
            PHEP(2,I)   = PFINEL(2) ! py
            PHEP(3,I)   = PFINEL(3) ! pz
            PHEP(4,I)   = PFINEL(0) ! E
            PHEP(5,I)   = AMASS     ! mass
         
         ELSE IF ( I.EQ. 2) THEN

            PHEP(1,I)   = PFINPOS(1) ! px : positron/mu+/pi+  or gamma
            PHEP(2,I)   = PFINPOS(2) ! py
            PHEP(3,I)   = PFINPOS(3) ! pz
            PHEP(4,I)   = PFINPOS(0) ! E
            PHEP(5,I)   = AMASS      ! mass

         ELSE IF ( I .GT. 2) THEN

            PHEP(1,I)   = qph(INDEX(I-2),1) ! px : radiative gamma
            PHEP(2,I)   = qph(INDEX(I-2),2) ! py
            PHEP(3,I)   = qph(INDEX(I-2),3) ! pz
            PHEP(4,I)   = qph(INDEX(I-2),0) ! E
            PHEP(5,I)   = 0.                ! photn - mass

         ENDIF
         
         ENDDO
      
      return
      end





