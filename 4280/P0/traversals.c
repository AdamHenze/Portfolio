// Adam Henze
// cs4280
// Sharlee Climer
// P0
// 2/10/2024

#include "traversals.h"

#include <stdio.h>
#include "node.h"
#include <stdlib.h>

// function protos
int treeHeight(node_t*);
void printCurrentLevel(node_t*, int, int, char*);

// level order traversal
void traverseLevelOrder(node_t* root, char* fileName){
	// find initial tree height with helper func
	int height = (treeHeight(root));
	int i;
	// increment i up to tree height, each increment increases the level walked down to printing
	for( i = 1; i <= height; i++ ){
		printCurrentLevel(root, i, 0, fileName);
	}
};

// pre order traversal
void traversePreOrder(node_t* root, int level, char* fileName){
	// open file for writing based on input 
	FILE* file = fopen(fileName, "a");

        if (root != NULL) {
		// write to file, indent based on level
                fprintf(file,"%*s%d: ", level*4,"" , level);
                fprintf(file,"%c: ", root->node_char);
                // loop tokens to print
		for(int i = 0; i < root->node_counter; i++){
                        fprintf(file,"%s ", root->node_strings[i]);
                }
                fprintf(file,"\n");
		// recursion after node print, node PRE childrem
                traversePreOrder(root->left_child, level + 1, fileName);
                traversePreOrder(root->right_child, level + 1, fileName);
        }
	fclose(file);
};

// in order traversal
void traverseInOrder(node_t* root, int level, char* fileName){
	// open file for writing based on input
        FILE* file;

	if (root != NULL) {
		
		// recursive left
		traverseInOrder(root->left_child, level + 1, fileName);

		// print node
		file = fopen(fileName, "a");
		fprintf(file,"%*s%d: ", level*4,"" , level);
		fprintf(file,"%c: ", root->node_char);
                for(int i = 0; i < root->node_counter; i++){
                        fprintf(file,"%s ", root->node_strings[i]);
                }
                fprintf(file,"\n");
		fclose(file);

		// recursive right, left node right, IN order
		traverseInOrder(root->right_child, level + 1, fileName);
	}
};

// function to return tree height based on longest walk of nodes
int treeHeight(node_t* node){
	if(node == NULL){
		return 0;
	} else {
		// recursively walk nodes to find longest walk
		int lh = treeHeight(node->left_child);
		int rh = treeHeight(node->right_child);
		
		// check left or right for longest and return
		if( lh > rh ){
			return lh + 1;
		} else {
			return rh + 1;
		}
	}
};

// descends node levels until current level == 1 and prints current level
void printCurrentLevel(node_t* node, int level, int depth, char* fileName){
        FILE* file;
	if(node == NULL){
		return;
	}
	// if current level is 1 then right data to file
	if(level == 1){
		file = fopen(fileName, "a");
                fprintf(file,"%*s%d: ", depth*4,"" , depth);
                fprintf(file,"%c: ", node->node_char);
                for(int i = 0; i < node->node_counter; i++){
                        fprintf(file,"%s ", node->node_strings[i]);
                }
                fprintf(file,"\n");
		fclose(file);
	} else if ( level > 1 ){ 
		// if initially given a value > 1, walk down till level decrements to 1
		// depth increments top print node depth
		printCurrentLevel(node->left_child, level - 1, depth + 1, fileName);
		printCurrentLevel(node->right_child, level - 1, depth + 1, fileName);
	}
};

// cleaner walks nodes freeing memory
void cleaner(node_t* node){
	if(node == NULL)
		return;
	cleaner(node->left_child);
	cleaner(node->right_child);

	free(node);
};

