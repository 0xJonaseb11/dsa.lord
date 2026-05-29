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

    void remove(const std::string& name) {
        root_ = delete_node(std::move(root_), name);
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

    std::unique_ptr<ContactNode> delete_node(std::unique_ptr<ContactNode> node, const std::string& name) {
        if (!node) {
            return node;
        }
        if (name < node->name) {
            node->left = delete_node(std::move(node->left), name);
            return node;
        }
        if (name > node->name) {
            node->right = delete_node(std::move(node->right), name);
            return node;
        }
        if (!node->left) {
            return std::move(node->right);
        }
        if (!node->right) {
            return std::move(node->left);
        }

        ContactNode* successor = node->right.get();
        while (successor->left) {
            successor = successor->left.get();
        }
        node->name = successor->name;
        node->phone = successor->phone;
        node->right = delete_node(std::move(node->right), successor->name);
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
    book.insert("David", "+250700004");

    book.remove("Brian");
    book.print_inorder();
    return 0;
}
