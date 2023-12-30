#include "Appetiser.h"



Appetiser::Appetiser(char type, int cal, const std::string& nm, double pr, bool sh, bool tfo)
    : Item(type, cal, nm, pr), shareable(sh), twoForOne(tfo) {}

std::string Appetiser::toString() const {
    std::ostringstream oss;
    oss << name << ":"
        << " $" << std::fixed << std::setprecision(2) << price
        << ", " << calories << "cal"
        << " ( " << (shareable ? "Shareable " : "")
        << "" << (twoForOne ? "2-4-1 )" : ")");
    return oss.str();
}
