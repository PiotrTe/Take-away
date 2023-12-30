#pragma once
#include "Item.h"

class MainCourse : public Item {
public:
    MainCourse(char type, int cal, const std::string& nm, double pr);
    std::string toString() const override;
};
