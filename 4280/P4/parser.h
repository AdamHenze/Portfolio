// Adam Henze
// cs4280
// Sharlee Climer
// P4
// 5/4/2024

#ifndef PARSER_H
#define PARSER_H 

#include "cstdio"
#include "token.h"
#include "node.h"

node_t* parser(FILE*);
void print(node_t*, int);
void addChild(node_t*, node_t*);

node_t* Tk1();
node_t* Tk2();
node_t* Tk3();

node_t* S();
node_t* A();
node_t* B();
node_t* C();
node_t* D();
node_t* E();
node_t* F();
node_t* G();
node_t* H();
node_t* J();

#endif
