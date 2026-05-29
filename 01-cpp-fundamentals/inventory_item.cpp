#include <iostream>
#include <string>

class InventoryItem {
public:
    InventoryItem(std::string sku, std::string name, int quantity, double unit_price)
        : sku_(std::move(sku)), name_(std::move(name)), quantity_(quantity), unit_price_(unit_price) {}

    ~InventoryItem() = default;

    void restock(int units) {
        if (units <= 0) {
            return;
        }
        quantity_ += units;
    }

    bool sell(int units) {
        if (units <= 0 || units > quantity_) {
            return false;
        }
        quantity_ -= units;
        return true;
    }

    double stock_value() const { return quantity_ * unit_price_; }

    void print() const {
        std::cout << sku_ << " | " << name_ << " | qty=" << quantity_
                  << " | value=" << stock_value() << '\n';
    }

private:
    std::string sku_;
    std::string name_;
    int quantity_;
    double unit_price_;
};

int main() {
    InventoryItem laptop("SKU-1042", "Business Laptop", 12, 899.99);
    laptop.sell(3);
    laptop.restock(5);
    laptop.print();
    return 0;
}
