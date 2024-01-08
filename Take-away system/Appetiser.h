#pragma once
#include "Item.h"

class Appetiser : public Item
{
private:
	bool shareable; // Flag for shareability of the appetiser.
	bool twoForOne; // Flag for two-for-one offer availability.
	
public:
	// Constructor declaration.
	Appetiser(char type, int cal, const std::string& nm, double pr, bool sh, bool tfo);

	// Getter methods.
	bool getShareable() const {return shareable;}
	bool getTwoForOne() const {return twoForOne;}

	// Override of the toString method from the base class.
	std::string toString() const override;
};
