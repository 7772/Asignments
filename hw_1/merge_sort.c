#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

    // // 만약 바꾸는게 맞으면 바꿀 것.
    if(cnt > 1000000) {
        cnt = 1000000;
        printf("Numbers in your input file is greater than 1000000. So I changed Numbers from %d to 1000000 \n", cnt);
    }

    // printf("%d 개 \n", cnt);

    return cnt;
}

// 파일 I/O -> 배열에 저장하는 함수
// Parameter : 읽을 파일 이름
// Return : 읽은 파일을 개행으로 파싱하여 저장된 배열
int *readFile(int n, char *fileName) {
    
    printf("in readFile Func %d, %s \n", n, fileName);

    getchar();

    int numberArr[n];
    int i = 0, tmpNumber, j;

    FILE *fp = fopen(fileName, "rt");

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
            // printf("%s", buffer);
            values[i] = atoi(buffer);
            // printf("%d", values[i]);
            i++;
        }
    }

    fclose(fp);
    return values;
}

// Sorting Function
// Parameter : sorting 할 숫자 개수 N, Sorting 할 Array
// Return : N 개 만큼 정렬된 Array
// int sortingFunc(int n, int arr) {}

// 출력 함수
// Parameter : N, Array
// Return : null
// void printSortedArray(int n, int arr) {}

int main(int argc, char* argv[]) {

    // Not input number and fileName
    if (argc == 1) {
        fputs("Error! You should input number and fileName..\n", stderr);
        return -1;
    }

    int n = atoi(argv[1]);
    char *fileName = argv[2];
    int k = getHowManyNumber(fileName);
    int *values;

    if(n > k) {
        n = k;
        printf("Numbers to sort is greater than Numbers in input file. So I chaned Numbers to sort from %d to %d \n", n, k);
    }

    values = readFile(n, fileName);

    printf("The number of num in input file: %d \n", k);
    printf("The number of num to sort : %d \n", n);
    printf("File Name : %s \n", fileName);

    for(int j=0; j<n; j++) {
        printf("%d : %d \n", j, values[j]);
    }

    return 0;
}