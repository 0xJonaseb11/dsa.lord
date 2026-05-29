#include <iostream>
#include <memory>
#include <string>

struct FileNode {
    std::string path;
    int size_kb;
    std::unique_ptr<FileNode> left;
    std::unique_ptr<FileNode> right;
};

class FileIndex {
public:
    void add(std::string path, int size_kb) {
        root_ = insert(std::move(root_), std::move(path), size_kb);
    }

    void print_largest_first() const {
        reverse_walk(root_.get());
        std::cout << '\n';
    }

    int total_size() const { return sum(root_.get()); }

private:
    std::unique_ptr<FileNode> root_;

    std::unique_ptr<FileNode> insert(std::unique_ptr<FileNode> node, std::string path, int size_kb) {
        if (!node) {
            auto created = std::make_unique<FileNode>();
            created->path = std::move(path);
            created->size_kb = size_kb;
            return created;
        }
        if (size_kb < node->size_kb) {
            node->left = insert(std::move(node->left), std::move(path), size_kb);
        } else {
            node->right = insert(std::move(node->right), std::move(path), size_kb);
        }
        return node;
    }

    void reverse_walk(const FileNode* node) const {
        if (!node) {
            return;
        }
        reverse_walk(node->right.get());
        std::cout << node->path << " " << node->size_kb << " KB\n";
        reverse_walk(node->left.get());
    }

    int sum(const FileNode* node) const {
        if (!node) {
            return 0;
        }
        return node->size_kb + sum(node->left.get()) + sum(node->right.get());
    }
};

int main() {
    FileIndex index;
    index.add("/var/log/system.log", 920);
    index.add("/home/docs/report.pdf", 240);
    index.add("/home/photos/trip.jpg", 1800);
    index.add("/tmp/cache.bin", 64);

    index.print_largest_first();
    std::cout << "total " << index.total_size() << " KB\n";
    return 0;
}
