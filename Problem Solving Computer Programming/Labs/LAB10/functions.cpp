/*
	Title: functions.cpp
	Date: 10/26/2016
	Author: Cesar Camarena
	Purpose: lab9
*/

#include "netflix.h"

/*
	The makeArray function will create a an integer array with a
	pointer named studentData that will point to it and returns
	it to the main function.
*/
int* makeArray(int students)
{
	int* studentData;
	
	studentData = new int[students];
	
	return studentData;
}

/*
	The getStudentData function allows the user to enter the amount of
	netflix watched per student.
*/
void getStudentData(int* studentData, int students)
{
	cout << "Enter the number of hours each student spent watching Netflix." << endl;
	
	for (int x = 0; x < students; x++)
	{
		cout << "Student " << (x + 1) << ":  ";
		cin >> *(studentData + x);
		
		while (*(studentData + x) < 0)
		{
			cout << "Please enter a number greater than 0." << endl;
			cout << "Student " << (x + 1) << ":  ";
			cin >> *(studentData + x);
		}
	}
	cout << endl;
	
}

/*
	The getAverage function will average the amount of netflix watched
	and returns it to the main function.
*/
float getAverage(int* studentData, int students)
{
	float average;
	int total = 0;
	
	for (int x = 0; x < students; x++)
	{
		total += *(studentData + x);
	}
	average = static_cast<float>(total) / static_cast<float>(students);
	return average;
}

/**************************************************
 * Function selectionSort                         *
 * This function performs the selection sort      *
 * algorithm on array, sorting it into ascending  *
 * order. The parameter size holds the number of  *
 * elements in the array.                         *
 **************************************************/
void selectionSort(int *array, int size)
{
   int startScan, minIndex, minValue;

   for (startScan = 0; startScan < (size - 1); startScan++)
   {
      minIndex = startScan;
      minValue = *(array+startScan);
      for(int index = startScan + 1; index < size; index++)
      {
         if (*(array+index) < minValue)
         {
            minValue = *(array+index);
            minIndex = index;
         }
      }
      *(array+minIndex) = *(array+startScan);
      *(array+startScan) = minValue;
	}
}

/*
	The printArray function will print the data
*/
void printArray(int* studentData, int students)
{
	cout << "Hours each student watched Netflix in ascending order:" << endl;
	
	for (int x = 0; x < students; x++)
	{
		cout << *(studentData + x) << " ";
	}
	cout << endl;
}

/*
	The getMedian function will obtain the median from the data
*/
float getMedian(int* studentData, int students)
{
	float median;
	
	median =  *(studentData + (students/2));
	
	if(students%2 == 0)
	{
		median = ((*(studentData + (students/2))) + (*(studentData + ((students/2) - 1)))) / static_cast<float>(2);
	}
	else
	{
		median =  *(studentData + (students/2));
	}
	
	return median;
}