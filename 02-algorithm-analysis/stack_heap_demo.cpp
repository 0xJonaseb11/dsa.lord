#include <iostream>
#include <vector>

void stack_buffer_demo() {
    int ids[4] = {101, 102, 103, 104};
    std::cout << "stack sample=" << ids[0] << '\n';
}

void heap_buffer_demo() {
    int* ids = new int[4]{201, 202, 203, 204};
    std::cout << "heap sample=" << ids[0] << '\n';
    delete[] ids;
}

int main() {
    stack_buffer_demo();
    heap_buffer_demo();

    std::vector<int> dynamic = {301, 302, 303};
    std::cout << "vector size=" << dynamic.size() << '\n';
    return 0;
}
