/*
	Name: Cesar Camarena
	Purpose: Program 2
*/
#include "InventoryManager.h"

InventoryManager::InventoryManager(int choice) //LIFO or FIFO
{
	inventory_choice = choice;
	
	totalProfit = 0;
	
	if (inventory_choice == 1) //LIFO
	{
		stackDeque = new StackDeque<Widget>;
	}
	
	if (inventory_choice == 2)
	{
		queueDeque = new QueueDeque<Widget>;
	}
	
}

InventoryManager::~InventoryManager()
{
	if (inventory_choice == 1)
	{
		delete stackDeque;
	}
	
	if (inventory_choice == 2)
	{
		delete queueDeque;
	}
}

void InventoryManager::buyWidgets(double cost, int num_to_buy)
{
	for (int i = 0; i < num_to_buy; i++)
	{
		Widget* widgetBought = new Widget();
		widgetBought->setCost(cost);
		
		if (inventory_choice == 1)
		{
			stackDeque->push(widgetBought);
		}
		
		if (inventory_choice == 2)
		{
			queueDeque->enqueue(widgetBought);
		}
		
	}
}

double InventoryManager::getTotalProfit()
{
	return totalProfit;
}

double InventoryManager::sellWidgets(double price, int num_to_sell)
{
	Widget* widgetSold;
	double cost = 0;
	double profit = 0;
	
	for (int i = 0; i < num_to_sell; i++)
	{
		if (inventory_choice == 1)
		{
			if (!stackDeque->isEmpty())
			{
				widgetSold = stackDeque->pop();
				cost = widgetSold->getCost();
				profit = profit + (price - cost);
			}
		}

		if (inventory_choice ==  2)
		{
			if (!queueDeque->isEmpty())
			{
				widgetSold = queueDeque->dequeue();
				cost = widgetSold->getCost();
				profit = profit + (price - cost);
			}
		}
	}
	
	totalProfit += profit;
	
	return profit;
}