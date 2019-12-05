// Trie ADT implementation ... COMP9024 17s2

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Trie.h"

typedef struct Node {
   bool finish;       // last char in key?
   Item data;         // NO_ITEM if !finish
   Trie child[ALPHABET_SIZE];
} Node;

Trie newTrie() {
   return NULL;
}

void freeTrie(Trie t) {
   if (t != NULL) {
      int c;
      for (c = 0; c < ALPHABET_SIZE; c++)
	 freeTrie(t->child[c]);
      free(t);
   }
}

// make a new node
Node *newNode(void) {
   Trie new = malloc(sizeof(Node));
   assert(new != NULL);
   new->finish = false;
   new->data = NO_ITEM;
   int c;
   for (c = 0; c < ALPHABET_SIZE; c++)
      new->child[c] = NULL;
   return new;
}

Trie TrieInsert(Trie t, Key k, Item it) {
   if (t == NULL)
      t = newNode();
   
   if (k[0] == '\0') {
      t->finish = true;
      t->data = it;
   } else {
      int i = k[0] - FIRST_CHAR;
      t->child[i] = TrieInsert(t->child[i], k+1, it);
   }
   return t;
}

static bool newline;

void showTrieR(Trie t, int depth) {
   int i, d;
   if (t != NULL) {
      for (i = 0; i < ALPHABET_SIZE; i++) {
	 if (t->child[i] != NULL) {
	    if (newline) {                   // just started a new line?
	       for (d = 0; d < depth; d++)
		  putchar('-');
	       newline = false;
	    }
	    printf("%c", (char)i + FIRST_CHAR);
	    if (t->child[i]->finish) {
	       printf(" %d\n", t->child[i]->data);
	       newline = true;
	    }
	    showTrieR(t->child[i], depth+1);
	 }
      }
   }
}

void showTrie(Trie t) {
   newline = false;
   showTrieR(t, 0);
}
