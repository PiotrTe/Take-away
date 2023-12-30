#pragma once
#include "Item.h"

class Appetiser : public Item
{
private:
	bool shareable;
	bool twoForOne;

public:
	Appetiser(char type, int cal, const std::string& nm, double pr, bool sh, bool tfo);
	
	bool getShareable() const {return shareable;}
	bool getTwoForOne() const {return twoForOne;}
	
	std::string toString() const override;
};
