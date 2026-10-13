#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "help.h"

//Adam Henze
//Cs2750 Summer 2023
//Project4

//buffer for stdin store
#define stdinBuffer 1024

//begin main
int main(int argc, char** argv){

	FILE *fp = NULL;	//file
	int i, j;		//counter for loops
	int arrsize = argc - 2;	//useful int for dynamic memory alloc
	int check = 19;		//value to check for pairs	
	int count1 = 0;		//counter for pairs
	int argcheck = 3;	//check for # of arguments
	int childStatus;	//int for child status
	
	// Check if file exists
	fp = fopen(argv[1], "w");
	if (fp == NULL){ 
		printf("Could not open file %s\n", argv[1]);
		return 0;
	}
	
	//check args
	//this hard-coding the help option is due to getopt not liking negative ints
	for(i = 0; i < argc; i++){
		//printf("ARG %d : %s\n", i, argv[i]);
		if(strcmp( argv[i], "-h") == 0){
			help();
			return 0;
		}
		// To challenge myself i added another option '-n'
		// '-n' will take the next integer and use that as the number to match pairs too
		// it will not store the new check in dynamic memory
		if(strcmp( argv[i], "-n") == 0){
			//check for args after -n
			argcheck += 2;
			if(i == argc - 1){
				printf("Error: No int after '-n'. Syntax: '-n #'\n");
				return 1;
			}
			if(intcheck(argv, i + 1) == false){
				printf("Bad input after '-n'\n");
				return 1;
			}
			//if found set the next int value to check
			check = atoi(argv[i + 1]);
			//if we find this new option we can decrement dynamic mem size by 2, 
			arrsize -= 2;
			
		}
	}	
	//check for enough args
	if(argc < argcheck){
		printf("Not enought arguments.\n");
		return 1;
	};

	// check all arguments past file for type int	
	// loop through arguments
	for(i = 2; i < argc; i++){
		// loop through arg string
		if(strcmp( argv[i], "-n") == 0){
			continue;
		}

		if(intcheck(argv, i) == false){
			printf("Non Integer arguments Error\n");
			return 1;
		}
	}
	//pass checks, move on to fork/wait

//-----------------------------------------------------------------------------------------------------
	
	pid_t childPid = fork();

	//create dynamic memory of proper size
	//this was stored above as arrsize
	//arrsize is decremented based on options for proper memory size
	if(childPid == 0){
		int * numarr;
		numarr = malloc(sizeof(int) * (arrsize));
		//check for memory allocation
		if(numarr <= 0){
			printf("Could not allocate memory");
			return 1;
		}
		
		//fprintf(fp,"arrsize: %d\n", arrsize);
		fprintf(fp,"checking for number pair: x + y = %d\n", check);
		fprintf(fp,"Array: ");
		//parse the values of argv, turn to int, save into dynamic array
		for(i = 0; i < argc - 2; i++){
			//BIG SCARY IF STATEMENT
			//all this does is check for the current argument and previous argument to be '-n'
			//if im not '-n', and the guy behind me isnt '-n', then i must be good to store
			//note: we use i+2 to skip script and file arg
			if((strcmp( argv[i + 2], "-n") != 0) && (strcmp( argv[i + 1], "-n") != 0)){
				//if valid argument convert to int and store in numarr
				numarr[count1] = atoi(argv[i + 2]);
				fprintf(fp,"%d ", numarr[count1]);
				count1++;
			}
		
		}
		fprintf(fp,"\n");
	
		//Dude, I cant believe all of my parsing of argv and matching of stored ints worked first time
		//Marks videos were very informative on the subject
	
		//setup parse of numarr to check for matches at check value
		int matchcount = 0;
		for(i = 0; i < arrsize; i++){
			// set 'a' to current num
			int a = numarr[i];
			// parse rest of numarr
			for(j = i + 1; j < arrsize; j++){
				// set 'b' to next num
				int b = numarr[j];
				//if a + b = check value then good pair
				if( a + b == check){
					fprintf(fp,"Pair: (%d + %d = %d)\n", a, b, check);
					matchcount++;
				}
			}
		}
		//print child pid, free mem, return based on matches	
		fprintf(fp,"Child PID: %d\n", getpid());
		free(numarr);
		if(matchcount < 1){
			return 1;
		}else{
			return 0;
		}
	}else {
		//wait for child
		wait(&childStatus);
		//write exit status to file
		if(WIFEXITED(childStatus)){
			fprintf(fp,"Parent PID: %d\n", getpid());
			if(WEXITSTATUS(childStatus) == 0){
				fprintf(fp,"EXIT_SUCCESS\n");
			}
			if(WEXITSTATUS(childStatus) == 1){
				fprintf(fp,"No Matching Pairs\n");
				fprintf(fp,"EXIT_FAILURE\n");
			}
		}
	}
	//THANKS!	
	return 0;
}
