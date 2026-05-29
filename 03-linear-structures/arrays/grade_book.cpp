#include <iostream>
#include <numeric>
#include <vector>

double class_average(const std::vector<double>& scores) {
    if (scores.empty()) {
        return 0;
    }
    return std::accumulate(scores.begin(), scores.end(), 0.0) / scores.size();
}

int main() {
    std::vector<std::vector<double>> classes = {
        {78, 82, 91, 88},
        {64, 70, 73, 69},
        {95, 89, 92, 97},
    };

    for (size_t i = 0; i < classes.size(); ++i) {
        std::cout << "class " << (i + 1) << " avg=" << class_average(classes[i]) << '\n';
    }
    return 0;
}
