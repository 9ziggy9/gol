#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include <SDL2/SDL.h>

#include "./game.h"
#include "./logic.h"
#include "./render.h"

int main(int argc, char** argv)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Could not initialize SDL2: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Window *window = SDL_CreateWindow("Conway's Game",
                                        100, 100,
                                        SCREEN_WIDTH, SCREEN_HEIGHT,
                                        SDL_WINDOW_SHOWN);
  if (window == NULL) {
    fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                              SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) {
    SDL_DestroyWindow(window);
    fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  board_t board = {
    .game_state = PAUSE_STATE
  };

  for (int i = 0; i < COL_NUM; i++) {
    for (int j = 0; j < ROW_NUM; j++)
      board.cell_state[i][j] = DEAD;
  }

  int neighbors[COL_NUM][ROW_NUM] = {DEAD};

  // Initiate event
  SDL_Event e;
  bool quit = false; 
  while (!quit) {
    //Poll event and provide event type to switch statement
    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_KEYDOWN:
          // For keydown events, test for keycode type. See Wiki SDL_Keycode.
          if (e.key.keysym.sym == SDLK_ESCAPE) {
            quit = true;
            break;
          }
          if (e.key.keysym.sym == SDLK_SPACE) {
            if (board.game_state == RUNNING_STATE) {
              board.game_state = PAUSE_STATE;
              printf("Game paused: editing enabled.\n");
              break;
            }
            else if (board.game_state == PAUSE_STATE) {
              board.game_state = RUNNING_STATE;
              printf("Game running.\n");
              break;
            }
          }
          if (e.key.keysym.sym == SDLK_BACKSPACE) {
            for (int i = 0; i < COL_NUM; i++) {
              for (int j = 0; j < ROW_NUM; j++)
                board.cell_state[i][j] = DEAD;
            }
            break;
          }
          break;
        case SDL_MOUSEBUTTONDOWN:
          click_on_cell(&board,
                        e.button.y / CELL_HEIGHT,
                        e.button.x / CELL_WIDTH);
          break;
        default: {}
      }
    }
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 1);
    SDL_RenderClear(renderer);
    render_board(renderer, &board, neighbors);
    SDL_RenderPresent(renderer);
    usleep(TICKS);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
