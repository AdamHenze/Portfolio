// Adam Henze
// cs4280
// Sharlee Climer
// P0
// 2/10/2024

#include "buildTree.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <ctype.h>
#include <string.h>

// insert proto
node_t* insert(node_t*, char, char*);

// main func to build tree
node_t* buildTree(FILE* data){

	int count = 0; 		// counters
	int i = 0;
	int j = 0;
	char c;			// parser char
	int lineCounter = 0; 	// counts lines, each individual tokens
	int bufferCounter = 0;	// buffer size tracker
	int bufferSize = 0;	// final buffer size, based on largest token

	// parse file to set size token array and buffer based on total tokens and largest token
	for(c = getc(data); c != EOF; c = getc(data)){
		if( c == '\n' ){
			// if char is \n then new token
			lineCounter++;
			// reset buffer counter to count next token length
			bufferCounter = 0;
			continue;
		}
		// increment buffer counter on alphanum
		bufferCounter++;
		// set buffer size based on largest buffercount found
		if(bufferCounter > bufferSize){
			bufferSize = bufferCounter;
		}
	}

	// reset file pointer
	rewind(data);

	// final declares for token info
	char key;
	char *tokens[lineCounter];
	char buffer[bufferSize + 1];

	//while lines remain in data file, store to buffer, make token
        while(fgets(buffer, sizeof(buffer) + 1, data) != NULL){
		//strip newlines from data
		buffer[strlen(buffer) - 1] = '\0';
		//allocate token memory
		tokens[count] = (char*)malloc((strlen(buffer))*sizeof(char));

        	// check for bad token malloc
        	if(tokens[count] == NULL){
                	printf("MEMORY ALLOCATION ERROR\n");
				exit(1);
                        	return NULL;
        	}
		
		//copy buffer to token
		strcpy(tokens[count], buffer);
		count++;
	}		

	// create root of tree
	node_t *root = NULL;

	// no tokens bad file send back null to error out
	if(count == 0){
		exit(1);
		return NULL;
	}

	// NODE INSERTION LOOP
	// for number of tokens
	for(i = 0; i < count; i++){
		// parse token to find first capital alpha
		for(j = 0; j < (int)strlen(tokens[i]); j++){
			if(isupper(tokens[i][j])){
				key = tokens[i][j];
				// break on found
				break;
			}
		}
		// if is null then return insert node pointer directly to root
		if(root == NULL){
			root = insert(root, key, tokens[i]);
		}else{
			// if root not null insert at root
			insert(root,key,tokens[i]);
		}
	}
	// return root node back to main for traversals
	return root;
};

// node insertion function
node_t* insert(node_t* node, char key, char* token){
	// in node is null then make a temp node and return its location
	if(node == NULL){
		node_t* tempnode = (node_t*)malloc(sizeof(node_t));
		// set node KEY as char of its first insertion
		tempnode->node_char = key;
		// set first node token as input token
		tempnode->node_strings[0] = token;
		// increment counter for next token position
		tempnode->node_counter++;

		// check malloc
		if(tempnode == NULL){
			printf("MEMORY ALLOCATION ERROR\n");
			exit(1);
			return NULL;
		}
		// return node pointer
		return tempnode;
	}else if(key == node->node_char ){ // if matching key char then store token and increment counter
		node->node_strings[node->node_counter] = token;
		node->node_counter++;
	}else if(key < node->node_char ){ // if key lesser then left child recursion
		node->left_child = insert(node->left_child, key, token);
	}else if(key > node->node_char ){ // if key greater then right child recursion
                node->right_child = insert(node->right_child, key, token);
	}
	return node; // return node pointer
};
