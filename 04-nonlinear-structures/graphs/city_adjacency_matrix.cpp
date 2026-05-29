#include <iostream>
#include <string>
#include <vector>

class CityMatrix {
public:
    CityMatrix(const std::vector<std::string>& cities) : cities_(cities) {
        size_t n = cities.size();
        matrix_.assign(n, std::vector<int>(n, 0));
    }

    void connect(const std::string& from, const std::string& to, int minutes) {
        matrix_[index_of(from)][index_of(to)] = minutes;
        matrix_[index_of(to)][index_of(from)] = minutes;
    }

    int travel_time(const std::string& from, const std::string& to) const {
        return matrix_[index_of(from)][index_of(to)];
    }

    void print() const {
        std::cout << "    ";
        for (const auto& city : cities_) {
            std::cout << city << ' ';
        }
        std::cout << '\n';
        for (size_t i = 0; i < cities_.size(); ++i) {
            std::cout << cities_[i] << ' ';
            for (size_t j = 0; j < cities_.size(); ++j) {
                std::cout << matrix_[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

private:
    std::vector<std::string> cities_;
    std::vector<std::vector<int>> matrix_;

    size_t index_of(const std::string& city) const {
        for (size_t i = 0; i < cities_.size(); ++i) {
            if (cities_[i] == city) {
                return i;
            }
        }
        return 0;
    }
};

int main() {
    CityMatrix city({"Hub", "Remera", "Airport"});
    city.connect("Hub", "Remera", 12);
    city.connect("Remera", "Airport", 18);
    city.connect("Hub", "Airport", 35);

    city.print();
    std::cout << "Hub->Airport " << city.travel_time("Hub", "Airport") << " min\n";
    return 0;
}
