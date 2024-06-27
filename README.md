## Game Pong

A turn-based terminal game for two players similar to the game "Pong".
Developed in a structured programming style in pure C language.

![Screenshot_of_Game](images/Screenshot_of_Game.png)

### Start the Game

* To start the game - use `make build` and after `make start`.

### Game controls
  
* A/Z to move the left player's racket.
* K/M to move the right player's racket.
* Space Bar to skip action.
* "q" to exit game after end!

### It is possible to customize the size of the playing field

* WIDTH_FIELD - field width
* HEIGHT_FIELD - field height
* START_BALL_DIR_Y - initial vert. eg ball movement 1-down, -1-up
* START_BALL_DIR_X - initial horizon. eg ball movement 1-right, -1-left
* MAX_SCORE - the maximum score up to which we play, after which the winner will be announced and the game will end

### Info

* [Coverage analyzed during game test](tests/index.html)