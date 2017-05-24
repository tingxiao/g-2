      SUBROUTINE CCPOCK( THETA, PHI, THPO, PHPO, KPOC )
C.......................................................................
C.
C. CCBLOK - Return theta and phi in-a-pocket coordinates
C.
C. Inputs    : THETA - theta
C.             PHI   - phi
C. Outputs   : THBL  - theta-in-a-pocket (-0.5 to +0.5)
C.             PHBL  - phi-in-a-pocket   (-0.5 to +0.5)
C              KPOC  - pocket number     (1=edge, 6=center)
C.
C. COMMON    : None
C. Banks     : None
C.
C. Calls     : None
C. Called    : CCGECS
C. Author    : B. Heltsley  12/03/91  16.50.52
C.
C. Detailed description
C.  Use hardwired geometry for ROAR usage; not rigorously right,
C.......................................................................
#if defined(CLEO_TYPECHEK)
      IMPLICIT NONE
#endif
* -------------------- Argument declarations ---------------

      REAL THETA, PHI, THPO, PHPO

      INTEGER KPOC

* -------------------- EXTERNAL declarations ---------------
* None
* -------------------- SEQUENCE declarations ---------------
* None
* -------------------- Local    declarations ---------------
      LOGICAL RCSINI
*      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
*
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'CCPOCK' )

      LOGICAL LFIRST

      INTEGER POC

      REAL THEDGE( 0:24 ), WIDTH( 6 ), THP, FBCC

      REAL        PI,             TWOPI,         WIDPHI
      PARAMETER ( PI = 3.1415927, TWOPI = 2.*PI, WIDPHI = TWOPI/64. )

      REAL        PI2
      PARAMETER ( PI2 = PI/2. )
*
* -------------------- SAVE     declarations ---------------
      SAVE RCSINI

      SAVE LFIRST, THEDGE, WIDTH, FBCC

* -------------------- DATA  initializations ---------------
      DATA RCSINI/.TRUE./

      DATA LFIRST / .TRUE. /, FBCC / -0.0035 /

      DATA THEDGE /
     *  0.583557, 0.618597, 0.651286, 0.684065, 0.718190, 0.753089,
     *  0.789016, 0.825934, 0.864157, 0.903017, 0.942800, 0.983449,
     *  1.025309, 1.067605, 1.110661, 1.154432, 1.199267, 1.244324,
     *  1.289933, 1.336051, 1.383047, 1.430027, 1.477343, 1.524924,
     *  PI2 /

* ----------------- Executable code starts here ------------
*
      IF( LFIRST ) THEN

         LFIRST=.FALSE.

* on first call, initialize theta-width of pockets

         DO 100 POC= 1, 6

            WIDTH( POC ) = THEDGE( 4*POC ) - THEDGE( 4*(POC-1) )

  100    CONTINUE
      ENDIF

      kpoc = 0
      thpo = 999.
      phpo = 999.

      IF( THETA .GT. THEDGE( 0 ) .AND.
     *    THETA .LT. PI - THEDGE( 0 ) ) THEN

* legal theta: fold theta into 0 to pi/2, find row

         THP = AMIN1( THETA, PI - THETA )

         DO 200 POC = 1, 6

            IF( THP .GT. THEDGE( 4*(POC-1) ) .AND.
     *          THP .LE. THEDGE( 4*POC     ) ) THEN

               KPOC = POC
               GO TO 300
            ENDIF
  200    CONTINUE
* this should never happen
         KPOC = 6

  300    CONTINUE

* we have the row, do the real work here

         THPO = ( THP - THEDGE( 4*(KPOC-1) ) )/WIDTH( KPOC ) - 0.5

         IF( ABS( THPO ) .GT. 0.5 ) THPO = SIGN( 0.5, THPO )

      ELSE

* illegal theta
         THPO = 0.
      ENDIF

      PHPO = AMOD( PHI - FBCC, WIDPHI )/WIDPHI - 0.5
      IF( ABS( PHPO ) .GT. 0.5 ) PHPO = SIGN( 0.5, PHPO )

      RETURN
      END
