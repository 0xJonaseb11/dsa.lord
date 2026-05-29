#include <iostream>
#include <memory>
#include <string>

struct SongNode {
    std::string title;
    std::unique_ptr<SongNode> next;
};

class Playlist {
public:
    void add_front(std::string title) {
        auto node = std::make_unique<SongNode>();
        node->title = std::move(title);
        node->next = std::move(head_);
        head_ = std::move(node);
    }

    void print() const {
        for (const SongNode* node = head_.get(); node; node = node->next.get()) {
            std::cout << node->title << '\n';
        }
    }

private:
    std::unique_ptr<SongNode> head_;
};

int main() {
    Playlist playlist;
    playlist.add_front("Midnight Transit");
    playlist.add_front("City Lights");
    playlist.add_front("Open Road");
    playlist.print();
    return 0;
}
