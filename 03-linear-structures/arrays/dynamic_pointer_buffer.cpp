#include <iostream>

int main() {
    int size = 5;
    int* buffer = new int[size]{10, 20, 30, 40, 50};

    buffer[2] = 35;
    int total = 0;
    for (int i = 0; i < size; ++i) {
        total += buffer[i];
    }

    std::cout << "total=" << total << '\n';
    delete[] buffer;
    return 0;
}
