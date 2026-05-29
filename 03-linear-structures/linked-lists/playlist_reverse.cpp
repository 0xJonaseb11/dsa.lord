#include <iostream>
#include <memory>
#include <string>

struct SongNode {
    std::string title;
    std::unique_ptr<SongNode> next;
};

std::unique_ptr<SongNode> reverse_list(std::unique_ptr<SongNode> head) {
    std::unique_ptr<SongNode> prev;
    while (head) {
        std::unique_ptr<SongNode> next = std::move(head->next);
        head->next = std::move(prev);
        prev = std::move(head);
        head = std::move(next);
    }
    return prev;
}

void print_list(const SongNode* head) {
    for (const SongNode* node = head; node; node = node->next.get()) {
        std::cout << node->title << '\n';
    }
}

int main() {
    std::unique_ptr<SongNode> head = std::make_unique<SongNode>();
    head->title = "Track C";
    head->next = std::make_unique<SongNode>();
    head->next->title = "Track B";
    head->next->next = std::make_unique<SongNode>();
    head->next->next->title = "Track A";

    head = reverse_list(std::move(head));
    print_list(head.get());
    return 0;
}
