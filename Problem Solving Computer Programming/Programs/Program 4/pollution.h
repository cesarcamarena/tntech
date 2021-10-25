/*
	Title: pollution.h
	Date: 11/14/2016
	Author: Cesar Camarena
	Purpose: Program 4 header file
*/
#ifndef POLLUTION_H
#define POLLUTION_H

#include <iostream>
using namespace std;

//function prototypes
void enterFactoryNames(string [], int);
float* makeArray(int);
void enterCOData(float*, int);
void enterNO2Data(float*, int);
void enterO3Data(float*, int);
void printOverLimit(string [], float**, int, float);
void getLargest(string [], float**, int, string&, float&, int&);

#endif