// Adam Henze
// cs4280
// Sharlee Climer
// P1
// 3/6/2024

#include "token.h"
#include "testScanner.h"
#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

//Kept much of the functionallity from P0, had already tokenized strings for easy reading in P0
int main(int argc, char* argv[]) {
			
        //int check = 0;		// checker int for various needs
	FILE *fp = NULL;		// file pointer for input
	FILE *data = NULL;		// file pointer for temp data file
	char c;				// char for file parsing
	//int i;			// counter
	//const int stdinBuffer = 1024;	// buffer size
        //char buffer[stdinBuffer];	// buffer for stdin input

	// temp file for cleaned data to pass to tree builder
        data = fopen("tempdata.txt", "w");

	if(argc > 2){ // too many args
		printf("ERROR: TOO MANY COMMANDLINE ARGUMENTS\n");
                printf("USAGE:\n");
                printf("\t...]$ ./P0\n");
                printf("\t...]$ ./P0 ""file""\n");
                printf("\t...]$ ./P0 < ""file""\n");
		return 1;
	} else if ((argc == 1) && ((fseek(stdin, 0, SEEK_END), ftell(stdin)) < 0)) { // no input grab stdin
		// at this point the only reason to separate no-stdin vs file-redirection is for this prompt
		printf("NO FILE OR STDIN INPUT: WRITE TO STDIN: END w/ EOF (CTRL-D):\n");
		fp = stdin;
        } else if (argc == 2){ // file found try open
		fp = fopen(argv[1], "r");
	} else if ((fseek(stdin, 0, SEEK_END), ftell(stdin)) > 0){ // no args but stdin redirect
		// previous logic removed on realization to set pointer to stdin		
		fp = stdin;
	}

        if(fp == NULL){
                printf("ERROR: NO FILE FOUND OR STDIN DETECTED\n");
                return 1;
        } else {
		//write to temp data
		rewind(fp);
		c = fgetc(fp);
        	while (c != EOF) {
			fputc(c,data);
			c = fgetc(fp);
        	}
	}
	//close and reopen for read data file
	fclose(data);
	fopen("tempdata.txt", "r");
	
	// data file setup, pass to test scanner -----------------------------------------------------------
	rewind(data);	
	testScanner(data);

	fclose(data);
	remove("tempdata.txt");
	// holy cow we made it, Exit success
	printf("EXIT_SUCCESS\n");
	return EXIT_SUCCESS;
};
