#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


#include "textbuffer.h"


typedef struct TBNode {
    char *value;
    struct TBNode *prev;
    struct TBNode *next;
} TBNode;

struct textbuffer {
    size_t totalChar; 
    int nitems;
    TBNode *first;
    TBNode *last;
};

////// START HELPER FUNCTIONS
// frees a singly linked list - used for searchTB
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

// prints a singly linked list - used for searchTB
void printList (Match head) {
    if (head == NULL) return;
    for (Match curr = head; curr != NULL; curr = curr->next) {
        printf("Node lineNum: %d, Node colNum: %d\n",
        curr->lineNumber, curr->columnNumber);
    }   
}

// aborts whenever an invalid input was received
void errorAbort (char *text){
    printf("%s\n",text);
    abort();
}


// Checking for internal consistency of the TB
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
    
    //checking number of characters are consistent
    count = 0;
    for (TBNode *curr = tb->first; curr != NULL; curr = curr->next) {
        count += strlen(curr->value);
        count += strlen("\n");
    }
    
    
    if (count != tb->totalChar) {
        printf("Total char count mismatch; counted=%zu, totalChar=%ld\n",
			count,
			tb->totalChar);
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

//creates a new textbuffer node - used in newTB
void newNodefoo (TB tb, char *text){
    
    if (text == NULL) return;
    //allocate memory for the node
    TBNode *newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) errorAbort("ERROR in newNodefoo");
    //allocate memory for the array
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
    tb->nitems++;
    
} 


//shift the current position of the array forward, so that there is enough space to place the text string into the spot - used in strAppend as part of a function in formRichText
char* insertChar (int pos, char *string, char *insertString, bool replace) {
    size_t length;
    if (replace) {
        length = strlen(string) + strlen(insertString);
    } else {
        length = strlen(string) + strlen(insertString) + 1;
    }
    // malloc +1 for null terminator
    char *textArray = malloc(sizeof(char) *(length+1));
    textArray[0] = '\0';
    int i = 0;
    
    for (i = 0; i < length; i++) {
        if (i >= pos && i < pos + strlen(insertString)) {
            textArray[i] = insertString[i-pos];
        } else if (i < pos) {
            textArray[i] = string[i];
        } else if (i >= pos + strlen(insertString)) {
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

//use insertChar function differently depending on the special symbols being used, if # is used, there will not be an ending # to be replaced. The strAppend will be used in applyRichText as part of formRichText
void strAppend (
    char *str, char* startBuffer, char* endBuffer,int startPos, int endPos
) {
    //inserting  starting pair <...> into the array
    char* temp;
    temp = insertChar(startPos,str,startBuffer,1);
    strcpy(str,temp);
    free(temp);
    
    //inserting  ending pair <...> into the array
    if (strcmp(endBuffer,"</h1>") == 0) {
        endPos = strlen(str);
        temp = insertChar(endPos,str,endBuffer,0);
        strcpy(str,temp);
        free(temp);
    } else {
        endPos += strlen(startBuffer) -1;
        temp = insertChar(endPos,str,endBuffer,1);
        strcpy(str,temp);
        free(temp);
    }
}

//function that takes in the textbuffer node and applies changes to the string it contains
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
                size_t newSLength = strlen(curr->value);
                newSLength += strlen("<h1>") + strlen("</h1>") + 1;
                curr->value = (char *)realloc(curr->value,newSLength);
                
                strAppend(curr->value,"<h1>", "</h1>",i,j);

                tb->totalChar += strlen("<h1>") + strlen("</h1>") -1;  
                
                //special case breaks loop if this runs
                break;
            }
        } else if (curr->value[i] == '*' || curr->value[i] == '_') {
            char symbol;
            // 5 is the max length of <b> or </b> + 1
            char buffer1[5];
            char buffer2[5];
            
            if (curr->value[i] == '*') {
                symbol = '*';
                strcpy(buffer1,"<b>");
                strcpy(buffer2,"</b>");
            } else {
                symbol = '_';
                strcpy(buffer1, "<i>");
                strcpy(buffer2, "</i>");
            }
            
            int j = i + 1;
            for (j = i+1; j < strlen(curr->value); j++) {
                if (curr->value[j] == symbol) {
                    break;
                }
            }
            
            if (j == i + 1) {
                i++;
            } else if (j == strlen(curr->value)) {
                i++;
            // there is a non consecutive asterix after i position
            } else {
                size_t newSLength = strlen(curr->value);
                newSLength += strlen(buffer1) + strlen(buffer2) + 1;
                curr->value = (char *)realloc(curr->value,newSLength);
                
                strAppend(curr->value,buffer1,buffer2, i,j);
                // - 2 totalChar because * are replaced
                tb->totalChar += strlen(buffer1) + strlen(buffer2) -2;
                //jump to the character after next special symbol
                i = j + 1;
            }
        } else {
            i++;
        }
    }

}

//////END HELPER FUNCTIONS

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
    
    int i, j;
    int prevI = 0;
    
    for (i = 0; text[i] != '\0'; i++) {
        char *temp = malloc(strlen(text)+1);
        if (text[i] == '\n') {
            for (j = 0; j < i-prevI; j++) {
                if (text[j+prevI] == '\n') {
                    prevI++;
                }
                if (text[j+prevI] != '\n'){
                    temp[j] = text[j+prevI];
                } else {
                    break;
                }
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
    if (validTB(tb) == false) errorAbort("validTB error");
    
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
        length = tb->totalChar+ totalSpaceDots+ totalDigits + 2;
    	char *textArray = malloc(length);
        textArray[0] = '\0';
        
        i = 1;
        TBNode *curr = tb->first;
        while (curr != NULL) {
            //initiate a variable for converting numbers into strings
            char *numberText = malloc(totalDigits);
            
            //paste into integers
            sprintf(numberText, "%d",i);
            strcat(numberText,". ");

            //append number and dots 
            strcat(textArray,numberText);
            
            //append text
            strcat(textArray, curr->value);	
	        strcat(textArray, "\n");
	        
	        free(numberText);
	        curr = curr->next;
	        i++;
	    }
	    strcat(textArray, "\0");
	    
	    return textArray;
	    
    } else {
        TBNode *curr = tb->first;
        // allocating +2 memory in case
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
    // find position for from and to, and assign nodes on them 
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
    // changing the nitems and totalChar after removing list
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
//which lines of text are added or deleted to get from tb1 to tb2
char *diffTB (TB tb1, TB tb2) {
    TBNode *curr1 = tb1->first;
    TBNode *curr2 = tb2->first;
    
    char *text = malloc(sizeof(*text));
    text[0] = '\0';
    int i = 1;
    
    //looping through both linked list, appending lines if different
    while (curr1 != NULL && curr2 != NULL) {
        if (strcmp(curr1->value,curr2->value) != 0) {
            
            size_t length = strlen(text) + strlen(curr1->value) + 
                strlen(curr2->value) + strlen("+,\n-,\n")
                + i + i+1 + 2;
            text = (char *)realloc(text, length);
            char *text2 = malloc(i);
            char *text3 = malloc(i+1);
            sprintf(text2,"%d",i);
            sprintf(text3,"%d",i+1);            
            
            strcat(text,"+,");
            strcat(text,text2);
            strcat(text,",");
            strcat(text,curr2->value);
            strcat(text,"\n-,");
            strcat(text,text3);
            strcat(text,"\n");
            
            free(text2);
            free(text3);
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
        i++;
    }
    /*** if first linked list hits NULL, loop through second linked list
    **   and print through the second linked list with +'s
    */
    if (curr1 == NULL && curr2 != NULL) {
        while (curr2 != NULL) {
            size_t length = strlen(text) + strlen(curr2->value) +
                strlen("+,,\n") + i + 1+ 2;
            text = (char *)realloc(text, length);
            //initiate a variable for converting numbers into strings
            char *text2 = malloc(i);
            sprintf(text2,"%d",i+1);
            
            strcat(text,"+,");
            strcat(text,text2);
            strcat(text,",");
            strcat(text,curr2->value);
            strcat(text,"\n");
            
            free(text2);
            i++;
            curr2 = curr2->next;
        }
    /*** if second linked list hits NULL, loop through first linked list
    **   and print through the first linked list with -'s
    */    
    } else if (curr1 != NULL && curr2 == NULL) {
        while (curr1 != NULL) {
            size_t length = strlen(text) + strlen(curr1->value) +
                strlen("-,\n") + i + 2;
            text = (char *)realloc(text, length);
            char *text2 = malloc(i);
            sprintf(text2,"%d",i+1);
            
            strcat(text,"-,");
            strcat(text,text2);
            strcat(text,"\n");
            
            free(text2);
            i++;
            curr1 = curr1->next;
        }
    }
    
	return text;
}

void undoTB (TB tb) {
    // operations that can be undone: deleteTB, mergeTB, pasteTB, cutTB
}

void redoTB (TB tb) {

}

