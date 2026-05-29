#include <iostream>
#include <string>

struct MemberNode {
    std::string name;
    MemberNode* next = nullptr;
    MemberNode* prev = nullptr;
};

class MeetingCircle {
public:
    MeetingCircle() = default;

    ~MeetingCircle() {
        if (!head_) {
            return;
        }
        MemberNode* node = head_;
        do {
            MemberNode* next = node->next;
            delete node;
            node = next;
        } while (node != head_);
    }

    MeetingCircle(const MeetingCircle&) = delete;
    MeetingCircle& operator=(const MeetingCircle&) = delete;

    void join(std::string name) {
        auto* node = new MemberNode{std::move(name), nullptr, nullptr};
        if (!head_) {
            node->next = node;
            node->prev = node;
            head_ = node;
            return;
        }
        node->next = head_;
        node->prev = head_->prev;
        head_->prev->next = node;
        head_->prev = node;
    }

    std::string pass_token(int steps) {
        if (!head_) {
            return "";
        }
        for (int i = 0; i < steps; ++i) {
            head_ = head_->next;
        }
        return head_->name;
    }

private:
    MemberNode* head_ = nullptr;
};

int main() {
    MeetingCircle circle;
    circle.join("Alice");
    circle.join("Brian");
    circle.join("Claire");

    std::cout << circle.pass_token(1) << '\n';
    std::cout << circle.pass_token(2) << '\n';
    return 0;
}
