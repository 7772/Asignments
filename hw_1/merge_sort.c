// 박현도, 20145810

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int getNum(char *fileName); // Get How many numbers in input file.
void readFile(int *values, int n, char *fileName); // Read the input file.
void merge(int *values, int *L, int leftCount, int *R, int rightCount); // Function to Merge Arrays L and R into A. 
void mergeRecursive(int *values, int n); // Recursive function to sort an array of integers.

int main(int argc, char* argv[]) {

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
    
    n = atoi(argv[1]); // Changed the first command line parameter from char to int.
    fileName = argv[2]; 
    k = getNum(fileName); // Get How many numbers in input file.

    // Change Value n from n to k
    if(n > k) {
        n = k;
    }

    values = (int*)malloc(sizeof(int)*n);

    readFile(values, n, fileName); // Read the input file.

    do {
        counter++;
        mergeRecursive(values, n); // Recursive function to sort an array of integers.
    } while(clock() - start < 1000);

    for(j=0; j<n; j++) {
        printf("%d \n", values[j]);
    }

    free(values);

    // Calalate running time.
    elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    timeForTask = elapsedTime / counter;

    printf("Running Time = %f ms \n", timeForTask);

    return 0;
}

// Get How many numbers in input file.
// Parameter : Filename
// Return : The number of numbers in input file.
int getNum(char* fileName) {
    int cnt = 0;
    char buffer[7];

    FILE *fp = fopen(fileName, "rt");

    if(fp == NULL) {
        printf("Error! File Open Failure..");
        return 0;
    }

    while(fgets(buffer, sizeof(buffer), fp) != NULL) {
        int length = strlen(buffer);
        if(length > 1) {
            cnt++;
        }
    }

    // If The number of numbers in input file, cnt is greater than 1000000
    if(cnt > 1000000) {
        cnt = 1000000;
    }

    return cnt;
}

// File I/O
// Parameter : Array, Number to read, Filename
// Return : Number Array 
void readFile(int *values, int n, char *fileName) {

    int i = 0;

    FILE *fp = fopen(fileName, "rt");

    if(fp == NULL) {
        printf("Error! File Open Failure..");
        return 0;
    }

    char buffer[7];

    while(i < n) {
        fgets(buffer, sizeof(buffer), fp);
        int length = strlen(buffer);
        if(length > 1) {
            // printf("%s", buffer);
            values[i] = atoi(buffer);
            // printf("%d", values[i]);
            i++;
        }
    }

    fclose(fp);
}

// Function to Merge Arrays L and R into A. 
void merge(int *values, int *L, int leftCount, int *R, int rightCount) {
    int i,j,k;

	// i - to mark the index of left aubarray (L)
	// j - to mark the index of right sub-raay (R)
	// k - to mark the index of merged subarray (values)
	i = 0; j = 0; k =0;

    while(i < leftCount && j < rightCount) {
		if(L[i] > R[j]) {
            values[k++] = L[i++];
        }
		else {
            values[k++] = R[j++];
        }
	}
    
	while(i < leftCount) {
        values[k++] = L[i++];
    }

	while(j < rightCount) {
        values[k++] = R[j++];
    }
}

// Sorting Function
// Parameter : length, arr
void mergeRecursive(int *values, int n) {
    int mid, i, *L, *R;

    if(n < 2) {
        return;
    }

    mid = n/2;

    L = (int*)malloc(mid*sizeof(int)); 
	R = (int*)malloc((n- mid)*sizeof(int)); 
	
	for(i = 0;i<mid;i++) L[i] = values[i]; // creating left subarray
	for(i = mid;i<n;i++) R[i-mid] = values[i]; // creating right subarray

	mergeRecursive(L, mid);  // sorting the left subarray
	mergeRecursive(R, n-mid);  // sorting the right subarray
	merge(values, L, mid, R, n-mid);  // Merging L and R into values as sorted list.
    free(L);
    free(R);
}