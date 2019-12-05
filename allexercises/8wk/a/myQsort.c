#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int intCompare(const void *ip1, const void *ip2 ) {
    int val1 = * ( (int *)ip1 ) ;
    int val2 = * ( (int *)ip2 ) ;

    return val1 - val2;
}

int intCompareDesc(const void *ip1, const void *ip2 ) {
    int val1 = * ( (int *)ip1 ) ;
    int val2 = * ( (int *)ip2 ) ;

    return val2 - val1;
}

/* stringCompare downcasts its void * arguments to char * and then passes
   them to strcmp for comparison
*/
int stringCompare(const void *ip1, const void *ip2) {
    
    char *s1 = (char *)ip1;
    char *s2 = (char *)ip2;

    return strcmp( s1, s2);
}


int main(int argc, char *argv[]) {
  
    int values[] = { 25, 4, 67, 79, 12 };
    int i = 0;

    printf("\n--------------------------\n");
    printf("Unsorted list is: \n");
    for( i = 0 ; i < 5; i++ ) 
    {
      printf("%d ", values[i]);
    }
    printf("\n--------------------------\n");

    qsort(values, 5, sizeof(int), intCompare);


    printf("\nSorted list (using intCompare) is: \n");
    for( i = 0 ; i < 5; i++ ) 
    {   
      printf("%d ", values[i]);
    }
    printf("\n--------------------------\n");


    qsort(values, 5, sizeof(int), intCompareDesc);


    printf("\nSorted (using intCompareDesc) list is: \n");
    for( i = 0 ; i < 5; i++ ) 
    {   
      printf("%d ", values[i]);
    }
    printf("\n--------------------------\n");


    return 0;
}

