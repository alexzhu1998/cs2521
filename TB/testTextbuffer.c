// testTextbuffer.c
// A stub file for you to test your textbuffer implementation.
// Note that you will NOT be submitting this - this is simply for you to
// test  your  functions as you go. We will have our own testTexbuffer.c
// for testing your submission.

////README FILE
////TO COMPILE RUN THIS LINE 
//gcc -Wall -Werror -std=c11 -O -lm -o testTextbuffer testTextbuffer.c textbuffer.c
//gcc -Wall -Werror -std=c11 -g -lm -o testTextbuffer testTextbuffer.c textbuffer.c

////TO LEAK CHECK RUN THIS LINE
//valgrind --track-origins=yes --leak-check=full ./testTextbuffer

//// this allows valgrind to check which line has memory leaks
//gcc -ggdb3 

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "textbuffer.h"

static void testNewTB(void);
static void testDumpTB(void);
static void testAddPrefixTB(void);
static void testMergeTB(void);
static void testPasteTB(void);
static void testCutTB(void);
static void testSearchTB(void);
static void freeList(Match head);
static void printList(Match head);
static void testDeleteTB (void);
static void testFormRichText (void);
static void testDiffTB (void); 
static void testUndoTB (void);

int main(void) {
	
	testNewTB();
	testDumpTB();
	testAddPrefixTB();
	testMergeTB();
	testPasteTB();
	testCutTB();
	testSearchTB();
	// testDeleteTB();
	// testFormRichText();
	// testDiffTB();
	// testUndoTB();
	// TODO: Call more test functions
	
	
	printf("All tests passed! You are awesome!\n");
}

static void printList (Match head) {
    if (head == NULL) return;
    for (Match curr = head; curr != NULL; curr = curr->next) {
        printf("Node lineNum: %d, Node colNum: %d\n",
        curr->lineNumber, curr->columnNumber);
    }   
}

static void freeList (Match head) {
    if (head == NULL) return;
    Match curr = head;
    Match prev = curr;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev);        
    }
}

static void testNewTB(void) {
	printf("-----------------------------------------\n"
	       "               newTB tests               \n"
	       "             case: 4 lines               \n"
	       "-----------------------------------------\n");
	
	// Calling dumpTB immediately after newTB, without modifying the TB
	TB tb1 = newTB("hello there,\nhow\nare\nthings\n");
	assert(linesTB(tb1) == 4);
	char *text1 = dumpTB(tb1, false); // Don't show line numbers
	assert(strcmp("hello there,\nhow\nare\nthings\n", text1) == 0);
	printf("PASSED\n");
	free(text1);
	releaseTB(tb1);
	
	printf("-----------------------------------------\n"
	       "               newTB tests               \n"
	       "             case: no line               \n"
	       "-----------------------------------------\n");
    TB tb2 = newTB("");
	assert(linesTB(tb2) == 0);
	char *text2 = dumpTB(tb2, false); 
	assert(strcmp("", text2) == 0);
	printf("PASSED\n");
	free(text2);
	releaseTB(tb2);
	
	printf("-----------------------------------------\n"
	       "               newTB tests               \n"
	       "      case: single new line character    \n"
	       "-----------------------------------------\n");
    
    TB tb3 = newTB("\n");
	assert(linesTB(tb3) == 1);
	printf("PASSED\n");
	releaseTB(tb3);
    
}

static void testDumpTB(void) {
	printf("-----------------------------------------\n"
	       "              dumpTB tests               \n"
	       "             case: 4 lines               \n"
	       "-----------------------------------------\n");
	
	TB tb1 = newTB("hello there,\nhow\nare\nthings\n");
	assert(linesTB(tb1) == 4);
	char *text1 = dumpTB(tb1, true);
	assert(strcmp(
	    "1. hello there,\n2. how\n3. are\n4. things\n", text1) == 0);
	printf("PASSED\n");
	free(text1);
	releaseTB(tb1);
	
	printf("-----------------------------------------\n"
	       "              dumpTB tests               \n"
	       "             case: no line               \n"
	       "-----------------------------------------\n");
    TB tb2 = newTB("");
	assert(linesTB(tb2) == 0);
	char *text2 = dumpTB(tb2, true); 
	assert(strcmp("", text2) == 0);
	printf("PASSED\n");
	free(text2);
	releaseTB(tb2);
	
	printf("-----------------------------------------\n"
	       "              dumpTB tests               \n"
	       "      case: single new line character    \n"
	       "-----------------------------------------\n");
    TB tb3 = newTB("\n");
	assert(linesTB(tb3) == 1);
	char *text3 = dumpTB(tb3, true); 
	assert(strcmp("1. \n", text3) == 0);
	char *text32 = dumpTB(tb3, false); 
	assert(strcmp("\n", text32) == 0);
	printf("PASSED\n");
	free(text3);
	free(text32);
	releaseTB(tb3);
	
	printf("-----------------------------------------\n"
           "             dumpTB tests                \n"
           "  case: consecutive new line characters  \n"
           "-----------------------------------------\n");
	TB tb4 = newTB("abc\n\n\n\n\ncde\n");
	assert(linesTB(tb4) == 6);
	char* text4 = dumpTB(tb4,true);
	assert(strcmp("1. abc\n2. \n3. \n4. \n5. \n6. cde\n",text4)==0);
    char* text42 = dumpTB(tb4,false);
	assert(strcmp("abc\n\n\n\n\ncde\n",text42)==0);
	printf("PASSED\n");
	free(text4);
	free(text42);
	releaseTB(tb4);
}

static void testAddPrefixTB(void) {
	printf("-----------------------------------------\n"
	       "            AddPrefix tests              \n"
	       "             case: 4 lines               \n"
	       "-----------------------------------------\n");
	
	TB tb1 = newTB("hello there,\nhow\nare\nthings\n");
	assert(linesTB(tb1) == 4);
	char *text1 = dumpTB(tb1, true);
	assert(strcmp(
	    "1. hello there,\n2. how\n3. are\n4. things\n", text1) == 0);
	printf("PASSED\n");
	free(text1);
	releaseTB(tb1);
	
	printf("-----------------------------------------\n"
	       "            AddPrefix tests              \n"
	       "             case: no line               \n"
	       "-----------------------------------------\n");
    TB tb2 = newTB("");
	assert(linesTB(tb2) == 0);
	char *text2 = dumpTB(tb2, true); 
	assert(strcmp("", text2) == 0);
	printf("PASSED\n");
	free(text2);
	releaseTB(tb2);
	
	printf("-----------------------------------------\n"
	       "            AddPrefix tests              \n"
	       "      case: single new line character    \n"
	       "-----------------------------------------\n");
    TB tb3 = newTB("\n");
	assert(linesTB(tb3) == 1);
	char *text3 = dumpTB(tb3, true); 
	assert(strcmp("1. \n", text3) == 0);
	printf("PASSED\n");
	free(text3);
	releaseTB(tb3);    
}

static void testMergeTB(void) {
	printf("-----------------------------------------\n"
	       "           testMergeTB tests             \n"
	       "      case: 4 lines TB <- 5 lines TB     \n"
	       "             pos: 3, 1, 5                \n"
	       "-----------------------------------------\n");
	
	TB tb1 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb2 = newTB("pretty good,\nhows\nthings\nfor\nyou\n");
	TB tb3 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb4 = newTB("pretty good,\nhows\nthings\nfor\nyou\n");
	TB tb5 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb6 = newTB("pretty good,\nhows\nthings\nfor\nyou\n");	
	
	mergeTB(tb1,3,tb2);
	mergeTB(tb3,1,tb4);
	mergeTB(tb5,5,tb6);
	
	char *text1 = dumpTB(tb1, false);
	char *text12 = dumpTB(tb3, false);
	char *text13 = dumpTB(tb5, false);	
	
	assert(strcmp(
        "hello there,\nhow\npretty good,\nhows\nthings\nfor\nyou\nare\nthings\n"
	    , text1) == 0);
	printf("PASSED pos 3\n");	
	
	assert(strcmp(
        "pretty good,\nhows\nthings\nfor\nyou\nhello there,\nhow\nare\nthings\n"
	    , text12) == 0);
	printf("PASSED pos 1\n");
	
	assert(strcmp(
        "hello there,\nhow\nare\nthings\npretty good,\nhows\nthings\nfor\nyou\n"
	    , text13) == 0);
	printf("PASSED pos 5\n");
	
	free(text1);
	free(text12);
	free(text13);
	
	releaseTB(tb1);
	releaseTB(tb3);
	releaseTB(tb5);
	
	printf("-----------------------------------------\n"
	       "           testMergeTB tests             \n"
	       "      case: 4 lines TB <- 1 line TB      \n"
	       "             pos: 3, 1, 5                \n"
	       "-----------------------------------------\n");
	TB tb21 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb22 = newTB("\n");
	TB tb23 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb24 = newTB("\n");
	TB tb25 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb26 = newTB("\n");
	
	mergeTB(tb21,3,tb22);
	mergeTB(tb23,1,tb24);
	mergeTB(tb25,5,tb26);
	
	char *text2 = dumpTB(tb21, false);
	char *text22 = dumpTB(tb23, false);
	char *text23 = dumpTB(tb25, false);	
	
	assert(strcmp(
        "hello there,\nhow\n\nare\nthings\n"
	    , text2) == 0);
	printf("PASSED pos 3\n");	
	
	assert(strcmp(
        "\nhello there,\nhow\nare\nthings\n"
	    , text22) == 0);
	printf("PASSED pos 1\n");
	
	assert(strcmp(
        "hello there,\nhow\nare\nthings\n\n"
	    , text23) == 0);
	printf("PASSED pos 5\n");
	
	free(text2);
	free(text22);
	free(text23);
	
	releaseTB(tb21);
	releaseTB(tb23);
	releaseTB(tb25);
		       
	printf("-----------------------------------------\n"
	       "           testMergeTB tests             \n"
	       "      case: 4 lines TB <- 0 lines TB     \n"
	       "                 pos: 1                  \n"
	       "-----------------------------------------\n");
	TB tb31 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb32 = newTB("");
	mergeTB(tb31,3,tb32);
	char *text3 = dumpTB(tb31, false);
    assert(strcmp("hello there,\nhow\nare\nthings\n", text3) == 0);
	printf("PASSED\n");
	free(text3);
	releaseTB(tb31);	       
	
	printf("-----------------------------------------\n"
	       "           testMergeTB tests             \n"
	       "      case: 1 line TB <- 5 lines TB      \n"
	       "                pos: 1, 2                \n"
	       "-----------------------------------------\n");
	TB tb41 = newTB("\n");
	TB tb42 = newTB("pretty good,\nhows\nthings\nfor\nyou\n");
	TB tb43 = newTB("\n");
	TB tb44 = newTB("pretty good,\nhows\nthings\nfor\nyou\n");	
	mergeTB(tb41,1,tb42);
	mergeTB(tb43,2,tb44);
	char *text4 = dumpTB(tb41, false);
	char *text42 = dumpTB(tb43, false);
    assert(strcmp("pretty good,\nhows\nthings\nfor\nyou\n\n", text4) == 0);
    printf("PASSED pos 1\n");
    assert(
        strcmp("\npretty good,\nhows\nthings\nfor\nyou\n", text42) == 0
    );    
    printf("PASSED pos 2\n");	
	free(text4);
	free(text42);
	releaseTB(tb41);
	releaseTB(tb43);
		       	       
	printf("-----------------------------------------\n"
	       "           testMergeTB tests             \n"
	       "      case: 0 lines TB <- 1 line TB      \n"
	       "                 pos: 1                  \n"
	       "-----------------------------------------\n");
    TB tb51 = newTB("");
	TB tb52 = newTB("\n");
	mergeTB(tb51,1,tb52);	       
    char *text5 = dumpTB(tb51, false);
    assert(strcmp("\n", text5) == 0);
    printf("PASSED\n");
	free(text5);
	releaseTB(tb51);	       
	
	printf("-----------------------------------------\n"
	       "           testMergeTB tests             \n"
	       "      case: 0 lines TB <- 0 lines TB     \n"
	       "                 pos: 1                  \n"
	       "-----------------------------------------\n");	       
    TB tb61 = newTB("");
	TB tb62 = newTB("");
	mergeTB(tb61,1,tb62);	       
    char *text6 = dumpTB(tb61, false);
    assert(strcmp("", text6) == 0);
    printf("PASSED\n");
	free(text6);
	releaseTB(tb61);       	       	
}

static void testPasteTB(void) {
	printf("-----------------------------------------\n"
	       "           testPasteTB tests             \n"
	       "      case: 4 lines TB <- 5 lines TB     \n"
	       "             pos: 3, 1, 5                \n"
	       "-----------------------------------------\n");
	
	TB tb1 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb2 = newTB("pretty good,\nhows\nthings\nfor\nyou\n");
	TB tb3 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb4 = newTB("pretty good,\nhows\nthings\nfor\nyou\n");
	TB tb5 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb6 = newTB("pretty good,\nhows\nthings\nfor\nyou\n");	
	
	pasteTB(tb1,3,tb2);
	pasteTB(tb3,1,tb4);
	pasteTB(tb5,5,tb6);
	
	char *text111 = dumpTB(tb1, false);
	char *text112 = dumpTB(tb2, false);
	char *text121 = dumpTB(tb3, false);
	char *text122 = dumpTB(tb4, false);	
	char *text131 = dumpTB(tb5, false);
	char *text132 = dumpTB(tb6, false);		
	
	assert(strcmp(
        "hello there,\nhow\npretty good,\nhows\nthings\nfor\nyou\nare\nthings\n", text111
    ) == 0);
	    
	assert(strcmp(
	    "pretty good,\nhows\nthings\nfor\nyou\n", text112
    ) == 0);	    
    
	printf("PASSED pos 3\n");	
	
	assert(strcmp(
        "pretty good,\nhows\nthings\nfor\nyou\nhello there,\nhow\nare\nthings\n", text121
    ) == 0);
    
    assert(strcmp(
        "pretty good,\nhows\nthings\nfor\nyou\n", text122
    ) == 0);
    	    
	printf("PASSED pos 1\n");
	
	assert(strcmp(
        "hello there,\nhow\nare\nthings\npretty good,\nhows\nthings\nfor\nyou\n"
	    , text131) == 0);
    assert(strcmp(
        "pretty good,\nhows\nthings\nfor\nyou\n", text132
    ) == 0);	    
	printf("PASSED pos 5\n");
	
	free(text111);
	free(text121);
	free(text131);
	free(text112);
	free(text122);
	free(text132);	
	
	releaseTB(tb1);
	releaseTB(tb2);
	releaseTB(tb3);
	releaseTB(tb4);
	releaseTB(tb5);
	releaseTB(tb6);
	
	printf("-----------------------------------------\n"
	       "           testPasteTB tests             \n"
	       "      case: 4 lines TB <- 1 line TB      \n"
	       "             pos: 3, 1, 5                \n"
	       "-----------------------------------------\n");
	TB tb21 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb22 = newTB("\n");
	TB tb23 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb24 = newTB("\n");
	TB tb25 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb26 = newTB("\n");
	
	pasteTB(tb21,3,tb22);
	pasteTB(tb23,1,tb24);
	pasteTB(tb25,5,tb26);
	
	char *text211 = dumpTB(tb21, false);
	char *text212 = dumpTB(tb22, false);
	char *text221 = dumpTB(tb23, false);
	char *text222 = dumpTB(tb24, false);
	char *text231 = dumpTB(tb25, false);	
	char *text232 = dumpTB(tb26, false);	
	
	assert(strcmp("hello there,\nhow\n\nare\nthings\n", text211) == 0);
	assert(strcmp("\n", text212) == 0);	
	printf("PASSED pos 3\n");	
	
	assert(strcmp(
        "\nhello there,\nhow\nare\nthings\n"
	    , text221) == 0);
	assert(strcmp("\n", text222) == 0);		    
	printf("PASSED pos 1\n");
	
	assert(strcmp(
        "hello there,\nhow\nare\nthings\n\n"
	    , text231) == 0);
	assert(strcmp("\n", text232) == 0);		    
	printf("PASSED pos 5\n");
	
	free(text211);
	free(text212);
	free(text221);	
	free(text222);	
	free(text231);
	free(text232);	
	
	releaseTB(tb21);
	releaseTB(tb22);	
	releaseTB(tb23);
	releaseTB(tb24);	
	releaseTB(tb25);
	releaseTB(tb26);	
		       
	printf("-----------------------------------------\n"
	       "           testPasteTB tests             \n"
	       "      case: 4 lines TB <- 0 lines TB     \n"
	       "                 pos: 1                  \n"
	       "-----------------------------------------\n");
	TB tb31 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb32 = newTB("");
	pasteTB(tb31,3,tb32);
	char *text3 = dumpTB(tb31, false);
	char *text32 = dumpTB(tb32, false);	
    assert(strcmp("hello there,\nhow\nare\nthings\n", text3) == 0);
    assert(strcmp("", text32) == 0);    
	printf("PASSED\n");
	free(text3);
	free(text32);
	releaseTB(tb31);	       
	releaseTB(tb32);	
	
	printf("-----------------------------------------\n"
	       "           testPasteTB tests             \n"
	       "      case: 1 line TB <- 5 lines TB      \n"
	       "                pos: 1, 2                \n"
	       "-----------------------------------------\n");
	TB tb41 = newTB("\n");
	TB tb42 = newTB("pretty good,\nhows\nthings\nfor\nyou\n");
	TB tb43 = newTB("\n");
	TB tb44 = newTB("pretty good,\nhows\nthings\nfor\nyou\n");	
	pasteTB(tb41,1,tb42);
	pasteTB(tb43,2,tb44);
	char *text411 = dumpTB(tb41, false);
	char *text412 = dumpTB(tb42, false);	
	char *text421 = dumpTB(tb43, false);
	char *text422 = dumpTB(tb44, false);	
    assert(strcmp("pretty good,\nhows\nthings\nfor\nyou\n\n", text411) == 0);
    assert(strcmp("pretty good,\nhows\nthings\nfor\nyou\n",text412) == 0);
    printf("PASSED pos 1\n");
    assert(
        strcmp("\npretty good,\nhows\nthings\nfor\nyou\n", text421) == 0
    );
    assert(strcmp("pretty good,\nhows\nthings\nfor\nyou\n",text422) == 0);    
    printf("PASSED pos 2\n");	
	
	free(text411);
	free(text412);
    free(text421);	
    free(text422);
        
	releaseTB(tb41);
	releaseTB(tb42);	
	releaseTB(tb43);
	releaseTB(tb44);	
		       	       
	printf("-----------------------------------------\n"
	       "           testPasteTB tests             \n"
	       "      case: 0 lines TB <- 1 line TB      \n"
	       "                 pos: 1                  \n"
	       "-----------------------------------------\n");
    TB tb51 = newTB("");
	TB tb52 = newTB("\n");
	pasteTB(tb51,1,tb52);	       
    char *text5 = dumpTB(tb51, false);
    char *text52 = dumpTB(tb52, false);    
    assert(strcmp("\n", text5) == 0);
    assert(strcmp("\n", text52) == 0);
    printf("PASSED\n");
	free(text5);
	free(text52);	
	releaseTB(tb51);	       
	releaseTB(tb52);	       
	
	printf("-----------------------------------------\n"
	       "            testPasteTB tests            \n"
	       "      case: 0 lines TB <- 0 lines TB     \n"
	       "                 pos: 1                  \n"
	       "-----------------------------------------\n");	       
    TB tb61 = newTB("");
	TB tb62 = newTB("");
	pasteTB(tb61,1,tb62);	       
    char *text6 = dumpTB(tb61, false);
    char *text62 = dumpTB(tb62, false);    
    assert(strcmp("", text6) == 0);
    assert(strcmp("", text62) == 0);
    printf("PASSED\n");
	free(text6);
	free(text62);
	releaseTB(tb61);
    releaseTB(tb62);	 
}

static void testCutTB(void){
	printf("-----------------------------------------\n"
	       "               cutTB tests               \n"
	       "    case: 4 lines TB   from: 1  to: 1    \n"
	       "-----------------------------------------\n");
	       
	TB tb11 = newTB("hello there,\nhow\nare\nthings\n");
	TB tb12 = cutTB(tb11,1,1);	       
    char *text11 = dumpTB(tb11, false);
    char *text12 = dumpTB(tb12, false);    
    assert(strcmp("how\nare\nthings\n", text11) == 0);
    assert(strcmp("hello there,\n", text12) == 0);
    printf("PASSED\n");
	free(text11);
	free(text12);
	releaseTB(tb11);
    releaseTB(tb12);
    
    printf("-----------------------------------------\n"
	       "               cutTB tests               \n"
	       "    case: 10 lines TB   from: 1  to: 5   \n"
	       "-----------------------------------------\n");
	       
	TB tb21 = newTB("a\nb\nc\nd\ne\nf\ng\nh\ni\nj\n");
	TB tb22 = cutTB(tb21,1,5);	       
    char *text21 = dumpTB(tb21, false);
    char *text22 = dumpTB(tb22, false);    
    assert(strcmp("f\ng\nh\ni\nj\n", text21) == 0);
    assert(strcmp("a\nb\nc\nd\ne\n", text22) == 0);
    printf("PASSED\n");
	free(text21);
	free(text22);
	releaseTB(tb21);
    releaseTB(tb22);
    
    printf("-----------------------------------------\n"
	       "               cutTB tests               \n"
	       "    case: 1 line TB   from: 1  to: 1     \n"
	       "-----------------------------------------\n");
	       
	TB tb31 = newTB("\n");
	TB tb32 = cutTB(tb31,1,1);	       
    char *text31 = dumpTB(tb31, false);
    char *text32 = dumpTB(tb32, false);    
    assert(strcmp("", text31) == 0);
    assert(strcmp("\n", text32) == 0);
    printf("PASSED\n");
	free(text31);
	free(text32);
	releaseTB(tb31);
    releaseTB(tb32);
    
    printf("-----------------------------------------\n"
	       "               cutTB tests               \n"
	       "    case: 10 lines TB   from: 1  to: 10  \n"
	       "-----------------------------------------\n");
	       
	TB tb41 = newTB("a\nb\nc\nd\ne\nf\ng\nh\ni\nj\n");
	TB tb42 = cutTB(tb41,1,10);	       
    char *text41 = dumpTB(tb41, false);
    char *text42 = dumpTB(tb42, false);    
    assert(strcmp("", text41) == 0);
    assert(strcmp("a\nb\nc\nd\ne\nf\ng\nh\ni\nj\n", text42) == 0);
    printf("PASSED\n");
    
	free(text41);
	free(text42);
	releaseTB(tb41);
    releaseTB(tb42);        
}

static void testSearchTB (void) {
    printf("-----------------------------------------\n"
	       "            searchTB tests               \n"
	       "     case: 10 lines TB   search: jkl     \n"
	       "-----------------------------------------\n");
	           
    TB tb1 = newTB("abc\nbcd\ncde\ndef\nefg\nfgh\nghi\nhijkl\nijk\nijkl\n");
    Match matchNode1 = searchTB(tb1, "jkl");
    printList(matchNode1);
    printf("PASSED\n");
    freeList(matchNode1);
	releaseTB(tb1);
	
    printf("-----------------------------------------\n"
	       "            searchTB tests               \n"
	       "      case: 10 lines TB   search:        \n"
	       "-----------------------------------------\n");
	           
    TB tb2 = newTB("abc\nbcd\ncde\ndef\nefg\nfgh\nghi\nhijkl\nijk\nijkl\n");
    
    Match matchNode2 = searchTB(tb2, "");
    printList(matchNode2);
    printf("PASSED\n");
    freeList(matchNode2);
	releaseTB(tb2);
	
    printf("-----------------------------------------\n"
	       "            searchTB tests               \n"
	       "      case: 0 lines TB   search:         \n"
	       "-----------------------------------------\n");
	           
    TB tb3 = newTB("");
    
    Match matchNode3 = searchTB(tb3, "hi");
    printList(matchNode3);
    printf("PASSED\n");
    freeList(matchNode3);
	releaseTB(tb3);

	printf("-----------------------------------------\n"
	       "            searchTB special tests       \n"
	       "      case: 0 lines TB   search: hihi    \n"
	       "-----------------------------------------\n");
	           
    TB tb3a = newTB("hihihihihihihi\n");
    
    Match matchNode3a = searchTB(tb3a, "hihi");
    printList(matchNode3a);
	printf("PASSED\n");
    freeList(matchNode3a);
	releaseTB(tb3a);
	
    printf("-----------------------------------------\n"
           "            searchTB tests               \n"
           "      case: 2 lines TB   search: hi      \n"
           "-----------------------------------------\n");
	           
    TB tb4 = newTB("hihihihihihi\nihihihihihi\n");
    
    Match matchNode4 = searchTB(tb4, "hi");
    printList(matchNode4);
    printf("PASSED\n");
    freeList(matchNode4);
	releaseTB(tb4);
	
    printf("-----------------------------------------\n"
           "            searchTB tests               \n"
           "      case: 2 lines TB   search: iii     \n"
           "-----------------------------------------\n");
	           
    TB tb5 = newTB("iihiihihihihiii\nihihiihiiihihi\n");
    
    Match matchNode5 = searchTB(tb5, "i");
    printList(matchNode5);
    printf("PASSED\n");
    freeList(matchNode5);
	releaseTB(tb5);			
}

static void testDeleteTB (void) {
	printf("-----------------------------------------\n"
	       "             deleteTB tests              \n"
	       "    case: 4 lines TB   from: 1  to: 1    \n"
	       "-----------------------------------------\n");
	       
	TB tb1 = newTB("hello there,\nhow\nare\nthings\n");
	deleteTB(tb1,1,1);
    char *text1 = dumpTB(tb1, false);
	assert(strcmp("how\nare\nthings\n", text1) == 0);
    printf("PASSED\n");
	free(text1);
	releaseTB(tb1);
	
	
	printf("-----------------------------------------\n"
	       "             deleteTB tests              \n"
	       "    case: 4 lines TB   from: 1  to: 4    \n"
	       "-----------------------------------------\n");
	       
	TB tb2 = newTB("hello there,\nhow\nare\nthings\n");
	deleteTB(tb2,1,4);
    char *text2 = dumpTB(tb2, false);
	assert(strcmp("", text2) == 0);
    printf("PASSED\n");
	free(text2);
	releaseTB(tb2);
	
	printf("-----------------------------------------\n"
	       "             deleteTB tests              \n"
	       "    case: 1 line TB   from: 1  to: 1    \n"
	       "-----------------------------------------\n");
	       
	TB tb3 = newTB("hello there,\n");
	deleteTB(tb3,1,1);
    char *text3 = dumpTB(tb3, false);
	assert(strcmp("", text3) == 0);
    printf("PASSED\n");
	free(text3);
	releaseTB(tb3);	
} 


static void testFormRichText (void) {
    printf("-----------------------------------------\n"
	       "          FormRichText tests             \n"
	       "           case: 4 lines TB              \n"
	       "-----------------------------------------\n");
	       
	TB tb1 = newTB("***hello**there**   ****** **x*,\n*ho*w\na*re* \nth*i*ng*s\n**\nab\n*__*\n*_*\n");
	TB tb2 = newTB("#*some* _string_\n*some* _string*_\n##\n_ _\ndsfdf**\n_so*m*e_\nsome#string*once_again*\n__* *\n");
	//
	//formRichText(tb1);
	formRichText(tb1);
	char* text1 = dumpTB(tb1,false);
	printf("%s\n", text1);
	free(text1);
	releaseTB(tb1);
	formRichText(tb2);
	char* text2 = dumpTB(tb2,false);
	printf("%s\n", text2);
	free(text2);
	releaseTB(tb2);

}


static void testDiffTB (void) {
    printf("-----------------------------------------\n"
	       "              diffTB tests               \n"
	       "            case: n lines TB             \n"
	       "-----------------------------------------\n");
	       
	TB tb1 = newTB("\n\n\n\nsdfdsf\nsdf\naafb\n");    
	
	TB tb2 = newTB("\n\na\nbc\n\n\n\n\n\n\n");
	char* text = dumpTB(tb2,true);
	free(text);
	char* diffText = diffTB(tb1,tb2); 
	printf("%s\n",diffText);
	free(diffText);
	releaseTB(tb1);  
	releaseTB(tb2);
}

static void testUndoTB (void) {
    printf("-----------------------------------------\n"
	       "              UndoTB tests               \n"
	       "            case: n lines TB             \n"
	       "-----------------------------------------\n");    
    TB tb1 = newTB("\n\n\n\nsdfdsf\nsdf\naafb\n");
    undoTB(tb1);
    releaseTB(tb1);
    
}

	/*
	
	
	// TODO: Add more tests
	
	*/

// TODO: Add more test functions here

