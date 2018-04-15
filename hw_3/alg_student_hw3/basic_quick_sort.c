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

#include <time.h>

void readFile(int *values, int n, char *fileName);

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

    clock_t start;
    start = clock();
    double counter = 0;
    double elapsedTime, timeForTask;

	int n, k, j, *values; // n : first parameter, k : The number of numbers in input file, values : array
    char *fileName; // fileName : second parameter, That is, Input File name.


	// Not input number and fileName
    if (argc == 1) {
        fputs("Error! You should input number and fileName..\n", stderr);
        return -1;
    }

	n = atoi(argv[2]); // Changed the first command line parameter from char to int.
    
	// if N > K, change N to 1000000.
	if(n > 1000000) {
		n = 1000000;
	}
	
	fileName = argv[1]; 
    // k = getNum(fileName); // Get How many numbers in input file.
	values = (int*)malloc(sizeof(int)*n);
	readFile(values, n, fileName);

	/* your code here */


	/* your code here */

	
	/* your code here */
	
	
	// Please keep these printf statements!
    // printf("N = %7d,\tRunning_Time = %.3f ms\n", N, duration);

	/* your code here */
	

	// free values
	free(values);	
    return 0;
}

// File I/O
// Parameter : Array, Number to read, Filename
// Return : Number Array 
void readFile(int *values, int n, char *fileName) {

    int i = 0;

    FILE *fp = fopen(fileName, "rt");

    if(fp == NULL) {
        printf("Error! File Open Failure..");
        exit(-1);
    }

    char buffer[7];

    while(i <= n) {
        fgets(buffer, sizeof(buffer), fp);
        int length = strlen(buffer);
        if(length > 1) {
            // printf("%s", buffer);
            values[i] = atoi(buffer);
            // printf("%d \n", values[i]);
            i++;
        }
    }

    fclose(fp);
}