#include <iostream>
#include <queue>
#include <string>

struct PrintJob {
    std::string document;
    int pages;
};

int main() {
    std::queue<PrintJob> jobs;
    jobs.push({"Quarterly Report", 18});
    jobs.push({"Invoice Batch", 6});
    jobs.push({"Visitor Badges", 2});

    while (!jobs.empty()) {
        PrintJob job = jobs.front();
        jobs.pop();
        std::cout << job.document << " pages=" << job.pages << '\n';
    }
    return 0;
}
