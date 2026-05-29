#include <iostream>
#include <unordered_map>
#include <vector>

using Folder = std::unordered_map<std::string, std::vector<std::string>>;

int folder_size_kb(const Folder& tree, const std::string& node, const std::unordered_map<std::string, int>& file_sizes) {
    int total = file_sizes.count(node) ? file_sizes.at(node) : 0;
    if (!tree.count(node)) {
        return total;
    }
    for (const auto& child : tree.at(node)) {
        total += folder_size_kb(tree, child, file_sizes);
    }
    return total;
}

int main() {
    Folder tree = {
        {"root", {"src", "assets"}},
        {"src", {"main.cpp", "utils"}},
        {"utils", {"parser.cpp"}},
        {"assets", {"logo.png"}},
    };

    std::unordered_map<std::string, int> sizes = {
        {"main.cpp", 12},
        {"parser.cpp", 8},
        {"logo.png", 240},
    };

    std::cout << "project size=" << folder_size_kb(tree, "root", sizes) << " KB\n";
    return 0;
}
