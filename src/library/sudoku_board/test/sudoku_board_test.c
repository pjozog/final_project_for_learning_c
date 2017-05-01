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

static void test_sudoku_board_fread() {
  FILE *fp_write = fopen("saved.sudoku", "w");

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

  sudoku_board_fprint(sb, fp_write);
  fclose(fp_write);

  /* read the values back in, make sure it's the same */
  FILE *fp_read = fopen("saved.sudoku", "r");
  sudoku_board_t* sb_read = sudoku_board_fread(fp_read);
  fclose(fp_read);
  assert(sudo_board_equals(sb, sb_read));

  sudoku_board_destroy(sb_read);
  sudoku_board_destroy(sb);
}

static void test_sudoku_board_equals() {
  sudoku_board_t* sb_a = sudoku_board_create();
  sudoku_board_t* sb_b = sudoku_board_create();
  sudoku_board_t* sb_c = sudoku_board_create();
  sudoku_board_set(sb_c, 3, 1, 9);
  sudoku_board_t* sb_d = sudoku_board_copy(sb_c);

  assert(sudo_board_equals(sb_a, sb_b));
  assert(sudo_board_equals(sb_c, sb_c));
  assert(sudo_board_equals(sb_c, sb_d));
  assert(!sudo_board_equals(sb_a, sb_c));

  sudoku_board_destroy(sb_a);
  sudoku_board_destroy(sb_b);
  sudoku_board_destroy(sb_c);
  sudoku_board_destroy(sb_d);
}

int main() {
  test_sudoku_board_create();
  test_sudoku_board_getset();
  test_sudoku_board_fread();
  test_sudoku_board_equals();
  return 0;
}
