#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


#include "textbuffer.h"
////README FILE
////TO COMPILE RUN THIS LINE 
//gcc -Wall -Werror -std=c11 -O -lm -o testTextbuffer testTextbuffer.c textbuffer.c
//gcc -Wall -Werror -std=c11 -g -lm -o testTextbuffer testTextbuffer.c textbuffer.c

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

void freeList (Match head) {
    if (head == NULL) return;
    Match curr = head;
    Match prev = curr;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev);        
    }
}

void printList (Match head) {
    if (head == NULL) return;
    for (Match curr = head; curr != NULL; curr = curr->next) {
        printf("Node lineNum: %d, Node colNum: %d\n",
        curr->lineNumber, curr->columnNumber);
    }   
}

void errorAbort (char *text){
    printf("%s\n",text);
    abort();
}


/** Checking for internal consistency of the TB
*/
bool validTB (TB tb) {
    if (tb == NULL) {
		errorAbort("TB is NULL\n");
		return false;
	}

	if (tb->first == NULL) {
		// list is empty; last should be null
		if (tb->last != NULL) {
			errorAbort("Non-NULL pointers in empty list\n");
			return false;
		}
	} else {
		// list is not empty; last should be non-null
		if (tb->last == NULL) {
			errorAbort("NULL pointers in non-empty list\n");
			return false;
		}
	}

	// check scanning forward through list
	size_t count = 0;
	for (TBNode *curr = tb->first; curr != NULL; curr = curr->next) {
		if (curr->prev != NULL && curr->prev->next != curr) {
		    printf("Invalid forward link into node (%s)\n",curr->value);
			errorAbort("");
			return 0;
		}

		if (curr->next != NULL && curr->next->prev != curr) {
		    printf("Invalid backward link into node (%s)\n",curr->value);
            errorAbort("");
			return 0;
		}
		count++;
	}

	if (count != tb->nitems) {
	    printf("Forward count mismatch; counted=%zu, nitems=%d\n",
			count,
			tb->nitems);
		errorAbort("");
		return false;
	}

	// check scanning backward through list
	count = 0;
	for (TBNode *curr = tb->last; curr != NULL; curr = curr->prev)
		count++;

	if (count != tb->nitems) {
	    printf("Backward count mismatch; counted=%zu, nitems=%d\n",
			count,
			tb->nitems);
		errorAbort("");
		return false;
	}
	// nothing went wrong => should be ok
	return true;
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


/**
 * Allocate a new textbuffer whose contents is initialised with the text
 * in the given string.
 */
TB newTB (char *text) {
    // allocating memory for textbuffer
    TB new = malloc(sizeof(*new));
    if (new == NULL) errorAbort("ERROR in newTB"); 
    new->first = new->last = NULL;
    new->totalChar = sizeof(char)*strlen(text);
    new->nitems = 0;
    
    if (strcmp(text,"") == 0) {
        return new; 
    }
    
    //allocating memory for a writable file
    char *temp = malloc(sizeof(char)*(strlen(text)+1));
    if (temp == NULL) abort();
    strcpy(temp,text);
    
    char *res = strtok(temp, "\n"); 
    if (res == NULL) {
        new->nitems++;
        newNodefoo(new,"");    
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
    assert(validTB(tb));
    
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
    // separating two cases for Line Numbers 
    if (showLineNumbers) {
        //record exact memory required for digits and spaces
        int i;
        size_t totalSpaceDots = sizeof(". ")*tb->nitems;
        size_t totalDigits = 0;
        for (i = 1; i <= tb->nitems; i++) totalDigits += sizeof(i);
        size_t length;
        length = tb->totalChar+ totalSpaceDots+ totalDigits+ 2;
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
        TBNode *curr = tb->first;
        // use +2 in case if \n is the only character in TB
        char *textArray = malloc(tb->totalChar+2);
        textArray[0] = '\0';
        
        if (curr != NULL){ 
            while (curr != NULL) {
                strcat(textArray, curr->value);	
                strcat(textArray, "\n");
                curr = curr->next;
            }
            strcat(textArray, "\0");
        }
        return textArray;
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
    if (tb2->first == NULL || tb2 == NULL){ 
        free(tb2);
        return;
    }
    
    if (tb1->first == NULL && tb1->last == NULL) {
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
        for (curr = tb->first; curr!= NULL; curr = curr->next) {
            tb->nitems ++;
            tb->totalChar += strlen(curr->value)+1;
        }
    }
    
    tbNew->nitems = tempItems - tb->nitems;
    tbNew->totalChar = tempChar - tb->totalChar;    
    
	return tbNew;
}

/*
typedef struct _matchNode {
	int lineNumber;
	int columnNumber;
	struct _matchNode *next;
} matchNode;

typedef matchNode *Match;
*/

/**
 * Return a linked list of match nodes containing the positions of all
 * of the matches of string 'search' in 'tb'.
 * - The textbuffer 'tb' should remain unmodified.
 * - The user is responsible for freeing the returned list.
 */
Match searchTB (TB tb, char *search) {
    if (search == NULL) 
        errorAbort("ERROR in searchTB search field is NULL");
    
    Match head = malloc(sizeof(*head));
    head->columnNumber = 0;
    head->lineNumber = 0;
    head->next = NULL;
    
    if (strcmp(search, "") == 0 || tb->first == NULL) {
        free(head);
        return NULL;
    }
    
    Match currNode = head;
    int lNum = 1;
    int cNum = 0;
    int numNodes = 0;
    TBNode *curr = tb->first;
    for (curr = tb->first; curr != NULL; curr = curr->next) {
        char *pointer = curr->value;
        while ((pointer = strstr(pointer,search)) != NULL) {
            cNum = pointer - curr->value + 1;
            //shifting position to its next substring
            pointer++;
            if (numNodes == 0) {
                currNode->columnNumber = cNum;
                currNode->lineNumber = lNum;
            } else {
                currNode->next = malloc(sizeof(*currNode));
                currNode = currNode->next;
                currNode->columnNumber = cNum;
                currNode->lineNumber = lNum;
            }
            numNodes++;
        }
        lNum++;
    }
    
    currNode->next = NULL;
    
    return head;
}

/**
 * Remove  the  lines between 'from' and 'to' (inclusive) from the given
 * textbuffer 'tb'.
 * - The  program should abort() with an error message if 'from' or 'to'
 *   is out of range.
 */
void deleteTB (TB tb, int from, int to) {
    if (to < from || to <= 0 || from <= 0 || to > tb->nitems) 
        errorAbort("ERROR in deleteTB boundary");
        
    TB garbageTB = cutTB(tb,from,to);
    releaseTB(garbageTB);
}
//insertChar should shift the current position of the array forward, such that there is enough space to place the text string into the spot
char* insertChar (int pos, char *string, char *insertString, bool replace) {
    size_t length;
    if (replace) {
        length = strlen(string) + strlen(insertString);
    } else {
        length = strlen(string) + strlen(insertString) + 1;
    }
    // +1 works??
    char *textArray = malloc(sizeof(char) *(length+1));
    textArray[0] = '\0';
    int i = 0;
    
    for (i = 0; i < length; i++) {
        if (i >= pos && i < pos + strlen(insertString)) {
            //printf("%c",insertString[i-pos]);
            textArray[i] = insertString[i-pos];
        } else if (i < pos) {
            //printf("%c",string[i]);
            textArray[i] = string[i];
        } else if (i >= pos + strlen(insertString)) {
            //printf("%c",string[i-pos-strlen(insertString)]);
            if (replace) {
                textArray[i] = string[i-strlen(insertString)+1];
            } else {
                textArray[i] = string[i-strlen(insertString)];
            }
        }
    }
    textArray[i] = '\0';
    //printf("textArray %s\n", textArray);
    return textArray;
    
}

void strAppend (char *str, char* startStr, char* endStr, char* symb, int startPos, int endPos) {
    char* temp;
    temp = insertChar(startPos,str,startStr,1);
    strcpy(str,temp);
    free(temp);
    
    if (strcmp(endStr,"</h1>") == 0) {
        endPos = strlen(str);
        temp = insertChar(endPos,str,endStr,0);
        strcpy(str,temp);
        free(temp);
    } else {
        endPos += strlen(startStr) -1;
        temp = insertChar(endPos,str,endStr,1);
        strcpy(str,temp);
        free(temp);
    }
}

void applyRichText (TB tb, TBNode *node) {
    TBNode *curr = node;
    int i = 0;
    while (i < strlen(curr->value)) {
        if (curr->value[i] == '#' && i == 0) {
            //string ended
            if (curr->value[i + 1] == '\0') {
                i++;
            // string didnt end, go to the end and insert <h1> and </h1> 
            } else {
                int j = strlen(curr->value);
                //printf("strlen curr->value before %ld\n", strlen(curr->value));
                size_t newSLength = strlen(curr->value);
                newSLength += strlen("<h1>") + strlen("</h1>") + 1;
                curr->value = (char *)realloc(curr->value,newSLength);
                
                strAppend(curr->value,"<h1>", "</h1>", "#",i,j);
                //printf("#i is %d\n",i);
                //printf("#j is %d\n",j);
                tb->totalChar += strlen("<h1>") + strlen("</h1>") -1;  
                
                //special case breaks loop if this runs
                break;
            }
        } else if (curr->value[i] == '*') {
            int j = i + 1;
            for (j = i+1; j < strlen(curr->value); j++) {
                if (curr->value[j] == '*') {
                    break;
                }
            }
            
            if (j == i + 1) {
                i++;
            } else if (j == strlen(curr->value)) {
                //printf("no more*\n");
                i++;
            // there is a non consecutive asterix after i position
            } else {
                size_t newSLength = strlen(curr->value);
                newSLength += strlen("<b>") + strlen("</b>") + 1;
                curr->value = (char *)realloc(curr->value,newSLength);
                
                strAppend(curr->value,"<b>", "</b>", "*",i,j);
                
                tb->totalChar += strlen("<b>") + strlen("</b>") -2;
                i = j + 1;
            }
            //printf("*i is %d\n",i);
            //printf("*j is %d\n",j);
            
        } else if (curr->value[i] == '_') {
            int j = i+1;
            for (j = i+1; j < strlen(curr->value); j++) {
                if (curr->value[j] == '_') {
                    break;
                }
            }
            if (j == i + 1) {
                i++;
            } else if (j == strlen(curr->value)) {
                //printf("no more_\n");
                i++;
            // there is a non consecutive asterix after i position
            } else {
                size_t newSLength = strlen(curr->value);
                newSLength += strlen("<i>") + strlen("</i>") + 1;
                curr->value = (char *)realloc(curr->value,newSLength);
                
                strAppend(curr->value,"<i>", "</i>", "_",i,j);
                
                tb->totalChar += strlen("<i>") + strlen("</i>") -2;
                i = j + 1;
            }
            
            //printf("_i is %d\n",i);
            //printf("_j is %d\n",j);
        } else {
            i++;
        }
    }
    //printf("%s\n",curr->value);
    
    //printf("%d\n", node->columnNumber);
    

    
    

}

/**
 * Search  every  line of the given textbuffer for every occurrence of a
 * set of specified substitutions and alter them accordingly.
 * - Refer to the spec for details.
 */
void formRichText (TB tb) {
    TBNode *curr = tb->first;
    
    while (curr != NULL) {
        applyRichText(tb,curr);
        curr = curr->next;
    }
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

