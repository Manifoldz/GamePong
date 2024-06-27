#ifndef GAME_PONG_H
#define GAME_PONG_H

#include <stdio.h>

#define WIDTH_FIELD 80
#define HEIGHT_FIELD 25

// начальное верт. напр. движения мяча 1-вниз, -1-вверх
#define START_BALL_DIR_Y 1
// начальное гориз. напр. движения мяча 1-вправо, -1-влево
#define START_BALL_DIR_X 1

// счет, до которого играем
#define MAX_SCORE 3

// отрисовка
void show_field(int y1Rocket, int y2Rocket, int xBall, int yBall, int score1,
                int score2);

// проверяет закончена ли игра, если да, то принтует кто победил и возращает 1
int is_end(int s1, int s2);

// возвращает новое положение ракетки
int new_rocket_location(int rocket_y, int rocket_id);

// возвращает результат проверки отскочил ли мяч по вертикали
int is_new_ball_dir_y(int ball_dir_y, int ball_y);

// возвращает результат проверки отскочил ли мяч по горизонтали
int is_new_ball_dir_x(int ball_y, int ball_x, int rocket1, int rocket2);

#endif