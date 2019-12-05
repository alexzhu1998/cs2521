#include <stdlib.h>
#include <stdio.h>


void printMark(int x) { 
		printf("Marks: %d \n", x);
}

void printPassFail(int x) { 
	if(x <50){
		printf("Marks: %d, Fail\n", x);
	}
	else{
		printf("Marks: %d, Pass\n", x);
	}
}

void traverseA(int *a, int n, void (*fp) (int)){

	for(int i=0; i<n; i++){

		fp( a[i] );

	}
}

int main(int argc, char *argv[])
{
	int marksA[] = {67, 34, 81, 44, 91};

	traverseA (marksA, 5, printMark);

	printf("------------------------------------- \n");

	traverseA (marksA, 5, printPassFail);



	return EXIT_SUCCESS;
}

