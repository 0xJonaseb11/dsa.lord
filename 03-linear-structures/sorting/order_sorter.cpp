#include <iostream>
#include <string>
#include <vector>

struct Order {
    std::string id;
    double total;
};

void bubble_sort(std::vector<Order>& orders) {
    for (size_t i = 0; i + 1 < orders.size(); ++i) {
        for (size_t j = 0; j + 1 < orders.size() - i; ++j) {
            if (orders[j].total > orders[j + 1].total) {
                std::swap(orders[j], orders[j + 1]);
            }
        }
    }
}

void selection_sort(std::vector<Order>& orders) {
    for (size_t i = 0; i < orders.size(); ++i) {
        size_t min_index = i;
        for (size_t j = i + 1; j < orders.size(); ++j) {
            if (orders[j].total < orders[min_index].total) {
                min_index = j;
            }
        }
        if (min_index != i) {
            std::swap(orders[i], orders[min_index]);
        }
    }
}

void insertion_sort(std::vector<Order>& orders) {
    for (size_t i = 1; i < orders.size(); ++i) {
        Order key = orders[i];
        size_t j = i;
        while (j > 0 && orders[j - 1].total > key.total) {
            orders[j] = orders[j - 1];
            --j;
        }
        orders[j] = key;
    }
}

void merge(std::vector<Order>& orders, size_t left, size_t mid, size_t right) {
    std::vector<Order> buffer(orders.begin() + left, orders.begin() + right + 1);
    size_t i = 0;
    size_t j = mid - left + 1;
    size_t k = left;

    while (i < mid - left + 1 && j < buffer.size()) {
        if (buffer[i].total <= buffer[j].total) {
            orders[k++] = buffer[i++];
        } else {
            orders[k++] = buffer[j++];
        }
    }
    while (i < mid - left + 1) {
        orders[k++] = buffer[i++];
    }
    while (j < buffer.size()) {
        orders[k++] = buffer[j++];
    }
}

void merge_sort(std::vector<Order>& orders, size_t left, size_t right) {
    if (left >= right) {
        return;
    }
    size_t mid = left + (right - left) / 2;
    merge_sort(orders, left, mid);
    merge_sort(orders, mid + 1, right);
    merge(orders, left, mid, right);
}

size_t partition(std::vector<Order>& orders, size_t low, size_t high) {
    double pivot = orders[high].total;
    size_t i = low;
    for (size_t j = low; j < high; ++j) {
        if (orders[j].total <= pivot) {
            std::swap(orders[i++], orders[j]);
        }
    }
    std::swap(orders[i], orders[high]);
    return i;
}

void quick_sort(std::vector<Order>& orders, size_t low, size_t high) {
    if (low >= high) {
        return;
    }
    size_t pivot = partition(orders, low, high);
    if (pivot > 0) {
        quick_sort(orders, low, pivot - 1);
    }
    quick_sort(orders, pivot + 1, high);
}

void heapify(std::vector<Order>& orders, size_t size, size_t root) {
    size_t largest = root;
    size_t left = root * 2 + 1;
    size_t right = root * 2 + 2;

    if (left < size && orders[left].total > orders[largest].total) {
        largest = left;
    }
    if (right < size && orders[right].total > orders[largest].total) {
        largest = right;
    }
    if (largest != root) {
        std::swap(orders[root], orders[largest]);
        heapify(orders, size, largest);
    }
}

void heap_sort(std::vector<Order>& orders) {
    for (int i = static_cast<int>(orders.size() / 2) - 1; i >= 0; --i) {
        heapify(orders, orders.size(), static_cast<size_t>(i));
    }
    for (size_t i = orders.size(); i > 1; --i) {
        std::swap(orders[0], orders[i - 1]);
        heapify(orders, i - 1, 0);
    }
}

void print_orders(const std::vector<Order>& orders) {
    for (const auto& order : orders) {
        std::cout << order.id << " " << order.total << '\n';
    }
}

int main() {
    std::vector<Order> sample = {
        {"ORD-104", 120.5},
        {"ORD-101", 45.0},
        {"ORD-103", 88.25},
        {"ORD-102", 210.0},
    };

    auto bubble = sample;
    bubble_sort(bubble);
    print_orders(bubble);

    auto selection = sample;
    selection_sort(selection);
    print_orders(selection);

    auto insertion = sample;
    insertion_sort(insertion);
    print_orders(insertion);

    auto merged = sample;
    merge_sort(merged, 0, merged.size() - 1);
    print_orders(merged);

    auto quick = sample;
    quick_sort(quick, 0, quick.size() - 1);
    print_orders(quick);

    auto heap = sample;
    heap_sort(heap);
    print_orders(heap);
    return 0;
}
