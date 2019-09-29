// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DLList.h"

int main (void)
{
    printf("Test 1 Read inputs and print outputs from a DLList\n");
	DLList myList = getDLList (stdin);
    
    printf("List After:\n");
	putDLList (stdout, myList);
    printf("curr: %s, ", DLListCurrent(myList));
    printf("Length: %zu\n", DLListLength(myList));
	
	assert (validDLList (myList));
	freeDLList(myList);
	printf("\n");
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
	
	
	
    printf("Test 2 Delete a node in an empty list\n");
	myList = newDLList ();
	
    printf("List Before:\n");
    putDLList (stdout, myList);	
    printf("curr: %s, ", DLListCurrent(myList));
    printf("Length: %zu\n", DLListLength(myList));
    
	printf("\n");    
    printf("__FUNCTION__: Delete currentNode\n");
    DLListDelete(myList);
	printf("\n");
    
    printf("List After:\n");
	putDLList (stdout, myList);
    printf("curr: %s, ", DLListCurrent(myList));
    printf("Length: %zu\n", DLListLength(myList));
	
	assert (validDLList (myList));
	freeDLList(myList);
	printf("\n");
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");

	
	
	printf("Test 3 Add nodes empty DLList\n");
	myList = newDLList();
    
    printf("List Before:\n"); 
    putDLList (stdout, myList);
    printf("curr: %s, ", DLListCurrent(myList));
    printf("Length: %zu\n", DLListLength(myList));
    
	printf("\n");
    printf("__FUNCTION__: Inserting before currentNode\n");
    DLListBefore(myList, "Wubalubadubdub");    	
	printf("\n");
	
    printf("List After:\n");
	putDLList (stdout, myList);
    printf("curr: %s, ", DLListCurrent(myList));
	printf("Length: %zu\n", DLListLength(myList));
	
    assert(strcmp(DLListCurrent(myList),"Wubalubadubdub")==0);	
	assert (validDLList (myList));
	freeDLList (myList);
	printf("\n");
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
	
	
	
	printf("Test 4 Add nodes empty DLList\n");
	myList = newDLList();

    printf("List Before:\n"); 
    putDLList (stdout, myList);
    printf("curr: %s, ", DLListCurrent(myList));
    printf("Length: %zu\n", DLListLength(myList));

	printf("\n");    
    printf("__FUNCTION__: Inserting after currentNode\n");
    DLListAfter(myList, "Wubalubadubdub");
	printf("\n");    
    
    printf("List After:\n");
	putDLList (stdout, myList);
    printf("curr: %s, ", DLListCurrent(myList));
	printf("Length: %zu\n", DLListLength(myList));

    assert(strcmp(DLListCurrent(myList),"Wubalubadubdub")==0);		
	assert (validDLList (myList));
	freeDLList (myList);
	printf("\n");
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
	
	
	
	printf("Test 5 DeleteNodes one Node DLList\n");
	myList = newDLList();
	printf("\n");
	printf("__FUNCTION__: Inserting after currentNode\n");
	DLListAfter(myList, "Wubalubadubdub");
	printf("\n");
	
    printf("List Before:\n"); 
    putDLList (stdout, myList);
    printf("curr: %s, ", DLListCurrent(myList));
    printf("Length: %zu\n", DLListLength(myList));
    
	printf("\n");
    printf("__FUNCTION__: Delete currentNode\n");
    DLListDelete(myList);
	printf("\n");
	
    printf("List After:\n"); 
    putDLList (stdout, myList);
    printf("curr: %s, ", DLListCurrent(myList));
	printf("Length: %zu\n", DLListLength(myList));
	
	assert (validDLList (myList));
	freeDLList (myList);
	printf("\n");
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
	
	
	
	printf("Test 6 DeleteNodes one Node DLList\n");
	DLList oneNodeList = newDLList();
	printf("\n");
	printf("__FUNCTION__: Inserting before currentNode\n");
	DLListBefore(oneNodeList, "Wubalubadubdub");
	printf("\n");
	
    printf("List Before:\n"); 
    putDLList (stdout, oneNodeList);
    printf("curr: %s, ", DLListCurrent(oneNodeList));
    printf("Length: %zu\n", DLListLength(oneNodeList));

	printf("\n");    
    printf("__FUNCTION__: Delete currentNode\n");
    DLListDelete(oneNodeList);
	printf("\n");

    printf("List After:\n"); 
    putDLList (stdout, oneNodeList);
    printf("curr: %s, ", DLListCurrent(oneNodeList));
	printf("Length: %zu\n", DLListLength(oneNodeList));
	
	assert (validDLList (oneNodeList));
	freeDLList (oneNodeList);
	printf("\n");
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
	
	
	
    //one node
    printf("Test 7 Add nodes before Curr One node DLList\n");
    oneNodeList = newDLList ();
    DLListAfter(oneNodeList, "Wubalubadubdub");

    printf("List Before:\n"); 
    putDLList (stdout, oneNodeList);
    printf("curr: %s, ", DLListCurrent(oneNodeList));
    printf("Length: %zu\n", DLListLength(oneNodeList));

	printf("\n");    
    printf("__FUNCTION__: Inserting before currentNode\n");    
    DLListBefore(oneNodeList, "xd");
	printf("\n");
    
    printf("List After:\n"); 
    putDLList (stdout, oneNodeList);
    printf("curr: %s, ", DLListCurrent(oneNodeList));
    printf("Length: %zu\n", DLListLength(oneNodeList));

    assert(strcmp(DLListCurrent(oneNodeList),"xd")==0);		
	assert (validDLList (oneNodeList));
	freeDLList (oneNodeList);
	printf("\n");
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
	
	
	//one node
	printf("Test 8 Add nodes after Curr One node DLList\n");
    oneNodeList = newDLList ();
    DLListAfter(oneNodeList, "Wubalubadubdub");

    printf("List Before:\n"); 
    putDLList (stdout, oneNodeList);
    printf("curr: %s, ", DLListCurrent(oneNodeList));
    printf("Length: %zu\n", DLListLength(oneNodeList));

	printf("\n");    
    printf("__FUNCTION__: Inserting after currentNode\n");    
    DLListAfter(oneNodeList, "xd");
	printf("\n");
    
    printf("List After:\n"); 
    putDLList (stdout, oneNodeList);
    printf("curr: %s, ", DLListCurrent(oneNodeList));
    printf("Length: %zu\n", DLListLength(oneNodeList));

    assert(strcmp(DLListCurrent(oneNodeList),"xd")==0);	
	assert (validDLList (oneNodeList));
	freeDLList (oneNodeList);
	printf("\n");
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
	
	
	
	//multiple nodes
	printf("Test 9 Adding before first node Multi-nodes DLList\n");
    DLList multiNodeList = newDLList ();
    DLListAfter(multiNodeList, "How plumbuses are made");
    DLListAfter(multiNodeList, "First you take a dinglebob");
    DLListAfter(multiNodeList, "and you smooth it out");
    DLListAfter(multiNodeList, "with a bunch of shleem");    

    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
    
	printf("\n");    
    printf("__FUNCTION__: Move to the first node\n"); 
    DLListMove(multiNodeList, -4);
    printf("__FUNCTION__: Add before first Node\n");    
    DLListBefore(multiNodeList, "xd");
	printf("\n");
	    
    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
	
    assert(strcmp(DLListCurrent(multiNodeList),"xd")==0);	
	assert (validDLList (multiNodeList));
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
	
		
	
    printf("Test 10 Delete first node Multi-nodes DLList\n");
    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
    	
	printf("\n");
    printf("__FUNCTION__: Delete currentNode\n");
    DLListDelete(multiNodeList);
	printf("\n");
	 
    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
    
    assert(
        strcmp(DLListCurrent(multiNodeList),
        "How plumbuses are made")==0
    );        
    assert (validDLList (multiNodeList));   
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
	
	
	
    printf("Test 11 Adding after first node Multi-nodes DLList\n");
    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));

	printf("\n");        
    printf("__FUNCTION__: Add after first Node\n");    
    DLListAfter(multiNodeList, "xd");
	printf("\n");
    
    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
	
    assert(strcmp(DLListCurrent(multiNodeList),"xd")==0);	
	assert (validDLList (multiNodeList));
    freeDLList(multiNodeList);
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
	
	
	
	printf("Test 12 Adding after last node Multi-nodes DLList\n");
    multiNodeList = newDLList ();
    DLListAfter(multiNodeList, "How plumbuses are made");
    DLListAfter(multiNodeList, "First you take a dinglebob");
    DLListAfter(multiNodeList, "and you smooth it out");
    DLListAfter(multiNodeList, "with a bunch of shleem");    

    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));

	printf("\n");    
    printf("__FUNCTION__: Add after last Node \n");    
    DLListAfter(multiNodeList, "xd");
	printf("\n");
    
    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
    
    assert(strcmp(DLListCurrent(multiNodeList),"xd")==0);    
	assert (validDLList (multiNodeList));
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
	
	
	
	printf("Test 13 Deleting last node Multi-nodes DLList\n");
    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
    		
	printf("\n");
    printf("__FUNCTION__: Delete currentNode\n");
    DLListDelete(multiNodeList);
	printf("\n");
    
    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
	
    assert(
        strcmp(DLListCurrent(multiNodeList),
        "with a bunch of shleem")==0
    );    	
	assert (validDLList (multiNodeList));
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
	
	
	
	printf("Test 14 Inserting before last node Multi-nodes DLList\n");
    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
    
	printf("\n");
    printf("__FUNCTION__: Add Before Last Node\n");    
    DLListBefore(multiNodeList, "xd");
	printf("\n");
    
    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
    
    assert(strcmp(DLListCurrent(multiNodeList),"xd")==0);    
	assert (validDLList (multiNodeList));
    freeDLList(multiNodeList);	
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
	
	
		
	//multiple nodes
	printf("Test 15 Adding before middle node Multi-nodes DLList\n");
    multiNodeList = newDLList ();
    DLListAfter(multiNodeList, "How plumbuses are made");
    DLListAfter(multiNodeList, "First you take a dinglebob");
    DLListAfter(multiNodeList, "and you smooth it out");
    DLListAfter(multiNodeList, "with a bunch of shleem");    

    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
    
	printf("\n");
    printf("__FUNCTION__: Move to the third node\n"); 
    DLListMove(multiNodeList, -1);
    printf("__FUNCTION__: Add before third Node\n");    
    DLListBefore(multiNodeList, "xd");
	printf("\n");
    
    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
    
    assert(strcmp(DLListCurrent(multiNodeList),"xd")==0);
	assert (validDLList (multiNodeList));
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
	
		
	
    printf("Test 16 Delete a middle node Multi-nodes DLList\n");
    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
    	
	printf("\n");
    printf("__FUNCTION__: Delete currentNode\n");
    DLListDelete(multiNodeList);
	printf("\n");
	 
    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
    
    assert(
        strcmp(DLListCurrent(multiNodeList),
        "and you smooth it out")==0
    );    
    assert (validDLList (multiNodeList));   
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
	
	
	
    printf("Test 17 Adding after middle node Multi-nodes DLList\n");
    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
        
	printf("\n");
    printf("__FUNCTION__: Add after middle Node\n");    
    DLListAfter(multiNodeList, "xd");
	printf("\n");
    
    printf("List:\n");
    putDLList (stdout, multiNodeList);
    printf("curr: %s, ", DLListCurrent(multiNodeList));
    printf("Length: %zu\n", DLListLength(multiNodeList));
	
    assert(strcmp(DLListCurrent(multiNodeList),"xd")==0);	
	assert (validDLList (multiNodeList));
    freeDLList(multiNodeList);
	printf("---------TEST PASSED---------");
	printf("\n\n\n\n");
    
	return EXIT_SUCCESS;
}
