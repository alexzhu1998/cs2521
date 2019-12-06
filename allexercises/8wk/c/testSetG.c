/* 	
	testSetG.c ... client to test Generic Set ADT
 	Written by Ashesh Mahidadia, March 2016, Modified August 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "SetG.h"
#include "positiveIntSet.h"
#include "stringSet.h" 

#define MAXARRAY 10

int main(int argc, char *argv[])
{
  
  /* =======================================
    --------- positiveInt Set (1) ----------
  */

  printf("\n%%%%%%------ positiveInt Set (1)  ------\n");

  Set s1 = SetNew(positiveIntValid, positiveIntCompare, positiveIntNew, positiveIntFree);  

  int a[MAXARRAY] = { 25, 12, 6, 82, 52 , 12, 67, 25, 8, 45};

  int i;
  for(i=0; i<MAXARRAY; i++){
     int result = SetInsert(s1 , &a[i]); 
     printf("Inserting %d: %s \n", a[i], (result==1 ? "Success" : "Failed") );
  }
 
  printf("\n\nSet values:  \n");
  SetTraverse(s1, positiveIntPrintNode);
  printf("\n------------ -------------- ---------- \n\n");




  /* =======================================
    --------- positiveInt Set (2) ----------
  */
  printf("\n%%%%%%------ positiveInt Set (2)  ------\n");
  
  Set s2 = SetNew(positiveIntValid, positiveIntCompare, positiveIntNew, positiveIntFree);  
  
  int b[MAXARRAY] = { 56, 4, 10, 69, 99, 33, 4, 33, 71, 99 };

  for(i=0; i<MAXARRAY; i++){
     int result = SetInsert(s2 , &b[i]); 
     printf("Inserting %d: %s \n", b[i], (result==1 ? "Success" : "Failed") );
  }
 
  printf("\n\nSet values:  \n");
  SetTraverse(s2, positiveIntPrintNode);
  printf("\n------------ -------------- ---------- \n\n");




  /* =======================================
     --------- String Set ----------
  */
  
  printf("\n------ stringSet  ------\n");

  Set s3 = SetNew(stringValid, stringCompare, stringNew, stringFree);  

  char *strA[MAXARRAY];
  strA[0] = strdup("john");
  strA[1] = strdup("rita");
  strA[2] = strdup("john");
  strA[3] = strdup("abby"); 
  strA[4] = strdup("rachel");
  strA[5] = strdup("luke");
 
  for(i=0; i<6; i++){
     int result = SetInsert(s3 , strA[i]); 
     printf("Inserting %s: %s \n", strA[i], (result==1 ? "Success" : "Failed") );
  }
 
  printf("\nSet values:  \n");
  SetTraverse(s3, stringPrintNode);
  printf("\n------------ -------------- ---------- \n\n");

  printf("\n------------ Delete ---------- \n");
  printf("Set values: \n");
  SetTraverse(s3, stringPrintNode);

  char *nameP = "abby";
  SetDelete(s3, nameP);

  printf("\n\nAfter deleting:  %s  \n", nameP);
  printf("\nSet values: \n");
  SetTraverse(s3, stringPrintNode);
  printf("\n------------ -------------- ---------- \n\n");

  printf("\n------------ Delete ---------- \n");
  printf("Set values: \n");
  SetTraverse(s1, positiveIntPrintNode);

  int value = 82;
  SetDelete(s1, &value);

  printf("\n\nAfter deleting:  %d  \n", value);
  printf("\nSet values: \n");
  SetTraverse(s1, positiveIntPrintNode);
  printf("\n------------ -------------- ---------- \n\n");




  return EXIT_SUCCESS;

}
