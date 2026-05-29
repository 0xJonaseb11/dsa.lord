#include <functional>
#include <iostream>
#include <list>
#include <optional>
#include <string>
#include <vector>

struct User {
    std::string email;
    std::string role;
};

class UserDirectory {
public:
    explicit UserDirectory(size_t bucket_count = 8) : buckets_(bucket_count) {}

    void insert(User user) {
        size_t index = hash(user.email);
        for (auto& [email, record] : buckets_[index]) {
            if (email == user.email) {
                record = std::move(user);
                return;
            }
        }
        buckets_[index].emplace_back(user.email, std::move(user));
    }

    std::optional<User> find(const std::string& email) const {
        size_t index = hash(email);
        for (const auto& [key, record] : buckets_[index]) {
            if (key == email) {
                return record;
            }
        }
        return std::nullopt;
    }

private:
    size_t hash(const std::string& key) const {
        return std::hash<std::string>{}(key) % buckets_.size();
    }

    std::vector<std::list<std::pair<std::string, User>>> buckets_;
};

int main() {
    UserDirectory directory;
    directory.insert({"dev@acme.io", "engineer"});
    directory.insert({"ops@acme.io", "operator"});

    if (auto user = directory.find("dev@acme.io")) {
        std::cout << user->email << " " << user->role << '\n';
    }
    return 0;
}
