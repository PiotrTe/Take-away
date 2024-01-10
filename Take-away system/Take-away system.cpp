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

    // Display welcome message
    cout << "Welcome to the restaurant type 'help' to view all available commands\n";
    
    // Initialize Menu and Order objects
    Menu menu = Menu("menu.csv");
    Order order = Order(menu.items);
    
    // Main loop to process user commands
    while (userCommand != "exit")
    {
        getline(cin, userCommand);

        // Skip if input is empty
        if (userCommand.empty()) {
            cout << "No input entered. Please enter a command." << endl;
            continue;
        }
        
        char* cstr = new char[userCommand.length() + 1];
        strcpy(cstr, userCommand.c_str());

        // Tokenize the user input into command and parameters
        char* token;
        token = strtok(cstr, " ");
        while (token != NULL)
        {
            parameters.push_back(token);
            token = strtok(NULL, " ");
        }

        string command = parameters[0];

        // Process the 'menu' command
        if (command.compare("menu") == 0) {
            // Handle different menu display options
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
        // Process the 'add' command
        if (command.compare("add") == 0)
        {
            // Add items to the order
            for (int i = 1; i < parameters.size(); i++) {
                try {
                    int itemId = std::stoi(parameters[i]);
                    order.addItem(itemId);
                }
                catch (const std::invalid_argument& e) {
                    std::cout << "Invalid item ID: " << parameters[i] << ". Please make sure to enter a numeric ID Separated by a space." << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cout << "Item ID is too large: " << parameters[i] << ". Please enter a valid ID." << std::endl;
                }
            }
        }
        // Process the 'remove' command
        else if (command.compare("remove") == 0)
        {
            // Remove items from the order
            for (int i = 1; i < parameters.size(); i++) {
                try {
                    const int itemId = std::stoi(parameters[i]);
                    order.removeItem(itemId);
                }
                catch (const std::invalid_argument& e) {
                    std::cout << "Invalid item ID: " << parameters[i] << ". Please make sure to enter a numeric IDs Separated by a space." << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cout << "Item ID is too large: " << parameters[i] << ". Please enter a valid ID." << std::endl;
                }
            }
        }
        // Process the 'checkout' command
        else if (command.compare("checkout") == 0)
        {
            order.checkout();
        }
        // Process the 'help' command
        else if (command.compare("help") == 0) {
            cout << "Available commands:\n";
            cout << "  menu [ascending/descending] - Display the menu. Optionally sort by price in ascending or descending order.\n";
            cout << "  add [item ID] [item ID] ... - Add one or more items to your order by their ID.\n";
            cout << "  remove [item ID] [item ID] ... - Remove one or more items from your order by their ID.\n";
            cout << "  checkout - Proceed to checkout, displaying the order and total price. Confirm to complete the order.\n";
            cout << "  exit - Exit the program.\n";
            cout << "  help - Display this help message.\n";
        }
        else
        {
            cout << "Invalid command: " << command << ". Type 'help' to see a list of available commands." << '\n';
        }

        // Clear the parameters for the next command
        parameters.clear();
    }
}