#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using Network = std::unordered_map<std::string, std::vector<std::string>>;

int degrees_apart(const Network& graph, const std::string& from, const std::string& to) {
    if (from == to) {
        return 0;
    }

    std::queue<std::string> queue;
    std::unordered_map<std::string, int> depth;
    queue.push(from);
    depth[from] = 0;

    while (!queue.empty()) {
        std::string person = queue.front();
        queue.pop();

        for (const auto& friend_name : graph.at(person)) {
            if (depth.count(friend_name)) {
                continue;
            }
            depth[friend_name] = depth[person] + 1;
            if (friend_name == to) {
                return depth[friend_name];
            }
            queue.push(friend_name);
        }
    }
    return -1;
}

int main() {
    Network graph = {
        {"Jonas", {"Mira", "Paul"}},
        {"Mira", {"Jonas", "Lea", "Noah"}},
        {"Paul", {"Jonas", "Lea"}},
        {"Lea", {"Mira", "Paul", "Zoe"}},
        {"Noah", {"Mira"}},
        {"Zoe", {"Lea"}},
    };

    std::cout << "Jonas to Zoe: " << degrees_apart(graph, "Jonas", "Zoe") << '\n';
    std::cout << "Noah to Paul: " << degrees_apart(graph, "Noah", "Paul") << '\n';
    return 0;
}
