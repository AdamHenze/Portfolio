// Adam Henze
// cs4280
// Sharlee Climer
// P0
// 2/10/2024

#ifndef TRAVERSALS_H
#define TRAVERSALS_H 

#include "node.h"

// additional cleaner function used by main
void traverseLevelOrder(node_t*, char*);
void traversePreOrder(node_t*, int, char*);
void traverseInOrder(node_t*, int, char*);
void cleaner(node_t*);

#endif
