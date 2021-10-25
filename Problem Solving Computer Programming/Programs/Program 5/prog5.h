/*
	Program Name: prog5.h
	Author: Cesar Camarena
	Date: 11/28/2016
	Purpose: Program 5
*/
#ifndef PROG5_H
#define PROG5_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

//Cost Structure
struct Cost
{
	float hours;
	float costOfCreature;
	float costOfFood;
	float costOfSupplies;
};

//Creatures Structure
struct Creatures
{
	string name;
	string description;
	float length;
	float height;
	string origin;
	bool danger;
	Cost costData;
};

//Function prototypes
int enterCreatures(Creatures*, int);
int deleteCreature(Creatures*, int);
bool moveArrayElements(Creatures*, string, int);
void printCreatures(Creatures*, int);
void printStatistics(Creatures*, int);
void saveCreaturesToFile(Creatures*, int);
float convertToFloat(string);
 
#endif