#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using Graph = std::unordered_map<std::string, std::vector<std::string>>;

std::vector<std::string> topo_order(const Graph& graph) {
    std::unordered_map<std::string, int> indegree;
    for (const auto& [node, edges] : graph) {
        if (!indegree.count(node)) {
            indegree[node] = 0;
        }
        for (const auto& next : edges) {
            ++indegree[next];
        }
    }

    std::queue<std::string> ready;
    for (const auto& [node, degree] : indegree) {
        if (degree == 0) {
            ready.push(node);
        }
    }

    std::vector<std::string> order;
    while (!ready.empty()) {
        std::string node = ready.front();
        ready.pop();
        order.push_back(node);

        if (!graph.count(node)) {
            continue;
        }
        for (const auto& next : graph.at(node)) {
            if (--indegree[next] == 0) {
                ready.push(next);
            }
        }
    }
    return order;
}

int main() {
    Graph pipeline = {
        {"checkout", {"build", "lint"}},
        {"lint", {"test"}},
        {"build", {"test"}},
        {"test", {"deploy"}},
        {"deploy", {}},
    };

    for (const auto& step : topo_order(pipeline)) {
        std::cout << step << '\n';
    }
    return 0;
}
