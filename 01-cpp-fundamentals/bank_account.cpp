#include <iostream>
#include <stdexcept>
#include <string>

class BankAccount {
public:
    BankAccount(std::string owner, double opening_balance)
        : owner_(std::move(owner)), balance_(opening_balance) {
        if (balance_ < 0) {
            throw std::invalid_argument("opening balance cannot be negative");
        }
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("deposit must be positive");
        }
        balance_ += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("withdrawal must be positive");
        }
        if (amount > balance_) {
            throw std::runtime_error("insufficient funds");
        }
        balance_ -= amount;
    }

    double balance() const { return balance_; }
    const std::string& owner() const { return owner_; }

private:
    std::string owner_;
    double balance_;
};

int main() {
    BankAccount account("Amina K.", 1500.0);
    account.deposit(250.0);
    account.withdraw(400.0);

    std::cout << account.owner() << " balance: " << account.balance() << '\n';
    return 0;
}
