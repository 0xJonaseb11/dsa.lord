#include <chrono>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

using Clock = std::chrono::steady_clock;

long long linear_search(const std::vector<int>& data, int target) {
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i] == target) {
            return static_cast<long long>(i);
        }
    }
    return -1;
}

long long hash_lookup(const std::unordered_set<int>& index, int target) {
    return index.count(target) ? 0 : -1;
}

template <typename Fn>
long long measure(Fn fn) {
    auto start = Clock::now();
    fn();
    auto end = Clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    constexpr int n = 200000;
    std::vector<int> records(n);
    std::unordered_set<int> index;

    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(1, 1000000);

    for (int i = 0; i < n; ++i) {
        records[i] = dist(rng);
        index.insert(records[i]);
    }

    int target = records[n / 2];

    long long linear_us = measure([&] { linear_search(records, target); });
    long long hash_us = measure([&] { hash_lookup(index, target); });

    std::cout << "records=" << n << '\n';
    std::cout << "linear_search_us=" << linear_us << '\n';
    std::cout << "hash_lookup_us=" << hash_us << '\n';
    return 0;
}
