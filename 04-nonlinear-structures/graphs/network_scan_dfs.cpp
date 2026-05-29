#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using Graph = std::unordered_map<std::string, std::vector<std::string>>;

std::vector<std::string> dfs_network(const Graph& graph, const std::string& start) {
    std::vector<std::string> order;
    std::unordered_map<std::string, bool> visited;
    std::stack<std::string> stack;
    stack.push(start);

    while (!stack.empty()) {
        std::string node = stack.top();
        stack.pop();
        if (visited[node]) {
            continue;
        }
        visited[node] = true;
        order.push_back(node);

        for (auto it = graph.at(node).rbegin(); it != graph.at(node).rend(); ++it) {
            stack.push(*it);
        }
    }
    return order;
}

int main() {
    Graph network = {
        {"router-a", {"switch-1", "switch-2"}},
        {"switch-1", {"server-db", "server-api"}},
        {"switch-2", {"server-cache"}},
        {"server-db", {}},
        {"server-api", {}},
        {"server-cache", {}},
    };

    for (const auto& node : dfs_network(network, "router-a")) {
        std::cout << node << '\n';
    }
    return 0;
}
