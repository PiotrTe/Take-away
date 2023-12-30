#include "ItemList.h"
#include "Appetiser.h"
#include "MainCourse.h"
#include "Beverage.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

ItemList::ItemList() {}

void ItemList::addItemId(int id, const std::shared_ptr<Item>& item)
{
    items.emplace_back(id, item);
}

std::string ItemList::toString() const {
    std::ostringstream oss;
    for (const auto& pair : items) {
        oss << pair.second->toString() << '\n';
    }
    return oss.str();
}

std::shared_ptr<Item> ItemList::getItemById(const int id) const
{
    for (const auto& pair : items) 
    {
        if(pair.first == id) 
        {
            return pair.second;
        }
    }
    throw std::runtime_error("Item with id " + std::to_string(id) + " doesn't exist");
}

void ItemList::loadFromCsv(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;
    int counter = 1;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<std::string> tokens;
        std::string token;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        char type = tokens[0][0];
        std::string name = tokens[1];
        double price = !tokens[2].empty() ? std::stod(tokens[2]) : 0.0;
        int calories = !tokens[3].empty() ? std::stoi(tokens[3]) : 0;
        bool shareable = tokens[4] == "y";
        bool twoForOne = tokens[5] == "y";
        int volume = 0;
        double abv = 0.0;

        if (tokens.size() == 8) {
            volume = !tokens[6].empty() ? std::stoi(tokens[6]) : 0;
            abv = !tokens[7].empty() ? std::stod(tokens[7]) : 0.0;
        }

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
        addItemId(counter, item);
        counter++;  // increment the counter at the end of each loop
    }
    file.close();
}