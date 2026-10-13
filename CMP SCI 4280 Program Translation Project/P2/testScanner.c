// Adam Henze
// cs4280
// Sharlee Climer
// P1
// 3/6/2024

#include "testScanner.h"
#include "scanner.h"

#include <stdio.h>
#include "token.h"
#include <stdlib.h>

//string array to convert enum of token into output
char* tokenNames[] = {"T1 Token","T2 Token","T3 Token","EOFTk"};

void testScanner(FILE* data){
	token_t token;
	
	// while not returning EOF keep geting tokens, Kept it simple here, everything handled in scanner
	while( token.tokenID != EOFTk ){
		//printf("TESTER\n");
		token = scanner(data);	
		printf("\t%s\t\"%s\"\t%d\n", tokenNames[token.tokenID], token.tokenString, token.lineNum);
	}
}
