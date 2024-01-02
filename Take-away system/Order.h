#pragma once
#include "ItemList.h"

class Order : public ItemList {

private:
    mutable double total;
    mutable double savings;
    std::vector<std::pair<int, std::shared_ptr<Item>>> orderedItems;

public:
    explicit Order(std::vector<std::pair<int, std::shared_ptr<Item>>>);
    void addItem(int id);
    void removeItem(int id);
    std::string printReceipt() const;
    void checkout();
    std::pair<double, double> calculateTotal() const;
    static void writeReceiptToFile(const std::string& receipt, const std::string& filename);

    std::string toString() const override;
};
