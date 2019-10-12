#include <stdio.h>
#include <assert.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>


typedef struct TBNode {
    char *value;
    struct TBNode *next;
} TBNode;

typedef struct textbuffer {
    TBNode *first;
    TBNode *last;
} TB;


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
}


int main (void) {
    
    
    TB *new = malloc(sizeof(*new));
    new->first = new->last = NULL;
    if (new == NULL) err(EX_OSERR, "couldn't allocate DLList");
    
    char text[] = "hello there,\nhow\nare\nthings\n";
    
    int i, j;
    int prevI = 0;
    for (i = 0; text[i] != '\0'; i++) {
        char *temp = (char *) malloc (sizeof(char));
        if (text[i] == '\n'){
            for (j = 0; j < i-prevI; j++) {
                if (text[j+prevI] == '\n') prevI++;
                temp[j] = text[j+prevI];
                //temp[j+1] = '\0'; 
            }
            temp[j] = '\0';
            prevI = i;
            
            TBNode *newNode = malloc(sizeof(*newNode));
            newNode->value = strDup(temp);
            newNode->next = NULL;

            if (new->first == NULL && new->last == NULL){ 
                //printf("hi1");
                new->first = newNode;
                new->last = newNode;
            } else {
                //printf("hi2");
                new->last->next = newNode;
                new->last = newNode;
            }
            
            
        }
        free(temp);
    }
    
   
    TBNode *curr = new->first;
    while (curr != NULL) {
        printf("new line: %s ", curr->value);
        curr = curr->next;
    }
    printf("\n");
    
    curr = new->first;
    while (curr != NULL) {
        TBNode *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(new);
    
    
    int k = 15;
    
    printf("%ld",sizeof(k));
    
    return 0;
}
