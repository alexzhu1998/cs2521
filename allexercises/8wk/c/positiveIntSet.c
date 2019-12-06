/* 	
	positiveIntSet.c ... 
	positiveInt Set implementation 
	Written by Ashesh Mahidadia, March 2016, Modified August 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "positiveIntSet.h" 

/* =====   positiveInt Set ===== */

int positiveIntValid(void const *vp){
  int v = * (int *) vp ;  
  // OR use local method like int v = getInt(vp);

  return ( v >= 0) ? 1 : 0 ;
}

void positiveIntFree(void *vp){
  free(vp);
}

void *positiveIntNew(void const *vp){
  int v = * (int *) vp ;   
  // OR use local method like int v = getInt(vp);

  int *ip = malloc(sizeof(int));
  *ip = v;
  return ip;
}

int positiveIntCompare(void const *vp1, void const *vp2){
  int v1 = * (int *) vp1 ;
  int v2 = * (int *) vp2 ;

  if( v1 == v2 ){ return 0; }
  if( v1 < v2 ) { return -1; }
  return 1;
}


/* =======  Loacal methods ====== */ 

int getInt(void const *vp){
  int *ip = (int *) vp ;
  return *ip;
}

void positiveIntPrintNode(void const *vp){
  int v = getInt(vp);
  printf("%d, ", v);
}


