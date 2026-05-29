#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::vector<std::string>> seating = {
        {"A1", "A2", "A3"},
        {"B1", "B2"},
        {"C1", "C2", "C3", "C4"},
    };

    for (size_t row = 0; row < seating.size(); ++row) {
        std::cout << "row " << row << ": ";
        for (const auto& seat : seating[row]) {
            std::cout << seat << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
