/*
	Title:  netflix.h
	Date: 10/26/2016
	Author: Cesar Camarena
	Purpose: Netflix Header File
*/
#ifndef NETFLIX_H
#define NETFLIX_H

#include <iostream>
#include <iomanip>
using namespace std;

//function prototypes
int* makeArray (int);
void getStudentData(int*, int);
float getAverage(int*, int);
void selectionSort(int*, int);
void printArray(int*, int);
float getMedian(int*, int);

#endif