#pragma once
#include "ItemList.h"

class Menu : public ItemList {
public:
    explicit Menu(const std::string& filePath);
    std::string toString() const override;
    void printCategoryItems(std::ostringstream& oss, char categoryType) const;
    std::string toStringDescending() const;
    std::string toStringAscending() const;
    void printSortedCategory(std::ostringstream& oss, char categoryType, bool ascending) const;
};
