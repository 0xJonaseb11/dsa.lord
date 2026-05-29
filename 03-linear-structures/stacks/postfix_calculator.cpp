#include <cctype>
#include <iostream>
#include <stack>
#include <string>

int apply(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

int evaluate_postfix(const std::string& expression) {
    std::stack<int> values;
    for (char ch : expression) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            values.push(ch - '0');
            continue;
        }
        int b = values.top(); values.pop();
        int a = values.top(); values.pop();
        values.push(apply(a, b, ch));
    }
    return values.top();
}

int main() {
    std::cout << evaluate_postfix("23*5+") << '\n';
    return 0;
}
