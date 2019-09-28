// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "DLList.h"

int main (void)
{
    printf("Test 1 Read inputs and print outputs from a DLList\n");
	DLList myList = getDLList (stdin);
	putDLList (stdout, myList);
	assert (validDLList (myList));
	freeDLList(myList);

	
	
	printf("Test 2 Inserting before currentNode in empty DLList\n");
	myList = newDLList();
    printf("Length: %zu\n", DLListLength(myList));
    DLListBefore(myList, "Hello");    	
	putDLList (stdout, myList);
	assert (validDLList (myList));
	freeDLList (myList);
	
    //one node
    /*
    DLList oneNodeList = newDLList ();
    
    putDLList (stdout, oneNodeList);
	assert (validDLList (oneNodeList));
	freeDLList (oneNodeList);
    */
	return EXIT_SUCCESS;
}
