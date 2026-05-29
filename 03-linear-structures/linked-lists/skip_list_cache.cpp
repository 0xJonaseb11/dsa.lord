#include <iostream>
#include <optional>
#include <string>

struct Node {
    std::string key;
    std::string value;
    Node* next = nullptr;
    Node* express = nullptr;
};

class SkipList {
public:
    SkipList() : head_(new Node{"", "", nullptr, nullptr}) {}
    ~SkipList() { clear(head_); }

    SkipList(const SkipList&) = delete;
    SkipList& operator=(const SkipList&) = delete;

    void put(const std::string& key, const std::string& value) {
        Node* prev = head_;
        Node* current = head_->next;

        while (current && current->key < key) {
            prev = current;
            current = current->next;
        }

        if (current && current->key == key) {
            current->value = value;
            return;
        }

        Node* node = new Node{key, value, current, nullptr};
        prev->next = node;
        rebuild_express();
    }

    std::optional<std::string> get(const std::string& key) const {
        Node* current = head_->express ? head_->express : head_;
        while (current && current->key < key) {
            if (current->express && current->express->key <= key) {
                current = current->express;
            } else {
                current = current->next;
            }
        }
        while (current && current->key < key) {
            current = current->next;
        }
        if (current && current->key == key) {
            return current->value;
        }
        return std::nullopt;
    }

private:
    Node* head_;

    void clear(Node* node) {
        while (node) {
            Node* next = node->next;
            delete node;
            node = next;
        }
    }

    void rebuild_express() {
        head_->express = nullptr;
        for (Node* node = head_; node; node = node->next) {
            node->express = nullptr;
        }

        Node* express = head_;
        Node* walker = head_->next;
        int count = 0;
        while (walker) {
            ++count;
            if (count % 2 == 0) {
                express->express = walker;
                express = walker;
            }
            walker = walker->next;
        }
    }
};

int main() {
    SkipList cache;
    cache.put("user:100", "Alice");
    cache.put("user:200", "Brian");
    cache.put("user:300", "Claire");

    if (auto name = cache.get("user:200")) {
        std::cout << *name << '\n';
    }
    return 0;
}
