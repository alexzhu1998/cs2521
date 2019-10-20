#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


#include "textbuffer.h"
////README FILE
////TO COMPILE RUN THIS LINE 
//gcc -Wall -Werror -std=c11 -O -lm -o testTextbuffer testTextbuffer.c textbuffer.c
////TO LEAK CHECK RUN THIS LINE
//valgrind --track-origins=yes --leak-check=full ./testTextbuffer

//// this allows valgrind to check which line has memory leaks
//gcc -ggdb3 


typedef struct TBNode {
    char *value;
    struct TBNode *prev;
    struct TBNode *next;
} TBNode;

struct textbuffer {
    size_t totalChar; // dont forget to change this!!!
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
void errorAbort (char *text){
    printf("%s\n",text);
    abort();
}
 
void newNodefoo (TB tb, char *text){
    
    if (text == NULL) return;
    //malloc the node
    TBNode *newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) errorAbort("ERROR in newNodefoo");
    //malloc the array
    newNode->value = malloc(sizeof(char)*(strlen(text) + 1));
    if (newNode == NULL) errorAbort("ERROR in newNodefoo");
    strcpy(newNode->value, text);
    newNode->prev = newNode->next = NULL;
    
    //linking the nodes in the textbuffer
    if (tb->first == NULL && tb->last == NULL){ 
        tb->first = tb->last = newNode;
    } else {
        tb->last->next = newNode;
        newNode->prev = tb->last;
        tb->last = newNode;
    }
    
} 
 
TB newTB (char *text) {
    // allocating memory for textbuffer
    TB new = malloc(sizeof(*new));
    if (new == NULL) errorAbort("ERROR in newTB"); 
    new->first = new->last = NULL;
    new->totalChar = sizeof(char)*strlen(text);
    new->nitems = 0;
    
    //allocating memory for a writable file
    char *temp = malloc(sizeof(char)*(strlen(text)+1));
    if (temp == NULL) abort();
    strcpy(temp,text);
    
    char *res = strtok(temp, "\n"); 
    if (res == NULL) {
        new->nitems++;
        newNodefoo(new,"\n");    
    }
    while (res != NULL) {
        newNodefoo(new, res);
        res = strtok(NULL, "\n");
        new->nitems++;
    }
    
    free(temp);
    
    
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
        
        while (curr != NULL) {
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
        // separating two cases for Line Numbers 
	    if (showLineNumbers) {
	        //record exact memory required for digits and spaces
	        int i;
	        size_t totalSpaceDots = sizeof(". ")*tb->nitems;
	        size_t totalDigits = 0;
	        for (i = 1; i <= tb->nitems; i++) totalDigits += sizeof(i);
	        size_t length;
	        length = tb->totalChar+ totalSpaceDots+ totalDigits+ 1;
	        char *textArray = malloc(length);
            textArray[0] = '\0';

	        i = 1;
	        TBNode *curr = tb->first;
            while (curr != NULL) {
                //append number and dots before text
                sprintf(textArray, "%s%d. ", textArray,i);
                //concatenate from behind
                strcat(textArray, curr->value);	
		        strcat(textArray, "\n");
		        curr = curr->next;
		        i++;
		    }
		    strcat(textArray, "\0");
		    
		    return textArray;
		    
	    } else {
	    
	        char *textArray = malloc(tb->totalChar+1);
	        textArray[0] = '\0';
            TBNode *curr = tb->first;
            
            while (curr != NULL) {
                strcat(textArray, curr->value);	
		        strcat(textArray, "\n");
		        curr = curr->next;
		    }
		    strcat(textArray, "\0");
		    
		    return textArray;
	    }
	}
	return NULL;
}

/**
 * Return the number of lines of the given textbuffer.
 */
int linesTB (TB tb) {
	return tb->nitems; 
}

/**
 * Add a given prefix to all lines between 'from' and 'to', inclusive.
 * - The  program  should abort() wih an error message if 'from' or 'to'
 *   is out of range. The first line of a textbuffer is at position 1.
 */
void addPrefixTB (TB tb, int from, int to, char *prefix) {
    //if incorrect parameters, abort;
    if (to < from || to < 0 || from < 0) 
        errorAbort("ERROR in addPrefixTB");
    if (prefix == NULL) errorAbort("ERROR in addPrefixTB");
    if (prefix[0] == '\0') return;
    
    TBNode *curr = tb->first;
    char *temp = malloc(sizeof(char)*((tb->totalChar)+1));
    if (temp == NULL) errorAbort("ERROR in addPrefixTB");
    temp[0] = '\0';
    
        
    int i = 1;
    while (curr != NULL && i <= to) {
        // initiate temporary to concatenate curr->value to prefix
        if (i >= from && i <= to) {
            strcpy(temp, curr->value);
            size_t length = strlen(prefix)+strlen(curr->value)+1;
            curr->value = (char *)realloc(curr->value, length);
            sprintf(curr->value, "%s%s", prefix, temp);
            tb->totalChar += strlen(prefix);
        }
        i++;
        curr = curr->next;
    }
    free(temp);
    
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
    if (pos > tb1->nitems+1 || pos < 1) errorAbort("ERROR in mergeTB");
    if (tb1 == tb2) return;
    if (tb2->first == NULL || tb2 == NULL) return;
    
    if (tb1 == NULL) {
        tb1->first = tb2->first;
        tb1->last = tb2->last;
    } else {
        if (pos == 1) {
            // position number at the start
            tb1->first->prev = tb2->last;
            tb2->last->next = tb1->first;
            tb1->first = tb2->first;
        } else if (pos == tb1->nitems+1) {
            // position number at the end
            tb1->last->next = tb2->first;
            tb2->first->prev = tb1->last;
            tb1->last = tb2->last;  
        } else {
            // position number in the middle
            TBNode *curr1 = tb1->first;
            int i = 1;
            while (curr1 != NULL) {
                //moving curr in position
                if (i == pos) {
                    break;
                }
                i++;
                curr1 = curr1->next;
            }
            //relinking
            tb2->first->prev = curr1->prev;
            tb2->last->next = curr1;
            curr1->prev->next = tb2->first;
            curr1->prev = tb2->last;
        }
    }
    //changing tb1 nitems and totalChar
    tb1->nitems += tb2->nitems;
    tb1->totalChar += tb2->totalChar;
    
    //removing the ties of tb2
    tb2->first = NULL;
    tb2->last = NULL;
    free(tb2);
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
    if (pos > tb1->nitems+1 || pos < 1) errorAbort("ERROR in pasteTB");
    if (tb2->first == NULL || tb2 == NULL) return;
    
    char *tempText = dumpTB(tb2,false);
    TB tbTemp = newTB(tempText);
    free(tempText);
    mergeTB(tb1,pos,tbTemp);
}

/**
 * Cut the lines between and including 'from' and 'to' out of the given
 * textbuffer 'tb' into a new textbuffer.
 * - The result is a new textbuffer (much as one created with newTB()).
 * - The cut lines will be deleted from 'tb'.
 * - The  program should abort() with an error message if 'from' or 'to'
 *   is out of range.
 */
TB cutTB (TB tb, int from, int to) {
    if (to < from || to <= 0 || from <= 0 || to > tb->nitems) 
        errorAbort("ERROR in cutTB boundary");
    
    printf("%d\n", tb->nitems);
    printf("%ld\n",tb->totalChar);
    
    TBNode *curr = tb->first;
    TBNode *fromNode = NULL;
    TBNode *toNode = NULL;
    
    int i = 1;
    while (curr != NULL && i <= to) {
        if (i == from) {
            fromNode = curr;
        } 
        if (i == to || i == tb->nitems) {
            toNode = curr;
            break;
        }
        curr = curr->next;
        i++;
    }
    
    printf("tb first %s\n", tb->first->value);
    printf("tb last %s\n", tb->last->value);
    /*
    printf("i is %d\n", i);
    assert(tb->last == toNode);
    if (i == tb->nitems) {
        assert(tb->last == toNode);
    }*/
    
    TB tbNew = newTB("");
    tbNew->first = fromNode;
    tbNew->last = toNode;
    //if from is the first item 
    if (tb->first == fromNode) {
        // if to is the last item
        if (tb->last == toNode) {
            tb->first = NULL;
            tb->last = NULL;
        } else {
            tb->first = toNode->next;
            toNode->next->prev = NULL;
            toNode->next = NULL;
        }
        // if to is not the last item 
    } else {
        // if to is the last item, and from is not the last item 
        if (tb->last == toNode) {
            tb->last = fromNode->prev;
            fromNode->prev->next = NULL;
            fromNode->prev = NULL;
        } else {
            fromNode->prev->next = toNode->next;
            toNode->next->prev = fromNode->prev;
            fromNode->prev = NULL;
            toNode->next = NULL;
        }
    }
    
    int tempItems = tb->nitems;
    size_t tempChar = tb->totalChar;
    
    curr = tb->first;
    tb->nitems = 0;
    tb->totalChar = 0;
    if (curr != NULL) {
        while (curr!= NULL) {
            tb->nitems ++;
            tb->totalChar += strlen(curr->value);
            curr = curr->next;
        }
    }
    printf("tb first %s\n", tb->first->value);
    printf("tb last %s\n", tb->last->value);
    
    tbNew->nitems = tempItems - tb->nitems;
    tbNew->totalChar = tempChar - tb->totalChar;    
    
    printf("%d\n", tb->nitems);
    printf("%d\n", tbNew->nitems);
    printf("%ld\n",tb->totalChar);
    printf("%ld\n",tbNew->totalChar);
	return tbNew;
}

/**
 * Return a linked list of match nodes containing the positions of all
 * of the matches of string 'search' in 'tb'.
 * - The textbuffer 'tb' should remain unmodified.
 * - The user is responsible for freeing the returned list.
 */
Match searchTB (TB tb, char *search) {
    TBNode *curr = tb->first;
    
    while (curr != NULL) {
        if (strcmp(curr->value, search) == 0) {
            
        
        }
        curr = curr->next;
    }
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

