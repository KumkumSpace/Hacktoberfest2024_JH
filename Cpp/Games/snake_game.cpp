#include <iostream>
#include <conio.h> // For _kbhit() and _getch()
#include <cstdlib>
#include <ctime>
#include <vector>
#include <windows.h> // For Sleep()

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;
char board[HEIGHT][WIDTH];
int snakeLength;
int snakeX, snakeY;
vector<pair<int, int>> snake; // Snake body coordinates
int foodX, foodY;
bool gameOver;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    snakeX = WIDTH / 2;
    snakeY = HEIGHT / 2;
    snakeLength = 1;
    snake.push_back(make_pair(snakeX, snakeY));

    // Place food
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
}

void Draw() {
    system("cls"); // Clear the console

    for (int i = 0; i < WIDTH + 2; ++i) cout << "#";
    cout << endl;

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (j == 0) cout << "#"; // Left border
            if (i == snakeY && j == snakeX) cout << "O"; // Snake head
            else if (i == foodY && j == foodX) cout << "F"; // Food
            else {
                bool isBodyPart = false;
                for (int k = 1; k < snakeLength; ++k) {
                    if (snake[k].first == j && snake[k].second == i) {
                        cout << "o"; // Snake body
                        isBodyPart = true;
                        break;
                    }
                }
                if (!isBodyPart) cout << " ";
            }
            if (j == WIDTH - 1) cout << "#"; // Right border
        }
        cout << endl;
    }

    for (int i = 0; i < WIDTH + 2; ++i) cout << "#";
    cout << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'x': gameOver = true; break; // Exit
        }
    }
}

void Logic() {
    // Save the previous head position
    int prevX = snakeX;
    int prevY = snakeY;
    int prev2X, prev2Y;

    // Update the head position
    switch (dir) {
        case LEFT: snakeX--; break;
        case RIGHT: snakeX++; break;
        case UP: snakeY--; break;
        case DOWN: snakeY++; break;
    }

    // Check for wall collision
    if (snakeX >= WIDTH) snakeX = 0; else if (snakeX < 0) snakeX = WIDTH - 1;
    if (snakeY >= HEIGHT) snakeY = 0; else if (snakeY < 0) snakeY = HEIGHT - 1;

    // Check for self collision
    for (int i = 1; i < snakeLength; ++i) {
        if (snake[i].first == snakeX && snake[i].second == snakeY) {
            gameOver = true;
        }
    }

    // Check if snake eats food
    if (snakeX == foodX && snakeY == foodY) {
        snakeLength++;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
    }

    // Move the body
    for (int i = 0; i < snakeLength; ++i) {
        if (i == 0) {
            snake[i] = make_pair(snakeX, snakeY); // Update head position
        } else {
            prev2X = snake[i].first;
            prev2Y = snake[i].second;
            snake[i] = make_pair(prevX, prevY); // Move body to previous position
            prevX = prev2X;
            prevY = prev2Y;
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // Control the speed
    }
    cout << "Game Over!" << endl;
    return 0;
}
    
