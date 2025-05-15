// Adam Henze
// cs4280
// Sharlee Climer
// P4
// 5/4/2024

#include "scanner.h"
#include "parser.h"
#include "node.h"

#include <stdio.h>
#include "token.h"
#include <stdlib.h>

extern char* tokenNames[];
token_t token;
FILE* data;
int i;

//add child, attaches child to parent node
//NOTE: the use of addChild is what runs bnf functions and adds nodes as needed
void addChild(node_t* parent,node_t* child){
	if(parent == NULL){
		printf("NULL P\n");
		exit(1);
	}
        if(child == NULL){
                printf("NULL C\n");
                exit(1);
        }
	size_t nchild = 0;
	if(parent->children != NULL){
		for(i = 0; i < 10; i++){
			if(parent->children[i] == NULL)
				break;		
			nchild++;
		}
	}	
	parent->children[nchild] = child;
	return;	
}

//SWEET JESUS ITS WORKING DONT TOUCH IT DONT TOUCH IT DONT TOUCH IT
node_t* parser(FILE* file){
	node_t* root = (node_t*)malloc(sizeof(node_t));
	data = file;
	token = scanner(data);
	//printf("PARSER\n");
	//printf("================\n");
	root = S();
	return root;	
}

// FINAL TOKEN FUNCTIOINS, ALL SIMILAR, Check and store
node_t* Tk1(){
        node_t* node = (node_t*)malloc(sizeof(node_t));//new node
        node->node_char = '1';//node int represents toke type 1 == token type 1
	if(token.tokenID != T1){//check type
		printf("Error: T1 token call\n");//errors
		printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
		exit(1);
	}
        node->node_strings[node->node_counter] = token.tokenString;//store string
	node->lineNum = token.lineNum;
        node->node_counter++;//increment node counter if more strings stored
	return node;
}

node_t* Tk2(){
        node_t* node = (node_t*)malloc(sizeof(node_t));
        node->node_char = '2';
        if(token.tokenID != T2){
                printf("Error: T2 token call\n");
                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                exit(1);
        }
        node->node_strings[node->node_counter] = token.tokenString;
        node->lineNum = token.lineNum;
        node->node_counter++;
        return node;
}

node_t* Tk3(){
        node_t* node = (node_t*)malloc(sizeof(node_t));
        node->node_char = '3';
        if(token.tokenID != T3){
                printf("Error: T3 token call\n");
                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                exit(1);
        }
        node->node_strings[node->node_counter] = token.tokenString;
        node->lineNum = token.lineNum;
        node->node_counter++;
        return node;
}

//PARSER
//every function enters with the token it intends to check already primed
//every function should leave with all its tokens consumed
node_t* S(){// S -> C D
        node_t* node = (node_t*)malloc(sizeof(node_t));
	node->node_char = 'S';//set node char

        //printf("%s\n",token.tokenString);

	addChild(node,C());//uses add child function to attach child nodes
	//token = scanner(data);//get next token for D
        //printf(token.tokenString);

	addChild(node,D());
        if(token.tokenID != EOFTk){//If not EOF at end of parse we didnt reach file end, error
                printf("Error: S EOF call\n");
                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                exit(1);
        }
	return node;
}

node_t* A(){// A -> F F ?$ || F .
        node_t* node = (node_t*)malloc(sizeof(node_t));
        node->node_char = 'A';
	addChild(node,F());//get first F
	if(strcmp(token.tokenString,".") == 0){ // if next token . then predect F.
                addChild(node,Tk3());
	        token = scanner(data); // consume .
		return node;
	}
	addChild(node,F());// else get next F
        if(strcmp(token.tokenString,"?$") != 0){//if not ?" after then error
                printf("Error: A ?$ call\n");
                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                exit(1);
        }
	addChild(node,Tk3());
	token = scanner(data); // consume ?$
	return node;
}

node_t* B(){// B -> . Tk2 A !
        node_t* node = (node_t*)malloc(sizeof(node_t));
        node->node_char = 'B';
        if(strcmp(token.tokenString,".") != 0){// check for .
                printf("Error: B . call\n");
                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                exit(1);
        }
        addChild(node,Tk3());
        token = scanner(data);
        if(token.tokenID != T2){// check for tk2
                printf("Error: B T2 call\n");
                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                exit(1);
        }
        addChild(node,Tk2());
	token = scanner(data);//get next then run A
	addChild(node,A());
        if(strcmp(token.tokenString,"!") != 0){//check for !
                printf("Error: B ! call\n");
                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                exit(1);
        }
        addChild(node,Tk3());
        token = scanner(data);
	return node;
}

node_t* C(){// C -> tk2 *
	node_t* node = (node_t*)malloc(sizeof(node_t));
        node->node_char = 'C';
	if(token.tokenID != T2){//check for tk2
                printf("Error: C T2 call\n");
                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                exit(1);
	}
	addChild(node,Tk2());	
     	token = scanner(data);
        if(strcmp(token.tokenString,"*") != 0){//check for *
        printf(token.tokenString);
                printf("Error: C * call\n");
                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                exit(1);
        }
	addChild(node,Tk3());
	token = scanner(data);
	return node;
}

node_t* D(){// D -> H ? D || empty

	//NOTE: 
	//D -> D H ? | e    remove lhr
	//
	//D -> e D'
	//D'-> H ? D' || e
	//
	//simplifies
	//D -> H ? D || e 

        node_t* node = (node_t*)malloc(sizeof(node_t));
        node->node_char = 'D';
	if(token.tokenID != EOFTk){ // NOT NULL
		addChild(node,H());//check H
	        if(strcmp(token.tokenString,"?") != 0){//check for ?
	                printf("Error: D ? call\n");
	                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
	                exit(1);
	        }
	        addChild(node,Tk3());
		token = scanner(data);	// consume ?	
		addChild(node,D()); // check D
	}else if(token.tokenID == EOFTk){ // NULL D
                node->node_strings[node->node_counter] = "Empty";
                node->node_counter++;
	}
	return node;
}

node_t* E(){// E -> , A A H | ,; F H
        node_t* node = (node_t*)malloc(sizeof(node_t));
        node->node_char = 'E';
	if(strcmp(token.tokenString,",") == 0){//check for , or ,;
	        addChild(node,Tk3());
		token = scanner(data);//next tok
		addChild(node,A());
		addChild(node,A());
		addChild(node,H());
	}else if(strcmp(token.tokenString,",;") == 0){
	        addChild(node,Tk3());
		token = scanner(data);//next tok
		addChild(node,F());
		addChild(node,H());
	}else{
                printf("Error: E , || ,; call\n");
                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                exit(1);
	}
	return node;
}

node_t* F(){// F -> tk1 | tk2
        node_t* node = (node_t*)malloc(sizeof(node_t));
        node->node_char = 'F';
	if(token.tokenID == T1){//check tk1 or tk2 error else
		addChild(node,Tk1());
                token = scanner(data);
	}else if(token.tokenID == T2){
		addChild(node,Tk2());
                token = scanner(data);
	}else{
                printf("Error: F Tk1 || Tk2 call\n");
                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                exit(1);
	}
	return node;
}

node_t* G(){// G -> B | C | J
        node_t* node = (node_t*)malloc(sizeof(node_t));
        node->node_char = 'G';
        if(strcmp(token.tokenString,".") == 0){
		addChild(node,B());	
	}else if(token.tokenID == T2){
		addChild(node,C());
	}else if(strcmp(token.tokenString,"*\"") == 0){
		addChild(node,J());
	}else{
                printf("Error: G -> B || C || J call\n");
                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                exit(1);
	}
	return node;
}

node_t* H(){// H -> E ? || G . || e
        node_t* node = (node_t*)malloc(sizeof(node_t));
        node->node_char = 'H';
	if(strcmp(token.tokenString,"?") == 0){ // NULL H if next token is ?
                node->node_strings[node->node_counter] = "Empty";
                node->node_counter++;
	}else if(strcmp(token.tokenString,",") == 0 || strcmp(token.tokenString,",;") == 0){// predicts E
		addChild(node,E());	
	        if(strcmp(token.tokenString,"?") != 0){	//check for ?
	                printf("Error: H ? call\n");
	                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
	                exit(1);
	        }
		addChild(node,Tk3());
		token = scanner(data);	// consume ?
	}else if(strcmp(token.tokenString,".") == 0 || strcmp(token.tokenString,"*\"") == 0 || token.tokenID == T2){ //predicts G
		addChild(node,G());
                if(strcmp(token.tokenString,".") != 0){//check for .
                        printf("Error: H . call\n");
                        printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                        exit(1);
                }
		addChild(node,Tk3());
		token = scanner(data); // consume .
	}else{	//error
                printf("ERROR in H\n");
                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                exit(1);		
	}
	return node;
}

node_t* J(){// J -> *" A .
        node_t* node = (node_t*)malloc(sizeof(node_t));
        node->node_char = 'J';
        if(strcmp(token.tokenString,"*\"") != 0){//check for *"
                printf("Error: J *\" call\n");
                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                exit(1);
        }
	addChild(node,Tk3());
        token = scanner(data);// run A
	addChild(node,A());
        if(strcmp(token.tokenString,".") != 0){//check .
                printf("Error: J . call\n");
                printf("Token: %s\nLine: %d\n",token.tokenString,token.lineNum);
                exit(1);
        }
        addChild(node,Tk3());
        token = scanner(data);
	return node;
}


