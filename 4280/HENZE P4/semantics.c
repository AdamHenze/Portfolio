// Adam Henze
// // cs4280
// // Sharlee Climer
// // P5
// // 5/4/2024

#include "scanner.h"
#include "parser.h"
#include "node.h"
#include <stdio.h>
#include "token.h"
#include <stdlib.h>
#include <ctype.h>

//I just decided to highjack the node design we already made to make a semantics list
node_t* semanticsTree;
int loopCounter = 0;

//print tree, used for debug
void print(node_t* node, int level){
        int j = 0;
        int k = 0;
        printf("%c\n",node->node_char);
        while(node->children[j] != NULL){
                printf("%*s", level*4,"");
                print(node->children[j], level + 1);
                j++;
        }
        while(node->node_strings[k] != NULL){
                printf("%*s", level*4,"");
                printf("%s\n",node->node_strings[k]);
                k++;
        }
}

//print semantics
void printSemantics(node_t* node){
        int j = 0;
	//run through the semantics list 
        while(node->children[j] != NULL){
                printSemantics(node->children[j]);
                j++;
        }
	//if I have strings and I am a tk2 node, then print my string, all stored will meet this
        if(node->node_strings[0] && node->node_char == '2')
		printf("VARIABLE DECLARATION: %s\tLINE: %d\n",node->node_strings[0], node->lineNum);
}

//check proper semantics
void checkSemantics(node_t* node){
        int j = 0;
        int k = 0;
        while(node->children[j] != NULL){
                checkSemantics(node->children[j]);
                j++;
        }
	if(node->node_char == 'C'){// IF i am a C node, the only assigner, then check for matches with my first childs string
				   // if no matches then store new variable
		//check for duplicate
		while(semanticsTree->children[k] != NULL){
			if(strcmp(semanticsTree->children[k]->children[0]->node_strings[0],node->children[0]->node_strings[0])==0){
				printf("ERROR, DUPLICATE DECLARATION %s\n",node->children[0]->node_strings[0]);
				exit(1);
			}
			k++;
		}
		//add
		addChild(semanticsTree ,node);

	}else if(node->node_char == 'B'){// IF i am a B node, check the string of my second child, a tk2, for being declared
                while(semanticsTree->children[k] != NULL){
                        if(strcmp(semanticsTree->children[k]->children[0]->node_strings[0],node->children[1]->node_strings[0])==0){
                                return;
                        }
			k++;
                }
		addChild(semanticsTree ,node);
		//printf("ERROR, NO DECLARATION %s\n", node->children[1]->node_strings[0]);
		//exit(1);
	}else if(node->node_char == 'F' && node->children[0]->node_char == '2'){// if i am an F node AND my child is a tk2, then check the child string for being declared
                while(semanticsTree->children[k] != NULL){
                        if(strcmp(semanticsTree->children[k]->children[0]->node_strings[0],node->children[0]->node_strings[0])==0){
                                return;
                        }else if(strcmp(semanticsTree->children[k]->children[1]->node_strings[0],node->children[0]->node_strings[0])==0){
				return;
			}
                        k++;
                }
                printf("ERROR, NO DECLARATION %s\n", node->children[0]->node_strings[0]);
		exit(1);
        }
}

// Generator function
// giant switch case to check node character value from BNF
// generate assembly based on node char while performing preorder travers
// PLEASE SEE PARSER FOR DETAILED NODE BREAKDOWNS AND PATHS
void generator(FILE* file, node_t* node){
	switch(node->node_char){//check node char for code insertions
		case 'S':
	                generator(file, node->children[0]);
	                generator(file, node->children[1]);
	                fprintf(file,"STOP\n");
			break;
		case 'A':// either return sum or number, leave in acc
			if(node->children[1]->node_char == '3'){// A -> F.
	                        fprintf(file,"LOAD ");
				generator(file, node->children[0]);
				fprintf(file,"\n");
			}else{// A -> F + F -> F F ?$
				fprintf(file,"LOAD ");	
                                generator(file, node->children[0]);
				fprintf(file,"\n");
				fprintf(file,"ADD ");
                                generator(file, node->children[1]);
                                fprintf(file,"\n");
			}
			break;
		case 'B':// assign val to var
			generator(file, node->children[2]);
			node->children[1]->node_strings[0][0] = 'v';
			fprintf(file,"STORE %s\n", node->children[1]->node_strings[0]);
			break;
		case 'C':// read in val to  var
			node->children[0]->node_strings[0][0] = 'v';
			fprintf(file,"READ %s\n", node->children[0]->node_strings[0]);
			break;
		case 'D':// recursion, generates no code directly
			if(node->node_counter > 0){
				break;
			}
                        	generator(file, node->children[0]);
				generator(file, node->children[2]);
			break;
		case 'E':// E, IF or FOR see lines for break down
			if(strcmp(node->children[0]->node_strings[0], ",") == 0){
				generator(file, node->children[1]);// first A in acc
                        	fprintf(file,"STORE x\n");// store first A
				generator(file, node->children[2]);// second A in acc
				fprintf(file,"SUB x\n");// sub first A
				fprintf(file,"BRPOS Skip\n");// If we have a positive value then int1 was smaller than int2, so skip
				generator(file, node->children[3]); // H
				fprintf(file,"Skip: NOOP\n");// skip ( IF )
			}else if(strcmp(node->children[0]->node_strings[0], ",;") == 0){
				loopCounter++;//counter to store number of loops incase nested or else
				fprintf(file,"LOAD ");
				generator(file, node->children[1]);//load value to loop for i
				fprintf(file,"\n");
				fprintf(file,"STORE i%d\n", loopCounter);//store in var i#
				fprintf(file,"Loop%d: NOOP\n", loopCounter);//loop checkpoint
				generator(file, node->children[2]);//generate code within loop
				fprintf(file,"LOAD i%d\n", loopCounter);//load counter
				fprintf(file,"SUB 1\n");//decrement
				fprintf(file,"STORE i%d\n", loopCounter);//save
				fprintf(file,"BRPOS Loop%d\n", loopCounter);//check for loop, break on pos
			}
			break;
		case 'F':// F returns values or variable identifiers
			if(node->children[0]->node_char == '1'){//if node char is TK1 then int
				if((isupper(node->children[0]->node_strings[0][0])) == 0){//check for upper
					node->children[0]->node_strings[0][0] = '-';//lower then set -
					fprintf(file,"%s",node->children[0]->node_strings[0]);
				}else{
					fprintf(file,"%s",node->children[0]->node_strings[0] + 1);//upper fprint val
				}
			}else{
                                node->children[0]->node_strings[0][0] = 'v';//if ident then set sting[0] to v to match variable declares in 'C'
                                fprintf(file,"%s",node->children[0]->node_strings[0]);
			}
			break;
		case 'H':
                        if(node->node_counter > 0){//if string counter > 0 then signifies "EMPTY" as a string in node
                                break;
                        }
			if(node->children[1]->node_char == '3'){//generate for E or G
                        	generator(file, node->children[0]);
			}
			break;
                case 'G':
                        generator(file, node->children[0]);//Easy, move to next child
                        break;
		case 'J':
			generator(file, node->children[1]);//get val in acc
			fprintf(file,"STORE write\n");//store to temp write var
			fprintf(file,"WRITE write\n");//write write var
			break;
		default:
			break;
	}
}

//wrapper to run generator recursion and file setup
void generateCode(node_t* node){
	int i;
        FILE* file;
        file = fopen("OUTPUT.asm", "w");//file output
        fprintf(file,"STORE write\n");//temp vars init
	fprintf(file,"STORE x\n");
	generator(file,node);//start generator
	while(semanticsTree->children[i] != NULL){//clear out vars in semantics tree
		if(semanticsTree->children[i]->node_char == 'C'){
			fprintf(file,"%s 0\n", semanticsTree->children[i]->children[0]->node_strings[0]);
		}else{
			fprintf(file,"%s 0\n", semanticsTree->children[i]->children[1]->node_strings[0]);
		}
		i++;
	}	
	while(loopCounter > 0){//clear out loop counters
		fprintf(file,"i%d 0\n",loopCounter);
		loopCounter--;
	}
	fprintf(file,"write 0\n");//clear temp vars
	fprintf(file,"x 0\n");
	fclose(file);
	printf("GENERATOR EXIT SUCCESS\n");
}

void testTree(node_t* node){
	print(node,1);
}

//the use of a wrapper function allowed me to not worry about semantics tree leaving file
void semantics(node_t* root){
	semanticsTree = (node_t*)malloc(sizeof(node_t));
	checkSemantics(root);
}


