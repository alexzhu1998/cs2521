/*
	positiveIntSet.h ... 
	positiveInt Set interface/API
	Written by Ashesh Mahidadia, March 2016, Modified August 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


/* =====   positiveInt Set interface/API ===== */

int   positiveIntValid(void const *vp);
void  positiveIntFree(void *vp);
void *positiveIntNew(void const *vp);
int   positiveIntCompare(void const *vp1, void const *vp2);

int   getInt(void const *vp);
void  positiveIntPrintNode(void const *vp);


/* =====   End positiveInt Set interface/API ===== */
