/*
	Name: Cesar Camarena
	Purpose: Program 2
*/
#if !defined (WIDGET_H)
#define WIDGET_H

#include <iostream>
using namespace std;

class Widget
{
	private:
		double cost;
	
	public:
	  /*pre: Nothing.
	    post: Constructs a widget*/
		Widget();
		
	  /*pre: Nothing.
	    post: Deconstructs the widget*/
		~Widget();
		
	  /*pre: Nothing.
	    post: Returns the cost of the widget*/
		double getCost();
		
	  /*pre: The cost that the user wants to set for the widget
	    post: Newly sets the cost of the widget from the user*/
		void setCost(double num);
};

#endif