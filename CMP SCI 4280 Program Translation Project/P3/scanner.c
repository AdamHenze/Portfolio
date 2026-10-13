// Adam Henze
// cs4280
// Sharlee Climer
// P3
// 4/12/2024

#include "scanner.h"
#include "token.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <ctype.h>
#include <string.h>

//proto for conversion func
int setCol (char);

//set line number
int lineNum = 1;
//init FSA table
//found and corrected errors in HW1
int table[12][12] = {
	{0,1000,1,-1,3,5,6,8,10,-1,-1,-1},
	{-2,-2,-2,2,-2,-2,-2,-2,-2,-2,-2,-2},
	{1001,1001,1001,2,1001,1001,1001,1001,1001,1001,1001,1001},
	{-4,-4,-4,4,-4,-4,-4,-4,-4,-4,-4,-4},
	{1002,1002,1002,4,1002,1002,1002,1002,1002,1002,1002,1002},
	{1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003},
	{1003,1003,1003,1003,1003,1003,1003,1003,1003,7,1003,1003},
	{1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003},
	{1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,9,1003},
	{1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003},
	{1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,11},
	{1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003}};

//c is lookahead char
char c;
//string to build token
char* s = (char*)malloc(1024 * sizeof(char));

token_t scanner(FILE* data){

	//printf("LINE %d\n",lineNum);
	token_t token;
		
	int state = 0;
	int nextState = 0;
	int commentSwitch = 0;
	
	int nextChar; //NOTE: nextChar is the FSA column conversion of the lookahead char 'c'
	//reset s
	s = (char*)malloc(1024 * sizeof(char));
	c = fgetc(data);

	//loop while state non final
	while(state < 1000){

		//if statements control comment ignores
		//it felt appropriate to have an Error if a comment is never closed correctly
                if(c == EOF && commentSwitch == 1){
                        printf("SCANNER ERROR: UNCLOSED COMMENT AFTER LINE NUM %d",lineNum);
			exit(1);
                }
		if(c == '#'){
			//comment switch flips to stop reading until second hash encountered
			commentSwitch = 1 - commentSwitch;
			//printf("COMMENT = %d\n",commentSwitch);
			c = fgetc(data);
			//printf("%c\n",c);
			continue;
		}
		if(commentSwitch == 1){
			c = fgetc(data);
                        //printf("%c\n",c);
			continue;
		}

		//pass comment checks set next state from FSA table
		nextChar = setCol(c);		
                nextState = table[state][nextChar];

		//lookahesd to next state with c
		if(nextState >= 1000){ //codes > 1000 indicate final states
			switch(nextState){
				case 1000:
				        token.tokenID = EOFTk;
				        token.tokenString = "EOF";
				        token.lineNum = lineNum;
				        if(c != '\n'){
						fseek(data,-1,SEEK_CUR);
					} else {
						lineNum++;
					}
					return token;
					//eof
					break;
				case 1001:
                                        token.tokenID = T1;
                                        token.tokenString = s;
                                        token.lineNum = lineNum;
                                        if(c != '\n'){
                                                fseek(data,-1,SEEK_CUR);
                                        } else {
                                                lineNum++;
                                        } 
                                        return token;
					//t1
					break;
				case 1002:
                                        token.tokenID = T2;
                                        token.tokenString = s;
                                        token.lineNum = lineNum;
                                        if(c != '\n'){
                                                fseek(data,-1,SEEK_CUR);
                                        } else {
                                                lineNum++;
                                        }
                                        return token;
					//t2
					break;
				case 1003:
                                        token.tokenID = T3;
                                        token.tokenString = s;
                                        token.lineNum = lineNum;
                                        if(c != '\n'){
                                                fseek(data,-1,SEEK_CUR);
                                        } else {
                                                lineNum++;
                                        }
					return token;
					//t3
					break;
			}
		} else if(nextState < 0){ //codes below 0 indicate errors based on val
                        printf("SCANNER ERROR: DECLARATION ERROR @ LINE %d, \"%s\"\n",lineNum,s);
			switch(nextState){
				case -1:
					printf("INVALID TOKEN INITIALIZER CHARACTER\n");
					break;
				case -2:
                                        printf("INVALID T1-TOKEN CHARACTER, REQUIRES NUMERALS\n");
                                        break;
				case -4:
                                        printf("INVALID T2-TOKEN CHARACTER, REQUIRES NUMERALS\n");
                                        break;
			}
                        exit(1);
		} else if(nextState == 0){ //if nextstate == 0, meaning loop at Pos0, grab more chars
			if(c == '\n'){ //if new line found increment linenum
				lineNum++;
			}
                        state = nextState;
                        c = fgetc(data);
		} else { //IF IVE MADE IT HERE THEN I MUST BE A GOOD CHARACTER TO APPEND, STATE TRANSITION
                        state = nextState;
			strncat(s,&c,1);
                        c = fgetc(data);
		}
	}
	return token;
}

//function to set integer value of column FSA Table from char value
int setCol( char c ){

	//int value to store colomn conversion
	int nextChar;

	switch(c){
	        case '\n':
			nextChar = 0;
			//lineNum++; //almost incremented correctly, reimplimented elsewhere
        		break;
        	case ' ':
        	case '\t':
			nextChar = 0;
        		break;
        	case EOF:
			nextChar = 1;
        		break;
		case 'A' ... 'Z':
        	case 'a' ... 'z':
			nextChar = 2;
        		break;
        	case '0' ... '9':
			nextChar = 3;
        		break;
        	case '%':
			nextChar = 4;
        		break;
        	case '.':
        	case '!':
			nextChar = 5;
        		break;
        	case '*':
			nextChar = 6;
        		break;
        	case '?':
			nextChar = 7;
        		break;
        	case ',':
			nextChar = 8;
        		break;
        	case '"':
			nextChar = 9;
        		break;
        	case '$':
			nextChar = 10;
        		break;
        	case ';':
			nextChar = 11;
        		break;
		case '#':
			break;
		default: //NOTE: IF IM DEFAULTING THEN I MUST NOT BE AN ACCEPTABLE CHAR, ERROR
        		if(c > 0){
			printf("SCANNER ERROR: INVALID CHARACTER @ LINE %d, \"%c\" in \"%s\"\n", lineNum + 1, c,s);
			exit(1);
			}
			break;
		}
	return nextChar;
}
