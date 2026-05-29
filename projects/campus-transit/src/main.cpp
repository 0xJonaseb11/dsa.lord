#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using Graph = std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>;

std::vector<std::string> shortest_path(const Graph& graph, const std::string& start, const std::string& goal) {
    std::unordered_map<std::string, int> dist;
    std::unordered_map<std::string, std::string> parent;

    for (const auto& [node, _] : graph) {
        dist[node] = std::numeric_limits<int>::max();
    }
    dist[start] = 0;

    using State = std::pair<int, std::string>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> queue;
    queue.push({0, start});

    while (!queue.empty()) {
        auto [cost, node] = queue.top();
        queue.pop();
        if (cost > dist[node]) {
            continue;
        }
        if (node == goal) {
            break;
        }
        for (const auto& [next, minutes] : graph.at(node)) {
            int next_cost = cost + minutes;
            if (next_cost < dist[next]) {
                dist[next] = next_cost;
                parent[next] = node;
                queue.push({next_cost, next});
            }
        }
    }

    std::vector<std::string> path;
    if (!parent.count(goal) && start != goal) {
        return path;
    }

    for (std::string node = goal; node != start; node = parent[node]) {
        path.push_back(node);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

int main() {
    Graph campus = {
        {"Gate", {{"Library", 4}, {"Cafeteria", 7}}},
        {"Library", {{"Lab", 3}}},
        {"Cafeteria", {{"Lab", 5}, {"Dorm", 6}}},
        {"Lab", {{"Dorm", 2}}},
        {"Dorm", {}},
    };

    auto path = shortest_path(campus, "Gate", "Dorm");
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i + 1 < path.size()) {
            std::cout << " -> ";
        }
    }
    std::cout << '\n';
    return 0;
}
