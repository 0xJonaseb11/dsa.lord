#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using Clock = std::chrono::steady_clock;

void bubble_sort(std::vector<int>& data) {
    for (size_t i = 0; i + 1 < data.size(); ++i) {
        for (size_t j = 0; j + 1 < data.size() - i; ++j) {
            if (data[j] > data[j + 1]) {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}

void insertion_sort(std::vector<int>& data) {
    for (size_t i = 1; i < data.size(); ++i) {
        int key = data[i];
        size_t j = i;
        while (j > 0 && data[j - 1] > key) {
            data[j] = data[j - 1];
            --j;
        }
        data[j] = key;
    }
}

size_t partition(std::vector<int>& data, size_t low, size_t high) {
    int pivot = data[high];
    size_t i = low;
    for (size_t j = low; j < high; ++j) {
        if (data[j] <= pivot) {
            std::swap(data[i++], data[j]);
        }
    }
    std::swap(data[i], data[high]);
    return i;
}

void quick_sort(std::vector<int>& data, size_t low, size_t high) {
    if (low >= high) {
        return;
    }
    size_t pivot = partition(data, low, high);
    if (pivot > 0) {
        quick_sort(data, low, pivot - 1);
    }
    quick_sort(data, pivot + 1, high);
}

template <typename Fn>
long long time_sort(Fn fn) {
    auto start = Clock::now();
    fn();
    auto end = Clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main() {
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(1, 1000000);

    std::vector<int> base(3000);
    for (int& value : base) {
        value = dist(rng);
    }

    auto bubble = base;
    long long bubble_ms = time_sort([&] { bubble_sort(bubble); });

    auto insertion = base;
    long long insertion_ms = time_sort([&] { insertion_sort(insertion); });

    auto quick = base;
    long long quick_ms = time_sort([&] { quick_sort(quick, 0, quick.size() - 1); });

    auto stl = base;
    long long stl_ms = time_sort([&] { std::sort(stl.begin(), stl.end()); });

    std::cout << "n=" << base.size() << '\n';
    std::cout << "bubble_ms=" << bubble_ms << '\n';
    std::cout << "insertion_ms=" << insertion_ms << '\n';
    std::cout << "quick_ms=" << quick_ms << '\n';
    std::cout << "stl_ms=" << stl_ms << '\n';
    return 0;
}
