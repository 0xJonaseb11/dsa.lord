#include <iostream>
#include <optional>
#include <string>
#include <vector>

class BrowserHistory {
public:
    void visit(const std::string& url) {
        stack_.push_back(url);
    }

    std::optional<std::string> back() {
        if (stack_.size() <= 1) {
            return std::nullopt;
        }
        stack_.pop_back();
        return stack_.back();
    }

    void print() const {
        for (const auto& url : stack_) {
            std::cout << url << '\n';
        }
    }

private:
    std::vector<std::string> stack_;
};

int main() {
    BrowserHistory history;
    history.visit("https://news.example");
    history.visit("https://shop.example/cart");
    history.visit("https://shop.example/checkout");

    if (auto page = history.back()) {
        std::cout << "current: " << *page << '\n';
    }
    history.print();
    return 0;
}
