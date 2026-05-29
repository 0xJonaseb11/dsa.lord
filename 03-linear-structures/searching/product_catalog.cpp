#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Product {
    std::string sku;
    std::string name;
    double price;
};

const Product* find_by_sku(const std::vector<Product>& catalog, const std::string& sku) {
    for (const auto& product : catalog) {
        if (product.sku == sku) {
            return &product;
        }
    }
    return nullptr;
}

const Product* binary_search_sku(const std::vector<Product>& catalog, const std::string& sku) {
    auto it = std::lower_bound(
        catalog.begin(), catalog.end(), sku,
        [](const Product& product, const std::string& key) { return product.sku < key; });
    if (it != catalog.end() && it->sku == sku) {
        return &(*it);
    }
    return nullptr;
}

int main() {
    std::vector<Product> catalog = {
        {"SKU-01", "Keyboard", 45.0},
        {"SKU-02", "Mouse", 25.0},
        {"SKU-03", "Monitor", 180.0},
    };

    if (const Product* found = find_by_sku(catalog, "SKU-02")) {
        std::cout << found->name << " " << found->price << '\n';
    }

    if (const Product* found = binary_search_sku(catalog, "SKU-03")) {
        std::cout << found->name << " " << found->price << '\n';
    }
    return 0;
}
