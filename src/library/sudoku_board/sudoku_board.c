#include "library/sudoku_board/sudoku_board.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE SUDOKU_BOARD_NUM_DIGITS

struct sudoku_board {
  int* data;
};

struct sudoku_board_region {
  int* data;
  sudoku_board_region_type_t type;
};

sudoku_board_t* sudoku_board_create() {
  sudoku_board_t* sb = calloc(1, sizeof *sb);
  sb->data = calloc(SIZE * SIZE, sizeof *sb->data);
  return sb;
}

sudoku_board_t* sudoku_board_copy(const sudoku_board_t* that) {
  sudoku_board_t* sb = sudoku_board_create();
  sb->data = memcpy(sb->data, that->data, SIZE * SIZE * sizeof (*sb->data));
  return sb;
}

void sudoku_board_destroy(sudoku_board_t* sb) {
  free(sb->data);
  free(sb);
}

int sudoku_board_get(const sudoku_board_t* sb, int row, int col) {
  assert(row >= 0 && row < SIZE);
  assert(col >= 0 && col < SIZE);
  return sb->data[row * SIZE + col];
}

void sudoku_board_set(sudoku_board_t* sb, int row, int col, int value) {
  assert(row >= 0 && row < SIZE);
  assert(col >= 0 && col < SIZE);
  assert(value == SUDOKU_BOARD_UNKNOWN || (value >= 1 && value <= SIZE));
  sb->data[row * SIZE + col] = value;
}

void sudoku_board_print(const sudoku_board_t* sb) {
  sudoku_board_fprint(sb, stdout);
}

void sudoku_board_fprint(const sudoku_board_t* sb, FILE* fp) {
  for (int row = 0; row < SIZE; ++row) {
    for (int col = 0; col < SIZE; ++col) {
      if (sudoku_board_get(sb, row, col) == SUDOKU_BOARD_UNKNOWN) {
        fprintf(fp, "_ ");
      } else {
        fprintf(fp, "%d ", sudoku_board_get(sb, row, col));
      }
    }
    fprintf(fp, "\n");
  }
  fprintf(fp, "\n");
}

sudoku_board_t* sudoku_board_fread(FILE* fp) {
  sudoku_board_t* sb = sudoku_board_create();
  int c = 0;
  int i = 0;
  int row = 0;
  int col = 0;
  while ((c = fgetc(fp)) != EOF) {
    if (isdigit(c)) {
      row = i / SIZE;
      col = i % SIZE;
      sudoku_board_set(sb, row, col, c - '0');
      ++i;
    } else if (c == '_') {
      row = i / SIZE;
      col = i % SIZE;
      sudoku_board_set(sb, row, col, SUDOKU_BOARD_UNKNOWN);
      ++i;
    }
  }
  return sb;
}

int sudo_board_equals(const sudoku_board_t* sb_a, const sudoku_board_t* sb_b) {
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      if (sudoku_board_get(sb_a, i, j) != sudoku_board_get(sb_b, i, j)) {
        return 0;
      }
    }
  }
  return 1;
}

sudoku_board_region_t* sudoku_board_region_create(
    const sudoku_board_t* sb, int row, int col,
    sudoku_board_region_type_t type) {
  sudoku_board_region_t* sbr = calloc(1, sizeof *sbr);
  sbr->data = calloc(SIZE, sizeof *sb->data);
  sbr->type = type;
  return sbr;
}

void sudoku_board_region_destroy(sudoku_board_region_t* sbr) {
  free(sbr->data);
  free(sbr);
}
