#include <iostream>
#include <vector>

void move_disks(int count, int source, int target, int spare, std::vector<std::string>& plan) {
    if (count == 0) {
        return;
    }
    move_disks(count - 1, source, spare, target, plan);
    plan.push_back("move disk " + std::to_string(count) + " from bay " + std::to_string(source) +
                   " to bay " + std::to_string(target));
    move_disks(count - 1, spare, target, source, plan);
}

int main() {
    std::vector<std::string> migration_plan;
    move_disks(4, 1, 3, 2, migration_plan);

    for (const auto& step : migration_plan) {
        std::cout << step << '\n';
    }
    return 0;
}
