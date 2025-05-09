// Adam Henze
// cs4280
// Sharlee Climer
// P0
// 2/10/2024

#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <cstring>

enum tokens{T1, T2, T3, EOFTk};

typedef struct token_t{
	enum tokens tokenID;
	char* tokenString;
	int lineNum;
} token_t;

#endif
