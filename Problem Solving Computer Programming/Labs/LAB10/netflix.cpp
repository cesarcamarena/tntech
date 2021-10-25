/*
	Title:  netflix.cpp
	Date: 10/26/2016
	Author: Cesar Camarena
	Purpose: lab 9
*/

#include "netflix.h"

int main()
{
	int students;
	int* studentData;
	float average;
	float median;
	
	cout << "How many students were surveyed?  ";
	cin >> students;
	cout << endl;
	
	//input validation
	while (students < 0)
	{
		cout << "Please enter a number greater than 0." << endl;
		cout << "How many students were surveyed?  ";
		cin >> students;
	}
	
	//creates array
	studentData = makeArray(students);
	
	//gets data of how many hours students watched netflix
	getStudentData(studentData, students);
	
	//averages the amount
	average = getAverage(studentData, students);
	
	//sorts the data
	selectionSort(studentData, students);
	
	//displays the data
	printArray(studentData, students);
	
	//finds the median of the data
	median = getMedian(studentData, students);

	cout << "\n-------------------------------" << endl;
	cout << "-------------------------------" << endl;
	cout << "       NETFLIX STATISTICS      " << endl;
	cout << "-------------------------------" << endl;
	cout << "     Average:  " << setprecision(2) << fixed << average << endl;
	cout << "     Median:   " << setprecision(2) << fixed << median << endl;
	cout << "-------------------------------" << endl;
	cout << "-------------------------------" << endl;
	
	delete [] studentData; 
	
	return 0;
}
