#pragma once
#include <vector>
#include <memory>
#include "Item.h"

class ItemList {
protected:
    void addItemId(int id, const std::shared_ptr<Item>& item);
public:
    
    std::vector<std::pair<int, std::shared_ptr<Item>>> items;
    ItemList();
    virtual std::string toString() const;
    std::shared_ptr<Item> getItemById(int id) const;
    void loadFromCsv(const std::string& filePath);
};
