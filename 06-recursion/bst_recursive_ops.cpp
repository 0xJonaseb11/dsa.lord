#include <iostream>
#include <memory>
#include <optional>
#include <string>

struct Node {
    std::string key;
    std::string value;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};

std::unique_ptr<Node> insert_recursive(std::unique_ptr<Node> node, std::string key, std::string value) {
    if (!node) {
        auto created = std::make_unique<Node>();
        created->key = std::move(key);
        created->value = std::move(value);
        return created;
    }
    if (key < node->key) {
        node->left = insert_recursive(std::move(node->left), std::move(key), std::move(value));
    } else if (key > node->key) {
        node->right = insert_recursive(std::move(node->right), std::move(key), std::move(value));
    } else {
        node->value = std::move(value);
    }
    return node;
}

std::optional<std::string> search_recursive(const Node* node, const std::string& key) {
    if (!node) {
        return std::nullopt;
    }
    if (key == node->key) {
        return node->value;
    }
    if (key < node->key) {
        return search_recursive(node->left.get(), key);
    }
    return search_recursive(node->right.get(), key);
}

void inorder_recursive(const Node* node) {
    if (!node) {
        return;
    }
    inorder_recursive(node->left.get());
    std::cout << node->key << " " << node->value << '\n';
    inorder_recursive(node->right.get());
}

int main() {
    std::unique_ptr<Node> root;
    root = insert_recursive(std::move(root), "ops", "Operations");
    root = insert_recursive(std::move(root), "eng", "Engineering");
    root = insert_recursive(std::move(root), "fin", "Finance");

    inorder_recursive(root.get());

    if (auto dept = search_recursive(root.get(), "eng")) {
        std::cout << *dept << '\n';
    }
    return 0;
}
