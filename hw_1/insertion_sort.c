// 박현도, 20145810

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int getHowManyNumber(char *fileName); // Get How many numbers in input file.
int *readFile(int n, char *fileName); // Read the input file.
void insertionSort(int *values, int n); // Insertion Sort Func.

int main(int argc, char* argv[]) {

    clock_t start;
    start = clock();
    double counter = 0;
    double elapsedTime, timeForTask;

    int n, k, j, *values; // n : first parameter, k : The number of numbers in input file, values : array
    char *fileName; // fileName : second parameter, That is, Input File name.

    do {
        counter++;

        // Not input number and fileName
        if (argc == 1) {
            fputs("Error! You should input number and fileName..\n", stderr);
            return -1;
        }

        n = atoi(argv[1]); // Changed the first command line parameter from char to int.
        fileName = argv[2]; 
        k = getHowManyNumber(fileName); // Get How many numbers in input file.

        // Change Value n from n to k
        if(n > k) {
            n = k;
        }

        values = readFile(n, fileName); // Read the input file.

        insertionSort(values, n);

        for(int j=0; j<n; j++) {
            printf("%d \n", values[j]);
        }

        free(values);

    } while(clock() - start < 1000);

    // Calalate running time.
    elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC;
    timeForTask = elapsedTime / counter;

    printf("Running Time = %f ms \n", timeForTask);

    return 0;
}

// Get How many numbers in input file.
// Parameter : Filename
// Return : The number of numbers in input file.
int getHowManyNumber(char* fileName) {
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
// Parameter : Number to read, Filename
// Return : Number Array 
int *readFile(int n, char *fileName) {

    int i = 0;

    FILE *fp = fopen(fileName, "rt"); // "rt" is 

    if(fp == NULL) {
        printf("Error! File Open Failure..");
        return 0;
    }

    char buffer[7];

    int *values;
    values = (int*)malloc(sizeof(int)*n);

    while(i < n) {
        fgets(buffer, sizeof(buffer), fp);
        int length = strlen(buffer);
        if(length > 1) {
            values[i] = atoi(buffer);
            i++;
        }
    }

    fclose(fp);
    return values;
}

void insertionSort(int *values, int n) {
    int i, j, temp;

    for(i=1; i<n; i++) {
        temp = values[i];
        j = i - 1;
        while(j >= 0 && values[j] < temp) {
            values[j+1] = values[j];
            j = j - 1;
        }
        values[j+1] = temp;
    }
}
