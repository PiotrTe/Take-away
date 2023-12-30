
#include "Order.h"
#include "Menu.h"
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm> // added for sorting

Order::Order(std::vector<std::pair<int, std::shared_ptr<Item>>> list)
{
    items = std::move(list);
}

void Order::addItem(int id) {
    if (id < 1 || id > items.size()) { // added range validation
        std::cout << "Invalid ID: " << id << ". Must be between 1 and " << items.size() << ".\n";
        return;
    }
    std::shared_ptr<Item> itemPtr = getItemById(id);
    if (itemPtr) {
        orderedItems.emplace_back(id, itemPtr);
    } else {
        std::cout << "Item with ID " << id << " not found." << '\n';
        // Handle the error appropriately.
    }
}

void Order::removeItem(int id){
    auto it = std::find_if(orderedItems.begin(), orderedItems.end(),
       [&id](const std::pair<int, 
       std::shared_ptr<Item>>& element) {
       return element.first == id; });
    if (it != orderedItems.end()) {
        orderedItems.erase(it);
    } else {
        std::cout << "Item with ID " << id << " not in the order.\n";
        // Handle the error appropriately.
    }
}


auto Order::printReciept() -> std::string
{
    return " ";
}

std::string Order::toString() const {
    // Make a copy of the orderedItems vector to sort, because this method is const
    auto sortedItems = orderedItems;
    std::sort(sortedItems.begin(), sortedItems.end(),
        [](const std::pair<int, std::shared_ptr<Item>>& a, const std::pair<int, std::shared_ptr<Item>>& b) {
            return a.first < b.first;
        });

    std::ostringstream oss;
    for (const auto& itemPair : sortedItems) {
        oss << std::setw(2) << itemPair.first << ". " << itemPair.second->toString() << "\n";
    }

    return oss.str();
}