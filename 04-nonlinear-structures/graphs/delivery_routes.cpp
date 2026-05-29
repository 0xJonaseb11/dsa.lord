#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using Graph = std::unordered_map<std::string, std::vector<std::string>>;

std::vector<std::string> bfs_route(const Graph& graph, const std::string& start, const std::string& target) {
    std::queue<std::string> queue;
    std::unordered_map<std::string, std::string> parent;

    queue.push(start);
    parent[start] = "";

    while (!queue.empty()) {
        std::string node = queue.front();
        queue.pop();
        if (node == target) {
            break;
        }
        for (const auto& next : graph.at(node)) {
            if (parent.count(next)) {
                continue;
            }
            parent[next] = node;
            queue.push(next);
        }
    }

    std::vector<std::string> path;
    if (!parent.count(target)) {
        return path;
    }

    for (std::string node = target; !node.empty(); node = parent[node]) {
        path.push_back(node);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

int main() {
    Graph city = {
        {"Hub", {"Kimihurura", "Nyabugogo"}},
        {"Kimihurura", {"Remera"}},
        {"Nyabugogo", {"Kacyiru"}},
        {"Remera", {"Airport"}},
        {"Kacyiru", {"Airport"}},
    };

    auto path = bfs_route(city, "Hub", "Airport");
    for (const auto& stop : path) {
        std::cout << stop << '\n';
    }
    return 0;
}
