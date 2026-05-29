#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct Patient {
    std::string name;
    int severity;
};

struct CompareSeverity {
    bool operator()(const Patient& a, const Patient& b) const {
        return a.severity < b.severity;
    }
};

int main() {
    std::priority_queue<Patient, std::vector<Patient>, CompareSeverity> triage;
    triage.push({"Alice", 2});
    triage.push({"Brian", 5});
    triage.push({"Claire", 3});
    triage.push({"David", 5});

    while (!triage.empty()) {
        Patient next = triage.top();
        triage.pop();
        std::cout << next.name << " severity=" << next.severity << '\n';
    }
    return 0;
}
