#include "library/sudoku_board/sudoku_board.h"

int main() {
  sudoku_board_t* sb = sudoku_board_create();
  sudoku_board_destroy(sb);
  return 0;
}
