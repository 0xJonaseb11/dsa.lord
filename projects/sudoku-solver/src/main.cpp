#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using Grid = std::vector<std::vector<int>>;

Grid read_puzzle(const std::string& path) {
    std::ifstream input(path);
    Grid grid(9, std::vector<int>(9, 0));
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            input >> grid[row][col];
        }
    }
    return grid;
}

bool is_valid(const Grid& grid, int row, int col, int value) {
    for (int i = 0; i < 9; ++i) {
        if (grid[row][i] == value || grid[i][col] == value) {
            return false;
        }
    }
    int box_row = (row / 3) * 3;
    int box_col = (col / 3) * 3;
    for (int r = box_row; r < box_row + 3; ++r) {
        for (int c = box_col; c < box_col + 3; ++c) {
            if (grid[r][c] == value) {
                return false;
            }
        }
    }
    return true;
}

bool find_empty(const Grid& grid, int& row, int& col) {
    for (int r = 0; r < 9; ++r) {
        for (int c = 0; c < 9; ++c) {
            if (grid[r][c] == 0) {
                row = r;
                col = c;
                return true;
            }
        }
    }
    return false;
}

bool solve(Grid& grid) {
    int row = 0;
    int col = 0;
    if (!find_empty(grid, row, col)) {
        return true;
    }
    for (int value = 1; value <= 9; ++value) {
        if (!is_valid(grid, row, col, value)) {
            continue;
        }
        grid[row][col] = value;
        if (solve(grid)) {
            return true;
        }
        grid[row][col] = 0;
    }
    return false;
}

void print_grid(const Grid& grid) {
    for (const auto& row : grid) {
        for (size_t col = 0; col < row.size(); ++col) {
            std::cout << row[col];
            if (col + 1 < row.size()) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
}

int main(int argc, char* argv[]) {
    Grid puzzle = (argc > 1) ? read_puzzle(argv[1]) : Grid{
        {{5, 3, 0, 0, 7, 0, 0, 0, 0}},
        {{6, 0, 0, 1, 9, 5, 0, 0, 0}},
        {{0, 9, 8, 0, 0, 0, 0, 6, 0}},
        {{8, 0, 0, 0, 6, 0, 0, 0, 3}},
        {{4, 0, 0, 8, 0, 3, 0, 0, 1}},
        {{7, 0, 0, 0, 2, 0, 0, 0, 6}},
        {{0, 6, 0, 0, 0, 0, 2, 8, 0}},
        {{0, 0, 0, 4, 1, 9, 0, 0, 5}},
        {{0, 0, 0, 0, 8, 0, 0, 7, 9}},
    };

    if (!solve(puzzle)) {
        std::cout << "unsolvable\n";
        return 1;
    }

    print_grid(puzzle);
    return 0;
}
