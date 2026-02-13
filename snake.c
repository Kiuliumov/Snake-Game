#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"

void initGame(Snake *snake, Position *food, int *gameOver)
{
    snake->length = 3;
    snake->dir = RIGHT;

    for (int i = 0; i < snake->length; i++)
    {
        snake->body[i].x = WIDTH / 2 - i;
        snake->body[i].y = HEIGHT / 2;
    }

    srand(time(NULL));
    generateFood(food, snake);

    *gameOver = 0;
}

void drawGame(const Snake *snake, const Position *food)
{
    system("clear"); // Change to "cls" on Windows

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {

            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1)
            {
                printf("#");
            }
            else if (x == food->x && y == food->y)
            {
                printf("*");
            }
            else
            {
                int printed = 0;

                for (int i = 0; i < snake->length; i++)
                {
                    if (snake->body[i].x == x && snake->body[i].y == y)
                    {
                        if (i == 0)
                            printf("O");
                        else
                            printf("o");
                        printed = 1;
                        break;
                    }
                }

                if (!printed)
                    printf(" ");
            }
        }
        printf("\n");
    }
}

void updateGame(Snake *snake, Position *food, int *gameOver)
{

    for (int i = snake->length - 1; i > 0; i--)
    {
        snake->body[i] = snake->body[i - 1];
    }

    switch (snake->dir)
    {
    case UP:
        snake->body[0].y--;
        break;
    case DOWN:
        snake->body[0].y++;
        break;
    case LEFT:
        snake->body[0].x--;
        break;
    case RIGHT:
        snake->body[0].x++;
        break;
    }

    if (snake->body[0].x <= 0 || snake->body[0].x >= WIDTH - 1 ||
        snake->body[0].y <= 0 || snake->body[0].y >= HEIGHT - 1)
    {
        *gameOver = 1;
        return;
    }

    for (int i = 1; i < snake->length; i++)
    {
        if (snake->body[0].x == snake->body[i].x &&
            snake->body[0].y == snake->body[i].y)
        {
            *gameOver = 1;
            return;
        }
    }

    if (snake->body[0].x == food->x &&
        snake->body[0].y == food->y)
    {

        if (snake->length < MAX_SNAKE_LENGTH)
            snake->length++;

        generateFood(food, snake);
    }
}

void changeDirection(Snake *snake, Direction newDir)
{
    if ((snake->dir == UP && newDir == DOWN) ||
        (snake->dir == DOWN && newDir == UP) ||
        (snake->dir == LEFT && newDir == RIGHT) ||
        (snake->dir == RIGHT && newDir == LEFT))
    {
        return;
    }

    snake->dir = newDir;
}

void generateFood(Position *food, const Snake *snake)
{
    int valid = 0;

    while (!valid)
    {
        food->x = rand() % (WIDTH - 2) + 1;
        food->y = rand() % (HEIGHT - 2) + 1;

        valid = 1;
        for (int i = 0; i < snake->length; i++)
        {
            if (snake->body[i].x == food->x &&
                snake->body[i].y == food->y)
            {
                valid = 0;
                break;
            }
        }
    }
}