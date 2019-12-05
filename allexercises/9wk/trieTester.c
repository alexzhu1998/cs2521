// Trie ADT tester ... COMP9024 17s2

#include "Trie.h"

char *words[] = { "ear", "apply", "ape", "apes", "earth", "east",
		  "app", "ace", "early", "earl", "aces" };

int main(void) {
   Trie t = newTrie();

   int i;
   for (i = 0; i < sizeof(words)/sizeof(char *); i++)
      t = TrieInsert(t, words[i], i);

   showTrie(t);

   freeTrie(t);
   return 0;
}
