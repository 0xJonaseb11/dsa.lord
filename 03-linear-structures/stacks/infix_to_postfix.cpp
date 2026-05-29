#include <cctype>
#include <iostream>
#include <stack>
#include <string>

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

std::string infix_to_postfix(const std::string& expression) {
    std::stack<char> operators;
    std::string output;

    for (char ch : expression) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            output.push_back(ch);
            continue;
        }
        if (ch == '(') {
            operators.push(ch);
            continue;
        }
        if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                output.push_back(operators.top());
                operators.pop();
            }
            if (!operators.empty()) {
                operators.pop();
            }
            continue;
        }
        while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
            output.push_back(operators.top());
            operators.pop();
        }
        operators.push(ch);
    }

    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }
    return output;
}

int main() {
    std::cout << infix_to_postfix("(3+5)*2") << '\n';
    std::cout << infix_to_postfix("3+5*2") << '\n';
    return 0;
}
