#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <vector>

struct FamilyNode {
    std::string name;
    std::unique_ptr<FamilyNode> left;
    std::unique_ptr<FamilyNode> right;
};

void preorder(const FamilyNode* node, std::vector<std::string>& out) {
    if (!node) {
        return;
    }
    out.push_back(node->name);
    preorder(node->left.get(), out);
    preorder(node->right.get(), out);
}

void inorder(const FamilyNode* node, std::vector<std::string>& out) {
    if (!node) {
        return;
    }
    inorder(node->left.get(), out);
    out.push_back(node->name);
    inorder(node->right.get(), out);
}

void postorder(const FamilyNode* node, std::vector<std::string>& out) {
    if (!node) {
        return;
    }
    postorder(node->left.get(), out);
    postorder(node->right.get(), out);
    out.push_back(node->name);
}

void level_order(const FamilyNode* root, std::vector<std::string>& out) {
    if (!root) {
        return;
    }
    std::queue<const FamilyNode*> queue;
    queue.push(root);
    while (!queue.empty()) {
        const FamilyNode* node = queue.front();
        queue.pop();
        out.push_back(node->name);
        if (node->left) {
            queue.push(node->left.get());
        }
        if (node->right) {
            queue.push(node->right.get());
        }
    }
}

std::unique_ptr<FamilyNode> make_node(std::string name) {
    auto node = std::make_unique<FamilyNode>();
    node->name = std::move(name);
    return node;
}

void print_line(const std::string& label, const std::vector<std::string>& values) {
    std::cout << label << ':';
    for (const auto& value : values) {
        std::cout << ' ' << value;
    }
    std::cout << '\n';
}

int main() {
    auto root = make_node("Grandparent");
    root->left = make_node("Parent-A");
    root->right = make_node("Parent-B");
    root->left->left = make_node("Child-A1");
    root->left->right = make_node("Child-A2");
    root->right->left = make_node("Child-B1");

    std::vector<std::string> pre, in, post, level;
    preorder(root.get(), pre);
    inorder(root.get(), in);
    postorder(root.get(), post);
    level_order(root.get(), level);

    print_line("preorder", pre);
    print_line("inorder", in);
    print_line("postorder", post);
    print_line("level", level);
    return 0;
}
