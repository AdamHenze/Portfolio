/*Adam Henze
 *CMP_SCI-2250-004
 *Dr.Galina Piatnitskaia
 *Project 2
 *22th February 2023
*/

//Library inclusions
#include <iostream>
#include <cstring>

using namespace std;

//Required Word Structure
struct Word {
	string english;
	string piglatin;
};

//Function Prototypes
Word * splitSentence(const string, int &);
void convertToPigLatin(Word [], int);
void displayPigLatin(const Word [], int);

//Begin main program
int main ()
{

	//init variables to store user entered sentence and word count
	string sentence;
	int wordcount = 0;

	//accept user sentence
	cout << "Please enter a sentence to translate: \n";
	getline(cin, sentence);

	//init null word array
	Word *wordarr = nullptr;

	//call splitsentence to operate on user sentence and return word array of english words
	wordarr = splitSentence(sentence, wordcount);
	//call converttopiglatin to convert english word members to piglatin and populate piglatin word members
	convertToPigLatin(wordarr, wordcount);
	//call display piglatin to display values in word array in sentence form
	displayPigLatin(wordarr, wordcount);
	//end main program

	//delete dynamic memory
	delete [] wordarr;
	wordarr = nullptr;
	return 0;
}

Word * splitSentence(const string sentence, int &wordcount)
{

	//Listen... I may have gone overboard with the error checking, but i wanted it to work even if the cat sat on the keyboard.
	//it checks for a great deal of conditions before storing word strings

	//Begin cleanup of user sentence
	//init int for value of sentence length
	int sentlen = sentence.length();

	//Create temp string sentedit to edit initial sentence
	string sentedit = sentence;

	//forloop to parse through sentence and convert upper alpha values to lower values and convert nonalpha characters to * for removal later
	//the reason we convert nonalpha to * is if a nonalpha char was found inside of a word and converted to a space for removal the space char would indicate a word separation incorrectly
	for(int i = 0; i < sentlen; i++)
	{
		//convert upper to lower w/ spaces unaffected
		if(isalpha(sentence[i]) || isspace(sentence[i]))
		{
			sentedit[i] = tolower(sentence[i]);
		}
		//convert non alpha to *
		else
		{
			//the simplest way to convert in my opinion was to use char() with the ascii value of *
			sentedit[i] = char(42);
		}
	}

	//check converted sentence before removal and condensing, commented out after finalization
	//cout << sentedit << endl;

	//forloop to erase all non alpha values, which are now converted to *
	for(int i = 0; i < sentlen; i++)
	{
		//while the current character 'i' in sentence == * --->
		while(sentedit[i] == char(42))
		{
			//move the next value in sentence down one element to replace the * char.
			for(int j = i; j < sentlen; j++)
			{
				sentedit[j] = sentedit[j + 1];
			}
		}
	}

	//for loop to parse through sentence
	for(int i = 0; i < sentlen; i++)
	{
		//while loop to check for two spaces next to each other by looking at character 'i' and 'i + 1' in sentence
		//while current character 'i' of sentence == space && the next character of sentence == space --->
		while(isspace(sentedit[i]) && isspace(sentedit[i + 1]))
		{
			//while two spaces exist as the next two characters in sentence, move the remaining characters in the sentence down one element to replace one of the two spaces
			//this process will continue until all consecutive spaces are removed
			for(int j = i; j < sentlen; j++)
			{
				//move characters down one element
				sentedit[j] = sentedit[j + 1];
			}
		}
	}

	//if white space at begining of string decrement elements till removed
	while(sentedit[0] == char(32))
	{
		for(int i = 0; i < sentlen; i++)
		{
			sentedit[i] = sentedit[i + 1];
		}
	}

	//erase nonaplha at end of sentence
	while(!isalpha(sentedit[sentlen - 1]))
	{
		sentedit.erase(sentlen - 1);
		sentlen = sentedit.length();
	}
	//End Cleanup, words are now lower case and separated by spaces, all non alpha removed

	//Begin english word store
	//for loop to count 'spaces + 1', thus counting words
	for(int i = 0; i < sentlen; i++)
	{
		if(isspace(sentedit[i]) && i > 0)
		{
			wordcount++;
		}
	}
	wordcount += 1;
	//wordcount now reflects the correct number of substrings to create
	//this value is passed out of function via (int &) in function call

	//create temp dynamic word array to pass out of function
	Word *tempwordarr = new Word[wordcount];

	//create int to store current word element an tempwordarr
	int wordpos = 0;
	//for loop will parse through edited sentence and store characters to string of word.english, while finding a space will increment to next word element
	for(int i = 0; i < sentlen; i++)
	{
		//if space is found increment word
		if(isspace(sentedit[i]))
		{
			wordpos++;
		}
		//if alpha found add alpha value to current word.english string
		else
		{
			tempwordarr[wordpos].english += sentedit[i];
		}
	}
	//word array is now populated with english substrings
	//exit function
	return tempwordarr;
}


void convertToPigLatin(Word wordarr[], int size)
{
	//temp string to store english and piglatin word elements
	string tempstring;
	//int to store length of words
	int length;
	//char to store current first letter of current element
	char current;

	//forloop to parse through word array, size == number of word elements
	for(int i = 0; i < size; i++)
	{
		//set length to current word
		length = wordarr[i].english.length();
		//set current to first alpha char of current word
		current = wordarr[i].english[0];

		//if else to check for vowels found in first character of current word
		if(current == 'a' || current == 'e' || current == 'i' || current == 'o' || current == 'u')
		{
			//if vowel is found
			//set tempstring to english
			tempstring = wordarr[i].english;
			//set piglatin element to english plus "way"
			wordarr[i].piglatin =  tempstring + "way";
		}
		//if no vowel is found, thus a consonant as first char
		else
		{
			//set tempstring to english value
			tempstring = wordarr[i].english;
			//populate piglatin with english value
			wordarr[i].piglatin = tempstring;

			//for loop to decrement elements of current piglatin word
			for(int j = 0; j < length; j++)
			{
				wordarr[i].piglatin[j] = tempstring[j + 1];
			}
			//update tempstring to new piglatin string, remove extra space after decrement
			tempstring = wordarr[i].piglatin;
			tempstring.erase(length - 1);

			//set piglatin to decremented-tempstring, add current ( which temporarily stored the first character of the word ) to the back of string, add "ay" to string
			wordarr[i].piglatin = tempstring + current + "ay";
		}
	}
	//end of function
}

void displayPigLatin(const Word wordarr[], int size)
{
	//tempstring to store finalized sentence
	string tempstring;

	//begin sentence with first word of wordarr
	tempstring += wordarr[0].piglatin;

	//parse through word arr adding words to sentence
	for(int i = 1; i < size; i++)
	{
		tempstring += " " + wordarr[i].piglatin;
	}
	//ad period and cap first char
	tempstring += ".";
	tempstring[0] = toupper(tempstring[0]);
	//print
	cout << "The sentence translated into piglatin is:\n";
	cout << tempstring;
}

