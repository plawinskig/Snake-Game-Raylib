#include "Game.hpp"

void Game::runGame()
{
    InitWindow(CELL_SIZE * CELL_COUNT_X, CELL_SIZE * CELL_COUNT_Y, "Game of snake");
    SetTargetFPS(60);

    resetGame();

    while (!WindowShouldClose()) 
    {
        update();
        draw();
    }

    CloseWindow();
}

void Game::update()
{
    getSnakeDirectionFromInput();
    timer_ -= GetFrameTime();

    if (timer_ <= 0)
    {
        timer_ += MOVE_TIME_DURATION_SECONDS;
        
        Vector2 move_dir = snake_.getDirection();
        if (!input_queue_.empty())
        {
            move_dir = input_queue_.front();
            input_queue_.pop_front();
        }
        
        snake_.move(move_dir);

        snake_.wrap(CELL_COUNT_X, CELL_COUNT_Y);
    
        eatFruit();

        if(snake_.isColliding())
        {
            WaitTime(1);
            resetGame();
        }
    }
}

void Game::draw() const
{
    BeginDrawing();

    ClearBackground(DARK_GRAY);

    drawBackground();
    
    drawSnake();

    drawFruit();

    EndDrawing();
}

bool Game::setFruit()
{
    std::vector<Vector2> empty_cells = getEmptyCells();

    if (empty_cells.empty())
    {
        return false;
    }

    int idx = GetRandomValue(0, empty_cells.size() - 1);
    fruit_pos_ = empty_cells[idx];

    return true;
}

void Game::resetGame()
{
    snake_.reset();
    input_queue_.clear();
    setFruit();
    timer_ = MOVE_TIME_DURATION_SECONDS;
}

void Game::drawCell(int pos_x, int pos_y, Color col)
{
    DrawRectangle(pos_x * CELL_SIZE, pos_y * CELL_SIZE, CELL_SIZE, CELL_SIZE, col);
}

void Game::drawBackground()
{
    for (int i = 0; i < CELL_COUNT_X; ++i)
    {
        for (int j = 0; j < CELL_COUNT_Y; ++j)
        {
            if ((i + j) % 2 == 1)
            {
                drawCell(i, j, LIGHT_GRAY);
            }
        }
    }
}

void Game::drawSnake() const
{
    drawCell(snake_.getHeadPos().x, snake_.getHeadPos().y, DARKGREEN);

    for (size_t i = 1; i < snake_.getSize(); ++i)
    {
        drawCell(snake_[i].x, snake_[i].y, GREEN);
    }
}

void Game::drawFruit() const
{
    drawCell(fruit_pos_.x, fruit_pos_.y, RED);
}

void Game::getSnakeDirectionFromInput()
{
    Vector2 new_dir = {0, 0};

    if (IsKeyPressed(KEY_W)) { new_dir = {0, -1}; }
    else if (IsKeyPressed(KEY_S)) { new_dir = {0, 1}; }
    else if (IsKeyPressed(KEY_A)) { new_dir = {-1, 0}; }
    else if (IsKeyPressed(KEY_D)) { new_dir = {1, 0}; }

    if ((new_dir.x != 0 || new_dir.y != 0) && input_queue_.size() < MAX_INPUT_NUMBER_BUFFER)
    {
        input_queue_.push_back(new_dir);
    }
}

std::vector<Vector2> Game::getEmptyCells() const
{
    std::vector<Vector2> empty_cells;
    empty_cells.reserve(CELL_COUNT_X * CELL_COUNT_Y);

    for (int i = 0; i < CELL_COUNT_X; ++i)
    {
        for (int j = 0; j < CELL_COUNT_Y; ++j)
        {
            Vector2 vec = {static_cast<float>(i), static_cast<float>(j)};

            if (!snake_.occupies(vec))
            {
                empty_cells.push_back(vec);
            }
        }
    }

    return empty_cells;
}

void Game::eatFruit()
{
    if (snake_.getHeadPos().x == fruit_pos_.x &&
        snake_.getHeadPos().y == fruit_pos_.y)
    {
        snake_.extendBody();
        
        if (!setFruit()) 
        {
            WaitTime(1);
            resetGame();
        }
    }
}
