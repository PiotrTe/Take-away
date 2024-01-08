
#include "Order.h"
#include "Menu.h"
#include "Appetiser.h"
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm> // added for sorting
#include <fstream>
// Constructor initializes an Order with a list of menu items.
Order::Order(std::vector<std::pair<int, std::shared_ptr<Item>>> list)
{
    items = std::move(list);
}

// Method to add an item to the order by ID.
void Order::addItem(int id) {
    if (id < 1 || id > items.size()) { // added range validation
        std::cout << "Invalid ID: " << id << ". Must be between 1 and " << items.size() << ".\n";
        return;
    }
    std::shared_ptr<Item> itemPtr = getItemById(id);
    if (itemPtr) {
        std::cout << itemPtr->getName() << " added to order!" << "\n";
        orderedItems.emplace_back(id, itemPtr);
    } else {
        std::cout << "Item with ID " << id << " not found." << '\n';
        // Handle the error appropriately.
    }
}

// Method to remove an item from the order by ID.
void Order::removeItem(int id){
    auto item = std::find_if(orderedItems.begin(), orderedItems.end(),
       [&id](const std::pair<int, std::shared_ptr<Item>>& element) {
       return element.first == id; });
    if (item != orderedItems.end()) {
        std::cout << item->second->getName() << " removed from order!" << "\n";
        orderedItems.erase(item);
    } else {
        std::cout << "Item with ID " << id << " not in the order.\n";
        // Handle the error appropriately.
    }
}

// Method to print a receipt of the current order.
std::string Order::printReceipt() const {
    std::ostringstream receipt;

    // Header
    receipt << "========== Checkout ==========\n";
    for (const auto& itemPair : orderedItems) {
        receipt << "(" << itemPair.first << ") " << itemPair.second->toString() << '\n';
    }

    std::pair<double, double> totals = calculateTotal();

    if (totals.second > 0) {
        receipt << "2-4-1 discount applied! Savings: " << std::fixed << std::setprecision(2) << totals.second << "$" << '\n';
    }
    receipt << "Total: " << std::fixed << std::setprecision(2) << totals.first << "$" << '\n';

    return receipt.str();
}

// Method for the checkout process of the order.
void Order::checkout() {
    std::string receipt = printReceipt();
    std::cout << receipt;
    std::cout << "Do you want to place your order?\nType 'y' to confirm, or 'n' to go back and modify it.";

    char userResponse;
    std::cin >> userResponse;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

    if (userResponse == 'y' || userResponse == 'Y') {
        writeReceiptToFile(receipt, "receipt.txt");
        std::cout << "Thank you for your order! A receipt has been written to 'receipt.txt'.\n";
        orderedItems.clear(); // Clear the order list after finalizing the order
    } else {
        std::cout << "Order not confirmed. You can modify your order and try again.\n";
    }
}
// Method to calculate the total price of the order, including discounts.
std::pair<double, double> Order::calculateTotal() const {
    std::vector<double> twoForOnePrices;
    total = 0;
    savings = 0;

    for (const auto& itemPair : orderedItems) {
        double price = itemPair.second->getPrice();
        const Appetiser* appetiser = dynamic_cast<const Appetiser*>(itemPair.second.get());
        if (appetiser && appetiser->getType() == 'a') {
            if (appetiser->getTwoForOne()) {
                twoForOnePrices.push_back(price);
            } else {
                total += price;
            }
        } else {
            total += price;
        }
    }

    std::sort(twoForOnePrices.begin(), twoForOnePrices.end());

    for (size_t i = 0; i < twoForOnePrices.size() / 2; ++i) {
        savings += twoForOnePrices[i];
        total += twoForOnePrices[twoForOnePrices.size() - 1 - i];
    }

    if (twoForOnePrices.size() % 2 != 0) {
        total += twoForOnePrices[twoForOnePrices.size() / 2];
    }

    return {total, savings};
}

// Method to write the receipt to a file.
void Order::writeReceiptToFile(const std::string& receipt, const std::string& filename)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    outFile << receipt;
    outFile.close();
}

// Method to return a string representation of the order.
std::string Order::toString() const {
    auto sortedItems = orderedItems;
    
    std::sort(sortedItems.begin(), sortedItems.end(),
        [](const std::pair<int, std::shared_ptr<Item>>& a, const std::pair<int, std::shared_ptr<Item>>& b) {
            return a.first < b.first;});
    const std::pair<double, double> totals = calculateTotal();
    std::ostringstream oss;
    
    for (const auto& itemPair : sortedItems) {
        oss << std::setw(2) << itemPair.first << ". " << itemPair.second->toString() << "\n";
    }
    oss << "Total price: " << totals.first << "$" << "\n" << "Applied discount: " << totals.second << "$" << "\n";

    return oss.str();
}