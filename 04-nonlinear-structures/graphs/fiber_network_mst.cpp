#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

struct Edge {
    std::string from;
    std::string to;
    int cost;
};

class UnionFind {
public:
    explicit UnionFind(const std::vector<std::string>& nodes) {
        for (const auto& node : nodes) {
            parent_[node] = node;
        }
    }

    std::string find(const std::string& node) {
        if (parent_[node] != node) {
            parent_[node] = find(parent_[node]);
        }
        return parent_[node];
    }

    bool unite(const std::string& a, const std::string& b) {
        std::string root_a = find(a);
        std::string root_b = find(b);
        if (root_a == root_b) {
            return false;
        }
        parent_[root_b] = root_a;
        return true;
    }

private:
    std::unordered_map<std::string, std::string> parent_;
};

int main() {
    std::vector<std::string> sites = {"HQ", "Branch-A", "Branch-B", "Branch-C", "DataCenter"};
    std::vector<Edge> links = {
        {"HQ", "Branch-A", 4},
        {"HQ", "Branch-B", 6},
        {"Branch-A", "Branch-C", 3},
        {"Branch-B", "Branch-C", 2},
        {"Branch-C", "DataCenter", 5},
        {"Branch-A", "DataCenter", 10},
    };

    std::sort(links.begin(), links.end(), [](const Edge& a, const Edge& b) {
        return a.cost < b.cost;
    });

    UnionFind dsu(sites);
    int total_cost = 0;

    for (const auto& link : links) {
        if (!dsu.unite(link.from, link.to)) {
            continue;
        }
        total_cost += link.cost;
        std::cout << link.from << " - " << link.to << " " << link.cost << '\n';
    }

    std::cout << "total=" << total_cost << '\n';
    return 0;
}
