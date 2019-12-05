// Trie ADT interface ... COMP9024 17s2

#include <stdbool.h>

#define ALPHABET_SIZE 26
#define FIRST_CHAR 'a'
#define NO_ITEM 0

typedef int  Item;
typedef char *Key;

typedef struct Node *Trie;

Trie newTrie();        // create an empty Trie
void freeTrie(Trie);   // free memory associated with Trie
void showTrie(Trie);   // display a Trie (branch-by-branch)

Item *TrieSearch(Trie, Key);       // find a key in a Trie
Trie TrieInsert(Trie, Key, Item);  // insert a new item into a Trie
