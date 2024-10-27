#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int GRID_SIZE = 10;
const int NUM_MINES = 10;

class Minesweeper {
private:
    vector<vector<int>> grid;
    vector<vector<bool>> revealed;
    vector<vector<bool>> flagged;
    bool gameOver;

public:
    Minesweeper() {
        grid.resize(GRID_SIZE, vector<int>(GRID_SIZE, 0));
        revealed.resize(GRID_SIZE, vector<bool>(GRID_SIZE, false));
        flagged.resize(GRID_SIZE, vector<bool>(GRID_SIZE, false));
        gameOver = false;
        srand(static_cast<unsigned int>(time(0)));
        placeMines();
        calculateNumbers();
    }

    void placeMines() {
        for (int i = 0; i < NUM_MINES; ) {
            int x = rand() % GRID_SIZE;
            int y = rand() % GRID_SIZE;
            if (grid[x][y] == -1) continue; // Already a mine
            grid[x][y] = -1; // Place a mine
            i++;
        }
    }

    void calculateNumbers() {
        for (int x = 0; x < GRID_SIZE; ++x) {
            for (int y = 0; y < GRID_SIZE; ++y) {
                if (grid[x][y] == -1) continue;
                int count = 0;
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        if (dx == 0 && dy == 0) continue;
                        int nx = x + dx, ny = y + dy;
                        if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE && grid[nx][ny] == -1) {
                            count++;
                        }
                    }
                }
                grid[x][y] = count;
            }
        }
    }

    void displayGrid() {
        cout << "Current Board:\n";
        for (int x = 0; x < GRID_SIZE; ++x) {
            for (int y = 0; y < GRID_SIZE; ++y) {
                if (revealed[x][y]) {
                    if (grid[x][y] == -1) cout << "* ";
                    else cout << grid[x][y] << " ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }

    void uncover(int x, int y) {
        if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE || revealed[x][y]) return;
        
        revealed[x][y] = true;
        
        if (grid[x][y] == -1) {
            gameOver = true;
            cout << "Game Over! You hit a mine.\n";
            return;
        }
        
        // Uncover adjacent cells if the cell is 0
        if (grid[x][y] == 0) {
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) continue;
                    uncover(x + dx, y + dy);
                }
            }
        }
    }

    void play() {
        while (!gameOver) {
            displayGrid();
            cout << "Enter your move (row and column): ";
            int x, y;
            cin >> x >> y;

            if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE) {
                cout << "Invalid move! Try again.\n";
                continue;
            }
            uncover(x, y);
        }
        displayGrid();
    }
};

int main() {
    Minesweeper game;
    game.play();
    return 0;
}
