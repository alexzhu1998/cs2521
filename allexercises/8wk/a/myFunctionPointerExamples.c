#include <stdlib.h>
#include <stdio.h>

int square(int x) { 
	return x*x;
}

int timesTwo(int x) {
	return x*2;
}

double addGST( double val, int rate){
	double valPlusGST = val * (100.0 + rate)/100.0; 
	return valPlusGST;
}

int main(int argc, char *argv[])
{
		
	int (*fp)(int);    // declare fp as a point to function 

	fp = &square;      //fp points to the square function

	int n = (*fp)(10); //call the square function with input 10

	printf(">> n (after calling function square) %d \n", n);

	fp = timesTwo;     //works without the &
					    //fp points to the timesTwo function

	n = (*fp)(2);      //call the timesTwo function with input 2
	printf(">> n (after calling function timesTwo) %d \n", n);

	n = fp(2);         //can also use normal function call
				        //notation 
	printf(">> n (after calling fp(2)) %d \n", n);

	double (*fpGST) (double, int); 

	fpGST = addGST;
	double val2 = fpGST(125, 10);
	printf(">> val2 is %.2f \n", val2);



	return EXIT_SUCCESS;
}

