
#include "Order.h"
#include "Menu.h"
#include "Appetiser.h"
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm> // added for sorting
#include <fstream>

class Appetiser;

Order::Order(std::vector<std::pair<int, std::shared_ptr<Item>>> list)
{
    items = std::move(list);
}

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
// Implemented calculateTotal function to sum all prices in orderedItems list
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
void Order::writeReceiptToFile(const std::string& receipt, const std::string& filename)
{
    // Open the file in write mode. This will overwrite any existing file.
    std::ofstream outFile(filename);

    // Check if the file is open.
    if (!outFile.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    // Write the receipt to the file.
    outFile << receipt;

    // Close the file.
    outFile.close();
}

std::string Order::toString() const {
    // Make a copy of the orderedItems vector to sort, because this method is const
    auto sortedItems = orderedItems;
    std::sort(sortedItems.begin(), sortedItems.end(),
        [](const std::pair<int, std::shared_ptr<Item>>& a, const std::pair<int, std::shared_ptr<Item>>& b) {
            return a.first < b.first;
        });

    // We call calculateTotal here to ensure total is updated.
    const std::pair<double, double> totals = calculateTotal(); 

    std::ostringstream oss;
    for (const auto& itemPair : sortedItems) {
        oss << std::setw(2) << itemPair.first << ". " << itemPair.second->toString() << "\n";
    }

    // Use the values returned from calculateTotal function.
    oss << "Total price: " << totals.first << "$" << "\n" << "Applied discount: " << totals.second << "$" << "\n";

    return oss.str();
}