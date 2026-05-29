#include <iostream>
#include <string>
#include <vector>

using ShelfGrid = std::vector<std::vector<std::string>>;

int count_items(const ShelfGrid& grid, const std::string& sku) {
    int total = 0;
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell == sku) {
                ++total;
            }
        }
    }
    return total;
}

void restock(ShelfGrid& grid, int row, int col, const std::string& sku) {
    grid[row][col] = sku;
}

int main() {
    ShelfGrid warehouse = {
        {"SKU-01", "SKU-02", "SKU-01"},
        {"SKU-03", "SKU-01", "SKU-04"},
        {"SKU-02", "SKU-02", "SKU-03"},
    };

    restock(warehouse, 1, 2, "SKU-05");
    std::cout << "SKU-01 count=" << count_items(warehouse, "SKU-01") << '\n';
    std::cout << "SKU-05 count=" << count_items(warehouse, "SKU-05") << '\n';
    return 0;
}
