//library inclusions
#include "Horse.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

//empty constructor
Horse::Horse()
{

}

//constructor w/ name and rider to create horses
Horse::Horse(string newname, string newrider)
{
	name = newname;
	rider = newrider;
	distanceTraveled = 0;
	maxRunningDistPerSecond = rand() % 100 + 1;
	racesWon = 0;
}

//adds distance to horse races as random value based on horse speed
void Horse::runASecond()
{
	int newdistance = this->distanceTraveled;
	newdistance += (rand() % maxRunningDistPerSecond + 1);
	this->distanceTraveled = newdistance;
}

//reset horses to 0 pos
void Horse::sendToGate()
{
	this->distanceTraveled = 0;
}

//function to output race position
void Horse::displayHorse(int goalLength)
{
	//check point A and B represent the 20 different intervals to check against horse posistion
	int checkpointA;
	int checkpointB;

	//creat straing for lane display and empty
	string laneDisplay = "";

	//if horse is over finish then display lane as below
	if(this->distanceTraveled >= goalLength)
	{
		laneDisplay = "|--------------------|> Finished! ";
	}
	//if else then calc
	else
	{
		//begin lane w/ |
		laneDisplay += "|";

		//for loop 20 times for the 20 positions along the race path
		for(int i = 0; i < 20; i++)
		{
			//set checkpoint distances
			checkpointA = ((i * (goalLength / 20)));
			checkpointB = (((i + 1) * (goalLength / 20)));
			//if horse is between points then display horse as >
			if(this->distanceTraveled >= checkpointA && this->distanceTraveled < checkpointB)
			{
				laneDisplay += ">";
			}
			//if horse has passed point then display as -
			else if(this->distanceTraveled >= checkpointB)
			{
				laneDisplay += "-";
			}
			//if horse has not passed then display space in lane
			else
			{
				laneDisplay += " ";
			}
		}
		//end lane with |
		laneDisplay += "|";
	}
	//print horse info after lane display
	cout << "Horse: " + name + ", and Rider: " + rider + ": " << this->distanceTraveled << "/" << goalLength << "\n" << laneDisplay << "\n";
}

//accessor for horse distance
int Horse::getDistance()
{
	int distance;
	distance = this->distanceTraveled;
	return distance;
}

//mutator to increment horse wins
void Horse::isWinner()
{
	this->racesWon++;
}

//accessor for horse wins
int Horse::getWins()
{
	return this->racesWon;
}

//accessor for name and rider
string Horse::getname()
{
	string title;
	title = this->name + " and " + this->rider;
	return title;
}
