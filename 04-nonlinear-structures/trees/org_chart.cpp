#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct EmployeeNode {
    std::string name;
    std::vector<std::unique_ptr<EmployeeNode>> reports;
};

std::unique_ptr<EmployeeNode> make_employee(std::string name) {
    auto node = std::make_unique<EmployeeNode>();
    node->name = std::move(name);
    return node;
}

void print_org(const EmployeeNode& node, int depth = 0) {
    std::cout << std::string(depth * 2, ' ') << node.name << '\n';
    for (const auto& report : node.reports) {
        print_org(*report, depth + 1);
    }
}

int main() {
    auto ceo = make_employee("CEO");

    auto ops = make_employee("Ops Director");
    ops->reports.push_back(make_employee("Warehouse Lead"));
    ops->reports.push_back(make_employee("Support Lead"));

    auto eng = make_employee("Engineering Director");
    eng->reports.push_back(make_employee("Backend Lead"));
    eng->reports.push_back(make_employee("QA Lead"));

    ceo->reports.push_back(std::move(ops));
    ceo->reports.push_back(std::move(eng));

    print_org(*ceo);
    return 0;
}
