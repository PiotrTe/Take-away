#pragma once
#include "ItemList.h"

class Order : public ItemList {

private:
    double total;
    std::vector<std::pair<int, std::shared_ptr<Item>>> orderedItems;

public:
    explicit Order(std::vector<std::pair<int, std::shared_ptr<Item>>>);
    void addItem(int id);
    void removeItem(int id);
    std::string printReciept();
    std::string toString() const override;
};
