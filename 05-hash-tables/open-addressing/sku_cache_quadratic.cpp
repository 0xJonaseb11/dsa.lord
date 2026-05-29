#include <iostream>
#include <optional>
#include <string>
#include <vector>

class SkuCache {
public:
    explicit SkuCache(size_t capacity) : keys_(capacity), values_(capacity), occupied_(capacity, false) {}

    void put(const std::string& key, const std::string& value) {
        size_t index = hash(key) % keys_.size();
        size_t step = 1;

        for (size_t i = 0; i < keys_.size(); ++i) {
            if (!occupied_[index] || keys_[index] == key) {
                keys_[index] = key;
                values_[index] = value;
                occupied_[index] = true;
                return;
            }
            index = (index + step * step) % keys_.size();
            ++step;
        }
    }

    std::optional<std::string> get(const std::string& key) const {
        size_t index = hash(key) % keys_.size();
        size_t step = 1;

        for (size_t i = 0; i < keys_.size(); ++i) {
            if (!occupied_[index]) {
                return std::nullopt;
            }
            if (keys_[index] == key) {
                return values_[index];
            }
            index = (index + step * step) % keys_.size();
            ++step;
        }
        return std::nullopt;
    }

private:
    size_t hash(const std::string& key) const {
        size_t h = 0;
        for (char ch : key) {
            h = h * 131 + static_cast<unsigned char>(ch);
        }
        return h;
    }

    std::vector<std::string> keys_;
    std::vector<std::string> values_;
    std::vector<bool> occupied_;
};

int main() {
    SkuCache cache(16);
    cache.put("SKU-1001", "Wireless Mouse");
    cache.put("SKU-1002", "USB Hub");
    cache.put("SKU-1003", "HDMI Cable");

    if (auto name = cache.get("SKU-1002")) {
        std::cout << *name << '\n';
    }
    return 0;
}
