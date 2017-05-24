*
* $Id: ccblok.F,v 1.1 2007/03/18 13:42:14 bkh Exp $
*
* $Log: ccblok.F,v $
* Revision 1.1  2007/03/18 13:42:14  bkh
* Move fortran routines from C3cc
*
* Revision 1.3  2000/04/05 12:44:28  bkh
* Restore 3.5mrad offset
*
* Revision 1.2  2000/04/03 20:51:06  bkh
* Remove 3.5 mrad phi rotation.
*
* Revision 1.1  1999/06/30 18:20:08  bkh
* moved from Ccfc
*
* Revision 1.2  1999/05/19 15:04:21  bkh
* Get rid of fortran files having to do with zfiles
* Modify to use common blocks from this library not old cleo2 locations
*
* Revision 1.1  1998/07/15 21:01:26  bkh
* needed from cleo2 ccc library to avoid potential conflicts
*
* Revision 1.2  1995/09/28 21:10:47  bkh
*  fix ccblok.f bug
*
* Revision 1.1.1.1  1994/10/04  21:24:06  zfiles
* first version of ccc in CVS
*
*
*CMZ :  1.01/28 24/09/91  14.06.48  by  B. Heltsley
*-- Author :    B. Heltsley   12/03/91
      SUBROUTINE CCBLOK( THETA, PHI, THBL, PHBL )
C.......................................................................
C.
C. CCBLOK - Return theta and phi in-a-block coordinates
C.
C. Inputs    : THETA - theta
C.             PHI   - phi
C. Outputs   : THBL  - theta-in-a-block (-0.5 to +0.5)
C.             PHBL  - phi-in-a-block   (-0.5 to +0.5)
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
C.  especially for very old MC.
C.......................................................................
#if defined(CLEO_TYPECHEK)
      IMPLICIT NONE
#endif
* -------------------- Argument declarations ---------------

      REAL THETA, PHI, THBL, PHBL

* -------------------- EXTERNAL declarations ---------------
* None
* -------------------- SEQUENCE declarations ---------------
* None
* -------------------- Local    declarations ---------------
      LOGICAL RCSINI
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: ccblok.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.1 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 2007/03/18 13:42:14 $')
      PARAMETER(CHRCSA='$Author: bkh $')
*
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'CCBLOK' )

      LOGICAL LFIRST

      INTEGER ROW, KROW

      REAL THEDGE( 0:24 ), WIDTH( 24 ), THP, FBCC

      REAL        PI,             TWOPI,         WIDPHI
      PARAMETER ( PI = 3.1415927, TWOPI = 2.*PI, WIDPHI = TWOPI/128. )

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
#if WRITE_RCS_INFO
      IF(RCSINI)THEN
        RCSINI = .FALSE.
        WRITE(6,*)'-------- CVSinfo --------'
        WRITE(6,*)CHRCSS
        WRITE(6,*)CHRCSR//' '//CHRCST
        WRITE(6,*)CHRCSD//' '//CHRCSA
      ENDIF
#endif
*
      IF( LFIRST ) THEN

         LFIRST=.FALSE.

* on first call, initialize theta-width of rows

         DO 100 ROW= 1, 24

            WIDTH( ROW ) = THEDGE( ROW ) - THEDGE( ROW - 1 )

  100    CONTINUE
      ENDIF

      IF( THETA .GT. THEDGE( 0 ) .AND.
     *    THETA .LT. PI - THEDGE( 0 ) ) THEN

* legal theta: fold theta into 0 to pi/2, find row

         THP = AMIN1( THETA, PI - THETA )

         DO 200 ROW = 1, 24

            IF( THP .GT. THEDGE( ROW - 1 ) .AND.
     *          THP .LE. THEDGE( ROW ) ) THEN

               KROW = ROW
               GO TO 300
            ENDIF
  200    CONTINUE
* this should never happen
         KROW = 24

  300    CONTINUE

* we have the row, do the real work here

         THBL = ( THP - THEDGE( KROW - 1 ) )/WIDTH( KROW ) - 0.5

         IF( ABS( THBL ) .GT. 0.5 ) THBL = SIGN( 0.5, THBL )

      ELSE

* illegal theta
         THBL = 0.
      ENDIF

      PHBL = AMOD( PHI - FBCC, WIDPHI )/WIDPHI - 0.5
      IF( ABS( PHBL ) .GT. 0.5 ) PHBL = SIGN( 0.5, PHBL )

      RETURN
      END
