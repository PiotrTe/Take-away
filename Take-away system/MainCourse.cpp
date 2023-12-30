#include "MainCourse.h"

MainCourse::MainCourse(char type, int cal, const std::string& nm, double pr) : Item(type, cal, nm, pr) {}

#include "MainCourse.h"

std::string MainCourse::toString() const {
    std::ostringstream oss;
    oss << name << ":"
        << " $" << std::fixed << std::setprecision(2) << price
        << ", " << calories << "cal";
    return oss.str();
}
