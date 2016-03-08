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
    int getScore(Board *board,Move *move);
    bool corner(Move *move);
    bool cornerAccess(Move *move);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
