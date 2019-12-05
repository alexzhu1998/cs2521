// Knuth-Morris-Pratt algorithm ... COMP9024 17s2

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1024
#define MAX_PATTERN_LENGTH 20
#define TEXT_FORMAT_STRING "%1023s"
#define PATTERN_FORMAT_STRING "%19s"

int *failureFunction(char *pattern) {
   int m = strlen(pattern);
   int *F = malloc(m * sizeof(int));
   assert(F != NULL);
   
   int i = 1;
   int j = 0;

   while (i < m) {
      if (pattern[i] == pattern[j]) {  // we have matched j+1 characters
	 F[i++] = ++j;                 // => F[i] = j+1
      } else if (j > 0) {
	 j = F[j-1];                   // use failure function to shift pattern
      } else {
	 F[i++] = 0;                   // no match
      }
   }
   return F;
}

int kmp(char *text, char *pattern, int *F) {
   int n = strlen(text);
   int m = strlen(pattern);
   int i = 0;
   int j = 0;
   while (i < n) {
      if (text[i] == pattern[j]) {
	 if (j == m-1) {
	    return i-j;                // match found
	 } else {
	    i++; j++;
	 }
      } else if (j > 0) {
	    j = F[j-1];                // resume comparing at F[j-1]
      } else {
	    i++;
      }
   }
   return -1;                          // no match
}

int main(void) {
   char T[MAX_TEXT_LENGTH];
   char P[MAX_PATTERN_LENGTH];

   printf("Enter text: ");
   scanf(TEXT_FORMAT_STRING, T);
   printf("Enter pattern: ");
   scanf(PATTERN_FORMAT_STRING, P);

   int *F = failureFunction(P);
   int match = kmp(T, P, F);
   free(F);
   if (match > -1)
      printf("\nMatch found at position %d\n", match);
   else
      printf("\nNo match.\n");

   return 0;
}
