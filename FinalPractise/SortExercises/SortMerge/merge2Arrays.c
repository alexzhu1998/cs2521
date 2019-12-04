#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#define key(A) (A)
#define less(A,B) (key(A) < key(B))
#define swap(A,B) {int t; t = A; A = B; B = t;}
#define swil(A,B) {if (less(A,B)) swap(A,B);}

void doMergeSort(int a[], int b[], int lo, int hi,  int depth);
void merge(int a[], int aN, int b[], int bN, int c[]);
void printArray(int a[], int lo, int hi);
void printSpaces(int noSpaces);


void mergeSort(int a[], int lo, int hi)
{
   int i;
   int *aux = malloc((hi+1)*sizeof(int));
   for (i = lo; i <= hi; i++) aux[i] = a[i];
   doMergeSort(a, aux, lo, hi, 1);
   free(aux);
}

void doMergeSort(int a[], int b[], int lo, int hi, int depth)
{
   if (lo >= hi) return;
   int mid = (lo+hi)/2;

   printSpaces(depth*2);
   fprintf(stdout, "%d>> lo: %d, mid: %d, hi: %d\n", depth, lo, mid, hi);


   doMergeSort(b, a, lo, mid , depth+1);
   doMergeSort(b, a, mid+1, hi, depth+1);
   merge(b+lo, mid-lo+1, b+mid+1, hi-mid, a+lo);

   printSpaces(depth*2);
   fprintf(stdout, "%d>b(L,%d to %d): ", depth, lo, mid);
   printArray(b, lo, mid+1);

   printSpaces(depth*2);
   fprintf(stdout, "%d>b(R,%d to %d): ", depth, mid+1, hi);
   printArray(b, mid+1, hi+1);


   printSpaces(depth*2);
   fprintf(stdout, "%d>a(%d to %d): ", depth, lo, hi);
   printArray(a, lo, hi+1);

}


// merge arrays a[] and b[] into c[]
// aN = size of a[], bN = size of b[]
void merge(int a[], int aN, int b[], int bN, int c[])
{
   int i; // index into a[]
   int j; // index into b[]
   int k; // index into c[] 
   for (i = j = k = 0; k < aN+bN; k++) {
      if (i == aN)
         c[k] = b[j++];
      else if (j == bN)
         c[k] = a[i++];
      else if (less(a[i],b[j]))
         c[k] = a[i++];
      else
         c[k] = b[j++];
   }
}


void printSpaces(int noSpaces){
	int i;
	for(i=0; i<noSpaces; i++){
		fprintf(stdout, " ");
	}
}

void printArray(int a[], int lo, int hi){

	int i;
	for(i=lo; i<hi; i++){
		fprintf(stdout, "%d,", a[i]);
	}
	fprintf(stdout, "\n");
}

int main (int argc, char *argv[])
{ 

	int x[11] = {5,4,19,7,2,3,8,11,14,6,12}; 

	mergeSort(x, 0, 10);

	fprintf(stdout, "\n\nSorted: ");
	printArray(x, 0, 11);	
	fprintf(stdout, "\n");

	return 0;
}
