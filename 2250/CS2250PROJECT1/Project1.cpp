/*Adam Henze
 *CMP_SCI-2250-004
 *Dr.Galina Piatnitskaia
 *Project 1
 *9th February 2023
*/

//library inclusions
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Function prototypes
void initialize_array(int [], int);
int * shuffle_array(const int [], int);
void print_array(const int [], int);
int * createOddArray(const int [], int, int &);
int * createEvenArray(const int [], int, int &);
void array_war(int *, int, int *, int);
void sort_array(int *,int);

//Begin main program
int main ()
{
	//create initial array variables
	int arraysize = 0;
	int *numarray = nullptr;

	//check for 1-52 array size bounds with while loop
	while(arraysize > 52 || arraysize < 1)
	{
		cout << "Please enter an array size: ";
		cin >> arraysize;

		//display warning if outside bounds
		if(arraysize > 52 || arraysize < 1)
		{
			cout << "Only values of 1-52 please...\n";
		}
	}

	//create array of size entered
	numarray = new int[arraysize];

	//initialize sequence values
	initialize_array(numarray, arraysize);
	cout << "------------------------------------------------------------------\n";

	//print initialized array
	cout << "The original array is:\n";
	print_array(numarray, arraysize);
	cout << "------------------------------------------------------------------\n";

	//create new location and shuffle initial array into new array
	int * mixarray = nullptr;
	mixarray = shuffle_array(numarray, arraysize);
	cout << "The mixed array is:\n";
	print_array(mixarray, arraysize);
	cout << "------------------------------------------------------------------\n";

	//begin process of splitting mixed array
	//initialize variables to store number of odd integers and pointer to new oddarray location
	int oddsize;
	int *oddarray = nullptr;
	//call createOddArray to fill oddarray and oddsize
	oddarray = createOddArray(mixarray, arraysize, oddsize);
	cout << "The array of odd numbers is:\n";
	print_array(oddarray, oddsize);

	//initialize variables to store number of even integers andpointer to new evenarray location
	int evensize;
	int *evenarray = nullptr;
	//call creatEvenArray to fill evenarray and evensize
	evenarray = createEvenArray(mixarray, arraysize, evensize);
	cout << "The array of even numbers is:\n";
	print_array(evenarray, evensize);
	cout << "------------------------------------------------------------------\n";

	//call arraywar to compare values, populate new array, and sort
	array_war(oddarray, oddsize, evenarray, evensize);

	//clear dynamic memory
	delete [] numarray;
	delete [] evenarray;
	delete [] oddarray;
	delete [] mixarray;
	numarray = nullptr;
	evenarray = nullptr;
	oddarray = nullptr;
	mixarray = nullptr;
	//end main program
	return 0;
}

void array_war(int * oddarray, int oddsize, int * evenarray, int evensize)
{
	//initialize size of final array based on larger of even or odd arrays
	int warsize;
	if(oddsize < evensize)
	{
		warsize = evensize;
	}
	else
	{
		warsize = oddsize;
	}

	//create new array space based on larger size to store all winners
	int * wararray = new int[warsize];

	//create variables to store compared values
	int oddwarrior, evenwarrior;
	//for loop to pass through both arrays
	for(int count = 0; count < warsize; count++)
	{
		oddwarrior = 0;
		evenwarrior = 0;

		//if statement checks size of array to automatically declare winner if one array is larger
		if(evensize > count)
		{
			evenwarrior = evenarray[count];
		}
		if(oddsize > count)
		{
			oddwarrior = oddarray[count];
		}

		//next if statement checks which value is larger and assigns that value to the winners wararray
		if(evenwarrior > oddwarrior)
		{
			wararray[count] = evenwarrior;
		}
		else
		{
			wararray[count] = oddwarrior;
		}
	}

	//print outcomes of arraywar
	cout << "The veterans of the array war were:\n";
	print_array(wararray, warsize);

	//call sort_array to sort winners and then print these srted values
	sort_array(wararray, warsize);
	cout << "The ranked veterans of the array war are:\n";
	print_array(wararray, warsize);

	delete [] wararray;
}

void sort_array(int * array, int size)
{
	//create variables for position, value, and swap within select sort
	int minindex, minval;
	int temp;

	//pass through array beginning from 0 on up
	for(int count = 0; count < (size - 1); count++)
	{
		//set minindex and minval to count to begin next pass at next array position
		minindex = count;
		minval = array[count];
		//nested pass through array to check for smaller values
		for(int index = count + 1; index < size; index++)
		{
			//if smaller value is found swap update value and location variables
			if(array[index] < minval)
			{
				minval = array[index];
				minindex = index;
			}
		}
		//swap variables to finalize pass of sort
		temp = array[minindex];
		array[minindex] = array[count];
		array[count] = temp;
	}
}

void initialize_array(int array[], int size)
{
	//simple for loop to populate array based on size
	for(int count = 0; count < size; count++)
	{
		//index value = index + 1 to maintain greater than 0 values
		array[count] = count + 1;
	}
}

int * shuffle_array(const int array[], int size)
{
	//create new memory for shuffled array
	int *mixarray = new int[size];

	//for loop to populate shuffled array with initial array values
	for(int count = 0; count < size; count++)
	{
		mixarray[count] = array[count];
	}

	//seed random with time
	srand(time(0));
	//for loop to pass through array to shuffle elements
	for(int count = 0; count < size; count++)
	{
		//select random element within size of array
		int i = rand() % size;
		int x = mixarray[i];
		//select incremental element based on loop count
		int y = mixarray[count];

		//swap elements of array
		mixarray[i] = y;
		mixarray[count] = x;
	}

	return mixarray;
}

void print_array(const int array[], int size)
{
	//For loop to pass through array and incrementally print the elements
	for(int count = 0; count < size; count++)
	{
		cout << array[count] << " ";
	}
	cout << "\n";
}

int * createOddArray(const int array[], int size, int &newsize)
{
	//create variable to store number of odd integers
	int oddsize = 0;

	//for loop to pass through array and increment oddsize to reflect number of odd integers
	for(int count = 0; count < size; count++)
	{
		if(array[count] % 2 != 0)
		{
			oddsize++;
		}
	}

	//set the passed address of variable to the size of new array
	newsize = oddsize;

	//create space for new odd array
	int *oddarray = new int[oddsize];

	//create variable to increment new array position
	int oddarraypos = 0;
	//pass through initial array to place odd numbers in new oddarray
	for(int count = 0; count < size; count++)
	{
		if(array[count] % 2 != 0)
		{
			oddarray[oddarraypos] = array[count];
			oddarraypos++;
		}
	}
	return oddarray;
}

int * createEvenArray(const int array[], int size, int &newsize)
{
	//create variable to store number of even integers
	int evensize = 0;

	//for loop to pass through array and increment evensize to reflect number of even integers
	for(int count = 0; count < size; count++)
	{
		if(array[count] % 2 == 0)
		{
			evensize++;
		}
	}

	//set the passed address of variable to the size of new array
	newsize = evensize;

	//create space for new even array
	int *evenarray = new int[evensize];

	//create variable to increment new array position
	int evenarraypos = 0;
	//pass through initial array to place odd numbers in new oddarray
	for(int count = 0; count < size; count++)
	{
		if(array[count] % 2 == 0)
		{
			evenarray[evenarraypos] = array[count];
			evenarraypos++;
		}
	}
	return evenarray;
}
