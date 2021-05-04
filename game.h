#ifndef GAME_H_
#define GAME_H_

#define COL_NUM 300 // size of game universe, only windowed is shown.
#define ROW_NUM 300
#define ALIVE 1
#define DEAD 0

#define RUNNING_STATE 0
#define PAUSE_STATE 1

typedef struct {
  int cell_state[COL_NUM][ROW_NUM];
  int game_state;
  int CELL_WIDTH;
  int CELL_HEIGHT;
} board_t;

#endif // GAME_H_
