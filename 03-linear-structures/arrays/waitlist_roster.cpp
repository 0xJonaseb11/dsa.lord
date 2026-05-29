#include <iostream>
#include <string>
#include <vector>

void insert_at(std::vector<std::string>& roster, size_t index, const std::string& name) {
    if (index > roster.size()) {
        return;
    }
    roster.insert(roster.begin() + static_cast<std::ptrdiff_t>(index), name);
}

void remove_at(std::vector<std::string>& roster, size_t index) {
    if (index >= roster.size()) {
        return;
    }
    roster.erase(roster.begin() + static_cast<std::ptrdiff_t>(index));
}

int main() {
    std::vector<std::string> roster = {"Alice", "Brian", "Claire"};
    insert_at(roster, 1, "David");
    remove_at(roster, 2);

    for (const auto& name : roster) {
        std::cout << name << '\n';
    }
    return 0;
}
