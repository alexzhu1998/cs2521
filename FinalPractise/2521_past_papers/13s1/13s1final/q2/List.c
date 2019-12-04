// List.c ... implementation of simple List ADT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "List.h"

typedef struct Node *Link;

typedef struct Node {
	int  value;
	Link next;
} Node;

typedef struct ListRep {
	int  nnodes;
	Link first;
	Link last;
} ListRep;

// newList ... make new empty List
List newList()
{
	List new = malloc(sizeof(ListRep));
	assert(new != NULL);
	new->nnodes = 0;
	new->first = NULL;
	new->last = NULL;
	return new;
}

// ListShow ... display List as <a, b, c, d, ...z>
void ListShow(List L)
{
	assert(L != NULL);
	printf("[");
	Link curr = L->first;
	while (curr != NULL) {
		printf("%d",curr->value);
		if (curr->next != NULL) printf(", ");
		curr = curr->next;
	}
	printf("]\n");
}

// ListLength ... number of nodes in List
int ListLength(List L)
{
	assert(L != NULL);
	return (L->nnodes);
}

// ListAppend ... append a new value to List
void ListAppend(List L, int value)
{
	assert(L != NULL);
	Link new = malloc(sizeof(Node));
	assert(new != NULL);
	new->value = value;
	new->next = NULL;
	L->nnodes++;
	if (L->first == NULL)
		L->first = L->last = new;
	else {
		L->last->next = new;
		L->last = new;
	}
}

// ListReverse ... reverse a List
void ListReverse(List L)
{
	if(L->nnodes == 0) {
		return;
	}
	int *arr = malloc(sizeof(int)*L->nnodes);
	Link curr = L->first;

	int i = 0;
	while(curr!=NULL){
		arr[i] = curr->value;
		//printf("%d\n",curr->value);
		//printf("Arr %d\n",arr[i]);
		curr = curr->next;
		i++;
		
	}
	List new = newList();
	for(i=L->nnodes-1;i>=0;i--){
		//printf("Arr %d\n",arr[i]);
		ListAppend(new,arr[i]);
	}
	free(arr);
	List temp = L;
	curr = temp->first;
	while(curr!=NULL){
		Link temp1 = curr->next;
		free(curr);
		curr = temp1;
	}
	free(temp);
	L->first = new->first;
	L->last = new->last;
	L->nnodes = new->nnodes;
	//free(temp);
}
