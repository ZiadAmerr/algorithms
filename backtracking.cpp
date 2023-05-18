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
    int** solution() {
        return solution_;
    }
private:
    bool solve_knight_tour(const Position& pos, int move_number);
    void initialize_solution();
    int n_;
    Position start_pos_;
    int** solution_;
    const Position moves_[8] = {{2, 1},
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
    for (int i = 0; i < n_; i++) {
        for (int j = 0; j < n_; j++) {
            std::cout << " " << std::setw(2) << solution_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool KnightTour::solve_knight_tour(const Position& pos, int move_number) {
    if (move_number == n_ * n_) {
        // Check if the current position is one move away from the starting position
        for (int i = 0; i < 8; i++) {
            const int next_x = pos.x() + moves_[i].x();
            const int next_y = pos.y() + moves_[i].y();

            if (next_x == start_pos_.x() && next_y == start_pos_.y()) {
                solution_[next_x][next_y] = move_number;
                return true;
            }
        }
        return false;
    }

    for (int i = 0; i < 8; i++) {
        const int next_x = pos.x() + moves_[i].x();
        const int next_y = pos.y() + moves_[i].y();

        if (next_x >= 0 &&
            next_x < n_ &&
            next_y >= 0 &&
            next_y < n_ &&
            solution_[next_x][next_y] == -1)
        {
            solution_[next_x][next_y] = move_number;
            const Position next_pos(next_x, next_y);
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
    solution_ = new int*[n_];
    for (int i = 0; i < n_; i++) {
        solution_[i] = new int[n_];
        for (int j = 0; j < n_; j++) {
            solution_[i][j] = -1;
        }
    }
}

int main() {
    const int n = 6;
    const Position start_pos(0, 0);

    KnightTour tour(n, start_pos);
    tour.solve();
    tour.print_solution();

    return 0;
}
