#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using Graph = std::unordered_map<std::string, std::vector<std::pair<std::string, int>>>;

std::unordered_map<std::string, int> dijkstra(const Graph& graph, const std::string& start) {
    std::unordered_map<std::string, int> dist;
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
        for (const auto& [next, weight] : graph.at(node)) {
            int next_cost = cost + weight;
            if (next_cost < dist[next]) {
                dist[next] = next_cost;
                queue.push({next_cost, next});
            }
        }
    }
    return dist;
}

int main() {
    Graph routes = {
        {"Depot", {{"Kimihurura", 4}, {"Nyabugogo", 7}}},
        {"Kimihurura", {{"Remera", 3}, {"Kacyiru", 5}}},
        {"Nyabugogo", {{"Kacyiru", 2}}},
        {"Remera", {{"Airport", 6}}},
        {"Kacyiru", {{"Airport", 4}}},
        {"Airport", {}},
    };

    auto costs = dijkstra(routes, "Depot");
    for (const auto& [stop, minutes] : costs) {
        std::cout << stop << " " << minutes << " min\n";
    }
    return 0;
}
