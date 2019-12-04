
#define min(A,B) ((A < B) ? A : B)
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

static void mergesort(char a[], int lo, int hi);
static void merge(char a[], int lo, int mid, int hi);
int main(int argc, char *argv[])
{
   char a[16];
   a[0] = 's';
   a[1] = 'o';
   a[2] = 'r';
   a[3] = 't';
   a[4] = 'i';
   a[5] = 'n';
   a[6] = 'g';
   a[7] = 'i';
   a[8] = 's';
   a[9] = 'a';
   a[10] = 'w';
   a[11] = 'e';
   a[12] = 's';
   a[13] = 'o';
   a[14] = 'm';
   a[15] = 'e';
   mergesort(a,0,15);
   
   return 0;
}

static void mergesort(char a[], int lo, int hi)
{
int i, m; // m = length of runs
int end; // end of 2nd run
for (m = 1; m <= hi-lo; m = 2*m) {
for (i = lo; i <= hi-m; i += 2*m) {
end = min(i+2*m-1, hi);
merge(a, i, i+m-1, end);
}
for (int i = 0 ; i < 16 ; i++){
printf("%c",a[i]);}
printf("\n\n");
// show state of array at this point
}
}

static void merge(char a[], int lo, int mid, int hi)
{
int i, j, k, n = hi-lo+1;
char *tmp = malloc(n*sizeof(char));
i = lo; j = mid+1; k = 0;
// scan both segments, copying to tmp
while (i <= mid && j <= hi) {
if (a[i] < a[j])
tmp[k++] = a[i++];
else
tmp[k++] = a[j++];
}

// copy items from unfinished segment
while (i <= mid) tmp[k++] = a[i++];
while (j <= hi) tmp[k++] = a[j++];
//copy tmp back to main array
for (i = lo, k = 0; i <= hi; i++, k++)
a[i] = tmp[k];
free(tmp);
}
