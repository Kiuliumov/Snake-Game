#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "snake.h"

int kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int main()
{
    Snake snake;
    Position food;
    int gameOver;

    initGame(&snake, &food, &gameOver);

    while (!gameOver)
    {

        if (kbhit())
        {
            char ch = getchar();

            if (ch == 'w')
                changeDirection(&snake, UP);
            if (ch == 's')
                changeDirection(&snake, DOWN);
            if (ch == 'a')
                changeDirection(&snake, LEFT);
            if (ch == 'd')
                changeDirection(&snake, RIGHT);
        }

        updateGame(&snake, &food, &gameOver);
        drawGame(&snake, &food);

        usleep(100000);
    }

    printf("Game Over!\n");
    return 0;
}