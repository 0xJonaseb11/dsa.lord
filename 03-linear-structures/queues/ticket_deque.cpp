#include <deque>
#include <iostream>
#include <string>

int main() {
    std::deque<std::string> ticket_line;
    ticket_line.push_back("ticket-101");
    ticket_line.push_back("ticket-102");
    ticket_line.push_front("priority-099");
    ticket_line.push_back("ticket-103");

    while (!ticket_line.empty()) {
        std::cout << ticket_line.front() << '\n';
        ticket_line.pop_front();
    }
    return 0;
}
