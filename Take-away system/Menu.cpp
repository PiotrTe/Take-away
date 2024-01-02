#include "Menu.h"

#include <algorithm>

Menu::Menu(const std::string& filePath) {
    loadFromCsv(filePath);
}

std::string Menu::toString() const {
    std::ostringstream oss;

    // Group and print each category without sorting
    printCategoryItems(oss, 'a'); // Appetisers
    printCategoryItems(oss, 'm'); // Main Courses
    printCategoryItems(oss, 'b'); // Beverages

    return oss.str();
}

std::string Menu::toStringDescending() const {
    std::ostringstream oss;

    // Sort and print each category
    printSortedCategory(oss, 'a', false); // Appetisers
    printSortedCategory(oss, 'm', false); // Main Courses
    printSortedCategory(oss, 'b', false); // Beverages

    return oss.str();
}

std::string Menu::toStringAscending() const {
    std::ostringstream oss;

    // Sort and print each category
    printSortedCategory(oss, 'a', true); // Appetisers
    printSortedCategory(oss, 'm', true); // Main Courses
    printSortedCategory(oss, 'b', true); // Beverages

    return oss.str();
}

void Menu::printCategoryItems(std::ostringstream& oss, char categoryType) const {
    // Print category header
    switch (categoryType) {
    case 'a': oss << "------------------Appetisers-------------------\n"; break;
    case 'm': oss << "----------------Main Courses-------------------\n"; break;
    case 'b': oss << "------------------Beverages--------------------\n"; break;
    }

    // Print items in this category
    for (const auto& idItemPair : items) {
        if (idItemPair.second->getType() == categoryType) {
            oss << "(" << std::setw(2) << idItemPair.first << "). " << idItemPair.second->toString() << "\n";
        }
    }
}

void Menu::printSortedCategory(std::ostringstream& oss, char categoryType, bool ascending) const {
    std::vector<std::pair<int, std::shared_ptr<Item>>> categoryItems;

    // Extract items of the specified category along with their IDs
    for (const auto& idItemPair : items) {
        if (idItemPair.second->getType() == categoryType) {
            categoryItems.push_back(idItemPair);
        }
    }

    // Sort items in the specified order
    if (ascending) {
        std::sort(categoryItems.begin(), categoryItems.end(), 
            [](const std::pair<int, std::shared_ptr<Item>>& a, const std::pair<int, std::shared_ptr<Item>>& b) {
                return a.second->getPrice() < b.second->getPrice();
            });
    } else {
        std::sort(categoryItems.begin(), categoryItems.end(), 
            [](const std::pair<int, std::shared_ptr<Item>>& a, const std::pair<int, std::shared_ptr<Item>>& b) {
                return a.second->getPrice() > b.second->getPrice();
            });
    }

    // Print category header
    switch (categoryType) {
    case 'a': oss << "------------------Appetisers-------------------\n"; break;
    case 'm': oss << "----------------Main Courses-------------------\n"; break;
    case 'b': oss << "------------------Beverages--------------------\n"; break;
    }

    // Print sorted items in this category along with their IDs
    for (const auto& idItemPair : categoryItems) {
        oss << "(" << std::setw(2) << idItemPair.first << "). " << idItemPair.second->toString() << "\n";
    }
}
