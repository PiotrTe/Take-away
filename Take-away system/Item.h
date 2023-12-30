#pragma once
#include <string>
#include <iomanip>
#include <tuple>
#include <sstream>

class Item {
protected:
    char type;
    int calories;
    std::string name;
    double price;

public:
    Item(char type, int cal, std::string  nm, double pr);
    
    char getType() const {return type;}
    int getCalories() const {return calories;}
    std::string getName() const {return name;}
    double getPrice() const {return price;}
    
    virtual std::string toString() const = 0; // Pure virtual function for polymorphic behavior
    
};
