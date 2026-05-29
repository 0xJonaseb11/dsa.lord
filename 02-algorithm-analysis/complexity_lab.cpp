#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct ComplexityRow {
    std::string structure;
    std::string access;
    std::string search;
    std::string insert;
    std::string remove;
};

void print_table(const std::vector<ComplexityRow>& rows) {
    for (const auto& row : rows) {
        std::cout << row.structure << " | access=" << row.access
                  << " search=" << row.search
                  << " insert=" << row.insert
                  << " remove=" << row.remove << '\n';
    }
}

int count_pairs(const std::vector<int>& data) {
    int pairs = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = i + 1; j < data.size(); ++j) {
            if (data[i] == data[j]) {
                ++pairs;
            }
        }
    }
    return pairs;
}

int main() {
    std::vector<ComplexityRow> table = {
        {"array", "O(1)", "O(n)", "O(n)", "O(n)"},
        {"linked_list", "O(n)", "O(n)", "O(1)*", "O(1)*"},
        {"hash_table", "-", "O(1)*", "O(1)*", "O(1)*"},
        {"bst", "O(log n)", "O(log n)", "O(log n)", "O(log n)"},
        {"heap", "-", "O(n)", "O(log n)", "O(log n)"},
    };

    print_table(table);

    std::unordered_map<int, int> freq;
    std::vector<int> sample = {4, 1, 4, 2, 1, 4};
    for (int value : sample) {
        ++freq[value];
    }

    std::cout << "hash duplicates=" << (sample.size() - freq.size()) << '\n';
    std::cout << "pair_scan=" << count_pairs(sample) << '\n';
    return 0;
}
