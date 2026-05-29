#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Sale {
    std::string sku;
    int units;
    double revenue;
};

void sort_by_revenue(std::vector<Sale>& sales) {
    std::sort(sales.begin(), sales.end(), [](const Sale& a, const Sale& b) {
        return a.revenue > b.revenue;
    });
}

int main() {
    std::vector<Sale> daily = {
        {"SKU-11", 4, 320.0},
        {"SKU-07", 12, 540.0},
        {"SKU-03", 2, 180.0},
    };

    sort_by_revenue(daily);
    for (const auto& sale : daily) {
        std::cout << sale.sku << " " << sale.revenue << '\n';
    }
    return 0;
}
