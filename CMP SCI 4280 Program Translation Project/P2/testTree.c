// Adam Henze
// // cs4280
// // Sharlee Climer
// // P2
// // 4/10/2024

#include "scanner.h"
#include "parser.h"
#include "node.h"
#include <stdio.h>
#include "token.h"
#include <stdlib.h>

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

void testTree(node_t* node){
	print(node,1);
}
