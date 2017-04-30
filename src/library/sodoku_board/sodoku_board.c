#include "library/sodoku_board/sodoku_board.h"

#include <stdlib.h>

struct sodoku_board {
};

sodoku_board_t* sodoku_board_create() {
  sodoku_board_t* sb = calloc(1, sizeof *sb);
  return sb;
}

void sodoku_board_destroy(sodoku_board_t* sb) {
  free(sb);
}
