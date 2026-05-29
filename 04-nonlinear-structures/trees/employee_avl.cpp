#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

struct AvlNode {
    int id;
    std::string name;
    int height = 1;
    std::unique_ptr<AvlNode> left;
    std::unique_ptr<AvlNode> right;
};

int node_height(const AvlNode* node) {
    return node ? node->height : 0;
}

int balance_factor(const AvlNode* node) {
    return node_height(node->left.get()) - node_height(node->right.get());
}

void update_height(AvlNode* node) {
    node->height = 1 + std::max(node_height(node->left.get()), node_height(node->right.get()));
}

std::unique_ptr<AvlNode> rotate_right(std::unique_ptr<AvlNode> node) {
    std::unique_ptr<AvlNode> pivot = std::move(node->left);
    node->left = std::move(pivot->right);
    pivot->right = std::move(node);
    update_height(pivot->right.get());
    update_height(pivot.get());
    return pivot;
}

std::unique_ptr<AvlNode> rotate_left(std::unique_ptr<AvlNode> node) {
    std::unique_ptr<AvlNode> pivot = std::move(node->right);
    node->right = std::move(pivot->left);
    pivot->left = std::move(node);
    update_height(pivot->left.get());
    update_height(pivot.get());
    return pivot;
}

std::unique_ptr<AvlNode> rebalance(std::unique_ptr<AvlNode> node) {
    update_height(node.get());
    int balance = balance_factor(node.get());

    if (balance > 1) {
        if (balance_factor(node->left.get()) < 0) {
            node->left = rotate_left(std::move(node->left));
        }
        return rotate_right(std::move(node));
    }
    if (balance < -1) {
        if (balance_factor(node->right.get()) > 0) {
            node->right = rotate_right(std::move(node->right));
        }
        return rotate_left(std::move(node));
    }
    return node;
}

std::unique_ptr<AvlNode> insert_node(std::unique_ptr<AvlNode> node, int id, std::string name) {
    if (!node) {
        auto created = std::make_unique<AvlNode>();
        created->id = id;
        created->name = std::move(name);
        return created;
    }
    if (id < node->id) {
        node->left = insert_node(std::move(node->left), id, std::move(name));
    } else if (id > node->id) {
        node->right = insert_node(std::move(node->right), id, std::move(name));
    } else {
        node->name = std::move(name);
    }
    return rebalance(std::move(node));
}

const AvlNode* find_node(const AvlNode* node, int id) {
    while (node) {
        if (id == node->id) {
            return node;
        }
        node = id < node->id ? node->left.get() : node->right.get();
    }
    return nullptr;
}

void print_inorder(const AvlNode* node) {
    if (!node) {
        return;
    }
    print_inorder(node->left.get());
    std::cout << node->id << " " << node->name << '\n';
    print_inorder(node->right.get());
}

int main() {
    std::unique_ptr<AvlNode> root;
    root = insert_node(std::move(root), 30, "Ops");
    root = insert_node(std::move(root), 10, "Finance");
    root = insert_node(std::move(root), 20, "HR");
    root = insert_node(std::move(root), 40, "Engineering");
    root = insert_node(std::move(root), 50, "Support");

    print_inorder(root.get());

    if (const AvlNode* found = find_node(root.get(), 40)) {
        std::cout << "found " << found->name << '\n';
    }
    return 0;
}
