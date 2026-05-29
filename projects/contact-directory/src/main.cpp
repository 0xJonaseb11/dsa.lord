#include <iostream>
#include <memory>
#include <optional>
#include <string>

struct StaffNode {
    std::string id;
    std::string extension;
    std::unique_ptr<StaffNode> left;
    std::unique_ptr<StaffNode> right;
};

class ContactDirectory {
public:
    void add(std::string id, std::string extension) {
        root_ = insert(std::move(root_), std::move(id), std::move(extension));
    }

    void remove(const std::string& id) {
        root_ = erase(std::move(root_), id);
    }

    std::optional<std::string> lookup(const std::string& id) const {
        const StaffNode* node = root_.get();
        while (node) {
            if (id == node->id) {
                return node->extension;
            }
            node = id < node->id ? node->left.get() : node->right.get();
        }
        return std::nullopt;
    }

    void print_sorted() const {
        walk(root_.get());
        std::cout << '\n';
    }

private:
    std::unique_ptr<StaffNode> root_;

    std::unique_ptr<StaffNode> insert(
        std::unique_ptr<StaffNode> node, std::string id, std::string extension) {
        if (!node) {
            auto created = std::make_unique<StaffNode>();
            created->id = std::move(id);
            created->extension = std::move(extension);
            return created;
        }
        if (id < node->id) {
            node->left = insert(std::move(node->left), std::move(id), std::move(extension));
        } else if (id > node->id) {
            node->right = insert(std::move(node->right), std::move(id), std::move(extension));
        } else {
            node->extension = std::move(extension);
        }
        return node;
    }

    std::unique_ptr<StaffNode> erase(std::unique_ptr<StaffNode> node, const std::string& id) {
        if (!node) {
            return node;
        }
        if (id < node->id) {
            node->left = erase(std::move(node->left), id);
            return node;
        }
        if (id > node->id) {
            node->right = erase(std::move(node->right), id);
            return node;
        }
        if (!node->left) {
            return std::move(node->right);
        }
        if (!node->right) {
            return std::move(node->left);
        }

        StaffNode* successor = node->right.get();
        while (successor->left) {
            successor = successor->left.get();
        }
        node->id = successor->id;
        node->extension = successor->extension;
        node->right = erase(std::move(node->right), successor->id);
        return node;
    }

    void walk(const StaffNode* node) const {
        if (!node) {
            return;
        }
        walk(node->left.get());
        std::cout << node->id << " ext " << node->extension << '\n';
        walk(node->right.get());
    }
};

int main() {
    ContactDirectory directory;
    directory.add("E102", "2201");
    directory.add("E087", "2188");
    directory.add("E145", "2240");
    directory.add("E120", "2215");

    directory.remove("E087");
    directory.print_sorted();

    if (auto ext = directory.lookup("E145")) {
        std::cout << "E145 -> " << *ext << '\n';
    }
    return 0;
}
