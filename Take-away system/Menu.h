#pragma once
#include "ItemList.h"

// Menu class, derived from ItemList, for managing and displaying a restaurant menu.
class Menu : public ItemList {
public:
    // Constructor: Initializes the menu from a file.
    explicit Menu(const std::string& filePath);

    // Returns a string representation of the entire menu.
    std::string toString() const override;

    // Helper function to print items of a specific category.
    void printCategoryItems(std::ostringstream& oss, char categoryType) const;

    // Returns a string representation of the menu with items sorted in descending order.
    std::string toStringDescending() const;

    // Returns a string representation of the menu with items sorted in ascending order.
    std::string toStringAscending() const;

    // Helper function to print sorted items of a specific category.
    void printSortedCategory(std::ostringstream& oss, char categoryType, bool ascending) const;
};
