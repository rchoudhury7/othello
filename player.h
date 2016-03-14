#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {

public:
	Board *playBoard;
	Side color;
	Side oppColor;

    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);
    int getScore(Board *board, Side side);
    bool corner(Side side);
    void setBoard(char data[]);
    int minimax(int depth, Side side, Board *board);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
