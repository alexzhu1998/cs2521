/*	
	stringSet.h ... 
	String Set interface/API
	Written by Ashesh Mahidadia, March 2016, Modified August 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


/* =====   string Set header/API ===== */

int stringValid(void const *vp);
void stringFree(void *vp);
void *stringNew(void const *vp);
int stringCompare(void const *vp1, void const *vp2);


void stringPrintNode(void const *vp);


/* =====   End string Set header/API ===== */
