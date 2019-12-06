/*	
	stringSet.c ... 
 	string Set implementation 
	Written by Ashesh Mahidadia, March 2016, Modified August 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "stringSet.h" 

/* =====   string Set ===== */

int stringValid(void const *vp){
  // if required/possible, check for valid string
  return 1;
}

void stringFree(void *vp){
  free(vp);
}

void *stringNew(void const *vp){
  return strdup(vp);
}

int stringCompare(void const *vp1, void const *vp2){
  return strcmp(vp1, vp2);
}


/* =======  Additional methods ====== */ 

void stringPrintNode(void const *vp){
  char *st = (char *) vp;
  printf("%s, ", st);
}


