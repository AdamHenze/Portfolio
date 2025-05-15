/*
 * Horse.h
 *
 *  Created on: Mar 19, 2023
 *      Author: treyh
 */

//horse class file
#ifndef HORSE_H_
#define HORSE_H_


//inclusions
#include <iostream>
#include <cstring>

using namespace std;

//beginclass
class Horse
{
	//private data types
private:
	string name;
	string rider;
	int maxRunningDistPerSecond;
	int distanceTraveled;
	int racesWon;
	//public methods
public:
	Horse();
	Horse(string,string);
	void runASecond();
	void sendToGate();
	void displayHorse(int goalLength);
	int getDistance();
	void isWinner();
	int getWins();
	string getname();
};

#endif /* HORSE_H_ */
