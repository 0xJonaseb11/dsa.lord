#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, int> word_frequency(const std::string& text) {
    std::unordered_map<std::string, int> counts;
    std::istringstream stream(text);
    std::string word;

    while (stream >> word) {
        while (!word.empty() && !std::isalpha(static_cast<unsigned char>(word.back()))) {
            word.pop_back();
        }
        if (!word.empty()) {
            ++counts[word];
        }
    }
    return counts;
}

int main() {
    std::string article =
        "Delivery delays affect customer trust. "
        "Reliable delivery improves customer trust.";

    for (const auto& [word, count] : word_frequency(article)) {
        std::cout << word << " " << count << '\n';
    }
    return 0;
}
