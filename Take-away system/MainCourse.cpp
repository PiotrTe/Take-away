#include "MainCourse.h"

// Constructor initializes a MainCourse object using parameters.
MainCourse::MainCourse(char type, int cal, const std::string& nm, double pr) 
    : Item(type, cal, nm, pr) {} // Calls the base class (Item) constructor.

#include "MainCourse.h"

// Method to convert MainCourse object details into a string.
std::string MainCourse::toString() const {
    std::ostringstream oss;
    oss << name << ":" << " $" << std::fixed << std::setprecision(2) << price // Formats price to 2 decimal places.
        << ", " << calories << "cal";
    return oss.str();
}
