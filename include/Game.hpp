#pragma once

#include <vector>
#include <deque>
#include "Snake.hpp"

class Game
{
public:
    static constexpr int CELL_SIZE = 100;
    static constexpr int CELL_COUNT_X = 10;
    static constexpr int CELL_COUNT_Y = 9;

    static constexpr Color DARK_GRAY = {50, 50, 50, 255};
    static constexpr Color LIGHT_GRAY = {70, 70, 70, 255};

    static constexpr float MOVE_TIME_DURATION_SECONDS = 0.2f;
    
    static constexpr int MAX_INPUT_NUMBER_BUFFER = 2;

    Game();

    void runGame();
    
private:
    void update();
    void draw() const;

    [[nodiscard]] bool setFruit();
    void resetGame();
    void drawSnake() const;
    void drawFruit() const;
    void getSnakeDirectionFromInput();
    void getEmptyCells();
    [[nodiscard]] bool eatFruit();

    static void drawCell(int pos_x, int pos_y, Color col);
    static void drawBackground();
    
    Vector2 fruit_pos_ = {0, 0};
    Snake snake_;
    float timer_ = MOVE_TIME_DURATION_SECONDS;
    std::deque<Vector2> input_queue_;
    std::vector<Vector2> empty_cells_;
};
