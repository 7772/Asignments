/**
 * "Quick Sort"
 * - ./basic_quick_sort <input_file_name> <N>
 * - measure running time of 'Quick Sort'
 *
 * name / ID
  **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


void choose_pivot (int *data, unsigned int n) {
	
	/* your code here */
	
}

unsigned long quick_sort (int *data, unsigned int n) {
    unsigned long cnt = (n - 1); // number of comparisons

	/* your code here */

	
    // choose pivot and  always place it at first element of array
    choose_pivot(data, n);

	
	/* your code here */

	
    return cnt;
}



int main (int argc, char* argv[]) {





	/* your code here */


	/* your code here */

	
	/* your code here */
	
	
	// Please keep these printf statements!
    printf("N = %7d,\tRunning_Time = %.3f ms\n", N, duration);

	/* your code here */
	
		
    return 0;
}

