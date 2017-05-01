#include "library/sudoku_board/sudoku_board.h"

#include <assert.h>

static void test_sudoku_board_create() {
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

static void test_sudoku_board_getset() {
  sudoku_board_t* sb = sudoku_board_create();

  /* set the values; this test assumes that SUDOKU_BOARD_UNKNOWN is 0... */
  int size = SUDOKU_BOARD_NUM_DIGITS;
  int count = 0;
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      sudoku_board_set(sb, i, j, count);
      ++count;
      count = count % (size + 1);
    }
  }

  /* get the values */
  count = 0;
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      assert(sudoku_board_get(sb, i, j) == count);
      ++count;
      count = count % (size + 1);
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
