//Adam Henze
//CS2250
//5/5/2023

#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<cstring>
#include<limits>
#include<iomanip>

using namespace std;

//node structure to store strings and count
struct node
{
	string data;
	int count;
	node *left;
	node *right;
};

//function prototypes
void showState(ifstream &);
void getinput(ifstream &, int &, int &);
node* makenode(string);
node* insert(node*,string);
void display(node*, int);

//begin main
int main(){

	//testchar used to store character of current posistion in file
	char testchar;
	//k used to store max subsequence length, named k as specified in ruberic
	int k;
	//index used to store current position in file
	int index = 0;
	//offset is used to offset the index position if a nonalpha char is found while building sequences
	int offset;
	//arrayoffset is used to offset the position in sequence array, to populate sequences incrementally
	int arrayoffset;
	//filesize is used to store the maximum size of the file
	int filesize;

	//node pointer to root
	node* root = nullptr;

	//open file as input only
	ifstream inputfile;

	//call get input to populate file and its size and k
	getinput(inputfile, k, filesize);

	//Create an array of strings at size k
	//Since we know the max sequence length the array only needs to store that many possible strings
	string tempsequencearray[k];



	//begin to parse file
	//file is only parsed once, getting all potential sequences on every new index
	//if bad index char then loop to next index until a good position is found
	//this is done to prevent duplicate readings of sequences on bad index
	for(int i = 0; i < filesize; i++){

		//Before any actions check for good stream, throw and show error if bad
		if(!inputfile.good()){
			cout << "\n---AN ERROR HAS OCCURED---\n";
			showState(inputfile);
			return 0;
		}


		//reset offsets
		offset = 0;
		arrayoffset = 0;
		//seek to updated index of file
		inputfile.seekg(index, ios::beg);
		//get char of index to text
		inputfile.get(testchar);

		//set temp array strings to blank inorder to store new data
		for(int i = 0; i < k; i++){
			tempsequencearray[i] = "";
		}

		//test current index for good char
		//if bad then increment index and loop
		if(isalpha(testchar)){

			//begin array population loop
			while(arrayoffset < k){

				//if the index + offset seeks to a position beyond the filesize then break loop
				//if seeking beyond filesize then weve already grabbed all data for this pass
				if((index + offset) > filesize - 1){
					//this will break the while loop of populating strings
					//but will still allow primary for-loop to seek for smaller final sequences
					break;
				}

				//seek to index + offset, on first pass offset is 0
				inputfile.seekg(index + offset, ios::beg);
				//get character at current position
				inputfile.get(testchar);
				//if good char, which was guaranteed on first try by index check
				//append char to strings then increment offsets to look for next char
				if(isalpha(testchar)){
					//NOTE: J is set to arrayoffet to ensure only following strings are populated
					for(int j = arrayoffset; j < k; j++){
						//we append the character to the string of every string after offset
						tempsequencearray[j].append(1, testchar);
					}
					//update the array offset
					//this is only done if a char has been appended, to seek to next strings to append to
					arrayoffset++;
				}
				//If we found a good character and appended then we increment index offset
				//this is also done on a bad character, skipping appending, looking for next good char
				offset++;
			//exit of population loop
			}

			//with all possible data gathered we now parse the string array and insert the data into the tree
			for(int i = 0; i < k; i++){
				//make temp string for function pass
				string tempdata;
				//NOTE: We will only insert data if the string length matches its position in the array
				//the reason this is done is to prevent duplicate inserts at end of data and other circumstances
				if(tempsequencearray[i].length() == i + 1){
					tempdata = tempsequencearray[i];
					//Finally: insert data into tree via root node
					root = insert( root, tempdata);
				}
			//exit insertion loop
			}
		//exit index alpha test
		}
		//update index to next position
		index++;
	//exit file parse loop
	//file only parsed once
	}
	//display function will run INORDER traversal of tree and print data
	display(root, k);
	//exit
	return 0;
}

//getinput function runs input checks
void getinput(ifstream &inputfile, int &k, int &filesize){

	//string to store file name input
	string filename;
	//first attempt at open is used to 'prime' the while loop
	inputfile.open(filename, ios::in);

	//while input is bad loop for new input
	while(!inputfile){

		cout << "Enter the path and name of the file to be opened:\n";
		getline(cin, filename);

		//exit on command
		if(filename == "EXIT"){
			exit(0);
		}

		//NOTE: I found out that typing ctrl-z will blow-up CIN
		//I could only reason to throw an error on this input then restart
		if(cin.eof()){
			cout << "Please do not enter an End-Of-File character (ctrl + z), please restart the application...";
			exit(0);
		}

		//attempt open of user input
		inputfile.open(filename, ios::in);

		//if bad input throw error and loop
		if(!inputfile){
			cout << "File not found, please check for correct name and path. Type \"EXIT\" to quit.\n";
		}
	}
	//move forward on good file
	cout << "File opened\n";

	//get file size
	inputfile.seekg(0, ios::end);
	filesize = inputfile.tellg();
	cout<<"Size of the file is"<<" "<< filesize<<" "<<"bytes\n";

	//prompt input of sequence length (k)
	cout << "Enter the maximum length of all possible character combinations to check:\n";

	//begin try catch loop for K
	while(true){
		try{
			cin >> k;
			//throw k if input is < 0 || input >  filesize || bad input
			if(k < 1 || k > filesize || !cin){
				throw k;
			}
			break;
		}
		catch(int k){
			//error for end of file char
			if(cin.eof()){
				cout << "Please do not enter an End-Of-File character (ctrl + z), please restart the application...";
				exit(0);
			}
			//prompt for good input
			cout << "Please enter a number larger than 0 and smaller than the file size:\n";
			//clear CIN buffer
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}

//show state used to show file errors on !good()
void showState(ifstream &file){
   cout << "File Status:\n";
   cout << "   eof bit: " << file.eof() << endl;
   cout << "   fail bit: " << file.fail() << endl;
   cout << "   bad bit: " << file.bad() << endl;
   cout << "   good bit: " << file.good() << endl;
   file.clear();     // Clear any bad bits
}

//to create a new node
node* makenode(string sequence)
{
	//create new node with null children and string as data
	node* newnode = new node;
	newnode->data = sequence;
	newnode->count = 1;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

//function to insert a data in new node
node* insert(node *root, string sequence)
{
	//check for root, if none make root
	if (root == NULL) {
		return makenode(sequence);
	}

	//if matching data then increment count of current node
	if (sequence == root->data) {
		(root->count)++;
		return root;
	}
	//if data < root data then make left node
	if (sequence < root->data){
		root->left=insert(root->left, sequence);
	} else {
		//else = data > root data, make right node
		root->right=insert(root->right, sequence);
	}
	return root;
}

//inorder traversal of BST(binary search tree)
void display(node* temp, int k)
{
	//return on null child
	if (temp==NULL){
		return;
	}
	//display smaller data first
	display(temp->left, k);
	//display node data
	cout << left << std::setw(k + 5) << temp->data<<" ";
	//display count
	cout << temp->count<<endl;
	//display larger data after node
	display(temp->right, k);
}

//Thank you very much, I learned a great deal in this course and became much more confident in my ability
