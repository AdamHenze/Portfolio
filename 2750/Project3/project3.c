#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "findc.h"

//buffer for stdin store
#define stdinBuffer 1024

//begin main
int main(int argc, char** argv){

	int count = 0;		//char count
	int option;		//option
	char c;			//char to store file char
	char x = 'c';		//char to count
	FILE *fp = NULL;	//file
	int i;			//counter for loops
	
	//print args
	for(i = 0; i < argc; i++){
		printf("ARG %d : %s\n", i, argv[i]);
	}

	//options switch to handle arguments
	while ((option = getopt(argc, argv, "hf:c:")) != -1) {
		switch(option) {
			case 'h':
     				help();
     				return 0;
     				break;
    			case 'f':			
				fp = fopen(optarg, "r");
			   	// Check if file exists
			    	if (fp == NULL){ 
	                   		printf("Could not open file %s\n", optarg);
					return 0;
				}
     				continue;
    			case 'c':
				x = *optarg;
     				//printf("XXX: %s\n", optarg); //check to see character update
     				continue;
    			default:
     				help();
     				return 0;
   		}
	}

	// the '<' just makes it work, dont ask me how
	// trying to check for empty stdin and no file
	if(fp == NULL && (fseek(stdin, 0, SEEK_END), ftell(stdin)) < 0){	
		printf("NO FILE OR STDIN DETECTED\n");
		return 0;
	}
	//if good file then parse
	else if(fp != NULL){
    		c = fgetc(fp);
    		printf("FILE:-------------------------------------------------------------------\n");
		//parse for char
		while (c != EOF){
        	if (c == x){
			count++;
		}
		//print while parse
		printf ("%c", c);
        	c = fgetc(fp);
   		}
		printf("------------------------------------------------------------------------\n");
	}
	//if stdin not empty then parse
	else if((fseek(stdin, 0, SEEK_END), ftell(stdin)) > 0){
		rewind(stdin);
		//store stdin
		char buffer[stdinBuffer];
   		fgets(buffer, stdinBuffer, stdin);
    		//print stdin
		printf("FILE:-------------------------------------------------------------------\n");
    		printf("%s", buffer);
		printf("------------------------------------------------------------------------\n");
		//parse for char
		for( i = 0; i < 1024; i++){	
        		if (buffer[i] == x){
				count++;
			}
		}
	}
	//Print final count of character
	printf("'%c' Character Count: %d\n", x, count);	
	return 0;
}
