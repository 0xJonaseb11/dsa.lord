#include <iostream>
#include <memory>
#include <optional>
#include <string>

struct TabNode {
    std::string url;
    std::unique_ptr<TabNode> next;
    TabNode* prev = nullptr;
};

class TabHistory {
public:
    void open(std::string url) {
        auto node = std::make_unique<TabNode>();
        node->url = std::move(url);

        if (current_) {
            node->prev = current_;
            current_->next = std::move(node);
            current_ = current_->next.get();
            return;
        }

        head_ = std::move(node);
        current_ = head_.get();
    }

    std::optional<std::string> back() {
        if (!current_ || !current_->prev) {
            return std::nullopt;
        }
        current_ = current_->prev;
        return current_->url;
    }

    std::optional<std::string> forward() {
        if (!current_ || !current_->next) {
            return std::nullopt;
        }
        current_ = current_->next.get();
        return current_->url;
    }

    void print() const {
        for (TabNode* node = head_.get(); node; node = node->next.get()) {
            std::cout << (node == current_ ? "> " : "  ") << node->url << '\n';
        }
    }

private:
    std::unique_ptr<TabNode> head_;
    TabNode* current_ = nullptr;
};

int main() {
    TabHistory tabs;
    tabs.open("https://mail.example");
    tabs.open("https://docs.example/report");
    tabs.open("https://docs.example/edit");

    tabs.back();
    tabs.forward();
    tabs.print();
    return 0;
}
