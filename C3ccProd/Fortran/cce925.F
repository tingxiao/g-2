*
* $Id: cce925.F,v 1.1 2007/03/18 13:42:14 bkh Exp $
*
* $Log: cce925.F,v $
* Revision 1.1  2007/03/18 13:42:14  bkh
* Move fortran routines from C3cc
*
* Revision 1.1  1999/07/19 15:07:02  bkh
* Gives value of cut1 internally
*
* Revision 1.1.1.1  1994/10/04 21:24:06  zfiles
* first version of ccc in CVS
*
*
*CMZ :  1.01/17 26/03/91  14.00.42  by  B. Heltsley
* fix bug from last week
*CMZ :          14/03/91  14.07.03  by  B. Heltsley
*-- Author :    B. Heltsley   14/03/91
      SUBROUTINE CCE925( ENERGY, THETA, PHI, CUT1, CUT5, CUT10 )
C.......................................................................
C.
C. CCE925 - Return E9/E25 cuts as a fcn of energy and theta
C.
C. Inputs    : ENERGY - shower energy in GeV
C.           : THETA  - shower polar angle (radians)
C.           : PHI    - shower azimuthal angle (radians)
C.
C. Outputs   : CUT1   - a  1% contour (99% of photons are higher)
C.             CUT5   - a  5% contour (95% of photons are higher)
C.             CUT10  - a 10% contour (90% of photons are higher)
C.
C. COMMON    : None
C. Banks     : None
C.
C. Calls     : None
C. Called    : User
C. Author    : B. Heltsley  14/03/91  14.00.48
C.
C. Detailed description
C.  Return parameterization.
C.......................................................................
#if defined(CLEO_TYPECHEK)
      IMPLICIT NONE
#endif
* -------------------- Argument declarations ---------------

      REAL ENERGY, THETA, PHI, CUT1, CUT5, CUT10

* -------------------- EXTERNAL declarations ---------------
* None
* -------------------- SEQUENCE declarations ---------------
* None
* -------------------- Local    declarations ---------------
      LOGICAL RCSINI
      CHARACTER*(*) CHRCSS, CHRCSR, CHRCST, CHRCSD, CHRCSA
      PARAMETER(CHRCSS='$RCSfile: cce925.F,v $')
      PARAMETER(CHRCSR='$Revision: 1.1 $')
      PARAMETER(CHRCST='$State: Exp $')
      PARAMETER(CHRCSD='$Date: 2007/03/18 13:42:14 $')
      PARAMETER(CHRCSA='$Author: bkh $')
*
      CHARACTER*(*) CRNAME
      PARAMETER(    CRNAME = 'CCE925' )

      REAL THP, E, SQRTE

      REAL        PI
      PARAMETER ( PI = 3.1415927 )
*
* -------------------- SAVE     declarations ---------------
      SAVE RCSINI
* None
* -------------------- DATA  initializations ---------------
      DATA RCSINI/.TRUE./
* None
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
      THP = MIN( THETA, PI-THETA )

      E = MAX( 0.01, ENERGY )

      IF( THP .GT. 0.6283 ) THEN

         CUT5 = 0.955*(E**0.0065) - 0.004/E
     *                           + MIN(0.1,(1.6E-8)/(E**4))

         SQRTE = SQRT( E )

         CUT1 = CUT5 - 0.018/SQRTE

         CUT10 = CUT5 + 0.006/SQRTE

      ELSE

         CUT5 = 0.86*(E**0.01) - 0.002/E

         CUT1 = CUT5 - 0.09

         CUT10 = CUT5 + 0.035

      ENDIF

      RETURN
      END
