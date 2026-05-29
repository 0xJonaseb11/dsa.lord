#include <iostream>
#include <optional>
#include <queue>
#include <string>

struct Ticket {
    int id;
    std::string issue;
};

class ServiceDesk {
public:
    void enqueue(Ticket ticket) { queue_.push(std::move(ticket)); }

    std::optional<Ticket> serve_next() {
        if (queue_.empty()) {
            return std::nullopt;
        }
        Ticket next = queue_.front();
        queue_.pop();
        return next;
    }

    size_t waiting() const { return queue_.size(); }

private:
    std::queue<Ticket> queue_;
};

int main() {
    ServiceDesk desk;
    desk.enqueue({101, "password reset"});
    desk.enqueue({102, "billing dispute"});
    desk.enqueue({103, "device setup"});

    while (desk.waiting() > 0) {
        Ticket ticket = desk.serve_next().value();
        std::cout << ticket.id << " " << ticket.issue << '\n';
    }
    return 0;
}
