#include <iostream>
#include <memory>
#include <optional>
#include <string>

struct TaskNode {
    std::string label;
    std::unique_ptr<TaskNode> next;
};

class TaskStack {
public:
    void push(std::string label) {
        auto node = std::make_unique<TaskNode>();
        node->label = std::move(label);
        node->next = std::move(head_);
        head_ = std::move(node);
    }

    std::optional<std::string> pop() {
        if (!head_) {
            return std::nullopt;
        }
        std::string label = head_->label;
        head_ = std::move(head_->next);
        return label;
    }

private:
    std::unique_ptr<TaskNode> head_;
};

int main() {
    TaskStack stack;
    stack.push("compile module");
    stack.push("run tests");
    stack.push("deploy build");

    while (true) {
        if (auto task = stack.pop()) {
            std::cout << *task << '\n';
        } else {
            break;
        }
    }
    return 0;
}
