#pragma once

#include <vector>
#include "Snake.hpp"

class Game
{
public:
    Game() 
        : fruit_pos_({0, 0}), 
        snake_new_direction_({1, 0}), 
        snake_(Snake()), 
        timer_(MOVE_TIME_DURATION_SECONDS) 
    {
    }

    static constexpr int CELL_SIZE = 100;
    static constexpr int CELL_COUNT_X = 10;
    static constexpr int CELL_COUNT_Y = 9;

    static constexpr Color DARK_GRAY = {50, 50, 50, 255};
    static constexpr Color LIGHT_GRAY = {70, 70, 70, 255};

    static constexpr float MOVE_TIME_DURATION_SECONDS = 0.2f;

    void runGame();
    
private:
    void update();
    void draw() const;

    void setFruit();
    void resetGame();
    void drawSnake() const;
    void drawFruit() const;
    void getSnakeDirectionFromInput();
    std::vector<Vector2> getEmptyCells() const;
    void eatFruit();

    static void drawCell(int pos_x, int pos_y, Color col);
    static void drawBackground();
    
    Vector2 fruit_pos_;
    Vector2 snake_new_direction_;
    Snake snake_;

    float timer_;
};
