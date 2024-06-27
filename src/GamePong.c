#include "GamePong.h"

int main() {
  int score1 = 0, score2 = 0;  // cчет игры
  int ball_x = WIDTH_FIELD / 2;
  int ball_y = HEIGHT_FIELD / 2;
  int rocket1 = HEIGHT_FIELD / 2;
  int rocket2 = HEIGHT_FIELD / 2;
  int ball_dir_y = START_BALL_DIR_Y;
  int ball_dir_x = START_BALL_DIR_X;
  // основной боевой цикл до победного счета
  while (!is_end(score1, score2)) {
    show_field(rocket1, rocket2, ball_x, ball_y, score1, score2);
    rocket1 = new_rocket_location(rocket1, 1);
    show_field(rocket1, rocket2, ball_x, ball_y, score1, score2);
    rocket2 = new_rocket_location(rocket2, 2);
    // проверка сменится ли направление по горизонтали
    if (is_new_ball_dir_x(ball_y, ball_x + ball_dir_x, rocket1, rocket2))
      ball_dir_x *= -1;
    // cчитаем новое положение по горизонтали
    ball_x += ball_dir_x;
    // проверка сменится ли направление по вертикали
    if (is_new_ball_dir_y(ball_dir_y, ball_y)) ball_dir_y *= -1;
    // cчитаем новое положение по горизонтали
    ball_y += ball_dir_y;
    // если гол, то добавляем очко, возвращаем мяч в центр и на след. итерацию
    if (ball_x == 1) {
      score2 += 1;
      ball_x = WIDTH_FIELD / 2;
    } else if (ball_x == WIDTH_FIELD + 1) {
      score1 += 1;
      ball_x = WIDTH_FIELD / 2;
    }
    show_field(rocket1, rocket2, ball_x, ball_y, score1, score2);
  }

  while (getchar() != 'q');

  return 0;
}

void show_field(int y1Rocket, int y2Rocket, int xBall, int yBall, int score1,
                int score2) {
  // отрисовка поля
  for (int y = 0; y < HEIGHT_FIELD; y++) {  // проход по каждой строчке
    for (int x = 0; x < WIDTH_FIELD; x++) {  // проход по каждому столбцу
      if (x == xBall && y == yBall)  // сначала проверим не мяч ли здесь
        printf("o");
      else if (y == 0 || y == HEIGHT_FIELD - 1)  // проверим не забор ли здесь
        printf("#");
      // проверим не ракетка ли здесь должна быть
      else if ((x == 0 && (y1Rocket - y == 1 || y1Rocket - y == -1 ||
                           y1Rocket - y == 0)) ||
               (x == WIDTH_FIELD - 1 &&
                (y2Rocket - y == 1 || y2Rocket - y == -1 || y2Rocket - y == 0)))
        printf("|");
      else  // во всех иных случаях пустота - пробел
        printf(" ");
    }
    printf("\n");  // перенос на новую строку
  }
  // отрисовка счёта
  for (int x = 0; x < WIDTH_FIELD; x++) {  // пройдемся по столбцам строки счета
    // если на 25% от ширины поля - печаем очки левого
    if (x == WIDTH_FIELD / 4) printf("%d", score1);
    // если на 75% от ширины поля - печаем очки правого
    else if (x == WIDTH_FIELD * 3 / 4)
      printf("%d", score2);
    // во всех иных случаях пустота - пробел
    else
      printf(" ");
  }
  printf("\n");
}

int is_end(int s1, int s2) {
  int res = 0;
  if (s1 == MAX_SCORE) {
    printf("Left player wins the game!\nCongratulation!");
    res = 1;
  } else if (s2 == MAX_SCORE) {
    printf("Right player wins the game!\nCongratulation!");
    res = 1;
  }

  return res;
}

int new_rocket_location(int rocket_y, int rocket_id) {
  if (rocket_id ==
      1)  // в зависимости от id разные приглашения для ввода печатаем
    printf("Left player's turn:");
  else
    printf("Right player's turn:");
  // цикл посимвольного потока ввода бесконечен, до первого пробела или \n
  while (1) {
    char c = getchar();
    if (c == ' ' || c == '\n') {  // общие символы управления для выхода
      // fflush(stdin);
      break;
    } else {
      if (rocket_id == 1) {  // кнопки управления левого игрока
        if (c == 'a')
          rocket_y -= 1;
        else if (c == 'z')
          rocket_y += 1;
      } else {  // кнопки управления правого игрока
        if (c == 'k')
          rocket_y -= 1;
        else if (c == 'm')
          rocket_y += 1;
      }
    }
  }
  // проверка если ракетка вылезла за пределы поля - вернуть крайнее возможное
  if (rocket_y < 2)
    rocket_y = 2;
  else if (rocket_y > HEIGHT_FIELD - 3)
    rocket_y = HEIGHT_FIELD - 3;
  printf("\n");
  return rocket_y;
}

int is_new_ball_dir_y(int ball_dir_y, int ball_y) {
  int res;
  if (ball_y + ball_dir_y == 0)  // если следующее положение 0, то разворот
    res = 1;
  // если следующее положение на нижней стенке, то разворот
  else if (ball_y + ball_dir_y == HEIGHT_FIELD - 1)
    res = 1;
  else
    res = 0;  // иначе не меняется
  return res;
}

int is_new_ball_dir_x(int ball_y, int ball_x, int rocket1, int rocket2) {
  // сложное условие, поэтому опишу подробнее, в случае если мяч пересечется с
  // позицией рокетки, то направление сменилось. Поэтому проверим залетает ли в
  // зону или за зону ракетки мяч и отличается ли центр ракетки по оси y от
  // координаты y мяча на 1 единицу или 0. Да-отскок.
  int res = 0;
  if ((ball_x >= WIDTH_FIELD - 1 &&
       (rocket2 - ball_y == 1 || rocket2 - ball_y == 0 ||
        rocket2 - ball_y == -1)) ||
      (ball_x <= 1 && (rocket1 - ball_y == 1 || rocket1 - ball_y == 0 ||
                       rocket1 - ball_y == -1)))
    res = 1;
  return res;
}