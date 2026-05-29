#include <iostream>
#include <optional>
#include <string>
#include <vector>

class EmployeeRegistry {
public:
    explicit EmployeeRegistry(size_t capacity) : keys_(capacity), values_(capacity), occupied_(capacity, false) {}

    void put(const std::string& key, const std::string& value) {
        size_t index = probe_for_insert(key);
        keys_[index] = key;
        values_[index] = value;
        occupied_[index] = true;
    }

    std::optional<std::string> get(const std::string& key) const {
        size_t index = probe_for_lookup(key);
        if (!occupied_[index] || keys_[index] != key) {
            return std::nullopt;
        }
        return values_[index];
    }

private:
    size_t hash1(const std::string& key) const {
        return base_hash(key) % keys_.size();
    }

    size_t hash2(const std::string& key) const {
        size_t size = keys_.size();
        return size - (base_hash(key) % (size - 1)) - 1;
    }

    size_t base_hash(const std::string& key) const {
        size_t h = 0;
        for (char ch : key) {
            h = h * 131 + static_cast<unsigned char>(ch);
        }
        return h;
    }

    size_t probe_for_insert(const std::string& key) const {
        size_t index = hash1(key);
        size_t step = hash2(key);
        if (step == 0) {
            step = 1;
        }

        for (size_t i = 0; i < keys_.size(); ++i) {
            if (!occupied_[index] || keys_[index] == key) {
                return index;
            }
            index = (index + step) % keys_.size();
        }
        return index;
    }

    size_t probe_for_lookup(const std::string& key) const {
        size_t index = hash1(key);
        size_t step = hash2(key);
        if (step == 0) {
            step = 1;
        }

        for (size_t i = 0; i < keys_.size(); ++i) {
            if (!occupied_[index]) {
                return index;
            }
            if (keys_[index] == key) {
                return index;
            }
            index = (index + step) % keys_.size();
        }
        return index;
    }

    std::vector<std::string> keys_;
    std::vector<std::string> values_;
    std::vector<bool> occupied_;
};

int main() {
    EmployeeRegistry registry(16);
    registry.put("EMP-001", "Operations");
    registry.put("EMP-014", "Engineering");
    registry.put("EMP-027", "Finance");

    if (auto dept = registry.get("EMP-014")) {
        std::cout << *dept << '\n';
    }
    return 0;
}
