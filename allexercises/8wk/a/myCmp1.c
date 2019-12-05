#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* generic min function
*/
void * min(void *vp1, void *vp2,  int (*fpCmp) (void *, void *)  ){

	int cmpVal  = fpCmp(vp1, vp2); 

	if(cmpVal <= 0){
		return vp1;
	}
	else {
		return vp2; 
	}

}

int intCompare(void *ip1, void *ip2 ) {
    int val1 = * ( (int *)ip1 ) ;
    int val2 = * ( (int *)ip2 ) ;

    return val1 - val2;
}


/* stringCompare downcasts its void * arguments to char * and then passes
   them to strcmp for comparison
*/
int stringCompare(void *ip1, void *ip2) {
    
    char *s1 = (char *)ip1;
    char *s2 = (char *)ip2;

    return strcmp( s1, s2);
}


int main(int argc, char *argv[]) {
  
    char *s1 = "Sydney"; 
    char *s2 = "New Your"; 

    char *minString = (char *) min(s1, s2, stringCompare); 
    printf("\nmin string = %s\n", minString);
    printf("--------------------------\n");

    // -----------------------------------

    int val1 = 55;
    int val2 = 34;

    int *minInt = (int *) min(&val1, &val2, intCompare);
    printf("min int = %d\n", *minInt);
    printf("--------------------------\n");


    return 0;
}

