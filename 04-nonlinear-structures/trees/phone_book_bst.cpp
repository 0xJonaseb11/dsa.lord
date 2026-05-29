#include <iostream>
#include <memory>
#include <optional>
#include <string>

struct ContactNode {
    std::string name;
    std::string phone;
    std::unique_ptr<ContactNode> left;
    std::unique_ptr<ContactNode> right;
};

class PhoneBook {
public:
    void insert(std::string name, std::string phone) {
        root_ = insert_node(std::move(root_), std::move(name), std::move(phone));
    }

    std::optional<std::string> find(const std::string& name) const {
        const ContactNode* node = root_.get();
        while (node) {
            if (name == node->name) {
                return node->phone;
            }
            node = name < node->name ? node->left.get() : node->right.get();
        }
        return std::nullopt;
    }

    void print_inorder() const {
        walk(root_.get());
        std::cout << '\n';
    }

private:
    std::unique_ptr<ContactNode> root_;

    std::unique_ptr<ContactNode> insert_node(
        std::unique_ptr<ContactNode> node, std::string name, std::string phone) {
        if (!node) {
            auto created = std::make_unique<ContactNode>();
            created->name = std::move(name);
            created->phone = std::move(phone);
            return created;
        }
        if (name < node->name) {
            node->left = insert_node(std::move(node->left), std::move(name), std::move(phone));
        } else if (name > node->name) {
            node->right = insert_node(std::move(node->right), std::move(name), std::move(phone));
        } else {
            node->phone = std::move(phone);
        }
        return node;
    }

    void walk(const ContactNode* node) const {
        if (!node) {
            return;
        }
        walk(node->left.get());
        std::cout << node->name << " " << node->phone << '\n';
        walk(node->right.get());
    }
};

int main() {
    PhoneBook book;
    book.insert("Alice", "+250700001");
    book.insert("Brian", "+250700002");
    book.insert("Claire", "+250700003");

    book.print_inorder();

    if (auto phone = book.find("Brian")) {
        std::cout << "Brian " << *phone << '\n';
    }
    return 0;
}
