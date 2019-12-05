#include <stdlib.h>
#include <stdio.h>


int mySum(int x, int y) { 
    return x + y;
}

int mySumOdd(int x, int curValue) { 
    if( (x % 2) == 1 ) { return x + curValue; }
    else { return curValue; }
}

int myMax(int x, int curValue) { 
    if( x > curValue ) { return x; }
    else { return curValue; }
}

int myFold(int a[], int n, int (*fp) (int, int), int startValue){

    if(n == 0) { 
        return startValue; 
    }
    else {
        
        int curValue = myFold(a, n-1, fp, startValue); 
	int nodeVal = a[n-1]; 
        int ans = fp( nodeVal, curValue ); 
         
        return ans; 
   
    /**
        Alternatively, you can write the following one line 
        return fp( a[n-1], myFold(a, n-1, fp, startValue) ) ;  
    **/
    
    }
 }

int main(int argc, char *argv[])
{
	int marksA[] = {67, 134, 81, 44, 91};

	int ans = myFold(marksA, 5, mySum, 0) ;
	printf ("mySum: ans is : %d \n" , ans);

	ans = myFold(marksA, 5, mySumOdd, 0) ;
	printf ("mySumOdd: ans is : %d \n" , ans);

	ans = myFold(marksA, 5, myMax, marksA[0] ) ;
	printf ("myMax: ans is : %d \n" , ans);	

	return EXIT_SUCCESS;
}

