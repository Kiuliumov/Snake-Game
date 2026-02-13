#ifndef SNAKE_H
#define SNAKE_H

#define WIDTH 40
#define HEIGHT 20
#define MAX_SNAKE_LENGTH 100

typedef struct
{
    int x;
    int y;
} Position;

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct
{
    Position body[MAX_SNAKE_LENGTH];
    int length;
    Direction dir;
} Snake;

void initGame(Snake *snake, Position *food, int *gameOver);
void drawGame(const Snake *snake, const Position *food);
void updateGame(Snake *snake, Position *food, int *gameOver);
void changeDirection(Snake *snake, Direction newDir);
void generateFood(Position *food, const Snake *snake);

#endif