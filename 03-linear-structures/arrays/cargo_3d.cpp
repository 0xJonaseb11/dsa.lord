#include <iostream>
#include <vector>

int total_units(const std::vector<std::vector<std::vector<int>>>& warehouse) {
    int total = 0;
    for (const auto& floor : warehouse) {
        for (const auto& aisle : floor) {
            for (int crate : aisle) {
                total += crate;
            }
        }
    }
    return total;
}

int main() {
    std::vector<std::vector<std::vector<int>>> warehouse = {
        {
            {12, 8, 5},
            {4, 9},
        },
        {
            {7, 7, 7},
            {3, 3, 3, 3},
        },
    };

    std::cout << "units=" << total_units(warehouse) << '\n';
    return 0;
}
