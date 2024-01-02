/* ------------------------------------------------------
CMP2811 Applied Programming Paradigms
Driver program for "Takeaway" assignment
Autumn 2023

This file is a representative test file.
During marking, we will use the exact same notation
as provided in the brief, so make sure you follow that guideline.
Also make sure that you don't modify the code provided here,
but instead add what you need to complete the tasks.

Good luck!
------------------------------------------------------ */
// ReSharper disable CppClangTidyReadabilityStringCompare
#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"
#include "Order.h"
#include "Item.h"

#include <iostream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

int main()
{
	string userCommand;
	vector <string> parameters;

	//Create a menu object from a CSV file
	Menu menu = Menu("menu.csv");
	// Create an order object
	Order order = Order(menu.items);
	

	while (userCommand != "exit")
	{
		getline(cin, userCommand);
		char* cstr = new char[userCommand.length() + 1];
		strcpy(cstr, userCommand.c_str());

		char* token;
		token = strtok(cstr, " ");

		while (token != NULL)
		{
			parameters.push_back(token);
			token = strtok(NULL, " ");
		}

		string command = parameters[0];

		if (command.compare("menu") == 0) {
			if (parameters.size() > 1) {
				if (parameters[1].compare("ascending") == 0) {
					cout << menu.toStringAscending();
				} else if (parameters[1].compare("descending") == 0) {
					cout << menu.toStringDescending();
				}
			} else {
				cout << menu.toString();
			}
		}
		else if (command.compare("add") == 0)
		{
			for (int i = 1; i < parameters.size(); i++) {
				try {
					int itemId = std::stoi(parameters[i]); // Convert string to int
					order.addItem(itemId);
				}
				catch (const std::invalid_argument& e) {
					std::cout << "Invalid item ID: " << parameters[i] << ". Please make sure to enter a numeric ID Separated by a space." << std::endl;
				}
			}
		}
		else if (command.compare("remove") == 0)
		{
			for (int i = 1; i < parameters.size(); i++) {
				try {
					const int itemId = std::stoi(parameters[i]); // Convert string to int
					order.removeItem(itemId);
				}
				catch (const std::invalid_argument& e) {
					std::cout << "Invalid item ID: " << parameters[i] << ". Please make sure to enter a numeric IDs Separated by a space." << std::endl;
				}
			}
		}
		else if (command.compare("checkout") == 0)
		{
			order.checkout();
		}
		else if (command.compare("help") == 0) {
			cout << "Available commands:\n";
			cout << "  menu [ascending/descending] - Display the menu. Optionally sort by price in ascending or descending order.\n";
			cout << "  add [item ID] [item ID] ... - Add one or more items to your order by their ID.\n";
			cout << "  remove [item ID] [item ID] ... - Remove one or more items from your order by their ID.\n";
			cout << "  checkout - Proceed to checkout, displaying the order and total price. Confirm to complete the order.\n";
			cout << "  exit - Exit the program.\n";
			cout << "  help - Display this help message.\n";
		}

		parameters.clear();

	}

	cout << "Press any key to quit...";
	std::getchar();

}