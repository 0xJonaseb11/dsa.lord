#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using Graph = std::unordered_map<std::string, std::vector<std::string>>;

std::vector<std::string> install_order(const Graph& deps) {
    std::unordered_map<std::string, int> indegree;
    for (const auto& [pkg, edges] : deps) {
        if (!indegree.count(pkg)) {
            indegree[pkg] = 0;
        }
        for (const auto& next : edges) {
            ++indegree[next];
        }
    }

    std::queue<std::string> ready;
    for (const auto& [pkg, count] : indegree) {
        if (count == 0) {
            ready.push(pkg);
        }
    }

    std::vector<std::string> order;
    while (!ready.empty()) {
        std::string pkg = ready.front();
        ready.pop();
        order.push_back(pkg);

        if (!deps.count(pkg)) {
            continue;
        }
        for (const auto& next : deps.at(pkg)) {
            if (--indegree[next] == 0) {
                ready.push(next);
            }
        }
    }
    return order;
}

int main() {
    Graph deps = {
        {"libc", {"core", "net"}},
        {"core", {"ui"}},
        {"net", {"ui"}},
        {"ui", {"app"}},
        {"app", {}},
    };

    for (const auto& pkg : install_order(deps)) {
        std::cout << pkg << '\n';
    }
    return 0;
}
