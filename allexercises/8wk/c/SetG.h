/* 	
	SetG.h ... interface to generic Set ADT
	Written by Ashesh Mahidadia, March 2016, Modified August 2017
*/

#ifndef SETG_H
#define SETG_H

#include <stdio.h>

typedef struct SetRep *Set;

typedef void *(*SetElmNewFp)(void const *e1);
typedef int   (*SetElmCompareFp)(void const *e1, void const *e2);
typedef void  (*SetElmFreeFp)(void *e1); 
typedef int   (*SetElmValidFp)(void const *e1);


Set SetNew( SetElmValidFp         isValidFp, 
	    SetElmCompareFp       cmpFp, 
            SetElmNewFp           newFp, 
            SetElmFreeFp          freeFp    );

// free memory used by set
void SetDrop(Set);

// make a copy of a set
Set SetCopy(Set);

// add value into set
int SetInsert(Set, void *);

// remove value from set
int SetDelete(Set, void *);

// set membership test
int SetMember(Set, void *);

// return size of the set (#elements)
int SetSize(Set);

// display set with given function
void SetTraverse(Set, void (*Fp)(void const *e1) );


#endif
