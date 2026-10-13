// Adam Henze
// cs4280
// Sharlee Climer
// P4
// 5/4/2024

#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <cstring>

enum tokens{T1, T2, T3, EOFTk};

typedef struct token_t{
	enum tokens tokenID;
	char* tokenString;
	int lineNum;
} token_t;

#endif
