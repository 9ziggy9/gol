#ifndef RENDER_H_
#define RENDER_H_

void render_board(SDL_Renderer* renderer, board_t* board, 
                 int neighbors[COL_NUM][ROW_NUM]);

void render_running_state(SDL_Renderer *renderer, board_t *board);

void render_square(SDL_Renderer *renderer, int pos_x, int pos_y,
                  board_t* board);

void render_pause_state(SDL_Renderer *renderer, board_t *board);

void pause_square(SDL_Renderer *renderer, int pos_x, int pos_y,
                  board_t* board);

#endif // RENDER_H_
