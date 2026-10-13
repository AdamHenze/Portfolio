// Adam Henze
// cs4280
// Sharlee Climer
// P0
// 2/10/2024

#include "node.h"
#include "traversals.h"
#include "buildTree.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char* argv[]) {
			
        int check = 0;			// checker int for various needs
	FILE *fp = NULL;		// file pointer for input
	FILE *data = NULL;		// file pointer for temp data file
	char c;				// char for file parsing
	int i;				// counter
	const int stdinBuffer = 1024;	// buffer size
        char buffer[stdinBuffer];	// buffer for stdin input

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

	// final check, if pointer empty then bad input
        if(fp == NULL){
                printf("NO FILE OR STDIN DETECTED\n");
                return 1;
        } else { //else parse check for alhpanumeric and whitespace only
		rewind(fp);
		c = fgetc(fp);
        	while (c != EOF) {
        	        if(!isalnum(c) && !isspace(c)){
				printf("ERROR: NON ALPHANUMERIC CHARACTERS FOUND IN FILE\n");
				fclose(fp);
				fclose(data);
				remove("tempdata.txt");
				remove("tempfile.txt");
				return 1;
			} else if(isalnum(c)){
				// write chars of input to temp data
				fputc(c,data);
				// check used to store if previous char was space, prevents duplicate newlines
				check = 0;
			} else if(isspace(c) && check == 0){
				// if whitespace and check good, insert /n after token
				fputc('\n',data);
				check = 1;
			}
			// advance c
			c = fgetc(fp);
        	}
	}
	// data cleaned into rows save open for read
	fclose(data);
	data = fopen("tempdata.txt" , "r");

	// check for cap in every string
	// checks lines of cleaned data for atleast one CAP, each line being one token
        while(fgets(buffer, stdinBuffer, data) != NULL){
		// reset check
		check = 0;
		for(i = 0; i < (int)strlen(buffer); i++){
			if(isupper(buffer[i])){
				// found CAP check good
				check++;
			}
		}
		// no caps found on line
		if(check == 0){
			printf("ERROR: ALL STRINGS IN FILE REQUIRE ONE OR MORE CAPITAL ALPHA CHARACTER\n");
			return 1;
		}

        }

	// rewind pointer send to functions
	rewind(data);
	// build tree with cleaned data file
	node_t *root = buildTree(data);

	// if returns null then error
	if(root == NULL){
		printf("ERROR BUILDING TREE: CHECK DATA\n");
		return EXIT_FAILURE;
	}
	
	// pointer to store file output names and changes
	char* fileIn = NULL;
	char* fileOut = NULL;

	// if file name found then set size based on argv
	if(argc > 1){
		fileIn = (char*)malloc((strlen(argv[1])+1)*sizeof(char));
		fileOut = (char*)malloc((strlen(argv[1]) + 100)*sizeof(char));
	}else{
	// no file, stdin input, make reasonable buffer for file names
		fileIn = (char*)malloc((100)*sizeof(char));
		fileOut = (char*)malloc((100)*sizeof(char));
	}

	// checl for malloc error
	if(fileIn == NULL || fileOut == NULL){
		printf("MEMORY ALLOCATION ERROR\n");
		return 1;
	}

	// if file rename with argv
	if(argc > 1){
		strcat(fileIn, argv[1]);
	// no file rename to out
	}else{
		strcat(fileIn, "out");
	}


	// tree parse grouings
	// name file, remove previous versions of same name, write file 
	// In Order 
	strcat(fileOut, fileIn);
	strcat(fileOut, ".inorder");
        printf("Writing %s\n", fileOut);
	remove(fileOut);
	traverseInOrder(root, 0, fileOut);

	// PreOrder 
	strcpy(fileOut, "");
        strcat(fileOut, fileIn);
        strcat(fileOut, ".preorder");
	printf("Writing %s\n", fileOut);
        remove(fileOut);
	traversePreOrder(root, 0, fileOut);

	// Level Order
        strcpy(fileOut, "");
        strcat(fileOut, fileIn);
        strcat(fileOut, ".levelorder");
	printf("Writing %s\n", fileOut);
        remove(fileOut);
	traverseLevelOrder(root, fileOut);

	// free file name mallocs, run cleaner func to free tree memory
	free(fileIn);
	free(fileOut);
	cleaner(root);

	// close and remove temp files
	fclose(fp);
	fclose(data);
	remove("tempfile.txt");
	remove("tempdata.txt");

	// holy cow we made it, Exit success
	printf("EXIT_SUCCESS\n");
	return EXIT_SUCCESS;
};
