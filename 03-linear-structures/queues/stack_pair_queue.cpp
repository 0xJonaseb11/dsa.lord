#include <iostream>
#include <optional>
#include <stack>
#include <string>

class TaskQueue {
public:
    void enqueue(const std::string& task) {
        in_stack_.push(task);
    }

    std::optional<std::string> dequeue() {
        move_if_needed();
        if (out_stack_.empty()) {
            return std::nullopt;
        }
        std::string task = out_stack_.top();
        out_stack_.pop();
        return task;
    }

private:
    std::stack<std::string> in_stack_;
    std::stack<std::string> out_stack_;

    void move_if_needed() {
        if (!out_stack_.empty()) {
            return;
        }
        while (!in_stack_.empty()) {
            out_stack_.push(in_stack_.top());
            in_stack_.pop();
        }
    }
};

int main() {
    TaskQueue queue;
    queue.enqueue("compile");
    queue.enqueue("test");
    queue.enqueue("deploy");

    while (true) {
        if (auto task = queue.dequeue()) {
            std::cout << *task << '\n';
        } else {
            break;
        }
    }
    return 0;
}
