// testTextbuffer.c
// A stub file for you to test your textbuffer implementation.
// Note that you will NOT be submitting this - this is simply for you to
// test  your  functions as you go. We will have our own testTexbuffer.c
// for testing your submission.

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "textbuffer.h"

static void testNewTB(void);


int main(void) {
	
	testNewTB();
	
	// TODO: Call more test functions
	
	
	printf("All tests passed! You are awesome!\n");
}

static void testNewTB(void) {
	printf("-----------------------------------------\n"
	       "               newTB tests               \n"
	       "-----------------------------------------\n");
	
	// Calling dumpTB immediately after newTB, without modifying the TB
	/*
	TB tb1 = newTB("hello there,\nhow\nare\nthings\n");
	assert(linesTB(tb1) == 4);
	char *text1 = dumpTB(tb1, false); // Don't show line numbers
	assert(strcmp("hello there,\nhow\nare\nthings\n", text1) == 0);
	free(text1);
	char *text3 = dumpTB(tb1, true);
    printf("%s\n", text3);    
	free(text3);
    addPrefixTB(tb1,2,2,"hi, ");
    char *text2 = dumpTB(tb1, false);
    printf("%s\n", text2);
    free(text2);
	releaseTB(tb1);
	*/
	
	TB tb1 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb2 = newTB("pretty good,\nhows\nthings\nfor\nyou\n");
	assert(linesTB(tb1) == 4);
	assert(linesTB(tb2) == 5);
	
	pasteTB(tb1,5,tb2);
	char *text3 = dumpTB(tb1, true);
	printf("%s\n",text3);
	free(text3);
	//assert(linesTB(tb1) == 9);
	releaseTB(tb1);
	releaseTB(tb2);
	/*
	// TODO: Add more tests
	TB tb1 = newTB("dfgfd\nfdg\nsdf\n");
	assert(linesTB(tb1) == 3);
	addPrefixTB(tb1,1,3,"");
	char *text3 = dumpTB(tb1, true);
	printf("%s",text3);
	free(text3);
	releaseTB(tb1);
	*/
	printf("newTB tests passed!\n");
}

// TODO: Add more test functions here

