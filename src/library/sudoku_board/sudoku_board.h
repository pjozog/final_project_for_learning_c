#ifndef _SUDOKU_BOARD_H
#define _SUDOKU_BOARD_H

#include <stdio.h>

#define SUDOKU_BOARD_NUM_DIGITS 9
#define SUDOKU_BOARD_UNKNOWN 0

typedef struct sudoku_board sudoku_board_t;
typedef struct sudoku_board_region sudoku_board_region_t;

typedef enum sudoku_board_region_type {
  SUDOKU_BOARD_REGION_TYPE_ROW,
  SUDOKU_BOARD_REGION_TYPE_COL,
  SUDOKU_BOARD_REGION_TYPE_3X3,
} sudoku_board_region_type_t;

/**
 * Create a new sudoku_board_t; all values are initialized to
 * SUDOKU_BOARD_UNKNOWN. The board row/column convention is as follows:
 *
 *                    _ _ _ _ _ _ _ _ _
 *                    _ _ _ _ _ _ _ _ _
 *                    _ _ _ _ _ _ 1 _ _
 *                    _ _ _ _ _ _ _ _ _
 * This is row 3 --- >_ _ 3 _ _ _ _ _ _
 *                    _ _ _ _ _ _ _ _ _
 *                    _ _ _ _ _ _ _ _ _
 *                    _ _ _ _ _ _ _ _ _
 *                    _ _ _ _ _ _ _ 9 _
 *
 *                        ^
 *                        |
 *                         - This is column 2
 *
 * The returned sudoku board must be destroyed with sudoku_board_destroy().
 */
sudoku_board_t* sudoku_board_create();

/**
 * Make a copy of 'that'. The returned sudoku board must be destroyed with
 * sudoku_board_destroy().
 */
sudoku_board_t* sudoku_board_copy(const sudoku_board_t* that);

/**
 * Destroy the sudoku_board_t
 */
void sudoku_board_destroy(sudoku_board_t* sb);

/**
 * Get the current entry of the board at the provided row and column
 *
 * 'row' and 'col' must both be one of [0, 1, ..., 8]
 */
int sudoku_board_get(const sudoku_board_t* sb, int row, int col);

/**
 * Set the current entry of the board at the provided row and column
 *
 * 'row' and 'col' must both be one of [0, 1, ..., 8]
 *
 * 'value' must be one of [SUDOKU_BOARD_UNKNOWN, 1, 2, ..., 9]
 */
void sudoku_board_set(sudoku_board_t* sb, int row, int col, int value);

/**
 * Print the sudoku board to stdout
 */
void sudoku_board_print(const sudoku_board_t* sb);

/**
 * Print the sudoku board to the file handle provided by 'fp'
 */
void sudoku_board_fprint(const sudoku_board_t* sb, FILE* fp);

/**
 * Returns 1 if sb_a == sb_b, 0 otherwise
 */
int sudo_board_equals(const sudoku_board_t* sb_a, const sudoku_board_t* sb_b);

/**
 * Read the sudoku board from the file handle provided by 'fp'
 */
sudoku_board_t* sudoku_board_fread(FILE* fp);

/**
 * Create a sudoku board region.
 *
 * TODO: Describe what a region is
 */
sudoku_board_region_t* sudoku_board_region_create(
    const sudoku_board_t* sb, int row, int col,
    sudoku_board_region_type_t type);

/**
 * Destroy a sudoku board region.
 */
void sudoku_board_region_destroy(sudoku_board_region_t* sbr);

#endif
