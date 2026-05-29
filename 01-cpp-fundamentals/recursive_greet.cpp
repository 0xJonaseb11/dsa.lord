#include <iostream>
#include <string>

void greet(const std::string& name, int times) {
    if (times == 0) {
        return;
    }
    std::cout << "hello " << name << '\n';
    greet(name, times - 1);
}

int main() {
    greet("team", 3);
    return 0;
}
