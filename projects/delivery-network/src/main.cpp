#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using Graph = std::unordered_map<std::string, std::vector<std::string>>;

std::vector<std::string> bfs_stops(const Graph& graph, const std::string& start) {
    std::vector<std::string> order;
    std::unordered_map<std::string, bool> seen;
    std::queue<std::string> queue;
    queue.push(start);

    while (!queue.empty()) {
        std::string stop = queue.front();
        queue.pop();
        if (seen[stop]) {
            continue;
        }
        seen[stop] = true;
        order.push_back(stop);

        for (const auto& next : graph.at(stop)) {
            queue.push(next);
        }
    }
    return order;
}

std::vector<std::string> dfs_stops(const Graph& graph, const std::string& start) {
    std::vector<std::string> order;
    std::unordered_map<std::string, bool> seen;
    std::stack<std::string> stack;
    stack.push(start);

    while (!stack.empty()) {
        std::string stop = stack.top();
        stack.pop();
        if (seen[stop]) {
            continue;
        }
        seen[stop] = true;
        order.push_back(stop);

        const auto& neighbors = graph.at(stop);
        for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
            stack.push(*it);
        }
    }
    return order;
}

int main() {
    Graph routes = {
        {"Depot", {"NorthHub", "EastHub"}},
        {"NorthHub", {"ShopA", "ShopB"}},
        {"EastHub", {"ShopC"}},
        {"ShopA", {}},
        {"ShopB", {"ShopC"}},
        {"ShopC", {}},
    };

    std::cout << "bfs:";
    for (const auto& stop : bfs_stops(routes, "Depot")) {
        std::cout << ' ' << stop;
    }
    std::cout << "\ndfs:";
    for (const auto& stop : dfs_stops(routes, "Depot")) {
        std::cout << ' ' << stop;
    }
    std::cout << '\n';
    return 0;
}
