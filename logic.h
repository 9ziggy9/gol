#ifndef LOGIC_H_
#define LOGIC_H_

void click_on_cell(board_t* board, int row, int column);

void count_neighbors(board_t* board, int neighbors[COL_NUM][ROW_NUM]);

void evolve(board_t* board, const int neighbors[COL_NUM][ROW_NUM]);

#endif // LOGIC_H_
