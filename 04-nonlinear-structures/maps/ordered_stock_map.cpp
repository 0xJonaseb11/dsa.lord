#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> stock;
    stock["keyboard"] = 42;
    stock["mouse"] = 88;
    stock["monitor"] = 15;
    stock["hub"] = 63;

    for (const auto& [item, quantity] : stock) {
        std::cout << item << " " << quantity << '\n';
    }

    auto it = stock.lower_bound("m");
    if (it != stock.end()) {
        std::cout << "first from m: " << it->first << '\n';
    }
    return 0;
}
