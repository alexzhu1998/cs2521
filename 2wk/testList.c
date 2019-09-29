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
    printf("curr: %s, ", DLListCurrent(myList));
    printf("Length: %zu\n", DLListLength(myList));
    DLListBefore(myList, "Hello");    	
	putDLList (stdout, myList);
    printf("curr: %s, ", DLListCurrent(myList));
	printf("Length: %zu\n", DLListLength(myList));
	assert (validDLList (myList));
	freeDLList (myList);
	
	
	
	printf("Test 3 Inserting after currentNode in empty DLList\n");
	myList = newDLList();
    printf("curr: %s, ", DLListCurrent(myList));
    printf("Length: %zu\n", DLListLength(myList));
    DLListAfter(myList, "Hello");    	
	putDLList (stdout, myList);
    printf("curr: %s, ", DLListCurrent(myList));
	printf("Length: %zu\n", DLListLength(myList));
	assert (validDLList (myList));
	freeDLList (myList);
	
    //one node
    printf("Test 4 Inserting before first Node in a one node DLList\n");
    DLList oneNodeList = newDLList ();
    printf("curr: %s, ", DLListCurrent(oneNodeList));
    printf("Length: %zu\n", DLListLength(oneNodeList));
    DLListAfter(oneNodeList, "Hello");
    printf("curr: %s, ", DLListCurrent(oneNodeList));
    printf("Length: %zu\n", DLListLength(oneNodeList));
    putDLList (stdout, oneNodeList);
	assert (validDLList (oneNodeList));
	freeDLList (oneNodeList);
    
	return EXIT_SUCCESS;
}
