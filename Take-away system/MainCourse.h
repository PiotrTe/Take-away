#pragma once
#include "Item.h"

class MainCourse : public Item {
public:
    // Constructor for MainCourse class.
    MainCourse(char type, int cal, const std::string& nm, double pr);

    // Overridden toString method to provide a string representation of a MainCourse object.
    std::string toString() const override;
};
