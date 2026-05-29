#include <iostream>
#include <memory>
#include <optional>
#include <string>

struct TrackNode {
    std::string title;
    std::unique_ptr<TrackNode> next;
    TrackNode* prev = nullptr;
};

class Playlist {
public:
    void add_back(std::string title) {
        auto node = std::make_unique<TrackNode>();
        node->title = std::move(title);

        if (!head_) {
            head_ = std::move(node);
            tail_ = head_.get();
            current_ = tail_;
            return;
        }

        node->prev = tail_;
        tail_->next = std::move(node);
        tail_ = tail_->next.get();
    }

    bool remove_current() {
        if (!current_) {
            return false;
        }

        TrackNode* doomed = current_;
        TrackNode* next = doomed->next.get();
        TrackNode* prev = doomed->prev;

        if (prev) {
            prev->next = std::move(doomed->next);
        } else {
            head_ = std::move(doomed->next);
        }

        if (next) {
            next->prev = prev;
            current_ = next;
        } else {
            tail_ = prev;
            current_ = prev;
        }

        return true;
    }

    std::optional<std::string> next_track() {
        if (!current_ || !current_->next) {
            return std::nullopt;
        }
        current_ = current_->next.get();
        return current_->title;
    }

    std::optional<std::string> previous_track() {
        if (!current_ || !current_->prev) {
            return std::nullopt;
        }
        current_ = current_->prev;
        return current_->title;
    }

    void print() const {
        for (TrackNode* node = head_.get(); node; node = node->next.get()) {
            if (node == current_) {
                std::cout << "> ";
            } else {
                std::cout << "  ";
            }
            std::cout << node->title << '\n';
        }
    }

private:
    std::unique_ptr<TrackNode> head_;
    TrackNode* tail_ = nullptr;
    TrackNode* current_ = nullptr;
};

int main() {
    Playlist queue;
    queue.add_back("Intro");
    queue.add_back("Midnight Run");
    queue.add_back("Closing Theme");

    queue.next_track();
    queue.remove_current();
    queue.previous_track();
    queue.print();
    return 0;
}
