#include <array>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

class UndoStack {
public:
    explicit UndoStack(size_t capacity) : capacity_(capacity), top_(0) {
        if (capacity_ > buffer_.size()) {
            throw std::invalid_argument("capacity exceeds buffer");
        }
    }

    void push(const std::string& action) {
        if (top_ >= capacity_) {
            throw std::runtime_error("undo stack overflow");
        }
        buffer_[top_++] = action;
    }

    std::optional<std::string> pop() {
        if (top_ == 0) {
            return std::nullopt;
        }
        return buffer_[--top_];
    }

    size_t size() const { return top_; }

private:
    std::array<std::string, 64> buffer_;
    size_t capacity_;
    size_t top_;
};

int main() {
    UndoStack stack(8);
    stack.push("typed title");
    stack.push("added paragraph");
    stack.push("inserted image");

    while (stack.size() > 0) {
        if (auto action = stack.pop()) {
            std::cout << "undo " << *action << '\n';
        }
    }
    return 0;
}
