#include <array>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

class CallQueue {
public:
    explicit CallQueue(size_t capacity) : capacity_(capacity), head_(0), tail_(0), count_(0) {}

    void enqueue(const std::string& caller) {
        if (count_ >= capacity_) {
            throw std::runtime_error("call queue full");
        }
        buffer_[tail_] = caller;
        tail_ = (tail_ + 1) % capacity_;
        ++count_;
    }

    std::optional<std::string> dequeue() {
        if (count_ == 0) {
            return std::nullopt;
        }
        std::string caller = buffer_[head_];
        head_ = (head_ + 1) % capacity_;
        --count_;
        return caller;
    }

    size_t waiting() const { return count_; }

private:
    static constexpr size_t kMaxCalls = 32;
    std::array<std::string, kMaxCalls> buffer_{};
    size_t capacity_;
    size_t head_;
    size_t tail_;
    size_t count_;
};

int main() {
    CallQueue queue(4);
    queue.enqueue("+250788111001");
    queue.enqueue("+250788111002");
    queue.enqueue("+250788111003");

    while (queue.waiting() > 0) {
        if (auto caller = queue.dequeue()) {
            std::cout << "serving " << *caller << '\n';
        }
    }
    return 0;
}
