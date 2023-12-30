#pragma once
#include "Item.h"

class Beverage : public Item {
private:
    double abv; // Alcohol by volume
    int volume;

public:
    Beverage(char type, int cal, const std::string& nm, double pr, int vol, double abv);
    
    double getAbv() const {return abv;}
    int getVolume() const {return volume;}
    bool isAlcoholic() const;
    
    virtual std::string toString() const override;
};
