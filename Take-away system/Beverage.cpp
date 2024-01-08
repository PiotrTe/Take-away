#include "Beverage.h"

// Constructor for the Beverage class
Beverage::Beverage(char type, int cal, const std::string& nm, double pr, int vol, double abv)
    : Item(type, cal, nm, pr), abv(abv), volume(vol) {} // Initializes base class and Beverage specific attributes

// Function to check if the Beverage contains alcohol
bool Beverage::isAlcoholic() const {
    return abv > 0.0; // Returns true if alcohol by volume (ABV) is greater than 0
}
// Method to convert Beverage object details to a string
std::string Beverage::toString() const {
    std::ostringstream oss;
    oss << name << ":"
        << " $" << std::fixed << std::setprecision(2) << price
        << ", " << calories << "cal"
        << " (" << volume << "ml";
        if (isAlcoholic()) {
            oss << ", " << abv << "% ABV)";
        }
        else
        {
            oss << ")";
        }

    return oss.str();
}