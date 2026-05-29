#include <iostream>

namespace units {

template <typename T>
T celsius_to_fahrenheit(T celsius) {
    return (celsius * 9 / 5) + 32;
}

template <typename T>
T fahrenheit_to_celsius(T fahrenheit) {
    return (fahrenheit - 32) * 5 / 9;
}

}  // namespace units

int main() {
    std::cout << units::celsius_to_fahrenheit(20.0) << '\n';
    std::cout << units::fahrenheit_to_celsius(68.0) << '\n';
    return 0;
}
