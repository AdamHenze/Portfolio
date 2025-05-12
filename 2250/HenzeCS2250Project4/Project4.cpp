#include<iostream>
#include<cstring>

using namespace std;

//class definition
class DelimiterStack
{
	private:
		struct DelimiterNode{
			//node variables
			char character;
			int lineNumber;
			int charCount;
			//pointer to next node
			DelimiterNode *next;
		};

		//define top node
		DelimiterNode *top;

	public:
		//constructor
		DelimiterStack(){
			top = nullptr;
		}

		//Destructor
		~DelimiterStack();

		//Stack Operations
		void push(char, int, int);
		void popDelimiter(char&, int &, int &);
		bool isEmpty();
};

//Destructor
DelimiterStack::~DelimiterStack(){
	//nodes to parse stack
	DelimiterNode *nodeptr = nullptr, *nextnode = nullptr;
	//position nodeptr to top
	nodeptr = top;
	//parse stack and delete while not empty
	while(nodeptr != nullptr){
		nextnode = nodeptr->next;
		delete nodeptr;
		nodeptr = nextnode;
	}
}
//push
void DelimiterStack::push(char character, int linenum, int position){

	//ptr to new node
	DelimiterNode *newnode = nullptr;

	//allocate and store delimiter data
	newnode = new DelimiterNode;
	newnode->character = character;
	newnode->lineNumber = linenum;
	newnode->charCount = position;

	if(isEmpty()){
		//set new node as top if empty
		top = newnode;
		newnode->next = nullptr;
	}
	else{
		//set new nodes next node pointer to top
		newnode->next = top;
		//set new node as top, pushing old top down on stack
		top = newnode;
	}
}
//pop
void DelimiterStack::popDelimiter(char &character, int &linenum, int &position){

	DelimiterNode *temp = nullptr;

	if(isEmpty()){
		//error on attempt to pop empty
		cout << "EMPTY STACK ERROR";
	}
	else{
		//pass out top values to variable addresses
		character = top->character;
		linenum = top->lineNumber;
		position = top->charCount;

		//set temp to next
		temp = top->next;

		//erase top
		delete top;
		//set next node, stored in temp, as new top of stack
		top = temp;
	}
}
//check empty
bool DelimiterStack::isEmpty(){
	bool state;
	//if no top then empty
	 if(!top){
		 state = true;
	 }
	 //else not empty
	 else{
		 state = false;
	 }
	 return state;
}

//main program
int main(){

	// variable declarations and initializations

	DelimiterStack mydelistack;

	char catchchar;
	int catchlinenum;
	int catchposition;

	int linenum = 1;
	int linelength;
	string currentLine = "";

	cout << "ENTER TEXT TO DELIMIT (EXIT WITH \"DONE\")\n";

	//begin main loop
	while(currentLine != "DONE"){

		cout << "PLEASE ENTER LINE #" << linenum << ":\n";
		//get new line and length
		getline(cin, currentLine);
		linelength = currentLine.length();

		//parse line for delimiters
		for(int i = 0; i < linelength; i++){
			//check for left delimiters to push
			if(currentLine[i] == char(40) || currentLine[i] == char(91) || currentLine[i] == char(123)){
				//push if found
				mydelistack.push(currentLine[i],linenum,i);
			}
			//check for right delimiters
			if(currentLine[i] == char(41) || currentLine[i] == char(93) || currentLine[i] == char(125)){

				//if right delimiter found on empty stack then error
				if(mydelistack.isEmpty()){
					cout << "Right delimiter " << currentLine[i] << " had no left delimiter: found at line " << linenum << ", char " << i + 1;
					return 0;
				}

				//pop top delimiter
				mydelistack.popDelimiter(catchchar, catchlinenum, catchposition);

				//check for three cases of matched delimiters
				if(currentLine[i] == char(41) && catchchar == char(40)){
					//characters match, do nothing
				}
				else if(currentLine[i] == char(93) && catchchar == char(91)){
					//characters match, do nothing
				}
				else if(currentLine[i] == char(125) && catchchar == char(123)){
					//characters match, do nothing
				}
				else{
					//non match error call
					cout << "Mismatched delimiter: " << catchchar << " found at line " << catchlinenum << ", char " << catchposition << " does not match to " << currentLine[i] << " found at line " << linenum << ", char " << i + 1;
					return 0;
				}
			}
		}
		//increment linenum
		linenum++;
	};

	//exit main loop check for empty stack
	if(!mydelistack.isEmpty()){
		//if not empty, whileloop to pop stack in error messages
		while(!mydelistack.isEmpty()){
			mydelistack.popDelimiter(catchchar, catchlinenum, catchposition);
			cout << "Left delimiter " << catchchar << " found at line " << catchlinenum << ", char " << catchposition << " had no right delimiter\n";
		}
	}

	return 0;
}
