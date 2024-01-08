#include "ItemList.h"

#include <algorithm>
#include "Appetiser.h"
#include "MainCourse.h"
#include "Beverage.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <map>
// Method to add an item with its ID to the list
void ItemList::addItemId(int id, const std::shared_ptr<Item>& item) {
    items.emplace_back(id, item);
}

// Method to generate a string representation of all items in the list
std::string ItemList::toString() const {
    std::ostringstream oss;
    for (const auto& pair : items) {
        oss << pair.second->toString() << '\n';
    }
    return oss.str();
}

// Method to get an item by its ID
std::shared_ptr<Item> ItemList::getItemById(const int id) const {
    for (const auto& pair : items) {
        if(pair.first == id) {
            return pair.second;
        }
    }
    throw std::runtime_error("Item with id " + std::to_string(id) + " doesn't exist");
}

// Method to load items from a CSV file and add them to the list
void ItemList::loadFromCsv(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::vector<std::shared_ptr<Item>> tempItems;

    while (std::getline(file, line)) {
        // Parsing each line of the CSV file
        std::istringstream ss(line);
        std::vector<std::string> tokens;
        std::string token;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // Processing each line to create corresponding Item objects
        char type = tokens[0][0];
        std::string name = tokens[1];
        double price = std::stod(tokens[2]);
        int calories = std::stoi(tokens[3]);
        bool shareable = tokens[4] == "y";
        bool twoForOne = tokens[5] == "y";
        int volume = (tokens.size() > 6 && !tokens[6].empty()) ? std::stoi(tokens[6]) : 0;
        double abv = (tokens.size() > 7 && !tokens[7].empty()) ? std::stod(tokens[7]) : 0.0;

        std::shared_ptr<Item> item;
        switch (type) {
            case 'a':
                item = std::make_shared<Appetiser>(type, calories, name, price, shareable, twoForOne);
                break;
            case 'm':
                item = std::make_shared<MainCourse>(type, calories, name, price);
                break;
            case 'b':
                item = std::make_shared<Beverage>(type, calories, name, price, volume, abv);
                break;
            default:
                std::cerr << "Unknown item type: " << type << " in line: " << line << '\n';
                continue; // Skip this line
        }
        tempItems.push_back(item);
    }
    // Sort the items before adding them to the list
    std::sort(tempItems.begin(), tempItems.end(),
        [](const std::shared_ptr<Item>& a, const std::shared_ptr<Item>& b) -> bool {
            // Map type characters to sorting orders
            static const std::map<char, int> sortOrder = {
                {'a', 1}, // Appetisers
                {'m', 2}, // Main Courses
                {'b', 3}  // Beverages
            };

            char typeA = a->getType();
            char typeB = b->getType();

            // Find the sorting order for each type
            int orderA = sortOrder.count(typeA) ? sortOrder.at(typeA) : 4;
            int orderB = sortOrder.count(typeB) ? sortOrder.at(typeB) : 4;

            // Compare based on defined sorting order
            return orderA < orderB;
        }
    );

    // Assign IDs to the sorted items and add them to the list
    int counter = 1;
    for (auto& item : tempItems) {
        addItemId(counter++, item);
    }

    file.close(); // Close the file after processing
}