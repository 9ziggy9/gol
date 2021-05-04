#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "./game.h"
#include "./logic.h"
#include "./render.h"

void usage(void)
{
  printf("\nUsage: conway [-t ticks] [-c cell_size] \n\n-t\tSet number of ticks in microseconds.\n\t");
  printf("Enter extremely low values at own peril.\n\tRecommended to stay in 30000-100000 range.\n\tDefaults to 50000.\n\n"); 
  printf("\n -c\tSet cell size to small, medium or large.\n\tDefaults to small.\n\n");
}

int main(int argc, char** argv)
{
  // Set default rate of ticks.
  int TICKS = 50000;
  
  // Set initial window scaling factor
  float SCALE = 0.5;

  // Configure board initial state.
  board_t board = {
    .game_state = PAUSE_STATE
  };

  board.CELL_WIDTH = 15; // Reasonable default size
  board.CELL_HEIGHT = 15;

  for (int i = 0; i < COL_NUM; i++) {
    for (int j = 0; j < ROW_NUM; j++)
      board.cell_state[i][j] = DEAD;
  }

  int neighbors[COL_NUM][ROW_NUM] = {DEAD};

  // Command line options.
  int opt;

  while((opt = getopt(argc, argv, "t:c:h")) != -1) {
    switch (opt) {
      case 't':
        TICKS = atoi(optarg);
        break;
      case 'c':
        if (strcmp(optarg,"medium") == 0) {
          board.CELL_WIDTH = 30;  
          board.CELL_HEIGHT = 30;
        } 
        else if (strcmp(optarg,"large") == 0) {
          board.CELL_WIDTH = 50;
          board.CELL_HEIGHT = 50;
        }
        else
          break;
        break;
      case 'h':
        usage();
        exit(EXIT_SUCCESS);
        break;
      case '?':
        if (optopt == 't' || optopt == 's' || optopt == 'c')
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
        printf("Setting default options.\n");
        usage();
        break;
      default:
        printf("Setting default options.\n");
        usage();
        break;
    }
  }
  
  // Initialize SDL subsystem
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Could not initialize SDL2: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }
  
  // Grab display dimensions.
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  
  // Set and scale window dimensions.
  int SCREEN_WIDTH = DM.w;
  int SCREEN_HEIGHT = DM.h;
  SCREEN_WIDTH = SCREEN_WIDTH * SCALE ;
  SCREEN_HEIGHT = SCREEN_HEIGHT * SCALE ;

  // An SDL_Rect type called peeper whose scale is fed into
  // SDL_RenderSetViewport() very shortly must also include
  // an offset to ensure boundary conditions along x=0 and
  // y=0 are sufficiently out of frame.
  int PEEPER_SIZE = 10 * SCREEN_WIDTH; // Should be sufficient.
  int PEEPER_OFFSET = PEEPER_SIZE / 4;

  SDL_Rect peeper; // In future may take values from event loop.

  // Create window
  SDL_Window *window = SDL_CreateWindow("Conway's Game",
                                        100, 100,
                                        SCREEN_WIDTH, SCREEN_HEIGHT,
                                        SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  // Create renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                              SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) {
    SDL_DestroyWindow(window);
    fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

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
                        (e.button.y + PEEPER_OFFSET) / board.CELL_HEIGHT,
                        (e.button.x + PEEPER_OFFSET) / board.CELL_WIDTH);
          break;
        default: {}
      }
    }

    // Assignment to viewport
    peeper.x = -PEEPER_OFFSET;
    peeper.y = -PEEPER_OFFSET;
    peeper.w = PEEPER_SIZE;
    peeper.h = PEEPER_SIZE;
    SDL_RenderSetViewport(renderer, &peeper);

    // Draw
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 1);
    SDL_RenderClear(renderer);
    render_board(renderer, &board, neighbors);
    SDL_RenderPresent(renderer);
    usleep(TICKS);
  }

  // Clean up
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
