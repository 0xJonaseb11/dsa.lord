#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

namespace logs {

int count_level(const std::string& text, const std::string& level) {
    std::istringstream stream(text);
    std::string line;
    int count = 0;

    while (std::getline(stream, line)) {
        if (line.find(level) != std::string::npos) {
            ++count;
        }
    }
    return count;
}

}  // namespace logs

int main() {
    std::string sample =
        "2026-05-01 ERROR payment gateway timeout\n"
        "2026-05-01 INFO user login success\n"
        "2026-05-01 ERROR database retry failed\n"
        "2026-05-01 WARN cache near capacity\n";

    std::cout << "errors: " << logs::count_level(sample, "ERROR") << '\n';
    std::cout << "warnings: " << logs::count_level(sample, "WARN") << '\n';
    return 0;
}
