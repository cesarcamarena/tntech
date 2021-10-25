/*
	Name: Cesar Camarena
	Purpose: Program 2
*/
#if !defined (INVENTORYMANAGER_H)
#define INVENTORYMANAGER_H

#include "DequeArray.h"
#include "StackDeque.h"
#include "QueueDeque.h"
#include "Widget.h"

class InventoryManager
{
	private:
		StackDeque<Widget>* stackDeque;
		QueueDeque<Widget>* queueDeque;
		
		double totalProfit;
		int inventory_choice;
	
	public:
	  /*pre: Receives a choice from the user whether they want a stack or queue array
	    post: Constructs a stack or queue array based upon the user's choice*/
		InventoryManager(int inventory_choice); //LIFO or FIFO
		
	  /*pre: Nothing.
	    post: Deconstructs the array that the user chose*/
		~InventoryManager();
		
	  /*pre: Receives the cost for each widget and how many widgets the user wants to buy
	    post: Inserts the data into the array*/
		void buyWidgets(double cost, int num_to_buy);
		
	  /*pre: Nothing.
	    post: Returns the total profit*/
		double getTotalProfit();
		
	  /*pre: Receives the price and the amount of widgets that user will sell
	    post: Returns the profit the made from the sell*/
		double sellWidgets(double price, int num_to_sell);
	
};

#endif