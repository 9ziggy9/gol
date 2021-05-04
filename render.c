#include <SDL2/SDL.h>

#include "./game.h"
#include "./render.h"
#include "./logic.h"

void render_board(SDL_Renderer* renderer, board_t* board,
                  int neighbors[COL_NUM][ROW_NUM])
{
  switch(board->game_state) {
    case RUNNING_STATE:
      render_running_state(renderer, board);
      count_neighbors(board, neighbors);
      evolve(board, neighbors);
      break;
    case PAUSE_STATE:
      render_pause_state(renderer, board);
      break;
    default: {}
  }
}

void render_running_state(SDL_Renderer *renderer, board_t *board)
{
  int pos_x = 0;
  int pos_y = 0;

  for (int i = 0; i < COL_NUM; i++) {
    for (int j = 0; j < ROW_NUM; j++) {
      pos_x = i * board->CELL_WIDTH;
      pos_y = j * board->CELL_HEIGHT;
      if (board->cell_state[i][j] == ALIVE)
        render_square(renderer, pos_x, pos_y, board);
    }
  }
}

void render_pause_state(SDL_Renderer *renderer, board_t *board)
{
  int pos_x = 0;
  int pos_y = 0;

  for (int i = 0; i < COL_NUM; i++) {
    for (int j = 0; j < ROW_NUM; j++) {
      pos_x = i * board->CELL_WIDTH;
      pos_y = j * board->CELL_HEIGHT;
      if (board->cell_state[i][j] == ALIVE)
        pause_square(renderer, pos_x, pos_y, board);
    }
  }
}

void render_square(SDL_Renderer *renderer, int pos_x, int pos_y, board_t* board)
{
  SDL_Rect cell;
  cell.x = pos_x;
  cell.y = pos_y;
  cell.w = board->CELL_WIDTH - 1;
  cell.h = board->CELL_HEIGHT - 1;
  SDL_SetRenderDrawColor(renderer, 142, 192, 124, 1);
  SDL_RenderFillRect(renderer, &cell);
}

void pause_square(SDL_Renderer *renderer, int pos_x, int pos_y, board_t* board)
{
  SDL_Rect cell;
  cell.x = pos_x;
  cell.y = pos_y;
  cell.w = board->CELL_WIDTH - 1;
  cell.h = board->CELL_HEIGHT - 1;
  SDL_SetRenderDrawColor(renderer, 146, 131, 116, 1);
  SDL_RenderFillRect(renderer, &cell);
}
