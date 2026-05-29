#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using Node = std::unordered_map<std::string, std::vector<std::string>>;

void walk(const Node& tree, const std::string& current, int depth) {
    std::cout << std::string(depth * 2, ' ') << current << '\n';
    if (!tree.count(current)) {
        return;
    }
    for (const auto& child : tree.at(current)) {
        walk(tree, child, depth + 1);
    }
}

int main() {
    Node project = {
        {"root", {"src", "docs"}},
        {"src", {"main.cpp", "utils"}},
        {"utils", {"parser.cpp"}},
        {"docs", {"readme.md"}},
    };

    walk(project, "root", 0);
    return 0;
}
