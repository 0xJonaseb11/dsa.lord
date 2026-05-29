#include <iostream>

struct Vec2 {
    double x;
    double y;
};

Vec2 operator+(const Vec2& a, const Vec2& b) {
    return {a.x + b.x, a.y + b.y};
}

Vec2 operator*(const Vec2& v, double scalar) {
    return {v.x * scalar, v.y * scalar};
}

std::ostream& operator<<(std::ostream& out, const Vec2& v) {
    out << '(' << v.x << ", " << v.y << ')';
    return out;
}

int main() {
    Vec2 origin{0, 0};
    Vec2 step{3, 4};
    Vec2 target = origin + step * 2.5;

    std::cout << target << '\n';
    return 0;
}
