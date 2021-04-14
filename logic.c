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
  // Clear neighbors
  for (int i = 0; i < COL_NUM; i++) {
    for (int j = 0; j < ROW_NUM; j++) {
      neighbors[i][j] = DEAD;
    }
  }

  // Inner cells
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

  // Top cells
  for (int i = 1; i < (COL_NUM - 1); i++) {
    if (board->cell_state[i-1][0] == ALIVE) {
      neighbors[i][0]++;
    }
    if (board->cell_state[i-1][1] == ALIVE) {
      neighbors[i][0]++;
    }
    if (board->cell_state[i][1] == ALIVE) {
      neighbors[i][0]++;
    }
    if (board->cell_state[i+1][1] == ALIVE) {
      neighbors[i][0]++;
    }
    if (board->cell_state[i+1][0] == ALIVE) {
      neighbors[i][0]++;
    }
  }
  
  // Left cells
  for (int j = 1; j < (ROW_NUM - 1); j++) {
    if (board->cell_state[0][j-1] == ALIVE) {
      neighbors[0][j]++;
    }
    if (board->cell_state[1][j-1] == ALIVE) {
      neighbors[0][j]++;
    }
    if (board->cell_state[1][j] == ALIVE) {
      neighbors[0][j]++;
    }
    if (board->cell_state[1][j+1] == ALIVE) {
      neighbors[0][j]++;
    }
    if (board->cell_state[0][j+1] == ALIVE) {
      neighbors[0][j]++;
    }
  }

  // Bottom cells
  for (int i = 1; i < (COL_NUM - 1); i++) {
    if (board->cell_state[i-1][ROW_NUM - 1] == ALIVE) {
      neighbors[i][ROW_NUM - 1]++;
    }
    if (board->cell_state[i-1][ROW_NUM - 2] == ALIVE) {
      neighbors[i][ROW_NUM - 1]++;
    }
    if (board->cell_state[i][ROW_NUM - 2] == ALIVE) {
      neighbors[i][ROW_NUM - 1]++;
    }
    if (board->cell_state[i+1][ROW_NUM - 2] == ALIVE) {
      neighbors[i][ROW_NUM - 1]++;
    }
    if (board->cell_state[i+1][ROW_NUM - 1] == ALIVE) {
      neighbors[i][ROW_NUM - 1]++;
    }
  
  }
  // Right cells
  for (int j = 1; j < (ROW_NUM - 1); j++) {
    if (board->cell_state[COL_NUM - 1][j-1] == ALIVE) {
      neighbors[COL_NUM - 1][j]++;
    }
    if (board->cell_state[COL_NUM - 2][j-1] == ALIVE) {
      neighbors[COL_NUM - 1][j]++;
    }
    if (board->cell_state[COL_NUM - 2][j] == ALIVE) {
      neighbors[COL_NUM - 1][j]++;
    }
    if (board->cell_state[COL_NUM - 2][j+1] == ALIVE) {
      neighbors[COL_NUM - 1][j]++;
    }
    if (board->cell_state[COL_NUM - 1][j+1] == ALIVE) {
      neighbors[COL_NUM - 1][j]++;
    }
  }

  // Top left corner
  if (board->cell_state[1][0] == ALIVE)
    neighbors[0][0]++;
  if (board->cell_state[1][1] == ALIVE)
    neighbors[0][0]++;
  if (board->cell_state[0][1] == ALIVE)
    neighbors[0][0]++;

  // Bottom left corner
  if (board->cell_state[1][ROW_NUM - 1] == ALIVE)
    neighbors[0][ROW_NUM - 1]++;
  if (board->cell_state[1][ROW_NUM - 2] == ALIVE)
    neighbors[0][ROW_NUM - 1]++;
  if (board->cell_state[0][ROW_NUM - 2] == ALIVE)
    neighbors[0][ROW_NUM - 1]++;

  // Bottom right corner
  if (board->cell_state[COL_NUM - 2][ROW_NUM - 1] == ALIVE)
    neighbors[COL_NUM - 1][ROW_NUM - 1]++;
  if (board->cell_state[COL_NUM - 1][ROW_NUM - 2] == ALIVE)
    neighbors[COL_NUM - 1][ROW_NUM - 1]++;
  if (board->cell_state[COL_NUM - 2][ROW_NUM - 2] == ALIVE)
    neighbors[COL_NUM - 1][ROW_NUM - 1]++;

  // Top left corner
  if (board->cell_state[COL_NUM - 1][1] == ALIVE)
    neighbors[COL_NUM - 1][0]++;
  if (board->cell_state[COL_NUM - 2][1] == ALIVE)
    neighbors[COL_NUM - 1][0]++;
  if (board->cell_state[COL_NUM - 2][0] == ALIVE)
    neighbors[COL_NUM - 1][0]++;
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
