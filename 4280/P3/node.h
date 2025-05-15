// Adam Henze
// cs4280
// Sharlee Climer
// P3
// 4/12/2024

#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

const int ARRSIZE = 100;
const int CSIZE = 10;

typedef struct node_t{

	// node key char
	char node_char;
	// counter stores string count
	int node_counter = 0;
	// string array
	char* node_strings[ARRSIZE];
	// children pointers
	node_t *children[CSIZE];

	int lineNum;
} node_t;

#endif
