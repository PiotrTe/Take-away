#include "Menu.h"

Menu::Menu(const std::string& filePath) {
    loadFromCsv(filePath);
}

std::string Menu::toString() const {
    
    std::ostringstream oss;

    oss <<  "------------------Appetisers-------------------\n";
    for (const auto& idItemPair : items) {
        if (idItemPair.second->getType() == 'a')
            oss << std::setw(2) << idItemPair.first << ". " << idItemPair.second->toString() << "\n";
    }

    oss << "\n----------------Main Courses-------------------\n";
    for (const auto& idItemPair : items) {
        if (idItemPair.second->getType() == 'm')
            oss << std::setw(2) << idItemPair.first << ". " << idItemPair.second->toString() << "\n";
    }

    oss << "\n------------------Beverages--------------------\n";
    for (const auto& idItemPair : items) {
        if (idItemPair.second->getType() == 'b')
            oss << std::setw(2) << idItemPair.first << ". " << idItemPair.second->toString() << "\n";
    }

    return oss.str();
}