#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "PhokaraGeneratorProd/ranlxd.h"

int rlxdinit_(int *lux,int *seed)
{     int lux1,seed1;
  lux1=*lux;seed1=*seed;
/*   printf("%d\t",lux1);
      printf("%d\n\n",seed1); */ 
  rlxd_init(lux1,seed1);
  
  return 0;
}

int ranlxdf_(double vec[],int *lvec)
{   int lvec1,k; 
   lvec1=*lvec;
   /*  printf("\n%d\n",lvec1); */
  ranlxd(vec,lvec1);
  /*   for (k=0;k<lvec1;k++) 
       { printf("%d\t",k); printf("%12.9f\n",vec[k]); } */
  
  return 0;
}

int rlxdgetf_(int *state)
{  int k;
rlxd_get(state);
/* printf("========\n");
   for (k=0;k<=rlxd_size();k++) 
   {printf("%d\t",k); printf("%d\n",state[k]);}; */
  
  return 0;
}

  int rlxdresetf_(int *state1)
{  int k;
rlxd_reset(state1);
/* printf("========\n");
   for (k=0;k<=rlxd_size();k++) 
   {printf("%d\t",k); printf("%d\n",state1[k]);}; */
  
  return 0;
}

  int rlxd_sizef_(int *n)
{ int n1;
  n1=rlxd_size();
  *n=n1;
/*   printf("n1= "); printf("%d\t",n1); */
  
  return 0;
}
