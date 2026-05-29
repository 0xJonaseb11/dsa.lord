#include <iostream>
#include <list>
#include <optional>
#include <string>
#include <unordered_map>

class PageCache {
public:
    explicit PageCache(size_t capacity) : capacity_(capacity) {}

    void access(const std::string& page) {
        auto found = lookup_.find(page);
        if (found != lookup_.end()) {
            order_.splice(order_.begin(), order_, found->second);
            return;
        }

        if (order_.size() >= capacity_) {
            const std::string& evicted = order_.back();
            lookup_.erase(evicted);
            order_.pop_back();
        }

        order_.push_front(page);
        lookup_[page] = order_.begin();
    }

    std::optional<std::string> most_recent() const {
        if (order_.empty()) {
            return std::nullopt;
        }
        return order_.front();
    }

    void print() const {
        for (const auto& page : order_) {
            std::cout << page << '\n';
        }
    }

private:
    size_t capacity_;
    std::list<std::string> order_;
    std::unordered_map<std::string, std::list<std::string>::iterator> lookup_;
};

int main() {
    PageCache cache(3);
    cache.access("/home");
    cache.access("/products");
    cache.access("/cart");
    cache.access("/home");
    cache.access("/checkout");

    cache.print();
    return 0;
}
