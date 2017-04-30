#include "library/sodoku_board/sodoku_board.h"

int main() {
  sodoku_board_t* sb = sodoku_board_create();
  sodoku_board_destroy(sb);
  return 0;
}
