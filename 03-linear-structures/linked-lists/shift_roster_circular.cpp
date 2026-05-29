#include <iostream>
#include <string>

struct WorkerNode {
    std::string name;
    WorkerNode* next = nullptr;
};

class ShiftRoster {
public:
    ShiftRoster() = default;

    ~ShiftRoster() {
        if (!tail_) {
            return;
        }
        WorkerNode* start = tail_->next;
        tail_->next = nullptr;
        while (start) {
            WorkerNode* next = start->next;
            delete start;
            start = next;
        }
    }

    ShiftRoster(const ShiftRoster&) = delete;
    ShiftRoster& operator=(const ShiftRoster&) = delete;

    void add(std::string name) {
        auto* node = new WorkerNode{std::move(name), nullptr};
        if (!tail_) {
            node->next = node;
            tail_ = node;
            return;
        }
        node->next = tail_->next;
        tail_->next = node;
        tail_ = node;
    }

    std::string next_worker() {
        if (!tail_) {
            return "";
        }
        tail_ = tail_->next;
        return tail_->name;
    }

private:
    WorkerNode* tail_ = nullptr;
};

int main() {
    ShiftRoster roster;
    roster.add("Alice");
    roster.add("Brian");
    roster.add("Claire");

    for (int round = 0; round < 6; ++round) {
        std::cout << roster.next_worker() << '\n';
    }
    return 0;
}
