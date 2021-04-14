#include <stdio.h>
#include "./game.h"
#include "./logic.h"

void click_on_cell(board_t* board, int row, int column)
{
  if (board->game_state == PAUSE_STATE) {
    if (board->cell_state[column][row] == DEAD) {
      board->cell_state[column][row] = ALIVE;
      printf("Cell (%d,%d) set to ALIVE.\n", column, row);
    }
    else if (board->cell_state[column][row] == ALIVE) {
      board->cell_state[column][row] = DEAD;
      printf("Cell (%d,%d) set to DEAD.\n", column, row);
    }
  }
  else if (board->game_state == RUNNING_STATE)
    printf("Game is running, hit space to pause and edit.\n");
}

void count_neighbors(board_t* board, int neighbors[COL_NUM][ROW_NUM])
{
  for (int i = 0; i < COL_NUM; i++) {
    for (int j = 0; j < ROW_NUM; j++) {
      neighbors[i][j] = DEAD;
    }
  }

  for (int i = 1; i < (COL_NUM - 1); i++) {
    for (int j = 1; j < (ROW_NUM - 1); j++) {
      if (board->cell_state[i-1][j-1] == ALIVE) {
        neighbors[i][j]++;
      }
      if (board->cell_state[i][j-1] == ALIVE) {
        neighbors[i][j]++;
      }
      if (board->cell_state[i+1][j-1] == ALIVE) {
        neighbors[i][j]++;
      }
      if (board->cell_state[i-1][j] == ALIVE) {
        neighbors[i][j]++;
      }
      if (board->cell_state[i+1][j] == ALIVE) {
        neighbors[i][j]++;
      }
      if (board->cell_state[i-1][j+1] == ALIVE) {
        neighbors[i][j]++;
      }
      if (board->cell_state[i][j+1] == ALIVE) {
        neighbors[i][j]++;
      }
      if (board->cell_state[i+1][j+1] == ALIVE) {
        neighbors[i][j]++;
      }
    }
  }
}

void evolve(board_t* board, const int neighbors[COL_NUM][ROW_NUM])
{
  for (int i = 0; i < COL_NUM; i++) {
    for (int j = 0; j < ROW_NUM; j++) {
      // underopulation case
      if (neighbors[i][j] < 2)
        board->cell_state[i][j] = DEAD;
      // birth case
      else if (neighbors[i][j] == 3)
        board->cell_state[i][j] = ALIVE;
      // overpopulation case
      else if (neighbors[i][j] > 3)
        board->cell_state[i][j] = DEAD;
      // survival case is implicit, as only cells with 2 or 3 neighbors will
      // survive.
    }
  }
}
