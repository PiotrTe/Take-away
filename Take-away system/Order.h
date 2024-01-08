#pragma once
#include "ItemList.h"

class Order : public ItemList {
private:
    mutable double total; // Total cost of the order.
    mutable double savings; // Savings applied to the order.
    std::vector<std::pair<int, std::shared_ptr<Item>>> orderedItems; // List of ordered items.

public:
    // Constructor: Initializes an Order with a list of items.
    explicit Order(std::vector<std::pair<int, std::shared_ptr<Item>>>);

    // Method to add an item to the order.
    void addItem(int id);

    // Method to remove an item from the order.
    void removeItem(int id);

    // Method to print a receipt of the order.
    std::string printReceipt() const;

    // Method for processing the checkout of the order.
    void checkout();

    // Method to calculate the total cost and savings of the order.
    std::pair<double, double> calculateTotal() const;

    // Static method to write the receipt to a file.
    static void writeReceiptToFile(const std::string& receipt, const std::string& filename);

    // Method to return a string representation of the order.
    std::string toString() const override;
};
