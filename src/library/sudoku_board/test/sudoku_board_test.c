#include "library/sudoku_board/sudoku_board.h"

#include <assert.h>

void test_sudoku_board_create() {
  sudoku_board_t* sb = sudoku_board_create();

  int size = SUDOKU_BOARD_NUM_DIGITS;
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      assert(sudoku_board_get(sb, i, j) == SUDOKU_BOARD_UNKNOWN);
    }
  }

  sudoku_board_print(sb);
  sudoku_board_destroy(sb);
}

void test_sudoku_board_getset() {
  sudoku_board_t* sb = sudoku_board_create();

  /* set the values */
  int size = SUDOKU_BOARD_NUM_DIGITS;
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      sudoku_board_set(sb, i, j, 2);
    }
  }

  /* get the values */
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      assert(sudoku_board_get(sb, i, j) == 2);
    }
  }

  sudoku_board_print(sb);
  sudoku_board_destroy(sb);
}

int main() {
  test_sudoku_board_create();
  test_sudoku_board_getset();
  return 0;
}
