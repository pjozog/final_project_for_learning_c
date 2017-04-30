#ifndef _SODOKU_BOARD_H
#define _SODOKU_BOARD_H

typedef struct sodoku_board sodoku_board_t;

#define SODOKU_BOARD_NUM_DIGITS 10

sodoku_board_t* sodoku_board_create();
void sodoku_board_destroy(sodoku_board_t* board);

#endif
