/**
 * "MSD Radix Sort"
 *
 * name: Hyundo Park
 * ID: 20145810
 * 
  **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int readFile(int * data, int n, char * fileName);
void msd_radix_sort(int * data, int length);
int getMax(int data[], int length);
void countSort(int data[], int length, int exp);

int main (int argc, char* argv[]) {

    clock_t start;
    start = clock();
    double counter = 0;
    double elapsedTime, timeForTask;

    // n : first parameter
    // k : The number of numbers in input file
    // data : array
	int n, k, j, * data; 
    // fileName : second parameter, That is, Input File name.
    char * fileName;
    // the length of array
    int length;         

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
	data = (int *) malloc(sizeof(int) * n);

    // To handle all exception(especially the last line),
    // Add return statement in readFile Func
    // and variable 'length' is the length of array.
	length = readFile(data, n, fileName);

    do {
        counter++;
        msd_radix_sort(data, length);
    } while(clock() - start < 1000);

    for(k = 0; k < length; k++) {
        printf("%d\n", data[k]);
    }

    // Calalate running time.
    elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    timeForTask = elapsedTime / counter;

    printf("Running Time = %f ms \n", timeForTask);

	// free data
	free(data);	
    return 0;
}

// File I/O
// Parameter : Array, Number to read, Filename
// Return : Number Array 
int readFile(int * data, int n, char * fileName) {

    int i = 0, length = 0, strLength = 0;
    int tmpNumber = 0;
    char buffer[8];

    FILE *fp = fopen(fileName, "rt");

    if(fp == NULL) {
        printf("Error! File Open Failure..");
        exit(-1);
    }

    while(!feof(fp)) {
        // since i is postfix increment, check if same n+1 
        if(i == n + 1) break;

        fgets(buffer, sizeof(buffer), fp);
        strLength = strlen(buffer);
        tmpNumber = atoi(buffer);
        
        if(strLength > 1) {
            if(tmpNumber != 0) {        // '/n' == atoi(buffer) == 0
                ++length;               // the length of array
                data[i] = tmpNumber;
            }
            i++;
        }
    }

    return length;
    fclose(fp);
}

void msd_radix_sort(int * data, int length) {
    // Find the maximum number to know number of digits
    int m = getMax(data, length);
 
    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10) {
        countSort(data, length, exp);
    }
}

// A function to do counting sort of data[] according to
// the digit represented by exp.
void countSort(int * data, int length, int exp) {
    int aux[length]; // aux array
    int i, count[10] = { 0 };
 
    // Store count of occurrences in count[]
    for (i = 0; i < length; i++)
        count[ (data[i] / exp) % 10 ]++;
 
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in aux[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the aux array
    for (i = length - 1; i >= 0; i--)
    {
        aux[count[ (data[i] / exp) % 10 ] - 1] = data[i];
        count[ (data[i] / exp) % 10 ]--;
    }
 
    // Copy the aux array to data[], so that data[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < length; i++) {
        // To not save 0
        if(aux[i] > 0) {     
            data[i] = aux[i];
        }
    }
}

// A utility function to get maximum value in data[]
int getMax(int * data, int length)
{
    int max = data[0];
    for (int i = 1; i < length; i++) {
        if (data[i] > max) {
            max = data[i];
        }
    }
    return max;
}