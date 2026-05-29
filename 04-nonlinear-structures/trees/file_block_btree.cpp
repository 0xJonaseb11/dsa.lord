#include <algorithm>
#include <iostream>
#include <vector>

class FileBlockIndex {
public:
    explicit FileBlockIndex(size_t block_capacity) : block_capacity_(block_capacity) {
        blocks_.push_back({});
    }

    void insert(int block_id) {
        for (auto& block : blocks_) {
            if (std::binary_search(block.begin(), block.end(), block_id)) {
                return;
            }
        }

        auto& block = blocks_.back();
        auto position = std::lower_bound(block.begin(), block.end(), block_id);
        block.insert(position, block_id);

        if (block.size() > block_capacity_) {
            std::vector<int> split(block.begin() + static_cast<std::ptrdiff_t>(block_capacity_ / 2), block.end());
            block.erase(block.begin() + static_cast<std::ptrdiff_t>(block_capacity_ / 2), block.end());
            blocks_.push_back(std::move(split));
        }
    }

    bool contains(int block_id) const {
        for (const auto& block : blocks_) {
            if (std::binary_search(block.begin(), block.end(), block_id)) {
                return true;
            }
        }
        return false;
    }

    void print() const {
        for (size_t i = 0; i < blocks_.size(); ++i) {
            std::cout << "block " << i << ':';
            for (int id : blocks_[i]) {
                std::cout << ' ' << id;
            }
            std::cout << '\n';
        }
    }

private:
    size_t block_capacity_;
    std::vector<std::vector<int>> blocks_;
};

int main() {
    FileBlockIndex index(3);
    for (int id : {10, 20, 5, 6, 12, 30, 7, 17}) {
        index.insert(id);
    }

    index.print();
    std::cout << std::boolalpha;
    std::cout << "has 6 " << index.contains(6) << '\n';
    std::cout << "has 15 " << index.contains(15) << '\n';
    return 0;
}
