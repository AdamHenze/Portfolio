// Adam Henze
// cs4280
// Sharlee Climer
// P0
// 2/10/2024

#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

const int ARRSIZE = 100;

typedef struct node_t{

	// node key char
	char node_char;
	// counter stores string count
	int node_counter = 0;
	// string array
	char* node_strings[ARRSIZE];
	// children pointers
	node_t *left_child, *right_child;

} node_t;

#endif
