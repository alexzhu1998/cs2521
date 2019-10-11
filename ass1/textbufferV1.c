#include <stdio.h>
#include <assert.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>


#include "textbuffer.h"
//valgrind --track-origins=yes --leak-check=full ./testTextbuffer
//gcc -Wall -Werror -std=c11 -O -lm -o testTextbuffer testTextbuffer.c textbuffer.c

typedef struct TBNode {
    char *value;
    struct TBNode *prev;
    struct TBNode *next;
} TBNode;

struct textbuffer {
    int totalChar;
    int nitems;
    TBNode *first;
    TBNode *curr;
    TBNode *last;
};

/*
char *strDup(const char *string) {
    if (string == NULL) return NULL;
    // Space for length plus null
    char *dest = malloc(strlen (string) + 1);
    // No memory  
    if (dest == NULL) return NULL;          
    // Copy the characters
    strcpy(dest, string);                   
    // Return the new string
    return dest;                            
}*/

/**
 * Allocate a new textbuffer whose contents is initialised with the text
 * in the given string.
 */
 
void newNodefoo (TB tb, char *text){
    
    if (text == NULL) return;
    //malloc the node
    TBNode *newNode = malloc(sizeof(*newNode));
    //malloc the array
    newNode->value = malloc(strlen(text) + 1);
    strcpy(newNode->value, text);
    newNode->prev = newNode->next = NULL;
    
    
    if (tb->first == NULL && tb->last == NULL){ 
        //printf("hi1");
        tb->first = tb->last = newNode;
    } else {
        //printf("hi2");
        tb->last->next = newNode;
        newNode->prev = tb->last;
        tb->last = newNode;
        tb->last->next = NULL;
        /*
        printf ("first = %s\n", tb->first->value);
        printf ("first->next = %s\n", tb->first->next->value);
        printf ("first->next->prev = %s\n", tb->first->next->prev->value);
        printf ("last->prev = %s\n", tb->last->prev->value);
        printf ("last->prev->next = %s\n", tb->last->prev->next->value);
        printf ("last = %s\n", tb->last->value);
        printf ("---\n");
        */
    }
    
} 
 
TB newTB (char *text) {

    struct textbuffer *new = malloc(sizeof(*new));
    if (new == NULL) err(EX_OSERR, "couldn't allocate DLList");
    new->first = new->last = NULL;
    new->totalChar = strlen(text);
//    char *ptr = strstr(text, "\n");
    int i, j;
    int prevI = 0;
    
    for (i = 0; text[i] != '\0'; i++) {
        char *temp = malloc(strlen(text)+1);
        if (text[i] == '\n'){
            for (j = 0; j < i-prevI; j++) {
                if (text[j+prevI] == '\n') prevI++;
                temp[j] = text[j+prevI];
                //temp[j+1] = '\0'; 
            }
            temp[j] = '\0';
            prevI = i;
            
            newNodefoo(new, temp);
            
        }
        free(temp);
    }
    
	return new;
}

/**
 * Free  the  memory occupied by the given textbuffer. It is an error to
 * access the buffer afterwards.
 */
void releaseTB (TB tb) {
    if (tb == NULL) return;
    
    if (tb->first == NULL && tb->last == NULL) {
        free(tb);
    } else {
        
        TBNode *curr = tb->first;
        //printf("%s", tb->first->next->next->next->value);
        
        while (curr != NULL) {
            //printf("%s", curr->value);
            if (curr->value != NULL) free(curr->value);
            TBNode *tmp = curr;
            curr = curr->next;
            free(tmp);
            
            
        }
        
        free(tb);
    }
    
    
}


/**
 * Allocate  and return a string containing all of the text in the given
 * textbuffer. If showLineNumbers is true, add a prefix corresponding to
 * the line number.
 */
char *dumpTB (TB tb, bool showLineNumbers) {
	if (tb == NULL) return NULL;
    if (tb->first == NULL && tb->last == NULL) { 
        return NULL;
    } else {
        char *textArray = malloc(tb->totalChar+1);
        textArray[0] = '\0';
	    if (showLineNumbers) {
	        printf("show line numbers");
	    } else {
	        /*
	        int textLen = 0;
            TBNode *curr = tb->first;
            while (curr != NULL) {
                for (int i = 0; i < strlen(curr->value); i++) {
                    textArray[i+textLen] = curr->value[i];
                    //printf("%c", curr->value[i]);
                    if (i+1 == strlen(curr->value)) {
                        textLen++;
                        textArray[i+textLen] = '\n';
                    }
                }
                textLen += strlen(curr->value);
                curr = curr->next;
            }
            textArray[textLen]='\0';
            */
            TBNode *curr = tb->first;
            while (curr != NULL) {
                strcat(textArray, curr->value);	
		        strcat(textArray, "\n");
		        curr = curr->next;
		    }
		    strcat(textArray, "\0");
	    }
	    //printf("Textarray is %s",textArray);
        //printf("\n");
	    return textArray;
	}
	return NULL;
	
}

/**
 * Return the number of lines of the given textbuffer.
 */
int linesTB (TB tb) {
	if (tb == NULL) return 0;
	if (tb->first == NULL && tb->last == NULL) { 
	    return 0;
    } else {
        TBNode *curr = tb->first;
        int count = 0;
        while (curr != NULL) {
            curr = curr->next;
            count++;
        }
        return count;
    }
	return 0; 
	
}

/**
 * Add a given prefix to all lines between 'from' and 'to', inclusive.
 * - The  program  should abort() wih an error message if 'from' or 'to'
 *   is out of range. The first line of a textbuffer is at position 1.
 */
void addPrefixTB (TB tb, int from, int to, char *prefix) {

}

/**
 * Merge 'tb2' into 'tb1' at line 'pos'.
 * - After this operation:
 *   - What was at line 1 of 'tb2' will now be at line 'pos' of 'tb1'.
 *   - Line  'pos' of 'tb1' will moved to line ('pos' + linesTB('tb2')),
 *     after the merged-in lines from 'tb2'.
 *   - 'tb2' can't be used anymore (as if we had used releaseTB() on it)
 * - The program should abort() with an error message if 'pos' is out of
 *   range.
 */
void mergeTB (TB tb1, int pos, TB tb2) {

}

/**
 * Copy 'tb2' into 'tb1' at line 'pos'.
 * - After this operation:
 *   - What was at line 1 of 'tb2' will now be at line 'pos' of 'tb1'.
 *   - Line  'pos' of 'tb1' will moved to line ('pos' + linesTB('tb2')),
 *     after the pasted-in lines from 'tb2'.
 *   - 'tb2' is unmodified and remains usable independent of tb1.
 * - The program should abort() with an error message if 'pos' is out of
 *   range.
 */
void pasteTB (TB tb1, int pos, TB tb2) {

}

/**
 * Cut  the lines between and including 'from' and 'to' out of the given
 * textbuffer 'tb' into a new textbuffer.
 * - The result is a new textbuffer (much as one created with newTB()).
 * - The cut lines will be deleted from 'tb'.
 * - The  program should abort() with an error message if 'from' or 'to'
 *   is out of range.
 */
TB cutTB (TB tb, int from, int to) {
	return NULL;
}

/**
 * Return  a  linked list of match nodes containing the positions of all
 * of the matches of string 'search' in 'tb'.
 * - The textbuffer 'tb' should remain unmodified.
 * - The user is responsible for freeing the returned list.
 */
Match searchTB (TB tb, char *search) {
	return NULL;
}

/**
 * Remove  the  lines between 'from' and 'to' (inclusive) from the given
 * textbuffer 'tb'.
 * - The  program should abort() with an error message if 'from' or 'to'
 *   is out of range.
 */
void deleteTB (TB tb, int from, int to) {

}

/**
 * Search  every  line of the given textbuffer for every occurrence of a
 * set of specified substitutions and alter them accordingly.
 * - Refer to the spec for details.
 */
void formRichText (TB tb) {

}

////////////////////////////////////////////////////////////////////////
// Bonus challenges

char *diffTB (TB tb1, TB tb2) {
	return NULL;
}

void undoTB (TB tb) {

}

void redoTB (TB tb) {

}

