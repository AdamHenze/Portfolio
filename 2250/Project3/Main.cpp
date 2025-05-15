//Adam Henze
//3/20/2023
//CS2250

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Horse.h"

using namespace std;
//prototypes
void newrace(int, Horse[], int &, int &);
void checkwinners(int, Horse[], int &, int &, string &);
string userinput();

//begin main
int main()
{
	//seed random
	srand(time(0));

	//create variables
	int racecount = 0;
	int racelength;
	int horsecount;
	string tempname;
	string temprider;

	//ask user for number of horses
	cout << "Please enter the number of horses to race: ";
	while(!(cin >> horsecount) || horsecount <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Try again. Please only enter positive numbers: ";
	}

	//create new array based on horse count
	Horse *Lineup = new Horse[horsecount];

	//parse array and cerate new objects for array positions with constructors
	for(int i = 0; i < horsecount; i++)
	{
		cout << "Enter a name for horse #" << (i + 1) << ": ";
		cin >> tempname;
		cout << "Enter a name for rider #" << (i + 1) << ": ";
		cin >> temprider;

		Lineup[i] = Horse(tempname, temprider);
	}

	//begin new race
	newrace(horsecount, Lineup, racelength, racecount);

	//string for user input
	string input;

	//while input is not 'n' then we can assume input is 'y' so we continue inwhile loop
	while(input != "n")
	{
		//ask user for continue
		input = userinput();

		//exit if n
		if(input == "n")
		{
			return 0;
		}

		//spacer
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

		//parses lineup of horses and runs them one second
		for(int i = 0; i < horsecount; i++)
		{
			Lineup[i].runASecond();
		}

		//display new positions
		for(int i = 0; i < horsecount; i++)
		{
			Lineup[i].displayHorse(racelength);
		}
		//check for winners, this function will begin a new race if needed, return from function, then continue to top of loop
		checkwinners(horsecount, Lineup, racelength, racecount, input);

	}

	delete [] Lineup;
	Lineup = nullptr;
	//exit and end once loop is left
	return 0;
}

//function to restart race
void newrace(int horsecount, Horse Lineup[], int &racelength, int &racecount)
{
	//update race count to store number of races
	racecount++;
	cout << "Please enter the race length: ";
	//check for correct inputs
	while(!(cin >> racelength) || racelength < 100)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Try again. Please only enter positive numbers greater than 100: ";
	}

	//start new race
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "Start!\n";

	//send linupe of horses to gate
	for(int i = 0; i < horsecount; i++)
	{
		Lineup[i].sendToGate();
	}

	//display horses at start
	for(int i = 0; i < horsecount; i++)
	{
		Lineup[i].displayHorse(racelength);
	}
}

//function to check if horse has one after each second
void checkwinners(int horsecount, Horse Lineup[], int &racelength, int &racecount, string &input)
{
	int finishcount = 0;

	//function checks for finishers, if finishers then check for ties, if no ties then select farthest as winner


	//check for winners and increment finish count to cont finished horses
	for(int i = 0; i < horsecount; i++)
	{
		if(Lineup[i].getDistance() >= racelength)
		{
			//incremement winners
			finishcount++;
		}
	}

	//if based on win count
	if(finishcount == 0)
	{
		//if no winners then exit immediately
		return;
	}
	else if(finishcount == 1)
	{
		//if one winner parse lineup and find winner based on passing length of race
		for(int i = 0; i < horsecount; i++)
		{
			if(Lineup[i].getDistance() >= racelength)
			{
				//set as winner
				Lineup[i].isWinner();
			}
			//print races won
			cout << Lineup[i].getname() << " Races won: " << Lineup[i].getWins() << "/" << racecount << "\n";
		}
		//ask for continue
		input = userinput();
		//if no continue then exit before new race is called
		if(input == "n")
		{
			return;
		}
		//new race if yes
		newrace(horsecount, Lineup, racelength, racecount);
	}
	//else for finishers > 1
	else{

		//variables and arrays to store winner positions and tied positions to check for greatest length and randomize ties
		int winsposition = 0;
		int *winpositionarray = new int[finishcount];
		int tempwinner = 0;
		int farthest = 0;
		int ties = 0;
		int tiesposition = 0;

		int previousdistance;

		//parse and store winner positions in winner array
		for(int i = 0; i < horsecount; i++)
		{
			//if finished store
			if(Lineup[i].getDistance() >= racelength)
			{
				//store
				winpositionarray[winsposition] = i;
				//incriment to next winarray position
				winsposition++;
			}
		}

		//check for ties and add to tie array if so
		for(int i = 0; i < finishcount; i++)
		{
			//if matches next or previous value increment then we have a tie, and the current posiiton in winner array is added to tie array,
			//we check the distance of the winners against the next and previous winners to check for ties
			if(Lineup[winpositionarray[i]].getDistance() == Lineup[winpositionarray[i + 1]].getDistance() || Lineup[winpositionarray[i]].getDistance() == previousdistance)
			{
				//increment ties if so
				ties++;
			}
			//set previous distance as current [i] to check against on next pass
			previousdistance = Lineup[winpositionarray[i]].getDistance();
		}

		//create array for ties based on number of ties
		int *tiepositionarray = new int[ties];

		for(int i = 0; i < finishcount; i++)
		{
			//if matches next or previous value add the position of this horse to the array of tied positions
			if(Lineup[winpositionarray[i]].getDistance() == Lineup[winpositionarray[i + 1]].getDistance() || Lineup[winpositionarray[i]].getDistance() == previousdistance)
			{
				//add to array and increment position
				tiepositionarray[tiesposition] = winpositionarray[i];
				tiesposition++;
			}
			//set previous distance
			previousdistance = Lineup[winpositionarray[i]].getDistance();
		}

		// if we have more than 0 ties, then we have ties lanes and must randomly select a winner from those positions stored in the tied array
		if(ties > 0)
		{
			//randomly select winner
			Lineup[tiepositionarray[rand() % ties]].isWinner();

			//print wins
			for(int i = 0; i < horsecount; i++)
			{
				cout << Lineup[i].getname() << " Races won: " << Lineup[i].getWins() << "/" << racecount << "\n";
			}

			//ask for new race
			input = userinput();
			if(input == "n")
			{
				return;
			}
			newrace(horsecount, Lineup, racelength, racecount);
			return;
		}


		//if function continues to here then no ties were found and we next look for the farthest distance horse to delclare winner

		//parse based on finish positions
		for(int i = 0; i < finishcount; i++)
		{
			//if farthest then save
			if(Lineup[winpositionarray[i]].getDistance() > farthest)
			{
				farthest = Lineup[winpositionarray[i]].getDistance();
				tempwinner = winpositionarray[i];
			}
		}

		//declare farthest as winner
		Lineup[tempwinner].isWinner();

		//print wins
		for(int i = 0; i < horsecount; i++)
		{
			cout << Lineup[i].getname() << " Races won: " << Lineup[i].getWins() << "/" << racecount << "\n";
		}

		//user input for new race
		input = userinput();
		if(input == "n")
		{
			return;
		}
		newrace(horsecount, Lineup, racelength, racecount);
		return;
	}
}

//function to get y\n from user and check for correct input
string userinput()
{
	string input;

	cout << "Continue? y/n : ";
	cin >> input;
	//while input is not y or n retry
	while(input != "n" && input != "y")
	{
		cout << "only enter y/n please: ";
		cin >> input;
	}

	return input;
}
