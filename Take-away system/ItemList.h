#pragma once
#include <vector>
#include <memory>
#include "Item.h"

// ItemList class manages a collection of items.
class ItemList {
protected:
    // Method to add an item with its unique ID to the list.
    void addItemId(int id, const std::shared_ptr<Item>& item);

public:
    
    // Container to store items with their corresponding IDs.
    std::vector<std::pair<int, std::shared_ptr<Item>>> items;

    // Method to return a string representation of all items.
    virtual std::string toString() const;

    // Method to retrieve an item by its ID.
    std::shared_ptr<Item> getItemById(int id) const;

    // Method to load and initialize items from a CSV file.
    void loadFromCsv(const std::string& filePath);
};
