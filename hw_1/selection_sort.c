// 박현도, 20145810

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int getNum(char *fileName); // Get How many numbers in input file.
void readFile(int *values, int n, char *fileName); // Read the input file.
void selectionSort(int *values, int n); // Selection Sort Func.

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
        selectionSort(values, n);
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
        printf("Error! File Open Failure.. \n");
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
        return;
    }

    char buffer[7];

    while(i < n) {
        fgets(buffer, sizeof(buffer), fp);
        int length = strlen(buffer);
        if(length > 1) {
            values[i] = atoi(buffer);
            i++;
        }
    }

    fclose(fp);
}

void selectionSort(int *values, int n) {
    int i, j, indexMin, temp;

    // loop through all numbers 
    for(i = 0; i < n-1; i++) { 

        // set current element as minimum 
        indexMin = i;
        
        // check the element to be minimum 
        for(j=i+1; j<n; j++) {
            if(values[j] > values[indexMin]) {
                indexMin = j;
            }
        }

        if(indexMin != i) {
            // swap the numbers 
            temp = values[indexMin];
            values[indexMin] = values[i];
            values[i] = temp;
        }          
    }
}
