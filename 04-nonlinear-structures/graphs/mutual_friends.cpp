#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using Graph = std::unordered_map<std::string, std::vector<std::string>>;

std::vector<std::string> mutual_friends(
    const Graph& graph, const std::string& user_a, const std::string& user_b) {
    std::unordered_set<std::string> friends_a(graph.at(user_a).begin(), graph.at(user_a).end());
    std::vector<std::string> shared;

    for (const auto& friend_name : graph.at(user_b)) {
        if (friends_a.count(friend_name)) {
            shared.push_back(friend_name);
        }
    }
    return shared;
}

int main() {
    Graph network = {
        {"Alice", {"Brian", "Claire", "David"}},
        {"Brian", {"Alice", "Claire", "Eric"}},
        {"Claire", {"Alice", "Brian", "Fiona"}},
        {"David", {"Alice"}},
        {"Eric", {"Brian"}},
        {"Fiona", {"Claire"}},
    };

    for (const auto& name : mutual_friends(network, "Alice", "Brian")) {
        std::cout << name << '\n';
    }
    return 0;
}
