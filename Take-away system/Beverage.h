#pragma once
#include "Item.h"

// Beverage class inheriting from Item with additional beverage-specific attributes.
class Beverage : public Item {
private:
    double abv; // Alcohol by volume percentage.
    int volume; // Volume of the beverage.

public:
    // Constructor for Beverage class.
    Beverage(char type, int cal, const std::string& nm, double pr, int vol, double abv);
    
    // Getters for beverage properties.
    double getAbv() const;
    int getVolume() const;

    // Method to check alcohol presence.
    bool isAlcoholic() const;
    
    // Overridden method for string representation of a beverage.
    virtual std::string toString() const override;
};