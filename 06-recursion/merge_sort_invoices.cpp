#include <iostream>
#include <vector>

void merge(std::vector<int>& data, size_t left, size_t mid, size_t right) {
    std::vector<int> buffer(right - left + 1);
    size_t i = left;
    size_t j = mid + 1;
    size_t k = 0;

    while (i <= mid && j <= right) {
        if (data[i] <= data[j]) {
            buffer[k++] = data[i++];
        } else {
            buffer[k++] = data[j++];
        }
    }
    while (i <= mid) {
        buffer[k++] = data[i++];
    }
    while (j <= right) {
        buffer[k++] = data[j++];
    }
    for (size_t index = 0; index < buffer.size(); ++index) {
        data[left + index] = buffer[index];
    }
}

void merge_sort(std::vector<int>& data, size_t left, size_t right) {
    if (left >= right) {
        return;
    }
    size_t mid = left + (right - left) / 2;
    merge_sort(data, left, mid);
    merge_sort(data, mid + 1, right);
    merge(data, left, mid, right);
}

int main() {
    std::vector<int> invoices = {42, 17, 88, 5, 31, 64};
    merge_sort(invoices, 0, invoices.size() - 1);

    for (int value : invoices) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    return 0;
}
