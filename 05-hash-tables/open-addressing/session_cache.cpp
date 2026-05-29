#include <iostream>
#include <optional>
#include <string>
#include <vector>

class SessionCache {
public:
    explicit SessionCache(size_t capacity) : keys_(capacity), values_(capacity), occupied_(capacity, false) {}

    void put(const std::string& key, const std::string& value) {
        size_t index = probe(key);
        keys_[index] = key;
        values_[index] = value;
        occupied_[index] = true;
    }

    std::optional<std::string> get(const std::string& key) const {
        size_t index = probe(key);
        if (!occupied_[index] || keys_[index] != key) {
            return std::nullopt;
        }
        return values_[index];
    }

private:
    size_t hash(const std::string& key) const {
        size_t h = 0;
        for (char ch : key) {
            h = h * 131 + static_cast<unsigned char>(ch);
        }
        return h;
    }

    size_t probe(const std::string& key) const {
        size_t index = hash(key) % keys_.size();
        while (occupied_[index] && keys_[index] != key) {
            index = (index + 1) % keys_.size();
        }
        return index;
    }

    std::vector<std::string> keys_;
    std::vector<std::string> values_;
    std::vector<bool> occupied_;
};

int main() {
    SessionCache cache(16);
    cache.put("session-42", "user:1024");
    cache.put("session-77", "user:2048");

    if (auto user = cache.get("session-42")) {
        std::cout << *user << '\n';
    }
    return 0;
}
