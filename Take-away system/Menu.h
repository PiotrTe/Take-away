#pragma once
#include "ItemList.h"

class Menu : public ItemList {
public:
    explicit Menu(const std::string& filePath);
    std::string toString() const override;
};
