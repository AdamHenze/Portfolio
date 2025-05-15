// Adam Henze
// // cs4280
// // Sharlee Climer
// // P3
// // 4/12/2024

#include "scanner.h"
#include "parser.h"
#include "node.h"
#include <stdio.h>
#include "token.h"
#include <stdlib.h>

//I just decided to highjack the node design we already made to make a semantics list
node_t* semanticsTree;

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
		printf("ERROR, NO DECLARATION %s\n", node->children[1]->node_strings[0]);
		exit(1);
	}else if(node->node_char == 'F' && node->children[0]->node_char == '2'){// if i am an F node AND my child is a tk2, then check the child string for being declared
                while(semanticsTree->children[k] != NULL){
                        if(strcmp(semanticsTree->children[k]->children[0]->node_strings[0],node->children[0]->node_strings[0])==0){
                                return;
                        }
                        k++;
                }
                printf("ERROR, NO DECLARATION %s\n", node->children[0]->node_strings[0]);
		exit(1);
        }
}


void testTree(node_t* node){
	print(node,1);
}

//the use of a wrapper function allowed me to not worry about semantics tree leaving file
void semantics(node_t* root){
	//printf("CHECK1\n");
	semanticsTree = (node_t*)malloc(sizeof(node_t));
	checkSemantics(root);
        //printf("CHECK->PRINT\n");
	printSemantics(semanticsTree);
        //printf("CHECKDONE\n");
}


