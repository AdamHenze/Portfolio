/*
 ============================================================================
 Name        : Project4.c
 Author      : Adam Henze
 Professor   : Sambriddhi Mainali
 Class       : 2023FS-CMP_SCI-4250-001
 Description : Project 4
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define ARRSIZE 1000

// function 1
void f1() {
	// char array and variables
    char array[ARRSIZE];
    static int n = 0;
    static long int addr = 0;

    // check for 10 increments
    if (n < 10) {
    	// print call
    	printf("Call number %d at %p\n", ++n, &array);
        // checks previous address for size estimate
    	long int arSize = (long int)&array - addr;
        printf("\Address %d size is %ld\n\n", n - 1, arSize);
    }

    // recursive call if less than 10 incriments
    if (n < 10) {
        addr = (long int)&array;
        f1();
    }
}

void f2() {
    char array[ARRSIZE];
    static int n = 0;
    static long int addr = 0;

    printf("Call number %d at %p\n", ++n, &array);
    // infinite runtime
    if (n > 1) {
        long int arSize = (long int)&array - addr;
        long int stackSize = arSize * n;
        printf("\Address %d size is %ld\n\n", n - 1, arSize);
        printf("Stack Size #%d is %ld\n\n", n - 1, stackSize);
    }
    //continue to call infinitely
    addr = (long int)&array;
    f2();
}

void f3() {
	// malloc of array size
    char *array = (char *)malloc(ARRSIZE);
    char c;
    static int n = 0;
    static long int addr = 0;

    // call and free array memory
    if (n < 10) {
    	printf("Call number %d at %p\n", ++n, array);
    	long int arSize = (long int)array - addr;
        printf("\Address %d size is %ld\n\n", n - 1, arSize);
        free(array);
    }

    // recursion
    if (n < 10) {
        addr = (long int)array;
        f3();
    }
}

int main() {
	// choose which function to run by un-commenting selected function

    // f1();
    // f2();
    f3();

    return 0;
}

