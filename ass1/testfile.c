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




int main (void) {
    
    
    TB *new = malloc(sizeof(*new));
    new->first = new->last = NULL;
    if (new == NULL) err(EX_OSERR, "couldn't allocate DLList");
    
    
    char text[] = "hello there,\nhow\nare\nthings\n";
    //printf("%s\n", greeting);
    char temp[] = "";
    int i, j;
    int prevI = 0;
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n'){
            for (j = 0; j < i-prevI; j++) {
                if (text[j+prevI] == '\n') prevI++;
                temp[j] = text[j+prevI]; 
            }
            temp[j] = '\0';
            prevI = i;
            
            printf("%s" ,temp);
            printf("j is %d", j);
            printf("i is %d", i);
            
            
            TBNode *newNode = malloc(sizeof(*newNode));
            newNode->value = malloc(sizeof(*(newNode->value)));
            strcpy(newNode->value,temp);
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
    }
//// NOT TESTED
    char textArray[] = "";
    int textLen = 0;
    TBNode *curr = new->first;
    while (curr != NULL) {
        for (int i = 0; i < strlen(curr->value); i++) {
            textArray[i+textLen] = curr->value[i];
            if (i+1 == strlen(curr->value)) {
                textLen++;
                textArray[i+textLen] = '\n';
            }
        }
        textLen += strlen(curr->value);
        curr = curr->next;
    }
    textArray[textLen]='\0';
    printf("%c\n",textArray[textLen+1]);
    
    printf("%s",textArray);
    
    assert(strcmp(textArray,"hello there,\nhow\nare\nthings\n") == 0);
    /*
    while (curr != NULL) {
        strcpy(textArray,curr->value);
        printf("%c",textArray[strlen(curr->value)-1]);
        curr = curr->next;
    }
    printf("\n");
    */
    
    curr = new->first;
    while (curr != NULL) {
        printf("%s ", curr->value);
        curr = curr->next;
    }
    printf("\n");
    
    /*
    int i = 0;
    while (i < MAX_LINE_LENGTH  && greeting[i] != '\0') {
        char *xd = "";
        printf("%c\n", greeting[i]);
        if (greeting[i] == '\n') {
            xd[
            printf("yay");
        }
        i++;
    }
    */
    
    curr = new->first;
    while (curr != NULL) {
        TBNode *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(new);
    return 0;
}

