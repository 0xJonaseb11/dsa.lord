#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace billing {

struct LineItem {
    std::string description;
    int quantity;
    double unit_price;
};

double line_total(const LineItem& item) {
    return item.quantity * item.unit_price;
}

void print_invoice(const std::string& customer, const std::vector<LineItem>& items, double tax_rate) {
    double subtotal = 0;
    for (const auto& item : items) {
        subtotal += line_total(item);
    }
    double tax = subtotal * tax_rate;
    double total = subtotal + tax;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "customer: " << customer << '\n';
    for (const auto& item : items) {
        std::cout << std::setw(20) << std::left << item.description
                  << std::setw(6) << item.quantity
                  << std::setw(10) << item.unit_price
                  << std::setw(10) << line_total(item) << '\n';
    }
    std::cout << "subtotal " << subtotal << '\n';
    std::cout << "tax " << tax << '\n';
    std::cout << "total " << total << '\n';
}

LineItem parse_line(const std::string& row) {
    std::istringstream stream(row);
    LineItem item;
    stream >> item.description >> item.quantity >> item.unit_price;
    return item;
}

}

int main() {
    std::vector<billing::LineItem> items = {
        billing::parse_line("hosting 1 49.99"),
        billing::parse_line("support 3 15.00"),
        billing::parse_line("storage 2 8.50"),
    };

    billing::print_invoice("Kigali Tech Ltd", items, 0.18);
    return 0;
}
