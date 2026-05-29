#include <iostream>
#include <list>
#include <string>

class RecentFiles {
public:
    void open(const std::string& path) {
        for (auto it = order_.begin(); it != order_.end(); ++it) {
            if (*it == path) {
                order_.erase(it);
                break;
            }
        }
        order_.push_front(path);
        if (order_.size() > limit_) {
            order_.pop_back();
        }
    }

    void print() const {
        for (const auto& path : order_) {
            std::cout << path << '\n';
        }
    }

private:
    std::list<std::string> order_;
    size_t limit_ = 5;
};

int main() {
    RecentFiles files;
    files.open("/docs/report.q1");
    files.open("/src/main.cpp");
    files.open("/docs/report.q1");
    files.open("/assets/logo.svg");
    files.print();
    return 0;
}
