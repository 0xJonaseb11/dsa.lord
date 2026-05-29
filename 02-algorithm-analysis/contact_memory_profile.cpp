#include <iostream>
#include <string>
#include <vector>

struct Contact {
    std::string name;
    std::string phone;
};

size_t stack_footprint_bytes(const std::vector<Contact>& contacts) {
    size_t bytes = sizeof(contacts);
    bytes += contacts.capacity() * sizeof(Contact);
    for (const auto& contact : contacts) {
        bytes += contact.name.capacity();
        bytes += contact.phone.capacity();
    }
    return bytes;
}

int main() {
    std::vector<Contact> directory = {
        {"Aline U.", "+250788000001"},
        {"Brian N.", "+250788000002"},
        {"Chloe T.", "+250788000003"},
    };

    std::cout << "contacts=" << directory.size() << '\n';
    std::cout << "approx_bytes=" << stack_footprint_bytes(directory) << '\n';
    return 0;
}
