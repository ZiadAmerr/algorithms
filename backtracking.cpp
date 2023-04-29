#include <iostream>
#include <iomanip>

class Position {
public:
    Position(int x, int y): x_{x}, y_{y} {}
    int x() const {
        return x_;
    }
    int y() const {
        return y_;
    }
private:
    int x_;
    int y_;
};

class KnightTour {
public:
    KnightTour(int n, const Position& start_pos);
    void solve();
    void print_solution() const;
private:
    bool solve_knight_tour(const Position& pos, int move_number);
    void initialize_solution();
    int n_;
    Position start_pos_;
    std::vector<std::vector<int>> solution_;
    const std::vector<Position> moves_ = {{2, 1},
                                          {1, 2},
                                          {-1, 2},
                                          {-2, 1},
                                          {1, -2},
                                          {2, -1},
                                          {-2, -1},
                                          {-1, -2}};
};

KnightTour::KnightTour(int n, const Position& start_pos): n_{n}, start_pos_{start_pos} {
    initialize_solution();
    solution_[start_pos_.x()][start_pos_.y()] = 0;
}

void KnightTour::solve() {
    solve_knight_tour(start_pos_, 1);
}

void KnightTour::print_solution() const {
    for (const auto& row : solution_) {
        for (const auto& value : row) {
            std::cout << " " << std::setw(2) << value << " ";
        }
        std::cout << std::endl;
    }
}

bool KnightTour::solve_knight_tour(const Position& pos, int move_number) {
    if (move_number == n_ * n_) {
        return true;
    }

    for (const auto& move : moves_) {
        const int next_x = pos.x() + move.x();
        const int next_y = pos.y() + move.y();
        const Position next_pos(next_x, next_y);

        if (next_x >= 0 &&
            next_x < n_ &&
            next_y >= 0 &&
            next_y < n_ &&
            solution_[next_x][next_y] == -1)
        {
            solution_[next_x][next_y] = move_number;
            if (solve_knight_tour(next_pos, move_number + 1)) {
                return true;
            } else {
                solution_[next_x][next_y] = -1;
            }
        }
    }
    return false;
}

void KnightTour::initialize_solution() {
    solution_.resize(n_, std::vector<int>(n_, -1));
}

int main() {
    const int n = 5;
    const Position start_pos(0, 0);

    KnightTour tour(n, start_pos);
    tour.solve();
    tour.print_solution();

    return 0;
}
