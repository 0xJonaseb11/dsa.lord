#include <iostream>
#include <unordered_map>
#include <vector>

int coin_change_ways(int amount, const std::vector<int>& coins, std::unordered_map<int, int>& memo) {
    if (amount == 0) {
        return 1;
    }
    if (amount < 0) {
        return 0;
    }
    if (memo.count(amount)) {
        return memo[amount];
    }

    int ways = 0;
    for (int coin : coins) {
        ways += coin_change_ways(amount - coin, coins, memo);
    }
    memo[amount] = ways;
    return ways;
}

int main() {
    std::vector<int> denominations = {1, 5, 10, 25};
    std::unordered_map<int, int> memo;
    std::cout << coin_change_ways(30, denominations, memo) << '\n';
    return 0;
}
