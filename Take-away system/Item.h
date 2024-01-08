#pragma once
#include <string>
#include <iomanip>
#include <tuple>
#include <sstream>

// Base class Item, to be inherited by specific item types (like Beverage, Appetiser, etc.)
class Item {
protected:
    char type;         // Type of the item
    int calories;      // Calories of the item
    std::string name;  // Name of the item
    double price;      // Price of the item

public:
    // Constructor for Item class
    Item(char type, int cal, std::string  nm, double pr);
    
    // Getters for item properties
    char getType() const {return type;}
    int getCalories() const {return calories;}
    std::string getName() const {return name;}
    double getPrice() const {return price;}
    
    // Pure virtual function for string representation
    virtual std::string toString() const = 0; 
};
