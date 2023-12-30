#include "Beverage.h"

Beverage::Beverage(char type, int cal, const std::string& nm, double pr, int vol, double abv)
    : Item(type, cal, nm, pr), abv(abv), volume(vol) {}

bool Beverage::isAlcoholic() const {
    return abv > 0.0; // Assumes any ABV greater than 0 is alcoholic
}

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