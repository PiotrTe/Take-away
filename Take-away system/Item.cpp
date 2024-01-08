#include "Item.h"
#include <utility>

// Constructor for the Item class
Item::Item(char type, int cal, std::string  nm, double pr) : type(type), calories(cal), name(std::move(nm)), price(pr) {}

